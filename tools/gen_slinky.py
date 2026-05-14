#!/usr/bin/env python3
"""
gen_slinky.py — emit config/ico.us.slinky.yaml from the current build
state.

slinky (decompals/slinky) is a YAML-driven linker-script generator
used by parappa2 (same ee-gcc 2.9-991111-01) and several other PS2
decomps. It emits one input-section line per .o per output section in
declared file order — no SORT_BY_NAME, no cross-file name-sorting.

This script produces `config/ico.us.slinky.yaml`. Run `slinky-cli` on
it to emit `config/ico.us.slinky.ld`. The output is per-section
segments (one slinky segment per ICO ELF section), with each segment's
`files:` list sorted by the .o's minimum contributing VMA in that
section.

## Current status — NOT YET WIRED INTO NINJA

The slinky.yaml is a parallel artifact. ninja still builds with the
postprocess_ld.py-patched `config/ico.us.ld`. Reason: the current
data layout uses `.X.0xVMA` typed sections that scatter across the
VMA range *within* a single .o (e.g. clothAnimation.o has .sdata
sections at 0x631940, 0x632010, 0x632D58, 0x6332A8…). slinky's
per-file emission packs all of one .o's `.X*` sections contiguously,
breaking the cross-VMA-stream layout that SORT_BY_NAME currently
preserves. Producing a SHA-1-identical ELF from slinky requires
Phase 3c/3d: promote each TU's contiguous sub-ranges and drop the
`.X.0xVMA` wrapper so the resulting .o has plain `.X` sections in
one contiguous run.

For TUs whose entire .X content IS a single contiguous range (236 of
309 TU-sections per `decomp/data_tu_boundaries.json`), the slinky
yaml already places them at the correct VMA. The DmaPacket REVISIT
note in `src/DmaPacket.c` is the canonical first promotion target.

## Inputs

- `build.ninja`     — final link line for canonical .o list
- `build/**/*.o`    — objdump -h for per-.o section content
- `config/ico.us.ld` — current ld for .text ordering ground truth

## Output

- `config/ico.us.slinky.yaml`
"""

from __future__ import annotations

import re
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
NINJA = REPO / "build.ninja"
CUR_LD = REPO / "config" / "ico.us.ld"
OUT = REPO / "config" / "ico.us.slinky.yaml"

# Section bases we care about (ELF input section name prefixes).
ALLOC_BASES = (".text", ".data", ".rodata", ".lit4", ".sdata")
NOLOAD_BASES = (".sbss", ".bss")
NOLOAD_ALIASES = {".sbss": (".sbss", ".scommon"), ".bss": (".bss", "COMMON")}

# Section start VMAs in the baseelf (ground truth for segment placement).
SECTION_VRAM = {
    ".text":   0x00100000,
    ".data":   0x00274700,
    ".rodata": 0x00553700,
    ".lit4":   0x00630900,
    ".sdata":  0x00631900,
    ".sbss":   0x00633C00,
    ".bss":    0x00634000,
}

# Alignment requirements at the start of each segment (derived from
# baseelf VMA layout — see decomp/NOTES.md "Per-TU section linking"
# block). 0x100 is the pad that postprocess_ld.py currently injects
# between data sub-sections; 0x80 is .bss's required alignment per the
# original Sony linker config.
SEGMENT_START_ALIGN = {
    ".data":   0x100,
    ".rodata": 0x100,
    ".lit4":   0x100,
    ".sdata":  0x100,
    ".sbss":   0x100,
    ".bss":    0x80,
}

OBJDUMP_CANDIDATES = ("mips64r5900el-ps2-elf-objdump", "mips-linux-gnu-objdump")


def find_objdump() -> str:
    for name in OBJDUMP_CANDIDATES:
        try:
            subprocess.run([name, "--version"], capture_output=True, check=True)
            return name
        except (FileNotFoundError, subprocess.CalledProcessError):
            continue
    raise SystemExit("gen_slinky: no objdump found "
                     f"(tried {', '.join(OBJDUMP_CANDIDATES)})")


