# func_00269480 — fdlibm isnan(double bits in a long long)

VRAM 0x00269480. `int isnan` bit-trick: lx=(int)x; hx=(int)(x>>32);
hx&=0x7fffffff; hx|=(unsigned)(lx|-lx)>>31; hx=0x7ff00000-hx; return (unsigned)hx>>31.

Residual rc4 = a single sched2 reorder: ROM emits, after lx (dsll32+dsra32),
the order **hx(dsra32 a0), lui(mask), negu, ori, or, and**; gcc -O2 sched2
emits **lui, negu, ori, hx, ...** — the hx-extract (and its dependent `or hx|=`)
are pushed ~3 slots later.

## Root cause (confirmed this session via direct-compiler diagnostic)
Pure **post-RA sched2 priority tie**. With `-fno-schedule-insns2` the emission
order is EXACTLY ROM (hx at pos3). With sched2 on, the mask const-load `lui`
and `negu` (critical-path priority 6) outrank hx-extract (priority 5: hx->and->
or->subu->srl) and displace it. The gap is structural: as long as the 0x7fffffff
mask is a 2-insn lui+ori feeding the same `and` that consumes hx, priority(lui)
= priority(hx)+1, so sched2 always schedules lui first. Byte-preserving source
cannot raise hx's path by 1 (no op to add) nor shorten lui's (mask needs 2
insns). DAG is fixed by the 14 required insns; only regalloc / UID tie-break are
free, and both are dominated by priority here.

## Fire history
- Fire 9 (prev session): ~30 forms + 100s permuter, no rc0. (b)
- 2026-06-10 RESUME: re-attacked with **30 genuinely-distinct clean-C hand
  hypotheses** (decl order, fold/reassoc, operand swaps, named consts, temps for
  lo/neg/mask, long-long-intermediate, ptr-alias word reads, ull param, implicit
  truncation, register-qualified, single-expr, etc.). ALL rc4 or worse — none
  moved hx out of the displaced slot. Independently screened ~36 shapes via the
  raw ee-gcc: every clean 13-insn form puts the mask `lui` at pos3. `next` ->
  permute at stall=30/30.

## Lever space exhausted by hand → permuter-class
Only remaining escape is a non-obvious regalloc-perturbing value rewrite (cf.
func_001FB768 `(new_var2=new_var)>=7`) that hand pins can't express. Seed the
permuter with this canonical rc4 form (tough_nuts/func_00269480/func_00269480.c).

---

## Attempt at 2026-06-10

**Reason parked:** rc4 sched2 priority tie (mask-lui+negu pri6 outrank hx-extract pri5; -fno-sched2 = ROM order). 30 distinct clean hand hyps this resume + 36 screened, all rc4. permuter-class.

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_00269480/func_00269480.1.c`

Disassembly:

```
.align 3
nonmatching func_00269480, 0x38

glabel func_00269480
    /* 169480 00269480 3C100400 */  dsll32     $2, $4, 0
    /* 169484 00269484 3F100200 */  dsra32     $2, $2, 0
    /* 169488 00269488 3F200400 */  dsra32     $4, $4, 0
    /* 16948C 0026948C FF7F033C */  lui        $3, (0x7FFFFFFF >> 16)
    /* 169490 00269490 23280200 */  negu       $5, $2
    /* 169494 00269494 FFFF6334 */  ori        $3, $3, (0x7FFFFFFF & 0xFFFF)
    /* 169498 00269498 25104500 */  or         $2, $2, $5
    /* 16949C 0026949C 24208300 */  and        $4, $4, $3
    /* 1694A0 002694A0 C2170200 */  srl        $2, $2, 31
    /* 1694A4 002694A4 F07F033C */  lui        $3, (0x7FF00000 >> 16)
    /* 1694A8 002694A8 25208200 */  or         $4, $4, $2
    /* 1694AC 002694AC 23206400 */  subu       $4, $3, $4
    /* 1694B0 002694B0 0800E003 */  jr         $31
    /* 1694B4 002694B4 C2170400 */   srl       $2, $4, 31
endlabel func_00269480
```

## Permuter result (2026-06-10 resume)
Fired bounded permuter (quick_diff CFLAGS, -j4, --stop-on-zero, seed=.1.c):
"no permutation matched (permuter exit=0)" — no improving output this pass.
Stale Fire-9 outputs (score 175..270) are semantically-broken mutations
(e.g. output-175 does `hx=lx` clobber), all ≫ rc4. Resolution (b): permuter-
exhausted. Re-attack on a future resume with a fresh regalloc-perturbing idea.
