#!/usr/bin/env python3
"""tools/gen_ninja_plain.py: emit build.plain.ninja from config/link_order.pal.txt.

The plain build: every object from its own source, linked by the hand-written
config/link.pal.ld in the one object order of config/link_order.pal.txt, with
no splat manifest and no generated linker script. It runs beside the splat
build (objects under build/plain/) until the cut-over, where this file becomes
tools/gen_ninja.py and OUT becomes build/.

Rules: cc (tools/compile_c.sh), as (the .s sources, assembler and -G per
archive as compile_c.sh chooses them for C), vu (tools/assemble_vu0.py, then the
game's assembler), data (tools/extract_data.py per data-only member row), link,
rom, verify (tools/check_elf.py --gate). Transitional: blob (a splat data blob
under asm/data/cod/, aligned to its own ROM address) and labels (the names the
uncarved C still gives addresses inside the extracted tables, read from the
splat blobs the data: lines replace).

    .venv/bin/python tools/gen_ninja_plain.py && ninja -f build.plain.ninja
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
OUT = "build/plain"
NINJA = "build.plain.ninja"
LABELS = f"{OUT}/data_labels.txt"
# Output sections the script can take input by input (its INCLUDE lines).
LISTED = {"data": ".data .data.*", "rodata": ".rodata .rodata.*"}
# Linker inputs splat still writes; gone with splat at the cut-over.
UNDEFINED = ["config/undefined_funcs_auto.pal.txt", "config/undefined_syms_auto.pal.txt",
             "config/undefined_funcs_extra.pal.txt"]


def fail(msg):
    sys.exit(f"gen_ninja_plain: {msg}")


def parse_list():
    entries = []
    for n, line in enumerate((ROOT / LIST).read_text().splitlines(), 1):
        f = line.split("#", 1)[0].split()
        if not f:
            continue
        kind, _, name = f[0].rpartition(":")
        kind = kind or "src"
        if kind not in ("src", "data", "blob", "part"):
            fail(f"{LIST}:{n}: unknown line form '{f[0]}'")
        sel, align = {}, {}
        for tok in f[1:]:
            m = re.fullmatch(r"(align\.)?(data|rodata)=(\S+)", tok)
            if not m or kind not in ("src", "part"):
                fail(f"{LIST}:{n}: bad token '{tok}'")
            if m.group(1):
                align[m.group(2)] = int(m.group(3))
            else:
                sel[m.group(2)] = [] if m.group(3) == "-" else m.group(3).split(",")
        entries.append(dict(kind=kind, name=name, sel=sel, align=align, line=n))
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


def blob_align(name):
    """The largest power of two, at most 16, dividing the blob's own address."""
    a = int(name.split("/")[-1].split(".")[0], 16)
    n = 1
    while n < 16 and a % (n * 2) == 0:
        n *= 2
    return n


def check(entries, rows):
    listed = set()
    for e in entries:
        where = f"{LIST}:{e['line']}"
        if e["kind"] in ("src", "part"):
            if not (ROOT / e["name"]).is_file():
                fail(f"{where}: {e['name']} does not exist")
            if e["kind"] == "src":
                if e["name"] in listed:
                    fail(f"{where}: {e['name']} is listed twice")
                listed.add(e["name"])
        elif e["kind"] == "blob" and not (ROOT / f"asm/data/{e['name']}.s").is_file():
            fail(f"{where}: asm/data/{e['name']}.s does not exist (run tools/build.sh setup)")
        elif e["kind"] == "data" and e["name"] not in rows:
            fail(f"{where}: {e['name']} is not a member in {TABLE}")
    for e in entries:
        if e["kind"] == "part" and e["name"] not in listed:
            fail(f"{LIST}:{e['line']}: part of {e['name']}, which has no line of its own")
    tracked = subprocess.run(["git", "ls-files", "--", "ico2", "sce"], cwd=ROOT,
                             capture_output=True, text=True, check=True).stdout.split()
    missing = [p for p in tracked if p.endswith((".c", ".s", ".S")) and p not in listed]
    if missing:
        fail(f"tracked sources missing from {LIST}:\n  " + "\n  ".join(missing))


def write_labels(out):
    """Transitional: every label splat gave inside a blob no blob: line uses."""
    used = {e["name"] for e in parse_list() if e["kind"] == "blob"}
    lines = []
    for s in sorted((ROOT / "asm/data/cod").glob("*.s")):
        if f"cod/{s.stem}" in used:
            continue
        name = None
        for line in s.read_text().splitlines():
            m = re.match(r"\s*dlabel\s+(\S+)", line)
            if m:
                name = m.group(1)
                continue
            m = re.search(r"/\*((?:\s+[0-9A-F]+)+)\s*\*/", line)
            if name and m:
                g = m.group(1).split()
                lines.append(f"{name} {g[1] if len(g) > 1 else g[0]}")
                name = None
    Path(out).parent.mkdir(parents=True, exist_ok=True)
    Path(out).write_text("\n".join(lines) + "\n")


def objects(e, rows):
    if e["kind"] == "src":
        return [obj_of(e["name"])]
    if e["kind"] == "part":
        return []
    if e["kind"] == "blob":
        return [f"{OUT}/asm/data/{e['name']}.o"]
    return [f"{OUT}/data/{k}.o" for k in rows[e["name"]]]


