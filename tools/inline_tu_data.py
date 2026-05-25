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

# Per-symbol inline cap. check_no_rom.sh now allows tracked C source up
# to 8 MiB (its content is gated by the raw-byte-array rule), so the
# only real limit is the per-file budget below. Keep a high per-symbol
# ceiling purely as a sanity backstop against a single absurd blob.
MAX_INLINE_BYTES = 4 * 1024 * 1024

# Per-file budget: keep the inlined .c under check_no_rom.sh's 8 MiB
# source ceiling (with margin). The budget pass demotes the largest
# emits to the sidecar only if a TU would somehow exceed this.
FILE_CAP_BYTES = 7 * 1024 * 1024


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
                 "reason", "lines", "euc", "keep_extern")

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
        self.keep_extern = False  # c-ref defs keep their extern (DmaPacket)


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


# Existing `extern` declaration shapes for a D_ symbol, used to emit a
# type-matched def that KEEPS the extern (DmaPacket pattern) so ee-gcc's
# addressing decision at reference sites is unchanged → .text identical.
_EXT_FUNCPTR = re.compile(
    r'extern\s+(?P<ret>[A-Za-z_][\w\s\*]*?)\(\s*\*\s*(?P<sym>D_[0-9A-Fa-f]{8})\s*\)'
    r'\s*\((?P<args>[^)]*)\)\s*;'
)
_EXT_OBJ = re.compile(
    r'extern\s+(?P<pre>(?:const\s+)?(?:unsigned\s+|signed\s+)?'
    r'(?:char|short|int|long|float|double|void)(?:\s*\*)*)\s*'
    r'(?P<sym>D_[0-9A-Fa-f]{8})\s*(?P<arr>\[[^\]]*\])?\s*;'
)


def emit_cref(sym: str, data: bytes, decl: str, mf) -> list[str] | None:
    """Emit a def for a C-referenced symbol that matches its existing
    `extern` declaration `decl` (which the caller keeps). Returns the def
    lines, or None if the shape isn't safely representable (caller skips).
    The extern fixes the addressing; this only supplies bytes."""
    size = len(data)
    m = _EXT_FUNCPTR.match(decl.strip())
    if m:  # function pointer: extern RET (*D_X)(ARGS);
        if size != 4:
            return None
        w = int.from_bytes(data, "little")
        ret, args = m.group("ret").strip(), m.group("args").strip()
        named = _resolve_word_as_pointer(w, mf) if mf else None
        val = (named[1:] if named and named.startswith("&") else
               f"({ret} (*)({args}))0x{w:08X}")
        return [f"{ret} (*{sym})({args}) = {val};"]
    m = _EXT_OBJ.match(decl.strip())
    if not m:
        return None
    pre = " ".join(m.group("pre").split())   # normalize spacing
    is_ptr = "*" in pre
    is_array = m.group("arr") is not None
    base = pre.replace("*", "").replace("const", "").strip()  # char/int/...

    def _ptr_elem(w):
        named = _resolve_word_as_pointer(w, mf) if mf else None
        if w == 0:
            return f"({pre})0"
        return (named[1:] if named and named.startswith("&")
                else f"({pre})0x{w:08X}")

    if not is_array:  # scalar
        if size > 4:
            return None
        w = int.from_bytes(data, "little")
        if is_ptr:
            return [f"{pre} {sym} = {_ptr_elem(w)};"]
        return [f"{pre} {sym} = 0x{w:0{size * 2}X};"]
    # array
    if is_ptr:                       # pointer array
        if size % 4:
            return None
        words = [int.from_bytes(data[i:i + 4], "little") for i in range(0, size, 4)]
        elems = ", ".join(_ptr_elem(w) for w in words)
        return [f"{pre} {sym}[{len(words)}] = {{ {elems} }};"]
    if base == "char":               # char[] — only if it's a string
        if not _looks_like_string(data):
            return None
        lit, _ = _c_string_literal(data)
        return [f"{pre} {sym}[{size}] = {lit};"]
    esz = {"short": 2, "int": 4, "long": 4, "float": 4}.get(base)
    if esz is None or size % esz:
        return None
    n = size // esz
    vals = [int.from_bytes(data[i:i + esz], "little") for i in range(0, size, esz)]
    elems = ", ".join(f"0x{v:0{esz * 2}X}" for v in vals)
    return [f"{pre} {sym}[{n}] = {{ {elems} }};"]


