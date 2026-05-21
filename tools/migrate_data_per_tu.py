#!/usr/bin/env python3
"""
migrate_data_per_tu.py — emit per-TU data .c files (per-TU layout).

Reads `decomp/data_tu_map.json` (built by tools/build_data_tu_map.py)
and the asm-side data files. For each TU, generates a single
`src/cod/<tu_base>_data.c` containing definitions for every data
symbol assigned to that TU. The definitions use
`__attribute__((section(".X.0xVMA")))` so the linker places them at
the correct VMA via SORT_BY_NAME (see tools/postprocess_ld.py).

Chunking strategy
-----------------

  * If the symbol's VMA is 8-aligned: emit one `unsigned char[N]`
    per block. ee-gcc 2.9's `.align 3` over-alignment is a no-op
    at an 8-aligned VMA, so the section stays in the right place.
  * For misaligned VMAs (rare — mid-table byte symbols), emit
    per-VMA aligned-largest chunks: `unsigned int` for 4-aligned
    4-byte chunks, then `unsigned short`, then `unsigned char`.
    Single-element definitions of these types get small enough
    section alignment that the linker can place them anywhere.

Function-side codegen
---------------------
The per-TU .c files contain ONLY data definitions — no function
bodies. Matched function .c files (src/cod/<file_off>.c) keep
their `extern` declarations of these symbols, so ee-gcc 2.9
continues to emit %gp_rel for small-data references (the
small-data analysis is preserved because the function .c never
sees a section attribute).

Plumbing
--------
* `tools/rewrite_data_named_sections.py` reads every src/cod/*.c
  for `__attribute__((section(".X.0xVMA")))` definitions and
  strips the corresponding blocks from the asm-side data files.
* Per-TU files are picked up by the Makefile's `find src/ -name
  '*.c'` glob — no yaml editing needed.
* Add file basenames to config/use_modern_as.txt so they skip
  the slow ee-as 2.10 (large data .c files are unusably slow
  to assemble there).

Inputs / outputs
----------------
* IN:  decomp/data_tu_map.json
* IN:  asm/data/cod/{531900.sdata.s,530900.lit4.s,453700.rodata.s,174700.data.s}
* OUT: src/cod/<tu_base>_data.c (one per TU)

Idempotent: each run regenerates every per-TU file from scratch.
"""

from __future__ import annotations

import json
import re
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
TU_MAP = REPO_ROOT / "decomp" / "data_tu_map.json"
MAP_PATH = REPO_ROOT / "build" / "ico.us.map"
# Loaded VMA range — words outside this range are integers, not pointers.
LOAD_VMA_LO = 0x00100000
LOAD_VMA_HI = 0x00700000
ASM_FILES = {
    ".sdata":  REPO_ROOT / "asm" / "data" / "src" / "cod" / "531900.sdata.s",
    ".lit4":   REPO_ROOT / "asm" / "data" / "src" / "cod" / "530900.lit4.s",
    ".rodata": REPO_ROOT / "asm" / "data" / "src" / "cod" / "453700.rodata.s",
    ".data":   REPO_ROOT / "asm" / "data" / "src" / "cod" / "174700.data.s",
}
SECTION_RANGES = {
    ".sdata":  (0x00631900, 0x00633BC6),
    ".lit4":   (0x00630900, 0x006318D0),
    ".rodata": (0x00553700, 0x006308A8),
    ".data":   (0x00274700, 0x005536B8),
}
SRC_DIR = REPO_ROOT / "src" / "cod"
USE_MODERN_AS = REPO_ROOT / "config" / "use_modern_as.txt"


def _section_for_vma(vma: int) -> str | None:
    for sect, (lo, hi) in SECTION_RANGES.items():
        if lo <= vma < hi:
            return sect
    return None


