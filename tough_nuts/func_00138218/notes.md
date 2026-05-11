
---

## Attempt at 2026-05-09

**Reason parked:** size mismatch: built=0x30 expected=0x44 diff=-20

Seed: `tough_nuts/func_00138218/038218.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00138218; check asm/matchings/cod/038218/)
```

---

## Attempt at 2026-05-11

**Reason parked:** near-miss: regalloc — built uses a1 for self-copy + a2 for mask; expected uses v1 for self-copy + a3 for mask. Both gcc-correct but bytes differ.

Seed: `tough_nuts/func_00138218/038218.c.new`

Disassembly excerpt:

```
glabel func_00138218
    /* 38218 00138218 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 3821C 0013821C 2D188000 */  daddu      $v1, $a0, $zero
    /* 38220 00138220 0000BFFF */  sd         $ra, 0x0($sp)
    /* 38224 00138224 0D000224 */  addiu      $v0, $zero, 0xD
    /* 38228 00138228 040062AC */  sw         $v0, 0x4($v1)
    /* 3822C 0013822C FEFF0724 */  addiu      $a3, $zero, -0x2
    /* 38230 00138230 2800043C */  lui        $a0, %hi(D_00280F88)
    /* 38234 00138234 2D286000 */  daddu      $a1, $v1, $zero
    /* 38238 00138238 000062DC */  ld         $v0, 0x0($v1)
    /* 3823C 0013823C 880F8424 */  addiu      $a0, $a0, %lo(D_00280F88)
    /* 38240 00138240 2D300000 */  daddu      $a2, $zero, $zero
    /* 38244 00138244 24104700 */  and        $v0, $v0, $a3
    /* 38248 00138248 6EE9040C */  jal        func_0013A5B8
    /* 3824C 0013824C 000062FC */   sd        $v0, 0x0($v1)
    /* 38250 00138250 0000BFDF */  ld         $ra, 0x0($sp)
    /* 38254 00138254 0800E003 */  jr         $ra
    /* 38258 00138258 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_00138218
```
