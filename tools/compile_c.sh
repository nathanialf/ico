#!/usr/bin/env bash
# tools/compile_c.sh <src.c> <out.o>
#
# Compile one C source for the ICO decomp: ee-gcc → .s →
# postprocessors → regname sed → ee-as (or mips-as fallback) → objcopy.
# Replaces the per-recipe body of the Makefile's $(BUILD_DIR)/src/%.o
# rule so the same path is callable from both Make (Phase 1) and Ninja
# (Phase 2). Running all the steps inside one shell invocation avoids
# the per-line fork overhead that Make imposed on every `.c` file.

set -eu

[ $# -eq 2 ] || { echo "usage: $0 <src.c> <out.o>" >&2; exit 2; }
SRC="$1"
OUT="$2"

ROOT="$(cd "$(dirname "$0")/.." && pwd)"

EEGCC_DIR="${EEGCC_DIR:-${ROOT}/tools/cc/ee-gcc2.9-991111}"
EEGCC_LIB="${EEGCC_DIR}/gcc-lib/ee/2.9-ee-991111-01/"
CC="${EEGCC_DIR}/ee-gcc"

if command -v mips64r5900el-ps2-elf-as >/dev/null 2>&1; then
    MIPS_PREFIX="mips64r5900el-ps2-elf-"
else
    MIPS_PREFIX="mips-linux-gnu-"
fi
AS="${MIPS_PREFIX}as"
OBJCOPY="${MIPS_PREFIX}objcopy"

EE_AS="${ROOT}/tools/cc/ee-gcc2.96/bin/as"
# Period assembler whose delay-slot reorder is LESS aggressive than 2.96: it
# does not hoist a preceding unaligned store (sdl/sdr/...) into a `j <func>`
# tail-call delay slot, matching the original ICO toolchain (verified universal:
# 0 of 783 ROM tail-calls carry an unaligned store in the delay). Selected
# per-TU via config/use_old_as.txt for the rare TU that needs it; the gcc-emitted
# .s is byte-for-byte the same input — only the assembler binary differs.
EE_AS_OLD="${ROOT}/tools/cc/ee-gcc2.9-991111/bin/as"

INCLUDE_DIR="${ROOT}/include"
CFLAGS="-S -G 8 -O2 -mips3 -EL -fno-builtin -nostdinc -fdata-sections -I${INCLUDE_DIR}"
ASFLAGS="-EL -march=r5900 -mabi=eabi -G 8 -no-pad-sections -I${INCLUDE_DIR}"
EE_ASFLAGS="-EL -mcpu=5900 -G 8"

PYTHON="${ROOT}/.venv/bin/python"

EXTRA_CFLAGS_LOOKUP="${ROOT}/tools/extra_cflags.sh"
USE_MODERN_AS_TXT="${ROOT}/config/use_modern_as.txt"
USE_OLD_AS_TXT="${ROOT}/config/use_old_as.txt"

BASE="$(basename "${SRC}" .c)"
# Relative TU path without the .c (e.g. fumi/src/jimaku), with any leading
# ROOT/ prefix stripped — the alternate config key form quick_diff.sh accepts.
REL="${SRC%.c}"; REL="${REL#"${ROOT}/"}"
S="${OUT%.o}.s"

# Match the Makefile's `^[[:space:]]*<KEY>(<space>|<eol>|#)` pattern. KEY may be
# the TU BASENAME (canonical) or the full TU path — both forms are honored here
# and in quick_diff.sh so a single config line agrees across diff and build.
listed() {
    local txt="$1"
    [ -r "$txt" ] || return 1
    grep -qE "^[[:space:]]*(${BASE}|${REL})([[:space:]]|\$|#)" "$txt"
}

# Func-range SCOPING for TU-global postprocesses. A coalesced TU holds many
# funcs; a postprocess added for ONE of them must not rewrite its siblings
# (the func_001E0D50-vs-func_001E44C0 swap_addu collision). Annotate the TU's
# config line with `@func_<hex>` tokens to scope the postprocess to just those
# functions' `.ent`/`.end` blocks; with no @func token it stays whole-file
# (unchanged — e.g. single-func hex entries). See lint_postprocess_collisions.py.
funcs_for() {
    awk -v b="${BASE}" '$1==b{for(i=2;i<=NF;i++){if($i=="#")break;
        if($i ~ /^@func_/){sub(/^@/,"",$i); print $i}}}' "$1"
}
# apply_sed_scoped <sed -E program> [func...] — whole-file if no funcs given.
apply_sed_scoped() {
    local prog="$1"; shift
    if [ $# -eq 0 ]; then sed -i -E "$prog" "${S}"; return; fi
    local f
    for f in "$@"; do
        sed -i -E "/\.ent[[:space:]]+${f}\$/,/\.end[[:space:]]+${f}\$/ ${prog}" "${S}"
    done
}
# run_pp_scoped <config.txt> <tool.py> [tool-args...] — run a python postprocess
# on the whole .s, or (if the TU line names @funcs) on just those funcs' blocks
# via tools/scope_pp.py.
run_pp_scoped() {
    local txt="$1" tool="$2"; shift 2
    local fns; fns="$(funcs_for "$txt" | paste -sd, -)"
    if [ -z "$fns" ]; then
        "${PYTHON}" "${ROOT}/tools/${tool}" "$@" "${S}"
    else
        "${PYTHON}" "${ROOT}/tools/scope_pp.py" "${S}" "${fns}" -- \
            "${PYTHON}" "${ROOT}/tools/${tool}" "$@"
    fi
}

# Replicates Makefile:162 ALIGN_FOR in pure shell — picks the largest
# power-of-two ≤ 8 dividing the hex offset encoded in the .o basename.
# Non-hex basenames (and offset 0) fall through to 8.
align_for() {
    local b="$1" n=0 a=8
    if [[ "$b" =~ ^[0-9A-Fa-f]+$ ]]; then
        n=$((16#$b))
    fi
    while [ "$a" -gt 1 ] && [ "$n" -ne 0 ] && [ $((n % a)) -ne 0 ]; do
        a=$((a / 2))
    done
    printf '%s' "$a"
}
ALIGN="$(align_for "$(basename "${OUT%.o}")")"

mkdir -p "$(dirname "${OUT}")"

EXTRA="$("${EXTRA_CFLAGS_LOOKUP}" "${SRC}" 2>/dev/null || true)"

# shellcheck disable=SC2086
"${CC}" -B "${EEGCC_LIB}" ${CFLAGS} ${EXTRA} -o "${S}" "${SRC}"

# Split each gcc-emitted switch jtbl onto its own .rodata.0x<VMA>
# section so the linker can place multi-jtbl TUs correctly. No-op on
# single-jtbl TUs and on .s files with no `.rdata`/jtbl blocks.
"${PYTHON}" "${ROOT}/tools/postprocess_split_jtbls.py" "${S}"

# Each runs whole-TU unless its config line carries `@func_<hex>` tokens, in
# which case run_pp_scoped limits it to those funcs' .ent/.end blocks — so a
# postprocess added for one func in a coalesced TU can't rewrite its siblings.
# Promote gcc's `#nop` hazard-hint comment after an FCC compare to a real `nop`
# when the following branch sits in a `.set noreorder` block — ee-as 2.96 ignores
# the comment, so the R5900 FCC-update hazard slot would otherwise be unfilled.
# Universal assembler-adaptation (retired postprocess_fcc_nop.py + its allowlist),
# same category as the move→daddu / break sed rewrites below.
awk '
{ ln[NR]=$0 }
END { i=1; while (i<=NR) { print ln[i];
  if (ln[i] ~ /^[ \t]*c\.(lt|le|eq)\.[sd]([ \t]|$)/ && (i+1)<=NR && ln[i+1] ~ /^[ \t]*#nop[ \t]*$/) {
    j=i+2; while (j<=NR && ln[j] ~ /^[ \t]*(#|$)/) j++;
    if (j<=NR && ln[j] ~ /^[ \t]*\.set[ \t]+noreorder([ \t]|$)/) { print "\tnop"; i+=2; continue } }
  i++ } }' "${S}" > "${S}.fcc" && mv "${S}.fcc" "${S}"

# ee-as 2.96 fills a jr/j $31 delay slot with a preceding FP store (s.s/swc1)
# or FP convert (cvt.*), but the R5900 FP→return hazard means the original
# assembler left a nop there (verified universal: 0 ROM funcs have cvt in a jr
# delay). Wrap such a return in .set noreorder + explicit nop. Universal
# assembler-adaptation.
awk '{ ln[NR]=$0 } END { i=1; while (i<=NR) {
  if ((ln[i] ~ /^[ \t]*jr?[ \t]+\$31[ \t]*$/) && i>1 && ln[i-1] ~ /^[ \t]*(s\.s|swc1|cvt\.[swd]\.[swd])[ \t]/) {
    print "\t.set noreorder"; print ln[i]; print "\tnop"; print "\t.set reorder"
  } else print ln[i]; i++ } }' "${S}" > "${S}.jrfp" && mv "${S}.jrfp" "${S}"

# A `j <func>` TAIL CALL with a preceding unaligned store (sdl/sdr/swl/swr): ee-as
# 2.96 and modern-as both hoist that store into the j delay slot, but the original
# assembler left it nop (verified universal: 0 of 783 ROM tail-calls carry an
# unaligned store in the delay — see use_old_as note above). Wrap the tail call in
# .set noreorder + explicit nop so the store stays BEFORE the j and the delay is
# nop — universally and per-FUNCTION (the `.set` pair is local), so it does NOT
# require switching the whole TU to ee-as (which regresses modern-as-matched
# siblings, e.g. fieldCollision). Assembler-parity, byte-correct everywhere.
awk '{ ln[NR]=$0 } END { i=1; while (i<=NR) {
  if ((ln[i] ~ /^[ \t]*j[ \t]+[A-Za-z_.]/) && i>1 && ln[i-1] ~ /^[ \t]*(sdl|sdr|swl|swr)[ \t]/) {
    print "\t.set noreorder"; print ln[i]; print "\tnop"; print "\t.set reorder"
  } else print ln[i]; i++ } }' "${S}" > "${S}.jtc" && mv "${S}.jtc" "${S}"


# ee-gcc emits `move $r,$s` for parameter-passing moves. ee-as 2.10
# encodes `move` as `daddu $r,$s,$0` (function code 0x2D); modern gas
# encodes `move` as `or $r,$s,$0` (function code 0x25). Original ELF
# uses daddu encoding. Force daddu explicitly so both assemblers agree.
sed -i -E 's/\bmove[[:space:]]+(\$[0-9a-zA-Z]+),[[:space:]]*(\$[0-9a-zA-Z]+)\b/daddu \1,\2,$0/g' "${S}"

# ee-gcc emits a single-operand `break 7` for its integer divide-by-zero
# trap. ee-as 2.10 puts that code in the LOW field (break 0,7 → 0x000001cd,
# the original ELF's encoding); modern gas puts a single operand in the HIGH
# field (0x0007000d). Rewrite to the explicit two-operand `break 0,N` so both
# assemblers emit the low-field encoding the ROM uses. (Already-explicit
# `break a,b` from INCLUDE_ASM'd .s has a comma and is left untouched.)
sed -i -E 's/\bbreak[[:space:]]+(0x[0-9a-fA-F]+|[0-9]+)[[:space:]]*$/break 0,\1/' "${S}"

# COP1 cvt.w.s: gas's r5900 (mips3) port — the modern-as fallback used for TUs
# whose INCLUDE_ASM siblings only modern gas can parse — REJECTS the cvt.w.s
# mnemonic, although the EE FPU implements it and the ROM holds the raw COP1
# encoding (splat emits it as `.word 0x46......` on the target side too).
# Rewrite gcc's `cvt.w.s $fD,$fS` to the identical `.word` so either assembler
# emits the exact bytes. Pure assembler parity; a no-op for any TU that never
# emits cvt.w.s, and byte-identical where it does.
"${PYTHON}" - "${S}" <<'PYEOF'
import re, sys
p = sys.argv[1]; s = open(p).read()
def _repl(m):
    fd, fs = int(m.group(1)), int(m.group(2))
    return "\t.word 0x%08X" % (0x46000000 | (fs << 11) | (fd << 6) | 0x24)
s2 = re.sub(r"\tcvt\.w\.s\s+\$f(\d+)\s*,\s*\$f(\d+)\b", _repl, s)
if s2 != s:
    open(p, "w").write(s2)
PYEOF

# ee-as 2.10 only accepts numbered MIPS registers; translate all aliases
# (float regs $f0-$f31 and VU regs $vfN are already accepted as-is).
sed -i -E \
    -e 's/\$zero\b/$0/g'  -e 's/\$at\b/$1/g' \
    -e 's/\$v0\b/$2/g'    -e 's/\$v1\b/$3/g' \
    -e 's/\$a0\b/$4/g'    -e 's/\$a1\b/$5/g' \
    -e 's/\$a2\b/$6/g'    -e 's/\$a3\b/$7/g' \
    -e 's/\$t0\b/$8/g'    -e 's/\$t1\b/$9/g' \
    -e 's/\$t2\b/$10/g'   -e 's/\$t3\b/$11/g' \
    -e 's/\$t4\b/$12/g'   -e 's/\$t5\b/$13/g' \
    -e 's/\$t6\b/$14/g'   -e 's/\$t7\b/$15/g' \
    -e 's/\$s0\b/$16/g'   -e 's/\$s1\b/$17/g' \
    -e 's/\$s2\b/$18/g'   -e 's/\$s3\b/$19/g' \
    -e 's/\$s4\b/$20/g'   -e 's/\$s5\b/$21/g' \
    -e 's/\$s6\b/$22/g'   -e 's/\$s7\b/$23/g' \
    -e 's/\$t8\b/$24/g'   -e 's/\$t9\b/$25/g' \
    -e 's/\$k0\b/$26/g'   -e 's/\$k1\b/$27/g' \
    -e 's/\$gp\b/$28/g'   -e 's/\$sp\b/$29/g' \
    -e 's/\$fp\b/$30/g'   -e 's/\$ra\b/$31/g' \
    "${S}"

# Per-TU assembler selection. Default ee-as is 2.96; a TU listed in
# use_old_as.txt assembles with the less-aggressive 2.9-991111 instead (same
# .s input, different reorder behavior — see EE_AS_OLD above). 2.9-991111 is the
# ROM's contemporary assembler: it leaves a jal/jr delay as `nop` where 2.96 /
# modern-as over-fill it with a preceding store. But it rejects splat's
# `%gp_rel(SYM)($28)` spelling, so a MIXED TU (C + INCLUDE_ASM siblings) is first
# flattened + gp_rel-translated by preprocess_old_as.py (byte-identical GPREL16).
ASM_INPUT="${S}"
SELECTED_EE_AS="${EE_AS}"
if listed "${USE_OLD_AS_TXT}"; then
    SELECTED_EE_AS="${EE_AS_OLD}"
fi
# Flatten INCLUDE_ASM siblings + translate splat's gp_rel spellings to the bare
# gp-addressable form the PERIOD assembler accepts, so the ROM's contemporary
# assembler (ee-as 2.10, or 2.9-991111 for use_old_as) assembles mixed C+asm TUs
# directly instead of silently falling back to modern gas (which mis-encodes
# `la sdata` as daddiu where the ROM has addiu). See decomp/NOTES.md.
if "${PYTHON}" "${ROOT}/tools/preprocess_old_as.py" "${S}" "${S}.pp" 2>/dev/null; then
    ASM_INPUT="${S}.pp"
fi

if listed "${USE_MODERN_AS_TXT}"; then
    # shellcheck disable=SC2086
    "${AS}" ${ASFLAGS} -o "${OUT}" "${S}"
    "${OBJCOPY}" --set-section-alignment ".text=${ALIGN}" "${OUT}"
# shellcheck disable=SC2086
elif "${SELECTED_EE_AS}" ${EE_ASFLAGS} -I"${INCLUDE_DIR}" -o "${OUT}" "${ASM_INPUT}" 2>/dev/null; then
    "${OBJCOPY}" "${OUT}" "${OUT}"
else
    echo "  → consider adding ${BASE} to ${USE_MODERN_AS_TXT}" >&2
    # shellcheck disable=SC2086
    "${AS}" ${ASFLAGS} -o "${OUT}" "${S}"
    "${OBJCOPY}" --set-section-alignment ".text=${ALIGN}" "${OUT}"
fi

# .lit4 pool placement: gas interns inline float literals into an anonymous
# `.lit4` section (flags WAp — note the MIPS-GPREL `p` flag). tools/gen_slinky.py
# can only place a `.lit4` slot at its original VMA when the section name carries
# the VMA (`.lit4.0xVMA`). Rename this TU's pool section per
# config/lit4_pool_slots.txt so the constant lands at its real address.
#
# SINGLE-ENTRY ONLY: `objcopy --rename-section` renames the WHOLE `.lit4` to one
# VMA, which is correct only when the compiler pooled exactly ONE constant for
# this TU (4 bytes). A multi-entry pool needs per-word splitting that PRESERVES
# the WAp/GPREL flag (which `--add-section` cannot set) — the ".lit4/.lit8
# TU-pool migration" task. The guard below HARD-ERRORS on a multi-entry pool so
# a second matched literal can never silently rename to one VMA and corrupt the
# layout (the kind of mismatch ninja would catch only at the final SHA).
LIT4_POOL_TXT="${ROOT}/config/lit4_pool_slots.txt"
if [ -r "${LIT4_POOL_TXT}" ]; then
    LIT4_VMA="$(awk -v b="${BASE}" '$1==b{print $2; exit}' "${LIT4_POOL_TXT}")"
    if [ -n "${LIT4_VMA}" ]; then
        # .lit4 size in bytes from objdump -h (field 3 is the hex size), 0 if absent.
        LIT4_SZ_HEX="$("${MIPS_PREFIX}objdump" -h "${OUT}" 2>/dev/null \
            | awk '$2==".lit4"{print $3; exit}')"
        LIT4_SZ=$(( 16#${LIT4_SZ_HEX:-0} ))
        if [ "${LIT4_SZ}" -eq 4 ]; then
            "${OBJCOPY}" --rename-section ".lit4=.lit4.0x${LIT4_VMA}" "${OUT}"
        elif [ "${LIT4_SZ}" -gt 4 ]; then
            echo "compile_c.sh: ERROR — ${BASE} has a ${LIT4_SZ}-byte .lit4 pool" \
                 "(>1 entry) but lit4_pool_slots.txt lists a single VMA. Multi-entry" \
                 ".lit4 splitting is not yet implemented (see the .lit4/.lit8 TU-pool" \
                 "migration task). Refusing to rename the whole pool to one VMA." >&2
            exit 1
        fi
        # LIT4_SZ == 0: configured TU emitted no pool this build — nothing to rename.
    fi
fi
