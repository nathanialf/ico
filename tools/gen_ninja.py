#!/usr/bin/env python3
"""tools/gen_ninja.py — emit build.ninja from the splat-generated manifest.

Replaces the Makefile's `$(shell find ...)` discovery and per-recipe
shell-outs. Reads `config/ico.us.d` (the authoritative .o list in link
order) and writes a `build.ninja` covering:

    asm/%.s          → build/asm/%.o     via mips-as + objcopy
    src/%.s          → build/src/%.o     via mips-as + objcopy
    src/%.c          → build/src/%.o     via tools/compile_c.sh
    $(ALL_OBJS) +ld  → build/ico.elf     via ld -T
    build/ico.elf    → build/ico.rom     via objcopy -O binary
                       build/ico.rom     verified against config/sha1sums.txt

The generator emits one `build build.ninja: gen_ninja ...` edge so Ninja
auto-regenerates the manifest when `config/ico.us.d` (or any of the
postprocess lookup TXTs) changes — the moment someone flips an asm
subsegment to c and re-runs `tools/build.sh setup`, the next `ninja`
picks up the new graph without manual intervention.

The compile rule still calls `tools/compile_c.sh` with 2 args; the
script does its own per-file grep lookups. This is byte-identical to
Make. Pre-baking grep results at generate time is a separate
optimization deferred to a follow-up.
"""

from __future__ import annotations

import os
import re
import shutil
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
# Version slug selects the target's config namespace. `main` (USA retail)
# defaults to 'us'; the `aug6` prototype branch sets VERSION=aug6.
VERSION = os.environ.get("VERSION", "us")
DEPS_FILE = ROOT / "config" / f"ico.{VERSION}.d"
# Both live branches are raw round-trips: link directly against splat's
# one-pass linker script.
# Noncontiguous data blocks are placed by the carved subsegments splat emits
# (no postprocess pass). A hand-written `linker_script_extra.ld` may add
# per-symbol selectors for #include-coalesced TUs. The old slinky.ld
# pipeline lived on the retired `retail` branch (deleted 2026-07-29).
LDSCRIPT = ROOT / "config" / f"ico.{VERSION}.ld"
LDSCRIPT_EXTRA = ROOT / "config" / f"ico.{VERSION}.linker_script_extra.ld"
AUTO_FUNCS = ROOT / "config" / f"undefined_funcs_auto.{VERSION}.txt"
AUTO_SYMS = ROOT / "config" / f"undefined_syms_auto.{VERSION}.txt"
EXTRA_SYMS = ROOT / "config" / f"undefined_funcs_extra.{VERSION}.txt"

POSTPROCESS_TXTS = [
    "extra_cflags.txt",
    # use_modern_as.txt retired 2026-08-05 — the file is gone and no tool reads
    # it. Modern gas fills delay slots ee-as 2.9-991111 leaves bare, so any TU
    # that reached it could read as MATCHED on the assembler's scheduling rather
    # than on source shape (8 functions were falsely matched that way and had to
    # be reverted). See compile_c.sh / decomp/NOTES.md "Assembler".
    "use_old_as.txt",
    "use_as296.txt",
    # no_trailing_nop / shared_sp_restore / shared_jr_restore retired
    # 2026-05-31 (funcs parked to asm).
]

OUTPUT = ROOT / "build.ninja"

ASM_RE = re.compile(r"^build/asm/(.+)\.o$")
# Source roots that map to repo-root subdirs (matches splat's src_path: .).
# retail (us): src/ + ios/ sound/ isys/. The aug6 prototype branch mirrors the
# dev's per-developer module tree (TRFILE: common/ fumi/ sugipon/ seki/ omori/
# script/ ito/, each with src/ and subsystem subdirs).
_SRC_ROOTS = "src|ios|sound|isys|common|fumi|sugipon|seki|omori|script|ito"
SRC_RE = re.compile(rf"^build/((?:{_SRC_ROOTS})/.+)\.o$")


def mips_prefix() -> str:
    if shutil.which("mips64r5900el-ps2-elf-as"):
        return "mips64r5900el-ps2-elf-"
    return "mips-linux-gnu-"


