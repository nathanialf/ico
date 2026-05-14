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
1.0f`, `const char D_X[] = "host:"`, etc.) in one pass. The
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

# Legacy consolidated outputs. The decoder no longer writes to these
# (per-TU files are emitted via _tu_to_path below) but we delete any
# leftover ones on each run so old consolidated content doesn't
# coexist with the per-TU split.
LEGACY_SDATA_C = REPO_ROOT / "src" / "sdata.c"
LEGACY_LIT4_C = REPO_ROOT / "src" / "lit4.c"


def _tu_to_path(tu: str) -> Path:
    """Convert a TU label from decomp/data_tu_map.json into the path
    of the tracked per-TU .c file. TU labels are repo-root-relative
    paths matching the original ICO source-tree layout documented in
    `decomp/source_tree/`:

      src/Basic.c           ->  src/Basic.c
      src/way_tool.c        ->  src/way_tool.c
      ios/cdvd.c            ->  ios/cdvd.c
      isys/gobj.c           ->  isys/gobj.c
      sound/s_init.c        ->  sound/s_init.c
      _unassigned           ->  src/_unassigned.c

    The synthetic `_unassigned` bucket (proximity-fallback symbols
    with no text-side vote) lands at the top of `src/` so it's easy
    to spot."""
    if tu == "_unassigned":
        return REPO_ROOT / "src" / "_unassigned.c"
    return REPO_ROOT / tu

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


def _try_float_literal(data: bytes) -> str | None:
    """Format a 4-byte chunk as a `<decimal>f` literal that re-encodes
    back to the exact same bytes. Tries three precision levels; returns
    None if none round-trip cleanly (NaN, denormal, etc.)."""
    if len(data) != 4:
        return None
    f = struct.unpack("<f", data)[0]
    for fmt in ("%.7g", "%.9g", "%.17g"):
        s = fmt % f
        try:
            if struct.pack("<f", float(s)) == data:
                if "." not in s and "e" not in s and "n" not in s and "i" not in s:
                    s = s + ".0"
                return s + "f"
        except ValueError:
            pass
    return None


def _decode_lit4(name: str, sect: str, data: bytes) -> str:
    """`.lit4` is a 4-byte float pool — every slot is a float. All `.lit4`
    symbol VMAs are 4-aligned (sometimes 8-aligned), so a single `float D_X`
    declaration gets `.align 2` and produces byte-identical 4 bytes at the
    correct VMA.

    Fall back to `unsigned int = 0xXXXX` on the rare unrepresentable bit
    pattern (NaN payload, exotic denormal) — same alignment behavior."""
    assert len(data) == 4, f"{name}: lit4 entry should be 4 bytes, got {len(data)}"
    f_str = _try_float_literal(data)
    if f_str is not None:
        return f'__attribute__((section("{sect}"))) float {name} = {f_str};'
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


def _decode_sdata(name: str, sect: str, data: bytes) -> list[str]:
    """Pick the most natural typed C representation for a sdata block.

    Returns a list of definition lines (one entry per emitted C
    declaration). Single typed forms are one element; misaligned-VMA
    blocks fall through to per-VMA single-element chunks that mirror
    `tools/migrate_data_per_tu.py:_emit_chunked` exactly.

    Why the chunking dispatch: ee-gcc 2.9 applies `.align 3` (8-byte
    section alignment) to any multi-element array initializer
    regardless of `__attribute__((aligned(N)))`. At an 8-aligned VMA
    the `.align 3` is a no-op and the section lands at the right
    offset; at a non-8-aligned VMA the linker pads the cursor to
    8-aligned before placement, shifting every symbol downstream and
    breaking the byte-identical round-trip (root cause of the rolled-
    back attempt in commit d1c0bd4). Single-element typed forms
    (`unsigned int`/`float`/`short`/`char`) carry their type's natural
    alignment (4/4/2/1), so we never trigger `.align 3` if we stay
    single-element on misaligned blocks."""
    vma = int(sect.split(".0x")[-1], 16)

    # --- Single-byte forms: safe at any VMA (alignment 1). ---
    if len(data) == 1:
        if data[0] == 0:
            return [f'__attribute__((section("{sect}"))) char {name} = 0;']
        return [
            f'__attribute__((section("{sect}"))) '
            f'unsigned char {name} = 0x{data[0]:02X};'
        ]

    # --- Single-short / single-int: safe iff VMA satisfies that type's
    # natural alignment (2-byte / 4-byte). ---
    if len(data) == 2 and vma % 2 == 0:
        v = struct.unpack("<H", data)[0]
        if v == 0:
            return [f'__attribute__((section("{sect}"))) short {name} = 0;']
        return [
            f'__attribute__((section("{sect}"))) '
            f'unsigned short {name} = 0x{v:04X};'
        ]
    if len(data) == 4 and vma % 4 == 0:
        if data == b"\x00\x00\x00\x00":
            return [f'__attribute__((section("{sect}"))) int {name} = 0;']
        # Try float, fall back to unsigned int.
        if _looks_like_float(data):
            f_str = _try_float_literal(data)
            if f_str is not None:
                return [
                    f'__attribute__((section("{sect}"))) '
                    f'float {name} = {f_str};'
                ]
        v = struct.unpack("<I", data)[0]
        return [
            f'__attribute__((section("{sect}"))) '
            f'unsigned int {name} = 0x{v:08X};'
        ]

    # --- Multi-byte forms: only safe at 8-aligned VMAs, where
    # gcc's `.align 3` for arrays is a no-op. ---
    if vma % 8 == 0 and len(data) >= 2:
        # All-zero: implicit zero-fill is a small source representation
        # and produces byte-identical output.
        if all(b == 0 for b in data):
            return [
                f'__attribute__((section("{sect}"))) '
                f'char {name}[{len(data)}] = {{ 0 }};'
            ]

        # ASCIZ string with optional zero padding: emit as `const char[]`.
        if _looks_like_string(data):
            nul = data.find(b"\x00")
            body = _c_escape_string(data[:nul])
            if len(data) > nul + 1:
                return [
                    f'__attribute__((section("{sect}"))) '
                    f'const char {name}[{len(data)}] = "{body}";'
                ]
            return [
                f'__attribute__((section("{sect}"))) '
                f'const char {name}[] = "{body}";'
            ]

        # Multi-element float array — pairs / triples / quads of coords.
        if len(data) % 4 == 0 and len(data) >= 8:
            chunks = [data[i:i + 4] for i in range(0, len(data), 4)]
            if all(
                _looks_like_float(c) or c == b"\x00\x00\x00\x00"
                for c in chunks
            ):
                vals: list[str] = []
                ok = True
                for c in chunks:
                    if c == b"\x00\x00\x00\x00":
                        vals.append("0.0f")
                        continue
                    s = _try_float_literal(c)
                    if s is None:
                        ok = False
                        break
                    vals.append(s)
                if ok:
                    return [
                        f'__attribute__((section("{sect}"))) '
                        f'float {name}[{len(chunks)}] = '
                        f'{{ {", ".join(vals)} }};'
                    ]

        # Multi-byte mixed content — fall back to `unsigned char[N]`
        # with explicit hex literals. Still safe at 8-aligned VMA.
        bs = ", ".join(f"0x{b:02X}" for b in data)
        return [
            f'__attribute__((section("{sect}"))) '
            f'unsigned char {name}[{len(data)}] = {{ {bs} }};'
        ]

    # --- Misaligned-VMA or odd-size block: per-VMA chunked emission.
    # Mirrors migrate_data_per_tu.py:_emit_chunked so the resulting
    # section alignment never exceeds 4-byte (no `.align 3`).
    out: list[str] = []
    cursor = vma
    end = vma + len(data)
    first = True
    while cursor < end:
        rem = end - cursor
        off = cursor - vma
        chunk_sect = f"{sect.rsplit('.0x', 1)[0]}.0x{cursor:08X}"
        sym = name if first else f"_pad_{cursor:08X}"
        first = False
        if cursor % 4 == 0 and rem >= 4:
            chunk = data[off:off + 4]
            if chunk == b"\x00\x00\x00\x00":
                out.append(
                    f'__attribute__((section("{chunk_sect}"))) '
                    f'int {sym} = 0;'
                )
            elif _looks_like_float(chunk):
                f_str = _try_float_literal(chunk)
                if f_str is not None:
                    out.append(
                        f'__attribute__((section("{chunk_sect}"))) '
                        f'float {sym} = {f_str};'
                    )
                else:
                    v = struct.unpack("<I", chunk)[0]
                    out.append(
                        f'__attribute__((section("{chunk_sect}"))) '
                        f'unsigned int {sym} = 0x{v:08X};'
                    )
            else:
                v = struct.unpack("<I", chunk)[0]
                out.append(
                    f'__attribute__((section("{chunk_sect}"))) '
                    f'unsigned int {sym} = 0x{v:08X};'
                )
            cursor += 4
        elif cursor % 2 == 0 and rem >= 2:
            v = struct.unpack("<H", data[off:off + 2])[0]
            out.append(
                f'__attribute__((section("{chunk_sect}"))) '
                f'unsigned short {sym} = 0x{v:04X};'
            )
            cursor += 2
        else:
            out.append(
                f'__attribute__((section("{chunk_sect}"))) '
                f'unsigned char {sym} = 0x{data[off]:02X};'
            )
            cursor += 1
    return out


def _walk_baseelf_blocks(sect_name: str, vma_lo: int, vma_hi: int,
                         baseelf_data: dict[str, bytes]):
    """Yield (sect, name, data) for every `D_<VMA>` symbol in the given
    VMA range. Reads bytes DIRECTLY from baserom (via `baseelf_data`)
    keyed off the symbol list in `decomp/data_tu_map.json` — which is
    just symbol-name metadata, regenerable from the same baserom on
    any clone.

    Reading from baserom (rather than the asm-side `.s` files) means
    the decoder is robust against the `rewrite_data_named_sections.py`
    stripping pass: that rewriter removes migrated symbols' blocks
    from the asm, so a decoder reading the asm post-rewrite sees an
    empty file. Pulling bytes from baserom decouples the two."""
    import json
    tu_map_path = REPO_ROOT / "decomp" / "data_tu_map.json"
    if not tu_map_path.exists():
        return
    tu_map = json.loads(tu_map_path.read_text())

    # Filter to D_ symbols in the requested VMA range and sort by VMA.
    syms = []
    for sym, rec in tu_map.items():
        if not sym.startswith("D_"):
            continue
        vma = int(sym.split("_")[-1], 16)
        if vma_lo <= vma < vma_hi:
            syms.append((vma, sym))
    syms.sort()

    base = baseelf_data.get(sect_name)
    if base is None:
        return
    base_vma = baseelf_data[sect_name + ":vma"]

    for i, (vma, sym) in enumerate(syms):
        next_vma = syms[i + 1][0] if i + 1 < len(syms) else vma_hi
        off = vma - base_vma
        data = base[off:off + (next_vma - vma)]
        yield f"{sect_name}.0x{vma:08X}", sym, data


def _load_baseelf_sections() -> dict:
    """Pull the four data-section blobs out of baserom/baseelf.elf
    once so subsequent per-symbol byte extraction is just a slice."""
    from elftools.elf.elffile import ELFFile
    out: dict = {}
    with (REPO_ROOT / "baserom" / "baseelf.elf").open("rb") as f:
        elf = ELFFile(f)
        for sec in elf.iter_sections():
            if sec.name in (".sdata", ".lit4", ".rodata", ".data"):
                out[sec.name] = sec.data()
                out[sec.name + ":vma"] = sec["sh_addr"]
    return out


def _decode_lit4_block(name: str, sect: str, data: bytes, vma: int) -> list[str]:
    """`.lit4` entries are uniformly 4-byte floats. Most blocks are
    exactly 4 bytes; the rare longer block (zero-padded float bucket)
    decodes as one `float` per 4-byte slice, falling through to the
    same misaligned-VMA chunked path as `.sdata` for any non-4-byte
    tail (shouldn't happen in practice, but be safe)."""
    lines: list[str] = []
    cursor = vma
    end = vma + len(data)
    first = True
    while cursor + 4 <= end:
        chunk = data[cursor - vma:cursor - vma + 4]
        sym = name if first else f"_pad_{cursor:08X}"
        lines.append(_decode_lit4(sym, f".lit4.0x{cursor:08X}", chunk))
        first = False
        cursor += 4
    if cursor < end:
        tail = data[cursor - vma:]
        tail_sect = f".lit4.0x{cursor:08X}"
        tail_name = name if first else f"_pad_{cursor:08X}"
        lines.extend(_decode_sdata(tail_name, tail_sect, tail))
    return lines


def main() -> int:
    import json
    tu_map_path = REPO_ROOT / "decomp" / "data_tu_map.json"
    if not tu_map_path.exists():
        print("decode_sdata_lit4_typed: missing decomp/data_tu_map.json — "
              "run `make setup` first to generate it.")
        return 1
    tu_map = json.loads(tu_map_path.read_text())

    # Group each block's emitted lines by owning TU and by VMA so the
    # per-TU files stay sorted (deterministic regeneration).
    by_tu: dict[str, list[tuple[int, list[str]]]] = {}

    baseelf = _load_baseelf_sections()

    for sect, name, data in _walk_baseelf_blocks(
        ".sdata", 0x00631900, 0x00633BC6, baseelf,
    ):
        rec = tu_map.get(name)
        if rec is None:
            continue
        vma = int(sect.split(".0x")[-1], 16)
        by_tu.setdefault(rec["tu"], []).append(
            (vma, _decode_sdata(name, sect, data))
        )

    for sect, name, data in _walk_baseelf_blocks(
        ".lit4", 0x00630900, 0x006318D0, baseelf,
    ):
        rec = tu_map.get(name)
        if rec is None:
            continue
        vma = int(sect.split(".0x")[-1], 16)
        by_tu.setdefault(rec["tu"], []).append(
            (vma, _decode_lit4_block(name, sect, data, vma))
        )

    # ee-gcc 2.9 (the SCEI 1999 fork) is ASCII-only and chokes on
    # Unicode em-dashes or curly apostrophes in source comments. It
    # also closes /* ... */ comments at the FIRST `*/` it sees, so
    # avoid `**/` (the `**/` would close the comment).
    header_template = (
        "/* {tu} -- typed sdata / lit4 definitions for this TU.\n"
        " *\n"
        " * Generated initially by tools/decode_sdata_lit4_typed.py\n"
        " * from baserom/baseelf.elf. Each line is a developer\n"
        " * reconstruction of one game variable or constant; the\n"
        " * file is tracked because the typed forms (named float\n"
        " * constants, string literals, single hex-word declarations)\n"
        " * are clean-room rather than raw byte arrays.\n"
        " *\n"
        " * As the TU gets fully decompiled, function definitions\n"
        " * land in this same file (per-TU layout); typed\n"
        " * data declarations stay here next to their references.\n"
        " *\n"
        " * Downstream tools (rewrite_data_named_sections.py,\n"
        " * migrate_data_per_tu.py _scan_existing_definitions) detect\n"
        " * the D_<VMA> name on each line and drop the corresponding\n"
        " * asm-generated and sidecar definitions.\n"
        " */\n\n"
    )

    # Delete legacy consolidated outputs so they don't double-define
    # against the new per-TU split.
    for legacy in (LEGACY_SDATA_C, LEGACY_LIT4_C):
        if legacy.exists():
            legacy.unlink()

    written: list[Path] = []
    total_lines = 0
    total_blocks = 0
    skipped_existing: list[Path] = []

    for tu, blocks in sorted(by_tu.items()):
        path = _tu_to_path(tu)
        blocks.sort(key=lambda x: x[0])
        lines = [ln for _, body in blocks for ln in body]
        if not lines:
            continue
        if path.exists() and path != _tu_to_path("_unassigned"):
            # Don't overwrite hand-crafted TU files. The decoder is
            # idempotent on its own outputs but mustn't clobber work
            # already in flight (e.g. src/Basic.c). Flag and skip.
            existing = path.read_text()
            if "decode_sdata_lit4_typed.py" not in existing:
                skipped_existing.append(path)
                continue
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(
            header_template.format(tu=path.name) +
            "\n".join(lines) + "\n"
        )
        written.append(path)
        total_lines += len(lines)
        total_blocks += len(blocks)

    print(f"decode_sdata_lit4_typed: wrote {total_lines} typed "
          f"definitions ({total_blocks} source blocks) across "
          f"{len(written)} per-TU files.")
    for p in skipped_existing:
        print(f"decode_sdata_lit4_typed: SKIPPED (hand-crafted, no decoder "
              f"signature): {p.relative_to(REPO_ROOT)}")
    if skipped_existing:
        print("  To include the decoder's symbols, add them manually to the "
              "existing file. Subsequent regenerations will continue to "
              "skip — the decoder never overwrites a hand-crafted .c.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
