# soundDataAreaGet (fumi/sound/s_init) — RESUME

Linear search over 16 structs (stride 0x30) from D_006A3070; compare
*(int*)entry == a0[0]; return entry ptr or 0. Do-while, bottom test
slt(p<end)+bne (PLAIN, not bnel), found-block out-of-line.

## Best: rc10 — two-pointer goto form
```c
int key = *a0;
char *p = D_006A3070;          // load + bound  (expected: a1)
char *ret = D_006A3070;        // returned       (expected: a2)
char *end = D_006A3070 + 0x300;// (expected: a3)
do { if (*(int*)p == key) goto found; p += 0x30; ret += 0x30; }
while ((int)p < (int)end);
return 0;
found: return ret;
```
ISOMORPHIC to expected — only a REGISTER COIN-FLIP remains:
- expected: load/bound ptr=a1 (home base reg), ret=a2, end=a3; ret-inc
  deferred via temp v1 across both delay slots, walk-inc inline.
- built: load/bound ptr=v1, ret=a1 (home), end=a2; walk-inc in beq delay,
  ret-inc inline in bne delay.
gcc consistently puts the DEREF'd pointer in v1 and the RETURNED giv in
home reg a1 — opposite of ROM.

## Tried (all → rc10/11/12, reg locked):
single-ptr do-while/goto (rc12 hoist+bnel, software-pipelines load);
two-ptr goto (rc10 best); decl-order swaps; incr-order swap; bound-on-ret
(rc11); ret=p copy; end=p+0x300; inline end (CSE'd); int*(stride0xC);
typed array-ptr ret; ptr-to-array deref char(*)[] on p/ret (FOLDS, single
base — lever is for TWO distinct globals per gene_enemy, N/A here);
base+k index-giv (rc8 but adds addu+sltiu, wrong addressing).

## Next ideas: permuter (regalloc coin-flip is permuter-class); or find a
perturbation that makes gcc give the deref'd ptr the home reg a1.

## UPDATE: best now rc7 (three-walker)
```c
char *p=D_006A3070, *q=D_006A3070, *ret=D_006A3070, *end=D_006A3070+0x300;
do { if(*(int*)p==key) goto found; p+=0x30; q+=0x30; ret+=0x30; }
while((int)q<(int)end);
return 0; found: return ret;
```
rc7: deref=p→a1 (CORRECT, lw 0(a1) matches), return=ret→a2 (CORRECT), end→a3.
ONLY gap: built has bound on a separate walker q (v1), ROM merges bound into
the deref (a1) and uses v1 as a TEMP for the return-split (daddu v1,a2;
addiu a2,v1,48). gcc ALWAYS gives the biv (loop-control/bound walker) v1 and
the other giv the home reg; ROM has biv(deref+bound) in a1. This biv-register
flip + the return-temp-split is the residual — a reorg/regalloc tie that NO
source meaning flips (31 distinct meanings tried). §regalloc-swap tag +
COOKBOOK §3.10 both name this walking-ptr search-return form as REG-pin /
permuter territory; REG pins are forbidden by decomp-match. Permuter seed =
this rc7 (registers already right) OR the rc10 2-walker (right structure).
