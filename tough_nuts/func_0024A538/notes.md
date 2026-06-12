# func_0024A538 — parked

VRAM: 0x0024A538 (file_off 0x14A538)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0024A538.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (near-miss); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0024A538/func_0024A538.c`

Disassembly:

```
.align 3
nonmatching func_0024A538, 0x80

glabel func_0024A538
    /* 14A538 0024A538 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 14A53C 0024A53C 7100023C */  lui        $2, %hi(D_007115C0)
    /* 14A540 0024A540 1000B0FF */  sd         $16, 0x10($29)
    /* 14A544 0024A544 0F000324 */  addiu      $3, $0, 0xF
    /* 14A548 0024A548 C0155024 */  addiu      $16, $2, %lo(D_007115C0)
    /* 14A54C 0024A54C 7100043C */  lui        $4, %hi(D_00711280)
    /* 14A550 0024A550 2000BFFF */  sd         $31, 0x20($29)
    /* 14A554 0024A554 80128424 */  addiu      $4, $4, %lo(D_00711280)
    /* 14A558 0024A558 C01543AC */  sw         $3, %lo(D_007115C0)($2)
    /* 14A55C 0024A55C 01000524 */  addiu      $5, $0, 0x1
    /* 14A560 0024A560 0000A0AF */  sw         $0, 0x0($29)
    /* 14A564 0024A564 2D300000 */  daddu      $6, $0, $0
    /* 14A568 0024A568 2D380002 */  daddu      $7, $16, $0
    /* 14A56C 0024A56C 80000824 */  addiu      $8, $0, 0x80
    /* 14A570 0024A570 2D480002 */  daddu      $9, $16, $0
    /* 14A574 0024A574 80000A24 */  addiu      $10, $0, 0x80
    /* 14A578 0024A578 5E0A090C */  jal        func_00242978
    /* 14A57C 0024A57C 2D580000 */   daddu     $11, $0, $0
    /* 14A580 0024A580 03004304 */  bgezl      $2, .L0024A590
    /* 14A584 0024A584 0C00078E */   lw        $7, 0xC($16)
    /* 14A588 0024A588 07000010 */  b          .L0024A5A8
    /* 14A58C 0024A58C 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0024A590:
    /* 14A590 0024A590 01000224 */  addiu      $2, $0, 0x1
    /* 14A594 0024A594 0400E214 */  bne        $7, $2, .L0024A5A8
    /* 14A598 0024A598 2D10E000 */   daddu     $2, $7, $0
    /* 14A59C 0024A59C 5500023C */  lui        $2, %hi(D_0054C648)
    /* 14A5A0 0024A5A0 48C640AC */  sw         $0, %lo(D_0054C648)($2)
    /* 14A5A4 0024A5A4 2D10E000 */  daddu      $2, $7, $0
.align 2
  .L0024A5A8:
    /* 14A5A8 0024A5A8 2000BFDF */  ld         $31, 0x20($29)
    /* 14A5AC 0024A5AC 1000B0DF */  ld         $16, 0x10($29)
    /* 14A5B0 0024A5B0 0800E003 */  jr         $31
    /* 14A5B4 0024A5B4 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_0024A538
```
