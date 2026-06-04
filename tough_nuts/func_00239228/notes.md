# func_00239228 — parked

VRAM: 0x00239228 (file_off 0x139228)
Asm source: asm/aug6/nonmatchings/ito/mpeg/mv_audiodec/func_00239228.s

## Attempt at 2026-06-04

**Reason parked:** rc5 scheduler near-miss: FP const -133.0f (lui+mtc1, 2-insn chain) is deprioritized vs the two single-insn %gp_rel lwc1 loads — gcc hoists the loads before the const (ROM has const first), cascading the swc1 store order. Structure/regalloc otherwise matches sendDispEnv idiom. 3 forms (temp/direct/store-order) rc5-8. Permuter target.

**TU:** `ito/mpeg/mv_audiodec.c`

**Seed:** `tough_nuts/func_00239228/func_00239228.c`

Disassembly:

```
.align 3
nonmatching func_00239228, 0x28

glabel func_00239228
    /* 139228 00239228 3400838C */  lw         $3, 0x34($4)
    /* 13922C 0023922C 01000224 */  addiu      $2, $0, 0x1
    /* 139230 00239230 05C3013C */  lui        $1, (0xC3050000 >> 16)
    /* 139234 00239234 00088144 */  mtc1       $1, $f1
    /* 139238 00239238 448F82C7 */  lwc1       $f2, %gp_rel(D_00629B34)($28)
    /* 13923C 0023923C 488F80C7 */  lwc1       $f0, %gp_rel(D_00629B38)($28)
    /* 139240 00239240 000061E4 */  swc1       $f1, 0x0($3)
    /* 139244 00239244 080060E4 */  swc1       $f0, 0x8($3)
    /* 139248 00239248 0800E003 */  jr         $31
    /* 13924C 0023924C 040062E4 */   swc1      $f2, 0x4($3)
endlabel func_00239228
```

## Resume 2026-06-04 (hand iteration; matchings refreshed via build.sh setup)

Confirmed best **rc5** still; residual is ONE block: the FP const `-133.0f`
(`lui 0xc305; mtc1 $f1`) is scheduled AFTER the two `%gp_rel lwc1` loads; ROM
emits the const block BEFORE the loads. Store batching (0x0, 0x8, 0x4 with the
0x4 store in the jr-ra delay) and regalloc otherwise match.

**Diagnostics this resume:**
- The `int` return value `1` is REQUIRED and correct: `li v0,1` lands 2nd
  (matches ROM) and putting `1` in v0 is exactly what forces the pointer into
  `v1` (`lw v1,0x34(a0)`). Dropping it (void form) → rc8 and loses `addiu v0,1`.
  So the func is `int func(void*){...; return 1;}` — not void, not pointer-return.
- 8 dev-plausible hand forms all rc5–8, const-after-loads robust:
  seed(temps a/b/c) rc5; inline-all natural order rc7 (const-FIRST but eager
  stores break batch/delay); volatile-p rc5-variant (const-first but kills
  jr-delay → trailing nop); temps+ROM-store-order(p0,p2,p1) rc8; const-temp
  declared-last rc5; const-inline+global-temps rc5.
- `tools/sched_diff.py` is NOT aug6-aware ("no source for TU") — can't introspect
  the per-pass RTL here.

**Next levers to try (hand, do NOT force the permuter — gated by `next` only):**
- recover the dev's actual struct type for a0->field34 (a 3-float vector
  setter in Ito's mv_audiodec; -133.0 + 2 gp globals) — maybe a named struct
  assignment changes the const-vs-load sched priority.
- find a sibling in the ito/mpeg TUs that sets an FP const before gp_rel loads
  and copy its idiom.
- the const block loses sched priority to the higher-latency loads; look for a
  source shape where the const's value is on a longer/equal critical path.

