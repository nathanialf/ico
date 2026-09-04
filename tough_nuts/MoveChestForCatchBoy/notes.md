# MoveChestForCatchBoy — parked

VRAM: 0x0015EAC8 (file_off 0x05EAC8)
Asm source: asm/aug6/nonmatchings/fumi/src/enemy_act/MoveChestForCatchBoy.s

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=6). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/enemy_act.c`

**Seed:** `tough_nuts/MoveChestForCatchBoy/MoveChestForCatchBoy.c`

Disassembly:

```
.align 3
nonmatching MoveChestForCatchBoy, 0x10C

glabel MoveChestForCatchBoy
    /* 5EAC8 0015EAC8 B0FFBD27 */  addiu      $29, $29, -0x50
    /* 5EACC 0015EACC 1000B0FF */  sd         $16, 0x10($29)
    /* 5EAD0 0015EAD0 2D808000 */  daddu      $16, $4, $0
    /* 5EAD4 0015EAD4 3000BFFF */  sd         $31, 0x30($29)
    /* 5EAD8 0015EAD8 4000B4E7 */  swc1       $f20, 0x40($29)
    /* 5EADC 0015EADC 2000B1FF */  sd         $17, 0x20($29)
    /* 5EAE0 0015EAE0 F891848F */  lw         $4, %gp_rel(D_00629DE8)($28)
    /* 5EAE4 0015EAE4 0B008010 */  beqz       $4, .L0015EB14
    /* 5EAE8 0015EAE8 6401118E */   lw        $17, 0x164($16)
    /* 5EAEC 0015EAEC 2D280002 */  daddu      $5, $16, $0
    /* 5EAF0 0015EAF0 3C04080C */  jal        ACTReserveTarget
    /* 5EAF4 0015EAF4 EC000624 */   addiu     $6, $0, 0xEC
    /* 5EAF8 0015EAF8 06004010 */  beqz       $2, .L0015EB14
    /* 5EAFC 0015EAFC 6B000224 */   addiu     $2, $0, 0x6B
    /* 5EB00 0015EB00 F891858F */  lw         $5, %gp_rel(D_00629DE8)($28)
    /* 5EB04 0015EB04 6401A38C */  lw         $3, 0x164($5)
    /* 5EB08 0015EB08 3000648C */  lw         $4, 0x30($3)
    /* 5EB0C 0015EB0C 03008214 */  bne        $4, $2, .L0015EB1C
    /* 5EB10 0015EB10 2D10A003 */   daddu     $2, $29, $0
