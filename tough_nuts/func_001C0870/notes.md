# func_001C0870 — parked

VRAM: 0x001C0870 (file_off 0x0C0870)
Asm source: asm/matchings/cod/0C0870/func_001C0870.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/switch.c`

**Seed:** `tough_nuts/func_001C0870/func_001C0870.c`

Disassembly:

```
.align 3
nonmatching func_001C0870, 0x48

glabel func_001C0870
    /* C0870 001C0870 D0FFBD27 */  addiu      $29, $29, -0x30
    /* C0874 001C0874 1000B1FF */  sd         $17, 0x10($29)
    /* C0878 001C0878 2000BFFF */  sd         $31, 0x20($29)
    /* C087C 001C087C 2D88A000 */  daddu      $17, $5, $0
    /* C0880 001C0880 0000B0FF */  sd         $16, 0x0($29)
    /* C0884 001C0884 5C01828C */  lw         $2, 0x15C($4)
    /* C0888 001C0888 0008508C */  lw         $16, 0x800($2)
    /* C088C 001C088C 0400038E */  lw         $3, 0x4($16)
    /* C0890 001C0890 04007150 */  beql       $3, $17, .L001C08A4
    /* C0894 001C0894 040011AE */   sw        $17, 0x4($16)
    /* C0898 001C0898 2AF0060C */  jal        func_001BC0A8
    /* C089C 001C089C 00000000 */   nop
    /* C08A0 001C08A0 040011AE */  sw         $17, 0x4($16)
.align 2
  .L001C08A4:
    /* C08A4 001C08A4 2000BFDF */  ld         $31, 0x20($29)
    /* C08A8 001C08A8 1000B1DF */  ld         $17, 0x10($29)
    /* C08AC 001C08AC 0000B0DF */  ld         $16, 0x0($29)
    /* C08B0 001C08B0 0800E003 */  jr         $31
    /* C08B4 001C08B4 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_001C0870
```
