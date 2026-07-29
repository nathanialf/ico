#!/bin/bash
# recompile TU with dumps + run trio sim. usage: oracle.sh
ROOT=/primary/dev/ico
SP=/tmp/claude-1005/-primary-dev-ico/fd7bfd8a-5faa-485e-9c46-6127ff47e64b/scratchpad
cd $SP/dump
cp $ROOT/sugipon/src/motionFileManager.c .
EEGCC="$ROOT/tools/cc/ee-gcc2.9-991111/ee-gcc"
LIB="$ROOT/tools/cc/ee-gcc2.9-991111/gcc-lib/ee/2.9-ee-991111-01/"
rm -f motionFileManager.c.greg motionFileManager.c.lreg
$EEGCC -B $LIB -S -G 8 -O2 -mips3 -EL -fno-builtin -nostdinc -fdata-sections -I$ROOT/include -dg -dl -o motionFileManager.s motionFileManager.c 2>$SP/cc.err
if [ ! -f motionFileManager.c.greg ]; then echo "COMPILE FAIL:"; tail -5 $SP/cc.err; exit 1; fi
python3 $SP/sim2.py
