
---

## Attempt at 2026-05-12

**Reason parked:** queue slot calc: gcc reorders sw zero before addiu v0,-4 (scheduling difference)

Seed: `tough_nuts/func_00245228/145228.c`

Disassembly excerpt:

```
glabel func_00245228
    /* 145228 00245228 0000828C */  lw         $v0, 0x0($a0)
    /* 14522C 0024522C 0C00858C */  lw         $a1, 0xC($a0)
    /* 145230 00245230 FCFF4224 */  addiu      $v0, $v0, -0x4
    /* 145234 00245234 0C0080AC */  sw         $zero, 0xC($a0)
    /* 145238 00245238 23104500 */  subu       $v0, $v0, $a1
    /* 14523C 0024523C 0000A38C */  lw         $v1, 0x0($a1)
    /* 145240 00245240 83100200 */  sra        $v0, $v0, 2
    /* 145244 00245244 82100200 */  srl        $v0, $v0, 2
    /* 145248 00245248 21186200 */  addu       $v1, $v1, $v0
    /* 14524C 0024524C 0800E003 */  jr         $ra
    /* 145250 00245250 0000A3AC */   sw        $v1, 0x0($a1)
endlabel func_00245228
```

---

## Attempt at 2026-05-12

**Reason parked:** diff scaling matches; reg alloc differs (a0 for diff vs v0; v1 for p vs a1)

Seed: `tough_nuts/func_00245228/145228.c.new`

Disassembly excerpt:

```
glabel func_00245228
    /* 145228 00245228 0000828C */  lw         $v0, 0x0($a0)
    /* 14522C 0024522C 0C00858C */  lw         $a1, 0xC($a0)
    /* 145230 00245230 FCFF4224 */  addiu      $v0, $v0, -0x4
    /* 145234 00245234 0C0080AC */  sw         $zero, 0xC($a0)
    /* 145238 00245238 23104500 */  subu       $v0, $v0, $a1
    /* 14523C 0024523C 0000A38C */  lw         $v1, 0x0($a1)
    /* 145240 00245240 83100200 */  sra        $v0, $v0, 2
    /* 145244 00245244 82100200 */  srl        $v0, $v0, 2
    /* 145248 00245248 21186200 */  addu       $v1, $v1, $v0
    /* 14524C 0024524C 0800E003 */  jr         $ra
    /* 145250 00245250 0000A3AC */   sw        $v1, 0x0($a1)
endlabel func_00245228
```

---

## Attempt at 2026-05-12

**Reason parked:** addiu v0,-4 and sw zero,12(a0) reordered by scheduler; body identical otherwise

Seed: `tough_nuts/func_00245228/145228.c.new`

Disassembly excerpt:

```
glabel func_00245228
    /* 145228 00245228 0000828C */  lw         $v0, 0x0($a0)
    /* 14522C 0024522C 0C00858C */  lw         $a1, 0xC($a0)
    /* 145230 00245230 FCFF4224 */  addiu      $v0, $v0, -0x4
    /* 145234 00245234 0C0080AC */  sw         $zero, 0xC($a0)
    /* 145238 00245238 23104500 */  subu       $v0, $v0, $a1
    /* 14523C 0024523C 0000A38C */  lw         $v1, 0x0($a1)
    /* 145240 00245240 83100200 */  sra        $v0, $v0, 2
    /* 145244 00245244 82100200 */  srl        $v0, $v0, 2
    /* 145248 00245248 21186200 */  addu       $v1, $v1, $v0
    /* 14524C 0024524C 0800E003 */  jr         $ra
    /* 145250 00245250 0000A3AC */   sw        $v1, 0x0($a1)
endlabel func_00245228
```
