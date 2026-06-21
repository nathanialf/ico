# BoyBgaManager — parked

VRAM: 0x0014CD00 (file_off 0x04CD00)
Asm source: asm/aug6/nonmatchings/fumi/src/boyact/BoyBgaManager.s

## Attempt at 2026-06-21

**Reason parked:** override=permute

**TU:** `fumi/src/boyact.c`

**Seed:** `tough_nuts/BoyBgaManager/BoyBgaManager.c`

Disassembly:

```
.align 3
nonmatching BoyBgaManager, 0x120

glabel BoyBgaManager
    /* 4CD00 0014CD00 B0FFBD27 */  addiu      $29, $29, -0x50
    /* 4CD04 0014CD04 2800073C */  lui        $7, %hi(D_0027DF90)
    /* 4CD08 0014CD08 3000B2FF */  sd         $18, 0x30($29)
    /* 4CD0C 0014CD0C 2D90C000 */  daddu      $18, $6, $0
    /* 4CD10 0014CD10 90DFE28C */  lw         $2, %lo(D_0027DF90)($7)
    /* 4CD14 0014CD14 4000BFFF */  sd         $31, 0x40($29)
    /* 4CD18 0014CD18 2D300000 */  daddu      $6, $0, $0
    /* 4CD1C 0014CD1C 2000B1FF */  sd         $17, 0x20($29)
    /* 4CD20 0014CD20 1000B0FF */  sd         $16, 0x10($29)
    /* 4CD24 0014CD24 0E004004 */  bltz       $2, .L0014CD60
    /* 4CD28 0014CD28 0000A4AF */   sw        $4, 0x0($29)
    /* 4CD2C 0014CD2C 2D200000 */  daddu      $4, $0, $0
    /* 4CD30 0014CD30 90DFE324 */  addiu      $3, $7, %lo(D_0027DF90)
    /* 4CD34 0014CD34 00000000 */  nop
.align 2
  .L0014CD38:
    /* 4CD38 0014CD38 21208300 */  addu       $4, $4, $3
    /* 4CD3C 0014CD3C 0000828C */  lw         $2, 0x0($4)
    /* 4CD40 0014CD40 1C004510 */  beq        $2, $5, .L0014CDB4
    /* 4CD44 0014CD44 0100C624 */   addiu     $6, $6, 0x1
    /* 4CD48 0014CD48 80110600 */  sll        $2, $6, 6
    /* 4CD4C 0014CD4C 2D204000 */  daddu      $4, $2, $0
    /* 4CD50 0014CD50 21188300 */  addu       $3, $4, $3
    /* 4CD54 0014CD54 0000628C */  lw         $2, 0x0($3)
    /* 4CD58 0014CD58 F7FF4104 */  bgez       $2, .L0014CD38
    /* 4CD5C 0014CD5C 90DFE324 */   addiu     $3, $7, %lo(D_0027DF90)
.align 2
  .L0014CD60:
    /* 4CD60 0014CD60 5500103C */  lui        $16, %hi(D_005525C8)
    /* 4CD64 0014CD64 D5050524 */  addiu      $5, $0, 0x5D5
    /* 4CD68 0014CD68 C8251026 */  addiu      $16, $16, %lo(D_005525C8)
    /* 4CD6C 0014CD6C 2D880000 */  daddu      $17, $0, $0
    /* 4CD70 0014CD70 40AB060C */  jal        func_001AAD00
    /* 4CD74 0014CD74 2D200002 */   daddu     $4, $16, $0
    /* 4CD78 0014CD78 6300063C */  lui        $6, %hi(D_0062C3F8)
    /* 4CD7C 0014CD7C 2D200002 */  daddu      $4, $16, $0
    /* 4CD80 0014CD80 F8C3C624 */  addiu      $6, $6, %lo(D_0062C3F8)
    /* 4CD84 0014CD84 E080090C */  jal        func_00260380
    /* 4CD88 0014CD88 D5050524 */   addiu     $5, $0, 0x5D5
.align 2
  .L0014CD8C:
    /* 4CD8C 0014CD8C 0000438E */  lw         $3, 0x0($18)
    /* 4CD90 0014CD90 1E006004 */  bltz       $3, .L0014CE0C
    /* 4CD94 0014CD94 4000BFDF */   ld        $31, 0x40($29)
    /* 4CD98 0014CD98 0C002292 */  lbu        $2, 0xC($17)
    /* 4CD9C 0014CD9C 07004010 */  beqz       $2, .L0014CDBC
    /* 4CDA0 0014CDA0 2D10A003 */   daddu     $2, $29, $0
    /* 4CDA4 0014CDA4 E832050C */  jal        UpdateGeo
    /* 4CDA8 0014CDA8 2D202002 */   daddu     $4, $17, $0
    /* 4CDAC 0014CDAC 08000010 */  b          .L0014CDD0
    /* 4CDB0 0014CDB0 0000438E */   lw        $3, 0x0($18)
.align 2
  .L0014CDB4:
    /* 4CDB4 0014CDB4 F5FF0010 */  b          .L0014CD8C
    /* 4CDB8 0014CDB8 2D888000 */   daddu     $17, $4, $0
.align 2
  .L0014CDBC:
    /* 4CDBC 0014CDBC 04006014 */  bnez       $3, .L0014CDD0
    /* 4CDC0 0014CDC0 00000000 */   nop
    /* 4CDC4 0014CDC4 E832050C */  jal        UpdateGeo
    /* 4CDC8 0014CDC8 2D202002 */   daddu     $4, $17, $0
    /* 4CDCC 0014CDCC 0000438E */  lw         $3, 0x0($18)
.align 2
  .L0014CDD0:
    /* 4CDD0 0014CDD0 00608344 */  mtc1       $3, $f12
    /* 4CDD4 0014CDD4 20638046 */  cvt.s.w    $f12, $f12
    /* 4CDD8 0014CDD8 0000248E */  lw         $4, 0x0($17)
    /* 4CDDC 0014CDDC 20002526 */  addiu      $5, $17, 0x20
    /* 4CDE0 0014CDE0 AEA7040C */  jal        stage_SetParentOfGObj
    /* 4CDE4 0014CDE4 30002626 */   addiu     $6, $17, 0x30
    /* 4CDE8 0014CDE8 64000046 */  .word      0x46000064                    # cvt.w.s    $f1, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* 4CDEC 0014CDEC 00080744 */  mfc1       $7, $f1
    /* 4CDF0 0014CDF0 0E002292 */  lbu        $2, 0xE($17)
    /* 4CDF4 0014CDF4 04004050 */  beql       $2, $0, .L0014CE08
    /* 4CDF8 0014CDF8 000047AE */   sw        $7, 0x0($18)
    /* 4CDFC 0014CDFC 0300E004 */  bltz       $7, .L0014CE0C
    /* 4CE00 0014CE00 4000BFDF */   ld        $31, 0x40($29)
    /* 4CE04 0014CE04 000047AE */  sw         $7, 0x0($18)
.align 2
  .L0014CE08:
    /* 4CE08 0014CE08 4000BFDF */  ld         $31, 0x40($29)
.align 2
  .L0014CE0C:
    /* 4CE0C 0014CE0C 3000B2DF */  ld         $18, 0x30($29)
    /* 4CE10 0014CE10 2000B1DF */  ld         $17, 0x20($29)
    /* 4CE14 0014CE14 1000B0DF */  ld         $16, 0x10($29)
    /* 4CE18 0014CE18 0800E003 */  jr         $31
    /* 4CE1C 0014CE1C 5000BD27 */   addiu     $29, $29, 0x50
endlabel BoyBgaManager
```
