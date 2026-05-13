
---

## Attempt at 2026-05-09

**Reason parked:** size mismatch: built=0x54 expected=0x50 diff=+4

Seed: `tough_nuts/func_00107DD8/007DD8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00107DD8; check asm/matchings/cod/007DD8/)
```

---

## Attempt at 2026-05-13

**Reason parked:** reg alloc info=v0 vs v1; gcc shuffles multiple regs

Seed: `tough_nuts/func_00107DD8/007DD8.c.new`

Disassembly excerpt:

```
glabel func_00107DD8
    /* 7DD8 00107DD8 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 7DDC 00107DDC 2D10C000 */  daddu      $v0, $a2, $zero
    /* 7DE0 00107DE0 0000B0FF */  sd         $s0, 0x0($sp)
    /* 7DE4 00107DE4 1000BFFF */  sd         $ra, 0x10($sp)
    /* 7DE8 00107DE8 2D80A000 */  daddu      $s0, $a1, $zero
    /* 7DEC 00107DEC 0000488C */  lw         $t0, 0x0($v0)
    /* 7DF0 00107DF0 0400478C */  lw         $a3, 0x4($v0)
    /* 7DF4 00107DF4 5C01038D */  lw         $v1, 0x15C($t0)
    /* 7DF8 00107DF8 0800468C */  lw         $a2, 0x8($v0)
    /* 7DFC 00107DFC 80390700 */  sll        $a3, $a3, 6
    /* 7E00 00107E00 0C00628C */  lw         $v0, 0xC($v1)
    /* 7E04 00107E04 B8A2050C */  jal        func_00168AE0
    /* 7E08 00107E08 21384700 */   addu      $a3, $v0, $a3
    /* 7E0C 00107E0C 2D200002 */  daddu      $a0, $s0, $zero
    /* 7E10 00107E10 040000AE */  sw         $zero, 0x4($s0)
    /* 7E14 00107E14 1000BFDF */  ld         $ra, 0x10($sp)
    /* 7E18 00107E18 2D288000 */  daddu      $a1, $a0, $zero
    /* 7E1C 00107E1C 0000B0DF */  ld         $s0, 0x0($sp)
    /* 7E20 00107E20 BC600408 */  j          func_001182F0
    /* 7E24 00107E24 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_00107DD8
```
