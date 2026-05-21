#!/usr/bin/env python3
"""
postprocess_slinky_ld.py — patch the slinky-generated linker script so
the resulting ELF is SHA-1-identical to the baseelf round-trip.

Today's pipeline carries every typed clean-room data def in tracked
`src/<TU>.c` wrapped in `__attribute__((section(".X.0xVMA")))`. Slinky
emits per-`.o` `(.X*)` globs in declared order, which is wrong for
typed-section placement. Phase 3d (the wrapper-retirement work) needs
**explicit-address placement** for every typed section so that:

  1. attr-tagged defs that still exist land at their named VMA, and
  2. promoted-TU plain defs land in the promoted TU's contiguous range
     at the TU's `lo_vma`.

We achieve both with one mechanism: **emit one explicit `. = ABS_VMA;
KEEP(<.o>(.<sec>.<...>));` slot per byte-contributing section** between
`<sec>_START` and `<sec>_END` in `ico.us.slinky.ld`.

Slot sources (per data section, all merged + sorted by VMA ascending):

  - **Typed slots**: every `.<sec>.0x<VMA>` named section that any `.o`
    contributes. Detected via `objdump -h` on each `.o` in the link
    list parsed out of build.ninja.
  - **Plain promoted slots**: for every (TU, section) in
    `decomp/data_tu_boundaries.json` with `promotable=true &&
    stripped=true && o_path is present && o_path's plain `.<sec>` is
    non-empty`, emit one slot at `lo_vma` pulling `<o_path>(.<sec>*)`.

Idempotent: each slot block is gated by `/* phase3d-slots <section> */`
marker. Second run sees the marker and skips.

Also strips slinky's trailing `. = ALIGN(., 16)` before `.sdata` end —
baseelf's `.sdata` ends at exactly `0x633BC6` (not 16-aligned), so the
pad pushes `.rom` 10 bytes longer.

Run as part of `tools/build.sh slinky`.
"""
from __future__ import annotations

import json
import re
import subprocess
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
LD = REPO / "config" / "ico.us.slinky.ld"
NINJA = REPO / "build.ninja"
BOUNDARIES_JSON = REPO / "decomp" / "data_tu_boundaries.json"

# (start_symbol, end_symbol, section_name, vram_symbol) per data section.
SECTIONS = [
    ("data_DATA_START",     "data_DATA_END",     ".data",   "data_VRAM",   0x00274700, 0x005536B8),
    ("rodata_RODATA_START", "rodata_RODATA_END", ".rodata", "rodata_VRAM", 0x00553700, 0x006308A8),
    ("lit4_LIT4_START",     "lit4_LIT4_END",     ".lit4",   "lit4_VRAM",   0x00630900, 0x006318D0),
    ("sdata_SDATA_START",   "sdata_SDATA_END",   ".sdata",  "sdata_VRAM",  0x00631900, 0x00633BC6),
]
MARKER_PREFIX = "/* phase3d-slots "

OBJDUMP_CANDIDATES = ("mips64r5900el-ps2-elf-objdump", "mips-linux-gnu-objdump")
_OBJDUMP_CACHE: dict[str, list[tuple[str, int]]] = {}


def find_objdump() -> str:
    for name in OBJDUMP_CANDIDATES:
        try:
            subprocess.run([name, "--version"], capture_output=True, check=True)
            return name
        except (FileNotFoundError, subprocess.CalledProcessError):
            continue
    raise SystemExit(
        "postprocess_slinky_ld: no objdump found "
        f"(tried {', '.join(OBJDUMP_CANDIDATES)})"
    )


def sections_of(objdump: str, opath: str) -> list[tuple[str, int]]:
    """[(section_name, size), ...] for a .o file. Zero-size sections
    dropped. Cached — link list has duplicates."""
    if opath in _OBJDUMP_CACHE:
        return _OBJDUMP_CACHE[opath]
    if not (REPO / opath).exists():
        _OBJDUMP_CACHE[opath] = []
        return []
    r = subprocess.run([objdump, "-h", opath], capture_output=True, text=True,
                       cwd=REPO)
    secs: list[tuple[str, int]] = []
    for m in re.finditer(
        r'^\s*\d+\s+(\S+)\s+([0-9a-fA-F]+)\s+', r.stdout, re.MULTILINE
    ):
        name, sz_hex = m.group(1), m.group(2)
        sz = int(sz_hex, 16)
        if sz > 0:
            secs.append((name, sz))
    _OBJDUMP_CACHE[opath] = secs
    return secs


