# quick_save_wpfile — parked

VRAM: 0x00204D20 (file_off 0x104D20)
Asm source: asm/aug6/nonmatchings/fumi/src/way_tool/quick_save_wpfile.s

## Attempt at 2026-06-21

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=4). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/way_tool.c`

**Seed:** `tough_nuts/quick_save_wpfile/quick_save_wpfile.c`

Disassembly:

```
.align 3
nonmatching quick_save_wpfile, 0x120

glabel quick_save_wpfile
    /* 104D20 00204D20 90FFBD27 */  addiu      $29, $29, -0x70
    /* 104D24 00204D24 5000B2FF */  sd         $18, 0x50($29)
    /* 104D28 00204D28 4000B1FF */  sd         $17, 0x40($29)
    /* 104D2C 00204D2C 3000B0FF */  sd         $16, 0x30($29)
    /* 104D30 00204D30 6000BFFF */  sd         $31, 0x60($29)
    /* 104D34 00204D34 0000A4AF */  sw         $4, 0x0($29)
    /* 104D38 00204D38 7E75060C */  jal        backStageProcessMain
    /* 104D3C 00204D3C 6100113C */   lui       $17, %hi(D_00614370)
    /* 104D40 00204D40 76E3050C */  jal        func_00178DD8
    /* 104D44 00204D44 07000424 */   addiu     $4, $0, 0x7
    /* 104D48 00204D48 40D1060C */  jal        lt_fade_status
    /* 104D4C 00204D4C 33000424 */   addiu     $4, $0, 0x33
    /* 104D50 00204D50 01000224 */  addiu      $2, $0, 0x1
    /* 104D54 00204D54 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* 104D58 00204D58 2AE4050C */  jal        func_001790A8
    /* 104D5C 00204D5C A49C82AF */   sw        $2, %gp_rel(D_0062A894)($28)
    /* 104D60 00204D60 28020424 */  addiu      $4, $0, 0x228
    /* 104D64 00204D64 01000524 */  addiu      $5, $0, 0x1
    /* 104D68 00204D68 76A5040C */  jal        stage_KillPlayBgAnimation
    /* 104D6C 00204D6C 2D300000 */   daddu     $6, $0, $0
    /* 104D70 00204D70 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* 104D74 00204D74 DEE3050C */  jal        gflagOff
    /* 104D78 00204D78 2D010524 */   addiu     $5, $0, 0x12D
    /* 104D7C 00204D7C 2000B027 */  addiu      $16, $29, 0x20
    /* 104D80 00204D80 03000010 */  b          .L00204D90
    /* 104D84 00204D84 1000B227 */   addiu     $18, $29, 0x10
.align 2
  .L00204D88:
    /* 104D88 00204D88 6004080C */  jal        _ACTWait
    /* 104D8C 00204D8C 01000424 */   addiu     $4, $0, 0x1
.align 2
  .L00204D90:
    /* 104D90 00204D90 56AA040C */  jal        func_0012A958
    /* 104D94 00204D94 28020424 */   addiu     $4, $0, 0x228
    /* 104D98 00204D98 FBFF4010 */  beqz       $2, .L00204D88
    /* 104D9C 00204D9C 00000000 */   nop
    /* 104DA0 00204DA0 6004080C */  jal        _ACTWait
    /* 104DA4 00204DA4 01000424 */   addiu     $4, $0, 0x1
    /* 104DA8 00204DA8 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* 104DAC 00204DAC DEE3050C */  jal        gflagOff
    /* 104DB0 00204DB0 2D280000 */   daddu     $5, $0, $0
    /* 104DB4 00204DB4 70432226 */  addiu      $2, $17, %lo(D_00614370)
    /* 104DB8 00204DB8 704323DE */  ld         $3, %lo(D_00614370)($17)
    /* 104DBC 00204DBC 080045DC */  ld         $5, 0x8($2)
    /* 104DC0 00204DC0 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* 104DC4 00204DC4 1000A3FF */  sd         $3, 0x10($29)
    /* 104DC8 00204DC8 3E74050C */  jal        ContinueCorrectPosition
    /* 104DCC 00204DCC 1800A5FF */   sd        $5, 0x18($29)
    /* 104DD0 00204DD0 2D284002 */  daddu      $5, $18, $0
    /* 104DD4 00204DD4 2D304000 */  daddu      $6, $2, $0
    /* 104DD8 00204DD8 0200090C */  jal        func_00240008
    /* 104DDC 00204DDC 2D200002 */   daddu     $4, $16, $0
    /* 104DE0 00204DE0 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* 104DE4 00204DE4 B6E3050C */  jal        gflagChk
    /* 104DE8 00204DE8 2D280002 */   daddu     $5, $16, $0
    /* 104DEC 00204DEC 3AE4050C */  jal        func_001790E8
    /* 104DF0 00204DF0 F491848F */   lw        $4, %gp_rel(D_00629DE4)($28)
    /* 104DF4 00204DF4 A49C80AF */  sw         $0, %gp_rel(D_0062A894)($28)
    /* 104DF8 00204DF8 40D1060C */  jal        lt_fade_status
    /* 104DFC 00204DFC 32000424 */   addiu     $4, $0, 0x32
    /* 104E00 00204E00 6004080C */  jal        _ACTWait
    /* 104E04 00204E04 3C000424 */   addiu     $4, $0, 0x3C
    /* 104E08 00204E08 00B0848F */  lw         $4, %gp_rel(D_0062BBF0)($28)
    /* 104E0C 00204E0C 04008050 */  beql       $4, $0, .L00204E20
    /* 104E10 00204E10 00B080AF */   sw        $0, %gp_rel(D_0062BBF0)($28)
    /* 104E14 00204E14 04EA050C */  jal        scpTrans
    /* 104E18 00204E18 50000524 */   addiu     $5, $0, 0x50
    /* 104E1C 00204E1C 00B080AF */  sw         $0, %gp_rel(D_0062BBF0)($28)
.align 2
  .L00204E20:
    /* 104E20 00204E20 6004080C */  jal        _ACTWait
    /* 104E24 00204E24 2D200000 */   daddu     $4, $0, $0
    /* 104E28 00204E28 6000BFDF */  ld         $31, 0x60($29)
    /* 104E2C 00204E2C 5000B2DF */  ld         $18, 0x50($29)
    /* 104E30 00204E30 4000B1DF */  ld         $17, 0x40($29)
    /* 104E34 00204E34 3000B0DF */  ld         $16, 0x30($29)
    /* 104E38 00204E38 0800E003 */  jr         $31
    /* 104E3C 00204E3C 7000BD27 */   addiu     $29, $29, 0x70
endlabel quick_save_wpfile
```