def _tu_to_filename(tu: str) -> str:
    """Convert a TU path into the per-TU data-sidecar .c file's path
    relative to `src/`. TUs under the original `src/` dir flatten to
    the top of `src/`; TUs under `ios/`, `isys/`, `sound/` keep their
    subdir structure. The `_data` suffix distinguishes auto-generated
    data sidecars from hand-crafted TU files (e.g. src/Basic.c,
    promoted in commit 0e05303), so this tool can be rerun without
    overwriting hand-edited TU sources. Example mapping:

        src/Basic.c          →  Basic_data.c
        src/way_tool.c       →  way_tool_data.c
        ios/cdvd.c           →  ios/cdvd_data.c
        isys/gobj.c          →  isys/gobj_data.c
        sound/s_init.c       →  sound/s_init_data.c
        _unassigned          →  _unassigned_data.c

    Once a TU's matched functions migrate into the hand-crafted .c,
    its sidecar can be folded in and deleted. Until then, both files
    coexist and contribute to the same final .o sections (the linker
    uses SORT_BY_NAME on per-VMA section names, so data placement
    doesn't depend on which file holds each definition).
    """
    if tu == "_unassigned":
        return "src/_unassigned_data.c"
    # TU strings are repo-root-relative paths (e.g. "src/Basic.c",
    # "ios/cdvd.c"). Insert `_data` before the .c extension.
    rel = tu
    if rel.endswith(".c"):
        return rel[:-2] + "_data.c"
    return rel + "_data.c"


# All dlabel boundaries (D_ + jtbl_ + func_) — used to compute the
# END_VMA of each migrated block. We need to see every boundary so
# the size of a `D_` block doesn't accidentally extend across a
# subsequent `jtbl_*` (which the migrator deliberately skips — see
# below) and produce too-long byte arrays.
ALL_DLABEL_RE = re.compile(
    r'^dlabel\s+((?:D_|jtbl_|func_)[0-9A-Fa-f]{8})',
    re.MULTILINE,
)

# Block-extractor for `D_` blocks only.
#
# IMPORTANT — only `D_` symbols are migrated. `jtbl_*` symbols are jump
# tables: their bytes are 4-byte little-endian encodings of .text VMAs
# (the `.L<vma>` labels they index into). Emitting those as raw byte
# arrays would (a) duplicate the asm-side definition because the
# rewriter only strips `D_` blocks (its name-scan deliberately ignores
# jtbl to keep label resolution on the asm side), and (b) bake the
# current .text layout into the bytes, breaking any future .text
# matching that shifts symbols. Jump tables stay on the asm side until
# they're hand-typed as `static void *jtbl_X[] = { &&L0, &&L1, ... }`
# in the corresponding TU source. Same logic applies to the rare
# `func_*` labels that appear in data sections.
DLABEL_RE = re.compile(
    r'^dlabel\s+(D_[0-9A-Fa-f]{8})\s*\n(?P<body>.*?)^enddlabel',
    re.MULTILINE | re.DOTALL,
)


def _walk_blocks(asm_path: Path, vma_lo: int, vma_hi: int):
    """Yield (sym, vma, end_vma, body) for every `D_` block, using
    *all* dlabel boundaries (D_/jtbl_/func_) to compute end_vma. If
    a D_ block is immediately followed by a jtbl_ in the asm, end_vma
    is the jtbl_'s VMA, so the migrated byte array stops at the right
    spot instead of extending into the next jtbl block (which would
    duplicate bytes that the asm side still emits)."""
    if not asm_path.exists():
        return
    text = asm_path.read_text()
    # All boundary VMAs (D_ + jtbl_ + func_) for end-of-block lookup.
    boundaries = sorted({
        int(m.group(1).split("_")[-1], 16)
        for m in ALL_DLABEL_RE.finditer(text)
    })
    d_blocks = []
    for m in DLABEL_RE.finditer(text):
        sym = m.group(1)
        vma = int(sym.split("_")[-1], 16)
        d_blocks.append((vma, sym, m.group("body")))
    d_blocks.sort()
    import bisect
    for vma, sym, body in d_blocks:
        # end_vma = the next boundary strictly greater than vma, or
        # vma_hi if this block is the last one in the section.
        idx = bisect.bisect_right(boundaries, vma)
        end_vma = boundaries[idx] if idx < len(boundaries) else vma_hi
        if vma_lo <= vma < vma_hi:
            yield sym, vma, end_vma, body


