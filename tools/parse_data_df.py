#!/usr/bin/env python3
"""
parse_data_df.py — extract DFDATAS/DATA.DF from the user's ICO disc image
into individual game-asset files under assets/disc/dfdatas/.

Two-level container format, derived from RE of the ios/cdvd.c family in the
EE ELF (DfOpen, the TOC parser at vaddr 0x1321c8, and the lookup at 0x132388):

  Outer DATA.DF (uncompressed):
    u32  count
    per entry (40 bytes):
      bytes 0-31: name           (null-terminated, garbage padding)
      bytes 32-35: byte offset    (within DATA.DF)
      bytes 36-39: size           (in bytes)

  Inner .DF (raw DEFLATE compressed; zlib.decompress wbits=-15):
    32-byte header:
      u32[0]: inner entry count
      u32[1..7]: misc (some 0xDDDDDDDD-uninit)
    per inner entry (548 bytes):
      bytes 0-511: filename       (null-terminated, 0xFF-padded)
      u32 at 512: entry index
      u32 at 516: data offset within inflated archive
      bytes 520-543: misc metadata
      u32 at 544: size of NEXT entry (one-step lookahead)
    file data: at each entry's offset, sized via next-entry-offset diff
               (last entry: inflated_size - last_offset)

Outer entries with non-".DF" extensions (.pss / .smb / .int / .jim) are
not container archives — they're dumped as-is.

assets/ is gitignored; nothing extracted here ever enters the tracked tree.
"""

from __future__ import annotations

import argparse
import hashlib
import io
import struct
import sys
import zlib
from pathlib import Path

import pycdlib

REPO_ROOT = Path(__file__).resolve().parent.parent
BASEROM_DIR = REPO_ROOT / "baserom"
ISO = BASEROM_DIR / "Ico_USA.iso"
OUT_DIR = REPO_ROOT / "assets" / "disc" / "dfdatas"

OUTER_ENTRY_SIZE = 40
OUTER_NAME_BYTES = 32

INNER_HEADER_BYTES = 32
INNER_ENTRY_SIZE = 548
INNER_NAME_BYTES = 512
# After the 512-byte filename: u32 entry index, then u32 data offset.
INNER_OFFSET_FIELD = INNER_NAME_BYTES + 4


def sha1_of(b: bytes) -> str:
    return hashlib.sha1(b).hexdigest()


def read_data_df(iso_path: Path) -> bytes:
    """Pull DFDATAS/DATA.DF out of the cooked ISO and return as bytes."""
    iso = pycdlib.PyCdlib()
    iso.open(str(iso_path))
    try:
        buf = io.BytesIO()
        iso.get_file_from_iso_fp(buf, iso_path="/DFDATAS/DATA.DF;1")
        return buf.getvalue()
    finally:
        iso.close()


def parse_outer_toc(data_df: bytes) -> list[tuple[str, int, int]]:
    """Parse DATA.DF's outer TOC.

    Returns: list of (name, byte_offset, size) tuples.
    """
    count = struct.unpack_from("<I", data_df, 0)[0]
    entries: list[tuple[str, int, int]] = []
    for i in range(count):
        o = 4 + i * OUTER_ENTRY_SIZE
        name_field = data_df[o:o + OUTER_NAME_BYTES]
        name = name_field.split(b"\x00", 1)[0].decode("ascii", errors="replace")
        offset, size = struct.unpack_from("<II", data_df, o + OUTER_NAME_BYTES)
        entries.append((name, offset, size))
    return entries


def parse_inner_archive(blob: bytes) -> list[tuple[str, int, int]]:
    """Parse a decompressed inner .DF archive.

    `blob` is the *already-inflated* contents. Returns (name, offset, size)
    triples where offset/size index into `blob`.
    """
    if len(blob) < INNER_HEADER_BYTES:
        raise ValueError(f"inner archive too small ({len(blob)} bytes)")
    count = struct.unpack_from("<I", blob, 0)[0]
    raw_entries: list[tuple[str, int]] = []
    for i in range(count):
        o = INNER_HEADER_BYTES + i * INNER_ENTRY_SIZE
        name_field = blob[o:o + INNER_NAME_BYTES]
        name = name_field.split(b"\x00", 1)[0].decode("ascii", errors="replace")
        file_off = struct.unpack_from("<I", blob, o + INNER_OFFSET_FIELD)[0]
        raw_entries.append((name, file_off))

    # Compute sizes via next-offset trick; last entry uses total inflated size.
    out: list[tuple[str, int, int]] = []
    for i, (name, off) in enumerate(raw_entries):
        if i + 1 < count:
            size = raw_entries[i + 1][1] - off
        else:
            size = len(blob) - off
        if size < 0:
            # entries are usually offset-sorted; warn rather than abort
            print(f"  WARNING: entry {i} {name!r} has negative size {size}",
                  file=sys.stderr)
            size = 0
        out.append((name, off, size))
    return out


def is_inner_archive(name: str) -> bool:
    """A `.DF` outer entry is a compressed inner archive; everything else
    (`.pss`, `.smb`, `.int`, `.jim`, ...) is dumped as-is."""
    return name.upper().endswith(".DF")


