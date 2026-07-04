# func_0023CB70 — parked

VRAM: 0x0023CB70 (file_off 0x13CB70)
Asm source: asm/aug6/nonmatchings/common/src/GobjProc/func_0023CB70.s

## Attempt at 2026-07-04

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=64). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/GobjProc.c`

**Seed:** `tough_nuts/func_0023CB70/func_0023CB70.c`

Disassembly:

```
.align 3
nonmatching func_0023CB70, 0x16C

glabel func_0023CB70
    /* 13CB70 0023CB70 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 13CB74 0023CB74 2D588000 */  daddu      $11, $4, $0
    /* 13CB78 0023CB78 0000B0FF */  sd         $16, 0x0($29)
    /* 13CB7C 0023CB7C 2D68A000 */  daddu      $13, $5, $0
    /* 13CB80 0023CB80 01001824 */  addiu      $24, $0, 0x1
    /* 13CB84 0023CB84 5C00628D */  lw         $2, 0x5C($11)
    /* 13CB88 0023CB88 5800658D */  lw         $5, 0x58($11)
    /* 13CB8C 0023CB8C 5400698D */  lw         $9, 0x54($11)
    /* 13CB90 0023CB90 23104500 */  subu       $2, $2, $5
    /* 13CB94 0023CB94 21104900 */  addu       $2, $2, $9
    /* 13CB98 0023CB98 01002051 */  beql       $9, $0, .L0023CBA0
    /* 13CB9C 0023CB9C CD010000 */   break     0, 7
.align 2
  .L0023CBA0:
    /* 13CBA0 0023CBA0 1A004900 */  div        $0, $2, $9
    /* 13CBA4 0023CBA4 0800638D */  lw         $3, 0x8($11)
    /* 13CBA8 0023CBA8 C0520300 */  sll        $10, $3, 11
    /* 13CBAC 0023CBAC 10200000 */  mfhi       $4
    /* 13CBB0 0023CBB0 4600A018 */  blez       $5, .L0023CCCC
    /* 13CBB4 0023CBB4 2D608000 */   daddu     $12, $4, $0
    /* 13CBB8 0023CBB8 18000224 */  addiu      $2, $0, 0x18
    /* 13CBBC 0023CBBC 5000638D */  lw         $3, 0x50($11)
    /* 13CBC0 0023CBC0 18108201 */  mult       $2, $12, $2
    /* 13CBC4 0023CBC4 21286200 */  addu       $5, $3, $2
    /* 13CBC8 0023CBC8 1400A88C */  lw         $8, 0x14($5)
    /* 13CBCC 0023CBCC 40000011 */  beqz       $8, .L0023CCD0
    /* 13CBD0 0023CBD0 0000B0DF */   ld        $16, 0x0($29)
    /* 13CBD4 0023CBD4 1400A78D */  lw         $7, 0x14($13)
    /* 13CBD8 0023CBD8 3C00E010 */  beqz       $7, .L0023CCCC
    /* 13CBDC 0023CBDC 2D806000 */   daddu     $16, $3, $0
    /* 13CBE0 0023CBE0 2D780000 */  daddu      $15, $0, $0
    /* 13CBE4 0023CBE4 FFFF0E24 */  addiu      $14, $0, -0x1
    /* 13CBE8 0023CBE8 18001924 */  addiu      $25, $0, 0x18
    /* 13CBEC 0023CBEC 00000000 */  nop
.align 2
  .L0023CBF0:
    /* 13CBF0 0023CBF0 1000A48C */  lw         $4, 0x10($5)
    /* 13CBF4 0023CBF4 01004051 */  beql       $10, $0, .L0023CBFC
    /* 13CBF8 0023CBF8 CD010000 */   break     0, 7
.align 2
  .L0023CBFC:
    /* 13CBFC 0023CBFC 1000A68D */  lw         $6, 0x10($13)
    /* 13CC00 0023CC00 21108A00 */  addu       $2, $4, $10
    /* 13CC04 0023CC04 23104600 */  subu       $2, $2, $6
    /* 13CC08 0023CC08 1A004A00 */  div        $0, $2, $10
    /* 13CC0C 0023CC0C 10180000 */  mfhi       $3
    /* 13CC10 0023CC10 2A186700 */  slt        $3, $3, $7
    /* 13CC14 0023CC14 1B006010 */  beqz       $3, .L0023CC84
    /* 13CC18 0023CC18 2110C700 */   addu      $2, $6, $7
    /* 13CC1C 0023CC1C 01004F51 */  beql       $10, $15, .L0023CC24
    /* 13CC20 0023CC20 CD010000 */   break     0, 7