ADDR_HEX_RE = re.compile(
    r'^[ \t]*/\*\s+[0-9A-Fa-f]+\s+(?P<vma>[0-9A-Fa-f]{8})\s+'
    r'(?P<hex>(?:[0-9A-Fa-f]{2})+)\s*\*/'
)
CONT_HEX_RE = re.compile(r'^[ \t]*/\*\s*(?P<hex>[0-9A-Fa-f]+)\s*\*/\s*$')
ADDR_ONLY_RE = re.compile(
    r'^[ \t]*/\*\s+[0-9A-Fa-f]+\s+(?P<vma>[0-9A-Fa-f]{8})\s*\*/\s*(?P<rest>.*)$'
)


def _extract_bytes(body: str, start_vma: int, end_vma: int) -> bytes | None:
    """Reconstruct the raw byte sequence for a dlabel block. Returns
    None if the block has a shape we can't represent (e.g. .word with
    a symbol reference — those need link-time relocations that the
    pool approach can't emit purely from C definitions)."""
    expected_size = end_vma - start_vma
    out = bytearray()
    cursor = start_vma
    lines = body.splitlines()
    i = 0
    while i < len(lines):
        line = lines[i]
        m = ADDR_HEX_RE.match(line)
        if m:
            vma = int(m.group("vma"), 16)
            if vma != cursor:
                return None
            word = bytes.fromhex(m.group("hex"))
            out.extend(word)
            cursor += len(word)
            i += 1
            continue
        m = ADDR_ONLY_RE.match(line)
        if m:
            vma = int(m.group("vma"), 16)
            if vma != cursor:
                return None
            rest = m.group("rest").strip()
            mbyte = re.match(r'\.byte\s+(.+)$', rest)
            if mbyte:
                for elt in mbyte.group(1).split(","):
                    elt = elt.strip()
                    if not elt or not re.fullmatch(r"-?(?:0x[0-9A-Fa-f]+|\d+)", elt):
                        return None
                    out.append(int(elt, 0) & 0xFF)
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
                    out.extend(val.to_bytes(2, "little"))
                    cursor += 2
                i += 1
                continue
            mword = re.match(r'\.(?:word|long|4byte|float)\s+(.+)$', rest)
            if mword and re.fullmatch(r"-?(?:0x[0-9A-Fa-f]+|\d+)", mword.group(1).strip()):
                val = int(mword.group(1).strip(), 0) & 0xFFFFFFFF
                out.extend(val.to_bytes(4, "little"))
                cursor += 4
                i += 1
                continue
            i += 1
            while i < len(lines):
                cl = lines[i]
                if cl.strip().startswith("enddlabel"):
                    break
                if ADDR_HEX_RE.match(cl) or ADDR_ONLY_RE.match(cl):
                    break
                if re.match(r'\s*\.\s*(align|balign)\b', cl):
                    i += 1
                    continue
                m2 = CONT_HEX_RE.match(cl)
                if m2:
                    hex_str = m2.group("hex")
                    if len(hex_str) % 2 != 0:
                        return None
                    out.extend(bytes.fromhex(hex_str))
                    cursor += len(hex_str) // 2
                    i += 1
                    continue
                i += 1
            continue
        if re.match(r'\s*\.\s*(align|balign)\b', line):
            j = i + 1
            while j < len(lines) and not lines[j].strip():
                j += 1
            if j < len(lines):
                next_m = ADDR_HEX_RE.match(lines[j]) or ADDR_ONLY_RE.match(lines[j])
                if next_m:
                    next_vma = int(next_m.group("vma"), 16)
                    if next_vma > cursor:
                        out.extend(b"\x00" * (next_vma - cursor))
                        cursor = next_vma
            i += 1
            continue
        i += 1

    if cursor < end_vma:
        out.extend(b"\x00" * (end_vma - cursor))
        cursor = end_vma
    if len(out) != expected_size:
        return None
    return bytes(out)


_MAP_CACHE: object = ...  # sentinel — None after first failed load


def _load_map():
    """Cached mapfile_parser load. Returns a MapFile or None if the
    linker map isn't built yet. Parse cost is ~3 s; one parse per run."""
    global _MAP_CACHE
    if _MAP_CACHE is not ...:
        return _MAP_CACHE
    if not MAP_PATH.exists():
        _MAP_CACHE = None
        return None
    try:
        from mapfile_parser import mapfile
        _MAP_CACHE = mapfile.MapFile.newFromMapFile(MAP_PATH)
    except Exception:
        _MAP_CACHE = None
    return _MAP_CACHE


