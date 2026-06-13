#!/usr/bin/env bash
# tools/sweep_stop.sh — end the decomp-sweep keep-going loop (user-authorized).
#
# The sweep_stop_guard.py Stop-hook blocks turn-end while a sweep is armed
# (.claude/.decomp_sweep_active) and non-SPILL targets remain. This is the ONE
# sanctioned end: it drops the stop marker the hook honors and clears the arm +
# guard, so the next turn-end is allowed. (The hook also auto-frees after its
# no-progress CAP, so this is a manual early-out, not the only escape.)
set -u
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
touch "${ROOT}/.claude/.decomp_sweep_stop"
rm -f "${ROOT}/.claude/.decomp_sweep_active" "${ROOT}/.claude/.decomp_sweep_guard"
echo "decomp-sweep: stop requested — the keep-going hook will release on the next turn-end."
