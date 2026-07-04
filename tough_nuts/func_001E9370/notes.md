# func_001E9370 — parked

VRAM: 0x001E9370 (file_off 0x0E9370)
Asm source: asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager/func_001E9370.s

## Attempt at 2026-07-04

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=44). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `sugipon/src/stageMultiBgaManager.c`

**Seed:** `tough_nuts/func_001E9370/func_001E9370.c`

Disassembly:

```
.align 3
nonmatching func_001E9370, 0x178

glabel func_001E9370
    /* E9370 001E9370 80FFBD27 */  addiu      $29, $29, -0x80
    /* E9374 001E9374 7000033C */  lui        $3, %hi(D_00706D78)
    /* E9378 001E9378 6000B2FF */  sd         $18, 0x60($29)
    /* E937C 001E937C 786D6A24 */  addiu      $10, $3, %lo(D_00706D78)
    /* E9380 001E9380 5000B1FF */  sd         $17, 0x50($29)
    /* E9384 001E9384 FFFF0424 */  addiu      $4, $0, -0x1
    /* E9388 001E9388 4000B0FF */  sd         $16, 0x40($29)
    /* E938C 001E938C 4C00123C */  lui        $18, %hi(D_004C2220)
    /* E9390 001E9390 7000BFFF */  sd         $31, 0x70($29)
    /* E9394 001E9394 1000B127 */  addiu      $17, $29, 0x10
    /* E9398 001E9398 6C93858F */  lw         $5, %gp_rel(D_00629F5C)($28)
    /* E939C 001E939C 2000B027 */  addiu      $16, $29, 0x20
    /* E93A0 001E93A0 0C00498D */  lw         $9, 0xC($10)
    /* E93A4 001E93A4 0400488D */  lw         $8, 0x4($10)
    /* E93A8 001E93A8 2A208500 */  slt        $4, $4, $5
    /* E93AC 001E93AC 08004B8D */  lw         $11, 0x8($10)
    /* E93B0 001E93B0 7093868F */  lw         $6, %gp_rel(D_00629F60)($28)
    /* E93B4 001E93B4 10000825 */  addiu      $8, $8, 0x10
    /* E93B8 001E93B8 0000A2AF */  sw         $2, 0x0($29)
    /* E93BC 001E93BC 786D678C */  lw         $7, %lo(D_00706D78)($3)
    /* E93C0 001E93C0 3F00A224 */  addiu      $2, $5, 0x3F
    /* E93C4 001E93C4 00190500 */  sll        $3, $5, 4
    /* E93C8 001E93C8 00310600 */  sll        $6, $6, 4
    /* E93CC 001E93CC 2130C900 */  addu       $6, $6, $9
    /* E93D0 001E93D0 0B10A400 */  movn       $2, $5, $4
    /* E93D4 001E93D4 21186B00 */  addu       $3, $3, $11
    /* E93D8 001E93D8 1000E724 */  addiu      $7, $7, 0x10
    /* E93DC 001E93DC 2000A7AF */  sw         $7, 0x20($29)
    /* E93E0 001E93E0 2700043C */  lui        $4, %hi(D_00271240)
    /* E93E4 001E93E4 2400A8AF */  sw         $8, 0x24($29)
    /* E93E8 001E93E8 20224926 */  addiu      $9, $18, %lo(D_004C2220)
    /* E93EC 001E93EC 2C00A6AF */  sw         $6, 0x2C($29)
    /* E93F0 001E93F0 00070824 */  addiu      $8, $0, 0x700
    /* E93F4 001E93F4 2800A3AF */  sw         $3, 0x28($29)
    /* E93F8 001E93F8 00080724 */  addiu      $7, $0, 0x800
    /* E93FC 001E93FC 4012868C */  lw         $6, %lo(D_00271240)($4)
    /* E9400 001E9400 83110200 */  sra        $2, $2, 6
    /* E9404 001E9404 1400458D */  lw         $5, 0x14($10)
    /* E9408 001E9408 1000438D */  lw         $3, 0x10($10)
    /* E940C 001E940C 0A380601 */  movz       $7, $8, $6
    /* E9410 001E9410 0400248D */  lw         $4, 0x4($9)
    /* E9414 001E9414 00FCA524 */  addiu      $5, $5, -0x400
    /* E9418 001E9418 2700A66B */  ldl        $6, 0x27($29)
    /* E941C 001E941C 2000A66F */  ldr        $6, 0x20($29)
    /* E9420 001E9420 2F00A86B */  ldl        $8, 0x2F($29)
    /* E9424 001E9424 2800A86F */  ldr        $8, 0x28($29)
    /* E9428 001E9428 1700A6B3 */  sdl        $6, 0x17($29)
    /* E942C 001E942C 1000A6B7 */  sdr        $6, 0x10($29)
    /* E9430 001E9430 1F00A8B3 */  sdl        $8, 0x1F($29)
    /* E9434 001E9434 1800A8B7 */  sdr        $8, 0x18($29)
    /* E9438 001E9438 B8130200 */  dsll       $2, $2, 14
    /* E943C 001E943C 3400A5AF */  sw         $5, 0x34($29)
    /* E9440 001E9440 25208200 */  or         $4, $4, $2
    /* E9444 001E9444 00F86324 */  addiu      $3, $3, -0x800
    /* E9448 001E9448 00100624 */  addiu      $6, $0, 0x1000
    /* E944C 001E944C 80CC0534 */  ori        $5, $0, 0xCC80
    /* E9450 001E9450 F82C0500 */  dsll       $5, $5, 19
    /* E9454 001E9454 3000A3AF */  sw         $3, 0x30($29)
    /* E9458 001E9458 3800A6AF */  sw         $6, 0x38($29)
    /* E945C 001E945C 25288500 */  or         $5, $4, $5
    /* E9460 001E9460 3C00A7AF */  sw         $7, 0x3C($29)
    /* E9464 001E9464 3700A26B */  ldl        $2, 0x37($29)
    /* E9468 001E9468 3000A26F */  ldr        $2, 0x30($29)
    /* E946C 001E946C 3F00A36B */  ldl        $3, 0x3F($29)
    /* E9470 001E9470 3800A36F */  ldr        $3, 0x38($29)
    /* E9474 001E9474 2700A2B3 */  sdl        $2, 0x27($29)
    /* E9478 001E9478 2000A2B7 */  sdr        $2, 0x20($29)
    /* E947C 001E947C 2F00A3B3 */  sdl        $3, 0x2F($29)
    /* E9480 001E9480 2800A3B7 */  sdr        $3, 0x28($29)
    /* E9484 001E9484 2E47040C */  jal        gif_SpriteOrg
    /* E9488 001E9488 06000424 */   addiu     $4, $0, 0x6
    /* E948C 001E948C 2022448E */  lw         $4, %lo(D_004C2220)($18)
    /* E9490 001E9490 2D480000 */  daddu      $9, $0, $0
    /* E9494 001E9494 2D280000 */  daddu      $5, $0, $0
    /* E9498 001E9498 00010624 */  addiu      $6, $0, 0x100
    /* E949C 001E949C 80000724 */  addiu      $7, $0, 0x80
    /* E94A0 001E94A0 F643040C */  jal        gif_MakeSprite
    /* E94A4 001E94A4 2D400000 */   daddu     $8, $0, $0
    /* E94A8 001E94A8 01000424 */  addiu      $4, $0, 0x1
    /* E94AC 001E94AC 05000524 */  addiu      $5, $0, 0x5
    /* E94B0 001E94B0 D248040C */  jal        gsb_SetFrame
    /* E94B4 001E94B4 2D300000 */   daddu     $6, $0, $0
    /* E94B8 001E94B8 2D200002 */  daddu      $4, $16, $0
    /* E94BC 001E94BC 2D302002 */  daddu      $6, $17, $0
    /* E94C0 001E94C0 2D280000 */  daddu      $5, $0, $0
    /* E94C4 001E94C4 58AD8727 */  addiu      $7, $28, %gp_rel(D_0062B948)
    /* E94C8 001E94C8 A443040C */  jal        gif_MakeLine2DOffset
    /* E94CC 001E94CC 01000824 */   addiu     $8, $0, 0x1
    /* E94D0 001E94D0 7000BFDF */  ld         $31, 0x70($29)
    /* E94D4 001E94D4 6000B2DF */  ld         $18, 0x60($29)
    /* E94D8 001E94D8 5000B1DF */  ld         $17, 0x50($29)
    /* E94DC 001E94DC 4000B0DF */  ld         $16, 0x40($29)
    /* E94E0 001E94E0 0800E003 */  jr         $31
    /* E94E4 001E94E4 8000BD27 */   addiu     $29, $29, 0x80
endlabel func_001E9370
```
