# reg_dispLine — parked

VRAM: 0x00120298 (file_off 0x020298)
Asm source: asm/aug6/nonmatchings/seki/src/RegistPacket/reg_dispLine.s

## Attempt at 2026-06-08

**Reason parked:** best=rc4 (void-return, TCO j dl_GetPri correct). Residual: dpk_Init(2,D,4) delay-slot tie — ROM defers a0=2 to the jal delay (a1hi,a2,a1lo,[a0]); ee-gcc emits args L-to-R so a1lo (pointer %lo, last-ready via RAW chain) always fills the delay (a1hi,a0,a2,[a1lo]). 30+ distinct forms (return type void/int/long/void*, proto void*/int*/char/short/array/const/register, global ref D/&D[0]/D+1/scalar&/struct, enum/unsigned/comma/bare-call/two-stmt) + flag sweep (O1/O2/no-sched1/no-sched2) ALL rc4. a0=2 is a pure no-WAR constant (SgSetReverbFeedback defers const only via $4 WAR from an incoming arg; reg_dispLine is void(void)) so it can never schedule last by source. Permuter-class scheduler tie.

**TU:** `seki/src/RegistPacket.c`

**Seed:** `tough_nuts/reg_dispLine/reg_dispLine.c`

Disassembly:

```
.align 3
nonmatching reg_dispLine, 0x30

glabel reg_dispLine
    /* 20298 00120298 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 2029C 0012029C 0000BFFF */  sd         $31, 0x0($29)
    /* 202A0 001202A0 BAE1070C */  jal        dpk_SwapBuffer
    /* 202A4 001202A4 00000000 */   nop
    /* 202A8 001202A8 5500053C */  lui        $5, %hi(D_0054FBE0)
    /* 202AC 001202AC 04000624 */  addiu      $6, $0, 0x4
    /* 202B0 001202B0 E0FBA524 */  addiu      $5, $5, %lo(D_0054FBE0)
    /* 202B4 001202B4 C4E1070C */  jal        dpk_Init
    /* 202B8 001202B8 02000424 */   addiu     $4, $0, 0x2
    /* 202BC 001202BC 0000BFDF */  ld         $31, 0x0($29)
    /* 202C0 001202C0 48E10708 */  j          dl_GetPri
    /* 202C4 001202C4 1000BD27 */   addiu     $29, $29, 0x10
endlabel reg_dispLine
```

## Permuter harvest 2026-06-08 (this pass)

Fired bounded permuter (8445 iters). Best = `output-20-1` (score 20 = **rc2**,
improving the clean-C rc4): the mutation is an empty `if (D_0054FBE0) {}` BEFORE
the calls, which materializes `%hi(D)` (lui a1) early so `a1lo` no longer falls
into the dpk_Init delay slot. Residual rc2 is then purely the `a0=2`/`a2=4`
transposition: ROM emits `a2=4` into the a1 hi/lo gap and defers `a0=2` to the
delay; ee-gcc 2.9 emits call args LEFT-TO-RIGHT so `a0` (arg0) fills the gap and
`a2` (arg2) is deferred. No clean source reorders two plain immediates across a
fixed-position call. arg0-const-in-delay needs a WAR hazard on $4 (cf.
SgSetReverbFeedback `f(0x18,a0,a1,0)` where an incoming param copied to a1 forces the
const write last) — reg_dispLine is `void(void)`, no incoming arg, so no WAR.
The `if(D){}` is a permuter artifact, NOT clean dev C, and still only rc2.
Permuter found NO rc0 (no output-0-*). RESUME idea: find the dev construct that
creates a $4 WAR (an arg/temp using $4 before dpk_Init) — that is the only known
lever that defers a const arg0.

## Pass 2 (2026-06-08): rc4->rc2 adopted, (b) re-confirmed
Fresh levers tried: do{}while(0)/empty-block anchor (no effect on arg-sched),
const-form variants (1<<2, 4>>1, 2+2, type changes — all fold, rc2). Adopted the
if(D){} rc2 form (best now rc2). Permuter seeded WITH the rc2 form (closer start):
~7400 iters, NO rc0. Best harvest = score-15 UB artifact `dpk_Init(nv, D, nv=(nv=4))`
which yields a0=4 (WRONG value) — real_count 2 but semantically broken, does NOT
beat rc2. Genuine floor stays rc2 (a0/a2 left-to-right gap-filler swap). (b).

