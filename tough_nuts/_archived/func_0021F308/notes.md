
---

## Attempt at 2026-05-08

**Reason parked:** wait loop: ee-gcc 14 insns; original 16 (extra nops)

Seed: `tough_nuts/func_0021F308/11F308.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0021F308; check asm/matchings/cod/11F308/)
```

---

## Attempt at 2026-05-13

**Reason parked:** alignment nops + splat boundary: jr ra delay in next subseg

Seed: `tough_nuts/func_0021F308/11F308.c.new`

Disassembly excerpt:

```
glabel func_0021F308
    /* 11F308 0021F308 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 11F30C 0021F30C 1000BFFF */  sd         $ra, 0x10($sp)
    /* 11F310 0021F310 0000A4AF */  sw         $a0, 0x0($sp)
    /* 11F314 0021F314 04000010 */  b          .L0021F328
    /* 11F318 0021F318 00000000 */   nop
    /* 11F31C 0021F31C 00000000 */  nop
.align 2
  .L0021F320:
    /* 11F320 0021F320 A80E080C */  jal        func_00203AA0
    /* 11F324 0021F324 01000424 */   addiu     $a0, $zero, 0x1
.align 2
  .L0021F328:
    /* 11F328 0021F328 8CEC050C */  jal        func_0017B230
    /* 11F32C 0021F32C A3000424 */   addiu     $a0, $zero, 0xA3
    /* 11F330 0021F330 FBFF4010 */  beqz       $v0, .L0021F320
    /* 11F334 0021F334 03000424 */   addiu     $a0, $zero, 0x3
    /* 11F338 0021F338 CC16080C */  jal        func_00205B30
    /* 11F33C 0021F33C 01000524 */   addiu     $a1, $zero, 0x1
    /* 11F340 0021F340 1000BFDF */  ld         $ra, 0x10($sp)
    /* 11F344 0021F344 0800E003 */  jr         $ra
endlabel func_0021F308
```
