#!/bin/bash
# thin wrapper: exactly the repo CFLAGS, ee-gcc only, extra args passthrough
ROOT=/primary/dev/ico
D=$ROOT/tools/cc/ee-gcc2.9-991111
exec $D/ee-gcc -B $D/gcc-lib/ee/2.9-ee-991111-01/ -S -G 8 -O2 -mips3 -EL -fno-builtin -nostdinc -fdata-sections -I$ROOT/include "$@"
