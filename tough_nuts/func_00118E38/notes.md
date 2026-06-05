# func_00118E38 — parked

VRAM: 0x00118E38 (file_off 0x018E38)
Asm source: asm/aug6/nonmatchings/seki/src/MicroCode/func_00118E38.s

## Attempt at 2026-06-05

**Reason parked:** rc12 regalloc-coloring tie: structure correct (TImode lq/sq, load-all-then-store-forward); ROM colors 4 loaded values into a2/a3/t0/t1 ($6-$9) via src-ptr pre-saves (daddu t2,a2/v1,a3/v0,t0), gcc uses scattered v0/v1 recycle. 30-stall: 19 distinct hand shapes (temps fwd/rev, ptr-locals, byval-128, restrict, struct4, vol-dst, mode variants) all rc12 — only the $6-$9 coloring differs. Permuter-class like GetRealModelId.

**TU:** `seki/src/MicroCode.c`

**Seed:** `tough_nuts/func_00118E38/func_00118E38.c`

Disassembly:

```
.align 3
nonmatching func_00118E38, 0x34

glabel func_00118E38
    /* 18E38 00118E38 2D50C000 */  daddu      $10, $6, $0
    /* 18E3C 00118E3C 2D18E000 */  daddu      $3, $7, $0
    /* 18E40 00118E40 2D100001 */  daddu      $2, $8, $0
    /* 18E44 00118E44 0000A678 */  lq         $6, 0x0($5)
    /* 18E48 00118E48 00004779 */  lq         $7, 0x0($10)
    /* 18E4C 00118E4C 00006878 */  lq         $8, 0x0($3)
    /* 18E50 00118E50 00004978 */  lq         $9, 0x0($2)
    /* 18E54 00118E54 0000867C */  sq         $6, 0x0($4)
    /* 18E58 00118E58 1000877C */  sq         $7, 0x10($4)
    /* 18E5C 00118E5C 2000887C */  sq         $8, 0x20($4)
    /* 18E60 00118E60 3000897C */  sq         $9, 0x30($4)
    /* 18E64 00118E64 0800E003 */  jr         $31
    /* 18E68 00118E68 00000000 */   nop
endlabel func_00118E38
    /* 18E6C 00118E6C 00000000 */  nop
```

## Permuter shot (2026-06-05) — resolution (b), exhausted this set

Fired the tool-gated bounded permuter at the genuine stall=30/30. ~800 iters,
plateaued at permuter-score 1700 (base 1900), NO score-0. Harvested all
output-1700-* and output-1800-* by true real_count via `diff --dry`: every one
== rc12, nothing beat the parked best.

**Tooling finding (important for resume):** decomp-permuter's import STRIPS the
GNU `__attribute__((mode(TI)))` — its base.c became `typedef int Qw128;` (plain
32-bit int). So the permuter never actually explored the 128-bit lq/sq space;
its candidates can't express qword copies. This run is not a fair permuter test
of the regalloc-coloring tie.

**Resume strategy:** hand-only. The tie is purely the coloring of the 4 loaded
values into a2/a3/t0/t1 ($6-$9) with src-ptr pre-saves. Fresh hand hypotheses to
try next time: (a) a 6th dummy/used arg to shift the arg-register frontier;
(b) feeding the 4 values onward to a call expecting $6-$9; (c) QCOPY64-style
macro from include/r5900.h if one spells this exact 4-qword gather; (d) fixing
the permuter import to preserve mode(TI), then re-firing.
