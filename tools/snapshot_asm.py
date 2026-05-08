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
ASM_COD_SRC = REPO_ROOT / "asm" / "cod"
ASM_MATCHINGS_SRC = REPO_ROOT / "asm" / "matchings" / "cod"
SNAPSHOT_ROOT = REPO_ROOT / "decomp" / "asm_snapshot"
SNAPSHOT_COD = SNAPSHOT_ROOT / "cod"
SNAPSHOT_MATCHINGS = SNAPSHOT_ROOT / "matchings" / "cod"


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
    cod_files = list(ASM_COD_SRC.glob("*.s")) if ASM_COD_SRC.exists() else []
    if not cod_files:
        sys.exit(f"snapshot_asm: {ASM_COD_SRC.relative_to(REPO_ROOT)}/ "
                 "is empty — matching loop is mid-cycle. Wait for "
                 "splat to regenerate segment .s files, then re-run.")

    SNAPSHOT_ROOT.mkdir(parents=True, exist_ok=True)

    n_cod = snapshot(ASM_COD_SRC, SNAPSHOT_COD, "asm/cod")
    n_matchings = snapshot(ASM_MATCHINGS_SRC, SNAPSHOT_MATCHINGS,
                           "asm/matchings/cod", glob="func_*.s")

    print(f"snapshot_asm: total {n_cod + n_matchings} file(s) in "
          f"{SNAPSHOT_ROOT.relative_to(REPO_ROOT)}/")
    return 0


if __name__ == "__main__":
    sys.exit(main())
