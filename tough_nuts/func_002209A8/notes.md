# func_002209A8 — parked

VRAM: 0x002209A8 (file_off 0x1209A8)
Asm source: asm/aug6/nonmatchings/script/src/st08a/func_002209A8.s

## Attempt at 2026-06-13

**Reason parked:** scheduler filler tie rc6 — exact clone of func_00220918 (D_004CCB00/actSt05eWaterMain). 30 distinct shapes (24 store orders + 6 temp/type), none beat rc6. seed=int-cast arg-temp

**TU:** `script/src/st08a.c`

**Seed:** `tough_nuts/func_002209A8/func_002209A8.c`

Disassembly:

```
.align 3
nonmatching func_002209A8, 0x58

glabel func_002209A8
    /* 1209A8 002209A8 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 1209AC 002209AC 4D00023C */  lui        $2, %hi(D_004CCB00)
    /* 1209B0 002209B0 0000A4AF */  sw         $4, 0x0($29)
    /* 1209B4 002209B4 2200033C */  lui        $3, %hi(actSt05eWaterMain)
    /* 1209B8 002209B8 1000BFFF */  sd         $31, 0x10($29)
    /* 1209BC 002209BC 00CB4224 */  addiu      $2, $2, %lo(D_004CCB00)
    /* 1209C0 002209C0 0000A58F */  lw         $5, 0x0($29)
    /* 1209C4 002209C4 D8CE6324 */  addiu      $3, $3, %lo(actSt05eWaterMain)
    /* 1209C8 002209C8 0000A48F */  lw         $4, 0x0($29)
    /* 1209CC 002209CC 01000724 */  addiu      $7, $0, 0x1
    /* 1209D0 002209D0 6401A68C */  lw         $6, 0x164($5)
    /* 1209D4 002209D4 89010524 */  addiu      $5, $0, 0x189
    /* 1209D8 002209D8 A49C87AF */  sw         $7, %gp_rel(D_0062A894)($28)
    /* 1209DC 002209DC B400C2AC */  sw         $2, 0xB4($6)
    /* 1209E0 002209E0 040043AC */  sw         $3, 0x4($2)
    /* 1209E4 002209E4 F867050C */  jal        BoxBarSoundOn
    /* 1209E8 002209E8 B000C0AC */   sw        $0, 0xB0($6)
    /* 1209EC 002209EC 6004080C */  jal        _ACTWait
    /* 1209F0 002209F0 2D200000 */   daddu     $4, $0, $0
    /* 1209F4 002209F4 1000BFDF */  ld         $31, 0x10($29)
    /* 1209F8 002209F8 0800E003 */  jr         $31
    /* 1209FC 002209FC 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_002209A8
```
