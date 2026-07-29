#!/bin/bash
# usage: probe17.sh <candidate.c>  -> prints rc/sites/census + divide-class metric
R=/primary/dev/ico/.claude/worktrees/motionmgr
cp "$1" $R/sugipon/src/motionFileManager.c
cd $R
M=$(python3 tough_nuts/ResetStatic2MotionManager/r9_m.py 2>&1 | head -1)
H=$(python3 tough_nuts/ResetStatic2MotionManager/r13_hunks.py 0 999999 2>/dev/null | tail -1)
S=$(awk '/^ResetStatic2MotionManager:/{f=1} f&&/\.end/{exit} f' build/quick_diff/sugipon/src/motionFileManager.s 2>/dev/null | grep -c 'mult	\$5,\$5,\$6')
echo "$M | $H | mult_a1=$S/6"
