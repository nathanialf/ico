# EBRAIN_SEND_MES — parked

VRAM: 0x00158030 (file_off 0x058030)
Asm source: asm/aug6/nonmatchings/fumi/src/commonact/EBRAIN_SEND_MES.s

## Attempt at 2026-06-24

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=43). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/commonact.c`

**Seed:** `tough_nuts/EBRAIN_SEND_MES/EBRAIN_SEND_MES.c`

Disassembly:

```
.align 3
nonmatching EBRAIN_SEND_MES, 0x148

glabel EBRAIN_SEND_MES
    /* 58030 00158030 D0FEBD27 */  addiu      $29, $29, -0x130
    /* 58034 00158034 0001B3FF */  sd         $19, 0x100($29)
    /* 58038 00158038 F000B2FF */  sd         $18, 0xF0($29)
    /* 5803C 0015803C 2D988000 */  daddu      $19, $4, $0
    /* 58040 00158040 E000B1FF */  sd         $17, 0xE0($29)
    /* 58044 00158044 2D90A000 */  daddu      $18, $5, $0
    /* 58048 00158048 D000B0FF */  sd         $16, 0xD0($29)
    /* 5804C 0015804C 1000B127 */  addiu      $17, $29, 0x10
    /* 58050 00158050 2001B4E7 */  swc1       $f20, 0x120($29)
    /* 58054 00158054 00840600 */  sll        $16, $6, 16
    /* 58058 00158058 03841000 */  sra        $16, $16, 16
    /* 5805C 0015805C 06650046 */  mov.s      $f20, $f12
    /* 58060 00158060 1001BFFF */  sd         $31, 0x110($29)
    /* 58064 00158064 2D202002 */  daddu      $4, $17, $0
    /* 58068 00158068 0000A2AF */  sw         $2, 0x0($29)
    /* 5806C 0015806C 2D280000 */  daddu      $5, $0, $0
    /* 58070 00158070 5A81090C */  jal        memset
    /* 58074 00158074 C0000624 */   addiu     $6, $0, 0xC0
    /* 58078 00158078 1E14040C */  jal        func_00105078
    /* 5807C 0015807C 00000000 */   nop
    /* 58080 00158080 A862040C */  jal        _UnitMatrix
    /* 58084 00158084 2D204000 */   daddu     $4, $2, $0
    /* 58088 00158088 2A14040C */  jal        func_001050A8
    /* 5808C 0015808C 2D204002 */   daddu     $4, $18, $0
    /* 58090 00158090 7013040C */  jal        MatrixDrive_RotMatrixY
    /* 58094 00158094 2D200002 */   daddu     $4, $16, $0
    /* 58098 00158098 00608044 */  mtc1       $0, $f12
    /* 5809C 0015809C 86A30046 */  mov.s      $f14, $f20
    /* 580A0 001580A0 4214040C */  jal        func_00105108
    /* 580A4 001580A4 46630046 */   mov.s     $f13, $f12
    /* 580A8 001580A8 1E14040C */  jal        func_00105078
    /* 580AC 001580AC 2000B027 */   addiu     $16, $29, 0x20
    /* 580B0 001580B0 30004524 */  addiu      $5, $2, 0x30
    /* 580B4 001580B4 4017040C */  jal        MatrixDrive_TurnObjectMatrix
    /* 580B8 001580B8 2D200002 */   daddu     $4, $16, $0
    /* 580BC 001580BC 2D202002 */  daddu      $4, $17, $0
    /* 580C0 001580C0 4017040C */  jal        MatrixDrive_TurnObjectMatrix
    /* 580C4 001580C4 2D284002 */   daddu     $5, $18, $0
    /* 580C8 001580C8 1400A2C7 */  lwc1       $f2, 0x14($29)
    /* 580CC 001580CC 2D202002 */  daddu      $4, $17, $0
    /* 580D0 001580D0 2400A0C7 */  lwc1       $f0, 0x24($29)
    /* 580D4 001580D4 4842013C */  lui        $1, (0x42480000 >> 16)
    /* 580D8 001580D8 00088144 */  mtc1       $1, $f1
    /* 580DC 001580DC 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* 580E0 001580E0 00188144 */  mtc1       $1, $f3
    /* 580E4 001580E4 01000146 */  sub.s      $f0, $f0, $f1
    /* 580E8 001580E8 81100146 */  sub.s      $f2, $f2, $f1
    /* 580EC 001580EC 1C00A3E7 */  swc1       $f3, 0x1C($29)
    /* 580F0 001580F0 2C00A3E7 */  swc1       $f3, 0x2C($29)
    /* 580F4 001580F4 2400A0E7 */  swc1       $f0, 0x24($29)
    /* 580F8 001580F8 7E98050C */  jal        ClipWallBoxStop
    /* 580FC 001580FC 1400A2E7 */   swc1      $f2, 0x14($29)
    /* 58100 00158100 9800A28F */  lw         $2, 0x98($29)
    /* 58104 00158104 14004014 */  bnez       $2, .L00158158
    /* 58108 00158108 2D100000 */   daddu     $2, $0, $0
    /* 5810C 0015810C 2D280002 */  daddu      $5, $16, $0
    /* 58110 00158110 4017040C */  jal        MatrixDrive_TurnObjectMatrix
    /* 58114 00158114 2D202002 */   daddu     $4, $17, $0
    /* 58118 00158118 2400A0C7 */  lwc1       $f0, 0x24($29)
    /* 5811C 0015811C 2D202002 */  daddu      $4, $17, $0
    /* 58120 00158120 C842013C */  lui        $1, (0x42C80000 >> 16)
    /* 58124 00158124 00088144 */  mtc1       $1, $f1
    /* 58128 00158128 00000146 */  add.s      $f0, $f0, $f1
    /* 5812C 0015812C DA98050C */  jal        ChangeFieldCollisionDebugMode
    /* 58130 00158130 2400A0E7 */   swc1      $f0, 0x24($29)
    /* 58134 00158134 A400A28F */  lw         $2, 0xA4($29)
    /* 58138 00158138 06004010 */  beqz       $2, .L00158154
    /* 5813C 0015813C 2D206002 */   daddu     $4, $19, $0
    /* 58140 00158140 2D304002 */  daddu      $6, $18, $0
    /* 58144 00158144 F861040C */  jal        _SubVectorXYZ
    /* 58148 00158148 3000A527 */   addiu     $5, $29, 0x30
    /* 5814C 0015814C 02000010 */  b          .L00158158
    /* 58150 00158150 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L00158154:
    /* 58154 00158154 2D100000 */  daddu      $2, $0, $0
.align 2
  .L00158158:
    /* 58158 00158158 1001BFDF */  ld         $31, 0x110($29)
    /* 5815C 0015815C 0001B3DF */  ld         $19, 0x100($29)
    /* 58160 00158160 F000B2DF */  ld         $18, 0xF0($29)
    /* 58164 00158164 E000B1DF */  ld         $17, 0xE0($29)
    /* 58168 00158168 D000B0DF */  ld         $16, 0xD0($29)
    /* 5816C 0015816C 2001B4C7 */  lwc1       $f20, 0x120($29)
    /* 58170 00158170 0800E003 */  jr         $31
    /* 58174 00158174 3001BD27 */   addiu     $29, $29, 0x130
endlabel EBRAIN_SEND_MES
```
