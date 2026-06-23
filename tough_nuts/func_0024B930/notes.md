# func_0024B930 — parked

VRAM: 0x0024B930 (file_off 0x14B930)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0024B930.s

## Attempt at 2026-06-23

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=5). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0024B930/func_0024B930.c`

Disassembly:

```
.align 3
nonmatching func_0024B930, 0x134

glabel func_0024B930
    /* 14B930 0024B930 70FFBD27 */  addiu      $29, $29, -0x90
    /* 14B934 0024B934 6000B5FF */  sd         $21, 0x60($29)
    /* 14B938 0024B938 3000B2FF */  sd         $18, 0x30($29)
    /* 14B93C 0024B93C 2DA88000 */  daddu      $21, $4, $0
    /* 14B940 0024B940 5500123C */  lui        $18, %hi(D_0054C694)
    /* 14B944 0024B944 7000B6FF */  sd         $22, 0x70($29)
    /* 14B948 0024B948 4000B3FF */  sd         $19, 0x40($29)
    /* 14B94C 0024B94C 2DB0A000 */  daddu      $22, $5, $0
    /* 14B950 0024B950 2000B1FF */  sd         $17, 0x20($29)
    /* 14B954 0024B954 2D98E000 */  daddu      $19, $7, $0
    /* 14B958 0024B958 94C6448E */  lw         $4, %lo(D_0054C694)($18)
    /* 14B95C 0024B95C 2D88C000 */  daddu      $17, $6, $0
    /* 14B960 0024B960 8000BFFF */  sd         $31, 0x80($29)
    /* 14B964 0024B964 5000B4FF */  sd         $20, 0x50($29)
    /* 14B968 0024B968 5C01040C */  jal        func_00100570
    /* 14B96C 0024B96C 1000B0FF */   sd        $16, 0x10($29)
    /* 14B970 0024B970 03004104 */  bgez       $2, .L0024B980
    /* 14B974 0024B974 7100023C */   lui       $2, %hi(D_00711640)
    /* 14B978 0024B978 30000010 */  b          .L0024BA3C
    /* 14B97C 0024B97C 38FF0224 */   addiu     $2, $0, -0xC8
.align 2
  .L0024B980:
    /* 14B980 0024B980 40165424 */  addiu      $20, $2, %lo(D_00711640)
    /* 14B984 0024B984 2400838E */  lw         $3, 0x24($20)
    /* 14B988 0024B988 05006014 */  bnez       $3, .L0024B9A0
    /* 14B98C 0024B98C 00000000 */   nop
    /* 14B990 0024B990 5001040C */  jal        func_00100540
    /* 14B994 0024B994 94C6448E */   lw        $4, %lo(D_0054C694)($18)
    /* 14B998 0024B998 28000010 */  b          .L0024BA3C
    /* 14B99C 0024B99C 9CFF0224 */   addiu     $2, $0, -0x64
.align 2
  .L0024B9A0:
    /* 14B9A0 0024B9A0 04002012 */  beqz       $17, .L0024B9B4
    /* 14B9A4 0024B9A4 00000000 */   nop
    /* 14B9A8 0024B9A8 00002282 */  lb         $2, 0x0($17)
    /* 14B9AC 0024B9AC 05004014 */  bnez       $2, .L0024B9C4
    /* 14B9B0 0024B9B0 7100103C */   lui       $16, %hi(D_00711704)
.align 2
  .L0024B9B4:
    /* 14B9B4 0024B9B4 5001040C */  jal        func_00100540
    /* 14B9B8 0024B9B8 94C6448E */   lw        $4, %lo(D_0054C694)($18)
    /* 14B9BC 0024B9BC 1F000010 */  b          .L0024BA3C
    /* 14B9C0 0024B9C0 2EFF0224 */   addiu     $2, $0, -0xD2
