# actEnemyAttack — parked

VRAM: 0x0015DA10 (file_off 0x05DA10)
Asm source: asm/aug6/nonmatchings/fumi/src/enemy_act/actEnemyAttack.s

## Attempt at 2026-07-02

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=15). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/enemy_act.c`

**Seed:** `tough_nuts/actEnemyAttack/actEnemyAttack.c`

Disassembly:

```
.align 3
nonmatching actEnemyAttack, 0x164

glabel actEnemyAttack
    /* 5DA10 0015DA10 B0FFBD27 */  addiu      $29, $29, -0x50
    /* 5DA14 0015DA14 2000B1FF */  sd         $17, 0x20($29)
    /* 5DA18 0015DA18 1000B0FF */  sd         $16, 0x10($29)
    /* 5DA1C 0015DA1C 4000BFFF */  sd         $31, 0x40($29)
    /* 5DA20 0015DA20 2D808000 */  daddu      $16, $4, $0
    /* 5DA24 0015DA24 3000B2FF */  sd         $18, 0x30($29)
    /* 5DA28 0015DA28 5C01028E */  lw         $2, 0x15C($16)
    /* 5DA2C 0015DA2C 8800528C */  lw         $18, 0x88($2)
    /* 5DA30 0015DA30 0E00401A */  blez       $18, .L0015DA6C
    /* 5DA34 0015DA34 2D880000 */   daddu     $17, $0, $0
    /* 5DA38 0015DA38 2D200002 */  daddu      $4, $16, $0
    /* 5DA3C 0015DA3C 00000000 */  nop
.align 2
  .L0015DA40:
    /* 5DA40 0015DA40 022F070C */  jal        HotInitDemoMotionGeo
    /* 5DA44 0015DA44 2D282002 */   daddu     $5, $17, $0
    /* 5DA48 0015DA48 05004054 */  bnel       $2, $0, .L0015DA60
    /* 5DA4C 0015DA4C 01003126 */   addiu     $17, $17, 0x1
    /* 5DA50 0015DA50 2D200002 */  daddu      $4, $16, $0
    /* 5DA54 0015DA54 7276050C */  jal        subEnemyCollision
    /* 5DA58 0015DA58 2D282002 */   daddu     $5, $17, $0
    /* 5DA5C 0015DA5C 01003126 */  addiu      $17, $17, 0x1
.align 2
  .L0015DA60:
    /* 5DA60 0015DA60 2A103202 */  slt        $2, $17, $18
    /* 5DA64 0015DA64 F6FF4014 */  bnez       $2, .L0015DA40
    /* 5DA68 0015DA68 2D200002 */   daddu     $4, $16, $0
.align 2
  .L0015DA6C:
    /* 5DA6C 0015DA6C 6401068E */  lw         $6, 0x164($16)
    /* 5DA70 0015DA70 2D900000 */  daddu      $18, $0, $0
    /* 5DA74 0015DA74 04001124 */  addiu      $17, $0, 0x4
.align 2
  .L0015DA78:
    /* 5DA78 0015DA78 7006C28C */  lw         $2, 0x670($6)
    /* 5DA7C 0015DA7C 21104202 */  addu       $2, $18, $2
    /* 5DA80 0015DA80 60034524 */  addiu      $5, $2, 0x360
    /* 5DA84 0015DA84 1D00A380 */  lb         $3, 0x1D($5)
    /* 5DA88 0015DA88 32006050 */  beql       $3, $0, .L0015DB54
    /* 5DA8C 0015DA8C FFFF3126 */   addiu     $17, $17, -0x1
    /* 5DA90 0015DA90 1C00A280 */  lb         $2, 0x1C($5)
    /* 5DA94 0015DA94 12004010 */  beqz       $2, .L0015DAE0
    /* 5DA98 0015DA98 2D20A003 */   daddu     $4, $29, $0
    /* 5DA9C 0015DA9C 5C01038E */  lw         $3, 0x15C($16)
    /* 5DAA0 0015DAA0 1400A28C */  lw         $2, 0x14($5)
    /* 5DAA4 0015DAA4 0C00658C */  lw         $5, 0xC($3)
    /* 5DAA8 0015DAA8 80110200 */  sll        $2, $2, 6
    /* 5DAAC 0015DAAC 2128A200 */  addu       $5, $5, $2
    /* 5DAB0 0015DAB0 2000090C */  jal        func_00240080
    /* 5DAB4 0015DAB4 3000A524 */   addiu     $5, $5, 0x30
    /* 5DAB8 0015DAB8 6401038E */  lw         $3, 0x164($16)
    /* 5DABC 0015DABC 2D28A003 */  daddu      $5, $29, $0
    /* 5DAC0 0015DAC0 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* 5DAC4 0015DAC4 00008144 */  mtc1       $1, $f0
    /* 5DAC8 0015DAC8 7006628C */  lw         $2, 0x670($3)
    /* 5DACC 0015DACC 0C00A0E7 */  swc1       $f0, 0xC($29)
    /* 5DAD0 0015DAD0 21104202 */  addu       $2, $18, $2
    /* 5DAD4 0015DAD4 C652060C */  jal        BirdDL
    /* 5DAD8 0015DAD8 7003448C */   lw        $4, 0x370($2)
    /* 5DADC 0015DADC 6401068E */  lw         $6, 0x164($16)
