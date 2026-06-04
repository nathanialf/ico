#!/usr/bin/env bash
# permute_run.sh — drive decomp-permuter for a single ICO function.
#
# Usage: tools/permute_run.sh <func_name> [seed_c_path] [-- <permuter args>]
# Example: tools/permute_run.sh func_00105278
#          tools/permute_run.sh func_00105278 tough_nuts/func_00105278/func_00105278.c
#          tools/permute_run.sh func_00105278 -- --stop-on-zero --best-only -j 1
#
# What it does:
#   - Resolves the function's seed C file (auto-discovers a .c under
#     tough_nuts/<func>/ if no path is given).
#   - Resolves the per-function asm: prefers
#     asm/matchings/cod/<file_off>/<func>.s (created by splat once the yaml
#     entry is flipped to `c`); falls back to slicing the matching glabel
#     block out of the segment-level asm/cod/<seg>.s.
#   - Sets up lib/decomp-permuter/runs/<func>/ with base.c (preprocessed
#     seed, single function), target.s + target.o (assembled with the
#     project's matching as flags), compile.sh (ee-gcc 2.96 + mips-as,
#     same flag shape as tools/quick_diff.sh), and settings.toml
#     (compiler_type = gcc, func_name set).
#   - Execs lib/decomp-permuter/permuter.py against that run dir. Anything
#     after `--` is forwarded verbatim to permuter.py.
#
# Project conventions reused from tools/quick_diff.sh:
#   - VRAM_BASE = 0x100000 for the cod segment (file_off = vram - 0x100000).
#   - ee-gcc 2.96 lives at tools/cc/ee-gcc2.96/bin/gcc with cc1 under
#     gcc-lib/ee/2.96-ee-001003-1/ (passed via -B).
#   - CFLAGS: -S -G 8 -O2 -g2 -fno-builtin -fno-optimize-sibling-calls
#             -nostdinc -Iinclude  (override with CFLAGS=).
#   - ASFLAGS: -EL -march=r5900 -mabi=eabi -G 8 -no-pad-sections -Iinclude
#             (override with ASFLAGS_QD=).
#   - target.s is wrapped with `.include "macro.inc"` + `.set noreorder`
#     + `.set noat` so the splat per-function form assembles with the same
#     bytes as the segment-level form (see decomp/NOTES.md "Per-function
#     .s vs segment .s").
#
# Exit:
#   0 = permuter found a matching candidate (grep for `found a match` in log)
#   1 = no match (or permuter exited normally with no zero-score result)
#  >1 = setup error (missing seed, missing asm, missing toolchain, etc.)
#
# Intermediates land in lib/decomp-permuter/runs/<func>/ and are gitignored.

set -uo pipefail

# --- Child cleanup trap -----------------------------------------------------
# Without this, if our parent (auto_permute.sh) dies or this script is
# killed mid-run, the python permuter (a grandchild via the `tee` pipe)
# reparents to init and lingers forever — which is exactly the orphan
# leak we hit before. Trap on EXIT/INT/TERM/HUP and SIGTERM every
# descendant we spawned (permuter.py, tee, compile.sh, cc1, mips-as).
_PERMUTE_RUN_CLEANED=0
_permute_run_kill_descendants() {
    local sig="${1:-TERM}"
    # BFS the descendant tree of this script's PID and signal everything.
    local frontier="$$"
    local pids=""
    while [ -n "${frontier// /}" ]; do
        local next
        next="$(ps -eo pid,ppid --no-headers 2>/dev/null \
            | awk -v ps="${frontier// /|}" 'BEGIN{n=split(ps,a,"|"); for(i=1;i<=n;i++) p[a[i]]=1} ($2 in p){print $1}' \
            | tr '\n' ' ')"
        [ -z "${next// /}" ] && break
        pids="${pids} ${next}"
        frontier="${next}"
    done
    # shellcheck disable=SC2086
    [ -n "${pids// /}" ] && kill -"${sig}" ${pids} 2>/dev/null || true
}
_permute_run_cleanup() {
    [ "${_PERMUTE_RUN_CLEANED}" = "1" ] && return 0
    _PERMUTE_RUN_CLEANED=1
    _permute_run_kill_descendants TERM
    # Brief grace period, then SIGKILL stragglers.
    local waited=0
    while [ "${waited}" -lt 4 ]; do
        # If no children remain at all, we're done.
        if ! pgrep -P $$ >/dev/null 2>&1; then
            return 0
        fi
        sleep 0.5
        waited=$((waited + 1))
    done
    _permute_run_kill_descendants KILL
}
trap '_permute_run_cleanup' EXIT HUP
trap '_permute_run_cleanup; trap - INT TERM EXIT; exit 130' INT TERM

if [ "$#" -lt 1 ]; then
    echo "usage: $0 <func_name> [seed_c_path] [-- <permuter args>]" >&2
    exit 2
fi

FUNC_NAME="$1"
shift

