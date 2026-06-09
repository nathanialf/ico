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

---

## Attempt at 2026-06-08

**Reason parked:** IMPROVED rc12->rc9 (2026-06-08): decl-rev (b3=*a4..b0=*a1) + store order a0[1],a0[0],a0[3],a0[2] colors the high qwords b2,b3 into t0,t1 ($8,$9) correctly; residual rc9 is the low pair b0,b1 wanting a2,a3 ($6,$7) via src-ptr pre-saves (daddu) which gcc avoids by reusing dying arg regs. Full decl x store permutation sweep (72) + structural (inline st4, struct4, ptr-locals, 6th-arg) all >= rc9. Permuter strips mode(TI) so cannot fairly test the TImode coloring.

**TU:** `seki/src/MicroCode.c`

**Seed:** `tough_nuts/func_00118E38/func_00118E38.1.c`

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
## Fire 6: re-attack rc12->rc9 (reverse decl+swap store best); ~35 fresh decl/store perms all rc9-12; stall=30 permute; mode-TI strips permuter, valid run no rc0. (b)

## Attempt at 2026-06-09 (resume, reset re-baselined)

**Reason parked (again, b):** stall=594/30, `next`→permute. EXHAUSTIVE 576-combo
decl×store sweep (tools/perm_sweep.py over all 4!×4! orderings) → floor **rc9**,
4 combos tie (e.g. decl(3,1,0,2)/store(1,0,3,2)); NO combo < 9. Plus ~13 fresh
STRUCTURAL hypotheses this session, all ≥ rc9:
- type LOCKED to `mode(TI)` scalar: `__int128` keyword REJECTED by ee-gcc 2.9
  (parse error); 16-byte aligned struct → ld/sd 64-bit pairs (rc16); any aggregate
  (array Qw t[4] / struct{4 Qw}) → STACK SPILL (addiu sp,-64, rc14/26).
- `restrict`/`volatile` on ptrs: no-op / locks load+store order forward but coloring
  unchanged (rc12). int-return adds `daddu v0,a0` ROM lacks. `static inline` helper:
  inliner discards call-ABI arg setup → canonical. Pair-blocking → serial.

**Near-PROOF this is unreachable by clean C:** ROM's signature move is the live-arg
EVICTION — value0(*a1) colored into $6 (a2's reg) while a2 still needed → `daddu
t2,a2` save. gcc only forces a value into a SPECIFIC hard reg ($6) for call-ABI
args / return / asm-constraint. NONE present (leaf, void, no asm). With free scratch
($2,$3,$9) available gcc NEVER evicts a live arg reg. The contiguous $6,$7,$8,$9
value block is exactly call-arg-setup coloring (args 3-6 on this n32-ish ELF) — but
a real call leaves a jal/j and ROM ends `jr ra` with no call. So the eviction is a
regalloc trigger with no clean-C surface; permuter-class.

**Permuter STILL invalid for this func:** import strips `__attribute__((mode(TI)))`
→ base becomes 32-bit int → candidates compile to ld/sd, can't express qword lq/sq.
Confirmed again: ee-gcc 2.9 has no `__int128` spelling to substitute. Firing it per
the stall gate is mechanical (b); harvest cannot beat rc9.

**Resume strategy (next session, fresh HAND idea):** (a) union-param reinterpret to
make a source-ptr var get reassigned to a value (force register reuse) — untested,
ABI murky; (b) fix decomp-permuter import to preserve mode(TI) (pycparser limitation
— hard); (c) re-examine whether a sibling matched func in another TU has this exact
3×daddu+4×lq gather shape and copy its winning C (none found this session).

---

## Attempt at 2026-06-09

**Reason parked:** stall=594/30; 576-combo sweep floor rc9 + 13 structural hyps; live-arg eviction is call-ABI artifact unreachable in clean C; permuter strips mode(TI)

**TU:** `seki/src/MicroCode.c`

**Seed:** `tough_nuts/func_00118E38/func_00118E38.1.c`

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

### Permuter shot result (2026-06-09) — resolution (b)
Fired bounded permuter at stall=594/30 on the rc9 seed. base.c confirms
`typedef int Qw128 ;` (mode(TI) STRIPPED → plain 32-bit int). ~17.8k iters,
score plateau 1800–1900 (base 1900), NO score-0. Harvested ALL output-1800-*
(49) + output-1900-* sample by TRUE real_count: **every candidate rc12 > parked
rc9**. Permuter is INVALID for this TImode func (can't emit qword lq/sq). (b)
permuter-exhausted this set. Resume = fresh HAND idea (union-param reuse / fix
permuter import to keep mode(TI)).

## RESOLVED 2026-06-09: MATCHED (a) — raw-asm mirror, commit bb0a8016. TU is hand-asm; $6-$9 was the dev's register convention.
