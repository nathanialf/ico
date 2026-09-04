# strstr — parked

VRAM: 0x00261B10 (file_off 0x161B10)
Asm source: asm/aug6/nonmatchings/common/src/PObj/strstr.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/strstr/strstr.c`

Disassembly:

```
.align 3
nonmatching strstr, 0x6C

glabel strstr
    /* 161B10 00261B10 00008280 */  lb         $2, 0x0($4)
    /* 161B14 00261B14 06004014 */  bnez       $2, .L00261B30
    /* 161B18 00261B18 0000A380 */   lb        $3, 0x0($5)
    /* 161B1C 00261B1C 2D100000 */  daddu      $2, $0, $0
    /* 161B20 00261B20 0800E003 */  jr         $31
    /* 161B24 00261B24 0A108300 */   movz      $2, $4, $3
.align 2
  .L00261B28:
    /* 161B28 00261B28 0800E003 */  jr         $31
    /* 161B2C 00261B2C 2D108000 */   daddu     $2, $4, $0
.align 2
  .L00261B30:
    /* 161B30 00261B30 FDFF6010 */  beqz       $3, .L00261B28
    /* 161B34 00261B34 2D380000 */   daddu     $7, $0, $0
    /* 161B38 00261B38 00008280 */  lb         $2, 0x0($4)
    /* 161B3C 00261B3C 0A006254 */  bnel       $3, $2, .L00261B68
    /* 161B40 00261B40 01008424 */   addiu     $4, $4, 0x1
    /* 161B44 00261B44 0100E724 */  addiu      $7, $7, 0x1
.align 2
  .L00261B48:
    /* 161B48 00261B48 2110A700 */  addu       $2, $5, $7
    /* 161B4C 00261B4C 00004680 */  lb         $6, 0x0($2)
    /* 161B50 00261B50 F5FFC010 */  beqz       $6, .L00261B28
    /* 161B54 00261B54 21108700 */   addu      $2, $4, $7
    /* 161B58 00261B58 00004380 */  lb         $3, 0x0($2)
    /* 161B5C 00261B5C FAFFC350 */  beql       $6, $3, .L00261B48
    /* 161B60 00261B60 0100E724 */   addiu     $7, $7, 0x1
    /* 161B64 00261B64 01008424 */  addiu      $4, $4, 0x1
.align 2
  .L00261B68:
    /* 161B68 00261B68 00008280 */  lb         $2, 0x0($4)
    /* 161B6C 00261B6C F0FF4054 */  bnel       $2, $0, .L00261B30
    /* 161B70 00261B70 0000A380 */   lb        $3, 0x0($5)
    /* 161B74 00261B74 0800E003 */  jr         $31
    /* 161B78 00261B78 2D100000 */   daddu     $2, $0, $0
endlabel strstr
    /* 161B7C 00261B7C 00000000 */  nop
```
