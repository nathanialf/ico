# soundBufAdpcmFree — parked

VRAM: 0x00142658 (file_off 0x042658)
Asm source: asm/aug6/nonmatchings/fumi/sound/s_init/soundBufAdpcmFree.s

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=13). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/sound/s_init.c`

**Seed:** `tough_nuts/soundBufAdpcmFree/soundBufAdpcmFree.c`

Disassembly:

```
.align 3
nonmatching soundBufAdpcmFree, 0x110

glabel soundBufAdpcmFree
    /* 42658 00142658 B0FFBD27 */  addiu      $29, $29, -0x50
    /* 4265C 0014265C D8B386DF */  ld         $6, %gp_rel(D_0062BFC8)($28)
    /* 42660 00142660 2000B2FF */  sd         $18, 0x20($29)
    /* 42664 00142664 3000B3FF */  sd         $19, 0x30($29)
    /* 42668 00142668 2D908000 */  daddu      $18, $4, $0
    /* 4266C 0014266C 1000B1FF */  sd         $17, 0x10($29)
    /* 42670 00142670 2D98A000 */  daddu      $19, $5, $0
    /* 42674 00142674 4000BFFF */  sd         $31, 0x40($29)
    /* 42678 00142678 2D880000 */  daddu      $17, $0, $0
    /* 4267C 0014267C 0000B0FF */  sd         $16, 0x0($29)
    /* 42680 00142680 01000424 */  addiu      $4, $0, 0x1
    /* 42684 00142684 04102402 */  sllv       $2, $4, $17
.align 2
  .L00142688:
    /* 42688 00142688 24184600 */  and        $3, $2, $6
    /* 4268C 0014268C 10006010 */  beqz       $3, .L001426D0
    /* 42690 00142690 01000224 */   addiu     $2, $0, 0x1
    /* 42694 00142694 01003126 */  addiu      $17, $17, 0x1
    /* 42698 00142698 4000222E */  sltiu      $2, $17, 0x40
    /* 4269C 0014269C FAFF4014 */  bnez       $2, .L00142688
    /* 426A0 001426A0 04102402 */   sllv      $2, $4, $17
    /* 426A4 001426A4 5500103C */  lui        $16, %hi(D_00551FC8)
    /* 426A8 001426A8 E7010524 */  addiu      $5, $0, 0x1E7
    /* 426AC 001426AC C81F1026 */  addiu      $16, $16, %lo(D_00551FC8)
    /* 426B0 001426B0 40AB060C */  jal        func_001AAD00
    /* 426B4 001426B4 2D200002 */   daddu     $4, $16, $0
    /* 426B8 001426B8 6300063C */  lui        $6, %hi(D_0062C388)
    /* 426BC 001426BC 2D200002 */  daddu      $4, $16, $0
    /* 426C0 001426C0 88C3C624 */  addiu      $6, $6, %lo(D_0062C388)
    /* 426C4 001426C4 E080090C */  jal        func_00260380
    /* 426C8 001426C8 E7010524 */   addiu     $5, $0, 0x1E7
    /* 426CC 001426CC 01000224 */  addiu      $2, $0, 0x1
.align 2
  .L001426D0:
    /* 426D0 001426D0 180044DE */  ld         $4, 0x18($18)
    /* 426D4 001426D4 04102202 */  sllv       $2, $2, $17
    /* 426D8 001426D8 D8B383DF */  ld         $3, %gp_rel(D_0062BFC8)($28)
    /* 426DC 001426DC 0500252A */  slti       $5, $17, 0x5
    /* 426E0 001426E0 25208200 */  or         $4, $4, $2
    /* 426E4 001426E4 25186200 */  or         $3, $3, $2
    /* 426E8 001426E8 180044FE */  sd         $4, 0x18($18)
    /* 426EC 001426EC 0E00A014 */  bnez       $5, .L00142728
    /* 426F0 001426F0 D8B383FF */   sd        $3, %gp_rel(D_0062BFC8)($28)
    /* 426F4 001426F4 5500043C */  lui        $4, %hi(D_00552060)
    /* 426F8 001426F8 F290060C */  jal        debug_assertMessage
    /* 426FC 001426FC 60208424 */   addiu     $4, $4, %lo(D_00552060)
    /* 42700 00142700 5500103C */  lui        $16, %hi(D_00551FC8)
    /* 42704 00142704 EB010524 */  addiu      $5, $0, 0x1EB
    /* 42708 00142708 C81F1026 */  addiu      $16, $16, %lo(D_00551FC8)
    /* 4270C 0014270C 40AB060C */  jal        func_001AAD00
    /* 42710 00142710 2D200002 */   daddu     $4, $16, $0
    /* 42714 00142714 6300063C */  lui        $6, %hi(D_0062C388)
    /* 42718 00142718 2D200002 */  daddu      $4, $16, $0
    /* 4271C 0014271C 88C3C624 */  addiu      $6, $6, %lo(D_0062C388)
    /* 42720 00142720 E080090C */  jal        func_00260380
    /* 42724 00142724 EB010524 */   addiu     $5, $0, 0x1EB
.align 2
  .L00142728:
    /* 42728 00142728 05002106 */  bgez       $17, .L00142740
    /* 4272C 0014272C 000071AE */   sw        $17, 0x0($19)
    /* 42730 00142730 1D00023C */  lui        $2, (0x1D9020 >> 16)
    /* 42734 00142734 801B1100 */  sll        $3, $17, 14
    /* 42738 00142738 03000010 */  b          .L00142748
    /* 4273C 0014273C 20904234 */   ori       $2, $2, (0x1D9020 & 0xFFFF)
.align 2
  .L00142740:
    /* 42740 00142740 801B1100 */  sll        $3, $17, 14
    /* 42744 00142744 1E00023C */  lui        $2, (0x1E0000 >> 16)
.align 2
  .L00142748:
    /* 42748 00142748 21106200 */  addu       $2, $3, $2
    /* 4274C 0014274C 4000BFDF */  ld         $31, 0x40($29)
    /* 42750 00142750 3000B3DF */  ld         $19, 0x30($29)
    /* 42754 00142754 2000B2DF */  ld         $18, 0x20($29)
    /* 42758 00142758 1000B1DF */  ld         $17, 0x10($29)
    /* 4275C 0014275C 0000B0DF */  ld         $16, 0x0($29)
    /* 42760 00142760 0800E003 */  jr         $31
    /* 42764 00142764 5000BD27 */   addiu     $29, $29, 0x50
endlabel soundBufAdpcmFree
```
