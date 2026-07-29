#!/bin/bash
# CORRECTED oracle: recompiles the WORKTREE TU with -dg/-dl and runs the
# CLASS-AWARE simulator (sim4.py).  Use this, not oracle.sh:
#  - oracle.sh compiled /primary/dev/ico (MAIN tree), not the worktree;
#  - sim2.py/findreg_sim.py let FP_REGS allocnos occupy GP regs -> WRONG blockers.
# Point SP at your own session scratchpad; sim4.py has the same path baked in.
SP=${SP:-/tmp/claude-1005/-primary-dev-ico/4f803788-72d7-4575-a256-423f93f9bced/scratchpad}
ROOT=/primary/dev/ico/.claude/worktrees/motionmgr
mkdir -p $SP/dump; cd $SP/dump
cp ${1:-$ROOT/sugipon/src/motionFileManager.c} ./motionFileManager.c
EEGCC=/primary/dev/ico/tools/cc/ee-gcc2.9-991111/ee-gcc
LIB=/primary/dev/ico/tools/cc/ee-gcc2.9-991111/gcc-lib/ee/2.9-ee-991111-01/
rm -f motionFileManager.c.greg motionFileManager.c.lreg
$EEGCC -B $LIB -S -G 8 -O2 -mips3 -EL -fno-builtin -nostdinc -fdata-sections -I$ROOT/include -dg -dl -o motionFileManager.s motionFileManager.c 2>$SP/cc.err
[ -f motionFileManager.c.greg ] || { echo "COMPILE FAIL:"; tail -20 $SP/cc.err; exit 1; }
python3 $SP/sim4.py
