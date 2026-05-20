
---

## Attempt at 2026-05-12

**Reason parked:** lui+addiu vs gp_rel addressing for D_006323C0 ldl/ldr — symbol needs proper sized typedef

Seed: `tough_nuts/func_00167258/067258.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00167258; check asm/matchings/cod/067258/)
```

---

## Attempt at 2026-05-12

**Reason parked:** packed struct gp_rel ldl/ldr goes via addiu a3, gp, 0 intermediate instead of 0(gp) direct

Seed: `tough_nuts/func_00167258/067258.c.new`

Disassembly excerpt:

```
glabel func_00167258
    /* 67258 00167258 2D108000 */  daddu      $v0, $a0, $zero
    /* 6725C 0016725C 940040AC */  sw         $zero, 0x94($v0)
    /* 67260 00167260 D79A836B */  ldl        $v1, %gp_rel(D_006323C7)($gp)
    /* 67264 00167264 D09A836F */  ldr        $v1, %gp_rel(D_006323C0)($gp)
    /* 67268 00167268 930043B0 */  sdl        $v1, 0x93($v0)
    /* 6726C 0016726C 8C0043B4 */  sdr        $v1, 0x8C($v0)
    /* 67270 00167270 849B0508 */  j          func_00166E10
    /* 67274 00167274 00000000 */   nop
endlabel func_00167258
```