def parse_objs(deps_path: Path) -> list[str]:
    """Pull the `.o` paths out of the splat-generated dependency file.

    Format is a Make rule:
        build/ico.elf: \
            build/asm/cod/000000.o \
            build/src/cod/0000B8.o \
            ...
    """
    objs: list[str] = []
    text = deps_path.read_text()
    after_colon = text.split(":", 1)[1] if ":" in text else text
    for tok in after_colon.replace("\\", " ").split():
        if tok.endswith(".o"):
            objs.append(tok)
    return objs


def discover_sidecar_objs(splat_objs: set[str]) -> list[str]:
    """Find `.c`/`.s` source files that splat does NOT list in ico.<VERSION>.d.

    Any object under a source root that isn't already emitted from the
    splat manifest (e.g. a hand-added TU not yet wired as a subsegment)
    still needs its `.o` listed on the link command line, so the build
    graph must build it too. Match Make's `find src -name '*.c'`
    discovery for everything outside the splat manifest.
    """
    extras: list[str] = []
    # Walk every source root the project lays out at repo top-level.
    # `src/` plus the original ICO sibling subsystems `ios/`, `sound/`,
    # `isys/` (relocated out of `src/` to mirror the original tree).
    for root_name in ("src", "ios", "sound", "isys", "common", "fumi",
                       "sugipon", "seki", "omori", "script", "ito"):
        root_dir = ROOT / root_name
        if not root_dir.is_dir():
            continue
        for ext in ("*.c", "*.s"):
            for path in sorted(root_dir.rglob(ext)):
                obj_path = "build/" + str(path.relative_to(ROOT).with_suffix(".o"))
                if obj_path not in splat_objs:
                    extras.append(obj_path)
    return extras


def align_for(basename: str) -> int:
    """Largest power-of-two ≤ 8 dividing the hex offset, else 8.

    Mirrors Makefile:162 and tools/compile_c.sh::align_for so the
    objcopy --set-section-alignment matches the original recipe.
    """
    stem = basename.split(".", 1)[0]
    if not re.fullmatch(r"[0-9A-Fa-f]+", stem):
        return 8
    n = int(stem, 16)
    if n == 0:
        return 8
    a = 8
    while a > 1 and n % a != 0:
        a //= 2
    return a


# Section names splat can hand a raw blob object. splat's data-blob objects are
# named `<ROMHEX>.<section>.o` (e.g. `174700.data.o`, `453700.rodata.o`); asm
# text blobs and textbin are plain `<ROMHEX>.o`.
_BLOB_SECT_RE = re.compile(r"^[0-9A-Fa-f]+\.(data|rodata|lit4|sdata|sbss|bss)\.o$")


def section_for(basename: str) -> str:
    """The one ALLOC section a splat blob object owns.

    Carve correctness depends on this: `ee-as`/gas apply
    `record_alignment (data_section, 4)` — i.e. a hard 2**4 (16-byte) minimum
    alignment — to the STANDARD sections `.text`/`.data`/`.bss` regardless of
    what the assembly actually contains. A `.data` blob whose resume address is
    only 8-aligned (any carve that does not end on a 16-byte boundary) then gets
    silently padded by `ld` to the next multiple of 16, shifting every following
    byte and blowing the SHA-1 gate. Custom section names (`.rodata`, `.lit4`,
    `.sdata`) escape that default, which is why the jtbl `.rodata` carves always
    round-tripped while the first `.data`/`.bss` carve at a non-16-aligned
    boundary did not. Normalising each blob's alignment down to `align_for()`
    (a divisor of its own ROM address, so never a source of padding) removes
    the whole failure mode. See decomp/carve_ledger.md "Root cause".
    """
    m = _BLOB_SECT_RE.match(basename)
    if m:
        return f".{m.group(1)}"
    return ".text"


