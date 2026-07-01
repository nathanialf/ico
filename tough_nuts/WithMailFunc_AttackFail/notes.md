# WithMailFunc_AttackFail — parked

VRAM: 0x00156080 (file_off 0x056080)
Asm source: asm/aug6/nonmatchings/fumi/src/commonact/WithMailFunc_AttackFail.s

## Attempt at 2026-07-01

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=19). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/commonact.c`

**Seed:** `tough_nuts/WithMailFunc_AttackFail/WithMailFunc_AttackFail.c`

Disassembly:

```
.align 3
nonmatching WithMailFunc_AttackFail, 0x168

glabel WithMailFunc_AttackFail
    /* 56080 00156080 2700023C */  lui        $2, %hi(D_00271240)
    /* 56084 00156084 0A000724 */  addiu      $7, $0, 0xA
    /* 56088 00156088 4012458C */  lw         $5, %lo(D_00271240)($2)
    /* 5608C 0015608C A0FFBD27 */  addiu      $29, $29, -0x60
    /* 56090 00156090 4000B1FF */  sd         $17, 0x40($29)
    /* 56094 00156094 40124224 */  addiu      $2, $2, %lo(D_00271240)
    /* 56098 00156098 1828A700 */  mult       $5, $5, $7
    /* 5609C 0015609C 3000B0FF */  sd         $16, 0x30($29)
    /* 560A0 001560A0 5000BFFF */  sd         $31, 0x50($29)
    /* 560A4 001560A4 3C000324 */  addiu      $3, $0, 0x3C
    /* 560A8 001560A8 0400468C */  lw         $6, 0x4($2)
    /* 560AC 001560AC 23186500 */  subu       $3, $3, $5
    /* 560B0 001560B0 0000A4AF */  sw         $4, 0x0($29)
    /* 560B4 001560B4 1A006600 */  div        $0, $3, $6
    /* 560B8 001560B8 0100C050 */  beql       $6, $0, .L001560C0
    /* 560BC 001560BC CD010000 */   break     0, 7
.align 2
  .L001560C0:
    /* 560C0 001560C0 0000A28F */  lw         $2, 0x0($29)
    /* 560C4 001560C4 0000A48F */  lw         $4, 0x0($29)
    /* 560C8 001560C8 6401508C */  lw         $16, 0x164($2)
    /* 560CC 001560CC 6401828C */  lw         $2, 0x164($4)
    /* 560D0 001560D0 900500C6 */  lwc1       $f0, 0x590($16)
    /* 560D4 001560D4 7806458C */  lw         $5, 0x678($2)
    /* 560D8 001560D8 EC05118E */  lw         $17, 0x5EC($16)
    /* 560DC 001560DC 1000A0E7 */  swc1       $f0, 0x10($29)
    /* 560E0 001560E0 0000A48F */  lw         $4, 0x0($29)
    /* 560E4 001560E4 940500C6 */  lwc1       $f0, 0x594($16)
    /* 560E8 001560E8 1400A0E7 */  swc1       $f0, 0x14($29)
    /* 560EC 001560EC 980501C6 */  lwc1       $f1, 0x598($16)
    /* 560F0 001560F0 1800A1E7 */  swc1       $f1, 0x18($29)
    /* 560F4 001560F4 12180000 */  mflo       $3
    /* 560F8 001560F8 80100300 */  sll        $2, $3, 2
    /* 560FC 001560FC 21104300 */  addu       $2, $2, $3
    /* 56100 00156100 3E74050C */  jal        ContinueCorrectPosition
    /* 56104 00156104 8003A2AC */   sw        $2, 0x380($5)
    /* 56108 00156108 040040C4 */  lwc1       $f0, 0x4($2)
    /* 5610C 0015610C 90050526 */  addiu      $5, $16, 0x590
    /* 56110 00156110 0000A48F */  lw         $4, 0x0($29)
    /* 56114 00156114 5810040C */  jal        CylinderCollision
    /* 56118 00156118 1400A0E7 */   swc1      $f0, 0x14($29)
    /* 5611C 0015611C 0000B08F */  lw         $16, 0x0($29)
    /* 56120 00156120 2000A427 */  addiu      $4, $29, 0x20
    /* 56124 00156124 80BF013C */  lui        $1, (0xBF800000 >> 16)
    /* 56128 00156128 00608144 */  mtc1       $1, $f12
    /* 5612C 0015612C 6401058E */  lw         $5, 0x164($16)
    /* 56130 00156130 0E00090C */  jal        func_00240038
    /* 56134 00156134 A004A524 */   addiu     $5, $5, 0x4A0
    /* 56138 00156138 2D200002 */  daddu      $4, $16, $0
    /* 5613C 0015613C 2E1A040C */  jal        dispPlane
    /* 56140 00156140 2000A527 */   addiu     $5, $29, 0x20
    /* 56144 00156144 00000000 */  nop
