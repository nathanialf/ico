# MakeExitAttributeIndex — parked

VRAM: 0x00165088 (file_off 0x065088)
Asm source: asm/aug6/nonmatchings/fumi/src/fieldCollision/MakeExitAttributeIndex.s

## Attempt at 2026-06-03

**Reason parked:** rc6 TOOLCHAIN gap (not source-shape): unaligned 64-bit load of gp_rel global D_0062A6A0. ee-gcc emits 'uld $3,D_0062A6A0'; BOTH assemblers (2.96 + 2.9-991111, verified via minimal .s) expand uld to 'daddiu at,gp,sym; ldl 7(at); ldr 0(at)' while ROM folds 'ldl %gp_rel(sym+7)($28); ldr %gp_rel(sym)($28)'. use_old_as does NOT fix. ~14 source forms (packed struct/union/array/aligned(1)/asm-alias/temp/memcpy) all emit uld. Override-park on empirical toolchain finding; needs a uld-fold peephole or period toolchain. See uld_gprel_fold_gap memory + ~9 sibling funcs.

**TU:** `fumi/src/fieldCollision.c`

**Seed:** `tough_nuts/MakeExitAttributeIndex/MakeExitAttributeIndex.c`

Disassembly:

```
.align 3
nonmatching MakeExitAttributeIndex, 0x20

glabel MakeExitAttributeIndex
    /* 65088 00165088 2D108000 */  daddu      $2, $4, $0
    /* 6508C 0016508C 940040AC */  sw         $0, 0x94($2)
    /* 65090 00165090 B79A836B */  ldl        $3, %gp_rel(D_0062A6A7)($28)
    /* 65094 00165094 B09A836F */  ldr        $3, %gp_rel(D_0062A6A0)($28)
    /* 65098 00165098 930043B0 */  sdl        $3, 0x93($2)
    /* 6509C 0016509C 8C0043B4 */  sdr        $3, 0x8C($2)
    /* 650A0 001650A0 10930508 */  j          GetEdgeOfFloor
    /* 650A4 001650A4 00000000 */   nop
endlabel MakeExitAttributeIndex
```

## Resume progress (user directive: earnest attempts to formal 30-stall)
Un-parked the premature override-park. Best improved rc6 -> rc5 via the
`struct[0]` assignment + copy-before-zero reorder:
    ((struct PackedLL *)((char *)a0 + 0x8C))[0] = D_0062A6A0;
    *(int *)((char *)a0 + 0x94) = 0;
    GetEdgeOfFloor(a0);   // tail-call (j), void
(`[0]` indexing matters: plain `*(T*)dst = D` regresses to rc11.)
Remaining rc5 diff = the irreducible uld core (gcc `uld $3,D_0062A6A0` ->
`daddiu a2,gp; ldl 7(a2); ldr 0(a2)` vs ROM folded `ldl/ldr %gp_rel(gp)`) plus a
`daddu a0,v0` copy-placement line. ~30 byte-distinct source forms tried total;
uld emission invariant. Continuing to formal 30-stall (currently 7/30 from rc5).
Next levers to try: forms that remove the extra a0-copy (base-var used for both
stores while a0 stays for the tail call).

## Resume progress cont. (rc5 -> rc4)
Double zero-store bracket REMOVED the round-trip a0<->v0 copy:
    *(int *)((char *)a0 + 0x94) = 0;
    *((struct PackedLL *)((char *)a0 + 0x8C)) = D_0062A6A0;   // deref-assign (NOT [0])
    *(int *)((char *)a0 + 0x94) = 0;                          // 2nd zero (gcc DCEs one)
    GetEdgeOfFloor(a0);
