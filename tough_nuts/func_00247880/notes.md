# func_00247880 — parked

VRAM: 0x00247880 (file_off 0x147880)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_00247880.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_00247880/func_00247880.c`

Disassembly:

```
.align 3
nonmatching func_00247880, 0x84

glabel func_00247880
    /* 147880 00247880 2D308000 */  daddu      $6, $4, $0
    /* 147884 00247884 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 147888 00247888 FFFFC424 */  addiu      $4, $6, -0x1
    /* 14788C 0024788C 1000BFFF */  sd         $31, 0x10($29)
    /* 147890 00247890 0D00822C */  sltiu      $2, $4, 0xD
    /* 147894 00247894 04004014 */  bnez       $2, .L002478A8
    /* 147898 00247898 0000B0FF */   sd        $16, 0x0($29)
    /* 14789C 0024789C FFFF023C */  lui        $2, (0xFFFFFFFF >> 16)
    /* 1478A0 002478A0 14000010 */  b          .L002478F4
    /* 1478A4 002478A4 FFFF4234 */   ori       $2, $2, (0xFFFFFFFF & 0xFFFF)
.align 2
  .L002478A8:
    /* 1478A8 002478A8 5500023C */  lui        $2, %hi(D_0054AB48)
    /* 1478AC 002478AC 80180600 */  sll        $3, $6, 2
    /* 1478B0 002478B0 48AB4224 */  addiu      $2, $2, %lo(D_0054AB48)
    /* 1478B4 002478B4 0300842C */  sltiu      $4, $4, 0x3
    /* 1478B8 002478B8 21186200 */  addu       $3, $3, $2
    /* 1478BC 002478BC 0000708C */  lw         $16, 0x0($3)
    /* 1478C0 002478C0 07008010 */  beqz       $4, .L002478E0
    /* 1478C4 002478C4 000065AC */   sw        $5, 0x0($3)
    /* 1478C8 002478C8 2400053C */  lui        $5, %hi(D_00247C40)
    /* 1478CC 002478CC 2D20C000 */  daddu      $4, $6, $0
    /* 1478D0 002478D0 7400040C */  jal        func_001001D0
    /* 1478D4 002478D4 407CA524 */   addiu     $5, $5, %lo(D_00247C40)
    /* 1478D8 002478D8 06000010 */  b          .L002478F4
    /* 1478DC 002478DC 2D100002 */   daddu     $2, $16, $0
.align 2
  .L002478E0:
    /* 1478E0 002478E0 2400053C */  lui        $5, %hi(D_00247C40)
    /* 1478E4 002478E4 2D20C000 */  daddu      $4, $6, $0
    /* 1478E8 002478E8 7800040C */  jal        func_001001E0
    /* 1478EC 002478EC 407CA524 */   addiu     $5, $5, %lo(D_00247C40)
    /* 1478F0 002478F0 2D100002 */  daddu      $2, $16, $0
.align 2
  .L002478F4:
    /* 1478F4 002478F4 1000BFDF */  ld         $31, 0x10($29)
    /* 1478F8 002478F8 0000B0DF */  ld         $16, 0x0($29)
    /* 1478FC 002478FC 0800E003 */  jr         $31
    /* 147900 00247900 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_00247880
    /* 147904 00247904 00000000 */  nop
```
