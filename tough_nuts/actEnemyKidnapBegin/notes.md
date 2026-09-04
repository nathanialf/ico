# actEnemyKidnapBegin — parked

VRAM: 0x0015E970 (file_off 0x05E970)
Asm source: asm/aug6/nonmatchings/fumi/src/enemy_act/actEnemyKidnapBegin.s

## Attempt at 2026-06-29

**Reason parked:** rc10 near-miss — fp store-back coloring (addiu v0,256 giv + swc1/lwc1 sched on a0/a1 unk164+0x100 plane stores); user-directed park

**TU:** `fumi/src/enemy_act.c`

**Seed:** `tough_nuts/actEnemyKidnapBegin/actEnemyKidnapBegin.c`

Disassembly:

```
.align 3
nonmatching actEnemyKidnapBegin, 0x158

glabel actEnemyKidnapBegin
    /* 5E970 0015E970 30FFBD27 */  addiu      $29, $29, -0xD0
    /* 5E974 0015E974 A000B5FF */  sd         $21, 0xA0($29)
    /* 5E978 0015E978 2DA88000 */  daddu      $21, $4, $0
    /* 5E97C 0015E97C 7000B2FF */  sd         $18, 0x70($29)
    /* 5E980 0015E980 C000B4E7 */  swc1       $f20, 0xC0($29)
    /* 5E984 0015E984 2D90A000 */  daddu      $18, $5, $0
    /* 5E988 0015E988 9000B4FF */  sd         $20, 0x90($29)
    /* 5E98C 0015E98C 8000B3FF */  sd         $19, 0x80($29)
    /* 5E990 0015E990 6000B1FF */  sd         $17, 0x60($29)
    /* 5E994 0015E994 5000B0FF */  sd         $16, 0x50($29)
    /* 5E998 0015E998 0000A2AF */  sw         $2, 0x0($29)
    /* 5E99C 0015E99C B000BFFF */  sd         $31, 0xB0($29)
    /* 5E9A0 0015E9A0 3E74050C */  jal        ContinueCorrectPosition
    /* 5E9A4 0015E9A4 06650046 */   mov.s     $f20, $f12
    /* 5E9A8 0015E9A8 000040C4 */  lwc1       $f0, 0x0($2)
    /* 5E9AC 0015E9AC 2D20A002 */  daddu      $4, $21, $0
    /* 5E9B0 0015E9B0 3E74050C */  jal        ContinueCorrectPosition
    /* 5E9B4 0015E9B4 1000A0E7 */   swc1      $f0, 0x10($29)
    /* 5E9B8 0015E9B8 040040C4 */  lwc1       $f0, 0x4($2)
    /* 5E9BC 0015E9BC 2D20A002 */  daddu      $4, $21, $0
    /* 5E9C0 0015E9C0 3E74050C */  jal        ContinueCorrectPosition
    /* 5E9C4 0015E9C4 1400A0E7 */   swc1      $f0, 0x14($29)
    /* 5E9C8 0015E9C8 080040C4 */  lwc1       $f0, 0x8($2)
    /* 5E9CC 0015E9CC 2D204002 */  daddu      $4, $18, $0
    /* 5E9D0 0015E9D0 3E74050C */  jal        ContinueCorrectPosition
    /* 5E9D4 0015E9D4 1800A0E7 */   swc1      $f0, 0x18($29)
    /* 5E9D8 0015E9D8 000040C4 */  lwc1       $f0, 0x0($2)
    /* 5E9DC 0015E9DC 2D204002 */  daddu      $4, $18, $0
    /* 5E9E0 0015E9E0 3E74050C */  jal        ContinueCorrectPosition
    /* 5E9E4 0015E9E4 2000A0E7 */   swc1      $f0, 0x20($29)
    /* 5E9E8 0015E9E8 040040C4 */  lwc1       $f0, 0x4($2)
    /* 5E9EC 0015E9EC 2D204002 */  daddu      $4, $18, $0
    /* 5E9F0 0015E9F0 3E74050C */  jal        ContinueCorrectPosition
    /* 5E9F4 0015E9F4 2400A0E7 */   swc1      $f0, 0x24($29)
    /* 5E9F8 0015E9F8 080040C4 */  lwc1       $f0, 0x8($2)
    /* 5E9FC 0015E9FC 3000B327 */  addiu      $19, $29, 0x30
    /* 5EA00 0015EA00 2000B027 */  addiu      $16, $29, 0x20
    /* 5EA04 0015EA04 1000B427 */  addiu      $20, $29, 0x10
    /* 5EA08 0015EA08 2D206002 */  daddu      $4, $19, $0
    /* 5EA0C 0015EA0C 2D280002 */  daddu      $5, $16, $0
    /* 5EA10 0015EA10 2D308002 */  daddu      $6, $20, $0
    /* 5EA14 0015EA14 F447060C */  jal        _OrientXZGV
    /* 5EA18 0015EA18 2800A0E7 */   swc1      $f0, 0x28($29)
    /* 5EA1C 0015EA1C 4000B127 */  addiu      $17, $29, 0x40
    /* 5EA20 0015EA20 06A30046 */  mov.s      $f12, $f20
    /* 5EA24 0015EA24 2D202002 */  daddu      $4, $17, $0
    /* 5EA28 0015EA28 0E00090C */  jal        sceVu0ScaleVector
    /* 5EA2C 0015EA2C 2D286002 */   daddu     $5, $19, $0
    /* 5EA30 0015EA30 2D288002 */  daddu      $5, $20, $0
    /* 5EA34 0015EA34 2D302002 */  daddu      $6, $17, $0
    /* 5EA38 0015EA38 FCFF080C */  jal        sceVu0AddVector
    /* 5EA3C 0015EA3C 2D200002 */   daddu     $4, $16, $0
    /* 5EA40 0015EA40 2D280002 */  daddu      $5, $16, $0
    /* 5EA44 0015EA44 5810040C */  jal        CylinderCollision
    /* 5EA48 0015EA48 2D204002 */   daddu     $4, $18, $0
    /* 5EA4C 0015EA4C 6401A28E */  lw         $2, 0x164($21)
    /* 5EA50 0015EA50 2D286002 */  daddu      $5, $19, $0
    /* 5EA54 0015EA54 3000A0C7 */  lwc1       $f0, 0x30($29)
    /* 5EA58 0015EA58 6401448E */  lw         $4, 0x164($18)
    /* 5EA5C 0015EA5C 000140E4 */  swc1       $f0, 0x100($2)
    /* 5EA60 0015EA60 80BF013C */  lui        $1, (0xBF800000 >> 16)
    /* 5EA64 0015EA64 00608144 */  mtc1       $1, $f12
    /* 5EA68 0015EA68 00018424 */  addiu      $4, $4, 0x100
    /* 5EA6C 0015EA6C 3400A0C7 */  lwc1       $f0, 0x34($29)
    /* 5EA70 0015EA70 040140E4 */  swc1       $f0, 0x104($2)
    /* 5EA74 0015EA74 3800A1C7 */  lwc1       $f1, 0x38($29)
    /* 5EA78 0015EA78 0E00090C */  jal        sceVu0ScaleVector
    /* 5EA7C 0015EA7C 080141E4 */   swc1      $f1, 0x108($2)
    /* 5EA80 0015EA80 6401A58E */  lw         $5, 0x164($21)
    /* 5EA84 0015EA84 2D20A002 */  daddu      $4, $21, $0
    /* 5EA88 0015EA88 2E1A040C */  jal        dispPlane
    /* 5EA8C 0015EA8C 0001A524 */   addiu     $5, $5, 0x100
    /* 5EA90 0015EA90 6401458E */  lw         $5, 0x164($18)
    /* 5EA94 0015EA94 2D204002 */  daddu      $4, $18, $0
    /* 5EA98 0015EA98 2E1A040C */  jal        dispPlane
    /* 5EA9C 0015EA9C 0001A524 */   addiu     $5, $5, 0x100
    /* 5EAA0 0015EAA0 B000BFDF */  ld         $31, 0xB0($29)
    /* 5EAA4 0015EAA4 A000B5DF */  ld         $21, 0xA0($29)
    /* 5EAA8 0015EAA8 9000B4DF */  ld         $20, 0x90($29)
    /* 5EAAC 0015EAAC 8000B3DF */  ld         $19, 0x80($29)
    /* 5EAB0 0015EAB0 7000B2DF */  ld         $18, 0x70($29)
    /* 5EAB4 0015EAB4 6000B1DF */  ld         $17, 0x60($29)
    /* 5EAB8 0015EAB8 5000B0DF */  ld         $16, 0x50($29)
    /* 5EABC 0015EABC C000B4C7 */  lwc1       $f20, 0xC0($29)
    /* 5EAC0 0015EAC0 0800E003 */  jr         $31
    /* 5EAC4 0015EAC4 D000BD27 */   addiu     $29, $29, 0xD0
endlabel actEnemyKidnapBegin
```
