#!/usr/bin/env python3
"""
patch_splat.py — apply local fixes to the pip-installed splat64 package.

Idempotent: skips files that already contain the patch marker.
Re-run via `tools/build.sh setup` after every pip install / venv
rebuild — the patch only sticks until the package is reinstalled.

RETIRED (2026-08-01): the r5900 `$ACC`/`$Q`/`$R` dollar-prefix rewrite.
Splat's bare `ACC`/`Q`/`R` spelling IS the period assembler's dialect
(ee-as 2.9-991111 rejects `$ACC`); the `$` form was only ever needed for
the modern-gas fallback, which compile_c.sh now bridges by canonicalizing
the C-side inline-asm sigils to bare instead. main() UNAPPLIES the old
patch from an already-patched install so no venv keeps the stale rewrite.
"""
from __future__ import annotations

import os
import re
import sys
from pathlib import Path

def find_splat_c_py() -> Path | None:
    """Find the installed splat's c.py."""
    try:
        import splat
    except ImportError:
        return None
    splat_dir = Path(splat.__file__).parent
    candidate = splat_dir / "segtypes" / "common" / "c.py"
    return candidate if candidate.exists() else None


# RETIRED sigil rewrite — kept verbatim ONLY so main() can strip it from a
# venv where a previous run already inserted it (the patch text is exactly
# what was appended after its anchor line, so a literal replace removes it).
RETIRED_SIGIL_PATCH = """
        # ICO_PATCH: r5900 $ACC/$Q dollar-prefix fix
        # Splat's per-func emit path leaves `ACC` / `Q` bare; mips-as
        # / ee-as require `$ACC` / `$Q`. Post-process the .s file to
        # add the prefix in operand positions.
        if options.opts.platform == "ps2":
            import re as _ico_re
            _ico_text = outpath.read_text()
            _ico_text = _ico_re.sub(r'([\\t ,])(ACC|Q|R)\\b', r'\\1$\\2', _ico_text)
            outpath.write_text(_ico_text)
"""

# Second patch: make get_global_asm_funcs follow #include "X.c.inc"
# directives so INCLUDE_ASM declarations inside .c.inc fragments
# are visible to splat. Without this, funcs declared INCLUDE_ASM
# inside a `.c.inc` end up in `asm/matchings/` instead of
# `asm/nonmatchings/` and the macro path fails at link time.
INC_MARKER = "# ICO_PATCH: scan .c.inc includes"
INC_ANCHOR = '        text = CommonSegC.strip_c_comments(c_file.read_text(encoding="utf-8"))'
INC_PATCH = """
        # ICO_PATCH: scan .c.inc includes
        # Expand any `#include "X.c.inc"` (and `.h` for completeness)
        # so INCLUDE_ASM directives inside those fragments are visible.
        import re as _ico_inc_re
        _ico_seen = set()
        def _ico_expand(c_path, depth=0):
            if depth > 4: return ""
            try:
                t = c_path.read_text(encoding="utf-8", errors="replace")
            except Exception:
                return ""
            out_parts = [t]
            for _m in _ico_inc_re.finditer(r'^\\s*#\\s*include\\s+"([^"]+\\.c\\.inc)"', t, _ico_inc_re.MULTILINE):
                _inc_name = _m.group(1)
                _inc_path = c_path.parent / _inc_name
                if not _inc_path.exists() or str(_inc_path) in _ico_seen:
                    continue
                _ico_seen.add(str(_inc_path))
                out_parts.append(_ico_expand(_inc_path, depth+1))
            return "\\n".join(out_parts)
        text = CommonSegC.strip_c_comments(_ico_expand(c_file))
"""


