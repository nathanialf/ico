# func_001C0BF8 — parked

VRAM: 0x001C0BF8 (file_off 0x0C0BF8)
Asm source: asm/matchings/src/switch/func_001C0BF8.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (MATERIALIZE,REG)

**TU:** `src/switch.c`

**Seed:** `tough_nuts/func_001C0BF8/func_001C0BF8.c`

Disassembly:

```
.align 3
nonmatching func_001C0BF8, 0x44

glabel func_001C0BF8
    /* C0BF8 001C0BF8 5C01838C */  lw         $3, 0x15C($4)
    /* C0BFC 001C0BFC 0008638C */  lw         $3, 0x800($3)
    /* C0C00 001C0C00 02006284 */  lh         $2, 0x2($3)
    /* C0C04 001C0C04 01004204 */  bltzl      $2, .L001C0C0C
    /* C0C08 001C0C08 23100200 */   negu      $2, $2
.align 2
  .L001C0C0C:
    /* C0C0C 001C0C0C B90B4228 */  slti       $2, $2, 0xBB9
    /* C0C10 001C0C10 07004010 */  beqz       $2, .L001C0C30
    /* C0C14 001C0C14 2D200000 */   daddu     $4, $0, $0
    /* C0C18 001C0C18 00006284 */  lh         $2, 0x0($3)
    /* C0C1C 001C0C1C 01004204 */  bltzl      $2, .L001C0C24
    /* C0C20 001C0C20 23100200 */   negu      $2, $2
.align 2
  .L001C0C24:
    /* C0C24 001C0C24 B90B4228 */  slti       $2, $2, 0xBB9
    /* C0C28 001C0C28 02004014 */  bnez       $2, .L001C0C34
    /* C0C2C 001C0C2C 00000000 */   nop
.align 2
  .L001C0C30:
    /* C0C30 001C0C30 01000424 */  addiu      $4, $0, 0x1
.align 2
  .L001C0C34:
    /* C0C34 001C0C34 0800E003 */  jr         $31
    /* C0C38 001C0C38 2D108000 */   daddu     $2, $4, $0
endlabel func_001C0BF8
    /* C0C3C 001C0C3C 00000000 */  nop
```
