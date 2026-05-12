#!/usr/bin/env python3
"""
quick_data_diff.py — fast verifier for typed .rodata/.data/.sdata/.lit4
symbols, skipping the ~4-min full link.

For each `__attribute__((section(".X.0xVMA"))) ... D_<VMA>` definition in
a hand-promoted src/<TU>.c, this tool:

  1. Compiles the file to a .o (mirroring the Makefile rule).
  2. For each per-VMA named section in the .o, extracts the raw bytes.
  3. Reads the same byte range from baserom/baseelf.elf at VMA `0xVMA`.
  4. Reports match/mismatch byte-for-byte.

No linker invocation. The match here proves the typed source produces
the same bytes the ROM has — which is what `make && verify-target`
ultimately checks for data sections, just without the 4 minutes of ld.

If every typed symbol in every changed src/<TU>.c reports MATCH, a
subsequent `make && verify-target` will too (modulo any text-side
regressions, which `quick_diff.sh` catches separately).

Usage:
    tools/quick_data_diff.py src/sugiTree.c [src/girlForceField.c ...]
    tools/quick_data_diff.py --all   # scan every tracked src/**/*.c
"""

from __future__ import annotations

import argparse
import re
import shutil
import subprocess
import sys
from pathlib import Path

try:
    from elftools.elf.elffile import ELFFile
except ImportError as exc:
    sys.exit(
        f"quick_data_diff: missing dependency ({exc.name}). "
        "Run `.venv/bin/pip install -r tools/requirements.txt`."
    )


REPO = Path(__file__).resolve().parent.parent
BASEELF = REPO / "baserom" / "baseelf.elf"
BUILD = REPO / "build" / "quick_data_diff"
EEGCC = REPO / "tools" / "cc" / "ee-gcc2.9-991111" / "ee-gcc"
EEGCC_LIB = REPO / "tools" / "cc" / "ee-gcc2.9-991111" / "gcc-lib" / "ee" / "2.9-ee-991111-01"
EE_AS = REPO / "tools" / "cc" / "ee-gcc2.96" / "bin" / "as"
EXTRA_CFLAGS = REPO / "tools" / "extra_cflags.sh"

CFLAGS_BASE = [
    "-S", "-G", "8", "-O2", "-mips3", "-EL",
    "-fno-builtin", "-nostdinc",
    f"-I{REPO / 'include'}",
]
EE_ASFLAGS = ["-EL", "-mcpu=5900", "-G", "8"]
MIPS_AS_FALLBACK = "mips-linux-gnu-as"
MIPS_ASFLAGS_FALLBACK = ["-EL", "-march=r5900", "-mabi=eabi", "-G", "8", "-no-pad-sections"]

SECTION_RE = re.compile(
    r'__attribute__\s*\(\(\s*section\s*\(\s*"\.(\w+)\.0x([0-9A-Fa-f]+)"\s*\)\s*\)\)'
    r'\s*(?:[\w\s\*]+?)\s+D_[0-9A-Fa-f]{8}\b'
)
DEFAULT_REGISTER_RENAME = [
    (r'\$zero\b', '$0'),  (r'\$at\b', '$1'),
    (r'\$v0\b',  '$2'),   (r'\$v1\b', '$3'),
    (r'\$a0\b',  '$4'),   (r'\$a1\b', '$5'),
    (r'\$a2\b',  '$6'),   (r'\$a3\b', '$7'),
    (r'\$t0\b',  '$8'),   (r'\$t1\b', '$9'),
    (r'\$t2\b',  '$10'),  (r'\$t3\b', '$11'),
    (r'\$t4\b',  '$12'),  (r'\$t5\b', '$13'),
    (r'\$t6\b',  '$14'),  (r'\$t7\b', '$15'),
    (r'\$s0\b',  '$16'),  (r'\$s1\b', '$17'),
    (r'\$s2\b',  '$18'),  (r'\$s3\b', '$19'),
    (r'\$s4\b',  '$20'),  (r'\$s5\b', '$21'),
    (r'\$s6\b',  '$22'),  (r'\$s7\b', '$23'),
    (r'\$t8\b',  '$24'),  (r'\$t9\b', '$25'),
    (r'\$k0\b',  '$26'),  (r'\$k1\b', '$27'),
    (r'\$gp\b',  '$28'),  (r'\$sp\b', '$29'),
    (r'\$fp\b',  '$30'),  (r'\$ra\b', '$31'),
]


def _canon_regs(s: str) -> str:
    out = s
    for pat, rep in DEFAULT_REGISTER_RENAME:
        out = re.sub(pat, rep, out)
    return out


