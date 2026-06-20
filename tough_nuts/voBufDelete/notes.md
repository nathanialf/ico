# voBufDelete (ito/mpeg/mv_vobuf) — parked at rc5 (loop-init scheduling only)

## Status
Algorithm fully recovered; matches ROM except a 3-byte scheduling residual in the
frame-clear loop's init block (file offset 0x19BA54-0x19BA60).

## Key dev-intent finding (from voBufGetTag, now matched)
voBufGetTag matched as `void voBufGetTag(volatile int *a0)` — the movie output
ring buffer is VOLATILE (shared with the IPU/interrupt; movie_init in mv_main.c
also takes `volatile int *`). So voBufDelete takes the SAME `volatile int *a0`.

`volatile` is the breakthrough: it ordered the field inits (writeIdx@12,
numFrames@16, readIdx@8) AND fixed the loop register tie (counter->a1, stride->v1,
matching ROM). Combined with a do-while (no initial guard), this took voBufDelete
from rc32 -> rc5. The seed here is the volatile do-while form.

## Remaining residual (rc5 = 2 link-resolved false-negs + 3 real)
The 2 `addiu a2,a2,24` (blk 3/9) are in-TU "p != NULL" %lo false-negs that resolve
in the full link. The 3 REAL bytes: gcc materializes `li v0,5` (numFrames value)
and `lui v1,0xa` (stride hi) one instruction LATER than ROM:
  ROM:   addiu v0,5 ; sw zero,12 ; lui v1 ; sw v0,16 ; sw zero,8
  built: sw zero,12 ; addiu v0,5 ; sw v0,16 ; lui v1 ; sw zero,8
Store ORDER matches (12,16,8); only the two value-materializations are deprioritized
by sched2 (short critical path: li 5 -> sw 16; the loop reloads a0[4] from memory so
the reg chain is broken). Confirmed NOT a hard volatile barrier — the li sits between
two :TI volatile stores and is movable; sched2 just won't hoist it. ~40 hand shapes
+ two permuter runs (volatile seed base score 210) did not crack it. Permuter-class
sched2 tie; re-attack with a structural perturbation that lengthens the 5's chain.

## Companion: data carve (REVERTED, redo when this matches)
The deq_movie_mes assert strings carve `[0x457158, .rodata, ito/mpeg/mv_vobuf]`
(D_00557158 "../ito/include/mv_defs.h" + D_00557178 "p != NULL") REQUIRES the inline
`deq_movie_mes` form so mv_vobuf.o emits the strings via __FILE__ (explicit string
defs don't reproduce the 0x20/0x10 padding). It is coupled to this match: re-apply
the yaml split + `#include "mv_defs.h"` + include_ito.txt entry once the loop matches.
The seed here uses extern strings (standalone, no header) for the permuter.

---

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=2). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `ito/mpeg/mv_vobuf.c`

**Seed:** `tough_nuts/voBufDelete/voBufDelete.1.c`

Disassembly:

