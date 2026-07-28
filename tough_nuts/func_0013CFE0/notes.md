# func_0013CFE0 — parked

VRAM: 0x0013CFE0 (file_off 0x03CFE0)
Asm source: asm/nonmatchings/ios/thread/func_0013CFE0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (DEFEAT_TCO)

**TU:** `ios/thread.c`

**Seed:** `tough_nuts/func_0013CFE0/func_0013CFE0.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00632190, 1

.align 3
nonmatching func_0013CFE0, 0xB8

glabel func_0013CFE0
    /* 3CFE0 0013CFE0 90FFBD27 */  addiu      $29, $29, -0x70
    /* 3CFE4 0013CFE4 5000B5FF */  sd         $21, 0x50($29)
    /* 3CFE8 0013CFE8 4000B4FF */  sd         $20, 0x40($29)
    /* 3CFEC 0013CFEC 2DA8A000 */  daddu      $21, $5, $0
    /* 3CFF0 0013CFF0 3000B3FF */  sd         $19, 0x30($29)
    /* 3CFF4 0013CFF4 2DA0C000 */  daddu      $20, $6, $0
    /* 3CFF8 0013CFF8 2000B2FF */  sd         $18, 0x20($29)
    /* 3CFFC 0013CFFC 2D980000 */  daddu      $19, $0, $0
    /* 3D000 0013D000 1000B1FF */  sd         $17, 0x10($29)
    /* 3D004 0013D004 2D908000 */  daddu      $18, $4, $0
    /* 3D008 0013D008 6000BFFF */  sd         $31, 0x60($29)
    /* 3D00C 0013D00C 2D880000 */  daddu      $17, $0, $0
    /* 3D010 0013D010 18004012 */  beqz       $18, .L0013D074
    /* 3D014 0013D014 0000B0FF */   sd        $16, 0x0($29)
    /* 3D018 0013D018 0000508E */  lw         $16, 0x0($18)
    /* 3D01C 0013D01C 0F000012 */  beqz       $16, .L0013D05C
    /* 3D020 0013D020 0001232A */   slti      $3, $17, 0x100
    /* 3D024 0013D024 00000000 */  nop
.align 2
  .L0013D028:
    /* 3D028 0013D028 A098828F */  lw         $2, (D_00632190) /* gp_rel: (D_00632190) */
    /* 3D02C 0013D02C 2D200002 */  daddu      $4, $16, $0
    /* 3D030 0013D030 88EF040C */  jal        func_0013BE20
    /* 3D034 0013D034 0800458C */   lw        $5, 0x8($2)
    /* 3D038 0013D038 A098838F */  lw         $3, (D_00632190) /* gp_rel: (D_00632190) */
    /* 3D03C 0013D03C 2D200002 */  daddu      $4, $16, $0
    /* 3D040 0013D040 21882202 */  addu       $17, $17, $2
    /* 3D044 0013D044 E0EE040C */  jal        func_0013BB80
    /* 3D048 0013D048 0800658C */   lw        $5, 0x8($3)
    /* 3D04C 0013D04C 3400108E */  lw         $16, 0x34($16)
    /* 3D050 0013D050 F5FF0016 */  bnez       $16, .L0013D028
    /* 3D054 0013D054 25986202 */   or        $19, $19, $2
    /* 3D058 0013D058 0001232A */  slti       $3, $17, 0x100
.align 2
  .L0013D05C:
    /* 3D05C 0013D05C FF000224 */  addiu      $2, $0, 0xFF
    /* 3D060 0013D060 0A884300 */  movz       $17, $2, $3
    /* 3D064 0013D064 2D204002 */  daddu      $4, $18, $0
    /* 3D068 0013D068 000091A2 */  sb         $17, 0x0($20)
    /* 3D06C 0013D06C 08F2040C */  jal        func_0013C820
    /* 3D070 0013D070 0000B3A2 */   sb        $19, 0x0($21)
.align 2
  .L0013D074:
    /* 3D074 0013D074 6000BFDF */  ld         $31, 0x60($29)
    /* 3D078 0013D078 5000B5DF */  ld         $21, 0x50($29)
    /* 3D07C 0013D07C 4000B4DF */  ld         $20, 0x40($29)
    /* 3D080 0013D080 3000B3DF */  ld         $19, 0x30($29)
    /* 3D084 0013D084 2000B2DF */  ld         $18, 0x20($29)
    /* 3D088 0013D088 1000B1DF */  ld         $17, 0x10($29)
    /* 3D08C 0013D08C 0000B0DF */  ld         $16, 0x0($29)
    /* 3D090 0013D090 0800E003 */  jr         $31
    /* 3D094 0013D094 7000BD27 */   addiu     $29, $29, 0x70
endlabel func_0013CFE0
```