.align 2
  .L0024B9C4:
    /* 14B9C4 0024B9C4 2D282002 */  daddu      $5, $17, $0
    /* 14B9C8 0024B9C8 04171026 */  addiu      $16, $16, %lo(D_00711704)
    /* 14B9CC 0024B9CC FF030624 */  addiu      $6, $0, 0x3FF
    /* 14B9D0 0024B9D0 4086090C */  jal        func_00261900
    /* 14B9D4 0024B9D4 2D200002 */   daddu     $4, $16, $0
    /* 14B9D8 0024B9D8 ECFF0326 */  addiu      $3, $16, -0x14
    /* 14B9DC 0024B9DC ECFF15AE */  sw         $21, -0x14($16)
    /* 14B9E0 0024B9E0 080073AC */  sw         $19, 0x8($3)
    /* 14B9E4 0024B9E4 7100093C */  lui        $9, %hi(D_00712C00)
    /* 14B9E8 0024B9E8 040076AC */  sw         $22, 0x4($3)
    /* 14B9EC 0024B9EC 2D208002 */  daddu      $4, $20, $0
    /* 14B9F0 0024B9F0 130460A0 */  sb         $0, 0x413($3)
    /* 14B9F4 0024B9F4 2D386000 */  daddu      $7, $3, $0
    /* 14B9F8 0024B9F8 002C2925 */  addiu      $9, $9, %lo(D_00712C00)
    /* 14B9FC 0024B9FC 02000524 */  addiu      $5, $0, 0x2
    /* 14BA00 0024BA00 0000A0AF */  sw         $0, 0x0($29)
    /* 14BA04 0024BA04 01000624 */  addiu      $6, $0, 0x1
    /* 14BA08 0024BA08 14040824 */  addiu      $8, $0, 0x414
    /* 14BA0C 0024BA0C 04000A24 */  addiu      $10, $0, 0x4
    /* 14BA10 0024BA10 5E0A090C */  jal        func_00242978
    /* 14BA14 0024BA14 2D580000 */   daddu     $11, $0, $0
    /* 14BA18 0024BA18 2D804000 */  daddu      $16, $2, $0
    /* 14BA1C 0024BA1C 04000016 */  bnez       $16, .L0024BA30
    /* 14BA20 0024BA20 5500033C */   lui       $3, %hi(D_0054C690)
    /* 14BA24 0024BA24 02000224 */  addiu      $2, $0, 0x2
    /* 14BA28 0024BA28 03000010 */  b          .L0024BA38
    /* 14BA2C 0024BA2C 90C662AC */   sw        $2, %lo(D_0054C690)($3)
.align 2
  .L0024BA30:
    /* 14BA30 0024BA30 5001040C */  jal        func_00100540
    /* 14BA34 0024BA34 94C6448E */   lw        $4, %lo(D_0054C694)($18)
.align 2
  .L0024BA38:
    /* 14BA38 0024BA38 2D100002 */  daddu      $2, $16, $0
.align 2
  .L0024BA3C:
    /* 14BA3C 0024BA3C 8000BFDF */  ld         $31, 0x80($29)
    /* 14BA40 0024BA40 7000B6DF */  ld         $22, 0x70($29)
    /* 14BA44 0024BA44 6000B5DF */  ld         $21, 0x60($29)
    /* 14BA48 0024BA48 5000B4DF */  ld         $20, 0x50($29)
    /* 14BA4C 0024BA4C 4000B3DF */  ld         $19, 0x40($29)
    /* 14BA50 0024BA50 3000B2DF */  ld         $18, 0x30($29)
    /* 14BA54 0024BA54 2000B1DF */  ld         $17, 0x20($29)
    /* 14BA58 0024BA58 1000B0DF */  ld         $16, 0x10($29)
    /* 14BA5C 0024BA5C 0800E003 */  jr         $31
    /* 14BA60 0024BA60 9000BD27 */   addiu     $29, $29, 0x90
endlabel func_0024B930
    /* 14BA64 0024BA64 00000000 */  nop
```
