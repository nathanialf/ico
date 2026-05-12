# func_0014B2F0 — parked

VRAM: 0x0014B2F0 (file offset 0x04B2F0)
Asm source: `asm/cod/04B270.s`

## Attempt at 2026-05-08

**Reason parked:** ee-gcc 2.9 emits the bit-test (`1 << idx & low32`) in 8 instructions versus the expected 10. The compiler folds the `(1 << idx) & val ? 1 : 0` ternary into shift+and+movz, but the original codegen also has an explicit ld of the qword field at 0x58 and a separate sllv on the constant 1. Likely needs `(long long)` types or volatile qword load to match.

Seed: `tough_nuts/func_0014B2F0/04B2F0.c`

---

## Attempt at 2026-05-08

**Reason parked:** leaf bitfield-test: ee-gcc emits dsrav+andi (8 insns); original sllv+and+movz (10 insns) — bit-extract idiom diff

Seed: `tough_nuts/func_0014B2F0/04B2F0.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0014B2F0; check asm/matchings/cod/04B2F0/)
```

---

## Attempt at 2026-05-12

**Reason parked:** bnel branch-likely vs beq+daddu; final daddu v0,a0,0 copy (r→v0)

Seed: `tough_nuts/func_0014B2F0/04B2F0.c.new`

Disassembly excerpt:

```
glabel func_0014B2F0
    /* 4B2F0 0014B2F0 6401838C */  lw         $v1, 0x164($a0)
    /* 4B2F4 0014B2F4 06006010 */  beqz       $v1, .L0014B310
    /* 4B2F8 0014B2F8 2D100000 */   daddu     $v0, $zero, $zero
    /* 4B2FC 0014B2FC 01000224 */  addiu      $v0, $zero, 0x1
    /* 4B300 0014B300 580063DC */  ld         $v1, 0x58($v1)
    /* 4B304 0014B304 0420A200 */  sllv       $a0, $v0, $a1
    /* 4B308 0014B308 24188300 */  and        $v1, $a0, $v1
    /* 4B30C 0014B30C 0A100300 */  movz       $v0, $zero, $v1
.align 2
  .L0014B310:
    /* 4B310 0014B310 0800E003 */  jr         $ra
    /* 4B314 0014B314 00000000 */   nop
endlabel func_0014B2F0
```
