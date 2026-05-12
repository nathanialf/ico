
---

## Attempt at 2026-05-09

**Reason parked:** size mismatch: built=0x30 expected=0x44 diff=-20

Seed: `tough_nuts/func_001381D0/0381D0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001381D0; check asm/matchings/cod/0381D0/)
```

---

## Attempt at 2026-05-12

**Reason parked:** self-init+call: scheduler differs in placement of sd v0,0(v1) (target: jal delay; built: before jal); regalloc swap

Seed: `tough_nuts/func_001381D0/0381D0.c.new`

Disassembly excerpt:

```
glabel func_001381D0
    /* 381D0 001381D0 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 381D4 001381D4 2D188000 */  daddu      $v1, $a0, $zero
    /* 381D8 001381D8 0000BFFF */  sd         $ra, 0x0($sp)
    /* 381DC 001381DC 0C000224 */  addiu      $v0, $zero, 0xC
    /* 381E0 001381E0 040062AC */  sw         $v0, 0x4($v1)
    /* 381E4 001381E4 FEFF0724 */  addiu      $a3, $zero, -0x2
    /* 381E8 001381E8 2800043C */  lui        $a0, %hi(D_00280F88)
    /* 381EC 001381EC 2D286000 */  daddu      $a1, $v1, $zero
    /* 381F0 001381F0 000062DC */  ld         $v0, 0x0($v1)
    /* 381F4 001381F4 880F8424 */  addiu      $a0, $a0, %lo(D_00280F88)
    /* 381F8 001381F8 2D300000 */  daddu      $a2, $zero, $zero
    /* 381FC 001381FC 24104700 */  and        $v0, $v0, $a3
    /* 38200 00138200 6EE9040C */  jal        func_0013A5B8
    /* 38204 00138204 000062FC */   sd        $v0, 0x0($v1)
    /* 38208 00138208 0000BFDF */  ld         $ra, 0x0($sp)
    /* 3820C 0013820C 0800E003 */  jr         $ra
    /* 38210 00138210 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_001381D0
```