def check_ld_carve_globs(ld_path: Path) -> None:
    """Fail loudly on a per-TU/per-section carve glob emitted more than once.

    splat emits one whole-object selector — `build/src/<tu>.o(.data*)` — per
    dot-form carve subsegment. GNU ld assigns each input section to the FIRST
    output statement that matches it, so a TU with TWO disjoint carved runs in
    the SAME section produces two identical globs of which only the first is
    live: every carved section of that TU collapses into the first run's
    address and the link silently mislays the rest. One contiguous carved run
    per (TU, section) is therefore a hard constraint of the one-pass model, and
    this check makes violating it a build error instead of a SHA mismatch.
    """
    if not ld_path.exists():
        return
    seen: dict[tuple[str, str], int] = {}
    dupes: list[str] = []
    for line in ld_path.read_text().splitlines():
        m = re.match(r"\s*(build/\S+\.o)\((\S+?)\);", line)
        if not m:
            continue
        key = (m.group(1), m.group(2))
        seen[key] = seen.get(key, 0) + 1
        if seen[key] == 2:
            dupes.append(f"{key[0]}({key[1]})")
    if dupes:
        raise SystemExit(
            "gen_ninja: duplicate linker-script selector(s) — a TU may hold only "
            "ONE contiguous carved run per section; the 2nd+ run is dead and its "
            "bytes collapse into the 1st run's address:\n  "
            + "\n  ".join(dupes)
            + "\nMerge the runs into one contiguous carve (absorbing any "
            "verified in-between bytes) or leave the later run in the blob."
        )


def source_for(obj_path: str) -> tuple[str, str]:
    """Map `build/<sub>/<stem>.o` to its source `.c` or `.s` and the rule name.

    Returns (source_path, rule_name). Asm objects always use `as_asm`.
    Source objects probe the filesystem: `.c` (cc_src) or `.s` (as_hasm).
    """
    m = ASM_RE.match(obj_path)
    if m:
        return f"asm/{m.group(1)}.s", "as_asm"

    m = SRC_RE.match(obj_path)
    if m:
        # `stem` already includes the source-root prefix (e.g. "src/cod/000110"
        # or "ios/cdvd") since YAML names are repo-root-relative.
        stem = m.group(1)
        c_path = ROOT / f"{stem}.c"
        s_path = ROOT / f"{stem}.s"
        if c_path.exists():
            return f"{stem}.c", "cc_src"
        if s_path.exists():
            return f"{stem}.s", "as_hasm"
        raise SystemExit(
            f"gen_ninja: no source for {obj_path} (looked for {c_path} and {s_path})"
        )

    raise SystemExit(f"gen_ninja: unrecognized object path {obj_path}")


def emit_header(out, prefix: str) -> None:
    out.write("# Auto-generated by tools/gen_ninja.py — do not edit by hand.\n")
    out.write("# Regenerate via `tools/build.sh setup` or by touching one of\n")
    out.write("# the listed regen inputs and running `ninja` again.\n\n")
    out.write("ninja_required_version = 1.10\n\n")
    out.write("root = .\n")
    out.write("builddir = build\n\n")
    out.write(f"mips_as = {prefix}as\n")
    out.write(f"mips_ld = {prefix}ld\n")
    out.write(f"mips_objcopy = {prefix}objcopy\n\n")
    out.write(
        "asflags = -EL -march=r5900 -mabi=eabi -G 8 -no-pad-sections -Iinclude\n\n"
    )


def emit_rules(out) -> None:
    out.write("rule gen_ninja\n")
    # Pin the active VERSION into the self-regen command. Without this the
    # ninja-triggered regen runs gen_ninja.py with no env and falls back to
    # VERSION=us (line 38), rebuilding the manifest for retail and breaking the
    # aug6 build (references asm/src/cod/*.s that don't exist on this branch).
    out.write(f"  command = VERSION={VERSION} .venv/bin/python tools/gen_ninja.py\n")
    out.write("  description = GEN build.ninja\n")
    out.write("  generator = 1\n\n")

    out.write("rule as_asm\n")
    out.write(
        "  command = $mips_as $asflags -o $out $in && "
        "$mips_objcopy $alignflags $out\n"
    )
    out.write("  description = AS $out\n\n")

    out.write("rule as_hasm\n")
    out.write(
        "  command = $mips_as $asflags -o $out $in && "
        "$mips_objcopy $alignflags $out\n"
    )
    out.write("  description = AS $out\n\n")

    out.write("rule cc_src\n")
    out.write("  command = tools/compile_c.sh $in $out\n")
    out.write("  description = CC $out\n\n")

    out.write("rule link\n")
    out.write("  command = $mips_ld $ldflags -o $out $objs\n")
    out.write("  description = LD $out\n\n")

    out.write("rule objcopy_rom\n")
    out.write("  command = $mips_objcopy -O binary --gap-fill=0x00 $in $out\n")
    out.write("  description = OBJCOPY $out\n\n")

    out.write("rule verify_rom\n")
    out.write(
        "  command = .venv/bin/python tools/verify_elf.py "
        "--target $in --name baseelf.rom && touch $out\n"
    )
    out.write("  description = VERIFY $in\n\n")


