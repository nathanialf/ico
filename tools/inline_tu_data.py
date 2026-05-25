#!/usr/bin/env python3
"""
inline_tu_data.py — Phase 3e: move a TU's safe sidecar data inline.

Reads a TU's data symbols (from decomp/data_tu_map.json), reconstructs
each symbol's bytes from the asm-side data files (reusing the
byte-reconstruction + classification helpers in
tools/migrate_data_per_tu.py), and inserts the *safe* ones as idiomatic
typed C definitions directly into the tracked `<TU>.c` — no
`__attribute__((section(".X.0xVMA")))` wrappers. ee-gcc's
`-fdata-sections` emits each plain def into its own
`.<sect>.D_<VMA>` section; tools/postprocess_slinky_ld.py routes those
to the correct VMA, so inline defs land byte-identically (proven by
src/DmaPacket.c).

What gets inlined (the mechanically-safe categories):

  * scalars (size 1/2/4)      -> `unsigned char/short/int D_X = 0x..;`
                                 ee-gcc aligns scalars to natural width
                                 (.align 0/1/2), so any aligned VMA is safe.
  * all-zero arrays (8-aligned VMA)
                              -> `unsigned char D_X[N] = { 0 };`
  * strings (8-aligned VMA)   -> `const char D_X[N] = "...";`
                                 (+ EUC-JP decode comment when multibyte)
  * plain numeric word arrays (8-aligned VMA, not a pointer table)
                              -> `unsigned int D_X[N] = { 0x.., .. };`

What stays in the sidecar (skipped, with a reason in --dry-run):

  * `_pad_*` and any block whose data shape we can't reconstruct.
  * ARRAYS at a 4-aligned-not-8 VMA — ee-gcc emits `.align 3` (8-byte)
    before every array regardless of element type (confirmed
    empirically), so inlining one shifts every later symbol by +4.
    The sidecar's chunking path (fix_sidecar_align.py) handles these.
  * `.lit4` floats — no clean ee-gcc default placement; tiny; deferred.
  * pointer tables (>=25% of words resolve to D_/func_/jtbl_ VMAs).
  * repeating-record / opaque blobs — need structural RE.
  * `.sdata` symbols referenced by an ee-gcc-compiled C body in THIS TU
    — colocating the def would flip the reference's addressing
    (gp_rel vs lui+addiu) and break SHA-1. Asm-side (INCLUDE_ASM)
    references are fine: they resolve identically whether the def is
    inline or in the sidecar.

After inlining, `tools/build.sh setup` regenerates the sidecar — its
`_scan_existing_definitions()` sees the new inline defs and omits those
symbols, so the sidecar shrinks (or vanishes) automatically.

Usage:
    tools/inline_tu_data.py --dry-run src/Texture.c     # review table
    tools/inline_tu_data.py src/Texture.c               # apply
    tools/inline_tu_data.py --sections .data .rodata src/Texture.c

Idempotent: symbols already defined inline (plain or attr-tagged) are
detected and skipped.
"""

from __future__ import annotations

import argparse
import bisect
import json
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / "tools"))

from migrate_data_per_tu import (  # noqa: E402  (shared helpers)
    _looks_like_string,
    _load_map,
    _resolve_word_as_pointer,
    SECTION_RANGES,
)

SDATA_LO, SDATA_HI = SECTION_RANGES[".sdata"]

# Per-symbol inline cap: a non-zero string / word array larger than this
# would push the tracked .c past check_no_rom.sh's 256 KB per-file limit.
# All-zero arrays are exempt (they emit as a one-line `{ 0 }`). Oversized
# blobs stay in the gitignored sidecar.
MAX_INLINE_BYTES = 32768

# check_no_rom.sh fails any tracked file > 256 KiB. Keep the inlined .c
# comfortably under that; the budget pass demotes the largest emits to
# the sidecar once the projected file size would exceed this.
FILE_CAP_BYTES = 250000


# ---------------------------------------------------------------------------
# Byte source: parse the TU's _data.c sidecar (already byte-typed),
# merging `_pad_*` chunks back into their parent D_ symbol so we
# classify at original-symbol granularity. The asm-side data files are
# no longer a usable source — rewrite_data_named_sections.py strips
# every migrated symbol from them.
# ---------------------------------------------------------------------------

