# func_001F16A0 — parked

VRAM: 0x001F16A0 (file_off 0x0F16A0)
Asm source: asm/nonmatchings/cod/0F16A0/func_001F16A0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (KEEP_LIVE)

**TU:** `src/sugiTree.c`

**Seed:** `tough_nuts/func_001F16A0/func_001F16A0.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00632010, 1

.align 3
nonmatching func_001F16A0, 0x54

glabel func_001F16A0
    /* F16A0 001F16A0 D0FFBD27 */  addiu      $29, $29, -0x30
    /* F16A4 001F16A4 6200063C */  lui        $6, %hi(D_0061A6D8)
    /* F16A8 001F16A8 2097848F */  lw         $4, %gp_rel(D_00632010)($gp) /* gp_rel: (D_00632010) */
    /* F16AC 001F16AC D8A6C624 */  addiu      $6, $6, %lo(D_0061A6D8)
    /* F16B0 001F16B0 1000B0FF */  sd         $16, 0x10($29)
    /* F16B4 001F16B4 02000524 */  addiu      $5, $0, 0x2
    /* F16B8 001F16B8 2000BFFF */  sd         $31, 0x20($29)
    /* F16BC 001F16BC 3EE8040C */  jal        func_0013A0F8
    /* F16C0 001F16C0 0C000724 */   addiu     $7, $0, 0xC
    /* F16C4 001F16C4 5893090C */  jal        func_00264D60
    /* F16C8 001F16C8 2D804000 */   daddu     $16, $2, $0
    /* F16CC 001F16CC 2D184000 */  daddu      $3, $2, $0
    /* F16D0 001F16D0 03006104 */  bgez       $3, .L001F16E0
    /* F16D4 001F16D4 000003A6 */   sh        $3, 0x0($16)
    /* F16D8 001F16D8 FFFF0234 */  ori        $2, $0, 0xFFFF
    /* F16DC 001F16DC 21106200 */  addu       $2, $3, $2
.align 2
  .L001F16E0:
    /* F16E0 001F16E0 2D100002 */  daddu      $2, $16, $0
    /* F16E4 001F16E4 2000BFDF */  ld         $31, 0x20($29)
    /* F16E8 001F16E8 1000B0DF */  ld         $16, 0x10($29)
    /* F16EC 001F16EC 0800E003 */  jr         $31
    /* F16F0 001F16F0 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_001F16A0
```
