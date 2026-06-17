#!/usr/bin/env python3
"""
tools/match_diff.py — structured, reloc-normalized diff for the agent loop.

Wraps tools/quick_diff.sh (so the compile/canon/postprocess pipeline is
never duplicated), parses its labeled "=== expected ===" / "=== built ==="
canonical instruction streams, and emits machine-readable JSON:

    { "status": "match" | "diffs" | "compile-fail",
      "real_count": <int>,        # RELOC-NORMALIZED root-diff count (progress metric)
      "raw_count":  <int>,        # before normalization (cascade-inflated)
      "tags":  [ {"id","name","hint","section"} , ... ],
      "lines": [ {"expected","built"} , ... ] }     # the differing (normalized) pairs

Why real_count != raw_count:
  The canonical streams already render %hi/%lo/gp_rel relocs identically on
  both sides (`lui r,0x0`, `addiu r,r,0`, `0(gp)`), so those never diff.
  The remaining noise is jump/branch TARGETS:
    * `jal 0 <symguess>` — objdump's nearest-symbol guess differs between the
      target .o and the built .o (different symbol tables), a false diff.
    * `<func+0xNN>` branch targets all shift by the same delta when ONE early
      instruction is added/removed — a single root cause inflated into many
      lines. real_count collapses both so the metric tracks ROOT divergences,
      which is what the plateau rule (tools/match_loop.py) must measure.

Usage:
    tools/match_diff.py <TU> <func>            # JSON to stdout
    tools/match_diff.py --count <TU> <func>    # just the real_count int
"""
from __future__ import annotations
import argparse
import difflib
import hashlib
import json
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

# Mnemonics whose final operand is a branch/jump TARGET (an address/reloc),
# not a real immediate. Targets are normalized away for the root-diff count.
JUMP_MNEMONICS = {
    "j", "jal", "b", "bal",
    "beq", "bne", "beqz", "bnez", "beql", "bnel", "beqzl", "bnezl",
    "blez", "bgez", "bltz", "bgtz", "blezl", "bgezl", "bltzl", "bgtzl",
    "bc1f", "bc1t", "bc1fl", "bc1tl",
}

_ANNOT = re.compile(r"\s*<[^>]*>")          # strip "<func+0xNN>" / "<sym>"
_TRAIL_HEX = re.compile(r"\b[0-9a-f]+\s*$")  # bare hex target (no 0x prefix)

# %hi/%lo address-materialization pair: `lui rX, H` then `addiu rX, rX, L`. The
# H/L immediates are a symbol's %hi/%lo, resolved differently in the isolated
# quick_diff .o than in the per-function target .s (a SAME-TU symbol is an
# external reloc on the target side -> addend 0, but a resolved local .text
# offset on the built side). That is a relocation difference the linker fixes
# (verify_elf is byte-identical), NOT a real diff — so normalize both immediates
# to "T", exactly as jal targets are normalized. SAFE: a frame adjust
# (`addiu sp,sp,-16`) is never preceded by `lui sp`, so this never masks a
# frame-size diff. See the getParallelWindVector false-rc1 (ExecWindField, 2026-06-04).
_LUI_RE   = re.compile(r"^lui\t([^,]+),")
_ADDIU_RE = re.compile(r"^addiu\t([^,]+),([^,]+),")
def normalize_lui_addiu(lines: list[str]) -> list[str]:
    out = list(lines)
    for i in range(len(out) - 1):
        m = _LUI_RE.match(out[i])
        if not m:
            continue
        reg = m.group(1)
        m2 = _ADDIU_RE.match(out[i + 1])
        if m2 and m2.group(1) == reg and m2.group(2) == reg:
            out[i]     = f"lui\t{reg},T"
            out[i + 1] = f"addiu\t{reg},{reg},T"
    return out
_CATN = re.compile(r"\s*\d+\t(.*)")          # `cat -n` prefix: ws + number + tab

# objdump renders `nop` as `sll zero,zero,0x0`; accept both spellings.
_NOP_RE = re.compile(r"^(nop|sll\tzero,zero,0x0|sll\tzero,zero,0)$")
def strip_trailing_align_nops(exp: list[str], blt: list[str]):
    """Drop EXCESS trailing nops from whichever stream is longer. The function's
    real body ends at its declared size; a `nop` past that (the isolated quick_diff
    .o pads the .text section, while the per-function target .s stops at `endlabel`)
    is alignment padding, not a code diff — it false-rc1's a last/only-func TU
    (e.g. ACTGetWish_FromPad). Only the EXCESS is stripped, so an intra-body nop
    that lines up with a real insn in the other stream is untouched; ninja
    verify_elf remains the final authority."""
    e, b = list(exp), list(blt)
    while len(b) > len(e) and b and _NOP_RE.match(b[-1].strip()):
        b.pop()
    while len(e) > len(b) and e and _NOP_RE.match(e[-1].strip()):
        e.pop()
    return e, b


