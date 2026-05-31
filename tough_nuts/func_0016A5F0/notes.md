# func_0016A5F0 — parked

VRAM: 0x0016A5F0 (file_off 0x06A5F0)
Asm source: asm/nonmatchings/src/commonact/func_0016A5F0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (MEM_BARRIER)

**TU:** `src/commonact.c`

**Seed:** `tough_nuts/func_0016A5F0/func_0016A5F0.c`

Disassembly:

```
.align 3
nonmatching func_0016A5F0, 0x88

glabel func_0016A5F0
    /* 6A5F0 0016A5F0 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 6A5F4 0016A5F4 1000B1FF */  sd         $17, 0x10($29)
    /* 6A5F8 0016A5F8 0000B0FF */  sd         $16, 0x0($29)
    /* 6A5FC 0016A5FC 2D88A000 */  daddu      $17, $5, $0
    /* 6A600 0016A600 2D808000 */  daddu      $16, $4, $0
    /* 6A604 0016A604 2000BFFF */  sd         $31, 0x20($29)
    /* 6A608 0016A608 2D202002 */  daddu      $4, $17, $0
    /* 6A60C 0016A60C C427040C */  jal        func_00109F10
    /* 6A610 0016A610 23000524 */   addiu     $5, $0, 0x23
    /* 6A614 0016A614 2D284000 */  daddu      $5, $2, $0
    /* 6A618 0016A618 0C00238E */  lw         $3, 0xC($17)
    /* 6A61C 0016A61C 04000224 */  addiu      $2, $0, 0x4
    /* 6A620 0016A620 05006214 */  bne        $3, $2, .L0016A638
    /* 6A624 0016A624 000000AE */   sw        $0, 0x0($16)
    /* 6A628 0016A628 80BF013C */  lui        $1, (0xBF800000 >> 16)
    /* 6A62C 0016A62C 00008144 */  mtc1       $1, $f0
    /* 6A630 0016A630 04000010 */  b          .L0016A644
    /* 6A634 0016A634 040000E6 */   swc1      $f0, 0x4($16)
.align 2
  .L0016A638:
    /* 6A638 0016A638 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* 6A63C 0016A63C 00008144 */  mtc1       $1, $f0
    /* 6A640 0016A640 040000E6 */  swc1       $f0, 0x4($16)
.align 2
  .L0016A644:
    /* 6A644 0016A644 080000AE */  sw         $0, 0x8($16)
    /* 6A648 0016A648 0C0000AE */  sw         $0, 0xC($16)
    /* 6A64C 0016A64C 2D200002 */  daddu      $4, $16, $0
    /* 6A650 0016A650 80290500 */  sll        $5, $5, 6
    /* 6A654 0016A654 2000BFDF */  ld         $31, 0x20($29)
    /* 6A658 0016A658 5C01238E */  lw         $3, 0x15C($17)
    /* 6A65C 0016A65C 2D308000 */  daddu      $6, $4, $0
    /* 6A660 0016A660 1000B1DF */  ld         $17, 0x10($29)
    /* 6A664 0016A664 0C00628C */  lw         $2, 0xC($3)
    /* 6A668 0016A668 0000B0DF */  ld         $16, 0x0($29)
    /* 6A66C 0016A66C 21284500 */  addu       $5, $2, $5
    /* 6A670 0016A670 2E0E0908 */  j          func_002438B8
    /* 6A674 0016A674 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_0016A5F0
```
