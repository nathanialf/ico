
---

## Attempt at 2026-05-08

**Reason parked:** ee-gcc places sw v0,gp_rel BEFORE ld s0; original places it AFTER

Seed: `tough_nuts/func_0023F030/13F030.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0023F030; check asm/matchings/cod/13F030/)
```

---

## Attempt at 2026-05-11

**Reason parked:** near-miss: gcc schedules sw zero,zero,v0 in store sequence; expected order is v0,zero,zero. Memory barrier helps order but ld ra placement still differs.

Seed: `tough_nuts/func_0023F030/13F030.c.new`

Disassembly excerpt:

```
glabel func_0023F030
    /* 13F030 0023F030 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 13F034 0023F034 0000B0FF */  sd         $s0, 0x0($sp)
    /* 13F038 0023F038 1000BFFF */  sd         $ra, 0x10($sp)
    /* 13F03C 0023F03C 2D808000 */  daddu      $s0, $a0, $zero
.align 2
  .L0023F040:
    /* 13F040 0023F040 6A09090C */  jal        func_002425A8
    /* 13F044 0023F044 2D200000 */   daddu     $a0, $zero, $zero
    /* 13F048 0023F048 FDFF5010 */  beq        $v0, $s0, .L0023F040
    /* 13F04C 0023F04C 01000224 */   addiu     $v0, $zero, 0x1
    /* 13F050 0023F050 1000BFDF */  ld         $ra, 0x10($sp)
    /* 13F054 0023F054 98B282AF */  sw         $v0, %gp_rel(D_00633B88)($gp)
    /* 13F058 0023F058 0000B0DF */  ld         $s0, 0x0($sp)
    /* 13F05C 0023F05C ECB680AF */  sw         $zero, %gp_rel(D_00633FDC)($gp)
    /* 13F060 0023F060 94B280AF */  sw         $zero, %gp_rel(D_00633B84)($gp)
    /* 13F064 0023F064 0800E003 */  jr         $ra
    /* 13F068 0023F068 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_0023F030
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss: 1-line swap of ld s0 vs sw v0 (D_00633B88=1) in epilogue

Seed: `tough_nuts/func_0023F030/13F030.c.new`

Disassembly excerpt:

```
glabel func_0023F030
    /* 13F030 0023F030 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 13F034 0023F034 0000B0FF */  sd         $s0, 0x0($sp)
    /* 13F038 0023F038 1000BFFF */  sd         $ra, 0x10($sp)
    /* 13F03C 0023F03C 2D808000 */  daddu      $s0, $a0, $zero
.align 2
  .L0023F040:
    /* 13F040 0023F040 6A09090C */  jal        func_002425A8
    /* 13F044 0023F044 2D200000 */   daddu     $a0, $zero, $zero
    /* 13F048 0023F048 FDFF5010 */  beq        $v0, $s0, .L0023F040
    /* 13F04C 0023F04C 01000224 */   addiu     $v0, $zero, 0x1
    /* 13F050 0023F050 1000BFDF */  ld         $ra, 0x10($sp)
    /* 13F054 0023F054 98B282AF */  sw         $v0, %gp_rel(D_00633B88)($gp)
    /* 13F058 0023F058 0000B0DF */  ld         $s0, 0x0($sp)
    /* 13F05C 0023F05C ECB680AF */  sw         $zero, %gp_rel(D_00633FDC)($gp)
    /* 13F060 0023F060 94B280AF */  sw         $zero, %gp_rel(D_00633B84)($gp)
    /* 13F064 0023F064 0800E003 */  jr         $ra
    /* 13F068 0023F068 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_0023F030
```
