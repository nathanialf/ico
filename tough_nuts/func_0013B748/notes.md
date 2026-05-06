# func_0013B748 — la-macro 64-bit (D_002811C0 stride 0x200, +0x0)

Same la-macro 64-bit failure as func_00105278. See
`../func_00105278/notes.md`.

Original asm:
```
lui   $v0, %hi(D_002811C0)
sll   $a1, $a1, 9
addiu $v0, $v0, %lo(D_002811C0)
addu  $a1, $a1, $v0
jr    $ra
lw    $v0, 0x0($a1)
```
