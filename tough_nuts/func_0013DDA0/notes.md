
---

## Attempt at 2026-05-08

**Reason parked:** regalloc swap: ee-gcc picks (v0,v1) and a0 for (D_A,D_B,counter); expected (v1,v0) and a1 — declaration order changes don't flip

Seed: `tough_nuts/func_0013DDA0/03DDA0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0013DDA0; check asm/matchings/cod/03DDA0/)
```

---

## Attempt at 2026-05-13

**Reason parked:** addiu v0/v1 swapped + addiu a1 placement

Seed: `tough_nuts/func_0013DDA0/03DDA0.c.new`

Disassembly excerpt:

```
glabel func_0013DDA0
    /* 3DDA0 0013DDA0 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 3DDA4 0013DDA4 2800033C */  lui        $v1, %hi(D_00281A70)
    /* 3DDA8 0013DDA8 2800023C */  lui        $v0, %hi(D_00281A90)
    /* 3DDAC 0013DDAC 0000BFFF */  sd         $ra, 0x0($sp)
    /* 3DDB0 0013DDB0 901A4224 */  addiu      $v0, $v0, %lo(D_00281A90)
    /* 3DDB4 0013DDB4 701A6324 */  addiu      $v1, $v1, %lo(D_00281A70)
    /* 3DDB8 0013DDB8 07000524 */  addiu      $a1, $zero, 0x7
    /* 3DDBC 0013DDBC 00000000 */  nop
.align 2
  .L0013DDC0:
    /* 3DDC0 0013DDC0 000060AC */  sw         $zero, 0x0($v1)
    /* 3DDC4 0013DDC4 FFFFA524 */  addiu      $a1, $a1, -0x1
    /* 3DDC8 0013DDC8 000040AC */  sw         $zero, 0x0($v0)
    /* 3DDCC 0013DDCC 04006324 */  addiu      $v1, $v1, 0x4
    /* 3DDD0 0013DDD0 04004224 */  addiu      $v0, $v0, 0x4
    /* 3DDD4 0013DDD4 FAFFA104 */  bgez       $a1, .L0013DDC0
    /* 3DDD8 0013DDD8 00000000 */   nop
    /* 3DDDC 0013DDDC 34F9040C */  jal        func_0013E4D0
    /* 3DDE0 0013DDE0 00000000 */   nop
    /* 3DDE4 0013DDE4 0000BFDF */  ld         $ra, 0x0($sp)
    /* 3DDE8 0013DDE8 DC9880AF */  sw         $zero, %gp_rel(D_006321CC)($gp)
    /* 3DDEC 0013DDEC E09880AF */  sw         $zero, %gp_rel(D_006321D0)($gp)
    /* 3DDF0 0013DDF0 62F70408 */  j          func_0013DD88
    /* 3DDF4 0013DDF4 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0013DDA0
```

---

## Attempt at 2026-05-14

**Reason parked:** addiu v0 vs v1 scheduling near-miss with REG pins

Seed: `tough_nuts/func_0013DDA0/03DDA0.c.new`

Disassembly excerpt:

```
glabel func_0013DDA0
    /* 3DDA0 0013DDA0 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 3DDA4 0013DDA4 2800033C */  lui        $v1, %hi(D_00281A70)
    /* 3DDA8 0013DDA8 2800023C */  lui        $v0, %hi(D_00281A90)
    /* 3DDAC 0013DDAC 0000BFFF */  sd         $ra, 0x0($sp)
    /* 3DDB0 0013DDB0 901A4224 */  addiu      $v0, $v0, %lo(D_00281A90)
    /* 3DDB4 0013DDB4 701A6324 */  addiu      $v1, $v1, %lo(D_00281A70)
    /* 3DDB8 0013DDB8 07000524 */  addiu      $a1, $zero, 0x7
    /* 3DDBC 0013DDBC 00000000 */  nop
.align 2
  .L0013DDC0:
    /* 3DDC0 0013DDC0 000060AC */  sw         $zero, 0x0($v1)
    /* 3DDC4 0013DDC4 FFFFA524 */  addiu      $a1, $a1, -0x1
    /* 3DDC8 0013DDC8 000040AC */  sw         $zero, 0x0($v0)
    /* 3DDCC 0013DDCC 04006324 */  addiu      $v1, $v1, 0x4
    /* 3DDD0 0013DDD0 04004224 */  addiu      $v0, $v0, 0x4
    /* 3DDD4 0013DDD4 FAFFA104 */  bgez       $a1, .L0013DDC0
    /* 3DDD8 0013DDD8 00000000 */   nop
    /* 3DDDC 0013DDDC 34F9040C */  jal        func_0013E4D0
    /* 3DDE0 0013DDE0 00000000 */   nop
    /* 3DDE4 0013DDE4 0000BFDF */  ld         $ra, 0x0($sp)
    /* 3DDE8 0013DDE8 DC9880AF */  sw         $zero, %gp_rel(D_006321CC)($gp)
    /* 3DDEC 0013DDEC E09880AF */  sw         $zero, %gp_rel(D_006321D0)($gp)
    /* 3DDF0 0013DDF0 62F70408 */  j          func_0013DD88
    /* 3DDF4 0013DDF4 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0013DDA0
```
