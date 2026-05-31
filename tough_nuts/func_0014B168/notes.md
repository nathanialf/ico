# func_0014B168 — parked

VRAM: 0x0014B168 (file_off 0x04B168)
Asm source: asm/nonmatchings/src/act-parallel-control/func_0014B168.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (ANCHOR,REG)

**TU:** `src/act-parallel-control.c`

**Seed:** `tough_nuts/func_0014B168/func_0014B168.c`

Disassembly:

```
.align 3
nonmatching func_0014B168, 0x64

glabel func_0014B168
    /* 4B168 0014B168 6401838C */  lw         $3, 0x164($4)
    /* 4B16C 0014B16C 06000224 */  addiu      $2, $0, 0x6
    /* 4B170 0014B170 0500E214 */  bne        $7, $2, .L0014B188
    /* 4B174 0014B174 2D200000 */   daddu     $4, $0, $0
    /* 4B178 0014B178 9C0060AC */  sw         $0, 0x9C($3)
    /* 4B17C 0014B17C 980060AC */  sw         $0, 0x98($3)
    /* 4B180 0014B180 10000010 */  b          .L0014B1C4
    /* 4B184 0014B184 A00060AC */   sw        $0, 0xA0($3)
.align 2
  .L0014B188:
    /* 4B188 0014B188 9C00628C */  lw         $2, 0x9C($3)
    /* 4B18C 0014B18C 2A10E200 */  slt        $2, $7, $2
    /* 4B190 0014B190 0C004014 */  bnez       $2, .L0014B1C4
    /* 4B194 0014B194 00000000 */   nop
    /* 4B198 0014B198 0700C010 */  beqz       $6, .L0014B1B8
    /* 4B19C 0014B19C 980065AC */   sw        $5, 0x98($3)
    /* 4B1A0 0014B1A0 0000C0C4 */  lwc1       $f0, 0x0($6)
    /* 4B1A4 0014B1A4 B00060E4 */  swc1       $f0, 0xB0($3)
    /* 4B1A8 0014B1A8 0400C1C4 */  lwc1       $f1, 0x4($6)
    /* 4B1AC 0014B1AC B40061E4 */  swc1       $f1, 0xB4($3)
    /* 4B1B0 0014B1B0 0800C0C4 */  lwc1       $f0, 0x8($6)
    /* 4B1B4 0014B1B4 B80060E4 */  swc1       $f0, 0xB8($3)
.align 2
  .L0014B1B8:
    /* 4B1B8 0014B1B8 9C0067AC */  sw         $7, 0x9C($3)
    /* 4B1BC 0014B1BC 01000424 */  addiu      $4, $0, 0x1
    /* 4B1C0 0014B1C0 A00068AC */  sw         $8, 0xA0($3)
.align 2
  .L0014B1C4:
    /* 4B1C4 0014B1C4 0800E003 */  jr         $31
    /* 4B1C8 0014B1C8 2D108000 */   daddu     $2, $4, $0
endlabel func_0014B168
    /* 4B1CC 0014B1CC 00000000 */  nop
```
