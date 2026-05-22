#!/usr/bin/env python3
"""
decode_tm2.py — decode Sony TIM2 textures (.tm2) to PNG.

Clean-room implementation of the Sony TIM2 spec — file header, picture
header, indexed/direct pixel formats, and the standard PSMT8 CLUT
de-interleave. No code copied from any third-party decoder.

Supports the formats ICO actually uses (PSMT4, PSMT8, PSMCT32, PSMCT16).
Linear pixel layout only — does not attempt to deswizzle GS-page-tiled
images (those would need the GS PSMT page-layout reverse, a separate
research item).

PS2 alpha is 0..128 (128 = fully opaque). Scaled to 0..255 for PNG.

Usage:
  tools/decode_tm2.py <input.tm2> [-o out.png]            # single file
  tools/decode_tm2.py <dir-or-tree> -o <out-dir>          # bulk: PNGs mirror tree
  tools/decode_tm2.py --manifest assets/disc/dfdatas/MANIFEST.tsv -o out/
"""

from __future__ import annotations

import argparse
import struct
import sys
from dataclasses import dataclass
from pathlib import Path

from PIL import Image


TIM2_MAGIC = b"TIM2"
TIM2_FILE_HEADER = 16
TIM2_PIC_HEADER_MIN = 48


@dataclass
class Picture:
    width: int
    height: int
    bits_per_pixel: int       # 4, 8, 16, 24, or 32
    clut_count: int           # 0 if not indexed
    clut_bytes_per_color: int  # 0 if not indexed, else 2 or 4
    image: bytes
    clut: bytes


