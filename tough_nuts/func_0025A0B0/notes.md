# SgStAdpcmOpen — parked

VRAM: 0x0025A0B0 (file_off 0x15A0B0)
Asm source: asm/aug6/nonmatchings/common/src/PObj/SgStAdpcmOpen.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (near-miss); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/SgStAdpcmOpen/SgStAdpcmOpen.c`

Disassembly:

```
.align 3
nonmatching SgStAdpcmOpen, 0x90

glabel SgStAdpcmOpen
    /* 15A0B0 0025A0B0 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 15A0B4 0025A0B4 0000B0FF */  sd         $16, 0x0($29)
    /* 15A0B8 0025A0B8 1000BFFF */  sd         $31, 0x10($29)
    /* 15A0BC 0025A0BC FE53090C */  jal        func_00254FF8
    /* 15A0C0 0025A0C0 2D808000 */   daddu     $16, $4, $0
    /* 15A0C4 0025A0C4 0C000A8E */  lw         $10, 0xC($16)
    /* 15A0C8 0025A0C8 FF00043C */  lui        $4, (0xFF0000 >> 16)
    /* 15A0CC 0025A0CC FF00083C */  lui        $8, (0xFFFFFF >> 16)
    /* 15A0D0 0025A0D0 00000592 */  lbu        $5, 0x0($16)
    /* 15A0D4 0025A0D4 024A0A00 */  srl        $9, $10, 8
    /* 15A0D8 0025A0D8 0400028E */  lw         $2, 0x4($16)
    /* 15A0DC 0025A0DC FFFF0835 */  ori        $8, $8, (0xFFFFFF & 0xFFFF)
    /* 15A0E0 0025A0E0 1000068E */  lw         $6, 0x10($16)
    /* 15A0E4 0025A0E4 002E0500 */  sll        $5, $5, 24
    /* 15A0E8 0025A0E8 1400038E */  lw         $3, 0x14($16)
    /* 15A0EC 0025A0EC 24104400 */  and        $2, $2, $4
    /* 15A0F0 0025A0F0 0800078E */  lw         $7, 0x8($16)
    /* 15A0F4 0025A0F4 2420C400 */  and        $4, $6, $4
    /* 15A0F8 0025A0F8 2528A200 */  or         $5, $5, $2
    /* 15A0FC 0025A0FC 00FF6330 */  andi       $3, $3, 0xFF00
    /* 15A100 0025A100 02240400 */  srl        $4, $4, 16
    /* 15A104 0025A104 2528A300 */  or         $5, $5, $3
    /* 15A108 0025A108 2438E800 */  and        $7, $7, $8
    /* 15A10C 0025A10C FFFF2931 */  andi       $9, $9, 0xFFFF
    /* 15A110 0025A110 00560A00 */  sll        $10, $10, 24
    /* 15A114 0025A114 00340600 */  sll        $6, $6, 16
    /* 15A118 0025A118 2528A400 */  or         $5, $5, $4
    /* 15A11C 0025A11C 2530C900 */  or         $6, $6, $9
    /* 15A120 0025A120 25384701 */  or         $7, $10, $7
    /* 15A124 0025A124 6055090C */  jal        _SgSetPkAdd
    /* 15A128 0025A128 3E000424 */   addiu     $4, $0, 0x3E
    /* 15A12C 0025A12C 1000BFDF */  ld         $31, 0x10($29)
    /* 15A130 0025A130 2D100000 */  daddu      $2, $0, $0
    /* 15A134 0025A134 0000B0DF */  ld         $16, 0x0($29)
    /* 15A138 0025A138 0800E003 */  jr         $31
    /* 15A13C 0025A13C 2000BD27 */   addiu     $29, $29, 0x20
endlabel SgStAdpcmOpen
```