# --- aug6 byte-perfect round-trip patches (linker_entry.py + data.py) ---
# Reproduce the original SCE linker's exact layout for the aug6 prototype target
# with NO output postprocessing. All gated on the cod segment's align >= 0x40
# (aug6 sets `align: 0x80`; retail uses splat's default 16), so the retail build
# is provably unaffected.
LE_MARKER = "# ICO_PATCH: aug6 layout"
LE_OLD_1 = '''    def _end_section(self, seg_name: str, cur_section: str, segment: Segment) -> None:
        section_start = get_segment_section_start(seg_name, cur_section)
        section_end = get_segment_section_end(seg_name, cur_section)
        section_size = get_segment_section_size(seg_name, cur_section)
        if options.opts.ld_align_section_vram_end and segment.align is not None:
            self._writeln(f". = ALIGN(., {segment.align});")'''
LE_NEW_1 = '''    def _end_section(self, seg_name: str, cur_section: str, segment: Segment, emit_align: bool = True) -> None:  # ICO_PATCH: aug6 layout
        section_start = get_segment_section_start(seg_name, cur_section)
        section_end = get_segment_section_end(seg_name, cur_section)
        section_size = get_segment_section_size(seg_name, cur_section)
        if emit_align and options.opts.ld_align_section_vram_end and segment.align is not None:
            self._writeln(f". = ALIGN(., {segment.align});")'''
LE_OLD_2 = '''        if not is_first:
            self._end_block()

        self._begin_segment(segment, seg_name, noload=noload, is_first=is_first)

        for section_name, entries in section_entries.items():
            if len(entries) == 0:
                continue

            first_entry = entries[0]
            if first_entry.noload != noload:
                continue

            self._begin_section(seg_name, section_name)
            for entry in entries:
                entry.emit_entry(self)
            self._end_section(seg_name, section_name, segment)'''
LE_NEW_2 = '''        # ICO_PATCH: aug6 layout (cod align>=0x40). End the loadable segment at
        # its last section's content (no trailing rom pad), and align the NOLOAD
        # bss segment EXTERNALLY so it aligns without rom-padding.
        _ico_aug6 = (segment.align is not None and segment.align >= 0x40
                     and options.opts.ld_align_section_vram_end)
        if not is_first:
            self._end_block()
            if _ico_aug6 and noload:
                self._writeln(f". = ALIGN(., {segment.align});")

        self._begin_segment(segment, seg_name, noload=noload, is_first=is_first)

        _ico_last = None
        for _sn, _en in section_entries.items():
            if len(_en) > 0 and _en[0].noload == noload:
                _ico_last = _sn

        for section_name, entries in section_entries.items():
            if len(entries) == 0:
                continue

            first_entry = entries[0]
            if first_entry.noload != noload:
                continue

            self._begin_section(seg_name, section_name)
            for entry in entries:
                entry.emit_entry(self)
            self._end_section(seg_name, section_name, segment,
                              emit_align=not (_ico_aug6 and section_name == _ico_last))'''

DP_MARKER = "# ICO_PATCH: trailing sub-word"
DP_OLD = '''        self.split_as_asm_file(self.asm_out_path())

    def should_self_split(self) -> bool:'''
DP_NEW = '''        self.split_as_asm_file(self.asm_out_path())

        # ICO_PATCH: trailing sub-word data bytes spimdisasm's word-array model
        # drops (a non-word-aligned data section at the rom end, e.g. the final
        # .sdata string). Gated to the aug6 cod segment (align>=0x40) so retail
        # is untouched. Reads the authoritative rom bytes.
        _ico_p = self.get_most_parent()
        if getattr(_ico_p, "align", None) and _ico_p.align >= 0x40:
            _ico_tail = (self.rom_end - self.rom_start) % 4
            if _ico_tail:
                _ico_bytes = rom_bytes[self.rom_end - _ico_tail : self.rom_end]
                with open(self.asm_out_path(), "a") as _ico_f:
                    _ico_f.write("\\n/* ICO_PATCH: trailing sub-word bytes spimdisasm drops */\\n")
                    for _ico_b in _ico_bytes:
                        _ico_f.write(f".byte 0x{_ico_b:02X}\\n")

    def should_self_split(self) -> bool:'''


def _splat_file(rel: str) -> Path | None:
    try:
        import splat
    except ImportError:
        return None
    cand = Path(splat.__file__).parent / rel
    return cand if cand.exists() else None


