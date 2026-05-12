#!/usr/bin/env python3
"""decode_sjis.py — decode a rodata symbol's bytes as Shift-JIS and
emit a `SJIS("\\xNN...")` C literal for hand-promotion.

Usage: tools/decode_sjis.py D_<VMA> [D_<VMA> ...]

For each requested symbol, this tool:
  1. Reads the bytes from baserom/baseelf.elf at the symbol's VMA.
  2. Attempts to decode them as Shift-JIS (the codepage Japanese
     PS2 titles use).
  3. Prints the decoded Unicode (for the developer to read in context),
     followed by a C literal that preserves the original SJIS bytes
     via `\\xNN` hex escapes.
  4. The C literal is what the developer copies into the tracked
     `src/<TU>.c`, wrapped in `SJIS(...)` to mark intent.

The macro is a no-op identity — the literal value is the same SJIS
bytes the migrator would emit as `unsigned char[]`, just typed as
`const char[]` so it counts as a clean-room reconstruction
(the developer has decoded and confirmed the meaning).

Examples (run after a full build so symbol_addrs.us.txt is complete):

    $ tools/decode_sjis.py D_00554C90
    D_00554C90 (24 bytes @ 0x00554C90)
      Decoded: "Light:NULLになってんで\\n"
      Literal: SJIS("Light:NULL\\xa4\\xcb\\xa4\\xca\\xa4\\xc3\\xa4\\xc6\\xa4\\xf3\\xa4\\xc7\\n")
"""
from __future__ import annotations

import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
SRC = REPO / "src"

# Match `... unsigned char D_<VMA>[N] = { 0xNN, 0xNN, ... };` lines
# (the only shape that holds raw SJIS bytes — strings, floats, and
# pointer arrays are already type-distinguished by the migrator).
BYTE_ARR_RE = re.compile(
    r'__attribute__\(\(section\("\.\w+\.0x[0-9A-Fa-f]+"\)\)\)\s+'
    r'(?:const\s+)?unsigned char (D_[0-9A-Fa-f]{8})\[(\d+)\]\s*=\s*\{([^}]*)\}\s*;'
)


def _find_symbol_bytes(sym: str) -> tuple[int, bytes] | None:
    """Scan every src/**/*.c (tracked and _data.c sidecars) for the
    symbol's byte-array definition. Returns (size, bytes) or None."""
    for c_path in SRC.rglob("*.c"):
        try:
            text = c_path.read_text()
        except OSError:
            continue
        if sym not in text:
            continue
        for m in BYTE_ARR_RE.finditer(text):
            if m.group(1) != sym:
                continue
            size = int(m.group(2))
            tokens = [t.strip() for t in m.group(3).split(",") if t.strip()]
            try:
                bs = bytes(int(t, 16) for t in tokens)
            except ValueError:
                continue
            if len(bs) == size:
                return size, bs
    return None


def _encode_c_literal(data: bytes) -> str:
    """Produce a SJIS-preserving C string literal. Trailing single NUL
    is dropped (implicit C-string terminator). Embedded NULs use 3-digit
    octal `\\000` to avoid octal-continuation ambiguity. ASCII passes
    through; high-bit bytes become `\\xNN`."""
    if data and data[-1] == 0:
        body = data[:-1]
    else:
        body = data
    out: list[str] = []
    for b in body:
        if b == 0:
            out.append("\\000")
        elif b == ord("\\"):
            out.append("\\\\")
        elif b == ord('"'):
            out.append('\\"')
        elif b == 0x0a:
            out.append("\\n")
        elif b == 0x09:
            out.append("\\t")
        elif b == 0x0d:
            out.append("\\r")
        elif 0x20 <= b < 0x7f:
            out.append(chr(b))
        else:
            out.append(f"\\x{b:02x}")
    return '"' + "".join(out) + '"'


def _decode_for_display(data: bytes) -> str:
    """Best-effort Shift-JIS decode. Replace bad bytes so the developer
    still sees what's recognizable."""
    return data.decode("shift_jis", errors="replace")


def main() -> int:
    if len(sys.argv) < 2:
        sys.exit("usage: decode_sjis.py D_<VMA> [D_<VMA> ...]")
    for arg in sys.argv[1:]:
        sym = arg.strip()
        if not re.fullmatch(r'D_[0-9A-Fa-f]{8}', sym):
            print(f"skipping {arg}: not a D_<8hex> symbol", file=sys.stderr)
            continue
        sym = "D_" + sym[2:].upper()
        found = _find_symbol_bytes(sym)
        if found is None:
            print(f"{sym}: no `unsigned char {sym}[N] = {{ ... }}` definition "
                  f"in src/. Either the symbol is already typed, or the "
                  f"migrator hasn't run — try tools/build.sh setup.",
                  file=sys.stderr)
            continue
        size, data = found
        vma = int(sym[2:], 16)
        decoded = _decode_for_display(data)
        literal = _encode_c_literal(data)
        high_bit = sum(1 for b in data if b >= 0x80)
        likely_sjis = high_bit >= 2
        marker = "Decoded" if likely_sjis else "Note: <2 high-bit bytes; may not be SJIS"
        macro = "SJIS" if likely_sjis else "const char"
        print(f"{sym} ({size} bytes @ 0x{vma:08X})")
        print(f"  {marker}: {decoded!r}")
        print(f"  Literal: {macro}({literal})")
        print()
    return 0


if __name__ == "__main__":
    sys.exit(main())
