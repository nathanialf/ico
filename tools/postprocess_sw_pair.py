#!/usr/bin/env python3
"""tools/postprocess_sw_pair.py — swap two `sw` stores around a `j $31`
when the file_off is listed in config/swap_sw_pair.txt.

Pattern (idempotent — only fires once per match):

    sw  $X, OFF1($Y)
    .set noreorder            (any number of .set lines)
    .set nomacro
    j   $31
    sw  $Z, OFF2($Y)

becomes:

    sw  $Z, OFF2($Y)
    .set noreorder
    .set nomacro
    j   $31
    sw  $X, OFF1($Y)

The two stores must share a base register $Y. Order swap is functionally
identical (different addresses, no aliasing); the encoded bytes change.
Used to coerce ee-gcc 2.9-991111 into the original ICO store-pair
ordering for getset-style functions.

Usage: postprocess_sw_pair.py <file.s>  (file_off derived from basename)
"""
import os, pathlib, re, sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
CFG = ROOT / "config" / "swap_sw_pair.txt"


def listed(file_off):
    if not CFG.exists():
        return False
    for line in CFG.read_text().splitlines():
        line = line.split("#", 1)[0].strip()
        if not line:
            continue
        if line.upper().split()[0] == file_off.upper():
            return True
    return False


PAT = re.compile(
    r"(?P<sw1>\tsw\t\$\d+,\d+\(\$(?P<base1>\d+)\)\n)"
    r"(?P<mid>(?:\t\.set\s+\w+\n)*)"
    r"(?P<j>\tj\t\$\d+\n)"
    r"(?P<sw2>\tsw\t\$\d+,\d+\(\$(?P<base2>\d+)\)\n)",
    re.M,
)


def swap(m):
    if m.group("base1") != m.group("base2"):
        return m.group(0)
    return m.group("sw2") + m.group("mid") + m.group("j") + m.group("sw1")


def main():
    if len(sys.argv) < 2:
        print("usage: postprocess_sw_pair.py <file.s>", file=sys.stderr)
        return 2
    p = pathlib.Path(sys.argv[1])
    file_off = p.stem.upper()
    if not listed(file_off):
        return 0
    text = p.read_text()
    p.write_text(PAT.sub(swap, text))
    return 0


if __name__ == "__main__":
    sys.exit(main())
