#!/usr/bin/env python3
"""
decode_vag.py — decode Sony VAG ADPCM (.bd / standalone .vag) to WAV.

Clean-room implementation of the public Sony VAG ADPCM spec — 16-byte blocks,
4-bit nibbles per sample, 5-entry filter table, second-order recursive
reconstruction. No code copied from any third-party decoder.

Supports:
  - Standalone `.vag` files (with the 'VAGp' header)
  - Raw `.bd` files: decoded as one concatenated mono stream. The companion
    `.hd` (SShd) typically holds per-sample offsets/rates; parsing it to
    split a .bd into per-sample WAVs is a separate research item (the .hd
    format has a 12-byte preamble then a 'SShd' block — RE needed).

PS2 native VAG is mono 16-bit signed PCM. Output is a 16-bit mono WAV.

Usage:
  tools/decode_vag.py file.bd [-o out.wav] [--rate 22050]
  tools/decode_vag.py dir/ -o out_dir/ [--rate 22050]
"""

from __future__ import annotations

import argparse
import struct
import sys
import wave
from pathlib import Path


# Sony VAG filter coefficients (scaled by 1/64).
# Public Sony spec — used in PS1 VAG and PS2 VAGp identically.
F1 = (0, 60, 115, 98, 122)
F2 = (0, 0, -52, -55, -60)

# Flag bits in byte 1 of each 16-byte VAG block.
FLAG_END_AND_LOOP   = 0x01
FLAG_LOOP_REGION    = 0x02
FLAG_LOOP_START     = 0x04
FLAG_END_OF_STREAM  = 0x07  # all three bits, observed terminator


def decode_vag_stream(data: bytes, stop_on_end: bool = True) -> list[int]:
    """Decode raw VAG-ADPCM blocks (16 bytes each) into signed-int16 samples.

    Returns a list of int samples (in [-32768, 32767]).
    Stops early at an end-of-stream flag if `stop_on_end` is True.
    """
    samples: list[int] = []
    prev1 = 0
    prev2 = 0
    n_blocks = len(data) // 16
    for blk in range(n_blocks):
        off = blk * 16
        header = data[off]
        flags = data[off + 1]
        filter_idx = (header >> 4) & 0x0F
        shift = header & 0x0F

        # Filters 0..4 are the Sony spec; anything else is invalid (or
        # marks a terminator block in some encoders). Clamp to 0.
        if filter_idx > 4:
            filter_idx = 0
        f1 = F1[filter_idx]
        f2 = F2[filter_idx]

        # 28 nibbles, low nibble of each byte first.
        for i in range(28):
            byte = data[off + 2 + (i >> 1)]
            nib = byte & 0x0F if (i & 1) == 0 else (byte >> 4) & 0x0F
            # Sign-extend the 4-bit value.
            if nib & 0x08:
                nib -= 16
            # Reconstruct: scale up to 16-bit then shift down by `shift`.
            s = (nib << 12) >> shift
            pred = (f1 * prev1 + f2 * prev2) >> 6
            v = s + pred
            # Clamp to int16.
            if v > 32767:
                v = 32767
            elif v < -32768:
                v = -32768
            samples.append(v)
            prev2 = prev1
            prev1 = v

        if stop_on_end and (flags & FLAG_END_AND_LOOP):
            # End-of-stream terminator block (all three flag bits typically
            # set on the final block). Stop here.
            if flags & 0x06 == 0x06 or flags == FLAG_END_AND_LOOP:
                break
    return samples


def parse_vagp_header(data: bytes) -> tuple[int, int, bytes]:
    """Parse a standalone VAGp file: return (sample_rate, channels, raw_blocks).

    VAGp file layout (big-endian on PSX-derived tools, but PS2 typically uses
    little-endian; we handle both by sniffing the magic):
      magic ('VAGp')   : 4 bytes
      version          : u32
      reserved         : u32
      data_size        : u32
      sample_rate      : u32
      reserved2        : 12 bytes
      name             : 16 bytes
      ADPCM data       : remainder
    """
    if data[:4] != b"VAGp":
        raise ValueError("not a VAGp file")
    # Try big-endian first (classic VAG), then little-endian.
    for endian in (">", "<"):
        try:
            _ver, _rsv, data_size, rate = struct.unpack_from(endian + "IIII",
                                                              data, 4)
            if 4000 <= rate <= 96000 and 0 < data_size <= len(data):
                return rate, 1, data[48:48 + data_size]
        except struct.error:
            pass
    # Fall back: assume LE, no validation.
    rate = struct.unpack_from("<I", data, 16)[0] or 22050
    return rate, 1, data[48:]


def write_wav(samples: list[int], path: Path, sample_rate: int,
              channels: int = 1) -> None:
    raw = bytearray()
    for s in samples:
        raw += struct.pack("<h", s)
    with wave.open(str(path), "wb") as w:
        w.setnchannels(channels)
        w.setsampwidth(2)
        w.setframerate(sample_rate)
        w.writeframes(bytes(raw))


def decode_one(in_path: Path, out_path: Path, sample_rate: int) -> int:
    """Decode a single .bd / .vag file. Returns sample count."""
    data = in_path.read_bytes()
    if data[:4] == b"VAGp":
        rate, _ch, blocks = parse_vagp_header(data)
        samples = decode_vag_stream(blocks, stop_on_end=True)
        write_wav(samples, out_path, rate)
    else:
        # Raw .bd: scan the entire file as VAG blocks. Don't stop on end-flag
        # (a .bd contains many concatenated samples; the first end-flag is
        # only the end of sample #0).
        samples = decode_vag_stream(data, stop_on_end=False)
        write_wav(samples, out_path, sample_rate)
    return len(samples)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("inputs", nargs="+",
                    help=".bd / .vag files, or directories to recurse")
    ap.add_argument("-o", "--output", default=None,
                    help="output WAV (single) or directory (bulk)")
    ap.add_argument("--rate", type=int, default=22050,
                    help="sample rate for raw .bd output (default: 22050)")
    ap.add_argument("--quiet", action="store_true")
    args = ap.parse_args()

    work: list[tuple[Path, Path]] = []
    out_root = Path(args.output) if args.output else None
    for raw in args.inputs:
        p = Path(raw)
        if p.is_file():
            if out_root and out_root.is_dir():
                dst = out_root / (p.stem + ".wav")
            elif out_root:
                dst = out_root
            else:
                dst = p.with_suffix(".wav")
            work.append((p, dst))
        elif p.is_dir():
            for f in sorted(list(p.rglob("*.bd")) + list(p.rglob("*.vag"))):
                if out_root:
                    dst = out_root / (f.relative_to(p).with_suffix(".wav"))
                else:
                    dst = f.with_suffix(".wav")
                work.append((f, dst))

    if not work:
        ap.print_help()
        return 1

    ok = fail = 0
    for src, dst in work:
        try:
            dst.parent.mkdir(parents=True, exist_ok=True)
            n = decode_one(src, dst, args.rate)
            if not args.quiet:
                print(f"  {src} -> {dst}  ({n:,} samples)")
            ok += 1
        except Exception as exc:
            print(f"  FAIL {src}: {exc}", file=sys.stderr)
            fail += 1

    print(f"decode_vag: {ok} OK, {fail} failed (of {len(work)} total)")
    return 0 if fail == 0 else 2


if __name__ == "__main__":
    sys.exit(main())
