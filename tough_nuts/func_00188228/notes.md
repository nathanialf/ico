
---

## Attempt at 2026-05-08

**Reason parked:** wrap-1jal-array-init: regalloc swap a2/v0/v1 vs a1/v1/v0 between original and ee-gcc 2.9

Seed: `tough_nuts/func_00188228/088228.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00188228; check asm/matchings/cod/088228/)
```

---

## Attempt at 2026-05-13

**Reason parked:** reg alloc n in a0 vs expected a1; multiple register swaps

Seed: `tough_nuts/func_00188228/088228.c.new`

Disassembly excerpt:

```
glabel func_00188228
    /* 88228 00188228 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 8822C 0018822C 0000BFFF */  sd         $ra, 0x0($sp)
    /* 88230 00188230 C02C060C */  jal        func_0018B300
    /* 88234 00188234 00000000 */   nop
    /* 88238 00188238 2D184000 */  daddu      $v1, $v0, $zero
    /* 8823C 0018823C 0800658C */  lw         $a1, 0x8($v1)
    /* 88240 00188240 4C000224 */  addiu      $v0, $zero, 0x4C
    /* 88244 00188244 10006424 */  addiu      $a0, $v1, 0x10
    /* 88248 00188248 549E83AF */  sw         $v1, %gp_rel(D_00632744)($gp)
    /* 8824C 0018824C 1810A200 */  mult       $v0, $a1, $v0
    /* 88250 00188250 589E85AF */  sw         $a1, %gp_rel(D_00632748)($gp)
    /* 88254 00188254 0B00A018 */  blez       $a1, .L00188284
    /* 88258 00188258 21308200 */   addu      $a2, $a0, $v0
    /* 8825C 0018825C 58006224 */  addiu      $v0, $v1, 0x58
    /* 88260 00188260 2D18A000 */  daddu      $v1, $a1, $zero
    /* 88264 00188264 00000000 */  nop
.align 2
  .L00188268:
    /* 88268 00188268 000046AC */  sw         $a2, 0x0($v0)
    /* 8826C 0018826C FFFF6324 */  addiu      $v1, $v1, -0x1
    /* 88270 00188270 4C004224 */  addiu      $v0, $v0, 0x4C
    /* 88274 00188274 00000000 */  nop
    /* 88278 00188278 00000000 */  nop
    /* 8827C 0018827C FAFF6014 */  bnez       $v1, .L00188268
    /* 88280 00188280 00000000 */   nop
.align 2
  .L00188284:
    /* 88284 00188284 0000BFDF */  ld         $ra, 0x0($sp)
    /* 88288 00188288 EA250608 */  j          func_001897A8
    /* 8828C 0018828C 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_00188228
```
