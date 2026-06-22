# func_0025EAA8 — parked

VRAM: 0x0025EAA8 (file_off 0x15EAA8)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0025EAA8.s

## Attempt at 2026-06-22

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=33). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0025EAA8/func_0025EAA8.c`

Disassembly:

```
.align 3
nonmatching func_0025EAA8, 0x12C

glabel func_0025EAA8
    /* 15EAA8 0025EAA8 0000838C */  lw         $3, 0x0($4)
    /* 15EAAC 0025EAAC 2D380000 */  daddu      $7, $0, $0
    /* 15EAB0 0025EAB0 0400888C */  lw         $8, 0x4($4)
    /* 15EAB4 0025EAB4 0200622C */  sltiu      $2, $3, 0x2
    /* 15EAB8 0025EAB8 06004010 */  beqz       $2, .L0025EAD4
    /* 15EABC 0025EABC 100085DC */   ld        $5, 0x10($4)
    /* 15EAC0 0025EAC0 00800234 */  ori        $2, $0, 0x8000
    /* 15EAC4 0025EAC4 3C110200 */  dsll32     $2, $2, 4
    /* 15EAC8 0025EAC8 FF070724 */  addiu      $7, $0, 0x7FF
    /* 15EACC 0025EACC 2A000010 */  b          .L0025EB78
    /* 15EAD0 0025EAD0 2528A200 */   or        $5, $5, $2
.align 2
  .L0025EAD4:
    /* 15EAD4 0025EAD4 04006238 */  xori       $2, $3, 0x4
    /* 15EAD8 0025EAD8 16004050 */  beql       $2, $0, .L0025EB34
    /* 15EADC 0025EADC FF070724 */   addiu     $7, $0, 0x7FF
    /* 15EAE0 0025EAE0 02006238 */  xori       $2, $3, 0x2
    /* 15EAE4 0025EAE4 03004014 */  bnez       $2, .L0025EAF4
    /* 15EAE8 0025EAE8 00000000 */   nop
    /* 15EAEC 0025EAEC 22000010 */  b          .L0025EB78
    /* 15EAF0 0025EAF0 2D280000 */   daddu     $5, $0, $0
.align 2
  .L0025EAF4:
    /* 15EAF4 0025EAF4 2000A010 */  beqz       $5, .L0025EB78
    /* 15EAF8 0025EAF8 00000000 */   nop
    /* 15EAFC 0025EAFC 0800838C */  lw         $3, 0x8($4)
    /* 15EB00 0025EB00 02FC6228 */  slti       $2, $3, -0x3FE
    /* 15EB04 0025EB04 07004010 */  beqz       $2, .L0025EB24
    /* 15EB08 0025EB08 02FC0224 */   addiu     $2, $0, -0x3FE
    /* 15EB0C 0025EB0C 23104300 */  subu       $2, $2, $3
    /* 15EB10 0025EB10 39004328 */  slti       $3, $2, 0x39
    /* 15EB14 0025EB14 17006014 */  bnez       $3, .L0025EB74
    /* 15EB18 0025EB18 16284500 */   dsrlv     $5, $5, $2
    /* 15EB1C 0025EB1C 15000010 */  b          .L0025EB74
    /* 15EB20 0025EB20 2D280000 */   daddu     $5, $0, $0
.align 2
  .L0025EB24:
    /* 15EB24 0025EB24 00046228 */  slti       $2, $3, 0x400
    /* 15EB28 0025EB28 04004014 */  bnez       $2, .L0025EB3C
    /* 15EB2C 0025EB2C FF036724 */   addiu     $7, $3, 0x3FF
    /* 15EB30 0025EB30 FF070724 */  addiu      $7, $0, 0x7FF
.align 2
  .L0025EB34:
    /* 15EB34 0025EB34 10000010 */  b          .L0025EB78
    /* 15EB38 0025EB38 2D280000 */   daddu     $5, $0, $0