## Fire 6 (2026-06-08): re-attack, rc2 floor re-confirmed
Reset + 28 fresh distinct forms this pass: local-ptr-temp(13), ternary-a0(4),
four-temp(2), scalar-addrof(2), enum-a0(2), explicit-ne/hex/arith consts(2),
long/voidptr/int return(5), charptr-cast(5), register-two(2), guard-deref(13),
negated-guard(4), ptr-no-guard(13), ptr+0(2), two-locals(2), unsigned(2),
dowhile0(4), void-cast-ref(4), guard-both-swap(18), addr-elem0(2), bare-return(2),
comma-return(2). All rc2 or worse. stall=30 -> permute. Bounded permuter (seeded
rc2 if-guard form): best output-15 = rc2, NO output-0 (no rc0). a0=2/a2=4
gap-filler swap floor holds; no clean $4-WAR exists for void(void). (b).
## Fire 7: re-attack rc2 a0/a2 swap; ~30 fresh forms (comma/sub/add/sizeof/cast/guard variants) all rc2; stall=31 permute, valid run no rc0. (b)
## Fire 8: re-attack rc2; ~30 forms all rc2; stall=31 permute, valid run no rc0. (b)
## Fire 9 (2026-06-09): SYSTEMATIC ANALYSIS — tie is compiler-level, 30 fresh hyps, all rc2+
Root-caused the residual: ROM emits call args [consts a1..an fwd][computed][a0-const LAST];
our 2.9-991111-01 emits [a0-const FIRST][consts fwd][computed last]. Swept the whole ROM:
121 sites share (const-a0 + >=1 computed arg → a0 in jal delay); **0 of 121 are matched**.
371 FWD sites (all-const, e.g. gif_SetAlpha(1,n,0x80), or WAR like tex_setRegisters) match fine.
Probes: proto/varargs/K&R, a0/a2 param types (char..long long), ptrdiff late-fold, mask+trunc
combine games, do-while(0)/while(1)/for loop contexts (preserve_subexpressions_p), static
inline wrappers (incl. REVERSED param order), comma-call-in-arg0, shared-local derived consts
(n-2/n>>1/n/2 with a2=n), 2D-decay/union a1 decls, int-return comma tail — ALL collapse to the
same order: sched1 re-sorts hard-reg arg sets with a forward-luid tie-break, erasing every
expand/cse-level luid game. Only a real $4 dependence flips it; impossible in void(void) clean C.
CONCLUSION: dev binary's tie-break (sched rank or load_register_parameters order) differs from
ours for this configuration. Candidate: different ee-gcc 2.9-991111 sub-build. The 121-site
unmatched cluster is the falsifiable fingerprint. If a second 2.9 binary ever surfaces, test
probe: dpk_Init(2, D_0054FBE0, 4) after a void call — expect lui,a2,lo,jal,[a0].
### Fire 9 permuter shot (2026-06-09) — resolution (b)
Bounded run at stall=30/30 (~600s). Single harvest output-15-1 = UB artifact
(new_var4 overwritten 2→4 before use → dpk_Init(4,D,4), WRONG a0 value — same
class as fire-2's score-15). No output-0. Nothing beats rc2. (b) re-confirmed.

## Fire 10 analysis (2026-06-10) — compiler theory REFUTED

Value-tracked whole-ROM scan (final a0=const + final arg-reg=%lo ptr):
21 sites have %lo in the jal delay (OUR compiler's style) vs 9 with
const-a0 in the delay (this site + PObj trio 248BB8/248EB8/2491D0 →
sceCdSync(1,&D_00710F98) + MakeBarString/fog_DrawFog/CandleGeo/
lookAtTest/func_001CC518). Same binary, both orders → context-controlled,
not a sub-build. decompme ee-gcc2.9-991111 (pre-01) and 991111a probe
identically to ours; 2.96 = third order. Old "121-site cluster" was a
loose-pattern overcount. Leads: a0=0 sites (daddu $4,$0,$0) go early in
ROM exactly like ours; the 9 are nonzero-li + %lo-in-$5 + 2-3 args.
WORKING fallback (rc0 + ninja-verified, in tree uncommitted): pin p/$5,
n/$6 via register asm, volatile barrier reading both, then the call —
forces only li $4 after the barrier → delay slot. See probe harness
tools/probe_compiler.sh.

## Fire 11 (2026-06-10) — 30-stall re-confirmed at rc2, clean-C
Resumed post-refutation (compiler vindicated). 30 distinct hypotheses recorded
in match_loop state: ptr-diff folds (a0/a2), shared-local n derived consts,
DImode/HImode/enum const modes, varargs/fn-ptr/implicit protos, guard position/
double-guard/guarded-call/folded-else, call-in-arg evaluation (a1/a2), comma
returns, statement-exprs, builtin-vanishing call-exprs. ALL collapse to rc2
(guard form) or worse. Mechanism (sched_diff): both const li's re-materialize
at the call in arg order (cse erases every earlier def); sched1 luid tie keeps
li-a0 first; dbr fills the jal delay with the last pre-jal insn. Non-tail
all-const calls always emit a0-first on this binary (probes: siteC/D/E in
/tmp lost; reproduce via tools/probe_compiler.sh-style probe). ROM's sibling
configs with a reg-copy arg DO defer li-a0 naturally (func_001CC518-style) —
reg_dispLine's all-const config is the hard one. Crutch rc0 fallback preserved
in crutch_rc0.c (pinned $5/$6 + volatile barrier).

### Fire 11 permuter shot (2026-06-10) — resolution (b)
Bounded 600s run, base score 20, two output-15 harvests. Both measure TRUE
rc2 (equal to parked best, the same a0/a2 li transposition; output-15-2 is
the fire-8 UB class again: `dpk_Init(new_var, p, new_var = 4)` unsequenced).
Nothing beats best. (b) re-confirmed on clean-C; crutch rc0 remains the
only byte-exact form known for this site.
