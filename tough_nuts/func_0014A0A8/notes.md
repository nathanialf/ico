# func_0014A0A8 — parked

VRAM: 0x0014A0A8 (file_off 0x04A0A8)
Asm source: asm/matchings/cod/04A0A8/func_0014A0A8.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/act-game.c`

**Seed:** `tough_nuts/func_0014A0A8/func_0014A0A8.c`

Disassembly:

```
.align 3
nonmatching func_0014A0A8, 0x2C

glabel func_0014A0A8
    /* 4A0A8 0014A0A8 6401838C */  lw         $3, 0x164($4)
    /* 4A0AC 0014A0AC A041013C */  lui        $1, (0x41A00000 >> 16)
    /* 4A0B0 0014A0B0 00088144 */  mtc1       $1, $f1
    /* 4A0B4 0014A0B4 D00160C4 */  lwc1       $f0, 0x1D0($3)
    /* 4A0B8 0014A0B8 36000146 */  c.le.s     $f0, $f1
    /* 4A0BC 0014A0BC 00000000 */  nop
    /* 4A0C0 0014A0C0 02000045 */  bc1f       .L0014A0CC
    /* 4A0C4 0014A0C4 2D100000 */   daddu     $2, $0, $0
    /* 4A0C8 0014A0C8 01000224 */  addiu      $2, $0, 0x1
.align 2
  .L0014A0CC:
    /* 4A0CC 0014A0CC 0800E003 */  jr         $31
    /* 4A0D0 0014A0D0 00000000 */   nop
endlabel func_0014A0A8
    /* 4A0D4 0014A0D4 00000000 */  nop
```
