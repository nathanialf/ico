# gene_enemy — parked

VRAM: 0x00195960 (file_off 0x095960)
Asm source: asm/aug6/nonmatchings/ito/src/itou_boss/gene_enemy.s

## Attempt at 2026-06-09

**Reason parked:** rc10 breakthrough: algorithm + loop body + giv-init copy ALL match ROM. Seed = base-invariant form (base=D_006CCE60 separate var; e=base+k*0x40 index-giv self-incrementing; m/q/r explicit pointers; unsigned k do-while). Residual = pure 2-temp allocator tiebreak: ROM base_e(D_006CCE60)=$3/v1 & base_r(D_00555F00)=$2/v0; built swaps them (base_e=$2). Source reordering (8 init orders), r-index, symmetric-givs all fail to flip it. Permuter-class regalloc copy.

**TU:** `ito/src/itou_boss.c`

**Seed:** `tough_nuts/gene_enemy/gene_enemy.c`

Disassembly:

```
.align 3
nonmatching gene_enemy, 0x110

glabel gene_enemy
    /* 95960 00195960 70FFBD27 */  addiu      $29, $29, -0x90
    /* 95964 00195964 5500063C */  lui        $6, %hi(D_00556348)
    /* 95968 00195968 0000B0FF */  sd         $16, 0x0($29)
    /* 9596C 0019596C 4863C624 */  addiu      $6, $6, %lo(D_00556348)
    /* 95970 00195970 2D808000 */  daddu      $16, $4, $0
    /* 95974 00195974 7000B7FF */  sd         $23, 0x70($29)
    /* 95978 00195978 2097848F */  lw         $4, %gp_rel(D_0062A310)($28)
    /* 9597C 0019597C 2D280000 */  daddu      $5, $0, $0
    /* 95980 00195980 6000B6FF */  sd         $22, 0x60($29)
    /* 95984 00195984 6F010724 */  addiu      $7, $0, 0x16F
    /* 95988 00195988 5000B5FF */  sd         $21, 0x50($29)
    /* 9598C 0019598C 01001724 */  addiu      $23, $0, 0x1
    /* 95990 00195990 4000B4FF */  sd         $20, 0x40($29)
    /* 95994 00195994 02001624 */  addiu      $22, $0, 0x2
    /* 95998 00195998 3000B3FF */  sd         $19, 0x30($29)
    /* 9599C 0019599C 2000B2FF */  sd         $18, 0x20($29)
    /* 959A0 001959A0 1000B1FF */  sd         $17, 0x10($29)
    /* 959A4 001959A4 8000BFFF */  sd         $31, 0x80($29)
    /* 959A8 001959A8 CEE2040C */  jal        iosFree
    /* 959AC 001959AC 2DA00000 */   daddu     $20, $0, $0
    /* 959B0 001959B0 2D200002 */  daddu      $4, $16, $0
    /* 959B4 001959B4 3CFE070C */  jal        actInitialize
    /* 959B8 001959B8 2DA84000 */   daddu     $21, $2, $0
    /* 959BC 001959BC 0CFE070C */  jal        actInitialize_ext_charcter
    /* 959C0 001959C0 2D200002 */   daddu     $4, $16, $0
    /* 959C4 001959C4 5500043C */  lui        $4, %hi(D_00556358)
    /* 959C8 001959C8 35000524 */  addiu      $5, $0, 0x35
    /* 959CC 001959CC F290060C */  jal        debug_assertMessage
    /* 959D0 001959D0 58638424 */   addiu     $4, $4, %lo(D_00556358)
    /* 959D4 001959D4 6D00033C */  lui        $3, %hi(D_006CCE60)
    /* 959D8 001959D8 5500043C */  lui        $4, %hi(D_005551F0)
    /* 959DC 001959DC 60CE6324 */  addiu      $3, $3, %lo(D_006CCE60)
    /* 959E0 001959E0 5500023C */  lui        $2, %hi(D_00555F00)
    /* 959E4 001959E4 005F5324 */  addiu      $19, $2, %lo(D_00555F00)
    /* 959E8 001959E8 F0519224 */  addiu      $18, $4, %lo(D_005551F0)
    /* 959EC 001959EC 2D806000 */  daddu      $16, $3, $0
    /* 959F0 001959F0 20007124 */  addiu      $17, $3, 0x20
    /* 959F4 001959F4 00000000 */  nop
.align 2
  .L001959F8:
    /* 959F8 001959F8 04000282 */  lb         $2, 0x4($16)
    /* 959FC 001959FC 02005714 */  bne        $2, $23, .L00195A08
    /* 95A00 00195A00 000000AE */   sw        $0, 0x0($16)
    /* 95A04 00195A04 040016A2 */  sb         $22, 0x4($16)
.align 2
  .L00195A08:
    /* 95A08 00195A08 2D202002 */  daddu      $4, $17, $0
    /* 95A0C 00195A0C 2000090C */  jal        func_00240080
    /* 95A10 00195A10 2D284002 */   daddu     $5, $18, $0
    /* 95A14 00195A14 01009426 */  addiu      $20, $20, 0x1
    /* 95A18 00195A18 F0FF2426 */  addiu      $4, $17, -0x10
    /* 95A1C 00195A1C 8A57060C */  jal        apply_matrix_w1
    /* 95A20 00195A20 D0FF4526 */   addiu     $5, $18, -0x30
    /* 95A24 00195A24 40005226 */  addiu      $18, $18, 0x40
    /* 95A28 00195A28 300013AE */  sw         $19, 0x30($16)
    /* 95A2C 00195A2C 40003126 */  addiu      $17, $17, 0x40
    /* 95A30 00195A30 10007326 */  addiu      $19, $19, 0x10
    /* 95A34 00195A34 3500822E */  sltiu      $2, $20, 0x35
    /* 95A38 00195A38 EFFF4014 */  bnez       $2, .L001959F8
    /* 95A3C 00195A3C 40001026 */   addiu     $16, $16, 0x40
    /* 95A40 00195A40 2D10A002 */  daddu      $2, $21, $0
    /* 95A44 00195A44 8000BFDF */  ld         $31, 0x80($29)
    /* 95A48 00195A48 7000B7DF */  ld         $23, 0x70($29)
    /* 95A4C 00195A4C 6000B6DF */  ld         $22, 0x60($29)
    /* 95A50 00195A50 5000B5DF */  ld         $21, 0x50($29)
    /* 95A54 00195A54 4000B4DF */  ld         $20, 0x40($29)
    /* 95A58 00195A58 3000B3DF */  ld         $19, 0x30($29)
    /* 95A5C 00195A5C 2000B2DF */  ld         $18, 0x20($29)
    /* 95A60 00195A60 1000B1DF */  ld         $17, 0x10($29)
    /* 95A64 00195A64 0000B0DF */  ld         $16, 0x0($29)
    /* 95A68 00195A68 0800E003 */  jr         $31
    /* 95A6C 00195A6C 9000BD27 */   addiu     $29, $29, 0x90
endlabel gene_enemy
```
