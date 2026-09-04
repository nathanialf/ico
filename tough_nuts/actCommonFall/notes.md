# actCommonFall — parked

VRAM: 0x0015B628 (file_off 0x05B628)
Asm source: asm/aug6/nonmatchings/fumi/src/commonact/actCommonFall.s

## Attempt at 2026-06-17

**Reason parked:** rc3 logic-complete; sole residual = §5.7 far-global D_005530B8 addressing: ROM uses gas-macro $at form (lui $1,%hi; ld $5,%lo($1)) for a far 64-bit scalar; ee-gcc gp-rels it (R_MIPS_GPREL16 truncated) or array-alias gives explicit normal-reg %hi/%lo (rc3) + lui-hoist scheduling. ~15 addressing/scheduling constructs tried (gp_rel/scalar-alias/array-alias/sized-array/struct/char-alias/volatile/absolute-literal/const-ptr/inline/long-long-local). permuter-class; note already flagged 'alias overcorrects to 3'.

**TU:** `fumi/src/commonact.c`

**Seed:** `tough_nuts/actCommonFall/actCommonFall.c`

Disassembly:

```
.align 3
nonmatching actCommonFall, 0x98

glabel actCommonFall
    /* 5B628 0015B628 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 5B62C 0015B62C 1000B0FF */  sd         $16, 0x10($29)
    /* 5B630 0015B630 2D28A003 */  daddu      $5, $29, $0
    /* 5B634 0015B634 2000BFFF */  sd         $31, 0x20($29)
    /* 5B638 0015B638 2D808000 */  daddu      $16, $4, $0
    /* 5B63C 0015B63C 2D20A003 */  daddu      $4, $29, $0
    /* 5B640 0015B640 5C01028E */  lw         $2, 0x15C($16)
    /* 5B644 0015B644 C00140C4 */  lwc1       $f0, 0x1C0($2)
    /* 5B648 0015B648 0000A0E7 */  swc1       $f0, 0x0($29)
    /* 5B64C 0015B64C C40141C4 */  lwc1       $f1, 0x1C4($2)
    /* 5B650 0015B650 0400A1E7 */  swc1       $f1, 0x4($29)
    /* 5B654 0015B654 C80140C4 */  lwc1       $f0, 0x1C8($2)
    /* 5B658 0015B658 A6FF080C */  jal        sceVu0Normalize
    /* 5B65C 0015B65C 0800A0E7 */   swc1      $f0, 0x8($29)
    /* 5B660 0015B660 0000A0C7 */  lwc1       $f0, 0x0($29)
    /* 5B664 0015B664 0800ACC7 */  lwc1       $f12, 0x8($29)
    /* 5B668 0015B668 02000046 */  mul.s      $f0, $f0, $f0
    /* 5B66C 0015B66C 02630C46 */  mul.s      $f12, $f12, $f12
    /* 5B670 0015B670 7817040C */  jal        FSqrt
    /* 5B674 0015B674 00030C46 */   add.s     $f12, $f0, $f12
    /* 5B678 0015B678 D080090C */  jal        fptodp
    /* 5B67C 0015B67C 06030046 */   mov.s     $f12, $f0
    /* 5B680 0015B680 5500013C */  lui        $1, %hi(D_005530B8)
    /* 5B684 0015B684 B83025DC */  ld         $5, %lo(D_005530B8)($1)
    /* 5B688 0015B688 287D090C */  jal        dpcmp
    /* 5B68C 0015B68C 2D204000 */   daddu     $4, $2, $0
    /* 5B690 0015B690 07004018 */  blez       $2, .L0015B6B0
    /* 5B694 0015B694 2D20A003 */   daddu     $4, $29, $0
    /* 5B698 0015B698 0400A0AF */  sw         $0, 0x4($29)
    /* 5B69C 0015B69C A6FF080C */  jal        sceVu0Normalize
    /* 5B6A0 0015B6A0 2D28A003 */   daddu     $5, $29, $0
    /* 5B6A4 0015B6A4 2D200002 */  daddu      $4, $16, $0
    /* 5B6A8 0015B6A8 2E1A040C */  jal        dispPlane
    /* 5B6AC 0015B6AC 2D28A003 */   daddu     $5, $29, $0
.align 2
  .L0015B6B0:
    /* 5B6B0 0015B6B0 2000BFDF */  ld         $31, 0x20($29)
    /* 5B6B4 0015B6B4 1000B0DF */  ld         $16, 0x10($29)
    /* 5B6B8 0015B6B8 0800E003 */  jr         $31
    /* 5B6BC 0015B6BC 3000BD27 */   addiu     $29, $29, 0x30
endlabel actCommonFall
```