ELEM_SIZE = {
    "unsigned char": 1, "char": 1, "signed char": 1,
    "unsigned short": 2, "short": 2,
    "unsigned int": 4, "int": 4, "float": 4,
    "void *": 4, "void*": 4,
}

# `__attribute__((section(".SECT.0xVMA"))) [const] TYPE NAME[OPT] = INIT ;`
_SIDECAR_DEF = re.compile(
    r'__attribute__\(\(section\("\.(?P<sect>\w+)\.0x(?P<vma>[0-9A-Fa-f]+)"\)\)\)\s+'
    r'(?:const\s+)?(?P<ty>void\s*\*|unsigned\s+(?:char|short|int)|signed\s+char|char|short|int|float)\s+'
    r'(?P<name>(?:D_|_pad_)[0-9A-Fa-f]+)\s*'
    r'(?:\[\s*(?P<n>\d+)\s*\])?\s*=\s*(?P<init>.*?);',
    re.DOTALL,
)


def _norm_ty(ty: str) -> str:
    if "void" in ty and "*" in ty:
        return "void *"
    return " ".join(ty.split())


def _decode_init(ty: str, n: int | None, init: str) -> bytes | None:
    """Decode a sidecar initializer to raw little-endian bytes. Returns
    None for shapes we can't represent as fixed bytes (void* pointer
    tables, string literals)."""
    es = ELEM_SIZE[ty]
    if ty == "void *":
        return None  # pointer table — leave in sidecar
    init = init.strip()
    if init.startswith('"'):
        return None  # already a string literal — handled elsewhere
    if init.startswith("{"):
        body = init.strip("{} \t\n").strip()
        elems = [e.strip() for e in body.split(",") if e.strip() != ""]
        count = n if n is not None else len(elems)
        if len(elems) == 1 and elems[0] in ("0", "0x0", "0x00") and n:
            return b"\x00" * (es * count)
        if len(elems) != count:
            return None
        out = bytearray()
        for e in elems:
            try:
                out += (int(e, 0) & ((1 << (8 * es)) - 1)).to_bytes(es, "little")
            except ValueError:
                return None
        return bytes(out)
    # scalar
    try:
        return (int(init, 0) & ((1 << (8 * es)) - 1)).to_bytes(es, "little")
    except ValueError:
        return None


def parse_sidecar(sidecar_path: Path):
    """Return (symbols, void_syms) where:
      symbols  = {D_sym: (vma, sect, bytes)} at original granularity
                 (_pad_* chunks merged back into their parent D_),
      void_syms = {D_sym: (vma, sect)} for void* pointer tables (skip).
    """
    text = sidecar_path.read_text()
    defs = []  # (vma, sect, name, ty, bytes_or_None)
    void_syms: dict[str, tuple[int, str]] = {}
    for m in _SIDECAR_DEF.finditer(text):
        sect = "." + m.group("sect")
        vma = int(m.group("vma"), 16)
        ty = _norm_ty(m.group("ty"))
        name = m.group("name")
        n = int(m.group("n")) if m.group("n") else None
        if ty == "void *":
            void_syms[name] = (vma, sect)
            defs.append((vma, sect, name, ty, None))
            continue
        data = _decode_init(ty, n, m.group("init"))
        defs.append((vma, sect, name, ty, data))
    defs.sort(key=lambda d: d[0])

    symbols: dict[str, tuple[int, str, bytes]] = {}
    cur_sym: str | None = None
    cur_vma = 0
    cur_sect = ""
    cur_buf = bytearray()

    def _flush():
        nonlocal cur_sym
        if cur_sym is not None:
            symbols[cur_sym] = (cur_vma, cur_sect, bytes(cur_buf))
        cur_sym = None

    for vma, sect, name, ty, data in defs:
        if name.startswith("_pad_"):
            if (cur_sym is not None and data is not None
                    and sect == cur_sect and vma == cur_vma + len(cur_buf)):
                cur_buf += data
            # else: orphan pad — ignore (parent was unparseable/void)
            continue
        # D_ symbol
        _flush()
        if data is None:
            continue  # void* / string — recorded in void_syms or skipped
        cur_sym, cur_vma, cur_sect, cur_buf = name, vma, sect, bytearray(data)
    _flush()
    return symbols, void_syms


