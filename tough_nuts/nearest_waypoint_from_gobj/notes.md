# nearest_waypoint_from_gobj — parked

VRAM: 0x00177990 (file_off 0x077990)
Asm source: asm/aug6/nonmatchings/fumi/src/way_util/nearest_waypoint_from_gobj.s

## Attempt at 2026-06-29

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=49). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/way_util.c`

**Seed:** `tough_nuts/nearest_waypoint_from_gobj/nearest_waypoint_from_gobj.c`

Disassembly:

```
.align 3
nonmatching nearest_waypoint_from_gobj, 0x154

glabel nearest_waypoint_from_gobj
    /* 77990 00177990 34000B24 */  addiu      $11, $0, 0x34
    /* 77994 00177994 4C00023C */  lui        $2, %hi(D_004C6FF0)
    /* 77998 00177998 1848CB00 */  mult       $9, $6, $11
    /* 7799C 0017799C F06F4724 */  addiu      $7, $2, %lo(D_004C6FF0)
    /* 779A0 001779A0 2D508000 */  daddu      $10, $4, $0
    /* 779A4 001779A4 2110E900 */  addu       $2, $7, $9
    /* 779A8 001779A8 1800438C */  lw         $3, 0x18($2)
    /* 779AC 001779AC 06006010 */  beqz       $3, .L001779C8
    /* 779B0 001779B0 2D40A000 */   daddu     $8, $5, $0
    /* 779B4 001779B4 01000224 */  addiu      $2, $0, 0x1
    /* 779B8 001779B8 29006210 */  beq        $3, $2, .L00177A60
    /* 779BC 001779BC 21302701 */   addu      $6, $9, $7
    /* 779C0 001779C0 0800E003 */  jr         $31
    /* 779C4 001779C4 00000000 */   nop
.align 2
  .L001779C8:
    /* 779C8 001779C8 18100B01 */  mult       $2, $8, $11
    /* 779CC 001779CC 4C00083C */  lui        $8, %hi(D_004C7CF0)
    /* 779D0 001779D0 21284700 */  addu       $5, $2, $7
    /* 779D4 001779D4 2000A48C */  lw         $4, 0x20($5)
    /* 779D8 001779D8 F07C0725 */  addiu      $7, $8, %lo(D_004C7CF0)
    /* 779DC 001779DC 80110400 */  sll        $2, $4, 6
    /* 779E0 001779E0 21104700 */  addu       $2, $2, $7
    /* 779E4 001779E4 2000438C */  lw         $3, 0x20($2)
    /* 779E8 001779E8 08006610 */  beq        $3, $6, .L00177A0C
    /* 779EC 001779EC 2D184000 */   daddu     $3, $2, $0
    /* 779F0 001779F0 2400A28C */  lw         $2, 0x24($5)
    /* 779F4 001779F4 80110200 */  sll        $2, $2, 6
    /* 779F8 001779F8 21104700 */  addu       $2, $2, $7
    /* 779FC 001779FC 2000438C */  lw         $3, 0x20($2)
    /* 77A00 00177A00 26186600 */  xor        $3, $3, $6
    /* 77A04 00177A04 0B100300 */  movn       $2, $0, $3
    /* 77A08 00177A08 2D184000 */  daddu      $3, $2, $0
.align 2
  .L00177A0C:
    /* 77A0C 00177A0C 80110400 */  sll        $2, $4, 6
    /* 77A10 00177A10 040043AD */  sw         $3, 0x4($10)
    /* 77A14 00177A14 F07C0425 */  addiu      $4, $8, %lo(D_004C7CF0)
    /* 77A18 00177A18 21104400 */  addu       $2, $2, $4
    /* 77A1C 00177A1C 2000428C */  lw         $2, 0x20($2)
    /* 77A20 00177A20 03004654 */  bnel       $2, $6, .L00177A30
    /* 77A24 00177A24 2400A28C */   lw        $2, 0x24($5)
    /* 77A28 00177A28 07000010 */  b          .L00177A48
    /* 77A2C 00177A2C 0800A78C */   lw        $7, 0x8($5)
