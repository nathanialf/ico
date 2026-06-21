# debug_GetDebugOption — parked

VRAM: 0x001A0420 (file_off 0x0A0420)
Asm source: asm/aug6/nonmatchings/common/src/debug/debug_GetDebugOption.s

## Attempt at 2026-06-21

**Reason parked:** override=permute

**TU:** `common/src/debug.c`

**Seed:** `tough_nuts/debug_GetDebugOption/debug_GetDebugOption.c`

Disassembly:

```
.align 3
nonmatching debug_GetDebugOption, 0x120

glabel debug_GetDebugOption
    /* A0420 001A0420 90FEBD27 */  addiu      $29, $29, -0x170
    /* A0424 001A0424 6100043C */  lui        $4, %hi(D_0060D520)
    /* A0428 001A0428 1001B1FF */  sd         $17, 0x110($29)
    /* A042C 001A042C 20D58424 */  addiu      $4, $4, %lo(D_0060D520)
    /* A0430 001A0430 6001BFFF */  sd         $31, 0x160($29)
    /* A0434 001A0434 5001B5FF */  sd         $21, 0x150($29)
    /* A0438 001A0438 4001B4FF */  sd         $20, 0x140($29)
    /* A043C 001A043C 3001B3FF */  sd         $19, 0x130($29)
    /* A0440 001A0440 2001B2FF */  sd         $18, 0x120($29)
    /* A0444 001A0444 F290060C */  jal        debug_assertMessage
    /* A0448 001A0448 0001B0FF */   sd        $16, 0x100($29)
    /* A044C 001A044C 6100043C */  lui        $4, %hi(D_0060D560)
    /* A0450 001A0450 02060524 */  addiu      $5, $0, 0x602
    /* A0454 001A0454 A29E060C */  jal        func_001A7A88
    /* A0458 001A0458 60D58424 */   addiu     $4, $4, %lo(D_0060D560)
    /* A045C 001A045C C28F0200 */  srl        $17, $2, 31
    /* A0460 001A0460 06002012 */  beqz       $17, .L001A047C
    /* A0464 001A0464 6100153C */   lui       $21, %hi(D_0060D4E0)
    /* A0468 001A0468 6100043C */  lui        $4, %hi(D_0060D578)
    /* A046C 001A046C F290060C */  jal        debug_assertMessage
    /* A0470 001A0470 78D58424 */   addiu     $4, $4, %lo(D_0060D578)
    /* A0474 001A0474 25000010 */  b          .L001A050C
    /* A0478 001A0478 00000000 */   nop
.align 2
  .L001A047C:
    /* A047C 001A047C 6100023C */  lui        $2, %hi(D_0060C610)
    /* A0480 001A0480 6300143C */  lui        $20, %hi(D_0062CB60)
    /* A0484 001A0484 10C65024 */  addiu      $16, $2, %lo(D_0060C610)
    /* A0488 001A0488 6300133C */  lui        $19, %hi(D_0062CB68)
    /* A048C 001A048C 54071226 */  addiu      $18, $16, 0x754
    /* A0490 001A0490 0000068E */  lw         $6, 0x0($16)
    /* A0494 001A0494 00000000 */  nop
.align 2
  .L001A0498:
    /* A0498 001A0498 2D20A003 */  daddu      $4, $29, $0
    /* A049C 001A049C 6284090C */  jal        func_00261188
    /* A04A0 001A04A0 60CB8526 */   addiu     $5, $20, %lo(D_0062CB60)
    /* A04A4 001A04A4 8385090C */  jal        func_0026160C
    /* A04A8 001A04A8 2D20A003 */   daddu     $4, $29, $0
    /* A04AC 001A04AC 2D304000 */  daddu      $6, $2, $0
    /* A04B0 001A04B0 2D202002 */  daddu      $4, $17, $0
    /* A04B4 001A04B4 5410090C */  jal        func_00244150
    /* A04B8 001A04B8 2D28A003 */   daddu     $5, $29, $0
    /* A04BC 001A04BC 0800038E */  lw         $3, 0x8($16)
    /* A04C0 001A04C0 2D20A003 */  daddu      $4, $29, $0
    /* A04C4 001A04C4 68CB6526 */  addiu      $5, $19, %lo(D_0062CB68)
    /* A04C8 001A04C8 1C001026 */  addiu      $16, $16, 0x1C
    /* A04CC 001A04CC 6284090C */  jal        func_00261188
    /* A04D0 001A04D0 0000668C */   lw        $6, 0x0($3)
    /* A04D4 001A04D4 8385090C */  jal        func_0026160C
    /* A04D8 001A04D8 2D20A003 */   daddu     $4, $29, $0
    /* A04DC 001A04DC 2D304000 */  daddu      $6, $2, $0
    /* A04E0 001A04E0 2D202002 */  daddu      $4, $17, $0
    /* A04E4 001A04E4 5410090C */  jal        func_00244150
    /* A04E8 001A04E8 2D28A003 */   daddu     $5, $29, $0
    /* A04EC 001A04EC 2A181202 */  slt        $3, $16, $18
    /* A04F0 001A04F0 E9FF6054 */  bnel       $3, $0, .L001A0498
    /* A04F4 001A04F4 0000068E */   lw        $6, 0x0($16)
    /* A04F8 001A04F8 BA9E060C */  jal        func_001A7AE8
    /* A04FC 001A04FC 2D202002 */   daddu     $4, $17, $0
    /* A0500 001A0500 6100043C */  lui        $4, %hi(D_0060D5B0)
    /* A0504 001A0504 F290060C */  jal        debug_assertMessage
    /* A0508 001A0508 B0D58424 */   addiu     $4, $4, %lo(D_0060D5B0)
.align 2
  .L001A050C:
    /* A050C 001A050C F290060C */  jal        debug_assertMessage
    /* A0510 001A0510 E0D4A426 */   addiu     $4, $21, %lo(D_0060D4E0)
    /* A0514 001A0514 EC80060C */  jal        debug_LogPrintf
    /* A0518 001A0518 00000000 */   nop
    /* A051C 001A051C 6001BFDF */  ld         $31, 0x160($29)
    /* A0520 001A0520 5001B5DF */  ld         $21, 0x150($29)
    /* A0524 001A0524 4001B4DF */  ld         $20, 0x140($29)
    /* A0528 001A0528 3001B3DF */  ld         $19, 0x130($29)
    /* A052C 001A052C 2001B2DF */  ld         $18, 0x120($29)
    /* A0530 001A0530 1001B1DF */  ld         $17, 0x110($29)
    /* A0534 001A0534 0001B0DF */  ld         $16, 0x100($29)
    /* A0538 001A0538 0800E003 */  jr         $31
    /* A053C 001A053C 7001BD27 */   addiu     $29, $29, 0x170
endlabel debug_GetDebugOption
```