def _resolve_word_as_pointer(w: int, mf) -> str | None:
    """If `w` exactly matches a known D_/func_/jtbl_ symbol's VMA,
    return `&name`; else None. Restricts to the loaded VMA range
    AND to canonical name prefixes — synthetic linker symbols
    (section starts, mangled names) aren't valid C references."""
    if mf is None:
        return None
    if not (LOAD_VMA_LO <= w < LOAD_VMA_HI):
        return None
    found = mf.findSymbolByVramOrVrom(w)
    if found is None:
        return None
    sym = found.symbol
    if sym.vram != w:
        return None  # word points mid-symbol — treat as int, not pointer
    name = sym.name
    # Only canonical decomp symbols are safe as `&name` initializers.
    # Mangled / section-internal names (e.g. __cod_16F5E0_textbin.NON_MATCHING,
    # D_00641821.NON_MATCHING) break C parsing.
    if not (name.startswith("D_")
            or name.startswith("func_")
            or name.startswith("jtbl_")):
        return None
    if "." in name or "$" in name:
        return None
    return f"&{name}"


def _looks_like_string(data: bytes) -> bool:
    """True if `data` plausibly contains text — NUL-terminated, at
    least one printable ASCII byte, no embedded zero-runs that
    aren't string padding. Both pure ASCII and ASCII+SJIS-mix qualify;
    the byte-array shape is preserved so the tracked-side migrators
    (string + SJIS) can recognize and re-type them."""
    if not data or data[-1] != 0:
        return False
    if not any(0x20 <= b < 0x7f for b in data):
        return False
    # Reject if there's a >=4-byte all-zero run somewhere before the
    # trailing padding — that means it's structured data, not a string.
    n = len(data)
    last_nonzero = -1
    for i in range(n - 1, -1, -1):
        if data[i] != 0:
            last_nonzero = i
            break
    if last_nonzero < 0:
        return False
    run = 0
    for i in range(last_nonzero):
        if data[i] == 0:
            run += 1
            if run >= 4:
                return False
        else:
            run = 0
    return True