# Optional seed path; if next arg isn't `--`, treat it as the seed.
SEED_C=""
if [ "$#" -gt 0 ] && [ "$1" != "--" ]; then
    SEED_C="$1"
    shift
fi

# Forward args after `--` to permuter.py
PERMUTER_EXTRA_ARGS=()
if [ "$#" -gt 0 ] && [ "$1" = "--" ]; then
    shift
    PERMUTER_EXTRA_ARGS=("$@")
fi

# --- Resolve project paths --------------------------------------------------
PROJECT_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
PERMUTER_DIR="${PERMUTER_DIR:-${PROJECT_ROOT}/lib/decomp-permuter}"
RUNS_DIR="${PERMUTER_DIR}/runs"
VENV="${VENV:-${PROJECT_ROOT}/.venv}"
PYTHON="${PYTHON:-${VENV}/bin/python}"

# --- aug6 vs retail layout detection ---------------------------------------
# Retail: func_XXXXXXXX names, asm/matchings/cod/<file_off>/, VRAM from name.
# aug6:   NAMED functions (voBufIncCount, setGIFtag, ...) OR func_XXXXXXXX,
#         asm/aug6/{matchings,nonmatchings}/<module>/<TU>/<name>.s, coalesced
#         TUs, configs keyed on TU basename. Detected by locating the per-
#         function .s under asm/aug6/. When found, AUG6_MODE=1 and the build
#         is delegated to tools/compile_c.sh (byte-identical to the real build).
AUG6_MODE=0
AUG6_S=""
if [ -d "${PROJECT_ROOT}/asm/aug6" ]; then
    AUG6_S="$(find "${PROJECT_ROOT}/asm/aug6/matchings" "${PROJECT_ROOT}/asm/aug6/nonmatchings" \
                   -maxdepth 6 -name "${FUNC_NAME}.s" 2>/dev/null | head -1)"
    [ -n "${AUG6_S}" ] && AUG6_MODE=1
fi

# Validate function name shape (retail only — aug6 allows named functions).
if [ "${AUG6_MODE}" = "0" ] && ! [[ "${FUNC_NAME}" =~ ^func_([0-9A-Fa-f]{8})$ ]]; then
    echo "ERROR: ${FUNC_NAME} not found under asm/aug6/ and is not func_XXXXXXXX." >&2
    echo "       (aug6 named funcs need a per-function .s under asm/aug6/{matchings,nonmatchings}/.)" >&2
    exit 2
fi
# --- Stall gate -------------------------------------------------------------
# The permuter is fired AT a genuine 30-stall, gated by `match_loop next`, not
# by "it feels stuck". If an interactive match_loop state exists for this func
# and it is mid-loop (still improving / stall below the limit, best != 0),
# REFUSE — an improvement you just made reset the counter, so hand-iterate.
# Allowed silently when: no state (offline auto_permute / first run), at a
# plateau (stall >= limit), or PERMUTE_FORCE=1. Set PERMUTE_FORCE=1 to override.
_GATE_STATE="$(cd "$(dirname "$0")/.." && pwd)/build/match_loop/${FUNC_NAME}.json"
if [ "${PERMUTE_FORCE:-0}" != "1" ] && [ -r "${_GATE_STATE}" ]; then
    _GATE_MSG="$("$(cd "$(dirname "$0")/.." && pwd)/.venv/bin/python" - "${_GATE_STATE}" <<'PYG'
import json, sys
LIMIT = 30
try:
    st = json.load(open(sys.argv[1]))
except Exception:
    sys.exit(0)
best, stall = st.get("best"), st.get("stall", 0)
if best in (None, 0):          # never measured, or already matched
    sys.exit(0)
if stall >= LIMIT:             # genuine plateau — permuter is authorized
    sys.exit(0)
print(f"stall={stall}/{LIMIT}, best={best}")
PYG
)"
    if [ -n "${_GATE_MSG}" ]; then
        echo "REFUSING permuter: ${FUNC_NAME} is mid-loop (${_GATE_MSG})." >&2
        echo "  The permuter is gated by 'match_loop next' (fire only at a 30-stall)." >&2
        echo "  An improvement you just made reset the counter — hand-iterate, or run" >&2
        echo "  'tools/match_loop.py next ${FUNC_NAME}' to confirm the verdict." >&2
        echo "  Override (offline batch / deliberate) with PERMUTE_FORCE=1." >&2
        exit 3
    fi
fi

if [ "${AUG6_MODE}" = "1" ]; then
    # aug6: VRAM from the .s address comment ( /* fileoff VRAM bytes */ insn ).
    VRAM_HEX="$(grep -oE '/\* [0-9A-Fa-f]+ ([0-9A-Fa-f]{8}) ' "${AUG6_S}" | head -1 \
                | awk '{print $3}')"
    if [ -z "${VRAM_HEX}" ]; then
        echo "ERROR: could not parse VRAM from ${AUG6_S#${PROJECT_ROOT}/}" >&2
        exit 1
    fi
    # TU path/basename from the .s location: asm/aug6/<kind>/<TU...>/<name>.s
    AUG6_TU_PATH="${AUG6_S#${PROJECT_ROOT}/asm/aug6/matchings/}"
    AUG6_TU_PATH="${AUG6_TU_PATH#${PROJECT_ROOT}/asm/aug6/nonmatchings/}"
    AUG6_TU_PATH="${AUG6_TU_PATH%/${FUNC_NAME}.s}"     # e.g. ito/mpeg/mv_vobuf
    AUG6_TU_BASE="$(basename "${AUG6_TU_PATH}")"        # e.g. mv_vobuf
