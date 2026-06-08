# initGeometryState — parked

VRAM: 0x0019BB68 (file_off 0x09BB68)
Asm source: asm/aug6/nonmatchings/common/src/DObj/initGeometryState.s

## Attempt at 2026-06-05

**Reason parked:** rc6 regalloc coalescing tie: value/product in v1 + const in v0 (ROM) vs swapped (built coalesces value->v0=return reg, fills beq delay with const lui). if(!=)compute gives correct beq; ~20 distinct shapes (operand order, temps, struct, ptr-return, cmp-swap, goto-end) all rc6. Permuter-class like func_00118E38.

**TU:** `common/src/DObj.c`

**Seed:** `tough_nuts/initGeometryState/initGeometryState.c`

Disassembly:

```
.align 3
nonmatching initGeometryState, 0x34

glabel initGeometryState
    /* 9BB68 0019BB68 0C00838C */  lw         $3, 0xC($4)
    /* 9BB6C 0019BB6C 1000828C */  lw         $2, 0x10($4)
    /* 9BB70 0019BB70 08006210 */  beq        $3, $2, .L0019BB94
    /* 9BB74 0019BB74 00000000 */   nop
    /* 9BB78 0019BB78 0800838C */  lw         $3, 0x8($4)
    /* 9BB7C 0019BB7C 1500023C */  lui        $2, (0x151800 >> 16)
    /* 9BB80 0019BB80 00184234 */  ori        $2, $2, (0x151800 & 0xFFFF)
    /* 9BB84 0019BB84 0000848C */  lw         $4, 0x0($4)
    /* 9BB88 0019BB88 18186200 */  mult       $3, $3, $2
    /* 9BB8C 0019BB8C 0800E003 */  jr         $31
    /* 9BB90 0019BB90 21108300 */   addu      $2, $4, $3
.align 2
  .L0019BB94:
    /* 9BB94 0019BB94 0800E003 */  jr         $31
    /* 9BB98 0019BB98 2D100000 */   daddu     $2, $0, $0
endlabel initGeometryState
    /* 9BB9C 0019BB9C 00000000 */  nop
```

## Convergence (resolution b, 2 permuter passes)
rc6 (hand floor) -> rc5 (permuter pass1: value-before-if `int count` + `long long`
result temp fixed const->v0). Pass2 (seeded from rc5) found nothing below rc5 ->
permuter-exhausted. Residual at rc5: value->a1, base->v1, product->a0 vs ROM
value->v1, base->a0, product->v1 (regalloc coalescing coupling — same class as
[[feedback_zero_reuse_store_unfolds_index]] / func_001F8848). Re-attack: a value
reuse trick that keeps the count in v1 (the freed a0->0xC compare reg) while const
stays v0. The if(!=)compute shape (not if(==)return0, which gives bnel) is required.
## Fire 6: re-attack rc5 coalescing (v1-reuse+nop-delay); ~33 distinct forms all rc5-20; seed best rc5; stall=30 permute, valid run no rc0. (b)
