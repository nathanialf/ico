#!/usr/bin/env python3
"""
migrate_data_full.py — full migration of .sdata / .lit4 / .rodata /
.data from the asm-side blob into per-section pool .c files.

Unlike tools/migrate_data_referenced.py (which only migrates symbols
that a matched src/cod/*.c references via `extern`), this tool migrates
EVERY symbol regardless of whether it's currently referenced. The goal
is to credit every data byte to the matched-bytes counter so the
section-percentage tables track non-text progress as well.

CHUNKING STRATEGY
-----------------
ee-gcc 2.9 over-aligns any array-shaped initializer to 8 bytes
(`.align 3`), even with `__attribute__((aligned(4)))`. For data whose
VMA is only 4-aligned (or worse), this forces the linker to insert
padding ahead of the section, breaking layout. So instead of emitting
one C definition per asm `dlabel` block, we walk the block's raw bytes
(extracted from splat's hex annotations) and emit definitions in
*aligned single-element chunks*:

  * if the cursor is 4-aligned and >= 4 bytes remain → `unsigned int`
  * else if 2-aligned and >= 2 bytes remain        → `unsigned short`
  * else                                            → `unsigned char`

Each chunk lives in its own per-VMA named section (`.sdata.0xVMA`).
Single-element definitions of these types get `.align 2`/`.align 1`/
no-align respectively — the linker can place each chunk at its
natural VMA without padding.

For .word symbol references (function pointers etc.), we emit
`extern <type> sym; ... = (unsigned int)&sym;`. The forward
declarations live at the top of the pool file.

Idempotent: re-running picks up newly-added symbols and skips ones
already in the migrated list / pool file.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
SRC_DIR = REPO_ROOT / "src" / "cod"
MIGRATED_LIST = REPO_ROOT / "config" / "migrated_data_symbols.txt"

# (section_name, asm_file, vma_lo, vma_hi_exclusive, pool_c)
SECTIONS = [
    (".sdata",  REPO_ROOT / "asm" / "data" / "cod" / "531900.sdata.s",
     0x00631900, 0x00633BC6, REPO_ROOT / "src" / "cod" / "sdata_pool.c"),
    (".lit4",   REPO_ROOT / "asm" / "data" / "cod" / "530900.lit4.s",
     0x00630900, 0x006318D0, REPO_ROOT / "src" / "cod" / "lit4_pool.c"),
]

DLABEL_RE = re.compile(
    r'^dlabel\s+(D_[0-9A-Fa-f]{8})\s*\n(?P<body>.*?)^enddlabel',
    re.MULTILINE | re.DOTALL,
)
NEXT_BLOCK_RE = re.compile(r'^nonmatching\s+D_([0-9A-Fa-f]{8})', re.MULTILINE)
POOL_FILE_NAMES = {p.name for _, _, _, _, p in SECTIONS}


def _load_migrated() -> set[str]:
    if not MIGRATED_LIST.exists():
        return set()
    out: set[str] = set()
    for line in MIGRATED_LIST.read_text().splitlines():
        line = line.split("#", 1)[0].strip()
        if line:
            out.add(line)
    return out


def _extract_block_bytes(body: str, start_vma: int, end_vma: int) -> bytes | None:
    """Read splat's hex annotations to reconstruct the raw bytes of a
    block. Each data line in splat has an address comment like
    `/* FILE_OFF VMA HEX */ .word ...` where HEX is the literal little-
    endian bytes of the directive. For .asciz with strings, the hex
    appears on a continuation line `/* ASCIIHEX */` after the asciz
    line. We collect all these hexes and concatenate.

    Returns the byte buffer, or None if we couldn't reconstruct the
    full expected size (a sign that the block has a shape this parser
    doesn't handle — symbol references etc.).
    """
    expected_size = end_vma - start_vma
    bytes_out = bytearray()
    cursor = start_vma  # absolute VMA

    # Address comment forms with embedded hex bytes. Splat typically
    # emits 8 hex digits (= 4 bytes), but the postprocess_asm tail-fix
    # for D_00633BC0 emits a 2-byte `.byte 0x45, 0x00` with only 4 hex
    # digits — so we accept any even count of hex digits.
    addr_hex_re = re.compile(
        r'^[ \t]*/\*\s+[0-9A-Fa-f]+\s+(?P<vma>[0-9A-Fa-f]{8})\s+(?P<hex>(?:[0-9A-Fa-f]{2})+)\s*\*/'
    )
    cont_hex_re = re.compile(
        r'^[ \t]*/\*\s*(?P<hex>[0-9A-Fa-f]+)\s*\*/\s*$'
    )
    addr_only_re = re.compile(
        r'^[ \t]*/\*\s+[0-9A-Fa-f]+\s+(?P<vma>[0-9A-Fa-f]{8})\s*\*/\s*(?P<rest>.*)$'
    )

    lines = body.splitlines()
    i = 0
    while i < len(lines):
        line = lines[i]
        # Address comment with 4-byte hex (.word/.float/.long): the hex
        # bytes are immediately readable as little-endian 4-byte chunks.
        m = addr_hex_re.match(line)
        if m:
            vma = int(m.group("vma"), 16)
            hex_str = m.group("hex")
            # Splat's hex annotation is in natural memory order (the
            # exact bytes that land at the given VMA). Length is
            # variable: 8 hex digits for `.word`, 4 for the `.byte`
            # tail-fix patch.
            word = bytes.fromhex(hex_str)
            if vma != cursor:
                return None
            bytes_out.extend(word)
            cursor += len(word)
            i += 1
            continue
        # Address comment with NO hex on the same line. Two sub-cases:
        #   (a) The directive's operand encodes the bytes directly
        #       (e.g. `.byte 0x70` — splat doesn't repeat the hex).
        #   (b) The bytes are on `/* HEXSTRING */` continuation lines
        #       below (typical for `.asciz` strings).
        m = addr_only_re.match(line)
        if m:
            vma = int(m.group("vma"), 16)
            if vma != cursor:
                return None
            rest = m.group("rest").strip()
            # Case (a): inline directive operand.
            mbyte = re.match(r'\.byte\s+(.+)$', rest)
            if mbyte:
                for elt in mbyte.group(1).split(","):
                    elt = elt.strip()
                    if not elt or not re.fullmatch(r"-?(?:0x[0-9A-Fa-f]+|\d+)", elt):
                        return None
                    bytes_out.append(int(elt, 0) & 0xFF)
                    cursor += 1
                i += 1
                continue
            mshort = re.match(r'\.(?:short|hword|half|2byte)\s+(.+)$', rest)
            if mshort:
                for elt in mshort.group(1).split(","):
                    elt = elt.strip()
                    if not elt or not re.fullmatch(r"-?(?:0x[0-9A-Fa-f]+|\d+)", elt):
                        return None
                    val = int(elt, 0) & 0xFFFF
                    bytes_out.extend(val.to_bytes(2, "little"))
                    cursor += 2
                i += 1
                continue
            mword = re.match(r'\.(?:word|long|4byte|float)\s+(.+)$', rest)
            if mword and re.fullmatch(r"-?(?:0x[0-9A-Fa-f]+|\d+)", mword.group(1).strip()):
                val = int(mword.group(1).strip(), 0) & 0xFFFFFFFF
                bytes_out.extend(val.to_bytes(4, "little"))
                cursor += 4
                i += 1
                continue
            # Case (b): continuation hex lines.
            i += 1
            while i < len(lines):
                cl = lines[i]
                if cl.strip().startswith("enddlabel"):
                    break
                if addr_hex_re.match(cl) or addr_only_re.match(cl):
                    break
                if re.match(r'\s*\.\s*(align|balign)\b', cl):
                    i += 1
                    continue
                m2 = cont_hex_re.match(cl)
                if m2:
                    hex_str = m2.group("hex")
                    if len(hex_str) % 2 != 0:
                        return None
                    bytes_out.extend(bytes.fromhex(hex_str))
                    cursor += len(hex_str) // 2
                    i += 1
                    continue
                i += 1
            continue
        # Lines like `.align N` are byte-cursor padding the rewriter
        # turned into `.skip N`. For pure-data reconstruction we need to
        # observe these — but in splat output the `.align` directives
        # only fire when the previous content's natural size leaves
        # a gap, and the gap is always zero-filled. The address comments
        # on the NEXT data line will catch the new cursor position, so
        # we can synthesize zero bytes here on demand. Lookahead:
        if re.match(r'\s*\.\s*(align|balign)\b', line):
            # Look at the next non-blank line's VMA.
            j = i + 1
            while j < len(lines) and not lines[j].strip():
                j += 1
            if j < len(lines):
                next_m = addr_hex_re.match(lines[j]) or addr_only_re.match(lines[j])
                if next_m:
                    next_vma = int(next_m.group("vma"), 16)
                    if next_vma > cursor:
                        bytes_out.extend(b"\x00" * (next_vma - cursor))
                        cursor = next_vma
            i += 1
            continue
        i += 1

    if cursor < end_vma:
        # Trailing pad to next-symbol VMA (zero-filled).
        bytes_out.extend(b"\x00" * (end_vma - cursor))
        cursor = end_vma
    if len(bytes_out) != expected_size:
        return None
    return bytes(bytes_out)


def _emit_chunked(sym: str, vma: int, sect_name: str,
                  data: bytes) -> list[str]:
    """Walk `data` from `vma`, emitting C definitions in
    aligned-largest-first chunks. First emitted symbol uses `sym`;
    subsequent ones use `_pad_<VMA>` names."""
    out: list[str] = []
    cursor = vma
    end = vma + len(data)
    first = True
    while cursor < end:
        remaining = end - cursor
        offset = cursor - vma
        if cursor % 4 == 0 and remaining >= 4:
            chunk_size = 4
            value = int.from_bytes(data[offset:offset + 4], "little")
            c_type = "unsigned int"
            initializer = f"0x{value:08X}"
        elif cursor % 2 == 0 and remaining >= 2:
            chunk_size = 2
            value = int.from_bytes(data[offset:offset + 2], "little")
            c_type = "unsigned short"
            initializer = f"0x{value:04X}"
        else:
            chunk_size = 1
            value = data[offset]
            c_type = "unsigned char"
            initializer = f"0x{value:02X}"
        name = sym if first else f"_pad_{cursor:08X}"
        out.append(
            f'__attribute__((section("{sect_name}.0x{cursor:08X}"))) '
            f'{c_type} {name} = {initializer};'
        )
        first = False
        cursor += chunk_size
    return out


def _walk_blocks(asm_path: Path, vma_lo: int, vma_hi: int):
    """Yield (sym, start_vma, end_vma, body) for each dlabel block."""
    text = asm_path.read_text()
    # Find boundaries: every nonmatching/dlabel pair.
    blocks = []
    matches = list(DLABEL_RE.finditer(text))
    # Compute end VMA by looking at the NEXT block's start VMA.
    starts = []
    for m in matches:
        sym = m.group(1)
        vma = int(sym[2:], 16)
        starts.append((vma, sym, m.group("body")))
    starts.sort()
    for i, (vma, sym, body) in enumerate(starts):
        end_vma = starts[i + 1][0] if i + 1 < len(starts) else vma_hi
        if vma_lo <= vma < vma_hi:
            yield sym, vma, end_vma, body


def main() -> int:
    migrated = _load_migrated()
    new_list_entries: list[str] = []
    grand_total = 0

    for sect_name, asm_file, vma_lo, vma_hi, pool_c in SECTIONS:
        if not asm_file.exists():
            continue
        if pool_c.exists():
            pool_text = pool_c.read_text()
            pool_have = set(re.findall(r'\bD_[0-9A-Fa-f]{8}\b', pool_text))
        else:
            pool_text = ""
            pool_have = set()
        new_defs: list[str] = []
        new_names: list[str] = []
        skipped_shape = 0
        for sym, vma, end_vma, body in _walk_blocks(asm_file, vma_lo, vma_hi):
            if sym in migrated or sym in pool_have:
                continue
            data = _extract_block_bytes(body, vma, end_vma)
            if data is None:
                skipped_shape += 1
                continue
            new_defs.extend(_emit_chunked(sym, vma, sect_name, data))
            new_names.append(sym)
        if new_defs:
            if not pool_text.strip():
                pool_text = (
                    f"/* Migrated {sect_name} symbols. Each chunk lives in its\n"
                    f" * own per-VMA named section so the linker can place it\n"
                    f" * via SORT_BY_NAME without alignment padding. */\n"
                )
            if not pool_text.endswith("\n"):
                pool_text += "\n"
            pool_text += "\n" + "\n".join(new_defs) + "\n"
            pool_c.write_text(pool_text)
            new_list_entries.extend(new_names)
            grand_total += len(new_names)
        print(f"migrate_data_full: {sect_name}: +{len(new_names)} migrated, "
              f"{skipped_shape} unhandled shapes")

    if new_list_entries:
        with MIGRATED_LIST.open("a") as f:
            for sym in new_list_entries:
                f.write(sym + "\n")
    print(f"migrate_data_full: TOTAL +{grand_total} symbols")
    return 0


if __name__ == "__main__":
    sys.exit(main())
