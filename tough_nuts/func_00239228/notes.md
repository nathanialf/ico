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
