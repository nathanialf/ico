# subBoyCollision — parked

VRAM: 0x00150718 (file_off 0x050718)
Asm source: asm/aug6/nonmatchings/fumi/src/boyact/subBoyCollision.s

## Attempt at 2026-07-07

**Reason parked:** rc5 structure recovered (2 float guards + 2 null checks + final dist compare, ret1 join); residual=beql-vs-beq on D_00629DE4==0 + fp-reg f1/f2 swap for 450.0f const vs ra->f4; both fold under reshaping; permuter-class

**TU:** `fumi/src/boyact.c`

**Seed:** `tough_nuts/subBoyCollision/subBoyCollision.c`

Disassembly:

```
.align 3
nonmatching subBoyCollision, 0xF0

glabel subBoyCollision
    /* 50718 00150718 C0FFBD27 */  addiu      $29, $29, -0x40
    /* 5071C 0015071C F491828F */  lw         $2, %gp_rel(D_00629DE4)($28)
    /* 50720 00150720 1000B0FF */  sd         $16, 0x10($29)
    /* 50724 00150724 3000BFFF */  sd         $31, 0x30($29)
    /* 50728 00150728 2000B1FF */  sd         $17, 0x20($29)
    /* 5072C 0015072C F891848F */  lw         $4, %gp_rel(D_00629DE8)($28)
    /* 50730 00150730 3E74050C */  jal        ContinueCorrectPosition
    /* 50734 00150734 6401518C */   lw        $17, 0x164($2)
    /* 50738 00150738 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* 5073C 0015073C 3E74050C */  jal        ContinueCorrectPosition
    /* 50740 00150740 2D804000 */   daddu     $16, $2, $0
    /* 50744 00150744 2D304000 */  daddu      $6, $2, $0
    /* 50748 00150748 2D280002 */  daddu      $5, $16, $0
    /* 5074C 0015074C 0200090C */  jal        func_00240008
    /* 50750 00150750 2D20A003 */   daddu     $4, $29, $0
    /* 50754 00150754 2D20A003 */  daddu      $4, $29, $0
    /* 50758 00150758 9CFF080C */  jal        func_0023FE70
    /* 5075C 0015075C B0042526 */   addiu     $5, $17, 0x4B0
    /* 50760 00150760 00088044 */  mtc1       $0, $f1
    /* 50764 00150764 34080046 */  c.lt.s     $f1, $f0
    /* 50768 00150768 00000000 */  nop
    /* 5076C 0015076C 20000045 */  bc1f       .L001507F0
    /* 50770 00150770 F891848F */   lw        $4, %gp_rel(D_00629DE8)($28)
    /* 50774 00150774 3E74050C */  jal        ContinueCorrectPosition
    /* 50778 00150778 00053026 */   addiu     $16, $17, 0x500
    /* 5077C 0015077C 2D200002 */  daddu      $4, $16, $0
    /* 50780 00150780 0047060C */  jal        InitHandCameraCorrect
    /* 50784 00150784 2D284000 */   daddu     $5, $2, $0
    /* 50788 00150788 F841013C */  lui        $1, (0x41F80000 >> 16)
    /* 5078C 0015078C 00088144 */  mtc1       $1, $f1
    /* 50790 00150790 34000146 */  c.lt.s     $f0, $f1
    /* 50794 00150794 00000000 */  nop
    /* 50798 00150798 15000045 */  bc1f       .L001507F0
    /* 5079C 0015079C F891848F */   lw        $4, %gp_rel(D_00629DE8)($28)
    /* 507A0 001507A0 11008010 */  beqz       $4, .L001507E8
    /* 507A4 001507A4 F491828F */   lw        $2, %gp_rel(D_00629DE4)($28)
    /* 507A8 001507A8 12004010 */  beqz       $2, .L001507F4
    /* 507AC 001507AC 01000224 */   addiu     $2, $0, 0x1
    /* 507B0 001507B0 3E74050C */  jal        ContinueCorrectPosition
    /* 507B4 001507B4 00000000 */   nop
    /* 507B8 001507B8 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* 507BC 001507BC 3E74050C */  jal        ContinueCorrectPosition
    /* 507C0 001507C0 2D804000 */   daddu     $16, $2, $0
    /* 507C4 001507C4 040040C4 */  lwc1       $f0, 0x4($2)
    /* 507C8 001507C8 E143013C */  lui        $1, (0x43E10000 >> 16)
    /* 507CC 001507CC 00088144 */  mtc1       $1, $f1
    /* 507D0 001507D0 040002C6 */  lwc1       $f2, 0x4($16)
    /* 507D4 001507D4 00000146 */  add.s      $f0, $f0, $f1
    /* 507D8 001507D8 34000246 */  c.lt.s     $f0, $f2
    /* 507DC 001507DC 00000000 */  nop
    /* 507E0 001507E0 04000145 */  bc1t       .L001507F4
    /* 507E4 001507E4 2D100000 */   daddu     $2, $0, $0
.align 2
  .L001507E8:
    /* 507E8 001507E8 02000010 */  b          .L001507F4
    /* 507EC 001507EC 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L001507F0:
    /* 507F0 001507F0 2D100000 */  daddu      $2, $0, $0
.align 2
  .L001507F4:
    /* 507F4 001507F4 3000BFDF */  ld         $31, 0x30($29)
    /* 507F8 001507F8 2000B1DF */  ld         $17, 0x20($29)
    /* 507FC 001507FC 1000B0DF */  ld         $16, 0x10($29)
    /* 50800 00150800 0800E003 */  jr         $31
    /* 50804 00150804 4000BD27 */   addiu     $29, $29, 0x40
endlabel subBoyCollision
```
