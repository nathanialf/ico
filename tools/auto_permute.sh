#!/usr/bin/env bash
# auto_permute.sh — parallel permuter pool over tough_nuts/<func>/.
#
# Iterates each function with a `tough_nuts/<func>/` seed directory
# and runs tools/permute_run.sh against it. Up to PARALLEL functions
# are permuted concurrently (default 4), each pinned to `-j 1` so the
# total concurrent thread count equals PARALLEL — i.e. each core
# handles its own function.
#
# **Progress IS preserved across runs**, by promoting the best-scoring
# candidate from each run back into the seed file. Mechanism: the
# permuter writes improved candidates to
#   lib/decomp-permuter/runs/<func>/output-<score>-<n>/source.c
# (lower score = better). After each per-function run, this script picks
# the lowest-score source.c and overwrites the seed with it. The next
# run starts from that improved seed instead of the original. Original
# seeds are preserved in git history — `git diff tough_nuts/<func>/`
# shows the cumulative improvement.
#
# On a match, the matching candidate is left in place; this script does
# NOT auto-promote into src/ or flip the yaml — that's a manual review
# step. Instead, the script prints a clear "MATCH: <func>" line and
# moves on.
#
# Usage:
#   tools/auto_permute.sh             # parallel pool over tough_nuts/*/
#   tools/auto_permute.sh func_X      # only this one (single, not parallel)
#
# Env:
#   PARALLEL=N        max concurrent permuter processes (default: 4).
#                      Each uses `-j 1`, so total cores ≈ PARALLEL.
#   ITERATIONS=N      cap total round-robin passes (default: infinite).
#   SKIP_MATCHED=1    skip functions whose yaml entry has already been
#                      flipped to `c` (default: 1; set to 0 to retry).
#   STOP_AT_SCORE=N   advance to next function once permuter has produced
#                      an output with score <= N (default: 0 = match-only).
#                      A score-50 result is hand-attackable: the wrapper
#                      will kill that function's permuter and move on so
#                      the operator can review/promote the result manually.
#   TOUGH_NUTS_DIR=path  override the registry root (default:
#                         <repo>/tough_nuts).
#   RANDOM_ORDER=1    shuffle tough_nuts/<func>/ enumeration each pass so
#                      concurrent workers spread across different shapes
#                      (default: 1; set to 0 for sorted/reproducible order).
#
# Output:
#   Logs from each per-function run land in
#   lib/decomp-permuter/runs/<func>/permuter.log (overwritten per run).
#   This wrapper writes a top-level activity log to
#   lib/decomp-permuter/auto_permute.log

set -uo pipefail