def emit_edges(out, objs: list[str]) -> None:
    for obj in objs:
        src, rule = source_for(obj)
        align = align_for(Path(obj).name)
        sect = section_for(Path(obj).name)
        if rule == "cc_src":
            out.write(f"build {obj}: cc_src {src}\n")
        else:
            # Own section: aligned to a divisor of its own ROM address (never a
            # source of padding). Every OTHER standard section gas emits is an
            # empty leftover carrying gas's 2**4 default — and ld pads for a
            # zero-size input section just as eagerly as for a real one, so any
            # of them landing at a non-16-aligned spot injects phantom fill.
            # Force those to 1. See section_for()'s docstring.
            flags = " ".join(
                [f"--set-section-alignment {sect}={align}"]
                + [
                    f"--set-section-alignment {s}=1"
                    for s in (".text", ".data", ".bss")
                    if s != sect
                ]
            )
            out.write(f"build {obj}: {rule} {src}\n  alignflags = {flags}\n")
    out.write("\n")


def emit_link(out, objs: list[str]) -> None:
    ld_inputs = [str(LDSCRIPT.relative_to(ROOT))]
    ldflag_parts = ["-EL", "-T", str(LDSCRIPT.relative_to(ROOT))]
    for opt_ld in (LDSCRIPT_EXTRA, AUTO_FUNCS, AUTO_SYMS, EXTRA_SYMS):
        if opt_ld.exists():
            rel = str(opt_ld.relative_to(ROOT))
            ld_inputs.append(rel)
            ldflag_parts.extend(["-T", rel])
    ldflag_parts.extend(
        ["--no-check-sections", "--no-warn-mismatch", "-Map", f"build/ico.{VERSION}.map"]
    )

    objs_line = " ".join(objs)
    deps_line = " ".join(ld_inputs)
    out.write(f"build build/ico.elf: link {objs_line} | {deps_line}\n")
    out.write(f"  ldflags = {' '.join(ldflag_parts)}\n")
    out.write(f"  objs = {objs_line}\n\n")

    out.write("build build/ico.rom: objcopy_rom build/ico.elf\n\n")
    out.write("build build/.verified: verify_rom build/ico.rom\n\n")
    out.write("default build/.verified\n\n")


def emit_regen(out) -> None:
    inputs = ["tools/gen_ninja.py", str(DEPS_FILE.relative_to(ROOT))]
    for txt in POSTPROCESS_TXTS:
        inputs.append(f"config/{txt}")
    inputs_line = " $\n    ".join(inputs)
    out.write(f"build build.ninja: gen_ninja | $\n    {inputs_line}\n\n")


def main() -> int:
    if not DEPS_FILE.exists():
        print(
            f"gen_ninja: {DEPS_FILE} missing — run `tools/build.sh setup` first",
            file=sys.stderr,
        )
        return 1

    check_ld_carve_globs(LDSCRIPT)

    splat_objs = parse_objs(DEPS_FILE)
    if not splat_objs:
        print(f"gen_ninja: no .o entries found in {DEPS_FILE}", file=sys.stderr)
        return 1
    sidecar_objs = discover_sidecar_objs(set(splat_objs))
    all_objs = splat_objs + sidecar_objs

    prefix = mips_prefix()

    with OUTPUT.open("w") as out:
        emit_header(out, prefix)
        emit_rules(out)
        emit_edges(out, all_objs)
        emit_link(out, all_objs)
        emit_regen(out)

    print(
        f"gen_ninja: wrote {OUTPUT.relative_to(ROOT)} "
        f"({len(splat_objs)} splat + {len(sidecar_objs)} sidecar = {len(all_objs)} objects)"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
