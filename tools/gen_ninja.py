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
DEPS_FILE = ROOT / "config" / "ico.us.d"
LDSCRIPT = ROOT / "config" / "ico.us.slinky.ld"
LDSCRIPT_EXTRA = ROOT / "config" / "ico.us.linker_script_extra.ld"
AUTO_FUNCS = ROOT / "config" / "undefined_funcs_auto.us.txt"
AUTO_SYMS = ROOT / "config" / "undefined_syms_auto.us.txt"
EXTRA_SYMS = ROOT / "config" / "undefined_funcs_extra.us.txt"

POSTPROCESS_TXTS = [
    "extra_cflags.txt",
    "use_modern_as.txt",
    "swap_addu_operands.txt",
    "coalesce_v1_v0.txt",
    "no_trailing_nop.txt",
    # swap_addu_to_rt.txt retired 2026-05-21 (inline asm in C)
    "shared_sp_restore.txt",
    "shared_jr_restore.txt",
    "early_body_swap.txt",
    "fcc_nop.txt",
    "unfold_ra_delay.txt",
    "early_epilogue_restore.txt",
    "fill_blez_delay.txt",
]

OUTPUT = ROOT / "build.ninja"

ASM_RE = re.compile(r"^build/asm/(.+)\.o$")
# Source roots that map to repo-root subdirs (matches splat's src_path: .).
# `src/` is the catchall; `ios/`, `sound/`, `isys/` are sibling subsystems
# from the original ICO source layout.
SRC_RE = re.compile(r"^build/((?:src|ios|sound|isys)/.+)\.o$")


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
    """Find data-sidecar `.c` files that splat does NOT list in ico.us.d.

    `tools/migrate_data_per_tu.py` emits per-TU `src/<TU>_data.c` (and
    related) files outside splat's awareness. The linker script picks
    up their `.data.0x*` / `.rodata.0x*` sections via SORT_BY_NAME
    globs, but ld still needs the `.o` listed on the command line, so
    the build graph must build them too. Match Make's `find src -name
    '*.c'` discovery for everything outside the splat manifest.
    """
    extras: list[str] = []
    # Walk every source root the project lays out at repo top-level.
    # `src/` plus the original ICO sibling subsystems `ios/`, `sound/`,
    # `isys/` (relocated out of `src/` to mirror the original tree).
    for root_name in ("src", "ios", "sound", "isys"):
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
    out.write("  command = .venv/bin/python tools/gen_ninja.py\n")
    out.write("  description = GEN build.ninja\n")
    out.write("  generator = 1\n\n")

    out.write("rule as_asm\n")
    out.write(
        "  command = $mips_as $asflags -o $out $in && "
        "$mips_objcopy --set-section-alignment .text=$align $out\n"
    )
    out.write("  description = AS $out\n\n")

    out.write("rule as_hasm\n")
    out.write(
        "  command = $mips_as $asflags -o $out $in && "
        "$mips_objcopy --set-section-alignment .text=$align $out\n"
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
        if rule == "cc_src":
            out.write(f"build {obj}: cc_src {src}\n")
        else:
            out.write(f"build {obj}: {rule} {src}\n  align = {align}\n")
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
        ["--no-check-sections", "--no-warn-mismatch", "-Map", "build/ico.us.map"]
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
