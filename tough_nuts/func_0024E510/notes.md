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
