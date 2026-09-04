# subEnemyControl — parked

VRAM: 0x0015D818 (file_off 0x05D818)
Asm source: asm/aug6/nonmatchings/fumi/src/enemy_act/subEnemyControl.s

## Attempt at 2026-07-07

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=5). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/enemy_act.c`

**Seed:** `tough_nuts/subEnemyControl/subEnemyControl.c`

Disassembly:

```
.align 3
nonmatching subEnemyControl, 0x1AC

glabel subEnemyControl
    /* 5D818 0015D818 40FFBD27 */  addiu      $29, $29, -0xC0
    /* 5D81C 0015D81C 9000BEFF */  sd         $30, 0x90($29)
    /* 5D820 0015D820 8000B7FF */  sd         $23, 0x80($29)
    /* 5D824 0015D824 16001E3C */  lui        $30, %hi(GetEnemyTypeFromGObj)
    /* 5D828 0015D828 7000B6FF */  sd         $22, 0x70($29)
    /* 5D82C 0015D82C 2700173C */  lui        $23, %hi(D_00271240)
    /* 5D830 0015D830 6000B5FF */  sd         $21, 0x60($29)
    /* 5D834 0015D834 01001624 */  addiu      $22, $0, 0x1
    /* 5D838 0015D838 5000B4FF */  sd         $20, 0x50($29)
    /* 5D83C 0015D83C 4000B3FF */  sd         $19, 0x40($29)
    /* 5D840 0015D840 2DA0A000 */  daddu      $20, $5, $0
    /* 5D844 0015D844 3000B2FF */  sd         $18, 0x30($29)
    /* 5D848 0015D848 80A91400 */  sll        $21, $20, 6
    /* 5D84C 0015D84C B000B4E7 */  swc1       $f20, 0xB0($29)
    /* 5D850 0015D850 2D908000 */  daddu      $18, $4, $0
    /* 5D854 0015D854 A000BFFF */  sd         $31, 0xA0($29)
    /* 5D858 0015D858 2D200000 */  daddu      $4, $0, $0
    /* 5D85C 0015D85C 2000B1FF */  sd         $17, 0x20($29)
    /* 5D860 0015D860 60031324 */  addiu      $19, $0, 0x360
    /* 5D864 0015D864 1000B0FF */  sd         $16, 0x10($29)
    /* 5D868 0015D868 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* 5D86C 0015D86C 00A08144 */  mtc1       $1, $f20
    /* 5D870 0015D870 6401458E */  lw         $5, 0x164($18)
    /* 5D874 0015D874 00000000 */  nop
.align 2
  .L0015D878:
    /* 5D878 0015D878 7006A28C */  lw         $2, 0x670($5)
    /* 5D87C 0015D87C 40890400 */  sll        $17, $4, 5
    /* 5D880 0015D880 21102202 */  addu       $2, $17, $2
    /* 5D884 0015D884 7D034380 */  lb         $3, 0x37D($2)
    /* 5D888 0015D888 3B006014 */  bnez       $3, .L0015D978
    /* 5D88C 0015D88C 01008424 */   addiu     $4, $4, 0x1
    /* 5D890 0015D890 2D20A003 */  daddu      $4, $29, $0
    /* 5D894 0015D894 2D280000 */  daddu      $5, $0, $0
    /* 5D898 0015D898 5A81090C */  jal        memset
    /* 5D89C 0015D89C 10000624 */   addiu     $6, $0, 0x10
    /* 5D8A0 0015D8A0 0C00B4E7 */  swc1       $f20, 0xC($29)
    /* 5D8A4 0015D8A4 6401428E */  lw         $2, 0x164($18)
    /* 5D8A8 0015D8A8 5C01438E */  lw         $3, 0x15C($18)
    /* 5D8AC 0015D8AC 7006508C */  lw         $16, 0x670($2)
    /* 5D8B0 0015D8B0 0C00658C */  lw         $5, 0xC($3)
    /* 5D8B4 0015D8B4 21803002 */  addu       $16, $17, $16
    /* 5D8B8 0015D8B8 2128B500 */  addu       $5, $5, $21
    /* 5D8BC 0015D8BC 60031026 */  addiu      $16, $16, 0x360
    /* 5D8C0 0015D8C0 3000A524 */  addiu      $5, $5, 0x30
    /* 5D8C4 0015D8C4 2000090C */  jal        sceVu0CopyVector
    /* 5D8C8 0015D8C8 2D200002 */   daddu     $4, $16, $0
    /* 5D8CC 0015D8CC 6401428E */  lw         $2, 0x164($18)
    /* 5D8D0 0015D8D0 06A30046 */  mov.s      $f12, $f20
    /* 5D8D4 0015D8D4 0C0014E6 */  swc1       $f20, 0xC($16)
    /* 5D8D8 0015D8D8 503BC827 */  addiu      $8, $30, %lo(GetEnemyTypeFromGObj)
    /* 5D8DC 0015D8DC 7006458C */  lw         $5, 0x670($2)
    /* 5D8E0 0015D8E0 0C000424 */  addiu      $4, $0, 0xC
    /* 5D8E4 0015D8E4 2D30A003 */  daddu      $6, $29, $0
    /* 5D8E8 0015D8E8 2128B300 */  addu       $5, $5, $19
    /* 5D8EC 0015D8EC 9253060C */  jal        GatherEffect_Proc
    /* 5D8F0 0015D8F0 2D38A000 */   daddu     $7, $5, $0
    /* 5D8F4 0015D8F4 6401448E */  lw         $4, 0x164($18)
    /* 5D8F8 0015D8F8 0A000724 */  addiu      $7, $0, 0xA
    /* 5D8FC 0015D8FC 3C000624 */  addiu      $6, $0, 0x3C
    /* 5D900 0015D900 7006838C */  lw         $3, 0x670($4)
    /* 5D904 0015D904 21182302 */  addu       $3, $17, $3
    /* 5D908 0015D908 700362AC */  sw         $2, 0x370($3)
    /* 5D90C 0015D90C 6401448E */  lw         $4, 0x164($18)
    /* 5D910 0015D910 7006828C */  lw         $2, 0x670($4)
    /* 5D914 0015D914 21102202 */  addu       $2, $17, $2
    /* 5D918 0015D918 740354AC */  sw         $20, 0x374($2)
    /* 5D91C 0015D91C 2700023C */  lui        $2, %hi(D_00271240)
    /* 5D920 0015D920 4012E38E */  lw         $3, %lo(D_00271240)($23)
    /* 5D924 0015D924 40124224 */  addiu      $2, $2, %lo(D_00271240)
    /* 5D928 0015D928 0400458C */  lw         $5, 0x4($2)
    /* 5D92C 0015D92C 18186700 */  mult       $3, $3, $7
    /* 5D930 0015D930 6401448E */  lw         $4, 0x164($18)
    /* 5D934 0015D934 0100A050 */  beql       $5, $0, .L0015D93C
    /* 5D938 0015D938 CD010000 */   break     0, 7