.align 2
  .L0015EB14:
    /* 5EB14 0015EB14 29000010 */  b          .L0015EBBC
    /* 5EB18 0015EB18 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0015EB1C:
    /* 5EB1C 0015EB1C 4842013C */  lui        $1, (0x42480000 >> 16)
    /* 5EB20 0015EB20 00608144 */  mtc1       $1, $f12
    /* 5EB24 0015EB24 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* 5EB28 0015EB28 00A08144 */  mtc1       $1, $f20
    /* 5EB2C 0015EB2C 5C7A050C */  jal        actEnemyKidnapBegin
    /* 5EB30 0015EB30 2D200002 */   daddu     $4, $16, $0
    /* 5EB34 0015EB34 2D20A003 */  daddu      $4, $29, $0
    /* 5EB38 0015EB38 2D280000 */  daddu      $5, $0, $0
    /* 5EB3C 0015EB3C 5A81090C */  jal        memset
    /* 5EB40 0015EB40 10000624 */   addiu     $6, $0, 0x10
    /* 5EB44 0015EB44 0C00B4E7 */  swc1       $f20, 0xC($29)
    /* 5EB48 0015EB48 2D20A003 */  daddu      $4, $29, $0
    /* 5EB4C 0015EB4C 3A39040C */  jal        func_0010E4E8
    /* 5EB50 0015EB50 00800524 */   addiu     $5, $0, -0x8000
    /* 5EB54 0015EB54 6401038E */  lw         $3, 0x164($16)
    /* 5EB58 0015EB58 C6A30046 */  mov.s      $f15, $f20
    /* 5EB5C 0015EB5C 00688044 */  mtc1       $0, $f13
    /* 5EB60 0015EB60 2D40A003 */  daddu      $8, $29, $0
    /* 5EB64 0015EB64 7006628C */  lw         $2, 0x670($3)
    /* 5EB68 0015EB68 2D280002 */  daddu      $5, $16, $0
    /* 5EB6C 0015EB6C F891848F */  lw         $4, %gp_rel(D_00629DE8)($28)
    /* 5EB70 0015EB70 02000624 */  addiu      $6, $0, 0x2
    /* 5EB74 0015EB74 EC01478C */  lw         $7, 0x1EC($2)
    /* 5EB78 0015EB78 9041013C */  lui        $1, (0x41900000 >> 16)
    /* 5EB7C 0015EB7C 00608144 */  mtc1       $1, $f12
    /* 5EB80 0015EB80 9629040C */  jal        GetHeightOfFieldPlaneDifference
    /* 5EB84 0015EB84 866B0046 */   mov.s     $f14, $f13
    /* 5EB88 0015EB88 F891828F */  lw         $2, %gp_rel(D_00629DE8)($28)
    /* 5EB8C 0015EB8C 6401438C */  lw         $3, 0x164($2)
    /* 5EB90 0015EB90 2D204000 */  daddu      $4, $2, $0
    /* 5EB94 0015EB94 280122AE */  sw         $2, 0x128($17)
    /* 5EB98 0015EB98 2022050C */  jal        ACTParaStatus_Exec
    /* 5EB9C 0015EB9C 240170AC */   sw        $16, 0x124($3)
    /* 5EBA0 0015EBA0 2D200002 */  daddu      $4, $16, $0
    /* 5EBA4 0015EBA4 A83C060C */  jal        func_0018F2A0
    /* 5EBA8 0015EBA8 09000524 */   addiu     $5, $0, 0x9
    /* 5EBAC 0015EBAC 2D200002 */  daddu      $4, $16, $0
    /* 5EBB0 0015EBB0 A83C060C */  jal        func_0018F2A0
    /* 5EBB4 0015EBB4 07000524 */   addiu     $5, $0, 0x7
    /* 5EBB8 0015EBB8 01000224 */  addiu      $2, $0, 0x1
.align 2
  .L0015EBBC:
    /* 5EBBC 0015EBBC 3000BFDF */  ld         $31, 0x30($29)
    /* 5EBC0 0015EBC0 2000B1DF */  ld         $17, 0x20($29)
    /* 5EBC4 0015EBC4 1000B0DF */  ld         $16, 0x10($29)
    /* 5EBC8 0015EBC8 4000B4C7 */  lwc1       $f20, 0x40($29)
    /* 5EBCC 0015EBCC 0800E003 */  jr         $31
    /* 5EBD0 0015EBD0 5000BD27 */   addiu     $29, $29, 0x50
endlabel MoveChestForCatchBoy
    /* 5EBD4 0015EBD4 00000000 */  nop
```

---

## Attempt at 2026-07-07

**Reason parked:** rc6 delay-slot scheduling tie: gcc hoists D_00629DE8 gp_rel load into the ACTReserveTarget-result beqz delay while ROM hoists the 0x6B state-compare const there (and fills the state bne delay with a spare daddu v0,sp buf-addr). Single-block schedule/regalloc swap. 6 distinct source shapes (early-return, inverted-guard, float-buf, operand-swap, int-param, state-temp) all fold to rc6. Permuter-domain scheduling. Seed=rc6.

**TU:** `fumi/src/enemy_act.c`

**Seed:** `tough_nuts/MoveChestForCatchBoy/MoveChestForCatchBoy.1.c`

Disassembly:

```
.align 3
nonmatching MoveChestForCatchBoy, 0x10C