## Re-test 2026-06-04 (loop): in-flight working-tree attempt was `volatile float *p`
form (rc5) — volatile OVER-SERIALIZES (forces swc1 after each lwc1, blocking
ROM's load-all-3-then-store latency-hiding). Plain `float*` order 0,1,2 = rc7,
order 0,2,1 = rc6, load-into-temps-first = rc5. Residual across all: const
materialized to $f0 (built) vs $f1 (ROM), and the lwc1/swc1 interleave. Not a
volatile problem to add — needs the regalloc/sched shape that puts const in $f1
with all three FP loads hoisted before the three stores (p[1] store in jr-delay).
Reverted working tree to INCLUDE_ASM (stays parked); seed = temps form (rc5).

## Resume 2026-06-04 (loop set "10 smallest") — 8 more distinct forms, rc5 root confirmed

Re-attacked with 8 genuinely-distinct hand hypotheses, ALL rc5+:
- inline all, store order p0,p2,p1 → rc6 (const-first but eager/unbatched stores)
- temp load-order c-before-b, seed store order → rc7
- union{int;float} const (a.i=0xC3050000) → rc7 (forces integer `sw`, not `swc1` — WRONG)
- struct Vec3 {x,y,z} members → rc7 (eager 0,4,8 stores)
- `*(volatile float*)&D_…` loads → rc6 (hoists loads even EARLIER, wrong dir)
- `*(volatile float*)&p[0]` store → rc5 (const still materialized after loads; no pin)
- array D_00629B34[0]/[1] → rc5 (equivalent to two symbols, no sched change)
- decl order c(B38),a(const),b(B34) to target reg-alloc f0=B38 → rc7 (got B38→f1, wrong)

ROOT (single, robust): gcc sched1 ranks the two single-insn `%gp_rel lwc1` loads
ahead of the 2-insn `lui+mtc1` const chain; ROM emits the const block first.
The dependent swc1 p0/p2 swap is a CONSEQUENCE of that one ordering decision.
No pure-C hand lever flips a 2-insn const-chain ahead of single-insn loads here
(latency-priority floor). This is the textbook decomp-permuter case.

DEFER: permuter is a USER-GATED one-shot (permuter-hand-grind-discipline) — NOT
fired in this unsupervised /loop. Seed below is the rc5 best. Next user-present
session: `tools/permute_run.sh func_00239228 <seed> -- --stop-on-zero -j 4`.

---

## Attempt at 2026-06-04

**Reason parked:** rc5 plateau @stall=30: single root = gcc sched1 ranks 2x single-insn gp_rel lwc1 loads ahead of 2-insn lui+mtc1 const chain; ROM emits const block first. 14 distinct hand forms ruled out (store/decl/regalloc order, volatile loads/stores/ptr, union, struct, array, char*-arith, nested-block, return-temp). next->park, routed to offline auto_permute batch.

**TU:** `ito/mpeg/mv_audiodec.c`

**Seed:** `tough_nuts/func_00239228/func_00239228.1.c`

Disassembly:

```
.align 3
nonmatching func_00239228, 0x28

glabel func_00239228
    /* 139228 00239228 3400838C */  lw         $3, 0x34($4)
    /* 13922C 0023922C 01000224 */  addiu      $2, $0, 0x1
    /* 139230 00239230 05C3013C */  lui        $1, (0xC3050000 >> 16)
    /* 139234 00239234 00088144 */  mtc1       $1, $f1
    /* 139238 00239238 448F82C7 */  lwc1       $f2, %gp_rel(D_00629B34)($28)
    /* 13923C 0023923C 488F80C7 */  lwc1       $f0, %gp_rel(D_00629B38)($28)
    /* 139240 00239240 000061E4 */  swc1       $f1, 0x0($3)
    /* 139244 00239244 080060E4 */  swc1       $f0, 0x8($3)
    /* 139248 00239248 0800E003 */  jr         $31
    /* 13924C 0023924C 040062E4 */   swc1      $f2, 0x4($3)
endlabel func_00239228
```