# ---------------------------------------------------------------------------
# Classification
# ---------------------------------------------------------------------------

class Result:
    __slots__ = ("sym", "vma", "sect", "size", "category", "action",
                 "reason", "lines", "euc")

    def __init__(self, sym, vma, sect, size):
        self.sym = sym
        self.vma = vma
        self.sect = sect
        self.size = size
        self.category = "?"
        self.action = "skip"
        self.reason = ""
        self.lines: list[str] = []
        self.euc: str | None = None


def _c_string_literal(data: bytes) -> tuple[str, str | None]:
    """Return (C string literal, euc_jp_decoded_or_None). The literal
    covers bytes up to the last non-zero byte; the array's declared [N]
    zero-fills the trailing padding (and the implicit terminator)."""
    last = max(i for i, b in enumerate(data) if b != 0)
    body = data[: last + 1]
    out = []
    for b in body:
        if b == 0x0A:
            out.append("\\n")
        elif b == 0x09:
            out.append("\\t")
        elif b == 0x22:
            out.append('\\"')
        elif b == 0x5C:
            out.append("\\\\")
        elif 0x20 <= b < 0x7F:
            out.append(chr(b))
        else:
            out.append("\\%03o" % b)  # 3-digit octal: unambiguous next-char
    lit = '"' + "".join(out) + '"'
    euc = None
    if any(b >= 0x80 for b in body):
        try:
            euc = body.rstrip(b"\x00").decode("euc-jp")
        except Exception:
            euc = None
    return lit, euc


def _is_pointer_table(data: bytes) -> bool:
    """True if >=25% of the 4-byte words resolve to a known
    D_/func_/jtbl_ VMA (mirrors migrate_data_per_tu._emit_chunked's
    density gate). Such tables must be hand-typed as `void *[]`."""
    if len(data) < 4 or len(data) % 4 != 0:
        return False
    mf = _load_map()
    if mf is None:
        return False
    words = [int.from_bytes(data[i:i + 4], "little")
             for i in range(0, len(data), 4)]
    resolved = sum(1 for w in words
                   if _resolve_word_as_pointer(w, mf) is not None)
    return resolved >= 1 and resolved * 4 >= len(words)


def _looks_like_address_table(data: bytes) -> bool:
    """True if the block reads as little-endian pointers into the loaded
    VMA range (0x00100000..0x00700000). Catches address tables the
    sidecar typed as `unsigned char[]` whose pointers target mid-array
    locations (so they don't resolve to exact symbols and slip past
    _is_pointer_table) — and which _looks_like_string false-positives on
    (a printable byte + a 0x00 every 4th byte). Must be checked before
    the string test.

    Gate: >=2 nonzero words and EVERY nonzero word lands in the loaded
    VMA range. A real address table has every entry as a 0x00XXXXXX
    pointer; an ASCII string like "MIPMAPK\\0" has at least one word with
    a high non-zero byte (e.g. 0x4D504D49) that falls out of range, so it
    isn't misflagged."""
    if len(data) < 4 or len(data) % 4 != 0:
        return False
    words = [int.from_bytes(data[i:i + 4], "little")
             for i in range(0, len(data), 4)]
    nonzero = [w for w in words if w != 0]
    if len(nonzero) < 2:
        return False
    return all(0x00100000 <= w < 0x00700000 for w in nonzero)


