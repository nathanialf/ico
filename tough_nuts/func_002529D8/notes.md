# func_002529D8 — parked

VRAM: 0x002529D8 (file_off 0x1529D8)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_002529D8.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_002529D8/func_002529D8.c`

Disassembly:

```
.align 3
nonmatching func_002529D8, 0x68

glabel func_002529D8
    /* 1529D8 002529D8 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 1529DC 002529DC 1000BFFF */  sd         $31, 0x10($29)
    /* 1529E0 002529E0 C448090C */  jal        func_00252310
    /* 1529E4 002529E4 0000B0FF */   sd        $16, 0x0($29)
    /* 1529E8 002529E8 0010023C */  lui        $2, (0x10002020 >> 16)
    /* 1529EC 002529EC 20204234 */  ori        $2, $2, (0x10002020 & 0xFFFF)
    /* 1529F0 002529F0 0000438C */  lw         $3, 0x0($2)
    /* 1529F4 002529F4 07006330 */  andi       $3, $3, 0x7
    /* 1529F8 002529F8 23180300 */  negu       $3, $3
    /* 1529FC 002529FC 07006430 */  andi       $4, $3, 0x7
    /* 152A00 00252A00 07008010 */  beqz       $4, .L00252A20
    /* 152A04 00252A04 01001024 */   addiu     $16, $0, 0x1
    /* 152A08 00252A08 D649090C */  jal        func_00252758
    /* 152A0C 00252A0C 00000000 */   nop
    /* 152A10 00252A10 03000010 */  b          .L00252A20
    /* 152A14 00252A14 00000000 */   nop
.align 2
  .L00252A18:
    /* 152A18 00252A18 D649090C */  jal        func_00252758
    /* 152A1C 00252A1C 00000000 */   nop
.align 2
  .L00252A20:
    /* 152A20 00252A20 8849090C */  jal        func_00252620
    /* 152A24 00252A24 18000424 */   addiu     $4, $0, 0x18
    /* 152A28 00252A28 FBFF5014 */  bne        $2, $16, .L00252A18
    /* 152A2C 00252A2C 08000424 */   addiu     $4, $0, 0x8
    /* 152A30 00252A30 1000BFDF */  ld         $31, 0x10($29)
    /* 152A34 00252A34 0000B0DF */  ld         $16, 0x0($29)
    /* 152A38 00252A38 0800E003 */  jr         $31
    /* 152A3C 00252A3C 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_002529D8
```
