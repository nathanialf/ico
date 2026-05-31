# func_001C06A0 — parked

VRAM: 0x001C06A0 (file_off 0x0C06A0)
Asm source: asm/matchings/src/switch/func_001C06A0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/switch.c`

**Seed:** `tough_nuts/func_001C06A0/func_001C06A0.c`

Disassembly:

```
.align 3
nonmatching func_001C06A0, 0x68

glabel func_001C06A0
    /* C06A0 001C06A0 E0FFBD27 */  addiu      $29, $29, -0x20
    /* C06A4 001C06A4 1000BFFF */  sd         $31, 0x10($29)
    /* C06A8 001C06A8 0000B0FF */  sd         $16, 0x0($29)
    /* C06AC 001C06AC 5C01828C */  lw         $2, 0x15C($4)
    /* C06B0 001C06B0 0008508C */  lw         $16, 0x800($2)
    /* C06B4 001C06B4 5800038E */  lw         $3, 0x58($16)
    /* C06B8 001C06B8 04006010 */  beqz       $3, .L001C06CC
    /* C06BC 001C06BC 00000000 */   nop
    /* C06C0 001C06C0 1001028E */  lw         $2, 0x110($16)
    /* C06C4 001C06C4 0B004014 */  bnez       $2, .L001C06F4
    /* C06C8 001C06C8 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L001C06CC:
    /* C06CC 001C06CC 0500A004 */  bltz       $5, .L001C06E4
    /* C06D0 001C06D0 00000000 */   nop
    /* C06D4 001C06D4 6CF2060C */  jal        func_001BC9B0
    /* C06D8 001C06D8 00000000 */   nop
    /* C06DC 001C06DC 04000010 */  b          .L001C06F0
    /* C06E0 001C06E0 140100AE */   sw        $0, 0x114($16)
.align 2
  .L001C06E4:
    /* C06E4 001C06E4 6EF2060C */  jal        func_001BC9B8
    /* C06E8 001C06E8 00000000 */   nop
    /* C06EC 001C06EC 140100AE */  sw         $0, 0x114($16)
.align 2
  .L001C06F0:
    /* C06F0 001C06F0 01000224 */  addiu      $2, $0, 0x1
.align 2
  .L001C06F4:
    /* C06F4 001C06F4 1000BFDF */  ld         $31, 0x10($29)
    /* C06F8 001C06F8 100102AE */  sw         $2, 0x110($16)
    /* C06FC 001C06FC 0000B0DF */  ld         $16, 0x0($29)
    /* C0700 001C0700 0800E003 */  jr         $31
    /* C0704 001C0704 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_001C06A0
```
