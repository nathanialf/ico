# gsb_controlBrightness — parked

VRAM: 0x00112668 (file_off 0x012668)
Asm source: asm/aug6/nonmatchings/seki/src/GsBase/gsb_controlBrightness.s

## Attempt at 2026-07-05

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=10). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `seki/src/GsBase.c`

**Seed:** `tough_nuts/gsb_controlBrightness/gsb_controlBrightness.c`

Disassembly:

```
.align 3
nonmatching gsb_controlBrightness, 0xF4

glabel gsb_controlBrightness
    /* 12668 00112668 C0FFBD27 */  addiu      $29, $29, -0x40
    /* 1266C 0011266C 2D188000 */  daddu      $3, $4, $0
    /* 12670 00112670 2000B2FF */  sd         $18, 0x20($29)
    /* 12674 00112674 00FE0B24 */  addiu      $11, $0, -0x200
    /* 12678 00112678 1000B1FF */  sd         $17, 0x10($29)
    /* 1267C 0011267C 00440800 */  sll        $8, $8, 16
    /* 12680 00112680 0000B0FF */  sd         $16, 0x0($29)
    /* 12684 00112684 28007124 */  addiu      $17, $3, 0x28
    /* 12688 00112688 3000BFFF */  sd         $31, 0x30($29)
    /* 1268C 0011268C 03440800 */  sra        $8, $8, 16
    /* 12690 00112690 6C939287 */  lh         $18, %gp_rel(D_00629F5C)($28)
    /* 12694 00112694 3C440800 */  dsll32     $8, $8, 16
    /* 12698 00112698 1000228E */  lw         $2, 0x10($17)
    /* 1269C 0011269C 0F00E930 */  andi       $9, $7, 0xF
    /* 126A0 001126A0 70939097 */  lhu        $16, %gp_rel(D_00629F60)($28)
    /* 126A4 001126A4 3B440800 */  dsra       $8, $8, 16
    /* 126A8 001126A8 24104B00 */  and        $2, $2, $11
    /* 126AC 001126AC 00FE0424 */  addiu      $4, $0, -0x200
    /* 126B0 001126B0 100022AE */  sw         $2, 0x10($17)
    /* 126B4 001126B4 00841000 */  sll        $16, $16, 16
    /* 126B8 001126B8 C0000224 */  addiu      $2, $0, 0xC0
    /* 126BC 001126BC C2571000 */  srl        $10, $16, 31
    /* 126C0 001126C0 500165DC */  ld         $5, 0x150($3)
    /* 126C4 001126C4 25400201 */  or         $8, $8, $2
    /* 126C8 001126C8 600066DC */  ld         $6, 0x60($3)
    /* 126CC 001126CC 40000224 */  addiu      $2, $0, 0x40
    /* 126D0 001126D0 1000678C */  lw         $7, 0x10($3)
    /* 126D4 001126D4 2428A400 */  and        $5, $5, $4
    /* 126D8 001126D8 2430C400 */  and        $6, $6, $4
    /* 126DC 001126DC 03841000 */  sra        $16, $16, 16
    /* 126E0 001126E0 384E0900 */  dsll       $9, $9, 24
    /* 126E4 001126E4 2438EB00 */  and        $7, $7, $11
    /* 126E8 001126E8 25482801 */  or         $9, $9, $8
    /* 126EC 001126EC 2530C200 */  or         $6, $6, $2
    /* 126F0 001126F0 2528A200 */  or         $5, $5, $2
    /* 126F4 001126F4 21800A02 */  addu       $16, $16, $10
    /* 126F8 001126F8 43801000 */  sra        $16, $16, 1
    /* 126FC 001126FC 100067AC */  sw         $7, 0x10($3)
    /* 12700 00112700 500165FC */  sd         $5, 0x150($3)
    /* 12704 00112704 2D380002 */  daddu      $7, $16, $0
    /* 12708 00112708 600066FC */  sd         $6, 0x60($3)
    /* 1270C 0011270C 2D206000 */  daddu      $4, $3, $0
    /* 12710 00112710 700069FC */  sd         $9, 0x70($3)
    /* 12714 00112714 2D304002 */  daddu      $6, $18, $0
    /* 12718 00112718 600169FC */  sd         $9, 0x160($3)
    /* 1271C 0011271C 2D280000 */  daddu      $5, $0, $0
    /* 12720 00112720 2D400000 */  daddu      $8, $0, $0
    /* 12724 00112724 74F8080C */  jal        func_0023E1D0
    /* 12728 00112728 2D480000 */   daddu     $9, $0, $0
    /* 1272C 0011272C 2D202002 */  daddu      $4, $17, $0
    /* 12730 00112730 2D304002 */  daddu      $6, $18, $0
    /* 12734 00112734 2D380002 */  daddu      $7, $16, $0
    /* 12738 00112738 3000BFDF */  ld         $31, 0x30($29)
    /* 1273C 0011273C 2000B2DF */  ld         $18, 0x20($29)
    /* 12740 00112740 2D280000 */  daddu      $5, $0, $0
    /* 12744 00112744 1000B1DF */  ld         $17, 0x10($29)
    /* 12748 00112748 2D400000 */  daddu      $8, $0, $0
    /* 1274C 0011274C 0000B0DF */  ld         $16, 0x0($29)
    /* 12750 00112750 2D480000 */  daddu      $9, $0, $0
    /* 12754 00112754 74F80808 */  j          func_0023E1D0
    /* 12758 00112758 4000BD27 */   addiu     $29, $29, 0x40
endlabel gsb_controlBrightness
    /* 1275C 0011275C 00000000 */  nop
```
