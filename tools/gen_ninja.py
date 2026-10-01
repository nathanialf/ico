#!/usr/bin/env python3
"""tools/gen_ninja.py: emit build.ninja from config/link_order.pal.txt.

Every object from its own source, linked by the hand-written config/link.pal.ld
in the one object order of config/link_order.pal.txt.

Rules: cc (tools/compile_c.sh), as (the .s sources, assembler and -G per
archive as compile_c.sh chooses them for C), vu (ico2/vusrc/*.dsm through
dvp-as, ps2dev's DVP assembler built by tools/setup.sh under tools/cc/dvp-as/,
run from ico2/ on the path vusrc/<stem>.dsm because the overlay section names
it writes hash that path; -no-abicalls -mabi=64 leave the ABI bits of e_flags
clear, the one setting the link merges with the game's EABI64 objects), data
(tools/extract_data.py per data-only member row), labels (the D_<VMA>
placeholders a tracked source still spells inside a data member's row, which
the extractor defines as labels), link (the period linker, GNU ld 2.10 with
tools/binutils-2.10-ee.patch, built by tools/setup.sh under
tools/cc/binutils-2.10-ee/, writing the IRIX-compatible elf32-littlemips output
MAIN.MAP names: once to ico.syms.elf, which keeps the symbols, and once with -s
to ico.elf, since the base carries no .symtab or .strtab but 2.10's -s keeps
their names in .shstrtab as the base does; ld 2.10 has no INCLUDE inside a
section, so the script it reads is build/link.ld, config/link.pal.ld with its
INCLUDE lines expanded), rom, verify (tools/check_elf.py --gate).

    tools/build.sh setup && ninja
"""

import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
LIST = "config/link_order.pal.txt"
SCRIPT = "config/link.pal.ld"
TABLE = "config/data_members.pal.txt"
BASE_ELF = "baserom/pal/baseelf.elf"
OUT = "build"
NINJA = "build.ninja"
LD = "tools/cc/binutils-2.10-ee/bin/ld"
DVP_AS = "tools/cc/dvp-as/bin/dvp-as"
LINK_LD = f"{OUT}/link.ld"
LABELS = f"{OUT}/data_labels.txt"
# Output sections the script can take input by input (its INCLUDE lines).
LISTED = {"data": ".data .data.*", "rodata": ".rodata .rodata.*"}


def fail(msg):
    sys.exit(f"gen_ninja: {msg}")


def parse_list():
    entries = []
    for n, line in enumerate((ROOT / LIST).read_text().splitlines(), 1):
        f = line.split("#", 1)[0].split()
        if not f:
            continue
        kind, _, name = f[0].rpartition(":")
        kind = kind or "src"
        if kind not in ("src", "data"):
            fail(f"{LIST}:{n}: unknown line form '{f[0]}'")
        align = {}
        for tok in f[1:]:
            m = re.fullmatch(r"align\.(data|rodata)=(\d+)", tok)
            if not m or kind != "src":
                fail(f"{LIST}:{n}: bad token '{tok}'")
            align[m.group(1)] = int(m.group(2))
        entries.append(dict(kind=kind, name=name, align=align, line=n))
    return entries


def table_rows():
    rows = {}
    for line in (ROOT / TABLE).read_text().splitlines():
        f = line.split("#", 1)[0].split()
        if f:
            rows.setdefault(f[1], []).append(f"{f[1]}.{f[0]}")
    return rows


def obj_of(src):
    return f"{OUT}/{src.rsplit('.', 1)[0]}.o"


def archive_as(src):
    """compile_c.sh's per-archive assembler and -G for a source path."""
    if re.match(r"sce/(libc|libm|libgcc)/", src):
        return "as_old", "0"
    if src.startswith("sce/"):
        return "as_sdk", "0"
    return "as_old", "8"


