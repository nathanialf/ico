
---

## Attempt at 2026-05-12

**Reason parked:** same shape as func_00219478: trailing hazard nop

Seed: `tough_nuts/func_00224E30/124E30.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00224E30; check asm/matchings/cod/124E30/)
```

---

## Attempt at 2026-05-13

**Reason parked:** ee-as fills jal delay with lw a0; expected has nop in delay

Seed: `tough_nuts/func_00224E30/124E30.c.new`

Disassembly excerpt:

```
glabel func_00224E30
    /* 124E30 00224E30 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 124E34 00224E34 0000A4AF */  sw         $a0, 0x0($sp)
    /* 124E38 00224E38 1000BFFF */  sd         $ra, 0x10($sp)
    /* 124E3C 00224E3C 0000A28F */  lw         $v0, 0x0($sp)
    /* 124E40 00224E40 0000A48F */  lw         $a0, 0x0($sp)
    /* 124E44 00224E44 8208080C */  jal        func_00202208
    /* 124E48 00224E48 00000000 */   nop
    /* 124E4C 00224E4C A80E080C */  jal        func_00203AA0
    /* 124E50 00224E50 01000424 */   addiu     $a0, $zero, 0x1
    /* 124E54 00224E54 8CEC050C */  jal        func_0017B230
    /* 124E58 00224E58 CE000424 */   addiu     $a0, $zero, 0xCE
    /* 124E5C 00224E5C 05004010 */  beqz       $v0, .L00224E74
    /* 124E60 00224E60 1000BFDF */   ld        $ra, 0x10($sp)
    /* 124E64 00224E64 62F8050C */  jal        func_0017E188
    /* 124E68 00224E68 FC040424 */   addiu     $a0, $zero, 0x4FC
    /* 124E6C 00224E6C 6C0140AC */  sw         $zero, 0x16C($v0)
    /* 124E70 00224E70 1000BFDF */  ld         $ra, 0x10($sp)
.align 2
  .L00224E74:
    /* 124E74 00224E74 0800E003 */  jr         $ra
    /* 124E78 00224E78 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_00224E30
```