.align 2
  .L00156148:
    /* 56148 00156148 23002012 */  beqz       $17, .L001561D8
    /* 5614C 0015614C 00000000 */   nop
    /* 56150 00156150 0000A28F */  lw         $2, 0x0($29)
    /* 56154 00156154 5C01438C */  lw         $3, 0x15C($2)
    /* 56158 00156158 F405648C */  lw         $4, 0x5F4($3)
    /* 5615C 0015615C 16008010 */  beqz       $4, .L001561B8
    /* 56160 00156160 00000000 */   nop
    /* 56164 00156164 0C00238E */  lw         $3, 0xC($17)
    /* 56168 00156168 0000B08F */  lw         $16, 0x0($29)
    /* 5616C 0015616C 16006228 */  slti       $2, $3, 0x16
    /* 56170 00156170 0C004014 */  bnez       $2, .L001561A4
    /* 56174 00156174 18006228 */   slti      $2, $3, 0x18
    /* 56178 00156178 05004010 */  beqz       $2, .L00156190
    /* 5617C 0015617C 2000A427 */   addiu     $4, $29, 0x20
    /* 56180 00156180 78E5060C */  jal        pushStartSE
    /* 56184 00156184 2D282002 */   daddu     $5, $17, $0
    /* 56188 00156188 06000010 */  b          .L001561A4
    /* 5618C 0015618C 00000000 */   nop
.align 2
  .L00156190:
    /* 56190 00156190 1A006228 */  slti       $2, $3, 0x1A
    /* 56194 00156194 03004010 */  beqz       $2, .L001561A4
    /* 56198 00156198 00000000 */   nop
    /* 5619C 0015619C 78E6060C */  jal        WallLeverGeo
    /* 561A0 001561A0 2D282002 */   daddu     $5, $17, $0
.align 2
  .L001561A4:
    /* 561A4 001561A4 50838CC7 */  lwc1       $f12, %gp_rel(D_00628F40)($28)
    /* 561A8 001561A8 2D200002 */  daddu      $4, $16, $0
    /* 561AC 001561AC 16000524 */  addiu      $5, $0, 0x16
    /* 561B0 001561B0 840A040C */  jal        SetRootMatrixWithTransOffsetByDObj
    /* 561B4 001561B4 2000A627 */   addiu     $6, $29, 0x20
.align 2
  .L001561B8:
    /* 561B8 001561B8 0000A28F */  lw         $2, 0x0($29)
    /* 561BC 001561BC 5C01438C */  lw         $3, 0x15C($2)
    /* 561C0 001561C0 F005648C */  lw         $4, 0x5F0($3)
    /* 561C4 001561C4 04008010 */  beqz       $4, .L001561D8
    /* 561C8 001561C8 00000000 */   nop
    /* 561CC 001561CC 0000A48F */  lw         $4, 0x0($29)
    /* 561D0 001561D0 FE57050C */  jal        func_00155FF8
    /* 561D4 001561D4 2D282002 */   daddu     $5, $17, $0
.align 2
  .L001561D8:
    /* 561D8 001561D8 6004080C */  jal        _ACTWait
    /* 561DC 001561DC 01000424 */   addiu     $4, $0, 0x1
    /* 561E0 001561E0 D9FF0010 */  b          .L00156148
    /* 561E4 001561E4 00000000 */   nop
endlabel WithMailFunc_AttackFail
```