def check(entries, rows):
    listed = set()
    for e in entries:
        where = f"{LIST}:{e['line']}"
        if e["kind"] == "src":
            if not (ROOT / e["name"]).is_file():
                fail(f"{where}: {e['name']} does not exist")
            if e["name"] in listed:
                fail(f"{where}: {e['name']} is listed twice")
            listed.add(e["name"])
        elif e["name"] not in rows:
            fail(f"{where}: {e['name']} is not a member in {TABLE}")
    tracked = subprocess.run(["git", "ls-files", "--", "ico2", "sce"], cwd=ROOT,
                             capture_output=True, text=True, check=True).stdout.split()
    missing = [p for p in tracked if p.endswith((".c", ".s", ".S", ".dsm")) and p not in listed]
    if missing:
        fail(f"tracked sources missing from {LIST}:\n  " + "\n  ".join(missing))


def label_sources():
    """The files write_labels scans: every tracked C, header and assembly source."""
    tracked = subprocess.run(["git", "ls-files", "--", "ico2", "sce"], cwd=ROOT,
                             capture_output=True, text=True, check=True).stdout.split()
    return [p for p in tracked if p.endswith((".c", ".h", ".inc", ".s", ".S"))]


def write_labels(out):
    """Transitional: the placeholders a source still gives addresses inside the
    extracted tables. config/data_members.pal.txt carries MAIN.MAP's names and
    the few derived names the C reads a table by; a C or assembly file that reads
    a table at an interior offset by a placeholder (D_<VMA>, the address is the
    name) needs that label defined. Only names some source spells are written,
    so the file empties as the readers take their tables' real names."""
    rows = []
    for line in (ROOT / TABLE).read_text().splitlines():
        f = line.split("#", 1)[0].split()
        if f:
            own = set() if f[4] == "-" else {s.split("@")[0] for s in f[4].split(",")}
            rows.append((int(f[2], 16), int(f[3], 16), own))
    idents = set()
    for p in label_sources():
        idents.update(re.findall(r"\bD_[0-9A-F]{8}\b", (ROOT / p).read_text(errors="replace")))
    lines = []
    for name in sorted(idents):
        addr = int(name[2:], 16)
        if any(lo <= addr < hi and name not in own for lo, hi, own in rows):
            lines.append(f"{name} {addr:08X}")
    Path(out).parent.mkdir(parents=True, exist_ok=True)
    Path(out).write_text("".join(l + "\n" for l in lines))


def objects(e, rows):
    if e["kind"] == "src":
        return [obj_of(e["name"])]
    return [f"{OUT}/data/{k}.o" for k in rows[e["name"]]]


def inputs_ld(entries, rows, sec):
    """build/<sec>.inputs.ld: the section input by input, or empty when no
    line needs more than the script's wildcard."""
    if not any(sec in e["align"] for e in entries):
        return ""
    out = []
    for e in entries:
        for o in objects(e, rows):
            if sec in e["align"]:
                out.append(f". = ALIGN({e['align'][sec]});")
            out.append(f"*{o}({LISTED[sec]})")
    return "\n".join(out) + "\n"


def expand_includes(script):
    """config/link.pal.ld with each INCLUDE line replaced by the file it names:
    ld 2.10 reads INCLUDE only at the top level of a script."""
    out = []
    for line in (ROOT / script).read_text().splitlines(keepends=True):
        m = re.fullmatch(r"(\s*)INCLUDE\s+(\S+)\s*", line)
        if m:
            out.append((ROOT / m.group(2)).read_text())
        else:
            out.append(line)
    return "".join(out)