def run_quick_diff(tu: str, func: str | None) -> str:
    """Invoke quick_diff.sh; return combined stdout (it never exits nonzero
    on a plain diff, only on usage/compile problems). `func` may be omitted
    (single-arg form, mirroring quick_diff.sh's own <NAME> [func] signature)."""
    cmd = ["bash", str(ROOT / "tools" / "quick_diff.sh"), tu]
    if func:
        cmd.append(func)
    proc = subprocess.run(cmd, capture_output=True, text=True, cwd=str(ROOT))
    return proc.stdout + proc.stderr


def parse_blocks(out: str):
    """Extract the expected/built canonical instruction streams from the
    `cat -n` blocks. Returns (expected_lines, built_lines) or (None, None)
    if the markers are absent (compile-fail / usage error)."""
    exp: list[str] | None = None
    blt: list[str] | None = None
    cur: list[str] | None = None
    for line in out.splitlines():
        if line.startswith("=== expected:"):
            exp = []; cur = exp; continue
        if line.startswith("=== built:"):
            blt = []; cur = blt; continue
        if line.startswith("==="):
            cur = None; continue
        if cur is None:
            continue
        m = _CATN.match(line)
        if m:
            cur.append(m.group(1))
    return exp, blt


def normalize(line: str) -> str:
    """Collapse jump/branch target addresses + objdump symbol guesses so a
    single structural shift doesn't inflate the count."""
    line = _ANNOT.sub("", line).rstrip()
    mnem = line.split("\t", 1)[0].strip()
    if mnem in JUMP_MNEMONICS:
        line = _TRAIL_HEX.sub("T", line)
    return line


def count_and_pairs(a: list[str], b: list[str]):
    """Diff two instruction streams; return (count, differing_pairs)."""
    sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
    count = 0
    pairs = []
    for op, i1, i2, j1, j2 in sm.get_opcodes():
        if op == "equal":
            continue
        count += max(i2 - i1, j2 - j1)
        le, lb = a[i1:i2], b[j1:j2]
        for k in range(max(len(le), len(lb))):
            pairs.append({
                "expected": le[k] if k < len(le) else "",
                "built": lb[k] if k < len(lb) else "",
            })
    return count, pairs


def _mnem(line: str) -> str:
    return line.split("\t", 1)[0].strip()


def divergence_sites(a: list[str], b: list[str], ctx: int = 3):
    """Map EVERY place the two normalized streams diverge.

    The skill's core doctrine is "a high real_count is usually ONE root cause
    cascading — fix the root." For a long function that residual is really N
    sub-problems, so a scalar count hides the structure. This returns the full
    list of non-equal opcode blocks, each tagged with:
      * exp_index — 0-based position in the expected stream
      * block     — basic-block number (count of branch/jump insns before it),
                    so on a long func you see "sites at block 2, 9, 14"
      * context   — `ctx` shared insns just before the split (the first site)
      * expected / built — the diverging lines on each side
    `len(sites) == 1` means the whole residual is a single root.
    """
    sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
    sites = []
    for op, i1, i2, j1, j2 in sm.get_opcodes():
        if op == "equal":
            continue
        block = sum(1 for l in a[:i1] if _mnem(l) in JUMP_MNEMONICS)
        site = {"kind": op, "exp_index": i1, "block": block,
                "expected": a[i1:i2], "built": b[j1:j2]}
        if not sites:                       # leading context on the FIRST site
            site["context"] = a[max(0, i1 - ctx):i1]
        sites.append(site)
    return sites


def detect_scheduling(nexp: list[str], nblt: list[str]):
    """Flag a PURE SCHEDULING diff: the differing instructions on each side are
    the SAME multiset, just reordered (incl. moved into/out of a delay slot).
    This is the signature that the residual is an ORDERING problem, not codegen
    — so the lever is source-order / live-range / -fno-schedule-insns2 (per the
    pass that moved it), NOT a fresh C operation. Points at tools/sched_diff.py
    to see which pass did the move."""
    import collections
    sm = difflib.SequenceMatcher(None, nexp, nblt, autojunk=False)
    exp_diff, blt_diff = [], []
    for op, i1, i2, j1, j2 in sm.get_opcodes():
        if op == "equal":
            continue
        exp_diff += nexp[i1:i2]
        blt_diff += nblt[j1:j2]
    if not exp_diff:
        return None
    ce, cb = collections.Counter(exp_diff), collections.Counter(blt_diff)
    if ce != cb:
        return None
    # pure permutation: every differing insn on one side appears on the other
    moved = sorted(set(exp_diff))
    return {
        "permutation": True,
        "moved_insns": moved[:8],
        "moved_total": len(moved),
        "hint": "pure reorder (same insns, different slots) — ordering, not "
                "codegen. Run `tools/sched_diff.py <TU> <func>` and read the "
                "move map: moved@sched -> source-order/live-range lever; "
                "moved@sched2 -> -fno-schedule-insns2; moved@dbr -> delay-slot "
                "readiness (keep the insn's inputs live to the branch).",
    }


