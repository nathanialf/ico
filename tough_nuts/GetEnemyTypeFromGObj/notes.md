# GetEnemyTypeFromGObj — parked

VRAM: 0x00163B50 (file_off 0x063B50)
Asm source: asm/aug6/nonmatchings/fumi/src/enemy_act/GetEnemyTypeFromGObj.s

## Attempt at 2026-07-07

**Reason parked:** rc10 strength-reduction/regalloc permuter-class: p164->670 base is register-held (not a global) so gcc forms a walking-pointer giv (bne+addiu32) where ROM keeps i<<5 mult + base reload (bnel). p164 lands v0 not a1; all coupled to the giv. Distinct shapes (int do-while, char* for, inline-3x, struct-typed, separate-temp) fold to rc10/rc13 — stall cannot reach 30. Seed=rc10 char* for-loop for permuter.

**TU:** `fumi/src/enemy_act.c`

**Seed:** `tough_nuts/GetEnemyTypeFromGObj/GetEnemyTypeFromGObj.c`

Disassembly:

```
.align 3
nonmatching GetEnemyTypeFromGObj, 0xA8

glabel GetEnemyTypeFromGObj
    /* 63B50 00163B50 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 63B54 00163B54 0000B0FF */  sd         $16, 0x0($29)
    /* 63B58 00163B58 2D808000 */  daddu      $16, $4, $0
    /* 63B5C 00163B5C 2000BFFF */  sd         $31, 0x20($29)
    /* 63B60 00163B60 1000B1FF */  sd         $17, 0x10($29)
    /* 63B64 00163B64 8EF9040C */  jal        isysGObjSearchFromObjLayoutID
    /* 63B68 00163B68 04000424 */   addiu     $4, $0, 0x4
    /* 63B6C 00163B6C 2D204000 */  daddu      $4, $2, $0
    /* 63B70 00163B70 1C008010 */  beqz       $4, .L00163BE4
    /* 63B74 00163B74 03001124 */   addiu     $17, $0, 0x3
    /* 63B78 00163B78 6401858C */  lw         $5, 0x164($4)
    /* 63B7C 00163B7C 00000000 */  nop
.align 2
  .L00163B80:
    /* 63B80 00163B80 7006A28C */  lw         $2, 0x670($5)
    /* 63B84 00163B84 DC01438C */  lw         $3, 0x1DC($2)
    /* 63B88 00163B88 11007114 */  bne        $3, $17, .L00163BD0
    /* 63B8C 00163B8C 2D30A000 */   daddu     $6, $5, $0
    /* 63B90 00163B90 2D280000 */  daddu      $5, $0, $0
    /* 63B94 00163B94 7006C28C */  lw         $2, 0x670($6)
.align 2
  .L00163B98:
    /* 63B98 00163B98 40190500 */  sll        $3, $5, 5
    /* 63B9C 00163B9C 21186200 */  addu       $3, $3, $2
    /* 63BA0 00163BA0 60036324 */  addiu      $3, $3, 0x360
    /* 63BA4 00163BA4 1D006280 */  lb         $2, 0x1D($3)
    /* 63BA8 00163BA8 06004010 */  beqz       $2, .L00163BC4
    /* 63BAC 00163BAC 0100A524 */   addiu     $5, $5, 0x1
    /* 63BB0 00163BB0 1000628C */  lw         $2, 0x10($3)
    /* 63BB4 00163BB4 04005014 */  bne        $2, $16, .L00163BC8
    /* 63BB8 00163BB8 0500A228 */   slti      $2, $5, 0x5
    /* 63BBC 00163BBC 09000010 */  b          .L00163BE4
    /* 63BC0 00163BC0 1C0060A0 */   sb        $0, 0x1C($3)
.align 2
  .L00163BC4:
    /* 63BC4 00163BC4 0500A228 */  slti       $2, $5, 0x5
.align 2
  .L00163BC8:
    /* 63BC8 00163BC8 F3FF4054 */  bnel       $2, $0, .L00163B98
    /* 63BCC 00163BCC 7006C28C */   lw        $2, 0x670($6)
.align 2
  .L00163BD0:
    /* 63BD0 00163BD0 B2F9040C */  jal        isysGObjSearchFromObjKindID_begin
    /* 63BD4 00163BD4 00000000 */   nop
    /* 63BD8 00163BD8 2D204000 */  daddu      $4, $2, $0
    /* 63BDC 00163BDC E8FF8054 */  bnel       $4, $0, .L00163B80
    /* 63BE0 00163BE0 6401858C */   lw        $5, 0x164($4)
.align 2
  .L00163BE4:
    /* 63BE4 00163BE4 2000BFDF */  ld         $31, 0x20($29)
    /* 63BE8 00163BE8 1000B1DF */  ld         $17, 0x10($29)
    /* 63BEC 00163BEC 0000B0DF */  ld         $16, 0x0($29)
    /* 63BF0 00163BF0 0800E003 */  jr         $31
    /* 63BF4 00163BF4 3000BD27 */   addiu     $29, $29, 0x30
endlabel GetEnemyTypeFromGObj
```
