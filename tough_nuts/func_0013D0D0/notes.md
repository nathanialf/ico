# func_0013D0D0 — parked

VRAM: 0x0013D0D0 (file_off 0x03D0D0)
Asm source: asm/nonmatchings/ios/thread/func_0013D0D0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (ANCHOR,REG)

**TU:** `ios/thread.c`

**Seed:** `tough_nuts/func_0013D0D0/func_0013D0D0.c`

Disassembly:

```
.align 3
nonmatching func_0013D0D0, 0x6C

glabel func_0013D0D0
    /* 3D0D0 0013D0D0 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 3D0D4 0013D0D4 1000BFFF */  sd         $31, 0x10($29)
    /* 3D0D8 0013D0D8 0000B0FF */  sd         $16, 0x0($29)
    /* 3D0DC 0013D0DC 3000A38C */  lw         $3, 0x30($5)
    /* 3D0E0 0013D0E0 05006010 */  beqz       $3, .L0013D0F8
    /* 3D0E4 0013D0E4 2D308000 */   daddu     $6, $4, $0
    /* 3D0E8 0013D0E8 3400A28C */  lw         $2, 0x34($5)
    /* 3D0EC 0013D0EC 340062AC */  sw         $2, 0x34($3)
    /* 3D0F0 0013D0F0 03000010 */  b          .L0013D100
    /* 3D0F4 0013D0F4 3400B08C */   lw        $16, 0x34($5)
.align 2
  .L0013D0F8:
    /* 3D0F8 0013D0F8 3400B08C */  lw         $16, 0x34($5)
    /* 3D0FC 0013D0FC 0000D0AC */  sw         $16, 0x0($6)
.align 2
  .L0013D100:
    /* 3D100 0013D100 05000052 */  beql       $16, $0, .L0013D118
    /* 3D104 0013D104 0800C28C */   lw        $2, 0x8($6)
    /* 3D108 0013D108 3000A28C */  lw         $2, 0x30($5)
    /* 3D10C 0013D10C 300002AE */  sw         $2, 0x30($16)
    /* 3D110 0013D110 3400B08C */  lw         $16, 0x34($5)
    /* 3D114 0013D114 0800C28C */  lw         $2, 0x8($6)
.align 2
  .L0013D118:
    /* 3D118 0013D118 03004010 */  beqz       $2, .L0013D128
    /* 3D11C 0013D11C 2D20A000 */   daddu     $4, $5, $0
    /* 3D120 0013D120 09F84000 */  jalr       $2
    /* 3D124 0013D124 0C00C58C */   lw        $5, 0xC($6)
.align 2
  .L0013D128:
    /* 3D128 0013D128 2D100002 */  daddu      $2, $16, $0
    /* 3D12C 0013D12C 1000BFDF */  ld         $31, 0x10($29)
    /* 3D130 0013D130 0000B0DF */  ld         $16, 0x0($29)
    /* 3D134 0013D134 0800E003 */  jr         $31
    /* 3D138 0013D138 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_0013D0D0
    /* 3D13C 0013D13C 00000000 */  nop
```
