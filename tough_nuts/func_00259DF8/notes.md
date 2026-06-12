# func_00259DF8 — parked

VRAM: 0x00259DF8 (file_off 0x159DF8)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_00259DF8.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_00259DF8/func_00259DF8.c`

Disassembly:

```
.align 3
nonmatching func_00259DF8, 0x70

glabel func_00259DF8
    /* 159DF8 00259DF8 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 159DFC 00259DFC 3000822C */  sltiu      $2, $4, 0x30
    /* 159E00 00259E00 0000B0FF */  sd         $16, 0x0($29)
    /* 159E04 00259E04 1000BFFF */  sd         $31, 0x10($29)
    /* 159E08 00259E08 13004010 */  beqz       $2, .L00259E58
    /* 159E0C 00259E0C 2D80A000 */   daddu     $16, $5, $0
    /* 159E10 00259E10 11000006 */  bltz       $16, .L00259E58
    /* 159E14 00259E14 0040022A */   slti      $2, $16, 0x4000
    /* 159E18 00259E18 10004010 */  beqz       $2, .L00259E5C
    /* 159E1C 00259E1C 1000BFDF */   ld        $31, 0x10($29)
    /* 159E20 00259E20 F853090C */  jal        func_00254FE0
    /* 159E24 00259E24 00000000 */   nop
    /* 159E28 00259E28 0000448C */  lw         $4, 0x0($2)
    /* 159E2C 00259E2C FFFF053C */  lui        $5, (0xFFFFDFFF >> 16)
    /* 159E30 00259E30 FFDFA534 */  ori        $5, $5, (0xFFFFDFFF & 0xFFFF)
    /* 159E34 00259E34 400050AC */  sw         $16, 0x40($2)
    /* 159E38 00259E38 00208434 */  ori        $4, $4, 0x2000
    /* 159E3C 00259E3C 000044AC */  sw         $4, 0x0($2)
    /* 159E40 00259E40 0000438C */  lw         $3, 0x0($2)
    /* 159E44 00259E44 00046334 */  ori        $3, $3, 0x400
    /* 159E48 00259E48 000043AC */  sw         $3, 0x0($2)
    /* 159E4C 00259E4C 0000448C */  lw         $4, 0x0($2)
    /* 159E50 00259E50 24208500 */  and        $4, $4, $5
    /* 159E54 00259E54 000044AC */  sw         $4, 0x0($2)
.align 2
  .L00259E58:
    /* 159E58 00259E58 1000BFDF */  ld         $31, 0x10($29)
.align 2
  .L00259E5C:
    /* 159E5C 00259E5C 0000B0DF */  ld         $16, 0x0($29)
    /* 159E60 00259E60 0800E003 */  jr         $31
    /* 159E64 00259E64 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_00259DF8
```