# --- one-assembler patches (2026-09-15) ---
# The period assembler ee-as 2.9-991111 now builds EVERY object, blobs
# included, so splat must stop emitting the modern-gas dialect:
#
#   * the header line. splat hard-codes `.include "macro.inc"` at the top of
#     each standalone blob `.s` (codesubsegment's whole-file header, plus the
#     three *bin emitters). macro.inc was the modern-gas spelling of the label
#     macros and is deleted; the period-assembler twin is include/labels.inc.
#     A blob is one whole section that the link script globs as one input
#     section, so it also sets labels.inc's `__blob = 1`, which turns off the
#     per-symbol `.rodata.<sym>` switch dlabel does for C-TU stub rodata.
#   * `.incbin`. ee-as 2.9-991111 has no such pseudo-op (it is a later binutils
#     addition), so the textbin emitter writes the bytes it just extracted as
#     `.word` directives. Same bytes, no external file read at assembly time,
#     and no cwd-relative path to resolve.
BLOB_MARKER = "# ICO_PATCH: one assembler"
BLOB_OLD_HEADER = "        ret.append('.include \"macro.inc\"')\n"
BLOB_NEW_HEADER = (
    "        ret.append('.include \"labels.inc\"')  # ICO_PATCH: one assembler\n"
    "        ret.append('__blob = 1')\n"
)
BLOB_OLD_WRITE = "f.write('.include \"macro.inc\"\\n\\n')\n"
BLOB_NEW_WRITE = (
    "f.write('.include \"labels.inc\"\\n__blob = 1\\n\\n')  # ICO_PATCH: one assembler\n"
)
INCBIN_OLD = "        f.write(f'.incbin \"{binpath.as_posix()}\"\\n')\n"
INCBIN_NEW = (
    "        # ICO_PATCH: one assembler — ee-as 2.9-991111 has no .incbin, so the\n"
    "        # extracted bytes go out as .word (little-endian) directives instead.\n"
    "        _ico_blob = binpath.read_bytes()\n"
    "        _ico_tail = len(_ico_blob) % 4\n"
    "        for _ico_i in range(0, len(_ico_blob) - _ico_tail, 4):\n"
    "            _ico_w = int.from_bytes(_ico_blob[_ico_i:_ico_i + 4], 'little')\n"
    "            f.write(f'.word 0x{_ico_w:08X}\\n')\n"
    "        for _ico_b in _ico_blob[len(_ico_blob) - _ico_tail:]:\n"
    "            f.write(f'.byte 0x{_ico_b:02X}\\n')\n"
)


def patch_one_assembler() -> None:
    """Blob `.s` files speak the period assembler's dialect (labels.inc, no .incbin)."""
    for rel in ("segtypes/common/codesubsegment.py",
                "segtypes/common/textbin.py",
                "segtypes/common/databin.py",
                "segtypes/common/rodatabin.py"):
        f = _splat_file(rel)
        if f is None:
            continue
        t = f.read_text()
        if BLOB_MARKER in t:
            print(f"patch_splat: {f} one-assembler already patched.")
            continue
        n = t
        if BLOB_OLD_HEADER in n:
            n = n.replace(BLOB_OLD_HEADER, BLOB_NEW_HEADER, 1)
        if BLOB_OLD_WRITE in n:
            n = n.replace(BLOB_OLD_WRITE, BLOB_NEW_WRITE)
        if INCBIN_OLD in n:
            n = n.replace(INCBIN_OLD, INCBIN_NEW, 1)
        if n == t:
            print(f"patch_splat: one-assembler anchors not found in {f}; skipping.",
                  file=sys.stderr)
            continue
        f.write_text(n)
        print(f"patch_splat: one-assembler dialect applied to {f}")