else
    VRAM_HEX="${BASH_REMATCH[1]}"
fi
VRAM_DEC=$((16#${VRAM_HEX}))
VRAM_BASE_DEC=$((16#100000))
if [ "${VRAM_DEC}" -lt "${VRAM_BASE_DEC}" ]; then
    echo "ERROR: ${FUNC_NAME} has vram 0x${VRAM_HEX} below cod segment base 0x100000" >&2
    exit 2
fi
FILE_OFF_DEC=$((VRAM_DEC - VRAM_BASE_DEC))
FILE_OFF_HEX="$(printf '%06X' "${FILE_OFF_DEC}")"

if [ ! -d "${PERMUTER_DIR}" ]; then
    echo "ERROR: decomp-permuter not found at ${PERMUTER_DIR}." >&2
    echo "       Initialize the submodule, or set PERMUTER_DIR=." >&2
    exit 1
fi
if [ ! -x "${PYTHON}" ]; then
    echo "ERROR: project venv python missing at ${PYTHON}." >&2
    echo "       Run ./tools/setup.sh (or 'tools/build.sh setup') first." >&2
    exit 1
fi

# Permuter requires `toml` (and `pynacl` / `Levenshtein` are optional).
# Check for toml up front so users don't get a confusing ImportError mid-run.
if ! "${PYTHON}" -c 'import toml' >/dev/null 2>&1; then
    cat >&2 <<EOF
ERROR: decomp-permuter requires the 'toml' Python package, missing from ${VENV}.
       Install:
           ${VENV}/bin/pip install pynacl toml Levenshtein
       (pynacl and Levenshtein are optional; toml is required.)
EOF
    exit 1
fi

EEGCC="${EEGCC:-${PROJECT_ROOT}/tools/cc/ee-gcc2.9-991111/ee-gcc}"
EEGCC_LIB="${EEGCC_LIB:-${PROJECT_ROOT}/tools/cc/ee-gcc2.9-991111/gcc-lib/ee/2.9-ee-991111-01/}"
AS_FOR_QD="${AS_FOR_QD:-mips-linux-gnu-as}"

if [ ! -x "${EEGCC}" ]; then
    echo "ERROR: ee-gcc 2.9-991111 not found at ${EEGCC}." >&2
    echo "       Run ./tools/setup.sh to fetch it (or set EEGCC=)." >&2
    exit 1
fi
if ! command -v "${AS_FOR_QD}" >/dev/null 2>&1; then
    echo "ERROR: ${AS_FOR_QD} not on PATH (override with AS_FOR_QD=)." >&2
    exit 1
fi

# --- Resolve seed C file ----------------------------------------------------
# Order of search (when SEED_C empty):
#   1. tough_nuts/<func>/<func>.c           — snap-style naming
#   2. tough_nuts/<func>/<file_off_lower>.c — file_off lowercase (e.g. 005278.c)
#   3. tough_nuts/<func>/<file_off_upper>.c — file_off uppercase
#   4. first *.c found under tough_nuts/<func>/
#   5. src/cod/<file_off>.c                 — already-c'd source (matched
#                                             siblings sharing a TU)
if [ -z "${SEED_C}" ]; then
    file_off_lower="$(echo "${FILE_OFF_HEX}" | tr 'A-F' 'a-f')"
    candidates=(
        "${PROJECT_ROOT}/tough_nuts/${FUNC_NAME}/${FUNC_NAME}.c"
        "${PROJECT_ROOT}/tough_nuts/${FUNC_NAME}/${FILE_OFF_HEX}.c"
        "${PROJECT_ROOT}/tough_nuts/${FUNC_NAME}/${file_off_lower}.c"
        "${PROJECT_ROOT}/src/cod/${FILE_OFF_HEX}.c"
        "${PROJECT_ROOT}/src/cod/${file_off_lower}.c"
    )
    for c in "${candidates[@]}"; do
        if [ -f "${c}" ]; then
            SEED_C="${c}"
            break
        fi
    done
    if [ -z "${SEED_C}" ]; then
        # Fall back to first *.c under tough_nuts/<func>/
        if [ -d "${PROJECT_ROOT}/tough_nuts/${FUNC_NAME}" ]; then
            SEED_C="$(find "${PROJECT_ROOT}/tough_nuts/${FUNC_NAME}" -maxdepth 1 -name '*.c' | head -1)"
        fi
    fi
fi
if [ -z "${SEED_C}" ] || [ ! -f "${SEED_C}" ]; then
    echo "ERROR: no seed C file found for ${FUNC_NAME}." >&2
    echo "       Looked under tough_nuts/${FUNC_NAME}/ and src/cod/${FILE_OFF_HEX}.c." >&2
    echo "       Pass an explicit path as the second argument." >&2
    exit 1
fi

# --- Resolve target asm -----------------------------------------------------
# Search order:
#   1. asm/matchings/cod/<file_off>/<func>.s — splat per-function emit when
#      yaml entry is `c` for a single-function file_off.
#   2. asm/nonmatchings/<TU>/<func>.s — INCLUDE_ASM-style per-function .s
#      shipped under a TU-named directory (e.g. Basic/, set in
#      src/<TU>.c via `INCLUDE_ASM("asm/nonmatchings/<TU>", func_X)`).
#   3. asm/cod/<seg>.s — fall back to slicing the function block out of
#      the segment-level multi-function asm.
RUN_DIR="${RUNS_DIR}/${FUNC_NAME}"
mkdir -p "${RUN_DIR}"
TARGET_S="${RUN_DIR}/target.s"

PER_FUNC_S="${PROJECT_ROOT}/asm/matchings/cod/${FILE_OFF_HEX}/${FUNC_NAME}.s"
SEG_S=""
if [ "${AUG6_MODE}" = "1" ]; then
    # aug6: the per-function .s was already located during detection.
    PER_FUNC_S="${AUG6_S}"
fi
if [ "${AUG6_MODE}" = "0" ] && [ ! -f "${PER_FUNC_S}" ]; then
    # Try INCLUDE_ASM TU dirs: asm/nonmatchings/<TU>/<func>.s and the
    # deeper carved-cod layout asm/nonmatchings/src/cod/<file_off>/<func>.s.
    NONMATCH_S="$(find "${PROJECT_ROOT}/asm/nonmatchings" -maxdepth 5 \
                       -name "${FUNC_NAME}.s" 2>/dev/null | head -1)"
    if [ -n "${NONMATCH_S}" ] && [ -f "${NONMATCH_S}" ]; then
        PER_FUNC_S="${NONMATCH_S}"
    fi
fi
if [ ! -f "${PER_FUNC_S}" ]; then
    # Search asm/cod/*.s for a glabel matching this function name. There
    # should only be one segment that owns it.
    SEG_S="$(grep -rl --include='*.s' -E "^glabel[[:space:]]+${FUNC_NAME}\b" \
             "${PROJECT_ROOT}/asm/cod" 2>/dev/null | head -1 || true)"
    if [ -z "${SEG_S}" ]; then
        echo "ERROR: cannot locate asm for ${FUNC_NAME}." >&2
        echo "       Looked at:" >&2
        echo "         asm/matchings/cod/${FILE_OFF_HEX}/${FUNC_NAME}.s" >&2
        echo "         asm/nonmatchings/*/${FUNC_NAME}.s" >&2
        echo "         asm/cod/*.s (segment-level glabel grep)" >&2
        echo "       Did 'tools/build.sh setup' run?" >&2
        exit 1
    fi
fi

# Build target.s. Header mirrors tools/quick_diff.sh's wrapping so per-
# function and segment slices assemble to the same bytes.
{
    if [ "${AUG6_MODE}" = "1" ]; then
        echo '.include "labels.inc"'
    else
        echo '.include "macro.inc"'
    fi
    echo '.set noreorder'
    echo '.set noat'
    if [ -n "${SEG_S}" ]; then
        # Slice the glabel ... endlabel block out of the segment file.
        awk -v fn="${FUNC_NAME}" '
            $0 ~ ("^glabel[[:space:]]+" fn "([[:space:]]|$)") { in_fn = 1 }
            in_fn { print }
            $0 ~ ("^endlabel[[:space:]]+" fn "([[:space:]]|$)") { in_fn = 0 }
        ' "${SEG_S}"
    else
        cat "${PER_FUNC_S}"
    fi
} > "${TARGET_S}"

# Sanity: confirm we extracted *something*.
if ! grep -qE "^[[:space:]]*glabel[[:space:]]+${FUNC_NAME}([[:space:]]|$)" "${TARGET_S}"; then
    echo "ERROR: failed to extract ${FUNC_NAME} into ${TARGET_S}." >&2
    exit 1
fi

# Rewrite splat's bare-paren `(SYM) /* gp_rel: (SYM) */` to
# `%gp_rel(SYM)($gp)` form. modern gas (mips-linux-gnu-as) under
# `.set noat` rejects the bare-paren macro; ee-as 2.96 accepts it.
# This rewrite is local to the permuter's target.s — we do NOT touch
# the source asm/nonmatchings/ files (they're INCLUDE_ASM'd into src/
# and assembled by ee-as 2.96, which needs the bare-paren form).
sed -i -E 's|\(([A-Za-z_][A-Za-z0-9_]*)\)([[:space:]]*/\*[[:space:]]*gp_rel:[[:space:]]*\(\1\))|%gp_rel(\1)($gp)\2|g' \
    "${TARGET_S}"

# Assemble target.s -> target.o. Same flags as quick_diff.sh's ASFLAGS_QD.
ASFLAGS_QD="${ASFLAGS_QD:--EL -march=r5900 -mabi=eabi -G 8 -no-pad-sections -Iinclude}"
TARGET_O="${RUN_DIR}/target.o"
# shellcheck disable=SC2086
"${AS_FOR_QD}" ${ASFLAGS_QD} -I"${PROJECT_ROOT}/include" \
    -o "${TARGET_O}" "${TARGET_S}"

# --- base.c — preprocess seed, then strip to a single function --------------
BASE_C="${RUN_DIR}/base.c"
# Use ee-gcc as the preprocessor so any compiler-specific predefined
# macros (e.g. __EE__) are honored. Falls back to host cpp if -E fails.
if ! "${EEGCC}" -B "${EEGCC_LIB}" -E -P -nostdinc \
        -DPERMUTER \
        -D'__attribute__(x)=' \
        -D'_Static_assert(x, y)=' \
        -D'GLOBAL_ASM(...)=' \
        -I"${PROJECT_ROOT}/include" \
        -I"${PROJECT_ROOT}/src" \
        "${SEED_C}" -o "${BASE_C}" 2>/dev/null; then
    cpp -P -undef -nostdinc \
        -DPERMUTER \
        -D'__attribute__(x)=' \
        -D'_Static_assert(x, y)=' \
        -D'GLOBAL_ASM(...)=' \
        -I"${PROJECT_ROOT}/include" \
        -I"${PROJECT_ROOT}/src" \
        "${SEED_C}" -o "${BASE_C}"
fi

# Trim base.c to just the target function (in-place rewrite). If the seed
# already contains exactly one function this is a no-op.
"${PYTHON}" "${PERMUTER_DIR}/strip_other_fns.py" "${BASE_C}" "${FUNC_NAME}" || {
    echo "WARNING: strip_other_fns.py failed; permuter may complain." >&2
}

# --- compile.sh — mirrors Makefile $(BUILD_DIR)/src/%.o: rule -------------
# Same toolchain pipeline as the real build:
#   ee-gcc 2.9-991111 + per-file extra_cflags
#   → postprocess scripts (gated by FILE_OFF in *.txt configs)
#   → $sp/$ra/$zero/etc → $29/$31/$0/etc sed translation
#   → ee-as 2.96 (preferred) or mips-linux-gnu-as (use_modern_as.txt /
#     fallback) + objcopy section alignment
# Without these, permuter "score 0" hits can be false positives — the
# permuter compares its output to a target.s that DOES go through the
# postprocess pipeline (see target.s assembly above), so any function
# whose Makefile path includes a postprocess only matches when the
# permuter's compile.sh does the same. (See decomp/NOTES.md for the
# specific patterns each postprocess fixes.)
#
# We bake the FILE_OFF lookup decisions at compile.sh-generation time
# (a function's file_off doesn't change between permuter iterations),
# so the generated script does no per-call greps.
COMPILE_SH="${RUN_DIR}/compile.sh"
CFLAGS="${CFLAGS:--S -G 8 -O2 -mips3 -EL -fno-builtin -nostdinc -Iinclude}"
EE_AS_BIN="${PROJECT_ROOT}/tools/cc/ee-gcc2.96/bin/as"
EE_ASFLAGS="-EL -mcpu=5900 -G 8"
OBJCOPY="${OBJCOPY:-mips-linux-gnu-objcopy}"

if [ "${AUG6_MODE}" = "1" ]; then
    # aug6: delegate the per-iteration build to tools/compile_c.sh so the
    # permuter's candidate bytes are IDENTICAL to the real ninja build — SAME
    # compiler (ee-gcc 2.9-991111) AND same DEFAULT PERIOD ASSEMBLER
    # (ee-gcc2.9-991111/bin/as), NOT the 2.10/"2.96" EE_AS_BIN hardcoded above
    # (that is only the retail/non-aug6 branch). Because it routes through
    # compile_c.sh, the assembler-default fix applies to the permuter
    # automatically — do NOT hardcode an assembler in this aug6 path. Plus the
    # universal awk/sed rewrites (move→daddu, break 0,N, FCC nop, jr-FP nop,
    # split_jtbls). We copy the permuter's mutated
    # base.c to a TU-basename-named file so compile_c.sh's config lookups
    # (which key on basename) match the real build for this TU.
    cat > "${COMPILE_SH}" <<EOF
#!/usr/bin/env bash
# Auto-generated by tools/permute_run.sh (aug6 mode) — delegates to
# tools/compile_c.sh for byte-parity with the real build. TU=${AUG6_TU_BASE}.
set -e
INPUT="\$1"; shift || true
OUTPUT=""
while [ "\$#" -gt 0 ]; do
    case "\$1" in
        -o) OUTPUT="\$2"; shift 2 ;;
        *)  shift ;;
    esac
done
[ -n "\${OUTPUT}" ] || { echo "compile.sh: missing -o" >&2; exit 2; }
# Name the source after the TU so compile_c.sh's basename-keyed config
# lookups (use_old_as.txt / extra_cflags.txt) match the real build. Place it in
# a per-OUTPUT subdir: parallel permuter workers (-j N) share the temp dir, so a
# single shared <TU>.c next to OUTPUT RACES (one worker overwrites another's
# candidate before it compiles → the scored .o is some other candidate → false
# score-0). The unique OUTPUT name keys the dir; the basename stays <TU> so the
# config lookups still match.
SRC_TU_DIR="\${OUTPUT%.o}.srcdir"
mkdir -p "\${SRC_TU_DIR}"
SRC_TU="\${SRC_TU_DIR}/${AUG6_TU_BASE}.c"
cp "\${INPUT}" "\${SRC_TU}"
VERSION=aug6 "${PROJECT_ROOT}/tools/compile_c.sh" "\${SRC_TU}" "\${OUTPUT}"
EOF
    chmod +x "${COMPILE_SH}"
else

# Compute alignment for objcopy (max power-of-2 ≤ 8 dividing FILE_OFF;
# matches Makefile's ALIGN_FOR helper).
align_for_off() {
    local off="$1" a=8
    while [ "$a" -gt 1 ] && [ "$((off % a))" -ne 0 ]; do
        a=$((a / 2))
    done
    echo "$a"
}
ALIGN_FOR="$(align_for_off "${FILE_OFF_DEC}")"

# Look up per-file extra cflags. extra_cflags.sh keys on uppercase
# basename of the .c argument; we hand it a synthetic path so the
# baked-in cflags match what the Makefile's `$(notdir $(basename $<))`
# would produce for src/cod/<FILE_OFF>.c.
EXTRA_CFLAGS_LOOKUP="${PROJECT_ROOT}/tools/extra_cflags.sh"
EXTRA_CFLAGS=""
if [ -x "${EXTRA_CFLAGS_LOOKUP}" ]; then
    EXTRA_CFLAGS="$("${EXTRA_CFLAGS_LOOKUP}" "src/cod/${FILE_OFF_HEX}.c" 2>/dev/null || true)"
fi

# Helper: is FILE_OFF_HEX listed in a config/*.txt file? (Same regex as
# the Makefile rule — first column, comments OK.)
in_config_txt() {
    local path="$1"
    [ -r "${path}" ] || return 1
    grep -qE "^[[:space:]]*${FILE_OFF_HEX}([[:space:]]|$|#)" "${path}"
}

CFG="${PROJECT_ROOT}/config"
PP_FLAGS=""
in_config_txt "${CFG}/no_trailing_nop.txt"     && PP_FLAGS="${PP_FLAGS} no_trailing_nop"
in_config_txt "${CFG}/shared_sp_restore.txt"   && PP_FLAGS="${PP_FLAGS} shared_sp_restore"
in_config_txt "${CFG}/shared_jr_restore.txt"   && PP_FLAGS="${PP_FLAGS} shared_jr_restore"
in_config_txt "${CFG}/early_body_swap.txt"     && PP_FLAGS="${PP_FLAGS} early_body_swap"
in_config_txt "${CFG}/swap_addu_operands.txt"  && PP_FLAGS="${PP_FLAGS} swap_addu"
in_config_txt "${CFG}/coalesce_v1_v0.txt"      && PP_FLAGS="${PP_FLAGS} coalesce_v1_v0"
USE_MODERN_AS=0
in_config_txt "${CFG}/use_modern_as.txt"       && USE_MODERN_AS=1

# Generate compile.sh. Postprocess steps that don't apply to this file
# are simply omitted from the generated script.
{
cat <<EOF
#!/usr/bin/env bash
# Auto-generated by tools/permute_run.sh — mirrors Makefile src/%.o rule.
# FILE_OFF=${FILE_OFF_HEX}  postprocesses=${PP_FLAGS:-(none)}  use_modern_as=${USE_MODERN_AS}
set -e
INPUT="\$1"
shift || true
OUTPUT=""
while [ "\$#" -gt 0 ]; do
    case "\$1" in
        -o) OUTPUT="\$2"; shift 2 ;;
        *)  shift ;;
    esac
done
if [ -z "\${OUTPUT}" ]; then
    echo "compile.sh: missing -o" >&2; exit 2
fi
TMP_S="\$(mktemp --suffix=.s)"
trap 'rm -f "\${TMP_S}"' EXIT

# 1. ee-gcc compile (with per-file extra cflags baked in).
"${EEGCC}" -B "${EEGCC_LIB}" ${CFLAGS} ${EXTRA_CFLAGS} \\
    -I"${PROJECT_ROOT}/include" \\
    -o "\${TMP_S}" "\${INPUT}"

EOF

# 1.5 FCC hazard nop + jr/j-$31 FP-delay nop — inline universal awk rules
#     (these were retired from postprocess_fcc_nop.py into compile_c.sh; mirror
#     them here so the permuter's pipeline matches the real build). Safe to run
#     unconditionally.
cat <<'AWKPP'
awk '
{ ln[NR]=$0 }
END { i=1; while (i<=NR) { print ln[i];
  if (ln[i] ~ /^[ \t]*c\.(lt|le|eq)\.[sd]([ \t]|$)/ && (i+1)<=NR && ln[i+1] ~ /^[ \t]*#nop[ \t]*$/) {
    j=i+2; while (j<=NR && ln[j] ~ /^[ \t]*(#|$)/) j++;
    if (j<=NR && ln[j] ~ /^[ \t]*\.set[ \t]+noreorder([ \t]|$)/) { print "\tnop"; i+=2; continue } }
  i++ } }' "${TMP_S}" > "${TMP_S}.fcc" && mv "${TMP_S}.fcc" "${TMP_S}"
awk '{ ln[NR]=$0 } END { i=1; while (i<=NR) {
  if ((ln[i] ~ /^[ \t]*jr?[ \t]+\$31[ \t]*$/) && i>1 && ln[i-1] ~ /^[ \t]*(s\.s|swc1)[ \t]/) {
    print "\t.set noreorder"; print ln[i]; print "\tnop"; print "\t.set reorder"
  } else print ln[i]; i++ } }' "${TMP_S}" > "${TMP_S}.jrfp" && mv "${TMP_S}.jrfp" "${TMP_S}"
AWKPP

# 2. Postprocess scripts (only the ones that apply to this FILE_OFF).
if [[ " ${PP_FLAGS} " == *" no_trailing_nop "* ]]; then
    echo "${PYTHON} ${PROJECT_ROOT}/tools/postprocess_no_trailing_nop.py \"\${TMP_S}\""
fi
if [[ " ${PP_FLAGS} " == *" shared_sp_restore "* ]]; then
    echo "${PYTHON} ${PROJECT_ROOT}/tools/postprocess_shared_sp_restore.py --sp-only \"\${TMP_S}\""
fi
if [[ " ${PP_FLAGS} " == *" shared_jr_restore "* ]]; then
    echo "${PYTHON} ${PROJECT_ROOT}/tools/postprocess_shared_sp_restore.py --jr-and-sp \"\${TMP_S}\""
fi
if [[ " ${PP_FLAGS} " == *" early_body_swap "* ]]; then
    echo "${PYTHON} ${PROJECT_ROOT}/tools/postprocess_early_body_swap.py \"\${TMP_S}\""
fi
if [[ " ${PP_FLAGS} " == *" swap_addu "* ]]; then
    cat <<'EOF'
sed -i -E 's/(addu[[:space:]]+\$([0-9]+),)\$([0-9]+),\$\2\b/\1$\2,$\3/g' "${TMP_S}"
EOF
fi
if [[ " ${PP_FLAGS} " == *" coalesce_v1_v0 "* ]]; then
    cat <<'EOF'
sed -i -E -e '/^[[:space:]]*move[[:space:]]+\$2,\$3[[:space:]]*$/d' \
          -e 's/\$3\b/$2/g' "${TMP_S}"
EOF
fi
# 3. Reg-name → numbered translation (always applied; ee-as 2.10 needs it).
cat <<'EOF'
sed -i -E -e 's/\$zero\b/$0/g'   -e 's/\$at\b/$1/g'  \
          -e 's/\$v0\b/$2/g'     -e 's/\$v1\b/$3/g'  \
          -e 's/\$a0\b/$4/g'     -e 's/\$a1\b/$5/g'  \
          -e 's/\$a2\b/$6/g'     -e 's/\$a3\b/$7/g'  \
          -e 's/\$t0\b/$8/g'     -e 's/\$t1\b/$9/g'  \
          -e 's/\$t2\b/$10/g'    -e 's/\$t3\b/$11/g' \
          -e 's/\$t4\b/$12/g'    -e 's/\$t5\b/$13/g' \
          -e 's/\$t6\b/$14/g'    -e 's/\$t7\b/$15/g' \
          -e 's/\$s0\b/$16/g'    -e 's/\$s1\b/$17/g' \
          -e 's/\$s2\b/$18/g'    -e 's/\$s3\b/$19/g' \
          -e 's/\$s4\b/$20/g'    -e 's/\$s5\b/$21/g' \
          -e 's/\$s6\b/$22/g'    -e 's/\$s7\b/$23/g' \
          -e 's/\$t8\b/$24/g'    -e 's/\$t9\b/$25/g' \
          -e 's/\$k0\b/$26/g'    -e 's/\$k1\b/$27/g' \
          -e 's/\$gp\b/$28/g'    -e 's/\$sp\b/$29/g' \
          -e 's/\$fp\b/$30/g'    -e 's/\$ra\b/$31/g' \
          "${TMP_S}"
EOF

# 4. Assemble. Same fallback chain as Makefile: USE_MODERN_AS forces
#    mips-linux-gnu-as; otherwise try ee-as 2.96, fall back to modern as
#    on failure (some VU0/MMI / SYSCALL_WRAPPER inputs ee-as rejects).
if [ "${USE_MODERN_AS}" = "1" ]; then
    cat <<EOF
"${AS_FOR_QD}" ${ASFLAGS_QD} -I"${PROJECT_ROOT}/include" \\
    -o "\${OUTPUT}" "\${TMP_S}"
"${OBJCOPY}" --set-section-alignment .text=${ALIGN_FOR} "\${OUTPUT}"
EOF
else
    cat <<EOF
if "${EE_AS_BIN}" ${EE_ASFLAGS} -o "\${OUTPUT}" "\${TMP_S}" 2>/dev/null; then
    "${OBJCOPY}" "\${OUTPUT}" "\${OUTPUT}"
else
    "${AS_FOR_QD}" ${ASFLAGS_QD} -I"${PROJECT_ROOT}/include" \\
        -o "\${OUTPUT}" "\${TMP_S}"
    "${OBJCOPY}" --set-section-alignment .text=${ALIGN_FOR} "\${OUTPUT}"
fi
EOF
fi
} > "${COMPILE_SH}"
chmod +x "${COMPILE_SH}"
fi   # end AUG6_MODE compile.sh branch

