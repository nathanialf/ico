# func_00104478 — parked

VRAM: 0x00104478 (file_off 0x004478)
Asm source: asm/nonmatchings/src/geometryManager/func_00104478.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (MEM_BARRIER)

**TU:** `src/geometryManager.c`

**Seed:** `tough_nuts/func_00104478/func_00104478.c`

Disassembly:

```
.align 3
nonmatching func_00104478, 0x8C

glabel func_00104478
    /* 4478 00104478 90FFBD27 */  addiu      $29, $29, -0x70
    /* 447C 0010447C 5000B1FF */  sd         $17, 0x50($29)
    /* 4480 00104480 4000B0FF */  sd         $16, 0x40($29)
    /* 4484 00104484 6000BFFF */  sd         $31, 0x60($29)
    /* 4488 00104488 2D808000 */  daddu      $16, $4, $0
    /* 448C 0010448C 5C01028E */  lw         $2, 0x15C($16)
    /* 4490 00104490 A0005124 */  addiu      $17, $2, 0xA0
    /* 4494 00104494 C017040C */  jal        func_00105F00
    /* 4498 00104498 2D202002 */   daddu     $4, $17, $0
    /* 449C 0010449C 040020C6 */  lwc1       $f0, 0x4($17)
    /* 44A0 001044A0 C00021C6 */  lwc1       $f1, 0xC0($17)
    /* 44A4 001044A4 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* 44A8 001044A8 00108144 */  mtc1       $1, $f2
    /* 44AC 001044AC 01000146 */  sub.s      $f0, $f0, $f1
    /* 44B0 001044B0 0C0022E6 */  swc1       $f2, 0xC($17)
    /* 44B4 001044B4 040020E6 */  swc1       $f0, 0x4($17)
    /* 44B8 001044B8 5C01038E */  lw         $3, 0x15C($16)
    /* 44BC 001044BC 0000628C */  lw         $2, 0x0($3)
    /* 44C0 001044C0 0B004010 */  beqz       $2, .L001044F0
    /* 44C4 001044C4 2D20A003 */   daddu     $4, $29, $0
    /* 44C8 001044C8 5C01428C */  lw         $2, 0x15C($2)
    /* 44CC 001044CC 0400658C */  lw         $5, 0x4($3)
    /* 44D0 001044D0 0C00438C */  lw         $3, 0xC($2)
    /* 44D4 001044D4 80290500 */  sll        $5, $5, 6
    /* 44D8 001044D8 9C17040C */  jal        func_00105E70
    /* 44DC 001044DC 21286500 */   addu      $5, $3, $5
    /* 44E0 001044E0 2D202002 */  daddu      $4, $17, $0
    /* 44E4 001044E4 2D28A003 */  daddu      $5, $29, $0
    /* 44E8 001044E8 2E0E090C */  jal        sceVu0ApplyMatrix
    /* 44EC 001044EC 2D308000 */   daddu     $6, $4, $0
.align 2
  .L001044F0:
    /* 44F0 001044F0 6000BFDF */  ld         $31, 0x60($29)
    /* 44F4 001044F4 5000B1DF */  ld         $17, 0x50($29)
    /* 44F8 001044F8 4000B0DF */  ld         $16, 0x40($29)
    /* 44FC 001044FC 0800E003 */  jr         $31
    /* 4500 00104500 7000BD27 */   addiu     $29, $29, 0x70
endlabel func_00104478
    /* 4504 00104504 00000000 */  nop
```
