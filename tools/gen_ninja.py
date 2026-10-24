#!/usr/bin/env python3
"""tools/gen_ninja.py: emit build.ninja from config/link_order.<slug>.txt.

Every object from its own source, linked by the hand-written
config/link.<slug>.ld in the one object order of config/link_order.<slug>.txt.
<slug> is the target as tools/ico_version.py detects it (VERSION, or the
first configured one), the base ELF is baserom/<slug>/baseelf.elf, and every
output is under build/<slug>/ (OUT below), ninja's own log and deps included,
so two targets built one after the other each stay incremental. build.ninja
at the root is the manifest of one target at a time: its first line names
the slug, every rule command runs with VERSION set to it, and tools/build.sh
and ./build.sh write it again when the slug asked for is another.

The sources are one tree, ico2/ and sce/, for every target: where targets
differ, the file says so inline in VERSION_<SLUG> blocks, which
compile_c.sh defines (docs/BUILDING.md, "Targets and version blocks"). A
link-order row names the source, and the object is build/<slug>/<row>.o.
Every compile runs in the source's own directory, so the relative paths it
spells (the source argument, ../<prog>/include/x.h, src/x.c.inc,
vusrc/x.dsm) are the ones gcc records.

Rules: cc (tools/compile_c.sh), as (the .s sources, assembler and -G per
archive as compile_c.sh chooses them for C), vucpp and vu (each VU1
microprogram is two files: ico2/vusrc/<stem>.vsm, the program text, which the
period cpp reads from standard input in ico2/ with -Ivusrc, -DVERSION_<SLUG>
and the LN define compile_c.sh gives the C, so the text holds the targets'
version blocks as the C does, and writes to build/<slug>/ico2/vusrc/<stem>.i,
and ico2/vusrc/<stem>.dsm, the DMA tags around `.include "vusrc/<stem>.i"`,
which dvp-as, ps2dev's DVP assembler built by tools/setup.sh under
tools/cc/dvp-as/, assembles from ico2/ on the path vusrc/<stem>.dsm with -I
naming build/<slug>/ico2. The overlay section names dvp-as writes
hash the file and line it is reading: the .dsm path for the first, and the
name cpp gives the text after that, "" for standard input and vusrc/<name>.h
for a shared include. Those names are in the base ELF's .DVP.ovlystrtab, so
the .vsm line of each continuation overlay's first instruction is a datum of
the build, and dvp-as takes it from cpp's line markers: where the targets'
texts hold that instruction at different lines, a `#line LN(...) ""` before
it gives each target its own line (ico2/vusrc/mesh.dsm). -no-abicalls
-mabi=64 leave the ABI bits of e_flags
clear, the one setting the link merges with the game's EABI64 objects;
`overlay-fill=N` on a .dsm line passes --overlay-fill=N, the byte the
constant-address overlay sections carry, and is omitted when absent), the
members config/data_schema.<slug>.txt lists as C (tools/gen_data_c.py: a zero
stand-in per member, a layout link with the stand-ins that fixes every other
address, the member's C written from the base ELF with its pointers named from
that link, compiled by ccdata (compile_c.sh run on it as a game TU, from a
programmer directory, so it reaches every ico2 include directory as the game's
TUs do), checked against the ROM range, and the placeholder
labels inside it bound by a linker assignment), labels (the D_<VMA>
placeholders a tracked source spells inside a data member's row, which
gen_data_c.py binds), link (the period linker, GNU ld 2.10 with
tools/binutils-2.10-ee.patch, built by tools/setup.sh under
tools/cc/binutils-2.10-ee/, writing the IRIX-compatible elf32-littlemips output
the PAL disc's MAIN.MAP names: once to ico.syms.elf, which keeps the symbols,
and once with -s to ico.elf, since the base carries no .symtab or .strtab but
2.10's -s keeps their names in .shstrtab as the base does; ld 2.10 has no
INCLUDE inside a section, so the script it reads is build/<slug>/link.ld,
config/link.<slug>.ld with its INCLUDE lines expanded; the map it writes is
build/<slug>/ico.<slug>.map), stubs (tools/gen_stub_s.py:
build/<slug>/stubs/<stem>.s for each row of config/stubs.<slug>.txt, from
the base ELF, <stem>.lit.s for a row with def literal rows, and the macro's
header build/<slug>/stubs/include_asm.h,
implicit inputs of the object of the TU the row names, which includes the
stub with INCLUDE_ASM and INCLUDE_ASM_LIT; a row's in=<file.c.inc> is an
implicit input of that object too), stubcheck
(gen_stub_s.py --check on the linked ELF, so a stub out of place is named
before the gate), rom, verify (tools/check_elf.py --gate
--require-elf-sha: the allocated sections, the ROM SHA-1 and the whole ELF's
SHA-1).

    tools/build.sh setup && ninja
"""

