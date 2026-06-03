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
