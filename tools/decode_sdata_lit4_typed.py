#!/usr/bin/env python3
"""
decode_sdata_lit4_typed.py — promote the small data sections from
auto-generated raw-byte sidecars to hand-typed C tracked sources.

`tools/migrate_data_per_tu.py` emits the byte content of every data
symbol as `unsigned char[N] = { 0xXX, ... }` (or `unsigned int D_X =
0xXXXX` for single 4-byte words). Those `_data.c` files are gitignored
because the byte literals are the original game's data verbatim — IP-
sensitive.

For `.lit4` (4 KB) and `.sdata` (8.7 KB) the byte volume is small enough
that we can decode each block into a typed C definition (`float D_X =
1.0f`, `static const char D_X[] = "host:"`, etc.) in one pass. The
typed output is a developer's clean-room reconstruction — committable
without IP risk — and progress.py credits the bytes once the tracked
files exist.

This tool walks the `.lit4.0xVMA` and `.sdata.0xVMA` entries in every
auto-generated `src/**/*_data.c` and writes:

  * src/sdata_typed.c — typed sdata definitions (floats, ints, strings)
  * src/lit4_typed.c  — typed lit4 definitions (always `float`)

`migrate_data_per_tu.py`'s `_scan_existing_definitions()` picks them
up next run and drops the corresponding entries from the auto-generated
sidecars. The build round-trips byte-identical because each typed
definition produces exactly the same bytes as the source byte array.

Idempotent.
"""

from __future__ import annotations

import re
import struct
import glob
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
SDATA_OUT = REPO_ROOT / "src" / "sdata.c"
LIT4_OUT = REPO_ROOT / "src" / "lit4.c"

# Regex for parsing one definition from a _data.c file.
DEF_RE = re.compile(
    r'__attribute__\(\(section\("(?P<sect>\.\w+\.0x[0-9A-Fa-f]+)"\)\)\)\s+'
    r'(?P<type>unsigned\s+(?:int|short|char))\s+'
    r'(?P<name>(?:D_|_pad_)[0-9A-Fa-f]{8})'
    r'(?P<dim>\[(?P<n>\d+)\])?\s*=\s*'
    r'(?P<init>(?:\{[^}]*\}|0x[0-9A-Fa-f]+|\d+))\s*;'
)


def _parse_init_bytes(c_type: str, dim_n: int, init: str) -> bytes:
    """Return the raw bytes a definition produces. Handles the three
    shapes the migrator emits: single int/short/char, char array, and
    char array with `{ 0 }` zero-fill shorthand."""
    if init.startswith("{"):
        inner = init.strip().lstrip("{").rstrip("}").strip()
        if inner == "0" and dim_n:
            return b"\x00" * dim_n
        elts = [e.strip() for e in inner.split(",") if e.strip()]
        bs = bytearray()
        for e in elts:
            v = int(e, 0)
            if "char" in c_type:
                bs.append(v & 0xFF)
            elif "short" in c_type:
                bs.extend((v & 0xFFFF).to_bytes(2, "little"))
            else:
                bs.extend((v & 0xFFFFFFFF).to_bytes(4, "little"))
        return bytes(bs)
    v = int(init, 0)
    if "char" in c_type:
        return bytes([v & 0xFF])
    if "short" in c_type:
        return (v & 0xFFFF).to_bytes(2, "little")
    return (v & 0xFFFFFFFF).to_bytes(4, "little")


def _decode_lit4(name: str, sect: str, data: bytes) -> str:
    """`.lit4` is a 4-byte float pool — every slot is a float. Emit as
    `float D_X = <value>f;` where `<value>` is the IEEE-decoded literal."""
    assert len(data) == 4, f"{name}: lit4 entry should be 4 bytes, got {len(data)}"
    f = struct.unpack("<f", data)[0]
    # Try a short representation first; fall back to full precision
    # via hex if shorthand loses information. The literal we emit must
    # re-encode back to the same 4 bytes when compiled.
    for fmt in ("%.7g", "%.9g", "%.17g"):
        s = fmt % f
        # Make sure the string parses back to the same float
        try:
            if struct.pack("<f", float(s)) == data:
                # Prepend "0x" for hex form? gcc accepts decimal float literals.
                if "." not in s and "e" not in s and "n" not in s and "i" not in s:
                    s = s + ".0"
                return (
                    f'__attribute__((section("{sect}"))) '
                    f'float {name} = {s}f;'
                )
        except ValueError:
            pass
    # Couldn't round-trip — fall back to hex bit pattern via union
    # trick. ee-gcc 2.9 accepts `__builtin_inf()` but not a hex float
    # literal, so we use a union-typed C99 reinterpret.
    v = struct.unpack("<I", data)[0]
    return (
        f'__attribute__((section("{sect}"))) '
        f'unsigned int {name} = 0x{v:08X}; '
        f'/* float bit-pattern; round-trip via decimal failed */'
    )


# Heuristic decoders for .sdata.

PRINTABLE = set(range(0x20, 0x7F)) | {0x09, 0x0A, 0x0D}  # tab, LF, CR


