
---

## Attempt at 2026-05-12

**Reason parked:** float comparator: missing nop between c.lt.s and bc1fl (FP hazard barrier)

Seed: `tough_nuts/func_001287B8/0287B8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001287B8; check asm/matchings/cod/0287B8/)
```

---

## Attempt at 2026-05-12

**Reason parked:** missing FPU hazard nop between c.lt.s and bc1fl; ee-gcc not inserting hazard, need NOP() but pattern blocks src/cod/__asm__

Seed: `tough_nuts/func_001287B8/0287B8.c.new`

Disassembly excerpt:

```
glabel func_001287B8
    /* 287B8 001287B8 00008044 */  mtc1       $zero, $f0
    /* 287BC 001287BC 34000C46 */  c.lt.s     $f0, $f12
    /* 287C0 001287C0 00000000 */  nop
    /* 287C4 001287C4 04000245 */  bc1fl      .L001287D8
    /* 287C8 001287C8 2008828C */   lw        $v0, 0x820($a0)
    /* 287CC 001287CC 2408828C */  lw         $v0, 0x824($a0)
    /* 287D0 001287D0 0800E003 */  jr         $ra
    /* 287D4 001287D4 3C004CE4 */   swc1      $f12, 0x3C($v0)
.align 2
  .L001287D8:
    /* 287D8 001287D8 2408838C */  lw         $v1, 0x824($a0)
    /* 287DC 001287DC 3C0040C4 */  lwc1       $f0, 0x3C($v0)
    /* 287E0 001287E0 0800E003 */  jr         $ra
    /* 287E4 001287E4 3C0060E4 */   swc1      $f0, 0x3C($v1)
endlabel func_001287B8
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss: gcc emits bc1f vs expected bc1fl (branch likely with annulled delay)

Seed: `tough_nuts/func_001287B8/0287B8.c.new`

Disassembly excerpt:

```
glabel func_001287B8
    /* 287B8 001287B8 00008044 */  mtc1       $zero, $f0
    /* 287BC 001287BC 34000C46 */  c.lt.s     $f0, $f12
    /* 287C0 001287C0 00000000 */  nop
    /* 287C4 001287C4 04000245 */  bc1fl      .L001287D8
    /* 287C8 001287C8 2008828C */   lw        $v0, 0x820($a0)
    /* 287CC 001287CC 2408828C */  lw         $v0, 0x824($a0)
    /* 287D0 001287D0 0800E003 */  jr         $ra
    /* 287D4 001287D4 3C004CE4 */   swc1      $f12, 0x3C($v0)
.align 2
  .L001287D8:
    /* 287D8 001287D8 2408838C */  lw         $v1, 0x824($a0)
    /* 287DC 001287DC 3C0040C4 */  lwc1       $f0, 0x3C($v0)
    /* 287E0 001287E0 0800E003 */  jr         $ra
    /* 287E4 001287E4 3C0060E4 */   swc1      $f0, 0x3C($v1)
endlabel func_001287B8
```