def classify(sym: str, vma: int, sect: str, data: bytes,
             c_refs: set[str], inc_externs: set[str],
             asm_gprel: set[str]) -> Result:
    r = Result(sym, vma, sect, len(data))
    size = len(data)

    if size == 0:
        r.reason = "empty"
        return r

    # >8-byte symbol referenced via %gp_rel by this TU's INCLUDE_ASM:
    # inlining an oversized local def flips ee-as's gp_rel pseudo to
    # lui+addiu (1→2 insns), growing the asm function. Leave in sidecar.
    if size > 8 and sym in asm_gprel:
        r.category = "asm-gprel-oversized"
        r.reason = "%gp_rel in TU asm + >8 B (ee-as pseudo would flip)"
        return r

    # Declared extern in an included .c.inc fragment (hand-matched code):
    # inlining the def into this TU would clash with the fragment's extern
    # type. Leave it in the sidecar's separate .o.
    if sym in inc_externs:
        r.category = "inc-extern"
        r.reason = "extern in included .c.inc (type-conflict risk)"
        return r

    # .lit4 floats — deferred (no clean ee-gcc default placement).
    if sect == ".lit4":
        r.category = "lit4"
        r.reason = "lit4 float (deferred)"
        return r

    # Symbol referenced by an ee-gcc-compiled C body in THIS TU → leave it
    # in the sidecar's separate .o. Colocating the def changes what the
    # compiler sees at the reference site (extern vs local def), which can
    # change the addressing it emits — gp_rel vs absolute lui+addiu differ
    # in INSTRUCTION COUNT (1 vs 2), so the referencing function's code
    # size shifts, moving .text end → _gp → every gp_rel offset (total
    # SHA divergence), and small non-.sdata symbols additionally hit
    # "relocation truncated to fit R_MIPS_GPREL16". Size doesn't bound the
    # risk. Asm (INCLUDE_ASM) references are immune: their instructions are
    # pre-written and fixed; ee-as just resolves the symbol locally to the
    # same bytes. So the safe boundary is: never inline a C-referenced
    # symbol; only asm-referenced / unreferenced data migrates.
    if sym in c_refs:
        r.category = "c-ref"
        r.reason = "referenced by tracked C body (codegen-size risk)"
        return r

    is_array = size > 4

    # --- Scalars (size 1/2/4): natural alignment, always safe ---
    if not is_array:
        if size == 1:
            ty, val = "unsigned char", data[0]
            r.lines = [f"unsigned char {sym} = 0x{val:02X};"]
        elif size == 2:
            val = int.from_bytes(data, "little")
            r.lines = [f"unsigned short {sym} = 0x{val:04X};"]
        else:  # size in (3, 4) — treat as a 4-byte word scalar
            if size != 4:
                r.category = "odd"
                r.reason = f"odd scalar size {size}"
                return r
            val = int.from_bytes(data, "little")
            r.lines = [f"unsigned int {sym} = 0x{val:08X};"]
        r.category = "scalar"
        r.action = "emit"
        return r

    # --- Arrays: only safe at an 8-aligned VMA (.align 3 hazard) ---
    if vma % 8 != 0:
        r.category = "array-misaligned"
        r.reason = f"array at 4-aligned VMA (.align 3 would shift +{8 - vma % 8})"
        return r

    if all(b == 0 for b in data):
        r.category = "all-zero"
        r.action = "emit"
        r.lines = [f"unsigned char {sym}[{size}] = {{ 0 }};"]
        return r

    # Address tables before strings: pointer blobs typed as byte arrays
    # in the sidecar can false-positive _looks_like_string.
    if _looks_like_address_table(data) or _is_pointer_table(data):
        r.category = "pointer-table"
        r.reason = "address/pointer table (needs hand-typing)"
        return r

    if _looks_like_string(data):
        # Size guard: a huge non-zero blob inlined verbatim would blow
        # check_no_rom.sh's 256 KB per-file cap. Leave oversized ones in
        # the sidecar (they're gitignored, so the cap doesn't apply there).
        if size > MAX_INLINE_BYTES:
            r.category = "too-large"
            r.reason = f"string {size} B > {MAX_INLINE_BYTES} cap"
            return r
        lit, euc = _c_string_literal(data)
        r.category = "string"
        r.action = "emit"
        r.euc = euc
        r.lines = [f"const char {sym}[{size}] = {lit};"]
        return r

    if size % 4 == 0 and not _is_pointer_table(data):
        if size > MAX_INLINE_BYTES:
            r.category = "too-large"
            r.reason = f"word-array {size} B > {MAX_INLINE_BYTES} cap"
            return r
        words = [int.from_bytes(data[i:i + 4], "little")
                 for i in range(0, size, 4)]
        parts = ", ".join(f"0x{w:08X}" for w in words)
        r.category = "word-array"
        r.action = "emit"
        r.lines = [f"unsigned int {sym}[{len(words)}] = {{ {parts} }};"]
        return r

    r.category = "opaque"
    r.reason = "opaque / record / pointer-table (needs RE)"
    return r


