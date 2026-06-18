# actSt13aElevUp — parked

VRAM: 0x00224580 (file_off 0x124580)
Asm source: asm/aug6/nonmatchings/script/src/st13a/actSt13aElevUp.s

## Attempt at 2026-06-18

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=6). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `script/src/st13a.c`

**Seed:** `tough_nuts/actSt13aElevUp/actSt13aElevUp.c`

Disassembly:

```
.align 3
nonmatching actSt13aElevUp, 0x98

glabel actSt13aElevUp
    /* 124580 00224580 B0FFBD27 */  addiu      $29, $29, -0x50
    /* 124584 00224584 0000A4AF */  sw         $4, 0x0($29)
    /* 124588 00224588 4000BFFF */  sd         $31, 0x40($29)
    /* 12458C 0022458C 3000B2FF */  sd         $18, 0x30($29)
    /* 124590 00224590 2000B1FF */  sd         $17, 0x20($29)
    /* 124594 00224594 0000A28F */  lw         $2, 0x0($29)
    /* 124598 00224598 1000B0FF */  sd         $16, 0x10($29)
    /* 12459C 0022459C 6401508C */  lw         $16, 0x164($2)
    /* 1245A0 002245A0 4D00113C */  lui        $17, %hi(D_004CD380)
    /* 1245A4 002245A4 04000010 */  b          .L002245B8
    /* 1245A8 002245A8 2200123C */   lui       $18, %hi(actSt13aElevDownChk)
    /* 1245AC 002245AC 00000000 */  nop
.align 2
  .L002245B0:
    /* 1245B0 002245B0 6004080C */  jal        _ACTWait
    /* 1245B4 002245B4 01000424 */   addiu     $4, $0, 0x1
.align 2
  .L002245B8:
    /* 1245B8 002245B8 1AEE050C */  jal        actSt25aQueenDeadChk
    /* 1245BC 002245BC 5D060424 */   addiu     $4, $0, 0x65D
    /* 1245C0 002245C0 2D204000 */  daddu      $4, $2, $0
    /* 1245C4 002245C4 B4EB050C */  jal        scpSleepSpiderGroupOne
    /* 1245C8 002245C8 0002053C */   lui       $5, (0x2000000 >> 16)
    /* 1245CC 002245CC F8FF4010 */  beqz       $2, .L002245B0
    /* 1245D0 002245D0 00000000 */   nop
    /* 1245D4 002245D4 76E3050C */  jal        func_00178DD8
    /* 1245D8 002245D8 63000424 */   addiu     $4, $0, 0x63
    /* 1245DC 002245DC 80D32226 */  addiu      $2, $17, %lo(D_004CD380)
    /* 1245E0 002245E0 18464326 */  addiu      $3, $18, %lo(actSt13aElevDownChk)
    /* 1245E4 002245E4 0000A48F */  lw         $4, 0x0($29)
    /* 1245E8 002245E8 89010524 */  addiu      $5, $0, 0x189
    /* 1245EC 002245EC B40002AE */  sw         $2, 0xB4($16)
    /* 1245F0 002245F0 F867050C */  jal        BoxBarSoundOn
    /* 1245F4 002245F4 040043AC */   sw        $3, 0x4($2)
    /* 1245F8 002245F8 6004080C */  jal        _ACTWait
    /* 1245FC 002245FC 2D200000 */   daddu     $4, $0, $0
    /* 124600 00224600 4000BFDF */  ld         $31, 0x40($29)
    /* 124604 00224604 3000B2DF */  ld         $18, 0x30($29)
    /* 124608 00224608 2000B1DF */  ld         $17, 0x20($29)
    /* 12460C 0022460C 1000B0DF */  ld         $16, 0x10($29)
    /* 124610 00224610 0800E003 */  jr         $31
    /* 124614 00224614 5000BD27 */   addiu     $29, $29, 0x50
endlabel actSt13aElevUp
```
