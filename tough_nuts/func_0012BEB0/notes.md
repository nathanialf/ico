# func_0012BEB0 — parked

VRAM: 0x0012BEB0 (file_off 0x02BEB0)
Asm source: asm/nonmatchings/src/Texture/func_0012BEB0.s

## Attempt at 2026-05-22

**Reason parked:** iter 30: 169 byte diffs out of 105 instrs. Function structure approximated but gcc's scheduling differs significantly from target. Tried: REG pins on a0/a1 to t2/t3, MATERIALIZE vs KEEP_LIVE barriers, source reordering (lbu before/after table load), inline _12 reads, -fno-schedule-insns and -fno-schedule-insns2 (no effect on 2.9), goto-based assert, __builtin_expect, return-after-break. Key blockers: (1) target uses beqzl + 'break 0,7' in annulled delay slot, gcc emits bnezl + li_8 in delay + break sequentially; (2) target saves a1 to t3 LATER than build (between table compute and lbu); (3) loop body access ordering doesn't match. The 59-entry pixel-format jtbl itself emits correctly with the postprocess_split_jtbls.py infra unlock, but the surrounding body is gcc-scheduling-dominated.

**TU:** `src/Texture.c`

**Seed:** `tough_nuts/func_0012BEB0/func_0012BEB0.c`

Disassembly:

