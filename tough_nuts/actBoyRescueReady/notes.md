# actBoyRescueReady — parked

VRAM: 0x001528A8 (file_off 0x0528A8)
Asm source: asm/aug6/nonmatchings/fumi/src/boyact/actBoyRescueReady.s

## Attempt at 2026-07-07

**Reason parked:** rc6 reorg tie: CylinderCollision delay-slot occupant (swc1 vs weapon lw a0) + weapon-reload v0/v1 coloring at +0x16C store; 6 distinct source shapes fold; permuter-class

**TU:** `fumi/src/boyact.c`

**Seed:** `tough_nuts/actBoyRescueReady/actBoyRescueReady.c`

Disassembly:

```
.align 3
nonmatching actBoyRescueReady, 0x90

glabel actBoyRescueReady
    /* 528A8 001528A8 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 528AC 001528AC F491828F */  lw         $2, %gp_rel(D_00629DE4)($28)
    /* 528B0 001528B0 2000BFFF */  sd         $31, 0x20($29)
    /* 528B4 001528B4 1C004010 */  beqz       $2, .L00152928
    /* 528B8 001528B8 1000B0FF */   sd        $16, 0x10($29)
    /* 528BC 001528BC 6401508C */  lw         $16, 0x164($2)
    /* 528C0 001528C0 3001048E */  lw         $4, 0x130($16)
    /* 528C4 001528C4 14008010 */  beqz       $4, .L00152918
    /* 528C8 001528C8 6A00023C */   lui       $2, %hi(D_006A4608)
    /* 528CC 001528CC 22C4070C */  jal        ExecWeaponHitReaction
    /* 528D0 001528D0 00000000 */   nop
    /* 528D4 001528D4 2D20A003 */  daddu      $4, $29, $0
    /* 528D8 001528D8 2D280000 */  daddu      $5, $0, $0
    /* 528DC 001528DC 5A81090C */  jal        func_00260568
    /* 528E0 001528E0 10000624 */   addiu     $6, $0, 0x10
    /* 528E4 001528E4 2C8380C7 */  lwc1       $f0, %gp_rel(D_00628F1C)($28)
    /* 528E8 001528E8 2D28A003 */  daddu      $5, $29, $0
    /* 528EC 001528EC 0000A0E7 */  swc1       $f0, 0x0($29)
    /* 528F0 001528F0 5810040C */  jal        CylinderCollision
    /* 528F4 001528F4 3001048E */   lw        $4, 0x130($16)
    /* 528F8 001528F8 3001048E */  lw         $4, 0x130($16)
    /* 528FC 001528FC 2D280000 */  daddu      $5, $0, $0
    /* 52900 00152900 A090878F */  lw         $7, %gp_rel(D_00629C90)($28)
    /* 52904 00152904 6EAE060C */  jal        func_001AB9B8
    /* 52908 00152908 2D300000 */   daddu     $6, $0, $0
    /* 5290C 0015290C 3001038E */  lw         $3, 0x130($16)
    /* 52910 00152910 6C0160AC */  sw         $0, 0x16C($3)
    /* 52914 00152914 6A00023C */  lui        $2, %hi(D_006A4608)
.align 2
  .L00152918:
    /* 52918 00152918 6A00033C */  lui        $3, %hi(D_006A45A0)
    /* 5291C 0015291C 084640AC */  sw         $0, %lo(D_006A4608)($2)
    /* 52920 00152920 A04560AC */  sw         $0, %lo(D_006A45A0)($3)
    /* 52924 00152924 300100AE */  sw         $0, 0x130($16)
.align 2
  .L00152928:
    /* 52928 00152928 2000BFDF */  ld         $31, 0x20($29)
    /* 5292C 0015292C 1000B0DF */  ld         $16, 0x10($29)
    /* 52930 00152930 0800E003 */  jr         $31
    /* 52934 00152934 3000BD27 */   addiu     $29, $29, 0x30
endlabel actBoyRescueReady
```
