# CallSpidersToReviveEnemy — parked

VRAM: 0x001E72E8 (file_off 0x0E72E8)
Asm source: asm/aug6/nonmatchings/sugipon/src/spider/CallSpidersToReviveEnemy.s

## Attempt at 2026-07-02

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=2). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `sugipon/src/spider.c`

**Seed:** `tough_nuts/CallSpidersToReviveEnemy/CallSpidersToReviveEnemy.c`

Disassembly:

```
.align 3
nonmatching CallSpidersToReviveEnemy, 0x168

glabel CallSpidersToReviveEnemy
    /* E72E8 001E72E8 50FFBD27 */  addiu      $29, $29, -0xB0
    /* E72EC 001E72EC 2097848F */  lw         $4, %gp_rel(D_0062A310)($28)
    /* E72F0 001E72F0 5000B1FF */  sd         $17, 0x50($29)
    /* E72F4 001E72F4 2B000724 */  addiu      $7, $0, 0x2B
    /* E72F8 001E72F8 4000B0FF */  sd         $16, 0x40($29)
    /* E72FC 001E72FC 6100113C */  lui        $17, %hi(D_00612A30)
    /* E7300 001E7300 2D80A000 */  daddu      $16, $5, $0
    /* E7304 001E7304 302A3126 */  addiu      $17, $17, %lo(D_00612A30)
    /* E7308 001E7308 8000B4FF */  sd         $20, 0x80($29)
    /* E730C 001E730C 40000524 */  addiu      $5, $0, 0x40
    /* E7310 001E7310 7000B3FF */  sd         $19, 0x70($29)
    /* E7314 001E7314 2D302002 */  daddu      $6, $17, $0
    /* E7318 001E7318 6000B2FF */  sd         $18, 0x60($29)
    /* E731C 001E731C 2D980000 */  daddu      $19, $0, $0
    /* E7320 001E7320 9000BFFF */  sd         $31, 0x90($29)
    /* E7324 001E7324 A800B5E7 */  swc1       $f21, 0xA8($29)
    /* E7328 001E7328 CEE2040C */  jal        iosFree
    /* E732C 001E732C A000B4E7 */   swc1      $f20, 0xA0($29)
    /* E7330 001E7330 30000D8E */  lw         $13, 0x30($16)
    /* E7334 001E7334 2D904000 */  daddu      $18, $2, $0
    /* E7338 001E7338 6200023C */  lui        $2, %hi(D_0061D730)
    /* E733C 001E733C 300004DE */  ld         $4, 0x30($16)
    /* E7340 001E7340 40190D00 */  sll        $3, $13, 5
    /* E7344 001E7344 30D74224 */  addiu      $2, $2, %lo(D_0061D730)
    /* E7348 001E7348 21104300 */  addu       $2, $2, $3
    /* E734C 001E734C 00000CDE */  ld         $12, 0x0($16)
    /* E7350 001E7350 1000548C */  lw         $20, 0x10($2)
    /* E7354 001E7354 2D302002 */  daddu      $6, $17, $0
    /* E7358 001E7358 08000BDE */  ld         $11, 0x8($16)
    /* E735C 001E735C 2F000724 */  addiu      $7, $0, 0x2F
    /* E7360 001E7360 10000ADE */  ld         $10, 0x10($16)
    /* E7364 001E7364 80281400 */  sll        $5, $20, 2
    /* E7368 001E7368 180009DE */  ld         $9, 0x18($16)
    /* E736C 001E736C 200002DE */  ld         $2, 0x20($16)
    /* E7370 001E7370 280003DE */  ld         $3, 0x28($16)
    /* E7374 001E7374 380008DE */  ld         $8, 0x38($16)
    /* E7378 001E7378 3000A4FF */  sd         $4, 0x30($29)
    /* E737C 001E737C 0000ACFF */  sd         $12, 0x0($29)
    /* E7380 001E7380 0800ABFF */  sd         $11, 0x8($29)
    /* E7384 001E7384 1000AAFF */  sd         $10, 0x10($29)
    /* E7388 001E7388 1800A9FF */  sd         $9, 0x18($29)
    /* E738C 001E738C 2000A2FF */  sd         $2, 0x20($29)
    /* E7390 001E7390 2800A3FF */  sd         $3, 0x28($29)
    /* E7394 001E7394 3800A8FF */  sd         $8, 0x38($29)
    /* E7398 001E7398 200054AE */  sw         $20, 0x20($18)
    /* E739C 001E739C 2097848F */  lw         $4, %gp_rel(D_0062A310)($28)
    /* E73A0 001E73A0 CEE2040C */  jal        iosFree
    /* E73A4 001E73A4 34004DAE */   sw        $13, 0x34($18)
    /* E73A8 001E73A8 FFFF0324 */  addiu      $3, $0, -0x1
    /* E73AC 001E73AC 240042AE */  sw         $2, 0x24($18)
    /* E73B0 001E73B0 380043AE */  sw         $3, 0x38($18)
    /* E73B4 001E73B4 280040AE */  sw         $0, 0x28($18)
    /* E73B8 001E73B8 000043AE */  sw         $3, 0x0($18)
    /* E73BC 001E73BC 2C0040AE */  sw         $0, 0x2C($18)
    /* E73C0 001E73C0 300040AE */  sw         $0, 0x30($18)
    /* E73C4 001E73C4 1700801A */  blez       $20, .L001E7424
    /* E73C8 001E73C8 3C0040AE */   sw        $0, 0x3C($18)
    /* E73CC 001E73CC 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* E73D0 001E73D0 00A88144 */  mtc1       $1, $f21
    /* E73D4 001E73D4 C08A94C7 */  lwc1       $f20, %gp_rel(D_006296B0)($28)
.align 2
  .L001E73D8:
    /* E73D8 001E73D8 A463040C */  jal        _GetRandom
    /* E73DC 001E73DC 00000000 */   nop
    /* E73E0 001E73E0 00000046 */  add.s      $f0, $f0, $f0
    /* E73E4 001E73E4 2D20A003 */  daddu      $4, $29, $0
    /* E73E8 001E73E8 01001546 */  sub.s      $f0, $f0, $f21
    /* E73EC 001E73EC 02001446 */  mul.s      $f0, $f0, $f20
    /* E73F0 001E73F0 26DF060C */  jal        IsActCharDead
    /* E73F4 001E73F4 1400A0E7 */   swc1      $f0, 0x14($29)
    /* E73F8 001E73F8 2400448E */  lw         $4, 0x24($18)
    /* E73FC 001E73FC 80181300 */  sll        $3, $19, 2
    /* E7400 001E7400 2D280000 */  daddu      $5, $0, $0
    /* E7404 001E7404 01007326 */  addiu      $19, $19, 0x1
    /* E7408 001E7408 21186400 */  addu       $3, $3, $4
    /* E740C 001E740C 2D204000 */  daddu      $4, $2, $0
    /* E7410 001E7410 BEDE060C */  jal        subAP1BrainMain
    /* E7414 001E7414 000062AC */   sw        $2, 0x0($3)
    /* E7418 001E7418 2A107402 */  slt        $2, $19, $20
    /* E741C 001E741C EEFF4014 */  bnez       $2, .L001E73D8
    /* E7420 001E7420 00000000 */   nop
.align 2
  .L001E7424:
    /* E7424 001E7424 2D104002 */  daddu      $2, $18, $0
    /* E7428 001E7428 9000BFDF */  ld         $31, 0x90($29)
    /* E742C 001E742C 8000B4DF */  ld         $20, 0x80($29)
    /* E7430 001E7430 7000B3DF */  ld         $19, 0x70($29)
    /* E7434 001E7434 6000B2DF */  ld         $18, 0x60($29)
    /* E7438 001E7438 5000B1DF */  ld         $17, 0x50($29)
    /* E743C 001E743C 4000B0DF */  ld         $16, 0x40($29)
    /* E7440 001E7440 A800B5C7 */  lwc1       $f21, 0xA8($29)
    /* E7444 001E7444 A000B4C7 */  lwc1       $f20, 0xA0($29)
    /* E7448 001E7448 0800E003 */  jr         $31
    /* E744C 001E744C B000BD27 */   addiu     $29, $29, 0xB0
endlabel CallSpidersToReviveEnemy
```
