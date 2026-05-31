# func_001BBDD8 — parked

VRAM: 0x001BBDD8 (file_off 0x0BBDD8)
Asm source: asm/nonmatchings/cod/0BBDD8/func_001BBDD8.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/attackCheckBoundary.c`

**Seed:** `tough_nuts/func_001BBDD8/func_001BBDD8.c`

Disassembly:

```
.align 3
nonmatching func_001BBDD8, 0x6C

glabel func_001BBDD8
    /* BBDD8 001BBDD8 5C01838C */  lw         $3, 0x15C($4)
    /* BBDDC 001BBDDC 0008698C */  lw         $9, 0x800($3)
    /* BBDE0 001BBDE0 0000228D */  lw         $2, 0x0($9)
    /* BBDE4 001BBDE4 13004018 */  blez       $2, .L001BBE34
    /* BBDE8 001BBDE8 2D400000 */   daddu     $8, $0, $0
    /* BBDEC 001BBDEC 0C002A8D */  lw         $10, 0xC($9)
    /* BBDF0 001BBDF0 C0280800 */  sll        $5, $8, 3
    /* BBDF4 001BBDF4 01000724 */  addiu      $7, $0, 0x1
.align 2
  .L001BBDF8:
    /* BBDF8 001BBDF8 2128AA00 */  addu       $5, $5, $10
    /* BBDFC 001BBDFC 01000825 */  addiu      $8, $8, 0x1
    /* BBE00 001BBE00 0000A68C */  lw         $6, 0x0($5)
    /* BBE04 001BBE04 5C01C28C */  lw         $2, 0x15C($6)
    /* BBE08 001BBE08 0008438C */  lw         $3, 0x800($2)
    /* BBE0C 001BBE0C 0400648C */  lw         $4, 0x4($3)
    /* BBE10 001BBE10 0400A4AC */  sw         $4, 0x4($5)
    /* BBE14 001BBE14 5C01C28C */  lw         $2, 0x15C($6)
    /* BBE18 001BBE18 0008438C */  lw         $3, 0x800($2)
    /* BBE1C 001BBE1C 040060AC */  sw         $0, 0x4($3)
    /* BBE20 001BBE20 6C01C7AC */  sw         $7, 0x16C($6)
    /* BBE24 001BBE24 0000228D */  lw         $2, 0x0($9)
    /* BBE28 001BBE28 2A100201 */  slt        $2, $8, $2
    /* BBE2C 001BBE2C F2FF4014 */  bnez       $2, .L001BBDF8
    /* BBE30 001BBE30 C0280800 */   sll       $5, $8, 3
.align 2
  .L001BBE34:
    /* BBE34 001BBE34 0400228D */  lw         $2, 0x4($9)
    /* BBE38 001BBE38 040020AD */  sw         $0, 0x4($9)
    /* BBE3C 001BBE3C 0800E003 */  jr         $31
    /* BBE40 001BBE40 080022AD */   sw        $2, 0x8($9)
endlabel func_001BBDD8
    /* BBE44 001BBE44 00000000 */  nop
```
