#!/usr/bin/env python3
"""
first_diff.py — symbolic ELF-mismatch diagnosis for the ICO decomp.

When `make` reports a SHA-1 mismatch between the built ELF and the
extracted base ELF, this tool walks both files four bytes at a time
across the .text section, locates each differing word in the linker
mapfile, and prints the containing function, the byte offset within
that function, and a side-by-side disassembly of the differing
instructions.

Defaults:
    --base   baserom/baseelf.elf
    --built  build/baseelf.elf
    --map    build/ico.us.map
"""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

try:
    import rabbitizer
    from elftools.elf.elffile import ELFFile
    from mapfile_parser import mapfile
except ImportError as exc:  # pragma: no cover
    sys.exit(
        f"first_diff.py: missing dependency ({exc.name}). "
        "Run `.venv/bin/pip install -r tools/requirements.txt`."
    )


REPO_ROOT = Path(__file__).resolve().parent.parent
DEFAULT_BASE = REPO_ROOT / "baserom" / "baseelf.elf"
DEFAULT_BUILT = REPO_ROOT / "build" / "baseelf.elf"
DEFAULT_MAP = REPO_ROOT / "build" / "ico.us.map"


def _word_le(buf: bytes) -> int:
    return buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24)


def _load_text(elf_path: Path) -> tuple[bytes, int]:
    """Return (.text bytes, .text vram start)."""
    with elf_path.open("rb") as f:
        elf = ELFFile(f)
        sec = elf.get_section_by_name(".text")
        if sec is None:
            raise SystemExit(f"first_diff: no .text in {elf_path}")
        return sec.data(), sec["sh_addr"]


def _disasm_with_symbols(
    word_bytes: bytes,
    vram: int,
    map_file: mapfile.MapFile | None,
) -> str:
    instr = rabbitizer.Instruction(_word_le(word_bytes), vram)
    if map_file is not None and instr.isJumpWithAddress():
        target = instr.getInstrIndexAsVram()
        found = map_file.findSymbolByVramOrVrom(target)
        if found is not None:
            return instr.disassemble(found.symbol.name)
    return instr.disassemble()


def _resolve_function(
    map_file: mapfile.MapFile | None,
    vram_addr: int,
) -> tuple[str, int] | None:
    if map_file is None:
        return None
    found = map_file.findSymbolByVramOrVrom(vram_addr)
    if found is None:
        return None
    sym = found.symbol
    return sym.name, vram_addr - sym.vram


def first_diff(
    base_path: Path,
    built_path: Path,
    map_path: Path,
    diff_count: int,
) -> int:
    for label, p in (("base ELF", base_path), ("built ELF", built_path)):
        if not p.exists():
            print(f"first_diff: {label} not found at {p}", file=sys.stderr)
            return 2

    base_text, base_vram = _load_text(base_path)
    built_text, built_vram = _load_text(built_path)

    if base_text == built_text:
        print("first_diff: .text sections are identical (mismatch elsewhere — check .data/.rodata).")
        return 0

    if base_vram != built_vram:
        print(
            f"first_diff: .text VRAM differs — base=0x{base_vram:X} built=0x{built_vram:X}",
            file=sys.stderr,
        )

    map_file = None
    if map_path.exists():
        try:
            map_file = mapfile.MapFile.newFromMapFile(map_path)
        except Exception as e:
            print(f"first_diff: mapfile parse failed ({e}); names will be unresolved", file=sys.stderr)

    end = min(len(base_text), len(built_text))
    found_any = 0
    for off in range(0, end - (end % 4), 4):
        if base_text[off : off + 4] == built_text[off : off + 4]:
            continue
        vram = base_vram + off
        resolved = _resolve_function(map_file, vram)
        if resolved is None:
            print(
                f"0x{vram:08X} (no symbol):  base={base_text[off:off+4].hex()}  "
                f"built={built_text[off:off+4].hex()}"
            )
        else:
            func, in_func_off = resolved
            base_disasm = _disasm_with_symbols(base_text[off : off + 4], vram, map_file)
            built_disasm = _disasm_with_symbols(built_text[off : off + 4], vram, map_file)
            print(
                f"{func}+0x{in_func_off:X}:  base= {base_disasm}     built= {built_disasm}"
            )
        found_any += 1
        if found_any >= diff_count:
            break

    if found_any == 0:
        print("first_diff: ELFs differ but no 4-byte word diffs in .text.")
        return 1
    return 0


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("-n", type=int, default=5, metavar="N",
                        help="print up to N differing instructions (default: 5)")
    parser.add_argument("--base", type=Path, default=DEFAULT_BASE)
    parser.add_argument("--built", type=Path, default=DEFAULT_BUILT)
    parser.add_argument("--map", type=Path, default=DEFAULT_MAP, dest="map_path")
    args = parser.parse_args(argv)
    return first_diff(args.base, args.built, args.map_path, args.n)


if __name__ == "__main__":
    sys.exit(main())
