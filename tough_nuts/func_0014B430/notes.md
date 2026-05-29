# func_0014B430 — parked

VRAM: 0x0014B430 (file_off 0x04B430)
Asm source: asm/nonmatchings/src/act-parallel-control/func_0014B430.s

## Attempt at 2026-05-29

**Reason parked:** best rc17 (28->17 hand). Frame-range/anim-active check; sibling func_00149EF8 (act-game.c) matched w/ same D_00565060 table (0x190 stride, short fields 0x180/0x182, obj=self->0x15C, idx=obj->0x4A0, time=obj->0x4AC float). Residual = regalloc coalescing: orig reuses a1 for BOTH reload-base obj-copy (daddu a1,a2) AND the -1 const, forcing non-coalesce + beql-reload-in-delay + idx-in-v0-clobbered-then-reload. Levers that helped: struct-cast keeps 0x180 offset on lh (not basefold), stride pin n=$4 (400 reuses dead self a0), obj pin $6=a2, volatile thresh forces obj->0x4AC reload. Tried & failed: volatile/MEM_BARRIER on idx (rc30 overfence), q-ptr pin a1 (coalesces), goto-split reloads (rc30), r5 reuse reload-base+-1 (rc20). PERMUTER: needs a1-reuse coalescing the hand pins can't produce.

**TU:** `src/act-parallel-control.c`

**Seed:** `tough_nuts/func_0014B430/func_0014B430.c`

Disassembly:

```
.align 3
nonmatching func_0014B430, 0x98

glabel func_0014B430
    /* 4B430 0014B430 5C01868C */  lw         $6, 0x15C($4)
    /* 4B434 0014B434 5600073C */  lui        $7, %hi(D_00565060)
    /* 4B438 0014B438 90010424 */  addiu      $4, $0, 0x190
    /* 4B43C 0014B43C 6050E324 */  addiu      $3, $7, %lo(D_00565060)
    /* 4B440 0014B440 A004C28C */  lw         $2, 0x4A0($6)
    /* 4B444 0014B444 AC04C1C4 */  lwc1       $f1, 0x4AC($6)
    /* 4B448 0014B448 18104400 */  mult       $2, $2, $4
    /* 4B44C 0014B44C 21104300 */  addu       $2, $2, $3
    /* 4B450 0014B450 80014384 */  lh         $3, 0x180($2)
    /* 4B454 0014B454 00008344 */  mtc1       $3, $f0
    /* 4B458 0014B458 20008046 */  cvt.s.w    $f0, $f0
    /* 4B45C 0014B45C 34000146 */  c.lt.s     $f0, $f1
    /* 4B460 0014B460 00000000 */  nop
    /* 4B464 0014B464 06000045 */  bc1f       .L0014B480
    /* 4B468 0014B468 2D28C000 */   daddu     $5, $6, $0
    /* 4B46C 0014B46C FFFF0224 */  addiu      $2, $0, -0x1
    /* 4B470 0014B470 04006250 */  beql       $3, $2, .L0014B484
    /* 4B474 0014B474 A004A38C */   lw        $3, 0x4A0($5)
    /* 4B478 0014B478 0800E003 */  jr         $31
    /* 4B47C 0014B47C 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L0014B480:
    /* 4B480 0014B480 A004A38C */  lw         $3, 0x4A0($5)
.align 2
  .L0014B484:
    /* 4B484 0014B484 90010224 */  addiu      $2, $0, 0x190
    /* 4B488 0014B488 6050E424 */  addiu      $4, $7, %lo(D_00565060)
    /* 4B48C 0014B48C FFFF0524 */  addiu      $5, $0, -0x1
    /* 4B490 0014B490 18186200 */  mult       $3, $3, $2
    /* 4B494 0014B494 21186400 */  addu       $3, $3, $4
    /* 4B498 0014B498 82016384 */  lh         $3, 0x182($3)
    /* 4B49C 0014B49C 08006510 */  beq        $3, $5, .L0014B4C0
    /* 4B4A0 0014B4A0 2D100000 */   daddu     $2, $0, $0
    /* 4B4A4 0014B4A4 00088344 */  mtc1       $3, $f1
    /* 4B4A8 0014B4A8 60088046 */  cvt.s.w    $f1, $f1
    /* 4B4AC 0014B4AC AC04C0C4 */  lwc1       $f0, 0x4AC($6)
    /* 4B4B0 0014B4B0 34000146 */  c.lt.s     $f0, $f1
    /* 4B4B4 0014B4B4 00000000 */  nop
    /* 4B4B8 0014B4B8 01000345 */  bc1tl      .L0014B4C0
    /* 4B4BC 0014B4BC 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L0014B4C0:
    /* 4B4C0 0014B4C0 0800E003 */  jr         $31
    /* 4B4C4 0014B4C4 00000000 */   nop
endlabel func_0014B430
```

