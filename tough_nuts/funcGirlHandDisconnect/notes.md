# funcGirlHandDisconnect — parked

VRAM: 0x00168420 (file_off 0x068420)
Asm source: asm/aug6/nonmatchings/fumi/src/girl_act/funcGirlHandDisconnect.s

## Attempt at 2026-07-07

**Reason parked:** structure byte-perfect rc10; residual is single global regalloc tie: rv coalesces to $4 not ROM's $5, tail block otherwise isomorphic. 15 distinct shapes (add-order, accumulate, pointer-index, base-var/early-base, ternary, unsigned, store-reorder, inverted-branch) all fold to rc10 or regress; none below 10. Permuter-class.

**TU:** `fumi/src/girl_act.c`

**Seed:** `tough_nuts/funcGirlHandDisconnect/funcGirlHandDisconnect.c`

Disassembly:

```
.align 3
nonmatching funcGirlHandDisconnect, 0x88

glabel funcGirlHandDisconnect
    /* 68420 00168420 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 68424 00168424 1000B1FF */  sd         $17, 0x10($29)
    /* 68428 00168428 0000B0FF */  sd         $16, 0x0($29)
    /* 6842C 0016842C 2D88A000 */  daddu      $17, $5, $0
    /* 68430 00168430 2D808000 */  daddu      $16, $4, $0
    /* 68434 00168434 2000BFFF */  sd         $31, 0x20($29)
    /* 68438 00168438 2D202002 */  daddu      $4, $17, $0
    /* 6843C 0016843C 9627040C */  jal        DebugDisp1CollisionWithColor
    /* 68440 00168440 23000524 */   addiu     $5, $0, 0x23
    /* 68444 00168444 2D284000 */  daddu      $5, $2, $0
    /* 68448 00168448 0C00238E */  lw         $3, 0xC($17)
    /* 6844C 0016844C 04000224 */  addiu      $2, $0, 0x4
    /* 68450 00168450 05006214 */  bne        $3, $2, .L00168468
    /* 68454 00168454 000000AE */   sw        $0, 0x0($16)
    /* 68458 00168458 80BF013C */  lui        $1, (0xBF800000 >> 16)
    /* 6845C 0016845C 00008144 */  mtc1       $1, $f0
    /* 68460 00168460 04000010 */  b          .L00168474
    /* 68464 00168464 040000E6 */   swc1      $f0, 0x4($16)
.align 2
  .L00168468:
    /* 68468 00168468 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* 6846C 0016846C 00008144 */  mtc1       $1, $f0
    /* 68470 00168470 040000E6 */  swc1       $f0, 0x4($16)
.align 2
  .L00168474:
    /* 68474 00168474 080000AE */  sw         $0, 0x8($16)
    /* 68478 00168478 0C0000AE */  sw         $0, 0xC($16)
    /* 6847C 0016847C 2D200002 */  daddu      $4, $16, $0
    /* 68480 00168480 80290500 */  sll        $5, $5, 6
    /* 68484 00168484 2000BFDF */  ld         $31, 0x20($29)
    /* 68488 00168488 5C01238E */  lw         $3, 0x15C($17)
    /* 6848C 0016848C 2D308000 */  daddu      $6, $4, $0
    /* 68490 00168490 1000B1DF */  ld         $17, 0x10($29)
    /* 68494 00168494 0C00628C */  lw         $2, 0xC($3)
    /* 68498 00168498 0000B0DF */  ld         $16, 0x0($29)
    /* 6849C 0016849C 21284500 */  addu       $5, $2, $5
    /* 684A0 001684A0 76FF0808 */  j          func_0023FDD8
    /* 684A4 001684A4 3000BD27 */   addiu     $29, $29, 0x30
endlabel funcGirlHandDisconnect
```
