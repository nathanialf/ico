#!/usr/bin/env python3
"""
find_boundaries.py — detect likely TU file boundaries in `.text`.

Mirrors what spimdisasm reports under splat's `find_file_boundaries:
True` option, but as a pure read-only analyzer that never touches the
splat config or the build pipeline.

Heuristics (in order of confidence):

1. **Synthetic single-`nop` functions.** Splat sometimes labels a lone
   alignment-padding nop as a function (size 0x4, body is just `nop`).
   These are not real functions; they're padding the linker inserted
   between two TUs to align the next TU's `.text` start. Strong
   boundary marker — boundary lies *immediately after* this fake func.

2. **Trailing nop padding within a function.** A function that ends
   with multiple consecutive nops *after* its `jr $ra` delay slot
   indicates the assembler/linker padded the function's tail to align
   the next TU. Boundary lies after the padding.

3. **vram gap between consecutive functions.** If function X ends at
   `vram_end_X` and the next function Y starts at `vram_Y > vram_end_X`,
   the gap is padding bytes — almost always a TU boundary.

Output: `decomp/boundaries.json` — list of
  {vma: <addr>, kind: synthetic_nop|trailing_nop|gap, evidence: str}

Read-only; zero build impact. Compares cleanly against `decomp/tu_map.md`
TU regions for confidence checks.

Run: `.venv/bin/python tools/find_boundaries.py`
"""

from __future__ import annotations

import json
import re
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
OUT_PATH = REPO_ROOT / "decomp" / "boundaries.json"
# Read from snapshot to stay isolated from the live matching loop.
ASM_COD_DIR = REPO_ROOT / "decomp" / "asm_snapshot" / "cod"
ASM_MATCHINGS_DIR = REPO_ROOT / "decomp" / "asm_snapshot" / "matchings" / "cod"

GLABEL_RE = re.compile(r"^glabel\s+(func_[0-9A-Fa-f]+)\s*$")
ENDLABEL_RE = re.compile(r"^endlabel\s+(func_[0-9A-Fa-f]+)\s*$")
INSN_VRAM_RE = re.compile(r"^\s*/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)\s+[0-9A-Fa-f]+\s*\*/\s*(\w+)")


def parse_funcs(sfile: Path) -> list[dict]:
    """Return a list of function bodies from one .s file:
       {name, vram_start, instructions: [(vram, mnemonic), ...]}."""
    funcs: list[dict] = []
    cur: dict | None = None

    def flush() -> None:
        nonlocal cur
        if cur and cur["instructions"]:
            funcs.append(cur)
        cur = None

    for line in sfile.read_text(errors="ignore").splitlines():
        m = GLABEL_RE.match(line)
        if m:
            flush()
            cur = {"name": m.group(1), "vram_start": None,
                   "instructions": []}
            continue
        if ENDLABEL_RE.match(line):
            flush()
            continue
        if cur is None:
            continue
        mv = INSN_VRAM_RE.match(line)
        if mv:
            vram = int(mv.group(1), 16)
            mnem = mv.group(2)
            if cur["vram_start"] is None:
                cur["vram_start"] = vram
            cur["instructions"].append((vram, mnem))
    flush()
    return funcs


def detect_boundaries(funcs: list[dict]) -> list[dict]:
    """Walk vram-sorted functions; emit boundary candidates."""
    funcs = sorted(funcs, key=lambda f: f["vram_start"] or 0)
    out: list[dict] = []

    for i, f in enumerate(funcs):
        insns = f["instructions"]
        if not insns:
            continue
        last_vram, last_mnem = insns[-1]

        # 1. All-nop body → synthetic boundary marker.
        if all(m == "nop" for _, m in insns):
            out.append({
                "vma": last_vram + 4,
                "kind": "synthetic_nop",
                "evidence": (f"`{f['name']}` is "
                             f"{len(insns)} nop(s) at "
                             f"0x{f['vram_start']:08x}"),
            })
            continue

        # 2. Trailing-nop padding (>=2 nops at end after the jr-delay
        # slot's nop). The last "real" nop is the delay slot — extras
        # beyond that indicate alignment padding.
        trailing = 0
        for _, m in reversed(insns):
            if m == "nop":
                trailing += 1
            else:
                break
        # Allow exactly one trailing nop (delay slot or real nop). Two
        # or more is suspicious.
        if trailing >= 2:
            out.append({
                "vma": last_vram + 4,
                "kind": "trailing_nop",
                "evidence": (f"`{f['name']}` ends with {trailing} "
                             f"trailing nop(s) at 0x{insns[-trailing][0]:08x}"),
            })

        # 3. vram gap to the next function.
        if i + 1 < len(funcs):
            nxt = funcs[i + 1]
            expected_next = last_vram + 4
            if nxt["vram_start"] and nxt["vram_start"] > expected_next:
                gap = nxt["vram_start"] - expected_next
                out.append({
                    "vma": expected_next,
                    "kind": "gap",
                    "evidence": (f"{gap}-byte gap between "
                                 f"`{f['name']}` end (0x{expected_next:08x}) "
                                 f"and `{nxt['name']}` start "
                                 f"(0x{nxt['vram_start']:08x})"),
                })
    return out


def main() -> int:
    if not ASM_COD_DIR.exists():
        sys.exit(f"find_boundaries: {ASM_COD_DIR.relative_to(REPO_ROOT)}/ "
                 "missing — run `tools/snapshot_asm.py` first.")
    all_funcs: list[dict] = []
    for sfile in sorted(ASM_COD_DIR.glob("*.s")):
        all_funcs.extend(parse_funcs(sfile))
    if ASM_MATCHINGS_DIR.exists():
        for sfile in sorted(ASM_MATCHINGS_DIR.rglob("func_*.s")):
            all_funcs.extend(parse_funcs(sfile))

    print(f"find_boundaries: parsed {len(all_funcs)} function bodies")

    # Dedup by vram_start (segment + matchings can both contain the
    # same function in some splat configurations).
    by_vram: dict[int, dict] = {}
    for f in all_funcs:
        v = f["vram_start"]
        if v is not None and v not in by_vram:
            by_vram[v] = f

    boundaries = detect_boundaries(list(by_vram.values()))

    # Order by vma; dedup adjacent entries that point to the same vma
    # (e.g. a synthetic_nop and a gap can both flag the same boundary).
    boundaries.sort(key=lambda b: (b["vma"], b["kind"]))
    dedup: list[dict] = []
    seen_vma: set[int] = set()
    for b in boundaries:
        if b["vma"] in seen_vma:
            continue
        seen_vma.add(b["vma"])
        dedup.append(b)

    OUT_PATH.write_text(json.dumps(dedup, indent=2) + "\n")

    by_kind: dict[str, int] = {}
    for b in dedup:
        by_kind[b["kind"]] = by_kind.get(b["kind"], 0) + 1
    print(f"find_boundaries: {len(dedup)} unique boundary candidates")
    for k, n in sorted(by_kind.items(), key=lambda kv: -kv[1]):
        print(f"  {k:<16} {n:>5}")
    print(f"find_boundaries: wrote {OUT_PATH.relative_to(REPO_ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
