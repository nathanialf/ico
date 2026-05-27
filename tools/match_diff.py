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
_CATN = re.compile(r"\s*\d+\t(.*)")          # `cat -n` prefix: ws + number + tab


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

    raw_count, _ = count_and_pairs(exp, blt)
    nexp = [normalize(l) for l in exp]
    nblt = [normalize(l) for l in blt]
    real_count, pairs = count_and_pairs(nexp, nblt)
    tags = run_tag_diff(exp, blt)
    status = "match" if real_count == 0 else "diffs"
    return {"status": status, "real_count": real_count, "raw_count": raw_count,
            "tags": tags, "lines": pairs}


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
    print(json.dumps(result, indent=2))
    return 0 if result["status"] in ("match", "diffs") else 2


if __name__ == "__main__":
    sys.exit(main())
