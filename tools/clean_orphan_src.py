#!/usr/bin/env python3
"""tools/clean_orphan_src.py — flag (or delete) orphan src/cod/*.c files.

When a yaml subsegment flips from `[0xVMA, c, cod/VMA]` to a coalesced
TU name like `[0xVMA, c, sugiTree]`, the old `src/cod/VMA.c` becomes
dead weight. `tools/gen_ninja.py::discover_sidecar_objs` rglobs
`src/**/*.c` and adds every match to the link graph, so a leftover
`src/cod/VMA.c` produces a duplicate-symbol link failure against the
new TU `.o`.

This tool scans `config/ico.us.yaml` for live `[..., c, cod/VMA]`
subsegments, lists every `src/cod/*.c` on disk, and flags any source
whose hex stem is not covered.

Default action: print the orphan list and exit non-zero (so setup
fails loudly). With `--delete`, the orphan .c/.s sources AND their
`build/src/cod/VMA.*` artifacts are removed.

Wired into `tools/build.sh setup` between `split` and `regen_ninja`,
so every setup invocation catches stale files before the next ninja.
"""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
YAML = REPO / "config" / "ico.us.yaml"
SRC_COD = REPO / "src" / "cod"
BUILD_SRC_COD = REPO / "build" / "src" / "cod"

# Match yaml subseg `- [0xVMA, {c|hasm}, cod/VMA]` (with whitespace
# tolerance). `c` ⇒ src/cod/<hex>.c; `hasm` ⇒ src/cod/<hex>.s. Both
# are live sources we must preserve. We do NOT match TU-promoted
# entries like `[0xF16A0, c, sugiTree]` — those live at `src/<name>.c`,
# not `src/cod/<hex>.c`, and are protected from this scan.
SUBSEG_COD_RE = re.compile(
    r"^\s*-\s*\[\s*0x[0-9A-Fa-f]+\s*,\s*(?:c|hasm)\s*,\s*cod/([0-9A-Fa-f]+)\s*\]",
)


def live_cod_stems() -> set[str]:
    """Hex stems referenced as `cod/<stem>` in a live `c` subseg."""
    stems: set[str] = set()
    for line in YAML.read_text().splitlines():
        m = SUBSEG_COD_RE.match(line)
        if m:
            stems.add(m.group(1).upper())
    return stems


def on_disk_cod_stems() -> dict[str, list[Path]]:
    """Map `<HEX>` → list of related on-disk paths (src + build sidecars)."""
    out: dict[str, list[Path]] = {}
    if SRC_COD.is_dir():
        for p in sorted(SRC_COD.iterdir()):
            stem = p.stem.upper()
            if not re.fullmatch(r"[0-9A-F]+", stem):
                continue
            out.setdefault(stem, []).append(p)
    return out


def build_artifacts(stem: str) -> list[Path]:
    """Stale build/* artifacts for a given hex stem."""
    out: list[Path] = []
    if not BUILD_SRC_COD.is_dir():
        return out
    for p in BUILD_SRC_COD.iterdir():
        if p.stem.upper() == stem or p.name.upper().startswith(f"{stem}."):
            out.append(p)
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n", 1)[0])
    ap.add_argument(
        "--delete",
        action="store_true",
        help="Remove orphan src/cod/*.c (and any stale build/src/cod/*.{o,d,s}).",
    )
    args = ap.parse_args()

    live = live_cod_stems()
    on_disk = on_disk_cod_stems()
    orphans = {stem: paths for stem, paths in on_disk.items() if stem not in live}

    if not orphans:
        print(f"clean_orphan_src: no orphans ({len(live)} live cod/ subsegs)")
        return 0

    print(
        f"clean_orphan_src: {len(orphans)} orphan src/cod/*.c "
        f"file(s) not referenced by any live `c, cod/<hex>` subseg in {YAML.name}:"
    )
    for stem in sorted(orphans):
        for p in orphans[stem]:
            print(f"  src: {p.relative_to(REPO)}")
        for bp in build_artifacts(stem):
            print(f"  art: {bp.relative_to(REPO)}")

    if not args.delete:
        print(
            "\nRe-run with --delete to remove them, or restore the yaml subseg.\n"
            "(Hooked into tools/build.sh setup — left orphans block the next ninja.)"
        )
        return 1

    removed = 0
    for stem, paths in orphans.items():
        for p in paths:
            p.unlink()
            removed += 1
            print(f"  rm {p.relative_to(REPO)}")
        for bp in build_artifacts(stem):
            bp.unlink()
            removed += 1
            print(f"  rm {bp.relative_to(REPO)}")
    print(f"clean_orphan_src: removed {removed} file(s).")
    return 0


if __name__ == "__main__":
    sys.exit(main())