def _per_file_cflags(src: Path) -> list[str]:
    if not EXTRA_CFLAGS.is_file():
        return []
    res = subprocess.run(
        [str(EXTRA_CFLAGS), str(src)],
        capture_output=True, text=True, cwd=REPO, check=False,
    )
    return res.stdout.split()


def _compile(src: Path) -> Path:
    """Compile src/<TU>.c → BUILD/<TU>.o, mirroring the Makefile rule."""
    BUILD.mkdir(parents=True, exist_ok=True)
    rel = src.resolve().relative_to(REPO / "src")
    stem = "__".join(rel.with_suffix("").parts)
    asm_path = BUILD / f"{stem}.s"
    obj_path = BUILD / f"{stem}.o"

    cflags = ["-B", str(EEGCC_LIB) + "/", *CFLAGS_BASE, *_per_file_cflags(src)]
    subprocess.run(
        [str(EEGCC), *cflags, "-o", str(asm_path), str(src)],
        cwd=REPO, check=True,
    )
    # ee-as 2.10 wants numbered registers, not aliases.
    asm_path.write_text(_canon_regs(asm_path.read_text()))

    # Try ee-as 2.10 first; fall back to mips-linux-gnu-as.
    if EE_AS.is_file():
        res = subprocess.run(
            [str(EE_AS), *EE_ASFLAGS, "-o", str(obj_path), str(asm_path)],
            cwd=REPO, capture_output=True, check=False,
        )
        if res.returncode == 0:
            return obj_path
    subprocess.run(
        [MIPS_AS_FALLBACK, *MIPS_ASFLAGS_FALLBACK, "-o", str(obj_path), str(asm_path)],
        cwd=REPO, check=True,
    )
    return obj_path


def _load_baseelf_bytes(vma: int, length: int) -> bytes:
    """Return the `length` bytes at `vma` from baserom/baseelf.elf."""
    with BASEELF.open("rb") as f:
        elf = ELFFile(f)
        for seg in elf.iter_segments():
            ph_vma = seg["p_vaddr"]
            ph_msz = seg["p_memsz"]
            ph_fsz = seg["p_filesz"]
            if ph_vma <= vma < ph_vma + ph_msz:
                off_in_seg = vma - ph_vma
                # Outside the loaded portion (.bss) -> zero-filled.
                if off_in_seg >= ph_fsz:
                    return b"\x00" * length
                want_end_in_seg = off_in_seg + length
                fbytes = seg.data()[off_in_seg:want_end_in_seg]
                # Pad with zeros for tails that fall beyond p_filesz.
                if len(fbytes) < length:
                    fbytes += b"\x00" * (length - len(fbytes))
                return fbytes
    raise ValueError(f"VMA 0x{vma:08x} not in any baseelf load segment")


def _apply_relocations(obj: Path,
                       sym_vmas: dict[str, int]
                       ) -> dict[str, bytes]:
    """For each `.X.0xVMA` section in `obj`, patch its bytes with the
    resolved value of every relocation that targets a symbol in
    `sym_vmas`. Returns {section_name: patched_data}.

    Pointer-array `_data.c` shapes (`void *D_X[] = { &D_Y, ... };`)
    emit relocations in the .o, so the raw section bytes have zeros
    where the pointers go. To byte-compare against baseelf, we
    resolve `&D_Y` against the linker map's VMA and write that VMA
    into the section bytes. Supports R_MIPS_32 only (the only reloc
    type ee-gcc emits for `void *` initializers on LE r5900)."""
    from elftools.elf.relocation import RelocationSection
    patched: dict[str, bytes] = {}
    with obj.open("rb") as f:
        elf = ELFFile(f)
        symtab = elf.get_section_by_name(".symtab")
        for sec in elf.iter_sections():
            m = re.match(r"\.\w+\.0x([0-9A-Fa-f]+)$", sec.name)
            if not m:
                continue
            data = bytearray(sec.data())
            # Find the matching rel section, if any.
            rel_name = ".rel" + sec.name
            rel_sec = elf.get_section_by_name(rel_name)
            if isinstance(rel_sec, RelocationSection) and symtab is not None:
                for rel in rel_sec.iter_relocations():
                    rtype = rel["r_info_type"]
                    if rtype != 2:  # R_MIPS_32
                        continue
                    sym = symtab.get_symbol(rel["r_info_sym"])
                    name = sym.name
                    target = sym_vmas.get(name)
                    if target is None:
                        continue
                    off = rel["r_offset"]
                    if off + 4 > len(data):
                        continue
                    # Existing 4 bytes are an addend (usually 0).
                    addend = int.from_bytes(data[off:off + 4], "little")
                    final = (target + addend) & 0xFFFFFFFF
                    data[off:off + 4] = final.to_bytes(4, "little")
            patched[sec.name] = bytes(data)
    return patched


