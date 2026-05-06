# func_00244738 — la-macro 64-bit (lui+addiu vs lui+lw %lo split)

Variant of the la-macro 64-bit family. Original codegen shares one
`lui $v1, %hi(SYM)` between the load and the store, addressing both
via `%lo(SYM)($v1)`:

```
lui $v1, %hi(D_00550738)
lw  $v0, %lo(D_00550738)($v1)
jr  $ra
sw  $a0, %lo(D_00550738)($v1)
```

ee-gcc 2.96 -O2 instead expands the address with `addiu`, splits the
register, and reorders. See `../func_00105278/notes.md`.
