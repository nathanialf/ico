# func_0015AF10 — parked

VRAM: 0x0015AF10 (file_off 0x05AF10)
Asm source: asm/aug6/nonmatchings/fumi/src/commonact/func_0015AF10.s

## Attempt at 2026-06-24

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=8). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/commonact.c`

**Seed:** `tough_nuts/func_0015AF10/func_0015AF10.c`

Disassembly:

```
.align 3
nonmatching func_0015AF10, 0x144

glabel func_0015AF10
    /* 5AF10 0015AF10 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 5AF14 0015AF14 1000B0FF */  sd         $16, 0x10($29)
    /* 5AF18 0015AF18 2000BFFF */  sd         $31, 0x20($29)
    /* 5AF1C 0015AF1C 2D808000 */  daddu      $16, $4, $0
    /* 5AF20 0015AF20 6401038E */  lw         $3, 0x164($16)
    /* 5AF24 0015AF24 7006648C */  lw         $4, 0x670($3)
    /* 5AF28 0015AF28 B400828C */  lw         $2, 0xB4($4)
    /* 5AF2C 0015AF2C 01004224 */  addiu      $2, $2, 0x1
    /* 5AF30 0015AF30 B40082AC */  sw         $2, 0xB4($4)
    /* 5AF34 0015AF34 6401038E */  lw         $3, 0x164($16)
    /* 5AF38 0015AF38 7006648C */  lw         $4, 0x670($3)
    /* 5AF3C 0015AF3C B400888C */  lw         $8, 0xB4($4)
    /* 5AF40 0015AF40 B000898C */  lw         $9, 0xB0($4)
    /* 5AF44 0015AF44 2A102801 */  slt        $2, $9, $8
    /* 5AF48 0015AF48 37004054 */  bnel       $2, $0, .L0015B028
    /* 5AF4C 0015AF4C B80082DC */   ld        $2, 0xB8($4)
    /* 5AF50 0015AF50 F891828F */  lw         $2, %gp_rel(D_00629DE8)($28)
    /* 5AF54 0015AF54 0D000256 */  bnel       $16, $2, .L0015AF8C
    /* 5AF58 0015AF58 7006658C */   lw        $5, 0x670($3)
    /* 5AF5C 0015AF5C 94A3828F */  lw         $2, %gp_rel(D_0062AF84)($28)
    /* 5AF60 0015AF60 01004230 */  andi       $2, $2, 0x1
    /* 5AF64 0015AF64 08004010 */  beqz       $2, .L0015AF88
    /* 5AF68 0015AF68 5500073C */   lui       $7, %hi(D_005530A8)
    /* 5AF6C 0015AF6C FF0F063C */  lui        $6, (0xFFFFFFF >> 16)
    /* 5AF70 0015AF70 A830E724 */  addiu      $7, $7, %lo(D_005530A8)
    /* 5AF74 0015AF74 64000424 */  addiu      $4, $0, 0x64
    /* 5AF78 0015AF78 64000524 */  addiu      $5, $0, 0x64
    /* 5AF7C 0015AF7C F48F060C */  jal        traceLine
    /* 5AF80 0015AF80 FFFFC634 */   ori       $6, $6, (0xFFFFFFF & 0xFFFF)
    /* 5AF84 0015AF84 6401038E */  lw         $3, 0x164($16)
.align 2
  .L0015AF88:
    /* 5AF88 0015AF88 7006658C */  lw         $5, 0x670($3)