.align 2
  .L0015D93C:
    /* 5D93C 0015D93C 7006828C */  lw         $2, 0x670($4)
    /* 5D940 0015D940 2330C300 */  subu       $6, $6, $3
    /* 5D944 0015D944 21102202 */  addu       $2, $17, $2
    /* 5D948 0015D948 1A00C500 */  div        $0, $6, $5
    /* 5D94C 0015D94C 12300000 */  mflo       $6
    /* 5D950 0015D950 780346AC */  sw         $6, 0x378($2)
    /* 5D954 0015D954 6401438E */  lw         $3, 0x164($18)
    /* 5D958 0015D958 7006628C */  lw         $2, 0x670($3)
    /* 5D95C 0015D95C 21102202 */  addu       $2, $17, $2
    /* 5D960 0015D960 7C0356A0 */  sb         $22, 0x37C($2)
    /* 5D964 0015D964 6401438E */  lw         $3, 0x164($18)
    /* 5D968 0015D968 7006628C */  lw         $2, 0x670($3)
    /* 5D96C 0015D96C 21102202 */  addu       $2, $17, $2
    /* 5D970 0015D970 07000010 */  b          .L0015D990
    /* 5D974 0015D974 7D0356A0 */   sb        $22, 0x37D($2)
.align 2
  .L0015D978:
    /* 5D978 0015D978 05008228 */  slti       $2, $4, 0x5
    /* 5D97C 0015D97C BEFF4014 */  bnez       $2, .L0015D878
    /* 5D980 0015D980 20007326 */   addiu     $19, $19, 0x20
    /* 5D984 0015D984 2D204002 */  daddu      $4, $18, $0
    /* 5D988 0015D988 FA2E070C */  jal        InitDemoMotionGeo
    /* 5D98C 0015D98C 2D288002 */   daddu     $5, $20, $0
.align 2
  .L0015D990:
    /* 5D990 0015D990 A000BFDF */  ld         $31, 0xA0($29)
    /* 5D994 0015D994 9000BEDF */  ld         $30, 0x90($29)
    /* 5D998 0015D998 8000B7DF */  ld         $23, 0x80($29)
    /* 5D99C 0015D99C 7000B6DF */  ld         $22, 0x70($29)
    /* 5D9A0 0015D9A0 6000B5DF */  ld         $21, 0x60($29)
    /* 5D9A4 0015D9A4 5000B4DF */  ld         $20, 0x50($29)
    /* 5D9A8 0015D9A8 4000B3DF */  ld         $19, 0x40($29)
    /* 5D9AC 0015D9AC 3000B2DF */  ld         $18, 0x30($29)
    /* 5D9B0 0015D9B0 2000B1DF */  ld         $17, 0x20($29)
    /* 5D9B4 0015D9B4 1000B0DF */  ld         $16, 0x10($29)
    /* 5D9B8 0015D9B8 B000B4C7 */  lwc1       $f20, 0xB0($29)
    /* 5D9BC 0015D9BC 0800E003 */  jr         $31
    /* 5D9C0 0015D9C0 C000BD27 */   addiu     $29, $29, 0xC0
endlabel subEnemyControl
    /* 5D9C4 0015D9C4 00000000 */  nop
```