def parse_tim2(data: bytes) -> list[Picture]:
    """Parse a .tm2 file into a list of Picture objects."""
    if len(data) < TIM2_FILE_HEADER or data[:4] != TIM2_MAGIC:
        raise ValueError("not a TIM2 file (missing 'TIM2' magic)")
    _magic, _version, _format_hint, picture_count = struct.unpack_from(
        "<4sBBH", data, 0
    )

    pics: list[Picture] = []
    cursor = TIM2_FILE_HEADER
    for _ in range(picture_count):
        if cursor + TIM2_PIC_HEADER_MIN > len(data):
            raise ValueError("truncated TIM2 picture header")
        (total_size, clut_size, image_size, header_size,
         clut_color_count, _pic_fmt, mipmap_count, _clut_fmt, _img_fmt,
         width, height) = struct.unpack_from("<IIIHHBBBBHH", data, cursor)

        if header_size < TIM2_PIC_HEADER_MIN:
            raise ValueError(f"unexpected picture header size: {header_size}")

        # Image data starts right after the (variable-size) picture header.
        img_start = cursor + header_size
        img_end = img_start + image_size
        clut_end = img_end + clut_size

        if clut_end > cursor + total_size:
            raise ValueError("TIM2 picture body exceeds total_size")
        if clut_end > len(data):
            raise ValueError("TIM2 picture body exceeds file bounds")

        # When mipmaps are present, image_size covers mip 0 + mip 1 + ...
        # concatenated. Derive bpp from mip 0 alone (sum of geometric mip
        # sizes), and slice off just the base level.
        pixels = width * height
        if pixels == 0:
            raise ValueError("TIM2 picture has zero dimensions")
        n_mips = max(1, mipmap_count)
        mip_pixel_total = sum((width >> k) * (height >> k) for k in range(n_mips))
        if mip_pixel_total == 0:
            raise ValueError("TIM2 picture has zero mip-pixel total")
        # image_size for 4bpp is (mip_pixel_total + 1) // 2; for others it's
        # mip_pixel_total * (bpp // 8).
        if image_size * 2 == mip_pixel_total:
            bpp = 4
        elif image_size == mip_pixel_total:
            bpp = 8
        elif image_size == mip_pixel_total * 2:
            bpp = 16
        elif image_size == mip_pixel_total * 3:
            bpp = 24
        elif image_size == mip_pixel_total * 4:
            bpp = 32
        else:
            raise ValueError(
                f"can't derive bpp: image_size={image_size}, "
                f"mip0={pixels}, mip_total={mip_pixel_total}, mips={n_mips}"
            )

        # Slice mip 0 only (the base level we display). CLUT always follows
        # the full image block (mips included).
        mip0_bytes = (pixels * bpp + 7) // 8
        image = bytes(data[img_start:img_start + mip0_bytes])
        clut = bytes(data[img_end:clut_end])

        clut_bpc = (clut_size // clut_color_count) if clut_color_count else 0

        pics.append(Picture(
            width=width, height=height, bits_per_pixel=bpp,
            clut_count=clut_color_count, clut_bytes_per_color=clut_bpc,
            image=image, clut=clut,
        ))

        cursor += total_size

    return pics


def deinterleave_clut_psmt8(clut: bytes, bytes_per_color: int) -> bytes:
    """For 8-bit indexed images, PS2 stores the 256-color CLUT in 32-color
    blocks where rows 1 and 2 (each 8 colors wide) are swapped. Reverse it
    so CLUT[index] returns the correct color."""
    if len(clut) != 256 * bytes_per_color:
        return clut  # shape we don't recognise — pass through
    out = bytearray(len(clut))
    row_pairs = [0, 2, 1, 3]  # disk-row -> memory-row within each 32-color block
    for block in range(8):
        block_base = block * 32 * bytes_per_color
        for disk_row in range(4):
            mem_row = row_pairs[disk_row]
            src = block_base + disk_row * 8 * bytes_per_color
            dst = block_base + mem_row * 8 * bytes_per_color
            out[dst:dst + 8 * bytes_per_color] = clut[src:src + 8 * bytes_per_color]
    return bytes(out)


def expand_ps2_alpha(a: int) -> int:
    """PS2 alpha is 0..128. Scale to 0..255 for PNG output."""
    return 255 if a >= 128 else (a * 255 // 128)


def clut_to_rgba_table(clut: bytes, bytes_per_color: int, count: int) -> list[tuple[int, int, int, int]]:
    """Decode CLUT bytes into a list of (R, G, B, A) tuples."""
    out: list[tuple[int, int, int, int]] = []
    if bytes_per_color == 4:
        for i in range(count):
            r, g, b, a = clut[i*4:i*4+4]
            out.append((r, g, b, expand_ps2_alpha(a)))
    elif bytes_per_color == 3:
        # PSMCT24 CLUT: no alpha, treat as opaque.
        for i in range(count):
            r, g, b = clut[i*3:i*3+3]
            out.append((r, g, b, 255))
    elif bytes_per_color == 2:
        for i in range(count):
            v = struct.unpack_from("<H", clut, i * 2)[0]
            r = (v & 0x1F) << 3
            g = ((v >> 5) & 0x1F) << 3
            b = ((v >> 10) & 0x1F) << 3
            a = 255 if (v >> 15) & 1 else 0
            out.append((r, g, b, a))
    else:
        raise ValueError(f"unsupported CLUT bytes-per-color: {bytes_per_color}")
    return out


def decode_picture(pic: Picture) -> Image.Image:
    """Return a Pillow RGBA image for `pic`."""
    w, h, bpp = pic.width, pic.height, pic.bits_per_pixel

    if bpp == 4:
        # 4-bit indexed: 16 entries, no CLUT swizzle
        if pic.clut_count != 16:
            # Some 4bpp images may carry larger CLUTs — use first 16
            pass
        table = clut_to_rgba_table(pic.clut, pic.clut_bytes_per_color,
                                   pic.clut_count or 16)
        # Each byte is two pixels: low nibble first.
        out = bytearray(w * h * 4)
        for i in range(w * h):
            byte = pic.image[i >> 1]
            nib = byte & 0xF if (i & 1) == 0 else (byte >> 4) & 0xF
            r, g, b, a = table[nib] if nib < len(table) else (0, 0, 0, 0)
            j = i * 4
            out[j:j+4] = bytes((r, g, b, a))
        return Image.frombytes("RGBA", (w, h), bytes(out))

    if bpp == 8:
        # 8-bit indexed: 256 entries, CLUT row-swap unswizzle.
        clut = deinterleave_clut_psmt8(pic.clut, pic.clut_bytes_per_color)
        table = clut_to_rgba_table(clut, pic.clut_bytes_per_color, pic.clut_count or 256)
        out = bytearray(w * h * 4)
        for i in range(w * h):
            idx = pic.image[i]
            r, g, b, a = table[idx] if idx < len(table) else (0, 0, 0, 0)
            j = i * 4
            out[j:j+4] = bytes((r, g, b, a))
        return Image.frombytes("RGBA", (w, h), bytes(out))

    if bpp == 16:
        # PSMCT16: ABGR 1:5:5:5
        out = bytearray(w * h * 4)
        for i in range(w * h):
            v = struct.unpack_from("<H", pic.image, i * 2)[0]
            r = (v & 0x1F) << 3
            g = ((v >> 5) & 0x1F) << 3
            b = ((v >> 10) & 0x1F) << 3
            a = 255 if (v >> 15) & 1 else 0
            j = i * 4
            out[j:j+4] = bytes((r, g, b, a))
        return Image.frombytes("RGBA", (w, h), bytes(out))

    if bpp == 24:
        # PSMCT24: R G B, no alpha
        out = bytearray(w * h * 4)
        for i in range(w * h):
            r, g, b = pic.image[i*3:i*3+3]
            j = i * 4
            out[j:j+4] = bytes((r, g, b, 255))
        return Image.frombytes("RGBA", (w, h), bytes(out))

    if bpp == 32:
        # PSMCT32: R G B A (PS2 stores in that order, alpha is PS2-range)
        out = bytearray(w * h * 4)
        for i in range(w * h):
            r, g, b, a = pic.image[i*4:i*4+4]
            j = i * 4
            out[j:j+4] = bytes((r, g, b, expand_ps2_alpha(a)))
        return Image.frombytes("RGBA", (w, h), bytes(out))

    raise ValueError(f"unsupported bpp: {bpp}")


def decode_file(in_path: Path, out_path: Path) -> int:
    data = in_path.read_bytes()
    pics = parse_tim2(data)
    if not pics:
        return 0
    if len(pics) == 1:
        decode_picture(pics[0]).save(out_path)
        return 1
    written = 0
    for i, p in enumerate(pics):
        suffixed = out_path.with_suffix(f".{i}.png")
        decode_picture(p).save(suffixed)
        written += 1
    return written


def iter_inputs(args: argparse.Namespace) -> list[tuple[Path, Path]]:
    """Build (input_tm2, output_png) work list."""
    work: list[tuple[Path, Path]] = []
    if args.manifest:
        manifest_path = Path(args.manifest)
        out_root = Path(args.output or "out_tm2")
        for line in manifest_path.read_text().splitlines()[1:]:
            cols = line.split("\t")
            if len(cols) < 7:
                continue
            inner_name = cols[3] or cols[1]  # inner_name, else outer_name
            out_path_rel = Path(cols[6])
            if not inner_name.lower().endswith(".tm2"):
                continue
            src = Path(out_path_rel)
            dst = out_root / src.relative_to(src.parts[0]).with_suffix(".png")
            work.append((src, dst))
        return work

    if not args.inputs:
        return work

    out_root = Path(args.output) if args.output else None
    for raw in args.inputs:
        p = Path(raw)
        if p.is_file():
            if out_root and out_root.is_dir():
                dst = out_root / (p.stem + ".png")
            elif out_root:
                dst = out_root
            else:
                dst = p.with_suffix(".png")
            work.append((p, dst))
        elif p.is_dir():
            for f in sorted(p.rglob("*.tm2")):
                if out_root is not None:
                    rel = f.relative_to(p)
                    dst = out_root / rel.with_suffix(".png")
                else:
                    dst = f.with_suffix(".png")
                work.append((f, dst))
    return work


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("inputs", nargs="*",
                    help="TM2 files, or directories to recurse")
    ap.add_argument("-o", "--output", default=None,
                    help="output PNG path (single) or directory (bulk)")
    ap.add_argument("--manifest", default=None,
                    help="MANIFEST.tsv from parse_data_df.py; bulk-decodes "
                         "every .tm2 listed there")
    ap.add_argument("--quiet", action="store_true",
                    help="suppress per-file progress")
    args = ap.parse_args()

    work = iter_inputs(args)
    if not work:
        ap.print_help()
        return 1

    ok = fail = 0
    for src, dst in work:
        try:
            dst.parent.mkdir(parents=True, exist_ok=True)
            n = decode_file(src, dst)
            if not args.quiet:
                print(f"  {src} -> {dst}  ({n} picture{'s' if n != 1 else ''})")
            ok += 1
        except Exception as exc:
            print(f"  FAIL {src}: {exc}", file=sys.stderr)
            fail += 1

    print(f"decode_tm2: {ok} OK, {fail} failed (of {len(work)} total)")
    return 0 if fail == 0 else 2


if __name__ == "__main__":
    sys.exit(main())