.align 2
  .L0015AF8C:
    /* 5AF8C 0015AF8C 2D20A003 */  daddu      $4, $29, $0
    /* 5AF90 0015AF90 B400A38C */  lw         $3, 0xB4($5)
    /* 5AF94 0015AF94 9000A624 */  addiu      $6, $5, 0x90
    /* 5AF98 0015AF98 B000A28C */  lw         $2, 0xB0($5)
    /* 5AF9C 0015AF9C 00608344 */  mtc1       $3, $f12
    /* 5AFA0 0015AFA0 20638046 */  cvt.s.w    $f12, $f12
    /* 5AFA4 0015AFA4 23104300 */  subu       $2, $2, $3
    /* 5AFA8 0015AFA8 00688244 */  mtc1       $2, $f13
    /* 5AFAC 0015AFAC 606B8046 */  cvt.s.w    $f13, $f13
    /* 5AFB0 0015AFB0 0846060C */  jal        _InterGV
    /* 5AFB4 0015AFB4 7000A524 */   addiu     $5, $5, 0x70
    /* 5AFB8 0015AFB8 2D200002 */  daddu      $4, $16, $0
    /* 5AFBC 0015AFBC 5810040C */  jal        CylinderCollision
    /* 5AFC0 0015AFC0 2D28A003 */   daddu     $5, $29, $0
    /* 5AFC4 0015AFC4 6401038E */  lw         $3, 0x164($16)
    /* 5AFC8 0015AFC8 01000424 */  addiu      $4, $0, 0x1
    /* 5AFCC 0015AFCC 7006658C */  lw         $5, 0x670($3)
    /* 5AFD0 0015AFD0 B800A28C */  lw         $2, 0xB8($5)
    /* 5AFD4 0015AFD4 1C004414 */  bne        $2, $4, .L0015B048
    /* 5AFD8 0015AFD8 2000BFDF */   ld        $31, 0x20($29)
    /* 5AFDC 0015AFDC B400A38C */  lw         $3, 0xB4($5)
    /* 5AFE0 0015AFE0 A000A624 */  addiu      $6, $5, 0xA0
    /* 5AFE4 0015AFE4 B000A28C */  lw         $2, 0xB0($5)
    /* 5AFE8 0015AFE8 2D20A003 */  daddu      $4, $29, $0
    /* 5AFEC 0015AFEC 00608344 */  mtc1       $3, $f12
    /* 5AFF0 0015AFF0 20638046 */  cvt.s.w    $f12, $f12
    /* 5AFF4 0015AFF4 23104300 */  subu       $2, $2, $3
    /* 5AFF8 0015AFF8 00688244 */  mtc1       $2, $f13
    /* 5AFFC 0015AFFC 606B8046 */  cvt.s.w    $f13, $f13
    /* 5B000 0015B000 0846060C */  jal        _InterGV
    /* 5B004 0015B004 8000A524 */   addiu     $5, $5, 0x80
    /* 5B008 0015B008 2D20A003 */  daddu      $4, $29, $0
    /* 5B00C 0015B00C A6FF080C */  jal        sceVu0Normalize
    /* 5B010 0015B010 2D28A003 */   daddu     $5, $29, $0
    /* 5B014 0015B014 2D200002 */  daddu      $4, $16, $0
    /* 5B018 0015B018 2E1A040C */  jal        dispPlane
    /* 5B01C 0015B01C 2D28A003 */   daddu     $5, $29, $0
    /* 5B020 0015B020 09000010 */  b          .L0015B048
    /* 5B024 0015B024 2000BFDF */   ld        $31, 0x20($29)
.align 2
  .L0015B028:
    /* 5B028 0015B028 FEFF0324 */  addiu      $3, $0, -0x2
    /* 5B02C 0015B02C 381C0300 */  dsll       $3, $3, 16
    /* 5B030 0015B030 FFFF6334 */  ori        $3, $3, 0xFFFF
    /* 5B034 0015B034 381C0300 */  dsll       $3, $3, 16
    /* 5B038 0015B038 FFFF6334 */  ori        $3, $3, 0xFFFF
    /* 5B03C 0015B03C 24104300 */  and        $2, $2, $3
    /* 5B040 0015B040 B80082FC */  sd         $2, 0xB8($4)
    /* 5B044 0015B044 2000BFDF */  ld         $31, 0x20($29)
.align 2
  .L0015B048:
    /* 5B048 0015B048 1000B0DF */  ld         $16, 0x10($29)
    /* 5B04C 0015B04C 0800E003 */  jr         $31
    /* 5B050 0015B050 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_0015AF10
    /* 5B054 0015B054 00000000 */  nop
