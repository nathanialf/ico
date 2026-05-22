#!/usr/bin/env python3
"""
extract_assets.py — dump the ISO-level files from the user's ICO disc image
to assets/disc/, recording each file's SHA-1 in config/sha1sums.txt.

Reuses the cooked ISO produced by tools/extract_elf.py (baserom/Ico_USA.iso).

By default this extracts everything *except*:
  - SCUS_971.13          (the boot ELF — already pulled out as baseelf.elf)
  - LDUMMY.              (10 MiB of zero padding)
  - DFDATAS/DATA.DF      (539 MiB asset container — needs a separate parser)

Pass --include-data-df to also dump DATA.DF (slow, big). Pass --include-ldummy
to also dump the padding file (mostly useful for sanity checks).

Output filenames are lowercased and have the ISO9660 ';1' version stripped.

assets/ is gitignored, so nothing extracted here ever leaves the working copy.
"""

from __future__ import annotations

import argparse
import hashlib
import io
import sys
from pathlib import Path

import pycdlib

REPO_ROOT = Path(__file__).resolve().parent.parent
BASEROM_DIR = REPO_ROOT / "baserom"
ISO = BASEROM_DIR / "Ico_USA.iso"
ASSETS_DIR = REPO_ROOT / "assets" / "disc"
SHA1SUMS = REPO_ROOT / "config" / "sha1sums.txt"

DEFAULT_SKIP = {
    "SCUS_971.13",          # boot ELF, see baseelf.elf
}

OPTIONAL_SKIP = {
    "LDUMMY.": "--include-ldummy",
    "DFDATAS/DATA.DF": "--include-data-df",
}

SHA1SUMS_SECTION_HEADER = "# --- assets/disc/* (extracted from user's disc image) ---"


def normalize_iso_path(p: str) -> str:
    """'/DFDATAS/DATA.DF;1' -> 'DFDATAS/DATA.DF'."""
    p = p.lstrip("/")
    return p.split(";", 1)[0]


def local_name(iso_path_norm: str) -> Path:
    """Map an ISO path to a local filesystem path under assets/disc/.

    Lowercases components so we don't end up with SHOUTY filenames everywhere.
    """
    return ASSETS_DIR / iso_path_norm.lower()


def sha1_of(path: Path) -> str:
    h = hashlib.sha1()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def list_iso_files(iso_path: Path) -> list[tuple[str, int]]:
    """Walk the ISO and return [(normalized_path, size_bytes)] for all files."""
    iso = pycdlib.PyCdlib()
    iso.open(str(iso_path))
    try:
        out: list[tuple[str, int]] = []
        for dirname, _dirlist, filelist in iso.walk(iso_path="/"):
            for f in filelist:
                iso_p = (dirname.rstrip("/") + "/" + f) if dirname != "/" else "/" + f
                rec = iso.get_record(iso_path=iso_p)
                norm = normalize_iso_path(iso_p)
                out.append((norm, rec.get_data_length()))
        return out
    finally:
        iso.close()


def extract_one(iso_path: Path, iso_member_norm: str, out_path: Path) -> None:
    """Stream a named file from the ISO to out_path."""
    iso = pycdlib.PyCdlib()
    iso.open(str(iso_path))
    try:
        candidates = [f"/{iso_member_norm};1", f"/{iso_member_norm}"]
        last_err: Exception | None = None
        for p in candidates:
            try:
                out_path.parent.mkdir(parents=True, exist_ok=True)
                with out_path.open("wb") as dst:
                    iso.get_file_from_iso_fp(dst, iso_path=p)
                return
            except pycdlib.pycdlibexception.PyCdlibException as exc:
                last_err = exc
                continue
        raise SystemExit(
            f"extract_assets: '{iso_member_norm}' not found at any of "
            f"{candidates} ({last_err})"
        )
    finally:
        iso.close()


def read_sha1sums() -> dict[str, str]:
    """Return {name: sha1} for current sha1sums.txt entries (ignores comments)."""
    out: dict[str, str] = {}
    if not SHA1SUMS.exists():
        return out
    for line in SHA1SUMS.read_text().splitlines():
        s = line.strip()
        if not s or s.startswith("#"):
            continue
        parts = s.split()
        if len(parts) >= 2:
            out[parts[1]] = parts[0]
    return out


