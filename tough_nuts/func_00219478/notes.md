
---

## Attempt at 2026-05-12

**Reason parked:** 3-call wrapper extremely close; trailing nop before jr ra (hazard fill) shifts function size by 4

Seed: `tough_nuts/func_00219478/119478.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00219478; check asm/matchings/cod/119478/)
```

---

## Attempt at 2026-05-12

**Reason parked:** score-0 from permuter has trailing nop after final ld ra; pipeline differs

Seed: `tough_nuts/func_00219478/119478.c.new`

Disassembly excerpt:

```
glabel func_00219478
    /* 119478 00219478 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 11947C 0021947C 0000A4AF */  sw         $a0, 0x0($sp)
    /* 119480 00219480 1000BFFF */  sd         $ra, 0x10($sp)
    /* 119484 00219484 0000A28F */  lw         $v0, 0x0($sp)
    /* 119488 00219488 0000A48F */  lw         $a0, 0x0($sp)
    /* 11948C 0021948C 8208080C */  jal        func_00202208
    /* 119490 00219490 00000000 */   nop
    /* 119494 00219494 A80E080C */  jal        func_00203AA0
    /* 119498 00219498 01000424 */   addiu     $a0, $zero, 0x1
    /* 11949C 0021949C 8CEC050C */  jal        func_0017B230
    /* 1194A0 002194A0 CD000424 */   addiu     $a0, $zero, 0xCD
    /* 1194A4 002194A4 05004010 */  beqz       $v0, .L002194BC
    /* 1194A8 002194A8 1000BFDF */   ld        $ra, 0x10($sp)
    /* 1194AC 002194AC 62F8050C */  jal        func_0017E188
    /* 1194B0 002194B0 EE030424 */   addiu     $a0, $zero, 0x3EE
    /* 1194B4 002194B4 6C0140AC */  sw         $zero, 0x16C($v0)
    /* 1194B8 002194B8 1000BFDF */  ld         $ra, 0x10($sp)
.align 2
  .L002194BC:
    /* 1194BC 002194BC 0800E003 */  jr         $ra
    /* 1194C0 002194C0 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_00219478
```

---

## Attempt at 2026-05-14

**Reason parked:** load-use hazard nop before jr ra

Seed: `tough_nuts/func_00219478/119478.c.new`

Disassembly excerpt:

```
glabel func_00219478
    /* 119478 00219478 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 11947C 0021947C 0000A4AF */  sw         $a0, 0x0($sp)
    /* 119480 00219480 1000BFFF */  sd         $ra, 0x10($sp)
    /* 119484 00219484 0000A28F */  lw         $v0, 0x0($sp)
    /* 119488 00219488 0000A48F */  lw         $a0, 0x0($sp)
    /* 11948C 0021948C 8208080C */  jal        func_00202208
    /* 119490 00219490 00000000 */   nop
    /* 119494 00219494 A80E080C */  jal        func_00203AA0
    /* 119498 00219498 01000424 */   addiu     $a0, $zero, 0x1
    /* 11949C 0021949C 8CEC050C */  jal        func_0017B230
    /* 1194A0 002194A0 CD000424 */   addiu     $a0, $zero, 0xCD
    /* 1194A4 002194A4 05004010 */  beqz       $v0, .L002194BC
    /* 1194A8 002194A8 1000BFDF */   ld        $ra, 0x10($sp)
    /* 1194AC 002194AC 62F8050C */  jal        func_0017E188
    /* 1194B0 002194B0 EE030424 */   addiu     $a0, $zero, 0x3EE
    /* 1194B4 002194B4 6C0140AC */  sw         $zero, 0x16C($v0)
    /* 1194B8 002194B8 1000BFDF */  ld         $ra, 0x10($sp)
.align 2
  .L002194BC:
    /* 1194BC 002194BC 0800E003 */  jr         $ra
    /* 1194C0 002194C0 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_00219478
```
