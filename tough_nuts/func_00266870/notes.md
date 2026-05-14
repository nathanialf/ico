
---

## Attempt at 2026-05-08

**Reason parked:** byte-identical sibling of func_00265B28 — same branch-direction/regalloc divergence

Seed: `tough_nuts/func_00266870/166870.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00266870; check asm/matchings/cod/166870/)
```

---

## Attempt at 2026-05-14

**Reason parked:** branch direction + ret reg alloc; sibling of 265B28

Seed: `tough_nuts/func_00266870/166870.c.new`

Disassembly excerpt:

```
glabel func_00266870
    /* 166870 00266870 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 166874 00266874 0000B0FF */  sd         $s0, 0x0($sp)
    /* 166878 00266878 1000BFFF */  sd         $ra, 0x10($sp)
    /* 16687C 0026687C 2D80A000 */  daddu      $s0, $a1, $zero
    /* 166880 00266880 0800028E */  lw         $v0, 0x8($s0)
    /* 166884 00266884 03004014 */  bnez       $v0, .L00266894
    /* 166888 00266888 2D100000 */   daddu     $v0, $zero, $zero
    /* 16688C 0026688C 05000010 */  b          .L002668A4
    /* 166890 00266890 040000AE */   sw        $zero, 0x4($s0)
.align 2
  .L00266894:
    /* 166894 00266894 10AB090C */  jal        func_0026AC40
    /* 166898 00266898 2D280002 */   daddu     $a1, $s0, $zero
    /* 16689C 0026689C 040000AE */  sw         $zero, 0x4($s0)
    /* 1668A0 002668A0 080000AE */  sw         $zero, 0x8($s0)
.align 2
  .L002668A4:
    /* 1668A4 002668A4 1000BFDF */  ld         $ra, 0x10($sp)
    /* 1668A8 002668A8 0000B0DF */  ld         $s0, 0x0($sp)
    /* 1668AC 002668AC 0800E003 */  jr         $ra
    /* 1668B0 002668B0 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_00266870
```