def _emit_array_value(sym: str, data: bytes) -> tuple[str, list[str], str | None]:
    """Lines for an 8-aligned array def. Returns (category, lines, euc).
    Empty lines ⇒ couldn't represent (caller skips as opaque)."""
    size = len(data)
    if all(b == 0 for b in data):
        return "all-zero", [f"unsigned char {sym}[{size}] = {{ 0 }};"], None
    if _looks_like_address_table(data) or _is_pointer_table(data):
        mf = _load_map()
        words = [int.from_bytes(data[i:i + 4], "little")
                 for i in range(0, size, 4)]
        parts = []
        for w in words:
            named = _resolve_word_as_pointer(w, mf) if mf else None
            if w == 0:
                parts.append("(void *)0")
            elif named:
                parts.append(f"(void *)0x{w:08X} /* {named} */")
            else:
                parts.append(f"(void *)0x{w:08X}")
        return "pointer-table", [f"void *{sym}[{len(words)}] = {{ {', '.join(parts)} }};"], None
    if _looks_like_string(data):
        lit, euc = _c_string_literal(data)
        return "string", [f"const char {sym}[{size}] = {lit};"], euc
    if size % 4 == 0:
        words = [int.from_bytes(data[i:i + 4], "little")
                 for i in range(0, size, 4)]
        parts = ", ".join(f"0x{w:08X}" for w in words)
        return "word-array", [f"unsigned int {sym}[{len(words)}] = {{ {parts} }};"], None
    return "opaque", [], None


