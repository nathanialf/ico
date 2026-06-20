# func_00220A38 — parked

VRAM: 0x00220A38 (file_off 0x120A38)
Asm source: asm/aug6/nonmatchings/script/src/st08a/func_00220A38.s

## Attempt at 2026-06-13

**Reason parked:** scheduler filler tie rc6 — exact clone of func_00220918 (D_004CCB60/actSt05eWaterSwitch). 30 distinct shapes, none beat rc6. seed=int-cast arg-temp

**TU:** `script/src/st08a.c`

**Seed:** `tough_nuts/func_00220A38/func_00220A38.c`

Disassembly:

```
.align 3
nonmatching func_00220A38, 0x58

glabel func_00220A38
    /* 120A38 00220A38 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 120A3C 00220A3C 4D00023C */  lui        $2, %hi(D_004CCB60)
    /* 120A40 00220A40 0000A4AF */  sw         $4, 0x0($29)
    /* 120A44 00220A44 2200033C */  lui        $3, %hi(actSt05eWaterSwitch)
    /* 120A48 00220A48 1000BFFF */  sd         $31, 0x10($29)
    /* 120A4C 00220A4C 60CB4224 */  addiu      $2, $2, %lo(D_004CCB60)
    /* 120A50 00220A50 0000A58F */  lw         $5, 0x0($29)
    /* 120A54 00220A54 00D06324 */  addiu      $3, $3, %lo(actSt05eWaterSwitch)
    /* 120A58 00220A58 0000A48F */  lw         $4, 0x0($29)
    /* 120A5C 00220A5C 01000724 */  addiu      $7, $0, 0x1
    /* 120A60 00220A60 6401A68C */  lw         $6, 0x164($5)
    /* 120A64 00220A64 89010524 */  addiu      $5, $0, 0x189
    /* 120A68 00220A68 A49C87AF */  sw         $7, %gp_rel(D_0062A894)($28)
    /* 120A6C 00220A6C B400C2AC */  sw         $2, 0xB4($6)
    /* 120A70 00220A70 040043AC */  sw         $3, 0x4($2)
    /* 120A74 00220A74 F867050C */  jal        BoxBarSoundOn
    /* 120A78 00220A78 B000C0AC */   sw        $0, 0xB0($6)
    /* 120A7C 00220A7C 6004080C */  jal        _ACTWait
    /* 120A80 00220A80 2D200000 */   daddu     $4, $0, $0
    /* 120A84 00220A84 1000BFDF */  ld         $31, 0x10($29)
    /* 120A88 00220A88 0800E003 */  jr         $31
    /* 120A8C 00220A8C 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_00220A38
```

---

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=4). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `script/src/st08a.c`

**Seed:** `tough_nuts/func_00220A38/func_00220A38.1.c`

Disassembly:

```
.align 3
nonmatching func_00220A38, 0x58

glabel func_00220A38
    /* 120A38 00220A38 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 120A3C 00220A3C 4D00023C */  lui        $2, %hi(D_004CCB60)
    /* 120A40 00220A40 0000A4AF */  sw         $4, 0x0($29)
    /* 120A44 00220A44 2200033C */  lui        $3, %hi(actSt05eWaterSwitch)
    /* 120A48 00220A48 1000BFFF */  sd         $31, 0x10($29)
    /* 120A4C 00220A4C 60CB4224 */  addiu      $2, $2, %lo(D_004CCB60)
    /* 120A50 00220A50 0000A58F */  lw         $5, 0x0($29)
    /* 120A54 00220A54 00D06324 */  addiu      $3, $3, %lo(actSt05eWaterSwitch)
    /* 120A58 00220A58 0000A48F */  lw         $4, 0x0($29)
    /* 120A5C 00220A5C 01000724 */  addiu      $7, $0, 0x1
    /* 120A60 00220A60 6401A68C */  lw         $6, 0x164($5)
    /* 120A64 00220A64 89010524 */  addiu      $5, $0, 0x189
    /* 120A68 00220A68 A49C87AF */  sw         $7, %gp_rel(D_0062A894)($28)
    /* 120A6C 00220A6C B400C2AC */  sw         $2, 0xB4($6)
    /* 120A70 00220A70 040043AC */  sw         $3, 0x4($2)
    /* 120A74 00220A74 F867050C */  jal        BoxBarSoundOn
    /* 120A78 00220A78 B000C0AC */   sw        $0, 0xB0($6)
    /* 120A7C 00220A7C 6004080C */  jal        _ACTWait
    /* 120A80 00220A80 2D200000 */   daddu     $4, $0, $0
    /* 120A84 00220A84 1000BFDF */  ld         $31, 0x10($29)
    /* 120A88 00220A88 0800E003 */  jr         $31
    /* 120A8C 00220A8C 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_00220A38
```
