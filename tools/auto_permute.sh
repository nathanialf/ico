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
#   PARALLEL=N        max concurrent permuter processes (default: 2).
#                      Each uses `-j PERMUTER_J` threads.
#                      Default 2×4 = 8 cores, focused on 2 functions
#                      (vs the old 8×1 = 8 cores spread across 8
#                      functions, each starved → slow convergence).
#   PERMUTER_J=N      threads per permuter process (default: 4).
#                      Scales the per-function iteration rate; with the
#                      same total core budget, higher PERMUTER_J × lower
#                      PARALLEL converges closer-to-match seeds faster.
#   ITERATIONS=N      cap total round-robin passes (default: infinite).
#   SKIP_MATCHED=1    skip functions whose yaml entry has already been
#                      flipped to `c` (default: 1; set to 0 to retry).
#   STOP_AT_SCORE=N   advance to next function once permuter has produced
#                      an output with score <= N (default: 25).
#                      Hand-attackable results pull out of the queue
#                      early so the operator can review/promote
#                      manually instead of leaving permuter chewing
#                      on a converged seed for hours.
#   TOUGH_NUTS_DIR=path  override the registry root (default:
#                         <repo>/tough_nuts).
#   RANDOM_ORDER=1    shuffle tough_nuts/<func>/ enumeration each pass.
#                      Default 0: iterate lowest-score first (untried
#                      targets count as score 0 → tried first), so the
#                      cycles go to brand-new and near-miss parked
#                      targets rather than functions already hammered
#                      hard with no improvement.
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
PARALLEL="${PARALLEL:-2}"
STOP_AT_SCORE="${STOP_AT_SCORE:-25}"
RANDOM_ORDER="${RANDOM_ORDER:-0}"
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
# worker finishes. The pid stored here is the *worker subshell* pid;
# each worker is launched via setsid so its PID == its PGID, letting us
# kill the entire descendant tree (permute_run.sh shell, python permuter,
# tee, compile.sh, cc1, mips-as) with a single `kill -TERM -<pgid>`.
declare -A WORKER_NAME=()
CLEANUP_DONE=0

# Recursively SIGTERM then SIGKILL every descendant of the given pid.
# Used as a belt-and-braces fallback alongside pgroup-kill, because some
# children (e.g. python multiprocessing workers) can detach into their
# own session under load.
_kill_tree() {
    local root="$1"
    local sig="${2:-TERM}"
    local pids="$root"
    local frontier="$root"
    while [ -n "${frontier}" ]; do
        local next
        next="$(ps -eo pid,ppid --no-headers 2>/dev/null \
            | awk -v ps="${frontier// /|}" 'BEGIN{n=split(ps,a,"|"); for(i=1;i<=n;i++) p[a[i]]=1} ($2 in p){print $1}' \
            | tr '\n' ' ')"
        [ -z "${next// /}" ] && break
        pids="${pids} ${next}"
        frontier="${next}"
    done
    # shellcheck disable=SC2086
    kill -"${sig}" ${pids} 2>/dev/null || true
}

