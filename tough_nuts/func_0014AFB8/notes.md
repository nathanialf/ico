# func_0014AFB8 — parked

VRAM: 0x0014AFB8 (file_off 0x04AFB8)
Asm source: asm/nonmatchings/src/act-parallel-control/func_0014AFB8.s

## Attempt at 2026-05-31

**Reason parked:** rc6 search-loop near-miss. for-loop over D_006AA4B0 (count at +0x4B0), return matching entry's u8 at +0x320. count-first decl gets base->v0 correct; residual: ROM loads count->v1 (for blez) then COPIES to loop-bound a2 (reusing v1 for ptr) + schedules i=0 AFTER blez, while gcc loads count straight to a2 + hoists i=0 early. Pure allocation/scheduling tie-break; lever.py reorder sweep (all 6 orderings of the 3 decls) confirms rc6 is the source-order floor. for/do-while/while + explicit-base all tried. Needs permuter/alloc lever. stall 5, NOT a floor.

**TU:** `src/act-parallel-control.c`

**Seed:** `tough_nuts/func_0014AFB8/func_0014AFB8.c`

Disassembly:

```
.align 3
nonmatching func_0014AFB8, 0x48

glabel func_0014AFB8
    /* 4AFB8 0014AFB8 6B00023C */  lui        $2, %hi(D_006AA4B0)
    /* 4AFBC 0014AFBC B0A44224 */  addiu      $2, $2, %lo(D_006AA4B0)
    /* 4AFC0 0014AFC0 B004438C */  lw         $3, 0x4B0($2)
    /* 4AFC4 0014AFC4 0C006018 */  blez       $3, .L0014AFF8
    /* 4AFC8 0014AFC8 2D200000 */   daddu     $4, $0, $0
    /* 4AFCC 0014AFCC 2D306000 */  daddu      $6, $3, $0
    /* 4AFD0 0014AFD0 2D184000 */  daddu      $3, $2, $0
    /* 4AFD4 0014AFD4 00000000 */  nop
.align 2
  .L0014AFD8:
    /* 4AFD8 0014AFD8 0000628C */  lw         $2, 0x0($3)
    /* 4AFDC 0014AFDC 03004514 */  bne        $2, $5, .L0014AFEC
    /* 4AFE0 0014AFE0 01008424 */   addiu     $4, $4, 0x1
    /* 4AFE4 0014AFE4 0800E003 */  jr         $31
    /* 4AFE8 0014AFE8 20036290 */   lbu       $2, 0x320($3)
.align 2
  .L0014AFEC:
    /* 4AFEC 0014AFEC 2A108600 */  slt        $2, $4, $6
    /* 4AFF0 0014AFF0 F9FF4014 */  bnez       $2, .L0014AFD8
    /* 4AFF4 0014AFF4 04006324 */   addiu     $3, $3, 0x4
.align 2
  .L0014AFF8:
    /* 4AFF8 0014AFF8 0800E003 */  jr         $31
    /* 4AFFC 0014AFFC 2D100000 */   daddu     $2, $0, $0
endlabel func_0014AFB8
```
