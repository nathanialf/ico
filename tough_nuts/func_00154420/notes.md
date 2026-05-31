# func_00154420 — parked

VRAM: 0x00154420 (file_off 0x054420)
Asm source: asm/matchings/cod/054420/func_00154420.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/boyact.c`

**Seed:** `tough_nuts/func_00154420/func_00154420.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00631AE4, 1

.align 3
nonmatching func_00154420, 0x24

glabel func_00154420
    /* 54420 00154420 F491838F */  lw         $3, %gp_rel(D_00631AE4)($gp) /* gp_rel: (D_00631AE4) */
    /* 54424 00154424 6401648C */  lw         $4, 0x164($3)
    /* 54428 00154428 3000848C */  lw         $4, 0x30($4)
    /* 5442C 0015442C 5D00832C */  sltiu      $3, $4, 0x5D
    /* 54430 00154430 02006010 */  beqz       $3, .L0015443C
    /* 54434 00154434 01000224 */   addiu     $2, $0, 0x1
    /* 54438 00154438 5B00822C */  sltiu      $2, $4, 0x5B
.align 2
  .L0015443C:
    /* 5443C 0015443C 0800E003 */  jr         $31
    /* 54440 00154440 00000000 */   nop
endlabel func_00154420
```

## 2026-05-31 near-miss (§3.1 movn, NOT a floor)
Shape: `unsigned int v=*(int*)(*(int*)(D_00631AE4+0x164)+0x30); ret=1; if(v<0x5D) ret=(v<0x5B); return ret;`
single-return form -> gcc if-converts to sltu/sltiu/MOVN (built) vs expected BRANCH (beq v1,0;v0=1 in delay;sltiu fallthrough).
two-return goto forms branch but bne+swapped layout + wrong regalloc (expected keeps v in a0, built v in v0/v1).
NEXT levers: defeat noce if-conversion (make THEN-block >1 insn, or value not 1-insn); force v into a0;
match expected single-jr+delay-slot-v0=1 exactly; permuter after 30-stall.

## 2026-05-31 (turn 5) — seed PROVES REG("$2") need; 7 clean forms fail
Parked seed's solution: two named ptr vars (v0=D_00631AE4, v1=v0[0x164/4], a=v1[0x30/4]) +
goto-end + `register int ret REG("$2")`. The $2 pin does DOUBLE DUTY: (a) reserves v0 for ret early
→ deref uses v1/a0 (expected regalloc), (b) defeats the movn if-conversion.
Clean forms tried (all fail to reproduce BOTH):
 - single-return goto-end (ret=1 default)        -> movn, base->v0
 - single-return goto-end, ret=1 BEFORE deref    -> movn, base->v0 (ret-first does NOT reserve v0)
 - two-return `if(a>=0x5D)return 1; return a<0x5B`-> bne+swapped, base->v0
 - two-return `if(a<0x5D)return a<0x5B; return 1` -> bne+swapped, base->v0
 - one intermediate ptr vs two named ptrs        -> no change
CONCLUSION: needs REG("$2") (retired). Two-returns defeat movn but give bne+base->v0; the $2 pin is
what cascades to beq + base->v1/value->a0. Clean source-shape NOT found in 7 forms. REG-pin-dependent
like camera-ico2($3). Permuter/offline candidate; or scoped-pin exception if user allows.

## Update 2026-05-31 (session resume, clean-C)

**rc7 is the clean floor — CONFIRMED.** The CORRECT structure is the multi-return
COMPLEMENT form (not the accumulator, which if-converts to movz/movn):
```c
int func_00154420(void) {
    unsigned int x = *(unsigned int *)(*(int *)(D_00631AE4 + 0x164) + 0x30);
    if (x >= 0x5D) { return 1; }
    return x < 0x5B;
}
```
This gives the exact `beq` (not bne) + `addiu v0,1` in the beq delay slot +
single exit. 6 distinct forms tried this session: multi-return-direct (bne, rc8),
accumulator-default-1 (movn if-conv, rc8), flip-complement (beq CORRECT, rc7),
named-sub (rc7), ret-first-override (movz if-conv, rc8), goto-CFG (movn, rc8).

**Residual (rc7) = pure chain register allocation:** built puts the
global→sub→x chain in v0 (then reuses v0 for the return), original RESERVES v0
for the return value and puts the chain in v1/a0 (`lw v1,0(gp); lw a0,356(v1);
lw a0,48(a0); sltiu v1,a0,93; beq v1,zero,T; sltiu v0,a0,91`). Unlike
func_0014B2F0 (cracked by multi-return), there is NO value-reuse (no shift base)
to extend v0's web, so the allocator won't reserve v0 for the short return web.
The now-INERT `REG("$2")` stub also reaches only rc7 → confirms no clean lever.
Leave for offline auto_permute. See memory [[multireturn_reserves_v0]].
