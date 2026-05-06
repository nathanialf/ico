# func_0013F878

Same shape as func_0013B858 — `*(int*)(a0+0x18) = 1; return 1;` collapses
to 3 instructions in the original (single `$v0` reused for both store
and return value), but ee-gcc 2.96 -O2 splits the constant across `$v0`
and `$v1`, producing 4 instructions. See
`../func_0013B858/notes.md` for the full failure analysis.

Original asm (3 insns):
```
addiu $v0, $zero, 0x1
jr    $ra
sw    $v0, 0x18($a0)
```

Hypothesis: original compiler isn't ee-gcc 2.96.
