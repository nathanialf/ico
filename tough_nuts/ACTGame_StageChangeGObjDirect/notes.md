# ACTCheckCollis_WELL — parked

VRAM: 0x001493D8 (file_off 0x0493D8)
Asm source: asm/aug6/nonmatchings/fumi/src/act-game/ACTCheckCollis_WELL.s

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=27). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/act-game.c`

**Seed:** `tough_nuts/ACTCheckCollis_WELL/ACTCheckCollis_WELL.c`

Disassembly:

```
.align 3
nonmatching ACTCheckCollis_WELL, 0x104

glabel ACTCheckCollis_WELL
    /* 493D8 001493D8 C0FEBD27 */  addiu      $29, $29, -0x140
    /* 493DC 001493DC 0001B4FF */  sd         $20, 0x100($29)
    /* 493E0 001493E0 F000B3FF */  sd         $19, 0xF0($29)
    /* 493E4 001493E4 2DA0A000 */  daddu      $20, $5, $0
    /* 493E8 001493E8 D000B1FF */  sd         $17, 0xD0($29)
    /* 493EC 001493EC 2D988000 */  daddu      $19, $4, $0
    /* 493F0 001493F0 E000B2FF */  sd         $18, 0xE0($29)
    /* 493F4 001493F4 2D88C000 */  daddu      $17, $6, $0
    /* 493F8 001493F8 3001B4E7 */  swc1       $f20, 0x130($29)
    /* 493FC 001493FC 2D90E000 */  daddu      $18, $7, $0
    /* 49400 00149400 1001B5FF */  sd         $21, 0x110($29)
    /* 49404 00149404 06650046 */  mov.s      $f20, $f12
    /* 49408 00149408 2001BFFF */  sd         $31, 0x120($29)
    /* 4940C 0014940C 2D20A003 */  daddu      $4, $29, $0
    /* 49410 00149410 C000B0FF */  sd         $16, 0xC0($29)
    /* 49414 00149414 2D280000 */  daddu      $5, $0, $0
    /* 49418 00149418 C0000624 */  addiu      $6, $0, 0xC0
    /* 4941C 0014941C 5A81090C */  jal        memset
    /* 49420 00149420 01001524 */   addiu     $21, $0, 0x1
    /* 49424 00149424 03002012 */  beqz       $17, .L00149434
    /* 49428 00149428 2D800000 */   daddu     $16, $0, $0
    /* 4942C 0014942C 5C01228E */  lw         $2, 0x15C($17)
    /* 49430 00149430 7400508C */  lw         $16, 0x74($2)
.align 2
  .L00149434:
    /* 49434 00149434 7000B4E7 */  swc1       $f20, 0x70($29)
    /* 49438 00149438 2D286002 */  daddu      $5, $19, $0
    /* 4943C 0014943C 689980AF */  sw         $0, %gp_rel(D_0062A558)($28)
    /* 49440 00149440 2000090C */  jal        sceVu0CopyVector
    /* 49444 00149444 2D20A003 */   daddu     $4, $29, $0
    /* 49448 00149448 2D288002 */  daddu      $5, $20, $0
    /* 4944C 0014944C 2000090C */  jal        sceVu0CopyVector
    /* 49450 00149450 1000A427 */   addiu     $4, $29, 0x10
    /* 49454 00149454 03000012 */  beqz       $16, .L00149464
    /* 49458 00149458 00000000 */   nop
    /* 4945C 0014945C 5C01228E */  lw         $2, 0x15C($17)
    /* 49460 00149460 740040AC */  sw         $0, 0x74($2)
.align 2
  .L00149464:
    /* 49464 00149464 DA98050C */  jal        ChangeFieldCollisionDebugMode
    /* 49468 00149468 2D20A003 */   daddu     $4, $29, $0
    /* 4946C 0014946C 9400A28F */  lw         $2, 0x94($29)
    /* 49470 00149470 03004014 */  bnez       $2, .L00149480
    /* 49474 00149474 8C00A28F */   lw        $2, 0x8C($29)
    /* 49478 00149478 02000010 */  b          .L00149484
    /* 4947C 0014947C 2DA80000 */   daddu     $21, $0, $0
.align 2
  .L00149480:
    /* 49480 00149480 689982AF */  sw         $2, %gp_rel(D_0062A558)($28)
.align 2
  .L00149484:
    /* 49484 00149484 03000012 */  beqz       $16, .L00149494
    /* 49488 00149488 01000224 */   addiu     $2, $0, 0x1
    /* 4948C 0014948C 5C01238E */  lw         $3, 0x15C($17)
    /* 49490 00149490 740062AC */  sw         $2, 0x74($3)
.align 2
  .L00149494:
    /* 49494 00149494 06004012 */  beqz       $18, .L001494B0
    /* 49498 00149498 2000A0C7 */   lwc1      $f0, 0x20($29)
    /* 4949C 0014949C 2400A2C7 */  lwc1       $f2, 0x24($29)
    /* 494A0 001494A0 2800A1C7 */  lwc1       $f1, 0x28($29)
    /* 494A4 001494A4 000040E6 */  swc1       $f0, 0x0($18)
    /* 494A8 001494A8 080041E6 */  swc1       $f1, 0x8($18)
    /* 494AC 001494AC 040042E6 */  swc1       $f2, 0x4($18)
.align 2
  .L001494B0:
    /* 494B0 001494B0 2D10A002 */  daddu      $2, $21, $0
    /* 494B4 001494B4 2001BFDF */  ld         $31, 0x120($29)
    /* 494B8 001494B8 1001B5DF */  ld         $21, 0x110($29)
    /* 494BC 001494BC 0001B4DF */  ld         $20, 0x100($29)
    /* 494C0 001494C0 F000B3DF */  ld         $19, 0xF0($29)
    /* 494C4 001494C4 E000B2DF */  ld         $18, 0xE0($29)
    /* 494C8 001494C8 D000B1DF */  ld         $17, 0xD0($29)
    /* 494CC 001494CC C000B0DF */  ld         $16, 0xC0($29)
    /* 494D0 001494D0 3001B4C7 */  lwc1       $f20, 0x130($29)
    /* 494D4 001494D4 0800E003 */  jr         $31
    /* 494D8 001494D8 4001BD27 */   addiu     $29, $29, 0x140
endlabel ACTCheckCollis_WELL
    /* 494DC 001494DC 00000000 */  nop
```
