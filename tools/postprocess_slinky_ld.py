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
    ("data_DATA_START",     "data_DATA_END",     ".data",   "data_VRAM"),
    ("rodata_RODATA_START", "rodata_RODATA_END", ".rodata", "rodata_VRAM"),
    ("lit4_LIT4_START",     "lit4_LIT4_END",     ".lit4",   "lit4_VRAM"),
    ("sdata_SDATA_START",   "sdata_SDATA_END",   ".sdata",  "sdata_VRAM"),
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
                  link_objs: list[str], boundaries: dict
                  ) -> list[tuple[int, str, str, str]]:
    """Return [(vma, slot_kind, opath, section_glob), ...] for one
    data section. `slot_kind` is "typed" or "promoted"; `section_glob`
    is the input-section pattern to use inside KEEP(...)."""
    slots: list[tuple[int, str, str, str]] = []

    # 1. Typed slots — one per `.<base>.0xVMA` named section across
    #    every contributing .o.
    for o in link_objs:
        for name, _sz in sections_of(objdump, o):
            if not name.startswith(base + ".0x") and not name.startswith(base + ".0X"):
                continue
            try:
                vma = int(name.split(".0x", 1)[-1].split(".0X", 1)[-1], 16)
            except ValueError:
                continue
            slots.append((vma, "typed", o, name))

    # 2. Promoted plain slots — one per (TU, section) flagged
    #    promotable + stripped, whose .o has plain content AND whose
    #    range is FULLY covered by tracked typed defs in the TU's
    #    source (no sidecar contribution within the range — see below).
    #
    # A promoted slot pulls `<o>(.<base>*)` placed at lo_vma. If part
    # of the range is filled by a sidecar .o (which contributes
    # typed `.<base>.0xVMA` sections at intermediate VMAs), the
    # promoted slot's content would either double-define those bytes
    # or shift the TU's other defs off-VMA. Skip such TUs — their
    # typed slots will cover the bytes correctly via the catch-all
    # (no promoted slot needed yet).
    sidecar_vmas_in_range: set[int] = set()
    for o in link_objs:
        if not o.endswith("_data.o"):
            continue
        for name, _sz in sections_of(objdump, o):
            if not (name.startswith(base + ".0x") or name.startswith(base + ".0X")):
                continue
            try:
                v = int(name.split(".0x", 1)[-1].split(".0X", 1)[-1], 16)
            except ValueError:
                continue
            sidecar_vmas_in_range.add(v)

    for tu, sections in boundaries.items():
        info = sections.get(base)
        if info is None:
            continue
        if not info.get("promotable") or not info.get("stripped"):
            continue
        opath = info.get("o_path")
        if not opath:
            continue
        secs = sections_of(objdump, opath)
        if not _has_plain_section(secs, base):
            continue
        ranges = info.get("ranges", [])
        if not ranges:
            continue
        lo_vma = int(ranges[0]["lo_vma"], 16)
        hi_vma = int(ranges[0]["hi_vma"], 16)
        # If a sidecar .o contributes a typed section inside [lo, hi),
        # the TU's plain .rodata isn't the sole owner of this range —
        # skip promotion (typed slots will own the bytes).
        if any(lo_vma <= v < hi_vma for v in sidecar_vmas_in_range):
            continue
        slots.append((lo_vma, "promoted", opath, f"{base}*"))

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
    for start_sym, end_sym, base, vram_sym in SECTIONS:
        slots = collect_slots(objdump, base, vram_sym, link_objs, boundaries)
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
