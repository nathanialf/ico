# ChangeMailInLadder — parked

VRAM: 0x001549A0 (file_off 0x0549A0)
Asm source: asm/aug6/nonmatchings/fumi/src/commonact/ChangeMailInLadder.s

## Attempt at 2026-06-21

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=2). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/commonact.c`

**Seed:** `tough_nuts/ChangeMailInLadder/ChangeMailInLadder.c`

Disassembly:

```
.align 3
nonmatching ChangeMailInLadder, 0x12C

glabel ChangeMailInLadder
    /* 549A0 001549A0 A0FFBD27 */  addiu      $29, $29, -0x60
    /* 549A4 001549A4 3000B1FF */  sd         $17, 0x30($29)
    /* 549A8 001549A8 2000B0FF */  sd         $16, 0x20($29)
    /* 549AC 001549AC 2D888000 */  daddu      $17, $4, $0
    /* 549B0 001549B0 4000BFFF */  sd         $31, 0x40($29)
    /* 549B4 001549B4 2D80A000 */  daddu      $16, $5, $0
    /* 549B8 001549B8 5800B5E7 */  swc1       $f21, 0x58($29)
    /* 549BC 001549BC 1000A527 */  addiu      $5, $29, 0x10
    /* 549C0 001549C0 5000B4E7 */  swc1       $f20, 0x50($29)
    /* 549C4 001549C4 6401028E */  lw         $2, 0x164($16)
    /* 549C8 001549C8 5037060C */  jal        GetChainHangRange
    /* 549CC 001549CC 8001448C */   lw        $4, 0x180($2)
    /* 549D0 001549D0 2B004010 */  beqz       $2, .L00154A80
    /* 549D4 001549D4 2D20A003 */   daddu     $4, $29, $0
    /* 549D8 001549D8 2D280000 */  daddu      $5, $0, $0
    /* 549DC 001549DC 348395C7 */  lwc1       $f21, %gp_rel(D_00628F24)($28)
    /* 549E0 001549E0 5A81090C */  jal        func_00260568
    /* 549E4 001549E4 10000624 */   addiu     $6, $0, 0x10
    /* 549E8 001549E8 3443013C */  lui        $1, (0x43340000 >> 16)
    /* 549EC 001549EC 00A08144 */  mtc1       $1, $f20
    /* 549F0 001549F0 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* 549F4 001549F4 00008144 */  mtc1       $1, $f0
    /* 549F8 001549F8 2D200002 */  daddu      $4, $16, $0
    /* 549FC 001549FC 2274050C */  jal        subCommonIdle
    /* 54A00 00154A00 0800A0E7 */   swc1      $f0, 0x8($29)
    /* 54A04 00154A04 8C47060C */  jal        func_00191E30
    /* 54A08 00154A08 2D204000 */   daddu     $4, $2, $0
    /* 54A0C 00154A0C 00000000 */  nop
    /* 54A10 00154A10 00000000 */  nop
    /* 54A14 00154A14 03001546 */  div.s      $f0, $f0, $f21
    /* 54A18 00154A18 1000A28F */  lw         $2, 0x10($29)
    /* 54A1C 00154A1C 02001446 */  mul.s      $f0, $f0, $f20
    /* 54A20 00154A20 64000046 */  .word      0x46000064                    # cvt.w.s    $f1, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* 54A24 00154A24 00080444 */  mfc1       $4, $f1
    /* 54A28 00154A28 5848060C */  jal        func_00192160
    /* 54A2C 00154A2C 23208200 */   subu      $4, $4, $2
    /* 54A30 00154A30 6E48060C */  jal        InitMailAdditionalData
    /* 54A34 00154A34 2D204000 */   daddu     $4, $2, $0
    /* 54A38 00154A38 1000A48F */  lw         $4, 0x10($29)
    /* 54A3C 00154A3C 5848060C */  jal        func_00192160
    /* 54A40 00154A40 21208200 */   addu      $4, $4, $2
    /* 54A44 00154A44 00608244 */  mtc1       $2, $f12
    /* 54A48 00154A48 20638046 */  cvt.s.w    $f12, $f12
    /* 54A4C 00154A4C 02631546 */  mul.s      $f12, $f12, $f21
    /* 54A50 00154A50 00000000 */  nop
    /* 54A54 00154A54 00000000 */  nop
    /* 54A58 00154A58 03631446 */  div.s      $f12, $f12, $f20
    /* 54A5C 00154A5C 6E47060C */  jal        func_00191DB8
    /* 54A60 00154A60 2D20A003 */   daddu     $4, $29, $0
    /* 54A64 00154A64 0000A1C7 */  lwc1       $f1, 0x0($29)
    /* 54A68 00154A68 0400A2C7 */  lwc1       $f2, 0x4($29)
    /* 54A6C 00154A6C 0800A0C7 */  lwc1       $f0, 0x8($29)
    /* 54A70 00154A70 000021E6 */  swc1       $f1, 0x0($17)
    /* 54A74 00154A74 080020E6 */  swc1       $f0, 0x8($17)
    /* 54A78 00154A78 0D000010 */  b          .L00154AB0
    /* 54A7C 00154A7C 040022E6 */   swc1      $f2, 0x4($17)
.align 2
  .L00154A80:
    /* 54A80 00154A80 2274050C */  jal        subCommonIdle
    /* 54A84 00154A84 2D200002 */   daddu     $4, $16, $0
    /* 54A88 00154A88 000040C4 */  lwc1       $f0, 0x0($2)
    /* 54A8C 00154A8C 2D200002 */  daddu      $4, $16, $0
    /* 54A90 00154A90 2274050C */  jal        subCommonIdle
    /* 54A94 00154A94 000020E6 */   swc1      $f0, 0x0($17)
    /* 54A98 00154A98 040040C4 */  lwc1       $f0, 0x4($2)
    /* 54A9C 00154A9C 2D200002 */  daddu      $4, $16, $0
    /* 54AA0 00154AA0 2274050C */  jal        subCommonIdle
    /* 54AA4 00154AA4 040020E6 */   swc1      $f0, 0x4($17)
    /* 54AA8 00154AA8 080040C4 */  lwc1       $f0, 0x8($2)
    /* 54AAC 00154AAC 080020E6 */  swc1       $f0, 0x8($17)
.align 2
  .L00154AB0:
    /* 54AB0 00154AB0 4000BFDF */  ld         $31, 0x40($29)
    /* 54AB4 00154AB4 3000B1DF */  ld         $17, 0x30($29)
    /* 54AB8 00154AB8 2000B0DF */  ld         $16, 0x20($29)
    /* 54ABC 00154ABC 5800B5C7 */  lwc1       $f21, 0x58($29)
    /* 54AC0 00154AC0 5000B4C7 */  lwc1       $f20, 0x50($29)
    /* 54AC4 00154AC4 0800E003 */  jr         $31
    /* 54AC8 00154AC8 6000BD27 */   addiu     $29, $29, 0x60
endlabel ChangeMailInLadder
    /* 54ACC 00154ACC 00000000 */  nop
```