def parse_link_objs() -> list[str]:
    """.o list from build.ninja's final link statement."""
    text = NINJA.read_text()
    m = re.search(
        r'^build build/ico\.elf:\s*link\s+(.+?)(?:\n\s*\||\n[a-z]|\Z)',
        text, re.MULTILINE | re.DOTALL,
    )
    if not m:
        raise SystemExit("postprocess_slinky_ld: no link line in build.ninja")
    body = m.group(1).replace("$\n", " ").replace("\\\n", " ")
    objs: list[str] = []
    seen: set[str] = set()
    for o in re.findall(r'build/\S+?\.o', body):
        if o not in seen:
            seen.add(o)
            objs.append(o)
    return objs


def _load_boundaries() -> dict:
    if BOUNDARIES_JSON.exists():
        return json.loads(BOUNDARIES_JSON.read_text())
    return {}


_JTBL_REF_RE = re.compile(r'%hi\((jtbl_([0-9A-Fa-f]{8}))\)')
_C_FUNC_DEF_RE = re.compile(
    r'\b(func_[0-9A-Fa-f]{8})\s*\([^;{]*?\)\s*\{',
)
_INCLUDE_ASM_FUNC_RE = re.compile(
    r'\bINCLUDE_ASM\s*\([^)]*\b(func_[0-9A-Fa-f]{8})\b',
)


def _jtbl_opath_map(objdump: str, link_objs: list[str]) -> dict[int, str]:
    """Return {jtbl_VMA: function_owner_opath} for every jtbl whose
    owning function is C-matched (has a body in tracked source, not
    INCLUDE_ASM'd). The owning function's `.o(.rodata*)` contains
    gcc's emitted jtbl bytes; the asm-blanket entry was stripped by
    rewrite_data_named_sections.py, so this slot must take over."""
    # Map func name → opath. We rely on the conventional naming
    # `build/<src_path>.o` for `src/<src_path>.c` sources; cross-check
    # by reading each .c and matching func-def to opath.
    matched: dict[str, str] = {}  # func_name → opath
    via_include_asm: set[str] = set()
    src_roots = ("src", "ios", "sound", "isys")
    for root_name in src_roots:
        root_dir = REPO / root_name
        if not root_dir.is_dir():
            continue
        for p in root_dir.rglob("*"):
            if p.suffix not in (".c", ".inc"):
                continue
            try:
                text = p.read_text(errors="replace")
            except Exception:
                continue
            for m in _INCLUDE_ASM_FUNC_RE.finditer(text):
                via_include_asm.add(m.group(1))
            if p.suffix == ".c":
                # build/<rel_no_ext>.o
                rel = p.relative_to(REPO)
                opath = f"build/{rel.with_suffix('.o')}"
                for m in _C_FUNC_DEF_RE.finditer(text):
                    func = m.group(1)
                    if func not in matched:
                        matched[func] = opath
            # .c.inc fragments contribute defs but no .o of their
            # own; functions defined in includes belong to the
            # parent .c's .o (handled by parent's pass).
    # INCLUDE_ASM wins on conflict.
    for f in via_include_asm:
        matched.pop(f, None)
    # Now find jtbls referenced by matched functions via the
    # splat-emitted matchings .s.
    matchings_root = REPO / "asm" / "matchings"
    out: dict[int, str] = {}
    if not matchings_root.is_dir():
        return out
    for s_file in matchings_root.rglob("func_*.s"):
        func = s_file.stem
        opath = matched.get(func)
        if opath is None:
            continue
        try:
            text = s_file.read_text()
        except Exception:
            continue
        for m in _JTBL_REF_RE.finditer(text):
            vma = int(m.group(2), 16)
            if vma not in out:
                out[vma] = opath
    return out


def _has_plain_section(secs: list[tuple[str, int]], base: str) -> bool:
    """True if the .o has at least one plain-form section for `base` —
    a section named exactly `<base>` or `<base>.<non-hex-suffix>`
    (e.g. `.rodata.str1.4`, NOT `.rodata.0x00553700`). Phase 3d
    promoted slots only emit when the .o actually has plain content."""
    for name, _sz in secs:
        if name == base:
            return True
        if name.startswith(base + "."):
            rest = name[len(base) + 1:]
            # Hex-suffix style is the attr-tag form; anything else is
            # an ee-gcc sub-section (.str1.4 etc.) we treat as plain.
            if not (rest.startswith("0x") or rest.startswith("0X")):
                return True
    return False


