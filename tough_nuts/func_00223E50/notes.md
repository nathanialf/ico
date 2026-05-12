
---

## Attempt at 2026-05-08

**Reason parked:** wait loop: ee-gcc 14 insns; original 17 (extra nops)

Seed: `tough_nuts/func_00223E50/123E50.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00223E50; check asm/matchings/cod/123E50/)
```

---

## Attempt at 2026-05-12

**Reason parked:** scheduler puts sw a0 in b delay slot; expected has nop-nop padding before loop body, mine doesn't

Seed: `tough_nuts/func_00223E50/123E50.c.new`

Disassembly excerpt:

```
glabel func_00223E50
    /* 123E50 00223E50 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 123E54 00223E54 1000BFFF */  sd         $ra, 0x10($sp)
    /* 123E58 00223E58 0000A4AF */  sw         $a0, 0x0($sp)
    /* 123E5C 00223E5C 04000010 */  b          .L00223E70
    /* 123E60 00223E60 00000000 */   nop
    /* 123E64 00223E64 00000000 */  nop
.align 2
  .L00223E68:
    /* 123E68 00223E68 A80E080C */  jal        func_00203AA0
    /* 123E6C 00223E6C 01000424 */   addiu     $a0, $zero, 0x1
.align 2
  .L00223E70:
    /* 123E70 00223E70 8CEC050C */  jal        func_0017B230
    /* 123E74 00223E74 EA000424 */   addiu     $a0, $zero, 0xEA
    /* 123E78 00223E78 FBFF4010 */  beqz       $v0, .L00223E68
    /* 123E7C 00223E7C 03000424 */   addiu     $a0, $zero, 0x3
    /* 123E80 00223E80 CC16080C */  jal        func_00205B30
    /* 123E84 00223E84 01000524 */   addiu     $a1, $zero, 0x1
    /* 123E88 00223E88 1000BFDF */  ld         $ra, 0x10($sp)
    /* 123E8C 00223E8C 0800E003 */  jr         $ra
    /* 123E90 00223E90 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_00223E50
```