.align 2
  .L0025EB3C:
    /* 15EB3C 0025EB3C 80000224 */  addiu      $2, $0, 0x80
    /* 15EB40 0025EB40 FF00A330 */  andi       $3, $5, 0xFF
    /* 15EB44 0025EB44 04006254 */  bnel       $3, $2, .L0025EB58
    /* 15EB48 0025EB48 7F00A564 */   daddiu    $5, $5, 0x7F
    /* 15EB4C 0025EB4C 0001A330 */  andi       $3, $5, 0x100
    /* 15EB50 0025EB50 8000A264 */  daddiu     $2, $5, 0x80
    /* 15EB54 0025EB54 0B284300 */  movn       $5, $2, $3
.align 2
  .L0025EB58:
    /* 15EB58 0025EB58 FFFF0224 */  addiu      $2, $0, -0x1
    /* 15EB5C 0025EB5C FA100200 */  dsrl       $2, $2, 3
    /* 15EB60 0025EB60 2B104500 */  sltu       $2, $2, $5
    /* 15EB64 0025EB64 04004050 */  beql       $2, $0, .L0025EB78
    /* 15EB68 0025EB68 3A2A0500 */   dsrl      $5, $5, 8
    /* 15EB6C 0025EB6C 7A280500 */  dsrl       $5, $5, 1
    /* 15EB70 0025EB70 0100E724 */  addiu      $7, $7, 0x1
.align 2
  .L0025EB74:
    /* 15EB74 0025EB74 3A2A0500 */  dsrl       $5, $5, 8
.align 2
  .L0025EB78:
    /* 15EB78 0025EB78 F0FF0334 */  ori        $3, $0, 0xFFF0
    /* 15EB7C 0025EB7C 3C1C0300 */  dsll32     $3, $3, 16
    /* 15EB80 0025EB80 FFFF0224 */  addiu      $2, $0, -0x1
    /* 15EB84 0025EB84 3A130200 */  dsrl       $2, $2, 12
    /* 15EB88 0025EB88 2410A200 */  and        $2, $5, $2
    /* 15EB8C 0025EB8C 2430C300 */  and        $6, $6, $3
    /* 15EB90 0025EB90 2530C200 */  or         $6, $6, $2
    /* 15EB94 0025EB94 FF07E330 */  andi       $3, $7, 0x7FF
    /* 15EB98 0025EB98 0F80023C */  lui        $2, (0x800FFFFF >> 16)
    /* 15EB9C 0025EB9C FFFF4234 */  ori        $2, $2, (0x800FFFFF & 0xFFFF)
    /* 15EBA0 0025EBA0 38140200 */  dsll       $2, $2, 16
    /* 15EBA4 0025EBA4 FFFF4234 */  ori        $2, $2, 0xFFFF
    /* 15EBA8 0025EBA8 38140200 */  dsll       $2, $2, 16
    /* 15EBAC 0025EBAC FFFF4234 */  ori        $2, $2, 0xFFFF
    /* 15EBB0 0025EBB0 3C1D0300 */  dsll32     $3, $3, 20
    /* 15EBB4 0025EBB4 2430C200 */  and        $6, $6, $2
    /* 15EBB8 0025EBB8 FFFF0424 */  addiu      $4, $0, -0x1
    /* 15EBBC 0025EBBC 7A200400 */  dsrl       $4, $4, 1
    /* 15EBC0 0025EBC0 2530C300 */  or         $6, $6, $3
    /* 15EBC4 0025EBC4 FC170800 */  dsll32     $2, $8, 31
    /* 15EBC8 0025EBC8 2430C400 */  and        $6, $6, $4
    /* 15EBCC 0025EBCC 0800E003 */  jr         $31
    /* 15EBD0 0025EBD0 2510C200 */   or        $2, $6, $2
endlabel func_0025EAA8
    /* 15EBD4 0025EBD4 00000000 */  nop
```