# spimdisasm's `.float` line for a SUBNORMAL word. `%.10g` of the smallest
# subnormal (0x00000001) prints as `1.401298464e-45`, and the period
# assembler's float parser underflows that decimal to zero where modern gas
# rounds it back up — six ROM words came out zero the first time the data blobs
# were assembled with ee-as 2.9-991111. Every other subnormal in the split
# happens to round-trip, but what decides it is the printed decimal rather than
# the value, so the whole subnormal (and non-finite) class emits as a raw
# `.word`: same bytes, no float parser in the loop. Normal floats keep
# `.float`, which every C TU already assembles under this assembler.
FLOAT_MARKER = "# ICO_PATCH: subnormal float"
FLOAT_OLD = (
    '        dotType = ".float"\n'
    "        floatValue = common.Utils.wordToFloat(w)\n"
    '        value = f"{floatValue:.10g}"\n'
)
FLOAT_NEW = FLOAT_OLD + (
    "        # ICO_PATCH: subnormal float — the period assembler underflows the\n"
    "        # printed decimal of a subnormal; emit the raw word instead.\n"
    "        _ico_exp = w & 0x7F800000\n"
    "        if (_ico_exp == 0 and (w & 0x007FFFFF) != 0) or _ico_exp == 0x7F800000:\n"
    '            dotType = ".word"\n'
    '            value = f"0x{w:08X}"\n'
)


def patch_subnormal_float() -> None:
    """spimdisasm emits a subnormal / non-finite float word as a raw `.word`."""
    try:
        import spimdisasm
    except ImportError:
        print("patch_splat: spimdisasm not importable; skipping float patch.")
        return
    f = Path(spimdisasm.__file__).parent / "mips" / "symbols" / "MipsSymbolBase.py"
    if not f.exists():
        print(f"patch_splat: {f} missing; skipping float patch.", file=sys.stderr)
        return
    t = f.read_text()
    if FLOAT_MARKER in t:
        print(f"patch_splat: {f} subnormal-float already patched.")
        return
    if FLOAT_OLD not in t:
        print(f"patch_splat: subnormal-float anchor not found in {f}; skipping.",
              file=sys.stderr)
        return
    f.write_text(t.replace(FLOAT_OLD, FLOAT_NEW, 1))
    print(f"patch_splat: subnormal-float raw word applied to {f}")


def patch_aug6_layout() -> None:
    """aug6 byte-perfect linker layout + sub-word data tail (gated align>=0x40)."""
    le = _splat_file("segtypes/linker_entry.py")
    if le is not None:
        t = le.read_text()
        if LE_MARKER in t:
            print(f"patch_splat: {le} aug6 layout already patched.")
        elif LE_OLD_1 in t and LE_OLD_2 in t:
            le.write_text(t.replace(LE_OLD_1, LE_NEW_1, 1).replace(LE_OLD_2, LE_NEW_2, 1))
            print(f"patch_splat: aug6 linker layout applied to {le}")
        else:
            print(f"patch_splat: aug6 linker_entry anchors not found in {le}; skipping.", file=sys.stderr)
    dp = _splat_file("segtypes/common/data.py")
    if dp is not None:
        t = dp.read_text()
        if DP_MARKER in t:
            print(f"patch_splat: {dp} aug6 data tail already patched.")
        elif DP_OLD in t:
            dp.write_text(t.replace(DP_OLD, DP_NEW, 1))
            print(f"patch_splat: aug6 data sub-word tail applied to {dp}")
        else:
            print(f"patch_splat: aug6 data.py anchor not found in {dp}; skipping.", file=sys.stderr)


