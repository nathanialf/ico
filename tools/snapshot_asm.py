#!/usr/bin/env python3
"""
snapshot_asm.py — capture a stable copy of `asm/cod/` and
`asm/matchings/cod/` into `decomp/asm_snapshot/`.

The matching pipeline (auto-permuter / batch-claim loops) periodically
nukes and regenerates `asm/cod/*.s` via `rm asm/cod/*.s + make setup`.
Analysis tools that read those files get flaky output if they happen to
land in that window. Snapshotting once into a stable location lets the
analysis pipeline run independently of matching activity.

This script is read-only with respect to the live matching pipeline —
it only writes to `decomp/asm_snapshot/`.

Run: `.venv/bin/python tools/snapshot_asm.py`

Refuses to run if `asm/cod/` is empty (matching loop is mid-cycle);
re-run after the loop regenerates the segment files.
"""

from __future__ import annotations

import shutil
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
# Splat emits cod-segment .s files to asm/src/cod/ (after the repo's
# "flatten to repo root" reorganization). Snapshot mirrors them into
# decomp/asm_snapshot/cod/ so downstream readers (identify_tus,
# find_callgraph, find_boundaries, ...) don't need to know the live
# path — they only consume the snapshot view.
ASM_COD_SRC = REPO_ROOT / "asm" / "src" / "cod"
# Whole matchings/ and nonmatchings/ trees — both have a mixed layout
# (flattened src/ios/isys/sound subdirs + legacy cod/<offset> dirs +
# bare per-TU dirs at the top level like `Basic/`). Snapshot copies
# everything; analyzer rglobs for func_*.s files.
ASM_MATCHINGS_SRC = REPO_ROOT / "asm" / "matchings"
ASM_NONMATCHINGS_SRC = REPO_ROOT / "asm" / "nonmatchings"
SNAPSHOT_ROOT = REPO_ROOT / "decomp" / "asm_snapshot"
SNAPSHOT_COD = SNAPSHOT_ROOT / "cod"
SNAPSHOT_MATCHINGS = SNAPSHOT_ROOT / "matchings"
SNAPSHOT_NONMATCHINGS = SNAPSHOT_ROOT / "nonmatchings"


def snapshot(src: Path, dst: Path, label: str, glob: str = "*.s") -> int:
    """Mirror `src/**/<glob>` into `dst`, replacing any prior snapshot.
    Returns the number of files copied."""
    if not src.exists():
        return 0
    files = list(src.rglob(glob))
    if not files:
        return 0
    if dst.exists():
        shutil.rmtree(dst)
    dst.mkdir(parents=True)
    for f in files:
        rel = f.relative_to(src)
        target = dst / rel
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(f, target)
    print(f"snapshot_asm: {label}: copied {len(files)} file(s) into "
          f"{dst.relative_to(REPO_ROOT)}/")
    return len(files)


def main() -> int:
    SNAPSHOT_ROOT.mkdir(parents=True, exist_ok=True)

    cod_files = list(ASM_COD_SRC.glob("*.s")) if ASM_COD_SRC.exists() else []
    if cod_files:
        n_cod = snapshot(ASM_COD_SRC, SNAPSHOT_COD, "asm/cod")
    else:
        # Matching loop is mid-cycle (`rm asm/cod/*.s + make setup`).
        # Don't wipe the existing cod snapshot — it's still the most
        # recent stable copy. matchings/ and nonmatchings/ are NOT
        # cleared by the loop, so we can still refresh those.
        existing = len(list(SNAPSHOT_COD.rglob("*.s"))) if SNAPSHOT_COD.exists() else 0
        print(f"snapshot_asm: asm/cod/ is empty (matching loop "
              f"mid-cycle); keeping previous cod snapshot "
              f"({existing} file(s)).")
        n_cod = 0

    n_matchings = snapshot(ASM_MATCHINGS_SRC, SNAPSHOT_MATCHINGS,
                           "asm/matchings", glob="func_*.s")
    n_nonmatchings = snapshot(ASM_NONMATCHINGS_SRC, SNAPSHOT_NONMATCHINGS,
                              "asm/nonmatchings", glob="func_*.s")

    print(f"snapshot_asm: copied {n_cod} cod + {n_matchings} matchings "
          f"+ {n_nonmatchings} nonmatchings = "
          f"{n_cod + n_matchings + n_nonmatchings} file(s) into "
          f"{SNAPSHOT_ROOT.relative_to(REPO_ROOT)}/")
    return 0


if __name__ == "__main__":
    sys.exit(main())
