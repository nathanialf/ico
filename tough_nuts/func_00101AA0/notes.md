
---

## Attempt at 2026-05-08

**Reason parked:** DMA-tag setup buffer wrapper: ee-gcc -O2 schedules sw a0/sw a1/move a1=sp differently than original

Seed: `tough_nuts/func_00101AA0/001AA0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00101AA0; check asm/matchings/cod/001AA0/)
```

---

## Attempt at 2026-05-09

**Reason parked:** syscall wrapper: schedule of sw v0,12(sp) into delay slot doesn't match (close but final 5-insn block differs)

Seed: `tough_nuts/func_00101AA0/001AA0.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00101AA0; check asm/matchings/cod/001AA0/)
```

---

## Attempt at 2026-05-12

**Reason parked:** packet build: 3 instructions repositioned by scheduler (andi, or, daddu); all semantically equiv

Seed: `tough_nuts/func_00101AA0/001AA0.c.new`

Disassembly excerpt:

```
glabel func_00101AA0
    /* 1AA0 00101AA0 6300023C */  lui        $v0, %hi(D_006349E0)
    /* 1AA4 00101AA4 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 1AA8 00101AA8 0020033C */  lui        $v1, (0x20000000 >> 16)
    /* 1AAC 00101AAC E0494224 */  addiu      $v0, $v0, %lo(D_006349E0)
    /* 1AB0 00101AB0 FFFF8430 */  andi       $a0, $a0, 0xFFFF
    /* 1AB4 00101AB4 25104300 */  or         $v0, $v0, $v1
    /* 1AB8 00101AB8 0400A5AF */  sw         $a1, 0x4($sp)
    /* 1ABC 00101ABC 0000A4AF */  sw         $a0, 0x0($sp)
    /* 1AC0 00101AC0 2D28A003 */  daddu      $a1, $sp, $zero
    /* 1AC4 00101AC4 1000BFFF */  sd         $ra, 0x10($sp)
    /* 1AC8 00101AC8 01000424 */  addiu      $a0, $zero, 0x1
    /* 1ACC 00101ACC 0800A6AF */  sw         $a2, 0x8($sp)
    /* 1AD0 00101AD0 5402040C */  jal        func_00100950
    /* 1AD4 00101AD4 0C00A2AF */   sw        $v0, 0xC($sp)
    /* 1AD8 00101AD8 1000BFDF */  ld         $ra, 0x10($sp)
    /* 1ADC 00101ADC 0800E003 */  jr         $ra
    /* 1AE0 00101AE0 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_00101AA0
```

---

## Attempt at 2026-05-13

**Reason parked:** scheduler order: andi/or v0/daddu a1 placement diffs

Seed: `tough_nuts/func_00101AA0/001AA0.c.new`

Disassembly excerpt:

```
glabel func_00101AA0
    /* 1AA0 00101AA0 6300023C */  lui        $v0, %hi(D_006349E0)
    /* 1AA4 00101AA4 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 1AA8 00101AA8 0020033C */  lui        $v1, (0x20000000 >> 16)
    /* 1AAC 00101AAC E0494224 */  addiu      $v0, $v0, %lo(D_006349E0)
    /* 1AB0 00101AB0 FFFF8430 */  andi       $a0, $a0, 0xFFFF
    /* 1AB4 00101AB4 25104300 */  or         $v0, $v0, $v1
    /* 1AB8 00101AB8 0400A5AF */  sw         $a1, 0x4($sp)
    /* 1ABC 00101ABC 0000A4AF */  sw         $a0, 0x0($sp)
    /* 1AC0 00101AC0 2D28A003 */  daddu      $a1, $sp, $zero
    /* 1AC4 00101AC4 1000BFFF */  sd         $ra, 0x10($sp)
    /* 1AC8 00101AC8 01000424 */  addiu      $a0, $zero, 0x1
    /* 1ACC 00101ACC 0800A6AF */  sw         $a2, 0x8($sp)
    /* 1AD0 00101AD0 5402040C */  jal        func_00100950
    /* 1AD4 00101AD4 0C00A2AF */   sw        $v0, 0xC($sp)
    /* 1AD8 00101AD8 1000BFDF */  ld         $ra, 0x10($sp)
    /* 1ADC 00101ADC 0800E003 */  jr         $ra
    /* 1AE0 00101AE0 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_00101AA0
```