# --- settings.toml ----------------------------------------------------------
# compiler_type = gcc — the closest match in default_weights.toml for ee-gcc
# 2.96. Adjust via tools/gen_permuter_settings.py if a finer-grained set of
# weights is needed later.
cat > "${RUN_DIR}/settings.toml" <<EOF
compiler_type = "gcc"
func_name = "${FUNC_NAME}"
EOF

echo "[permute_run.sh] run dir:   ${RUN_DIR}"
echo "[permute_run.sh] func:      ${FUNC_NAME}  (vram=0x${VRAM_HEX}, file_off=0x${FILE_OFF_HEX})"
echo "[permute_run.sh] seed:      ${SEED_C#${PROJECT_ROOT}/}"
if [ -n "${SEG_S}" ]; then
    echo "[permute_run.sh] target.s:  sliced from ${SEG_S#${PROJECT_ROOT}/}"
else
    echo "[permute_run.sh] target.s:  ${PER_FUNC_S#${PROJECT_ROOT}/}"
fi
echo "[permute_run.sh] target.s:  $(wc -l < "${TARGET_S}") lines"
echo "[permute_run.sh] base.c:    $(wc -l < "${BASE_C}") lines"

# --- Invoke permuter --------------------------------------------------------
# Run the permuter backgrounded with `tee` as a separate process so this
# shell can keep handling signals. A foreground pipeline blocks SIGTERM
# delivery until the pipeline completes — which is what produced the
# orphan flood we just cleaned up: when auto_permute.sh tried to kill
# its workers, this shell was stuck inside `python | tee` and never ran
# its EXIT trap until the python process voluntarily returned.
LOG="${RUN_DIR}/permuter.log"
set +e
( cd "${RUN_DIR}" && \
    "${PYTHON}" "${PERMUTER_DIR}/permuter.py" \
        "${RUN_DIR}" \
        "${PERMUTER_EXTRA_ARGS[@]}" 2>&1 ) | tee "${LOG}" &
