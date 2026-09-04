
---

## Attempt at 2026-05-08

**Reason parked:** volatile prevents CSE of stored value with TCO arg; gcc emits separate a1/a0 setup vs target single a0 reused for both

Seed: `tough_nuts/func_001A3340/0A3340.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001A3340; check asm/matchings/cod/0A3340/)
```

---

## Attempt at 2026-05-13

**Reason parked:** reg alloc: 0x82 in a1 not a0; gcc reloads a0 separately for TCO

Seed: `tough_nuts/func_001A3340/0A3340.c.new`

Disassembly excerpt:

```
glabel func_001A3340
    /* A3340 001A3340 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* A3344 001A3344 0000BFFF */  sd         $ra, 0x0($sp)
    /* A3348 001A3348 BAA7060C */  jal        debug_ClearFontWindow
    /* A334C 001A334C 00000000 */   nop
    /* A3350 001A3350 0010023C */  lui        $v0, (0x10000010 >> 16)
    /* A3354 001A3354 A0A380AF */  sw         $zero, %gp_rel(D_00632C90)($gp)
    /* A3358 001A3358 A4A380AF */  sw         $zero, %gp_rel(D_00632C94)($gp)
    /* A335C 001A335C 82000424 */  addiu      $a0, $zero, 0x82
    /* A3360 001A3360 A8A380AF */  sw         $zero, %gp_rel(D_00632C98)($gp)
    /* A3364 001A3364 10004234 */  ori        $v0, $v0, (0x10000010 & 0xFFFF)
    /* A3368 001A3368 ACA380AF */  sw         $zero, %gp_rel(D_00632C9C)($gp)
    /* A336C 001A336C 0010033C */  lui        $v1, (0x10000810 >> 16)
    /* A3370 001A3370 B0A380AF */  sw         $zero, %gp_rel(D_00632CA0)($gp)
    /* A3374 001A3374 10086334 */  ori        $v1, $v1, (0x10000810 & 0xFFFF)
    /* A3378 001A3378 B4A380AF */  sw         $zero, %gp_rel(D_00632CA4)($gp)
    /* A337C 001A337C 54A480AF */  sw         $zero, %gp_rel(D_00632D44)($gp)
    /* A3380 001A3380 000044AC */  sw         $a0, 0x0($v0)
    /* A3384 001A3384 0000BFDF */  ld         $ra, 0x0($sp)
    /* A3388 001A3388 000064AC */  sw         $a0, 0x0($v1)
    /* A338C 001A338C 0E8F0608 */  j          func_001A3C38
    /* A3390 001A3390 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_001A3340
```

---

## Attempt at 2026-05-13

**Reason parked:** ld ra placement between 2 MMIO stores

Seed: `tough_nuts/func_001A3340/0A3340.c.new`

Disassembly excerpt:

```
glabel func_001A3340
    /* A3340 001A3340 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* A3344 001A3344 0000BFFF */  sd         $ra, 0x0($sp)
    /* A3348 001A3348 BAA7060C */  jal        debug_ClearFontWindow
    /* A334C 001A334C 00000000 */   nop
    /* A3350 001A3350 0010023C */  lui        $v0, (0x10000010 >> 16)
    /* A3354 001A3354 A0A380AF */  sw         $zero, %gp_rel(D_00632C90)($gp)
    /* A3358 001A3358 A4A380AF */  sw         $zero, %gp_rel(D_00632C94)($gp)
    /* A335C 001A335C 82000424 */  addiu      $a0, $zero, 0x82
    /* A3360 001A3360 A8A380AF */  sw         $zero, %gp_rel(D_00632C98)($gp)
    /* A3364 001A3364 10004234 */  ori        $v0, $v0, (0x10000010 & 0xFFFF)
    /* A3368 001A3368 ACA380AF */  sw         $zero, %gp_rel(D_00632C9C)($gp)
    /* A336C 001A336C 0010033C */  lui        $v1, (0x10000810 >> 16)
    /* A3370 001A3370 B0A380AF */  sw         $zero, %gp_rel(D_00632CA0)($gp)
    /* A3374 001A3374 10086334 */  ori        $v1, $v1, (0x10000810 & 0xFFFF)
    /* A3378 001A3378 B4A380AF */  sw         $zero, %gp_rel(D_00632CA4)($gp)
    /* A337C 001A337C 54A480AF */  sw         $zero, %gp_rel(D_00632D44)($gp)
    /* A3380 001A3380 000044AC */  sw         $a0, 0x0($v0)
    /* A3384 001A3384 0000BFDF */  ld         $ra, 0x0($sp)
    /* A3388 001A3388 000064AC */  sw         $a0, 0x0($v1)
    /* A338C 001A338C 0E8F0608 */  j          func_001A3C38
    /* A3390 001A3390 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_001A3340
```
