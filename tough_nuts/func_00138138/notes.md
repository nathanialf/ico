
---

## Attempt at 2026-05-12

**Reason parked:** two-entry function (glabel+alabel): 0x138138 has 2-insn 'restore sp' prefix before 0x138140 body

Seed: `tough_nuts/func_00138138/038138.c`

Disassembly excerpt:

```
glabel func_00138138
    /* 38138 00138138 1000BD27 */  addiu      $sp, $sp, 0x10
    /* 3813C 0013813C 00000000 */  nop
.align 2
  alabel func_00138140
    /* 38140 00138140 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 38144 00138144 2D188000 */  daddu      $v1, $a0, $zero
    /* 38148 00138148 0000BFFF */  sd         $ra, 0x0($sp)
    /* 3814C 0013814C 0A000224 */  addiu      $v0, $zero, 0xA
    /* 38150 00138150 040062AC */  sw         $v0, 0x4($v1)
    /* 38154 00138154 FEFF0724 */  addiu      $a3, $zero, -0x2
    /* 38158 00138158 480065AC */  sw         $a1, 0x48($v1)
    /* 3815C 0013815C 2800043C */  lui        $a0, %hi(D_00280F88)
    /* 38160 00138160 000062DC */  ld         $v0, 0x0($v1)
    /* 38164 00138164 880F8424 */  addiu      $a0, $a0, %lo(D_00280F88)
    /* 38168 00138168 2D286000 */  daddu      $a1, $v1, $zero
    /* 3816C 0013816C 2D300000 */  daddu      $a2, $zero, $zero
    /* 38170 00138170 24104700 */  and        $v0, $v0, $a3
    /* 38174 00138174 6EE9040C */  jal        func_0013A5B8
    /* 38178 00138178 000062FC */   sd        $v0, 0x0($v1)
    /* 3817C 0013817C 0000BFDF */  ld         $ra, 0x0($sp)
    /* 38180 00138180 0800E003 */  jr         $ra
    /* 38184 00138184 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_00138138
```