def _emit_chunked(sym: str, vma: int, sect_name: str,
                  data: bytes) -> list[str]:
    if not data:
        return []
    # NOTE: rodata symbols are deliberately emitted WITHOUT `const`.
    # gas warns about this ("setting incorrect section attributes for
    # .rodata.0xVMA" — section name suggests `"a"` flags but a
    # non-const decl makes gcc emit `"aw"`). The warning is cosmetic.
    # Adding `const` produces a SHA-1 mismatch: ee-gcc's linker groups
    # sections by flag set, so a mix of `"a"` (const) and `"aw"`
    # (non-const) `.rodata.0x*` sections gets reordered relative to
    # baserom's all-`"aw"` layout. Revisit only if the rodata sidecars
    # ever become uniformly const-able.
    # Word-array branch: for 4-aligned VMAs with multi-word, non-zero,
    # non-string bytes, emit `void *[]` (with &func_/&D_ resolved via
    # linker map) — but ONLY when the block is densely populated with
    # symbol pointers (>=25% of words resolve). Otherwise fall back to
    # `unsigned int[]`. The density gate keeps string-fragment blobs
    # (e.g. arrays of "camdata/cam0135.gcm"-style strings broken across
    # 4-byte words) from being mis-typed as pointer tables — a few
    # words coincidentally match symbol VMAs in that case but the
    # array is really a string blob.
    if (vma % 4 == 0 and len(data) >= 4 and len(data) % 4 == 0
            and not all(b == 0 for b in data)
            and not _looks_like_string(data)):
        mf = _load_map()
        words = [int.from_bytes(data[i:i + 4], "little")
                 for i in range(0, len(data), 4)]
        resolved = [_resolve_word_as_pointer(w, mf) for w in words]
        ptr_count = sum(1 for r in resolved if r is not None)
        density_ok = len(words) > 0 and ptr_count * 4 >= len(words)
        if ptr_count >= 1 and density_ok:
            parts = [r if r is not None
                     else (f"(void *)0x{w:08X}" if w else "(void *)0")
                     for w, r in zip(words, resolved)]
            return [
                f'__attribute__((section("{sect_name}.0x{vma:08X}"))) '
                f'void *{sym}[{len(words)}] = {{ {", ".join(parts)} }};'
            ]
        parts = [f"0x{w:08X}" for w in words]
        return [
            f'__attribute__((section("{sect_name}.0x{vma:08X}"))) '
            f'unsigned int {sym}[{len(words)}] = {{ {", ".join(parts)} }};'
        ]
    if vma % 8 == 0:
        if len(data) == 1:
            return [
                f'__attribute__((section("{sect_name}.0x{vma:08X}"))) '
                f'unsigned char {sym} = 0x{data[0]:02X};'
            ]
        # All-zero arrays — common for explicitly-zeroed .data buffers —
        # are emitted as `{ 0 }`, which C99 implicitly zero-fills to the
        # full size. This produces byte-identical output but keeps the
        # source line short (a 6872-byte buffer otherwise becomes ~40 KB
        # of hex literals, blowing past the check_no_rom.sh 256 KB
        # tracked-file threshold for several huge TUs).
        if all(b == 0 for b in data):
            return [
                f'__attribute__((section("{sect_name}.0x{vma:08X}"))) '
                f'unsigned char {sym}[{len(data)}] = {{ 0 }};'
            ]
        bs = ", ".join(f"0x{b:02X}" for b in data)
        return [
            f'__attribute__((section("{sect_name}.0x{vma:08X}"))) '
            f'unsigned char {sym}[{len(data)}] = {{ {bs} }};'
        ]
    out: list[str] = []
    cursor = vma
    end = vma + len(data)
    first = True
    while cursor < end:
        rem = end - cursor
        off = cursor - vma
        if cursor % 4 == 0 and rem >= 4:
            sz = 4
            val = int.from_bytes(data[off:off + 4], "little")
            ty = "unsigned int"
            init = f"0x{val:08X}"
        elif cursor % 2 == 0 and rem >= 2:
            sz = 2
            val = int.from_bytes(data[off:off + 2], "little")
            ty = "unsigned short"
            init = f"0x{val:04X}"
        else:
            sz = 1
            val = data[off]
            ty = "unsigned char"
            init = f"0x{val:02X}"
        name = sym if first else f"_pad_{cursor:08X}"
        out.append(
            f'__attribute__((section("{sect_name}.0x{cursor:08X}"))) '
            f'{ty} {name} = {init};'
        )
        first = False
        cursor += sz
    return out


def _check_basename_collisions(tu_map: dict) -> None:
    """Each TU maps to a per-TU filename via _tu_to_filename. Bail if
    two distinct TUs collide (e.g. src/box.c and ios/box.c). The
    rename scheme can be lengthened in that case."""
    seen: dict[str, str] = {}
    for tu in {rec["tu"] for rec in tu_map.values()}:
        fname = _tu_to_filename(tu)
        if fname in seen and seen[fname] != tu:
            sys.exit(f"migrate_data_per_tu: filename collision "
                     f"'{fname}.c' between TUs '{seen[fname]}' and '{tu}'")
        seen[fname] = tu


def _ensure_use_modern_as(basenames: list[str]) -> None:
    """Append per-TU basenames to config/use_modern_as.txt so the
    Makefile uses mips-linux-gnu-as instead of the slow ee-as 2.10
    on these auto-generated data files."""
    if not USE_MODERN_AS.exists():
        return
    text = USE_MODERN_AS.read_text()
    existing: set[str] = set()
    for line in text.splitlines():
        line = line.split("#", 1)[0].strip()
        if line:
            existing.add(line)
    added: list[str] = []
    for name in basenames:
        if name not in existing:
            added.append(name)
    if not added:
        return
    if not text.endswith("\n"):
        text += "\n"
    text += "\n# Auto-generated per-TU data files (migrate_data_per_tu.py)\n"
    for name in sorted(added):
        text += name + "\n"
    USE_MODERN_AS.write_text(text)
    print(f"migrate_data_per_tu: added {len(added)} entries to "
          f"config/use_modern_as.txt")