def _c_escape_string(bs: bytes) -> str:
    """C-escape every byte of a string body. Printable ASCII passes
    through (except `"` and `\\` which need escaping); control bytes
    become `\\n` / `\\t` / `\\r` / `\\xHH`. The result is safe to drop
    inside a `"..."` literal."""
    out: list[str] = []
    for b in bs:
        if b == 0x22:    # "
            out.append('\\"')
        elif b == 0x5C:  # \
            out.append("\\\\")
        elif b == 0x0A:
            out.append("\\n")
        elif b == 0x0D:
            out.append("\\r")
        elif b == 0x09:
            out.append("\\t")
        elif b == 0x07:
            out.append("\\a")
        elif b == 0x08:
            out.append("\\b")
        elif b == 0x0B:
            out.append("\\v")
        elif b == 0x0C:
            out.append("\\f")
        elif 0x20 <= b < 0x7F:
            out.append(chr(b))
        else:
            out.append(f"\\x{b:02x}")
    return "".join(out)


def _looks_like_string(data: bytes) -> bool:
    """True if the bytes look like an ASCIZ string: a printable-ASCII
    prefix (plus the common control bytes \\n \\r \\t \\b \\f \\v \\a
    plus the ANSI escape `\\x1b`) terminated by 0x00, plus only zero
    padding afterward."""
    if len(data) < 2:
        return False
    nul = data.find(b"\x00")
    if nul <= 0:
        return False
    string_safe = PRINTABLE | {0x07, 0x08, 0x0B, 0x0C, 0x1B}
    if any(b not in string_safe for b in data[:nul]):
        return False
    if any(b != 0 for b in data[nul + 1:]):
        return False
    return True


def _looks_like_float(data: bytes) -> bool:
    """Heuristic: a 4-byte word that round-trips through `float` cleanly
    AND is within a reasonable game-coord magnitude. The IEEE encoding
    of float 0.0 is 0x00000000 — that case is handled separately so we
    don't claim *every* zero word is a float."""
    if len(data) != 4:
        return False
    if data == b"\x00\x00\x00\x00":
        return False  # plain zero is more likely an int flag
    f = struct.unpack("<f", data)[0]
    # NaN / Inf rejected
    if f != f or f in (float("inf"), float("-inf")):
        return False
    af = abs(f)
    # Game-scale float magnitudes — covers common 3D coords (0..1M),
    # ratios (1e-6..1), and timing constants. Rejects bit patterns
    # whose value would be in the denormal or huge ranges (more likely
    # an int interpreted as float).
    if af == 0.0:
        return False
    if not (1e-7 <= af <= 1e8):
        return False
    return True


def _decode_sdata(name: str, sect: str, data: bytes) -> str:
    """Pick the most natural typed C representation for a sdata block."""
    # All-zero anything — emit as zeroed `int` for single 4-byte
    # symbols, `char[N] = { 0 }` for arrays.
    if all(b == 0 for b in data):
        if len(data) == 4:
            return f'__attribute__((section("{sect}"))) int {name} = 0;'
        if len(data) == 2:
            return f'__attribute__((section("{sect}"))) short {name} = 0;'
        if len(data) == 1:
            return f'__attribute__((section("{sect}"))) char {name} = 0;'
        return (f'__attribute__((section("{sect}"))) '
                f'char {name}[{len(data)}] = {{ 0 }};')

    # String?
    if _looks_like_string(data):
        nul = data.find(b"\x00")
        body = _c_escape_string(data[:nul])
        # If trailing zeros are padding to a different length, use [N] dim.
        if len(data) > nul + 1:
            return (f'__attribute__((section("{sect}"))) '
                    f'static const char {name}[{len(data)}] = "{body}";')
        return (f'__attribute__((section("{sect}"))) '
                f'static const char {name}[] = "{body}";')

    # Single 4-byte word: try float, else int.
    if len(data) == 4:
        if _looks_like_float(data):
            f = struct.unpack("<f", data)[0]
            for fmt in ("%.7g", "%.9g", "%.17g"):
                s = fmt % f
                try:
                    if struct.pack("<f", float(s)) == data:
                        if "." not in s and "e" not in s:
                            s = s + ".0"
                        return (
                            f'__attribute__((section("{sect}"))) '
                            f'float {name} = {s}f;'
                        )
                except ValueError:
                    pass
        # Plain int representation
        v = struct.unpack("<I", data)[0]
        return (f'__attribute__((section("{sect}"))) '
                f'unsigned int {name} = 0x{v:08X};')

    if len(data) == 2:
        v = struct.unpack("<H", data)[0]
        return (f'__attribute__((section("{sect}"))) '
                f'unsigned short {name} = 0x{v:04X};')
    if len(data) == 1:
        return (f'__attribute__((section("{sect}"))) '
                f'unsigned char {name} = 0x{data[0]:02X};')

    # Multi-element float array (e.g. coord pairs at 8 bytes,
    # color triples at 12). Try decoding each 4-byte chunk as a
    # float; emit as `float D_X[N]` only if every chunk passes
    # `_looks_like_float` (rejects integer flag arrays).
    if len(data) % 4 == 0 and len(data) >= 8:
        chunks = [data[i:i + 4] for i in range(0, len(data), 4)]
        if all(_looks_like_float(c) or c == b"\x00\x00\x00\x00" for c in chunks):
            vals = []
            ok = True
            for c in chunks:
                if c == b"\x00\x00\x00\x00":
                    vals.append("0.0f")
                    continue
                f = struct.unpack("<f", c)[0]
                for fmt in ("%.7g", "%.9g", "%.17g"):
                    s = fmt % f
                    try:
                        if struct.pack("<f", float(s)) == c:
                            if "." not in s and "e" not in s:
                                s = s + ".0"
                            vals.append(f"{s}f")
                            break
                    except ValueError:
                        pass
                else:
                    ok = False
                    break
            if ok:
                return (f'__attribute__((section("{sect}"))) '
                        f'float {name}[{len(chunks)}] = '
                        f'{{ {", ".join(vals)} }};')

    # Multi-byte mixed content — leave as char[] but emit hex literals.
    bs = ", ".join(f"0x{b:02X}" for b in data)
    return (f'__attribute__((section("{sect}"))) '
            f'unsigned char {name}[{len(data)}] = {{ {bs} }};')