```
.align 3
nonmatching func_0012BEB0, 0x1A0

glabel func_0012BEB0
    /* 2BEB0 0012BEB0 2D508000 */  daddu      $10, $4, $0
    /* 2BEB4 0012BEB4 0C000724 */  addiu      $7, $0, 0xC
    /* 2BEB8 0012BEB8 12004491 */  lbu        $4, 0x12($10)
    /* 2BEBC 0012BEBC 27000C3C */  lui        $12, %hi(D_00276268)
    /* 2BEC0 0012BEC0 68628625 */  addiu      $6, $12, %lo(D_00276268)
    /* 2BEC4 0012BEC4 2D58A000 */  daddu      $11, $5, $0
    /* 2BEC8 0012BEC8 3F008430 */  andi       $4, $4, 0x3F
    /* 2BECC 0012BECC 18208700 */  mult       $4, $4, $7
    /* 2BED0 0012BED0 2128C400 */  addu       $5, $6, $4
    /* 2BED4 0012BED4 0400A28C */  lw         $2, 0x4($5)
    /* 2BED8 0012BED8 01004050 */  beql       $2, $0, .L0012BEE0
    /* 2BEDC 0012BEDC CD010000 */   break     0, 7
.align 2
  .L0012BEE0:
    /* 2BEE0 0012BEE0 08000224 */  addiu      $2, $0, 0x8
    /* 2BEE4 0012BEE4 EA0062A5 */  sh         $2, 0xEA($11)
    /* 2BEE8 0012BEE8 12004291 */  lbu        $2, 0x12($10)
    /* 2BEEC 0012BEEC 3F004230 */  andi       $2, $2, 0x3F
    /* 2BEF0 0012BEF0 18184700 */  mult       $3, $2, $7
    /* 2BEF4 0012BEF4 21106600 */  addu       $2, $3, $6
    /* 2BEF8 0012BEF8 0000448C */  lw         $4, 0x0($2)
    /* 2BEFC 0012BEFC 3B00832C */  sltiu      $3, $4, 0x3B
    /* 2BF00 0012BF00 10006010 */  beqz       $3, .L0012BF44
    /* 2BF04 0012BF04 14004595 */   lhu       $5, 0x14($10)
    /* 2BF08 0012BF08 5500023C */  lui        $2, %hi(jtbl_005560D0)
    /* 2BF0C 0012BF0C 80180400 */  sll        $3, $4, 2
    /* 2BF10 0012BF10 D0604224 */  addiu      $2, $2, %lo(jtbl_005560D0)
    /* 2BF14 0012BF14 21186200 */  addu       $3, $3, $2
    /* 2BF18 0012BF18 0000648C */  lw         $4, 0x0($3)
    /* 2BF1C 0012BF1C 08008000 */  jr         $4
    /* 2BF20 0012BF20 00000000 */   nop
.align 2
  jlabel .L0012BF24
    /* 2BF24 0012BF24 3F00A224 */  addiu      $2, $5, 0x3F
    /* 2BF28 0012BF28 07000010 */  b          .L0012BF48
    /* 2BF2C 0012BF2C 83190200 */   sra       $3, $2, 6
.align 2
  jlabel .L0012BF30
    /* 2BF30 0012BF30 3F00A224 */  addiu      $2, $5, 0x3F
    /* 2BF34 0012BF34 83110200 */  sra        $2, $2, 6
    /* 2BF38 0012BF38 01004330 */  andi       $3, $2, 0x1
    /* 2BF3C 0012BF3C 02000010 */  b          .L0012BF48
    /* 2BF40 0012BF40 21184300 */   addu      $3, $2, $3
.align 2
  jlabel .L0012BF44
    /* 2BF44 0012BF44 2D180000 */  daddu      $3, $0, $0
.align 2
  .L0012BF48:
    /* 2BF48 0012BF48 E0006295 */  lhu        $2, 0xE0($11)
    /* 2BF4C 0012BF4C 2D480000 */  daddu      $9, $0, $0
    /* 2BF50 0012BF50 3D004010 */  beqz       $2, .L0012C048
    /* 2BF54 0012BF54 E80063A5 */   sh        $3, 0xE8($11)
    /* 2BF58 0012BF58 13004591 */  lbu        $5, 0x13($10)
    /* 2BF5C 0012BF5C 00000000 */  nop
.align 2
  .L0012BF60:
    /* 2BF60 0012BF60 24000624 */  addiu      $6, $0, 0x24
    /* 2BF64 0012BF64 18202601 */  mult       $4, $9, $6
    /* 2BF68 0012BF68 0C000824 */  addiu      $8, $0, 0xC
    /* 2BF6C 0012BF6C 1828A800 */  mult       $5, $5, $8
    /* 2BF70 0012BF70 14004395 */  lhu        $3, 0x14($10)
    /* 2BF74 0012BF74 16004295 */  lhu        $2, 0x16($10)
    /* 2BF78 0012BF78 68628725 */  addiu      $7, $12, %lo(D_00276268)
    /* 2BF7C 0012BF7C 07182301 */  srav       $3, $3, $9
    /* 2BF80 0012BF80 07102201 */  srav       $2, $2, $9
    /* 2BF84 0012BF84 21308B00 */  addu       $6, $4, $11
    /* 2BF88 0012BF88 18186200 */  mult       $3, $3, $2
    /* 2BF8C 0012BF8C 2120E500 */  addu       $4, $7, $5
    /* 2BF90 0012BF90 0400828C */  lw         $2, 0x4($4)
    /* 2BF94 0012BF94 2D288000 */  daddu      $5, $4, $0
    /* 2BF98 0012BF98 01004050 */  beql       $2, $0, .L0012BFA0
    /* 2BF9C 0012BF9C CD010000 */   break     0, 7
.align 2
  .L0012BFA0:
    /* 2BFA0 0012BFA0 1A006200 */  div        $0, $3, $2
    /* 2BFA4 0012BFA4 0800A48C */  lw         $4, 0x8($5)
    /* 2BFA8 0012BFA8 12180000 */  mflo       $3
    /* 2BFAC 0012BFAC C2170300 */  srl        $2, $3, 31
    /* 2BFB0 0012BFB0 21186200 */  addu       $3, $3, $2
    /* 2BFB4 0012BFB4 43180300 */  sra        $3, $3, 1
    /* 2BFB8 0012BFB8 18186400 */  mult       $3, $3, $4
    /* 2BFBC 0012BFBC 83190300 */  sra        $3, $3, 6
    /* 2BFC0 0012BFC0 0E01C3A4 */  sh         $3, 0x10E($6)
    /* 2BFC4 0012BFC4 13004491 */  lbu        $4, 0x13($10)
    /* 2BFC8 0012BFC8 14004295 */  lhu        $2, 0x14($10)
    /* 2BFCC 0012BFCC 18188800 */  mult       $3, $4, $8
    /* 2BFD0 0012BFD0 07282201 */  srav       $5, $2, $9
    /* 2BFD4 0012BFD4 21206700 */  addu       $4, $3, $7
    /* 2BFD8 0012BFD8 0000838C */  lw         $3, 0x0($4)
    /* 2BFDC 0012BFDC 3B00622C */  sltiu      $2, $3, 0x3B
    /* 2BFE0 0012BFE0 0F004010 */  beqz       $2, .L0012C020
    /* 2BFE4 0012BFE4 5500023C */   lui       $2, %hi(jtbl_005561C0)
    /* 2BFE8 0012BFE8 80180300 */  sll        $3, $3, 2
    /* 2BFEC 0012BFEC C0614224 */  addiu      $2, $2, %lo(jtbl_005561C0)
    /* 2BFF0 0012BFF0 21186200 */  addu       $3, $3, $2
    /* 2BFF4 0012BFF4 0000648C */  lw         $4, 0x0($3)
    /* 2BFF8 0012BFF8 08008000 */  jr         $4
    /* 2BFFC 0012BFFC 00000000 */   nop
.align 2
  jlabel .L0012C000
    /* 2C000 0012C000 3F00A224 */  addiu      $2, $5, 0x3F
    /* 2C004 0012C004 07000010 */  b          .L0012C024
    /* 2C008 0012C008 83110200 */   sra       $2, $2, 6
.align 2
  jlabel .L0012C00C
    /* 2C00C 0012C00C 3F00A224 */  addiu      $2, $5, 0x3F
    /* 2C010 0012C010 83110200 */  sra        $2, $2, 6
    /* 2C014 0012C014 01004330 */  andi       $3, $2, 0x1
    /* 2C018 0012C018 02000010 */  b          .L0012C024
    /* 2C01C 0012C01C 21104300 */   addu      $2, $2, $3
.align 2
  jlabel .L0012C020
    /* 2C020 0012C020 2D100000 */  daddu      $2, $0, $0
.align 2
  .L0012C024:
    /* 2C024 0012C024 24000324 */  addiu      $3, $0, 0x24
    /* 2C028 0012C028 18202301 */  mult       $4, $9, $3
    /* 2C02C 0012C02C 01002925 */  addiu      $9, $9, 0x1
    /* 2C030 0012C030 21188B00 */  addu       $3, $4, $11
    /* 2C034 0012C034 0C0162A4 */  sh         $2, 0x10C($3)
    /* 2C038 0012C038 E0006295 */  lhu        $2, 0xE0($11)
    /* 2C03C 0012C03C 2A102201 */  slt        $2, $9, $2
    /* 2C040 0012C040 C7FF4054 */  bnel       $2, $0, .L0012BF60
    /* 2C044 0012C044 13004591 */   lbu       $5, 0x13($10)
.align 2
  .L0012C048:
    /* 2C048 0012C048 0800E003 */  jr         $31
    /* 2C04C 0012C04C 00000000 */   nop
endlabel func_0012BEB0
```