# --- carved `.lit4` pool word -> `li.s` in the still-asm owner (2026-09-15) ---
# A carved pool's words are LITERALS, and a literal belongs to the function that
# owns it. Where that function is C, the C carries it: gcc emits `li.s` and ee-as
# interns the word. Where it is still an INCLUDE_ASM stub, splat renders the load
# the same way, because the period assembler cannot be handed the pool word any
# other way: `nopic_need_relax()` (tc-mips.c:11141) asserts that no symbol it is
# asked about lives in `.lit4`, so a named `D_<VMA>` defined there and referenced
# from the same file aborts ee-as outright. `li.s $fN,<value>` sidesteps the
# symbol entirely: ee-as interns the word itself and appends it to the object's
# anonymous `.lit4` in FILE order, which is the stub's own shipped slot.
#
# This replaces the ASM_LIT4_SLOT macro (deleted 2026-09-15), which put the same
# value on a `.lit4_slot` line in the C and had tools/preprocess_old_as.py
# rewrite the load. Same bytes; the literal now lives in the function that owns
# it instead of on a macro line beside it.
#
# Scope: exactly the words a `[.., .lit4, <tu>]` row assigns to this TU, read
# from the ROM bytes at that address. `l.s` / `lwc1` are the only loads of a pool
# word; anything else reaching one is a hard error, as is a zero, subnormal or
# non-finite word, which `li.s` has no spelling for (ee-as rejects a hex
# operand, and its float parser underflows a subnormal's printed decimal; the
# raw-`.word` escape the blob path uses is not available inside an instruction).
# The PAL ROM has none: 0 of the 1065 words in the 111 carved pools.
LIT4_MARKER = "# ICO_PATCH: carved .lit4 literal"
LIT4_ANCHOR = '        self.log(f"Disassembled {func_sym.filename} to {outpath}")'
LIT4_PATCH = r"""        # ICO_PATCH: carved .lit4 literal. A pool word whose owning function is
        # still INCLUDE_ASM carries its literal IN THE STUB, spelled the way the
        # developers' compiler emitted it and their assembler interned it.
        _ico_l4 = self.siblings.get(".lit4")
        if _ico_l4 is not None and _ico_l4.vram_start is not None:
            import re as _ico_l4_re
            import struct as _ico_l4_st

            _ico_l4_rom = getattr(CommonSegC, "_ico_l4_rom_bytes", None)
            if _ico_l4_rom is None:
                _ico_l4_rom = options.opts.target_path.read_bytes()
                CommonSegC._ico_l4_rom_bytes = _ico_l4_rom

            def _ico_l4_owned(_sym):
                if not _sym.startswith("D_"):
                    return None
                try:
                    _a = int(_sym[2:], 16)
                except ValueError:
                    return None
                if _ico_l4.vram_start <= _a < _ico_l4.vram_end:
                    return _a
                return None

            def _ico_l4_text(_w):
                # The shortest decimal that round-trips through binary32, in the
                # exponent dialect ee-gcc 2.9 itself emits (no `+`, no zero pad).
                _f = _ico_l4_st.unpack("<f", _ico_l4_st.pack("<I", _w))[0]
                _s = "%.9g" % _f
                for _p in range(1, 10):
                    _c = "%.*g" % (_p, _f)
                    if _ico_l4_st.pack("<f", float(_c)) == _ico_l4_st.pack("<I", _w):
                        _s = _c
                        break
                if "e" in _s:
                    _m, _e = _s.split("e")
                    if "." not in _m:
                        _m += ".0"
                    _s = _m + "e" + str(int(_e))
                elif "." not in _s:
                    _s += ".0"
                return _s

            def _ico_l4_sub(_m):
                _a = _ico_l4_owned(_m.group("sym"))
                if _a is None:
                    return _m.group(0)
                _off = _ico_l4.rom_start + (_a - _ico_l4.vram_start)
                _w = _ico_l4_st.unpack_from("<I", _ico_l4_rom, _off)[0]
                _exp = _w & 0x7F800000
                if _w == 0 or (_exp == 0 and (_w & 0x007FFFFF) != 0) or _exp == 0x7F800000:
                    log.error(
                        f"{outpath}: carved .lit4 word {_m.group('sym')} is "
                        f"0x{_w:08X} (zero, subnormal or non-finite) and `li.s` "
                        "has no spelling for it, so a still-asm owner cannot "
                        "carry it. Land the owner in C, or leave the word in the "
                        "blob and shrink the carve."
                    )
                return "li.s%s%s, %s" % (_m.group("gap"), _m.group("reg"), _ico_l4_text(_w))

            _ico_l4_txt = outpath.read_text(encoding="utf-8")
            _ico_l4_new = _ico_l4_re.sub(
                r"\b(?:lwc1|l\.s)(?P<gap>\s+)(?P<reg>\$\w+),\s*"
                r"%gp_rel\((?P<sym>\w+)\)\(\$\d+\)",
                _ico_l4_sub,
                _ico_l4_txt,
            )
            for _ico_l4_m in _ico_l4_re.finditer(r"%gp_rel\((\w+)\)", _ico_l4_new):
                if _ico_l4_owned(_ico_l4_m.group(1)) is not None:
                    log.error(
                        f"{outpath}: {_ico_l4_m.group(1)} is a word of this TU's "
                        "carved .lit4 pool but is reached by something other than "
                        "an `l.s`/`lwc1` load. Only a float load can carry a pool "
                        "word; check the .lit4 row's range in the splat yaml."
                    )
            if _ico_l4_new != _ico_l4_txt:
                outpath.write_text(_ico_l4_new, encoding="utf-8", newline="\n")

"""


