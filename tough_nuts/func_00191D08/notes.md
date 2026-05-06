# func_00191D08 — `daddu` vs `or` for register-zero materialization

## Failure mode

The original ICO codegen materializes 0 in `$v0` via:
```
daddu $v0, $zero, $zero
```

ee-gcc 2.96 -O2 emits the semantically identical:
```
or    $v0, $zero, $zero    /* equivalently `move $v0, $zero` */
```

Same effect (R0 ⊕ R0 = 0; R0 + R0 = 0); different encoding. There is
no clean knob in ee-gcc to coerce `daddu` here.

## Original asm (6 insns)
```
addiu $v0, $zero, -0x1
sw    $zero, %gp_rel(D_00633DB4)($gp)
sw    $v0,  %gp_rel(D_00633DB8)($gp)
daddu $v0, $zero, $zero
jr    $ra
sw    $zero, %gp_rel(D_00633DBC)($gp)
```

## Hypothesis

Same root cause as the rest of the daddu/or cluster: original compiler
isn't ee-gcc 2.96. See `decomp/NOTES.md` "Patterns parked in
tough_nuts/" → `daddu vs or for register move`.