# ---------------------------------------------------------------------------
# Source-file analysis
# ---------------------------------------------------------------------------

INCLUDE_ASM_LINE = re.compile(r"INCLUDE_ASM(_NOAT|_NOP_PAD)?\s*\(")
EXTERN_LINE = re.compile(r"^\s*extern\b")


def _strip_for_cref(text: str) -> str:
    """Remove comments, INCLUDE_ASM lines, and extern lines so the
    remaining text is (approximately) the ee-gcc-compiled C — used to
    detect whether a symbol is referenced by a real C body."""
    text = re.sub(r"/\*.*?\*/", " ", text, flags=re.DOTALL)
    text = re.sub(r"//[^\n]*", " ", text)
    kept = []
    for ln in text.splitlines():
        if INCLUDE_ASM_LINE.search(ln):
            continue
        if EXTERN_LINE.match(ln):
            continue
        kept.append(ln)
    return "\n".join(kept)


def inc_extern_symbols(tu_path: Path, tu_c_text: str) -> set[str]:
    """Symbols declared `extern` in any `.inc` / `.c.inc` fragment the TU
    #includes. Those fragments are hand-matched code we must not edit, so
    a def we inline must NOT conflict with their extern's type. Simplest
    safe rule: skip inlining any such symbol (leave it in the sidecar's
    separate .o, where the extern + def don't share a translation unit)."""
    out: set[str] = set()
    extern_re = re.compile(r'\bextern\b[^;]*\b(D_[0-9A-Fa-f]{8})\b')
    for m in re.finditer(r'#include\s+"([^"]+\.inc)"', tu_c_text):
        inc = (tu_path.parent / m.group(1)).resolve()
        if not inc.exists():
            continue
        try:
            itext = inc.read_text(errors="replace")
        except Exception:
            continue
        for em in extern_re.finditer(itext):
            out.add(em.group(1))
    return out


def _included_inc_text(tu_path: Path, tu_c_text: str) -> str:
    """Concatenated text of every `.inc` / `.c.inc` fragment the TU
    #includes. These are compiled as part of the TU, so a symbol they
    reference is a real C reference for codegen purposes."""
    parts: list[str] = []
    for m in re.finditer(r'#include\s+"([^"]+\.inc)"', tu_c_text):
        inc = (tu_path.parent / m.group(1)).resolve()
        if inc.exists():
            try:
                parts.append(inc.read_text(errors="replace"))
            except Exception:
                pass
    return "\n".join(parts)


def asm_gprel_symbols(tu_path: Path, tu_c_text: str, inc_text: str) -> set[str]:
    """Symbols referenced via `%gp_rel(D_X)` in the .s files this TU pulls
    in through INCLUDE_ASM. ee-as expands that gp_rel pseudo based on the
    symbol's *defined* size: extern (or <=8 B local) → real gp_rel load
    (1 insn); a local def > 8 B → not small-data → lui+addiu (2 insns).
    So inlining a >8-byte def for such a symbol grows the asm function by
    an instruction per reference, shifting .text → _gp → SHA. Combined
    with the size>8 gate in classify, this leaves those in the sidecar."""
    out: set[str] = set()
    text = tu_c_text + "\n" + inc_text
    folders = set(re.findall(r'INCLUDE_ASM\w*\s*\(\s*"([^"]+)"', text))
    gprel_re = re.compile(r'%gp_rel\((D_[0-9A-Fa-f]{8})\)')
    for folder in folders:
        d = REPO / folder
        if not d.is_dir():
            continue
        for s in d.glob("*.s"):
            try:
                st = s.read_text(errors="replace")
            except Exception:
                continue
            for m in gprel_re.finditer(st):
                out.add(m.group(1))
    return out