rc4 remaining = TWO gcc-emission diffs, both compiler-difference (ee-gcc vs ROM):
  (1) uld core: gcc `uld $3,SYM` -> `daddiu a3,gp; ldl 7(a3); ldr 0(a3)` vs ROM
      folded `ldl/ldr %gp_rel(gp)` (+1 insn). use_old_as does NOT fix (re-tested).
  (2) dbr delay-fill: gcc's dbr hoists the `sw zero` into the `j GetEdgeOfFloor`
      delay; ROM leaves the delay `nop` (zero stored early). use_old_as does NOT
      fix (it's gcc dbr, not assembler-reorg). No source lever found to leave the
      j-delay nop (zero-store is an independent fillable candidate).
Both are emission-level (not regalloc/source-shape) -> rc4 is the ee-gcc floor;
rc0 needs the period compiler. Continuing to formal 30-stall per user directive.

---

## Attempt at 2026-06-03

**Reason parked:** GENUINE 30-stall park (best rc4, down from rc6 this resume). Earnest hand-grind per user directive: ~50 byte-distinct forms total. rc4 = TWO irreducible gcc-EMISSION diffs (compiler-difference, ee-gcc vs ROM's likely Pro-DG/CodeWarrior): (1) uld macro -> daddiu+ldl/ldr materialized base vs ROM folded ldl/ldr %gp_rel; (2) gcc dbr hoists 'sw zero' into the 'j GetEdgeOfFloor' delay vs ROM nop. use_old_as fixes neither (both gcc emission, not assembler). Levers found this resume: struct[0]+copy-first (rc6->5), double zero-store removes a0<->v0 round-trip (rc5->4). Needs period compiler / uld-fold peephole. See uld_gprel_fold_gap memory.

**TU:** `fumi/src/fieldCollision.c`

**Seed:** `tough_nuts/MakeExitAttributeIndex/MakeExitAttributeIndex.1.c`

Disassembly:

```
.align 3
nonmatching MakeExitAttributeIndex, 0x20

glabel MakeExitAttributeIndex
    /* 65088 00165088 2D108000 */  daddu      $2, $4, $0
    /* 6508C 0016508C 940040AC */  sw         $0, 0x94($2)
    /* 65090 00165090 B79A836B */  ldl        $3, %gp_rel(D_0062A6A7)($28)
    /* 65094 00165094 B09A836F */  ldr        $3, %gp_rel(D_0062A6A0)($28)
    /* 65098 00165098 930043B0 */  sdl        $3, 0x93($2)
    /* 6509C 0016509C 8C0043B4 */  sdr        $3, 0x8C($2)
    /* 650A0 001650A0 10930508 */  j          GetEdgeOfFloor
    /* 650A4 001650A4 00000000 */   nop
endlabel MakeExitAttributeIndex
```

## Resume 2026-06-03 (cont.) — concrete la/dbr characterization (gcc-version gap)
Inspected actual gcc 2.9-991111 .s (real flags). The packed-struct LOAD shape is
CORRECT (emits ldl/ldr). The two rc4 diffs are both gcc-VERSION emission gaps:
(1) gp_rel fold: gcc emits `la $7,D_0062A6A0 ; ldl $3,7($7) ; ldr $3,0($7)`
    (materializes the addr) vs ROM `ldl %gp_rel(SYM+7)($28) ; ldr %gp_rel(SYM)($28)`
    (folded, no la). TESTED: gcc's ALIGNED `ld` DOES fold gp_rel (`ld $2,SYM`),
    but the UNALIGNED ldl/ldr pattern does NOT — it always materializes via la/hi-lo.
    Fundamental conflict: ROM's ldl/ldr needs a packed source (else aligned ld),
    but packed forces the la. No source shape yields folded ldl/ldr → gcc-version gap.
(2) dbr: gcc fills the `j GetEdgeOfFloor` delay with `sw $0,0x94($2)` (independent
    of the tail call); ROM leaves the delay nop. gcc-version dbr behavior; no source
    lever leaves the delay nop.
Same CLASS as func_0025CC70 (mfc1 $3 coalesce): the project ee-gcc 2.9-991111 has
subtle codegen differences from ROM's compiler in edge cases. A la→gp_rel-fold +
dbr-nop parity postprocess COULD crack it (+~9 fieldCollision siblings) but both
CHANGE instruction count/scheduling (beyond encoding-parity like move→daddu) — a
project-policy decision deferred to the user. NOT a clean-C match at current flags.

## Resume 2026-06-03 (post func_0025CC70 match) — permuter resume shot, no improvement
Fired the now-FIXED permuter (5-min) on the rc4 seed. Best score 460 (base 600)
but ANTI-CORRELATED: its output dropped __attribute__((packed)) (→ aligned ld, not
ldl/ldr), and applied with packed its `new_var->v=(*(new_var=&D_0062A6A0)).v`
assignment-in-expr idea measures rc7 (worse). Nothing beat rc4. Left for offline
auto_permute (which cracked func_0025CC70's coalesce the same way). Next: reset +
hand-drive the gp_rel-ldl/ldr-fold + dbr residual to a tool-verdict, OR a longer
permuter shot finds the addressing/live-split lever like it did for fabsf.

## Resume 2026-06-03 — RETAIL CROSS-REFERENCE (user idea) → rc4->rc3 + j-delay diagnosed
The retail (main branch) src/fieldCollision.c has the debug string
"MakeExitAttributeIndex() %d\n" AND a sibling func_00167230 of the SAME shape that
reveals the dev's actual struct type:
    typedef struct { unsigned int lo; unsigned char m[3]; unsigned char hi; } FcBlk8;
NOT the `__attribute__((packed)) long long` I'd been guessing. Applying it:
    typedef struct { unsigned int lo; unsigned char m[3]; unsigned char hi; } FcBlk8;
    extern FcBlk8 D_0062A6A0;
    void MakeExitAttributeIndex(void *a0) {
        *(int *)((char *)a0 + 0x94) = 0;
        *(FcBlk8 *)((char *)a0 + 0x8C) = D_0062A6A0;
        GetEdgeOfFloor(a0);
    }
FIXED the gp_rel fold (gcc now emits direct-symbol `ldl D_0062A6A0` which folds to
%gp_rel) → rc4 -> rc3. The SOLE remaining diff is the assembler hoisting `sdr` into
the `j GetEdgeOfFloor` tail-call delay (ROM: sdr;j;nop). VERIFIED: ee-as 2.9-991111
leaves that delay nop (matches ROM); ee-as 2.96 + modern-as both fill it. This IS
the use_old_as case (compile_c.sh:31-38 documents it). BLOCKER: fieldCollision's
INCLUDE_ASM siblings use `%gp_rel(SYM)($28)` which ee-as REJECTS ("Bad expression"),
so the TU falls through to modern-as and use_old_as never takes effect. A rewrite
`%gp_rel(SYM)($28)->SYM` (byte-identical R_MIPS_GPREL16) lets ee-as assemble the
siblings — but switching the WHOLE TU to ee-as REGRESSED the build (ninja MISMATCH:
other decompiled fieldCollision/girl_act funcs that matched under modern-as differ
under ee-as). So the clean fix needs per-function assembler granularity (or to
confirm all fieldCollision funcs match under ee-as, as they do in retail). FcBlk8
struct is the validated win; the j-delay is a tooling follow-up.

## Resume 2026-06-03 (cont.) — regression isolated to fieldCollision's OWN funcs
Re-tested the ee-as path: removed girl_act from use_old_as (its build is unchanged
either way — it falls through to modern-as), kept only fieldCollision. ninja STILL
MISMATCHED (same SHA b42127e5...). So the regression is NOT girl_act — it is
fieldCollision's OTHER functions: they match under modern-as but differ under ee-as
(either the decompiled ClipWall*/etc. are tuned to modern-as delay-fill, or the
sibling `%gp_rel($28)->SYM` rewrite is not byte-identical for some instruction
beyond `sw`, which I only verified for `sw`). compile_c.sh's assembler choice is
PER-TU, so a TU-wide switch to ee-as can't give MakeExitAttributeIndex its nop
j-delay without regressing the siblings. NEXT (tooling follow-up, separate from the
match loop): (a) verify which fieldCollision funcs differ under ee-as and whether
the gp_rel rewrite is byte-exact for ldl/ldr/lw/sd (not just sw); (b) if the
siblings DO match under ee-as, the conflict is real → needs per-FUNCTION assembler
granularity in compile_c.sh/gen_ninja (split the TU .o, assemble MakeExitAttribute
Index's range with ee-as). FcBlk8 (rc3) stays the committed best; offline
auto_permute has the seed.
