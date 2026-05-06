# func_0014B358 — la-macro 64-bit (D_002924B0 stride 4, return float)

Same la-macro 64-bit failure as func_00105278. The result is loaded
into `$f0` via `lwc1`. See `../func_00105278/notes.md`.

Original asm:
```
lui   $v0, %hi(D_002924B0)
sll   $a0, $a0, 2
addiu $v0, $v0, %lo(D_002924B0)
addu  $a0, $a0, $v0
jr    $ra
lwc1  $f0, 0x0($a0)
```
