# func_0012FE08 — la-macro 64-bit + mult (D_006812D0 stride 0x2E8)

Same la-macro 64-bit failure as func_00105278, but the stride 0x2E8
is non-power-of-2 so the original codegen uses `mult` (low half via
`mflo`-elision: $a0 = $a0 * 0x2E8 in place — see asm). See
`../func_00105278/notes.md`.

Original asm:
```
addiu $v1, $zero, 0x2E8
lui   $v0, %hi(D_006812D0)
mult  $a0, $a0, $v1
addiu $v0, $v0, %lo(D_006812D0)
jr    $ra
addu  $v0, $a0, $v0
```