def patch_lit4_literals() -> None:
    """A still-asm owner of a carved `.lit4` word loads it as `li.s <value>`."""
    c_py = find_splat_c_py()
    if c_py is None:
        return
    t = c_py.read_text()
    if LIT4_MARKER in t:
        print(f"patch_splat: {c_py} carved-.lit4 literal already patched.")
        return
    if LIT4_ANCHOR not in t:
        print(f"patch_splat: carved-.lit4 anchor not found in {c_py}; skipping.",
              file=sys.stderr)
        return
    c_py.write_text(t.replace(LIT4_ANCHOR, LIT4_PATCH + LIT4_ANCHOR, 1))
    print(f"patch_splat: carved-.lit4 literal applied to {c_py}")


def main() -> int:
    patch_aug6_layout()
    patch_one_assembler()
    patch_subnormal_float()
    patch_lit4_literals()
    c_py = find_splat_c_py()
    if c_py is None:
        print("patch_splat: splat not importable; nothing to patch.")
        return 0

    text = c_py.read_text()
    changed = False

    # UNAPPLY the retired $ACC/$Q/$R sigil rewrite if a previous run of this
    # script installed it (splat's bare spelling is the period assembler's
    # correct dialect — see module docstring).
    if RETIRED_SIGIL_PATCH.rstrip() in text:
        text = text.replace(RETIRED_SIGIL_PATCH.rstrip(), "", 1)
        changed = True
        print(f"patch_splat: retired ACC/Q sigil rewrite REMOVED from {c_py}")

    if INC_MARKER not in text:
        if INC_ANCHOR not in text:
            print(
                f"patch_splat: .c.inc anchor not found in {c_py}; splat may "
                "have changed upstream. Skipping .c.inc-scan patch.",
                file=sys.stderr,
            )
        else:
            # Replace ALL occurrences — the anchor pattern appears in
            # both get_funcs_defined_in_c and get_global_asm_funcs (and
            # get_global_asm_rodata_syms). All three need .c.inc visibility.
            n_subs = text.count(INC_ANCHOR)
            text = text.replace(INC_ANCHOR, INC_PATCH.rstrip())
            changed = True
            print(f"patch_splat: .c.inc-scan applied to {c_py} ({n_subs} sites)")

    # Upgrade an already-applied .c.inc patch to the EUC-JP-tolerant read.
    # Carved TU sources carry raw EUC-JP string bytes (repo convention); a
    # strict utf-8 read raises inside _ico_expand's try/except, silently
    # yielding an EMPTY INCLUDE_ASM set — every function of that TU is then
    # misclassified into asm/matchings/ and a clean re-split loses its stubs.
    # The macro names splat parses are pure ASCII, so lossy decode is safe.
    _strict = 't = c_path.read_text(encoding="utf-8")'
    _tolerant = 't = c_path.read_text(encoding="utf-8", errors="replace")'
    if _strict in text:
        text = text.replace(_strict, _tolerant)
        changed = True
        print(f"patch_splat: EUC-JP-tolerant c-scan read applied to {c_py}")

    if changed:
        c_py.write_text(text)
    else:
        print(f"patch_splat: {c_py} already patched.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