.align 2
  .L00177A30:
    /* 77A30 00177A30 80110200 */  sll        $2, $2, 6
    /* 77A34 00177A34 21104400 */  addu       $2, $2, $4
    /* 77A38 00177A38 2000438C */  lw         $3, 0x20($2)
    /* 77A3C 00177A3C 02006614 */  bne        $3, $6, .L00177A48
    /* 77A40 00177A40 2D380000 */   daddu     $7, $0, $0
    /* 77A44 00177A44 0C00A78C */  lw         $7, 0xC($5)
.align 2
  .L00177A48:
    /* 77A48 00177A48 5500043C */  lui        $4, %hi(D_00554128)
    /* 77A4C 00177A4C 0400458D */  lw         $5, 0x4($10)
    /* 77A50 00177A50 28418424 */  addiu      $4, $4, %lo(D_00554128)
    /* 77A54 00177A54 2D30E000 */  daddu      $6, $7, $0
    /* 77A58 00177A58 F2900608 */  j          debug_assertMessage
    /* 77A5C 00177A5C 080047AD */   sw        $7, 0x8($10)
.align 2
  .L00177A60:
    /* 77A60 00177A60 2000C58C */  lw         $5, 0x20($6)
    /* 77A64 00177A64 4C00093C */  lui        $9, %hi(D_004C7CF0)
    /* 77A68 00177A68 F07C2725 */  addiu      $7, $9, %lo(D_004C7CF0)
    /* 77A6C 00177A6C 80110500 */  sll        $2, $5, 6
    /* 77A70 00177A70 21104700 */  addu       $2, $2, $7
    /* 77A74 00177A74 2000438C */  lw         $3, 0x20($2)
    /* 77A78 00177A78 03006854 */  bnel       $3, $8, .L00177A88
    /* 77A7C 00177A7C 2400C28C */   lw        $2, 0x24($6)
    /* 77A80 00177A80 07000010 */  b          .L00177AA0
    /* 77A84 00177A84 0800C48C */   lw        $4, 0x8($6)
.align 2
  .L00177A88:
    /* 77A88 00177A88 80110200 */  sll        $2, $2, 6
    /* 77A8C 00177A8C 21104700 */  addu       $2, $2, $7
    /* 77A90 00177A90 2000438C */  lw         $3, 0x20($2)
    /* 77A94 00177A94 02006814 */  bne        $3, $8, .L00177AA0
    /* 77A98 00177A98 2D200000 */   daddu     $4, $0, $0
    /* 77A9C 00177A9C 0C00C48C */  lw         $4, 0xC($6)
.align 2
  .L00177AA0:
    /* 77AA0 00177AA0 80110500 */  sll        $2, $5, 6
    /* 77AA4 00177AA4 F07C2325 */  addiu      $3, $9, %lo(D_004C7CF0)
    /* 77AA8 00177AA8 21284300 */  addu       $5, $2, $3
    /* 77AAC 00177AAC 040044AD */  sw         $4, 0x4($10)
    /* 77AB0 00177AB0 2000A28C */  lw         $2, 0x20($5)
    /* 77AB4 00177AB4 03004854 */  bnel       $2, $8, .L00177AC4
    /* 77AB8 00177AB8 2400C28C */   lw        $2, 0x24($6)
    /* 77ABC 00177ABC 07000010 */  b          .L00177ADC
    /* 77AC0 00177AC0 2D10A000 */   daddu     $2, $5, $0
.align 2
  .L00177AC4:
    /* 77AC4 00177AC4 80110200 */  sll        $2, $2, 6
    /* 77AC8 00177AC8 21284300 */  addu       $5, $2, $3
    /* 77ACC 00177ACC 2000A38C */  lw         $3, 0x20($5)
    /* 77AD0 00177AD0 2D100000 */  daddu      $2, $0, $0
    /* 77AD4 00177AD4 26186800 */  xor        $3, $3, $8
    /* 77AD8 00177AD8 0A10A300 */  movz       $2, $5, $3
.align 2
  .L00177ADC:
    /* 77ADC 00177ADC 0800E003 */  jr         $31
    /* 77AE0 00177AE0 080042AD */   sw        $2, 0x8($10)
endlabel nearest_waypoint_from_gobj
    /* 77AE4 00177AE4 00000000 */  nop
```