```
.align 3
nonmatching voBufDelete, 0x160

glabel voBufDelete
    /* 9B950 0019B950 C0FFBD27 */  addiu      $29, $29, -0x40
    /* 9B954 0019B954 5500023C */  lui        $2, %hi(D_00557158)
    /* 9B958 0019B958 1000B1FF */  sd         $17, 0x10($29)
    /* 9B95C 0019B95C 6900053C */  lui        $5, (0x697800 >> 16)
    /* 9B960 0019B960 2000B2FF */  sd         $18, 0x20($29)
    /* 9B964 0019B964 2D888000 */  daddu      $17, $4, $0
    /* 9B968 0019B968 58715224 */  addiu      $18, $2, %lo(D_00557158)
    /* 9B96C 0019B96C 5097848F */  lw         $4, %gp_rel(D_0062A340)($28)
    /* 9B970 0019B970 0000B0FF */  sd         $16, 0x0($29)
    /* 9B974 0019B974 40000624 */  addiu      $6, $0, 0x40
    /* 9B978 0019B978 3000BFFF */  sd         $31, 0x30($29)
    /* 9B97C 0019B97C 0078A534 */  ori        $5, $5, (0x697800 & 0xFFFF)
    /* 9B980 0019B980 2D384002 */  daddu      $7, $18, $0
    /* 9B984 0019B984 14E7040C */  jal        deq_mes_th
    /* 9B988 0019B988 2A000824 */   addiu     $8, $0, 0x2A
    /* 9B98C 0019B98C 2D804000 */  daddu      $16, $2, $0
    /* 9B990 0019B990 0A000056 */  bnel       $16, $0, .L0019B9BC
    /* 9B994 0019B994 6900063C */   lui       $6, (0x697800 >> 16)
    /* 9B998 0019B998 2D204002 */  daddu      $4, $18, $0
    /* 9B99C 0019B99C 40AB060C */  jal        func_001AAD00
    /* 9B9A0 0019B9A0 2B000524 */   addiu     $5, $0, 0x2B
    /* 9B9A4 0019B9A4 5500063C */  lui        $6, %hi(D_00557178)
    /* 9B9A8 0019B9A8 2D204002 */  daddu      $4, $18, $0
    /* 9B9AC 0019B9AC 7871C624 */  addiu      $6, $6, %lo(D_00557178)
    /* 9B9B0 0019B9B0 E080090C */  jal        func_00260380
    /* 9B9B4 0019B9B4 2B000524 */   addiu     $5, $0, 0x2B
    /* 9B9B8 0019B9B8 6900063C */  lui        $6, (0x697800 >> 16)
.align 2
  .L0019B9BC:
    /* 9B9BC 0019B9BC 2D200002 */  daddu      $4, $16, $0
    /* 9B9C0 0019B9C0 2D280000 */  daddu      $5, $0, $0
    /* 9B9C4 0019B9C4 5A81090C */  jal        func_00260568
    /* 9B9C8 0019B9C8 0078C634 */   ori       $6, $6, (0x697800 & 0xFFFF)
    /* 9B9CC 0019B9CC 32000012 */  beqz       $16, .L0019BA98
    /* 9B9D0 0019B9D0 FFFF0224 */   addiu     $2, $0, -0x1
    /* 9B9D4 0019B9D4 FF0F023C */  lui        $2, (0xFFFFFFF >> 16)
    /* 9B9D8 0019B9D8 0020033C */  lui        $3, (0x20000000 >> 16)
    /* 9B9DC 0019B9DC FFFF4234 */  ori        $2, $2, (0xFFFFFFF & 0xFFFF)
    /* 9B9E0 0019B9E0 5097848F */  lw         $4, %gp_rel(D_0062A340)($28)
    /* 9B9E4 0019B9E4 24100202 */  and        $2, $16, $2
    /* 9B9E8 0019B9E8 3200053C */  lui        $5, (0x323340 >> 16)
    /* 9B9EC 0019B9EC 25104300 */  or         $2, $2, $3
    /* 9B9F0 0019B9F0 4033A534 */  ori        $5, $5, (0x323340 & 0xFFFF)
    /* 9B9F4 0019B9F4 000022AE */  sw         $2, 0x0($17)
    /* 9B9F8 0019B9F8 40000624 */  addiu      $6, $0, 0x40
    /* 9B9FC 0019B9FC 2D384002 */  daddu      $7, $18, $0
    /* 9BA00 0019BA00 14E7040C */  jal        deq_mes_th
    /* 9BA04 0019BA04 2A000824 */   addiu     $8, $0, 0x2A
    /* 9BA08 0019BA08 2D804000 */  daddu      $16, $2, $0
    /* 9BA0C 0019BA0C 0A000056 */  bnel       $16, $0, .L0019BA38
    /* 9BA10 0019BA10 3200063C */   lui       $6, (0x323340 >> 16)
    /* 9BA14 0019BA14 2D204002 */  daddu      $4, $18, $0
    /* 9BA18 0019BA18 40AB060C */  jal        func_001AAD00
    /* 9BA1C 0019BA1C 2B000524 */   addiu     $5, $0, 0x2B
    /* 9BA20 0019BA20 5500063C */  lui        $6, %hi(D_00557178)
    /* 9BA24 0019BA24 2D204002 */  daddu      $4, $18, $0
    /* 9BA28 0019BA28 7871C624 */  addiu      $6, $6, %lo(D_00557178)
    /* 9BA2C 0019BA2C E080090C */  jal        func_00260380
    /* 9BA30 0019BA30 2B000524 */   addiu     $5, $0, 0x2B
    /* 9BA34 0019BA34 3200063C */  lui        $6, (0x323340 >> 16)
.align 2
  .L0019BA38:
    /* 9BA38 0019BA38 2D200002 */  daddu      $4, $16, $0
    /* 9BA3C 0019BA3C 2D280000 */  daddu      $5, $0, $0
    /* 9BA40 0019BA40 5A81090C */  jal        func_00260568
    /* 9BA44 0019BA44 4033C634 */   ori       $6, $6, (0x323340 & 0xFFFF)
    /* 9BA48 0019BA48 040030AE */  sw         $16, 0x4($17)
    /* 9BA4C 0019BA4C 12000012 */  beqz       $16, .L0019BA98
    /* 9BA50 0019BA50 FFFF0224 */   addiu     $2, $0, -0x1
    /* 9BA54 0019BA54 05000224 */  addiu      $2, $0, 0x5
    /* 9BA58 0019BA58 0C0020AE */  sw         $0, 0xC($17)
    /* 9BA5C 0019BA5C 0A00033C */  lui        $3, (0xA0A40 >> 16)
    /* 9BA60 0019BA60 100022AE */  sw         $2, 0x10($17)
    /* 9BA64 0019BA64 080020AE */  sw         $0, 0x8($17)
    /* 9BA68 0019BA68 2D200002 */  daddu      $4, $16, $0
    /* 9BA6C 0019BA6C 2D280000 */  daddu      $5, $0, $0
    /* 9BA70 0019BA70 400A6334 */  ori        $3, $3, (0xA0A40 & 0xFFFF)
    /* 9BA74 0019BA74 00000000 */  nop
.align 2
  .L0019BA78:
    /* 9BA78 0019BA78 000080AC */  sw         $0, 0x0($4)
    /* 9BA7C 0019BA7C 0100A524 */  addiu      $5, $5, 0x1
    /* 9BA80 0019BA80 21208300 */  addu       $4, $4, $3
    /* 9BA84 0019BA84 1000228E */  lw         $2, 0x10($17)
    /* 9BA88 0019BA88 2A10A200 */  slt        $2, $5, $2
    /* 9BA8C 0019BA8C FAFF4014 */  bnez       $2, .L0019BA78
    /* 9BA90 0019BA90 00000000 */   nop
    /* 9BA94 0019BA94 2D100000 */  daddu      $2, $0, $0
.align 2
  .L0019BA98:
    /* 9BA98 0019BA98 3000BFDF */  ld         $31, 0x30($29)
    /* 9BA9C 0019BA9C 2000B2DF */  ld         $18, 0x20($29)
    /* 9BAA0 0019BAA0 1000B1DF */  ld         $17, 0x10($29)
    /* 9BAA4 0019BAA4 0000B0DF */  ld         $16, 0x0($29)
    /* 9BAA8 0019BAA8 0800E003 */  jr         $31
    /* 9BAAC 0019BAAC 4000BD27 */   addiu     $29, $29, 0x40
endlabel voBufDelete
```
