# func_002416F0 — parked

VRAM: 0x002416F0 (file_off 0x1416F0)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_002416F0.s

## Attempt at 2026-06-13

**Reason parked:** rc8 stall=30/30. Pure regalloc tie: ROM uses dead arg regs (ptr=$5/a1, ternary result=$4/a0, alt=$2/v0, base=$4); gcc uses v0/v1/a1 (consistent v0<->a0,v1<->a1 relabel in tail). func_00241838(a0,2,3) modifies a0[0]; ptr=a0[0]; a0[0]=ptr+1; a0[3]=ptr; *ptr=a1?0xD0000000:0x50000000 (movn). Exhausted ~30 shapes: store-order(6), ptr/ptr+4 reg via param-reuse(a0/a1), ptr-to-array deref, struct-typed, void-callee, char*, int**, named-temp, explicit-if, assign-in-expr. Sibling func_00241640 matched trivially (diff callee func_002415E8). Permuter-class.

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_002416F0/func_002416F0.c`

Disassembly:

```
.align 3
nonmatching func_002416F0, 0x58

glabel func_002416F0
    /* 1416F0 002416F0 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 1416F4 002416F4 03000624 */  addiu      $6, $0, 0x3
    /* 1416F8 002416F8 1000B1FF */  sd         $17, 0x10($29)
    /* 1416FC 002416FC 0000B0FF */  sd         $16, 0x0($29)
    /* 141700 00241700 2D88A000 */  daddu      $17, $5, $0
    /* 141704 00241704 2D808000 */  daddu      $16, $4, $0
    /* 141708 00241708 2000BFFF */  sd         $31, 0x20($29)
    /* 14170C 0024170C 0E06090C */  jal        func_00241838
    /* 141710 00241710 02000524 */   addiu     $5, $0, 0x2
    /* 141714 00241714 0000058E */  lw         $5, 0x0($16)
    /* 141718 00241718 00D0023C */  lui        $2, (0xD0000000 >> 16)
    /* 14171C 0024171C 0050043C */  lui        $4, (0x50000000 >> 16)
    /* 141720 00241720 2000BFDF */  ld         $31, 0x20($29)
    /* 141724 00241724 0400A324 */  addiu      $3, $5, 0x4
    /* 141728 00241728 0B205100 */  movn       $4, $2, $17
    /* 14172C 0024172C 000003AE */  sw         $3, 0x0($16)
    /* 141730 00241730 0C0005AE */  sw         $5, 0xC($16)
    /* 141734 00241734 1000B1DF */  ld         $17, 0x10($29)
    /* 141738 00241738 0000B0DF */  ld         $16, 0x0($29)
    /* 14173C 0024173C 0000A4AC */  sw         $4, 0x0($5)
    /* 141740 00241740 0800E003 */  jr         $31
    /* 141744 00241744 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_002416F0
```

## Permuter run (2026-06-13) — resolution (b) permuter-exhausted
- ~250 iterations on the clean minimal seed; lowest score 45 → rc7 (output-45-1).
- BUT the rc7 is SEMANTICS-INVALID: it does `a0[3] = (int)((int*)a0[0])` AFTER
  `a0[0] = ptr+1`, i.e. stores ptr+1 to a0[3] (ROM stores the pre-advance ptr).
  Its only "win" is a regalloc flip enabled by letting ptr die early — illegal
  because ROM needs ptr live for both a0[3]=ptr and *ptr=val.
- Re-applied the structural idea CLEANLY (new_var=ptr+1 copy; a0[3]=a0[0] BEFORE
  advancing a0[0]; etc.) → all rc8, no improvement over the parked best.
- CONFIRMED: rc8 is the correct-semantics floor for hand shapes. Pure v0/v1<->a0/a1
  allocator tie (ROM reuses dead arg regs $4/$5 for result/ptr; gcc uses v0/v1).
- RESUME: needs a shape that makes gcc reuse the dead arg regs while keeping ptr
  live through the final store. Permuter can't (only finds it by dropping ptr's
  liveness illegally). Try a genuinely new hand hypothesis on resume.
