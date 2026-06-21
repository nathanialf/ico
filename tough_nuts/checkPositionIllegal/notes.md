# checkPositionIllegal — parked

VRAM: 0x001FE5E0 (file_off 0x0FE5E0)
Asm source: asm/aug6/nonmatchings/fumi/src/act-way/checkPositionIllegal.s

## Attempt at 2026-06-21

**Reason parked:** override=permute

**TU:** `fumi/src/act-way.c`

**Seed:** `tough_nuts/checkPositionIllegal/checkPositionIllegal.c`

Disassembly:

```
.align 3
nonmatching checkPositionIllegal, 0x130

glabel checkPositionIllegal
    /* FE5E0 001FE5E0 B0FFBD27 */  addiu      $29, $29, -0x50
    /* FE5E4 001FE5E4 2000B0FF */  sd         $16, 0x20($29)
    /* FE5E8 001FE5E8 3000BFFF */  sd         $31, 0x30($29)
    /* FE5EC 001FE5EC 2D808000 */  daddu      $16, $4, $0
    /* FE5F0 001FE5F0 4000B4E7 */  swc1       $f20, 0x40($29)
    /* FE5F4 001FE5F4 6C000424 */  addiu      $4, $0, 0x6C
    /* FE5F8 001FE5F8 6401028E */  lw         $2, 0x164($16)
    /* FE5FC 001FE5FC 3000438C */  lw         $3, 0x30($2)
    /* FE600 001FE600 35006410 */  beq        $3, $4, .L001FE6D8
    /* FE604 001FE604 2D30A000 */   daddu     $6, $5, $0
    /* FE608 001FE608 0800C2C4 */  lwc1       $f2, 0x8($6)
    /* FE60C 001FE60C 2D20A003 */  daddu      $4, $29, $0
    /* FE610 001FE610 0000C1C4 */  lwc1       $f1, 0x0($6)
    /* FE614 001FE614 2D280000 */  daddu      $5, $0, $0
    /* FE618 001FE618 0400C0C4 */  lwc1       $f0, 0x4($6)
    /* FE61C 001FE61C 2D380000 */  daddu      $7, $0, $0
    /* FE620 001FE620 C842013C */  lui        $1, (0x42C80000 >> 16)
    /* FE624 001FE624 00A08144 */  mtc1       $1, $f20
    /* FE628 001FE628 FF000624 */  addiu      $6, $0, 0xFF
    /* FE62C 001FE62C 0000A1E7 */  swc1       $f1, 0x0($29)
    /* FE630 001FE630 0400A0E7 */  swc1       $f0, 0x4($29)
    /* FE634 001FE634 06A30046 */  mov.s      $f12, $f20
    /* FE638 001FE638 1012060C */  jal        debug_Marker
    /* FE63C 001FE63C 0800A2E7 */   swc1      $f2, 0x8($29)
    /* FE640 001FE640 3E74050C */  jal        ContinueCorrectPosition
    /* FE644 001FE644 2D200002 */   daddu     $4, $16, $0
    /* FE648 001FE648 000040C4 */  lwc1       $f0, 0x0($2)
    /* FE64C 001FE64C 2D200002 */  daddu      $4, $16, $0
    /* FE650 001FE650 3E74050C */  jal        ContinueCorrectPosition
    /* FE654 001FE654 1000A0E7 */   swc1      $f0, 0x10($29)
    /* FE658 001FE658 040040C4 */  lwc1       $f0, 0x4($2)
    /* FE65C 001FE65C 2D200002 */  daddu      $4, $16, $0
    /* FE660 001FE660 3E74050C */  jal        ContinueCorrectPosition
    /* FE664 001FE664 1400A0E7 */   swc1      $f0, 0x14($29)
    /* FE668 001FE668 080040C4 */  lwc1       $f0, 0x8($2)
    /* FE66C 001FE66C 2D200002 */  daddu      $4, $16, $0
    /* FE670 001FE670 2C000524 */  addiu      $5, $0, 0x2C
    /* FE674 001FE674 7428040C */  jal        CheckPureWallAttribute
    /* FE678 001FE678 1800A0E7 */   swc1      $f0, 0x18($29)
    /* FE67C 001FE67C 1400A1C7 */  lwc1       $f1, 0x14($29)
    /* FE680 001FE680 06A30046 */  mov.s      $f12, $f20
    /* FE684 001FE684 1000A427 */  addiu      $4, $29, 0x10
    /* FE688 001FE688 2D280000 */  daddu      $5, $0, $0
    /* FE68C 001FE68C 41080046 */  sub.s      $f1, $f1, $f0
    /* FE690 001FE690 2D300000 */  daddu      $6, $0, $0
    /* FE694 001FE694 FF000724 */  addiu      $7, $0, 0xFF
    /* FE698 001FE698 1012060C */  jal        debug_Marker
    /* FE69C 001FE69C 1400A1E7 */   swc1      $f1, 0x14($29)
    /* FE6A0 001FE6A0 0400A2C7 */  lwc1       $f2, 0x4($29)
    /* FE6A4 001FE6A4 1400A0C7 */  lwc1       $f0, 0x14($29)
    /* FE6A8 001FE6A8 00088044 */  mtc1       $0, $f1
    /* FE6AC 001FE6AC 81100046 */  sub.s      $f2, $f2, $f0
    /* FE6B0 001FE6B0 34100146 */  c.lt.s     $f2, $f1
    /* FE6B4 001FE6B4 0A000045 */  bc1f       .L001FE6E0
    /* FE6B8 001FE6B8 00000000 */   nop
    /* FE6BC 001FE6BC 47100046 */  neg.s      $f1, $f2
    /* FE6C0 001FE6C0 2042013C */  lui        $1, (0x42200000 >> 16)
    /* FE6C4 001FE6C4 00008144 */  mtc1       $1, $f0
    /* FE6C8 001FE6C8 34000146 */  c.lt.s     $f0, $f1
    /* FE6CC 001FE6CC 00000000 */  nop
    /* FE6D0 001FE6D0 0A000145 */  bc1t       .L001FE6FC
    /* FE6D4 001FE6D4 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L001FE6D8:
    /* FE6D8 001FE6D8 08000010 */  b          .L001FE6FC
    /* FE6DC 001FE6DC 2D100000 */   daddu     $2, $0, $0
.align 2
  .L001FE6E0:
    /* FE6E0 001FE6E0 2042013C */  lui        $1, (0x42200000 >> 16)
    /* FE6E4 001FE6E4 00008144 */  mtc1       $1, $f0
    /* FE6E8 001FE6E8 34000246 */  c.lt.s     $f0, $f2
    /* FE6EC 001FE6EC 00000000 */  nop
    /* FE6F0 001FE6F0 02000145 */  bc1t       .L001FE6FC
    /* FE6F4 001FE6F4 01000224 */   addiu     $2, $0, 0x1
    /* FE6F8 001FE6F8 2D100000 */  daddu      $2, $0, $0
.align 2
  .L001FE6FC:
    /* FE6FC 001FE6FC 3000BFDF */  ld         $31, 0x30($29)
    /* FE700 001FE700 2000B0DF */  ld         $16, 0x20($29)
    /* FE704 001FE704 4000B4C7 */  lwc1       $f20, 0x40($29)
    /* FE708 001FE708 0800E003 */  jr         $31
    /* FE70C 001FE70C 5000BD27 */   addiu     $29, $29, 0x50
endlabel checkPositionIllegal
```