def parse_link_objs(ninja_text: str) -> list[str]:
    """Pull the .o list out of build.ninja's final link statement."""
    m = re.search(
        r'^build build/ico\.elf:\s*link\s+(.+?)(?:\n\s*\||\n[a-z]|\Z)',
        ninja_text, re.MULTILINE | re.DOTALL,
    )
    if not m:
        raise SystemExit("gen_slinky: no link line in build.ninja "
                         "(run `tools/build.sh setup` first)")
    body = m.group(1).replace("$\n", " ").replace("\\\n", " ")
    return re.findall(r'build/\S+?\.o', body)


def parse_ld_text_order(ld_text: str) -> list[str]:
    """Pull the .text input list from `cod_TEXT_START`..`cod_TEXT_END`.

    This is the splat-emitted order (already in .text VMA order) and is
    used directly for the slinky `text` segment.
    """
    m = re.search(
        r'cod_TEXT_START\s*=\s*\.\s*;(.*?)cod_TEXT_END\s*=\s*\.\s*;',
        ld_text, re.DOTALL,
    )
    if not m:
        raise SystemExit("gen_slinky: cod_TEXT_START/END not in ld")
    out = []
    for line in m.group(1).splitlines():
        m2 = re.match(r'\s*(build/\S+?\.o)\(', line)
        if m2:
            out.append(m2.group(1))
    return out


_OBJDUMP_CACHE: dict[str, list[tuple[str, int]]] = {}


def sections_of(objdump: str, opath: str) -> list[tuple[str, int]]:
    """Return [(section_name, size), ...] for a .o file.

    Sections with size 0 are dropped. Cached because the link list has
    duplicates and we call this per .o.
    """
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


def min_vma_in_section(secs: list[tuple[str, int]], base: str) -> int | None:
    """Lowest VMA of a `.<base>.0xVMA` section, or None if only plain
    `.<base>` is present (which carries no VMA hint in a relocatable .o)."""
    vmas: list[int] = []
    for name, _sz in secs:
        if name.startswith(base + ".0x"):
            try:
                vmas.append(int(name.split(".0x", 1)[1], 16))
            except ValueError:
                continue
    return min(vmas) if vmas else None


def contributes(secs: list[tuple[str, int]], base: str,
                noload_aliases: tuple[str, ...] = ()) -> bool:
    """True if this .o has any non-empty section matching the base or
    any of its noload aliases (.scommon for .sbss, COMMON for .bss)."""
    for name, _sz in secs:
        if name == base or name.startswith(base + "."):
            return True
        if name in noload_aliases:
            return True
    return False


def vma_from_blanket_path(opath: str) -> int | None:
    """Asm-side data blanket .o filenames encode their VMA, e.g.
    `build/asm/data/src/cod/174700.data.o` → 0x174700. Used to assign
    a sort key when the .o has only plain `.X` sections (no typed
    `.X.0xVMA`)."""
    m = re.search(r'/([0-9A-Fa-f]+)\.(?:data|rodata|lit4|sdata|sbss|bss)\.o$',
                  opath)
    if m:
        # File offset → VMA: load base is 0x100000.
        return int(m.group(1), 16) + 0x100000
    # 16F5E0 textbin .o is asm/data/src/cod/16F5E0.o — no .data infix.
    m = re.search(r'/([0-9A-Fa-f]{6,})\.o$', opath)
    if m:
        try:
            return int(m.group(1), 16) + 0x100000
        except ValueError:
            return None
    return None


