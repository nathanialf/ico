# waypoint_with_range — parked

VRAM: 0x00177F90 (file_off 0x077F90)
Asm source: asm/aug6/nonmatchings/fumi/src/way_util/waypoint_with_range.s

## Attempt at 2026-07-06

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=8). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/way_util.c`

**Seed:** `tough_nuts/waypoint_with_range/waypoint_with_range.c`

Disassembly:

```
.align 3
nonmatching waypoint_with_range, 0xAC

glabel waypoint_with_range
    /* 77F90 00177F90 34000324 */  addiu      $3, $0, 0x34
    /* 77F94 00177F94 B0FFBD27 */  addiu      $29, $29, -0x50
    /* 77F98 00177F98 1828A300 */  mult       $5, $5, $3
    /* 77F9C 00177F9C 4C00023C */  lui        $2, %hi(D_004C6FF0)
    /* 77FA0 00177FA0 2000B2FF */  sd         $18, 0x20($29)
    /* 77FA4 00177FA4 F06F4224 */  addiu      $2, $2, %lo(D_004C6FF0)
    /* 77FA8 00177FA8 1000B1FF */  sd         $17, 0x10($29)
    /* 77FAC 00177FAC 2D908000 */  daddu      $18, $4, $0
    /* 77FB0 00177FB0 4000B4E7 */  swc1       $f20, 0x40($29)
    /* 77FB4 00177FB4 3000BFFF */  sd         $31, 0x30($29)
    /* 77FB8 00177FB8 2128A200 */  addu       $5, $5, $2
    /* 77FBC 00177FBC 0000B0FF */  sd         $16, 0x0($29)
    /* 77FC0 00177FC0 0800B08C */  lw         $16, 0x8($5)
    /* 77FC4 00177FC4 448594C7 */  lwc1       $f20, %gp_rel(D_00629134)($28)
    /* 77FC8 00177FC8 0C00058E */  lw         $5, 0xC($16)
    /* 77FCC 00177FCC 1300A010 */  beqz       $5, .L0017801C
    /* 77FD0 00177FD0 2D880000 */   daddu     $17, $0, $0
    /* 77FD4 00177FD4 1200B010 */  beq        $5, $16, .L00178020
    /* 77FD8 00177FD8 2D102002 */   daddu     $2, $17, $0
    /* 77FDC 00177FDC 1000A524 */  addiu      $5, $5, 0x10
.align 2
  .L00177FE0:
    /* 77FE0 00177FE0 10000426 */  addiu      $4, $16, 0x10
    /* 77FE4 00177FE4 A4A0050C */  jal        fzMagnitudeByLineSeg
    /* 77FE8 00177FE8 2D304002 */   daddu     $6, $18, $0
    /* 77FEC 00177FEC 34001446 */  c.lt.s     $f0, $f20
    /* 77FF0 00177FF0 00000000 */  nop
    /* 77FF4 00177FF4 04000245 */  bc1fl      .L00178008
    /* 77FF8 00177FF8 0C00108E */   lw        $16, 0xC($16)
    /* 77FFC 00177FFC 06050046 */  mov.s      $f20, $f0
    /* 78000 00178000 2D880002 */  daddu      $17, $16, $0
    /* 78004 00178004 0C00108E */  lw         $16, 0xC($16)
.align 2
  .L00178008:
    /* 78008 00178008 0C00028E */  lw         $2, 0xC($16)
    /* 7800C 0017800C 03004010 */  beqz       $2, .L0017801C
    /* 78010 00178010 2D284000 */   daddu     $5, $2, $0
    /* 78014 00178014 F2FF5054 */  bnel       $2, $16, .L00177FE0
    /* 78018 00178018 1000A524 */   addiu     $5, $5, 0x10
.align 2
  .L0017801C:
    /* 7801C 0017801C 2D102002 */  daddu      $2, $17, $0
.align 2
  .L00178020:
    /* 78020 00178020 3000BFDF */  ld         $31, 0x30($29)
    /* 78024 00178024 2000B2DF */  ld         $18, 0x20($29)
    /* 78028 00178028 1000B1DF */  ld         $17, 0x10($29)
    /* 7802C 0017802C 0000B0DF */  ld         $16, 0x0($29)
    /* 78030 00178030 4000B4C7 */  lwc1       $f20, 0x40($29)
    /* 78034 00178034 0800E003 */  jr         $31
    /* 78038 00178038 5000BD27 */   addiu     $29, $29, 0x50
endlabel waypoint_with_range
    /* 7803C 0017803C 00000000 */  nop
```