```

---

## Attempt at 2026-07-07

**Reason parked:** rc20 near-miss: full body correct incl out-of-line mask block (goto clear) + FP OrientXZGV blocks. residual = ROM reloads self->164->670 chain after o->B4++ int store (-fno-strict-aliasing behavior), aug6 lacks that flag; coupled bnel delay-fill. needs union-typed alias or permuter.

**TU:** `fumi/src/commonact.c`

**Seed:** `tough_nuts/func_0015AF10/func_0015AF10.1.c`

Disassembly:

```
.align 3
nonmatching func_0015AF10, 0x144

glabel func_0015AF10
    /* 5AF10 0015AF10 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 5AF14 0015AF14 1000B0FF */  sd         $16, 0x10($29)
    /* 5AF18 0015AF18 2000BFFF */  sd         $31, 0x20($29)
    /* 5AF1C 0015AF1C 2D808000 */  daddu      $16, $4, $0
    /* 5AF20 0015AF20 6401038E */  lw         $3, 0x164($16)
    /* 5AF24 0015AF24 7006648C */  lw         $4, 0x670($3)
    /* 5AF28 0015AF28 B400828C */  lw         $2, 0xB4($4)
    /* 5AF2C 0015AF2C 01004224 */  addiu      $2, $2, 0x1
    /* 5AF30 0015AF30 B40082AC */  sw         $2, 0xB4($4)
    /* 5AF34 0015AF34 6401038E */  lw         $3, 0x164($16)
    /* 5AF38 0015AF38 7006648C */  lw         $4, 0x670($3)
    /* 5AF3C 0015AF3C B400888C */  lw         $8, 0xB4($4)
    /* 5AF40 0015AF40 B000898C */  lw         $9, 0xB0($4)
    /* 5AF44 0015AF44 2A102801 */  slt        $2, $9, $8
    /* 5AF48 0015AF48 37004054 */  bnel       $2, $0, .L0015B028
    /* 5AF4C 0015AF4C B80082DC */   ld        $2, 0xB8($4)
    /* 5AF50 0015AF50 F891828F */  lw         $2, %gp_rel(D_00629DE8)($28)
    /* 5AF54 0015AF54 0D000256 */  bnel       $16, $2, .L0015AF8C
    /* 5AF58 0015AF58 7006658C */   lw        $5, 0x670($3)
    /* 5AF5C 0015AF5C 94A3828F */  lw         $2, %gp_rel(D_0062AF84)($28)
    /* 5AF60 0015AF60 01004230 */  andi       $2, $2, 0x1
    /* 5AF64 0015AF64 08004010 */  beqz       $2, .L0015AF88
    /* 5AF68 0015AF68 5500073C */   lui       $7, %hi(D_005530A8)
    /* 5AF6C 0015AF6C FF0F063C */  lui        $6, (0xFFFFFFF >> 16)
    /* 5AF70 0015AF70 A830E724 */  addiu      $7, $7, %lo(D_005530A8)
    /* 5AF74 0015AF74 64000424 */  addiu      $4, $0, 0x64
    /* 5AF78 0015AF78 64000524 */  addiu      $5, $0, 0x64
    /* 5AF7C 0015AF7C F48F060C */  jal        traceLine
    /* 5AF80 0015AF80 FFFFC634 */   ori       $6, $6, (0xFFFFFFF & 0xFFFF)
    /* 5AF84 0015AF84 6401038E */  lw         $3, 0x164($16)
.align 2
  .L0015AF88:
    /* 5AF88 0015AF88 7006658C */  lw         $5, 0x670($3)
