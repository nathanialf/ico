# func_0024E510 (common/src/PObj) — parked at rc2 (stall=30 + permuter)

15-insn dispatcher. Structure is **byte-perfect** in clean C; sole residual is a
single-register local-alloc tiebreak.

## Recovered shape (best, rc2)
```c
extern int D_0054C92C[];
extern int func_0024E3E8(void);
extern int func_0024E550(void);

int func_0024E510(void) {
    if (D_0054C92C[0] == 3) {
        return func_0024E3E8();
    }
    return func_0024E550();
}
```
- `extern int D_0054C92C[]` (incomplete array) forces `%hi/%lo` over gp-rel (rc12→ fixed).
- **int return** (callees declared `int`, `return f()`) defeats the void-selector
  sibcall (`j`) → ROM's `jal` + frame + shared epilogue (rc12-shape → rc2). This was
  the big crack: void return TCO'd both calls as `j func`; int return restores jal.

## The rc2 residual (the ONLY diff)
```
exp: addiu v0,zero,3 ; beq v1,v0,T      # ROM: const 3 in $2, REUSING the freed %hi base reg
got: addiu a0,zero,3 ; beq v1,a0,T      # ours: const 3 in $4 (free arg reg)
```
ROM chains $2: `%hi`-base → const-3 → return-value. gcc local-alloc spreads the
const to the free arg reg $4 (the no-arg callees leave a0 free) instead of reusing
the dead $2. Inverse of `feedback_param_reuse_dead_arg_reg` (there ROM used the dead
arg reg and gcc reused %hi; here ROM reuses %hi and gcc uses the dead arg reg).

## Hypotheses tried (all rc2 unless noted) — stall=30
if/else, switch(case 3), ternary, explicit-r var, goto-shared-epilogue, temp
`int x`, two-temp `v`+`c`, named `int k=3`, operand-swap `3==D`, `*D` deref,
`*(int*)D` cast, unsigned-element array, `(unsigned)` compare, early-out-no-else,
nested-if, do-while(0), extra dead local, `void*` return chain. WORSE: `r=3` reuse-
coalesce → rc7 (forces callee-saved); sized `[1]` → rc3 (gp-rel); sized `[3]` rc2;
volatile load → rc2 but bne (branch flip); static-impl wrapper → rc8.

## Permuter (fired at gate)
`permute_run.sh func_0024E510 <seed> -- --stop-on-zero -j 4`: base score 215,
no candidate below 215 after extensive iterations, no match. Randomization doesn't
reach the $2-reuse — needs a targeted non-equivalent rewrite.

## Resume levers to try fresh
- Force a0 genuinely live at the compare (without adding a ROM-visible arg load).
- A rewrite that makes the const pseudo coalesce with the %hi-base pseudo (same qty)
  WITHOUT extending its live range across the calls (which `r=3` did → callee-saved).
- Re-seed permuter with a variant that already has an extra dead pseudo near the compare.

## Pass 2 (2026-06-11): resume, ~15 fresh forms -> rc2, stall=30 -> permute pass 2
Re-confirmed the sole residual: const 3 in $4 (free arg reg) vs ROM $2 (reused dead %hi base);
gcc reserves $2/v0 for the int return value so the const avoids it. Fresh this pass (all rc2):
a0-passthrough (rc6, adds a0-save), a0-unused param, const-var/named-3, temp-d, ptr-var/&deref,
switch(case3), if-else-r, !=-inverted, 3==D swap, (d&0xff)==3, goto-shared-epilogue, register d,
ternary. The (x^y)==0 lever (func_0017BD00) does NOT apply (would change beq-with-const to
xor+beqz, byte-different). a0 can't be made live without a save (passthrough) or it stays dead
(unused->still $4). Pure local-alloc reg-preference tiebreak. Firing permuter pass 2 re-seeded
with the two-temp (c=3,d=D[0]) variant (extra dead pseudos near the compare, per resume lever 3).

---

## Attempt at 2026-06-11

**Reason parked:** rc2 const-3 in $4 vs ROM $2 (dead %hi reuse; gcc reserves v0 for int return); ~15 fresh forms pass2 all rc2; pure local-alloc tiebreak. Pass 2.

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0024E510/func_0024E510.1.c`

Disassembly:

```
.align 3
nonmatching func_0024E510, 0x3C

glabel func_0024E510
    /* 14E510 0024E510 5500023C */  lui        $2, %hi(D_0054C92C)
    /* 14E514 0024E514 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 14E518 0024E518 2CC9438C */  lw         $3, %lo(D_0054C92C)($2)
    /* 14E51C 0024E51C 03000224 */  addiu      $2, $0, 0x3
    /* 14E520 0024E520 05006210 */  beq        $3, $2, .L0024E538
    /* 14E524 0024E524 0000BFFF */   sd        $31, 0x0($29)
    /* 14E528 0024E528 5439090C */  jal        func_0024E550
    /* 14E52C 0024E52C 00000000 */   nop
    /* 14E530 0024E530 04000010 */  b          .L0024E544
    /* 14E534 0024E534 0000BFDF */   ld        $31, 0x0($29)
.align 2
  .L0024E538:
    /* 14E538 0024E538 FA38090C */  jal        func_0024E3E8
    /* 14E53C 0024E53C 00000000 */   nop
    /* 14E540 0024E540 0000BFDF */  ld         $31, 0x0($29)
.align 2
  .L0024E544:
    /* 14E544 0024E544 0800E003 */  jr         $31
    /* 14E548 0024E548 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_0024E510
    /* 14E54C 0024E54C 00000000 */  nop
```

## Pass 2 harvest (2026-06-11): two-temp seed base=215, no sub-base -> (b)
Permuter (~2577 iters, two-temp c=3/d=D[0] seed, base 215) produced NO output below base. The
const-3 $4-vs-$2 local-alloc tiebreak is not reachable by the permuter's randomization (same as
pass 1). RESOLUTION (b) pass 2. Best stays rc2. Future resume: a non-equivalent rewrite that makes
the const pseudo coalesce with the dead %hi-base reg ($2) without reserving v0 — or accept it as a
local-alloc reg-order difference (the permuter twice can't reach it).
