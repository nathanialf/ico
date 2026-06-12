# func_0024A858 — parked

VRAM: 0x0024A858 (file_off 0x14A858)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0024A858.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0024A858/func_0024A858.c`

Disassembly:

```
.align 3
nonmatching func_0024A858, 0x60

glabel func_0024A858
    /* 14A858 0024A858 1C000224 */  addiu      $2, $0, 0x1C
    /* 14A85C 0024A85C 70000324 */  addiu      $3, $0, 0x70
    /* 14A860 0024A860 1828A200 */  mult       $5, $5, $2
    /* 14A864 0024A864 18208370 */  mult1      $4, $4, $3
    /* 14A868 0024A868 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 14A86C 0024A86C 7100023C */  lui        $2, %hi(D_007112D0)
    /* 14A870 0024A870 1000BFFF */  sd         $31, 0x10($29)
    /* 14A874 0024A874 D0124224 */  addiu      $2, $2, %lo(D_007112D0)
    /* 14A878 0024A878 0000B0FF */  sd         $16, 0x0($29)
    /* 14A87C 0024A87C 2128A400 */  addu       $5, $5, $4
    /* 14A880 0024A880 2128A200 */  addu       $5, $5, $2
    /* 14A884 0024A884 0000B08C */  lw         $16, 0x0($5)
    /* 14A888 0024A888 2D200002 */  daddu      $4, $16, $0
    /* 14A88C 0024A88C CCAD090C */  jal        func_0026B730
    /* 14A890 0024A890 00010526 */   addiu     $5, $16, 0x100
    /* 14A894 0024A894 5800028E */  lw         $2, 0x58($16)
    /* 14A898 0024A898 D800038E */  lw         $3, 0xD8($16)
    /* 14A89C 0024A89C 1000BFDF */  ld         $31, 0x10($29)
    /* 14A8A0 0024A8A0 2A104300 */  slt        $2, $2, $3
    /* 14A8A4 0024A8A4 C0110200 */  sll        $2, $2, 7
    /* 14A8A8 0024A8A8 21100202 */  addu       $2, $16, $2
    /* 14A8AC 0024A8AC 0000B0DF */  ld         $16, 0x0($29)
    /* 14A8B0 0024A8B0 0800E003 */  jr         $31
    /* 14A8B4 0024A8B4 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_0024A858
```
