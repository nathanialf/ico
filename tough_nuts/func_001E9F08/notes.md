# func_001E9F08 — parked

VRAM: 0x001E9F08 (file_off 0x0E9F08)
Asm source: asm/nonmatchings/src/rotObject/func_001E9F08.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/rotObject.c`

**Seed:** `tough_nuts/func_001E9F08/func_001E9F08.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00632010, 1
.extern D_006335C8, 1

.align 3
nonmatching func_001E9F08, 0x128

glabel func_001E9F08
    /* E9F08 001E9F08 B0FFBD27 */  addiu      $29, $29, -0x50
    /* E9F0C 001E9F0C 6200063C */  lui        $6, %hi(D_00619FC8)
    /* E9F10 001E9F10 2000B2FF */  sd         $18, 0x20($29)
    /* E9F14 001E9F14 C89FC624 */  addiu      $6, $6, %lo(D_00619FC8)
    /* E9F18 001E9F18 1000B1FF */  sd         $17, 0x10($29)
    /* E9F1C 001E9F1C 2D908000 */  daddu      $18, $4, $0
    /* E9F20 001E9F20 2D88A000 */  daddu      $17, $5, $0
    /* E9F24 001E9F24 2097848F */  lw         $4, (D_00632010) /* gp_rel: (D_00632010) */
    /* E9F28 001E9F28 0000B0FF */  sd         $16, 0x0($29)
    /* E9F2C 001E9F2C 40000524 */  addiu      $5, $0, 0x40
    /* E9F30 001E9F30 4000B4E7 */  swc1       $f20, 0x40($29)
    /* E9F34 001E9F34 3000BFFF */  sd         $31, 0x30($29)
    /* E9F38 001E9F38 3EE8040C */  jal        func_0013A0F8
    /* E9F3C 001E9F3C 37000724 */   addiu     $7, $0, 0x37
    /* E9F40 001E9F40 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* E9F44 001E9F44 00A08144 */  mtc1       $1, $f20
    /* E9F48 001E9F48 2D804000 */  daddu      $16, $2, $0
    /* E9F4C 001E9F4C 1E000624 */  addiu      $6, $0, 0x1E
    /* E9F50 001E9F50 D8AC8293 */  lbu        $2, (D_006335C8) /* gp_rel: (D_006335C8) */
    /* E9F54 001E9F54 10000426 */  addiu      $4, $16, 0x10
    /* E9F58 001E9F58 2D282002 */  daddu      $5, $17, $0
    /* E9F5C 001E9F5C 300002AE */  sw         $2, 0x30($16)
    /* E9F60 001E9F60 0100C050 */  beql       $6, $0, .L001E9F68
    /* E9F64 001E9F64 CD010000 */   break     0, 7
.align 2
  .L001E9F68:
    /* E9F68 001E9F68 D8AC8293 */  lbu        $2, (D_006335C8) /* gp_rel: (D_006335C8) */
    /* E9F6C 001E9F6C 01004224 */  addiu      $2, $2, 0x1
    /* E9F70 001E9F70 1A004600 */  div        $0, $2, $6
    /* E9F74 001E9F74 10180000 */  mfhi       $3
    /* E9F78 001E9F78 C017040C */  jal        func_00105F00
    /* E9F7C 001E9F7C D8AC83A3 */   sb        $3, (D_006335C8) /* gp_rel: (D_006335C8) */
    /* E9F80 001E9F80 1C0014E6 */  swc1       $f20, 0x1C($16)
    /* E9F84 001E9F84 03000424 */  addiu      $4, $0, 0x3
    /* E9F88 001E9F88 0047013C */  lui        $1, (0x47000000 >> 16)
    /* E9F8C 001E9F8C 00088144 */  mtc1       $1, $f1
    /* E9F90 001E9F90 140020C6 */  lwc1       $f0, 0x14($17)
    /* E9F94 001E9F94 3443013C */  lui        $1, (0x43340000 >> 16)
    /* E9F98 001E9F98 00108144 */  mtc1       $1, $f2
    /* E9F9C 001E9F9C 02000146 */  mul.s      $f0, $f0, $f1
    /* E9FA0 001E9FA0 3000238E */  lw         $3, 0x30($17)
    /* E9FA4 001E9FA4 00088044 */  mtc1       $0, $f1
    /* E9FA8 001E9FA8 000003AE */  sw         $3, 0x0($16)
    /* E9FAC 001E9FAC 00000000 */  nop
    /* E9FB0 001E9FB0 00000000 */  nop
    /* E9FB4 001E9FB4 03000246 */  div.s      $f0, $f0, $f2
    /* E9FB8 001E9FB8 280001E6 */  swc1       $f1, 0x28($16)
    /* E9FBC 001E9FBC 2C0001E6 */  swc1       $f1, 0x2C($16)
    /* E9FC0 001E9FC0 240000AE */  sw         $0, 0x24($16)
    /* E9FC4 001E9FC4 340000AE */  sw         $0, 0x34($16)
    /* E9FC8 001E9FC8 64000046 */  .word      0x46000064                    # cvt.w.s    $f1, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* E9FCC 001E9FCC 00080244 */  mfc1       $2, $f1
    /* E9FD0 001E9FD0 0A006414 */  bne        $3, $4, .L001E9FFC
    /* E9FD4 001E9FD4 200002A6 */   sh        $2, 0x20($16)
    /* E9FD8 001E9FD8 280021C6 */  lwc1       $f1, 0x28($17)
    /* E9FDC 001E9FDC 2700053C */  lui        $5, %hi(D_00275860)
    /* E9FE0 001E9FE0 6058A524 */  addiu      $5, $5, %lo(D_00275860)
    /* E9FE4 001E9FE4 280001E6 */  swc1       $f1, 0x28($16)
    /* E9FE8 001E9FE8 200020C6 */  lwc1       $f0, 0x20($17)
    /* E9FEC 001E9FEC 2C0000E6 */  swc1       $f0, 0x2C($16)
    /* E9FF0 001E9FF0 5C01448E */  lw         $4, 0x15C($18)
    /* E9FF4 001E9FF4 C017040C */  jal        func_00105F00
    /* E9FF8 001E9FF8 A0008424 */   addiu     $4, $4, 0xA0
.align 2
  .L001E9FFC:
    /* E9FFC 001E9FFC 5C01448E */  lw         $4, 0x15C($18)
    /* EA000 001EA000 2D100002 */  daddu      $2, $16, $0
    /* EA004 001EA004 3000BFDF */  ld         $31, 0x30($29)
    /* EA008 001EA008 4008838C */  lw         $3, 0x840($4)
    /* EA00C 001EA00C 2000B2DF */  ld         $18, 0x20($29)
    /* EA010 001EA010 200074E4 */  swc1       $f20, 0x20($3)
    /* EA014 001EA014 280074E4 */  swc1       $f20, 0x28($3)
    /* EA018 001EA018 240074E4 */  swc1       $f20, 0x24($3)
    /* EA01C 001EA01C 1000B1DF */  ld         $17, 0x10($29)
    /* EA020 001EA020 0000B0DF */  ld         $16, 0x0($29)
    /* EA024 001EA024 4000B4C7 */  lwc1       $f20, 0x40($29)
    /* EA028 001EA028 0800E003 */  jr         $31
    /* EA02C 001EA02C 5000BD27 */   addiu     $29, $29, 0x50
endlabel func_001E9F08
```
