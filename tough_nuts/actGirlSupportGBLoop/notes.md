# actGirlSupportGBLoop — parked

VRAM: 0x0016F720 (file_off 0x06F720)
Asm source: asm/aug6/nonmatchings/fumi/src/girl_act/actGirlSupportGBLoop.s

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=11). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/girl_act.c`

**Seed:** `tough_nuts/actGirlSupportGBLoop/actGirlSupportGBLoop.c`

Disassembly:

```
.align 3
nonmatching actGirlSupportGBLoop, 0x114

glabel actGirlSupportGBLoop
    /* 6F720 0016F720 A0FFBD27 */  addiu      $29, $29, -0x60
    /* 6F724 0016F724 F491858F */  lw         $5, %gp_rel(D_00629DE4)($28)
    /* 6F728 0016F728 3000B1FF */  sd         $17, 0x30($29)
    /* 6F72C 0016F72C 5000BFFF */  sd         $31, 0x50($29)
    /* 6F730 0016F730 2D880000 */  daddu      $17, $0, $0
    /* 6F734 0016F734 4000B2FF */  sd         $18, 0x40($29)
    /* 6F738 0016F738 3700A010 */  beqz       $5, .L0016F818
    /* 6F73C 0016F73C 2000B0FF */   sd        $16, 0x20($29)
    /* 6F740 0016F740 F891828F */  lw         $2, %gp_rel(D_00629DE8)($28)
    /* 6F744 0016F744 35004010 */  beqz       $2, .L0016F81C
    /* 6F748 0016F748 2D100000 */   daddu     $2, $0, $0
    /* 6F74C 0016F74C E229040C */  jal        GetHeightOfWallFromGObj
    /* 6F750 0016F750 2D20A003 */   daddu     $4, $29, $0
    /* 6F754 0016F754 1000B027 */  addiu      $16, $29, 0x10
    /* 6F758 0016F758 F891858F */  lw         $5, %gp_rel(D_00629DE8)($28)
    /* 6F75C 0016F75C 2D200002 */  daddu      $4, $16, $0
    /* 6F760 0016F760 E229040C */  jal        GetHeightOfWallFromGObj
    /* 6F764 0016F764 2D900002 */   daddu     $18, $16, $0
    /* 6F768 0016F768 0400A0C7 */  lwc1       $f0, 0x4($29)
    /* 6F76C 0016F76C 1400A1C7 */  lwc1       $f1, 0x14($29)
    /* 6F770 0016F770 00108044 */  mtc1       $0, $f2
    /* 6F774 0016F774 41000146 */  sub.s      $f1, $f0, $f1
    /* 6F778 0016F778 34080246 */  c.lt.s     $f1, $f2
    /* 6F77C 0016F77C 0A000045 */  bc1f       .L0016F7A8
    /* 6F780 0016F780 00000000 */   nop
    /* 6F784 0016F784 47080046 */  neg.s      $f1, $f1
    /* 6F788 0016F788 4843013C */  lui        $1, (0x43480000 >> 16)
    /* 6F78C 0016F78C 00008144 */  mtc1       $1, $f0
    /* 6F790 0016F790 34000146 */  c.lt.s     $f0, $f1
    /* 6F794 0016F794 00000000 */  nop
    /* 6F798 0016F798 09000345 */  bc1tl      .L0016F7C0
    /* 6F79C 0016F79C 01001124 */   addiu     $17, $0, 0x1
    /* 6F7A0 0016F7A0 07000010 */  b          .L0016F7C0
    /* 6F7A4 0016F7A4 00000000 */   nop
.align 2
  .L0016F7A8:
    /* 6F7A8 0016F7A8 4843013C */  lui        $1, (0x43480000 >> 16)
    /* 6F7AC 0016F7AC 00008144 */  mtc1       $1, $f0
    /* 6F7B0 0016F7B0 34000146 */  c.lt.s     $f0, $f1
    /* 6F7B4 0016F7B4 00000000 */  nop
    /* 6F7B8 0016F7B8 01000345 */  bc1tl      .L0016F7C0
    /* 6F7BC 0016F7BC 01001124 */   addiu     $17, $0, 0x1
.align 2
  .L0016F7C0:
    /* 6F7C0 0016F7C0 15002012 */  beqz       $17, .L0016F818
    /* 6F7C4 0016F7C4 2D284002 */   daddu     $5, $18, $0
    /* 6F7C8 0016F7C8 D846060C */  jal        RotateAccordingToStick_PatternThree
    /* 6F7CC 0016F7CC 2D20A003 */   daddu     $4, $29, $0
    /* 6F7D0 0016F7D0 D48481C7 */  lwc1       $f1, %gp_rel(D_006290C4)($28)
    /* 6F7D4 0016F7D4 34000146 */  c.lt.s     $f0, $f1
    /* 6F7D8 0016F7D8 00000000 */  nop
    /* 6F7DC 0016F7DC 0F000145 */  bc1t       .L0016F81C
    /* 6F7E0 0016F7E0 01000224 */   addiu     $2, $0, 0x1
    /* 6F7E4 0016F7E4 2D20A003 */  daddu      $4, $29, $0
    /* 6F7E8 0016F7E8 D846060C */  jal        RotateAccordingToStick_PatternThree
    /* 6F7EC 0016F7EC 2D280002 */   daddu     $5, $16, $0
    /* 6F7F0 0016F7F0 D88481C7 */  lwc1       $f1, %gp_rel(D_006290C8)($28)
    /* 6F7F4 0016F7F4 34000146 */  c.lt.s     $f0, $f1
    /* 6F7F8 0016F7F8 00000000 */  nop
    /* 6F7FC 0016F7FC 06000045 */  bc1f       .L0016F818
    /* 6F800 0016F800 2D280002 */   daddu     $5, $16, $0
    /* 6F804 0016F804 58BD050C */  jal        func_0016F560
    /* 6F808 0016F808 2D20A003 */   daddu     $4, $29, $0
    /* 6F80C 0016F80C 2D184000 */  daddu      $3, $2, $0
    /* 6F810 0016F810 02006014 */  bnez       $3, .L0016F81C
    /* 6F814 0016F814 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L0016F818:
    /* 6F818 0016F818 2D100000 */  daddu      $2, $0, $0
.align 2
  .L0016F81C:
    /* 6F81C 0016F81C 5000BFDF */  ld         $31, 0x50($29)
    /* 6F820 0016F820 4000B2DF */  ld         $18, 0x40($29)
    /* 6F824 0016F824 3000B1DF */  ld         $17, 0x30($29)
    /* 6F828 0016F828 2000B0DF */  ld         $16, 0x20($29)
    /* 6F82C 0016F82C 0800E003 */  jr         $31
    /* 6F830 0016F830 6000BD27 */   addiu     $29, $29, 0x60
endlabel actGirlSupportGBLoop
    /* 6F834 0016F834 00000000 */  nop
```
