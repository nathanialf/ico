
---

## Attempt at 2026-05-12

**Reason parked:** find-first-nonzero loop: lbu now correct but if-blez/early-exit structure differs

Seed: `tough_nuts/func_0013CD30/03CD30.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0013CD30; check asm/matchings/cod/03CD30/)
```

---

## Attempt at 2026-05-12

**Reason parked:** reg alloc differs (v0 vs a1 for count), branch inverted bgtz vs blez, restructure needed

Seed: `tough_nuts/func_0013CD30/03CD30.c.new`

Disassembly excerpt:

```
glabel func_0013CD30
    /* 3CD30 0013CD30 0000828C */  lw         $v0, 0x0($a0)
    /* 3CD34 0013CD34 2D280000 */  daddu      $a1, $zero, $zero
    /* 3CD38 0013CD38 0B004018 */  blez       $v0, .L0013CD68
    /* 3CD3C 0013CD3C 0400838C */   lw        $v1, 0x4($a0)
    /* 3CD40 0013CD40 2D204000 */  daddu      $a0, $v0, $zero
    /* 3CD44 0013CD44 00000000 */  nop
.align 2
  .L0013CD48:
    /* 3CD48 0013CD48 00006290 */  lbu        $v0, 0x0($v1)
    /* 3CD4C 0013CD4C 03004014 */  bnez       $v0, .L0013CD5C
    /* 3CD50 0013CD50 0100A524 */   addiu     $a1, $a1, 0x1
    /* 3CD54 0013CD54 0800E003 */  jr         $ra
    /* 3CD58 0013CD58 2D106000 */   daddu     $v0, $v1, $zero
.align 2
  .L0013CD5C:
    /* 3CD5C 0013CD5C 2A10A400 */  slt        $v0, $a1, $a0
    /* 3CD60 0013CD60 F9FF4014 */  bnez       $v0, .L0013CD48
    /* 3CD64 0013CD64 40006324 */   addiu     $v1, $v1, 0x40
.align 2
  .L0013CD68:
    /* 3CD68 0013CD68 0800E003 */  jr         $ra
    /* 3CD6C 0013CD6C 2D100000 */   daddu     $v0, $zero, $zero
endlabel func_0013CD30
```