.align 2
  .L0015AF8C:
    /* 5AF8C 0015AF8C 2D20A003 */  daddu      $4, $29, $0
    /* 5AF90 0015AF90 B400A38C */  lw         $3, 0xB4($5)
    /* 5AF94 0015AF94 9000A624 */  addiu      $6, $5, 0x90
    /* 5AF98 0015AF98 B000A28C */  lw         $2, 0xB0($5)
    /* 5AF9C 0015AF9C 00608344 */  mtc1       $3, $f12
    /* 5AFA0 0015AFA0 20638046 */  cvt.s.w    $f12, $f12
    /* 5AFA4 0015AFA4 23104300 */  subu       $2, $2, $3
    /* 5AFA8 0015AFA8 00688244 */  mtc1       $2, $f13
    /* 5AFAC 0015AFAC 606B8046 */  cvt.s.w    $f13, $f13
    /* 5AFB0 0015AFB0 0846060C */  jal        _InterGV
    /* 5AFB4 0015AFB4 7000A524 */   addiu     $5, $5, 0x70
    /* 5AFB8 0015AFB8 2D200002 */  daddu      $4, $16, $0
    /* 5AFBC 0015AFBC 5810040C */  jal        CylinderCollision
    /* 5AFC0 0015AFC0 2D28A003 */   daddu     $5, $29, $0
    /* 5AFC4 0015AFC4 6401038E */  lw         $3, 0x164($16)
    /* 5AFC8 0015AFC8 01000424 */  addiu      $4, $0, 0x1
    /* 5AFCC 0015AFCC 7006658C */  lw         $5, 0x670($3)
    /* 5AFD0 0015AFD0 B800A28C */  lw         $2, 0xB8($5)
    /* 5AFD4 0015AFD4 1C004414 */  bne        $2, $4, .L0015B048
    /* 5AFD8 0015AFD8 2000BFDF */   ld        $31, 0x20($29)
    /* 5AFDC 0015AFDC B400A38C */  lw         $3, 0xB4($5)
    /* 5AFE0 0015AFE0 A000A624 */  addiu      $6, $5, 0xA0
    /* 5AFE4 0015AFE4 B000A28C */  lw         $2, 0xB0($5)
    /* 5AFE8 0015AFE8 2D20A003 */  daddu      $4, $29, $0
    /* 5AFEC 0015AFEC 00608344 */  mtc1       $3, $f12
    /* 5AFF0 0015AFF0 20638046 */  cvt.s.w    $f12, $f12
    /* 5AFF4 0015AFF4 23104300 */  subu       $2, $2, $3
    /* 5AFF8 0015AFF8 00688244 */  mtc1       $2, $f13
    /* 5AFFC 0015AFFC 606B8046 */  cvt.s.w    $f13, $f13
    /* 5B000 0015B000 0846060C */  jal        _InterGV
    /* 5B004 0015B004 8000A524 */   addiu     $5, $5, 0x80
    /* 5B008 0015B008 2D20A003 */  daddu      $4, $29, $0
    /* 5B00C 0015B00C A6FF080C */  jal        sceVu0Normalize
    /* 5B010 0015B010 2D28A003 */   daddu     $5, $29, $0
    /* 5B014 0015B014 2D200002 */  daddu      $4, $16, $0
    /* 5B018 0015B018 2E1A040C */  jal        dispPlane
    /* 5B01C 0015B01C 2D28A003 */   daddu     $5, $29, $0
    /* 5B020 0015B020 09000010 */  b          .L0015B048
    /* 5B024 0015B024 2000BFDF */   ld        $31, 0x20($29)
.align 2
  .L0015B028:
    /* 5B028 0015B028 FEFF0324 */  addiu      $3, $0, -0x2
    /* 5B02C 0015B02C 381C0300 */  dsll       $3, $3, 16
    /* 5B030 0015B030 FFFF6334 */  ori        $3, $3, 0xFFFF
    /* 5B034 0015B034 381C0300 */  dsll       $3, $3, 16
    /* 5B038 0015B038 FFFF6334 */  ori        $3, $3, 0xFFFF
    /* 5B03C 0015B03C 24104300 */  and        $2, $2, $3
    /* 5B040 0015B040 B80082FC */  sd         $2, 0xB8($4)
    /* 5B044 0015B044 2000BFDF */  ld         $31, 0x20($29)
.align 2
  .L0015B048:
    /* 5B048 0015B048 1000B0DF */  ld         $16, 0x10($29)
    /* 5B04C 0015B04C 0800E003 */  jr         $31
    /* 5B050 0015B050 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_0015AF10
    /* 5B054 0015B054 00000000 */  nop
```
