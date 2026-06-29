# ChangeStageStartInfo — parked

VRAM: 0x001B50B0 (file_off 0x0B50B0)
Asm source: asm/aug6/nonmatchings/common/src/sceneManager/ChangeStageStartInfo.s

## Attempt at 2026-06-29

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=9). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/sceneManager.c`

**Seed:** `tough_nuts/ChangeStageStartInfo/ChangeStageStartInfo.c`

Disassembly:

```
.align 3
nonmatching ChangeStageStartInfo, 0x150

glabel ChangeStageStartInfo
    /* B50B0 001B50B0 2D388000 */  daddu      $7, $4, $0
    /* B50B4 001B50B4 4C000324 */  addiu      $3, $0, 0x4C
    /* B50B8 001B50B8 1818E300 */  mult       $3, $7, $3
    /* B50BC 001B50BC B0FFBD27 */  addiu      $29, $29, -0x50
    /* B50C0 001B50C0 2A00023C */  lui        $2, %hi(D_002A0A90)
    /* B50C4 001B50C4 2000B2FF */  sd         $18, 0x20($29)
    /* B50C8 001B50C8 4000BFFF */  sd         $31, 0x40($29)
    /* B50CC 001B50CC 900A4224 */  addiu      $2, $2, %lo(D_002A0A90)
    /* B50D0 001B50D0 3000B3FF */  sd         $19, 0x30($29)
    /* B50D4 001B50D4 64000524 */  addiu      $5, $0, 0x64
    /* B50D8 001B50D8 1000B1FF */  sd         $17, 0x10($29)
    /* B50DC 001B50DC 21186200 */  addu       $3, $3, $2
    /* B50E0 001B50E0 0000B0FF */  sd         $16, 0x0($29)
    /* B50E4 001B50E4 2A00043C */  lui        $4, %hi(D_0029F060)
    /* B50E8 001B50E8 60F08424 */  addiu      $4, $4, %lo(D_0029F060)
    /* B50EC 001B50EC 46006690 */  lbu        $6, 0x46($3)
    /* B50F0 001B50F0 1828C500 */  mult       $5, $6, $5
    /* B50F4 001B50F4 2190A400 */  addu       $18, $5, $4
    /* B50F8 001B50F8 4400428E */  lw         $2, 0x44($18)
    /* B50FC 001B50FC 39004010 */  beqz       $2, .L001B51E4
    /* B5100 001B5100 44007094 */   lhu       $16, 0x44($3)
    /* B5104 001B5104 37000012 */  beqz       $16, .L001B51E4
    /* B5108 001B5108 04000224 */   addiu     $2, $0, 0x4
    /* B510C 001B510C 3600C210 */  beq        $6, $2, .L001B51E8
    /* B5110 001B5110 4000BFDF */   ld        $31, 0x40($29)
    /* B5114 001B5114 74F9040C */  jal        isysGObjAddHead
    /* B5118 001B5118 2D20E000 */   daddu     $4, $7, $0
    /* B511C 001B511C 2D984000 */  daddu      $19, $2, $0
    /* B5120 001B5120 74F9040C */  jal        isysGObjAddHead
    /* B5124 001B5124 2D200002 */   daddu     $4, $16, $0
    /* B5128 001B5128 2D884000 */  daddu      $17, $2, $0
    /* B512C 001B512C 1A002052 */  beql       $17, $0, .L001B5198
    /* B5130 001B5130 6100043C */   lui       $4, %hi(D_0060FD08)
    /* B5134 001B5134 10003316 */  bne        $17, $19, .L001B5178
    /* B5138 001B5138 6100043C */   lui       $4, %hi(D_0060FCF8)
    /* B513C 001B513C 6100043C */  lui        $4, %hi(D_0060FC98)
    /* B5140 001B5140 2D284002 */  daddu      $5, $18, $0
    /* B5144 001B5144 F290060C */  jal        debug_assertMessage
    /* B5148 001B5148 98FC8424 */   addiu     $4, $4, %lo(D_0060FC98)
    /* B514C 001B514C 6100103C */  lui        $16, %hi(D_0060FCE0)
    /* B5150 001B5150 E7010524 */  addiu      $5, $0, 0x1E7
    /* B5154 001B5154 E0FC1026 */  addiu      $16, $16, %lo(D_0060FCE0)
    /* B5158 001B5158 40AB060C */  jal        func_001AAD00
    /* B515C 001B515C 2D200002 */   daddu     $4, $16, $0
    /* B5160 001B5160 6300063C */  lui        $6, %hi(D_0062D2D0)
    /* B5164 001B5164 2D200002 */  daddu      $4, $16, $0
    /* B5168 001B5168 D0D2C624 */  addiu      $6, $6, %lo(D_0062D2D0)
    /* B516C 001B516C E080090C */  jal        func_00260380
    /* B5170 001B5170 E7010524 */   addiu     $5, $0, 0x1E7
    /* B5174 001B5174 6100043C */  lui        $4, %hi(D_0060FCF8)
