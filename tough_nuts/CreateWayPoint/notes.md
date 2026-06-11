# CreateWayPoint — parked

VRAM: 0x00202F00 (file_off 0x102F00)
Asm source: asm/aug6/nonmatchings/fumi/src/way_llf/CreateWayPoint.s

## Attempt at 2026-06-11

**Reason parked:** rc5 fresh: element-ptr + null-guard + movz. if(a0){body}else{ret=0} fixes ret coloring to $4 (a0-reuse). Residual=coupled coloring+layout: element-addu steals beqz delay slot (ROM has ret=0 there) + separate else block + b. sched2/dbr tie, ~30 forms all rc5-9. reorg-tail permuter class.

**TU:** `fumi/src/way_llf.c`

**Seed:** `tough_nuts/CreateWayPoint/CreateWayPoint.c`

Disassembly:

```
.align 3
nonmatching CreateWayPoint, 0x3C

glabel CreateWayPoint
    /* 102F00 00202F00 2D288000 */  daddu      $5, $4, $0
    /* 102F04 00202F04 4C00023C */  lui        $2, %hi(D_004C6FF0)
    /* 102F08 00202F08 2000A38C */  lw         $3, 0x20($5)
    /* 102F0C 00202F0C 34000424 */  addiu      $4, $0, 0x34
    /* 102F10 00202F10 F06F4224 */  addiu      $2, $2, %lo(D_004C6FF0)
    /* 102F14 00202F14 18186400 */  mult       $3, $3, $4
    /* 102F18 00202F18 21186200 */  addu       $3, $3, $2
    /* 102F1C 00202F1C 0500A010 */  beqz       $5, .L00202F34
    /* 102F20 00202F20 2D200000 */   daddu     $4, $0, $0
    /* 102F24 00202F24 0C00A48C */  lw         $4, 0xC($5)
    /* 102F28 00202F28 0800628C */  lw         $2, 0x8($3)
    /* 102F2C 00202F2C 26108200 */  xor        $2, $4, $2
    /* 102F30 00202F30 0A200200 */  movz       $4, $0, $2
.align 2
  .L00202F34:
    /* 102F34 00202F34 0800E003 */  jr         $31
    /* 102F38 00202F38 2D108000 */   daddu     $2, $4, $0
endlabel CreateWayPoint
    /* 102F3C 00202F3C 00000000 */  nop
```

## Fresh match attempt 2026-06-11: rc8 -> rc5, stall=30 -> permute
Structure: `e=&D_004C6FF0[a0->0x20]; ret = a0 ? (a0->0xC==e->0x8 ? 0 : a0->0xC) : 0` (movz idiom).
Best=rc5 via `if(a0){ret=a0[3];if(a0[3]==e->w[2])ret=0;}else ret=0;` (a0-first if-else colors ret
into $4 = a0's reused arg reg). The DEFAULT `int ret=0;` form gives rc8 (ret->$6, wrong coloring).
Residual rc5 = COUPLED coloring+layout: gcc's dbr fills the beqz delay with the element-addu
(deferred, $3 used only inside the if) while ROM puts ret=0 there; the if-else then needs a separate
else block + `b` to merge vs ROM's ret=0-in-delay + shared return. sched2 schedules ret=0 early
(no deps) so it's never the dbr delay candidate. ~30 distinct hand forms (ternary/movn/sub-cmp/
goto/decl-order/branch-direction/ptr-vs-arr) all rc5-13. Permuter (reorg-tail class).

## Permuter harvest 2026-06-11: nothing below rc5 -> (b)
Permuter ran ~6000 iters, best score 180 (base 220) BUT diff --dry: output-180-1/185-1=rc7,
190-1=rc9, 205-1=rc8 — all WORSE than parked rc5 (score/real_count anti-correlation; the
"wins" are broken `ret=ret` uninitialized-else mutations). Nothing beats rc5. RESOLUTION (b).
Re-attack future resume with a fresh idea to get ret=0 into the beqz delay slot (vs the
deferred element-addu) without the separate else block.
