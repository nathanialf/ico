
---

## Attempt at 2026-05-12

**Reason parked:** same gp_rel issue as func_00167258: D_006323C0 emitted as lui+addiu instead of gp_rel

Seed: `tough_nuts/func_00167230/067230.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00167230; check asm/matchings/cod/067230/)
```

---

## Attempt at 2026-05-12

**Reason parked:** ldl/ldr emits via addiu at,gp,0 indirection instead of direct gp_rel(D_X)(gp) offset embedded

Seed: `tough_nuts/func_00167230/067230.c.new`

Disassembly excerpt:

```
glabel func_00167230
    /* 67230 00167230 2D108000 */  daddu      $v0, $a0, $zero
    /* 67234 00167234 B00040AC */  sw         $zero, 0xB0($v0)
    /* 67238 00167238 940040AC */  sw         $zero, 0x94($v0)
    /* 6723C 0016723C 880040AC */  sw         $zero, 0x88($v0)
    /* 67240 00167240 D79A836B */  ldl        $v1, %gp_rel(D_006323C7)($gp)
    /* 67244 00167244 D09A836F */  ldr        $v1, %gp_rel(D_006323C0)($gp)
    /* 67248 00167248 870043B0 */  sdl        $v1, 0x87($v0)
    /* 6724C 0016724C 800043B4 */  sdr        $v1, 0x80($v0)
    /* 67250 00167250 849B0508 */  j          func_00166E10
    /* 67254 00167254 00000000 */   nop
endlabel func_00167230
```

---

## Attempt at 2026-05-13

**Reason parked:** gcc 2.9 won't fold gp_rel into ldl/ldr through packed-struct cast

Seed: `tough_nuts/func_00167230/067230.c.new`

Disassembly excerpt:

```
glabel func_00167230
    /* 67230 00167230 2D108000 */  daddu      $v0, $a0, $zero
    /* 67234 00167234 B00040AC */  sw         $zero, 0xB0($v0)
    /* 67238 00167238 940040AC */  sw         $zero, 0x94($v0)
    /* 6723C 0016723C 880040AC */  sw         $zero, 0x88($v0)
    /* 67240 00167240 D79A836B */  ldl        $v1, %gp_rel(D_006323C7)($gp)
    /* 67244 00167244 D09A836F */  ldr        $v1, %gp_rel(D_006323C0)($gp)
    /* 67248 00167248 870043B0 */  sdl        $v1, 0x87($v0)
    /* 6724C 0016724C 800043B4 */  sdr        $v1, 0x80($v0)
    /* 67250 00167250 849B0508 */  j          func_00166E10
    /* 67254 00167254 00000000 */   nop
endlabel func_00167230
```

---

## Attempt at 2026-05-13

**Reason parked:** ldl/ldr gp_rel D_006323C0 vs computed la base; packed struct cast forces addiu+ldl/ldr

Seed: `tough_nuts/func_00167230/067230.c.new`

Disassembly excerpt:

```
glabel func_00167230
    /* 67230 00167230 2D108000 */  daddu      $v0, $a0, $zero
    /* 67234 00167234 B00040AC */  sw         $zero, 0xB0($v0)
    /* 67238 00167238 940040AC */  sw         $zero, 0x94($v0)
    /* 6723C 0016723C 880040AC */  sw         $zero, 0x88($v0)
    /* 67240 00167240 D79A836B */  ldl        $v1, %gp_rel(D_006323C7)($gp)
    /* 67244 00167244 D09A836F */  ldr        $v1, %gp_rel(D_006323C0)($gp)
    /* 67248 00167248 870043B0 */  sdl        $v1, 0x87($v0)
    /* 6724C 0016724C 800043B4 */  sdr        $v1, 0x80($v0)
    /* 67250 00167250 849B0508 */  j          func_00166E10
    /* 67254 00167254 00000000 */   nop
endlabel func_00167230
```