def build_data_segment_files(objdump: str, link_objs: list[str],
                             base: str, noload_aliases: tuple[str, ...] = (),
                             ) -> list[str]:
    """Order .o files for one data/bss segment by min VMA in that section."""
    seen: set[str] = set()
    entries: list[tuple[int, str]] = []
    for o in link_objs:
        if o in seen:
            continue
        seen.add(o)
        secs = sections_of(objdump, o)
        if not contributes(secs, base, noload_aliases):
            continue
        vma = min_vma_in_section(secs, base)
        if vma is None:
            vma = vma_from_blanket_path(o)
        if vma is None:
            # No VMA hint — append at the end (asm blanket .o that has
            # only a plain `.<base>` section without VMA suffix in name).
            vma = 0xFFFFFFFF
        entries.append((vma, o))
    entries.sort(key=lambda x: (x[0], x[1]))
    return [o for _, o in entries]


# Header comment for the emitted yaml — explains provenance and the
# "not yet wired" status so a reader understands the artifact's role.
YAML_HEADER = """\
# config/ico.us.slinky.yaml — auto-generated by tools/gen_slinky.py.
#
# DO NOT HAND-EDIT. Re-run `.venv/bin/python tools/gen_slinky.py` after
# splat changes the .o set.
#
# Status: PARALLEL ARTIFACT. ninja still uses ico.us.ld (the
# postprocess_ld.py-patched splat output). Switching ninja's -T to the
# slinky-generated ld requires retiring `.X.0xVMA` typed sections
# (Phase 3c/3d). See decomp/NOTES.md "Per-TU section linking — slinky
# integration roadmap" and src/DmaPacket.c REVISIT note.
"""


def emit_yaml(text_files: list[str],
              data_files: list[str],
              rodata_files: list[str],
              lit4_files: list[str],
              sdata_files: list[str],
              sbss_files: list[str],
              bss_files: list[str]) -> str:
    """Render the slinky yaml from the per-segment file lists."""
    lines: list[str] = [YAML_HEADER, ""]
    lines += [
        "settings:",
        "  base_path: build",
        "  subalign: null",
        "  wildcard_sections: True",
        "  discard_wildcard_section: True",
        "  sections_denylist:",
        "    - .reginfo",
        "    - .MIPS.abiflags",
        "    - .gnu.attributes",
        "    - .pdr",
        "    - .mdebug",
        "  sections_allowlist_extra:",
        "    - .shstrtab",
        "    - .symtab",
        "    - .strtab",
        "",
        "segments:",
    ]

    def emit_segment(name: str, files: list[str], *,
                     alloc: list[str] | None,
                     noload: list[str] | None,
                     fixed_vram: int | None = None,
                     start_align: int | None = None,
                     gp_info: tuple[str, int] | None = None) -> None:
        lines.append(f"  - name: {name}")
        if fixed_vram is not None:
            lines.append(f"    fixed_vram: 0x{fixed_vram:08X}")
        if start_align is not None:
            lines.append(f"    segment_start_align: 0x{start_align:X}")
        if gp_info is not None:
            sect, off = gp_info
            lines.append("    gp_info:")
            lines.append(f"      section: {sect}")
            lines.append(f"      offset: 0x{off:X}")
        # Always emit both alloc_sections and noload_sections explicitly
        # so we override slinky's default `[.sbss, .scommon, .bss, COMMON]`
        # noload list. Otherwise every alloc-only segment (text, data,
        # rodata, lit4, sdata) emits a `.X.noload` block that picks up
        # bss/sbss from every listed .o — double-counting the bss
        # content across segments.
        if alloc is None:
            lines.append("    alloc_sections: null")
        else:
            lines.append(f"    alloc_sections: [{', '.join(alloc)}]")
        if noload is None:
            lines.append("    noload_sections: null")
        else:
            lines.append(f"    noload_sections: [{', '.join(noload)}]")
        lines.append("    files:")
        for o in files:
            # Strip the "build/" prefix; base_path resolves it.
            path = o[len("build/"):] if o.startswith("build/") else o
            lines.append(f"      - {{ path: {path} }}")
        lines.append("")

    emit_segment("text", text_files,
                 alloc=[".text"], noload=None,
                 fixed_vram=SECTION_VRAM[".text"])
    emit_segment("data", data_files,
                 alloc=[".data"], noload=None,
                 start_align=SEGMENT_START_ALIGN[".data"])
    emit_segment("rodata", rodata_files,
                 alloc=[".rodata"], noload=None,
                 start_align=SEGMENT_START_ALIGN[".rodata"])
    # ICO sets _gp at .lit4 start + 0x7FF0 (NOT .sdata start). Matches
    # the current `_gp = cod_LIT4_START + 0x7FF0;` line in
    # config/ico.us.ld. slinky's default is .sdata-relative, which is
    # off by 0x1000 and overflows GPREL16 relocations for the lowest
    # .sdata symbols.
    emit_segment("lit4", lit4_files,
                 alloc=[".lit4"], noload=None,
                 start_align=SEGMENT_START_ALIGN[".lit4"],
                 gp_info=(".lit4", 0x7FF0))
    emit_segment("sdata", sdata_files,
                 alloc=[".sdata"], noload=None,
                 start_align=SEGMENT_START_ALIGN[".sdata"])
    # sbss/bss: list BOTH alloc and noload sections. ee-gcc's .o files
    # already mark these as SHT_NOBITS, so the linker emits them as
    # NOLOAD regardless. Listing them in alloc keeps slinky's automatic
    # `sbss_VRAM = ADDR(.sbss)` symbol references happy (with alloc
    # null, slinky still emits the symbol but there's no `.sbss`
    # output section → undefined section reference → link error).
    # Matches parappa2's slinky.yaml.
    emit_segment("sbss", sbss_files,
                 alloc=list(NOLOAD_ALIASES[".sbss"]),
                 noload=list(NOLOAD_ALIASES[".sbss"]),
                 start_align=SEGMENT_START_ALIGN[".sbss"])
    emit_segment("bss", bss_files,
                 alloc=list(NOLOAD_ALIASES[".bss"]),
                 noload=list(NOLOAD_ALIASES[".bss"]),
                 start_align=SEGMENT_START_ALIGN[".bss"])

    return "\n".join(lines)


