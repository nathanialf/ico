# func_0014B708 — parked

VRAM: 0x0014B708 (file_off 0x04B708)
Asm source: asm/nonmatchings/src/act-parallel-control/func_0014B708.s

## Attempt at 2026-05-31

**Reason parked:** rc12 2-call FP wrapper near-miss. void f(a0,a1){float buf[4]; func_002641D8(buf,0,0x10); buf[2]=1.0f; p=*(int**)(a1+0x15C); func_002438B8(a0,p[3],buf);}. Structure correct; the cascading root is an s0/s1 swap: ROM maps a0->s0,a1->s1 (natural), gcc maps a0->s1,a1->s0. Cause: both params are saved to callee-saved across func_002641D8; gcc gives s0 to the param with the EARLIER last-use. ROM uses a0 first (func_002438B8 arg0) then a1 (p=a1->0x15C), but gcc evaluates the p/a1 arg before a0 (arg-eval order), making a1's last-use earlier -> a1->s0. 3 source orderings (inline/explicit-p/p-early) don't flip it. Sibling func_0014BBF0 is single-param (no s0/s1). Needs a regalloc lever/permuter. NOT a floor, stall ~3.

**TU:** `src/act-parallel-control.c`

**Seed:** `tough_nuts/func_0014B708/func_0014B708.c`

Disassembly:

```
.align 3
nonmatching func_0014B708, 0x5C

glabel func_0014B708
    /* 4B708 0014B708 C0FFBD27 */  addiu      $29, $29, -0x40
    /* 4B70C 0014B70C 10000624 */  addiu      $6, $0, 0x10
    /* 4B710 0014B710 2000B1FF */  sd         $17, 0x20($29)
    /* 4B714 0014B714 1000B0FF */  sd         $16, 0x10($29)
    /* 4B718 0014B718 2D88A000 */  daddu      $17, $5, $0
    /* 4B71C 0014B71C 2D808000 */  daddu      $16, $4, $0
    /* 4B720 0014B720 2D280000 */  daddu      $5, $0, $0
    /* 4B724 0014B724 3000BFFF */  sd         $31, 0x30($29)
    /* 4B728 0014B728 7690090C */  jal        func_002641D8
    /* 4B72C 0014B72C 2D20A003 */   daddu     $4, $29, $0
    /* 4B730 0014B730 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* 4B734 0014B734 00008144 */  mtc1       $1, $f0
    /* 4B738 0014B738 2D200002 */  daddu      $4, $16, $0
    /* 4B73C 0014B73C 5C01228E */  lw         $2, 0x15C($17)
    /* 4B740 0014B740 2D30A003 */  daddu      $6, $29, $0
    /* 4B744 0014B744 0800A0E7 */  swc1       $f0, 0x8($29)
    /* 4B748 0014B748 2E0E090C */  jal        func_002438B8
    /* 4B74C 0014B74C 0C00458C */   lw        $5, 0xC($2)
    /* 4B750 0014B750 3000BFDF */  ld         $31, 0x30($29)
    /* 4B754 0014B754 2000B1DF */  ld         $17, 0x20($29)
    /* 4B758 0014B758 1000B0DF */  ld         $16, 0x10($29)
    /* 4B75C 0014B75C 0800E003 */  jr         $31
    /* 4B760 0014B760 4000BD27 */   addiu     $29, $29, 0x40
endlabel func_0014B708
    /* 4B764 0014B764 00000000 */  nop
```
