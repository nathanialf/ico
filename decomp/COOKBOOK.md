# Matching cookbook — shape → C recipe

**How to use this file.** When you're staring at an `asm/nonmatchings/<func>.s`
and trying to figure out what C produces it, *grep the asm for one of the
fingerprints below* and jump to the matching recipe. Recipes give you the
C template, the header macros to pull in, and a link to the originating
`feedback_*.md` memory if you want the full reasoning. This is a working
document — add to it whenever a new shape gets cracked.

> **Index philosophy.** Bucket by what you can grep for in `.s` (frame
> size, jal count, branch mnemonic, MMI op, gp_rel form), not by the
> name of the trick. "I see `bnel + b + jr ra + daddu v0`" → §3.2.

> **Companion tool.** `tools/classify_asm.py <func>.s` (sketch in §10)
> prints the top-N recipes whose fingerprints fire on a given .s. Use it
> when you're not sure which bucket applies.

> **First, the canonical loop.** Read `CLAUDE.md` and `decomp/NOTES.md`,
> then flip the yaml entry to `c`, run `tools/build.sh setup`, and
> iterate with `tools/quick_diff.sh <name>` — only run `ninja` once
> quick_diff is empty. ([matching-quick-diff-only])

---

## Table of contents

1. [Wrappers (1-jal / 2-jal / TCO / varargs)](#1-wrappers)
2. [Regalloc nudges (force a specific GPR / callee-save)](#2-regalloc-nudges)
3. [Branch shape (likely vs plain, single vs split returns)](#3-branch-shape)
4. [Conditional store / clamp idioms](#4-conditional-store)
5. [Pointer/address arithmetic & gp_rel](#5-pointer-arithmetic)
6. [Unaligned 64-bit loads, packed structs, sq/lq](#6-unaligned-and-mmi)
7. [Float-related (mfc1, mtc1, lwc1 ordering, FP delay slots)](#7-float)
8. [Scheduler / delay-slot fixes (postprocesses)](#8-scheduler-and-postprocesses)
9. [Frame size & stack-spill control](#9-frame-and-stack)
10. [Classifier contract — `tools/classify_asm.py`](#10-classifier)
11. [When nothing works — park, permute, defer](#11-park-permute-defer)
12. [Splat / build-system gotchas (not C-level)](#12-build-gotchas)

Each recipe carries the same skeleton:

```
### N.M Recipe name
ASM fingerprint:    one-line grep target ("`sra X,2; srl X,2` in same basic block")
Frame / jal / size: rough envelope when relevant
C recipe:           minimal template
Headers:            matching.h / regpin.h / r5900.h
Why:                one sentence (compiler bias being defeated)
See:                [feedback_X], [feedback_Y]
```

---

## 1. Wrappers

The single largest matchable bucket. Always pull in `matching.h` so
`DEFEAT_TCO()` is available — ee-gcc 2.9 hardcodes sibling-call opt at -O2.

### 1.1 Constant-arg / pass-through TCO leaf (2 insns)

ASM fingerprint: `j FUNC; addiu aN, $0, K` *or* `j FUNC; lw aN, OFF(aN)`.
Frame / jal: 8-byte function, frame 0, single tail-jal.

```c
extern int func_callee(int);
int func_wrapper(int x) { return func_callee(K); }
```

No `DEFEAT_TCO()` here — sibcall *is* what we want.

Examples: any commit titled `Match func_X (sceXXX-style syscall wrapper)`
or `Match func_X (size>>4-count process loop)` etc. — search
`git log --oneline | grep -i 'wrapper\|tco'`. Bucket lives at
`docs/candidates.md` under shape `wrap-1jal-*`.
See: [feedback_match_batching], [feedback_fast_pass_subshape].

### 1.2 1-jal wrapper with spill+reload (`sw aN; lw aN; jal`)

ASM fingerprint: `sw $a0,0(sp); lw $a0,0(sp); jal X` inside a 0x20 frame.

```c
extern void func_target(int);
void func_wrapper(volatile unsigned int a0) {
    volatile int local;   /* expands frame to 0x20 */
    func_target(a0);
}
```

`volatile` on the parameter forces the sw+lw around the call; `volatile int local`
reserves the stack slot without an extra sw/lw.

Headers: none.
Examples: `func_0015F4B8` (score-0 promotion), `func_0015F4F0`, `func_00180580`.
See: [feedback_volatile_wrapper_pattern].

### 1.3 1-jal wrapper, spill-only (no reload)

ASM fingerprint: `sd ra; sw a0,..; jal X` with **no** `lw a0` before the call.

**No known recipe.** Park it. ([feedback_volatile_wrapper_pattern] limitation.)
Example (parked): `func_00176198`.

### 1.4 2-jal wrapper, callee-save reused across both calls

ASM fingerprint: `lw $s0, OFF(...)` in the **delay slot of the first jal**;
both calls reference the same `$sN` afterward.

```c
int *s0 = *(int **)(a0 + OFF);   /* deref BEFORE first call */
func_first(D_X);
s0[FIELD] = MODE;
func_last(0);
```

The deref must come *before* the first call so gcc allocates a callee-save
reg to hold it across the call.

Examples: `func_00164EB0` family (8 wrappers promoted by permuter from
this trick). For the init-default + conditional-overwrite variant see
`func_0019BA60`.
See: [feedback_lift_deref_before_call], [feedback_force_callee_save_reuse].

### 1.5 Wrapper that defeats sibcall (`jal + jr ra` instead of `j`)

ASM fingerprint: `jal X; ... ld ra; jr ra` — full prologue/epilogue
preserved even though body is "just a call."

```c
#include "matching.h"
int wrapper(int x) {
    int r = func_target(x);
    DEFEAT_TCO();
    return r;
}
```

`DEFEAT_TCO()` is an empty `__asm__("" ::: "memory")` barrier.
Examples: pervasive — `grep -rn DEFEAT_TCO src/` for the current call
sites. Bucket lives at `docs/candidates.md` under `wrap-gp-1jal`.
See: `include/matching.h`, [feedback_match_batching].

### 1.6 Force-void-return TCO when default emits a frame

ASM fingerprint: `j target` (sibling-call) in a branch where the natural C
would preserve `$v0` and keep a frame.

```c
void wrapper(int a0) {       /* note: declared void */
    if (cond) {
        return func_callee(a0);   /* gcc warns; asm matches */
    }
    D_global = 1;
    return 1;
}
```

Examples: `func_001F0858`, `func_0017B358` (permuter promotions).
See: [feedback_void_return_tco].

### 1.7 vsprintf-style varargs forwarder

ASM fingerprint: 7 consecutive `sd $reg, OFF($sp)` saves (a1..t3) +
`addiu a1, sp, OFF_OF_a1_SAVE` before a single jal.

```c
extern int func_X(char *fmt, void *args);
int wrapper(char *fmt, ...) {
    void *args = (char *)__builtin_next_arg(fmt) - 0x38;
    return func_X(fmt, args);
}
```

For wrappers with 2 named args `(a, b, ...)`: subtract `0x30` instead and
pass `__builtin_next_arg(b)` (last named arg).

Examples: `func_00264298` (2-named-args, sp+0x50 → -0x30 form), and the
forwarder it calls `func_002669E8`.
See: [feedback_varargs_builtin_next_arg].

### 1.8 Void-tail TCO inside an int function (`j`, not `jal`)

```
ASM fingerprint:    trailing `j func_X` (callee-saved + ra + sp restored first) while
                    other paths emit `daddu v0,$0,$0` / set v0 = N
C recipe:
    int f(int *a0, int a1) {
        if (a0 == 0)          { func_log(MSG1); return 0; }  /* err paths set v0 */
        if (func_check(...))  { func_log(MSG2); return 0; }
        func_void_tail(a0 + 4, a1);   /* LAST statement, NO `return` after it  */
    }                                  /* control falls off the end (gcc warns) */
Why:                ee-gcc 2.9 has NO int sibling-call opt (`return g()` is always `jal`),
                    but a trailing VOID call with no `return` after it becomes `j`, while
                    the `return N` paths still emit v0 = N.
Pitfalls:           declaring f `void` drops the `return 0` (loses v0); declaring the
                    callee `int` + `return callee()` gives `jal`.
See:                [feedback_void_tail_in_int_func], [feedback_void_return_tco]
```

---

## 2. Regalloc nudges

The repo ships `include/regpin.h` so explicit register pins read as
`register T x REG("$N")` instead of raw `__asm__("$N")`. `src/cod/*.c`
must contain **zero** `__asm__` tokens — bodies go in
`include/matching.h` / `include/r5900.h`, pins go behind `REG()`.
([feedback_no_asm_in_src_cod])

### 2.1 Force `daddu $v1, $v0, $0` after a jal (dead copy of return)

ASM fingerprint: `jal X; nop; daddu $v1, $v0, $0; ... sw ..., OFF($v1)`.

**Diff fingerprint:** expected has `daddu $3,$2,$0` (or `move $3,$2`)
right after a `jal`; built lacks the dead copy and stores via `$v0`.

```c
#include "matching.h"
#include "regpin.h"
register int *q REG("$3") = func_X(...);
KEEP_LIVE(q);
/* subsequent stores via q now use $v1 */
```

`REG("$3")` alone is a non-binding hint; the `KEEP_LIVE` barrier is what
forces the materialize.
Examples: `func_001C3720`, `func_001F22E0` (callback-registration siblings),
`func_001AA4F0` (paired with `-fno-schedule-insns` for the prologue half).
See: [feedback_keep_live_v1_pin].

### 2.2 Pin the first store to function start (not jr-ra delay)

ASM fingerprint: `sw $a1, 0($a0)` at function entry; gcc tries to schedule
it into the final jr-ra delay slot.

```c
#include "matching.h"
out[0] = (int)q;
KEEP_LIVE_MEM(out[0]);
/* rest of body */
```

Examples: `grep -rn KEEP_LIVE_MEM src/` for current call sites.
See: [feedback_keep_live_mem_pin_first_store].

### 2.3 Force `addu` destination to keep base's register

ASM fingerprint: `addu $s0, $s0, $v0; lw $v0, OFF($s0)` (result back in s0)
vs your `addu $v0, $v0, $s0` (result in v0).

```c
base += idx * STRIDE;                       /* compound update */
rv = *(int *)(base + OFFSET);
```

Not `*(int *)(base + idx*STRIDE + OFFSET)` — gcc treats that as a fresh
expression with no constraint on destination reg.
Examples: rare enough that `grep -rn 'base += .*\*' src/` is the
current discovery path. The inverse swap (rt↔rs) lives in §8.11.
See: [feedback_compound_update_for_addu_dest].

### 2.4 Force the alias `$a1 = $a0` copy at function entry

ASM fingerprint: `daddu $5, $4, $0` right after prologue; later derefs use
`$a1` while `$a0` is preserved for a tail call.

```c
#include "matching.h"
#include "regpin.h"
register int *alias REG("$5") = self;
MATERIALIZE(alias);
/* derefs through alias; tail_call(self) at end */
```

Without `MATERIALIZE`, gcc CSEs `alias = self` away.
Example: `func_001CE6F0` (4 zero-stores at offsets 0x2B0/0x310/0x3B8/0x3BC
of `self->_15C` followed by tail-call to `func_001E3FC8`).
See: [feedback_volatile_stores_pin_tail_call].

### 2.5 Pin a loop-induction or accumulator reg

ASM fingerprint: original codegen accumulates into a specific non-$v0 reg
then copies `daddu $v0, $sN, $0` in the jr-ra delay slot.

```c
register int accum REG("$N");
/* writes to accum across branches */
MATERIALIZE(accum);          /* between distinct writes */
return accum;
```

`MATERIALIZE` (`"+r"(x)` barrier) blocks gcc's combine pass from folding
two writes into `xori`/`movz`.
Example: `func_001C0BF8` (`switch.c`) — sign-bound bool
`(abs(p[1]) >= 3001 || abs(p[0]) >= 3001) ? 1 : 0`.
See: [feedback_materialize_barrier].

---

### 2.6 Force `$fA` over `$fB` for a fresh FP load (REG pin)

**Diff fingerprint:** `lwc1 $fA, OFF(...)` (expected) vs
`lwc1 $fB, OFF(...)` (built); same mnemonic, same memory operand,
only the FP register letter differs. Usually paired with the matching
`swc1 $fA, OFF2(...)` on the next line. tag_diff §2.7 fires.

**Why:** when multiple FP registers are dead at the same program point,
ee-gcc 2.9's regalloc picks the lowest-numbered free reg by default
(typically `$f0` because it just held the last computed result and went
dead). The original codegen sometimes picked a *different* free reg
(e.g. `$f1` because the most recent `mtc1 $0, $f1` left it associated
with a value).

**Fix:** pin a local float to the desired register:

```c
{
    register float v REG("$f1");
    v = *(float *)((char *)src + 0x28);
    *(float *)((char *)dst + 0x28) = v;
}
```

Headers: `#include "regpin.h"`. Wrap in a `{ ... }` block so the pin's
lifetime is exactly the load/store pair — gcc rejects mid-block decls
in C89 mode, so this block scope is the only sane way.

Example: `func_001E9F08` (`rotObject.c`) — only diff at end was
`lwc1 $f1,40($s1) / swc1 $f1,40($s0)` vs gcc's `$f0` pick.
See: [feedback_fpr_letter_swap].

---

### 2.7 Dual-pin alternating regalloc for chained volatile reloads

**Diff fingerprint:** expected has a chain of ≥3 `lw $rT, OFF($rs)`
reloads of the SAME memory, alternating between `$v0` and `$v1` as
the destination (`lw $v1; sw…(v1); lw $v0; sw…(v0); lw $v1; sw…(v1)`).
Built compiles the same chain but with every `lw` going to `$v0`
(or every one going to `$v1` if you over-pinned the local). The
instructions are otherwise identical, only the destination register
letters differ across the chain. tag_diff §2.8 fires.

**Why:** when source-level code re-derefs the same volatile pointer
many times in a row (cookbook §5.4 pattern), gcc treats each load as
independent but defaults to allocating them all to the lowest free
temp. The original codegen rotated `$v0`/`$v1` across the chain —
likely because the scheduler treated alternating destinations as
hiding load-use latency. A single REG pin won't help: it locks every
load to one register.

**Fix:** declare **two** register-pinned aliases for the same logical
pointer; assign to whichever alias matches the original's choice at
each store:

```c
register int *p_v0 REG("$2");
register int *p_v1 REG("$3");

p_v1 = (int *)*(int * volatile *)((char *)self + OFF_PTR);
*(volatile int *)((char *)p_v1 + OFF_A) = const_a;
p_v0 = (int *)*(int * volatile *)((char *)self + OFF_PTR);
*(volatile int *)((char *)p_v0 + OFF_B) = 0;
p_v1 = (int *)*(int * volatile *)((char *)self + OFF_PTR);
*(volatile int *)((char *)p_v1 + OFF_C) = const_a;
/* …continue alternating… */
```

Headers: `#include "regpin.h"` and `#include "matching.h"`. The
volatile stores are required: without them gcc hoists all the lw's
to the top of the block, which breaks the lw/sw pairing the chain
depends on.

Example: `func_00197240` (`act_bird.c`) — 7 reloads of `self->_15C`
across the `_544/_54C/_548/_550/_4AC/_4B0/_4C4` store chain; built
defaulted all to `$v0`, expected alternates `$v1, $v0, $v1, $v0, $v0, $v1, $v0`.
See: [feedback_dual_pin_alternating].

---

### 2.8 Non-volatile anchor barrier — `__asm__("" : "+r"(p))`

**Diff fingerprint:** a register-pinned pointer (`register T *p
__asm__("$N")`) is *copied* to a working reg before being used as an `lw`
base — built has `daddu v0,$N; lw x,OFF(v0); …` where expected uses
`lw x,OFF($N)` directly. ee-gcc 2.9 refuses to use a *fixed* register as a
memory base and spills it to a pseudo.

**Fix:** add a barrier on `p` after the pin — but **non-volatile**:

```c
register int *p __asm__("$5") = arg;
__asm__("" : "+r"(p));          /* NOT __volatile__ */
… p[OFF/4] …                    /* now reads via $5 directly */
```

**Why non-volatile matters:** `__asm__ __volatile__("" : "+r"(p))` also
anchors `p`, but its volatile-ness imposes a *scheduling boundary* that
shoves nearby independent ops out of the slot they belong in (e.g. a
`daddu a2,a0` save that should sit in a beq delay slot gets pushed to
function entry). The plain `__asm__("" : "+r"(p))` anchors the register
binding without that boundary. In func_0013D0D0 (ios/thread.c) the volatile
form gave 3 diffs, the non-volatile form gave 1 (then 0). Opposite intent
to KEEP_LIVE/MATERIALIZE, which *want* the boundary.

See: [feedback_nonvolatile_anchor_barrier].

> **Match-effort note (top-level rule):** do **20** genuinely-distinct
> iterations before parking any function — see CLAUDE.md "Match-effort
> rule" and [feedback_20_iter_discipline]. func_0013D0D0 above cracked at
> iter 17 after looking like a "3-diff floor" at iter 14. Near-misses are
> not floors.

### 2.9 Pin a computed value to the dead arg reg the original reuses

```
ASM fingerprint:    big "right insn, wrong register" cascade on ONE value (+ its
                    dependents), the original holding it in a caller-saved arg reg
                    (a0-a3 / $4-$7) that died at an early return
C recipe:
    if (size < 0xA0) { ...; return 0; }   /* a1 dies here */
    register int count REG("$5");          /* reuse the now-dead a1 */
    count = ...;                            /* assign normally */
Why:                once the incoming arg is dead the allocator can legally bind the
                    local to that reg; one pin re-seats the whole dependent chain
                    (21 → 5 diffs in one shot). Fixes register ALLOCATION, not scheduling.
Extension:          a temp-register ROTATION in an address cluster (v1↔a1↔a0, same
                    values/order, only names rotate) — pin TWO things: a base to a dead
                    arg reg, AND the `idx*STRIDE` INTERMEDIATE (not the final pointer):
                    `register int off REG("$5") = idx*STRIDE; p = base + off;`
See:                [feedback_pin_computed_var_to_dead_arg_reg], [feedback_keep_live_v1_pin]
```

### 2.10 Pin every cluster value + emit `ANCHOR()` in execution order

```
ASM fingerprint:    a small SCHEDULING cluster of independent ops (la lui/addiu, a gp_rel
                    arg load, a store-value const, a store) ordered differently than the
                    original; no single barrier fixes it (each change just trades one
                    transposition for another → looks like a permuter floor)
C recipe:
    register int v   REG("$2") = 1;                /* store value */
    register int a0v REG("$4") = D_GLOBAL;         /* gp_rel arg  */
    register const char *msg REG("$6") = D_FMT;    /* la fmt      */
    ANCHOR(v);  self[0x48/4] = v;                  /* anchor in the original's order */
    ANCHOR(a0v); ANCHOR(msg);
    m = func_alloc(a0v, 0x50, msg, line);
Headers:            regpin.h (REG), matching.h (ANCHOR)
Why:                gcc materializes anchored values in anchor order; pinning the regs +
                    ordering the anchors reproduces the schedule. A multi-insn schedule
                    near-miss is crackable by pinning EVERY participant — try before
                    declaring any small-cluster schedule diff a permuter-only floor.
See:                [feedback_triple_pin_ordered_anchors], [feedback_nonvolatile_anchor_barrier]
```

### 2.11 Dual-pin both operands of a masked unaligned read

```
ASM fingerprint:    `lwl a2,0xF(p); lwr a2,0xC(p); lui v1,0xffff; dsrl32 v1,v1,0; and a2,a2,v1`
                    (an unaligned int read zero-extended into a 64-bit call arg)
C recipe:
    extern int func(int, int, unsigned long long a2, int, int);
    struct U32 { int v; } __attribute__((packed));            /* SIGNED read */
    register unsigned long long mask REG("$3") = 0xFFFFFFFFULL;
    register int wi REG("$6") = ((struct U32 *)(s + 0xC))->v;  /* read -> a2 */
    r = func(base, id, wi & mask, ...);
Why:                pinning the MASK to $3 materializes 0xFFFFFFFF fresh as `lui;dsrl32`
                    in v1; pinning the SIGNED int read to the arg reg gives in-place
                    `and a2,a2,v1`. A single pin gives the right value in the wrong form.
Related:            ANCHOR a stored constant (not the pointer/struct) to stop a store→load
                    const-fold that deletes the lwl/lwr ([feedback_anchor_breaks_store_to_load_fold]);
                    when hand store-orders plateau, BRUTE-FORCE all N! orders + ANCHOR a
                    ready-early/stored-late value ([feedback_brute_force_store_order_plus_anchor]).
See:                [feedback_dual_pin_read_and_mask_const], [feedback_dual_pin_alternating]
```

### 2.12 Force the `daddu` base-copy + keep a dead counter counting UP

```
ASM fingerprint:    `addiu $3,$3,%lo(SYM); daddu $16,$3; addiu $17,$3,0x20` (symbol address
                    in a caller-saved temp, COPIED to a callee-saved reg, others derived
                    from the temp) — ee-gcc coalesces SYM straight into the destination.
                    Plus a dead count-UP loop counter (`sltiu $cnt,N; bnez`) that ee-gcc
                    reverses to a count-DOWN dbra.
C recipe:
    register char *base REG("$3"); base = SYM; q = base + 0x20; e = base;
    /* compute q from base BEFORE `e = base` so q reads $3 */
    /* per-file `<UPPER_TU> -fno-strength-reduce` in config/extra_cflags.txt keeps count-up */
Why:                a plain `char *base = SYM;` lets gcc coalesce (no copy); the pin forces
                    materialize-into-temp-then-copy. -fno-strength-reduce keeps an explicit
                    count-up counter alongside explicit pointer IVs (safe for single-fn TUs).
Note:               permute_run's extra_cflags lookup is keyed to src/cod/<off>.c — for a
                    src/<TU> function pass the flag via `CFLAGS=` env, or the permuter
                    compiles count-down and never converges.
See:                [feedback_base_copy_pin_and_countup_flag], [feedback_basefold_copy_coalesce]
```

---

## 3. Branch shape

### 3.1 Multi-fail null-chain → bool (force 2 distinct `jr ra`)

**Diff fingerprint:** built has `sltu` followed by `movz`/`movn`
(bool-collapse); expected has multiple distinct `jr ra` paths returning
0 and 1.

ASM fingerprint:

```
beq $a0,$0,.fail
beq $a0->_X,$0,.fail
bne $a0->_Y,$0,.succ
.fail: jr ra; daddu $v0,$0,$0
.succ: jr ra; addiu $v0,$0,1
```

```c
int func(int *a0) {
    int *p; int v0;
    if (a0 == 0) goto fail;
    p = (int *)a0[X];
    if (p == 0) goto fail;
    v0 = p[Y];
    if (v0 != 0) goto succ;
fail: return 0;
succ: return 1;
}
```

`if (a0 && a0->_X && a0->_X->_Y) return 1; return 0;` collapses to sltu.
Examples: search `grep -rn 'goto fail' src/` — the idiom is rare enough
that current call sites are the canonical references.
See: [feedback_goto_separate_returns].

### 3.2 `bnel + b + shared epilogue` (single return point)

ASM fingerprint:

```
sltu v0,idx,len
bnel v0,$0,STORE
 lw  reg,OFF(base)        ; delay (only on taken)
b    END
addiu rv,$0,-1            ; delay (set sentinel)
STORE: ...
END: jr ra; daddu v0,rv,$0
```

```c
int rv;
if (guard) goto store;
rv = -1;
goto end;
store:
    /* work */
end:
    return rv;
```

Examples: search `grep -rn 'goto store\|goto end' src/` for current
call sites.
See: [feedback_goto_single_return].

### 3.3 `beql`/`bnel` vs `beq`/`bne` — park, don't grind

**Diff fingerprint:** built has `beq` (or `bne`) where expected has
`beql` (or `bnel`), otherwise identical operands.

ASM fingerprint: only branch-likely vs plain branch differs between built
and expected; body otherwise matches.

**No source-level fix.** ee-gcc 2.9's likely-branch heuristic is fixed;
flipping `==` to `!=` doesn't shift it. Park via `tools/park.sh`.

When the delay-slot op IS safe to annul, ee-gcc 2.9 now picks bnel
natively for most cases — see §8.6 (postprocess retired). If gcc still
disagrees, restructure the delay-slot operation to be a reload-for-next-iter.
See: [feedback_branch_likely_emission].

### 3.4 Single-cond skip-call loop → `bnel` via int-index for-loop

```
ASM fingerprint:    `bnel cond,skip / addiu p,stride (annulled delay)` then `jal f; daddu a0,p`
                    — a single-condition "call f(p) when test" walk you keep getting as `bne`
C recipe:
    for (i = 0; i < LIMIT; i += STRIDE) {
        T *p = base + i;                  /* pointer DERIVED INSIDE the body */
        if (cond(p)) func(p);
    }
Why:                the natural pointer do-while lets sched1 hoist the call-arg (`a0=p`) to
                    the loop top → only the advance fills the delay → reorg picks `bne`.
                    Re-deriving `p` in the body blocks the hoist → reorg annuls → `bnel`.
                    Multi-condition (nested-if) walks already give bnel from a plain do-while.
See:                [feedback_int_index_loop_forces_bnel], [feedback_branch_likely_emission]
```

### 3.5 Search loop returning the matched pointer — dual parallel IVs

```
ASM fingerprint:    two pointer IVs always equal but kept separate (one loaded+tested, one
                    only returned), the return-IV's increment SPLIT across the beq/bne delay
                    slots via a lag temp
C recipe:
    char *p = BASE;                            /* free -> la-result, loaded/tested */
    register char *end REG("$7") = p + N;      /* declare BEFORE r so bound is off p */
    register char *r   REG("$6") = BASE;       /* the returned pointer */
    do {
        char *tmp = r;                         /* lag copy -> beq delay */
        if (*(int *)p == key) goto found;      /* found OUT OF LINE */
        p += STRIDE;
        r = tmp + STRIDE;                       /* split increment -> bne delay */
    } while ((int)p < (int)end);
    return 0;
found: return r;
Why:                splitting r's increment across the delay slots frees the walk-advance to
                    be a normal insn and pushes the pointers to $5/$6/$7 with a $3 lag temp.
See:                [feedback_dual_iv_return_pointer]
```

### 3.6 Steer branch DIRECTION by physical block placement

```
ASM fingerprint:    original `bne r,BODY` (success body out-of-line, error falls through to
                    ret-0), but ee-gcc emits `beq r,ret` (body inline) regardless of
                    `if(r)` vs `if(r==0)`
C recipe:
        ...; if (r != 0) goto store;     /* r==0 falls through */
    fail:
        return 0;                         /* shared ret; early checks also `goto fail` */
    store:                                /* BODY placed AFTER fail -> out-of-line bne target */
        { ...body...; return slot[0]; }
Why:                branch direction isn't fixed by flipping the C condition, but a block
                    reached only by a forward goto, placed LAST, becomes the taken (`bne`)
                    target — and its first op fills the delay.
See:                [feedback_body_out_of_line_branch_direction], [feedback_goto_single_return]
```

### 3.7 Break a loop-entry / back-edge merge with `ANCHOR()`

```
ASM fingerprint:    nested search loop where the empty-container guard and the inner loop's
                    back-edge test are the SAME condition, so gcc emits `b loop_cond` (enters
                    at the condition) instead of a separate `beqz` guard + body entry
C recipe:
    if (head == 0) { res = 0; goto check; }
    ANCHOR(head);                          /* forces a BB boundary -> separate beqz + body */
    do { if (head[0]==a0){res=head;goto check;} head=head->next; } while (head != 0);
    res = 0;
    check: ...                             /* pair with out-of-line `goto ret_res` */
Headers:            matching.h (ANCHOR / MEM_BARRIER)
See:                [feedback_anchor_breaks_loop_entry_merge]
```

### 3.8 Body-out-of-line loop — default-flag + uninit + late assign

```
ASM fingerprint:    `if (count != 0x20) {flag=0; body} else {flag=-1}` where the original has
                    the body OUT of line (`bne count,0x20,body`, `count*8` in the delay,
                    rd==rt addu) but ee-gcc inlines the body (`beq`)
C recipe:           default the SPECIAL value, leave the body flag UNINITIALIZED, assign late:
    int full;                              /* NOT `= 0` */
    ANCHOR(full);                          /* before the if -> displaces default move from bne delay */
    if (count == 0x20) full = -1;
    else { idx = count*8; ADDU_RT(addr,node,idx); full = 0; *store = val; }  /* full=0 AFTER the addu */
Why:                setting full in either branch first collapses the body inline; the
                    uninit+anchor+late-assign combo keeps it out-of-line. Last-insn placement
                    is a Haifa tie-break — was permuter-only until this lever was found.
See:                [feedback_loop_body_out_of_line_collapse], [feedback_branch_likely_emission]
```

### 3.9 Count-guarded pointer search — pre-decremented base guard

```
ASM fingerprint:    table scan returning the first matching element's pointer. ee-gcc rotates
                    the count==0 guard into a PRE-DECREMENTED pointer compare and advances in
                    the guard's delay slot:
                        addiu p,base,-STRIDE        # p = base - stride
                        addu  end,base,(cnt-1)*STR  # end = LAST element (reuses base's reg)
                        beq   p,end,ret0            # count==0 guard
                         addiu p,p,STRIDE           # DELAY: first advance -> p = base
                        nop                          # loop-alignment nop
                      loop: lw v; bnez v,found; daddu ret,p (bnez delay); bne p,end,loop; addiu p (delay)
C recipe:
    T *base = SYM; T *p = base - 1;
    T *end = (T *)((char *)base + (CNT * STRIDE - STRIDE));
    ANCHOR(p);                              /* break (base-1)+1 -> base fold; see Why */
    if (p == end) goto ret0;
    p++;
    NOP();                                  /* un-merge back-edge + supply alignment nop */
  loop:
    if (p->field != 0) return p;            /* DIRECT return -> reorg imports ret=p into bnez delay */
    if (p != end) { p++; goto loop; }
  ret0:
    return 0;
Why:                three coupled levers, each needed:
                    (1) ANCHOR(p) before the guard makes p opaque so gcc can't fold
                        (base-1)+1==base into a `daddu p,base` copy in the guard delay; with the
                        fold gone, base dies into `end` (end reuses base's reg, e.g. a0, instead
                        of a fresh a1) and the guard delay gets the real `addiu p,p,STRIDE`.
                    (2) NOP() AFTER `p++` (not before — a barrier between guard and p++ blocks
                        the advance from filling the beq delay) does double duty: volatile
                        boundary that un-merges the loop back-edge from the entry test (else gcc
                        collapses to `b loop_cond`, dropping 2 insns) AND emits the standalone
                        loop-alignment nop.
                    (3) DIRECT `return p` in the body (NOT `goto found; found: return p;`): the
                        goto form makes the found block `jr;daddu(jr-delay)`, so reorg can't lift
                        the daddu; the direct return leaves found as the importable first-op so
                        reorg pulls `daddu ret,p` into the bnez delay, found becomes `jr;nop`.
                    Was PARKED as a "pure regalloc/sched tail -> permuter" floor at rc 7; cracked
                    BY HAND 7->5->4->3->2->0. Pinning `end`=$4 or a separate guard temp both
                    rescramble the count/base loads — don't.
Headers:            matching.h (ANCHOR / NOP)
See:                [feedback_anchor_breaks_loop_entry_merge] (the inverse merge), [feedback_20_iter_discipline]
```

### 3.10 Indexed table search — keep the per-iter MULT + fix the mult/elem regalloc swap

```
ASM fingerprint:    array-of-structs scan with a per-iteration `mult i,STRIDE; addu elem,mult,base`
                    (NOT strength-reduced to a pointer walk), int index `i` with `sltu i,n`
                    loop test and `beqz n` count==0 guard (n UNSIGNED). Returns &arr[i] on a
                    multi-field match, else 0.
C recipe:
    register unsigned int n REG("$8") = COUNT; register unsigned int i REG("$6");
    register T *base REG("$7"); register int stride REG("$2");
    if (n == 0) goto ret0;
    i = 0;
    ANCHOR(i);                              /* (C) i=0 -> beqz delay slot, not the sunk base lw */
    base = BASE;
    do {
        T *e; register int f0 REG("$3");    /* (B) pin the FIELD LOAD, not the offset/elem */
        stride = 0x174;                     /* (A) in-loop reassign keeps the MULT */
        e = (T *)((char *)base + i * stride);
        f0 = e->unk0;
        if (f0 != 0 && e->unk4 == key) return e;
        i++;
    } while (i < n);
  ret0: return 0;
Why:                (A) ee-gcc strength-reduces `base + i*C` to an additive pointer walk by
                    default — but reassigning the multiplier INSIDE the loop (`stride=0x174`
                    each iter) makes it non-loop-invariant, so the MULT stays WITHOUT a per-file
                    `-fno-strength-reduce` (which would be the wrong tool — it's file-scoped and
                    a sibling in the same TU may need strength reduction; here ECA8 §3.9 does).
                    The hoisted first `stride=` lands before the loop; the per-iter reload fills
                    the back-edge (`bnez`) delay since the unk4 load clobbers $2.
                    (B) the original reuses the DEAD mult-result reg ($3/v1) for the unk0 load,
                    which forces the elem pointer to $5/a1. Pinning the offset intermediate to
                    $3 is IGNORED (the mflo reg is chosen before the pin coalesces) and pinning
                    the elem pointer to $5 emits a spurious `daddu a1,v1` COPY (the addu dest is
                    already allocated). Pin the FIELD LOAD instead: a load targets any reg
                    directly (no copy), and reusing $3 for it cascades the whole v1<->a1 swap
                    (mult->$3, elem->$5, both field loads, the returned ptr). rc 8 -> 2 in one line.
                    (C) gcc sinks the loop-invariant base `lw` below the count guard and reorg
                    hoists THAT (a load, latency) into the beqz delay; ANCHOR(i) right after `i=0`
                    materializes the cheap `daddu i,0,0` first so reorg picks it for the delay
                    and the base lw follows. rc 2 -> 0.
                    Was PARKED as "v1<->a1 regalloc + sched -> permuter (needs -fno-strength-reduce)";
                    cracked BY HAND with default flags.
Headers:            matching.h (ANCHOR) + regpin.h (REG)
See:                §3.9 (the pointer-walk sibling), [feedback_20_iter_discipline]
```

---

## 4. Conditional store / clamp

### 4.1 Store-then-conditionally-overwrite-with-0

ASM fingerprint: `bgez $v, .L; sw $v, D; sw $0, D; .L:` (store unclamped
in delay, overwrite on negative).

```c
v = a0 - 1;
D = v;                    /* unconditional store */
if (v < 0) D = 0;         /* conditional overwrite */
```

NOT `if (v<0) v=0; D=v;` — that compiles to `slt+movz`.
Examples: `grep -rn 'D = v;' src/` next to a `if (v < 0) D = 0;` (idiom
is rare and search-discoverable).
See: [feedback_store_then_clamp].

### 4.2 `sra X,2; srl X,2` (signed-then-unsigned shift)

**Diff fingerprint:** built has `movn`/`slt+movn` sign-correction for
signed division; expected has plain `sra X,N; srl X,N` two-shift form.

ASM fingerprint: two-shift sequence with mixed signedness in same basic
block.

```c
int diff = ...;
*ptr += (unsigned int)(diff >> 2) >> 2;
```

NOT `signed / 16` or `>> 4` on signed — produces sign-correction
`addiu/slt/movn` instead.
Examples: `grep -rn '(unsigned int)(.* >> 2) >> 2' src/`.
See: [feedback_sra_srl_combo].

### 4.3 `__builtin_abs(x)` for `bltzl + negu`

ASM fingerprint: `bltzl $v,L; negu $v,$v` (branch-likely abs).

```c
v = __builtin_abs(p[1]);
```

Pair with `MATERIALIZE` if there's a bool-merge on top.
Example: shares `func_001C0BF8` with §2.5 (sign-bound bool).
See: [feedback_materialize_barrier] note about `__builtin_abs`.

---

## 5. Pointer arithmetic & gp_rel

### 5.1 Symbol offset folded into addiu vs left on store

ASM fingerprint: original has `lui+addiu(D,0)+addu+sw $rT,N($r)`; built
has `lui+addiu(D,N)+addu+sw $rT,0($r)`.

```c
struct Slot { int pad[N/4]; int field; int pad2[STRIDE/4 - N/4 - 1]; };
extern struct Slot D_X[];
D_X[slot].field = v;        /* `.field` keeps offset on store side */
```

Examples: `grep -rn 'struct Slot\|\.field = ' src/` for current uses;
the recipe is most common in `D_X[idx].field = ...` shapes where the
diff is an `addiu base,base,N` vs `sw $rT,N(base)` swap.
See: [feedback_struct_member_offset].

### 5.2 `& ~0x3F` matches addiu — use `0xFFFFFFC0u` for lui+ori

**Diff fingerprint:** built has single `addiu $rT,$0,0xFFC0`; expected
has `lui $rT,0xFFFF` followed by `ori $rT,$rT,0xFFC0`.

ASM fingerprint: original uses `lui $r,0xFFFF; ori $r,$r,0xFFC0` (2 insns);
your build emits `addiu $r,$0,0xFFC0` (1 insn).

```c
D_X = (D_Y + 0x3F) & 0xFFFFFFC0u;        /* unsigned 32-bit literal */
```

`~0x3F` is `int -64`, sign-extends through addiu; the unsigned literal
forces the 2-insn materialize.
Example: `func_001F0DA8` (`streamMotionManager.c`) — alignment of
`D_00633728 + 0x3F` to 64 bytes.
See: [feedback_unsigned_mask_for_lui_ori].

### 5.3 gp_rel `addiu` vs `daddiu` (quick_diff false positive)

**Diff fingerprint:** built has `addiu` and expected has `daddiu` on a
`%gp_rel(...)` operand, otherwise identical. **This is a false
positive — commit as-is.**

ASM fingerprint: quick_diff shows ONLY `addiu` vs `daddiu` differences
for `%gp_rel(D_X)($gp)` address loads, everything else matches.

**Commit it.** Original ELF has `addiu`; splat's `la` pseudo reassembles
to `daddiu`. The discrepancy is in quick_diff's reassembly path.
Example: any function with `daddiu $rT, $gp, %gp_rel(D_X)` in quick_diff
(left/expected) vs `addiu $rT, $gp, %gp_rel(D_X)` (right/built).
See: [feedback_la_pseudo_quick_diff], [feedback_aent_breaks_ee_as].

### 5.4 Re-deref a pointer on every access (defeat CSE)

ASM fingerprint: same `lw $rT, OFF(base)` multiple times across an
if/else; gcc's natural C compilation CSEs it.

```c
first = *(char * volatile *)(a0 + 0x164);    /* volatile on inner ptr */
if (cond) {
    second = *(char * volatile *)(a0 + 0x164);
} else {
    second = *(char * volatile *)(a0 + 0x164);
}
```

Examples: see §2.4 `func_001CE6F0` (uses the same `char * volatile *`
cast pattern for the `self->_15C` reloads).
See: [feedback_volatile_ptr_cast].

### 5.5 Lock load order via volatile pointer cast (defeat gas reorder)

ASM fingerprint: a tight run of `lwc1`/`lw` loads where gas `.set reorder`
shuffles the order relative to source.

```c
volatile float *cp = (volatile float *)cb;
vx = cp[2];     /* lwc1 $f2, 8($s2) */
vy = cp[0];     /* lwc1 $f0, 0($s2) */
vz = cp[1];     /* lwc1 $f1, 4($s2) */
```

Example: `func_00181D88` (`attackhit.c`) — cb-block at function tail.
See: [feedback_volatile_ptr_load_order].

### 5.6 `extern` for cross-TU `%hi/%lo` references

Don't declare cross-TU data symbols `static`. Typed `D_<VMA>` defs that
are referenced via `%hi/%lo` from another TU must have external linkage,
or the relocation will go through `_gp` instead. See [feedback_data_symbols_extern].

### 5.7 Far in-TU small global referenced from C — asm-label alias

**Diff fingerprint:** link error `R_MIPS_GPREL16 truncated against D_X`, or a
`sw $v,gp_rel(D_X)` where the original has `lui $h,%hi(D_X); sw $v,%lo(D_X)($h)`.
Happens when a `≤ -G`-sized global is DEFINED in the same TU but lives at a FAR
address (not near `_gp`, e.g. 0x274EEC vs `_gp`=0x6388f0): ee-gcc small-datas it →
gp_rel → truncates. The original used `%hi/%lo` because the dev referenced it as
`extern` from a code TU (data in a separate object).

Do **not** move the def: `__attribute__((section(".data.D_X")))` and sidecar moves
both *shift the .data VMA* (`.data.0x*` sorts in a different lexical group than
`.data.D_*`, +0x100). Keep the def; reference through an incomplete-array
asm-label alias:
```c
unsigned int D_X = 7;                              /* keep the .sdata def */
extern unsigned int D_X_a[] __asm__("D_X");        /* alias: [] ⇒ %hi/%lo */
...
D_X_a[0] = v;                                      /* R_MIPS_HI16/LO16, no shift */
```
Verify: `objdump -dr build/<tu>.o | grep D_X` → want `R_MIPS_HI16/LO16`, not
`R_MIPS_GPREL16`. Example: `func_001383F8` (ios/memory.c), `D_00274EEC`.
See: [feedback_asm_label_alias_far_sdata], [feedback_sdata_small_symbol_force_data_section].

### 5.8 Base-fold address arithmetic to control copy/coalesce registers

**Diff fingerprint:** an array-of-structs element copy/access where the registers
differ (copy temps, dest register, an `addu sX,sX,vN` that clobbers the array base
vs `addu vN,vN,sX` that keeps it) — instructions otherwise identical.

The *grouping* of the field-pointer arithmetic in C decides gcc's CSE and therefore
the register coalescing:
```c
/* element-fold (naive): gcc CSEs the element ptr, reuses/clobbers the array base */
*(Blk*)dst = ((Elem*)BASE)[i].field;        /* (BASE + i*stride) + field_off */

/* base-fold (matches the dev): field offset folded into BASE early; gcc keeps the
   array base live, coalesces element→dest into the original's register */
*(Blk*)dst = *(Blk*)(BASE + field_off + i*stride);   /* (BASE+field_off) + i*stride */
```
Pair it correctly: keep *other* accesses to the same element struct-based
(`((Elem*)BASE)[i].other`) so the array base stays in its callee-saved reg.
Diagnostic harness: build the `.o`, grep first `sdl …(REG)` (dest reg) + first
`ldl REG` (temp1), and check for a forbidden `addu sX,sX,…` (base clobber).
Example: `func_001383F8` tail 0x40-byte copy — base-fold src + struct `f148`
gives dest=`$v0`, temps `$a2/$a3/$t0`. See: [feedback_basefold_copy_coalesce].
General method for these: [feedback_deterministic_source_shape_not_floors].

For lit4 / gp_rel data symbols defined in the **same TU** as an
`INCLUDE_ASM`'d function: declare them `extern` in a header and keep the
definition out of that TU until all sibling funcs are decompiled.
Otherwise `.text` grows by 4 bytes and you cascade a SHA diff.
Examples: `src/motionManager2` (commit eccdc21), `src/sound/s_init`,
`src/icoMisc`, `src/FileManager`, `src/DmaPacket` — all surveyed when
the rule was finalized.
See: [feedback_lit4_gp_rel], [feedback_data_symbols_extern].

### 5.9 Eager rodata pointer materialization (split `lui+addiu` away from jal)

**Diff fingerprint:** built clusters `lui $aN, hi; addiu $aN, $aN, lo; jal`
right at the call site; expected emits `lui+addiu` earlier (between the
preceding stores) so the jal's delay slot can be filled by an unrelated
op. tag_diff §5.9 fires.

**Why:** gcc treats a global address (`D_X`) as a const it can synthesize
anywhere — its scheduler picks the latest legal point, which is right
before the call. The original codegen sometimes emitted the address
materialization earlier (probably because the const was already
loaded into a register from an earlier expression). Capturing the
global into a local + `KEEP_LIVE` forces gcc to materialize the
address at the local's def site rather than at the call.

**Fix:**

```c
{
    int *p = D_X;
    KEEP_LIVE(p);
    /* ... other stores ... */
    func_target(arg0, p);   /* call uses p (already in a register) */
}
```

Headers: `#include "matching.h"`. The `KEEP_LIVE` is what prevents
gcc from re-CSE-ing the global address back to the call site.

Example: `func_001E9F08` (`rotObject.c`) — `D_00275860` passed to
`func_00105F00`; without the local capture, `lui $a1; addiu $a1`
emitted right before jal; with the capture, emitted between the
two preceding `swc1` stores (matching original).
See: [feedback_eager_rodata_materialize].

### 5.10 Far global across calls — direct array index hoists `%hi` to callee-saved

```
ASM fingerprint:    a far (non-gp_rel) global read in several BBs separated by calls; original
                    keeps `%hi(D_X)` in a callee-saved reg (`lui $sN,%hi; addiu $r,$sN,%lo`
                    per use). A cached pointer var collapses it to one reg → smaller frame →
                    a -0x10 cascade through every stack offset & branch target (dozens of
                    fake diffs, ONE root cause).
C recipe:           access as a DIRECT indexed array, NOT a cached pointer:
    extern int D_X[];
    ... D_X[6] ...; D_X[5] ...;            /* NOT `char *p = &D_X; *(int*)(p+0x18)` */
Why:                a pointer var caches the FULL address in one reg; direct `D_X[i]` keeps
                    only %hi (callee-saved) and re-folds %lo per access — like an array.
                    `(char*)&D_X + 0x18` does NOT work (still pointer arith); must be `D_X[i]`.
See:                [feedback_far_global_direct_index_hoists_hi], [feedback_eager_rodata_materialize],
                    [feedback_asm_label_alias_far_sdata]; for keeping a small .sdata sym
                    addressed lui+addiu (extern, not gp_rel), [feedback_sdata_extern_keeps_lui_addiu]
```

### 5.11 Suppress 64-bit value canonicalization (`dsll32/dsra32`)

```
ASM fingerprint:    spurious `dsll32 r,x,0; dsra32 r,r,0` around a 64-bit op, OR a missing one
C recipe:
    bit test on a 64-bit field — compare to the bit value, not truthiness:
        if ((*(long long *)p & BIT) == BIT)         /* NOT `& BIT` / `!= 0` */
    value reused in 32-bit arithmetic that the asm sign-extends first:
        long long ret = func(); p += ret; n -= ret; /* `long long` local reproduces the extend */
Why:                `!=0`/truthy tests force a clean DImode boolean (→ extend); `== <nonzero
                    const>` lets the combiner see the value is already canonical. A `long long`
                    local reproduces the sign-extend of an int value reused in arithmetic.
See:                [feedback_64bit_bittest_eq], [feedback_longlong_signext]
```

---

## 6. Unaligned and MMI

### 6.1 Unaligned 64-bit copy (ldl/ldr/sdl/sdr)

ASM fingerprint: `ldl $X,7($s); ldr $X,0($s); sdl $X,7($d); sdr $X,0($d)`.

```c
struct __attribute__((packed)) u64_packed { long long v; };

void f(int *dst_struct, struct u64_packed *src) {
    struct u64_packed *dst = (struct u64_packed *)dst_struct[OFFSET/4];
    dst->v = src->v;
}
```

`aligned(1)` typedef alone is NOT enough — the packed-struct form is what
flips the codegen.
Example: `func_0019F4E8`. The gp_rel variant of this shape needed an
asm-level rewrite — see §13 `postprocess_09F530.py` for `func_0019F530`.
See: [feedback_packed_struct_unaligned_64].

### 6.2 Non-VU `sq $a1, 0(p)` in a leaf

ASM fingerprint: `sq $5, 0($vN)` in a function whose C signature can't
name a 128-bit value.

```c
__asm__ __volatile__("sq $5, 0(%0)" : : "r"(p) : "memory");
```

Caller passes the qword in `$a1`; the C param list does **not** declare
the qword, so gcc treats it as caller-managed scratch. Pair with a
`__asm__("":::"memory")` barrier between subsequent sw stores so they
don't fall into the jr-ra delay slot.
Example: `func_00145258` (leaf: `q[0]=p+0x10; sq a1,p; q[5]=p`).
See: [feedback_sq_a1_inline].

### 6.3 `lwu` emission (ee-gcc 2.9 never emits it under any C)

ASM fingerprint: any `lwu` in the original.

```c
__asm__ __volatile__("lwu %0, 0xBC(%1)" : "=r"(v) : "r"(v1));
```

This is one of the few cases where raw `__asm__` is appropriate — but
the bodies must remain ONE INSTRUCTION per `__asm__` block, and they
belong in a header macro if they recur.
Examples: `func_0015F208`, `func_001BB7E0` (both had `.skip`'d funcs
that this pattern unblocked).
See: [feedback_inline_asm_single_line].

### 6.4 `sync` / `EI` (R5900 fences)

ASM fingerprint: bare `sync` or the `EI` instruction (encoded
`.word 0x42000038`).

```c
#include "r5900.h"
SYNC();              /* one `sync` opcode + memory clobber */
EI();                /* one `.word 0x42000038` (COP0 EI) */
```

Use as a fence between a write and an external observer (GS, IPU, VU,
DMAC). `EI` pairs with `SYNC` in EE-kernel critical-section exits.
See: `include/r5900.h`.

### 6.5 16-byte quadword copy (`lq` / `sq` via a scratch GPR)

ASM fingerprint: `lq $rX, 0($a1); sq $rX, 0($a0); [nop]` (single qword
copy through one scratch reg).

```c
#include "r5900.h"
void qcopy16(void *dst, void *src) {
    QCOPY16("$a2");           /* trailing nop included */
    /* or: QCOPY16_NO_NOP("$a2") when next func's first insn fills jr-ra delay */
}
```

Scratch reg is a string-literal arg because the original codegen picks a
different temp per call site. The dst/src come from gcc's natural $a0/$a1
calling convention.
See: `include/r5900.h`.

### 6.6 64-byte qword copy — serial (lq/sq/lq/sq through one reg)

ASM fingerprint: 4× `(lq $rX,N($a1); sq $rX,N($a0))` pairs with the same
scratch GPR for all 8 ops.

```c
#include "r5900.h"
void qcopy64_serial(void *dst, void *src) {
    QCOPY64_SERIAL("$a2");
}
```

See: `include/r5900.h`.

### 6.7 64-byte qword copy — parallel (4 lq, then 4 sq, latency-hiding)

ASM fingerprint: 4× `lq $sN,N($a1)` followed by 4× `sq $sN,N($a0)`,
each `lq`/`sq` pair using a distinct scratch reg.

```c
#include "r5900.h"
void qcopy64_par(void *dst, void *src) {
    QCOPY64_PARALLEL("$a2", "$a3", "$t0", "$t1");
    /* QCOPY64_PARALLEL_NO_NOP if the trailing nop is filled at link time */
}
```

Use whenever the qword block is large enough that the original codegen
schedules the loads ahead of the stores to hide load latency.
See: `include/r5900.h`.

### 6.8 Direct `lq`/`sq` to a C-named pointer

ASM fingerprint: a single `lq $a2, 0($rP)` or `sq $a2, 0($rP)` where
`$rP` is whatever GPR gcc assigned to a C pointer variable.

```c
#include "r5900.h"
LQ16_FROM(p);                 /* lq $a2, 0(p) */
SQ16_TO(p);                   /* sq $a2, 0(p) */
```

The `$a2` is pinned in the macro; do not declare a C variable that
collides with it.
See: `include/r5900.h`. Distinct from [feedback_sq_a1_inline] (which is
for the unusual case where `$a1` carries a caller-built qword the C can't
name).

### 6.9 EE scratchpad addressing (`| 0x20000000` on a pointer)

ASM fingerprint: `lui $a3, 0x2000; or $a0, $a0, $a3` at function entry,
followed by qword copies through `$a0`.

```c
#include "r5900.h"
void spr_copy(void *dst, void *src) {
    MAP_A0_TO_SPR();          /* lui $a3,0x2000; or $a0,$a0,$a3 */
    QCOPY64_SERIAL("$a2");    /* or PARALLEL */
}
```

Use as the prelude when copying into/from the EE 16 KB scratchpad
(physical 0x70000000 mapped into virtual via the OR mask).
Examples: `grep -rn MAP_A0_TO_SPR src/` for current call sites.
See: `include/r5900.h`.

### 6.10 64-byte `ld`/`sd` struct copy — batch vs serial (NOT qword)

ASM fingerprint: a `dst = *src` aggregate copy the original BATCHES (8×`ld`
into distinct regs, THEN 8×`sd` — latency-hiding) but your build SERIALIZES
(`ld $2,N($s); sd $2,M($sp); ld $3,...` reusing v0/v1). This is gcc
`move_by_pieces` losing to register pressure; NOT a `lq`/`sq` qword copy (§6.7).

Two independent levers, both required to batch (confirmed on ee-gcc 2.9):

```c
/* 1. type the SOURCE as a typed pointer PARAMETER (cast at the call site) */
void f(int *self, int i, WBody *src) {     /* NOT `int arg1` then (WBody*)arg1 */
    struct { ...; WBody body; } req;        /* stack-local dst */
    req.body = *src;                        /* plain struct-assign batches */
    ...
}
/* 2. do NOT pin the source pointer: a `register WBody *p REG("$18")` pin
   combined with a loop later in the function FORCES move_by_pieces serial.
   Drop it — gcc naturally allocates p→$18(s2) AND batches. */
```

Why: (1) ALIAS ANALYSIS — a typed pointer *parameter* is assumed not to alias
the stack `dst`, so sched1 hoists all 8 loads above the stores (batch); a
`(WBody*)int` cast or a typed *local* is treated conservatively → serial.
(2) The `REG()` pin + a loop is the combination that flips batch→serial (pin
alone, no loop, still batches). Do NOT use `__builtin_memcpy` — it takes the
block-move path but emits unaligned `ldl/ldr` unless the src type itself is
8-aligned (a cast-from-int isn't trusted).
Example: `func_001F34C8` (weapon.c) 73→24; residual is a separate $a0/self
coalescing tail (permuter). See `tough_nuts/func_001F34C8/notes.md`.
See: [feedback_struct_copy_batch_typed_param].

---

## 7. Float

### 7.1 Mixed int+float call, int arg in jal delay slot

ASM fingerprint: `mtc1 + lwc1 + jal target + lw $a0, OFF(...)` (int load
in jal delay) — but gcc emits int load *before* the floats.

```c
#include "matching.h"
{
    int x;
    float f12 = 3.0f;
    float f13 = D_XXX;
    KEEP_LIVE_FP2(f12, f13);   /* materialize floats FIRST */
    x = p[OFF / 4];
    func_target(x, f12, f13);
}
```

Example: `func_0019A8F0` (`queen.c`) — float-scaled tail-call shape.
See: [feedback_keep_live_fp].

### 7.2 Push a float op OUT of jr-ra delay slot

ASM fingerprint: `cvt.s.w f0,f0; jr ra; nop` (compute then nop in delay)
— but gcc emits `jr ra; cvt.s.w f0,f0`.

```c
#include "matching.h"
#include "regpin.h"
register float v REG("$f0");
v = (float)some_int;
__asm__ __volatile__("" : "+f"(v));   /* fp barrier */
NOP();
return v;
```

`"+f"(v)` is an in/out FP barrier; `NOP()` displaces the body insn out
of the delay slot.
Examples: `grep -rn '"+f"(' src/` for current uses (the trick is rare
enough that current call sites are the canonical references).
See: [feedback_fp_barrier_nop].

### 7.3 `fabsf` / `isnanf` / `copysignf` bit-twiddle

ASM fingerprint: `mfc1 + lui 0x7fff + ori 0xffff + and + mtc1 $f0` (no
`abs.s` instruction).

```c
#include "matching.h"
float fabsf(float x) { FABSF_BIT_TWIDDLE(x); /* returns */ }
```

The macro is a *function body*, not an expression — it executes the full
return. Use only in single-statement fabsf-shaped bodies. There are
sibling macros `COPYSIGNF_BIT_TWIDDLE` and `ISNANF_BIT_TWIDDLE`.
Examples: live in the EE math TU — grep `FABSF_BIT_TWIDDLE` /
`COPYSIGNF_BIT_TWIDDLE` / `ISNANF_BIT_TWIDDLE` under `src/` for the
current call sites.
See: `include/matching.h`.

### 7.4 FP branch (`bc1f`/`bc1t`) delay should be `nop` — extern-alias + dual barrier

```
ASM fingerprint:    ee-gcc fills a bc1f/bc1t delay by hoisting the branch-target's first insn
                    — often a `lwc1 $fN, gp_rel` of a `const float` threshold — where the
                    original left the delay a `nop`
C recipe:
    extern const float THRESH_a __asm__("D_0063112C");  /* alias -> real (non-rematerializable) load */
    if (x < THRESH_a) { MEM_BARRIER(); ... }             /* barrier at branch-target START */
    else { d = -d; MEM_BARRIER(); ... }                  /* and after the neg.s in the fall-through */
Headers:            matching.h (MEM_BARRIER)
Why:                a folded const is rematerializable, so MEM_BARRIER alone can't block it;
                    the extern-alias makes it a real load, then both barriers force `nop`.
Also:               discarded-return call before a read landing in v0 (expected v1)? declare
                    that callee `int` (not `void`) to reserve v0 for the dead return.
See:                [feedback_fp_branch_delay_alias_barrier], [feedback_fp_barrier_nop]
```

### 7.5 Pin FP args + `KEEP_LIVE_FP` before a volatile reload

```
ASM fingerprint:    a `lw $v0, OFF($a1)` volatile reload scheduled BETWEEN the `mov.s` ops for
                    a call's FP args, where the original keeps the mov.s contiguous, then the
                    reload, then the jal
C recipe:
    register float f1 REG("$f12") = a1;  register float f2 REG("$f13") = a2;  /* pin $f12..$f17 used */
    KEEP_LIVE_FP(f2); KEEP_LIVE_FP(f3); ...
    v0 = *(int * volatile *)(a1 + 0x15C);    /* reload AFTER the mov.s ops */
    func(f1, f2, f3, ...);
Headers:            regpin.h (REG), matching.h (KEEP_LIVE_FP)
Why:                the KEEP_LIVE_FP barriers materialize each FP value at its source position
                    so the later volatile load can't slide above them.
See:                [feedback_pin_fp_args_before_volatile_reload], [feedback_keep_live_fp]
```

---

## 8. Scheduler and postprocesses

When source-level tricks won't budge gcc's RTL-level decisions, fall back
to per-file flags or per-TU postprocesses. Both are gated by config files,
so a single bad fit doesn't pollute the whole build.

### 8.1 `-fno-schedule-insns` for TU-context regressions

Symptom: function matches standalone but diverges when bundled into a
multi-function TU. Prologue order shifts (e.g. `sd ra` lands between `lui`
and `addiu` in standalone, after both in TU).

Fix: add to `config/extra_cflags.txt`:

```
BASIC -fno-schedule-insns
```

Disables the *first-pass* scheduler only; second pass still runs.
Don't reach for `-fno-schedule-insns2` first — too coarse.
Examples (from current `config/extra_cflags.txt`): `BASIC` (covers
`func_001F6E00` in `src/Basic.c`), `func_00263F48` (`163F48`),
`func_001EF9A8` (`0EF9A8`).
See: [feedback_no_schedule_insns_for_tu_context].

### 8.2 `postprocess_unfold_ra_delay.py`

Symptom: `beq $X,$0,.L; ld $31, OFF($sp)` (gcc folded ra restore into
delay slot of early exit) vs original `beq + move $Y,$0` (zero-init in
delay slot, branch to full epilogue).

Fix: add TU basename to `config/unfold_ra_delay.txt`.
Example: TU `weapon` (`func_001F40D8` — count-check + linked-list init
loop). Sibling `func_001F41C8` doesn't need the pass (only one early
exit).
See: [feedback_unfold_ra_delay].

### 8.3 `ld $31` / `daddu $2,$0,$0` epilogue swap — **RETIRED, use C fix**

**Diff fingerprint:** built has `daddu $2,$0,$0` (or `move $2,$0`)
immediately BEFORE `ld $31, OFF($sp)`; expected has them in the
opposite order.

Symptom: original has `ld ra; daddu v0,$0,$0` ordering; gcc emits
`daddu v0,$0,$0; ld ra`. Triggered by multiple `return 0;` paths in a
single function; gcc fuses them with the daddu-first ordering, the
original used ld-ra-first.

**Fix in C:** convert multiple `return 0;` paths to a single one via
`goto end; ... end: return 0;`. Forces gcc to use a single epilogue
basic block with the ld-ra-first ordering.

```c
int func(char *p) {
    if (p == 0) goto end;       // was: return 0;
    ... loop body ...
end:
    return 0;
}
```

Examples (retired postprocess): `func_00135BB8` (linked-list traversal,
`src/cod/035BB8.c`); `func_00140048` (`sound/adpcm_init.c`).

Postprocess removed 2026-05-21 — `tools/postprocess_swap_zero_ret_ld_ra.py`
and `config/swap_zero_ret_ld_ra.txt` were deleted.
See: [feedback_swap_zero_ret_ld_ra].

### 8.4 `postprocess_early_epilogue_restore.py`

Symptom: gcc schedules `ld $31` and `ld $16` *late* — after the last
buf-store, sometimes between trailing volatile float stores. Original
schedules them earlier.

Fix: add TU basename to `config/early_epilogue_restore.txt`.
Example: TU `girlForceField` (`func_001D1C78` — allocator + reciprocal
+ float-store pattern).
See: [feedback_early_epilogue_restore].

### 8.5 `postprocess_fill_blez_delay.py`

**Diff fingerprint:** built has
`blez/bgez/bltz/bgtz/beql/bnel/...; nop; <insn>`; expected has the
`<insn>` directly in the branch's delay slot.

Symptom: gcc emits a `blez/bgez/bltz/bgtz/bnel/beql/...` followed by an
intended delay-slot fill, but gas (`.set reorder`) inserts a `nop`
instead and bumps the fill insn down.

Fix: add TU basename to `config/fill_blez_delay.txt`. The pass wraps the
branch+fill pair with `.set noreorder/.set reorder`. **Excludes
`bne`/`beq`** — original ICO codegen left those delay slots unfilled.
Examples: TU `weapon` (`func_001F4318` — outer registry-walk loop),
file `109E48` → `func_00209E48`.
See: [feedback_fill_blez_delay].

### 8.6 bne→bnel / beq→beql mnemonic — **RETIRED, gcc picks naturally now**

Historical symptom: original ELF used branch-likely (`bnel`/`beql`) but
ee-gcc 2.9's heuristic picked the plain variant. The cookbook used to
claim "no C-level fix shifts the choice."

**Status 2026-05-21:** the two gate entries (`func_0013C920`,
`func_0010A3A0`) both emit `bnel` natively under the current C source
in `src/cod/03C920.c` and `src/cod/00A3A0.c`. Postprocess removed —
`tools/postprocess_bne_to_bnel.py` and `config/bne_to_bnel.txt` deleted.

If a future near-miss is purely bne vs bnel (or beq vs beql) and gcc's
heuristic disagrees, restructure the loop body so the delay-slot
operation is genuinely safe to annul (e.g. a reload-for-next-iter
shape) — ee-gcc 2.9's current behavior picks the likely variant
correctly in those patterns.

### 8.7 `postprocess_lui_const_swap.py` — swap regalloc on a dead `lui`

Symptom: original codegen reuses the register that held a `%hi/%lo`
address for an adjacent `li $rC, K` (where `$rC` is only used by the
following `beq`/`bne` compare). gcc emits two distinct regs.

```
lui   $A, %hi(D)
lw    $B, %lo(D)($A)      ; last use of $A
li    $C, K
beq   $B, $C, L           ; only use of $C
```

The pass renames `$C → $A` (and the lone use in the branch). Conceptually
a §2 regalloc nudge, implemented at the asm level because no C
formulation reliably forces gcc to reuse the dead `lui` reg.

Fix: add basename to `config/lui_const_swap.txt`.
Example: `152180` → `func_00252180`.

### 8.8 `postprocess_lui_li_pre_sd.py` — lift `lui/li` ahead of `sd $ra`

Symptom: gcc emits the prologue as `subu sp; daddu $8,$5; sd $31; lui;
li; sw; daddu $5,$0; daddu $6,$0`; original interleaves
`subu sp; lui; li; daddu $8; sd $31; daddu $5; sw; daddu $6`. The
constant-materialize moves *before* the `sd $31` and the arg moves
straddle it.

Fix: per-func allowlist in `config/lui_li_pre_sd.txt`.
Example: `14D9E8` → `func_0024D9E8`.

### 8.9 `sd $ra` between `lui` and `addiu` — **RETIRED, use `LA_SPLIT` macro**

Symptom: original schedules the prologue ra-save between the two halves
of an `la $X, SYM` macro emission:

```
addiu $sp,-N; lui $X,%hi(SYM); sd $31,OFF($sp); addiu $X,$X,%lo(SYM)
```

gcc emits the lui+addiu pair back-to-back with `sd $31` after. Common in
leaf-prologue 5-arg-via-`$tN` wrappers (func_0024DA50 family).

**Fix in C:** use the `LA_SPLIT` macro from `include/matching.h`, which
emits the `lui` and `addiu` in two separate `#APP/#NO_APP` blocks with
a `KEEP_LIVE` between to prevent ee-gcc 2.9 from coalescing them. The
scheduler then places `sd $ra` in the gap.

```c
register T *p REG("$8");
LA_SPLIT(p, SYM);            /* lui + KEEP_LIVE + addiu */
KEEP_LIVE(p);                /* anchor regalloc */
```

Without the inner `KEEP_LIVE`, gcc may merge adjacent `#APP` blocks into
one when nothing else separates them (observed for `func_001F6E00` in
`src/Basic.c`). The two-block emission is what gives the scheduler room
to interleave `sd $ra`.

Examples (retired postprocess): `func_0024DA50` (`src/cod/14DA50.c`),
`func_0024DA20` (`src/cod/14DA20.c`), `func_001F6E00` (`src/Basic.c`).
Postprocess removed 2026-05-21 — `tools/postprocess_la_sd_interleave.py`
and `config/la_sd_interleave.txt` were deleted.

### 8.10 `postprocess_v0_zero_in_bne_delay.py` — lift `daddu $v0,$0,$0` into bne delay

Symptom: original ELF has a clean `ld $31; ld $sN; jr $31` epilogue and
the return-value clear (`daddu $2,$0,$0`) lives in the delay slot of the
early-exit `bne $2,$0,$L`. ee-gcc 2.9 with `-fno-schedule-insns` emits
the daddu between the epilogue restores; gas refuses to fill the bne
delay with a write to the bne's input reg even though MIPS semantics
allow it.

Fix: per-func allowlist in `config/v0_zero_in_bne_delay.txt`. The pass
removes the epilogue daddu and wraps the bne in `.set noreorder/nomacro`
so gas accepts the manual fill.
Examples: `165B28` → `func_00265B28`, `166870` → `func_00266870`.

### 8.11 commutative `addu` operand swap — partial C fix, partial sed

**Diff fingerprint:** `addu $X,$X,$Y` (built) vs `addu $X,$Y,$X`
(expected), or vice versa — commutative operand swap.

Symptom: original uses one operand order for a commutative `addu`; gcc
emits the other. Both compute `dst = a + b`, bytes differ.

**For rd==rs → rd==rt (swap_addu_to_rt direction): use inline asm with
the destination tied to operand 0 via `+r`:**

```c
register T *base ...; /* in rs slot */
register int idx ...;
__asm__("addu %0, %1, %2" : "+r"(idx) : "r"(base));
/* now idx = base + idx, encoded as addu idx,base,idx (rd==rt) */
```

The `+r` constraint pins `idx` as both input and output; gas places
it in both rd and rt. Successful examples: `func_0013FF88`
(`sound/adpcm_init.c`) and `func_001FBBE0` (`src/cod/0FBBE0.c`).
Postprocess `postprocess_swap_addu_to_rt.py` retired 2026-05-21.

**For rd==rt → rd==rs (swap_addu_operands direction): still a sed pass in
`tools/compile_c.sh`** — per-file allowlist `config/swap_addu_operands.txt`.
Examples: `0E8D30` → `func_001E8D30`, `0F1148` → `func_001F1148`,
`105A78` → `func_00205A78`.

### 8.12 `postprocess_no_trailing_nop.py` — suppress gas-inserted trailing nop

**Diff fingerprint:** built ends with `j $31` followed by `nop`;
expected ends with `j $31` only (delay slot filled at link time by the
next function's first instruction).

Symptom: function ends with `j $31`; gas in `.set reorder` appends a
`nop` in the delay slot, but the original ELF leaves it empty (the next
function's first insn fills it at link time). Function comes out 4 bytes
long.

Fix: per-file gate (config not externally documented in the script;
opt-in via the umbrella `config/no_trailing_nop.txt`). The pass wraps
the final `j $31` with `.set noreorder/.set reorder` to block the
auto-fill.
Examples: `03A220` → `func_0013A220`, `0B7218` → `func_001B7218`,
`011918` → `func_00111918`.

### 8.13 `postprocess_shared_sp_restore.py` — fall-through into shared epilogue stub

Symptom: original has a 4- or 8-byte "stub" function immediately after
the real one that consists of just `addiu sp,+N` (4-byte) or
`jr ra; addiu sp,+N` (8-byte). The preceding function falls through into
it, sharing the epilogue.

Two modes:
- `--sp-only`: strip the `addu $sp,$sp,N` from the `j $31` delay slot.
  Function ends at `j $31` with empty delay. Next func is the
  4-byte stub. Per-file allowlist in `config/shared_sp_restore.txt`.
- `--jr-and-sp`: strip the entire `j $31; addu $sp` block. Function
  ends at `ld $31`. Next func is the 8-byte `jr ra; addiu sp` stub.
  Per-file allowlist in `config/shared_jr_restore.txt`.

This is a cross-function optimization no C-level trick can reproduce.
Examples (sp-only): `094400` → `func_00194400` (consumer of stub
`func_00194438`); `037F48`, `037F90`. Examples (jr-and-sp): `094398`
→ `func_00194398` (consumer of stub `func_001943C0`); `038140`.

### 8.14 linked-list walk loop with both delay slots filled — **RETIRED, use C restructure**

Symptom: linked-list-walk loop where original codegen fills both delay
slots usefully (jal delay = next-pointer load, bne delay = arg setup
for next iter). gcc's natural emit has `jal; daddu (delay); lw (body);
nop; bne; daddu (delay)`.

**Fix in C:** advance the pointer EARLY (before the call), keep a
separate `prev` register-pinned to `$a0`, and add an explicit `NOP()`
between the initial arg-setup and the loop label for alignment:

```c
register int *s0 REG("$16");
register int *prev REG("$4");

if (s0 == 0) return;
prev = s0;
NOP();                              // align loop entry to .align 2
loop:
    s0 = (int *)s0[OFFSET / 4];     // advance — lands in jal-delay
    func(prev);
    if (s0 != 0) {
        prev = s0;                  // sets up $a0 — lands in bne-delay
        goto loop;
    }
```

ee-gcc 2.9 picks up the optimal scheduling because:
- `prev` is pinned to `$a0`, so `prev = s0` IS the `daddu $a0,s0,$0` insn;
- `s0 = s0[OFFSET/4]` between the call and the conditional advance gets
  scheduled into the jal delay slot;
- the loop-tail `prev = s0; goto loop;` fills the bne delay slot;
- the explicit `NOP()` before the loop label keeps the entry aligned.

Example (retired postprocess): `func_001FAA58` (`src/cod/0FAA58.c`).
Postprocess removed 2026-05-21 — `tools/postprocess_jal_daddu_lw_loop.py`
and `config/jal_daddu_lw_loop.txt` were deleted.

### 8.15 `postprocess_fcc_nop.py` — promote `#nop` comment to real `nop` after FCC compare

**Diff fingerprint:** built has `c.lt.s/c.le.s/c.eq.s/...` not
followed by a `nop`; expected has the required FCC hazard nop after.

Symptom: missing nop in the FCC hazard slot after `c.lt.s` / `c.le.s` /
`c.eq.s` (and `.d` variants). ee-gcc 2.9 emits a `#nop` *comment* trusting
the assembler to insert the real nop; ee-as 2.10 ignores comments and
the nop is missing in the encoded bytes. (Modern gas inserts it but
breaks the `move` macro encoding — see §12.4.)

Fix: per-file allowlist in `config/fcc_nop.txt`. The pass converts
`#nop` lines that follow an FCC compare into real `nop`s.
Examples: `00D360` → `func_0010D360`, `0C9078` → `func_001C9078`,
`13C540` → `func_0023C540`.

### 8.16 `postprocess_move_sw_v0_before_lds.py` — interleave v0-store between epilogue restores

Symptom: function returns a value AND stores it to a gp_rel symbol on
the way out. gcc emits `ld $31; ld $16; sw $0,SYM1; sw $v0,SYM2; sw $0,SYM3`;
original interleaves the v0-store between the restores:
`ld $31; sw $v0,SYM2; ld $16; sw $0,SYM1; sw $0,SYM3`.

Fix: per-func allowlist in `config/move_sw_v0_before_lds.txt`.
Example: `13F030` → `func_0023F030`.

### 8.17 sw pair around `j $31` — **RETIRED, use volatile cast**

Symptom: original has `sw $Z,OFF2($Y); j $31; sw $X,OFF1($Y)` (one
store before the tail-jr, one in the delay slot); gcc emits the same
two stores in the opposite order. Different stores so no aliasing,
identical semantics, different bytes.

**Fix in C:** mark both stores with `*(volatile T *)&` casts. The
volatile qualifier forces gcc to keep source order for both writes,
which matches the original codegen.

```c
int func(int a0, int a1) {
    int old = D_X[5];
    *(volatile int *)&D_X[6] = a1;   // was: D_X[6] = a1;
    *(volatile int *)&D_X[5] = a0;   // was: D_X[5] = a0;
    return old;
}
```

Examples (retired postprocess): `func_0024BB90` (`src/cod/14BB90.c`,
getset on `D_00717758[5]/[6]`), `func_0024BBA8` (`src/cod/14BBA8.c`,
getset on `D_00717758[3]/[4]`).

Postprocess removed 2026-05-21 — `tools/postprocess_sw_pair.py` and
`config/swap_sw_pair.txt` were deleted.

### 8.18 `postprocess_early_body_swap.py` — body insn between sp-adjust and ra-save

Symptom: original schedules a single body instruction (`daddu $3,$4,$0`
copying $a0 to $v1, typically) between the prologue's `addiu sp,-N` and
`sd $31`. ee-gcc 2.9 always emits `sd $31` immediately after the
sp-adjust.

Fix: triggers when there's an `#APP/#NO_APP` block holding that single
body insn between sp-adjust and sd $31. Per-file allowlist in
`config/early_body_swap.txt`. To produce the `#APP` block, emit the body
insn from a one-line inline-asm at function entry — that's the C-level
mechanism that wires up to this postprocess.
Examples: `037F08` → `func_00137F08`, `037F48`, `037F90` (sibling family).

### 8.19 `coalesce_v1_v0` (sed pass in `tools/compile_c.sh`)

Symptom: original keeps a value in `$v0` throughout a "load global,
modify, store global, return" pattern; gcc splits it across `$v1` (load,
modify, store) and `$v0` (the return), bridged by a redundant
`move $2, $3` near the epilogue. Function comes out 1 insn long.

Fix: per-file allowlist in `config/coalesce_v1_v0.txt`. The sed pass
drops the `move $2,$3` line and renames `$3 → $2` across the function.
Safe only when `$v1` is not used elsewhere in the function (the
allowlist is conservative).
Examples: `005258` → `func_00105258` (`++D_00631B40`),
`005268` → `func_00105268` (`--D_00631B40`).

### 8.20 `postprocess_dummy_sp_prologue.py` — inject a dead `addiu sp, sp, 16`

Symptom: original has a no-op `addiu $sp, $sp, 16` immediately before
the real prologue sp-adjust. ee-gcc 2.9 sometimes left this dead
prologue insn at function head; modern ee-gcc never does.

Fix: per-file allowlist in `config/dummy_sp_prologue.txt`. Also lowers
function `.p2align` from 3 to 2 since the inserted insn shifts the
function's natural alignment (e.g. func_0023C17C sits at mod-8 = 4).
Example: `13C17C` → `func_0023C17C`.

### 8.21 `postprocess_fill_beq_delay.py` — wrap `beq`/`bne` so gas fills the delay slot

**Diff fingerprint:** `beq $X,$Y,$L; nop; <sw/insn>` (built) vs
`beq $X,$Y,$L; <sw/insn>` (expected, sw lives in delay slot).

Sibling of §8.5 `fill_blez_delay`, but for the plain `beq`/`bne`
families that §8.5 deliberately excludes. Most original ICO codegen
leaves `beq`/`bne` delay slots empty, but a handful of functions had a
real fill that ee-as 2.10 won't pack — the function comes out 4 bytes
too long with a `nop` between the branch and the would-be-delay insn.

Symptom: gcc emitted `beq $X, $Y, $L` directly followed by an
instruction (typically a store) that should land in the delay slot.
ee-as 2.10 conservatively inserts a `nop` instead of packing the next
insn. Built function is 4 bytes longer than expected and shifts every
subsequent address.

Fix: add the TU basename or file_off to `config/fill_beq_delay.txt`.
The pass wraps the branch+fill pair with `.set noreorder/.set reorder`
so gas honours gcc's emit order verbatim. Stores are always
delay-slot-safe relative to the branch's compare registers because the
store reads its source before the branch fires.

Example: TU `kanban` (`func_001B04E0` — doubly-linked-list unlink with
a `beq $v0, $0, .L; sw $v0, 0x18($v1)` pair gcc-intended but ee-as
left as `beq; nop; sw`).

### 8.22 `swc1` in jal delay slot — memory barrier before the call

**Diff fingerprint:** `jal X; swc1 $fN, OFF(...)` (built) vs
`jal X; <addiu/lw/mov>` (expected) — gcc fills the jal's delay slot
with an unrelated trailing store from the preceding block; original
codegen has the call-arg setup (addiu/lw) in the delay instead.
tag_diff §8.22 fires.

**Why:** gcc's scheduler considers every "movable" instruction near
the call as a candidate for the delay slot. A `swc1` store that
doesn't depend on the call-target's args is a perfectly legal pick.
The original codegen evidently considered the call-arg setup more
attractive (likely because the helper that emitted this code didn't
hoist trailing stores into delay slots in the first place).

**Fix:** insert a memory barrier between the trailing store and the
call so gcc can no longer treat that store as movable past the
sequence point:

```c
*(float *)((char *)obj + 0x28) = v_28;
*(float *)((char *)obj + 0x2C) = v_2c;
__asm__ __volatile__("" : : : "memory");
func_target(arg0, arg1);
```

Alternative: mark the stores `volatile` (`*(volatile float *)...`).
Both work; the explicit barrier is preferred when several stores
need to be locked in place at once (the volatile cast only locks
its single store relative to other volatile-accessed memory).

Example: `func_001E9F08` (`rotObject.c`) — `swc1 $f0, 44(s0)` was
landing in `jal func_00105F00`'s delay slot; the memory barrier
moved it before the jal and let the `addiu a0, a0, 160` (= the
helper's 2nd-arg construction) fill the slot.
See: [feedback_memory_barrier_before_call].

> All postprocesses are run by both `tools/compile_c.sh` and
> `tools/quick_diff.sh`, so quick_diff sees the same bytes ninja will.
> ([feedback_matching_quick_diff_only], [feedback_early_epilogue_restore])

> **When to write a new postprocess vs. fight gcc with C tricks:** if
> the diff is purely an instruction ordering / branch-mnemonic /
> operand-swap issue and at least 3 unrelated source-level attempts
> (register pins, MATERIALIZE, volatile, goto reshape) have failed,
> the answer is a postprocess. See §13 for one-off per-function
> postprocesses that document the threshold for going custom.

### 8.23 `MEM_BARRIER()` AFTER a loop — keep call-arg out of the bne delay

```
ASM fingerprint:    a loop whose back-edge delay should hold the loop's OWN latch copy
                    (`daddu c,nc`), but ee-gcc hoists the following call's arg setup
                    (`move a0,sN`) into the bne delay
C recipe:
    } while (nc != 0);
    MEM_BARRIER();                 /* matching.h */
    return func(a0, buf);
Why:                opposite direction to §8.22 — that PUSHES call-arg setup INTO a delay;
                    this KEEPS it OUT so the loop's own op wins the slot. (bne/beq are
                    excluded from the fill_blez_delay postprocess, so this is a C fix.)
See:                [feedback_barrier_after_loop_protect_bne_delay], §8.22
```

### 8.24 `MEM_BARRIER()` before the next loop's `la` — restore a `bgez` nop delay

```
ASM fingerprint:    back-to-back clear loops; original leaves `bgez $cnt` delay = NOP (the
                    next loop's counter reset writes $cnt — a taken-path hazard), but ee-gcc
                    emits the next loop's `la $reg` first → gas fills the delay → function
                    short → ninja MISMATCH (quick_diff false-passes)
C recipe:
    i = 1; MEM_BARRIER(); q = (int *)(base + 0x58);   /* counter reset emitted before the la */
    do { *q = 0; q = (int *)((char *)q - 0x58); } while (--i >= 0);
Why:                only when the original's post-`bgez` insn is a same-register hazard.
                    Confirm size shifts with a full-build `.o` byte/size compare — quick_diff
                    can't see them.
See:                [feedback_membar_counter_reset_bgez_nop], §8.5
```

### 8.25 Source-reorder the hoisted last store (zeroing-run + tail call)

```
ASM fingerprint:    a run of zeroing stores ending in a tail call (`j func` with a store in
                    the delay); ee-gcc's first-pass scheduler HOISTS the source-last store to
                    ~position 2
C recipe:           read the expected emitted order; the store at expected position 2 is the
                    hoist victim → put it LAST in source; keep every other store in order.
Why:                emitted order ≠ source order — gcc moves exactly one store (the last) to
                    the front, and the new source-last store falls into the branch delay.
See:                [feedback_scheduler_hoist_last_store], [feedback_demote_p2align]
```

### 8.26 Union to force narrow-store / wide-access order (no barrier)

```
ASM fingerprint:    a narrow `*(int*)(p+4)=v` store and an overlapping `*(long long*)p`
                    access that ee-gcc reorders (treats int vs long long as non-aliasing →
                    floats the `ld` above the `sw`)
C recipe:
    union U { long long ll; int i[2]; } *p = (union U *)a0;
    p->i[1] = 1;                              /* the +4 int store */
    p->ll = (p->ll & ~1LL) | (a1 & 1);        /* the 64-bit access — stays AFTER */
Why:                union members provably alias → gcc keeps source order WITHOUT a barrier
                    (and a barrier would over-anchor the following and/or early). Cf §8.22.
See:                [feedback_union_alias_order]
```

### 8.27 fn-ptr chain walk — node-first + early-advance → `beq` not `beql`

```
ASM fingerprint:    walk `node = node->next` calling `(*self[8])(node, self[0xC])`, then
                    `self[0]=0`; the early exits + loop exit converge on the store, so gcc
                    cross-jumps it into `beql` annul slots (expected: plain `beq`)
C recipe:
    int *node = self[0];                       /* load node BEFORE the fn==0 check */
    if (self[8] == 0) goto done;
    do {
        int *cur = node;
        node = (int *)node[0x34/4];             /* advance BEFORE the call */
        (*(void(**)(int,int))((char *)self+8))((int)cur, self[0xC/4]);
    } while (node != 0);
    done: self[0] = 0;
Why:                node-first fills the fn-check beq delay; early-advance rotates the loop so
                    the node-check beq fills from the body and the advance lands in the jalr delay.
See:                [feedback_fnptr_walk_early_advance], §8.14
```

### 8.28 goto-loop `{}` block to choose the jal-delay fill

```
ASM fingerprint:    per-iter call loop where `--i` (not `p += stride`) should fill the jal delay
C recipe:
    loop:
        p[0] = 0;
        { int *arg = p + N; p += stride; func(arg); }   /* advance is call SETUP -> before jal */
        --i;                                             /* post-call body -> jal delay */
        if (i != 0) goto loop;
Why:                the brace block signals "advance is part of call setup"; `--i` after the
                    call but before the test is independent of the args → cheap delay fill.
See:                [feedback_goto_loop_jal_delay_choice], [feedback_jal_daddu_lw_loop_advance] (§8.14)
```

### 8.29 Separate base-ptr local beats self-mutation (bne-delay + regalloc)

```
ASM fingerprint:    "advance a base then index it twice" (`g = self+8; g[idx]; g[n]`) where
                    `self += 4` self-mutation fills the bne-delay with `idx*4` and loses the
                    s0/s1 param↔idx tie (expected: the advance fills the delay)
C recipe:
    int *voices = (int *)((char *)self + 8);          /* separate local, NOT self += */
    ... voices[idx] ...;
    voices = (int *)((char *)voices + n*4);           /* compound advance for the LAST access */
    ... *voices ...;
Why:                self-mutation fragments self's live range; a separate pointer local keeps
                    it intact, flips the bne-delay to the advance, and fixes the v0/v1 pick.
                    Combine with ADDU_RT (§8.11, rt==rd direction), an `int` (not `void`)
                    discarded-return callee (§7.4) to push the next load to v1, and inverted
                    cond so the partial path is inline (§3.6). MUST ninja-verify.
See:                [feedback_voices_pointer_vs_self_mutation], [feedback_addu_rt_macro]
```

### 8.30 Feedback ↔ recipe index (techniques documented under existing sections)

These memories map to recipes that already exist; cited here so a memory search resolves
into the cookbook even though the section above doesn't name the feedback:

- [feedback_jal_daddu_lw_loop_advance] → §8.14 (linked-list walk, early advance + `NOP()`)
- [feedback_volatile_cast_paired_sw] → §8.17 (two `sw` swapped around `j $31`: `*(volatile T*)&` on both)
- [feedback_la_split_macro] → §8.9 (`LA_SPLIT(reg, sym)` for `sd $ra` between `lui`/`addiu`)
- [feedback_addu_rt_macro] → §8.11 (`ADDU_RT(dst,src)` for rd==rt commutative `addu`)
- [feedback_goto_end_fuses_returns] → §8.3 (single `goto end` to fuse multiple `return 0`)
- [feedback_fno_schedule_insns_native_beql] → §8.1 (per-file `-fno-schedule-insns` → native `beql`)
- [feedback_fcc_nop_noreorder_guard] → §8.15 (`postprocess_fcc_nop` only fires under `.set noreorder`)
- [feedback_compound_assignment] → §2 (prefer `+=`/`++` over `x = x + 1`)
- [feedback_deterministic_source_shape_not_floors] → §11 (regalloc/sched diffs are SOURCE-SHAPE, not floors)

---

## 9. Frame and stack

### 9.1 Frame is 0x10 too small — add a `volatile int pad`

Symptom: quick_diff shows correct insns but the frame is 0x10 short
(e.g. 0x30 vs 0x40).

```c
volatile int pad;       /* reserves slot; no sw/lw because nothing reads it */
```

NOT `int pad;` (eliminated) and NOT `volatile int pad = arg;` (forces sw).
Example: `func_001F0878` (matched 2026-05-13).
See: [feedback_volatile_pad_frame].

### 9.2 Force a local-array spill that gcc would normally elide

Symptom: original has `swc1/sw` stores to `sp+OFF` for a small local
array, no matching reads (e.g. vec3 swap via a temp).

```c
void f(float *a, float *b) {
    float tmp[3];
    tmp[0]=a[0]; tmp[1]=a[1]; tmp[2]=a[2];
    a[0]=b[0]; a[1]=b[1]; a[2]=b[2];
    b[0]=tmp[0]; b[1]=tmp[1]; b[2]=tmp[2];
    __asm__ __volatile__("" : : "r"(tmp) : "memory");
}
```

The `"r"(tmp)` materializes the address into a GPR, forcing stack
residency. (This is one of the few legitimate inline-asm uses in src/;
when it recurs, fold it into a macro in `matching.h`.)
Example: `0948A8` → `func_001948A8` (vec3 swap).
See: [feedback_force_stack_temp].

### 9.3 Loop-invariant constant emit order

Symptom: original emits `sll $rI,$rI,3; li $rC,1`; gcc emits
`li $rC,1; sll $rI,$rI,3`.

```c
do {
    e = (T *)(i << 3);
    const_one = 1;       /* declared with REG() pin pre-loop */
    ...
} while (i < count);
```

gcc hoists `const_one = 1;` back out of the loop but emits it *after*
the in-loop `sll`.
Example: `func_001BBDD8` (`attackCheckBoundary.c`) — last 2 of 14
byte diffs cracked by this trick.
See: [feedback_const_in_loop_for_emit_order].

---

## 10. Classifier — `tools/classify_asm.py`

**Not yet implemented.** This section documents the intended contract so
both humans and a future implementation know what to feed it.

### Input

```
tools/classify_asm.py asm/nonmatchings/<TU>/func_<addr>.s
tools/classify_asm.py --bucket asm/nonmatchings/<TU>/    # whole TU
```

### Output

```
$ tools/classify_asm.py asm/nonmatchings/foo/func_00112233.s

func_00112233.s — 24 insns, frame=0x20, 1 jal, no MMI, no FP

Top recipes:
  1.2 1-jal wrapper with spill+reload     [confidence: 0.9]
      fingerprint matched: `sw $a0,0(sp)` + `lw $a0,0(sp)` + `jal`
      see decomp/COOKBOOK.md#12

  5.2 lui+ori for 32-bit mask             [confidence: 0.4]
      fingerprint matched: `lui $r,0xFFFF; ori $r,$r,0xFFC0`
      see decomp/COOKBOOK.md#52

Compiler-bias warnings:
  - bnel detected: branch-likely heuristic may differ; if final diff is
    purely beql/bnel, park (see 3.3)
```

### Fingerprint dimensions (what to extract from the .s)

The classifier should compute these signals from a single pass over the
`.s`. Each is a primitive a recipe-matcher rule can test against.

| Signal | Source | Example uses |
|--------|--------|--------------|
| insn count | line count post-comment-strip | "leaf-ish?" |
| frame size | first `addiu $sp,$sp,-N` | 1.2, 9.1 |
| jal count | `grep -c '^\s*jal '` | 1.x bucket selection |
| sibcall (`j FUNC`) | `grep '\bj func_'` | 1.1 vs 1.5 |
| tail-call delay shape | last 3 insns | 1.5, 1.6 |
| branch-likely set | `grep -E '\b(beql|bnel|blezl|bgezl|bltzl|bgtzl)\b'` | 3.x, 8.5 |
| MMI ops | `grep -E '\b(sq|lq|pextlw|pmaddh|...)\b'` | 6.2 |
| unaligned LL set | `grep -E '\b(ldl|ldr|sdl|sdr)\b'` | 6.1 |
| FP ops | `grep -E '\b(mtc1|mfc1|lwc1|swc1|cvt|mul\.s|...)\b'` | §7 |
| gp_rel uses | `grep '%gp_rel'` | 5.3, 5.6 |
| MMI / VU0 / scratchpad refs | regex set | "is this VU territory?" |
| arg-save run | consecutive `sd $aN,OFF($sp)` count | 1.7 |
| post-jal `daddu $v1,$v0,$0` | regex | 2.1 |
| early-exit + `ld $31` in delay | regex pair | 8.2 |

### Recipe-matcher rule shape

Each recipe in §1-9 corresponds to a rule:

```python
{
  "id": "1.2",
  "name": "1-jal wrapper with spill+reload",
  "fingerprint": [
    ("jal_count", "==", 1),
    ("regex", r"sw\s+\$a0,\s*0\(\$sp\)"),
    ("regex", r"lw\s+\$a0,\s*0\(\$sp\)"),
    ("frame_size_in", (0x10, 0x40)),
  ],
  "weight": 0.9,
  "see": "decomp/COOKBOOK.md#12",
}
```

Confidence = sum(weight) of all fingerprints that fire, normalized.

### Out of scope (deliberately)

- Auto-generating C. The classifier picks recipes; the human (or a
  permuter run) writes the C. We do **not** want a "match-bot."
- Reading the original ELF. The classifier sees only the splat-emitted
  `.s`. Anything that requires baserom bytes belongs in `quick_diff` /
  `first_diff`, not here.

---

## 11. Park, permute, defer

If a recipe doesn't crack it inside ~10 minutes of source-level tweaks,
stop iterating and switch tools:

1. **Park.** `tools/park.sh 0x<VRAM> "<short reason>"`. Moves the .c into
   `tough_nuts/<func>/` with `notes.md`. **Never `rm src/cod/<file>.c`** —
   even a 1-insn-off seed is useful permuter input.
   ([feedback_park_failed_matches])
2. **Permute.** `tools/auto_permute.sh` iterates over the parked seed
   randomly. Check `lib/decomp-permuter/runs/<func>/output-0-N/score.txt`
   for `0` — score-0 outputs in `output-0-1` and higher are real matches
   that the dashboard silently misses. ([feedback_score0_promotion])
   For a *single* near-match (esp. a store-then-clamp / branch-likely TAIL
   that resists ~20 source forms), drive it directly:
   `tools/permute_run.sh <func> tough_nuts/<func>/<func>.c -- --stop-on-zero -j 4`
   — seed WITH the `REG()`/`ANCHOR()` pins + `#include "matching.h"/"regpin.h"`,
   `git checkout` the tracked TU first to keep the tree green, background it.
   It auto-resolves `asm/nonmatchings/<TU>/<func>.s` and uses the project
   ee-gcc 2.9-991111, so a zero score is ninja-real; translate
   `runs/<func>/output-0-1/source.c` (`asm("$N")`→`REG()`, `asm("":"+r"(x))`→
   `ANCHOR(x)`) back in and ninja-verify. A typical lever it finds: reuse a
   now-dead reg for a load placed BEFORE the dependent add.
   ([feedback_permuter_cracks_reorg_tail]; for a count-down/-fno-strength-reduce
   seed pass it via `CFLAGS=`, [feedback_base_copy_pin_and_countup_flag])
3. **Defer.** Add to `docs/MATCHING_NOTES.md` with a short pattern
   description and move on. Class-level blockers (whole families) need
   one tough_nut as a representative, not one per function.

Branch-likely-only diffs ([3.3]) should be parked, not retried with flipped
conditions.

---

## 12. Build-system gotchas (not C-level)

These are cookbook entries for *the build*, not for the C. Recipes here
fix `.s`/`.ld`/yaml problems, not codegen.

### 12.1 `.aent` breaks ee-as 2.10 → silent fallback to modern-as

Symptom: 1-4 single-byte diffs at offset+3 of word boundaries
(0x27 → 0x67 high opcode byte = `addiu` → `daddiu`).

Cause: an `alabel` somewhere expanded to `.aent`, ee-as failed, fallback
to modern-as canonicalized `la` → `daddiu`.

Fix already applied: `.aent` stripped from `include/labels.inc` and
`include/macro.inc`. If symptoms recur, grep for `\.aent` and remove.
Example: TU `way_tool` (~17 `INCLUDE_ASM` funcs with `alabel` calls)
was where this surfaced.
See: [feedback_aent_breaks_ee_as].

### 12.2 Splat lost a function symbol after subseg split

Symptom: `tools/build.sh setup` errors with `can't open
asm/.../func_<X>.s` and the preceding func's `.s` is oversized.

Fix: add an explicit entry to `config/symbol_addrs.us.txt`:

```
func_00167280 = 0x00167280; // type:func size:0x2A4
```

**Caveat:** `size:0x4` on small/trampoline funcs causes spim to *stop*
scanning after — omit the size field for ≤16-byte funcs. See full
discussion in [feedback_splat_lost_symbol].

Example: `fieldCollision` coalesce (2026-05-17) — splat absorbed
`func_00167280` (size 0x2A4) into `func_00167278.s` (size 0x8 → grew
to 0x2AC). Symbol-addr entry restored the boundary.

### 12.3 `INCLUDE_ASM_NOP_PAD` after another `INCLUDE_ASM`

Don't. Splat bundles the trailing pad nop into the preceding `.s`
already. Adding `INCLUDE_ASM_NOP_PAD` after an `INCLUDE_ASM` doubles the
pad → +4 bytes in `.text` → cascades through `ALIGN(0x10)` between
sections → ~1.4 MB SHA cascade.

Only emit `INCLUDE_ASM_NOP_PAD` when the preceding TU slot is a *matched
C body* (which has no trailing nop).
Example: TU `s_init` (`sound/s_init.c`) — `func_00143D14` `NOP_PAD`
after `INCLUDE_ASM(func_00143CD0)` caused +0x10 shift of `D_00274700`
and a 1.45 MB SHA cascade.
See: [feedback_nop_pad_after_include_asm].

### 12.4 `use_modern_as.txt` — fall back to modern gas for VU0 / MMI TUs

Default assembler is ee-as 2.10 (from the bundled `ee-gcc 2.96` tarball)
because it matches the original ICO codegen for `la` macros and the
zero-register-move (`move` → `daddu $r,$s,$0`, not `or`). But ee-as 2.10
predates several R5900 VU0 / MMI ops and rejects them outright.

TUs containing such ops must opt into modern `mips-linux-gnu-as` via
`config/use_modern_as.txt` (one TU basename per line). Modern gas
canonicalizes `move` to `or` and `la` to `daddiu`, which means those TUs
*also* need to compensate elsewhere:

- For `la` → `daddiu` differences on gp_rel address loads: handled
  globally by `postprocess_asm.patch_la_gp_rel_nonmatchings` (§12.5).
- For `move $r,$s` → `or` differences: handled by the inline sed in
  `compile_c.sh` that rewrites `move` to `daddu $r,$s,$0` *after* the
  C compile but *before* the assembler, so both assemblers see the
  same explicit `daddu` and agree on the encoding.

Examples: `018A68` → `func_00118A68` (VU0 `vrnext`/`vsubw`/`qmfc2.ni`),
`0986A8` → `func_001986A8` (VU0 `vmulax`/`vmadday`/`vmaddaz`),
`0902D8` → `func_001902D8` (`c.lt.s`/`bc1tl` FCC hazard nop only
inserted by `mips-linux-gnu-as`).

### 12.5 `postprocess_asm.py` — the umbrella post-splat fixup

Run once by `tools/build.sh setup` after `splat split`. Four jobs:

1. **`.sdata` tail truncation.** Splat 0.40.0 rounds the last data
   symbol down to `.word`, dropping 2 bytes ("E\0", completing "FALSE\0")
   at 0x633BC4. Patches `asm/data/cod/531900.sdata.s` to emit those
   bytes explicitly.
2. **`%gp_rel($gp)` rewrite under `asm/matchings/`.** Splat emits
   per-function gp_rel loads as `lw $rT, (SYM) /* gp_rel: (SYM) */` —
   bare-paren form. Under `.set noat` modern gas tries to expand that
   as a $at-using macro and errors. The pass rewrites it to
   `%gp_rel(SYM)($gp) /* ... */` which encodes to the correct gp_rel
   bytes and assembles cleanly.
3. **VU0 special-reg dollar-prefix.** Splat 0.40.0 emits `ACC`, `Q`,
   `R`, `I` bare on VU instruction lines under per-function `.s`;
   modern gas requires `$ACC`/`$Q`/`$R`/`$I`. Rewritten in-place.
4. **`la` → `.4byte 0x<INSN>` for nonmatchings.** When a TU falls back
   to modern gas (§12.4), the bundled splat `la $rT, (SYM)` pseudo
   expands to `daddiu` instead of the original `addiu`. The pass
   replaces those `la` pseudos with the original 4-byte encoding
   pulled from splat's per-instruction comment. Trade-off: loses the
   relocation entry, fine because the gp_rel offset is fixed by the
   baseline link layout.

This file is the right place to add new splat-output rewrites. If
splat's emission shape changes in a future upgrade, each step prints a
warning rather than silently re-introducing a diff.
Example anchor: `asm/data/cod/531900.sdata.s` — the file the sdata-tail
fix targets. The 2-byte tail completes the asciz `"FALSE\0"` at
`0x00633BC4`.

---

## 13. One-off per-function postprocesses

Files matching `tools/postprocess_<FILE_OFF>.py` (six hex digits, no
keyword) are surgical rewrites of a single function's `.s`. They exist
when the diff is *exactly one specific instruction-ordering pattern*
that:

1. No source-level C trick (register pin, MATERIALIZE, volatile,
   goto reshape, varargs builtin, etc.) reproduced.
2. No general postprocess covers, *and* the shape isn't general enough
   to be worth promoting to one (only this function in the codebase
   has it).

**Catalogue (as of 2026-05-19):**

| Script | Function | Pattern fixed |
|--------|----------|----------------|
| ~~`postprocess_00A3A0.py`~~ | `func_0010A3A0` | **Retired 2026-05-22** — restructure as `goto loop;` with `p[0]=0` inside the loop body and `p += 8` between `call_arg=p+4` and the call. ee-gcc 2.9 then puts `--i` in the jal delay naturally. |
| `postprocess_01BF60.py` | `func_0011BF60` | Inner loop schedule rewrite — `li $5,4` before jal, `addu $17,$17,16` in jal delay, `daddu $4,$17,$0` in bne delay. |
| `postprocess_080550.py` | `func_00180550` | Move `li $5,1` into the tail-call `j SYM`'s delay slot, ahead of the `mov.s` setup. |
| `postprocess_094630.py` | `func_00194630` | Move `sd $31; daddu $4,$sp,$0` before a `sw $0,4($sp)` in the prologue. |
| `postprocess_09F530.py` | `func_0019F530` | Fold `la $6,D; ldl/ldr 7($6),0($6)` into gp_rel `ldl/ldr %gp_rel(D+7)/(D)($gp)`. ([feedback_packed_struct_unaligned_64] is the C-level cousin — but here the address is gp_rel and the la-macro path can't reach it.) |
| `postprocess_0AE420.py` | `func_001AE420` | Prologue + body reorder: swap `sd $17/$16` order, pull `ld $31` ahead of `sw $16/$17`, swap the two body `sw`s. |
| `postprocess_0D4E30.py` | `func_001D4E30` | Loop body `bne+nondelay-store` → `beql+delay-store` (branch-likely with annulled delay). |
| `postprocess_0FBBE0.py` | `func_001FBBE0` | Register rename in prologue: `$v0` → `$a0` for four specific occurrences of the HI base, leaving later $v0 uses unchanged. |
| `postprocess_105628.py` | `func_00205628` | Prologue ordering: emit `lui %hi(D_004CAEC0)` before `lui %hi(D_004CC1E0)`. |

**Threshold to write a new one.** Before adding a `postprocess_<OFF>.py`:

1. Confirm the diff is purely a deterministic mechanical rewrite — no
   regalloc choices, no branch-mnemonic flips, just instruction order
   or operand-rename.
2. Confirm at least 3 source-level approaches failed (write them in
   the script's docstring so future sessions know what's been tried).
3. Confirm no general postprocess (§8.x) covers it. If a similar shape
   shows up in a second function, promote to a general postprocess
   keyed by an allowlist.

These scripts are essentially encoded "I gave up on the compiler" — but
they're disciplined: idempotent, pattern-matched (not blind line
replacement), and the diff is auditable.

---

## Appendix A — header macro inventory (quick lookup)

| Macro | File | Effect | Use case |
|-------|------|--------|----------|
| `DEFEAT_TCO()` | matching.h | `__asm__("" ::: "memory")` | block sibcall opt in short wrappers |
| `KEEP_LIVE(x)` | matching.h | `__asm__("" : : "r"(x))` | force materialize before barrier |
| `KEEP_LIVE_MEM(x)` | matching.h | KEEP_LIVE + `"memory"` | pin store to current position |
| `KEEP_LIVE_FP(x)` / `_FP2(x,y)` | matching.h | `f` constraint barrier | force float materialize before int load |
| `MATERIALIZE(x)` | matching.h | `__asm__("" : "+r"(x))` | block combine pass on two writes |
| `NOREORDER_BARRIER()` | matching.h | `.set noreorder/reorder` empty | suppress gas reorder span |
| `NOP()` | matching.h | one literal nop | force empty jr-ra delay slot |
| `TRAILING_PAD_NOP()` | matching.h | `\t.4byte 0` file-scope | reserve TU-trailing pad |
| `VOLATILE_RELOAD_CALL(a,f)` | matching.h | sw+lw+nop+call | spill+reload arg before jal |
| `DEAD_DADDU_V0_SP(a)` | matching.h | one `daddu $2,$29,$0` | reproduce dead pointer-copy between two calls |
| `FABSF_BIT_TWIDDLE(x)` | matching.h | mfc1+mask+mtc1 body | fabsf without abs.s |
| `COPYSIGNF_BIT_TWIDDLE(m,s)` | matching.h | bit-merge body | copysignf |
| `ISNANF_BIT_TWIDDLE(x)` | matching.h | bit-test body | isnanf |
| `REG("$N")` | regpin.h | `__asm__("$N")` | regalloc pin |
| `SYNC()` | r5900.h | `sync` opcode + memory clobber | EE → GS/IPU/VU/DMAC fence |
| `EI()` | r5900.h | `.word 0x42000038` (COP0 EI) | enable interrupts, kernel critical-section exit |
| `QCOPY16(scratch)` / `_NO_NOP` | r5900.h | `lq+sq+[nop]` via one scratch | 16-byte qword copy ($a0/$a1 implicit) |
| `QCOPY64_SERIAL(scratch)` | r5900.h | 4× `lq+sq` pairs, one scratch | 64-byte serial qcopy |
| `QCOPY64_PARALLEL(s0..s3)` / `_NO_NOP` | r5900.h | 4 `lq` then 4 `sq`, 4 scratches | 64-byte latency-hiding qcopy |
| `LQ16_FROM(p)` / `SQ16_TO(p)` | r5900.h | one `lq`/`sq` to a C ptr | named-pointer qword move via $a2 |
| `MAP_A0_TO_SPR()` | r5900.h | `lui $a3,0x2000; or $a0,$a0,$a3` | prelude for scratchpad copy |

---

## Appendix B — workflow checklist

When you sit down to match a new function:

1. Read `CLAUDE.md` and `decomp/NOTES.md` (compiler/splat quirks).
2. Open the `.s` at `asm/nonmatchings/<TU>/<func>.s` (or `asm/cod/<addr>.s`
   if not yet broken out). Don't squint at addresses — count insns,
   note frame size, jal count, branch types.
3. Run `tools/classify_asm.py <func>.s` (when it exists) for a recipe
   suggestion. Until then: skim §1-9 ToC and pick the shape that fits.
4. Flip the yaml entry to `[..., c, <name>]`, run `tools/build.sh setup`.
5. Write the C from the recipe. Iterate via `tools/quick_diff.sh <name>`
   (~100 ms each). Don't run `ninja` until the diff is empty.
6. Once empty: `ninja` to confirm the full ELF still SHA-matches.
7. `./tools/check_no_rom.sh && git add -p && git commit`.
8. If stuck ~10 min: park (§11.1), permute (§11.2), or defer (§11.3).

---

## Appendix C — memory cross-reference

Each `feedback_X` link in this file points to
`/primary/home/n/.claude/projects/-primary-dev-ico/memory/feedback_X.md`.
If you discover a new shape, write it up there *first* (with rule + Why
+ How to apply), then add a recipe entry here pointing back. The memory
is the source of truth; the cookbook is the lookup index.

[matching-quick-diff-only]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_matching_quick_diff_only.md
[feedback_volatile_wrapper_pattern]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_volatile_wrapper_pattern.md
[feedback_void_return_tco]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_void_return_tco.md
[feedback_lift_deref_before_call]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_lift_deref_before_call.md
[feedback_force_callee_save_reuse]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_force_callee_save_reuse.md
[feedback_match_batching]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_match_batching.md
[feedback_fast_pass_subshape]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_fast_pass_subshape.md
[feedback_varargs_builtin_next_arg]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_varargs_builtin_next_arg.md
[feedback_keep_live_v1_pin]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_keep_live_v1_pin.md
[feedback_keep_live_mem_pin_first_store]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_keep_live_mem_pin_first_store.md
[feedback_compound_update_for_addu_dest]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_compound_update_for_addu_dest.md
[feedback_volatile_stores_pin_tail_call]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_volatile_stores_pin_tail_call.md
[feedback_materialize_barrier]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_materialize_barrier.md
[feedback_goto_separate_returns]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_goto_separate_returns.md
[feedback_goto_single_return]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_goto_single_return.md
[feedback_branch_likely_emission]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_branch_likely_emission.md
[feedback_store_then_clamp]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_store_then_clamp.md
[feedback_sra_srl_combo]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_sra_srl_combo.md
[feedback_struct_member_offset]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_struct_member_offset.md
[feedback_unsigned_mask_for_lui_ori]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_unsigned_mask_for_lui_ori.md
[feedback_la_pseudo_quick_diff]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_la_pseudo_quick_diff.md
[feedback_aent_breaks_ee_as]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_aent_breaks_ee_as.md
[feedback_volatile_ptr_cast]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_volatile_ptr_cast.md
[feedback_volatile_ptr_load_order]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_volatile_ptr_load_order.md
[feedback_data_symbols_extern]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_data_symbols_extern.md
[feedback_lit4_gp_rel]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_lit4_gp_rel.md
[feedback_packed_struct_unaligned_64]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_packed_struct_unaligned_64.md
[feedback_sq_a1_inline]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_sq_a1_inline.md
[feedback_inline_asm_single_line]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_inline_asm_single_line.md
[feedback_no_asm_in_src_cod]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_no_asm_in_src_cod.md
[feedback_keep_live_fp]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_keep_live_fp.md
[feedback_fp_barrier_nop]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_fp_barrier_nop.md
[feedback_no_schedule_insns_for_tu_context]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_no_schedule_insns_for_tu_context.md
[feedback_unfold_ra_delay]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_unfold_ra_delay.md
[feedback_swap_zero_ret_ld_ra]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_swap_zero_ret_ld_ra.md
[feedback_early_epilogue_restore]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_early_epilogue_restore.md
[feedback_fill_blez_delay]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_fill_blez_delay.md
[feedback_matching_quick_diff_only]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_matching_quick_diff_only.md
[feedback_volatile_pad_frame]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_volatile_pad_frame.md
[feedback_force_stack_temp]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_force_stack_temp.md
[feedback_const_in_loop_for_emit_order]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_const_in_loop_for_emit_order.md
[feedback_park_failed_matches]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_park_failed_matches.md
[feedback_score0_promotion]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_score0_promotion.md
[feedback_splat_lost_symbol]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_splat_lost_symbol.md
[feedback_nop_pad_after_include_asm]: ../../../home/n/.claude/projects/-primary-dev-ico/memory/feedback_nop_pad_after_include_asm.md
