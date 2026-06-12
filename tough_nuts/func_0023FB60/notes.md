# func_0023FB60 — parked

VRAM: 0x0023FB60 (file_off 0x13FB60)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0023FB60.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (near-miss); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0023FB60/func_0023FB60.c`

Disassembly:

```
.align 3
nonmatching func_0023FB60, 0x88

glabel func_0023FB60
    /* 13FB60 0023FB60 300082DC */  ld         $2, 0x30($4)
    /* 13FB64 0023FB64 002C0500 */  sll        $5, $5, 16
    /* 13FB68 0023FB68 00340600 */  sll        $6, $6, 16
    /* 13FB6C 0023FB6C 032C0500 */  sra        $5, $5, 16
    /* 13FB70 0023FB70 3A1C0200 */  dsrl       $3, $2, 16
    /* 13FB74 0023FB74 03340600 */  sra        $6, $6, 16
    /* 13FB78 0023FB78 3E140200 */  dsrl32     $2, $2, 16
    /* 13FB7C 0023FB7C FF076330 */  andi       $3, $3, 0x7FF
    /* 13FB80 0023FB80 FF074230 */  andi       $2, $2, 0x7FF
    /* 13FB84 0023FB84 3C180300 */  dsll32     $3, $3, 0
    /* 13FB88 0023FB88 3F180300 */  dsra32     $3, $3, 0
    /* 13FB8C 0023FB8C 3C100200 */  dsll32     $2, $2, 0
    /* 13FB90 0023FB90 3F100200 */  dsra32     $2, $2, 0
    /* 13FB94 0023FB94 3C340600 */  dsll32     $6, $6, 16
    /* 13FB98 0023FB98 01004224 */  addiu      $2, $2, 0x1
    /* 13FB9C 0023FB9C 3C2C0500 */  dsll32     $5, $5, 16
    /* 13FBA0 0023FBA0 01006324 */  addiu      $3, $3, 0x1
    /* 13FBA4 0023FBA4 7A100200 */  dsrl       $2, $2, 1
    /* 13FBA8 0023FBA8 3F340600 */  dsra32     $6, $6, 16
    /* 13FBAC 0023FBAC 3F2C0500 */  dsra32     $5, $5, 16
    /* 13FBB0 0023FBB0 7A180300 */  dsrl       $3, $3, 1
    /* 13FBB4 0023FBB4 2F30C200 */  dsubu      $6, $6, $2
    /* 13FBB8 0023FBB8 2F28A300 */  dsubu      $5, $5, $3
    /* 13FBBC 0023FBBC 38110600 */  dsll       $2, $6, 4
    /* 13FBC0 0023FBC0 003C0700 */  sll        $7, $7, 16
    /* 13FBC4 0023FBC4 0400E010 */  beqz       $7, .L0023FBD8
    /* 13FBC8 0023FBC8 38290500 */   dsll      $5, $5, 4
    /* 13FBCC 0023FBCC 08004264 */  daddiu     $2, $2, 0x8
    /* 13FBD0 0023FBD0 02000010 */  b          .L0023FBDC
    /* 13FBD4 0023FBD4 3C100200 */   dsll32    $2, $2, 0
.align 2
  .L0023FBD8:
    /* 13FBD8 0023FBD8 3C110600 */  dsll32     $2, $6, 4
.align 2
  .L0023FBDC:
    /* 13FBDC 0023FBDC 2510A200 */  or         $2, $5, $2
    /* 13FBE0 0023FBE0 0800E003 */  jr         $31
    /* 13FBE4 0023FBE4 200082FC */   sd        $2, 0x20($4)
endlabel func_0023FB60
```