def classify(sym: str, vma: int, sect: str, data: bytes,
             c_refs: set[str], inc_externs: set[str],
             asm_gprel: set[str], extern_decls: dict[str, str],
             mf, no_cref: bool = False) -> Result:
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

    # .lit4 floats: emit with an explicit `.lit4.0xVMA` attribute (the
    # documented lit4 survivor form — ee-gcc has no automatic .lit4
    # placement). Keeping a real `.lit4` input section is also required by
    # the slinky pipeline (an empty lit4 segment crashes slinky-cli with
    # EmptyValue). Byte-exact via the raw bits as unsigned int (avoids
    # float-literal round-trip risk). Scalars are .align 2 (safe at any
    # 4-aligned VMA); float arrays are 8-aligned in practice.
    if sect == ".lit4":
        # A lit4 float referenced by C: emitting the def in-TU (even
        # attr-pinned) can flip the reference gp_rel↔absolute → .text
        # change. Leave those in the sidecar (it still provides a .lit4
        # input section, so the slinky segment stays non-empty).
        if sym in c_refs:
            r.category = "lit4"
            r.reason = "lit4 referenced by C (kept in sidecar)"
            return r
        attr = f'__attribute__((section(".lit4.0x{vma:08X}")))'
        if size == 4:
            w = int.from_bytes(data, "little")
            r.lines = [f"{attr} unsigned int {sym} = 0x{w:08X};"]
            r.category, r.action = "lit4", "emit"
            return r
        if size % 4 == 0:
            words = [int.from_bytes(data[i:i + 4], "little")
                     for i in range(0, size, 4)]
            parts = ", ".join(f"0x{w:08X}" for w in words)
            r.lines = [f"{attr} unsigned int {sym}[{len(words)}] = {{ {parts} }};"]
            r.category, r.action = "lit4", "emit"
            return r
        r.category = "lit4"
        r.reason = f"lit4 odd size {size}"
        return r

    # Symbol referenced by an ee-gcc-compiled C body in THIS TU (the `.c`
    # OR an included `.c.inc`). Naively colocating the def would change
    # what the compiler sees at the reference site (extern vs local def)
    # and could flip gp_rel↔absolute (1 vs 2 insns) → .text shift →
    # whole-binary SHA break. The DmaPacket fix: KEEP the existing extern
    # (which is what decides addressing) and add a type-matched def that
    # only supplies bytes — ee-gcc's view at reference sites is unchanged,
    # so .text stays identical. Requires a parseable extern to match; if
    # we can't represent the def for that type, leave it in the sidecar.
    if sym in c_refs or sym in inc_externs:
        decl = extern_decls.get(sym)
        lines = (emit_cref(sym, data, decl, mf)
                 if decl and not no_cref else None)
        if lines:
            r.category = "c-ref"
            r.action = "emit"
            r.keep_extern = True
            r.lines = lines
            return r
        r.category = "c-ref" if sym in c_refs else "inc-extern"
        r.reason = ("no parseable extern to match (kept in sidecar)" if decl is None
                    else "extern type not safely representable")
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

    # --- Arrays at an 8-aligned VMA: emit directly (no .align 3 shift) ---
    if vma % 8 == 0:
        cat, lines, euc = _emit_array_value(sym, data)
        if lines:
            r.category, r.action, r.lines, r.euc = cat, "emit", lines, euc
            return r
        r.category = "opaque"
        r.reason = "opaque (not 4-divisible / no inferable shape)"
        return r

    # --- Arrays at a 4-aligned-not-8 VMA: ee-gcc forces .align 3 on any
    # array, shifting it +4. Split into a 4-byte scalar head (natural
    # .align 2, safe at the 4-aligned VMA) + an 8-aligned tail array
    # under a VMA-named synthetic symbol. The migrator skips the original
    # symbol's whole extent once it sees the head defined, so the tail
    # isn't double-emitted. ---
    if vma % 8 == 4 and size >= 4:
        head = int.from_bytes(data[0:4], "little")
        lines = [f"unsigned int {sym} = 0x{head:08X};"]
        tail = data[4:]
        if tail:
            tail_vma = vma + 4  # now 8-aligned
            tcat, tlines, teuc = _emit_array_value(f"D_{tail_vma:08X}", tail)
            if not tlines:
                r.category = "array-misaligned"
                r.reason = "misaligned tail not representable"
                return r
            if teuc:
                lines.append(f'/* EUC-JP: "{teuc}" */')
            lines += tlines
        r.category = "misaligned-split"
        r.action = "emit"
        r.lines = lines
        return r

    r.category = "array-misaligned"
    r.reason = f"unhandled alignment (vma%8={vma % 8})"
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
    ap.add_argument("--no-cref", action="store_true",
                    help="leave C-referenced symbols in the sidecar (use for TUs "
                         "where keep-extern still flips addressing → .text change)")
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
    mf = _load_map()
    # Existing extern declarations (in the .c only — we keep these in
    # place for c-ref defs; .inc externs belong to hand-matched code we
    # don't touch, and emit_cref matches them via the same decl text).
    extern_decls: dict[str, str] = {}
    _ext_line = re.compile(r'^\s*(extern\b[^;]*\bD_[0-9A-Fa-f]{8}\b[^;]*;)\s*$',
                           re.MULTILINE)
    for src in (tu_c_text, inc_text):
        for m in _ext_line.finditer(src):
            decl = m.group(1)
            sm = re.search(r'(D_[0-9A-Fa-f]{8})', decl)
            if sm and sm.group(1) not in extern_decls:
                extern_decls[sm.group(1)] = decl

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
                                 asm_gprel, extern_decls, mf, args.no_cref))

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

    # --- Build the migration block, grouped by category (every emit
    # category must be listed here, else its defs are silently dropped). ---
    GROUPS = [
        ("scalar", "scalars"),
        ("all-zero", "zero-filled buffers"),
        ("string", "strings"),
        ("word-array", "numeric word tables"),
        ("pointer-table", "pointer / address tables"),
        ("misaligned-split", "misaligned arrays (scalar head + aligned tail)"),
        ("c-ref", "C-referenced data (extern kept, def supplies bytes)"),
        ("lit4", "lit4 floats (section-pinned, raw bits)"),
    ]
    known = {c for c, _ in GROUPS}
    leftover = sorted({r.category for r in emit} - known)
    for c in leftover:
        GROUPS.append((c, c))
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

    # --- Remove conflicting extern declarations for migrated symbols,
    # EXCEPT c-ref defs (keep_extern): those rely on the extern staying
    # in place so ee-gcc's addressing at reference sites is unchanged. ---
    keep_extern_syms = {r.sym for r in emit if r.keep_extern}
    migrated_syms = {r.sym for r in emit} - keep_extern_syms
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
