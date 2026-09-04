# soundInit — parked

VRAM: 0x0013FC18 (file_off 0x03FC18)
Asm source: asm/aug6/nonmatchings/fumi/sound/s_init/soundInit.s

## Attempt at 2026-06-26

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=3). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/sound/s_init.c`

**Seed:** `tough_nuts/soundInit/soundInit.c`

Disassembly:

```
.align 3
nonmatching soundInit, 0x150

glabel soundInit
    /* 3FC18 0013FC18 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 3FC1C 0013FC1C 5500043C */  lui        $4, %hi(D_00551FA0)
    /* 3FC20 0013FC20 0000BFFF */  sd         $31, 0x0($29)
    /* 3FC24 0013FC24 F290060C */  jal        debug_StdPrintfDummy
    /* 3FC28 0013FC28 A01F8424 */   addiu     $4, $4, %lo(D_00551FA0)
    /* 3FC2C 0013FC2C 5262090C */  jal        func_00258948
    /* 3FC30 0013FC30 00000000 */   nop
    /* 3FC34 0013FC34 7096838F */  lw         $3, %gp_rel(D_0062A260)($28)
    /* 3FC38 0013FC38 01000224 */  addiu      $2, $0, 0x1
    /* 3FC3C 0013FC3C 05006214 */  bne        $3, $2, .L0013FC54
    /* 3FC40 0013FC40 00000000 */   nop
    /* 3FC44 0013FC44 7E62090C */  jal        SgSetDigitalOutputMode
    /* 3FC48 0013FC48 80000424 */   addiu     $4, $0, 0x80
    /* 3FC4C 0013FC4C 04000010 */  b          .L0013FC60
    /* 3FC50 0013FC50 5500043C */   lui       $4, %hi(D_00551FB0)
.align 2
  .L0013FC54:
    /* 3FC54 0013FC54 7E62090C */  jal        SgSetDigitalOutputMode
    /* 3FC58 0013FC58 80080424 */   addiu     $4, $0, 0x880
    /* 3FC5C 0013FC5C 5500043C */  lui        $4, %hi(D_00551FB0)
.align 2
  .L0013FC60:
    /* 3FC60 0013FC60 F290060C */  jal        debug_StdPrintfDummy
    /* 3FC64 0013FC64 B01F8424 */   addiu     $4, $4, %lo(D_00551FB0)
    /* 3FC68 0013FC68 3864090C */  jal        SgSetTickMode
    /* 3FC6C 0013FC6C 3C000424 */   addiu     $4, $0, 0x3C
    /* 3FC70 0013FC70 1F00053C */  lui        $5, (0x1FFFFF >> 16)
    /* 3FC74 0013FC74 2D200000 */  daddu      $4, $0, $0
    /* 3FC78 0013FC78 1064090C */  jal        SgSetReverbEndAddr
    /* 3FC7C 0013FC7C FFFFA534 */   ori       $5, $5, (0x1FFFFF & 0xFFFF)
    /* 3FC80 0013FC80 1D00053C */  lui        $5, (0x1DFFFF >> 16)
    /* 3FC84 0013FC84 01000424 */  addiu      $4, $0, 0x1
    /* 3FC88 0013FC88 1064090C */  jal        SgSetReverbEndAddr
    /* 3FC8C 0013FC8C FFFFA534 */   ori       $5, $5, (0x1DFFFF & 0xFFFF)
    /* 3FC90 0013FC90 2D200000 */  daddu      $4, $0, $0
    /* 3FC94 0013FC94 1664090C */  jal        SgSetReverbType
    /* 3FC98 0013FC98 04000524 */   addiu     $5, $0, 0x4
    /* 3FC9C 0013FC9C 2D200000 */  daddu      $4, $0, $0
    /* 3FCA0 0013FCA0 CC0C0524 */  addiu      $5, $0, 0xCCC
    /* 3FCA4 0013FCA4 1C64090C */  jal        SgSetReverbDepth
    /* 3FCA8 0013FCA8 CC0C0624 */   addiu     $6, $0, 0xCCC
    /* 3FCAC 0013FCAC 01000424 */  addiu      $4, $0, 0x1
    /* 3FCB0 0013FCB0 1664090C */  jal        SgSetReverbType
    /* 3FCB4 0013FCB4 04000524 */   addiu     $5, $0, 0x4
    /* 3FCB8 0013FCB8 2D200000 */  daddu      $4, $0, $0
    /* 3FCBC 0013FCBC CC0C0524 */  addiu      $5, $0, 0xCCC
    /* 3FCC0 0013FCC0 1C64090C */  jal        SgSetReverbDepth
    /* 3FCC4 0013FCC4 CC0C0624 */   addiu     $6, $0, 0xCCC
    /* 3FCC8 0013FCC8 2D200000 */  daddu      $4, $0, $0
    /* 3FCCC 0013FCCC 2D280000 */  daddu      $5, $0, $0
    /* 3FCD0 0013FCD0 8264090C */  jal        SgSetMasterVol
    /* 3FCD4 0013FCD4 2D300000 */   daddu     $6, $0, $0
    /* 3FCD8 0013FCD8 01000424 */  addiu      $4, $0, 0x1
    /* 3FCDC 0013FCDC 2D280000 */  daddu      $5, $0, $0
    /* 3FCE0 0013FCE0 8264090C */  jal        SgSetMasterVol
    /* 3FCE4 0013FCE4 2D300000 */   daddu     $6, $0, $0
    /* 3FCE8 0013FCE8 6A00023C */  lui        $2, %hi(D_006A3070)
    /* 3FCEC 0013FCEC 0F000324 */  addiu      $3, $0, 0xF
    /* 3FCF0 0013FCF0 70304224 */  addiu      $2, $2, %lo(D_006A3070)
    /* 3FCF4 0013FCF4 D0024224 */  addiu      $2, $2, 0x2D0
