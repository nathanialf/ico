
---

## Attempt at 2026-05-12

**Reason parked:** scheduler chooses mov.s f16 vs addiu a1,1 in j delay slot; body matches, 1 op different

Seed: `tough_nuts/func_00180550/080550.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00180550; check asm/matchings/cod/080550/)
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss: a1 setup before mov.s in built, expected has a1 in jal delay slot

Seed: `tough_nuts/func_00180550/080550.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00180550; check asm/matchings/cod/080550/)
```

---

## Attempt at 2026-05-13

**Reason parked:** very close retry: lwc1 f15 misplaced between lui/addiu a0 + trailing align nop

Seed: `tough_nuts/func_00180550/080550.c.new`

Disassembly excerpt:

```
glabel func_00180550
    /* 80550 00180550 00608044 */  mtc1       $zero, $f12
    /* 80554 00180554 5600043C */  lui        $a0, %hi(D_0055A380)
    /* 80558 00180558 BC858FC7 */  lwc1       $f15, %gp_rel(D_00630EAC)($gp)
    /* 8055C 0018055C 80A38424 */  addiu      $a0, $a0, %lo(D_0055A380)
    /* 80560 00180560 003F013C */  lui        $at, (0x3F000000 >> 16)
    /* 80564 00180564 00888144 */  mtc1       $at, $f17
    /* 80568 00180568 46630046 */  mov.s      $f13, $f12
    /* 8056C 0018056C 86630046 */  mov.s      $f14, $f12
    /* 80570 00180570 06640046 */  mov.s      $f16, $f12
    /* 80574 00180574 FCBF0408 */  j          func_0012FFF0
    /* 80578 00180578 01000524 */   addiu     $a1, $zero, 0x1
endlabel func_00180550
```