PIPELINE_PID=$!
# `wait $!` returns immediately if the trap interrupts it; we re-enter
# the wait until the pipeline truly exits so RC reflects the real exit.
while ! wait "${PIPELINE_PID}" 2>/dev/null; do
    # If the process is gone, break out — wait failed because it's reaped.
    kill -0 "${PIPELINE_PID}" 2>/dev/null || break
done
RC=$?
set -e

# Permuter prints "found a match" on a zero-score hit; it's the only
# reliable signal across exit codes.
if grep -qE 'found a match' "${LOG}"; then
    echo
    echo "MATCH: found a permutation that matches ${FUNC_NAME}."
    if [ -d "${RUN_DIR}/output" ]; then
        echo "Matching candidates: ${RUN_DIR}/output/"
        ls -1 "${RUN_DIR}/output" | head -10
    fi
    exit 0
fi

# Base-score-0 detection: with --best-only, the permuter never writes
# an output-*-* dir when the seed already matches (no improvement is
# possible), and on --stop-on-zero it then exits non-zero. Synthesize
# an output-0-base/ dir so callers (auto_permute.sh, dashboards) treat
# the seed as a confirmed match instead of perpetually re-queuing it
# with "no-match" every pass.
if grep -qE '\[.*\] base score = 0' "${LOG}"; then
    BASE0_DIR="${RUN_DIR}/output-0-base"
    if [ ! -d "${BASE0_DIR}" ]; then
        mkdir -p "${BASE0_DIR}"
        cp "${SEED_C}" "${BASE0_DIR}/source.c"
        printf '0\n' > "${BASE0_DIR}/score.txt"
    fi
    echo
    echo "MATCH: ${FUNC_NAME} base score = 0 (seed already matches)."
    exit 0
fi

echo
echo "no permutation matched (permuter exit=${RC})"
exit 1