cleanup_workers() {
    # Idempotent: trap fires on both INT/TERM and EXIT, we only want one pass.
    [ "${CLEANUP_DONE}" = "1" ] && return 0
    CLEANUP_DONE=1
    if [ "${#WORKER_NAME[@]}" -eq 0 ]; then
        return 0
    fi
    log "cleanup: terminating ${#WORKER_NAME[@]} active worker(s)"
    # Phase 1: walk the descendant tree of each worker subshell and
    # SIGTERM everything (the worker shell, its permute_run.sh child, the
    # python permuter grandchild, tee, compile.sh, cc1, mips-as, ...).
    # We can't rely on bash's job control to forward signals because
    # `wait` doesn't propagate, and we can't use pgroups because the
    # workers were spawned with `&` in this script's own pgroup — killing
    # the pgroup would kill ourselves. The recursive walk is the
    # portable, surgical option.
    for pid in "${!WORKER_NAME[@]}"; do
        _kill_tree "${pid}" TERM
    done
    # Give children up to ~3s to exit cleanly so promote_best_into_seed
    # sees the final source.c the permuter wrote.
    local waited=0
    while [ "${waited}" -lt 6 ]; do
        local alive=0
        for pid in "${!WORKER_NAME[@]}"; do
            kill -0 "${pid}" 2>/dev/null && alive=$((alive + 1))
        done
        [ "${alive}" -eq 0 ] && break
        sleep 0.5
        waited=$((waited + 1))
    done
    # Phase 2: SIGKILL anything still alive (descendants too).
    for pid in "${!WORKER_NAME[@]}"; do
        if kill -0 "${pid}" 2>/dev/null; then
            _kill_tree "${pid}" KILL
        fi
    done
    # Reap so we don't leave zombies, then promote whatever the workers
    # managed to write before we killed them.
    for pid in "${!WORKER_NAME[@]}"; do
        wait "${pid}" 2>/dev/null || true
        local name="${WORKER_NAME[$pid]}"
        promote_best_into_seed "${name}" || true
        unset 'WORKER_NAME[$pid]'
    done
    # Phase 3 (belt-and-braces): _kill_tree only walks descendants of the
    # tracked worker subshell PIDs. If a worker spawned a python that
    # detached (e.g. via setsid in some library), or a worker was
    # registered in WORKER_NAME after we cleared it but before we exited,
    # the descendant walk will miss it. Sweep up any survivors that match
    # the auto_permute / permute_run / permuter.py / per-run compile.sh
    # signatures. PROJECT_ROOT-anchored so we don't kill an unrelated
    # permuter run in some other checkout.
    pkill -KILL -f "${PROJECT_ROOT}/tools/permute_run.sh" 2>/dev/null || true
    pkill -KILL -f "${PROJECT_ROOT}/lib/decomp-permuter/permuter.py" 2>/dev/null || true
    pkill -KILL -f "${PROJECT_ROOT}/lib/decomp-permuter/runs/.*/compile\.sh" 2>/dev/null || true
}

on_interrupt() {
    local sig="${1:-INT}"
    log "${sig} received; killing workers and promoting in-flight progress"
    cleanup_workers
    # Re-raise so the caller sees the right exit (130 INT, 143 TERM, 129 HUP).
    trap - INT TERM HUP EXIT
    case "$sig" in
        HUP)  exit 129 ;;
        TERM) exit 143 ;;
        *)    exit 130 ;;
    esac
}
# INT/TERM/HUP must all force an exit (cleanup-then-die), not just run the
# cleanup and let the script keep spawning workers. EXIT is the catch-all
# for normal completion / `set -e` abort / `exit` calls. The HUP handler is
# critical: when the controlling terminal closes, bash delivers SIGHUP and
# the previous `trap cleanup_workers EXIT HUP` fired cleanup but then let
# the script continue, immediately respawning workers and orphaning them.
trap 'on_interrupt INT'  INT
trap 'on_interrupt TERM' TERM
trap 'on_interrupt HUP'  HUP
trap cleanup_workers EXIT