.align 2
  .L001B5178:
    /* B5178 001B5178 2D284002 */  daddu      $5, $18, $0
    /* B517C 001B517C F290060C */  jal        debug_assertMessage
    /* B5180 001B5180 F8FC8424 */   addiu     $4, $4, %lo(D_0060FCF8)
    /* B5184 001B5184 5C01628E */  lw         $2, 0x15C($19)
    /* B5188 001B5188 000051AC */  sw         $17, 0x0($2)
    /* B518C 001B518C 5C01638E */  lw         $3, 0x15C($19)
    /* B5190 001B5190 14000010 */  b          .L001B51E4
    /* B5194 001B5194 040060AC */   sw        $0, 0x4($3)
.align 2
  .L001B5198:
    /* B5198 001B5198 2D284002 */  daddu      $5, $18, $0
    /* B519C 001B519C F290060C */  jal        debug_assertMessage
    /* B51A0 001B51A0 08FD8424 */   addiu     $4, $4, %lo(D_0060FD08)
    /* B51A4 001B51A4 6100103C */  lui        $16, %hi(D_0060FCE0)
    /* B51A8 001B51A8 F0010524 */  addiu      $5, $0, 0x1F0
    /* B51AC 001B51AC E0FC1026 */  addiu      $16, $16, %lo(D_0060FCE0)
    /* B51B0 001B51B0 40AB060C */  jal        func_001AAD00
    /* B51B4 001B51B4 2D200002 */   daddu     $4, $16, $0
    /* B51B8 001B51B8 2D200002 */  daddu      $4, $16, $0
    /* B51BC 001B51BC 6300063C */  lui        $6, %hi(D_0062D2D0)
    /* B51C0 001B51C0 4000BFDF */  ld         $31, 0x40($29)
    /* B51C4 001B51C4 D0D2C624 */  addiu      $6, $6, %lo(D_0062D2D0)
    /* B51C8 001B51C8 3000B3DF */  ld         $19, 0x30($29)
    /* B51CC 001B51CC F0010524 */  addiu      $5, $0, 0x1F0
    /* B51D0 001B51D0 2000B2DF */  ld         $18, 0x20($29)
    /* B51D4 001B51D4 1000B1DF */  ld         $17, 0x10($29)
    /* B51D8 001B51D8 0000B0DF */  ld         $16, 0x0($29)
    /* B51DC 001B51DC E0800908 */  j          func_00260380
    /* B51E0 001B51E0 5000BD27 */   addiu     $29, $29, 0x50
.align 2
  .L001B51E4:
    /* B51E4 001B51E4 4000BFDF */  ld         $31, 0x40($29)
.align 2
  .L001B51E8:
    /* B51E8 001B51E8 3000B3DF */  ld         $19, 0x30($29)
    /* B51EC 001B51EC 2000B2DF */  ld         $18, 0x20($29)
    /* B51F0 001B51F0 1000B1DF */  ld         $17, 0x10($29)
    /* B51F4 001B51F4 0000B0DF */  ld         $16, 0x0($29)
    /* B51F8 001B51F8 0800E003 */  jr         $31
    /* B51FC 001B51FC 5000BD27 */   addiu     $29, $29, 0x50
endlabel ChangeStageStartInfo
```
