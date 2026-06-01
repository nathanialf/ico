# func_0014A560 — parked

VRAM: 0x0014A560 (file_off 0x04A560)
Asm source: asm/nonmatchings/src/act-game/func_0014A560.s

## Attempt at 2026-05-31

**Reason parked:** genuine 35-stall (match_loop next=park, best=**rc8**, clean,
no pins). IMPROVED rc18->rc8 by hand-massaging the permuter's pinned rc8: the
beql/bnel branch-likely "wall" cracked (rv->$v0 direct field==1 return; load
p_15C in EACH state branch; entry base-fold). Equals the permuter's only sub-12
result with ZERO crutches. Residual rc8 = entry idx->$v1 load-dest/scheduler
tie. See seed header for the full lever chain.
goto-CFG seed (no crutches). Multi-crutch wall: (1) branch-likely beql/bnel
emission [uncontrollable per branch_likely_emission], (2) base/idx entry
scheduling [old MEM_BARRIER+REG($5)], (3) rv->$a2+move not $v0 [old REG($2)].
~30 distinct clean shapes plateau at rc18. See seed header for full lever log.

**TU:** `src/act-game.c`

**Seed:** `tough_nuts/func_0014A560/func_0014A560.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00631AE4, 1

.align 3
nonmatching func_0014A560, 0x60

glabel func_0014A560
    /* 4A560 0014A560 F491848F */  lw         $4, (D_00631AE4) /* gp_rel: (D_00631AE4) */
    /* 4A564 0014A564 13008010 */  beqz       $4, .L0014A5B4
    /* 4A568 0014A568 4B000324 */   addiu     $3, $0, 0x4B
    /* 4A56C 0014A56C 6401828C */  lw         $2, 0x164($4)
    /* 4A570 0014A570 3000458C */  lw         $5, 0x30($2)
    /* 4A574 0014A574 0500A350 */  beql       $5, $3, .L0014A58C
    /* 4A578 0014A578 5C01828C */   lw        $2, 0x15C($4)
    /* 4A57C 0014A57C 55000224 */  addiu      $2, $0, 0x55
    /* 4A580 0014A580 0D00A254 */  bnel       $5, $2, .L0014A5B8
    /* 4A584 0014A584 2D100000 */   daddu     $2, $0, $0
    /* 4A588 0014A588 5C01828C */  lw         $2, 0x15C($4)
.align 2
  .L0014A58C:
    /* 4A58C 0014A58C 5600053C */  lui        $5, %hi(D_00565060)
    /* 4A590 0014A590 90010424 */  addiu      $4, $0, 0x190
    /* 4A594 0014A594 6050A524 */  addiu      $5, $5, %lo(D_00565060)
    /* 4A598 0014A598 A004438C */  lw         $3, 0x4A0($2)
    /* 4A59C 0014A59C 01000624 */  addiu      $6, $0, 0x1
    /* 4A5A0 0014A5A0 18186400 */  mult       $3, $3, $4
    /* 4A5A4 0014A5A4 2128A300 */  addu       $5, $5, $3
    /* 4A5A8 0014A5A8 5C01A48C */  lw         $4, 0x15C($5)
    /* 4A5AC 0014A5AC 02008610 */  beq        $4, $6, .L0014A5B8
    /* 4A5B0 0014A5B0 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L0014A5B4:
    /* 4A5B4 0014A5B4 2D100000 */  daddu      $2, $0, $0
.align 2
  .L0014A5B8:
    /* 4A5B8 0014A5B8 0800E003 */  jr         $31
    /* 4A5BC 0014A5BC 00000000 */   nop
endlabel func_0014A560
```


## Permuter harvest 2026-05-31 (5-min shot)
Best output rc8 (vs parked rc18) but it REQUIRES `register int rv asm("$2")`
(the rv->$v0 pin) — and even then the beql/bnel branch-likely diffs remain
(rc8, not 0). Its clean structural ideas (read player+0x164 once into a shared
var, RE-READ *(new_var+0x30) for the 0x55 check, sub loaded once at a shared
have_sub) applied WITHOUT the pin give rc18 — no change. So the branch-likely
emission is the dominant wall; the rv pin has no clean massage that helps here.
Clean floor stays rc18.