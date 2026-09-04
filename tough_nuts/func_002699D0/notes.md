# __sseek — parked

VRAM: 0x002699D0 (file_off 0x1699D0)
Asm source: asm/aug6/nonmatchings/common/src/PObj/__sseek.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (near-miss); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/__sseek/__sseek.c`

Disassembly:

```
.align 3
nonmatching __sseek, 0x68

glabel __sseek
    /* 1699D0 002699D0 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 1699D4 002699D4 2D10A000 */  daddu      $2, $5, $0
    /* 1699D8 002699D8 0000B0FF */  sd         $16, 0x0($29)
    /* 1699DC 002699DC 2D38C000 */  daddu      $7, $6, $0
    /* 1699E0 002699E0 1000BFFF */  sd         $31, 0x10($29)
    /* 1699E4 002699E4 2D808000 */  daddu      $16, $4, $0
    /* 1699E8 002699E8 2D304000 */  daddu      $6, $2, $0
    /* 1699EC 002699EC 5400048E */  lw         $4, 0x54($16)
    /* 1699F0 002699F0 16AC090C */  jal        func_0026B058
    /* 1699F4 002699F4 0E000586 */   lh        $5, 0xE($16)
    /* 1699F8 002699F8 2D204000 */  daddu      $4, $2, $0
    /* 1699FC 002699FC FFFF0224 */  addiu      $2, $0, -0x1
    /* 169A00 00269A00 03008214 */  bne        $4, $2, .L00269A10
    /* 169A04 00269A04 0C000296 */   lhu       $2, 0xC($16)
    /* 169A08 00269A08 05000010 */  b          .L00269A20
    /* 169A0C 00269A0C FFEF4230 */   andi      $2, $2, 0xEFFF
.align 2
  .L00269A10:
    /* 169A10 00269A10 3C180400 */  dsll32     $3, $4, 0
    /* 169A14 00269A14 3F180300 */  dsra32     $3, $3, 0
    /* 169A18 00269A18 500003AE */  sw         $3, 0x50($16)
    /* 169A1C 00269A1C 00104234 */  ori        $2, $2, 0x1000
.align 2
  .L00269A20:
    /* 169A20 00269A20 0C0002A6 */  sh         $2, 0xC($16)
    /* 169A24 00269A24 1000BFDF */  ld         $31, 0x10($29)
    /* 169A28 00269A28 2D108000 */  daddu      $2, $4, $0
    /* 169A2C 00269A2C 0000B0DF */  ld         $16, 0x0($29)
    /* 169A30 00269A30 0800E003 */  jr         $31
    /* 169A34 00269A34 2000BD27 */   addiu     $29, $29, 0x20
endlabel __sseek
```
