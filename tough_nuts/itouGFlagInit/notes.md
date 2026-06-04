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
