#!/usr/bin/env python3
"""
scan_p2o.py — reconnaissance dump for ICO's proprietary 'PS2O' mesh format.

Not a converter — a scoping aid. Walks a .p2o / .p2s / .p2c file and prints
its high-level chunk structure (PS2O header + OBJH footer + body span).
Useful while RE'ing the mesh format from the EE-side loader.

The body is opaque binary; full extraction will require:
  - Tracing the VU1 microcode (.S/.bin under cod/) that consumes the data
  - Identifying vertex / normal / UV / bone-weight strides
  - Decoding triangle strips (likely a VU1-friendly format)
  - Mapping skeleton bone hierarchy from companion .skb / .p2s files
"""

from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path


def scan(path: Path) -> dict:
    data = path.read_bytes()
    info: dict = {
        "path": str(path),
        "size": len(data),
        "magic": data[:4].decode("ascii", errors="replace") if len(data) >= 4 else "",
    }
    if data[:4] != b"PS2O":
        info["error"] = "not a PS2O file"
        return info

    # Header: u32 file_size, u32 chunk_count(?), 8 bytes pad
    hdr = struct.unpack_from("<8I", data, 4) if len(data) >= 36 else ()
    info["header_size_field"] = hdr[0] if hdr else None
    info["header_field_1"]   = hdr[1] if len(hdr) > 1 else None
    info["header_padding"]   = list(hdr[2:5]) if len(hdr) >= 5 else None

    # OBJH chunks: header_field_1 hints at how many to expect.
    objh_positions: list[int] = []
    i = 0
    while True:
        j = data.find(b"OBJH", i)
        if j < 0:
            break
        objh_positions.append(j)
        i = j + 1
    info["objh_count"] = len(objh_positions)
    info["objh_offsets"] = objh_positions
    info["objh_fields_per"] = []
    for off in objh_positions:
        fields = struct.unpack_from("<8I", data, off + 4) \
            if off + 36 <= len(data) else ()
        info["objh_fields_per"].append(list(fields))
    if objh_positions:
        # First OBJH bounds the initial body span [32 .. objh_positions[0]).
        info["body_offset"] = 32
        info["body_size"] = objh_positions[0] - 32
        info["trailer_size"] = len(data) - (objh_positions[-1] + 4)

    # Sanity: are there other plausible 4-byte ASCII tags in the body that
    # *might* be sub-chunks? We filter to ones where the next u32 is a
    # plausible byte-aligned size.
    candidates = []
    for off in range(32, len(data) - 8, 4):
        tag = bytes(data[off:off+4])
        if not (all(0x41 <= b <= 0x5A or 0x30 <= b <= 0x39 or b == 0x20 for b in tag)):
            continue
        sz = struct.unpack_from("<I", data, off + 4)[0]
        if 0 < sz <= len(data) - off and sz % 4 == 0:
            candidates.append((off, tag.decode("ascii"), sz))
    # Keep at most 20 candidates to avoid noise.
    info["plausible_subchunks"] = candidates[:20]
    return info


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("inputs", nargs="+")
    ap.add_argument("--summary", action="store_true",
                    help="one-line summary per file; skip per-chunk dump")
    args = ap.parse_args()

    paths: list[Path] = []
    for raw in args.inputs:
        p = Path(raw)
        if p.is_file():
            paths.append(p)
        elif p.is_dir():
            for ext in ("*.p2o", "*.p2s", "*.p2c"):
                paths.extend(sorted(p.rglob(ext)))

    if not paths:
        ap.print_help()
        return 1

    if args.summary:
        print(f"{'size':>9}  {'body':>9}  {'objhN':>5}  {'fld1':>4}  path")
        for p in paths:
            info = scan(p)
            if "error" in info:
                print(f"{info['size']:>9}  ---        ---    ---  {p}  ({info['error']})")
                continue
            body = info.get("body_size") or 0
            n = info.get("objh_count") or 0
            fld1 = info.get("header_field_1")
            print(f"{info['size']:>9}  {body:>9}  {n:>5}  {fld1!s:>4}  {p}")
        return 0

    for p in paths:
        info = scan(p)
        print(f"==> {p}")
        if "error" in info:
            print(f"    ERROR: {info['error']}")
            continue
        print(f"    size:               {info['size']:,} bytes")
        print(f"    header file_size:   {info['header_size_field']} ({info['header_size_field']:#x})")
        print(f"    header field 1:     {info['header_field_1']}")
        print(f"    OBJH count:         {info['objh_count']} (header field 1 = {info['header_field_1']})")
        if info["objh_count"]:
            print(f"    OBJH offsets:       {info['objh_offsets']}")
            for k, (off, fields) in enumerate(zip(info['objh_offsets'], info['objh_fields_per'])):
                print(f"      [{k}] off={off:>7}  fields={fields}")
            print(f"    body span:          [32, {info['objh_offsets'][0]}) = {info['body_size']:,} bytes")
            print(f"    trailer after last OBJH: {info['trailer_size']} bytes")
        if info["plausible_subchunks"]:
            print(f"    plausible subchunks (filtered):")
            for off, tag, sz in info["plausible_subchunks"][:8]:
                print(f"      off={off:>6}  tag={tag!r:<8}  sz={sz}")
        print()

    return 0


if __name__ == "__main__":
    sys.exit(main())
