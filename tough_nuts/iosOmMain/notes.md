# iosOmMain — parked

VRAM: 0x0013F6E8 (file_off 0x03F6E8)
Asm source: asm/aug6/nonmatchings/fumi/isys/obj_manager/iosOmMain.s

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=30). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/isys/obj_manager.c`

**Seed:** `tough_nuts/iosOmMain/iosOmMain.c`

Disassembly:

```
.align 3
nonmatching iosOmMain, 0x10C

glabel iosOmMain
    /* 3F6E8 0013F6E8 B0FFBD27 */  addiu      $29, $29, -0x50
    /* 3F6EC 0013F6EC 2000B2FF */  sd         $18, 0x20($29)
    /* 3F6F0 0013F6F0 E498928F */  lw         $18, %gp_rel(D_0062A4D4)($28)
    /* 3F6F4 0013F6F4 4000BFFF */  sd         $31, 0x40($29)
    /* 3F6F8 0013F6F8 3000B3FF */  sd         $19, 0x30($29)
    /* 3F6FC 0013F6FC 1000B1FF */  sd         $17, 0x10($29)
    /* 3F700 0013F700 35004012 */  beqz       $18, .L0013F7D8
    /* 3F704 0013F704 0000B0FF */   sd        $16, 0x0($29)
    /* 3F708 0013F708 2800023C */  lui        $2, %hi(D_0027DE30)
    /* 3F70C 0013F70C 30DE5324 */  addiu      $19, $2, %lo(D_0027DE30)
    /* 3F710 0013F710 DC98838F */  lw         $3, %gp_rel(D_0062A4CC)($28)
    /* 3F714 0013F714 01006230 */  andi       $2, $3, 0x1
.align 2
  .L0013F718:
    /* 3F718 0013F718 09004010 */  beqz       $2, .L0013F740
    /* 3F71C 0013F71C 2D200000 */   daddu     $4, $0, $0
    /* 3F720 0013F720 4800428E */  lw         $2, 0x48($18)
    /* 3F724 0013F724 07004050 */  beql       $2, $0, .L0013F744
    /* 3F728 0013F728 07108300 */   srav      $2, $3, $4
    /* 3F72C 0013F72C 09F84000 */  jalr       $2
    /* 3F730 0013F730 2D204002 */   daddu     $4, $18, $0
    /* 3F734 0013F734 DC98838F */  lw         $3, %gp_rel(D_0062A4CC)($28)
    /* 3F738 0013F738 2D200000 */  daddu      $4, $0, $0
    /* 3F73C 0013F73C 00000000 */  nop
.align 2
  .L0013F740:
    /* 3F740 0013F740 07108300 */  srav       $2, $3, $4
.align 2
  .L0013F744:
    /* 3F744 0013F744 01004230 */  andi       $2, $2, 0x1
    /* 3F748 0013F748 1C004010 */  beqz       $2, .L0013F7BC
    /* 3F74C 0013F74C 01009124 */   addiu     $17, $4, 0x1
    /* 3F750 0013F750 4C00428E */  lw         $2, 0x4C($18)
    /* 3F754 0013F754 07108200 */  srav       $2, $2, $4
    /* 3F758 0013F758 01004230 */  andi       $2, $2, 0x1
    /* 3F75C 0013F75C 17004010 */  beqz       $2, .L0013F7BC
    /* 3F760 0013F760 80100400 */   sll       $2, $4, 2
    /* 3F764 0013F764 21105300 */  addu       $2, $2, $19
    /* 3F768 0013F768 0000508C */  lw         $16, 0x0($2)
    /* 3F76C 0013F76C 14000012 */  beqz       $16, .L0013F7C0
    /* 3F770 0013F770 2D202002 */   daddu     $4, $17, $0
    /* 3F774 0013F774 6C01028E */  lw         $2, 0x16C($16)
.align 2
  .L0013F778:
    /* 3F778 0013F778 0C004050 */  beql       $2, $0, .L0013F7AC
    /* 3F77C 0013F77C 3400108E */   lw        $16, 0x34($16)
    /* 3F780 0013F780 5000438E */  lw         $3, 0x50($18)
    /* 3F784 0013F784 5000028E */  lw         $2, 0x50($16)
    /* 3F788 0013F788 24186200 */  and        $3, $3, $2
    /* 3F78C 0013F78C 07006050 */  beql       $3, $0, .L0013F7AC
    /* 3F790 0013F790 3400108E */   lw        $16, 0x34($16)
    /* 3F794 0013F794 4800028E */  lw         $2, 0x48($16)
    /* 3F798 0013F798 04004050 */  beql       $2, $0, .L0013F7AC
    /* 3F79C 0013F79C 3400108E */   lw        $16, 0x34($16)
    /* 3F7A0 0013F7A0 09F84000 */  jalr       $2
    /* 3F7A4 0013F7A4 2D200002 */   daddu     $4, $16, $0
    /* 3F7A8 0013F7A8 3400108E */  lw         $16, 0x34($16)
.align 2
  .L0013F7AC:
    /* 3F7AC 0013F7AC F2FF0056 */  bnel       $16, $0, .L0013F778
    /* 3F7B0 0013F7B0 6C01028E */   lw        $2, 0x16C($16)
    /* 3F7B4 0013F7B4 02000010 */  b          .L0013F7C0
    /* 3F7B8 0013F7B8 2D202002 */   daddu     $4, $17, $0
.align 2
  .L0013F7BC:
    /* 3F7BC 0013F7BC 2D202002 */  daddu      $4, $17, $0
.align 2
  .L0013F7C0:
    /* 3F7C0 0013F7C0 20008228 */  slti       $2, $4, 0x20
    /* 3F7C4 0013F7C4 DEFF4014 */  bnez       $2, .L0013F740
    /* 3F7C8 0013F7C8 DC98838F */   lw        $3, %gp_rel(D_0062A4CC)($28)
    /* 3F7CC 0013F7CC 3400528E */  lw         $18, 0x34($18)
    /* 3F7D0 0013F7D0 D1FF4016 */  bnez       $18, .L0013F718
    /* 3F7D4 0013F7D4 01006230 */   andi      $2, $3, 0x1
.align 2
  .L0013F7D8:
    /* 3F7D8 0013F7D8 4000BFDF */  ld         $31, 0x40($29)
    /* 3F7DC 0013F7DC 3000B3DF */  ld         $19, 0x30($29)
    /* 3F7E0 0013F7E0 2000B2DF */  ld         $18, 0x20($29)
    /* 3F7E4 0013F7E4 1000B1DF */  ld         $17, 0x10($29)
    /* 3F7E8 0013F7E8 0000B0DF */  ld         $16, 0x0($29)
    /* 3F7EC 0013F7EC 0800E003 */  jr         $31
    /* 3F7F0 0013F7F0 5000BD27 */   addiu     $29, $29, 0x50
endlabel iosOmMain
    /* 3F7F4 0013F7F4 00000000 */  nop
```