def inputs_ld(entries, rows, sec):
    """build/plain/<sec>.inputs.ld: the section input by input, or empty when no
    line needs more than the script's wildcard."""
    if not any(sec in e["sel"] or sec in e["align"] for e in entries):
        return ""
    out = []
    for e in entries:
        obj = obj_of(e["name"]) if e["kind"] == "part" else None
        for o in [obj] if obj else objects(e, rows):
            sel = e["sel"].get(sec, LISTED[sec].split())
            if not sel:
                continue
            if sec in e["align"]:
                out.append(f". = ALIGN({e['align'][sec]});")
            out.append(f"*{o}({' '.join(sel)})")
    return "\n".join(out) + "\n"


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
    undefined = [u for u in UNDEFINED if (ROOT / u).exists()]
    blobs = [e for e in entries if e["kind"] == "blob"]
    w = []
    w.append(f"# Generated by tools/gen_ninja_plain.py from {LIST}; do not edit.\n"
             f"ninja_required_version = 1.10\nbuilddir = {OUT}\n"
             "ld = mips-linux-gnu-ld\nobjcopy = mips-linux-gnu-objcopy\npy = .venv/bin/python\n"
             "as_old = tools/period_env.sh tools/cc/ee-gcc2.9-991111/bin/as\n"
             "as_sdk = tools/period_env.sh tools/cc/ee-gcc2.96/bin/as\n"
             "asflags = -EL -mcpu=5900 -mabi=eabi\n\n")
    w.append(f"rule gen\n  command = $py tools/gen_ninja_plain.py\n  generator = 1\n"
             "  description = GEN $out\n\n"
             "rule cc\n  command = tools/compile_c.sh $in $out\n  description = CC $out\n\n")
    for r in ("as_old", "as_sdk"):
        w.append(f"rule {r}\n  command = ${r} $asflags -G $gnum -o $out $in\n  description = AS $out\n\n")
    w.append("rule vu\n  command = $py tools/assemble_vu0.py $in --label $label --out $s"
             " && $as_old $asflags -G 8 -o $out $s\n  description = VU $out\n\n"
             f"rule data\n  command = $py tools/extract_data.py --only $key --out-dir {OUT}/data"
             f" --extra-labels {LABELS} --assemble > /dev/null\n  description = DATA $out\n\n"
             "rule blob\n  command = $as_old $asflags -G 8 -Iinclude -o $out $in"
             " && $objcopy --set-section-alignment $sect=$align $out\n  description = BLOB $out\n\n"
             "rule labels\n  command = $py tools/gen_ninja_plain.py --labels $out\n"
             "  description = LABELS $out\n\n"
             f"rule link\n  command = $ld -EL -T {SCRIPT} {' '.join('-T ' + u for u in undefined)}"
             f" --no-warn-mismatch -z max-page-size=0x1000 -Map {OUT}/ico.pal.map -o $out $in\n  description = LD $out\n\n"
             "rule rom\n  command = $objcopy -O binary --gap-fill=0 $in $out\n  description = ROM $out\n\n"
             f"rule verify\n  command = $py tools/check_elf.py --gate --elf {OUT}/ico.elf"
             f" --map {OUT}/ico.pal.map --rom $in && touch $out\n  description = VERIFY $in\n\n")
    link = []
    for e in entries:
        for o in objects(e, rows):
            link.append(o)
            if e["kind"] == "src" and e["name"].endswith(".c"):
                w.append(f"build {o}: cc {e['name']}\n")
            elif e["kind"] == "src" and e["name"].endswith(".S"):
                stem = Path(e["name"]).stem
                label = "".join(p.title() for p in stem.split("_")) + "MicroProgram"
                w.append(f"build {o}: vu {e['name']} | tools/assemble_vu0.py\n"
                         f"  label = {label}\n  s = {o[:-2]}.s\n")
            elif e["kind"] == "src":
                rule, gnum = archive_as(e["name"])
                w.append(f"build {o}: {rule} {e['name']}\n  gnum = {gnum}\n")
            elif e["kind"] == "blob":
                sect = "." + e["name"].rsplit(".", 1)[1]
                w.append(f"build {o}: blob asm/data/{e['name']}.s\n"
                         f"  sect = {sect}\n  align = {blob_align(e['name'])}\n")
            else:
                key = Path(o).stem
                w.append(f"build {o}: data {TABLE} | tools/extract_data.py {BASE_ELF} {LABELS}\n"
                         f"  key = {key}\n")
    replaced = sorted(str(s.relative_to(ROOT)) for s in (ROOT / "asm/data/cod").glob("*.s")
                      if f"cod/{s.stem}" not in {e["name"] for e in blobs})
    w.append(f"build {LABELS}: labels {' '.join(replaced)} | {LIST} tools/gen_ninja_plain.py\n")
    w.append(f"\nbuild {OUT}/ico.elf: link {' '.join(link)} | {SCRIPT} {' '.join(undefined)}"
             f" {OUT}/data.inputs.ld {OUT}/rodata.inputs.ld\n"
             f"build {OUT}/ico.rom: rom {OUT}/ico.elf\n"
             f"build {OUT}/.verified: verify {OUT}/ico.rom | tools/check_elf.py\n"
             f"default {OUT}/.verified\n"
             f"build {NINJA} {OUT}/data.inputs.ld {OUT}/rodata.inputs.ld: gen | "
             f"tools/gen_ninja_plain.py {LIST} {TABLE}\n")
    (ROOT / NINJA).write_text("".join(w))
    n = {k: sum(e["kind"] == k for e in entries) for k in ("src", "data", "blob", "part")}
    toks = sum(len(e["sel"]) + len(e["align"]) for e in entries)
    print(f"gen_ninja_plain: wrote {NINJA} ({len(link)} objects: {n['src']} sources, "
          f"{n['data']} data members; transitional: {n['blob']} blob, {n['part']} part, {toks} tokens)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
