# func_0026B908 — parked

VRAM: 0x0026B908 (file_off 0x16B908)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0026B908.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0026B908/func_0026B908.c`

Disassembly:

```
.align 3
nonmatching func_0026B908, 0x5C

glabel func_0026B908
    /* 16B908 0026B908 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 16B90C 0026B90C 1000B1FF */  sd         $17, 0x10($29)
    /* 16B910 0026B910 0000B0FF */  sd         $16, 0x0($29)
    /* 16B914 0026B914 2D880000 */  daddu      $17, $0, $0
    /* 16B918 0026B918 2D808000 */  daddu      $16, $4, $0
    /* 16B91C 0026B91C 2000BFFF */  sd         $31, 0x20($29)
    /* 16B920 0026B920 287D090C */  jal        func_0025F4A0
    /* 16B924 0026B924 2D282002 */   daddu     $5, $17, $0
    /* 16B928 0026B928 07004104 */  bgez       $2, .L0026B948
    /* 16B92C 0026B92C 2D202002 */   daddu     $4, $17, $0
    /* 16B930 0026B930 C47B090C */  jal        func_0025EF10
    /* 16B934 0026B934 2D280002 */   daddu     $5, $16, $0
    /* 16B938 0026B938 D275090C */  jal        func_0025D748
    /* 16B93C 0026B93C 2D204000 */   daddu     $4, $2, $0
    /* 16B940 0026B940 03000010 */  b          .L0026B950
    /* 16B944 0026B944 2F100200 */   dsubu     $2, $0, $2
.align 2
  .L0026B948:
    /* 16B948 0026B948 D275090C */  jal        func_0025D748
    /* 16B94C 0026B94C 2D200002 */   daddu     $4, $16, $0
.align 2
  .L0026B950:
    /* 16B950 0026B950 2000BFDF */  ld         $31, 0x20($29)
    /* 16B954 0026B954 1000B1DF */  ld         $17, 0x10($29)
    /* 16B958 0026B958 0000B0DF */  ld         $16, 0x0($29)
    /* 16B95C 0026B95C 0800E003 */  jr         $31
    /* 16B960 0026B960 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_0026B908
    /* 16B964 0026B964 00000000 */  nop
    /* 16B968 0026B968 00000000 */  nop
    /* 16B96C 0026B96C 00000000 */  nop
```
