# actEnemy_isSmallEnemy — parked

VRAM: 0x00163750 (file_off 0x063750)
Asm source: asm/aug6/nonmatchings/fumi/src/enemy_act/actEnemy_isSmallEnemy.s

## Attempt at 2026-07-07

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=2). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/enemy_act.c`

**Seed:** `tough_nuts/actEnemy_isSmallEnemy/actEnemy_isSmallEnemy.c`

Disassembly:

```
.align 3
nonmatching actEnemy_isSmallEnemy, 0xDC

glabel actEnemy_isSmallEnemy
    /* 63750 00163750 90FFBD27 */  addiu      $29, $29, -0x70
    /* 63754 00163754 0000A4AF */  sw         $4, 0x0($29)
    /* 63758 00163758 4000B3FF */  sd         $19, 0x40($29)
    /* 6375C 0016375C 6000B4E7 */  swc1       $f20, 0x60($29)
    /* 63760 00163760 5000BFFF */  sd         $31, 0x50($29)
    /* 63764 00163764 3000B2FF */  sd         $18, 0x30($29)
    /* 63768 00163768 1000B0FF */  sd         $16, 0x10($29)
    /* 6376C 0016376C 0000A28F */  lw         $2, 0x0($29)
    /* 63770 00163770 2000B1FF */  sd         $17, 0x20($29)
    /* 63774 00163774 6401518C */  lw         $17, 0x164($2)
    /* 63778 00163778 4843013C */  lui        $1, (0x43480000 >> 16)
    /* 6377C 0016377C 00A08144 */  mtc1       $1, $f20
    /* 63780 00163780 2C01328E */  lw         $18, 0x12C($17)
    /* 63784 00163784 00013326 */  addiu      $19, $17, 0x100
.align 2
  .L00163788:
    /* 63788 00163788 0000A48F */  lw         $4, 0x0($29)
    /* 6378C 0016378C 3E74050C */  jal        ContinueCorrectPosition
    /* 63790 00163790 00000000 */   nop
    /* 63794 00163794 2D804000 */  daddu      $16, $2, $0
    /* 63798 00163798 3E74050C */  jal        ContinueCorrectPosition
    /* 6379C 0016379C 2D204002 */   daddu     $4, $18, $0
    /* 637A0 001637A0 2D200002 */  daddu      $4, $16, $0
    /* 637A4 001637A4 F246060C */  jal        ClearHandCameraCorrect
    /* 637A8 001637A8 2D284000 */   daddu     $5, $2, $0
    /* 637AC 001637AC 34001446 */  c.lt.s     $f0, $f20
    /* 637B0 001637B0 2D306002 */  daddu      $6, $19, $0
    /* 637B4 001637B4 2D380000 */  daddu      $7, $0, $0
    /* 637B8 001637B8 C842013C */  lui        $1, (0x42C80000 >> 16)
    /* 637BC 001637BC 00608144 */  mtc1       $1, $f12
    /* 637C0 001637C0 2D400000 */  daddu      $8, $0, $0
    /* 637C4 001637C4 2D284002 */  daddu      $5, $18, $0
    /* 637C8 001637C8 05000045 */  bc1f       .L001637E0
    /* 637CC 001637CC 01000424 */   addiu     $4, $0, 0x1
    /* 637D0 001637D0 6004080C */  jal        _ACTWait
    /* 637D4 001637D4 00000000 */   nop
    /* 637D8 001637D8 EBFF0010 */  b          .L00163788
    /* 637DC 001637DC 00000000 */   nop
.align 2
  .L001637E0:
    /* 637E0 001637E0 0000A48F */  lw         $4, 0x0($29)
    /* 637E4 001637E4 7A8F050C */  jal        DispCollisionPC
    /* 637E8 001637E8 00000000 */   nop
    /* 637EC 001637EC FF004230 */  andi       $2, $2, 0xFF
    /* 637F0 001637F0 06004014 */  bnez       $2, .L0016380C
    /* 637F4 001637F4 1E000424 */   addiu     $4, $0, 0x1E
    /* 637F8 001637F8 3C0320AE */  sw         $0, 0x33C($17)
    /* 637FC 001637FC 000120AE */  sw         $0, 0x100($17)
    /* 63800 00163800 040120AE */  sw         $0, 0x104($17)
    /* 63804 00163804 6004080C */  jal        _ACTWait
    /* 63808 00163808 080120AE */   sw        $0, 0x108($17)
.align 2
  .L0016380C:
    /* 6380C 0016380C 3C0320AE */  sw         $0, 0x33C($17)
    /* 63810 00163810 3C000424 */  addiu      $4, $0, 0x3C
    /* 63814 00163814 000120AE */  sw         $0, 0x100($17)
    /* 63818 00163818 040120AE */  sw         $0, 0x104($17)
    /* 6381C 0016381C 6004080C */  jal        _ACTWait
    /* 63820 00163820 080120AE */   sw        $0, 0x108($17)
    /* 63824 00163824 D8FF0010 */  b          .L00163788
    /* 63828 00163828 00000000 */   nop
endlabel actEnemy_isSmallEnemy
    /* 6382C 0016382C 00000000 */  nop
```