def main() -> int:
    if not NINJA.exists():
        raise SystemExit(
            "gen_slinky: build.ninja not found — run `tools/build.sh setup`"
        )
    if not CUR_LD.exists():
        raise SystemExit("gen_slinky: config/ico.us.ld not found")

    objdump = find_objdump()
    link_objs = parse_link_objs(NINJA.read_text())
    text_order = parse_ld_text_order(CUR_LD.read_text())

    # Sanity: text_order should be a subset of link_objs.
    missing = [o for o in text_order if o not in set(link_objs)]
    if missing:
        print(f"gen_slinky: WARN {len(missing)} .text .o file(s) "
              f"in ico.us.ld but not in build.ninja link line "
              f"(first: {missing[0]})", file=sys.stderr)

    data_files = build_data_segment_files(objdump, link_objs, ".data")
    rodata_files = build_data_segment_files(objdump, link_objs, ".rodata")
    lit4_files = build_data_segment_files(objdump, link_objs, ".lit4")
    sdata_files = build_data_segment_files(objdump, link_objs, ".sdata")
    sbss_files = build_data_segment_files(objdump, link_objs, ".sbss",
                                          noload_aliases=(".scommon",))
    bss_files = build_data_segment_files(objdump, link_objs, ".bss",
                                         noload_aliases=("COMMON",))

    yaml_text = emit_yaml(
        text_order,
        data_files, rodata_files, lit4_files, sdata_files,
        sbss_files, bss_files,
    )
    OUT.write_text(yaml_text + "\n")
    print(f"gen_slinky: wrote {OUT.relative_to(REPO)}"
          f"  text={len(text_order)} data={len(data_files)} "
          f"rodata={len(rodata_files)} lit4={len(lit4_files)} "
          f"sdata={len(sdata_files)} sbss={len(sbss_files)} "
          f"bss={len(bss_files)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
