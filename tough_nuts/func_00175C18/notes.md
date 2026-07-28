# func_00175C18 — parked

VRAM: 0x00175C18 (file_off 0x075C18)
Asm source: asm/nonmatchings/src/commonact/func_00175C18.s
TU: `src/commonact.c`
Seed: `tough_nuts/func_00175C18/func_00175C18.c`

## 2026-06-01 resume — FALSE-FLOOR CORRECTION → rc11 → rc10 → rc8 (chase terminated)

**Final best: rc8.** Full disciplined chase this session:
- Corrected the semantically-WRONG rc9 false floor → correct `&&` topology.
- Hand 30-stall → **rc11**.
- Permuter shot #1 (600s, first on a correct seed) → **rc10**: surfaced
  `(r = D_002883D0[0x5D]) != 0` (assignment-in-cond pins D[0x5D]→$a0). Adopted.
- Hand 30-stall on rc10 → plateau.
- Permuter shot #2 (600s) → **rc8**: surfaced
  `(r = D_002883D0[0x5D]) != (r = 0)` — a double-assignment that materializes
  the shared zero into `r` at the compare (plain C, semantically valid; on the
  short-circuit-false path r ends 0). Adopted. THIS IS THE CURRENT SEED.
- Hand 30-stall on rc8 → plateau (≈50 distinct hand forms total across the
  three loops; the load→$v1 base-coalesce never breaks by hand).
- Permuter shot #3 (600s) → **rc8, NO improvement** → chase terminated per
  procedure. Left for offline `auto_permute.sh` (longer unattended runs).

The rc8 residual is the SAME 3-cycle rotation: the speculative load still
coalesces into the dying `$v1` (sub) base instead of `$a0`; the permuter has
been shaving the *cascade* diffs (D[0x5D], the zero materialization) without yet
breaking the root coalesce. Offline permuter's job: the coalesce-break itself.



**Current best: rc10** (down from the broken rc9 false floor and the hand rc11).
The permuter (first-ever shot on a CORRECT seed, 600s) surfaced the
assignment-in-condition `(r = D_002883D0[0x5D]) != 0` — semantically valid on
this topology (r stays 0 on the v!=0x45 short-circuit) — which pins D[0x5D]→$a0
and shaves one diff. The permuter reached rc10, NOT 0, in 600s. Adopted as the
new seed; another hand sweep on the rc10 base (early-read, v-in-cond,
result-in-cond, r-decl-pre, nested — all WITH the assignment-in-cond) plateaus
at rc10 (early-read still costs bnel+entry → rc13). The residual is unchanged:
the load→$v1 base-coalesce 3-cycle rotation. Left for offline auto_permute
(longer runs) — its job is the coalesce-break the in-loop 600s shot didn't find.



**Headline finding:** the prior session's parked rc9 "best" was
**SEMANTICALLY WRONG** and is a *false floor* that can never reach rc0.
Its `r = v; … ; v = r; return v` chain returns `v` (the raw `sub->0x30`)
on the `v != 0x45` path, whereas the real function returns `0`
(`daddu v0,zero,zero`). That extra `daddu v0,a0` / wrong-value store is a
permanent diff no allocation can remove. The whole prior 26-lever streak
(and the prior permuter shot) was spent on this broken topology — so the
permuter has **never** run on a correct seed.

**Rebaselined** to the semantically-correct `&&` topology (rc11), which
matches the expected branch structure exactly (bne v!=0x45 → end, beq
D[0x5D]==0 → end, single shared `jr`):

```c
int v = *(int *)(sub + 0x30);
int r = 0;
if (v == 0x45 && D_002883D0[0x5D] != 0) r = D_002883D0[0x58] == 0;
return r;
```

### Sole residual: pure 3-cycle regalloc rotation (tag_diff §regalloc-swap)

The instruction stream is **byte-identical**; only the register coloring
rotates, all cascading from ONE decision:

- expected: `lw a0,48(v1)` — speculative delay-slot load → **$a0**;
  const 0x45 reuses dead sub base → **$v1**; result `r` → **$v0**.
- built:    `lw v1,48(v1)` — load **coalesces into the dying $v1 (sub)
  base**; that forces const → $v0, `r` → $a0 + a trailing
  `daddu v0,a0,zero` copy.