import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
# The member table's and the schema's one parser each.
from gen_data_c import parse_schema, parse_table  # noqa: E402
from ico_version import (  # noqa: E402
    detect_version, baseelf_path, build_dir, config_path, link_map_path,
)
from check_targets import problems as target_problems  # noqa: E402
# The stub list's one parser (config/stubs.<slug>.txt).
from gen_stub_s import HEADER as STUB_HEADER, LIST as STUB_LIST_PATH, parse_stubs, stub_files  # noqa: E402

VERSION = detect_version(ROOT)


def _rel(p):
    return p.relative_to(ROOT).as_posix()


LIST = _rel(config_path(ROOT, VERSION, "link_order", "txt"))
SCRIPT = _rel(config_path(ROOT, VERSION, "link", "ld"))
TABLE = _rel(config_path(ROOT, VERSION, "data_members", "txt"))
SCHEMA = _rel(config_path(ROOT, VERSION, "data_schema", "txt"))
BASE_ELF = _rel(baseelf_path(ROOT, VERSION))
LINK_MAP = _rel(link_map_path(ROOT, VERSION))
STUB_LIST = _rel(STUB_LIST_PATH)
OUT = _rel(build_dir(ROOT, VERSION))
NINJA = "build.ninja"
LD = "tools/cc/binutils-2.10-ee/bin/ld"
DVP_AS = "tools/cc/dvp-as/bin/dvp-as"
CPP = "tools/cc/ee-gcc2.9-991111/gcc-lib/ee/2.9-ee-991111-01/cpp"
# The LN define tools/compile_c.sh gives the C (VERSION_DEFS there), for the
# `#line LN(...)` of a VU program text; a joining target appends its argument
# in both.
LN_DEF = f'"-DLN(pal,jpn,kor,ntsc,aug6,jun26)={VERSION}"'
LINK_LD = f"{OUT}/link.ld"
# The layout link: the same objects and script with a zero stand-in for each
# member written as C, so the C's pointers can be named before it exists.
LAYOUT_LD = f"{OUT}/layout.ld"
LAYOUT_ELF = f"{OUT}/ico.layout.elf"
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
        fill = 0
        for tok in f[1:]:
            m = re.fullmatch(r"align\.(data|rodata)=(\d+)", tok)
            if m and kind == "src":
                align[m.group(1)] = int(m.group(2))
                continue
            m = re.fullmatch(r"overlay-fill=(\d+)", tok)
            if m and name.endswith(".dsm") and int(m.group(1)) <= 255:
                fill = int(m.group(1))
                continue
            fail(f"{LIST}:{n}: bad token '{tok}'")
        entries.append(dict(kind=kind, name=name, align=align, fill=fill, line=n))
    return entries


def table_members():
    """The members the member table (TABLE) has rows for."""
    return {r["member"] for r in parse_table(ROOT / TABLE)}


def schema_members():
    """The members tools/gen_data_c.py writes as C, with the headers their
    rows name."""
    return {m: " ".join(dict.fromkeys(r["header"] for r in rs))
            for m, rs in parse_schema(ROOT / SCHEMA).items()}


