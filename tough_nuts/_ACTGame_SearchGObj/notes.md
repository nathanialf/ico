# _ACTGame_SearchGObj — parked

VRAM: 0x00148710 (file_off 0x048710)
Asm source: asm/aug6/nonmatchings/fumi/src/act-game/_ACTGame_SearchGObj.s

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=14). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/act-game.c`

**Seed:** `tough_nuts/_ACTGame_SearchGObj/_ACTGame_SearchGObj.c`

Disassembly:

```
.align 3
nonmatching _ACTGame_SearchGObj, 0x10C

glabel _ACTGame_SearchGObj
    /* 48710 00148710 C0FFBD27 */  addiu      $29, $29, -0x40
    /* 48714 00148714 2D18A000 */  daddu      $3, $5, $0
    /* 48718 00148718 3000BFFF */  sd         $31, 0x30($29)
    /* 4871C 0014871C 2000B0FF */  sd         $16, 0x20($29)
    /* 48720 00148720 0800A6AF */  sw         $6, 0x8($29)
    /* 48724 00148724 0400A7AF */  sw         $7, 0x4($29)
    /* 48728 00148728 1000A8AF */  sw         $8, 0x10($29)
    /* 4872C 0014872C 1400A9AF */  sw         $9, 0x14($29)
    /* 48730 00148730 1800AAAF */  sw         $10, 0x18($29)
    /* 48734 00148734 0C00A4AF */  sw         $4, 0xC($29)
    /* 48738 00148738 1C00A5AF */  sw         $5, 0x1C($29)
    /* 4873C 0014873C 0F006010 */  beqz       $3, .L0014877C
    /* 48740 00148740 0000A0AF */   sw        $0, 0x0($29)
    /* 48744 00148744 01000224 */  addiu      $2, $0, 0x1
    /* 48748 00148748 10006210 */  beq        $3, $2, .L0014878C
    /* 4874C 0014874C 5500103C */   lui       $16, %hi(D_00552200)
    /* 48750 00148750 ED100524 */  addiu      $5, $0, 0x10ED
    /* 48754 00148754 00221026 */  addiu      $16, $16, %lo(D_00552200)
    /* 48758 00148758 40AB060C */  jal        func_001AAD00
    /* 4875C 0014875C 2D200002 */   daddu     $4, $16, $0
    /* 48760 00148760 6300063C */  lui        $6, %hi(D_0062C3C0)
    /* 48764 00148764 2D200002 */  daddu      $4, $16, $0
    /* 48768 00148768 C0C3C624 */  addiu      $6, $6, %lo(D_0062C3C0)
    /* 4876C 0014876C E080090C */  jal        func_00260380
    /* 48770 00148770 ED100524 */   addiu     $5, $0, 0x10ED
    /* 48774 00148774 0A000010 */  b          .L001487A0
    /* 48778 00148778 0800A58F */   lw        $5, 0x8($29)
.align 2
  .L0014877C:
    /* 4877C 0014877C 6401838C */  lw         $3, 0x164($4)
    /* 48780 00148780 7006628C */  lw         $2, 0x670($3)
    /* 48784 00148784 04000010 */  b          .L00148798
    /* 48788 00148788 14034224 */   addiu     $2, $2, 0x314
.align 2
  .L0014878C:
    /* 4878C 0014878C 6401838C */  lw         $3, 0x164($4)
    /* 48790 00148790 7006628C */  lw         $2, 0x670($3)
    /* 48794 00148794 1C034224 */  addiu      $2, $2, 0x31C
.align 2
  .L00148798:
    /* 48798 00148798 0000A2AF */  sw         $2, 0x0($29)
    /* 4879C 0014879C 0800A58F */  lw         $5, 0x8($29)
.align 2
  .L001487A0:
    /* 487A0 001487A0 0300A228 */  slti       $2, $5, 0x3
    /* 487A4 001487A4 0B004010 */  beqz       $2, .L001487D4
    /* 487A8 001487A8 0000A38F */   lw        $3, 0x0($29)
    /* 487AC 001487AC 0900A018 */  blez       $5, .L001487D4
    /* 487B0 001487B0 0400A28F */   lw        $2, 0x4($29)
    /* 487B4 001487B4 08004054 */  bnel       $2, $0, .L001487D8
    /* 487B8 001487B8 0400648C */   lw        $4, 0x4($3)
    /* 487BC 001487BC 0000A38F */  lw         $3, 0x0($29)
    /* 487C0 001487C0 0400628C */  lw         $2, 0x4($3)
    /* 487C4 001487C4 12004514 */  bne        $2, $5, .L00148810
    /* 487C8 001487C8 3000BFDF */   ld        $31, 0x30($29)
    /* 487CC 001487CC 02000010 */  b          .L001487D8
    /* 487D0 001487D0 0400648C */   lw        $4, 0x4($3)
.align 2
  .L001487D4:
    /* 487D4 001487D4 0400648C */  lw         $4, 0x4($3)
.align 2
  .L001487D8:
    /* 487D8 001487D8 04008010 */  beqz       $4, .L001487EC
    /* 487DC 001487DC 00000000 */   nop
    /* 487E0 001487E0 0000628C */  lw         $2, 0x0($3)
    /* 487E4 001487E4 05004014 */  bnez       $2, .L001487FC
    /* 487E8 001487E8 2A10A400 */   slt       $2, $5, $4
.align 2
  .L001487EC:
    /* 487EC 001487EC 7621050C */  jal        ACTGame_LwsEffectProcess
    /* 487F0 001487F0 2D10A003 */   daddu     $2, $29, $0
    /* 487F4 001487F4 06000010 */  b          .L00148810
    /* 487F8 001487F8 3000BFDF */   ld        $31, 0x30($29)
.align 2
  .L001487FC:
    /* 487FC 001487FC 04004014 */  bnez       $2, .L00148810
    /* 48800 00148800 3000BFDF */   ld        $31, 0x30($29)
    /* 48804 00148804 7621050C */  jal        ACTGame_LwsEffectProcess
    /* 48808 00148808 2D10A003 */   daddu     $2, $29, $0
    /* 4880C 0014880C 3000BFDF */  ld         $31, 0x30($29)
.align 2
  .L00148810:
    /* 48810 00148810 2000B0DF */  ld         $16, 0x20($29)
    /* 48814 00148814 0800E003 */  jr         $31
    /* 48818 00148818 4000BD27 */   addiu     $29, $29, 0x40
endlabel _ACTGame_SearchGObj
    /* 4881C 0014881C 00000000 */  nop
```
