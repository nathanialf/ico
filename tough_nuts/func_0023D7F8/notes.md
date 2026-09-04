# func_0023D7F8 — parked

VRAM: 0x0023D7F8 (file_off 0x13D7F8)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0023D7F8.s

## Attempt at 2026-06-21

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=36). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0023D7F8/func_0023D7F8.c`

Disassembly:

```
.align 3
nonmatching func_0023D7F8, 0x118

glabel func_0023D7F8
    /* 13D7F8 0023D7F8 0C010724 */  addiu      $7, $0, 0x10C
    /* 13D7FC 0023D7FC C0FFBD27 */  addiu      $29, $29, -0x40
    /* 13D800 0023D800 1838A700 */  mult       $7, $5, $7
    /* 13D804 0023D804 1000B1FF */  sd         $17, 0x10($29)
    /* 13D808 0023D808 2000B2FF */  sd         $18, 0x20($29)
    /* 13D80C 0023D80C 2D888000 */  daddu      $17, $4, $0
    /* 13D810 0023D810 0000B0FF */  sd         $16, 0x0($29)
    /* 13D814 0023D814 4D00063C */  lui        $6, %hi(D_004CED88)
    /* 13D818 0023D818 3000BFFF */  sd         $31, 0x30($29)
    /* 13D81C 0023D81C 88EDC624 */  addiu      $6, $6, %lo(D_004CED88)
    /* 13D820 0023D820 300025A6 */  sh         $5, 0x30($17)
    /* 13D824 0023D824 2180E600 */  addu       $16, $7, $6
    /* 13D828 0023D828 C3FF043C */  lui        $4, (0xFFC3FFFF >> 16)
    /* 13D82C 0023D82C FFFF8434 */  ori        $4, $4, (0xFFC3FFFF & 0xFFFF)
    /* 13D830 0023D830 3FFC053C */  lui        $5, (0xFC3FFFFF >> 16)
    /* 13D834 0023D834 FFFFA534 */  ori        $5, $5, (0xFC3FFFFF & 0xFFFF)
    /* 13D838 0023D838 08010292 */  lbu        $2, 0x108($16)
    /* 13D83C 0023D83C 2140C700 */  addu       $8, $6, $7
    /* 13D840 0023D840 300023DE */  ld         $3, 0x30($17)
    /* 13D844 0023D844 2D300001 */  daddu      $6, $8, $0
    /* 13D848 0023D848 3A110200 */  dsrl       $2, $2, 4
    /* 13D84C 0023D84C 24186400 */  and        $3, $3, $4
    /* 13D850 0023D850 B8140200 */  dsll       $2, $2, 18
    /* 13D854 0023D854 25186200 */  or         $3, $3, $2
    /* 13D858 0023D858 40080424 */  addiu      $4, $0, 0x840
    /* 13D85C 0023D85C 300023FE */  sd         $3, 0x30($17)
    /* 13D860 0023D860 24186500 */  and        $3, $3, $5
    /* 13D864 0023D864 0801028E */  lw         $2, 0x108($16)
    /* 13D868 0023D868 02120200 */  srl        $2, $2, 8
    /* 13D86C 0023D86C 0F004230 */  andi       $2, $2, 0xF
    /* 13D870 0023D870 B8150200 */  dsll       $2, $2, 22
    /* 13D874 0023D874 25186200 */  or         $3, $3, $2
    /* 13D878 0023D878 300023FE */  sd         $3, 0x30($17)
    /* 13D87C 0023D87C FC0000C5 */  lwc1       $f0, 0xFC($8)
    /* 13D880 0023D880 340020E6 */  swc1       $f0, 0x34($17)
    /* 13D884 0023D884 0001C1C4 */  lwc1       $f1, 0x100($6)
    /* 13D888 0023D888 28CF070C */  jal        freeseki
    /* 13D88C 0023D88C 380021E6 */   swc1      $f1, 0x38($17)
    /* 13D890 0023D890 2D904000 */  daddu      $18, $2, $0
    /* 13D894 0023D894 00010424 */  addiu      $4, $0, 0x100
    /* 13D898 0023D898 28CF070C */  jal        freeseki
    /* 13D89C 0023D89C 280032AE */   sw        $18, 0x28($17)
    /* 13D8A0 0023D8A0 340842AE */  sw         $2, 0x834($18)
    /* 13D8A4 0023D8A4 50000524 */  addiu      $5, $0, 0x50
    /* 13D8A8 0023D8A8 0801038E */  lw         $3, 0x108($16)
    /* 13D8AC 0023D8AC 100851AE */  sw         $17, 0x810($18)
    /* 13D8B0 0023D8B0 0F006330 */  andi       $3, $3, 0xF
    /* 13D8B4 0023D8B4 F00043AC */  sw         $3, 0xF0($2)
    /* 13D8B8 0023D8B8 2E002482 */  lb         $4, 0x2E($17)
    /* 13D8BC 0023D8BC 28CF070C */  jal        freeseki
    /* 13D8C0 0023D8C0 18208500 */   mult      $4, $4, $5
    /* 13D8C4 0023D8C4 3408438E */  lw         $3, 0x834($18)
    /* 13D8C8 0023D8C8 04000424 */  addiu      $4, $0, 0x4
    /* 13D8CC 0023D8CC 300842AE */  sw         $2, 0x830($18)
    /* 13D8D0 0023D8D0 F000628C */  lw         $2, 0xF0($3)
    /* 13D8D4 0023D8D4 07004410 */  beq        $2, $4, .L0023D8F4
    /* 13D8D8 0023D8D8 6300043C */   lui       $4, %hi(D_006280E0)
    /* 13D8DC 0023D8DC 2400228E */  lw         $2, 0x24($17)
    /* 13D8E0 0023D8E0 05004010 */  beqz       $2, .L0023D8F8
    /* 13D8E4 0023D8E4 3000BFDF */   ld        $31, 0x30($29)
    /* 13D8E8 0023D8E8 F83B040C */  jal        func_0010EFE0
    /* 13D8EC 0023D8EC 2D204002 */   daddu     $4, $18, $0
    /* 13D8F0 0023D8F0 6300043C */  lui        $4, %hi(D_006280E0)
.align 2
  .L0023D8F4:
    /* 13D8F4 0023D8F4 3000BFDF */  ld         $31, 0x30($29)
.align 2
  .L0023D8F8:
    /* 13D8F8 0023D8F8 2000B2DF */  ld         $18, 0x20($29)
    /* 13D8FC 0023D8FC E0808424 */  addiu      $4, $4, %lo(D_006280E0)
    /* 13D900 0023D900 1000B1DF */  ld         $17, 0x10($29)
    /* 13D904 0023D904 0000B0DF */  ld         $16, 0x0($29)
    /* 13D908 0023D908 F2900608 */  j          debug_StdPrintfDummy
    /* 13D90C 0023D90C 4000BD27 */   addiu     $29, $29, 0x40
endlabel func_0023D7F8
```
