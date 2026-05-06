# func_0013B858 (and 9 siblings) — combined sdata-set + return-value regalloc

## Failure mode

Pattern in original asm (3 instructions):
```
addiu $v0, $zero, 0x1
jr    $ra
sw    $v0, %gp_rel(D_X)($gp)
```

I.e. the constant `1` is loaded into `$v0` exactly once, used both as
the store value (in the jr delay slot) and as the return value.

ee-gcc 2.96 with `-O2` insists on a separate register for the store
value (`$v1`), producing 4 instructions:
```
addiu $v1, $zero, 0x1
addiu $v0, $zero, 0x1
jr    $ra
sw    $v1, %gp_rel(D_X)($gp)
```

Same C surface (`D_X = 1; return 1;` or `return D_X = 1;`), different
regalloc decision.

## Sibling functions (all same shape, different sdata sym / target)

- func_0013B858 — D_00633C90 = 1, return 1
- func_0013F878 — *(int*)($a0+0x18) = 1, return 1   (struct field, not sdata)
- func_0018CED0 — D_00633D9C (byte) = 1, return 1
- func_0018CEE0 — D_00633D8C (byte) = 1, return 1
- func_0018CFD0 — D_00633D8D (byte) = 1, return 1
- func_0018CFE0 — D_00632704 = 1, return 1
- func_00192040 — D_00632780 = 1, return 1
- func_0019E1C0 — *(int*)($a0+0xB8) = 1, return 1
- func_001B0A58 — D_00633024 = 1, return 1
- func_001FAA30 — D_006337B8 = 1, return 1

## Hypothesis

Likely the original wasn't ee-gcc 2.96 (consistent with the daddu/la
findings on func_00105278). Pro-DG/wcc and CodeWarrior reuse $v0 for
simultaneous store+return; ee-gcc 2.96 doesn't.