def collect_slots(objdump: str, base: str, vram_sym: str,
                  vma_lo: int, vma_hi: int,
                  link_objs: list[str], boundaries: dict
                  ) -> list[tuple[int, str, str, str]]:
    """Return [(vma, slot_kind, opath, section_glob), ...] for one
    data section. `slot_kind` is "typed", "promoted", or "jtbl";
    `section_glob` is the input-section pattern to use inside
    KEEP(...). Sections whose name-encoded VMA falls outside the
    output section's [vma_lo, vma_hi) are skipped — ee-gcc may
    place a symbol's bytes in the wrong default section under -G 8
    (e.g. `const float[2]` in `.rodata` range → `.sdata.D_X` per
    -fdata-sections), but the slot must only emit in the output
    block whose VMA range matches."""
    slots: list[tuple[int, str, str, str]] = []

    # 1. Typed slots — one per per-symbol section. Two forms:
    #    `.<base>.0x<VMA>` (attr-tag form) AND `.<base>.D_<VMA>`
    #    (ee-gcc -fdata-sections per-symbol emission).
    for o in link_objs:
        for name, _sz in sections_of(objdump, o):
            if not name.startswith(base + "."):
                continue
            suffix = name[len(base) + 1:]
            if suffix.startswith("0x") or suffix.startswith("0X"):
                try:
                    vma = int(suffix, 16)
                except ValueError:
                    continue
            elif suffix.startswith("D_") or suffix.startswith("d_"):
                try:
                    vma = int(suffix[2:], 16)
                except ValueError:
                    continue
            else:
                continue
            if not (vma_lo <= vma < vma_hi):
                continue
            slots.append((vma, "typed", o, name))

    # 2. Promoted plain slots — one per (TU, section) flagged
    #    promotable + stripped, whose .o has plain content AND whose
    #    [lo_vma, hi_vma) is exclusively owned by the TU's own .o
    #    (no other .o contributes a typed section inside the range).
    #
    # A promoted slot pulls `<o>(.<base>*)` placed at lo_vma. If
    # another .o contributes a typed `.<base>.0x<V>` section with
    # lo_vma <= V < hi_vma — be it a `_data.c` sidecar, an asm-side
    # blanket (`453700.rodata.o`) carrying a jtbl/non-typed dlabel,
    # or anything else — that section's bytes must land at V, which
    # conflicts with the promoted slot's contiguous fill. Skip such
    # TUs; their typed slots and external slots will own the bytes
    # via the catch-all.
    foreign_vmas_per_o: dict[str, set[int]] = {}
    for o in link_objs:
        vmas: set[int] = set()
        for name, _sz in sections_of(objdump, o):
            if not name.startswith(base + "."):
                continue
            suffix = name[len(base) + 1:]
            v: int | None = None
            if suffix.startswith("0x") or suffix.startswith("0X"):
                try:
                    v = int(suffix, 16)
                except ValueError:
                    v = None
            elif suffix.startswith("D_") or suffix.startswith("d_"):
                try:
                    v = int(suffix[2:], 16)
                except ValueError:
                    v = None
            if v is not None:
                vmas.add(v)
        foreign_vmas_per_o[o] = vmas

    # Per-TU promoted `(.<base>*)` slots are obviated by per-symbol
    # typed slots (`-fdata-sections` emits one `.<base>.D_<VMA>` per
    # plain def). The promoted glob would double-claim the same
    # bytes as the per-symbol slots and trigger a duplicate-VMA
    # assertion. Leave the loop placeholder so future re-enable is
    # a one-line revert.
    _ = boundaries  # noqa: silence unused-arg lint
    _ = foreign_vmas_per_o

    # 3. jtbl slots — for each C-matched function with a jtbl, the
    #    function's `.o` `.rodata` contains gcc's emitted jtbl bytes.
    #    The asm-blanket `.rodata.0x<jtbl_VMA>` block was stripped by
    #    rewrite_data_named_sections.py (see _load_matched_function_
    #    jtbls there), leaving a gap at the jtbl's VMA. Emit a slot
    #    pulling the function's `.o(.<base>*)` so gcc's bytes land at
    #    the original VMA.
    if base == ".rodata":
        for jtbl_vma, jtbl_opath in _jtbl_opath_map(objdump, link_objs).items():
            # Only emit if the .o actually has plain `.rodata` content
            # (the function was actually compiled, not just declared).
            secs = sections_of(objdump, jtbl_opath)
            if not _has_plain_section(secs, base):
                continue
            slots.append((jtbl_vma, "jtbl", jtbl_opath, f"{base}*"))

    slots.sort(key=lambda s: (s[0], s[1]))

    # Sanity: assert no duplicate VMAs and strictly ascending.
    seen_vmas: set[int] = set()
    for vma, kind, opath, _glob in slots:
        if vma in seen_vmas:
            raise SystemExit(
                f"postprocess_slinky_ld: duplicate slot at "
                f"{base} 0x{vma:08X} ({kind}, {opath})"
            )
        seen_vmas.add(vma)

    return slots