def c_referenced(tu_c_text: str, inc_text: str, syms: set[str]) -> set[str]:
    """Of `syms`, which appear in a compiled-C body of this TU — the `.c`
    OR any `.c.inc` fragment it #includes (excluding INCLUDE_ASM / extern
    / comments)? A member of this set must NOT be inlined: colocating its
    def can change the referencing function's addressing (gp_rel vs
    absolute) and thus its code size (see classify)."""
    body = _strip_for_cref(tu_c_text) + "\n" + _strip_for_cref(inc_text)
    return {s for s in syms if re.search(rf"\b{s}\b", body)}


def already_defined_inline(tu_c_text: str) -> set[str]:
    """Symbols already defined (plain or attr-tagged) in this file."""
    out: set[str] = set()
    typed = re.compile(
        r'__attribute__\s*\(\(section[^)]*\)\)\s*'
        r'(?:[\w\s\*]+?)\s+(D_[0-9A-Fa-f]{8})\b'
    )
    plain = re.compile(
        r'(?m)^(?!\s*extern\b)[ \t]*(?:[A-Za-z_]\w*\s+)+\**\s*'
        r'(D_[0-9A-Fa-f]{8})\b\s*(?:\[[^\]]*\])*\s*='
    )
    for m in typed.finditer(tu_c_text):
        out.add(m.group(1))
    for m in plain.finditer(tu_c_text):
        out.add(m.group(1))
    return out


