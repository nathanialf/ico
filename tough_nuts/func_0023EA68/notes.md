# func_0023EA68 — parked

VRAM: 0x0023EA68 (file_off 0x13EA68)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0023EA68.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0023EA68/func_0023EA68.c`

Disassembly:

```
.align 3
nonmatching func_0023EA68, 0x5C

glabel func_0023EA68
    /* 13EA68 0023EA68 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 13EA6C 0023EA6C 1000B1FF */  sd         $17, 0x10($29)
    /* 13EA70 0023EA70 2D888000 */  daddu      $17, $4, $0
    /* 13EA74 0023EA74 0000B0FF */  sd         $16, 0x0($29)
    /* 13EA78 0023EA78 0100B030 */  andi       $16, $5, 0x1
    /* 13EA7C 0023EA7C 28000424 */  addiu      $4, $0, 0x28
    /* 13EA80 0023EA80 18100402 */  mult       $2, $16, $4
    /* 13EA84 0023EA84 2000BFFF */  sd         $31, 0x20($29)
    /* 13EA88 0023EA88 10F9080C */  jal        func_0023E440
    /* 13EA8C 0023EA8C 21205100 */   addu      $4, $2, $17
    /* 13EA90 0023EA90 05000012 */  beqz       $16, .L0023EAA8
    /* 13EA94 0023EA94 00000000 */   nop
    /* 13EA98 0023EA98 BAF9080C */  jal        func_0023E6E8
    /* 13EA9C 0023EA9C 40012426 */   addiu     $4, $17, 0x140
    /* 13EAA0 0023EAA0 04000010 */  b          .L0023EAB4
    /* 13EAA4 0023EAA4 2000BFDF */   ld        $31, 0x20($29)
.align 2
  .L0023EAA8:
    /* 13EAA8 0023EAA8 BAF9080C */  jal        func_0023E6E8
    /* 13EAAC 0023EAAC 50002426 */   addiu     $4, $17, 0x50
    /* 13EAB0 0023EAB0 2000BFDF */  ld         $31, 0x20($29)
.align 2
  .L0023EAB4:
    /* 13EAB4 0023EAB4 1000B1DF */  ld         $17, 0x10($29)
    /* 13EAB8 0023EAB8 0000B0DF */  ld         $16, 0x0($29)
    /* 13EABC 0023EABC 0800E003 */  jr         $31
    /* 13EAC0 0023EAC0 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_0023EA68
    /* 13EAC4 0023EAC4 00000000 */  nop
```
