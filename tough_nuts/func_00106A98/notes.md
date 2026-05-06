# func_00106A98 / func_00106AA8 — tail call to func_00105F00

## Failure mode

ee-gcc 2.96 with `-O2` doesn't perform sibling-call (tail call)
optimization for MIPS. The original ICO codegen tail-calls into
func_00105F00 with no frame:

```
lw    $a1, 0x15C($a1)
j     func_00105F00
addiu $a1, $a1, 0x5C0
```

ee-gcc emits a full prologue/epilogue + j (no jal):

```
addiu $sp, $sp, -0x10
sd    $ra, 0($sp)
lw    $a1, 0x15C($a1)
ld    $ra, 0($sp)
addiu $a1, $a1, 0x5C0
j     func_00105F00
addiu $sp, $sp, 0x10
```

Same effect, different asm.

## Hypotheses

1. **Wrong compiler.** Newer gcc (3.x+) gained TCO for MIPS. Could
   indicate the original used CodeWarrior or Pro-DG (which TCO).
2. **Inline asm.** Could be matched by writing the body in `__asm__`,
   but that defeats the matching-decomp purpose.

## Next steps

- Wait until compiler identification firms up.
- Or revisit if a `-fno-frame-pointer` / `-fomit-frame-pointer`-style
  knob can suppress the prologue when the function only tail-jumps.
