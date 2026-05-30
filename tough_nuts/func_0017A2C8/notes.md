# func_0017A2C8 — parked

VRAM: 0x0017A2C8 (file_off 0x07A2C8)
Asm source: asm/nonmatchings/src/way_util/func_0017A2C8.s

## Attempt at 2026-05-30

**Reason parked:** rc2 (lwc1 $f20,D_00630E40 / move s1,v0 scheduling: orig has lwc1 immediately after jal+nop, gcc puts move s1,v0 first then lwc1 last). Tried: extern alias, attribute((section(.sdata))), volatile load, statement reorder (best=D_X before/after call), KEEP_LIVE_FP. None flip the gcc scheduling. Floor is at rc2 — structural issue with how gcc places the gp_rel load relative to the v0->callee-save move. Note: relocation type also differs (orig: bare D_X+0; built: .sdata.D_X+0x4000) due to -fdata-sections per-symbol sections, but linked ELF offsets match (-0x7AB0(gp)). Loop pattern is otherwise correct — sibling func_0017A230 (matched) uses identical shape with 100000.0f literal instead of D_00630E40 gp_rel.

**TU:** `src/way_util.c`

**Seed:** `tough_nuts/func_0017A2C8/func_0017A2C8.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00630E40, 1
.extern D_00633874, 1

.align 3
nonmatching func_0017A2C8, 0x9C

glabel func_0017A2C8
    /* 7A2C8 0017A2C8 A0FFBD27 */  addiu      $29, $29, -0x60
    /* 7A2CC 0017A2CC 3000B2FF */  sd         $18, 0x30($29)
    /* 7A2D0 0017A2D0 2D908000 */  daddu      $18, $4, $0
    /* 7A2D4 0017A2D4 2000B1FF */  sd         $17, 0x20($29)
    /* 7A2D8 0017A2D8 84AF848F */  lw         $4, (D_00633874) /* gp_rel: (D_00633874) */
    /* 7A2DC 0017A2DC 1000B0FF */  sd         $16, 0x10($29)
    /* 7A2E0 0017A2E0 5000B4E7 */  swc1       $f20, 0x50($29)
    /* 7A2E4 0017A2E4 4000BFFF */  sd         $31, 0x40($29)
    /* 7A2E8 0017A2E8 9E16080C */  jal        func_00205A78
    /* 7A2EC 0017A2EC 00000000 */   nop
    /* 7A2F0 0017A2F0 508594C7 */  lwc1       $f20, (D_00630E40) /* gp_rel: (D_00630E40) */
    /* 7A2F4 0017A2F4 2D884000 */  daddu      $17, $2, $0
    /* 7A2F8 0017A2F8 12002012 */  beqz       $17, .L0017A344
    /* 7A2FC 0017A2FC 2D802002 */   daddu     $16, $17, $0
    /* 7A300 0017A300 2D20A003 */  daddu      $4, $29, $0
    /* 7A304 0017A304 00000000 */  nop
.align 2
  .L0017A308:
    /* 7A308 0017A308 10000526 */  addiu      $5, $16, 0x10
    /* 7A30C 0017A30C BA0E090C */  jal        func_00243AE8
    /* 7A310 0017A310 2D304002 */   daddu     $6, $18, $0
    /* 7A314 0017A314 BEA8050C */  jal        func_0016A2F8
    /* 7A318 0017A318 2D20A003 */   daddu     $4, $29, $0
    /* 7A31C 0017A31C 34001446 */  c.lt.s     $f0, $f20
    /* 7A320 0017A320 03000045 */  bc1f       .L0017A330
    /* 7A324 0017A324 00000000 */   nop
    /* 7A328 0017A328 06050046 */  mov.s      $f20, $f0
    /* 7A32C 0017A32C 2D880002 */  daddu      $17, $16, $0
.align 2
  .L0017A330:
    /* 7A330 0017A330 A616080C */  jal        func_00205A98
    /* 7A334 0017A334 2D200002 */   daddu     $4, $16, $0
    /* 7A338 0017A338 2D804000 */  daddu      $16, $2, $0
    /* 7A33C 0017A33C F2FF0056 */  bnel       $16, $0, .L0017A308
    /* 7A340 0017A340 2D20A003 */   daddu     $4, $29, $0
.align 2
  .L0017A344:
    /* 7A344 0017A344 2D102002 */  daddu      $2, $17, $0
    /* 7A348 0017A348 4000BFDF */  ld         $31, 0x40($29)
    /* 7A34C 0017A34C 3000B2DF */  ld         $18, 0x30($29)
    /* 7A350 0017A350 2000B1DF */  ld         $17, 0x20($29)
    /* 7A354 0017A354 1000B0DF */  ld         $16, 0x10($29)
    /* 7A358 0017A358 5000B4C7 */  lwc1       $f20, 0x50($29)
    /* 7A35C 0017A35C 0800E003 */  jr         $31
    /* 7A360 0017A360 6000BD27 */   addiu     $29, $29, 0x60
endlabel func_0017A2C8
    /* 7A364 0017A364 00000000 */  nop
```
