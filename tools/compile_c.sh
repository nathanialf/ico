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

INCLUDE_DIR="${ROOT}/include"
CFLAGS="-S -G 8 -O2 -mips3 -EL -fno-builtin -nostdinc -fdata-sections -I${INCLUDE_DIR}"
ASFLAGS="-EL -march=r5900 -mabi=eabi -G 8 -no-pad-sections -I${INCLUDE_DIR}"
EE_ASFLAGS="-EL -mcpu=5900 -G 8"

PYTHON="${ROOT}/.venv/bin/python"

EXTRA_CFLAGS_LOOKUP="${ROOT}/tools/extra_cflags.sh"
USE_MODERN_AS_TXT="${ROOT}/config/use_modern_as.txt"
SWAP_ADDU_TXT="${ROOT}/config/swap_addu_operands.txt"
COALESCE_V1_V0_TXT="${ROOT}/config/coalesce_v1_v0.txt"
NO_TRAILING_NOP_TXT="${ROOT}/config/no_trailing_nop.txt"
SHARED_SP_RESTORE_TXT="${ROOT}/config/shared_sp_restore.txt"
SHARED_JR_RESTORE_TXT="${ROOT}/config/shared_jr_restore.txt"
EARLY_BODY_SWAP_TXT="${ROOT}/config/early_body_swap.txt"
FCC_NOP_TXT="${ROOT}/config/fcc_nop.txt"
FCC_NOREORDER_TXT="${ROOT}/config/fcc_noreorder.txt"
UNFOLD_RA_DELAY_TXT="${ROOT}/config/unfold_ra_delay.txt"
EARLY_EPILOGUE_RESTORE_TXT="${ROOT}/config/early_epilogue_restore.txt"
FILL_BLEZ_DELAY_TXT="${ROOT}/config/fill_blez_delay.txt"
FILL_BEQ_DELAY_TXT="${ROOT}/config/fill_beq_delay.txt"
V0_ZERO_IN_BNE_DELAY_TXT="${ROOT}/config/v0_zero_in_bne_delay.txt"
MOVE_SW_V0_BEFORE_LDS_TXT="${ROOT}/config/move_sw_v0_before_lds.txt"
LUI_CONST_SWAP_TXT="${ROOT}/config/lui_const_swap.txt"
LUI_LI_PRE_SD_TXT="${ROOT}/config/lui_li_pre_sd.txt"
DUMMY_SP_PROLOGUE_TXT="${ROOT}/config/dummy_sp_prologue.txt"

BASE="$(basename "${SRC}" .c)"
S="${OUT%.o}.s"

