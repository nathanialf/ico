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
CFLAGS="-S -G 8 -O2 -mips3 -EL -fno-builtin -nostdinc -I${INCLUDE_DIR}"
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
LA_SD_INTERLEAVE_TXT="${ROOT}/config/la_sd_interleave.txt"
EARLY_BODY_SWAP_TXT="${ROOT}/config/early_body_swap.txt"
FCC_NOP_TXT="${ROOT}/config/fcc_nop.txt"
UNFOLD_RA_DELAY_TXT="${ROOT}/config/unfold_ra_delay.txt"
EARLY_EPILOGUE_RESTORE_TXT="${ROOT}/config/early_epilogue_restore.txt"
FILL_BLEZ_DELAY_TXT="${ROOT}/config/fill_blez_delay.txt"
SWAP_ZERO_RET_LD_RA_TXT="${ROOT}/config/swap_zero_ret_ld_ra.txt"
V0_ZERO_IN_BNE_DELAY_TXT="${ROOT}/config/v0_zero_in_bne_delay.txt"

BASE="$(basename "${SRC}" .c)"
S="${OUT%.o}.s"

# Match the Makefile's `^[[:space:]]*<BASE>(<space>|<eol>|#)` pattern.
listed() {
    local txt="$1"
    [ -r "$txt" ] || return 1
    grep -qE "^[[:space:]]*${BASE}([[:space:]]|\$|#)" "$txt"
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

if listed "${NO_TRAILING_NOP_TXT}"; then
    "${PYTHON}" "${ROOT}/tools/postprocess_no_trailing_nop.py" "${S}"
fi
if listed "${SHARED_SP_RESTORE_TXT}"; then
    "${PYTHON}" "${ROOT}/tools/postprocess_shared_sp_restore.py" --sp-only "${S}"
fi
if listed "${SHARED_JR_RESTORE_TXT}"; then
    "${PYTHON}" "${ROOT}/tools/postprocess_shared_sp_restore.py" --jr-and-sp "${S}"
fi
if listed "${LA_SD_INTERLEAVE_TXT}"; then
    "${PYTHON}" "${ROOT}/tools/postprocess_la_sd_interleave.py" "${S}"
fi
if listed "${FCC_NOP_TXT}"; then
    "${PYTHON}" "${ROOT}/tools/postprocess_fcc_nop.py" "${S}"
fi
if listed "${EARLY_BODY_SWAP_TXT}"; then
    "${PYTHON}" "${ROOT}/tools/postprocess_early_body_swap.py" "${S}"
fi
if listed "${UNFOLD_RA_DELAY_TXT}"; then
    "${PYTHON}" "${ROOT}/tools/postprocess_unfold_ra_delay.py" "${S}"
fi
if listed "${EARLY_EPILOGUE_RESTORE_TXT}"; then
    "${PYTHON}" "${ROOT}/tools/postprocess_early_epilogue_restore.py" "${S}"
fi
if listed "${FILL_BLEZ_DELAY_TXT}"; then
    "${PYTHON}" "${ROOT}/tools/postprocess_fill_blez_delay.py" "${S}"
fi
if listed "${SWAP_ZERO_RET_LD_RA_TXT}"; then
    "${PYTHON}" "${ROOT}/tools/postprocess_swap_zero_ret_ld_ra.py" "${S}"
fi
if listed "${V0_ZERO_IN_BNE_DELAY_TXT}"; then
    "${PYTHON}" "${ROOT}/tools/postprocess_v0_zero_in_bne_delay.py" "${S}"
fi
if listed "${SWAP_ADDU_TXT}"; then
    sed -i -E 's/(addu[[:space:]]+\$([0-9]+),)\$([0-9]+),\$\2\b/\1$\2,$\3/g' "${S}"
fi
if listed "${COALESCE_V1_V0_TXT}"; then
    sed -i -E \
        -e '/^[[:space:]]*move[[:space:]]+\$2,\$3[[:space:]]*$/d' \
        -e 's/\$3\b/$2/g' "${S}"
fi
# Always runs — internal config/swap_sw_pair.txt gate, not a per-recipe `if`.
"${PYTHON}" "${ROOT}/tools/postprocess_sw_pair.py" "${S}"

# Always runs — internal config/bne_to_bnel.txt gate (per-function allowlist).
"${PYTHON}" "${ROOT}/tools/postprocess_bne_to_bnel.py" "${S}"

# ee-gcc emits `move $r,$s` for parameter-passing moves. ee-as 2.10
# encodes `move` as `daddu $r,$s,$0` (function code 0x2D); modern gas
# encodes `move` as `or $r,$s,$0` (function code 0x25). Original ELF
# uses daddu encoding. Force daddu explicitly so both assemblers agree.
sed -i -E 's/\bmove[[:space:]]+(\$[0-9a-zA-Z]+),[[:space:]]*(\$[0-9a-zA-Z]+)\b/daddu \1,\2,$0/g' "${S}"

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
