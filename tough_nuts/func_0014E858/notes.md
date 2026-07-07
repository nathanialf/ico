# func_0014E858 — parked

VRAM: 0x0014E858 (file_off 0x04E858)
Asm source: asm/aug6/nonmatchings/fumi/src/boyact/func_0014E858.s

## Attempt at 2026-07-07

**Reason parked:** rc41 structure recovered (GObjAddHead branch, disp_memory_partition, D_002A0A90 stride-0x4C table float-scale w/ div.s + 6-float copy branch); residual: frame-size (g/base callee-save alloc) + FP mul/div scheduling + fp-reg; permuter-class

**TU:** `fumi/src/boyact.c`

**Seed:** `tough_nuts/func_0014E858/func_0014E858.c`

Disassembly:

```
.align 3
nonmatching func_0014E858, 0x134

glabel func_0014E858
    /* 4E858 0014E858 C0FFBD27 */  addiu      $29, $29, -0x40
    /* 4E85C 0014E85C 1000B1FF */  sd         $17, 0x10($29)
    /* 4E860 0014E860 0000B0FF */  sd         $16, 0x0($29)
    /* 4E864 0014E864 6A00113C */  lui        $17, %hi(D_006A45A0)
    /* 4E868 0014E868 3000BFFF */  sd         $31, 0x30($29)
    /* 4E86C 0014E86C 2000B2FF */  sd         $18, 0x20($29)
    /* 4E870 0014E870 6401928C */  lw         $18, 0x164($4)
    /* 4E874 0014E874 A045248E */  lw         $4, %lo(D_006A45A0)($17)
    /* 4E878 0014E878 05008010 */  beqz       $4, .L0014E890
    /* 4E87C 0014E87C A0453026 */   addiu     $16, $17, %lo(D_006A45A0)
    /* 4E880 0014E880 74F9040C */  jal        isysGObjAddHead
    /* 4E884 0014E884 00000000 */   nop
    /* 4E888 0014E888 02000010 */  b          .L0014E894
    /* 4E88C 0014E88C 200002AE */   sw        $2, 0x20($16)
.align 2
  .L0014E890:
    /* 4E890 0014E890 200000AE */  sw         $0, 0x20($16)
.align 2
  .L0014E894:
    /* 4E894 0014E894 F805508E */  lw         $16, 0x5F8($18)
    /* 4E898 0014E898 A0453126 */  addiu      $17, $17, %lo(D_006A45A0)
    /* 4E89C 0014E89C 0C00048E */  lw         $4, 0xC($16)
    /* 4E8A0 0014E8A0 0800058E */  lw         $5, 0x8($16)
    /* 4E8A4 0014E8A4 E2AE060C */  jal        disp_memory_partition
    /* 4E8A8 0014E8A8 240030AE */   sw        $16, 0x24($17)
    /* 4E8AC 0014E8AC 0E004050 */  beql       $2, $0, .L0014E8E8
    /* 4E8B0 0014E8B0 0800028E */   lw        $2, 0x8($16)
    /* 4E8B4 0014E8B4 100040C4 */  lwc1       $f0, 0x10($2)
    /* 4E8B8 0014E8B8 300020E6 */  swc1       $f0, 0x30($17)
    /* 4E8BC 0014E8BC 140041C4 */  lwc1       $f1, 0x14($2)
    /* 4E8C0 0014E8C0 340021E6 */  swc1       $f1, 0x34($17)
    /* 4E8C4 0014E8C4 180040C4 */  lwc1       $f0, 0x18($2)
    /* 4E8C8 0014E8C8 380020E6 */  swc1       $f0, 0x38($17)
    /* 4E8CC 0014E8CC 200041C4 */  lwc1       $f1, 0x20($2)
    /* 4E8D0 0014E8D0 400021E6 */  swc1       $f1, 0x40($17)
    /* 4E8D4 0014E8D4 240040C4 */  lwc1       $f0, 0x24($2)
    /* 4E8D8 0014E8D8 440020E6 */  swc1       $f0, 0x44($17)
    /* 4E8DC 0014E8DC 280041C4 */  lwc1       $f1, 0x28($2)
    /* 4E8E0 0014E8E0 24000010 */  b          .L0014E974
    /* 4E8E4 0014E8E4 480021E6 */   swc1      $f1, 0x48($17)
.align 2
  .L0014E8E8:
    /* 4E8E8 0014E8E8 4C000424 */  addiu      $4, $0, 0x4C
    /* 4E8EC 0014E8EC 2A00033C */  lui        $3, %hi(D_002A0A90)
    /* 4E8F0 0014E8F0 F48280C7 */  lwc1       $f0, %gp_rel(D_00628EE4)($28)
    /* 4E8F4 0014E8F4 18104400 */  mult       $2, $2, $4
    /* 4E8F8 0014E8F8 900A6324 */  addiu      $3, $3, %lo(D_002A0A90)
    /* 4E8FC 0014E8FC 3443013C */  lui        $1, (0x43340000 >> 16)
    /* 4E900 0014E900 00308144 */  mtc1       $1, $f6
    /* 4E904 0014E904 21104300 */  addu       $2, $2, $3
    /* 4E908 0014E908 140041C4 */  lwc1       $f1, 0x14($2)
    /* 4E90C 0014E90C 0C0044C4 */  lwc1       $f4, 0xC($2)
    /* 4E910 0014E910 100045C4 */  lwc1       $f5, 0x10($2)
    /* 4E914 0014E914 42080046 */  mul.s      $f1, $f1, $f0
    /* 4E918 0014E918 02210046 */  mul.s      $f4, $f4, $f0
    /* 4E91C 0014E91C 180043C4 */  lwc1       $f3, 0x18($2)
    /* 4E920 0014E920 42290046 */  mul.s      $f5, $f5, $f0
    /* 4E924 0014E924 1C0042C4 */  lwc1       $f2, 0x1C($2)
    /* 4E928 0014E928 00000000 */  nop
    /* 4E92C 0014E92C 00000000 */  nop
    /* 4E930 0014E930 43080646 */  div.s      $f1, $f1, $f6
    /* 4E934 0014E934 200040C4 */  lwc1       $f0, 0x20($2)
    /* 4E938 0014E938 00000000 */  nop
    /* 4E93C 0014E93C 00000000 */  nop
    /* 4E940 0014E940 03210646 */  div.s      $f4, $f4, $f6
    /* 4E944 0014E944 00000000 */  nop
    /* 4E948 0014E948 00000000 */  nop
    /* 4E94C 0014E94C 43290646 */  div.s      $f5, $f5, $f6
    /* 4E950 0014E950 C7180046 */  neg.s      $f3, $f3
    /* 4E954 0014E954 87100046 */  neg.s      $f2, $f2
    /* 4E958 0014E958 07000046 */  neg.s      $f0, $f0
    /* 4E95C 0014E95C 480021E6 */  swc1       $f1, 0x48($17)
    /* 4E960 0014E960 300023E6 */  swc1       $f3, 0x30($17)
    /* 4E964 0014E964 340022E6 */  swc1       $f2, 0x34($17)
    /* 4E968 0014E968 380020E6 */  swc1       $f0, 0x38($17)
    /* 4E96C 0014E96C 400024E6 */  swc1       $f4, 0x40($17)
    /* 4E970 0014E970 440025E6 */  swc1       $f5, 0x44($17)
.align 2
  .L0014E974:
    /* 4E974 0014E974 3000BFDF */  ld         $31, 0x30($29)
    /* 4E978 0014E978 2000B2DF */  ld         $18, 0x20($29)
    /* 4E97C 0014E97C 1000B1DF */  ld         $17, 0x10($29)
    /* 4E980 0014E980 0000B0DF */  ld         $16, 0x0($29)
    /* 4E984 0014E984 0800E003 */  jr         $31
    /* 4E988 0014E988 4000BD27 */   addiu     $29, $29, 0x40
endlabel func_0014E858
    /* 4E98C 0014E98C 00000000 */  nop
```
