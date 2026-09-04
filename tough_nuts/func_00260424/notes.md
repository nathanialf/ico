# memcmp — parked

VRAM: 0x00260424 (file_off 0x160424)
Asm source: asm/aug6/nonmatchings/common/src/PObj/memcmp.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/memcmp/memcmp.c`

Disassembly:

```
nonmatching memcmp, 0x94

glabel memcmp
    /* 160424 00260424 1000C22C */  sltiu      $2, $6, 0x10
    /* 160428 00260428 11004014 */  bnez       $2, .L00260470
    /* 16042C 0026042C 25108500 */   or        $2, $4, $5
    /* 160430 00260430 0F004230 */  andi       $2, $2, 0xF
    /* 160434 00260434 0E004014 */  bnez       $2, .L00260470
    /* 160438 00260438 00000000 */   nop
.align 2
  .L0026043C:
    /* 16043C 0026043C 00008378 */  lq         $3, 0x0($4)
    /* 160440 00260440 2000C72C */  sltiu      $7, $6, 0x20
    /* 160444 00260444 0000A278 */  lq         $2, 0x0($5)
    /* 160448 00260448 10008424 */  addiu      $4, $4, 0x10
    /* 16044C 0026044C C9444370 */  pxor       $8, $2, $3
    /* 160450 00260450 1000A224 */  addiu      $2, $5, 0x10
    /* 160454 00260454 A9530771 */  pcpyud     $10, $8, $7
    /* 160458 00260458 25484801 */  or         $9, $10, $8
    /* 16045C 0026045C 0A284900 */  movz       $5, $2, $9
    /* 160460 00260460 03002055 */  bnel       $9, $0, .L00260470
    /* 160464 00260464 F0FF8424 */   addiu     $4, $4, -0x10
    /* 160468 00260468 F4FFE010 */  beqz       $7, .L0026043C
    /* 16046C 0026046C F0FFC624 */   addiu     $6, $6, -0x10
.align 2
  .L00260470:
    /* 160470 00260470 FFFF023C */  lui        $2, (0xFFFFFFFF >> 16)
    /* 160474 00260474 FFFFC624 */  addiu      $6, $6, -0x1
    /* 160478 00260478 FFFF4234 */  ori        $2, $2, (0xFFFFFFFF & 0xFFFF)
    /* 16047C 0026047C 0C00C210 */  beq        $6, $2, .L002604B0
    /* 160480 00260480 00000000 */   nop
    /* 160484 00260484 FFFF073C */  lui        $7, (0xFFFFFFFF >> 16)
    /* 160488 00260488 FFFFE734 */  ori        $7, $7, (0xFFFFFFFF & 0xFFFF)
.align 2
  .L0026048C:
    /* 16048C 0026048C 00008390 */  lbu        $3, 0x0($4)
    /* 160490 00260490 0000A290 */  lbu        $2, 0x0($5)
    /* 160494 00260494 03006210 */  beq        $3, $2, .L002604A4
    /* 160498 00260498 01008424 */   addiu     $4, $4, 0x1
    /* 16049C 0026049C 0800E003 */  jr         $31
    /* 1604A0 002604A0 23106200 */   subu      $2, $3, $2
.align 2
  .L002604A4:
    /* 1604A4 002604A4 FFFFC624 */  addiu      $6, $6, -0x1
    /* 1604A8 002604A8 F8FFC714 */  bne        $6, $7, .L0026048C
    /* 1604AC 002604AC 0100A524 */   addiu     $5, $5, 0x1
.align 2
  .L002604B0:
    /* 1604B0 002604B0 0800E003 */  jr         $31
    /* 1604B4 002604B4 2D100000 */   daddu     $2, $0, $0
endlabel memcmp
```
