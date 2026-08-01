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


def main() -> int:
    patch_aug6_layout()
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
