# func_00105278 / func_00105290 — `la` macro 64-bit expansion

## Failure mode

Pointer arithmetic on an array (`&D_0065FA40[D_00631B40]`) compiles to
the gas `la $2, SYM($2)` macro, which on the EE eabi expands to:

```
lui  $at, %hi(SYM)
daddiu $at, $at, %lo(SYM)   ; 64-bit addiu
daddu  $2, $at, $2          ; 64-bit addu
```

The original ICO code uses 32-bit `addiu` / `addu` and a different
instruction order:

```
lw    $v1, %gp_rel(D_00631B40)($gp)
lui   $v0, %hi(D_0065FA40)
addiu $v0, $v0, %lo(D_0065FA40)
sll   $v1, $v1, 6
jr    $ra
addu  $v0, $v1, $v0
```

I.e. the 32-bit register-overflow ABI, with the symbol load before the
shift (not after). ee-gcc 2.96 with `-G 8 -O2` emits the 64-bit `la`
form and reorders to load-after-shift. Tried unsigned int casts, int
arithmetic, `-mips2` — no change.

## Hypotheses

1. **Compiler isn't ee-gcc.** Most likely candidate. PS2 first-party
   2001 SCEI titles often used Pro-DG (wcc) or CodeWarrior, both of
   which have different macro expansion and scheduling defaults.
2. **ee-gcc with different flags.** Some `-mabi=` variant or a
   `-Wa,-mno-explicit-la` might suppress the 64-bit `la` macro
   expansion. Worth probing once the toolchain is confirmed.
3. **Inline asm escape hatch.** Could be matched by writing the body
   in inline asm, but that doesn't generalize and isn't a real match
   in the matching-decomp sense.

## What's been tried

- `extern struct {...} D_0065FA40[];` + `&D_0065FA40[D_00631B40]`
- `extern int D_0065FA40[];` + `D_0065FA40 + (D_00631B40 << 4)`
- `(int*)((unsigned)D_0065FA40 + ((unsigned)D_00631B40 << 6))`
- `-mips2` instead of `-mips3`

All produce identical 64-bit `la`-expanded output.

## Best-attempt source

See `func_00105278.c` (and identical-shape `func_00105290.c` for the
sibling at 0x5290). Diff is a 6-instruction-vs-6-instruction near miss
with order + 32/64-bit width differences.

## Next steps

1. Wait until compiler identification firms up (re-read
   `decomp/NOTES.md` "Compiler fingerprint" section).
2. If ee-gcc proves correct, dig into gas `la` macro source for any
   knob to force 32-bit expansion.
3. Try permuter for variations once we have a baseline that's at least
   the right instructions.