glabel MoveChestForCatchBoy
    /* 5EAC8 0015EAC8 B0FFBD27 */  addiu      $29, $29, -0x50
    /* 5EACC 0015EACC 1000B0FF */  sd         $16, 0x10($29)
    /* 5EAD0 0015EAD0 2D808000 */  daddu      $16, $4, $0
    /* 5EAD4 0015EAD4 3000BFFF */  sd         $31, 0x30($29)
    /* 5EAD8 0015EAD8 4000B4E7 */  swc1       $f20, 0x40($29)
    /* 5EADC 0015EADC 2000B1FF */  sd         $17, 0x20($29)
    /* 5EAE0 0015EAE0 F891848F */  lw         $4, %gp_rel(D_00629DE8)($28)
    /* 5EAE4 0015EAE4 0B008010 */  beqz       $4, .L0015EB14
    /* 5EAE8 0015EAE8 6401118E */   lw        $17, 0x164($16)
    /* 5EAEC 0015EAEC 2D280002 */  daddu      $5, $16, $0
    /* 5EAF0 0015EAF0 3C04080C */  jal        ACTReserveTarget
    /* 5EAF4 0015EAF4 EC000624 */   addiu     $6, $0, 0xEC
    /* 5EAF8 0015EAF8 06004010 */  beqz       $2, .L0015EB14
    /* 5EAFC 0015EAFC 6B000224 */   addiu     $2, $0, 0x6B
    /* 5EB00 0015EB00 F891858F */  lw         $5, %gp_rel(D_00629DE8)($28)
    /* 5EB04 0015EB04 6401A38C */  lw         $3, 0x164($5)
    /* 5EB08 0015EB08 3000648C */  lw         $4, 0x30($3)
    /* 5EB0C 0015EB0C 03008214 */  bne        $4, $2, .L0015EB1C
    /* 5EB10 0015EB10 2D10A003 */   daddu     $2, $29, $0
.align 2
  .L0015EB14:
    /* 5EB14 0015EB14 29000010 */  b          .L0015EBBC
    /* 5EB18 0015EB18 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0015EB1C:
    /* 5EB1C 0015EB1C 4842013C */  lui        $1, (0x42480000 >> 16)
    /* 5EB20 0015EB20 00608144 */  mtc1       $1, $f12
    /* 5EB24 0015EB24 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* 5EB28 0015EB28 00A08144 */  mtc1       $1, $f20
    /* 5EB2C 0015EB2C 5C7A050C */  jal        actEnemyKidnapBegin
    /* 5EB30 0015EB30 2D200002 */   daddu     $4, $16, $0
    /* 5EB34 0015EB34 2D20A003 */  daddu      $4, $29, $0
    /* 5EB38 0015EB38 2D280000 */  daddu      $5, $0, $0
    /* 5EB3C 0015EB3C 5A81090C */  jal        memset
    /* 5EB40 0015EB40 10000624 */   addiu     $6, $0, 0x10
    /* 5EB44 0015EB44 0C00B4E7 */  swc1       $f20, 0xC($29)
    /* 5EB48 0015EB48 2D20A003 */  daddu      $4, $29, $0
    /* 5EB4C 0015EB4C 3A39040C */  jal        func_0010E4E8
    /* 5EB50 0015EB50 00800524 */   addiu     $5, $0, -0x8000
    /* 5EB54 0015EB54 6401038E */  lw         $3, 0x164($16)
    /* 5EB58 0015EB58 C6A30046 */  mov.s      $f15, $f20
    /* 5EB5C 0015EB5C 00688044 */  mtc1       $0, $f13
    /* 5EB60 0015EB60 2D40A003 */  daddu      $8, $29, $0
    /* 5EB64 0015EB64 7006628C */  lw         $2, 0x670($3)
    /* 5EB68 0015EB68 2D280002 */  daddu      $5, $16, $0
    /* 5EB6C 0015EB6C F891848F */  lw         $4, %gp_rel(D_00629DE8)($28)
    /* 5EB70 0015EB70 02000624 */  addiu      $6, $0, 0x2
    /* 5EB74 0015EB74 EC01478C */  lw         $7, 0x1EC($2)
    /* 5EB78 0015EB78 9041013C */  lui        $1, (0x41900000 >> 16)
    /* 5EB7C 0015EB7C 00608144 */  mtc1       $1, $f12
    /* 5EB80 0015EB80 9629040C */  jal        GetHeightOfFieldPlaneDifference
    /* 5EB84 0015EB84 866B0046 */   mov.s     $f14, $f13
    /* 5EB88 0015EB88 F891828F */  lw         $2, %gp_rel(D_00629DE8)($28)
    /* 5EB8C 0015EB8C 6401438C */  lw         $3, 0x164($2)
    /* 5EB90 0015EB90 2D204000 */  daddu      $4, $2, $0
    /* 5EB94 0015EB94 280122AE */  sw         $2, 0x128($17)
    /* 5EB98 0015EB98 2022050C */  jal        ACTParaStatus_Exec
    /* 5EB9C 0015EB9C 240170AC */   sw        $16, 0x124($3)
    /* 5EBA0 0015EBA0 2D200002 */  daddu      $4, $16, $0
    /* 5EBA4 0015EBA4 A83C060C */  jal        func_0018F2A0
    /* 5EBA8 0015EBA8 09000524 */   addiu     $5, $0, 0x9
    /* 5EBAC 0015EBAC 2D200002 */  daddu      $4, $16, $0
    /* 5EBB0 0015EBB0 A83C060C */  jal        func_0018F2A0
    /* 5EBB4 0015EBB4 07000524 */   addiu     $5, $0, 0x7
    /* 5EBB8 0015EBB8 01000224 */  addiu      $2, $0, 0x1
