# WayGroup_next — parked

VRAM: 0x00203450 (file_off 0x103450)
Asm source: asm/aug6/nonmatchings/fumi/src/way_llf/WayGroup_next.s

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=5). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/way_llf.c`

**Seed:** `tough_nuts/WayGroup_next/WayGroup_next.c`

Disassembly:

```
.align 3
nonmatching WayGroup_next, 0x100

glabel WayGroup_next
    /* 103450 00203450 8CAF848F */  lw         $4, %gp_rel(D_0062BB7C)($28)
    /* 103454 00203454 34000524 */  addiu      $5, $0, 0x34
    /* 103458 00203458 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 10345C 0020345C 4C00023C */  lui        $2, %hi(D_004C6FF0)
    /* 103460 00203460 18208500 */  mult       $4, $4, $5
    /* 103464 00203464 94A3838F */  lw         $3, %gp_rel(D_0062AF84)($28)
    /* 103468 00203468 0000B0FF */  sd         $16, 0x0($29)
    /* 10346C 0020346C F06F4224 */  addiu      $2, $2, %lo(D_004C6FF0)
    /* 103470 00203470 1000BFFF */  sd         $31, 0x10($29)
    /* 103474 00203474 01006330 */  andi       $3, $3, 0x1
    /* 103478 00203478 12006010 */  beqz       $3, .L002034C4
    /* 10347C 0020347C 21808200 */   addu      $16, $4, $2
    /* 103480 00203480 6100073C */  lui        $7, %hi(D_006141A8)
    /* 103484 00203484 12000424 */  addiu      $4, $0, 0x12
    /* 103488 00203488 A841E724 */  addiu      $7, $7, %lo(D_006141A8)
    /* 10348C 0020348C 00FF063C */  lui        $6, (0xFF000000 >> 16)
    /* 103490 00203490 F48F060C */  jal        traceLine
    /* 103494 00203494 36000524 */   addiu     $5, $0, 0x36
    /* 103498 00203498 94A3828F */  lw         $2, %gp_rel(D_0062AF84)($28)
    /* 10349C 0020349C 01004230 */  andi       $2, $2, 0x1
    /* 1034A0 002034A0 08004010 */  beqz       $2, .L002034C4
    /* 1034A4 002034A4 6300073C */   lui       $7, %hi(D_0062DA08)
    /* 1034A8 002034A8 80FF063C */  lui        $6, (0xFF808000 >> 16)
    /* 1034AC 002034AC 1000088E */  lw         $8, 0x10($16)
    /* 1034B0 002034B0 08DAE724 */  addiu      $7, $7, %lo(D_0062DA08)
    /* 1034B4 002034B4 1A000424 */  addiu      $4, $0, 0x1A
    /* 1034B8 002034B8 42000524 */  addiu      $5, $0, 0x42
    /* 1034BC 002034BC F48F060C */  jal        traceLine
    /* 1034C0 002034C0 0080C634 */   ori       $6, $6, (0xFF808000 & 0xFFFF)
.align 2
  .L002034C4:
    /* 1034C4 002034C4 7100023C */  lui        $2, %hi(D_0070BBFC)
    /* 1034C8 002034C8 FCBB428C */  lw         $2, %lo(D_0070BBFC)($2)
    /* 1034CC 002034CC 20004330 */  andi       $3, $2, 0x20
    /* 1034D0 002034D0 17006010 */  beqz       $3, .L00203530
    /* 1034D4 002034D4 4D00043C */   lui       $4, %hi(D_004CB2B0)
    /* 1034D8 002034D8 7042013C */  lui        $1, (0x42700000 >> 16)
    /* 1034DC 002034DC 00608144 */  mtc1       $1, $f12
    /* 1034E0 002034E0 9EE0050C */  jal        visible_waypoint_of_all
    /* 1034E4 002034E4 B0B28424 */   addiu     $4, $4, %lo(D_004CB2B0)
    /* 1034E8 002034E8 15004050 */  beql       $2, $0, .L00203540
    /* 1034EC 002034EC 2D100000 */   daddu     $2, $0, $0
    /* 1034F0 002034F0 0400448C */  lw         $4, 0x4($2)
    /* 1034F4 002034F4 11008004 */  bltz       $4, .L0020353C
    /* 1034F8 002034F8 90AF84AF */   sw        $4, %gp_rel(D_0062BB80)($28)
    /* 1034FC 002034FC C40A080C */  jal        NearestEnemyFromGirl
    /* 103500 00203500 00000000 */   nop
    /* 103504 00203504 1000038E */  lw         $3, 0x10($16)
    /* 103508 00203508 04006014 */  bnez       $3, .L0020351C
    /* 10350C 0020350C 6100043C */   lui       $4, %hi(D_006141B8)
    /* 103510 00203510 400A080C */  jal        func_00202900
    /* 103514 00203514 8CAF848F */   lw        $4, %gp_rel(D_0062BB7C)($28)
    /* 103518 00203518 6100043C */  lui        $4, %hi(D_006141B8)
.align 2
  .L0020351C:
    /* 10351C 0020351C 90AF858F */  lw         $5, %gp_rel(D_0062BB80)($28)
    /* 103520 00203520 F290060C */  jal        debug_assertMessage
    /* 103524 00203524 B8418424 */   addiu     $4, $4, %lo(D_006141B8)
    /* 103528 00203528 05000010 */  b          .L00203540
    /* 10352C 0020352C 2D100000 */   daddu     $2, $0, $0
.align 2
  .L00203530:
    /* 103530 00203530 40004330 */  andi       $3, $2, 0x40
    /* 103534 00203534 02006014 */  bnez       $3, .L00203540
    /* 103538 00203538 FFFF0224 */   addiu     $2, $0, -0x1
.align 2
  .L0020353C:
    /* 10353C 0020353C 2D100000 */  daddu      $2, $0, $0
.align 2
  .L00203540:
    /* 103540 00203540 1000BFDF */  ld         $31, 0x10($29)
    /* 103544 00203544 0000B0DF */  ld         $16, 0x0($29)
    /* 103548 00203548 0800E003 */  jr         $31
    /* 10354C 0020354C 2000BD27 */   addiu     $29, $29, 0x20
endlabel WayGroup_next
```
