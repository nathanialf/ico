
---

## Attempt at 2026-05-08

**Reason parked:** if-else with two tail-call branches; ee-gcc 2.9 picks different regalloc (a0 vs v0 for compare const) and consolidates ld ra at shared epilogue while original keeps per-branch ld ra

Seed: `tough_nuts/func_00252180/152180.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00252180; check asm/matchings/cod/152180/)
```

---

## Attempt at 2026-05-11

**Reason parked:** near-miss regalloc: built uses a0 for constant 3 + bne; expected uses v0 + beq. Functionally identical.

Seed: `tough_nuts/func_00252180/152180.c.new`

Disassembly excerpt:

```
glabel func_00252180
    /* 152180 00252180 5500023C */  lui        $v0, %hi(D_0055266C)
    /* 152184 00252184 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 152188 00252188 6C26438C */  lw         $v1, %lo(D_0055266C)($v0)
    /* 15218C 0025218C 03000224 */  addiu      $v0, $zero, 0x3
    /* 152190 00252190 05006210 */  beq        $v1, $v0, .L002521A8
    /* 152194 00252194 0000BFFF */   sd        $ra, 0x0($sp)
    /* 152198 00252198 7048090C */  jal        func_002521C0
    /* 15219C 0025219C 00000000 */   nop
    /* 1521A0 002521A0 04000010 */  b          .L002521B4
    /* 1521A4 002521A4 0000BFDF */   ld        $ra, 0x0($sp)
.align 2
  .L002521A8:
    /* 1521A8 002521A8 1648090C */  jal        func_00252058
    /* 1521AC 002521AC 00000000 */   nop
    /* 1521B0 002521B0 0000BFDF */  ld         $ra, 0x0($sp)
.align 2
  .L002521B4:
    /* 1521B4 002521B4 0800E003 */  jr         $ra
    /* 1521B8 002521B8 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_00252180
```
