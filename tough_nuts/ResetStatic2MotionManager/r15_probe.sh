#!/bin/bash
# rc/sites/census/hunks + frame disposition for the key case-0x13 bundle.
R=/primary/dev/ico/.claude/worktrees/motionmgr
cd $R
[ -n "$1" ] && cp "$1" $R/sugipon/src/motionFileManager.c
python3 tough_nuts/ResetStatic2MotionManager/r9_m.py | head -1
python3 tough_nuts/ResetStatic2MotionManager/r13_hunks.py 99999 99999 | tail -1
python3 /tmp/claude-1005/-primary-dev-ico/04159692-777d-4d3f-b622-24989f59a5e8/scratchpad/off.py | tail -1
bash tough_nuts/ResetStatic2MotionManager/r15_dump.sh >/dev/null 2>&1 || echo "DUMP FAIL"
python3 tough_nuts/ResetStatic2MotionManager/r14_frame.py | egrep '0xf0|0x120|0x110|0x130|0x70\(|0x60\(' | awk '$7>=6'