.align 2
  .L0013FCF8:
    /* 3FCF8 0013FCF8 000040AC */  sw         $0, 0x0($2)
    /* 3FCFC 0013FCFC FFFF6324 */  addiu      $3, $3, -0x1
    /* 3FD00 0013FD00 D0FF4224 */  addiu      $2, $2, -0x30
    /* 3FD04 0013FD04 00000000 */  nop
    /* 3FD08 0013FD08 00000000 */  nop
    /* 3FD0C 0013FD0C FAFF6104 */  bgez       $3, .L0013FCF8
    /* 3FD10 0013FD10 00000000 */   nop
    /* 3FD14 0013FD14 6A00023C */  lui        $2, %hi(D_006A3370)
    /* 3FD18 0013FD18 D8B380FF */  sd         $0, %gp_rel(D_0062BFC8)($28)
    /* 3FD1C 0013FD1C 70334224 */  addiu      $2, $2, %lo(D_006A3370)
    /* 3FD20 0013FD20 E0B380FF */  sd         $0, %gp_rel(D_0062BFD0)($28)
    /* 3FD24 0013FD24 F00B4224 */  addiu      $2, $2, 0xBF0
    /* 3FD28 0013FD28 2F000324 */  addiu      $3, $0, 0x2F
    /* 3FD2C 0013FD2C 00000000 */  nop
.align 2
  .L0013FD30:
    /* 3FD30 0013FD30 000040AC */  sw         $0, 0x0($2)
    /* 3FD34 0013FD34 FFFF6324 */  addiu      $3, $3, -0x1
    /* 3FD38 0013FD38 C0FF4224 */  addiu      $2, $2, -0x40
    /* 3FD3C 0013FD3C 00000000 */  nop
    /* 3FD40 0013FD40 00000000 */  nop
    /* 3FD44 0013FD44 FAFF6104 */  bgez       $3, .L0013FD30
    /* 3FD48 0013FD48 00000000 */   nop
    /* 3FD4C 0013FD4C 62E4070C */  jal        AdpcmPlay
    /* 3FD50 0013FD50 00000000 */   nop
    /* 3FD54 0013FD54 0000BFDF */  ld         $31, 0x0($29)
    /* 3FD58 0013FD58 2D100000 */  daddu      $2, $0, $0
    /* 3FD5C 0013FD5C 089980AF */  sw         $0, %gp_rel(D_0062A4F8)($28)
    /* 3FD60 0013FD60 0800E003 */  jr         $31
    /* 3FD64 0013FD64 1000BD27 */   addiu     $29, $29, 0x10
endlabel soundInit
```
