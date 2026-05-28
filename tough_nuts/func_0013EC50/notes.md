# func_0013EC50 — parked

VRAM: 0x0013EC50 (file_off 0x03EC50)
Asm source: asm/nonmatchings/isys/gobj/func_0013EC50.s

## Attempt at 2026-05-28

**Reason parked:** rc ~5-6 (clean structure, v1/a1 regalloc swap residual). REQUIRES -fno-strength-reduce (per-file: 'GOBJ -fno-strength-reduce' in extra_cflags) -- the original recomputes base+i*0x174 via MULT each iteration (NOT strength-reduced to a pointer walk like sibling func_0013ECA8). Int-indexed (i), unsigned count (D_00633CA4) so guard is beqz (0<n => n!=0); loop test sltu i<n. Returns first elem (stride 0x174, base=D_00633CA0) where unk0!=0 && unk4==key, else 0. SOLVED structure via: unsigned count -> beqz guard; goto-ret0 so the LOOP stays inline + return-0 out of line (plain if(n==0)return0 inverts to bne-loop-out-of-line); pins count=$8/i=$6/base=$7; stride pinned $2(v0) AND assigned INSIDE the loop (stride=0x174 each iter) so v0 is reloaded each iteration after field4 (lw v0,4) clobbers it -- matches the original's 'addiu $2,0x174' in the bnez delay. RESIDUAL (permuter food): v1<->a1 swap on the mult-result (i*stride) vs elem pointer -- expected mult->v1/elem->a1, built mult->a1/elem->v1. off=$3 pin not honored (mult reg picked before coalesce); e=$5 pin forces a daddu copy; dual-pin worse. Plus i=0 (daddu a2) wants the beq-guard delay slot but lands after the base load. Pure regalloc/sched -> permuter (seed needs CFLAGS with -fno-strength-reduce).

**TU:** `isys/gobj.c`

**Seed:** `tough_nuts/func_0013EC50/func_0013EC50.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00633CA0, 1
.extern D_00633CA4, 1

.align 3
nonmatching func_0013EC50, 0x54

glabel func_0013EC50
    /* 3EC50 0013EC50 B4B3888F */  lw         $8, (D_00633CA4) /* gp_rel: (D_00633CA4) */
    /* 3EC54 0013EC54 11000011 */  beqz       $8, .L0013EC9C
    /* 3EC58 0013EC58 2D300000 */   daddu     $6, $0, $0
    /* 3EC5C 0013EC5C B0B3878F */  lw         $7, (D_00633CA0) /* gp_rel: (D_00633CA0) */
    /* 3EC60 0013EC60 74010224 */  addiu      $2, $0, 0x174
    /* 3EC64 0013EC64 00000000 */  nop
.align 2
  .L0013EC68:
    /* 3EC68 0013EC68 1818C200 */  mult       $3, $6, $2
    /* 3EC6C 0013EC6C 21286700 */  addu       $5, $3, $7
    /* 3EC70 0013EC70 0000A38C */  lw         $3, 0x0($5)
    /* 3EC74 0013EC74 06006010 */  beqz       $3, .L0013EC90
    /* 3EC78 0013EC78 0100C624 */   addiu     $6, $6, 0x1
    /* 3EC7C 0013EC7C 0400A28C */  lw         $2, 0x4($5)
    /* 3EC80 0013EC80 04004414 */  bne        $2, $4, .L0013EC94
    /* 3EC84 0013EC84 2B10C800 */   sltu      $2, $6, $8
    /* 3EC88 0013EC88 0800E003 */  jr         $31
    /* 3EC8C 0013EC8C 2D10A000 */   daddu     $2, $5, $0
.align 2
  .L0013EC90:
    /* 3EC90 0013EC90 2B10C800 */  sltu       $2, $6, $8
.align 2
  .L0013EC94:
    /* 3EC94 0013EC94 F4FF4014 */  bnez       $2, .L0013EC68
    /* 3EC98 0013EC98 74010224 */   addiu     $2, $0, 0x174
.align 2
  .L0013EC9C:
    /* 3EC9C 0013EC9C 0800E003 */  jr         $31
    /* 3ECA0 0013ECA0 2D100000 */   daddu     $2, $0, $0
endlabel func_0013EC50
    /* 3ECA4 0013ECA4 00000000 */  nop
```