PROJECT_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
TOUGH_NUTS_DIR="${TOUGH_NUTS_DIR:-${PROJECT_ROOT}/tough_nuts}"
PERMUTE_RUN="${PROJECT_ROOT}/tools/permute_run.sh"
PERMUTER_DIR="${PERMUTER_DIR:-${PROJECT_ROOT}/lib/decomp-permuter}"
RUNS_DIR="${PERMUTER_DIR}/runs"
ACTIVITY_LOG="${PERMUTER_DIR}/auto_permute.log"
YAML_FILE="${YAML_FILE:-${PROJECT_ROOT}/config/ico.us.yaml}"
SKIP_MATCHED="${SKIP_MATCHED:-1}"
ITERATIONS="${ITERATIONS:-0}"   # 0 = infinite
PARALLEL="${PARALLEL:-4}"
STOP_AT_SCORE="${STOP_AT_SCORE:-0}"
RANDOM_ORDER="${RANDOM_ORDER:-1}"
VRAM_BASE_DEC=$((16#100000))

if [ ! -d "${TOUGH_NUTS_DIR}" ]; then
    echo "ERROR: tough_nuts dir not found at ${TOUGH_NUTS_DIR}" >&2
    exit 1
fi
if [ ! -x "${PERMUTE_RUN}" ]; then
    echo "ERROR: permute_run.sh not executable at ${PERMUTE_RUN}" >&2
    exit 1
fi

mkdir -p "$(dirname "${ACTIVITY_LOG}")"

log() {
    local msg="$*"
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] ${msg}" | tee -a "${ACTIVITY_LOG}"
}

# pid -> function name, used to promote/cleanup the right seed when a
# worker finishes.
declare -A WORKER_NAME=()

on_interrupt() {
    log "interrupt received; killing workers and promoting in-flight progress"
    for pid in "${!WORKER_NAME[@]}"; do
        local name="${WORKER_NAME[$pid]}"
        kill -TERM "${pid}" 2>/dev/null || true
        wait "${pid}" 2>/dev/null || true
        promote_best_into_seed "${name}"
    done
    exit 130
}
trap on_interrupt INT TERM

# --- tough_nuts/ enumeration ------------------------------------------------
# Format: each subdir of tough_nuts/ named func_<HEX> is a parked function.
# Anything else (README.md, stray files) is ignored.
read_parked() {
    # RANDOM_ORDER=1 (default): shuffle so concurrent workers don't all
    # hammer the same alphabetical prefix — easier-to-crack functions
    # surface sooner. Set RANDOM_ORDER=0 for sorted/reproducible order.
    local order_cmd=(shuf)
    [ "${RANDOM_ORDER}" = "0" ] && order_cmd=(sort)
    find "${TOUGH_NUTS_DIR}" -mindepth 1 -maxdepth 1 -type d \
        -name 'func_*' -printf '%f\n' 2>/dev/null | "${order_cmd[@]}"
}

# --- file_off helpers -------------------------------------------------------
file_off_hex_of() {
    local name="$1"
    [[ "${name}" =~ ^func_([0-9A-Fa-f]{8})$ ]] || return 1
    local vram_dec=$((16#${BASH_REMATCH[1]}))
    [ "${vram_dec}" -ge "${VRAM_BASE_DEC}" ] || return 1
    printf '%06X\n' $((vram_dec - VRAM_BASE_DEC))
}

# --- seed discovery ---------------------------------------------------------
# Mirrors the search order in permute_run.sh; returns the *first* path
# found, or empty if none. Used by promote_best_into_seed to decide where
# to write the improved source back.
find_seed() {
    local name="$1"
    local file_off_hex
    file_off_hex="$(file_off_hex_of "${name}")" || return 1
    local file_off_lower
    file_off_lower="$(echo "${file_off_hex}" | tr 'A-F' 'a-f')"
    local candidates=(
        "${TOUGH_NUTS_DIR}/${name}/${name}.c"
        "${TOUGH_NUTS_DIR}/${name}/${file_off_hex}.c"
        "${TOUGH_NUTS_DIR}/${name}/${file_off_lower}.c"
        "${PROJECT_ROOT}/src/cod/${file_off_hex}.c"
        "${PROJECT_ROOT}/src/cod/${file_off_lower}.c"
    )
    for c in "${candidates[@]}"; do
        if [ -f "${c}" ]; then
            echo "${c}"
            return 0
        fi
    done
    if [ -d "${TOUGH_NUTS_DIR}/${name}" ]; then
        local first
        first="$(find "${TOUGH_NUTS_DIR}/${name}" -maxdepth 1 -name '*.c' | head -1)"
        if [ -n "${first}" ]; then
            echo "${first}"
            return 0
        fi
    fi
    return 1
}

# --- already-done check -----------------------------------------------------
# A parked function is considered "done" if the yaml has been flipped to
# `c` at its file_off (operator promotion), or the permuter has already
# produced a matching candidate (output-0-* directory).
already_done() {
    local name="$1"
    local file_off_hex
    file_off_hex="$(file_off_hex_of "${name}")" || return 1
    # Yaml line shape:  "      - [0x<FILEOFF>, c,   cod/<FILEOFF>]..."
    if grep -qE "^[[:space:]]*-[[:space:]]*\[0x${file_off_hex},[[:space:]]+c," \
        "${YAML_FILE}" 2>/dev/null; then
        return 0
    fi
    local run_dir="${RUNS_DIR}/${name}"
    if ls -d "${run_dir}"/output-0-* >/dev/null 2>&1; then
        return 0
    fi
    return 1
}

# --- promote best candidate back into seed ----------------------------------
# Permuter writes runs/<name>/output-<score>-<num>/source.c. Pick the
# lowest-score source.c and overwrite the seed file with it.
promote_best_into_seed() {
    local name="$1"
    local seed
    seed="$(find_seed "${name}")" || return 0
    local run_dir="${RUNS_DIR}/${name}"
    [ -d "${run_dir}" ] || return 0
    local best_dir
    best_dir="$(ls -d "${run_dir}"/output-*-* 2>/dev/null | \
        sed -nE 's|.*/output-([0-9]+)-.*|\1 &|p' | \
        sort -n | head -1 | awk '{print $2}')"
    if [ -z "${best_dir}" ] || [ ! -f "${best_dir}/source.c" ]; then
        return 0
    fi
    local best_path="${best_dir}/source.c"
    local best_score
    best_score="$(basename "${best_dir}" | sed -nE 's|^output-([0-9]+)-.*|\1|p')"
    if cmp -s "${best_path}" "${seed}"; then
        log "  best already matches seed for ${name} (score ${best_score})"
        return 0
    fi
    cp "${best_path}" "${seed}"
    log "  promoted best score=${best_score} for ${name} -> ${seed#${PROJECT_ROOT}/}"
}

# --- per-function worker ----------------------------------------------------
worker() {
    local name="$1"

    if ! file_off_hex_of "${name}" >/dev/null; then
        log "skip ${name}: cannot derive file_off (bad name shape)"
        return 1
    fi
    local seed
    if ! seed="$(find_seed "${name}")"; then
        log "skip ${name}: no seed C file under tough_nuts/${name}/ or src/cod/"
        return 1
    fi

    log "  START ${name} (seed=${seed#${PROJECT_ROOT}/})"

    # Each worker gets exactly 1 permuter thread so PARALLEL workers
    # consume PARALLEL cores total. --best-only writes only improved
    # candidates; --stop-on-zero exits the permuter on a true match.
    local extra=(-- --stop-on-zero --best-only -j 1)
    local rc=0
    local out_dir="${RUNS_DIR}/${name}"

    "${PERMUTE_RUN}" "${name}" "${seed}" "${extra[@]}" \
        >>"${ACTIVITY_LOG}" 2>&1 &
    local permuter_pid=$!

    # Optional STOP_AT_SCORE watchdog: poll runs/<name>/ for output-N-*
    # dirs; once any with N <= STOP_AT_SCORE appears, kill THIS permuter
    # only (not siblings).
    local watchdog_pid=""
    if [ "${STOP_AT_SCORE}" -gt 0 ]; then
        (
            while kill -0 "${permuter_pid}" 2>/dev/null; do
                sleep 5
                if ls -d "${out_dir}"/output-*-* 2>/dev/null \
                    | sed -nE 's|.*/output-([0-9]+)-.*|\1|p' \
                    | sort -n | head -1 \
                    | awk -v t="${STOP_AT_SCORE}" '{ exit !($1+0 <= t) }'; then
                    log "    STOP_AT_SCORE: ${name} reached score <= ${STOP_AT_SCORE}, killing permuter"
                    pkill -TERM -P "${permuter_pid}" 2>/dev/null || true
                    kill -TERM "${permuter_pid}" 2>/dev/null || true
                    break
                fi
            done
        ) &
        watchdog_pid=$!
    fi

    wait "${permuter_pid}" || rc=$?
    if [ -n "${watchdog_pid}" ]; then
        kill "${watchdog_pid}" 2>/dev/null || true
        wait "${watchdog_pid}" 2>/dev/null || true
    fi

    promote_best_into_seed "${name}"

    if [ "${rc}" -eq 0 ]; then
        log "MATCH: ${name}"
        return 0
    fi

    if [ "${STOP_AT_SCORE}" -gt 0 ] && [ -d "${out_dir}" ]; then
        local best
        best=$(ls -d "${out_dir}"/output-*-* 2>/dev/null \
            | sed -nE 's|.*/output-([0-9]+)-.*|\1|p' \
            | sort -n | head -1)
        if [ -n "${best}" ] && [ "${best}" -le "${STOP_AT_SCORE}" ]; then
            log "PLATEAU ${name}  (best score=${best}, advancing per STOP_AT_SCORE=${STOP_AT_SCORE})"
            return 0
        fi
    fi

    log "  no-match ${name}  (permuter exit=${rc}; seed updated to best so far)"
    return 1
}

# Reap any finished workers; remove them from WORKER_NAME so the pool
# can refill. Uses kill -0 probe so older bash versions work.
reap_finished() {
    local pid
    for pid in "${!WORKER_NAME[@]}"; do
        if ! kill -0 "${pid}" 2>/dev/null; then
            wait "${pid}" 2>/dev/null || true
            unset 'WORKER_NAME[$pid]'
        fi
    done
}

# --- collect candidates from tough_nuts/ ------------------------------------
collect_candidates() {
    local arg="${1:-}"
    if [ -n "${arg}" ]; then
        echo "${arg}"
        return
    fi
    local name
    while IFS= read -r name; do
        [ -n "${name}" ] || continue
        if [ "${SKIP_MATCHED}" = "1" ] && already_done "${name}"; then
            continue
        fi
        echo "${name}"
    done < <(read_parked)
}

# --- main -------------------------------------------------------------------
PASS=0
EXPLICIT_ARG="${1:-}"

if [ -n "${EXPLICIT_ARG}" ]; then
    # Single-function mode: just run it directly (no pool).
    worker "${EXPLICIT_ARG}" || true
    exit 0
fi

while :; do
    PASS=$((PASS + 1))
    mapfile -t CANDIDATES < <(collect_candidates)
    if [ "${#CANDIDATES[@]}" -eq 0 ]; then
        for pid in "${!WORKER_NAME[@]}"; do wait "${pid}" 2>/dev/null || true; done
        log "no remaining candidates under ${TOUGH_NUTS_DIR} — exiting."
        break
    fi
    log "=== PASS ${PASS} (${#CANDIDATES[@]} remaining, parallel=${PARALLEL}) ==="

    for name in "${CANDIDATES[@]}"; do
        # Wait for a slot to free up before starting next.
        while [ "${#WORKER_NAME[@]}" -ge "${PARALLEL}" ]; do
            wait -n 2>/dev/null || sleep 2
            reap_finished
        done

        # Re-check "already done" — a sibling worker may have just
        # promoted into src/ between when we built CANDIDATES and now.
        if [ "${SKIP_MATCHED}" = "1" ] && already_done "${name}"; then
            log "skip ${name} (already done)"
            continue
        fi

        worker "${name}" &
        local_pid=$!
        WORKER_NAME[${local_pid}]="${name}"
        log "  spawned ${name} as pid=${local_pid} (active=${#WORKER_NAME[@]}/${PARALLEL})"
    done

    # Drain the pool before declaring the pass done.
    while [ "${#WORKER_NAME[@]}" -gt 0 ]; do
        wait -n 2>/dev/null || sleep 2
        reap_finished
    done

    if [ "${ITERATIONS}" -gt 0 ] && [ "${PASS}" -ge "${ITERATIONS}" ]; then
        log "completed ${ITERATIONS} pass(es), exiting."
        break
    fi
done
