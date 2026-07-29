#!/bin/bash
# Regenerate the -dg/-dl dumps in d11/ for the CURRENT worktree TU (or $1).
set -e
R=/primary/dev/ico/.claude/worktrees/motionmgr
D=$R/tough_nuts/ResetStatic2MotionManager/d11
mkdir -p $D; cd $D
cp ${1:-$R/sugipon/src/motionFileManager.c} ./motionFileManager.c
EEGCC=/primary/dev/ico/tools/cc/ee-gcc2.9-991111/ee-gcc
LIB=/primary/dev/ico/tools/cc/ee-gcc2.9-991111/gcc-lib/ee/2.9-ee-991111-01/
rm -f motionFileManager.c.greg motionFileManager.c.lreg
$EEGCC -B $LIB -S -G 8 -O2 -mips3 -EL -fno-builtin -nostdinc -fdata-sections -I$R/include -dg -dl -o motionFileManager.s motionFileManager.c 2>$D/cc.err
[ -f motionFileManager.c.greg ] || { echo "COMPILE FAIL:"; tail -20 $D/cc.err; exit 1; }
echo "dumps ok"