def _scan_existing_definitions() -> set[str]:
    """Symbols already defined in any tracked src/ .c file. The per-TU
    migrator must skip these to avoid duplicate-definition link errors
    with the legacy pool files (src/cod/sdata_pool.c, src/cod/lit4_pool.c)
    and any hand-typed TU sources that already cover some symbols.

    Two def shapes are recognized:

    1. Typed def with explicit section attr:
       `__attribute__((section(".sdata.0x00632014"))) int D_00632014 = 0;`
       This is the legacy migrator-emitted shape and still covers most
       sidecar symbols.

    2. Plain def (no section attr):
       `int D_00632014 = 0;` / `const char D_0061AC60[N] = "...";`
       This shape lands in tracked TU files after Phase 3d promotion
       (typed attr stripped so ee-gcc emits %gp_rel for same-TU
       references). An `extern` declaration of the same symbol is NOT
       a def — the regex anchors on `=` after the symbol name.
    """
    out: set[str] = set()
    # Walk every source root: src/, plus the original ICO sibling
    # subsystems ios/, sound/, isys/ (relocated to repo root).
    # Also scan `.c.inc` fragments — they're inline-included by their
    # parent .c so any D_<VMA> they define is part of the parent's TU
    # and the sidecar must not duplicate it.
    src_paths: list = []
    for root_name in ("src", "ios", "sound", "isys"):
        root_dir = REPO_ROOT / root_name
        if root_dir.is_dir():
            src_paths += list(root_dir.rglob("*.c"))
            src_paths += list(root_dir.rglob("*.h"))
            src_paths += list(root_dir.rglob("*.c.inc"))
    typed_re = re.compile(
        r'__attribute__\s*\(\(section\s*\(\s*"\.\w+\.0x([0-9A-Fa-f]+)"\s*\)\s*\)\)\s*'
        r'(?:[\w\s\*]+?)\s+(D_[0-9A-Fa-f]{8})\b'
    )
    # Plain def: a line whose top-level statement defines `D_<VMA>`
    # with `=`. The symbol MUST be preceded by at least one type
    # token (e.g. `int`, `const char`, `unsigned int *`) so we don't
    # match in-function array writes like `    D_X[0] = ...;`.
    # `extern` declarations have no `=` so they don't match.
    plain_re = re.compile(
        r'(?m)^(?!\s*extern\b)[ \t]*'                      # line start, not extern
        r'(?:[A-Za-z_]\w*\s+)+'                            # one+ type tokens
        r'\**\s*'                                          # optional `*`s
        r'(D_[0-9A-Fa-f]{8})\b\s*(?:\[[^\]]*\])*\s*='      # name [N][M]... =
    )
    for c_path in src_paths:
        # Don't read our own _data sidecars — they're regenerated each
        # run, so symbols in them aren't a stable source-of-truth.
        if c_path.name.endswith("_data.c"):
            continue
        text = c_path.read_text()
        for m in typed_re.finditer(text):
            out.add(m.group(2))
        for m in plain_re.finditer(text):
            out.add(m.group(1))
    return out


