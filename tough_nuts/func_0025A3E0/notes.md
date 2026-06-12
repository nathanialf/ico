# func_0025A3E0 — parked

VRAM: 0x0025A3E0 (file_off 0x15A3E0)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0025A3E0.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0025A3E0/func_0025A3E0.c`

Disassembly:

```
.align 3
nonmatching func_0025A3E0, 0x6C

glabel func_0025A3E0
    /* 15A3E0 0025A3E0 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 15A3E4 0025A3E4 1F00033C */  lui        $3, (0x1FFFFF >> 16)
    /* 15A3E8 0025A3E8 0000BFFF */  sd         $31, 0x0($29)
    /* 15A3EC 0025A3EC FFFF6334 */  ori        $3, $3, (0x1FFFFF & 0xFFFF)
    /* 15A3F0 0025A3F0 0800868C */  lw         $6, 0x8($4)
    /* 15A3F4 0025A3F4 2B106600 */  sltu       $2, $3, $6
    /* 15A3F8 0025A3F8 10004014 */  bnez       $2, .L0025A43C
    /* 15A3FC 0025A3FC FFFF0824 */   addiu     $8, $0, -0x1
    /* 15A400 0025A400 0C00878C */  lw         $7, 0xC($4)
    /* 15A404 0025A404 2B106700 */  sltu       $2, $3, $7
    /* 15A408 0025A408 0D004014 */  bnez       $2, .L0025A440
    /* 15A40C 0025A40C 0000BFDF */   ld        $31, 0x0($29)
    /* 15A410 0025A410 0000858C */  lw         $5, 0x0($4)
    /* 15A414 0025A414 0A00A004 */  bltz       $5, .L0025A440
    /* 15A418 0025A418 1000A228 */   slti      $2, $5, 0x10
    /* 15A41C 0025A41C 09004010 */  beqz       $2, .L0025A444
    /* 15A420 0025A420 2D100001 */   daddu     $2, $8, $0
    /* 15A424 0025A424 0400828C */  lw         $2, 0x4($4)
    /* 15A428 0025A428 002E0500 */  sll        $5, $5, 24
    /* 15A42C 0025A42C 48000424 */  addiu      $4, $0, 0x48
    /* 15A430 0025A430 6055090C */  jal        func_00255580
    /* 15A434 0025A434 2528A200 */   or        $5, $5, $2
    /* 15A438 0025A438 2D400000 */  daddu      $8, $0, $0
.align 2
  .L0025A43C:
    /* 15A43C 0025A43C 0000BFDF */  ld         $31, 0x0($29)
.align 2
  .L0025A440:
    /* 15A440 0025A440 2D100001 */  daddu      $2, $8, $0
.align 2
  .L0025A444:
    /* 15A444 0025A444 0800E003 */  jr         $31
    /* 15A448 0025A448 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_0025A3E0
    /* 15A44C 0025A44C 00000000 */  nop
```