def _per_vma_sections(obj: Path) -> list[tuple[str, int, bytes]]:
    """List (section_name, vma, data) for every `.X.0xVMA` section.
    Relocations are applied if the linker map is available, so
    pointer-array sections compare correctly to baseelf without a
    full re-link."""
    sym_vmas = _load_symbol_vmas()
    patched = _apply_relocations(obj, sym_vmas) if sym_vmas else {}
    out: list[tuple[str, int, bytes]] = []
    with obj.open("rb") as f:
        elf = ELFFile(f)
        for sec in elf.iter_sections():
            m = re.match(r"\.\w+\.0x([0-9A-Fa-f]+)$", sec.name)
            if not m:
                continue
            vma = int(m.group(1), 16)
            data = patched.get(sec.name, sec.data())
            out.append((sec.name, vma, data))
    return out


_SYM_VMAS_CACHE: dict[str, int] | None = None


def _load_symbol_vmas() -> dict[str, int]:
    """Return {symbol_name: vma} from build/ico.us.map. Returns empty
    dict if the map isn't built yet (callers fall back to raw bytes)."""
    global _SYM_VMAS_CACHE
    if _SYM_VMAS_CACHE is not None:
        return _SYM_VMAS_CACHE
    map_path = REPO / "build" / "ico.us.map"
    if not map_path.exists():
        _SYM_VMAS_CACHE = {}
        return _SYM_VMAS_CACHE
    try:
        from mapfile_parser import mapfile
        mf = mapfile.MapFile.newFromMapFile(map_path)
    except Exception:
        _SYM_VMAS_CACHE = {}
        return _SYM_VMAS_CACHE
    out: dict[str, int] = {}
    for segment in mf:
        for file in segment:
            for sym in file:
                out[sym.name] = sym.vram
    _SYM_VMAS_CACHE = out
    return out


def _check_file(src: Path, verbose: bool) -> tuple[int, int]:
    """Return (n_match, n_mismatch) for the symbols in this file."""
    obj = _compile(src)
    syms = _per_vma_sections(obj)
    if not syms:
        if verbose:
            print(f"  {src.relative_to(REPO)}: no per-VMA sections in .o")
        return 0, 0
    n_ok = 0
    n_bad = 0
    for sect, vma, got in syms:
        want = _load_baseelf_bytes(vma, len(got))
        if got == want:
            n_ok += 1
            if verbose:
                print(f"  MATCH    {sect}  ({len(got)} bytes @ 0x{vma:08x})")
        else:
            n_bad += 1
            print(f"  MISMATCH {sect}  ({len(got)} bytes @ 0x{vma:08x})")
            print(f"    want: {want.hex()}")
            print(f"    got:  {got.hex()}")
    return n_ok, n_bad


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[1])
    ap.add_argument("paths", nargs="*", help="src/<TU>.c paths to verify")
    ap.add_argument("--all", action="store_true",
                    help="scan every src/**/*.c (excluding *_data.c)")
    ap.add_argument("-q", "--quiet", action="store_true",
                    help="only print mismatches and the final summary")
    args = ap.parse_args()

    if args.all:
        paths = sorted(p for p in (REPO / "src").rglob("*.c")
                       if not p.name.endswith("_data.c"))
    else:
        paths = [Path(p).resolve() for p in args.paths]
        if not paths:
            ap.error("pass at least one src/<TU>.c, or --all")
        for p in paths:
            if not p.is_file():
                sys.exit(f"quick_data_diff: not a file: {p}")

    if not BASEELF.is_file():
        sys.exit(f"quick_data_diff: missing baseelf at {BASEELF} — run tools/extract_elf.sh first")
    if not EEGCC.is_file():
        sys.exit(f"quick_data_diff: missing ee-gcc at {EEGCC} — run tools/setup.sh")

    total_ok = 0
    total_bad = 0
    n_files_with_data = 0
    for src in paths:
        text = src.read_text(errors="replace")
        if not SECTION_RE.search(text):
            continue  # no per-VMA section attributes; nothing to verify
        n_files_with_data += 1
        if not args.quiet:
            print(f"{src.relative_to(REPO)}:")
        ok, bad = _check_file(src, verbose=not args.quiet)
        total_ok += ok
        total_bad += bad

    print()
    print(f"quick_data_diff: {n_files_with_data} file(s) checked, "
          f"{total_ok} symbol(s) MATCH, {total_bad} MISMATCH")
    return 0 if total_bad == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