def find_insertion_index(lines: list[str]) -> int:
    """Line index to insert the migration block before. Prefer the
    `#include "include_asm.h"` line; else the first INCLUDE_ASM; else
    the first function definition; else end of file."""
    for i, ln in enumerate(lines):
        if re.search(r'#include\s+"include_asm\.h"', ln):
            return i
    for i, ln in enumerate(lines):
        if INCLUDE_ASM_LINE.search(ln):
            return i
    for i, ln in enumerate(lines):
        if re.match(r"^\s*(?:void|int|char|short|float|unsigned|static)\b.*\)\s*\{?\s*$", ln):
            return i
    return len(lines)


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("tu", help="tracked TU .c file, e.g. src/Texture.c")
    ap.add_argument("--dry-run", action="store_true",
                    help="print the classification table, change nothing")
    ap.add_argument("--sections", nargs="+",
                    help="restrict to these sections, e.g. --sections .data .rodata")
    args = ap.parse_args()

    tu_path = REPO / args.tu
    if not tu_path.exists():
        sys.exit(f"inline_tu_data: {args.tu} not found")

    sidecar_path = tu_path.with_name(tu_path.stem + "_data.c")
    if not sidecar_path.exists():
        print(f"inline_tu_data: no sidecar {sidecar_path.name} — "
              f"nothing to inline (already retired?)")
        return 0

    all_bytes, void_syms = parse_sidecar(sidecar_path)
    tu_c_text = tu_path.read_text()
    inline_already = already_defined_inline(tu_c_text)

    sect_filter = set(args.sections) if args.sections else None

    # Which owned symbols are referenced by a tracked C body here? A
    # <=8-byte one carries the gp_rel hazard if inlined (see classify).
    inc_text = _included_inc_text(tu_path, tu_c_text)
    c_refs = c_referenced(tu_c_text, inc_text, set(all_bytes))
    inc_externs = inc_extern_symbols(tu_path, tu_c_text)
    asm_gprel = asm_gprel_symbols(tu_path, tu_c_text, inc_text)

    results: list[Result] = []
    # void* pointer tables: always skipped, but surface them in the table.
    for sym, (vma, sect) in sorted(void_syms.items(), key=lambda x: x[1][0]):
        if sym in inline_already:
            continue
        if sect_filter and sect not in sect_filter:
            continue
        r = Result(sym, vma, sect, 0)
        r.category = "pointer-table"
        r.reason = "void* pointer table (needs hand-typing)"
        results.append(r)

    for sym in sorted(all_bytes, key=lambda s: int(s.split("_")[-1], 16)):
        if sym in inline_already:
            continue  # idempotent
        vma, sect, data = all_bytes[sym]
        if sect_filter and sect not in sect_filter:
            continue
        results.append(classify(sym, vma, sect, data, c_refs, inc_externs,
                                 asm_gprel))

    emit = [r for r in results if r.action == "emit"]
    skip = [r for r in results if r.action == "skip"]

    # --- Per-file size budget: keep the tracked .c under check_no_rom's
    # 256 KiB cap. Skip the largest emits (by emitted text length) until
    # the projected file fits, leaving them in the sidecar. all-zero /
    # scalars are tiny so they survive; big word-arrays / strings yield. ---
    def _emit_len(r: Result) -> int:
        return sum(len(ln) + 1 for ln in r.lines) + (len(r.euc) + 16 if r.euc else 0)
    projected = len(tu_c_text) + 600 + sum(_emit_len(r) for r in emit)
    if projected > FILE_CAP_BYTES:
        for r in sorted(emit, key=_emit_len, reverse=True):
            if projected <= FILE_CAP_BYTES:
                break
            r.action = "skip"
            r.reason = f"file-cap: would exceed {FILE_CAP_BYTES} B tracked-file limit"
            projected -= _emit_len(r)
        emit = [r for r in results if r.action == "emit"]
        skip = [r for r in results if r.action == "skip"]

    # --- Dry-run / summary table ---
    if args.dry_run:
        print(f"# inline_tu_data {args.tu} — DRY RUN")
        print(f"# {len(emit)} emit, {len(skip)} skip "
              f"({len(inline_already)} already inline)\n")
        for r in sorted(results, key=lambda x: (x.action != "emit", x.vma)):
            tag = "EMIT" if r.action == "emit" else "skip"
            note = r.category if r.action == "emit" else f"{r.category}: {r.reason}"
            print(f"  {tag:4} 0x{r.vma:08X} {r.sect:8} {r.sym:14} "
                  f"sz={r.size:<6} {note}")
        from collections import Counter
        cats = Counter(r.category for r in emit)
        print("\n# emit by category:", dict(cats))
        return 0

    if not emit:
        print(f"inline_tu_data: nothing to inline for {args.tu} "
              f"({len(skip)} skipped, {len(inline_already)} already inline)")
        return 0

    # --- Build the migration block, grouped by category ---
    GROUPS = [
        ("scalar", "scalars"),
        ("all-zero", "zero-filled buffers"),
        ("string", "strings"),
        ("word-array", "numeric word tables"),
    ]
    block: list[str] = [
        f"/* Inlined data (Phase 3e) — migrated from {tu_path.stem}_data.c.",
        " * Plain typed defs; ee-gcc -fdata-sections + slinky place each",
        " * at its original VMA. See tools/inline_tu_data.py. */",
    ]
    for cat, label in GROUPS:
        rs = [r for r in emit if r.category == cat]
        if not rs:
            continue
        block.append("")
        block.append(f"/* {label} */")
        for r in sorted(rs, key=lambda x: x.vma):
            if r.euc:
                block.append(f'/* EUC-JP: "{r.euc}" */')
            block.extend(r.lines)
    block.append("")

    # --- Remove conflicting extern declarations for migrated symbols ---
    migrated_syms = {r.sym for r in emit}
    lines = tu_c_text.splitlines()
    kept: list[str] = []
    extern_decl = re.compile(
        r"^\s*extern\b[^;]*\b(D_[0-9A-Fa-f]{8})\b[^;]*;\s*$"
    )
    removed_externs = 0
    for ln in lines:
        m = extern_decl.match(ln)
        if m and m.group(1) in migrated_syms:
            removed_externs += 1
            continue
        kept.append(ln)
    lines = kept

    insert_at = find_insertion_index(lines)
    new_lines = lines[:insert_at] + block + lines[insert_at:]
    tu_path.write_text("\n".join(new_lines) + "\n")

    from collections import Counter
    cats = Counter(r.category for r in emit)
    print(f"inline_tu_data: {args.tu} — inlined {len(emit)} symbols "
          f"{dict(cats)}; removed {removed_externs} extern decl(s); "
          f"{len(skip)} left in sidecar")
    return 0


if __name__ == "__main__":
    sys.exit(main())