# Match the Makefile's `^[[:space:]]*<BASE>(<space>|<eol>|#)` pattern.
listed() {
    local txt="$1"
    [ -r "$txt" ] || return 1
    grep -qE "^[[:space:]]*${BASE}([[:space:]]|\$|#)" "$txt"
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

# Demote `.p2align 3` -> `.p2align 2` for functions listed in
# config/demote_p2align.txt (per-function alternative to -malign-loops=2).
"${PYTHON}" "${ROOT}/tools/postprocess_demote_p2align.py" "${S}"
"${PYTHON}" "${ROOT}/tools/postprocess_0B8720.py" "${S}"

# Each runs whole-TU unless its config line carries `@func_<hex>` tokens, in
# which case run_pp_scoped limits it to those funcs' .ent/.end blocks — so a
# postprocess added for one func in a coalesced TU can't rewrite its siblings.
listed "${NO_TRAILING_NOP_TXT}"      && run_pp_scoped "${NO_TRAILING_NOP_TXT}"      postprocess_no_trailing_nop.py
listed "${SHARED_SP_RESTORE_TXT}"    && run_pp_scoped "${SHARED_SP_RESTORE_TXT}"    postprocess_shared_sp_restore.py --sp-only
listed "${SHARED_JR_RESTORE_TXT}"    && run_pp_scoped "${SHARED_JR_RESTORE_TXT}"    postprocess_shared_sp_restore.py --jr-and-sp
listed "${FCC_NOP_TXT}"              && run_pp_scoped "${FCC_NOP_TXT}"              postprocess_fcc_nop.py
listed "${FCC_NOREORDER_TXT}"        && run_pp_scoped "${FCC_NOREORDER_TXT}"        postprocess_fcc_noreorder.py
listed "${EARLY_BODY_SWAP_TXT}"      && run_pp_scoped "${EARLY_BODY_SWAP_TXT}"      postprocess_early_body_swap.py
listed "${UNFOLD_RA_DELAY_TXT}"      && run_pp_scoped "${UNFOLD_RA_DELAY_TXT}"      postprocess_unfold_ra_delay.py
listed "${EARLY_EPILOGUE_RESTORE_TXT}" && run_pp_scoped "${EARLY_EPILOGUE_RESTORE_TXT}" postprocess_early_epilogue_restore.py
listed "${FILL_BLEZ_DELAY_TXT}"      && run_pp_scoped "${FILL_BLEZ_DELAY_TXT}"      postprocess_fill_blez_delay.py
listed "${FILL_BEQ_DELAY_TXT}"       && run_pp_scoped "${FILL_BEQ_DELAY_TXT}"       postprocess_fill_beq_delay.py
listed "${V0_ZERO_IN_BNE_DELAY_TXT}" && run_pp_scoped "${V0_ZERO_IN_BNE_DELAY_TXT}" postprocess_v0_zero_in_bne_delay.py
listed "${LUI_CONST_SWAP_TXT}"       && run_pp_scoped "${LUI_CONST_SWAP_TXT}"       postprocess_lui_const_swap.py
listed "${MOVE_SW_V0_BEFORE_LDS_TXT}" && run_pp_scoped "${MOVE_SW_V0_BEFORE_LDS_TXT}" postprocess_move_sw_v0_before_lds.py
listed "${LUI_LI_PRE_SD_TXT}"        && run_pp_scoped "${LUI_LI_PRE_SD_TXT}"        postprocess_lui_li_pre_sd.py
if listed "${DUMMY_SP_PROLOGUE_TXT}"; then
    "${PYTHON}" "${ROOT}/tools/postprocess_dummy_sp_prologue.py" "${S}"
fi
if [ "${BASE}" = "0AE420" ]; then
    "${PYTHON}" "${ROOT}/tools/postprocess_0AE420.py" "${S}"
fi
if [ "${BASE}" = "080550" ]; then
    "${PYTHON}" "${ROOT}/tools/postprocess_080550.py" "${S}"
fi
if [ "${BASE}" = "105628" ]; then
    "${PYTHON}" "${ROOT}/tools/postprocess_105628.py" "${S}"
fi

if [ "${BASE}" = "09F530" ]; then
    "${PYTHON}" "${ROOT}/tools/postprocess_09F530.py" "${S}"
fi
if [ "${BASE}" = "lodManager" ]; then
    "${PYTHON}" "${ROOT}/tools/postprocess_0D4BD0.py" "${S}"
fi
if [ "${BASE}" = "adpcm_init" ]; then
    "${PYTHON}" "${ROOT}/tools/postprocess_040048.py" "${S}"
fi
if [ "${BASE}" = "14E4C8" ]; then
    "${PYTHON}" "${ROOT}/tools/postprocess_14E4C8.py" "${S}"
fi
if [ "${BASE}" = "103A10" ]; then
    "${PYTHON}" "${ROOT}/tools/postprocess_103A10.py" "${S}"
fi
if [ "${BASE}" = "0EF9E0" ]; then
    "${PYTHON}" "${ROOT}/tools/postprocess_0EF9E0.py" "${S}"
fi
if [ "${BASE}" = "fightSound" ]; then
    "${PYTHON}" "${ROOT}/tools/postprocess_191F50.py" "${S}"
fi
if [ "${BASE}" = "way_util" ]; then
    "${PYTHON}" "${ROOT}/tools/postprocess_07AC48.py" "${S}"
    "${PYTHON}" "${ROOT}/tools/postprocess_07ACD8.py" "${S}"
fi
if listed "${SWAP_ADDU_TXT}"; then
    # Scoped to the TU line's @func ranges (see funcs_for); whole-file for
    # single-func hex entries. This is what keeps func_001E0D50's swap from
    # touching its sibling func_001E44C0.
    # shellcheck disable=SC2046
    apply_sed_scoped 's/(addu[[:space:]]+\$([0-9]+),)\$([0-9]+),\$\2\b/\1$\2,$\3/g' \
        $(funcs_for "${SWAP_ADDU_TXT}")
fi
if listed "${COALESCE_V1_V0_TXT}"; then
    sed -i -E \
        -e '/^[[:space:]]*move[[:space:]]+\$2,\$3[[:space:]]*$/d' \
        -e 's/\$3\b/$2/g' "${S}"
fi
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

if listed "${USE_MODERN_AS_TXT}"; then
    # shellcheck disable=SC2086
    "${AS}" ${ASFLAGS} -o "${OUT}" "${S}"
    "${OBJCOPY}" --set-section-alignment ".text=${ALIGN}" "${OUT}"
# shellcheck disable=SC2086
elif "${EE_AS}" ${EE_ASFLAGS} -o "${OUT}" "${S}" 2>/dev/null; then
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