def main() -> int:
    if not TU_MAP.exists():
        sys.exit(f"migrate_data_per_tu: missing {TU_MAP}; "
                 f"run tools/build_data_tu_map.py first.")
    tu_map = json.loads(TU_MAP.read_text())
    _check_basename_collisions(tu_map)
    already_defined = _scan_existing_definitions()

    # Group symbol assignments by TU, skipping anything already defined
    # in a non-_data.c source (pool files, hand-typed TU sources).
    by_tu: dict[str, list[str]] = {}
    for sym, rec in tu_map.items():
        if sym in already_defined:
            continue
        by_tu.setdefault(rec["tu"], []).append(sym)

    # Walk every data file once, extracting bytes for every block.
    all_bytes: dict[str, tuple[int, str, bytes]] = {}  # sym -> (vma, sect, bytes)
    for sect_name, asm_path in ASM_FILES.items():
        vma_lo, vma_hi = SECTION_RANGES[sect_name]
        for sym, vma, end_vma, body in _walk_blocks(asm_path, vma_lo, vma_hi):
            data = _extract_bytes(body, vma, end_vma)
            if data is not None:
                all_bytes[sym] = (vma, sect_name, data)

    # Sidecars now land at repo-root paths (e.g. ios/cdvd_data.c, not
    # src/ios/cdvd_data.c). Clean every existing sidecar across all
    # source roots so a fully-typed TU doesn't leave a stale file.
    for root_name in ("src", "ios", "sound", "isys"):
        root_dir = REPO_ROOT / root_name
        if root_dir.is_dir():
            for stale in list(root_dir.rglob("*_data.c")):
                stale.unlink()
    generated_basenames: list[str] = []
    skipped_total = 0
    migrated_total = 0
    for tu, syms in sorted(by_tu.items()):
        fname = _tu_to_filename(tu)
        out_path = REPO_ROOT / fname
        out_path.parent.mkdir(parents=True, exist_ok=True)
        lines: list[str] = [
            f'/* Auto-generated per-TU data file for "{tu}".',
            f' * Regenerate via tools/build_data_tu_map.py + '
            f'tools/migrate_data_per_tu.py.',
            f' *',
            f' * Definitions are placed in per-VMA named sections so the',
            f' * linker emits them in the correct VMA order via SORT_BY_NAME',
            f' * (see tools/postprocess_ld.py). Function .c files declare',
            f' * these as `extern` only — that preserves ee-gcc 2.9 %gp_rel',
            f' * codegen for small-data references. */',
            "",
        ]
        defs: list[str] = []
        local_migrated = 0
        local_defined: set[str] = set()
        for sym in sorted(syms, key=lambda s: int(s.split("_")[-1], 16)):
            entry = all_bytes.get(sym)
            if entry is None:
                skipped_total += 1
                continue
            vma, sect_name, data = entry
            defs.extend(_emit_chunked(sym, vma, sect_name, data))
            local_defined.add(sym)
            local_migrated += 1
        if local_migrated == 0:
            continue  # don't generate empty files (e.g. symbol-ref-only TUs)
        # Pointer-array `void *D_X[] = { &D_Y, &func_Z, ... };` defs
        # need `extern` decls for every &-referenced symbol. Even
        # locally-defined symbols need a prior `extern` if they're
        # referenced earlier in the file — ee-gcc 2.9 rejects forward
        # references to file-scope objects without a prior declaration.
        # The extern's type must match the definition's type exactly,
        # otherwise ee-gcc 2.9 errors with "conflicting types".
        ref_re = re.compile(r'&((?:D_|func_|jtbl_)[0-9A-Fa-f]{8})\b')
        def_re = re.compile(
            r'__attribute__\(\(section\("[^"]+"\)\)\)\s+'
            r'(?P<ty>(?:void\s*\*|unsigned\s+(?:char|short|int)|char|short|int|float))\s+'
            r'(?P<name>(?:D_|_pad_|jtbl_)[0-9A-Fa-f]+)\s*(?P<arr>\[\d*\])?'
        )
        local_types: dict[str, tuple[str, bool]] = {}
        for line in defs:
            m = def_re.search(line)
            if m:
                ty = re.sub(r"\s+", " ", m.group("ty").strip())
                is_array = m.group("arr") is not None
                local_types[m.group("name")] = (ty, is_array)
        externs: set[str] = set()
        for line in defs:
            for m in ref_re.finditer(line):
                externs.add(m.group(1))
        if externs:
            for name in sorted(externs):
                if name.startswith("func_"):
                    lines.append(f'extern void {name}();')
                elif name in local_types:
                    ty, is_array = local_types[name]
                    suffix = "[]" if is_array else ""
                    lines.append(f'extern {ty} {name}{suffix};')
                else:
                    lines.append(f'extern char {name}[];')
            lines.append("")
        lines.extend(defs)
        out_path.write_text("\n".join(lines) + "\n")
        # use_modern_as.txt does basename matching, so we pass the
        # stem (e.g. `Basic`, `cdvd`) regardless of subdir.
        generated_basenames.append(out_path.stem)
        migrated_total += local_migrated

    _ensure_use_modern_as(generated_basenames)
    print(f"migrate_data_per_tu: generated {len(generated_basenames)} "
          f"per-TU files, {migrated_total} symbols migrated, "
          f"{skipped_total} skipped (symbol refs / unknown shapes).")
    return 0


if __name__ == "__main__":
    sys.exit(main())
