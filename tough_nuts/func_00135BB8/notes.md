
---

## Attempt at 2026-05-08

**Reason parked:** ee-gcc -O2 picks a0 for loop temp + nop scheduling differs; -fno-schedule-insns alone doesn't fix it (regalloc not scheduling)

Seed: `tough_nuts/func_00135BB8/035BB8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00135BB8; check asm/matchings/cod/035BB8/)
```

---

## Attempt at 2026-05-12

**Reason parked:** list walker: built uses v0/s0 split for next/cur; target reuses s0; ee-gcc 2.9 fails to coalesce live ranges

Seed: `tough_nuts/func_00135BB8/035BB8.c.new`

Disassembly excerpt:

```
glabel func_00135BB8
    /* 35BB8 00135BB8 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 35BBC 00135BBC 0000B0FF */  sd         $s0, 0x0($sp)
    /* 35BC0 00135BC0 2D808000 */  daddu      $s0, $a0, $zero
    /* 35BC4 00135BC4 07000012 */  beqz       $s0, .L00135BE4
    /* 35BC8 00135BC8 1000BFFF */   sd        $ra, 0x10($sp)
    /* 35BCC 00135BCC F8FF1026 */  addiu      $s0, $s0, -0x8
.align 2
  .L00135BD0:
    /* 35BD0 00135BD0 2D200002 */  daddu      $a0, $s0, $zero
    /* 35BD4 00135BD4 66E5040C */  jal        func_00139598
    /* 35BD8 00135BD8 0400108E */   lw        $s0, 0x4($s0)
    /* 35BDC 00135BDC FCFF0016 */  bnez       $s0, .L00135BD0
    /* 35BE0 00135BE0 F8FF1026 */   addiu     $s0, $s0, -0x8
.align 2
  .L00135BE4:
    /* 35BE4 00135BE4 1000BFDF */  ld         $ra, 0x10($sp)
    /* 35BE8 00135BE8 2D100000 */  daddu      $v0, $zero, $zero
    /* 35BEC 00135BEC 0000B0DF */  ld         $s0, 0x0($sp)
    /* 35BF0 00135BF0 0800E003 */  jr         $ra
    /* 35BF4 00135BF4 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_00135BB8
```