def write_sha1sums_section(new_entries: dict[str, str]) -> None:
    """Append/refresh the assets/disc/* section of sha1sums.txt.

    Strategy: preserve all non-section lines verbatim, drop any existing
    section block, then append a fresh one with current entries sorted.
    """
    existing_lines: list[str] = []
    if SHA1SUMS.exists():
        existing_lines = SHA1SUMS.read_text().splitlines()

    # Locate the section header and excise from there to end-of-file.
    cut = len(existing_lines)
    for i, line in enumerate(existing_lines):
        if line.strip() == SHA1SUMS_SECTION_HEADER:
            cut = i
            break
    head = existing_lines[:cut]

    # Drop trailing blank lines on head so we don't accumulate spacing.
    while head and not head[-1].strip():
        head.pop()

    section: list[str] = []
    if new_entries:
        section.append("")
        section.append(SHA1SUMS_SECTION_HEADER)
        for name in sorted(new_entries):
            section.append(f"{new_entries[name]}  {name}")

    SHA1SUMS.write_text("\n".join(head + section) + "\n")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--include-ldummy", action="store_true",
                    help="also extract LDUMMY. (10 MiB of zeros)")
    ap.add_argument("--include-data-df", action="store_true",
                    help="also extract DFDATAS/DATA.DF (539 MiB, slow)")
    ap.add_argument("--list", action="store_true",
                    help="list ISO contents and exit without extracting")
    args = ap.parse_args()

    if not ISO.exists():
        print(f"extract_assets: missing {ISO}", file=sys.stderr)
        print("  Run tools/extract_elf.sh first to produce the cooked ISO.",
              file=sys.stderr)
        return 1

    files = list_iso_files(ISO)
    files.sort(key=lambda x: x[0])

    if args.list:
        print(f"{'size':>12}  path")
        for norm, size in files:
            print(f"{size:>12}  {norm}")
        return 0

    skip = set(DEFAULT_SKIP)
    if not args.include_ldummy:
        skip.add("LDUMMY.")
    if not args.include_data_df:
        skip.add("DFDATAS/DATA.DF")

    ASSETS_DIR.mkdir(parents=True, exist_ok=True)

    sha1_map = read_sha1sums()
    new_sha1_entries: dict[str, str] = {
        k: v for k, v in sha1_map.items() if k.startswith("assets/disc/")
    }

    extracted = 0
    skipped = 0
    verified = 0
    mismatches: list[tuple[str, str, str]] = []  # (name, recorded, actual)

    for norm, size in files:
        if norm in skip:
            skipped += 1
            continue
        out = local_name(norm)
        record_key = f"assets/disc/{norm.lower()}"

        if out.exists() and out.stat().st_size == size:
            actual = sha1_of(out)
            recorded = new_sha1_entries.get(record_key)
            if recorded == actual:
                verified += 1
                continue
            if recorded is not None and recorded != actual:
                mismatches.append((record_key, recorded, actual))
                continue
            # No recorded hash yet — fall through to record it.
            new_sha1_entries[record_key] = actual
            print(f"==> recorded SHA-1 for existing {record_key}")
            continue

        print(f"==> extracting {norm}  ({size} bytes)")
        extract_one(ISO, norm, out)
        actual = sha1_of(out)
        recorded = new_sha1_entries.get(record_key)
        if recorded is not None and recorded != actual:
            mismatches.append((record_key, recorded, actual))
            continue
        new_sha1_entries[record_key] = actual
        extracted += 1

    write_sha1sums_section(new_sha1_entries)

    print()
    print(f"extract_assets: extracted {extracted}, verified {verified}, "
          f"skipped {skipped} (of {len(files)} total)")

    if mismatches:
        print(file=sys.stderr)
        print("extract_assets: SHA-1 mismatches against recorded values:",
              file=sys.stderr)
        for name, recorded, actual in mismatches:
            print(f"  {name}", file=sys.stderr)
            print(f"    recorded: {recorded}", file=sys.stderr)
            print(f"    actual:   {actual}", file=sys.stderr)
        print("Either your disc image is a different revision, or the recorded",
              file=sys.stderr)
        print(f"hashes are wrong. Do not blindly update {SHA1SUMS} — consult",
              file=sys.stderr)
        print("the maintainer first.", file=sys.stderr)
        return 4

    return 0


if __name__ == "__main__":
    sys.exit(main())
