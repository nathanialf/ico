#!/usr/bin/env python3
"""
verify_elf.py — confirm the SHA-1 of an extracted or built artifact matches
the value recorded in config/sha1sums.txt.

Used by the Makefile as a build-time oracle. Exits 0 on match, non-zero on
mismatch or missing target.

The recorded-name lookup defaults to the basename of --target, but can be
overridden with --name (useful when verifying build/ico.rom against the
'baseelf.rom' entry).

    verify_elf.py --target baserom/baseelf.elf
    verify_elf.py --target baserom/baseelf.rom
    verify_elf.py --target build/ico.rom --name baseelf.rom
"""

from __future__ import annotations

import argparse
import hashlib
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
SHA1SUMS = REPO_ROOT / "config" / "sha1sums.txt"


def load_recorded(name: str) -> str | None:
    if not SHA1SUMS.exists():
        return None
    for line in SHA1SUMS.read_text().splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        parts = line.split()
        if len(parts) >= 2 and parts[1] == name:
            return parts[0]
    return None


def sha1_of(path: Path) -> str:
    h = hashlib.sha1()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def main(argv: list[str] | None = None) -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--target", required=True, type=Path,
                    help="path to artifact to verify")
    ap.add_argument("--name", default=None,
                    help="name to look up in sha1sums.txt "
                         "(default: basename of --target)")
    args = ap.parse_args(argv)

    target: Path = args.target
    if not target.exists():
        print(f"verify_elf: target not found: {target}", file=sys.stderr)
        return 2

    name = args.name or target.name
    recorded = load_recorded(name)
    if recorded is None:
        print(
            f"verify_elf: no recorded SHA-1 for '{name}' in "
            f"{SHA1SUMS.relative_to(REPO_ROOT)}.\n"
            "  Run tools/extract_elf.sh first to record it.",
            file=sys.stderr,
        )
        return 3

    actual = sha1_of(target)
    if actual == recorded:
        print(f"verify_elf: OK ({target} sha1={actual})")
        return 0

    print(
        f"verify_elf: MISMATCH\n"
        f"  target:   {target}\n"
        f"  expected: {recorded}\n"
        f"  actual:   {actual}",
        file=sys.stderr,
    )
    return 1


if __name__ == "__main__":
    sys.exit(main())
