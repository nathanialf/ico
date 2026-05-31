# func_0012FCE0 — parked

VRAM: 0x0012FCE0 (file_off 0x02FCE0)
Asm source: asm/nonmatchings/src/Texture/func_0012FCE0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (MATERIALIZE)

**TU:** `src/Texture.c`

**Seed:** `tough_nuts/func_0012FCE0/func_0012FCE0.c`

Disassembly:

```
.align 3
nonmatching func_0012FCE0, 0x4C

glabel func_0012FCE0
    /* 2FCE0 0012FCE0 01000224 */  addiu      $2, $0, 0x1
    /* 2FCE4 0012FCE4 FFFF0524 */  addiu      $5, $0, -0x1
    /* 2FCE8 0012FCE8 2A104400 */  slt        $2, $2, $4
    /* 2FCEC 0012FCEC 04004014 */  bnez       $2, .L0012FD00
    /* 2FCF0 0012FCF0 2D180000 */   daddu     $3, $0, $0
    /* 2FCF4 0012FCF4 0B000010 */  b          .L0012FD24
    /* 2FCF8 0012FCF8 2D280000 */   daddu     $5, $0, $0
    /* 2FCFC 0012FCFC 00000000 */  nop
.align 2
  .L0012FD00:
    /* 2FD00 0012FD00 01006324 */  addiu      $3, $3, 0x1
.align 2
  .L0012FD04:
    /* 2FD04 0012FD04 0B006228 */  slti       $2, $3, 0xB
    /* 2FD08 0012FD08 06004010 */  beqz       $2, .L0012FD24
    /* 2FD0C 0012FD0C 01000224 */   addiu     $2, $0, 0x1
    /* 2FD10 0012FD10 04106200 */  sllv       $2, $2, $3
    /* 2FD14 0012FD14 2A104400 */  slt        $2, $2, $4
    /* 2FD18 0012FD18 FAFF4054 */  bnel       $2, $0, .L0012FD04
    /* 2FD1C 0012FD1C 01006324 */   addiu     $3, $3, 0x1
    /* 2FD20 0012FD20 2D286000 */  daddu      $5, $3, $0
.align 2
  .L0012FD24:
    /* 2FD24 0012FD24 0800E003 */  jr         $31
    /* 2FD28 0012FD28 2D10A000 */   daddu     $2, $5, $0
endlabel func_0012FCE0
    /* 2FD2C 0012FD2C 00000000 */  nop
```