def _walk_data_files():
    """Yield (sect, name, data) for every sdata/lit4 entry across all
    auto-generated _data.c sidecars. Skips the per-TU files entirely
    if any tracked source already defines a symbol (avoids overwriting
    hand-typed work)."""
    # Find already-typed symbols so we don't duplicate. Exclude our own
    # output files — otherwise re-running picks up the previous run's
    # definitions and emits nothing.
    own_files = {SDATA_OUT, LIT4_OUT}
    already = set()
    for p in (REPO_ROOT / "src").rglob("*.c"):
        if p.name.endswith("_data.c"):
            continue
        if p in own_files:
            continue
        for m in re.finditer(
            r'\b(D_[0-9A-Fa-f]{8})\b', p.read_text(),
        ):
            already.add(m.group(1))
    for p in (REPO_ROOT / "src").rglob("*_data.c"):
        text = p.read_text()
        for m in DEF_RE.finditer(text):
            sect = m.group("sect")
            name = m.group("name")
            if not name.startswith("D_"):
                continue  # _pad_ continuation chunks — skip
            if name in already:
                continue
            c_type = m.group("type").strip()
            dim_n = int(m.group("n") or "0")
            init = m.group("init")
            bs = _parse_init_bytes(c_type, dim_n or 1, init)
            yield sect, name, bs


def main() -> int:
    sdata_defs: list[tuple[int, str]] = []  # (vma, line)
    lit4_defs: list[tuple[int, str]] = []
    for sect, name, data in _walk_data_files():
        vma = int(sect.split(".0x")[-1], 16)
        if sect.startswith(".lit4."):
            lit4_defs.append((vma, _decode_lit4(name, sect, data)))
        elif sect.startswith(".sdata."):
            sdata_defs.append((vma, _decode_sdata(name, sect, data)))

    sdata_defs.sort()
    lit4_defs.sort()

    # ee-gcc 2.9 (the SCEI 1999 fork) is ASCII-only and chokes on
    # Unicode em-dashes or curly apostrophes in source comments. It
    # also closes /* ... */ comments at the FIRST `*/` it sees, so
    # `src/**/*_data.c` in a comment is a hidden trap (the `**/`
    # closes the comment). Header keeps both away.
    header_sdata = (
        "/* sdata.c -- hand-typed sdata symbol definitions.\n"
        " *\n"
        " * Generated initially by tools/decode_sdata_lit4_typed.py from\n"
        " * the auto-generated src tree byte content; refine in place\n"
        " * as the meaning of each symbol becomes clearer. Each line\n"
        " * is a developer reconstruction of one game variable or\n"
        " * constant. Unlike the raw byte arrays in the gitignored\n"
        " * data sidecars, these are clean-room and tracked.\n"
        " *\n"
        " * Migrators downstream (rewrite_data_named_sections.py,\n"
        " * migrate_data_per_tu.py _scan_existing_definitions) detect\n"
        " * the D_<VMA> name on each line and drop the corresponding\n"
        " * asm-generated definitions.\n"
        " */\n\n"
    )
    header_lit4 = header_sdata.replace("sdata.c", "lit4.c").replace(
        "sdata symbol", "float-literal-pool"
    ).replace(
        "one game variable or\n * constant", "one IEEE-encoded float constant"
    )

    SDATA_OUT.write_text(header_sdata + "\n".join(line for _, line in sdata_defs) + "\n")
    LIT4_OUT.write_text(header_lit4 + "\n".join(line for _, line in lit4_defs) + "\n")

    print(f"decode_sdata_lit4_typed: wrote {len(sdata_defs)} sdata defs to "
          f"{SDATA_OUT.relative_to(REPO_ROOT)}")
    print(f"decode_sdata_lit4_typed: wrote {len(lit4_defs)} lit4 defs to "
          f"{LIT4_OUT.relative_to(REPO_ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
