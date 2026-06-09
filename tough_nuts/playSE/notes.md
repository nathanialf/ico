# playSE — parked

VRAM: 0x001CE4F0 (file_off 0x0CE4F0)
Asm source: asm/aug6/nonmatchings/sugipon/src/frameDependSequence/playSE.s

## Attempt at 2026-06-09

**Reason parked:** best rc12 (from 46). Indexed table search (cookbook 3.10): explicit in-loop stride keeps mult + fixes stride-const reg; int end=-1 puts -1 in a2. RESIDUAL: (1) v0/v1 mflo register-swap (mult result v1 not v0) — cookbook 3.10(B) is REG-pin-only, downstream of (2); (2) loop1 jump-threading double-test (ROM: beq exit + bne loop + dead b, single load) — every goto/break form produces it only with bnel + prologue perturbation; clean while gives single bne. 30-stall, 42 distinct hyps. Permuter-class (mflo reg + double-test+bne).

**TU:** `sugipon/src/frameDependSequence.c`

**Seed:** `tough_nuts/playSE/playSE.c`

Disassembly:

```
.align 3
nonmatching playSE, 0x12C

glabel playSE
    /* CE4F0 001CE4F0 A0FFBD27 */  addiu      $29, $29, -0x60
    /* CE4F4 001CE4F4 0C000224 */  addiu      $2, $0, 0xC
    /* CE4F8 001CE4F8 0000B0FF */  sd         $16, 0x0($29)
    /* CE4FC 001CE4FC FFFF0624 */  addiu      $6, $0, -0x1
    /* CE500 001CE500 2D808000 */  daddu      $16, $4, $0
    /* CE504 001CE504 1000B1FF */  sd         $17, 0x10($29)
    /* CE508 001CE508 18100202 */  mult       $2, $16, $2
    /* CE50C 001CE50C 5300113C */  lui        $17, %hi(D_00535F68)
    /* CE510 001CE510 5000BFFF */  sd         $31, 0x50($29)
    /* CE514 001CE514 685F2726 */  addiu      $7, $17, %lo(D_00535F68)
    /* CE518 001CE518 4000B4FF */  sd         $20, 0x40($29)
    /* CE51C 001CE51C 3000B3FF */  sd         $19, 0x30($29)
    /* CE520 001CE520 2000B2FF */  sd         $18, 0x20($29)
    /* CE524 001CE524 2110E200 */  addu       $2, $7, $2
    /* CE528 001CE528 0800438C */  lw         $3, 0x8($2)
    /* CE52C 001CE52C 0F006610 */  beq        $3, $6, .L001CE56C
    /* CE530 001CE530 A4A3858F */   lw        $5, %gp_rel(D_0062AF94)($28)
    /* CE534 001CE534 6100043C */  lui        $4, %hi(D_006117C8)
    /* CE538 001CE538 6100143C */  lui        $20, %hi(D_00611700)
    /* CE53C 001CE53C 0C000224 */  addiu      $2, $0, 0xC
.align 2
  .L001CE540:
    /* CE540 001CE540 01001026 */  addiu      $16, $16, 0x1
    /* CE544 001CE544 18180202 */  mult       $3, $16, $2
    /* CE548 001CE548 21106700 */  addu       $2, $3, $7
    /* CE54C 001CE54C 0800428C */  lw         $2, 0x8($2)
    /* CE550 001CE550 FFFF0324 */  addiu      $3, $0, -0x1
    /* CE554 001CE554 07004310 */  beq        $2, $3, .L001CE574
    /* CE558 001CE558 00000000 */   nop
    /* CE55C 001CE55C F8FF4614 */  bne        $2, $6, .L001CE540
    /* CE560 001CE560 0C000224 */   addiu     $2, $0, 0xC
    /* CE564 001CE564 03000010 */  b          .L001CE574
    /* CE568 001CE568 00000000 */   nop
.align 2
  .L001CE56C:
    /* CE56C 001CE56C 6100043C */  lui        $4, %hi(D_006117C8)
    /* CE570 001CE570 6100143C */  lui        $20, %hi(D_00611700)
.align 2
  .L001CE574:
    /* CE574 001CE574 0400A010 */  beqz       $5, .L001CE588
    /* CE578 001CE578 0C000324 */   addiu     $3, $0, 0xC
    /* CE57C 001CE57C F290060C */  jal        debug_assertMessage
    /* CE580 001CE580 C8178424 */   addiu     $4, $4, %lo(D_006117C8)
    /* CE584 001CE584 0C000324 */  addiu      $3, $0, 0xC
.align 2
  .L001CE588:
    /* CE588 001CE588 685F2426 */  addiu      $4, $17, %lo(D_00535F68)
    /* CE58C 001CE58C 18180302 */  mult       $3, $16, $3
    /* CE590 001CE590 5D00023C */  lui        $2, %hi(D_005CD670)
    /* CE594 001CE594 70D65324 */  addiu      $19, $2, %lo(D_005CD670)
    /* CE598 001CE598 3C001224 */  addiu      $18, $0, 0x3C
    /* CE59C 001CE59C 01001124 */  addiu      $17, $0, 0x1
    /* CE5A0 001CE5A0 21806400 */  addu       $16, $3, $4
    /* CE5A4 001CE5A4 00000000 */  nop
.align 2
  .L001CE5A8:
    /* CE5A8 001CE5A8 0000028E */  lw         $2, 0x0($16)
    /* CE5AC 001CE5AC FFFF053C */  lui        $5, (0xFFFFFFFF >> 16)
    /* CE5B0 001CE5B0 2D300000 */  daddu      $6, $0, $0
    /* CE5B4 001CE5B4 FFFFA534 */  ori        $5, $5, (0xFFFFFFFF & 0xFFFF)
    /* CE5B8 001CE5B8 01000724 */  addiu      $7, $0, 0x1
    /* CE5BC 001CE5BC FFFF3126 */  addiu      $17, $17, -0x1
    /* CE5C0 001CE5C0 0C004010 */  beqz       $2, .L001CE5F4
    /* CE5C4 001CE5C4 2D204000 */   daddu     $4, $2, $0
    /* CE5C8 001CE5C8 F60A050C */  jal        soundSeDefPlayWithVolumeRate
    /* CE5CC 001CE5CC 00000000 */   nop
    /* CE5D0 001CE5D0 FFFF063C */  lui        $6, (0xFFFFFFFF >> 16)
    /* CE5D4 001CE5D4 A4A3828F */  lw         $2, %gp_rel(D_0062AF94)($28)
    /* CE5D8 001CE5D8 00178426 */  addiu      $4, $20, %lo(D_00611700)
    /* CE5DC 001CE5DC 05004010 */  beqz       $2, .L001CE5F4
    /* CE5E0 001CE5E0 FFFFC634 */   ori       $6, $6, (0xFFFFFFFF & 0xFFFF)
    /* CE5E4 001CE5E4 0000058E */  lw         $5, 0x0($16)
    /* CE5E8 001CE5E8 1810B200 */  mult       $2, $5, $18
    /* CE5EC 001CE5EC F290060C */  jal        debug_assertMessage
    /* CE5F0 001CE5F0 21285300 */   addu      $5, $2, $19
.align 2
  .L001CE5F4:
    /* CE5F4 001CE5F4 ECFF2106 */  bgez       $17, .L001CE5A8
    /* CE5F8 001CE5F8 04001026 */   addiu     $16, $16, 0x4
    /* CE5FC 001CE5FC 5000BFDF */  ld         $31, 0x50($29)
    /* CE600 001CE600 4000B4DF */  ld         $20, 0x40($29)
    /* CE604 001CE604 3000B3DF */  ld         $19, 0x30($29)
    /* CE608 001CE608 2000B2DF */  ld         $18, 0x20($29)
    /* CE60C 001CE60C 1000B1DF */  ld         $17, 0x10($29)
    /* CE610 001CE610 0000B0DF */  ld         $16, 0x0($29)
    /* CE614 001CE614 0800E003 */  jr         $31
    /* CE618 001CE618 6000BD27 */   addiu     $29, $29, 0x60
endlabel playSE
    /* CE61C 001CE61C 00000000 */  nop
```