**Mechanistic root (firmly established):** the load's allocno is created
before the const's (program order), so it wins the just-freed `$v1` slot.
To match, the *const* must win `$v1` and the load must land in `$a0`.

### Why no clean hand lever (31 distinct hypotheses, all rc11–17)

- Breaking the coalesce needs **register pressure AT the load** — the only
  hand way (explicit `cfg = D_002883D0` ptr held live) does break it
  (load→$v0, rc12) but **hoists the Dptr early** (reorders, wrong); a lazy
  ptr loses the pressure and the coalesce returns.
- **early-read** (load `v` before the flag branch) **uniquely puts the
  load in `$a0`** (line 7 matches expected!) but degrades `bnel`→`bne`
  (load no longer speculative) and rotates the whole entry (`$v0/$v1`
  split) + const/`r`. The notes' old "need a bnel companion" sub-problem:
  bnel correlates with `v` *inside* the taken block, which is exactly
  where it coalesces to `$v1`. So bnel and load→$a0 pull opposite ways by
  hand.
- To steer the load to `$a0` specifically, `$v0` must be busy at the load
  — but nothing legitimately occupies `$v0` on the taken path until `r=0`
  (after the compare). Putting `r=0` before the branch steals the bnel
  delay slot (rc11, bnel→bne).
- Tried + ruled out: decl order, r-decl-pre-branch, flat/nested ternary,
  nested-if, multi-return(17), if/elseif/else ladder(17), goto-body(13),
  do-while+break, out-of-line reject, switch(v), assignment-in-condition,
  v-as-result-reuse, struct-typedef model, 2-return-points, named-flag,
  D-ptr-deref, operand-order, gate>0 / gate-inside short-circuit / gate-
  ternary, while(1)+break, named-gate, int*[12] index, stmt-expr,
  v-unsigned, !-result, r-char, negate-cmp. None drop below 11.
- The historical match used `REG("$4")`(load)+`REG("$2")`(r) **scoped
  pins** — both RETIRED. There is no source-shape way to force a leaf
  load into `$a0` (no a0-affinity source in a leaf), so this is a
  graph-perturbation coloring tie = **permuter territory**.

### Next levers for the permuter / a future resume

Seed the permuter WITH the correct `&&` form above (`--stop-on-zero`). The
structural lever it must surface is whatever breaks the load↔$v1 coalesce
WITHOUT reordering the Dptr — likely a dead temp / assignment that shifts
the load's allocno number after the const's, or a live-range split that
makes the const win the freed-$v1 slot. This is its first shot on a
correct seed.

### Disassembly

```
glabel func_00175C18
    /* 75C18 */  lw      $3, (D_00631AE8)      # gp_rel
    /* 75C1C */  lw      $3, 0x164($3)         # sub
    /* 75C20 */  ld      $2, 0x18($3)
    /* 75C24 */  dsrl32  $2, $2, 4             # bit 36
    /* 75C28 */  andi    $2, $2, 0x1
    /* 75C2C */  bnel    $2, $0, .L00175C3C
    /* 75C30 */   lw     $4, 0x30($3)          # speculative load -> $a0
    /* 75C34 */  jr      $31                    # flag clear: return 1
    /* 75C38 */   addiu  $2, $0, 0x1
  .L00175C3C:
    /* 75C3C */  addiu   $3, $0, 0x45           # const reuses sub base -> $v1
    /* 75C40 */  bne     $4, $3, .L00175C64
    /* 75C44 */   daddu  $2, $0, $0             # r = 0 -> $v0
    /* 75C48 */  lui     $3, %hi(D_002883D0)
    /* 75C4C */  addiu   $3, $3, %lo(D_002883D0)
    /* 75C50 */  lbu     $4, 0x5D($3)
    /* 75C54 */  beq     $4, $0, .L00175C64
    /* 75C58 */   nop
    /* 75C5C */  lbu     $2, 0x58($3)
    /* 75C60 */  sltiu   $2, $2, 0x1            # r = (D[0x58]==0)
  .L00175C64:
    /* 75C64 */  jr      $31
    /* 75C68 */   nop
```
