# direction_across_bridge — parked

VRAM: 0x00178588 (file_off 0x078588)
Asm source: asm/aug6/nonmatchings/fumi/src/way_util/direction_across_bridge.s

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=14). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/way_util.c`

**Seed:** `tough_nuts/direction_across_bridge/direction_across_bridge.c`

Disassembly:

```
.align 3
nonmatching direction_across_bridge, 0x118

glabel direction_across_bridge
    /* 78588 00178588 B0FEBD27 */  addiu      $29, $29, -0x150
    /* 7858C 0017858C 4842013C */  lui        $1, (0x42480000 >> 16)
    /* 78590 00178590 00008144 */  mtc1       $1, $f0
    /* 78594 00178594 0001B3FF */  sd         $19, 0x100($29)
    /* 78598 00178598 2D988000 */  daddu      $19, $4, $0
    /* 7859C 0017859C 1001B4FF */  sd         $20, 0x110($29)
    /* 785A0 001785A0 D000B0FF */  sd         $16, 0xD0($29)
    /* 785A4 001785A4 2D20A000 */  daddu      $4, $5, $0
    /* 785A8 001785A8 4001B6E7 */  swc1       $f22, 0x140($29)
    /* 785AC 001785AC 2DA00000 */  daddu      $20, $0, $0
    /* 785B0 001785B0 2001BFFF */  sd         $31, 0x120($29)
    /* 785B4 001785B4 F000B2FF */  sd         $18, 0xF0($29)
    /* 785B8 001785B8 E000B1FF */  sd         $17, 0xE0($29)
    /* 785BC 001785BC 3801B5E7 */  swc1       $f21, 0x138($29)
    /* 785C0 001785C0 3001B4E7 */  swc1       $f20, 0x130($29)
    /* 785C4 001785C4 B80B080C */  jal        WayPointList_begin
    /* 785C8 001785C8 8000A0E7 */   swc1      $f0, 0x80($29)
    /* 785CC 001785CC 608596C7 */  lwc1       $f22, %gp_rel(D_00629150)($28)
    /* 785D0 001785D0 2D804000 */  daddu      $16, $2, $0
    /* 785D4 001785D4 26000012 */  beqz       $16, .L00178670
    /* 785D8 001785D8 1000B227 */   addiu     $18, $29, 0x10
    /* 785DC 001785DC 9642013C */  lui        $1, (0x42960000 >> 16)
    /* 785E0 001785E0 00A88144 */  mtc1       $1, $f21
    /* 785E4 001785E4 10001126 */  addiu      $17, $16, 0x10
.align 2
  .L001785E8:
    /* 785E8 001785E8 2D20A003 */  daddu      $4, $29, $0
    /* 785EC 001785EC 2D282002 */  daddu      $5, $17, $0
    /* 785F0 001785F0 0200090C */  jal        sceVu0SubVector
    /* 785F4 001785F4 2D306002 */   daddu     $6, $19, $0
    /* 785F8 001785F8 4AA0050C */  jal        func_00168128
    /* 785FC 001785FC 2D20A003 */   daddu     $4, $29, $0
    /* 78600 00178600 06050046 */  mov.s      $f20, $f0
    /* 78604 00178604 34A01646 */  c.lt.s     $f20, $f22
    /* 78608 00178608 00000000 */  nop
    /* 7860C 0017860C 13000045 */  bc1f       .L0017865C
    /* 78610 00178610 2D204002 */   daddu     $4, $18, $0
    /* 78614 00178614 2000090C */  jal        sceVu0CopyVector
    /* 78618 00178618 2D286002 */   daddu     $5, $19, $0
    /* 7861C 0017861C 2D282002 */  daddu      $5, $17, $0
    /* 78620 00178620 2000090C */  jal        sceVu0CopyVector
    /* 78624 00178624 2000A427 */   addiu     $4, $29, 0x20
    /* 78628 00178628 1400A1C7 */  lwc1       $f1, 0x14($29)
    /* 7862C 0017862C 2D204002 */  daddu      $4, $18, $0
    /* 78630 00178630 2400A0C7 */  lwc1       $f0, 0x24($29)
    /* 78634 00178634 41081546 */  sub.s      $f1, $f1, $f21
    /* 78638 00178638 01001546 */  sub.s      $f0, $f0, $f21
    /* 7863C 0017863C 1400A1E7 */  swc1       $f1, 0x14($29)
    /* 78640 00178640 7E98050C */  jal        ClipWallBoxStop
    /* 78644 00178644 2400A0E7 */   swc1      $f0, 0x24($29)
    /* 78648 00178648 9800A28F */  lw         $2, 0x98($29)
    /* 7864C 0017864C 03004014 */  bnez       $2, .L0017865C
    /* 78650 00178650 00000000 */   nop
    /* 78654 00178654 86A50046 */  mov.s      $f22, $f20
    /* 78658 00178658 2DA00002 */  daddu      $20, $16, $0
.align 2
  .L0017865C:
    /* 7865C 0017865C C00B080C */  jal        WayPointList_next
    /* 78660 00178660 2D200002 */   daddu     $4, $16, $0
    /* 78664 00178664 2D804000 */  daddu      $16, $2, $0
    /* 78668 00178668 DFFF0016 */  bnez       $16, .L001785E8
    /* 7866C 0017866C 10001126 */   addiu     $17, $16, 0x10
.align 2
  .L00178670:
    /* 78670 00178670 2D108002 */  daddu      $2, $20, $0
    /* 78674 00178674 2001BFDF */  ld         $31, 0x120($29)
    /* 78678 00178678 1001B4DF */  ld         $20, 0x110($29)
    /* 7867C 0017867C 0001B3DF */  ld         $19, 0x100($29)
    /* 78680 00178680 F000B2DF */  ld         $18, 0xF0($29)
    /* 78684 00178684 E000B1DF */  ld         $17, 0xE0($29)
    /* 78688 00178688 D000B0DF */  ld         $16, 0xD0($29)
    /* 7868C 0017868C 4001B6C7 */  lwc1       $f22, 0x140($29)
    /* 78690 00178690 3801B5C7 */  lwc1       $f21, 0x138($29)
    /* 78694 00178694 3001B4C7 */  lwc1       $f20, 0x130($29)
    /* 78698 00178698 0800E003 */  jr         $31
    /* 7869C 0017869C 5001BD27 */   addiu     $29, $29, 0x150
endlabel direction_across_bridge
```
