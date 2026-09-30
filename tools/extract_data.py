#!/usr/bin/env python3
"""tools/extract_data.py -- write the data-only members' assembly from the base ELF.

The retail link carries ico2000.a members that have .data/.rodata/.sdata but no
.text: game data tables (obj-layout, model-path, motion-def, sedef, way-point,
...). They are never committed as C (user decision 2026-09-30). The build
extracts their bytes from the user's own baserom/pal/baseelf.elf, one assembly
file per (member, section) row of config/data_members.pal.txt:

    build/data/<member>.<section>.s

Each file switches to the row's section, aligns to the member's natural
alignment (the largest power of two dividing its start, capped at 16), defines
a global label for every MAIN.MAP symbol the row names at its offset, and
spells the bytes as .word where the address is 4-aligned and .byte otherwise.
Pointers inside the tables stay absolute words: every address is fixed by the
link, so nothing needs a relocation.

Usage:
    tools/extract_data.py [--table T] [--elf E] [--out-dir D]
                          [--extra-labels F] [--assemble] [--only MEMBER.SECTION ...]

--assemble also assembles every written file with the period assembler the way
tools/compile_c.sh assembles game code (tools/period_env.sh + the ee-gcc
2.9-991111 as, -EL -mcpu=5900 -G 8) and checks that the object's section bytes
equal the ROM range exactly; any difference is an error.

--extra-labels names a file of "<symbol> <vma>" lines: each symbol inside a
row's range is also defined, as a global label at that address. The table only
carries MAIN.MAP's names; this is for links whose other objects still refer to
the tables by placeholder names.
"""

import argparse
import subprocess
import sys
from pathlib import Path

from elftools.elf.elffile import ELFFile

ROOT = Path(__file__).resolve().parent.parent
SECTIONS = ("data", "rodata", "sdata")
EE_AS = ROOT / "tools/cc/ee-gcc2.9-991111/bin/as"
PERIOD_ENV = ROOT / "tools/period_env.sh"
EE_ASFLAGS = ["-EL", "-mcpu=5900", "-G", "8"]


def parse_table(path):
    rows = []
    for n, line in enumerate(path.read_text().splitlines(), 1):
        line = line.split("#", 1)[0].strip()
        if not line:
            continue
        f = line.split()
        if len(f) != 5 or f[0] not in SECTIONS:
            sys.exit(f"{path}:{n}: expected '<section> <member> <rom_lo> <rom_hi> <symbols>'")
        lo, hi = int(f[2], 16), int(f[3], 16)
        if not lo < hi:
            sys.exit(f"{path}:{n}: empty range")
        syms = []
        if f[4] != "-":
            for s in f[4].split(","):
                name, off = s.split("@")
                syms.append((name, int(off, 16)))
        rows.append(dict(section=f[0], member=f[1], lo=lo, hi=hi, syms=syms, line=n))
    return rows


def rom_bytes(elf, lo, hi, section):
    s = elf.get_section_by_name("." + section)
    if s is None:
        sys.exit(f"base ELF has no .{section}")
    base, size = s["sh_addr"], s["sh_size"]
    if not (base <= lo and hi <= base + size):
        sys.exit(f"0x{lo:x}..0x{hi:x} is outside the base ELF's .{section} (0x{base:x}..0x{base + size:x})")
    return s.data()[lo - base:hi - base]


def natural_align(addr):
    a = 1
    while a < 16 and addr % (a * 2) == 0:
        a *= 2
    return a


