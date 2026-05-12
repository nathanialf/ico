
---

## Attempt at 2026-05-12

**Reason parked:** float comparator: missing nop between c.lt.s and bc1*; ee-gcc emits no hazard nop

Seed: `tough_nuts/func_0017B0D8/07B0D8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0017B0D8; check asm/matchings/cod/07B0D8/)
```

---

## Attempt at 2026-05-12

**Reason parked:** float comparator: missing FPU hazard nop between c.lt.s and bc1t (same issue as 1287B8)

Seed: `tough_nuts/func_0017B0D8/07B0D8.c.new`

Disassembly excerpt:

```
glabel func_0017B0D8
    /* 7B0D8 0017B0D8 040081C4 */  lwc1       $f1, 0x4($a0)
    /* 7B0DC 0017B0DC 0400A0C4 */  lwc1       $f0, 0x4($a1)
    /* 7B0E0 0017B0E0 34080046 */  c.lt.s     $f1, $f0
    /* 7B0E4 0017B0E4 00000000 */  nop
    /* 7B0E8 0017B0E8 06000145 */  bc1t       .L0017B104
    /* 7B0EC 0017B0EC FFFF0224 */   addiu     $v0, $zero, -0x1
    /* 7B0F0 0017B0F0 34000146 */  c.lt.s     $f0, $f1
    /* 7B0F4 0017B0F4 00000000 */  nop
    /* 7B0F8 0017B0F8 02000045 */  bc1f       .L0017B104
    /* 7B0FC 0017B0FC 2D100000 */   daddu     $v0, $zero, $zero
    /* 7B100 0017B100 01000224 */  addiu      $v0, $zero, 0x1
.align 2
  .L0017B104:
    /* 7B104 0017B104 0800E003 */  jr         $ra
    /* 7B108 0017B108 00000000 */   nop
endlabel func_0017B0D8
```
