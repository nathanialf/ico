# CorrectStickInfo — parked

VRAM: 0x00152A78 (file_off 0x052A78)
Asm source: asm/aug6/nonmatchings/fumi/src/boyact/CorrectStickInfo.s

## Attempt at 2026-07-07

**Reason parked:** rc3: single tail if-conversion residual (slt vs bgtz for final if(q->0x368>0)return 1;return 0); structure fully recovered (unsigned range-dispatch, inverted-nest AF0 out-of-line, single-exit funnel); 10+ distinct tail shapes fold; permuter-class ifcvt

**TU:** `fumi/src/boyact.c`

**Seed:** `tough_nuts/CorrectStickInfo/CorrectStickInfo.c`

Disassembly:

```
.align 3
nonmatching CorrectStickInfo, 0xB4

glabel CorrectStickInfo
    /* 52A78 00152A78 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 52A7C 00152A7C F491828F */  lw         $2, %gp_rel(D_00629DE4)($28)
    /* 52A80 00152A80 1000BFFF */  sd         $31, 0x10($29)
    /* 52A84 00152A84 0D004014 */  bnez       $2, .L00152ABC
    /* 52A88 00152A88 0000B0FF */   sd        $16, 0x0($29)
    /* 52A8C 00152A8C 5500103C */  lui        $16, %hi(D_005525C8)
    /* 52A90 00152A90 03140524 */  addiu      $5, $0, 0x1403
    /* 52A94 00152A94 C8251026 */  addiu      $16, $16, %lo(D_005525C8)
    /* 52A98 00152A98 40AB060C */  jal        func_001AAD00
    /* 52A9C 00152A9C 2D200002 */   daddu     $4, $16, $0
    /* 52AA0 00152AA0 6300063C */  lui        $6, %hi(D_0062C3F8)
    /* 52AA4 00152AA4 2D200002 */  daddu      $4, $16, $0
    /* 52AA8 00152AA8 F8C3C624 */  addiu      $6, $6, %lo(D_0062C3F8)
    /* 52AAC 00152AAC E080090C */  jal        __assert
    /* 52AB0 00152AB0 03140524 */   addiu     $5, $0, 0x1403
    /* 52AB4 00152AB4 19000010 */  b          .L00152B1C
    /* 52AB8 00152AB8 2D100000 */   daddu     $2, $0, $0
.align 2
  .L00152ABC:
    /* 52ABC 00152ABC 6401458C */  lw         $5, 0x164($2)
    /* 52AC0 00152AC0 3000A48C */  lw         $4, 0x30($5)
    /* 52AC4 00152AC4 1300822C */  sltiu      $2, $4, 0x13
    /* 52AC8 00152AC8 0D004014 */  bnez       $2, .L00152B00
    /* 52ACC 00152ACC 15000224 */   addiu     $2, $0, 0x15
    /* 52AD0 00152AD0 1600822C */  sltiu      $2, $4, 0x16
    /* 52AD4 00152AD4 06004054 */  bnel       $2, $0, .L00152AF0
    /* 52AD8 00152AD8 7006A28C */   lw        $2, 0x670($5)
    /* 52ADC 00152ADC 1800822C */  sltiu      $2, $4, 0x18
    /* 52AE0 00152AE0 07004010 */  beqz       $2, .L00152B00
    /* 52AE4 00152AE4 15000224 */   addiu     $2, $0, 0x15
    /* 52AE8 00152AE8 0C000010 */  b          .L00152B1C
    /* 52AEC 00152AEC 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L00152AF0:
    /* 52AF0 00152AF0 9C02438C */  lw         $3, 0x29C($2)
    /* 52AF4 00152AF4 09006014 */  bnez       $3, .L00152B1C
    /* 52AF8 00152AF8 01000224 */   addiu     $2, $0, 0x1
    /* 52AFC 00152AFC 15000224 */  addiu      $2, $0, 0x15
.align 2
  .L00152B00:
    /* 52B00 00152B00 06008210 */  beq        $4, $2, .L00152B1C
    /* 52B04 00152B04 01000224 */   addiu     $2, $0, 0x1
    /* 52B08 00152B08 7806A28C */  lw         $2, 0x678($5)
    /* 52B0C 00152B0C 6803438C */  lw         $3, 0x368($2)
    /* 52B10 00152B10 0200601C */  bgtz       $3, .L00152B1C
    /* 52B14 00152B14 01000224 */   addiu     $2, $0, 0x1
    /* 52B18 00152B18 2D100000 */  daddu      $2, $0, $0
.align 2
  .L00152B1C:
    /* 52B1C 00152B1C 1000BFDF */  ld         $31, 0x10($29)
    /* 52B20 00152B20 0000B0DF */  ld         $16, 0x0($29)
    /* 52B24 00152B24 0800E003 */  jr         $31
    /* 52B28 00152B28 2000BD27 */   addiu     $29, $29, 0x20
endlabel CorrectStickInfo
    /* 52B2C 00152B2C 00000000 */  nop
```
