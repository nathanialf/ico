#!/bin/bash
# ROUND-14 probe: measure rc/sites/census AND the frame-address disposition gate.
# usage: r14_probe.sh [candidate.c]
set -e
R=/primary/dev/ico/.claude/worktrees/motionmgr
cd $R
if [ -n "$1" ]; then cp "$1" $R/sugipon/src/motionFileManager.c; fi
python3 tough_nuts/ResetStatic2MotionManager/r9_m.py
python3 tough_nuts/ResetStatic2MotionManager/r11_census.py >/dev/null 2>&1 || true
python3 tough_nuts/ResetStatic2MotionManager/r14_frame.py 2>/dev/null | \
  egrep 'pseudo|0x60\(v60\)|0xf0\(qF0\)|0x110\(v110\)|0x70\(v70\)|allocnos' | \
  awk '$7>=6 || /pseudo|allocnos/'
