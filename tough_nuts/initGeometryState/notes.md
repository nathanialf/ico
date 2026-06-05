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