.align 2
  .L0015DAE0:
    /* 5DAE0 0015DAE0 7006C28C */  lw         $2, 0x670($6)
    /* 5DAE4 0015DAE4 21104202 */  addu       $2, $18, $2
    /* 5DAE8 0015DAE8 60034224 */  addiu      $2, $2, 0x360
    /* 5DAEC 0015DAEC 1800438C */  lw         $3, 0x18($2)
    /* 5DAF0 0015DAF0 06006054 */  bnel       $3, $0, .L0015DB0C
    /* 5DAF4 0015DAF4 7006C28C */   lw        $2, 0x670($6)
    /* 5DAF8 0015DAF8 1400458C */  lw         $5, 0x14($2)
    /* 5DAFC 0015DAFC FA2E070C */  jal        InitDemoMotionGeo
    /* 5DB00 0015DB00 2D200002 */   daddu     $4, $16, $0
    /* 5DB04 0015DB04 6401068E */  lw         $6, 0x164($16)
    /* 5DB08 0015DB08 7006C28C */  lw         $2, 0x670($6)
.align 2
  .L0015DB0C:
    /* 5DB0C 0015DB0C 21104202 */  addu       $2, $18, $2
    /* 5DB10 0015DB10 60034424 */  addiu      $4, $2, 0x360
    /* 5DB14 0015DB14 1C008380 */  lb         $3, 0x1C($4)
    /* 5DB18 0015DB18 07006054 */  bnel       $3, $0, .L0015DB38
    /* 5DB1C 0015DB1C 7006C38C */   lw        $3, 0x670($6)
    /* 5DB20 0015DB20 1800828C */  lw         $2, 0x18($4)
    /* 5DB24 0015DB24 04004304 */  bgezl      $2, .L0015DB38
    /* 5DB28 0015DB28 7006C38C */   lw        $3, 0x670($6)
    /* 5DB2C 0015DB2C 1D0080A0 */  sb         $0, 0x1D($4)
    /* 5DB30 0015DB30 6401068E */  lw         $6, 0x164($16)
    /* 5DB34 0015DB34 7006C38C */  lw         $3, 0x670($6)
.align 2
  .L0015DB38:
    /* 5DB38 0015DB38 21184302 */  addu       $3, $18, $3
    /* 5DB3C 0015DB3C 60036324 */  addiu      $3, $3, 0x360
    /* 5DB40 0015DB40 1800628C */  lw         $2, 0x18($3)
    /* 5DB44 0015DB44 FFFF4224 */  addiu      $2, $2, -0x1
    /* 5DB48 0015DB48 180062AC */  sw         $2, 0x18($3)
    /* 5DB4C 0015DB4C 6401068E */  lw         $6, 0x164($16)
    /* 5DB50 0015DB50 FFFF3126 */  addiu      $17, $17, -0x1
.align 2
  .L0015DB54:
    /* 5DB54 0015DB54 C8FF2106 */  bgez       $17, .L0015DA78
    /* 5DB58 0015DB58 20005226 */   addiu     $18, $18, 0x20
    /* 5DB5C 0015DB5C 4000BFDF */  ld         $31, 0x40($29)
    /* 5DB60 0015DB60 3000B2DF */  ld         $18, 0x30($29)
    /* 5DB64 0015DB64 2000B1DF */  ld         $17, 0x20($29)
    /* 5DB68 0015DB68 1000B0DF */  ld         $16, 0x10($29)
    /* 5DB6C 0015DB6C 0800E003 */  jr         $31
    /* 5DB70 0015DB70 5000BD27 */   addiu     $29, $29, 0x50
endlabel actEnemyAttack
    /* 5DB74 0015DB74 00000000 */  nop
```
