# func_0019E1C0

Sibling of func_0013B858 — `*(int*)(a0+0xB8) = 1; return 1;`. Same
regalloc split: original uses one `$v0` for both store value and return,
ee-gcc 2.96 -O2 uses `$v1` for the store and `$v0` for the return.

Original asm:
```
addiu $v0, $zero, 0x1
jr    $ra
sw    $v0, 0xB8($a0)
```

See `../func_0013B858/notes.md` for the full failure analysis.
