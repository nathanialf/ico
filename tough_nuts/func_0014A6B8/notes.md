# func_0014A6B8 — parked

VRAM: 0x0014A6B8 (file_off 0x04A6B8)
Asm source: asm/nonmatchings/src/act-game/func_0014A6B8.s

## Attempt at 2026-05-31

**Reason parked:** rc6 predicate near-miss. if(a0!=D_00631AE4)return 0; sub=a0->0x164; if(((D_0055CFD8[sub->0x30].f_4C>>9)&1)==0)return 0; return sub->0x180. Struct-array form (stride 0x50, f_4C field) gets the cleanest rc6. Residual: gcc fills the guard's bne delay with the hoistable stride const (addiu v0,80) + front-loads the far-global %hi, while the ROM fills the bne delay with the sub load (lw a1,356(a0)) and loads x=sub->0x30 first -> x/base register swap (x->a0 vs base->a0) cascading to 6 diffs. sched_diff: dbr fills bne delay with the stride const (insn 27) not the sub load (insn 19); sched2 orders the independent const before the dependent load. 7 forms tried (ptr-arith/explicit-x/struct/explicit-idx/cached-base). The matched sibling func_00149EF8 has the same array access but NO guard, so no bne-delay competition. Needs a sched lever/permuter. stall 3, NOT a floor.

**TU:** `src/act-game.c`

**Seed:** `tough_nuts/func_0014A6B8/func_0014A6B8.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00631AE4, 1

.align 3
nonmatching func_0014A6B8, 0x48

glabel func_0014A6B8
    /* 4A6B8 0014A6B8 F491828F */  lw         $2, (D_00631AE4) /* gp_rel: (D_00631AE4) */
    /* 4A6BC 0014A6BC 0E008214 */  bne        $4, $2, .L0014A6F8
    /* 4A6C0 0014A6C0 6401858C */   lw        $5, 0x164($4)
    /* 4A6C4 0014A6C4 3000A48C */  lw         $4, 0x30($5)
    /* 4A6C8 0014A6C8 50000224 */  addiu      $2, $0, 0x50
    /* 4A6CC 0014A6CC 5600033C */  lui        $3, %hi(D_0055CFD8)
    /* 4A6D0 0014A6D0 18208200 */  mult       $4, $4, $2
    /* 4A6D4 0014A6D4 D8CF6324 */  addiu      $3, $3, %lo(D_0055CFD8)
    /* 4A6D8 0014A6D8 21208300 */  addu       $4, $4, $3
    /* 4A6DC 0014A6DC 4C00828C */  lw         $2, 0x4C($4)
    /* 4A6E0 0014A6E0 42120200 */  srl        $2, $2, 9
    /* 4A6E4 0014A6E4 01004230 */  andi       $2, $2, 0x1
    /* 4A6E8 0014A6E8 03004010 */  beqz       $2, .L0014A6F8
    /* 4A6EC 0014A6EC 00000000 */   nop
    /* 4A6F0 0014A6F0 0800E003 */  jr         $31
    /* 4A6F4 0014A6F4 8001A28C */   lw        $2, 0x180($5)
.align 2
  .L0014A6F8:
    /* 4A6F8 0014A6F8 0800E003 */  jr         $31
    /* 4A6FC 0014A6FC 2D100000 */   daddu     $2, $0, $0
endlabel func_0014A6B8
```