.align 2
  .L0015EBBC:
    /* 5EBBC 0015EBBC 3000BFDF */  ld         $31, 0x30($29)
    /* 5EBC0 0015EBC0 2000B1DF */  ld         $17, 0x20($29)
    /* 5EBC4 0015EBC4 1000B0DF */  ld         $16, 0x10($29)
    /* 5EBC8 0015EBC8 4000B4C7 */  lwc1       $f20, 0x40($29)
    /* 5EBCC 0015EBCC 0800E003 */  jr         $31
    /* 5EBD0 0015EBD0 5000BD27 */   addiu     $29, $29, 0x50
endlabel MoveChestForCatchBoy
    /* 5EBD4 0015EBD4 00000000 */  nop
```

---

## Attempt at 2026-07-07

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=6). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/enemy_act.c`

**Seed:** `tough_nuts/MoveChestForCatchBoy/MoveChestForCatchBoy.2.c`

Disassembly:

```
.align 3
nonmatching MoveChestForCatchBoy, 0x10C

glabel MoveChestForCatchBoy
    /* 5EAC8 0015EAC8 B0FFBD27 */  addiu      $29, $29, -0x50
    /* 5EACC 0015EACC 1000B0FF */  sd         $16, 0x10($29)
    /* 5EAD0 0015EAD0 2D808000 */  daddu      $16, $4, $0
    /* 5EAD4 0015EAD4 3000BFFF */  sd         $31, 0x30($29)
    /* 5EAD8 0015EAD8 4000B4E7 */  swc1       $f20, 0x40($29)
    /* 5EADC 0015EADC 2000B1FF */  sd         $17, 0x20($29)
    /* 5EAE0 0015EAE0 F891848F */  lw         $4, %gp_rel(D_00629DE8)($28)
    /* 5EAE4 0015EAE4 0B008010 */  beqz       $4, .L0015EB14
    /* 5EAE8 0015EAE8 6401118E */   lw        $17, 0x164($16)
    /* 5EAEC 0015EAEC 2D280002 */  daddu      $5, $16, $0
    /* 5EAF0 0015EAF0 3C04080C */  jal        ACTReserveTarget
    /* 5EAF4 0015EAF4 EC000624 */   addiu     $6, $0, 0xEC
    /* 5EAF8 0015EAF8 06004010 */  beqz       $2, .L0015EB14
    /* 5EAFC 0015EAFC 6B000224 */   addiu     $2, $0, 0x6B
    /* 5EB00 0015EB00 F891858F */  lw         $5, %gp_rel(D_00629DE8)($28)
    /* 5EB04 0015EB04 6401A38C */  lw         $3, 0x164($5)
    /* 5EB08 0015EB08 3000648C */  lw         $4, 0x30($3)
    /* 5EB0C 0015EB0C 03008214 */  bne        $4, $2, .L0015EB1C
    /* 5EB10 0015EB10 2D10A003 */   daddu     $2, $29, $0
.align 2
  .L0015EB14:
    /* 5EB14 0015EB14 29000010 */  b          .L0015EBBC
    /* 5EB18 0015EB18 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0015EB1C:
    /* 5EB1C 0015EB1C 4842013C */  lui        $1, (0x42480000 >> 16)
    /* 5EB20 0015EB20 00608144 */  mtc1       $1, $f12
    /* 5EB24 0015EB24 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* 5EB28 0015EB28 00A08144 */  mtc1       $1, $f20
    /* 5EB2C 0015EB2C 5C7A050C */  jal        actEnemyKidnapBegin
    /* 5EB30 0015EB30 2D200002 */   daddu     $4, $16, $0
    /* 5EB34 0015EB34 2D20A003 */  daddu      $4, $29, $0
    /* 5EB38 0015EB38 2D280000 */  daddu      $5, $0, $0
    /* 5EB3C 0015EB3C 5A81090C */  jal        memset
    /* 5EB40 0015EB40 10000624 */   addiu     $6, $0, 0x10
    /* 5EB44 0015EB44 0C00B4E7 */  swc1       $f20, 0xC($29)
    /* 5EB48 0015EB48 2D20A003 */  daddu      $4, $29, $0
    /* 5EB4C 0015EB4C 3A39040C */  jal        func_0010E4E8
    /* 5EB50 0015EB50 00800524 */   addiu     $5, $0, -0x8000
    /* 5EB54 0015EB54 6401038E */  lw         $3, 0x164($16)
    /* 5EB58 0015EB58 C6A30046 */  mov.s      $f15, $f20
    /* 5EB5C 0015EB5C 00688044 */  mtc1       $0, $f13
    /* 5EB60 0015EB60 2D40A003 */  daddu      $8, $29, $0
    /* 5EB64 0015EB64 7006628C */  lw         $2, 0x670($3)
    /* 5EB68 0015EB68 2D280002 */  daddu      $5, $16, $0
    /* 5EB6C 0015EB6C F891848F */  lw         $4, %gp_rel(D_00629DE8)($28)
    /* 5EB70 0015EB70 02000624 */  addiu      $6, $0, 0x2
    /* 5EB74 0015EB74 EC01478C */  lw         $7, 0x1EC($2)
    /* 5EB78 0015EB78 9041013C */  lui        $1, (0x41900000 >> 16)
    /* 5EB7C 0015EB7C 00608144 */  mtc1       $1, $f12
    /* 5EB80 0015EB80 9629040C */  jal        GetHeightOfFieldPlaneDifference
    /* 5EB84 0015EB84 866B0046 */   mov.s     $f14, $f13
    /* 5EB88 0015EB88 F891828F */  lw         $2, %gp_rel(D_00629DE8)($28)
    /* 5EB8C 0015EB8C 6401438C */  lw         $3, 0x164($2)
    /* 5EB90 0015EB90 2D204000 */  daddu      $4, $2, $0
    /* 5EB94 0015EB94 280122AE */  sw         $2, 0x128($17)
    /* 5EB98 0015EB98 2022050C */  jal        ACTParaStatus_Exec
    /* 5EB9C 0015EB9C 240170AC */   sw        $16, 0x124($3)
    /* 5EBA0 0015EBA0 2D200002 */  daddu      $4, $16, $0
    /* 5EBA4 0015EBA4 A83C060C */  jal        func_0018F2A0
    /* 5EBA8 0015EBA8 09000524 */   addiu     $5, $0, 0x9
    /* 5EBAC 0015EBAC 2D200002 */  daddu      $4, $16, $0
    /* 5EBB0 0015EBB0 A83C060C */  jal        func_0018F2A0
    /* 5EBB4 0015EBB4 07000524 */   addiu     $5, $0, 0x7
    /* 5EBB8 0015EBB8 01000224 */  addiu      $2, $0, 0x1
.align 2
  .L0015EBBC:
    /* 5EBBC 0015EBBC 3000BFDF */  ld         $31, 0x30($29)
    /* 5EBC0 0015EBC0 2000B1DF */  ld         $17, 0x20($29)
    /* 5EBC4 0015EBC4 1000B0DF */  ld         $16, 0x10($29)
    /* 5EBC8 0015EBC8 4000B4C7 */  lwc1       $f20, 0x40($29)
    /* 5EBCC 0015EBCC 0800E003 */  jr         $31
    /* 5EBD0 0015EBD0 5000BD27 */   addiu     $29, $29, 0x50
endlabel MoveChestForCatchBoy
    /* 5EBD4 0015EBD4 00000000 */  nop
```
