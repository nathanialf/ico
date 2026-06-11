# func_001CF010 (sugipon/girlForceField) — RESUME notes

Best clean real_count = **9**. Shape is structurally correct; residual is a
register-allocation tie on the iosFree RETURN VALUE, not the deref chain.

## Proven facts
- Function RETURNS the iosFree alloc pointer (int*). ROM keeps it in v0
  (never overwritten), copies v0->v1 (`daddu $3,$2,$0`), and uses v1 as the
  base for BOTH the alloc-result stores AND the geo chain (p_830 reuses v1).
  Inter (self->p_15C) = a0. So ROM uses only 2 GP regs: v1 (shared) + a0.
- Retail sibling func_001D1C78 (byte-identical pattern, +0x840 not +0x830) was
  ONLY matched with crutches: REG("$2")/REG("$3")/MATERIALIZE(buf)/KEEP_LIVE +
  volatile geo stores. Retail HEAD now shows it back as INCLUDE_ASM (crutch
  version removed, never re-matched clean). So NO known clean solution exists.

## What's solved (keep these)
- int* return + `int *p = ret` copy: gives the v0->vN daddu copy + single
  lwc1 load of src->0x28 in $f0 (FP coloring f0=val, f1=one).  ESSENTIAL.
- `float one = 1.0f` named local shared by reciprocal + geo stores -> f1.
- `val = one/val` reuses val (single load).
- volatile geo stores (`*(volatile float*)`) -> preserves 0x20,0x28,0x24 order
  (non-volatile reorders). volatile is NOT a forbidden crutch (32 aug6 files).

## The residual (THE tie)
gcc copies v0 -> a0 (ptr chain) or a1 (int chain), NEVER v1. v1 is grabbed by
the geo chain instead:
- ptr-typed chain  `*(int**)((char*)*(int**)(self+0x15C)+0x830)`: count 9.
  buf=a0, inter=a1, p_830=v1, and chain HOISTS above the alloc stores
  (ptr load doesn't TBAA-alias the *(int*)(p+8)=0 store).
- int-typed chain  (GOBJ_SUB / int-read, the canonical anti-hoist form): count 13.
  NO hoist, but buf=a1, inter=v1, p_830=a0 (3-way reg relabel vs ROM).
The copy-target (v0->?) is the ROOT and is invariant to chain typing/expr form,
decl order (val-first), reuse-vs-separate buf, ptr-to-array deref on buf or
chain, r-store reorder. ~24 hand hypotheses tried.

## Levers still untried / for permuter
- permuter `new_var` discovery (cf. func_001FB768: `if((nv2=nv)>=7)` forced the
  non-coalesced copy hand pins couldn't). This is the documented escape for an
  alloc-result copy-target tie.
- Try forcing geo chain entirely into a0+a1 (both arg regs) so v1 is free for buf.
