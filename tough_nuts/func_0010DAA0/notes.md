# func_0010DAA0 — la-macro 64-bit (D_00660A40 stride 16)

Same shape as func_00105278: array index via `lui+addiu+addu` (32-bit)
in the original, `lui+daddiu+daddu` (64-bit) under ee-gcc 2.96 -O2,
plus scheduling differences. See `../func_00105278/notes.md` for the
full failure analysis.

Original asm:
```
lw    $v1, %gp_rel(D_00631B7C)($gp)
lui   $v0, %hi(D_00660A40)
addiu $v0, $v0, %lo(D_00660A40)
sll   $v1, $v1, 4
jr    $ra
addu  $v0, $v1, $v0
```