def normalize_subpath(name: str) -> Path:
    """Map an inner-archive filename to a safe relative path.

    Inner names may contain `..` parts (e.g. `boy/model/../texture/x.tm2`).
    Collapse them so we don't escape the output root, but keep the structure.
    """
    parts: list[str] = []
    for part in name.replace("\\", "/").split("/"):
        if part in ("", "."):
            continue
        if part == "..":
            if parts:
                parts.pop()
            continue
        parts.append(part)
    return Path(*parts) if parts else Path("_unnamed")


def stem(outer_name: str) -> str:
    """'COMMON.DF' -> 'common'."""
    n = outer_name
    if n.upper().endswith(".DF"):
        n = n[:-3]
    return n.lower()


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--list", action="store_true",
                    help="list contents without writing files")
    ap.add_argument("--outer-only", action="store_true",
                    help="extract outer entries as opaque blobs (don't crack .DF)")
    ap.add_argument("--filter", default=None,
                    help="only extract outer entries whose name contains this substring")
    ap.add_argument("--manifest", default=None,
                    help="write a TSV manifest of every extracted file to this path "
                         "(default: assets/disc/dfdatas/MANIFEST.tsv)")
    args = ap.parse_args()

    if not ISO.exists():
        print(f"parse_data_df: missing {ISO}", file=sys.stderr)
        print("  Run tools/extract_elf.sh first to produce the cooked ISO.",
              file=sys.stderr)
        return 1

    print(f"==> reading {ISO.relative_to(REPO_ROOT)}")
    data_df = read_data_df(ISO)
    print(f"==> DATA.DF: {len(data_df):,} bytes")

    outer = parse_outer_toc(data_df)
    print(f"==> outer TOC: {len(outer)} entries")

    if args.list and args.outer_only:
        print(f"{'idx':>4}  {'name':<22}  {'offset':>11}  {'size':>11}")
        for i, (name, off, size) in enumerate(outer):
            if args.filter and args.filter.lower() not in name.lower():
                continue
            print(f"{i:>4}  {name:<22}  {off:>11,}  {size:>11,}")
        return 0

    if not args.list:
        OUT_DIR.mkdir(parents=True, exist_ok=True)

    manifest_path = (Path(args.manifest)
                     if args.manifest else OUT_DIR / "MANIFEST.tsv")
    manifest_rows: list[str] = []
    manifest_rows.append("\t".join([
        "outer_index", "outer_name", "inner_index", "inner_name",
        "size_bytes", "sha1", "out_path",
    ]))

    total_files = 0
    total_bytes = 0

    for outer_idx, (outer_name, outer_off, outer_size) in enumerate(outer):
        if args.filter and args.filter.lower() not in outer_name.lower():
            continue
        blob = data_df[outer_off:outer_off + outer_size]
        if not is_inner_archive(outer_name) or args.outer_only:
            # opaque: dump as-is under outer name
            sub = OUT_DIR / outer_name.lower()
            if args.list:
                print(f"  [{outer_idx:>3}] {outer_name:<22} -> {sub.relative_to(REPO_ROOT)}  ({len(blob):,} B)")
            else:
                sub.parent.mkdir(parents=True, exist_ok=True)
                sub.write_bytes(blob)
            manifest_rows.append("\t".join([
                str(outer_idx), outer_name, "", "",
                str(len(blob)), sha1_of(blob),
                str(sub.relative_to(REPO_ROOT)),
            ]))
            total_files += 1
            total_bytes += len(blob)
            continue

        # inner archive: inflate and split
        try:
            inflated = zlib.decompress(blob, -15)
        except zlib.error as exc:
            print(f"  WARNING: {outer_name} inflate failed: {exc}", file=sys.stderr)
            continue

        try:
            inner = parse_inner_archive(inflated)
        except Exception as exc:
            print(f"  WARNING: {outer_name} inner TOC parse failed: {exc}",
                  file=sys.stderr)
            continue

        out_subdir = OUT_DIR / stem(outer_name)
        if args.list:
            print(f"  [{outer_idx:>3}] {outer_name:<22}  {outer_size:>9,}B -> "
                  f"{len(inner)} files in {out_subdir.relative_to(REPO_ROOT)}/")
            for j, (iname, ioff, isize) in enumerate(inner):
                if j < 5 or j == len(inner) - 1:
                    print(f"         [{j:>3}] {iname:<48} {isize:>9,}B")
                elif j == 5:
                    print(f"         ... ({len(inner)-6} more)")
            continue

        for j, (iname, ioff, isize) in enumerate(inner):
            sub = out_subdir / normalize_subpath(iname)
            sub.parent.mkdir(parents=True, exist_ok=True)
            payload = inflated[ioff:ioff + isize]
            sub.write_bytes(payload)
            manifest_rows.append("\t".join([
                str(outer_idx), outer_name, str(j), iname,
                str(isize), sha1_of(payload),
                str(sub.relative_to(REPO_ROOT)),
            ]))
            total_files += 1
            total_bytes += isize

        print(f"  [{outer_idx:>3}] {outer_name:<22}  {len(inner)} files, "
              f"{outer_size:,}B compressed -> {len(inflated):,}B inflated")

    if not args.list:
        manifest_path.parent.mkdir(parents=True, exist_ok=True)
        manifest_path.write_text("\n".join(manifest_rows) + "\n")
        print()
        print(f"==> wrote {total_files} files, {total_bytes:,} bytes total")
        print(f"==> manifest: {manifest_path.relative_to(REPO_ROOT)}")

    return 0


if __name__ == "__main__":
    sys.exit(main())
