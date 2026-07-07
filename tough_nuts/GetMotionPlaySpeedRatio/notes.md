# GetMotionPlaySpeedRatio — parked

VRAM: 0x001DDD28 (file_off 0x0DDD28)
Asm source: asm/aug6/nonmatchings/sugipon/src/motionOrientManager/GetMotionPlaySpeedRatio.s

## Attempt at 2026-07-06

**Reason parked:** permuter-class blocker rc12; ~8 codegen sigs, hand-exhausted; queued for dedicated permuter pass

**TU:** `sugipon/src/motionOrientManager.c`

**Seed:** `tough_nuts/GetMotionPlaySpeedRatio/GetMotionPlaySpeedRatio.c`

Disassembly:

```
.align 3
nonmatching GetMotionPlaySpeedRatio, 0xE0

glabel GetMotionPlaySpeedRatio
    /* DDD28 001DDD28 A0FFBD27 */  addiu      $29, $29, -0x60
    /* DDD2C 001DDD2C 2000B2FF */  sd         $18, 0x20($29)
    /* DDD30 001DDD30 5000BFFF */  sd         $31, 0x50($29)
    /* DDD34 001DDD34 2D908000 */  daddu      $18, $4, $0
    /* DDD38 001DDD38 4000B4FF */  sd         $20, 0x40($29)
    /* DDD3C 001DDD3C 3000B3FF */  sd         $19, 0x30($29)
    /* DDD40 001DDD40 1000B1FF */  sd         $17, 0x10($29)
    /* DDD44 001DDD44 0000B0FF */  sd         $16, 0x0($29)
.align 2
  .L001DDD48:
    /* DDD48 001DDD48 68AB828F */  lw         $2, %gp_rel(D_0062B758)($28)
    /* DDD4C 001DDD4C 80891200 */  sll        $17, $18, 6
    /* DDD50 001DDD50 FFFF1424 */  addiu      $20, $0, -0x1
    /* DDD54 001DDD54 1614040C */  jal        func_00105058
    /* DDD58 001DDD58 21985100 */   addu      $19, $2, $17
    /* DDD5C 001DDD5C 9837040C */  jal        GetTableCos
    /* DDD60 001DDD60 00000000 */   nop
    /* DDD64 001DDD64 584B070C */  jal        ResetStatic2MotionManager
    /* DDD68 001DDD68 2D204002 */   daddu     $4, $18, $0
    /* DDD6C 001DDD6C 6CAB828F */  lw         $2, %gp_rel(D_0062B75C)($28)
    /* DDD70 001DDD70 5C01438C */  lw         $3, 0x15C($2)
    /* DDD74 001DDD74 0C00708C */  lw         $16, 0xC($3)
    /* DDD78 001DDD78 1E14040C */  jal        func_00105078
    /* DDD7C 001DDD7C 21801102 */   addu      $16, $16, $17
    /* DDD80 001DDD80 2D200002 */  daddu      $4, $16, $0
    /* DDD84 001DDD84 4817040C */  jal        MatrixDrive_TurnXObjectMatrixYZ
    /* DDD88 001DDD88 2D284000 */   daddu     $5, $2, $0
    /* DDD8C 001DDD8C 30B6908F */  lw         $16, %gp_rel(D_0062C220)($28)
    /* DDD90 001DDD90 00111200 */  sll        $2, $18, 4
    /* DDD94 001DDD94 8C37040C */  jal        GetLastQuaternion
    /* DDD98 001DDD98 21800202 */   addu      $16, $16, $2
    /* DDD9C 001DDD9C 2D200002 */  daddu      $4, $16, $0
    /* DDDA0 001DDDA0 F036040C */  jal        GetInverseQuaternion
    /* DDDA4 001DDDA4 2D284000 */   daddu     $5, $2, $0
    /* DDDA8 001DDDA8 3000648E */  lw         $4, 0x30($19)
    /* DDDAC 001DDDAC 03009410 */  beq        $4, $20, .L001DDDBC
    /* DDDB0 001DDDB0 00000000 */   nop
    /* DDDB4 001DDDB4 4A77070C */  jal        GetMotionPlaySpeedRatio
    /* DDDB8 001DDDB8 00000000 */   nop
.align 2
  .L001DDDBC:
    /* DDDBC 001DDDBC 1A14040C */  jal        func_00105068
    /* DDDC0 001DDDC0 00000000 */   nop
    /* DDDC4 001DDDC4 AE37040C */  jal        InitTableSin
    /* DDDC8 001DDDC8 00000000 */   nop
    /* DDDCC 001DDDCC 3400648E */  lw         $4, 0x34($19)
    /* DDDD0 001DDDD0 00000000 */  nop
    /* DDDD4 001DDDD4 00000000 */  nop
    /* DDDD8 001DDDD8 00000000 */  nop
    /* DDDDC 001DDDDC 00000000 */  nop
    /* DDDE0 001DDDE0 D9FF9414 */  bne        $4, $20, .L001DDD48
    /* DDDE4 001DDDE4 2D908000 */   daddu     $18, $4, $0
    /* DDDE8 001DDDE8 5000BFDF */  ld         $31, 0x50($29)
    /* DDDEC 001DDDEC 4000B4DF */  ld         $20, 0x40($29)
    /* DDDF0 001DDDF0 3000B3DF */  ld         $19, 0x30($29)
    /* DDDF4 001DDDF4 2000B2DF */  ld         $18, 0x20($29)
    /* DDDF8 001DDDF8 1000B1DF */  ld         $17, 0x10($29)
    /* DDDFC 001DDDFC 0000B0DF */  ld         $16, 0x0($29)
    /* DDE00 001DDE00 0800E003 */  jr         $31
    /* DDE04 001DDE04 6000BD27 */   addiu     $29, $29, 0x60
endlabel GetMotionPlaySpeedRatio
```