def render(row, data, extra):
    lo, hi = row["lo"], row["hi"]
    labels = {}
    for name, off in row["syms"]:
        if not 0 <= off < hi - lo:
            sys.exit(f"table line {row['line']}: {name}@0x{off:x} is outside the row")
        labels.setdefault(lo + off, []).append(name)
    for name, addr in extra:
        if lo <= addr < hi and name not in labels.get(addr, []):
            labels.setdefault(addr, []).append(name)
    align = natural_align(lo)
    out = [
        f"# {row['member']}.o .{row['section']}: VMA 0x{lo:08X}..0x{hi:08X} ({hi - lo} B),",
        "# extracted from baserom/pal/baseelf.elf by tools/extract_data.py.",
        "# Generated: do not commit.",
        "",
        f"    .section .{row['section']}",
        f"    .align {align.bit_length() - 1}",
        "",
    ]
    for names in labels.values():
        for name in names:
            out.append(f"    .globl {name}")
    a = lo
    while a < hi:
        for name in labels.get(a, []):
            out.append(f"{name}:")
        # the next label bounds this run of words or bytes
        nxt = min([b for b in labels if a < b < hi] + [hi])
        if a % 4 == 0 and nxt - a >= 4:
            n = (nxt - a) // 4
            for i in range(0, n, 4):
                words = [int.from_bytes(data[a - lo + 4 * j:a - lo + 4 * j + 4], "little")
                         for j in range(i, min(i + 4, n))]
                out.append(f"    .word {', '.join(f'0x{w:08X}' for w in words)}  # {a + 4 * i:08X}")
            a += 4 * n
        else:
            end = nxt if a % 4 == 0 else min(nxt, (a + 3) & ~3)
            out.append(f"    .byte {', '.join(f'0x{b:02X}' for b in data[a - lo:end - lo])}  # {a:08X}")
            a = end
    out.append("")
    return "\n".join(out)


def assemble_and_check(src, row, data):
    obj = src.with_suffix(".o")
    r = subprocess.run([str(PERIOD_ENV), str(EE_AS), *EE_ASFLAGS, "-o", str(obj), str(src)],
                       capture_output=True, text=True)
    if r.returncode != 0:
        sys.exit(f"{src}: assembler failed:\n{r.stderr}")
    with open(obj, "rb") as fh:
        e = ELFFile(fh)
        s = e.get_section_by_name("." + row["section"])
        got = s.data() if s is not None else b""
        for other in (".data", ".rodata", ".sdata", ".text"):
            t = e.get_section_by_name(other)
            if other != "." + row["section"] and t is not None and t["sh_size"]:
                sys.exit(f"{obj}: unexpected bytes in {other}")
    if got != data:
        diff = next((i for i in range(min(len(got), len(data))) if got[i] != data[i]), min(len(got), len(data)))
        sys.exit(f"{obj}: .{row['section']} differs from the ROM at 0x{row['lo'] + diff:x} "
                 f"(object {len(got)} B, ROM {len(data)} B)")
    return obj


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--table", type=Path, default=ROOT / "config/data_members.pal.txt")
    ap.add_argument("--elf", type=Path, default=ROOT / "baserom/pal/baseelf.elf")
    ap.add_argument("--out-dir", type=Path, default=ROOT / "build/data")
    ap.add_argument("--extra-labels", type=Path)
    ap.add_argument("--assemble", action="store_true")
    ap.add_argument("--only", nargs="*", help="MEMBER.SECTION names to write (default: every row)")
    args = ap.parse_args()

    rows = parse_table(args.table)
    seen = set()
    for r in rows:
        key = f"{r['member']}.{r['section']}"
        if key in seen:
            sys.exit(f"table line {r['line']}: {key} appears twice")
        seen.add(key)
    extra = []
    if args.extra_labels:
        for line in args.extra_labels.read_text().split("\n"):
            if line.strip():
                name, addr = line.split()
                extra.append((name, int(addr, 16)))

    args.out_dir.mkdir(parents=True, exist_ok=True)
    with open(args.elf, "rb") as fh:
        elf = ELFFile(fh)
        for r in rows:
            key = f"{r['member']}.{r['section']}"
            if args.only and key not in args.only:
                continue
            data = rom_bytes(elf, r["lo"], r["hi"], r["section"])
            src = args.out_dir / f"{key}.s"
            src.write_text(render(r, data, extra))
            if args.assemble:
                assemble_and_check(src, r, data)
                print(f"ok {key} 0x{r['lo']:x}..0x{r['hi']:x}")


if __name__ == "__main__":
    main()
