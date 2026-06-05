#!/usr/bin/env bash
# User-authorized end of a decomp-match loop. Drops the stop sentinel that
# the Stop hook (.claude/hooks/decomp_stop_guard.py) honors once, then clears.
# Run this ONLY when the user has explicitly said to end the loop.
set -eu
cd "$(dirname "$0")/.."
touch .claude/.decomp_loop_stop
echo "decomp loop stop authorized — next turn-end will be allowed."
