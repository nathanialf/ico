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

# Validate function name shape and derive VRAM / file_off.
if ! [[ "${FUNC_NAME}" =~ ^func_([0-9A-Fa-f]{8})$ ]]; then
    echo "ERROR: function name must be func_XXXXXXXX (8 hex digits): ${FUNC_NAME}" >&2
    exit 2
fi
VRAM_HEX="${BASH_REMATCH[1]}"
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
    echo "       Run ./tools/setup.sh (or 'make setup') first." >&2
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
# Prefer per-function .s under asm/matchings/cod/<file_off>/, fall back to
# slicing the function block out of the segment-level asm/cod/<seg>.s.
RUN_DIR="${RUNS_DIR}/${FUNC_NAME}"
mkdir -p "${RUN_DIR}"
TARGET_S="${RUN_DIR}/target.s"

PER_FUNC_S="${PROJECT_ROOT}/asm/matchings/cod/${FILE_OFF_HEX}/${FUNC_NAME}.s"
SEG_S=""
if [ ! -f "${PER_FUNC_S}" ]; then
    # Search asm/cod/*.s for a glabel matching this function name. There
    # should only be one segment that owns it.
    SEG_S="$(grep -rl --include='*.s' -E "^glabel[[:space:]]+${FUNC_NAME}\b" \
             "${PROJECT_ROOT}/asm/cod" 2>/dev/null | head -1 || true)"
    if [ -z "${SEG_S}" ]; then
        echo "ERROR: cannot locate asm for ${FUNC_NAME}." >&2
        echo "       Looked at ${PER_FUNC_S} and asm/cod/*.s." >&2
        echo "       Did 'make setup' run?" >&2
        exit 1
    fi
fi

# Build target.s. Header mirrors tools/quick_diff.sh's wrapping so per-
# function and segment slices assemble to the same bytes.
{
    echo '.include "macro.inc"'
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
        -D'__attribute__(x)=' \
        -D'_Static_assert(x, y)=' \
        -D'GLOBAL_ASM(...)=' \
        -I"${PROJECT_ROOT}/include" \
        "${SEED_C}" -o "${BASE_C}" 2>/dev/null; then
    cpp -P -undef -nostdinc \
        -D'__attribute__(x)=' \
        -D'_Static_assert(x, y)=' \
        -D'GLOBAL_ASM(...)=' \
        -I"${PROJECT_ROOT}/include" \
        "${SEED_C}" -o "${BASE_C}"
fi

# Trim base.c to just the target function (in-place rewrite). If the seed
# already contains exactly one function this is a no-op.
"${PYTHON}" "${PERMUTER_DIR}/strip_other_fns.py" "${BASE_C}" "${FUNC_NAME}" || {
    echo "WARNING: strip_other_fns.py failed; permuter may complain." >&2
}

# --- compile.sh — ee-gcc 2.9-991111 → mips-linux-gnu-as → .o ---------------
COMPILE_SH="${RUN_DIR}/compile.sh"
CFLAGS="${CFLAGS:--S -G 8 -O2 -mips3 -EL -fno-builtin -nostdinc -Iinclude}"
cat > "${COMPILE_SH}" <<EOF
#!/usr/bin/env bash
# Auto-generated by tools/permute_run.sh — do not edit by hand.
# Invoked as: compile.sh <input.c> -o <output.o>
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
"${EEGCC}" -B "${EEGCC_LIB}" ${CFLAGS} \\
    -I"${PROJECT_ROOT}/include" \\
    -o "\${TMP_S}" "\${INPUT}"
"${AS_FOR_QD}" ${ASFLAGS_QD} \\
    -I"${PROJECT_ROOT}/include" \\
    -o "\${OUTPUT}" "\${TMP_S}"
EOF
chmod +x "${COMPILE_SH}"

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