def render_slot_block(base: str, vram_sym: str,
                      slots: list[tuple[int, str, str, str]], indent: str
                      ) -> str:
    """Render the slot block to inject inside the section body.

    The slots are pulled in VMA order via plain KEEP() lines — no
    explicit `. = ABS - VRAM` cursor assignments. Inside an output
    section ld interprets `.` as the absolute output address, and
    `. = X` where X < current `.` would silently move backwards; the
    first slot in each section starts at the section's natural base
    VMA, and subsequent slots are gap-free by construction (the
    original ELF's data sections are contiguous, see NOTES.md §
    "Migrating data sections from asm to src"), so natural location-
    counter advancement after each KEEP equals the next slot's VMA.

    The leading VMA comment doubles as an audit trail — a reader can
    confirm `.` matches the comment's VMA at every slot."""
    out = [f"{indent}{MARKER_PREFIX}{base} */"]
    for vma, kind, opath, glob in slots:
        out.append(
            f"{indent}KEEP({opath}({glob}));  "
            f"/* {kind} 0x{vma:08X} */"
        )
    return "\n".join(out) + "\n"


def restructure_section_body(text: str, base: str, start_sym: str,
                             end_sym: str, vram_sym: str,
                             slots: list[tuple[int, str, str, str]]
                             ) -> tuple[str, bool]:
    """Locate the section body between `start_sym = .;` and `end_sym =
    .;`, replace its prior slinky-emitted contents with our slot block.
    Returns (new_text, changed)."""
    marker = f"{MARKER_PREFIX}{base} */"
    if marker in text:
        return text, False
    body_re = re.compile(
        rf"(?P<head>\s*{re.escape(start_sym)}\s*=\s*\.\s*;\s*\n)"
        rf"(?P<body>.*?)"
        rf"(?P<tail>\s*{re.escape(end_sym)}\s*=\s*\.\s*;)",
        re.DOTALL,
    )
    m = body_re.search(text)
    if m is None:
        raise SystemExit(
            f"postprocess_slinky_ld: anchors {start_sym!r}/{end_sym!r} "
            f"not found in {LD.name} (slinky output format changed?)"
        )
    indent = re.match(r"\n?(\s*)", m.group("head").lstrip("\n")).group(1)
    slot_block = render_slot_block(base, vram_sym, slots, indent)
    new = text[:m.start("body")] + slot_block + text[m.end("body"):]
    return new, True


# Trailing ALIGN(., 16) before sdata_SDATA_END = .;
SDATA_END_ALIGN_RE = re.compile(
    r"\n\s*\.\s*=\s*ALIGN\(\.,\s*16\);\s*\n(\s*sdata_SDATA_END\s*=\s*\.\s*;)",
)


def kill_sdata_end_align(text: str) -> tuple[str, int]:
    return SDATA_END_ALIGN_RE.subn(r"\n\1", text, count=1)


def main() -> int:
    if not LD.exists():
        print(f"postprocess_slinky_ld: {LD} not found "
              "(run `tools/build.sh slinky` first)")
        return 0
    objdump = find_objdump()
    link_objs = parse_link_objs()
    boundaries = _load_boundaries()
    original = LD.read_text()
    text = original

    summary: list[str] = []
    for start_sym, end_sym, base, vram_sym, vma_lo, vma_hi in SECTIONS:
        slots = collect_slots(objdump, base, vram_sym, vma_lo, vma_hi,
                              link_objs, boundaries)
        text, changed = restructure_section_body(
            text, base, start_sym, end_sym, vram_sym, slots
        )
        if changed:
            typed_n = sum(1 for s in slots if s[1] == "typed")
            prom_n = sum(1 for s in slots if s[1] == "promoted")
            summary.append(
                f"{base}: {len(slots)} slots ({typed_n} typed, "
                f"{prom_n} promoted)"
            )

    text, killed = kill_sdata_end_align(text)
    if killed:
        summary.append("stripped sdata trailing ALIGN")

    if text != original:
        LD.write_text(text)
        print(f"postprocess_slinky_ld: {LD.name} — " + "; ".join(summary))
    else:
        print(f"postprocess_slinky_ld: {LD.name} already patched")
    return 0


if __name__ == "__main__":
    sys.exit(main())
