# iosPadDevRead — parked

VRAM: 0x0013B0F8 (file_off 0x03B0F8)
Asm source: asm/aug6/nonmatchings/fumi/ios/pad/iosPadDevRead.s

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=41). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/ios/pad.c`

**Seed:** `tough_nuts/iosPadDevRead/iosPadDevRead.c`

Disassembly:

```
.align 3
nonmatching iosPadDevRead, 0x104

glabel iosPadDevRead
    /* 3B0F8 0013B0F8 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 3B0FC 0013B0FC 6A00023C */  lui        $2, %hi(D_006A0930)
    /* 3B100 0013B100 1000BFFF */  sd         $31, 0x10($29)
    /* 3B104 0013B104 30094724 */  addiu      $7, $2, %lo(D_006A0930)
    /* 3B108 0013B108 0000B0FF */  sd         $16, 0x0($29)
    /* 3B10C 0013B10C 0F000824 */  addiu      $8, $0, 0xF
    /* 3B110 0013B110 FFFF0924 */  addiu      $9, $0, -0x1
    /* 3B114 0013B114 00000000 */  nop
.align 2
  .L0013B118:
    /* 3B118 0013B118 0000E28C */  lw         $2, 0x0($7)
    /* 3B11C 0013B11C 05004010 */  beqz       $2, .L0013B134
    /* 3B120 0013B120 FFFF0825 */   addiu     $8, $8, -0x1
    /* 3B124 0013B124 FCFF0915 */  bne        $8, $9, .L0013B118
    /* 3B128 0013B128 1800E724 */   addiu     $7, $7, 0x18
    /* 3B12C 0013B12C 02000010 */  b          .L0013B138
    /* 3B130 0013B130 2D800000 */   daddu     $16, $0, $0
.align 2
  .L0013B134:
    /* 3B134 0013B134 2D80E000 */  daddu      $16, $7, $0
.align 2
  .L0013B138:
    /* 3B138 0013B138 23008010 */  beqz       $4, .L0013B1C8
    /* 3B13C 0013B13C 2098828F */   lw        $2, %gp_rel(D_0062A410)($28)
    /* 3B140 0013B140 2A004010 */  beqz       $2, .L0013B1EC
    /* 3B144 0013B144 2D100000 */   daddu     $2, $0, $0
    /* 3B148 0013B148 1F000012 */  beqz       $16, .L0013B1C8
    /* 3B14C 0013B14C 5F00023C */   lui       $2, %hi(D_005EBB90)
    /* 3B150 0013B150 C0180500 */  sll        $3, $5, 3
    /* 3B154 0013B154 90BB4224 */  addiu      $2, $2, %lo(D_005EBB90)
    /* 3B158 0013B158 0000868C */  lw         $6, 0x0($4)
    /* 3B15C 0013B15C 21186200 */  addu       $3, $3, $2
    /* 3B160 0013B160 FF000924 */  addiu      $9, $0, 0xFF
    /* 3B164 0013B164 04006784 */  lh         $7, 0x4($3)
    /* 3B168 0013B168 A401C624 */  addiu      $6, $6, 0x1A4
    /* 3B16C 0013B16C 06006594 */  lhu        $5, 0x6($3)
    /* 3B170 0013B170 20000224 */  addiu      $2, $0, 0x20
    /* 3B174 0013B174 140009A2 */  sb         $9, 0x14($16)
    /* 3B178 0013B178 2D20C000 */  daddu      $4, $6, $0
    /* 3B17C 0013B17C 0F0002A2 */  sb         $2, 0xF($16)
    /* 3B180 0013B180 FFFF033C */  lui        $3, (0xFFFF0000 >> 16)
    /* 3B184 0013B184 3E180300 */  dsrl32     $3, $3, 0
    /* 3B188 0013B188 100005A6 */  sh         $5, 0x10($16)
    /* 3B18C 0013B18C 2D400000 */  daddu      $8, $0, $0
    /* 3B190 0013B190 0D0000A2 */  sb         $0, 0xD($16)
    /* 3B194 0013B194 2D28E000 */  daddu      $5, $7, $0
    /* 3B198 0013B198 0C0000A2 */  sb         $0, 0xC($16)
    /* 3B19C 0013B19C 0E0009A2 */  sb         $9, 0xE($16)
    /* 3B1A0 0013B1A0 080007AE */  sw         $7, 0x8($16)
    /* 3B1A4 0013B1A4 120000A6 */  sh         $0, 0x12($16)
    /* 3B1A8 0013B1A8 040006AE */  sw         $6, 0x4($16)
    /* 3B1AC 0013B1AC 9C98878F */  lw         $7, %gp_rel(D_0062A48C)($28)
    /* 3B1B0 0013B1B0 0F00068A */  lwl        $6, 0xF($16)
    /* 3B1B4 0013B1B4 0C00069A */  lwr        $6, 0xC($16)
    /* 3B1B8 0013B1B8 FEEE040C */  jal        ShockRequestBox_Regst
    /* 3B1BC 0013B1BC 2430C300 */   and       $6, $6, $3
    /* 3B1C0 0013B1C0 03004014 */  bnez       $2, .L0013B1D0
    /* 3B1C4 0013B1C4 9C98828F */   lw        $2, %gp_rel(D_0062A48C)($28)
.align 2
  .L0013B1C8:
    /* 3B1C8 0013B1C8 08000010 */  b          .L0013B1EC
    /* 3B1CC 0013B1CC 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0013B1D0:
    /* 3B1D0 0013B1D0 000002AE */  sw         $2, 0x0($16)
    /* 3B1D4 0013B1D4 01004224 */  addiu      $2, $2, 0x1
    /* 3B1D8 0013B1D8 03004014 */  bnez       $2, .L0013B1E8
    /* 3B1DC 0013B1DC 9C9882AF */   sw        $2, %gp_rel(D_0062A48C)($28)
    /* 3B1E0 0013B1E0 01000224 */  addiu      $2, $0, 0x1
    /* 3B1E4 0013B1E4 9C9882AF */  sw         $2, %gp_rel(D_0062A48C)($28)
.align 2
  .L0013B1E8:
    /* 3B1E8 0013B1E8 0000028E */  lw         $2, 0x0($16)
.align 2
  .L0013B1EC:
    /* 3B1EC 0013B1EC 1000BFDF */  ld         $31, 0x10($29)
    /* 3B1F0 0013B1F0 0000B0DF */  ld         $16, 0x0($29)
    /* 3B1F4 0013B1F4 0800E003 */  jr         $31
    /* 3B1F8 0013B1F8 2000BD27 */   addiu     $29, $29, 0x20
endlabel iosPadDevRead
    /* 3B1FC 0013B1FC 00000000 */  nop
```
