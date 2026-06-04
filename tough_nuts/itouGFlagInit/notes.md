# itouGFlagInit — parked

VRAM: 0x00195B48 (file_off 0x095B48)
Asm source: asm/aug6/nonmatchings/ito/src/itou_gflag/itouGFlagInit.s

## Attempt at 2026-06-04

**Reason parked:** rc4 floor (best). Shape fully recovered: int rv=1; void *r=InitParticleLayoutGeo(); **(int**)((char*)r+0x60)=rv; return rv;  (8 insns, double-deref store of constant 1, return same). RESIDUAL = single local-alloc tie-break: gcc allocates the shared store+return constant to {a0 or v1} and reserves v0 for an un-coalesced return-move; original reuses the dead call-result reg $2(v0) for the constant (lw $3,0x60($2); addiu $2,1; sw $2,0($3)). 30 distinct hand shapes ALL give ptr=v1/const=a0 (rc4) or ptr=a0/const=v1 (rc5), never {v1,v0}. ptr->v1 requires rv to span the call, which then conflicts with r in v0 -> const forced off v0. No clean-C shape produces the v0 reuse. next-verdict: park for offline auto_permute batch.

**TU:** `ito/src/itou_gflag.c`

**Seed:** `tough_nuts/itouGFlagInit/itouGFlagInit.c`

Disassembly:

```
.align 3
nonmatching itouGFlagInit, 0x28

glabel itouGFlagInit
    /* 95B48 00195B48 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 95B4C 00195B4C 0000BFFF */  sd         $31, 0x0($29)
    /* 95B50 00195B50 E497070C */  jal        InitParticleLayoutGeo
    /* 95B54 00195B54 00000000 */   nop
    /* 95B58 00195B58 6000438C */  lw         $3, 0x60($2)
    /* 95B5C 00195B5C 01000224 */  addiu      $2, $0, 0x1
    /* 95B60 00195B60 0000BFDF */  ld         $31, 0x0($29)
    /* 95B64 00195B64 000062AC */  sw         $2, 0x0($3)
    /* 95B68 00195B68 0800E003 */  jr         $31
    /* 95B6C 00195B6C 1000BD27 */   addiu     $29, $29, 0x10
endlabel itouGFlagInit
```

## Resume 2026-06-04 (loop) — stall 13/30 from reset
Precise diff (rc4): ROM single-materializes const 1 in v0 AFTER the lw (reuse
dead call-result v0): `lw v1,96(v0); addiu v0,1; ld ra; sw v0,0(v1); jr`.
gcc DOUBLE-materializes: `addiu a0,1` (store) + separate `addiu v0,1` (return)
— a cheap-constant remat that won't coalesce. ptr=v1 only when rv spans the
call; rv-after-call → ptr=a0 (rc5). NEW forms ruled out this session:
assignment-expr `return *p=1` (rc4/5, still double-mats), int** pp temp,
register int rv, and dummy-param register pressure (rc5 — dummy does NOT push
ptr to v1; only rv-spanning does). Tension confirmed: ptr=v1 ⇔ rv-spans-call ⇔
const-remat double. Likely needs a non-rematerializable spelling of 1 or the
permuter (constant-coalescing is its strength). Continue toward 30-stall then
the one permuter shot. Contrast: the sibling scheduling-tie class
(func_0011F1C8 >>5, func_001E8D10 post-inc) cracked by idiom — this is regalloc
coalescing of a constant, a harder sub-class.

## stall 21/30 (loop, more forms ruled out)
Also tried (all rc4 rv-spans / rc5 rv-after, none reuse v0): store-then-reload
`return *p`, int** pp double-deref, comma `(*p=1,1)`, static-inline-helper
(rc5), array-of-ptrs r[0][0], register int rv, (*pp)[0]. Root cause firmly:
rv spanning the call → gcc REMATERIALIZES const 1 at both store+return
(double addiu, never reuses dead call-result v0); rv-after-call removes the
double-mat but moves ptr off v1 (rc5). The two are linked through register
pressure; no clean-C form decouples them. This is the func_001FB768-class
constant-coalescing regalloc tie → permuter at 30-stall (it surfaces the
`if((x2=x))`-style live-range split hand forms can't). Continue toward 30.
