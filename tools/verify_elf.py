#!/usr/bin/env python3
"""
verify_elf.py: confirm the SHA-1 of an extracted or built artifact matches
the value recorded in config/sha1sums.<ver>.txt.

tools/build.sh setup runs it on the base ELF and ROM. Exits 0 on match,
non-zero on mismatch or missing target.

Each target records its own hashes in config/sha1sums.<ver>.txt, keyed by
BASENAME (baseelf.elf / baseelf.rom), so the same lookup works for every
target's baserom/<ver>/ (tools/ico_version.py; <ver> is VERSION, or the first
configured target). (The built ROM's SHA-1 is checked by tools/check_elf.py
--gate.)

    verify_elf.py --target baserom/<ver>/baseelf.elf
    verify_elf.py --target baserom/<ver>/baseelf.rom
"""

from __future__ import annotations

import argparse
import hashlib
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(Path(__file__).resolve().parent))
from ico_version import detect_version, link_map_path, sha1sums_path  # noqa: E402

VERSION = detect_version(REPO_ROOT)
SHA1SUMS = sha1sums_path(REPO_ROOT, VERSION)
LINK_MAP = link_map_path(REPO_ROOT, VERSION).relative_to(REPO_ROOT)


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
    args = ap.parse_args(argv)

    target: Path = args.target
    if not target.exists():
        print(f"verify_elf: target not found: {target}", file=sys.stderr)
        return 2

    name = target.name
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
        f"  actual:   {actual}\n"
        f"  localize: tools/check_elf.py --gate names the section that "
        f"differs, and {LINK_MAP} names the object at that address.",
        file=sys.stderr,
    )
    return 1


if __name__ == "__main__":
    sys.exit(main())