def main():
    if sys.argv[1:2] == ["--labels"]:
        write_labels(sys.argv[2])
        return 0
    entries = parse_list()
    rows = table_rows()
    check(entries, rows)
    for sec in LISTED:
        p = ROOT / OUT / f"{sec}.inputs.ld"
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(inputs_ld(entries, rows, sec))
    (ROOT / LINK_LD).write_text(expand_includes(SCRIPT))
    w = []
    w.append(f"# Generated by tools/gen_ninja.py from {LIST}; do not edit.\n"
             f"ninja_required_version = 1.10\nbuilddir = {OUT}\n"
             f"ld = {LD}\ndvp_as = {DVP_AS}\nobjcopy = mips-linux-gnu-objcopy\npy = .venv/bin/python\n"
             "as_old = tools/period_env.sh tools/cc/ee-gcc2.9-991111/bin/as\n"
             "as_sdk = tools/period_env.sh tools/cc/ee-gcc2.96/bin/as\n"
             "asflags = -EL -mcpu=5900 -mabi=eabi\n"
             f"ldcmd = $ld -EL --oformat elf32-littlemips -T {LINK_LD} --no-warn-mismatch\n\n")
    w.append(f"rule gen\n  command = $py tools/gen_ninja.py\n  generator = 1\n"
             "  description = GEN $out\n\n"
             "rule cc\n  command = tools/compile_c.sh $in $out\n  description = CC $out\n\n")
    for r in ("as_old", "as_sdk"):
        w.append(f"rule {r}\n  command = ${r} $asflags -G $gnum -o $out $in\n  description = AS $out\n\n")
    w.append("rule vu\n  command = cd ico2 && ../$dvp_as -no-abicalls -mabi=64 -o ../$out $dsm\n"
             "  description = VU $out\n\n"
             f"rule data\n  command = $py tools/extract_data.py --only $key --out-dir {OUT}/data"
             f" --extra-labels {LABELS} --assemble > /dev/null\n  description = DATA $out\n\n"
             "rule labels\n  command = $py tools/gen_ninja.py --labels $out\n"
             "  description = LABELS $out\n\n"
             f"rule link\n  command = $ldcmd -Map {OUT}/ico.pal.map -o {OUT}/ico.syms.elf $in"
             f" && $ldcmd -s -o {OUT}/ico.elf $in\n  description = LD $out\n\n"
             "rule rom\n  command = $objcopy -O binary --gap-fill=0 $in $out\n  description = ROM $out\n\n"
             f"rule verify\n  command = $py tools/check_elf.py --gate --elf {OUT}/ico.elf"
             f" --map {OUT}/ico.pal.map --rom $in && touch $out\n  description = VERIFY $in\n\n")
    link = []
    for e in entries:
        for o in objects(e, rows):
            link.append(o)
            if e["kind"] == "src" and e["name"].endswith(".c"):
                w.append(f"build {o}: cc {e['name']}\n")
            elif e["kind"] == "src" and e["name"].endswith(".dsm"):
                w.append(f"build {o}: vu {e['name']} | {DVP_AS}\n"
                         f"  dsm = {Path(e['name']).relative_to('ico2')}\n")
            elif e["kind"] == "src":
                rule, gnum = archive_as(e["name"])
                w.append(f"build {o}: {rule} {e['name']}\n  gnum = {gnum}\n")
            else:
                key = Path(o).stem
                w.append(f"build {o}: data {TABLE} | tools/extract_data.py {BASE_ELF} {LABELS}\n"
                         f"  key = {key}\n")
    w.append(f"build {LABELS}: labels {' '.join(label_sources())} | {LIST} {TABLE}"
             " tools/gen_ninja.py\n")
    w.append(f"\nbuild {OUT}/ico.syms.elf {OUT}/ico.elf: link {' '.join(link)} | {LINK_LD} {LD}\n"
             f"build {OUT}/ico.rom: rom {OUT}/ico.elf\n"
             f"build {OUT}/.verified: verify {OUT}/ico.rom | tools/check_elf.py\n"
             f"default {OUT}/.verified\n"
             f"build {NINJA} {OUT}/data.inputs.ld {OUT}/rodata.inputs.ld {LINK_LD}: gen | "
             f"tools/gen_ninja.py {LIST} {TABLE} {SCRIPT}\n")
    (ROOT / NINJA).write_text("".join(w))
    n = {k: sum(e["kind"] == k for e in entries) for k in ("src", "data")}
    toks = sum(len(e["align"]) for e in entries)
    print(f"gen_ninja: wrote {NINJA} ({len(link)} objects: {n['src']} sources, "
          f"{n['data']} data members, {toks} align tokens)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