def run_tag_diff(exp: list[str], blt: list[str]):
    """Call tools/tag_diff.py on the two streams; parse `[§N.M] name` output
    into structured tags."""
    with tempfile.NamedTemporaryFile("w", suffix=".exp", delete=False) as fe, \
         tempfile.NamedTemporaryFile("w", suffix=".blt", delete=False) as fb:
        fe.write("\n".join(exp) + "\n")
        fb.write("\n".join(blt) + "\n")
        ep, bp = fe.name, fb.name
    try:
        py = ROOT / ".venv" / "bin" / "python"
        py = str(py) if py.exists() else sys.executable
        proc = subprocess.run(
            [py, str(ROOT / "tools" / "tag_diff.py"), ep, bp],
            capture_output=True, text=True, cwd=str(ROOT),
        )
    finally:
        Path(ep).unlink(missing_ok=True)
        Path(bp).unlink(missing_ok=True)
    tags = []
    cur = None
    for line in proc.stdout.splitlines():
        m = re.match(r"\[§([0-9A-Za-z.\-/ ]+)\]\s+(.*)", line.strip())
        if m:
            cur = {"id": m.group(1), "name": m.group(2), "hint": "", "section": m.group(1).replace(".", "")}
            tags.append(cur)
        elif cur is not None and line.strip().startswith("→"):
            cur["hint"] = line.strip()[1:].strip()
    return tags


def analyze(tu: str, func: str | None) -> dict:
    out = run_quick_diff(tu, func)
    if "COMPILE-FAIL" in out or "compile" in out.lower() and "error" in out.lower() and "===" not in out:
        return {"status": "compile-fail", "real_count": -1, "raw_count": -1,
                "tags": [], "lines": [], "detail": out.strip().splitlines()[-5:]}
    exp, blt = parse_blocks(out)
    if exp is None or blt is None:
        return {"status": "compile-fail", "real_count": -1, "raw_count": -1,
                "tags": [], "lines": [], "detail": out.strip().splitlines()[-5:]}
    if "MATCH (canonical instruction stream identical)" in out:
        return {"status": "match", "real_count": 0, "raw_count": 0, "tags": [], "lines": []}

    exp, blt = strip_trailing_align_nops(exp, blt)
    raw_count, _ = count_and_pairs(exp, blt)
    nexp = normalize_lui_addiu([normalize(l) for l in exp])
    nblt = normalize_lui_addiu([normalize(l) for l in blt])
    real_count, pairs = count_and_pairs(nexp, nblt)
    sites = divergence_sites(nexp, nblt)
    tags = run_tag_diff(exp, blt)
    sched = detect_scheduling(nexp, nblt)
    status = "match" if real_count == 0 else "diffs"
    # codegen_sig: a stable hash of the NORMALIZED built instruction stream.
    # Two edits that compile to the same instructions (cosmetic no-ops, or
    # reloc/symbol-guess-only differences the normalization already folds) get
    # the SAME sig — so the driver/stall machinery can tell a genuinely-distinct
    # codegen attempt from a re-spelling. Uses nblt (normalized), matching the
    # real_count metric, NOT raw object bytes.
    codegen_sig = hashlib.sha1("\n".join(nblt).encode("utf-8", "replace")).hexdigest()[:16]
    result = {"status": status, "real_count": real_count, "raw_count": raw_count,
              "diff_sites": len(sites),
              "first_divergence": sites[0] if sites else None,
              "divergence_map": sites,
              "codegen_sig": codegen_sig,
              "tags": tags, "lines": pairs}
    if sched:
        result["scheduling"] = sched
    return result


def main() -> int:
    ap = argparse.ArgumentParser(description="reloc-normalized structured diff")
    ap.add_argument("tu")
    ap.add_argument("func", nargs="?", default=None)
    ap.add_argument("--count", action="store_true",
                    help="print only the real_count integer")
    ap.add_argument("--full", action="store_true",
                    help="emit ALL differing lines (default: a compact sample, to save tokens)")
    args = ap.parse_args()
    result = analyze(args.tu, args.func)
    if args.count:
        print(result["real_count"])
        return 0 if result["status"] in ("match", "diffs") else 2
    # Token discipline: the cascade can be dozens of lines; the tags + a small
    # representative sample are enough to pick a lever. Full dump behind --full.
    if not args.full and len(result.get("lines", [])) > 8:
        result["lines_total"] = len(result["lines"])
        result["lines"] = result["lines"][:8]
        result["lines_note"] = "sample (pass --full for all); reason from tags + sample"
    # The divergence_map (#5) can be long on a big func; keep a compact head
    # unless --full. first_divergence already carries the root block in full.
    dmap = result.get("divergence_map")
    if not args.full and dmap and len(dmap) > 6:
        result["divergence_map_total"] = len(dmap)
        result["divergence_map"] = dmap[:6]
        result["divergence_map_note"] = "first 6 sites (pass --full for all); see `block` for region"
    print(json.dumps(result, indent=2))
    return 0 if result["status"] in ("match", "diffs") else 2


if __name__ == "__main__":
    sys.exit(main())
