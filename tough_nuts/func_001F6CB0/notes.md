# func_001F6CB0

Compiles to 0xD8 (54 instructions); original is 0xE0 (56 instructions).
The dispatch logic differs in the if-else-if-no-else pattern: ee-gcc emits
`bnez (jump to first case if non-zero)` whereas original has
`beqz (D == 0 jump) ; li v0,1 ; beq v1,v0 (D == 1 jump) ; move v0,s2 ; b end ; ld ra (delay)`
— a 3-way branch with explicit fall-through to early-return-with-rv-default.

Suggests original may have been written as a switch or with an explicit
early-return for the "neither" case. Permuter should be able to find the
right C structure.

Known-good extra cflag: `BASIC -fno-schedule-insns` (already in
config/extra_cflags.txt for this TU).