def obj_of(src):
    return f"{OUT}/{src.rsplit('.', 1)[0]}.o"


def archive_as(src):
    """compile_c.sh's per-archive assembler and -G for a source path."""
    if re.match(r"sce/(libc|libm|libgcc)/", src):
        return "as_old", "0"
    if src.startswith("sce/"):
        return "as_sdk", "0"
    return "as_old", "8"


def check(entries, members):
    """The link order's own rows, then the source tree against every
    configured target (tools/check_targets.py): a tracked source must be a
    row of at least one configured target's link order, so a source only
    another target lists is not missing from this one."""
    listed = set()
    for e in entries:
        where = f"{LIST}:{e['line']}"
        if e["kind"] == "src":
            if not (ROOT / e["name"]).is_file():
                fail(f"{where}: {e['name']} does not exist")
            if e["name"] in listed:
                fail(f"{where}: {e['name']} is listed twice")
            listed.add(e["name"])
        elif e["name"] not in members:
            fail(f"{where}: {e['name']} is not a member in {TABLE}")
    bad = target_problems(ROOT)
    if bad:
        fail("the source tree does not fit the configured link orders"
             " (tools/check_targets.py):\n  " + "\n  ".join(bad))


def label_sources():
    """The files write_labels scans: every tracked C, header and assembly
    source."""
    tracked = subprocess.run(["git", "ls-files", "--", "ico2", "sce"], cwd=ROOT,
                             capture_output=True, text=True, check=True).stdout.split()
    return [p for p in tracked if p.endswith((".c", ".h", ".inc", ".s", ".S"))]


def write_labels(out):
    """The address-named labels (D_<VMA>) sources use inside the data
    members. The member table (TABLE) carries the disc map's names and the
    few derived names the C reads a table by; a C or assembly file that reads
    a table at an interior offset, where no map name falls, spells the
    address as the name, and gen_data_c.py --alias binds that label. Only
    names some source spells are written."""
    rows = [(r["lo"], r["hi"], {name for name, _ in r["syms"]}) for r in parse_table(ROOT / TABLE)]
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


def vu_headers():
    """The VU programs' shared includes (ninja does not track cpp's
    includes)."""
    return sorted(p.relative_to(ROOT).as_posix() for p in (ROOT / "ico2/vusrc").glob("*.h"))


def objects(e, layout=False):
    """The objects a line links: a data member is one object (in the layout
    link, its zero stand-in)."""
    if e["kind"] == "src":
        return [obj_of(e["name"])]
    return [f"{OUT}/data/stub/{e['name']}.o" if layout else f"{OUT}/data/{e['name']}.o"]


def inputs_ld(entries, sec, layout=False):
    """build/<slug>/<sec>.inputs.ld: the section input by input, or empty when no
    line needs more than the script's wildcard."""
    if not any(sec in e["align"] for e in entries):
        return ""
    out = []
    for e in entries:
        for o in objects(e, layout):
            if sec in e["align"]:
                out.append(f". = ALIGN({e['align'][sec]});")
            out.append(f"*{o}({LISTED[sec]})")
    return "\n".join(out) + "\n"


def expand_includes(script, swap=None):
    """The linker script (SCRIPT) with each INCLUDE line replaced by the file it names
    (or by the text swap gives for that path): ld 2.10 reads INCLUDE only at
    the top level of a script."""
    out = []
    for line in (ROOT / script).read_text().splitlines(keepends=True):
        m = re.fullmatch(r"(\s*)INCLUDE\s+(\S+)\s*", line)
        if m and swap is not None and m.group(2) in swap:
            out.append(swap[m.group(2)])
        elif m:
            out.append((ROOT / m.group(2)).read_text())
        else:
            out.append(line)
    return "".join(out)