# --- tough_nuts/ enumeration ------------------------------------------------
# Format: each subdir of tough_nuts/ named func_<HEX> is a parked function.
# Anything else (README.md, stray files) is ignored.
#
# Skip marker: if `tough_nuts/<func>/.skip` exists, the function is excluded
# from the iteration. Use this for targets blocked by class-level issues
# (e.g. la-macro 64-bit family) that the permuter can't crack via random
# C mutation — they'd otherwise hold a worker slot indefinitely without
# producing any score improvement. The .skip file's contents (if any) are
# treated as a free-form reason for documentation only.
#
# Default order: lowest existing permuter score first. Functions with no
# permuter run yet (no output-*-* dirs under runs/<func>/) are treated as
# lowest-score (sort key 0) so untried targets get attention first. The
# rationale: functions that have already been hammered hard with no
# improvement are the least likely to crack on the next pass; brand-new
# parked targets and near-miss targets (low score) deserve the cycles.
#
# Tie-breaker is alphabetical, so the order is reproducible. Set
# RANDOM_ORDER=1 to shuffle instead.
read_parked() {
    # Filter out functions with a `.skip` marker before any ordering.
    local raw
    raw="$(find "${TOUGH_NUTS_DIR}" -mindepth 1 -maxdepth 1 -type d \
                -name 'func_*' -printf '%f\n' 2>/dev/null \
            | while IFS= read -r name; do
                [ -f "${TOUGH_NUTS_DIR}/${name}/.skip" ] && continue
                printf '%s\n' "${name}"
              done)"
    if [ "${RANDOM_ORDER}" = "1" ]; then
        printf '%s\n' "${raw}" | shuf
        return
    fi
    # Compute "<best_score>\t<name>" per parked function then sort -k1n -k2.
    # Best score = lowest N in lib/decomp-permuter/runs/<name>/output-N-*/.
    # No output dirs (or no runs/<name>/ at all) => 0 so untried go first.
    while IFS= read -r name; do
        [ -z "${name}" ] && continue
        local runs_dir="${RUNS_DIR}/${name}"
        local best=0
        if [ -d "${runs_dir}" ]; then
            local n
            n="$(find "${runs_dir}" -maxdepth 1 -type d -name 'output-*-*' \
                    -printf '%f\n' 2>/dev/null \
                  | sed -nE 's/^output-([0-9]+)-.*$/\1/p' \
                  | sort -n | head -1)"
            [ -n "${n}" ] && best="${n}"
        fi
        printf '%s\t%s\n' "${best}" "${name}"
    done <<< "${raw}" \
      | sort -k1,1n -k2,2 \
      | cut -f2
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

    # Each worker uses `-j ${PERMUTER_J:-4}` permuter threads.
    # Total concurrent threads ≈ PARALLEL × PERMUTER_J.
    # Default 2×4 = 8 cores, focused on 2 functions at a time (vs the old
    # 8×1 = 8 cores spread across 8 functions, each starved).
    # --best-only writes only improved candidates; --stop-on-zero exits
    # the permuter on a true match.
    local pj="${PERMUTER_J:-4}"
    local extra=(-- --stop-on-zero --best-only -j "${pj}")
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

    # Base-score-0 case: permute_run.sh now writes an output-0-base/
    # dir when the seed already matches (see the matching block in that
    # script). It exits 0 in that case, so we hit the rc==0 branch
    # below — but we also explicitly detect the dir here for robustness
    # (older permute_run.sh, hand-built runs, etc.).
    if [ -d "${out_dir}/output-0-base" ]; then
        log "MATCH: ${name}  (base score = 0; seed already matches)"
        return 0
    fi

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
# Default mode picks 4 lowest-score (untried funcs sort as 0, so they go to
# the low queue too — they're cheap to try and may match on first pass) +
# 4 highest-score per pass. Rationale: focus cycles on the two ends of the
# parked-score distribution rather than uniformly grinding mid-score
# stragglers that aren't moving. As scores improve, the 4-low / 4-high
# selection naturally reseats each pass; "queues converge" when the same
# functions show up at both ends, at which point this is just round-robin.
#
# Override:
#   QUEUE_MODE=split  (default) — 4-low + 4-high, total 8/pass
#   QUEUE_MODE=all    — every parked function (legacy behavior)
QUEUE_LOW="${QUEUE_LOW:-4}"
QUEUE_HIGH="${QUEUE_HIGH:-4}"
QUEUE_MODE="${QUEUE_MODE:-split}"

collect_candidates() {
    local arg="${1:-}"
    if [ -n "${arg}" ]; then
        echo "${arg}"
        return
    fi
    # Filter to undone parked.
    local -a all=()
    local name
    while IFS= read -r name; do
        [ -n "${name}" ] || continue
        if [ "${SKIP_MATCHED}" = "1" ] && already_done "${name}"; then
            continue
        fi
        all+=("${name}")
    done < <(read_parked)

    if [ "${QUEUE_MODE}" = "all" ] || [ "${#all[@]}" -le $((QUEUE_LOW + QUEUE_HIGH)) ]; then
        printf '%s\n' "${all[@]}"
        return
    fi

    # read_parked returns lowest-score first; take first QUEUE_LOW and
    # last QUEUE_HIGH. Interleave so we don't burn the whole low queue
    # before any high-queue work happens.
    local total=${#all[@]}
    local low_end=$((QUEUE_LOW))
    local high_start=$((total - QUEUE_HIGH))
    local i=0 j=0
    while [ "${i}" -lt "${QUEUE_LOW}" ] || [ "${j}" -lt "${QUEUE_HIGH}" ]; do
        if [ "${i}" -lt "${QUEUE_LOW}" ]; then
            printf '%s\n' "${all[${i}]}"
            i=$((i + 1))
        fi
        if [ "${j}" -lt "${QUEUE_HIGH}" ]; then
            printf '%s\n' "${all[$((high_start + j))]}"
            j=$((j + 1))
        fi
    done
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