---

## Attempt at 2026-05-29

**Reason parked:** Resumed at rc17 (parker's count); 30-stall hand grind w/ 30 distinct hypotheses (idx pin, obj2 pin/anchor, base  pin, single-return goto, alias D_X, ANCHOR(idx), volatile idx, KEEP_LIVE(obj/n), commute mult, struct index access, e1/e2 ptrs, sizeof(_ECtlB), v pin , raw deref, decl reorder, etc.) - none cracked rc17. Parker's diagnosis confirmed: orig reuses  for BOTH obj-copy and -1 const via coalescing the hand pins cannot produce. Permuter territory.

**TU:** `src/act-parallel-control.c`

**Seed:** `tough_nuts/func_0014B430/func_0014B430.1.c`

Disassembly:

```
.align 3
nonmatching func_0014B430, 0x98

glabel func_0014B430
    /* 4B430 0014B430 5C01868C */  lw         $6, 0x15C($4)
    /* 4B434 0014B434 5600073C */  lui        $7, %hi(D_00565060)
    /* 4B438 0014B438 90010424 */  addiu      $4, $0, 0x190
    /* 4B43C 0014B43C 6050E324 */  addiu      $3, $7, %lo(D_00565060)
    /* 4B440 0014B440 A004C28C */  lw         $2, 0x4A0($6)
    /* 4B444 0014B444 AC04C1C4 */  lwc1       $f1, 0x4AC($6)
    /* 4B448 0014B448 18104400 */  mult       $2, $2, $4
    /* 4B44C 0014B44C 21104300 */  addu       $2, $2, $3
    /* 4B450 0014B450 80014384 */  lh         $3, 0x180($2)
    /* 4B454 0014B454 00008344 */  mtc1       $3, $f0
    /* 4B458 0014B458 20008046 */  cvt.s.w    $f0, $f0
    /* 4B45C 0014B45C 34000146 */  c.lt.s     $f0, $f1
    /* 4B460 0014B460 00000000 */  nop
    /* 4B464 0014B464 06000045 */  bc1f       .L0014B480
    /* 4B468 0014B468 2D28C000 */   daddu     $5, $6, $0
    /* 4B46C 0014B46C FFFF0224 */  addiu      $2, $0, -0x1
    /* 4B470 0014B470 04006250 */  beql       $3, $2, .L0014B484
    /* 4B474 0014B474 A004A38C */   lw        $3, 0x4A0($5)
    /* 4B478 0014B478 0800E003 */  jr         $31
    /* 4B47C 0014B47C 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L0014B480:
    /* 4B480 0014B480 A004A38C */  lw         $3, 0x4A0($5)
.align 2
  .L0014B484:
    /* 4B484 0014B484 90010224 */  addiu      $2, $0, 0x190
    /* 4B488 0014B488 6050E424 */  addiu      $4, $7, %lo(D_00565060)
    /* 4B48C 0014B48C FFFF0524 */  addiu      $5, $0, -0x1
    /* 4B490 0014B490 18186200 */  mult       $3, $3, $2
    /* 4B494 0014B494 21186400 */  addu       $3, $3, $4
    /* 4B498 0014B498 82016384 */  lh         $3, 0x182($3)
    /* 4B49C 0014B49C 08006510 */  beq        $3, $5, .L0014B4C0
    /* 4B4A0 0014B4A0 2D100000 */   daddu     $2, $0, $0
    /* 4B4A4 0014B4A4 00088344 */  mtc1       $3, $f1
    /* 4B4A8 0014B4A8 60088046 */  cvt.s.w    $f1, $f1
    /* 4B4AC 0014B4AC AC04C0C4 */  lwc1       $f0, 0x4AC($6)
    /* 4B4B0 0014B4B0 34000146 */  c.lt.s     $f0, $f1
    /* 4B4B4 0014B4B4 00000000 */  nop
    /* 4B4B8 0014B4B8 01000345 */  bc1tl      .L0014B4C0
    /* 4B4BC 0014B4BC 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L0014B4C0:
    /* 4B4C0 0014B4C0 0800E003 */  jr         $31
    /* 4B4C4 0014B4C4 00000000 */   nop
endlabel func_0014B430
```