.align 2
  .L0023CC24:
    /* 13CC24 0023CC24 23104400 */  subu       $2, $2, $4
    /* 13CC28 0023CC28 2A180201 */  slt        $3, $8, $2
    /* 13CC2C 0023CC2C 0B100301 */  movn       $2, $8, $3
    /* 13CC30 0023CC30 21208200 */  addu       $4, $4, $2
    /* 13CC34 0023CC34 1A008A00 */  div        $0, $4, $10
    /* 13CC38 0023CC38 23100201 */  subu       $2, $8, $2
    /* 13CC3C 0023CC3C 1400A2AC */  sw         $2, 0x14($5)
    /* 13CC40 0023CC40 10180000 */  mfhi       $3
    /* 13CC44 0023CC44 11004014 */  bnez       $2, .L0023CC8C
    /* 13CC48 0023CC48 1000A3AC */   sw        $3, 0x10($5)
    /* 13CC4C 0023CC4C 0000A2DC */  ld         $2, 0x0($5)
    /* 13CC50 0023CC50 06004204 */  bltzl      $2, .L0023CC6C
    /* 13CC54 0023CC54 5800628D */   lw        $2, 0x58($11)
    /* 13CC58 0023CC58 1400A0AC */  sw         $0, 0x14($5)
    /* 13CC5C 0023CC5C 0000AEFC */  sd         $14, 0x0($5)
    /* 13CC60 0023CC60 0800AEFC */  sd         $14, 0x8($5)
    /* 13CC64 0023CC64 1000A0AC */  sw         $0, 0x10($5)
    /* 13CC68 0023CC68 5800628D */  lw         $2, 0x58($11)
.align 2
  .L0023CC6C:
    /* 13CC6C 0023CC6C 5400698D */  lw         $9, 0x54($11)
    /* 13CC70 0023CC70 FFFF4224 */  addiu      $2, $2, -0x1
    /* 13CC74 0023CC74 2A18C201 */  slt        $3, $14, $2
    /* 13CC78 0023CC78 0A100300 */  movz       $2, $0, $3
    /* 13CC7C 0023CC7C 04000010 */  b          .L0023CC90
    /* 13CC80 0023CC80 580062AD */   sw        $2, 0x58($11)
.align 2
  .L0023CC84:
    /* 13CC84 0023CC84 02000010 */  b          .L0023CC90
    /* 13CC88 0023CC88 2DC00000 */   daddu     $24, $0, $0
.align 2
  .L0023CC8C:
    /* 13CC8C 0023CC8C 5400698D */  lw         $9, 0x54($11)
.align 2
  .L0023CC90:
    /* 13CC90 0023CC90 01008225 */  addiu      $2, $12, 0x1
    /* 13CC94 0023CC94 01002F51 */  beql       $9, $15, .L0023CC9C
    /* 13CC98 0023CC98 CD010000 */   break     0, 7
.align 2
  .L0023CC9C:
    /* 13CC9C 0023CC9C 1A004900 */  div        $0, $2, $9
    /* 13CCA0 0023CCA0 10180000 */  mfhi       $3
    /* 13CCA4 0023CCA4 09000013 */  beqz       $24, .L0023CCCC
    /* 13CCA8 0023CCA8 2D606000 */   daddu     $12, $3, $0
    /* 13CCAC 0023CCAC 18109901 */  mult       $2, $12, $25
    /* 13CCB0 0023CCB0 21285000 */  addu       $5, $2, $16
    /* 13CCB4 0023CCB4 1400A28C */  lw         $2, 0x14($5)
    /* 13CCB8 0023CCB8 04004010 */  beqz       $2, .L0023CCCC
    /* 13CCBC 0023CCBC 2D404000 */   daddu     $8, $2, $0
    /* 13CCC0 0023CCC0 1400A28D */  lw         $2, 0x14($13)
    /* 13CCC4 0023CCC4 CAFF4014 */  bnez       $2, .L0023CBF0
    /* 13CCC8 0023CCC8 2D384000 */   daddu     $7, $2, $0
.align 2
  .L0023CCCC:
    /* 13CCCC 0023CCCC 0000B0DF */  ld         $16, 0x0($29)
.align 2
  .L0023CCD0:
    /* 13CCD0 0023CCD0 2D100000 */  daddu      $2, $0, $0
    /* 13CCD4 0023CCD4 0800E003 */  jr         $31
    /* 13CCD8 0023CCD8 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_0023CB70
    /* 13CCDC 0023CCDC 00000000 */  nop
```
