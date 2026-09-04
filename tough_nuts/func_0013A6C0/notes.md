# func_0013A6C0 — parked

VRAM: 0x0013A6C0 (file_off 0x03A6C0)
Asm source: asm/nonmatchings/ios/message/func_0013A6C0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (REG)

**TU:** `ios/message.c`

**Seed:** `tough_nuts/func_0013A6C0/func_0013A6C0.c`

Disassembly:

```
.align 3
nonmatching func_0013A6C0, 0x104

glabel func_0013A6C0
    /* 3A6C0 0013A6C0 90FFBD27 */  addiu      $29, $29, -0x70
    /* 3A6C4 0013A6C4 5000B3FF */  sd         $19, 0x50($29)
    /* 3A6C8 0013A6C8 4000B2FF */  sd         $18, 0x40($29)
    /* 3A6CC 0013A6CC 2D98A000 */  daddu      $19, $5, $0
    /* 3A6D0 0013A6D0 3000B1FF */  sd         $17, 0x30($29)
    /* 3A6D4 0013A6D4 2D90C000 */  daddu      $18, $6, $0
    /* 3A6D8 0013A6D8 6000BFFF */  sd         $31, 0x60($29)
    /* 3A6DC 0013A6DC 2D888000 */  daddu      $17, $4, $0
    /* 3A6E0 0013A6E0 0E002016 */  bnez       $17, .L0013A71C
    /* 3A6E4 0013A6E4 2000B0FF */   sd        $16, 0x20($29)
    /* 3A6E8 0013A6E8 5500043C */  lui        $4, %hi(D_00557560)
    /* 3A6EC 0013A6EC 8A9B060C */  jal        func_001A6E28
    /* 3A6F0 0013A6F0 60758424 */   addiu     $4, $4, %lo(D_00557560)
    /* 3A6F4 0013A6F4 5500103C */  lui        $16, %hi(D_00557540)
    /* 3A6F8 0013A6F8 49010524 */  addiu      $5, $0, 0x149
    /* 3A6FC 0013A6FC 40751026 */  addiu      $16, $16, %lo(D_00557540)
    /* 3A700 0013A700 DAB5060C */  jal        func_001AD768
    /* 3A704 0013A704 2D200002 */   daddu     $4, $16, $0
    /* 3A708 0013A708 6300063C */  lui        $6, %hi(D_006320E8)
    /* 3A70C 0013A70C 2D200002 */  daddu      $4, $16, $0
    /* 3A710 0013A710 E820C624 */  addiu      $6, $6, %lo(D_006320E8)
    /* 3A714 0013A714 FC8F090C */  jal        __assert
    /* 3A718 0013A718 49010524 */   addiu     $5, $0, 0x149
.align 2
  .L0013A71C:
    /* 3A71C 0013A71C 2C00248E */  lw         $4, 0x2C($17)
    /* 3A720 0013A720 6401040C */  jal        ReferSemaStatus
    /* 3A724 0013A724 2D28A003 */   daddu     $5, $29, $0
    /* 3A728 0013A728 0800238E */  lw         $3, 0x8($17)
    /* 3A72C 0013A72C 07006054 */  bnel       $3, $0, .L0013A74C
    /* 3A730 0013A730 0400228E */   lw        $2, 0x4($17)
    /* 3A734 0013A734 01000224 */  addiu      $2, $0, 0x1
    /* 3A738 0013A738 1B004216 */  bne        $18, $2, .L0013A7A8
    /* 3A73C 0013A73C FFFF0224 */   addiu     $2, $0, -0x1
    /* 3A740 0013A740 5801040C */  jal        WaitSema
    /* 3A744 0013A744 2C00248E */   lw        $4, 0x2C($17)
    /* 3A748 0013A748 0400228E */  lw         $2, 0x4($17)
.align 2
  .L0013A74C:
    /* 3A74C 0013A74C 0000258E */  lw         $5, 0x0($17)
    /* 3A750 0013A750 80100200 */  sll        $2, $2, 2
    /* 3A754 0013A754 0400A48F */  lw         $4, 0x4($29)
    /* 3A758 0013A758 21104500 */  addu       $2, $2, $5
    /* 3A75C 0013A75C 0000438C */  lw         $3, 0x0($2)
    /* 3A760 0013A760 000063AE */  sw         $3, 0x0($19)
    /* 3A764 0013A764 01008050 */  beql       $4, $0, .L0013A76C
    /* 3A768 0013A768 CD010000 */   break     0, 7
.align 2
  .L0013A76C:
    /* 3A76C 0013A76C 0400228E */  lw         $2, 0x4($17)
    /* 3A770 0013A770 0800238E */  lw         $3, 0x8($17)
    /* 3A774 0013A774 01004224 */  addiu      $2, $2, 0x1
    /* 3A778 0013A778 1A004400 */  div        $0, $2, $4
    /* 3A77C 0013A77C FFFF6324 */  addiu      $3, $3, -0x1
    /* 3A780 0013A780 080023AE */  sw         $3, 0x8($17)
    /* 3A784 0013A784 10280000 */  mfhi       $5
    /* 3A788 0013A788 06006414 */  bne        $3, $4, .L0013A7A4
    /* 3A78C 0013A78C 040025AE */   sw        $5, 0x4($17)
    /* 3A790 0013A790 0C00A28F */  lw         $2, 0xC($29)
    /* 3A794 0013A794 04004018 */  blez       $2, .L0013A7A8
    /* 3A798 0013A798 2D100000 */   daddu     $2, $0, $0
    /* 3A79C 0013A79C 5001040C */  jal        SignalSema
    /* 3A7A0 0013A7A0 2C00248E */   lw        $4, 0x2C($17)
.align 2
  .L0013A7A4:
    /* 3A7A4 0013A7A4 2D100000 */  daddu      $2, $0, $0
.align 2
  .L0013A7A8:
    /* 3A7A8 0013A7A8 6000BFDF */  ld         $31, 0x60($29)
    /* 3A7AC 0013A7AC 5000B3DF */  ld         $19, 0x50($29)
    /* 3A7B0 0013A7B0 4000B2DF */  ld         $18, 0x40($29)
    /* 3A7B4 0013A7B4 3000B1DF */  ld         $17, 0x30($29)
    /* 3A7B8 0013A7B8 2000B0DF */  ld         $16, 0x20($29)
    /* 3A7BC 0013A7BC 0800E003 */  jr         $31
    /* 3A7C0 0013A7C0 7000BD27 */   addiu     $29, $29, 0x70
endlabel func_0013A6C0
    /* 3A7C4 0013A7C4 00000000 */  nop
```
