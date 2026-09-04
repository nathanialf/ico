# nearest_waypoint_by_lineseg_from_gobj — parked

VRAM: 0x00177EE8 (file_off 0x077EE8)
Asm source: asm/aug6/nonmatchings/fumi/src/way_util/nearest_waypoint_by_lineseg_from_gobj.s

## Attempt at 2026-07-06

**Reason parked:** permuter-class fold-blocker rc10; 4 sigs (10/12/14/20), local-vs-param homing tie hand-exhausted; queued for permuter

**TU:** `fumi/src/way_util.c`

**Seed:** `tough_nuts/nearest_waypoint_by_lineseg_from_gobj/nearest_waypoint_by_lineseg_from_gobj.c`

Disassembly:

```
.align 3
nonmatching nearest_waypoint_by_lineseg_from_gobj, 0xA4

glabel nearest_waypoint_by_lineseg_from_gobj
    /* 77EE8 00177EE8 90FFBD27 */  addiu      $29, $29, -0x70
    /* 77EEC 00177EEC 2D288000 */  daddu      $5, $4, $0
    /* 77EF0 00177EF0 4000B2FF */  sd         $18, 0x40($29)
    /* 77EF4 00177EF4 3000B1FF */  sd         $17, 0x30($29)
    /* 77EF8 00177EF8 2000B0FF */  sd         $16, 0x20($29)
    /* 77EFC 00177EFC 6000B4E7 */  swc1       $f20, 0x60($29)
    /* 77F00 00177F00 5000BFFF */  sd         $31, 0x50($29)
    /* 77F04 00177F04 C210040C */  jal        GetRootMatrixByDObj
    /* 77F08 00177F08 2D20A003 */   daddu     $4, $29, $0
    /* 77F0C 00177F0C 408594C7 */  lwc1       $f20, %gp_rel(D_00629130)($28)
    /* 77F10 00177F10 8CAF848F */  lw         $4, %gp_rel(D_0062BB7C)($28)
    /* 77F14 00177F14 B80B080C */  jal        WayPointList_begin
    /* 77F18 00177F18 2D90A003 */   daddu     $18, $29, $0
    /* 77F1C 00177F1C 2D884000 */  daddu      $17, $2, $0
    /* 77F20 00177F20 12002012 */  beqz       $17, .L00177F6C
    /* 77F24 00177F24 2D802002 */   daddu     $16, $17, $0
    /* 77F28 00177F28 1000A427 */  addiu      $4, $29, 0x10
    /* 77F2C 00177F2C 00000000 */  nop
.align 2
  .L00177F30:
    /* 77F30 00177F30 10000526 */  addiu      $5, $16, 0x10
    /* 77F34 00177F34 0200090C */  jal        sceVu0SubVector
    /* 77F38 00177F38 2D304002 */   daddu     $6, $18, $0
    /* 77F3C 00177F3C 4AA0050C */  jal        func_00168128
    /* 77F40 00177F40 1000A427 */   addiu     $4, $29, 0x10
    /* 77F44 00177F44 34001446 */  c.lt.s     $f0, $f20
    /* 77F48 00177F48 03000045 */  bc1f       .L00177F58
    /* 77F4C 00177F4C 00000000 */   nop
    /* 77F50 00177F50 06050046 */  mov.s      $f20, $f0
    /* 77F54 00177F54 2D880002 */  daddu      $17, $16, $0
.align 2
  .L00177F58:
    /* 77F58 00177F58 C00B080C */  jal        WayPointList_next
    /* 77F5C 00177F5C 2D200002 */   daddu     $4, $16, $0
    /* 77F60 00177F60 2D804000 */  daddu      $16, $2, $0
    /* 77F64 00177F64 F2FF0056 */  bnel       $16, $0, .L00177F30
    /* 77F68 00177F68 1000A427 */   addiu     $4, $29, 0x10
.align 2
  .L00177F6C:
    /* 77F6C 00177F6C 2D102002 */  daddu      $2, $17, $0
    /* 77F70 00177F70 5000BFDF */  ld         $31, 0x50($29)
    /* 77F74 00177F74 4000B2DF */  ld         $18, 0x40($29)
    /* 77F78 00177F78 3000B1DF */  ld         $17, 0x30($29)
    /* 77F7C 00177F7C 2000B0DF */  ld         $16, 0x20($29)
    /* 77F80 00177F80 6000B4C7 */  lwc1       $f20, 0x60($29)
    /* 77F84 00177F84 0800E003 */  jr         $31
    /* 77F88 00177F88 7000BD27 */   addiu     $29, $29, 0x70
endlabel nearest_waypoint_by_lineseg_from_gobj
    /* 77F8C 00177F8C 00000000 */  nop
```
