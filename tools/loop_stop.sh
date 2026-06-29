#!/usr/bin/env bash
# User-authorized end of a decomp-match loop. Drops the stop sentinel that
# the Stop hook (.claude/hooks/decomp_stop_guard.py) honors once, then clears.
# Run this ONLY when the user has explicitly said to end the loop.
set -eu
cd "$(dirname "$0")/.."
touch .claude/.decomp_loop_stop
# Tear down the completion-gated chain too: remove .decomp_chain_active (so the
# supervisor stops spawning the next worker) and the in-flight worker sentinel.
python3 tools/decomp_chain.py stop >/dev/null 2>&1 || rm -f .claude/.decomp_chain_active .claude/.decomp_worker.json
echo "decomp loop stop authorized — chain torn down; next turn-end will be allowed."
