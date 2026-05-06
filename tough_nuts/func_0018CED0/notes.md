# func_0018CED0

Sibling of func_0013B858. `D_00633D9C = 1; return 1;` (sdata **byte**
write — `sb`, not `sw`). 3-insn original collapses store-value and
return-value into the same `$v0`; ee-gcc 2.96 -O2 splits them.

Original asm:
```
addiu $v0, $zero, 0x1
jr    $ra
sb    $v0, %gp_rel(D_00633D9C)($gp)
```

See `../func_0013B858/notes.md` for the full pattern.