def main():
    if sys.argv[1:2] == ["--labels"]:
        write_labels(sys.argv[2])
        return 0
    entries = parse_list()
    stubs = parse_stubs()
    srcs = {e["name"] for e in entries if e["kind"] == "src"}
    for r in stubs:
        if r["tu"] not in srcs:
            fail(f"{STUB_LIST}:{r['line']}: {r['tu']} is not a source in {LIST}")
    stub_h = f"{OUT}/stubs/{STUB_HEADER}"
    # a literal row shares its function's file; a def row adds <stem>.lit.s
    stub_s = {tu: [stub_h] + [f"{OUT}/stubs/{n}" for n in ns] for tu, ns in stub_files(stubs).items()}
    # a row's in=<file.c.inc>, the file its INCLUDE_ASM line lives in, is
    # read by the TU's compile too (ninja does not track includes)
    stub_src = {}
    for r in stubs:
        if r["src"] != r["tu"] and r["src"] not in stub_src.setdefault(r["tu"], []):
            stub_src[r["tu"]].append(r["src"])
    members = table_members()
    cmembers = schema_members()
    check(entries, members)
    for m in cmembers:
        if m not in members:
            fail(f"{SCHEMA}: {m} is not a member in {TABLE}")
    for m in members:
        if m not in cmembers:
            fail(f"{TABLE}: {m} has no row in {SCHEMA}")
    swap = {}
    for sec in LISTED:
        p = ROOT / OUT / f"{sec}.inputs.ld"
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(inputs_ld(entries, sec))
        swap[f"{OUT}/{sec}.inputs.ld"] = inputs_ld(entries, sec, layout=True)
    (ROOT / LINK_LD).write_text(expand_includes(SCRIPT))
    (ROOT / LAYOUT_LD).write_text(expand_includes(SCRIPT, swap))
    w = []
    # The first line names the slug: tools/build.sh and ./build.sh read it
    # to tell whether this manifest is the target asked for.
    w.append(f"# ico build.ninja for VERSION={VERSION}: generated by tools/gen_ninja.py from {LIST}; do not edit.\n"
             f"ninja_required_version = 1.10\nbuilddir = {OUT}\nversion = {VERSION}\n"
             f"root = {ROOT.as_posix()}\n"
             f"ld = {LD}\ndvp_as = {DVP_AS}\ncpp = {CPP}\nobjcopy = mips-linux-gnu-objcopy\npy = .venv/bin/python\n"
             "as_old = tools/period_env.sh tools/cc/ee-gcc2.9-991111/bin/as\n"
             "as_sdk = tools/period_env.sh tools/cc/ee-gcc2.96/bin/as\n"
             "asflags = -EL -mcpu=5900 -mabi=eabi\n"
             f"ldcmd = $ld -EL --oformat elf32-littlemips -T {LINK_LD} --no-warn-mismatch\n"
             f"ldlayout = $ld -EL --oformat elf32-littlemips -T {LAYOUT_LD} --no-warn-mismatch\n\n")
    # Every command runs with VERSION set to this manifest's slug, so no
    # tool it calls detects another target.
    w.append("rule gen\n  command = VERSION=$version $py tools/gen_ninja.py\n  generator = 1\n"
             "  description = GEN $out\n\n"
             # $in is the row path; compile_c.sh compiles it from its own
             # directory, so __FILE__ and every relative include are spelled
             # as the original build spelled them.
             "rule cc\n  command = VERSION=$version tools/compile_c.sh $in $out\n  description = CC $out\n\n"
             # A data member's generated C is a game TU and compiles as one:
             # compile_c.sh compiles build/<slug>/data/<member>.c from inside
             # a programmer directory (common, which owns
             # typedef.h), so it gets the game's flags, assembler and the
             # relative -I list of every ico2 include directory its headers
             # reach into. No header name repeats across the include
             # directories, so the directory chosen changes no lookup.
             "rule ccdata\n  command = VERSION=$version tools/compile_c.sh $in $out\n"
             "  description = CC $out\n\n")
    for r in ("as_old", "as_sdk"):
        w.append(f"rule {r}\n  command = VERSION=$version ${r} $asflags -G $gnum -o $out $in\n"
                 "  description = AS $out\n\n")
    # vu: $fill is "--overlay-fill=N" for a .dsm line whose token gives a
    # nonzero N and is otherwise unset, so a link order without the token
    # (PAL's, whose overlay byte is 0) assembles with the same command line
    # under both the unpatched dvp-as and the one
    # tools/binutils-dvp-overlay-fill.patch builds. Two dashes: an unpatched
    # dvp-as reads "-overlay-fill=N" as -o "verlay-fill=N", which the later
    # -o overrides, and assembles on with the byte unset; "--overlay-fill"
    # it rejects.
    # The VU rules run in ico2/ (the paths cpp and dvp-as are
    # given, vusrc/<stem>.vsm, -Ivusrc and vusrc/<stem>.dsm, stay relative
    # there); the tools and the outputs are named from $root.
    w.append("rule vucpp\n  command = cd ico2 && VERSION=$version $root/tools/period_env.sh $root/$cpp"
             f" -DVERSION_{VERSION.upper()} {LN_DEF} -Ivusrc < $vsm > $root/$out\n"
             "  description = CPP $out\n\n"
             "rule vu\n  command = cd ico2 && VERSION=$version $root/$dvp_as -no-abicalls -mabi=64 $fill"
             f" -I$root/{OUT}/ico2 -o $root/$out $dsm\n"
             "  description = VU $out\n\n"
             "rule datastub\n  command = VERSION=$version $py tools/gen_data_c.py --stub $member --out $out\n"
             "  description = STUB $out\n  restat = 1\n\n"
             f"rule dataalias\n  command = VERSION=$version $py tools/gen_data_c.py --alias $member --labels {LABELS} --out $out\n"
             "  description = ALIAS $out\n  restat = 1\n\n"
             f"rule datac\n  command = VERSION=$version $py tools/gen_data_c.py --c $member --layout {LAYOUT_ELF} --out $out\n"
             "  description = DATAC $out\n  restat = 1\n\n"
             f"rule datacheck\n  command = VERSION=$version $py tools/gen_data_c.py --check $member --obj $obj"
             f" --layout {LAYOUT_ELF} --out $out\n  description = CHECK $obj\n\n"
             "rule layout\n  command = VERSION=$version $ldlayout -o $out $in\n  description = LD $out\n\n"
             "rule labels\n  command = VERSION=$version $py tools/gen_ninja.py --labels $out\n"
             "  description = LABELS $out\n\n"
             f"rule link\n  command = VERSION=$version $ldcmd -Map {LINK_MAP} -o {OUT}/ico.syms.elf $in"
             f" && VERSION=$version $ldcmd -s -o {OUT}/ico.elf $in\n  description = LD $out\n\n"
             "rule stubs\n  command = VERSION=$version $py tools/gen_stub_s.py\n"
             "  description = STUBS $out\n  restat = 1\n\n"
             f"rule stubcheck\n  command = VERSION=$version $py tools/gen_stub_s.py --check {OUT}/ico.syms.elf > $out\n"
             "  description = CHECK stubs\n\n"
             "rule rom\n  command = VERSION=$version $objcopy -O binary --gap-fill=0 $in $out\n"
             "  description = ROM $out\n\n"
             f"rule verify\n  command = VERSION=$version $py tools/check_elf.py --gate --require-elf-sha --elf {OUT}/ico.elf"
             f" --map {LINK_MAP} --rom $in && touch $out\n  description = VERIFY $in\n\n")
    link = []
    layout = []
    stamps = []
    gen_deps = f"{SCHEMA} {TABLE} tools/gen_data_c.py"
    for e in entries:
        if e["kind"] == "data":
            m = e["name"]
            stub, obj = f"{OUT}/data/stub/{m}.o", f"{OUT}/data/{m}.o"
            src, alias, ok = f"{OUT}/data/{m}.c", f"{OUT}/data/{m}.alias.ld", f"{OUT}/data/{m}.ok"
            w.append(f"build {OUT}/data/stub/{m}.s: datastub | {gen_deps} {cmembers[m]}\n  member = {m}\n"
                     f"build {stub}: as_old {OUT}/data/stub/{m}.s\n  gnum = 8\n"
                     f"build {alias}: dataalias | {LABELS} {gen_deps}\n  member = {m}\n"
                     f"build {src}: datac | {LAYOUT_ELF} {BASE_ELF} {gen_deps} {cmembers[m]}\n  member = {m}\n"
                     f"build {obj}: ccdata {src}\n"
                     f"build {ok}: datacheck | {obj} {LAYOUT_ELF} {BASE_ELF} {gen_deps}\n"
                     f"  member = {m}\n  obj = {obj}\n")
            link.append(obj)
            layout.append(stub)
            stamps.append(ok)
            continue
        for o in objects(e):
            link.append(o)
            layout.append(o)
            if e["name"].endswith(".c"):
                deps = stub_s.get(e["name"], []) + stub_src.get(e["name"], [])
                w.append(f"build {o}: cc {e['name']}{' | ' + ' '.join(deps) if deps else ''}\n")
            elif e["name"].endswith(".dsm"):
                dsm = Path(e["name"]).relative_to("ico2")
                vsm = dsm.with_suffix(".vsm")
                pre = f"{OUT}/ico2/{dsm.with_suffix('.i')}"
                w.append(f"build {pre}: vucpp ico2/{vsm.as_posix()} | {CPP} {' '.join(vu_headers())}\n"
                         f"  vsm = {vsm}\n"
                         f"build {o}: vu {e['name']} | {pre} {DVP_AS}\n"
                         f"  dsm = {dsm}\n")
                if e["fill"]:
                    w.append(f"  fill = --overlay-fill={e['fill']}\n")
            else:
                rule, gnum = archive_as(e["name"])
                w.append(f"build {o}: {rule} {e['name']}\n  gnum = {gnum}\n")
    w.append(f"build {LABELS}: labels {' '.join(label_sources())} | {LIST} {TABLE}"
             " tools/gen_ninja.py\n")
    if stubs:
        outs = [stub_h] + [s for ss in stub_s.values() for s in ss[1:]]
        w.append(f"build {' '.join(outs)}: stubs | {STUB_LIST} {BASE_ELF} tools/gen_stub_s.py\n"
                 f"build {OUT}/stubs.ok: stubcheck {OUT}/ico.syms.elf | {STUB_LIST} tools/gen_stub_s.py\n")
    aliases = [f"{OUT}/data/{m}.alias.ld" for m in cmembers]
    w.append(f"\nbuild {LAYOUT_ELF}: layout {' '.join(layout + aliases)} | {LAYOUT_LD} {LD}\n")
    w.append(f"\nbuild {OUT}/ico.syms.elf {OUT}/ico.elf: link {' '.join(link + aliases)} | {LINK_LD} {LD}"
             f"{''.join(' ' + s for s in stamps)}\n"
             f"build {OUT}/ico.rom: rom {OUT}/ico.elf\n"
             f"build {OUT}/.verified: verify {OUT}/ico.rom | tools/check_elf.py"
             f"{' ' + OUT + '/stubs.ok' if stubs else ''}\n"
             f"default {OUT}/.verified\n"
             f"build {NINJA} {OUT}/data.inputs.ld {OUT}/rodata.inputs.ld {LINK_LD} {LAYOUT_LD}: gen | "
             f"tools/gen_ninja.py tools/gen_data_c.py tools/gen_stub_s.py tools/ico_version.py tools/check_targets.py"
             f" {LIST} {TABLE} {SCHEMA} {SCRIPT}{' ' + STUB_LIST if STUB_LIST_PATH.exists() else ''}\n")
    (ROOT / NINJA).write_text("".join(w))
    n = {k: sum(e["kind"] == k for e in entries) for k in ("src", "data")}
    toks = sum(len(e["align"]) for e in entries)
    print(f"gen_ninja: wrote {NINJA} ({len(link)} objects: {n['src']} sources, "
          f"{n['data']} data members, {toks} align tokens, {len(stubs)} stubs)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
