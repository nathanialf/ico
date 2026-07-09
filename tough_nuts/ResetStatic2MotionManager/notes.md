# ResetStatic2MotionManager — parked

VRAM: 0x001D2D60 (file_off 0x0D2D60)
Asm source: asm/aug6/nonmatchings/sugipon/src/motionFileManager/ResetStatic2MotionManager.s

## Attempt at 2026-07-06

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=606). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `sugipon/src/motionFileManager.c`

**Seed:** `tough_nuts/ResetStatic2MotionManager/ResetStatic2MotionManager.c`

Disassembly:

```
.align 3
nonmatching ResetStatic2MotionManager, 0x2A10

glabel ResetStatic2MotionManager
    /* D2D60 001D2D60 70FDBD27 */  addiu      $29, $29, -0x290
    /* D2D64 001D2D64 6CAB858F */  lw         $5, %gp_rel(D_0062B75C)($28)
    /* D2D68 001D2D68 5002BEFF */  sd         $30, 0x250($29)
    /* D2D6C 001D2D6C 80390400 */  sll        $7, $4, 6
    /* D2D70 001D2D70 3002B6FF */  sd         $22, 0x230($29)
    /* D2D74 001D2D74 80180400 */  sll        $3, $4, 2
    /* D2D78 001D2D78 2002B5FF */  sd         $21, 0x220($29)
    /* D2D7C 001D2D7C 40210400 */  sll        $4, $4, 5
    /* D2D80 001D2D80 6002BFFF */  sd         $31, 0x260($29)
    /* D2D84 001D2D84 4002B7FF */  sd         $23, 0x240($29)
    /* D2D88 001D2D88 1002B4FF */  sd         $20, 0x210($29)
    /* D2D8C 001D2D8C 0002B3FF */  sd         $19, 0x200($29)
    /* D2D90 001D2D90 F001B2FF */  sd         $18, 0x1F0($29)
    /* D2D94 001D2D94 E001B1FF */  sd         $17, 0x1E0($29)
    /* D2D98 001D2D98 D001B0FF */  sd         $16, 0x1D0($29)
    /* D2D9C 001D2D9C 8002B6E7 */  swc1       $f22, 0x280($29)
    /* D2DA0 001D2DA0 7802B5E7 */  swc1       $f21, 0x278($29)
    /* D2DA4 001D2DA4 7002B4E7 */  swc1       $f20, 0x270($29)
    /* D2DA8 001D2DA8 68AB868F */  lw         $6, %gp_rel(D_0062B758)($28)
    /* D2DAC 001D2DAC 5C01A28C */  lw         $2, 0x15C($5)
    /* D2DB0 001D2DB0 21F0C700 */  addu       $30, $6, $7
    /* D2DB4 001D2DB4 28B6858F */  lw         $5, %gp_rel(D_0062C218)($28)
    /* D2DB8 001D2DB8 A0004224 */  addiu      $2, $2, 0xA0
    /* D2DBC 001D2DBC 3007468C */  lw         $6, 0x730($2)
    /* D2DC0 001D2DC0 21B0A400 */  addu       $22, $5, $4
    /* D2DC4 001D2DC4 2C07448C */  lw         $4, 0x72C($2)
    /* D2DC8 001D2DC8 FFFF0524 */  addiu      $5, $0, -0x1
    /* D2DCC 001D2DCC 21186600 */  addu       $3, $3, $6
    /* D2DD0 001D2DD0 3800C28F */  lw         $2, 0x38($30)
    /* D2DD4 001D2DD4 0000638C */  lw         $3, 0x0($3)
    /* D2DD8 001D2DD8 21A88700 */  addu       $21, $4, $7
    /* D2DDC 001D2DDC 0F004510 */  beq        $2, $5, .L001D2E1C
    /* D2DE0 001D2DE0 A001A3AF */   sw        $3, 0x1A0($29)
    /* D2DE4 001D2DE4 30AB8CC7 */  lwc1       $f12, %gp_rel(D_0062B720)($28)
    /* D2DE8 001D2DE8 1000A427 */  addiu      $4, $29, 0x10
    /* D2DEC 001D2DEC 5A02090C */  jal        func_00240968
    /* D2DF0 001D2DF0 1000C527 */   addiu     $5, $30, 0x10
    /* D2DF4 001D2DF4 1E14040C */  jal        func_00105078
    /* D2DF8 001D2DF8 00000000 */   nop
    /* D2DFC 001D2DFC 2414040C */  jal        func_00105090
    /* D2E00 001D2E00 30005024 */   addiu     $16, $2, 0x30
    /* D2E04 001D2E04 2D200002 */  daddu      $4, $16, $0
    /* D2E08 001D2E08 2D284000 */  daddu      $5, $2, $0
    /* D2E0C 001D2E0C 76FF080C */  jal        func_0023FDD8
    /* D2E10 001D2E10 1000A627 */   addiu     $6, $29, 0x10
    /* D2E14 001D2E14 06000010 */  b          .L001D2E30
    /* D2E18 001D2E18 0400C38F */   lw        $3, 0x4($30)
.align 2
  .L001D2E1C:
    /* D2E1C 001D2E1C 3AAB80A7 */  sh         $0, %gp_rel(D_0062B72A)($28)
    /* D2E20 001D2E20 38AB80A7 */  sh         $0, %gp_rel(D_0062B728)($28)
    /* D2E24 001D2E24 36AB80A7 */  sh         $0, %gp_rel(D_0062B726)($28)
    /* D2E28 001D2E28 34AB80A7 */  sh         $0, %gp_rel(D_0062B724)($28)
    /* D2E2C 001D2E2C 0400C38F */  lw         $3, 0x4($30)
.align 2
  .L001D2E30:
    /* D2E30 001D2E30 3400622C */  sltiu      $2, $3, 0x34
    /* D2E34 001D2E34 300A4010 */  beqz       $2, .L001D56F8
    /* D2E38 001D2E38 6100023C */   lui       $2, %hi(jtbl_00611A30)
    /* D2E3C 001D2E3C 80180300 */  sll        $3, $3, 2
    /* D2E40 001D2E40 301A4224 */  addiu      $2, $2, %lo(jtbl_00611A30)
    /* D2E44 001D2E44 21186200 */  addu       $3, $3, $2
    /* D2E48 001D2E48 0000648C */  lw         $4, 0x0($3)
    /* D2E4C 001D2E4C 08008000 */  jr         $4
    /* D2E50 001D2E50 00000000 */   nop
.align 2
  jlabel .L001D2E54
    /* D2E54 001D2E54 8C37040C */  jal        GetLastQuaternion
    /* D2E58 001D2E58 00000000 */   nop
    /* D2E5C 001D2E5C 9237040C */  jal        GetTableSin
    /* D2E60 001D2E60 2D804000 */   daddu     $16, $2, $0
    /* D2E64 001D2E64 2D200002 */  daddu      $4, $16, $0
    /* D2E68 001D2E68 2D284000 */  daddu      $5, $2, $0
    /* D2E6C 001D2E6C 5238040C */  jal        func_0010E148
    /* D2E70 001D2E70 1000C626 */   addiu     $6, $22, 0x10
    /* D2E74 001D2E74 8C37040C */  jal        GetLastQuaternion
    /* D2E78 001D2E78 4C00103C */   lui       $16, %hi(D_004C1C40)
    /* D2E7C 001D2E7C 2D884000 */  daddu      $17, $2, $0
    /* D2E80 001D2E80 8C37040C */  jal        GetLastQuaternion
    /* D2E84 001D2E84 401C1026 */   addiu     $16, $16, %lo(D_004C1C40)
    /* D2E88 001D2E88 2D280002 */  daddu      $5, $16, $0
    /* D2E8C 001D2E8C 2D202002 */  daddu      $4, $17, $0
    /* D2E90 001D2E90 0E0A0010 */  b          .L001D56CC
    /* D2E94 001D2E94 2D304000 */   daddu     $6, $2, $0
.align 2
  jlabel .L001D2E98
    /* D2E98 001D2E98 8C37040C */  jal        GetLastQuaternion
    /* D2E9C 001D2E9C 00000000 */   nop
    /* D2EA0 001D2EA0 9237040C */  jal        GetTableSin
    /* D2EA4 001D2EA4 2D804000 */   daddu     $16, $2, $0
    /* D2EA8 001D2EA8 2D200002 */  daddu      $4, $16, $0
    /* D2EAC 001D2EAC 2D284000 */  daddu      $5, $2, $0
    /* D2EB0 001D2EB0 5238040C */  jal        func_0010E148
    /* D2EB4 001D2EB4 1000C626 */   addiu     $6, $22, 0x10
    /* D2EB8 001D2EB8 8C37040C */  jal        GetLastQuaternion
    /* D2EBC 001D2EBC 00000000 */   nop
    /* D2EC0 001D2EC0 8C37040C */  jal        GetLastQuaternion
    /* D2EC4 001D2EC4 2D804000 */   daddu     $16, $2, $0
    /* D2EC8 001D2EC8 4C00063C */  lui        $6, %hi(D_004C1C30)
    /* D2ECC 001D2ECC 2D200002 */  daddu      $4, $16, $0
    /* D2ED0 001D2ED0 2D284000 */  daddu      $5, $2, $0
    /* D2ED4 001D2ED4 6238040C */  jal        func_0010E188
    /* D2ED8 001D2ED8 301CC624 */   addiu     $6, $6, %lo(D_004C1C30)
    /* D2EDC 001D2EDC FD090010 */  b          .L001D56D4
    /* D2EE0 001D2EE0 00000000 */   nop
.align 2
  jlabel .L001D2EE4
    /* D2EE4 001D2EE4 8C37040C */  jal        GetLastQuaternion
    /* D2EE8 001D2EE8 2000D127 */   addiu     $17, $30, 0x20
    /* D2EEC 001D2EEC 9237040C */  jal        GetTableSin
    /* D2EF0 001D2EF0 2D804000 */   daddu     $16, $2, $0
    /* D2EF4 001D2EF4 2D200002 */  daddu      $4, $16, $0
    /* D2EF8 001D2EF8 2D284000 */  daddu      $5, $2, $0
    /* D2EFC 001D2EFC 5238040C */  jal        func_0010E148
    /* D2F00 001D2F00 2D302002 */   daddu     $6, $17, $0
    /* D2F04 001D2F04 1E14040C */  jal        func_00105078
    /* D2F08 001D2F08 00000000 */   nop
    /* D2F0C 001D2F0C 8C37040C */  jal        GetLastQuaternion
    /* D2F10 001D2F10 2D804000 */   daddu     $16, $2, $0
    /* D2F14 001D2F14 2D200002 */  daddu      $4, $16, $0
    /* D2F18 001D2F18 7438040C */  jal        func_0010E1D0
    /* D2F1C 001D2F1C 2D284000 */   daddu     $5, $2, $0
    /* D2F20 001D2F20 3000B227 */  addiu      $18, $29, 0x30
    /* D2F24 001D2F24 2700053C */  lui        $5, %hi(D_002724B0)
    /* D2F28 001D2F28 B024A524 */  addiu      $5, $5, %lo(D_002724B0)
    /* D2F2C 001D2F2C F036040C */  jal        GetInverseQuaternion
    /* D2F30 001D2F30 2D204002 */   daddu     $4, $18, $0
    /* D2F34 001D2F34 2000B327 */  addiu      $19, $29, 0x20
    /* D2F38 001D2F38 1000C526 */  addiu      $5, $22, 0x10
    /* D2F3C 001D2F3C 2D302002 */  daddu      $6, $17, $0
    /* D2F40 001D2F40 6238040C */  jal        func_0010E188
    /* D2F44 001D2F44 2D206002 */   daddu     $4, $19, $0
    /* D2F48 001D2F48 40B6898F */  lw         $9, %gp_rel(D_0062C230)($28)
    /* D2F4C 001D2F4C 0803228D */  lw         $2, 0x308($9)
    /* D2F50 001D2F50 2B004010 */  beqz       $2, .L001D3000
    /* D2F54 001D2F54 2D382001 */   daddu     $7, $9, $0
    /* D2F58 001D2F58 D002228D */  lw         $2, 0x2D0($9)
    /* D2F5C 001D2F5C 28004010 */  beqz       $2, .L001D3000
    /* D2F60 001D2F60 2700023C */   lui       $2, %hi(D_00271240)
    /* D2F64 001D2F64 0A000624 */  addiu      $6, $0, 0xA
    /* D2F68 001D2F68 4012458C */  lw         $5, %lo(D_00271240)($2)
    /* D2F6C 001D2F6C 3C000324 */  addiu      $3, $0, 0x3C
    /* D2F70 001D2F70 40124224 */  addiu      $2, $2, %lo(D_00271240)
    /* D2F74 001D2F74 7042013C */  lui        $1, (0x42700000 >> 16)
    /* D2F78 001D2F78 00088144 */  mtc1       $1, $f1
    /* D2F7C 001D2F7C 1828A600 */  mult       $5, $5, $6
    /* D2F80 001D2F80 0400448C */  lw         $4, 0x4($2)
    /* D2F84 001D2F84 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* D2F88 001D2F88 00108144 */  mtc1       $1, $f2
    /* D2F8C 001D2F8C 01008050 */  beql       $4, $0, .L001D2F94
    /* D2F90 001D2F90 CD010000 */   break     0, 7
.align 2
  .L001D2F94:
    /* D2F94 001D2F94 AC0323C5 */  lwc1       $f3, 0x3AC($9)
    /* D2F98 001D2F98 23186500 */  subu       $3, $3, $5
    /* D2F9C 001D2F9C 0000A4C6 */  lwc1       $f4, 0x0($21)
    /* D2FA0 001D2FA0 1A006400 */  div        $0, $3, $4
    /* D2FA4 001D2FA4 F0A3828F */  lw         $2, %gp_rel(D_0062AFE0)($28)
    /* D2FA8 001D2FA8 41110446 */  sub.s      $f5, $f2, $f4
    /* D2FAC 001D2FAC 12180000 */  mflo       $3
    /* D2FB0 001D2FB0 00008344 */  mtc1       $3, $f0
    /* D2FB4 001D2FB4 20008046 */  cvt.s.w    $f0, $f0
    /* D2FB8 001D2FB8 00000000 */  nop
    /* D2FBC 001D2FBC 00000000 */  nop
    /* D2FC0 001D2FC0 43080046 */  div.s      $f1, $f1, $f0
    /* D2FC4 001D2FC4 C2180146 */  mul.s      $f3, $f3, $f1
    /* D2FC8 001D2FC8 06004010 */  beqz       $2, .L001D2FE4
    /* D2FCC 001D2FCC 81100346 */   sub.s     $f2, $f2, $f3
    /* D2FD0 001D2FD0 38A480C7 */  lwc1       $f0, %gp_rel(D_0062B028)($28)
    /* D2FD4 001D2FD4 20008046 */  cvt.s.w    $f0, $f0
    /* D2FD8 001D2FD8 B88981C7 */  lwc1       $f1, %gp_rel(D_006295A8)($28)
    /* D2FDC 001D2FDC 03000010 */  b          .L001D2FEC
    /* D2FE0 001D2FE0 02000146 */   mul.s     $f0, $f0, $f1
.align 2
  .L001D2FE4:
    /* D2FE4 001D2FE4 58B6828F */  lw         $2, %gp_rel(D_0062C248)($28)
    /* D2FE8 001D2FE8 580140C4 */  lwc1       $f0, 0x158($2)
.align 2
  .L001D2FEC:
    /* D2FEC 001D2FEC 02100046 */  mul.s      $f0, $f2, $f0
    /* D2FF0 001D2FF0 00180046 */  add.s      $f0, $f3, $f0
    /* D2FF4 001D2FF4 02280046 */  mul.s      $f0, $f5, $f0
    /* D2FF8 001D2FF8 27000010 */  b          .L001D3098
    /* D2FFC 001D2FFC 00200046 */   add.s     $f0, $f4, $f0
.align 2
  .L001D3000:
    /* D3000 001D3000 2700023C */  lui        $2, %hi(D_00271240)
    /* D3004 001D3004 0A000624 */  addiu      $6, $0, 0xA
    /* D3008 001D3008 4012458C */  lw         $5, %lo(D_00271240)($2)
    /* D300C 001D300C 3C000324 */  addiu      $3, $0, 0x3C
    /* D3010 001D3010 40124224 */  addiu      $2, $2, %lo(D_00271240)
    /* D3014 001D3014 7042013C */  lui        $1, (0x42700000 >> 16)
    /* D3018 001D3018 00088144 */  mtc1       $1, $f1
    /* D301C 001D301C 1828A600 */  mult       $5, $5, $6
    /* D3020 001D3020 0400448C */  lw         $4, 0x4($2)
    /* D3024 001D3024 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* D3028 001D3028 00208144 */  mtc1       $1, $f4
    /* D302C 001D302C 01008050 */  beql       $4, $0, .L001D3034
    /* D3030 001D3030 CD010000 */   break     0, 7
.align 2
  .L001D3034:
    /* D3034 001D3034 AC03E2C4 */  lwc1       $f2, 0x3AC($7)
    /* D3038 001D3038 23186500 */  subu       $3, $3, $5
    /* D303C 001D303C F0A3828F */  lw         $2, %gp_rel(D_0062AFE0)($28)
    /* D3040 001D3040 1A006400 */  div        $0, $3, $4
    /* D3044 001D3044 0000A5C6 */  lwc1       $f5, 0x0($21)
    /* D3048 001D3048 12180000 */  mflo       $3
    /* D304C 001D304C 00008344 */  mtc1       $3, $f0
    /* D3050 001D3050 20008046 */  cvt.s.w    $f0, $f0
    /* D3054 001D3054 00000000 */  nop
    /* D3058 001D3058 00000000 */  nop
    /* D305C 001D305C 43080046 */  div.s      $f1, $f1, $f0
    /* D3060 001D3060 82100146 */  mul.s      $f2, $f2, $f1
    /* D3064 001D3064 06004010 */  beqz       $2, .L001D3080
    /* D3068 001D3068 C1200246 */   sub.s     $f3, $f4, $f2
    /* D306C 001D306C 38A480C7 */  lwc1       $f0, %gp_rel(D_0062B028)($28)
    /* D3070 001D3070 20008046 */  cvt.s.w    $f0, $f0
    /* D3074 001D3074 BC8981C7 */  lwc1       $f1, %gp_rel(D_006295AC)($28)
    /* D3078 001D3078 03000010 */  b          .L001D3088
    /* D307C 001D307C 02000146 */   mul.s     $f0, $f0, $f1
.align 2
  .L001D3080:
    /* D3080 001D3080 58B6828F */  lw         $2, %gp_rel(D_0062C248)($28)
    /* D3084 001D3084 580140C4 */  lwc1       $f0, 0x158($2)
.align 2
  .L001D3088:
    /* D3088 001D3088 02180046 */  mul.s      $f0, $f3, $f0
    /* D308C 001D308C 00100046 */  add.s      $f0, $f2, $f0
    /* D3090 001D3090 01200046 */  sub.s      $f0, $f4, $f0
    /* D3094 001D3094 02280046 */  mul.s      $f0, $f5, $f0
.align 2
  .L001D3098:
    /* D3098 001D3098 0000A0E6 */  swc1       $f0, 0x0($21)
    /* D309C 001D309C 5000B027 */  addiu      $16, $29, 0x50
    /* D30A0 001D30A0 2D280000 */  daddu      $5, $0, $0
    /* D30A4 001D30A4 2D200002 */  daddu      $4, $16, $0
    /* D30A8 001D30A8 5A81090C */  jal        func_00260568
    /* D30AC 001D30AC 10000624 */   addiu     $6, $0, 0x10
    /* D30B0 001D30B0 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* D30B4 001D30B4 00008144 */  mtc1       $1, $f0
    /* D30B8 001D30B8 02000324 */  addiu      $3, $0, 0x2
    /* D30BC 001D30BC 48B6828F */  lw         $2, %gp_rel(D_0062C238)($28)
    /* D30C0 001D30C0 04004314 */  bne        $2, $3, .L001D30D4
    /* D30C4 001D30C4 5C00A0E7 */   swc1      $f0, 0x5C($29)
    /* D30C8 001D30C8 2D200002 */  daddu      $4, $16, $0
    /* D30CC 001D30CC 6239040C */  jal        func_0010E588
    /* D30D0 001D30D0 1C070524 */   addiu     $5, $0, 0x71C
.align 2
  .L001D30D4:
    /* D30D4 001D30D4 4000B127 */  addiu      $17, $29, 0x40
    /* D30D8 001D30D8 0000ACC6 */  lwc1       $f12, 0x0($21)
    /* D30DC 001D30DC 2D280002 */  daddu      $5, $16, $0
    /* D30E0 001D30E0 2D306002 */  daddu      $6, $19, $0
    /* D30E4 001D30E4 8237040C */  jal        GetCurrentQuaternion
    /* D30E8 001D30E8 2D202002 */   daddu     $4, $17, $0
    /* D30EC 001D30EC 2D204002 */  daddu      $4, $18, $0
    /* D30F0 001D30F0 2D284002 */  daddu      $5, $18, $0
    /* D30F4 001D30F4 5238040C */  jal        func_0010E148
    /* D30F8 001D30F8 2D302002 */   daddu     $6, $17, $0
    /* D30FC 001D30FC DC35040C */  jal        InvertCurrentQuaternion
    /* D3100 001D3100 2D204002 */   daddu     $4, $18, $0
    /* D3104 001D3104 1E14040C */  jal        func_00105078
    /* D3108 001D3108 00000000 */   nop
    /* D310C 001D310C 8C37040C */  jal        GetLastQuaternion
    /* D3110 001D3110 2D804000 */   daddu     $16, $2, $0
    /* D3114 001D3114 2D200002 */  daddu      $4, $16, $0
    /* D3118 001D3118 7438040C */  jal        func_0010E1D0
    /* D311C 001D311C 2D284000 */   daddu     $5, $2, $0
    /* D3120 001D3120 40B6858F */  lw         $5, %gp_rel(D_0062C230)($28)
    /* D3124 001D3124 2D202002 */  daddu      $4, $17, $0
    /* D3128 001D3128 F236040C */  jal        RegularizeQuaternion
    /* D312C 001D312C C002A524 */   addiu     $5, $5, 0x2C0
    /* D3130 001D3130 8C37040C */  jal        GetLastQuaternion
    /* D3134 001D3134 00000000 */   nop
    /* D3138 001D3138 8C37040C */  jal        GetLastQuaternion
    /* D313C 001D313C 2D804000 */   daddu     $16, $2, $0
    /* D3140 001D3140 2D200002 */  daddu      $4, $16, $0
    /* D3144 001D3144 2D282002 */  daddu      $5, $17, $0
    /* D3148 001D3148 60090010 */  b          .L001D56CC
    /* D314C 001D314C 2D304000 */   daddu     $6, $2, $0
.align 2
  jlabel .L001D3150
    /* D3150 001D3150 8C37040C */  jal        GetLastQuaternion
    /* D3154 001D3154 2000D127 */   addiu     $17, $30, 0x20
    /* D3158 001D3158 2D804000 */  daddu      $16, $2, $0
    /* D315C 001D315C 9237040C */  jal        GetTableSin
    /* D3160 001D3160 2700173C */   lui       $23, %hi(D_002724B0)
    /* D3164 001D3164 2D200002 */  daddu      $4, $16, $0
    /* D3168 001D3168 2D284000 */  daddu      $5, $2, $0
    /* D316C 001D316C 5238040C */  jal        func_0010E148
    /* D3170 001D3170 2D302002 */   daddu     $6, $17, $0
    /* D3174 001D3174 1E14040C */  jal        func_00105078
    /* D3178 001D3178 00000000 */   nop
    /* D317C 001D317C 8C37040C */  jal        GetLastQuaternion
    /* D3180 001D3180 2D804000 */   daddu     $16, $2, $0
    /* D3184 001D3184 2D200002 */  daddu      $4, $16, $0
    /* D3188 001D3188 7438040C */  jal        func_0010E1D0
    /* D318C 001D318C 2D284000 */   daddu     $5, $2, $0
    /* D3190 001D3190 3000A427 */  addiu      $4, $29, 0x30
    /* D3194 001D3194 F036040C */  jal        GetInverseQuaternion
    /* D3198 001D3198 B024E526 */   addiu     $5, $23, %lo(D_002724B0)
    /* D319C 001D319C 2000B427 */  addiu      $20, $29, 0x20
    /* D31A0 001D31A0 1000C526 */  addiu      $5, $22, 0x10
    /* D31A4 001D31A4 2D302002 */  daddu      $6, $17, $0
    /* D31A8 001D31A8 6238040C */  jal        func_0010E188
    /* D31AC 001D31AC 2D208002 */   daddu     $4, $20, $0
    /* D31B0 001D31B0 8C37040C */  jal        GetLastQuaternion
    /* D31B4 001D31B4 00000000 */   nop
    /* D31B8 001D31B8 40B6838F */  lw         $3, %gp_rel(D_0062C230)($28)
    /* D31BC 001D31BC 2D204000 */  daddu      $4, $2, $0
    /* D31C0 001D31C0 6239040C */  jal        func_0010E588
    /* D31C4 001D31C4 F4026584 */   lh        $5, 0x2F4($3)
    /* D31C8 001D31C8 1E14040C */  jal        func_00105078
    /* D31CC 001D31CC 00000000 */   nop
    /* D31D0 001D31D0 8C37040C */  jal        GetLastQuaternion
    /* D31D4 001D31D4 2D804000 */   daddu     $16, $2, $0
    /* D31D8 001D31D8 2D200002 */  daddu      $4, $16, $0
    /* D31DC 001D31DC 7438040C */  jal        func_0010E1D0
    /* D31E0 001D31E0 2D284000 */   daddu     $5, $2, $0
    /* D31E4 001D31E4 40B6898F */  lw         $9, %gp_rel(D_0062C230)($28)
    /* D31E8 001D31E8 0803228D */  lw         $2, 0x308($9)
    /* D31EC 001D31EC 20004010 */  beqz       $2, .L001D3270
    /* D31F0 001D31F0 2D382001 */   daddu     $7, $9, $0
    /* D31F4 001D31F4 D002228D */  lw         $2, 0x2D0($9)
    /* D31F8 001D31F8 1D004010 */  beqz       $2, .L001D3270
    /* D31FC 001D31FC 2700023C */   lui       $2, %hi(D_00271240)
    /* D3200 001D3200 0A000624 */  addiu      $6, $0, 0xA
    /* D3204 001D3204 4012458C */  lw         $5, %lo(D_00271240)($2)
    /* D3208 001D3208 3C000324 */  addiu      $3, $0, 0x3C
    /* D320C 001D320C 40124224 */  addiu      $2, $2, %lo(D_00271240)
    /* D3210 001D3210 7042013C */  lui        $1, (0x42700000 >> 16)
    /* D3214 001D3214 00208144 */  mtc1       $1, $f4
    /* D3218 001D3218 1828A600 */  mult       $5, $5, $6
    /* D321C 001D321C 0400448C */  lw         $4, 0x4($2)
    /* D3220 001D3220 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* D3224 001D3224 00088144 */  mtc1       $1, $f1
    /* D3228 001D3228 01008050 */  beql       $4, $0, .L001D3230
    /* D322C 001D322C CD010000 */   break     0, 7
.align 2
  .L001D3230:
    /* D3230 001D3230 0000A3C6 */  lwc1       $f3, 0x0($21)
    /* D3234 001D3234 23186500 */  subu       $3, $3, $5
    /* D3238 001D3238 AC0322C5 */  lwc1       $f2, 0x3AC($9)
    /* D323C 001D323C 1A006400 */  div        $0, $3, $4
    /* D3240 001D3240 41080346 */  sub.s      $f1, $f1, $f3
    /* D3244 001D3244 12180000 */  mflo       $3
    /* D3248 001D3248 00008344 */  mtc1       $3, $f0
    /* D324C 001D324C 20008046 */  cvt.s.w    $f0, $f0
    /* D3250 001D3250 00000000 */  nop
    /* D3254 001D3254 00000000 */  nop
    /* D3258 001D3258 03210046 */  div.s      $f4, $f4, $f0
    /* D325C 001D325C 82100446 */  mul.s      $f2, $f2, $f4
    /* D3260 001D3260 42080246 */  mul.s      $f1, $f1, $f2
    /* D3264 001D3264 C0180146 */  add.s      $f3, $f3, $f1
    /* D3268 001D3268 1C000010 */  b          .L001D32DC
    /* D326C 001D326C 0000A3E6 */   swc1      $f3, 0x0($21)
.align 2
  .L001D3270:
    /* D3270 001D3270 2700023C */  lui        $2, %hi(D_00271240)
    /* D3274 001D3274 0A000624 */  addiu      $6, $0, 0xA
    /* D3278 001D3278 4012458C */  lw         $5, %lo(D_00271240)($2)
    /* D327C 001D327C 3C000324 */  addiu      $3, $0, 0x3C
    /* D3280 001D3280 40124224 */  addiu      $2, $2, %lo(D_00271240)
    /* D3284 001D3284 7042013C */  lui        $1, (0x42700000 >> 16)
    /* D3288 001D3288 00188144 */  mtc1       $1, $f3
    /* D328C 001D328C 1828A600 */  mult       $5, $5, $6
    /* D3290 001D3290 0400448C */  lw         $4, 0x4($2)
    /* D3294 001D3294 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* D3298 001D3298 00208144 */  mtc1       $1, $f4
    /* D329C 001D329C 01008050 */  beql       $4, $0, .L001D32A4
    /* D32A0 001D32A0 CD010000 */   break     0, 7
.align 2
  .L001D32A4:
    /* D32A4 001D32A4 AC03E1C4 */  lwc1       $f1, 0x3AC($7)
    /* D32A8 001D32A8 23186500 */  subu       $3, $3, $5
    /* D32AC 001D32AC 0000A2C6 */  lwc1       $f2, 0x0($21)
    /* D32B0 001D32B0 1A006400 */  div        $0, $3, $4
    /* D32B4 001D32B4 12180000 */  mflo       $3
    /* D32B8 001D32B8 00008344 */  mtc1       $3, $f0
    /* D32BC 001D32BC 20008046 */  cvt.s.w    $f0, $f0
    /* D32C0 001D32C0 00000000 */  nop
    /* D32C4 001D32C4 00000000 */  nop
    /* D32C8 001D32C8 C3180046 */  div.s      $f3, $f3, $f0
    /* D32CC 001D32CC 42080346 */  mul.s      $f1, $f1, $f3
    /* D32D0 001D32D0 01210146 */  sub.s      $f4, $f4, $f1
    /* D32D4 001D32D4 82100446 */  mul.s      $f2, $f2, $f4
    /* D32D8 001D32D8 0000A2E6 */  swc1       $f2, 0x0($21)
.align 2
  .L001D32DC:
    /* D32DC 001D32DC 0000A1C6 */  lwc1       $f1, 0x0($21)
    /* D32E0 001D32E0 C08980C7 */  lwc1       $f0, %gp_rel(D_006295B0)($28)
    /* D32E4 001D32E4 34080046 */  c.lt.s     $f1, $f0
    /* D32E8 001D32E8 00000000 */  nop
    /* D32EC 001D32EC 0E000045 */  bc1f       .L001D3328
    /* D32F0 001D32F0 48B6828F */   lw        $2, %gp_rel(D_0062C238)($28)
    /* D32F4 001D32F4 8C37040C */  jal        GetLastQuaternion
    /* D32F8 001D32F8 1000B626 */   addiu     $22, $21, 0x10
    /* D32FC 001D32FC 2D284000 */  daddu      $5, $2, $0
    /* D3300 001D3300 F036040C */  jal        GetInverseQuaternion
    /* D3304 001D3304 2D20C002 */   daddu     $4, $22, $0
    /* D3308 001D3308 3000B026 */  addiu      $16, $21, 0x30
    /* D330C 001D330C 3036040C */  jal        GetMatrixFromQuaternion
    /* D3310 001D3310 2D200002 */   daddu     $4, $16, $0
    /* D3314 001D3314 2D280002 */  daddu      $5, $16, $0
    /* D3318 001D3318 F036040C */  jal        GetInverseQuaternion
    /* D331C 001D331C 2000A426 */   addiu     $4, $21, 0x20
    /* D3320 001D3320 8D000010 */  b          .L001D3558
    /* D3324 001D3324 9000B127 */   addiu     $17, $29, 0x90
.align 2
  .L001D3328:
    /* D3328 001D3328 04001124 */  addiu      $17, $0, 0x4
    /* D332C 001D332C 04005114 */  bne        $2, $17, .L001D3340
    /* D3330 001D3330 00000000 */   nop
    /* D3334 001D3334 5213040C */  jal        func_00104D48
    /* D3338 001D3338 00800424 */   addiu     $4, $0, -0x8000
    /* D333C 001D333C 40B6898F */  lw         $9, %gp_rel(D_0062C230)($28)
.align 2
  .L001D3340:
    /* D3340 001D3340 1E14040C */  jal        func_00105078
    /* D3344 001D3344 E0023025 */   addiu     $16, $9, 0x2E0
    /* D3348 001D3348 40B6868F */  lw         $6, %gp_rel(D_0062C230)($28)
    /* D334C 001D334C 30004524 */  addiu      $5, $2, 0x30
    /* D3350 001D3350 5E17040C */  jal        MatrixDrive_TurnZObjectMatrixXY
    /* D3354 001D3354 7000A427 */   addiu     $4, $29, 0x70
    /* D3358 001D3358 2D280002 */  daddu      $5, $16, $0
    /* D335C 001D335C 6000A427 */  addiu      $4, $29, 0x60
    /* D3360 001D3360 6417040C */  jal        MatrixDrive_GetTurnXAngleZY
    /* D3364 001D3364 7000A627 */   addiu     $6, $29, 0x70
    /* D3368 001D3368 1614040C */  jal        func_00105058
    /* D336C 001D336C 6C00A0AF */   sw        $0, 0x6C($29)
    /* D3370 001D3370 1E14040C */  jal        func_00105078
    /* D3374 001D3374 00000000 */   nop
    /* D3378 001D3378 2414040C */  jal        func_00105090
    /* D337C 001D337C 2D804000 */   daddu     $16, $2, $0
    /* D3380 001D3380 2D200002 */  daddu      $4, $16, $0
    /* D3384 001D3384 1C17040C */  jal        MatrixDrive_TransMatrix
    /* D3388 001D3388 2D284000 */   daddu     $5, $2, $0
    /* D338C 001D338C 1E14040C */  jal        func_00105078
    /* D3390 001D3390 00000000 */   nop
    /* D3394 001D3394 2D284000 */  daddu      $5, $2, $0
    /* D3398 001D3398 5000A427 */  addiu      $4, $29, 0x50
    /* D339C 001D339C 76FF080C */  jal        func_0023FDD8
    /* D33A0 001D33A0 6000A627 */   addiu     $6, $29, 0x60
    /* D33A4 001D33A4 1A14040C */  jal        func_00105068
    /* D33A8 001D33A8 00000000 */   nop
    /* D33AC 001D33AC 5000ACC7 */  lwc1       $f12, 0x50($29)
    /* D33B0 001D33B0 8000A427 */  addiu      $4, $29, 0x80
    /* D33B4 001D33B4 5400ADC7 */  lwc1       $f13, 0x54($29)
    /* D33B8 001D33B8 8200A527 */  addiu      $5, $29, 0x82
    /* D33BC 001D33BC FA15040C */  jal        MatrixDrive_PushMatrixWithNoCopy
    /* D33C0 001D33C0 5800AEC7 */   lwc1      $f14, 0x58($29)
    /* D33C4 001D33C4 8200AA97 */  lhu        $10, 0x82($29)
    /* D33C8 001D33C8 01000224 */  addiu      $2, $0, 0x1
    /* D33CC 001D33CC 8000A887 */  lh         $8, 0x80($29)
    /* D33D0 001D33D0 8400A427 */  addiu      $4, $29, 0x84
    /* D33D4 001D33D4 23500A00 */  negu       $10, $10
    /* D33D8 001D33D8 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* D33DC 001D33DC 00608144 */  mtc1       $1, $f12
    /* D33E0 001D33E0 00540A00 */  sll        $10, $10, 16
    /* D33E4 001D33E4 A001A78F */  lw         $7, 0x1A0($29)
    /* D33E8 001D33E8 0800A2AF */  sw         $2, 0x8($29)
    /* D33EC 001D33EC 03540A00 */  sra        $10, $10, 16
    /* D33F0 001D33F0 0000A0AF */  sw         $0, 0x0($29)
    /* D33F4 001D33F4 8600A527 */  addiu      $5, $29, 0x86
    /* D33F8 001D33F8 8800A627 */  addiu      $6, $29, 0x88
    /* D33FC 001D33FC 2D480000 */  daddu      $9, $0, $0
    /* D3400 001D3400 B648070C */  jal        AddMotionMemorySize
    /* D3404 001D3404 2D580000 */   daddu     $11, $0, $0
    /* D3408 001D3408 8600A287 */  lh         $2, 0x86($29)
    /* D340C 001D340C 48B6838F */  lw         $3, %gp_rel(D_0062C238)($28)
    /* D3410 001D3410 23100200 */  negu       $2, $2
    /* D3414 001D3414 05007114 */  bne        $3, $17, .L001D342C
    /* D3418 001D3418 8600A2A7 */   sh        $2, 0x86($29)
    /* D341C 001D341C 00140200 */  sll        $2, $2, 16
    /* D3420 001D3420 03140200 */  sra        $2, $2, 16
    /* D3424 001D3424 23100200 */  negu       $2, $2
    /* D3428 001D3428 8600A2A7 */  sh         $2, 0x86($29)
.align 2
  .L001D342C:
    /* D342C 001D342C 8000A397 */  lhu        $3, 0x80($29)
    /* D3430 001D3430 6000B127 */  addiu      $17, $29, 0x60
    /* D3434 001D3434 8400A797 */  lhu        $7, 0x84($29)
    /* D3438 001D3438 2D202002 */  daddu      $4, $17, $0
    /* D343C 001D343C 8200A297 */  lhu        $2, 0x82($29)
    /* D3440 001D3440 1000B626 */  addiu      $22, $21, 0x10
    /* D3444 001D3444 8600A697 */  lhu        $6, 0x86($29)
    /* D3448 001D3448 23186700 */  subu       $3, $3, $7
    /* D344C 001D344C 40B6858F */  lw         $5, %gp_rel(D_0062C230)($28)
    /* D3450 001D3450 3000B326 */  addiu      $19, $21, 0x30
    /* D3454 001D3454 23104600 */  subu       $2, $2, $6
    /* D3458 001D3458 2000B226 */  addiu      $18, $21, 0x20
    /* D345C 001D345C F202A2A4 */  sh         $2, 0x2F2($5)
    /* D3460 001D3460 3036040C */  jal        GetMatrixFromQuaternion
    /* D3464 001D3464 F002A3A4 */   sh        $3, 0x2F0($5)
    /* D3468 001D3468 8400A597 */  lhu        $5, 0x84($29)
    /* D346C 001D346C 2D202002 */  daddu      $4, $17, $0
    /* D3470 001D3470 23280500 */  negu       $5, $5
    /* D3474 001D3474 002C0500 */  sll        $5, $5, 16
    /* D3478 001D3478 1239040C */  jal        func_0010E448
    /* D347C 001D347C 032C0500 */   sra       $5, $5, 16
    /* D3480 001D3480 8600A597 */  lhu        $5, 0x86($29)
    /* D3484 001D3484 2D202002 */  daddu      $4, $17, $0
    /* D3488 001D3488 23280500 */  negu       $5, $5
    /* D348C 001D348C 002C0500 */  sll        $5, $5, 16
    /* D3490 001D3490 6239040C */  jal        func_0010E588
    /* D3494 001D3494 032C0500 */   sra       $5, $5, 16
    /* D3498 001D3498 8800A597 */  lhu        $5, 0x88($29)
    /* D349C 001D349C 2D202002 */  daddu      $4, $17, $0
    /* D34A0 001D34A0 23280500 */  negu       $5, $5
    /* D34A4 001D34A4 002C0500 */  sll        $5, $5, 16
    /* D34A8 001D34A8 3A39040C */  jal        func_0010E4E8
    /* D34AC 001D34AC 032C0500 */   sra       $5, $5, 16
    /* D34B0 001D34B0 C4898CC7 */  lwc1       $f12, %gp_rel(D_006295B4)($28)
    /* D34B4 001D34B4 2D382002 */  daddu      $7, $17, $0
    /* D34B8 001D34B8 A001A58F */  lw         $5, 0x1A0($29)
    /* D34BC 001D34BC 2D20C002 */  daddu      $4, $22, $0
    /* D34C0 001D34C0 EC4A070C */  jal        ResetDynamicMotionManager
    /* D34C4 001D34C4 2D306002 */   daddu     $6, $19, $0
    /* D34C8 001D34C8 8C37040C */  jal        GetLastQuaternion
    /* D34CC 001D34CC 7000B027 */   addiu     $16, $29, 0x70
    /* D34D0 001D34D0 2D302002 */  daddu      $6, $17, $0
    /* D34D4 001D34D4 2D200002 */  daddu      $4, $16, $0
    /* D34D8 001D34D8 5238040C */  jal        func_0010E148
    /* D34DC 001D34DC 2D284000 */   daddu     $5, $2, $0
    /* D34E0 001D34E0 9000B127 */  addiu      $17, $29, 0x90
    /* D34E4 001D34E4 2D280002 */  daddu      $5, $16, $0
    /* D34E8 001D34E8 2D202002 */  daddu      $4, $17, $0
    /* D34EC 001D34EC 6238040C */  jal        func_0010E188
    /* D34F0 001D34F0 2D30C002 */   daddu     $6, $22, $0
    /* D34F4 001D34F4 40B6828F */  lw         $2, %gp_rel(D_0062C230)($28)
    /* D34F8 001D34F8 A000B027 */  addiu      $16, $29, 0xA0
    /* D34FC 001D34FC B024E626 */  addiu      $6, $23, %lo(D_002724B0)
    /* D3500 001D3500 2D200002 */  daddu      $4, $16, $0
    /* D3504 001D3504 B4034CC4 */  lwc1       $f12, 0x3B4($2)
    /* D3508 001D3508 8237040C */  jal        GetCurrentQuaternion
    /* D350C 001D350C 2D282002 */   daddu     $5, $17, $0
    /* D3510 001D3510 40B6828F */  lw         $2, %gp_rel(D_0062C230)($28)
    /* D3514 001D3514 2D280002 */  daddu      $5, $16, $0
    /* D3518 001D3518 2D204002 */  daddu      $4, $18, $0
    /* D351C 001D351C 2D304002 */  daddu      $6, $18, $0
    /* D3520 001D3520 8237040C */  jal        GetCurrentQuaternion
    /* D3524 001D3524 B8034CC4 */   lwc1      $f12, 0x3B8($2)
    /* D3528 001D3528 2D304002 */  daddu      $6, $18, $0
    /* D352C 001D352C 2D20C002 */  daddu      $4, $22, $0
    /* D3530 001D3530 5238040C */  jal        func_0010E148
    /* D3534 001D3534 2D28C002 */   daddu     $5, $22, $0
    /* D3538 001D3538 0237040C */  jal        GetSlerpQuaternionNoRegularize
    /* D353C 001D353C 2D20C002 */   daddu     $4, $22, $0
    /* D3540 001D3540 8C37040C */  jal        GetLastQuaternion
    /* D3544 001D3544 00000000 */   nop
    /* D3548 001D3548 2D206002 */  daddu      $4, $19, $0
    /* D354C 001D354C 2D304000 */  daddu      $6, $2, $0
    /* D3550 001D3550 6238040C */  jal        func_0010E188
    /* D3554 001D3554 2D28C002 */   daddu     $5, $22, $0
.align 2
  .L001D3558:
    /* D3558 001D3558 8C37040C */  jal        GetLastQuaternion
    /* D355C 001D355C 4C00103C */   lui       $16, %hi(D_004C1C50)
    /* D3560 001D3560 40B6838F */  lw         $3, %gp_rel(D_0062C230)($28)
    /* D3564 001D3564 2D204000 */  daddu      $4, $2, $0
    /* D3568 001D3568 2040013C */  lui        $1, (0x40200000 >> 16)
    /* D356C 001D356C 00088144 */  mtc1       $1, $f1
    /* D3570 001D3570 50006284 */  lh         $2, 0x50($3)
    /* D3574 001D3574 23100200 */  negu       $2, $2
    /* D3578 001D3578 00008244 */  mtc1       $2, $f0
    /* D357C 001D357C 20008046 */  cvt.s.w    $f0, $f0
    /* D3580 001D3580 02000146 */  mul.s      $f0, $f0, $f1
    /* D3584 001D3584 64000046 */  .word      0x46000064                    # cvt.w.s    $f1, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* D3588 001D3588 00080544 */  mfc1       $5, $f1
    /* D358C 001D358C 002C0500 */  sll        $5, $5, 16
    /* D3590 001D3590 1239040C */  jal        func_0010E448
    /* D3594 001D3594 032C0500 */   sra       $5, $5, 16
    /* D3598 001D3598 8C37040C */  jal        GetLastQuaternion
    /* D359C 001D359C 501C1026 */   addiu     $16, $16, %lo(D_004C1C50)
    /* D35A0 001D35A0 2D202002 */  daddu      $4, $17, $0
    /* D35A4 001D35A4 2D284000 */  daddu      $5, $2, $0
    /* D35A8 001D35A8 5238040C */  jal        func_0010E148
    /* D35AC 001D35AC 2D308002 */   daddu     $6, $20, $0
    /* D35B0 001D35B0 8C37040C */  jal        GetLastQuaternion
    /* D35B4 001D35B4 00000000 */   nop
    /* D35B8 001D35B8 0000ACC6 */  lwc1       $f12, 0x0($21)
    /* D35BC 001D35BC 2D302002 */  daddu      $6, $17, $0
    /* D35C0 001D35C0 2D204000 */  daddu      $4, $2, $0
    /* D35C4 001D35C4 8237040C */  jal        GetCurrentQuaternion
    /* D35C8 001D35C8 2D28C002 */   daddu     $5, $22, $0
    /* D35CC 001D35CC 8C37040C */  jal        GetLastQuaternion
    /* D35D0 001D35D0 00000000 */   nop
    /* D35D4 001D35D4 8C37040C */  jal        GetLastQuaternion
    /* D35D8 001D35D8 2D884000 */   daddu     $17, $2, $0
    /* D35DC 001D35DC 2D280002 */  daddu      $5, $16, $0
    /* D35E0 001D35E0 2D202002 */  daddu      $4, $17, $0
    /* D35E4 001D35E4 39080010 */  b          .L001D56CC
    /* D35E8 001D35E8 2D304000 */   daddu     $6, $2, $0
.align 2
  jlabel .L001D35EC
    /* D35EC 001D35EC 8C37040C */  jal        GetLastQuaternion
    /* D35F0 001D35F0 2000D227 */   addiu     $18, $30, 0x20
    /* D35F4 001D35F4 9237040C */  jal        GetTableSin
    /* D35F8 001D35F8 2D804000 */   daddu     $16, $2, $0
    /* D35FC 001D35FC 2D200002 */  daddu      $4, $16, $0
    /* D3600 001D3600 2D284000 */  daddu      $5, $2, $0
    /* D3604 001D3604 5238040C */  jal        func_0010E148
    /* D3608 001D3608 2D304002 */   daddu     $6, $18, $0
    /* D360C 001D360C 1E14040C */  jal        func_00105078
    /* D3610 001D3610 00000000 */   nop
    /* D3614 001D3614 8C37040C */  jal        GetLastQuaternion
    /* D3618 001D3618 2D804000 */   daddu     $16, $2, $0
    /* D361C 001D361C 2D200002 */  daddu      $4, $16, $0
    /* D3620 001D3620 7438040C */  jal        func_0010E1D0
    /* D3624 001D3624 2D284000 */   daddu     $5, $2, $0
    /* D3628 001D3628 2700023C */  lui        $2, %hi(D_002724B0)
    /* D362C 001D362C 3000A427 */  addiu      $4, $29, 0x30
    /* D3630 001D3630 F036040C */  jal        GetInverseQuaternion
    /* D3634 001D3634 B0244524 */   addiu     $5, $2, %lo(D_002724B0)
    /* D3638 001D3638 2000B127 */  addiu      $17, $29, 0x20
    /* D363C 001D363C 1000C526 */  addiu      $5, $22, 0x10
    /* D3640 001D3640 2D304002 */  daddu      $6, $18, $0
    /* D3644 001D3644 6238040C */  jal        func_0010E188
    /* D3648 001D3648 2D202002 */   daddu     $4, $17, $0
    /* D364C 001D364C 8C37040C */  jal        GetLastQuaternion
    /* D3650 001D3650 00000000 */   nop
    /* D3654 001D3654 8C37040C */  jal        GetLastQuaternion
    /* D3658 001D3658 2D804000 */   daddu     $16, $2, $0
    /* D365C 001D365C 2D200002 */  daddu      $4, $16, $0
    /* D3660 001D3660 2D284000 */  daddu      $5, $2, $0
    /* D3664 001D3664 5238040C */  jal        func_0010E148
    /* D3668 001D3668 2D302002 */   daddu     $6, $17, $0
    /* D366C 001D366C 1E14040C */  jal        func_00105078
    /* D3670 001D3670 00000000 */   nop
    /* D3674 001D3674 8C37040C */  jal        GetLastQuaternion
    /* D3678 001D3678 2D804000 */   daddu     $16, $2, $0
    /* D367C 001D367C 2D200002 */  daddu      $4, $16, $0
    /* D3680 001D3680 7438040C */  jal        func_0010E1D0
    /* D3684 001D3684 2D284000 */   daddu     $5, $2, $0
    /* D3688 001D3688 40B6898F */  lw         $9, %gp_rel(D_0062C230)($28)
    /* D368C 001D368C 0C03228D */  lw         $2, 0x30C($9)
    /* D3690 001D3690 34004010 */  beqz       $2, .L001D3764
    /* D3694 001D3694 2D382001 */   daddu     $7, $9, $0
    /* D3698 001D3698 0803228D */  lw         $2, 0x308($9)
    /* D369C 001D369C 05004050 */  beql       $2, $0, .L001D36B4
    /* D36A0 001D36A0 2002228D */   lw        $2, 0x220($9)
    /* D36A4 001D36A4 D002228D */  lw         $2, 0x2D0($9)
    /* D36A8 001D36A8 07004014 */  bnez       $2, .L001D36C8
    /* D36AC 001D36AC 2700023C */   lui       $2, %hi(D_00271240)
    /* D36B0 001D36B0 2002228D */  lw         $2, 0x220($9)
.align 2
  .L001D36B4:
    /* D36B4 001D36B4 04004014 */  bnez       $2, .L001D36C8
    /* D36B8 001D36B8 2700023C */   lui       $2, %hi(D_00271240)
    /* D36BC 001D36BC 8002228D */  lw         $2, 0x280($9)
    /* D36C0 001D36C0 28004010 */  beqz       $2, .L001D3764
    /* D36C4 001D36C4 2700023C */   lui       $2, %hi(D_00271240)
.align 2
  .L001D36C8:
    /* D36C8 001D36C8 0A000624 */  addiu      $6, $0, 0xA
    /* D36CC 001D36CC 4012458C */  lw         $5, %lo(D_00271240)($2)
    /* D36D0 001D36D0 3C000324 */  addiu      $3, $0, 0x3C
    /* D36D4 001D36D4 40124224 */  addiu      $2, $2, %lo(D_00271240)
    /* D36D8 001D36D8 7042013C */  lui        $1, (0x42700000 >> 16)
    /* D36DC 001D36DC 00088144 */  mtc1       $1, $f1
    /* D36E0 001D36E0 1828A600 */  mult       $5, $5, $6
    /* D36E4 001D36E4 0400448C */  lw         $4, 0x4($2)
    /* D36E8 001D36E8 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* D36EC 001D36EC 00108144 */  mtc1       $1, $f2
    /* D36F0 001D36F0 01008050 */  beql       $4, $0, .L001D36F8
    /* D36F4 001D36F4 CD010000 */   break     0, 7
.align 2
  .L001D36F8:
    /* D36F8 001D36F8 AC03E3C4 */  lwc1       $f3, 0x3AC($7)
    /* D36FC 001D36FC 23186500 */  subu       $3, $3, $5
    /* D3700 001D3700 0000A4C6 */  lwc1       $f4, 0x0($21)
    /* D3704 001D3704 1A006400 */  div        $0, $3, $4
    /* D3708 001D3708 F0A3828F */  lw         $2, %gp_rel(D_0062AFE0)($28)
    /* D370C 001D370C 41110446 */  sub.s      $f5, $f2, $f4
    /* D3710 001D3710 12180000 */  mflo       $3
    /* D3714 001D3714 00008344 */  mtc1       $3, $f0
    /* D3718 001D3718 20008046 */  cvt.s.w    $f0, $f0
    /* D371C 001D371C 00000000 */  nop
    /* D3720 001D3720 00000000 */  nop
    /* D3724 001D3724 43080046 */  div.s      $f1, $f1, $f0
    /* D3728 001D3728 C2180146 */  mul.s      $f3, $f3, $f1
    /* D372C 001D372C 06004010 */  beqz       $2, .L001D3748
    /* D3730 001D3730 81100346 */   sub.s     $f2, $f2, $f3
    /* D3734 001D3734 38A480C7 */  lwc1       $f0, %gp_rel(D_0062B028)($28)
    /* D3738 001D3738 20008046 */  cvt.s.w    $f0, $f0
    /* D373C 001D373C C88981C7 */  lwc1       $f1, %gp_rel(D_006295B8)($28)
    /* D3740 001D3740 03000010 */  b          .L001D3750
    /* D3744 001D3744 02000146 */   mul.s     $f0, $f0, $f1
.align 2
  .L001D3748:
    /* D3748 001D3748 58B6828F */  lw         $2, %gp_rel(D_0062C248)($28)
    /* D374C 001D374C 580140C4 */  lwc1       $f0, 0x158($2)
.align 2
  .L001D3750:
    /* D3750 001D3750 02100046 */  mul.s      $f0, $f2, $f0
    /* D3754 001D3754 00180046 */  add.s      $f0, $f3, $f0
    /* D3758 001D3758 02280046 */  mul.s      $f0, $f5, $f0
    /* D375C 001D375C 27000010 */  b          .L001D37FC
    /* D3760 001D3760 00200046 */   add.s     $f0, $f4, $f0
.align 2
  .L001D3764:
    /* D3764 001D3764 2700023C */  lui        $2, %hi(D_00271240)
    /* D3768 001D3768 0A000624 */  addiu      $6, $0, 0xA
    /* D376C 001D376C 4012458C */  lw         $5, %lo(D_00271240)($2)
    /* D3770 001D3770 3C000324 */  addiu      $3, $0, 0x3C
    /* D3774 001D3774 40124224 */  addiu      $2, $2, %lo(D_00271240)
    /* D3778 001D3778 7042013C */  lui        $1, (0x42700000 >> 16)
    /* D377C 001D377C 00088144 */  mtc1       $1, $f1
    /* D3780 001D3780 1828A600 */  mult       $5, $5, $6
    /* D3784 001D3784 0400448C */  lw         $4, 0x4($2)
    /* D3788 001D3788 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* D378C 001D378C 00208144 */  mtc1       $1, $f4
    /* D3790 001D3790 01008050 */  beql       $4, $0, .L001D3798
    /* D3794 001D3794 CD010000 */   break     0, 7
.align 2
  .L001D3798:
    /* D3798 001D3798 AC03E2C4 */  lwc1       $f2, 0x3AC($7)
    /* D379C 001D379C 23186500 */  subu       $3, $3, $5
    /* D37A0 001D37A0 F0A3828F */  lw         $2, %gp_rel(D_0062AFE0)($28)
    /* D37A4 001D37A4 1A006400 */  div        $0, $3, $4
    /* D37A8 001D37A8 0000A5C6 */  lwc1       $f5, 0x0($21)
    /* D37AC 001D37AC 12180000 */  mflo       $3
    /* D37B0 001D37B0 00008344 */  mtc1       $3, $f0
    /* D37B4 001D37B4 20008046 */  cvt.s.w    $f0, $f0
    /* D37B8 001D37B8 00000000 */  nop
    /* D37BC 001D37BC 00000000 */  nop
    /* D37C0 001D37C0 43080046 */  div.s      $f1, $f1, $f0
    /* D37C4 001D37C4 82100146 */  mul.s      $f2, $f2, $f1
    /* D37C8 001D37C8 06004010 */  beqz       $2, .L001D37E4
    /* D37CC 001D37CC C1200246 */   sub.s     $f3, $f4, $f2
    /* D37D0 001D37D0 38A480C7 */  lwc1       $f0, %gp_rel(D_0062B028)($28)
    /* D37D4 001D37D4 20008046 */  cvt.s.w    $f0, $f0
    /* D37D8 001D37D8 CC8981C7 */  lwc1       $f1, %gp_rel(D_006295BC)($28)
    /* D37DC 001D37DC 03000010 */  b          .L001D37EC
    /* D37E0 001D37E0 02000146 */   mul.s     $f0, $f0, $f1
.align 2
  .L001D37E4:
    /* D37E4 001D37E4 58B6828F */  lw         $2, %gp_rel(D_0062C248)($28)
    /* D37E8 001D37E8 580140C4 */  lwc1       $f0, 0x158($2)
.align 2
  .L001D37EC:
    /* D37EC 001D37EC 02180046 */  mul.s      $f0, $f3, $f0
    /* D37F0 001D37F0 00100046 */  add.s      $f0, $f2, $f0
    /* D37F4 001D37F4 01200046 */  sub.s      $f0, $f4, $f0
    /* D37F8 001D37F8 02280046 */  mul.s      $f0, $f5, $f0
.align 2
  .L001D37FC:
    /* D37FC 001D37FC 0000A0E6 */  swc1       $f0, 0x0($21)
    /* D3800 001D3800 0000A1C6 */  lwc1       $f1, 0x0($21)
    /* D3804 001D3804 D08980C7 */  lwc1       $f0, %gp_rel(D_006295C0)($28)
    /* D3808 001D3808 34080046 */  c.lt.s     $f1, $f0
    /* D380C 001D380C 00000000 */  nop
    /* D3810 001D3810 0D000045 */  bc1f       .L001D3848
    /* D3814 001D3814 1000B626 */   addiu     $22, $21, 0x10
    /* D3818 001D3818 8C37040C */  jal        GetLastQuaternion
    /* D381C 001D381C 3000B026 */   addiu     $16, $21, 0x30
    /* D3820 001D3820 2D284000 */  daddu      $5, $2, $0
    /* D3824 001D3824 F036040C */  jal        GetInverseQuaternion
    /* D3828 001D3828 2D20C002 */   daddu     $4, $22, $0
    /* D382C 001D382C 3036040C */  jal        GetMatrixFromQuaternion
    /* D3830 001D3830 2D200002 */   daddu     $4, $16, $0
    /* D3834 001D3834 2D280002 */  daddu      $5, $16, $0
    /* D3838 001D3838 F036040C */  jal        GetInverseQuaternion
    /* D383C 001D383C 2000A426 */   addiu     $4, $21, 0x20
    /* D3840 001D3840 24010010 */  b          .L001D3CD4
    /* D3844 001D3844 00000000 */   nop
.align 2
  .L001D3848:
    /* D3848 001D3848 3000BE26 */  addiu      $30, $21, 0x30
    /* D384C 001D384C A001A58F */  lw         $5, 0x1A0($29)
    /* D3850 001D3850 2D20C002 */  daddu      $4, $22, $0
    /* D3854 001D3854 2D30C003 */  daddu      $6, $30, $0
    /* D3858 001D3858 984A070C */  jal        GetMotionMemorySize
    /* D385C 001D385C 2DA0C002 */   daddu     $20, $22, $0
    /* D3860 001D3860 2D900000 */  daddu      $18, $0, $0
    /* D3864 001D3864 40B6898F */  lw         $9, %gp_rel(D_0062C230)($28)
    /* D3868 001D3868 2DB80000 */  daddu      $23, $0, $0
    /* D386C 001D386C 01000224 */  addiu      $2, $0, 0x1
    /* D3870 001D3870 0C03318D */  lw         $17, 0x30C($9)
    /* D3874 001D3874 51002216 */  bne        $17, $2, .L001D39BC
    /* D3878 001D3878 2D980000 */   daddu     $19, $0, $0
    /* D387C 001D387C 8002228D */  lw         $2, 0x280($9)
    /* D3880 001D3880 24004010 */  beqz       $2, .L001D3914
    /* D3884 001D3884 90023025 */   addiu     $16, $9, 0x290
    /* D3888 001D3888 1E14040C */  jal        func_00105078
    /* D388C 001D388C 01001324 */   addiu     $19, $0, 0x1
    /* D3890 001D3890 40B6868F */  lw         $6, %gp_rel(D_0062C230)($28)
    /* D3894 001D3894 30004524 */  addiu      $5, $2, 0x30
    /* D3898 001D3898 5E17040C */  jal        MatrixDrive_TurnZObjectMatrixXY
    /* D389C 001D389C 6000A427 */   addiu     $4, $29, 0x60
    /* D38A0 001D38A0 2D280002 */  daddu      $5, $16, $0
    /* D38A4 001D38A4 5000A427 */  addiu      $4, $29, 0x50
    /* D38A8 001D38A8 6417040C */  jal        MatrixDrive_GetTurnXAngleZY
    /* D38AC 001D38AC 6000A627 */   addiu     $6, $29, 0x60
    /* D38B0 001D38B0 1614040C */  jal        func_00105058
    /* D38B4 001D38B4 5C00A0AF */   sw        $0, 0x5C($29)
    /* D38B8 001D38B8 1E14040C */  jal        func_00105078
    /* D38BC 001D38BC 00000000 */   nop
    /* D38C0 001D38C0 2414040C */  jal        func_00105090
    /* D38C4 001D38C4 2D804000 */   daddu     $16, $2, $0
    /* D38C8 001D38C8 2D200002 */  daddu      $4, $16, $0
    /* D38CC 001D38CC 1C17040C */  jal        MatrixDrive_TransMatrix
    /* D38D0 001D38D0 2D284000 */   daddu     $5, $2, $0
    /* D38D4 001D38D4 1E14040C */  jal        func_00105078
    /* D38D8 001D38D8 00000000 */   nop
    /* D38DC 001D38DC 2D284000 */  daddu      $5, $2, $0
    /* D38E0 001D38E0 A000A427 */  addiu      $4, $29, 0xA0
    /* D38E4 001D38E4 76FF080C */  jal        func_0023FDD8
    /* D38E8 001D38E8 5000A627 */   addiu     $6, $29, 0x50
    /* D38EC 001D38EC 1A14040C */  jal        func_00105068
    /* D38F0 001D38F0 00000000 */   nop
    /* D38F4 001D38F4 A000ACC7 */  lwc1       $f12, 0xA0($29)
    /* D38F8 001D38F8 B000A427 */  addiu      $4, $29, 0xB0
    /* D38FC 001D38FC A400ADC7 */  lwc1       $f13, 0xA4($29)
    /* D3900 001D3900 B200A527 */  addiu      $5, $29, 0xB2
    /* D3904 001D3904 E216040C */  jal        MatrixDrive_TransMatrixV
    /* D3908 001D3908 A800AEC7 */   lwc1      $f14, 0xA8($29)
    /* D390C 001D390C B000B287 */  lh         $18, 0xB0($29)
    /* D3910 001D3910 40B6898F */  lw         $9, %gp_rel(D_0062C230)($28)
.align 2
  .L001D3914:
    /* D3914 001D3914 0C03228D */  lw         $2, 0x30C($9)
    /* D3918 001D3918 29005154 */  bnel       $2, $17, .L001D39C0
    /* D391C 001D391C 0803228D */   lw        $2, 0x308($9)
    /* D3920 001D3920 2002228D */  lw         $2, 0x220($9)
    /* D3924 001D3924 25004010 */  beqz       $2, .L001D39BC
    /* D3928 001D3928 30023025 */   addiu     $16, $9, 0x230
    /* D392C 001D392C 1E14040C */  jal        func_00105078
    /* D3930 001D3930 01007326 */   addiu     $19, $19, 0x1
    /* D3934 001D3934 40B6868F */  lw         $6, %gp_rel(D_0062C230)($28)
    /* D3938 001D3938 30004524 */  addiu      $5, $2, 0x30
    /* D393C 001D393C 5E17040C */  jal        MatrixDrive_TurnZObjectMatrixXY
    /* D3940 001D3940 7000A427 */   addiu     $4, $29, 0x70
    /* D3944 001D3944 2D280002 */  daddu      $5, $16, $0
    /* D3948 001D3948 6000A427 */  addiu      $4, $29, 0x60
    /* D394C 001D394C 6417040C */  jal        MatrixDrive_GetTurnXAngleZY
    /* D3950 001D3950 7000A627 */   addiu     $6, $29, 0x70
    /* D3954 001D3954 1614040C */  jal        func_00105058
    /* D3958 001D3958 6C00A0AF */   sw        $0, 0x6C($29)
    /* D395C 001D395C 1E14040C */  jal        func_00105078
    /* D3960 001D3960 00000000 */   nop
    /* D3964 001D3964 2414040C */  jal        func_00105090
    /* D3968 001D3968 2D804000 */   daddu     $16, $2, $0
    /* D396C 001D396C 2D200002 */  daddu      $4, $16, $0
    /* D3970 001D3970 1C17040C */  jal        MatrixDrive_TransMatrix
    /* D3974 001D3974 2D284000 */   daddu     $5, $2, $0
    /* D3978 001D3978 1E14040C */  jal        func_00105078
    /* D397C 001D397C 00000000 */   nop
    /* D3980 001D3980 2D284000 */  daddu      $5, $2, $0
    /* D3984 001D3984 5000A427 */  addiu      $4, $29, 0x50
    /* D3988 001D3988 76FF080C */  jal        func_0023FDD8
    /* D398C 001D398C 6000A627 */   addiu     $6, $29, 0x60
    /* D3990 001D3990 1A14040C */  jal        func_00105068
    /* D3994 001D3994 00000000 */   nop
    /* D3998 001D3998 5000ACC7 */  lwc1       $f12, 0x50($29)
    /* D399C 001D399C B400A427 */  addiu      $4, $29, 0xB4
    /* D39A0 001D39A0 5400ADC7 */  lwc1       $f13, 0x54($29)
    /* D39A4 001D39A4 B600A527 */  addiu      $5, $29, 0xB6
    /* D39A8 001D39A8 6E16040C */  jal        MatrixDrive_GetMatrix
    /* D39AC 001D39AC 5800AEC7 */   lwc1      $f14, 0x58($29)
    /* D39B0 001D39B0 B400A287 */  lh         $2, 0xB4($29)
    /* D39B4 001D39B4 40B6898F */  lw         $9, %gp_rel(D_0062C230)($28)
    /* D39B8 001D39B8 23904202 */  subu       $18, $18, $2
.align 2
  .L001D39BC:
    /* D39BC 001D39BC 0803228D */  lw         $2, 0x308($9)
.align 2
  .L001D39C0:
    /* D39C0 001D39C0 39004010 */  beqz       $2, .L001D3AA8
    /* D39C4 001D39C4 2D884002 */   daddu     $17, $18, $0
    /* D39C8 001D39C8 D002228D */  lw         $2, 0x2D0($9)
    /* D39CC 001D39CC 36004010 */  beqz       $2, .L001D3AA8
    /* D39D0 001D39D0 00000000 */   nop
    /* D39D4 001D39D4 1E14040C */  jal        func_00105078
    /* D39D8 001D39D8 E0023025 */   addiu     $16, $9, 0x2E0
    /* D39DC 001D39DC 40B6868F */  lw         $6, %gp_rel(D_0062C230)($28)
    /* D39E0 001D39E0 30004524 */  addiu      $5, $2, 0x30
    /* D39E4 001D39E4 5E17040C */  jal        MatrixDrive_TurnZObjectMatrixXY
    /* D39E8 001D39E8 D000A427 */   addiu     $4, $29, 0xD0
    /* D39EC 001D39EC 2D280002 */  daddu      $5, $16, $0
    /* D39F0 001D39F0 C000A427 */  addiu      $4, $29, 0xC0
    /* D39F4 001D39F4 6417040C */  jal        MatrixDrive_GetTurnXAngleZY
    /* D39F8 001D39F8 D000A627 */   addiu     $6, $29, 0xD0
    /* D39FC 001D39FC 1614040C */  jal        func_00105058
    /* D3A00 001D3A00 CC00A0AF */   sw        $0, 0xCC($29)
    /* D3A04 001D3A04 1E14040C */  jal        func_00105078
    /* D3A08 001D3A08 00000000 */   nop
    /* D3A0C 001D3A0C 2414040C */  jal        func_00105090
    /* D3A10 001D3A10 2D804000 */   daddu     $16, $2, $0
    /* D3A14 001D3A14 2D200002 */  daddu      $4, $16, $0
    /* D3A18 001D3A18 1C17040C */  jal        MatrixDrive_TransMatrix
    /* D3A1C 001D3A1C 2D284000 */   daddu     $5, $2, $0
    /* D3A20 001D3A20 1E14040C */  jal        func_00105078
    /* D3A24 001D3A24 00000000 */   nop
    /* D3A28 001D3A28 2D284000 */  daddu      $5, $2, $0
    /* D3A2C 001D3A2C 6000A427 */  addiu      $4, $29, 0x60
    /* D3A30 001D3A30 76FF080C */  jal        func_0023FDD8
    /* D3A34 001D3A34 C000A627 */   addiu     $6, $29, 0xC0
    /* D3A38 001D3A38 1A14040C */  jal        func_00105068
    /* D3A3C 001D3A3C 00000000 */   nop
    /* D3A40 001D3A40 6000ACC7 */  lwc1       $f12, 0x60($29)
    /* D3A44 001D3A44 E000A427 */  addiu      $4, $29, 0xE0
    /* D3A48 001D3A48 6400ADC7 */  lwc1       $f13, 0x64($29)
    /* D3A4C 001D3A4C E200A527 */  addiu      $5, $29, 0xE2
    /* D3A50 001D3A50 FA15040C */  jal        MatrixDrive_PushMatrixWithNoCopy
    /* D3A54 001D3A54 6800AEC7 */   lwc1      $f14, 0x68($29)
    /* D3A58 001D3A58 40B6908F */  lw         $16, %gp_rel(D_0062C230)($28)
    /* D3A5C 001D3A5C 02000324 */  addiu      $3, $0, 0x2
    /* D3A60 001D3A60 D002028E */  lw         $2, 0x2D0($16)
    /* D3A64 001D3A64 06004314 */  bne        $2, $3, .L001D3A80
    /* D3A68 001D3A68 E000A297 */   lhu       $2, 0xE0($29)
    /* D3A6C 001D3A6C E000A287 */  lh         $2, 0xE0($29)
    /* D3A70 001D3A70 E200B787 */  lh         $23, 0xE2($29)
    /* D3A74 001D3A74 21902202 */  addu       $18, $17, $2
    /* D3A78 001D3A78 0A000010 */  b          .L001D3AA4
    /* D3A7C 001D3A7C 2D884002 */   daddu     $17, $18, $0
.align 2
  .L001D3A80:
    /* D3A80 001D3A80 F0020486 */  lh         $4, 0x2F0($16)
    /* D3A84 001D3A84 00140200 */  sll        $2, $2, 16
    /* D3A88 001D3A88 F2021786 */  lh         $23, 0x2F2($16)
    /* D3A8C 001D3A8C C21F0200 */  srl        $3, $2, 31
    /* D3A90 001D3A90 21902402 */  addu       $18, $17, $4
    /* D3A94 001D3A94 03140200 */  sra        $2, $2, 16
    /* D3A98 001D3A98 21104300 */  addu       $2, $2, $3
    /* D3A9C 001D3A9C 43100200 */  sra        $2, $2, 1
    /* D3AA0 001D3AA0 21882202 */  addu       $17, $17, $2
.align 2
  .L001D3AA4:
    /* D3AA4 001D3AA4 01007326 */  addiu      $19, $19, 0x1
.align 2
  .L001D3AA8:
    /* D3AA8 001D3AA8 0A006052 */  beql       $19, $0, .L001D3AD4
    /* D3AAC 001D3AAC 0800AB96 */   lhu       $11, 0x8($21)
    /* D3AB0 001D3AB0 1A005302 */  div        $0, $18, $19
    /* D3AB4 001D3AB4 1A003372 */  div1       $0, $17, $19
    /* D3AB8 001D3AB8 01006052 */  beql       $19, $0, .L001D3AC0
    /* D3ABC 001D3ABC CD010000 */   break     0, 7
.align 2
  .L001D3AC0:
    /* D3AC0 001D3AC0 12100000 */  mflo       $2
    /* D3AC4 001D3AC4 12180070 */  mflo1      $3
    /* D3AC8 001D3AC8 2D904000 */  daddu      $18, $2, $0
    /* D3ACC 001D3ACC 2D886000 */  daddu      $17, $3, $0
    /* D3AD0 001D3AD0 0800AB96 */  lhu        $11, 0x8($21)
.align 2
  .L001D3AD4:
    /* D3AD4 001D3AD4 23801700 */  negu       $16, $23
    /* D3AD8 001D3AD8 00841000 */  sll        $16, $16, 16
    /* D3ADC 001D3ADC 0400A986 */  lh         $9, 0x4($21)
    /* D3AE0 001D3AE0 23580B00 */  negu       $11, $11
    /* D3AE4 001D3AE4 03841000 */  sra        $16, $16, 16
    /* D3AE8 001D3AE8 005C0B00 */  sll        $11, $11, 16
    /* D3AEC 001D3AEC 00441200 */  sll        $8, $18, 16
    /* D3AF0 001D3AF0 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* D3AF4 001D3AF4 00608144 */  mtc1       $1, $f12
    /* D3AF8 001D3AF8 2D500002 */  daddu      $10, $16, $0
    /* D3AFC 001D3AFC A001A78F */  lw         $7, 0x1A0($29)
    /* D3B00 001D3B00 03440800 */  sra        $8, $8, 16
    /* D3B04 001D3B04 035C0B00 */  sra        $11, $11, 16
    /* D3B08 001D3B08 0000A0AF */  sw         $0, 0x0($29)
    /* D3B0C 001D3B0C E400A427 */  addiu      $4, $29, 0xE4
    /* D3B10 001D3B10 0800A0AF */  sw         $0, 0x8($29)
    /* D3B14 001D3B14 E600A527 */  addiu      $5, $29, 0xE6
    /* D3B18 001D3B18 B648070C */  jal        AddMotionMemorySize
    /* D3B1C 001D3B1C E800A627 */   addiu     $6, $29, 0xE8
    /* D3B20 001D3B20 2000B226 */  addiu      $18, $21, 0x20
    /* D3B24 001D3B24 0800AB96 */  lhu        $11, 0x8($21)
    /* D3B28 001D3B28 00441100 */  sll        $8, $17, 16
    /* D3B2C 001D3B2C 0400A986 */  lh         $9, 0x4($21)
    /* D3B30 001D3B30 2D500002 */  daddu      $10, $16, $0
    /* D3B34 001D3B34 23580B00 */  negu       $11, $11
    /* D3B38 001D3B38 A001A78F */  lw         $7, 0x1A0($29)
    /* D3B3C 001D3B3C 005C0B00 */  sll        $11, $11, 16
    /* D3B40 001D3B40 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* D3B44 001D3B44 00608144 */  mtc1       $1, $f12
    /* D3B48 001D3B48 03440800 */  sra        $8, $8, 16
    /* D3B4C 001D3B4C 035C0B00 */  sra        $11, $11, 16
    /* D3B50 001D3B50 0000A0AF */  sw         $0, 0x0($29)
    /* D3B54 001D3B54 EA00A427 */  addiu      $4, $29, 0xEA
    /* D3B58 001D3B58 0800A0AF */  sw         $0, 0x8($29)
    /* D3B5C 001D3B5C EC00A527 */  addiu      $5, $29, 0xEC
    /* D3B60 001D3B60 B648070C */  jal        AddMotionMemorySize
    /* D3B64 001D3B64 EE00A627 */   addiu     $6, $29, 0xEE
    /* D3B68 001D3B68 EC00A287 */  lh         $2, 0xEC($29)
    /* D3B6C 001D3B6C 7000B027 */  addiu      $16, $29, 0x70
    /* D3B70 001D3B70 2D200002 */  daddu      $4, $16, $0
    /* D3B74 001D3B74 23100200 */  negu       $2, $2
    /* D3B78 001D3B78 3036040C */  jal        GetMatrixFromQuaternion
    /* D3B7C 001D3B7C EC00A2A7 */   sh        $2, 0xEC($29)
    /* D3B80 001D3B80 E400A597 */  lhu        $5, 0xE4($29)
    /* D3B84 001D3B84 2D200002 */  daddu      $4, $16, $0
    /* D3B88 001D3B88 23280500 */  negu       $5, $5
    /* D3B8C 001D3B8C 002C0500 */  sll        $5, $5, 16
    /* D3B90 001D3B90 1239040C */  jal        func_0010E448
    /* D3B94 001D3B94 032C0500 */   sra       $5, $5, 16
    /* D3B98 001D3B98 EC00A597 */  lhu        $5, 0xEC($29)
    /* D3B9C 001D3B9C 2D200002 */  daddu      $4, $16, $0
    /* D3BA0 001D3BA0 23280500 */  negu       $5, $5
    /* D3BA4 001D3BA4 002C0500 */  sll        $5, $5, 16
    /* D3BA8 001D3BA8 6239040C */  jal        func_0010E588
    /* D3BAC 001D3BAC 032C0500 */   sra       $5, $5, 16
    /* D3BB0 001D3BB0 E800A597 */  lhu        $5, 0xE8($29)
    /* D3BB4 001D3BB4 2D200002 */  daddu      $4, $16, $0
    /* D3BB8 001D3BB8 23280500 */  negu       $5, $5
    /* D3BBC 001D3BBC 002C0500 */  sll        $5, $5, 16
    /* D3BC0 001D3BC0 3A39040C */  jal        func_0010E4E8
    /* D3BC4 001D3BC4 032C0500 */   sra       $5, $5, 16
    /* D3BC8 001D3BC8 8C37040C */  jal        GetLastQuaternion
    /* D3BCC 001D3BCC C000B127 */   addiu     $17, $29, 0xC0
    /* D3BD0 001D3BD0 2D300002 */  daddu      $6, $16, $0
    /* D3BD4 001D3BD4 2D202002 */  daddu      $4, $17, $0
    /* D3BD8 001D3BD8 5238040C */  jal        func_0010E148
    /* D3BDC 001D3BDC 2D284000 */   daddu     $5, $2, $0
    /* D3BE0 001D3BE0 D000B027 */  addiu      $16, $29, 0xD0
    /* D3BE4 001D3BE4 2D282002 */  daddu      $5, $17, $0
    /* D3BE8 001D3BE8 2D200002 */  daddu      $4, $16, $0
    /* D3BEC 001D3BEC 6238040C */  jal        func_0010E188
    /* D3BF0 001D3BF0 2D308002 */   daddu     $6, $20, $0
    /* D3BF4 001D3BF4 40B6828F */  lw         $2, %gp_rel(D_0062C230)($28)
    /* D3BF8 001D3BF8 F000B127 */  addiu      $17, $29, 0xF0
    /* D3BFC 001D3BFC 2700033C */  lui        $3, %hi(D_002724B0)
    /* D3C00 001D3C00 2D280002 */  daddu      $5, $16, $0
    /* D3C04 001D3C04 B4034CC4 */  lwc1       $f12, 0x3B4($2)
    /* D3C08 001D3C08 B0246624 */  addiu      $6, $3, %lo(D_002724B0)
    /* D3C0C 001D3C0C 8237040C */  jal        GetCurrentQuaternion
    /* D3C10 001D3C10 2D202002 */   daddu     $4, $17, $0
    /* D3C14 001D3C14 40B6828F */  lw         $2, %gp_rel(D_0062C230)($28)
    /* D3C18 001D3C18 2D282002 */  daddu      $5, $17, $0
    /* D3C1C 001D3C1C 2D204002 */  daddu      $4, $18, $0
    /* D3C20 001D3C20 2D304002 */  daddu      $6, $18, $0
    /* D3C24 001D3C24 8237040C */  jal        GetCurrentQuaternion
    /* D3C28 001D3C28 B8034CC4 */   lwc1      $f12, 0x3B8($2)
    /* D3C2C 001D3C2C 2D304002 */  daddu      $6, $18, $0
    /* D3C30 001D3C30 2D208002 */  daddu      $4, $20, $0
    /* D3C34 001D3C34 5238040C */  jal        func_0010E148
    /* D3C38 001D3C38 2D288002 */   daddu     $5, $20, $0
    /* D3C3C 001D3C3C 0237040C */  jal        GetSlerpQuaternionNoRegularize
    /* D3C40 001D3C40 2D208002 */   daddu     $4, $20, $0
    /* D3C44 001D3C44 8C37040C */  jal        GetLastQuaternion
    /* D3C48 001D3C48 00000000 */   nop
    /* D3C4C 001D3C4C 2D20C003 */  daddu      $4, $30, $0
    /* D3C50 001D3C50 2D288002 */  daddu      $5, $20, $0
    /* D3C54 001D3C54 6238040C */  jal        func_0010E188
    /* D3C58 001D3C58 2D304000 */   daddu     $6, $2, $0
    /* D3C5C 001D3C5C EC00A287 */  lh         $2, 0xEC($29)
    /* D3C60 001D3C60 0800A386 */  lh         $3, 0x8($21)
    /* D3C64 001D3C64 40B6858F */  lw         $5, %gp_rel(D_0062C230)($28)
    /* D3C68 001D3C68 23104300 */  subu       $2, $2, $3
    /* D3C6C 001D3C6C 0E00A486 */  lh         $4, 0xE($21)
    /* D3C70 001D3C70 00008244 */  mtc1       $2, $f0
    /* D3C74 001D3C74 20008046 */  cvt.s.w    $f0, $f0
    /* D3C78 001D3C78 B403A2C4 */  lwc1       $f2, 0x3B4($5)
    /* D3C7C 001D3C7C 00088444 */  mtc1       $4, $f1
    /* D3C80 001D3C80 60088046 */  cvt.s.w    $f1, $f1
    /* D3C84 001D3C84 B803A3C4 */  lwc1       $f3, 0x3B8($5)
    /* D3C88 001D3C88 0800A496 */  lhu        $4, 0x8($21)
    /* D3C8C 001D3C8C 02000246 */  mul.s      $f0, $f0, $f2
    /* D3C90 001D3C90 0000A4C6 */  lwc1       $f4, 0x0($21)
    /* D3C94 001D3C94 01000146 */  sub.s      $f0, $f0, $f1
    /* D3C98 001D3C98 02000346 */  mul.s      $f0, $f0, $f3
    /* D3C9C 001D3C9C 40080046 */  add.s      $f1, $f1, $f0
    /* D3CA0 001D3CA0 24080046 */  .word      0x46000824                    # cvt.w.s    $f0, $f1 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* D3CA4 001D3CA4 00000344 */  mfc1       $3, $f0
    /* D3CA8 001D3CA8 21208300 */  addu       $4, $4, $3
    /* D3CAC 001D3CAC 0E00A3A6 */  sh         $3, 0xE($21)
    /* D3CB0 001D3CB0 00140400 */  sll        $2, $4, 16
    /* D3CB4 001D3CB4 0800A4A6 */  sh         $4, 0x8($21)
    /* D3CB8 001D3CB8 03140200 */  sra        $2, $2, 16
    /* D3CBC 001D3CBC 00008244 */  mtc1       $2, $f0
    /* D3CC0 001D3CC0 20008046 */  cvt.s.w    $f0, $f0
    /* D3CC4 001D3CC4 02000446 */  mul.s      $f0, $f0, $f4
    /* D3CC8 001D3CC8 64000046 */  .word      0x46000064                    # cvt.w.s    $f1, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* D3CCC 001D3CCC 00080244 */  mfc1       $2, $f1
    /* D3CD0 001D3CD0 F402A2A4 */  sh         $2, 0x2F4($5)
.align 2
  .L001D3CD4:
    /* D3CD4 001D3CD4 8C37040C */  jal        GetLastQuaternion
    /* D3CD8 001D3CD8 00000000 */   nop
    /* D3CDC 001D3CDC 40B6838F */  lw         $3, %gp_rel(D_0062C230)($28)
    /* D3CE0 001D3CE0 2D204000 */  daddu      $4, $2, $0
    /* D3CE4 001D3CE4 2040013C */  lui        $1, (0x40200000 >> 16)
    /* D3CE8 001D3CE8 00088144 */  mtc1       $1, $f1
    /* D3CEC 001D3CEC 50006284 */  lh         $2, 0x50($3)
    /* D3CF0 001D3CF0 00008244 */  mtc1       $2, $f0
    /* D3CF4 001D3CF4 20008046 */  cvt.s.w    $f0, $f0
    /* D3CF8 001D3CF8 02000146 */  mul.s      $f0, $f0, $f1
    /* D3CFC 001D3CFC 64000046 */  .word      0x46000064                    # cvt.w.s    $f1, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* D3D00 001D3D00 00080544 */  mfc1       $5, $f1
    /* D3D04 001D3D04 002C0500 */  sll        $5, $5, 16
    /* D3D08 001D3D08 1239040C */  jal        func_0010E448
    /* D3D0C 001D3D0C 032C0500 */   sra       $5, $5, 16
    /* D3D10 001D3D10 8C37040C */  jal        GetLastQuaternion
    /* D3D14 001D3D14 00000000 */   nop
    /* D3D18 001D3D18 8C37040C */  jal        GetLastQuaternion
    /* D3D1C 001D3D1C 2D804000 */   daddu     $16, $2, $0
    /* D3D20 001D3D20 0000ACC6 */  lwc1       $f12, 0x0($21)
    /* D3D24 001D3D24 2D200002 */  daddu      $4, $16, $0
    /* D3D28 001D3D28 2D28C002 */  daddu      $5, $22, $0
    /* D3D2C 001D3D2C 8237040C */  jal        GetCurrentQuaternion
    /* D3D30 001D3D30 2D304000 */   daddu     $6, $2, $0
    /* D3D34 001D3D34 8C37040C */  jal        GetLastQuaternion
    /* D3D38 001D3D38 00000000 */   nop
    /* D3D3C 001D3D3C 40B6908F */  lw         $16, %gp_rel(D_0062C230)($28)
    /* D3D40 001D3D40 2D884000 */  daddu      $17, $2, $0
    /* D3D44 001D3D44 8C37040C */  jal        GetLastQuaternion
    /* D3D48 001D3D48 C0021026 */   addiu     $16, $16, 0x2C0
    /* D3D4C 001D3D4C 2D280002 */  daddu      $5, $16, $0
    /* D3D50 001D3D50 2D202002 */  daddu      $4, $17, $0
    /* D3D54 001D3D54 5238040C */  jal        func_0010E148
    /* D3D58 001D3D58 2D304000 */   daddu     $6, $2, $0
    /* D3D5C 001D3D5C 1E14040C */  jal        func_00105078
    /* D3D60 001D3D60 00000000 */   nop
    /* D3D64 001D3D64 8C37040C */  jal        GetLastQuaternion
    /* D3D68 001D3D68 2D804000 */   daddu     $16, $2, $0
    /* D3D6C 001D3D6C 2D200002 */  daddu      $4, $16, $0
    /* D3D70 001D3D70 7438040C */  jal        func_0010E1D0
    /* D3D74 001D3D74 2D284000 */   daddu     $5, $2, $0
    /* D3D78 001D3D78 7000103C */  lui        $16, %hi(D_00703020)
    /* D3D7C 001D3D7C 1E14040C */  jal        func_00105078
    /* D3D80 001D3D80 20301026 */   addiu     $16, $16, %lo(D_00703020)
    /* D3D84 001D3D84 2700063C */  lui        $6, %hi(D_00271BF0)
    /* D3D88 001D3D88 2D200002 */  daddu      $4, $16, $0
    /* D3D8C 001D3D8C 2D284000 */  daddu      $5, $2, $0
    /* D3D90 001D3D90 9C62040C */  jal        func_00118A70
    /* D3D94 001D3D94 F01BC624 */   addiu     $6, $6, %lo(D_00271BF0)
    /* D3D98 001D3D98 67060010 */  b          .L001D5738
    /* D3D9C 001D3D9C 6002BFDF */   ld        $31, 0x260($29)
.align 2
  jlabel .L001D3DA0
    /* D3DA0 001D3DA0 8C37040C */  jal        GetLastQuaternion
    /* D3DA4 001D3DA4 2000D227 */   addiu     $18, $30, 0x20
    /* D3DA8 001D3DA8 9237040C */  jal        GetTableSin
    /* D3DAC 001D3DAC 2D804000 */   daddu     $16, $2, $0
    /* D3DB0 001D3DB0 2D200002 */  daddu      $4, $16, $0
    /* D3DB4 001D3DB4 2D284000 */  daddu      $5, $2, $0
    /* D3DB8 001D3DB8 5238040C */  jal        func_0010E148
    /* D3DBC 001D3DBC 2D304002 */   daddu     $6, $18, $0
    /* D3DC0 001D3DC0 1E14040C */  jal        func_00105078
    /* D3DC4 001D3DC4 00000000 */   nop
    /* D3DC8 001D3DC8 8C37040C */  jal        GetLastQuaternion
    /* D3DCC 001D3DCC 2D804000 */   daddu     $16, $2, $0
    /* D3DD0 001D3DD0 2D200002 */  daddu      $4, $16, $0
    /* D3DD4 001D3DD4 7438040C */  jal        func_0010E1D0
    /* D3DD8 001D3DD8 2D284000 */   daddu     $5, $2, $0
    /* D3DDC 001D3DDC 3000B027 */  addiu      $16, $29, 0x30
    /* D3DE0 001D3DE0 2700053C */  lui        $5, %hi(D_002724B0)
    /* D3DE4 001D3DE4 2D200002 */  daddu      $4, $16, $0
    /* D3DE8 001D3DE8 F036040C */  jal        GetInverseQuaternion
    /* D3DEC 001D3DEC B024A524 */   addiu     $5, $5, %lo(D_002724B0)
    /* D3DF0 001D3DF0 2000B127 */  addiu      $17, $29, 0x20
    /* D3DF4 001D3DF4 1000C526 */  addiu      $5, $22, 0x10
    /* D3DF8 001D3DF8 2D304002 */  daddu      $6, $18, $0
    /* D3DFC 001D3DFC 6238040C */  jal        func_0010E188
    /* D3E00 001D3E00 2D202002 */   daddu     $4, $17, $0
    /* D3E04 001D3E04 2D200002 */  daddu      $4, $16, $0
    /* D3E08 001D3E08 2D280002 */  daddu      $5, $16, $0
    /* D3E0C 001D3E0C 5238040C */  jal        func_0010E148
    /* D3E10 001D3E10 2D302002 */   daddu     $6, $17, $0
    /* D3E14 001D3E14 DC35040C */  jal        InvertCurrentQuaternion
    /* D3E18 001D3E18 2D200002 */   daddu     $4, $16, $0
    /* D3E1C 001D3E1C 2D060010 */  b          .L001D56D4
    /* D3E20 001D3E20 00000000 */   nop
.align 2
  jlabel .L001D3E24
    /* D3E24 001D3E24 8C37040C */  jal        GetLastQuaternion
    /* D3E28 001D3E28 2000D127 */   addiu     $17, $30, 0x20
    /* D3E2C 001D3E2C 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* D3E30 001D3E30 00A08144 */  mtc1       $1, $f20
    /* D3E34 001D3E34 9237040C */  jal        GetTableSin
    /* D3E38 001D3E38 2D804000 */   daddu     $16, $2, $0
    /* D3E3C 001D3E3C 2D200002 */  daddu      $4, $16, $0
    /* D3E40 001D3E40 2D284000 */  daddu      $5, $2, $0
    /* D3E44 001D3E44 5238040C */  jal        func_0010E148
    /* D3E48 001D3E48 2D302002 */   daddu     $6, $17, $0
    /* D3E4C 001D3E4C 1E14040C */  jal        func_00105078
    /* D3E50 001D3E50 00000000 */   nop
    /* D3E54 001D3E54 8C37040C */  jal        GetLastQuaternion
    /* D3E58 001D3E58 2D804000 */   daddu     $16, $2, $0
    /* D3E5C 001D3E5C 2D200002 */  daddu      $4, $16, $0
    /* D3E60 001D3E60 7438040C */  jal        func_0010E1D0
    /* D3E64 001D3E64 2D284000 */   daddu     $5, $2, $0
    /* D3E68 001D3E68 3000A227 */  addiu      $2, $29, 0x30
    /* D3E6C 001D3E6C 2700033C */  lui        $3, %hi(D_002724B0)
    /* D3E70 001D3E70 A401A2AF */  sw         $2, 0x1A4($29)
    /* D3E74 001D3E74 B0246524 */  addiu      $5, $3, %lo(D_002724B0)
    /* D3E78 001D3E78 F036040C */  jal        GetInverseQuaternion
    /* D3E7C 001D3E7C 2D204000 */   daddu     $4, $2, $0
    /* D3E80 001D3E80 2000A227 */  addiu      $2, $29, 0x20
    /* D3E84 001D3E84 1000C526 */  addiu      $5, $22, 0x10
    /* D3E88 001D3E88 A801A2AF */  sw         $2, 0x1A8($29)
    /* D3E8C 001D3E8C 2D302002 */  daddu      $6, $17, $0
    /* D3E90 001D3E90 6238040C */  jal        func_0010E188
    /* D3E94 001D3E94 2D204000 */   daddu     $4, $2, $0
    /* D3E98 001D3E98 A000B227 */  addiu      $18, $29, 0xA0
    /* D3E9C 001D3E9C 2D280000 */  daddu      $5, $0, $0
    /* D3EA0 001D3EA0 2D204002 */  daddu      $4, $18, $0
    /* D3EA4 001D3EA4 5A81090C */  jal        func_00260568
    /* D3EA8 001D3EA8 10000624 */   addiu     $6, $0, 0x10
    /* D3EAC 001D3EAC 40B6908F */  lw         $16, %gp_rel(D_0062C230)($28)
    /* D3EB0 001D3EB0 AC00B4E7 */  swc1       $f20, 0xAC($29)
    /* D3EB4 001D3EB4 1E14040C */  jal        func_00105078
    /* D3EB8 001D3EB8 90021026 */   addiu     $16, $16, 0x290
    /* D3EBC 001D3EBC 40B6868F */  lw         $6, %gp_rel(D_0062C230)($28)
    /* D3EC0 001D3EC0 30004524 */  addiu      $5, $2, 0x30
    /* D3EC4 001D3EC4 5E17040C */  jal        MatrixDrive_TurnZObjectMatrixXY
    /* D3EC8 001D3EC8 7000A427 */   addiu     $4, $29, 0x70
    /* D3ECC 001D3ECC 2D280002 */  daddu      $5, $16, $0
    /* D3ED0 001D3ED0 6000A427 */  addiu      $4, $29, 0x60
    /* D3ED4 001D3ED4 6417040C */  jal        MatrixDrive_GetTurnXAngleZY
    /* D3ED8 001D3ED8 7000A627 */   addiu     $6, $29, 0x70
    /* D3EDC 001D3EDC 1614040C */  jal        func_00105058
    /* D3EE0 001D3EE0 6C00A0AF */   sw        $0, 0x6C($29)
    /* D3EE4 001D3EE4 1E14040C */  jal        func_00105078
    /* D3EE8 001D3EE8 00000000 */   nop
    /* D3EEC 001D3EEC 2414040C */  jal        func_00105090
    /* D3EF0 001D3EF0 2D804000 */   daddu     $16, $2, $0
    /* D3EF4 001D3EF4 2D200002 */  daddu      $4, $16, $0
    /* D3EF8 001D3EF8 1C17040C */  jal        MatrixDrive_TransMatrix
    /* D3EFC 001D3EFC 2D284000 */   daddu     $5, $2, $0
    /* D3F00 001D3F00 1E14040C */  jal        func_00105078
    /* D3F04 001D3F04 00000000 */   nop
    /* D3F08 001D3F08 2D284000 */  daddu      $5, $2, $0
    /* D3F0C 001D3F0C C000A427 */  addiu      $4, $29, 0xC0
    /* D3F10 001D3F10 76FF080C */  jal        func_0023FDD8
    /* D3F14 001D3F14 6000A627 */   addiu     $6, $29, 0x60
    /* D3F18 001D3F18 1A14040C */  jal        func_00105068
    /* D3F1C 001D3F1C 00000000 */   nop
    /* D3F20 001D3F20 C000ACC7 */  lwc1       $f12, 0xC0($29)
    /* D3F24 001D3F24 0401A427 */  addiu      $4, $29, 0x104
    /* D3F28 001D3F28 C400ADC7 */  lwc1       $f13, 0xC4($29)
    /* D3F2C 001D3F2C 0601A527 */  addiu      $5, $29, 0x106
    /* D3F30 001D3F30 8A15040C */  jal        MatrixDrive_ScaleMatrix
    /* D3F34 001D3F34 C800AEC7 */   lwc1      $f14, 0xC8($29)
    /* D3F38 001D3F38 01000224 */  addiu      $2, $0, 0x1
    /* D3F3C 001D3F3C 0401A887 */  lh         $8, 0x104($29)
    /* D3F40 001D3F40 0601AA87 */  lh         $10, 0x106($29)
    /* D3F44 001D3F44 06A30046 */  mov.s      $f12, $f20
    /* D3F48 001D3F48 A001A78F */  lw         $7, 0x1A0($29)
    /* D3F4C 001D3F4C 0801A427 */  addiu      $4, $29, 0x108
    /* D3F50 001D3F50 0000A2AF */  sw         $2, 0x0($29)
    /* D3F54 001D3F54 0A01A527 */  addiu      $5, $29, 0x10A
    /* D3F58 001D3F58 0800A0AF */  sw         $0, 0x8($29)
    /* D3F5C 001D3F5C 0C01A627 */  addiu      $6, $29, 0x10C
    /* D3F60 001D3F60 2D480000 */  daddu      $9, $0, $0
    /* D3F64 001D3F64 B648070C */  jal        AddMotionMemorySize
    /* D3F68 001D3F68 2D580000 */   daddu     $11, $0, $0
    /* D3F6C 001D3F6C 40B6828F */  lw         $2, %gp_rel(D_0062C230)($28)
    /* D3F70 001D3F70 8402438C */  lw         $3, 0x284($2)
    /* D3F74 001D3F74 05006010 */  beqz       $3, .L001D3F8C
    /* D3F78 001D3F78 5000A427 */   addiu     $4, $29, 0x50
    /* D3F7C 001D3F7C C661040C */  jal        _SetCurrentMatrix
    /* D3F80 001D3F80 C000A527 */   addiu     $5, $29, 0xC0
    /* D3F84 001D3F84 14000010 */  b          .L001D3FD8
    /* D3F88 001D3F88 2700033C */   lui       $3, %hi(D_00271BF0)
.align 2
  .L001D3F8C:
    /* D3F8C 001D3F8C 0A01B187 */  lh         $17, 0x10A($29)
    /* D3F90 001D3F90 0801B087 */  lh         $16, 0x108($29)
    /* D3F94 001D3F94 4C3B040C */  jal        func_0010ED30
    /* D3F98 001D3F98 2D202002 */   daddu     $4, $17, $0
    /* D3F9C 001D3F9C 06050046 */  mov.s      $f20, $f0
    /* D3FA0 001D3FA0 4C3B040C */  jal        func_0010ED30
    /* D3FA4 001D3FA4 2D200002 */   daddu     $4, $16, $0
    /* D3FA8 001D3FA8 02001446 */  mul.s      $f0, $f0, $f20
    /* D3FAC 001D3FAC 2D200002 */  daddu      $4, $16, $0
    /* D3FB0 001D3FB0 383B040C */  jal        p2o_SetDefaultEnviroment
    /* D3FB4 001D3FB4 5000A0E7 */   swc1      $f0, 0x50($29)
    /* D3FB8 001D3FB8 02001446 */  mul.s      $f0, $f0, $f20
    /* D3FBC 001D3FBC 2D202002 */  daddu      $4, $17, $0
    /* D3FC0 001D3FC0 383B040C */  jal        p2o_SetDefaultEnviroment
    /* D3FC4 001D3FC4 5400A0E7 */   swc1      $f0, 0x54($29)
    /* D3FC8 001D3FC8 07000046 */  neg.s      $f0, $f0
    /* D3FCC 001D3FCC 5C00A0AF */  sw         $0, 0x5C($29)
    /* D3FD0 001D3FD0 5800A0E7 */  swc1       $f0, 0x58($29)
    /* D3FD4 001D3FD4 2700033C */  lui        $3, %hi(D_00271BF0)
.align 2
  .L001D3FD8:
    /* D3FD8 001D3FD8 5000A427 */  addiu      $4, $29, 0x50
    /* D3FDC 001D3FDC F01B7024 */  addiu      $16, $3, %lo(D_00271BF0)
    /* D3FE0 001D3FE0 D261040C */  jal        _MulCurrentMatrixR
    /* D3FE4 001D3FE4 2D280002 */   daddu     $5, $16, $0
    /* D3FE8 001D3FE8 BC3B040C */  jal        func_0010EEF0
    /* D3FEC 001D3FEC 06030046 */   mov.s     $f12, $f0
    /* D3FF0 001D3FF0 2D884000 */  daddu      $17, $2, $0
    /* D3FF4 001D3FF4 2D300002 */  daddu      $6, $16, $0
    /* D3FF8 001D3FF8 6000A427 */  addiu      $4, $29, 0x60
    /* D3FFC 001D3FFC DE61040C */  jal        _MulCurrentMatrixL
    /* D4000 001D4000 5000A527 */   addiu     $5, $29, 0x50
    /* D4004 001D4004 2D282002 */  daddu      $5, $17, $0
    /* D4008 001D4008 D000A427 */  addiu      $4, $29, 0xD0
    /* D400C 001D400C 2238040C */  jal        func_0010E088
    /* D4010 001D4010 6000A627 */   addiu     $6, $29, 0x60
    /* D4014 001D4014 A000A427 */  addiu      $4, $29, 0xA0
    /* D4018 001D4018 D000A627 */  addiu      $6, $29, 0xD0
    /* D401C 001D401C 5238040C */  jal        func_0010E148
    /* D4020 001D4020 2D288000 */   daddu     $5, $4, $0
    /* D4024 001D4024 40B6868F */  lw         $6, %gp_rel(D_0062C230)($28)
    /* D4028 001D4028 01000224 */  addiu      $2, $0, 0x1
    /* D402C 001D402C 8002C38C */  lw         $3, 0x280($6)
    /* D4030 001D4030 11006210 */  beq        $3, $2, .L001D4078
    /* D4034 001D4034 02000224 */   addiu     $2, $0, 0x2
    /* D4038 001D4038 F7006210 */  beq        $3, $2, .L001D4418
    /* D403C 001D403C F000B427 */   addiu     $20, $29, 0xF0
    /* D4040 001D4040 A801A58F */  lw         $5, 0x1A8($29)
    /* D4044 001D4044 F036040C */  jal        GetInverseQuaternion
    /* D4048 001D4048 2D208002 */   daddu     $4, $20, $0
    /* D404C 001D404C 1000B626 */  addiu      $22, $21, 0x10
    /* D4050 001D4050 40B6848F */  lw         $4, %gp_rel(D_0062C230)($28)
    /* D4054 001D4054 2700023C */  lui        $2, %hi(D_002724B0)
    /* D4058 001D4058 D4898CC7 */  lwc1       $f12, %gp_rel(D_006295C4)($28)
    /* D405C 001D405C B0244624 */  addiu      $6, $2, %lo(D_002724B0)
    /* D4060 001D4060 C0028424 */  addiu      $4, $4, 0x2C0
    /* D4064 001D4064 8237040C */  jal        GetCurrentQuaternion
    /* D4068 001D4068 2D288000 */   daddu     $5, $4, $0
    /* D406C 001D406C 6000A327 */  addiu      $3, $29, 0x60
    /* D4070 001D4070 FB000010 */  b          .L001D4460
    /* D4074 001D4074 B801A3AF */   sw        $3, 0x1B8($29)
.align 2
  .L001D4078:
    /* D4078 001D4078 C000A427 */  addiu      $4, $29, 0xC0
    /* D407C 001D407C 8017040C */  jal        MatrixDrive_GetTurnYEAngleXZ
    /* D4080 001D4080 2D880000 */   daddu     $17, $0, $0
    /* D4084 001D4084 3000C48F */  lw         $4, 0x30($30)
    /* D4088 001D4088 FFFF0224 */  addiu      $2, $0, -0x1
    /* D408C 001D408C 1F008210 */  beq        $4, $2, .L001D410C
    /* D4090 001D4090 86050046 */   mov.s     $f22, $f0
    /* D4094 001D4094 6000A227 */  addiu      $2, $29, 0x60
    /* D4098 001D4098 2001A327 */  addiu      $3, $29, 0x120
    /* D409C 001D409C B801A2AF */  sw         $2, 0x1B8($29)
    /* D40A0 001D40A0 1000B626 */  addiu      $22, $21, 0x10
    /* D40A4 001D40A4 BC01A3AF */  sw         $3, 0x1BC($29)
    /* D40A8 001D40A8 7000B327 */  addiu      $19, $29, 0x70
    /* D40AC 001D40AC F000B427 */  addiu      $20, $29, 0xF0
    /* D40B0 001D40B0 1001B727 */  addiu      $23, $29, 0x110
    /* D40B4 001D40B4 3001B227 */  addiu      $18, $29, 0x130
    /* D40B8 001D40B8 68AB838F */  lw         $3, %gp_rel(D_0062B758)($28)
    /* D40BC 001D40BC 00000000 */  nop
.align 2
  .L001D40C0:
    /* D40C0 001D40C0 80110400 */  sll        $2, $4, 6
    /* D40C4 001D40C4 21806200 */  addu       $16, $3, $2
    /* D40C8 001D40C8 8017040C */  jal        MatrixDrive_GetTurnYEAngleXZ
    /* D40CC 001D40CC 10000426 */   addiu     $4, $16, 0x10
    /* D40D0 001D40D0 30AB81C7 */  lwc1       $f1, %gp_rel(D_0062B720)($28)
    /* D40D4 001D40D4 80101100 */  sll        $2, $17, 2
    /* D40D8 001D40D8 B801A38F */  lw         $3, 0x1B8($29)
    /* D40DC 001D40DC 01003126 */  addiu      $17, $17, 0x1
    /* D40E0 001D40E0 42080046 */  mul.s      $f1, $f1, $f0
    /* D40E4 001D40E4 21106200 */  addu       $2, $3, $2
    /* D40E8 001D40E8 0200232A */  slti       $3, $17, 0x2
    /* D40EC 001D40EC 10006010 */  beqz       $3, .L001D4130
    /* D40F0 001D40F0 000041E4 */   swc1      $f1, 0x0($2)
    /* D40F4 001D40F4 3000048E */  lw         $4, 0x30($16)
    /* D40F8 001D40F8 FFFF0224 */  addiu      $2, $0, -0x1
    /* D40FC 001D40FC F0FF8214 */  bne        $4, $2, .L001D40C0
    /* D4100 001D4100 68AB838F */   lw        $3, %gp_rel(D_0062B758)($28)
    /* D4104 001D4104 0B000010 */  b          .L001D4134
    /* D4108 001D4108 2700023C */   lui       $2, %hi(D_00271BF0)
.align 2
  .L001D410C:
    /* D410C 001D410C 6000A227 */  addiu      $2, $29, 0x60
    /* D4110 001D4110 2001A327 */  addiu      $3, $29, 0x120
    /* D4114 001D4114 B801A2AF */  sw         $2, 0x1B8($29)
    /* D4118 001D4118 1000B626 */  addiu      $22, $21, 0x10
    /* D411C 001D411C BC01A3AF */  sw         $3, 0x1BC($29)
    /* D4120 001D4120 7000B327 */  addiu      $19, $29, 0x70
    /* D4124 001D4124 F000B427 */  addiu      $20, $29, 0xF0
    /* D4128 001D4128 1001B727 */  addiu      $23, $29, 0x110
    /* D412C 001D412C 3001B227 */  addiu      $18, $29, 0x130
.align 2
  .L001D4130:
    /* D4130 001D4130 2700023C */  lui        $2, %hi(D_00271BF0)
.align 2
  .L001D4134:
    /* D4134 001D4134 6CAB848F */  lw         $4, %gp_rel(D_0062B75C)($28)
    /* D4138 001D4138 F01B5124 */  addiu      $17, $2, %lo(D_00271BF0)
    /* D413C 001D413C 9627040C */  jal        DebugDisp1CollisionWithColor
    /* D4140 001D4140 20000524 */   addiu     $5, $0, 0x20
    /* D4144 001D4144 00A88044 */  mtc1       $0, $f21
    /* D4148 001D4148 68AB848F */  lw         $4, %gp_rel(D_0062B758)($28)
    /* D414C 001D414C 80110200 */  sll        $2, $2, 6
    /* D4150 001D4150 21208200 */  addu       $4, $4, $2
    /* D4154 001D4154 8017040C */  jal        MatrixDrive_GetTurnYEAngleXZ
    /* D4158 001D4158 10008424 */   addiu     $4, $4, 0x10
    /* D415C 001D415C 30AB81C7 */  lwc1       $f1, %gp_rel(D_0062B720)($28)
    /* D4160 001D4160 6400A2C7 */  lwc1       $f2, 0x64($29)
    /* D4164 001D4164 42080046 */  mul.s      $f1, $f1, $f0
    /* D4168 001D4168 80100146 */  add.s      $f2, $f2, $f1
    /* D416C 001D416C 1614040C */  jal        func_00105058
    /* D4170 001D4170 6400A2E7 */   swc1      $f2, 0x64($29)
    /* D4174 001D4174 6CAB848F */  lw         $4, %gp_rel(D_0062B75C)($28)
    /* D4178 001D4178 9627040C */  jal        DebugDisp1CollisionWithColor
    /* D417C 001D417C 16000524 */   addiu     $5, $0, 0x16
    /* D4180 001D4180 1E14040C */  jal        func_00105078
    /* D4184 001D4184 2D804000 */   daddu     $16, $2, $0
    /* D4188 001D4188 28B6858F */  lw         $5, %gp_rel(D_0062C218)($28)
    /* D418C 001D418C 40811000 */  sll        $16, $16, 5
    /* D4190 001D4190 2D204000 */  daddu      $4, $2, $0
    /* D4194 001D4194 2128B000 */  addu       $5, $5, $16
    /* D4198 001D4198 3436040C */  jal        getQuaternionFromMatrix
    /* D419C 001D419C 1000A524 */   addiu     $5, $5, 0x10
    /* D41A0 001D41A0 A040013C */  lui        $1, (0x40A00000 >> 16)
    /* D41A4 001D41A4 00608144 */  mtc1       $1, $f12
    /* D41A8 001D41A8 40C0013C */  lui        $1, (0xC0400000 >> 16)
    /* D41AC 001D41AC 00688144 */  mtc1       $1, $f13
    /* D41B0 001D41B0 4214040C */  jal        func_00105108
    /* D41B4 001D41B4 86AB0046 */   mov.s     $f14, $f21
    /* D41B8 001D41B8 1E14040C */  jal        func_00105078
    /* D41BC 001D41BC 00000000 */   nop
    /* D41C0 001D41C0 30004524 */  addiu      $5, $2, 0x30
    /* D41C4 001D41C4 4017040C */  jal        MatrixDrive_TurnObjectMatrix
    /* D41C8 001D41C8 2D20E002 */   daddu     $4, $23, $0
    /* D41CC 001D41CC 3000C28F */  lw         $2, 0x30($30)
    /* D41D0 001D41D0 2D206002 */  daddu      $4, $19, $0
    /* D41D4 001D41D4 68AB858F */  lw         $5, %gp_rel(D_0062B758)($28)
    /* D41D8 001D41D8 2D30E002 */  daddu      $6, $23, $0
    /* D41DC 001D41DC 80110200 */  sll        $2, $2, 6
    /* D41E0 001D41E0 2128A200 */  addu       $5, $5, $2
    /* D41E4 001D41E4 E661040C */  jal        _ApplyCurrentMatrix
    /* D41E8 001D41E8 1000A524 */   addiu     $5, $5, 0x10
    /* D41EC 001D41EC 8017040C */  jal        MatrixDrive_GetTurnYEAngleXZ
    /* D41F0 001D41F0 2D206002 */   daddu     $4, $19, $0
    /* D41F4 001D41F4 30AB94C7 */  lwc1       $f20, %gp_rel(D_0062B720)($28)
    /* D41F8 001D41F8 2D204002 */  daddu      $4, $18, $0
    /* D41FC 001D41FC 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* D4200 001D4200 00088144 */  mtc1       $1, $f1
    /* D4204 001D4204 2D284002 */  daddu      $5, $18, $0
    /* D4208 001D4208 02A50046 */  mul.s      $f20, $f20, $f0
    /* D420C 001D420C 3801B5E7 */  swc1       $f21, 0x138($29)
    /* D4210 001D4210 3C01A1E7 */  swc1       $f1, 0x13C($29)
    /* D4214 001D4214 2D30E002 */  daddu      $6, $23, $0
    /* D4218 001D4218 3401B5E7 */  swc1       $f21, 0x134($29)
    /* D421C 001D421C F861040C */  jal        _TransposeRotationCurrentMatrix
    /* D4220 001D4220 3001B4E7 */   swc1      $f20, 0x130($29)
    /* D4224 001D4224 2D204002 */  daddu      $4, $18, $0
    /* D4228 001D4228 C661040C */  jal        _SetCurrentMatrix
    /* D422C 001D422C 2D284002 */   daddu     $5, $18, $0
    /* D4230 001D4230 BC01A48F */  lw         $4, 0x1BC($29)
    /* D4234 001D4234 2D284002 */  daddu      $5, $18, $0
    /* D4238 001D4238 DE61040C */  jal        _MulCurrentMatrixL
    /* D423C 001D423C 2D302002 */   daddu     $6, $17, $0
    /* D4240 001D4240 2D202002 */  daddu      $4, $17, $0
    /* D4244 001D4244 D261040C */  jal        _MulCurrentMatrixR
    /* D4248 001D4248 2D284002 */   daddu     $5, $18, $0
    /* D424C 001D424C BC3B040C */  jal        func_0010EEF0
    /* D4250 001D4250 06030046 */   mov.s     $f12, $f0
    /* D4254 001D4254 7000033C */  lui        $3, %hi(D_00703030)
    /* D4258 001D4258 BC01A68F */  lw         $6, 0x1BC($29)
    /* D425C 001D425C 30306424 */  addiu      $4, $3, %lo(D_00703030)
    /* D4260 001D4260 2238040C */  jal        func_0010E088
    /* D4264 001D4264 2D284000 */   daddu     $5, $2, $0
    /* D4268 001D4268 1A14040C */  jal        func_00105068
    /* D426C 001D426C 6400B4E7 */   swc1      $f20, 0x64($29)
    /* D4270 001D4270 40B6828F */  lw         $2, %gp_rel(D_0062C230)($28)
    /* D4274 001D4274 B402438C */  lw         $3, 0x2B4($2)
    /* D4278 001D4278 09006014 */  bnez       $3, .L001D42A0
    /* D427C 001D427C 6400A1C7 */   lwc1      $f1, 0x64($29)
    /* D4280 001D4280 6000A0C7 */  lwc1       $f0, 0x60($29)
    /* D4284 001D4284 80000146 */  add.s      $f2, $f0, $f1
    /* D4288 001D4288 34101646 */  c.lt.s     $f2, $f22
    /* D428C 001D428C 00000000 */  nop
    /* D4290 001D4290 04000345 */  bc1tl      .L001D42A4
    /* D4294 001D4294 86150046 */   mov.s     $f22, $f2
    /* D4298 001D4298 03000010 */  b          .L001D42A8
    /* D429C 001D429C 02030046 */   mul.s     $f12, $f0, $f0
.align 2
  .L001D42A0:
    /* D42A0 001D42A0 6000A0C7 */  lwc1       $f0, 0x60($29)
.align 2
  .L001D42A4:
    /* D42A4 001D42A4 02030046 */  mul.s      $f12, $f0, $f0
.align 2
  .L001D42A8:
    /* D42A8 001D42A8 02B51646 */  mul.s      $f20, $f22, $f22
    /* D42AC 001D42AC 42080146 */  mul.s      $f1, $f1, $f1
    /* D42B0 001D42B0 00000046 */  add.s      $f0, $f0, $f0
    /* D42B4 001D42B4 00A30C46 */  add.s      $f12, $f20, $f12
    /* D42B8 001D42B8 02001646 */  mul.s      $f0, $f0, $f22
    /* D42BC 001D42BC 01630146 */  sub.s      $f12, $f12, $f1
    /* D42C0 001D42C0 00000000 */  nop
    /* D42C4 001D42C4 00000000 */  nop
    /* D42C8 001D42C8 03630046 */  div.s      $f12, $f12, $f0
    /* D42CC 001D42CC BC3B040C */  jal        func_0010EEF0
    /* D42D0 001D42D0 00000000 */   nop
    /* D42D4 001D42D4 6400ACC7 */  lwc1       $f12, 0x64($29)
    /* D42D8 001D42D8 6000A0C7 */  lwc1       $f0, 0x60($29)
    /* D42DC 001D42DC 42600C46 */  mul.s      $f1, $f12, $f12
    /* D42E0 001D42E0 02000046 */  mul.s      $f0, $f0, $f0
    /* D42E4 001D42E4 00630C46 */  add.s      $f12, $f12, $f12
    /* D42E8 001D42E8 00A50146 */  add.s      $f20, $f20, $f1
    /* D42EC 001D42EC 02631646 */  mul.s      $f12, $f12, $f22
    /* D42F0 001D42F0 01A50046 */  sub.s      $f20, $f20, $f0
    /* D42F4 001D42F4 00000000 */  nop
    /* D42F8 001D42F8 00000000 */  nop
    /* D42FC 001D42FC 03A30C46 */  div.s      $f12, $f20, $f12
    /* D4300 001D4300 BC3B040C */  jal        func_0010EEF0
    /* D4304 001D4304 38AB82A7 */   sh        $2, %gp_rel(D_0062B728)($28)
    /* D4308 001D4308 0C01A587 */  lh         $5, 0x10C($29)
    /* D430C 001D430C A000A427 */  addiu      $4, $29, 0xA0
    /* D4310 001D4310 1239040C */  jal        func_0010E448
    /* D4314 001D4314 3AAB82A7 */   sh        $2, %gp_rel(D_0062B72A)($28)
    /* D4318 001D4318 38AB8587 */  lh         $5, %gp_rel(D_0062B728)($28)
    /* D431C 001D431C 6239040C */  jal        func_0010E588
    /* D4320 001D4320 A000A427 */   addiu     $4, $29, 0xA0
    /* D4324 001D4324 A000A527 */  addiu      $5, $29, 0xA0
    /* D4328 001D4328 F036040C */  jal        GetInverseQuaternion
    /* D432C 001D432C 2D208002 */   daddu     $4, $20, $0
    /* D4330 001D4330 1E14040C */  jal        func_00105078
    /* D4334 001D4334 00000000 */   nop
    /* D4338 001D4338 40B6908F */  lw         $16, %gp_rel(D_0062C230)($28)
    /* D433C 001D433C 30004524 */  addiu      $5, $2, 0x30
    /* D4340 001D4340 2001A427 */  addiu      $4, $29, 0x120
    /* D4344 001D4344 2D300002 */  daddu      $6, $16, $0
    /* D4348 001D4348 5E17040C */  jal        MatrixDrive_TurnZObjectMatrixXY
    /* D434C 001D434C 90021026 */   addiu     $16, $16, 0x290
    /* D4350 001D4350 2D280002 */  daddu      $5, $16, $0
    /* D4354 001D4354 7000A427 */  addiu      $4, $29, 0x70
    /* D4358 001D4358 6417040C */  jal        MatrixDrive_GetTurnXAngleZY
    /* D435C 001D435C 2001A627 */   addiu     $6, $29, 0x120
    /* D4360 001D4360 7C00A0AF */  sw         $0, 0x7C($29)
    /* D4364 001D4364 2D206002 */  daddu      $4, $19, $0
    /* D4368 001D4368 C661040C */  jal        _SetCurrentMatrix
    /* D436C 001D436C 2D286002 */   daddu     $5, $19, $0
    /* D4370 001D4370 7000023C */  lui        $2, %hi(D_00703020)
    /* D4374 001D4374 2D286002 */  daddu      $5, $19, $0
    /* D4378 001D4378 20304624 */  addiu      $6, $2, %lo(D_00703020)
    /* D437C 001D437C DE61040C */  jal        _MulCurrentMatrixL
    /* D4380 001D4380 2D20E002 */   daddu     $4, $23, $0
    /* D4384 001D4384 40B6898F */  lw         $9, %gp_rel(D_0062C230)($28)
    /* D4388 001D4388 02000324 */  addiu      $3, $0, 0x2
    /* D438C 001D438C 2D202001 */  daddu      $4, $9, $0
    /* D4390 001D4390 5003828C */  lw         $2, 0x350($4)
    /* D4394 001D4394 19004354 */  bnel       $2, $3, .L001D43FC
    /* D4398 001D4398 C0028424 */   addiu     $4, $4, 0x2C0
    /* D439C 001D439C 00008044 */  mtc1       $0, $f0
    /* D43A0 001D43A0 6000A2C7 */  lwc1       $f2, 0x60($29)
    /* D43A4 001D43A4 6400A1C7 */  lwc1       $f1, 0x64($29)
    /* D43A8 001D43A8 00B50046 */  add.s      $f20, $f22, $f0
    /* D43AC 001D43AC 00100146 */  add.s      $f0, $f2, $f1
    /* D43B0 001D43B0 34001446 */  c.lt.s     $f0, $f20
    /* D43B4 001D43B4 00000000 */  nop
    /* D43B8 001D43B8 0F000045 */  bc1f       .L001D43F8
    /* D43BC 001D43BC 2D30E002 */   daddu     $6, $23, $0
    /* D43C0 001D43C0 01A00046 */  sub.s      $f0, $f20, $f0
    /* D43C4 001D43C4 D88981C7 */  lwc1       $f1, %gp_rel(D_006295C8)($28)
    /* D43C8 001D43C8 BC01A48F */  lw         $4, 0x1BC($29)
    /* D43CC 001D43CC 02000146 */  mul.s      $f0, $f0, $f1
    /* D43D0 001D43D0 64000046 */  .word      0x46000064                    # cvt.w.s    $f1, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* D43D4 001D43D4 00080544 */  mfc1       $5, $f1
    /* D43D8 001D43D8 002C0500 */  sll        $5, $5, 16
    /* D43DC 001D43DC 2238040C */  jal        func_0010E088
    /* D43E0 001D43E0 032C0500 */   sra       $5, $5, 16
    /* D43E4 001D43E4 40B6848F */  lw         $4, %gp_rel(D_0062C230)($28)
    /* D43E8 001D43E8 BC01A68F */  lw         $6, 0x1BC($29)
    /* D43EC 001D43EC DC898CC7 */  lwc1       $f12, %gp_rel(D_006295CC)($28)
    /* D43F0 001D43F0 05000010 */  b          .L001D4408
    /* D43F4 001D43F4 C0028424 */   addiu     $4, $4, 0x2C0
.align 2
  .L001D43F8:
    /* D43F8 001D43F8 C0028424 */  addiu      $4, $4, 0x2C0
.align 2
  .L001D43FC:
    /* D43FC 001D43FC 2700023C */  lui        $2, %hi(D_002724B0)
    /* D4400 001D4400 E0898CC7 */  lwc1       $f12, %gp_rel(D_006295D0)($28)
    /* D4404 001D4404 B0244624 */  addiu      $6, $2, %lo(D_002724B0)
.align 2
  .L001D4408:
    /* D4408 001D4408 8237040C */  jal        GetCurrentQuaternion
    /* D440C 001D440C 2D288000 */   daddu     $5, $4, $0
    /* D4410 001D4410 14000010 */  b          .L001D4464
    /* D4414 001D4414 2700033C */   lui       $3, %hi(D_00271240)
.align 2
  .L001D4418:
    /* D4418 001D4418 2D284002 */  daddu      $5, $18, $0
    /* D441C 001D441C A002C624 */  addiu      $6, $6, 0x2A0
    /* D4420 001D4420 5238040C */  jal        func_0010E148
    /* D4424 001D4424 2D208002 */   daddu     $4, $20, $0
    /* D4428 001D4428 1000B626 */  addiu      $22, $21, 0x10
    /* D442C 001D442C A801A68F */  lw         $6, 0x1A8($29)
    /* D4430 001D4430 2D208002 */  daddu      $4, $20, $0
    /* D4434 001D4434 5238040C */  jal        func_0010E148
    /* D4438 001D4438 2D288002 */   daddu     $5, $20, $0
    /* D443C 001D443C 40B6848F */  lw         $4, %gp_rel(D_0062C230)($28)
    /* D4440 001D4440 2700033C */  lui        $3, %hi(D_002724B0)
    /* D4444 001D4444 E4898CC7 */  lwc1       $f12, %gp_rel(D_006295D4)($28)
    /* D4448 001D4448 B0246624 */  addiu      $6, $3, %lo(D_002724B0)
    /* D444C 001D444C C0028424 */  addiu      $4, $4, 0x2C0
    /* D4450 001D4450 8237040C */  jal        GetCurrentQuaternion
    /* D4454 001D4454 2D288000 */   daddu     $5, $4, $0
    /* D4458 001D4458 6000A227 */  addiu      $2, $29, 0x60
    /* D445C 001D445C B801A2AF */  sw         $2, 0x1B8($29)
.align 2
  .L001D4460:
    /* D4460 001D4460 2700033C */  lui        $3, %hi(D_00271240)
.align 2
  .L001D4464:
    /* D4464 001D4464 0A001124 */  addiu      $17, $0, 0xA
    /* D4468 001D4468 4012628C */  lw         $2, %lo(D_00271240)($3)
    /* D446C 001D446C 40127024 */  addiu      $16, $3, %lo(D_00271240)
    /* D4470 001D4470 0400038E */  lw         $3, 0x4($16)
    /* D4474 001D4474 3C001224 */  addiu      $18, $0, 0x3C
    /* D4478 001D4478 18105100 */  mult       $2, $2, $17
    /* D447C 001D447C 7042013C */  lui        $1, (0x42700000 >> 16)
    /* D4480 001D4480 00A08144 */  mtc1       $1, $f20
    /* D4484 001D4484 40B6878F */  lw         $7, %gp_rel(D_0062C230)($28)
    /* D4488 001D4488 01006050 */  beql       $3, $0, .L001D4490
    /* D448C 001D448C CD010000 */   break     0, 7
.align 2
  .L001D4490:
    /* D4490 001D4490 2D288002 */  daddu      $5, $20, $0
    /* D4494 001D4494 2D20C002 */  daddu      $4, $22, $0
    /* D4498 001D4498 B002E0C4 */  lwc1       $f0, 0x2B0($7)
    /* D449C 001D449C 2D30C002 */  daddu      $6, $22, $0
    /* D44A0 001D44A0 23104202 */  subu       $2, $18, $2
    /* D44A4 001D44A4 1A004300 */  div        $0, $2, $3
    /* D44A8 001D44A8 12100000 */  mflo       $2
    /* D44AC 001D44AC 00608244 */  mtc1       $2, $f12
    /* D44B0 001D44B0 20638046 */  cvt.s.w    $f12, $f12
    /* D44B4 001D44B4 00000000 */  nop
    /* D44B8 001D44B8 00000000 */  nop
    /* D44BC 001D44BC 03A30C46 */  div.s      $f12, $f20, $f12
    /* D44C0 001D44C0 8237040C */  jal        GetCurrentQuaternion
    /* D44C4 001D44C4 02030C46 */   mul.s     $f12, $f0, $f12
    /* D44C8 001D44C8 40B6848F */  lw         $4, %gp_rel(D_0062C230)($28)
    /* D44CC 001D44CC 8002828C */  lw         $2, 0x280($4)
    /* D44D0 001D44D0 18004010 */  beqz       $2, .L001D4534
    /* D44D4 001D44D4 2700033C */   lui       $3, %hi(D_00271240)
    /* D44D8 001D44D8 0000A3C6 */  lwc1       $f3, 0x0($21)
    /* D44DC 001D44DC 4012628C */  lw         $2, %lo(D_00271240)($3)
    /* D44E0 001D44E0 0400038E */  lw         $3, 0x4($16)
    /* D44E4 001D44E4 18105100 */  mult       $2, $2, $17
    /* D44E8 001D44E8 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* D44EC 001D44EC 00088144 */  mtc1       $1, $f1
    /* D44F0 001D44F0 01006050 */  beql       $3, $0, .L001D44F8
    /* D44F4 001D44F4 CD010000 */   break     0, 7
.align 2
  .L001D44F8:
    /* D44F8 001D44F8 B00382C4 */  lwc1       $f2, 0x3B0($4)
    /* D44FC 001D44FC 41080346 */  sub.s      $f1, $f1, $f3
    /* D4500 001D4500 23104202 */  subu       $2, $18, $2
    /* D4504 001D4504 1A004300 */  div        $0, $2, $3
    /* D4508 001D4508 12100000 */  mflo       $2
    /* D450C 001D450C 00008244 */  mtc1       $2, $f0
    /* D4510 001D4510 20008046 */  cvt.s.w    $f0, $f0
    /* D4514 001D4514 00000000 */  nop
    /* D4518 001D4518 00000000 */  nop
    /* D451C 001D451C 03A00046 */  div.s      $f0, $f20, $f0
    /* D4520 001D4520 82100046 */  mul.s      $f2, $f2, $f0
    /* D4524 001D4524 42080246 */  mul.s      $f1, $f1, $f2
    /* D4528 001D4528 C0180146 */  add.s      $f3, $f3, $f1
    /* D452C 001D452C 16000010 */  b          .L001D4588
    /* D4530 001D4530 0000A3E6 */   swc1      $f3, 0x0($21)
.align 2
  .L001D4534:
    /* D4534 001D4534 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* D4538 001D4538 00188144 */  mtc1       $1, $f3
    /* D453C 001D453C 4012628C */  lw         $2, %lo(D_00271240)($3)
    /* D4540 001D4540 0400038E */  lw         $3, 0x4($16)
    /* D4544 001D4544 18105100 */  mult       $2, $2, $17
    /* D4548 001D4548 01006050 */  beql       $3, $0, .L001D4550
    /* D454C 001D454C CD010000 */   break     0, 7
.align 2
  .L001D4550:
    /* D4550 001D4550 B00381C4 */  lwc1       $f1, 0x3B0($4)
    /* D4554 001D4554 0000A2C6 */  lwc1       $f2, 0x0($21)
    /* D4558 001D4558 23104202 */  subu       $2, $18, $2
    /* D455C 001D455C 1A004300 */  div        $0, $2, $3
    /* D4560 001D4560 12100000 */  mflo       $2
    /* D4564 001D4564 00008244 */  mtc1       $2, $f0
    /* D4568 001D4568 20008046 */  cvt.s.w    $f0, $f0
    /* D456C 001D456C 00000000 */  nop
    /* D4570 001D4570 00000000 */  nop
    /* D4574 001D4574 03A00046 */  div.s      $f0, $f20, $f0
    /* D4578 001D4578 42080046 */  mul.s      $f1, $f1, $f0
    /* D457C 001D457C C1180146 */  sub.s      $f3, $f3, $f1
    /* D4580 001D4580 82100346 */  mul.s      $f2, $f2, $f3
    /* D4584 001D4584 0000A2E6 */  swc1       $f2, 0x0($21)
.align 2
  .L001D4588:
    /* D4588 001D4588 0000ACC6 */  lwc1       $f12, 0x0($21)
    /* D458C 001D458C 2D28C002 */  daddu      $5, $22, $0
    /* D4590 001D4590 A801A68F */  lw         $6, 0x1A8($29)
    /* D4594 001D4594 8237040C */  jal        GetCurrentQuaternion
    /* D4598 001D4598 B801A48F */   lw        $4, 0x1B8($29)
    /* D459C 001D459C A401A48F */  lw         $4, 0x1A4($29)
    /* D45A0 001D45A0 B801A68F */  lw         $6, 0x1B8($29)
    /* D45A4 001D45A4 5238040C */  jal        func_0010E148
    /* D45A8 001D45A8 2D288000 */   daddu     $5, $4, $0
    /* D45AC 001D45AC DC35040C */  jal        InvertCurrentQuaternion
    /* D45B0 001D45B0 A401A48F */   lw        $4, 0x1A4($29)
    /* D45B4 001D45B4 1E14040C */  jal        func_00105078
    /* D45B8 001D45B8 00000000 */   nop
    /* D45BC 001D45BC 8C37040C */  jal        GetLastQuaternion
    /* D45C0 001D45C0 2D804000 */   daddu     $16, $2, $0
    /* D45C4 001D45C4 2D200002 */  daddu      $4, $16, $0
    /* D45C8 001D45C8 7438040C */  jal        func_0010E1D0
    /* D45CC 001D45CC 2D284000 */   daddu     $5, $2, $0
    /* D45D0 001D45D0 0000A1C6 */  lwc1       $f1, 0x0($21)
    /* D45D4 001D45D4 01000324 */  addiu      $3, $0, 0x1
    /* D45D8 001D45D8 E88980C7 */  lwc1       $f0, %gp_rel(D_006295D8)($28)
    /* D45DC 001D45DC 34000146 */  c.lt.s     $f0, $f1
    /* D45E0 001D45E0 00000000 */  nop
    /* D45E4 001D45E4 02000145 */  bc1t       .L001D45F0
    /* D45E8 001D45E8 24B681E7 */   swc1      $f1, %gp_rel(D_0062C214)($28)
    /* D45EC 001D45EC 2D180000 */  daddu      $3, $0, $0
.align 2
  .L001D45F0:
    /* D45F0 001D45F0 07006010 */  beqz       $3, .L001D4610
    /* D45F4 001D45F4 40B6898F */   lw        $9, %gp_rel(D_0062C230)($28)
    /* D45F8 001D45F8 B802228D */  lw         $2, 0x2B8($9)
    /* D45FC 001D45FC 05004054 */  bnel       $2, $0, .L001D4614
    /* D4600 001D4600 B40220AD */   sw        $0, 0x2B4($9)
    /* D4604 001D4604 01000224 */  addiu      $2, $0, 0x1
    /* D4608 001D4608 02000010 */  b          .L001D4614
    /* D460C 001D460C B40222AD */   sw        $2, 0x2B4($9)
.align 2
  .L001D4610:
    /* D4610 001D4610 B40220AD */  sw         $0, 0x2B4($9)
.align 2
  .L001D4614:
    /* D4614 001D4614 47040010 */  b          .L001D5734
    /* D4618 001D4618 B80223AD */   sw        $3, 0x2B8($9)
.align 2
  jlabel .L001D461C
    /* D461C 001D461C 8C37040C */  jal        GetLastQuaternion
    /* D4620 001D4620 2000D127 */   addiu     $17, $30, 0x20
    /* D4624 001D4624 9237040C */  jal        GetTableSin
    /* D4628 001D4628 2D804000 */   daddu     $16, $2, $0
    /* D462C 001D462C 2D200002 */  daddu      $4, $16, $0
    /* D4630 001D4630 2D302002 */  daddu      $6, $17, $0
    /* D4634 001D4634 5238040C */  jal        func_0010E148
    /* D4638 001D4638 2D284000 */   daddu     $5, $2, $0
    /* D463C 001D463C 1E14040C */  jal        func_00105078
    /* D4640 001D4640 00000000 */   nop
    /* D4644 001D4644 8C37040C */  jal        GetLastQuaternion
    /* D4648 001D4648 2D804000 */   daddu     $16, $2, $0
    /* D464C 001D464C 2D200002 */  daddu      $4, $16, $0
    /* D4650 001D4650 7438040C */  jal        func_0010E1D0
    /* D4654 001D4654 2D284000 */   daddu     $5, $2, $0
    /* D4658 001D4658 3000B327 */  addiu      $19, $29, 0x30
    /* D465C 001D465C 2700053C */  lui        $5, %hi(D_002724B0)
    /* D4660 001D4660 B024A524 */  addiu      $5, $5, %lo(D_002724B0)
    /* D4664 001D4664 F036040C */  jal        GetInverseQuaternion
    /* D4668 001D4668 2D206002 */   daddu     $4, $19, $0
    /* D466C 001D466C 2000B227 */  addiu      $18, $29, 0x20
    /* D4670 001D4670 2D302002 */  daddu      $6, $17, $0
    /* D4674 001D4674 1000C526 */  addiu      $5, $22, 0x10
    /* D4678 001D4678 6238040C */  jal        func_0010E188
    /* D467C 001D467C 2D204002 */   daddu     $4, $18, $0
    /* D4680 001D4680 6000B127 */  addiu      $17, $29, 0x60
    /* D4684 001D4684 2D284002 */  daddu      $5, $18, $0
    /* D4688 001D4688 F036040C */  jal        GetInverseQuaternion
    /* D468C 001D468C 2D202002 */   daddu     $4, $17, $0
    /* D4690 001D4690 40B6898F */  lw         $9, %gp_rel(D_0062C230)($28)
    /* D4694 001D4694 01000324 */  addiu      $3, $0, 0x1
    /* D4698 001D4698 8002228D */  lw         $2, 0x280($9)
    /* D469C 001D469C 14004314 */  bne        $2, $3, .L001D46F0
    /* D46A0 001D46A0 2700023C */   lui       $2, %hi(D_00271240)
    /* D46A4 001D46A4 38AB8597 */  lhu        $5, %gp_rel(D_0062B728)($28)
    /* D46A8 001D46A8 2D202002 */  daddu      $4, $17, $0
    /* D46AC 001D46AC 3AAB8297 */  lhu        $2, %gp_rel(D_0062B72A)($28)
    /* D46B0 001D46B0 00608044 */  mtc1       $0, $f12
    /* D46B4 001D46B4 2128A200 */  addu       $5, $5, $2
    /* D46B8 001D46B8 80BF013C */  lui        $1, (0xBF800000 >> 16)
    /* D46BC 001D46BC 00708144 */  mtc1       $1, $f14
    /* D46C0 001D46C0 23280500 */  negu       $5, $5
    /* D46C4 001D46C4 46630046 */  mov.s      $f13, $f12
    /* D46C8 001D46C8 002C0500 */  sll        $5, $5, 16
    /* D46CC 001D46CC D837040C */  jal        GetTableArcCos
    /* D46D0 001D46D0 032C0500 */   sra       $5, $5, 16
    /* D46D4 001D46D4 7000063C */  lui        $6, %hi(D_00703030)
    /* D46D8 001D46D8 2D202002 */  daddu      $4, $17, $0
    /* D46DC 001D46DC 3030C624 */  addiu      $6, $6, %lo(D_00703030)
    /* D46E0 001D46E0 5238040C */  jal        func_0010E148
    /* D46E4 001D46E4 2D282002 */   daddu     $5, $17, $0
    /* D46E8 001D46E8 40B6898F */  lw         $9, %gp_rel(D_0062C230)($28)
    /* D46EC 001D46EC 2700023C */  lui        $2, %hi(D_00271240)
.align 2
  .L001D46F0:
    /* D46F0 001D46F0 0A000424 */  addiu      $4, $0, 0xA
    /* D46F4 001D46F4 4012488C */  lw         $8, %lo(D_00271240)($2)
    /* D46F8 001D46F8 3C000324 */  addiu      $3, $0, 0x3C
    /* D46FC 001D46FC 40124224 */  addiu      $2, $2, %lo(D_00271240)
    /* D4700 001D4700 7042013C */  lui        $1, (0x42700000 >> 16)
    /* D4704 001D4704 00608144 */  mtc1       $1, $f12
    /* D4708 001D4708 18400401 */  mult       $8, $8, $4
    /* D470C 001D470C 0400478C */  lw         $7, 0x4($2)
    /* D4710 001D4710 1000B026 */  addiu      $16, $21, 0x10
    /* D4714 001D4714 2D282002 */  daddu      $5, $17, $0
    /* D4718 001D4718 0100E050 */  beql       $7, $0, .L001D4720
    /* D471C 001D471C CD010000 */   break     0, 7
.align 2
  .L001D4720:
    /* D4720 001D4720 2D200002 */  daddu      $4, $16, $0
    /* D4724 001D4724 B00221C5 */  lwc1       $f1, 0x2B0($9)
    /* D4728 001D4728 2D300002 */  daddu      $6, $16, $0
    /* D472C 001D472C 23186800 */  subu       $3, $3, $8
    /* D4730 001D4730 1A006700 */  div        $0, $3, $7
    /* D4734 001D4734 12180000 */  mflo       $3
    /* D4738 001D4738 00008344 */  mtc1       $3, $f0
    /* D473C 001D473C 20008046 */  cvt.s.w    $f0, $f0
    /* D4740 001D4740 00000000 */  nop
    /* D4744 001D4744 00000000 */  nop
    /* D4748 001D4748 03630046 */  div.s      $f12, $f12, $f0
    /* D474C 001D474C 8237040C */  jal        GetCurrentQuaternion
    /* D4750 001D4750 020B0C46 */   mul.s     $f12, $f1, $f12
    /* D4754 001D4754 7000B127 */  addiu      $17, $29, 0x70
    /* D4758 001D4758 24B68CC7 */  lwc1       $f12, %gp_rel(D_0062C214)($28)
    /* D475C 001D475C 2D280002 */  daddu      $5, $16, $0
    /* D4760 001D4760 2D304002 */  daddu      $6, $18, $0
    /* D4764 001D4764 8237040C */  jal        GetCurrentQuaternion
    /* D4768 001D4768 2D202002 */   daddu     $4, $17, $0
    /* D476C 001D476C 2D302002 */  daddu      $6, $17, $0
    /* D4770 001D4770 2D206002 */  daddu      $4, $19, $0
    /* D4774 001D4774 5238040C */  jal        func_0010E148
    /* D4778 001D4778 2D286002 */   daddu     $5, $19, $0
    /* D477C 001D477C DC35040C */  jal        InvertCurrentQuaternion
    /* D4780 001D4780 2D206002 */   daddu     $4, $19, $0
    /* D4784 001D4784 D3030010 */  b          .L001D56D4
    /* D4788 001D4788 00000000 */   nop
.align 2
  jlabel .L001D478C
    /* D478C 001D478C 8C37040C */  jal        GetLastQuaternion
    /* D4790 001D4790 2000D127 */   addiu     $17, $30, 0x20
    /* D4794 001D4794 9237040C */  jal        GetTableSin
    /* D4798 001D4798 2D804000 */   daddu     $16, $2, $0
    /* D479C 001D479C 2D200002 */  daddu      $4, $16, $0
    /* D47A0 001D47A0 2D284000 */  daddu      $5, $2, $0
    /* D47A4 001D47A4 5238040C */  jal        func_0010E148
    /* D47A8 001D47A8 2D302002 */   daddu     $6, $17, $0
    /* D47AC 001D47AC 1E14040C */  jal        func_00105078
    /* D47B0 001D47B0 00000000 */   nop
    /* D47B4 001D47B4 8C37040C */  jal        GetLastQuaternion
    /* D47B8 001D47B8 2D804000 */   daddu     $16, $2, $0
    /* D47BC 001D47BC 2D200002 */  daddu      $4, $16, $0
    /* D47C0 001D47C0 7438040C */  jal        func_0010E1D0
    /* D47C4 001D47C4 2D284000 */   daddu     $5, $2, $0
    /* D47C8 001D47C8 2700023C */  lui        $2, %hi(D_002724B0)
    /* D47CC 001D47CC 3000B427 */  addiu      $20, $29, 0x30
    /* D47D0 001D47D0 B0245024 */  addiu      $16, $2, %lo(D_002724B0)
    /* D47D4 001D47D4 2D208002 */  daddu      $4, $20, $0
    /* D47D8 001D47D8 F036040C */  jal        GetInverseQuaternion
    /* D47DC 001D47DC 2D280002 */   daddu     $5, $16, $0
    /* D47E0 001D47E0 2000B327 */  addiu      $19, $29, 0x20
    /* D47E4 001D47E4 1000C526 */  addiu      $5, $22, 0x10
    /* D47E8 001D47E8 2D302002 */  daddu      $6, $17, $0
    /* D47EC 001D47EC 6238040C */  jal        func_0010E188
    /* D47F0 001D47F0 2D206002 */   daddu     $4, $19, $0
    /* D47F4 001D47F4 40B6828F */  lw         $2, %gp_rel(D_0062C230)($28)
    /* D47F8 001D47F8 2003438C */  lw         $3, 0x320($2)
    /* D47FC 001D47FC 07006010 */  beqz       $3, .L001D481C
    /* D4800 001D4800 6000A227 */   addiu     $2, $29, 0x60
    /* D4804 001D4804 2D280002 */  daddu      $5, $16, $0
    /* D4808 001D4808 B801A2AF */  sw         $2, 0x1B8($29)
    /* D480C 001D480C F036040C */  jal        GetInverseQuaternion
    /* D4810 001D4810 2D204000 */   daddu     $4, $2, $0
    /* D4814 001D4814 07000010 */  b          .L001D4834
    /* D4818 001D4818 7000B027 */   addiu     $16, $29, 0x70
.align 2
  .L001D481C:
    /* D481C 001D481C 6000A327 */  addiu      $3, $29, 0x60
    /* D4820 001D4820 2D286002 */  daddu      $5, $19, $0
    /* D4824 001D4824 B801A3AF */  sw         $3, 0x1B8($29)
    /* D4828 001D4828 F036040C */  jal        GetInverseQuaternion
    /* D482C 001D482C 2D206000 */   daddu     $4, $3, $0
    /* D4830 001D4830 7000B027 */  addiu      $16, $29, 0x70
.align 2
  .L001D4834:
    /* D4834 001D4834 24B68CC7 */  lwc1       $f12, %gp_rel(D_0062C214)($28)
    /* D4838 001D4838 B801A58F */  lw         $5, 0x1B8($29)
    /* D483C 001D483C 2D200002 */  daddu      $4, $16, $0
    /* D4840 001D4840 8237040C */  jal        GetCurrentQuaternion
    /* D4844 001D4844 2D306002 */   daddu     $6, $19, $0
    /* D4848 001D4848 2D300002 */  daddu      $6, $16, $0
    /* D484C 001D484C 2D208002 */  daddu      $4, $20, $0
    /* D4850 001D4850 5238040C */  jal        func_0010E148
    /* D4854 001D4854 2D288002 */   daddu     $5, $20, $0
    /* D4858 001D4858 DC35040C */  jal        InvertCurrentQuaternion
    /* D485C 001D485C 2D208002 */   daddu     $4, $20, $0
    /* D4860 001D4860 1E14040C */  jal        func_00105078
    /* D4864 001D4864 00000000 */   nop
    /* D4868 001D4868 8C37040C */  jal        GetLastQuaternion
    /* D486C 001D486C 2D804000 */   daddu     $16, $2, $0
    /* D4870 001D4870 2D200002 */  daddu      $4, $16, $0
    /* D4874 001D4874 7438040C */  jal        func_0010E1D0
    /* D4878 001D4878 2D284000 */   daddu     $5, $2, $0
    /* D487C 001D487C 44B6858F */  lw         $5, %gp_rel(D_0062C234)($28)
    /* D4880 001D4880 C001A28C */  lw         $2, 0x1C0($5)
    /* D4884 001D4884 31004010 */  beqz       $2, .L001D494C
    /* D4888 001D4888 90010224 */   addiu     $2, $0, 0x190
    /* D488C 001D488C 3000A48C */  lw         $4, 0x30($5)
    /* D4890 001D4890 5600033C */  lui        $3, %hi(D_0055DA10)
    /* D4894 001D4894 18208200 */  mult       $4, $4, $2
    /* D4898 001D4898 10DA6324 */  addiu      $3, $3, %lo(D_0055DA10)
    /* D489C 001D489C 21208300 */  addu       $4, $4, $3
    /* D48A0 001D48A0 8C01828C */  lw         $2, 0x18C($4)
    /* D48A4 001D48A4 42100200 */  srl        $2, $2, 1
    /* D48A8 001D48A8 01004230 */  andi       $2, $2, 0x1
    /* D48AC 001D48AC 27004014 */  bnez       $2, .L001D494C
    /* D48B0 001D48B0 06000224 */   addiu     $2, $0, 0x6
    /* D48B4 001D48B4 6800A38C */  lw         $3, 0x68($5)
    /* D48B8 001D48B8 24006210 */  beq        $3, $2, .L001D494C
    /* D48BC 001D48BC 07006228 */   slti      $2, $3, 0x7
    /* D48C0 001D48C0 05004010 */  beqz       $2, .L001D48D8
    /* D48C4 001D48C4 0E000224 */   addiu     $2, $0, 0xE
    /* D48C8 001D48C8 20006010 */  beqz       $3, .L001D494C
    /* D48CC 001D48CC 00000000 */   nop
    /* D48D0 001D48D0 05000010 */  b          .L001D48E8
    /* D48D4 001D48D4 00000000 */   nop
.align 2
  .L001D48D8:
    /* D48D8 001D48D8 1C006210 */  beq        $3, $2, .L001D494C
    /* D48DC 001D48DC 13000224 */   addiu     $2, $0, 0x13
    /* D48E0 001D48E0 1A006210 */  beq        $3, $2, .L001D494C
    /* D48E4 001D48E4 00000000 */   nop
.align 2
  .L001D48E8:
    /* D48E8 001D48E8 B6C4070C */  jal        CheckSwapableWeapon
    /* D48EC 001D48EC C001A48C */   lw        $4, 0x1C0($5)
    /* D48F0 001D48F0 EC8981C7 */  lwc1       $f1, %gp_rel(D_006295DC)($28)
    /* D48F4 001D48F4 F08982C7 */  lwc1       $f2, %gp_rel(D_006295E0)($28)
    /* D48F8 001D48F8 02050146 */  mul.s      $f20, $f0, $f1
    /* D48FC 001D48FC 34101446 */  c.lt.s     $f2, $f20
    /* D4900 001D4900 00000000 */  nop
    /* D4904 001D4904 02000045 */  bc1f       .L001D4910
    /* D4908 001D4908 06A30046 */   mov.s     $f12, $f20
    /* D490C 001D490C 06130046 */  mov.s      $f12, $f2
.align 2
  .L001D4910:
    /* D4910 001D4910 06650046 */  mov.s      $f20, $f12
    /* D4914 001D4914 8C37040C */  jal        GetLastQuaternion
    /* D4918 001D4918 1000B026 */   addiu     $16, $21, 0x10
    /* D491C 001D491C 2D200002 */  daddu      $4, $16, $0
    /* D4920 001D4920 2D280002 */  daddu      $5, $16, $0
    /* D4924 001D4924 2D304000 */  daddu      $6, $2, $0
    /* D4928 001D4928 8237040C */  jal        GetCurrentQuaternion
    /* D492C 001D492C 06A30046 */   mov.s     $f12, $f20
    /* D4930 001D4930 8C37040C */  jal        GetLastQuaternion
    /* D4934 001D4934 00000000 */   nop
    /* D4938 001D4938 2D280002 */  daddu      $5, $16, $0
    /* D493C 001D493C F036040C */  jal        GetInverseQuaternion
    /* D4940 001D4940 2D204000 */   daddu     $4, $2, $0
    /* D4944 001D4944 63030010 */  b          .L001D56D4
    /* D4948 001D4948 00000000 */   nop
.align 2
  .L001D494C:
    /* D494C 001D494C 8C37040C */  jal        GetLastQuaternion
    /* D4950 001D4950 1000B026 */   addiu     $16, $21, 0x10
    /* D4954 001D4954 2D200002 */  daddu      $4, $16, $0
    /* D4958 001D4958 F036040C */  jal        GetInverseQuaternion
    /* D495C 001D495C 2D284000 */   daddu     $5, $2, $0
    /* D4960 001D4960 75030010 */  b          .L001D5738
    /* D4964 001D4964 6002BFDF */   ld        $31, 0x260($29)
.align 2
  jlabel .L001D4968
    /* D4968 001D4968 8C37040C */  jal        GetLastQuaternion
    /* D496C 001D496C 00000000 */   nop
    /* D4970 001D4970 9237040C */  jal        GetTableSin
    /* D4974 001D4974 2D804000 */   daddu     $16, $2, $0
    /* D4978 001D4978 2D200002 */  daddu      $4, $16, $0
    /* D497C 001D497C F036040C */  jal        GetInverseQuaternion
    /* D4980 001D4980 2D284000 */   daddu     $5, $2, $0
    /* D4984 001D4984 8C37040C */  jal        GetLastQuaternion
    /* D4988 001D4988 00000000 */   nop
    /* D498C 001D498C 8C37040C */  jal        GetLastQuaternion
    /* D4990 001D4990 2D804000 */   daddu     $16, $2, $0
    /* D4994 001D4994 4B030010 */  b          .L001D56C4
    /* D4998 001D4998 2D200002 */   daddu     $4, $16, $0
.align 2
  jlabel .L001D499C
    /* D499C 001D499C 8C37040C */  jal        GetLastQuaternion
    /* D49A0 001D49A0 2000D227 */   addiu     $18, $30, 0x20
    /* D49A4 001D49A4 9237040C */  jal        GetTableSin
    /* D49A8 001D49A8 2D804000 */   daddu     $16, $2, $0
    /* D49AC 001D49AC 2D200002 */  daddu      $4, $16, $0
    /* D49B0 001D49B0 2D284000 */  daddu      $5, $2, $0
    /* D49B4 001D49B4 5238040C */  jal        func_0010E148
    /* D49B8 001D49B8 2D304002 */   daddu     $6, $18, $0
    /* D49BC 001D49BC 1E14040C */  jal        func_00105078
    /* D49C0 001D49C0 00000000 */   nop
    /* D49C4 001D49C4 8C37040C */  jal        GetLastQuaternion
    /* D49C8 001D49C8 2D804000 */   daddu     $16, $2, $0
    /* D49CC 001D49CC 2D200002 */  daddu      $4, $16, $0
    /* D49D0 001D49D0 7438040C */  jal        func_0010E1D0
    /* D49D4 001D49D4 2D284000 */   daddu     $5, $2, $0
    /* D49D8 001D49D8 3000B027 */  addiu      $16, $29, 0x30
    /* D49DC 001D49DC 2700053C */  lui        $5, %hi(D_002724B0)
    /* D49E0 001D49E0 2D200002 */  daddu      $4, $16, $0
    /* D49E4 001D49E4 F036040C */  jal        GetInverseQuaternion
    /* D49E8 001D49E8 B024A524 */   addiu     $5, $5, %lo(D_002724B0)
    /* D49EC 001D49EC 2000B127 */  addiu      $17, $29, 0x20
    /* D49F0 001D49F0 1000C526 */  addiu      $5, $22, 0x10
    /* D49F4 001D49F4 2D304002 */  daddu      $6, $18, $0
    /* D49F8 001D49F8 6238040C */  jal        func_0010E188
    /* D49FC 001D49FC 2D202002 */   daddu     $4, $17, $0
    /* D4A00 001D4A00 2D200002 */  daddu      $4, $16, $0
    /* D4A04 001D4A04 2D280002 */  daddu      $5, $16, $0
    /* D4A08 001D4A08 5238040C */  jal        func_0010E148
    /* D4A0C 001D4A0C 2D302002 */   daddu     $6, $17, $0
    /* D4A10 001D4A10 DC35040C */  jal        InvertCurrentQuaternion
    /* D4A14 001D4A14 2D200002 */   daddu     $4, $16, $0
    /* D4A18 001D4A18 2E030010 */  b          .L001D56D4
    /* D4A1C 001D4A1C 00000000 */   nop
.align 2
  jlabel .L001D4A20
    /* D4A20 001D4A20 8C37040C */  jal        GetLastQuaternion
    /* D4A24 001D4A24 2000D127 */   addiu     $17, $30, 0x20
    /* D4A28 001D4A28 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* D4A2C 001D4A2C 00A08144 */  mtc1       $1, $f20
    /* D4A30 001D4A30 9237040C */  jal        GetTableSin
    /* D4A34 001D4A34 2D804000 */   daddu     $16, $2, $0
    /* D4A38 001D4A38 2D200002 */  daddu      $4, $16, $0
    /* D4A3C 001D4A3C 2D284000 */  daddu      $5, $2, $0
    /* D4A40 001D4A40 5238040C */  jal        func_0010E148
    /* D4A44 001D4A44 2D302002 */   daddu     $6, $17, $0
    /* D4A48 001D4A48 1E14040C */  jal        func_00105078
    /* D4A4C 001D4A4C 00000000 */   nop
    /* D4A50 001D4A50 8C37040C */  jal        GetLastQuaternion
    /* D4A54 001D4A54 2D804000 */   daddu     $16, $2, $0
    /* D4A58 001D4A58 2D200002 */  daddu      $4, $16, $0
    /* D4A5C 001D4A5C 7438040C */  jal        func_0010E1D0
    /* D4A60 001D4A60 2D284000 */   daddu     $5, $2, $0
    /* D4A64 001D4A64 3000A227 */  addiu      $2, $29, 0x30
    /* D4A68 001D4A68 2700053C */  lui        $5, %hi(D_002724B0)
    /* D4A6C 001D4A6C AC01A2AF */  sw         $2, 0x1AC($29)
    /* D4A70 001D4A70 B024A524 */  addiu      $5, $5, %lo(D_002724B0)
    /* D4A74 001D4A74 F036040C */  jal        GetInverseQuaternion
    /* D4A78 001D4A78 2D204000 */   daddu     $4, $2, $0
    /* D4A7C 001D4A7C 2000B427 */  addiu      $20, $29, 0x20
    /* D4A80 001D4A80 1000C526 */  addiu      $5, $22, 0x10
    /* D4A84 001D4A84 2D302002 */  daddu      $6, $17, $0
    /* D4A88 001D4A88 6238040C */  jal        func_0010E188
    /* D4A8C 001D4A8C 2D208002 */   daddu     $4, $20, $0
    /* D4A90 001D4A90 1001B727 */  addiu      $23, $29, 0x110
    /* D4A94 001D4A94 2D280000 */  daddu      $5, $0, $0
    /* D4A98 001D4A98 2D20E002 */  daddu      $4, $23, $0
    /* D4A9C 001D4A9C 5A81090C */  jal        func_00260568
    /* D4AA0 001D4AA0 10000624 */   addiu     $6, $0, 0x10
    /* D4AA4 001D4AA4 2D90E002 */  daddu      $18, $23, $0
    /* D4AA8 001D4AA8 40B6908F */  lw         $16, %gp_rel(D_0062C230)($28)
    /* D4AAC 001D4AAC 1C01B4E7 */  swc1       $f20, 0x11C($29)
    /* D4AB0 001D4AB0 1E14040C */  jal        func_00105078
    /* D4AB4 001D4AB4 30021026 */   addiu     $16, $16, 0x230
    /* D4AB8 001D4AB8 40B6868F */  lw         $6, %gp_rel(D_0062C230)($28)
    /* D4ABC 001D4ABC 30004524 */  addiu      $5, $2, 0x30
    /* D4AC0 001D4AC0 5E17040C */  jal        MatrixDrive_TurnZObjectMatrixXY
    /* D4AC4 001D4AC4 7001A427 */   addiu     $4, $29, 0x170
    /* D4AC8 001D4AC8 2D280002 */  daddu      $5, $16, $0
    /* D4ACC 001D4ACC 6001A427 */  addiu      $4, $29, 0x160
    /* D4AD0 001D4AD0 6417040C */  jal        MatrixDrive_GetTurnXAngleZY
    /* D4AD4 001D4AD4 7001A627 */   addiu     $6, $29, 0x170
    /* D4AD8 001D4AD8 1614040C */  jal        func_00105058
    /* D4ADC 001D4ADC 6C01A0AF */   sw        $0, 0x16C($29)
    /* D4AE0 001D4AE0 1E14040C */  jal        func_00105078
    /* D4AE4 001D4AE4 00000000 */   nop
    /* D4AE8 001D4AE8 2414040C */  jal        func_00105090
    /* D4AEC 001D4AEC 2D804000 */   daddu     $16, $2, $0
    /* D4AF0 001D4AF0 2D200002 */  daddu      $4, $16, $0
    /* D4AF4 001D4AF4 1C17040C */  jal        MatrixDrive_TransMatrix
    /* D4AF8 001D4AF8 2D284000 */   daddu     $5, $2, $0
    /* D4AFC 001D4AFC 1E14040C */  jal        func_00105078
    /* D4B00 001D4B00 00000000 */   nop
    /* D4B04 001D4B04 2D284000 */  daddu      $5, $2, $0
    /* D4B08 001D4B08 2001A427 */  addiu      $4, $29, 0x120
    /* D4B0C 001D4B0C 76FF080C */  jal        func_0023FDD8
    /* D4B10 001D4B10 6001A627 */   addiu     $6, $29, 0x160
    /* D4B14 001D4B14 1A14040C */  jal        func_00105068
    /* D4B18 001D4B18 00000000 */   nop
    /* D4B1C 001D4B1C 2001ACC7 */  lwc1       $f12, 0x120($29)
    /* D4B20 001D4B20 8001A427 */  addiu      $4, $29, 0x180
    /* D4B24 001D4B24 2401ADC7 */  lwc1       $f13, 0x124($29)
    /* D4B28 001D4B28 8201A527 */  addiu      $5, $29, 0x182
    /* D4B2C 001D4B2C 8A15040C */  jal        MatrixDrive_ScaleMatrix
    /* D4B30 001D4B30 2801AEC7 */   lwc1      $f14, 0x128($29)
    /* D4B34 001D4B34 01000224 */  addiu      $2, $0, 0x1
    /* D4B38 001D4B38 8001A887 */  lh         $8, 0x180($29)
    /* D4B3C 001D4B3C 8201AA87 */  lh         $10, 0x182($29)
    /* D4B40 001D4B40 06A30046 */  mov.s      $f12, $f20
    /* D4B44 001D4B44 A001A78F */  lw         $7, 0x1A0($29)
    /* D4B48 001D4B48 8401A427 */  addiu      $4, $29, 0x184
    /* D4B4C 001D4B4C 0000A2AF */  sw         $2, 0x0($29)
    /* D4B50 001D4B50 8601A527 */  addiu      $5, $29, 0x186
    /* D4B54 001D4B54 0800A0AF */  sw         $0, 0x8($29)
    /* D4B58 001D4B58 8801A627 */  addiu      $6, $29, 0x188
    /* D4B5C 001D4B5C 2D480000 */  daddu      $9, $0, $0
    /* D4B60 001D4B60 B648070C */  jal        AddMotionMemorySize
    /* D4B64 001D4B64 2D580000 */   daddu     $11, $0, $0
    /* D4B68 001D4B68 40B6828F */  lw         $2, %gp_rel(D_0062C230)($28)
    /* D4B6C 001D4B6C 2402438C */  lw         $3, 0x224($2)
    /* D4B70 001D4B70 05006010 */  beqz       $3, .L001D4B88
    /* D4B74 001D4B74 5001A427 */   addiu     $4, $29, 0x150
    /* D4B78 001D4B78 C661040C */  jal        _SetCurrentMatrix
    /* D4B7C 001D4B7C 2001A527 */   addiu     $5, $29, 0x120
    /* D4B80 001D4B80 14000010 */  b          .L001D4BD4
    /* D4B84 001D4B84 2700103C */   lui       $16, %hi(D_00271BF0)
.align 2
  .L001D4B88:
    /* D4B88 001D4B88 8601B187 */  lh         $17, 0x186($29)
    /* D4B8C 001D4B8C 8401B087 */  lh         $16, 0x184($29)
    /* D4B90 001D4B90 4C3B040C */  jal        func_0010ED30
    /* D4B94 001D4B94 2D202002 */   daddu     $4, $17, $0
    /* D4B98 001D4B98 06050046 */  mov.s      $f20, $f0
    /* D4B9C 001D4B9C 4C3B040C */  jal        func_0010ED30
    /* D4BA0 001D4BA0 2D200002 */   daddu     $4, $16, $0
    /* D4BA4 001D4BA4 02001446 */  mul.s      $f0, $f0, $f20
    /* D4BA8 001D4BA8 2D200002 */  daddu      $4, $16, $0
    /* D4BAC 001D4BAC 383B040C */  jal        p2o_SetDefaultEnviroment
    /* D4BB0 001D4BB0 5001A0E7 */   swc1      $f0, 0x150($29)
    /* D4BB4 001D4BB4 02001446 */  mul.s      $f0, $f0, $f20
    /* D4BB8 001D4BB8 2D202002 */  daddu      $4, $17, $0
    /* D4BBC 001D4BBC 383B040C */  jal        p2o_SetDefaultEnviroment
    /* D4BC0 001D4BC0 5401A0E7 */   swc1      $f0, 0x154($29)
    /* D4BC4 001D4BC4 07000046 */  neg.s      $f0, $f0
    /* D4BC8 001D4BC8 5C01A0AF */  sw         $0, 0x15C($29)
    /* D4BCC 001D4BCC 5801A0E7 */  swc1       $f0, 0x158($29)
    /* D4BD0 001D4BD0 2700103C */  lui        $16, %hi(D_00271BF0)
.align 2
  .L001D4BD4:
    /* D4BD4 001D4BD4 5001A427 */  addiu      $4, $29, 0x150
    /* D4BD8 001D4BD8 F01B1026 */  addiu      $16, $16, %lo(D_00271BF0)
    /* D4BDC 001D4BDC D261040C */  jal        _MulCurrentMatrixR
    /* D4BE0 001D4BE0 2D280002 */   daddu     $5, $16, $0
    /* D4BE4 001D4BE4 BC3B040C */  jal        func_0010EEF0
    /* D4BE8 001D4BE8 06030046 */   mov.s     $f12, $f0
    /* D4BEC 001D4BEC 2D884000 */  daddu      $17, $2, $0
    /* D4BF0 001D4BF0 2D300002 */  daddu      $6, $16, $0
    /* D4BF4 001D4BF4 6001A427 */  addiu      $4, $29, 0x160
    /* D4BF8 001D4BF8 DE61040C */  jal        _MulCurrentMatrixL
    /* D4BFC 001D4BFC 5001A527 */   addiu     $5, $29, 0x150
    /* D4C00 001D4C00 2D282002 */  daddu      $5, $17, $0
    /* D4C04 001D4C04 3001A427 */  addiu      $4, $29, 0x130
    /* D4C08 001D4C08 2238040C */  jal        func_0010E088
    /* D4C0C 001D4C0C 6001A627 */   addiu     $6, $29, 0x160
    /* D4C10 001D4C10 2D204002 */  daddu      $4, $18, $0
    /* D4C14 001D4C14 2D284002 */  daddu      $5, $18, $0
    /* D4C18 001D4C18 5238040C */  jal        func_0010E148
    /* D4C1C 001D4C1C 3001A627 */   addiu     $6, $29, 0x130
    /* D4C20 001D4C20 40B6868F */  lw         $6, %gp_rel(D_0062C230)($28)
    /* D4C24 001D4C24 01000224 */  addiu      $2, $0, 0x1
    /* D4C28 001D4C28 2002C38C */  lw         $3, 0x220($6)
    /* D4C2C 001D4C2C 08006210 */  beq        $3, $2, .L001D4C50
    /* D4C30 001D4C30 02000224 */   addiu     $2, $0, 0x2
    /* D4C34 001D4C34 5D006210 */  beq        $3, $2, .L001D4DAC
    /* D4C38 001D4C38 7000B327 */   addiu     $19, $29, 0x70
    /* D4C3C 001D4C3C 2D288002 */  daddu      $5, $20, $0
    /* D4C40 001D4C40 F036040C */  jal        GetInverseQuaternion
    /* D4C44 001D4C44 2D206002 */   daddu     $4, $19, $0
    /* D4C48 001D4C48 61000010 */  b          .L001D4DD0
    /* D4C4C 001D4C4C 1000B626 */   addiu     $22, $21, 0x10
.align 2
  .L001D4C50:
    /* D4C50 001D4C50 2001A427 */  addiu      $4, $29, 0x120
    /* D4C54 001D4C54 8017040C */  jal        MatrixDrive_GetTurnYEAngleXZ
    /* D4C58 001D4C58 2D800000 */   daddu     $16, $0, $0
    /* D4C5C 001D4C5C 3000C48F */  lw         $4, 0x30($30)
    /* D4C60 001D4C60 FFFF0224 */  addiu      $2, $0, -0x1
    /* D4C64 001D4C64 1B008210 */  beq        $4, $2, .L001D4CD4
    /* D4C68 001D4C68 06050046 */   mov.s     $f20, $f0
    /* D4C6C 001D4C6C 6001A227 */  addiu      $2, $29, 0x160
    /* D4C70 001D4C70 42A51446 */  mul.s      $f21, $f20, $f20
    /* D4C74 001D4C74 C001A2AF */  sw         $2, 0x1C0($29)
    /* D4C78 001D4C78 1000B626 */  addiu      $22, $21, 0x10
    /* D4C7C 001D4C7C 7000B327 */  addiu      $19, $29, 0x70
    /* D4C80 001D4C80 68AB838F */  lw         $3, %gp_rel(D_0062B758)($28)
    /* D4C84 001D4C84 00000000 */  nop
.align 2
  .L001D4C88:
    /* D4C88 001D4C88 80110400 */  sll        $2, $4, 6
    /* D4C8C 001D4C8C 21886200 */  addu       $17, $3, $2
    /* D4C90 001D4C90 8017040C */  jal        MatrixDrive_GetTurnYEAngleXZ
    /* D4C94 001D4C94 10002426 */   addiu     $4, $17, 0x10
    /* D4C98 001D4C98 30AB81C7 */  lwc1       $f1, %gp_rel(D_0062B720)($28)
    /* D4C9C 001D4C9C 80101000 */  sll        $2, $16, 2
    /* D4CA0 001D4CA0 C001A38F */  lw         $3, 0x1C0($29)
    /* D4CA4 001D4CA4 01001026 */  addiu      $16, $16, 0x1
    /* D4CA8 001D4CA8 42080046 */  mul.s      $f1, $f1, $f0
    /* D4CAC 001D4CAC 21106200 */  addu       $2, $3, $2
    /* D4CB0 001D4CB0 0200032A */  slti       $3, $16, 0x2
    /* D4CB4 001D4CB4 0C006010 */  beqz       $3, .L001D4CE8
    /* D4CB8 001D4CB8 000041E4 */   swc1      $f1, 0x0($2)
    /* D4CBC 001D4CBC 3000248E */  lw         $4, 0x30($17)
    /* D4CC0 001D4CC0 FFFF0224 */  addiu      $2, $0, -0x1
    /* D4CC4 001D4CC4 F0FF8214 */  bne        $4, $2, .L001D4C88
    /* D4CC8 001D4CC8 68AB838F */   lw        $3, %gp_rel(D_0062B758)($28)
    /* D4CCC 001D4CCC 07000010 */  b          .L001D4CEC
    /* D4CD0 001D4CD0 6CAB848F */   lw        $4, %gp_rel(D_0062B75C)($28)
.align 2
  .L001D4CD4:
    /* D4CD4 001D4CD4 6001A227 */  addiu      $2, $29, 0x160
    /* D4CD8 001D4CD8 42A51446 */  mul.s      $f21, $f20, $f20
    /* D4CDC 001D4CDC C001A2AF */  sw         $2, 0x1C0($29)
    /* D4CE0 001D4CE0 1000B626 */  addiu      $22, $21, 0x10
    /* D4CE4 001D4CE4 7000B327 */  addiu      $19, $29, 0x70
.align 2
  .L001D4CE8:
    /* D4CE8 001D4CE8 6CAB848F */  lw         $4, %gp_rel(D_0062B75C)($28)
.align 2
  .L001D4CEC:
    /* D4CEC 001D4CEC 9627040C */  jal        DebugDisp1CollisionWithColor
    /* D4CF0 001D4CF0 10000524 */   addiu     $5, $0, 0x10
    /* D4CF4 001D4CF4 68AB848F */  lw         $4, %gp_rel(D_0062B758)($28)
    /* D4CF8 001D4CF8 80110200 */  sll        $2, $2, 6
    /* D4CFC 001D4CFC 21208200 */  addu       $4, $4, $2
    /* D4D00 001D4D00 8017040C */  jal        MatrixDrive_GetTurnYEAngleXZ
    /* D4D04 001D4D04 10008424 */   addiu     $4, $4, 0x10
    /* D4D08 001D4D08 30AB81C7 */  lwc1       $f1, %gp_rel(D_0062B720)($28)
    /* D4D0C 001D4D0C 6401A2C7 */  lwc1       $f2, 0x164($29)
    /* D4D10 001D4D10 42080046 */  mul.s      $f1, $f1, $f0
    /* D4D14 001D4D14 6001ACC7 */  lwc1       $f12, 0x160($29)
    /* D4D18 001D4D18 02600C46 */  mul.s      $f0, $f12, $f12
    /* D4D1C 001D4D1C 80100146 */  add.s      $f2, $f2, $f1
    /* D4D20 001D4D20 00630C46 */  add.s      $f12, $f12, $f12
    /* D4D24 001D4D24 00A80046 */  add.s      $f0, $f21, $f0
    /* D4D28 001D4D28 42100246 */  mul.s      $f1, $f2, $f2
    /* D4D2C 001D4D2C 02631446 */  mul.s      $f12, $f12, $f20
    /* D4D30 001D4D30 01000146 */  sub.s      $f0, $f0, $f1
    /* D4D34 001D4D34 00000000 */  nop
    /* D4D38 001D4D38 00000000 */  nop
    /* D4D3C 001D4D3C 03030C46 */  div.s      $f12, $f0, $f12
    /* D4D40 001D4D40 BC3B040C */  jal        func_0010EEF0
    /* D4D44 001D4D44 6401A2E7 */   swc1      $f2, 0x164($29)
    /* D4D48 001D4D48 6401ACC7 */  lwc1       $f12, 0x164($29)
    /* D4D4C 001D4D4C 6001A1C7 */  lwc1       $f1, 0x160($29)
    /* D4D50 001D4D50 02600C46 */  mul.s      $f0, $f12, $f12
    /* D4D54 001D4D54 42080146 */  mul.s      $f1, $f1, $f1
    /* D4D58 001D4D58 00630C46 */  add.s      $f12, $f12, $f12
    /* D4D5C 001D4D5C 00A80046 */  add.s      $f0, $f21, $f0
    /* D4D60 001D4D60 02631446 */  mul.s      $f12, $f12, $f20
    /* D4D64 001D4D64 01000146 */  sub.s      $f0, $f0, $f1
    /* D4D68 001D4D68 00000000 */  nop
    /* D4D6C 001D4D6C 00000000 */  nop
    /* D4D70 001D4D70 03030C46 */  div.s      $f12, $f0, $f12
    /* D4D74 001D4D74 BC3B040C */  jal        func_0010EEF0
    /* D4D78 001D4D78 38AB82A7 */   sh        $2, %gp_rel(D_0062B728)($28)
    /* D4D7C 001D4D7C 8801A587 */  lh         $5, 0x188($29)
    /* D4D80 001D4D80 2D204002 */  daddu      $4, $18, $0
    /* D4D84 001D4D84 1239040C */  jal        func_0010E448
    /* D4D88 001D4D88 3AAB82A7 */   sh        $2, %gp_rel(D_0062B72A)($28)
    /* D4D8C 001D4D8C 38AB8587 */  lh         $5, %gp_rel(D_0062B728)($28)
    /* D4D90 001D4D90 6239040C */  jal        func_0010E588
    /* D4D94 001D4D94 2D204002 */   daddu     $4, $18, $0
    /* D4D98 001D4D98 2D284002 */  daddu      $5, $18, $0
    /* D4D9C 001D4D9C F036040C */  jal        GetInverseQuaternion
    /* D4DA0 001D4DA0 2D206002 */   daddu     $4, $19, $0
    /* D4DA4 001D4DA4 0D000010 */  b          .L001D4DDC
    /* D4DA8 001D4DA8 2700033C */   lui       $3, %hi(D_00271240)
.align 2
  .L001D4DAC:
    /* D4DAC 001D4DAC 2D28E002 */  daddu      $5, $23, $0
    /* D4DB0 001D4DB0 4002C624 */  addiu      $6, $6, 0x240
    /* D4DB4 001D4DB4 5238040C */  jal        func_0010E148
    /* D4DB8 001D4DB8 2D206002 */   daddu     $4, $19, $0
    /* D4DBC 001D4DBC 1000B626 */  addiu      $22, $21, 0x10
    /* D4DC0 001D4DC0 2D206002 */  daddu      $4, $19, $0
    /* D4DC4 001D4DC4 2D286002 */  daddu      $5, $19, $0
    /* D4DC8 001D4DC8 5238040C */  jal        func_0010E148
    /* D4DCC 001D4DCC 2D308002 */   daddu     $6, $20, $0
.align 2
  .L001D4DD0:
    /* D4DD0 001D4DD0 6001A327 */  addiu      $3, $29, 0x160
    /* D4DD4 001D4DD4 C001A3AF */  sw         $3, 0x1C0($29)
    /* D4DD8 001D4DD8 2700033C */  lui        $3, %hi(D_00271240)
.align 2
  .L001D4DDC:
    /* D4DDC 001D4DDC 0A001124 */  addiu      $17, $0, 0xA
    /* D4DE0 001D4DE0 4012628C */  lw         $2, %lo(D_00271240)($3)
    /* D4DE4 001D4DE4 40127024 */  addiu      $16, $3, %lo(D_00271240)
    /* D4DE8 001D4DE8 0400038E */  lw         $3, 0x4($16)
    /* D4DEC 001D4DEC 3C001224 */  addiu      $18, $0, 0x3C
    /* D4DF0 001D4DF0 18105100 */  mult       $2, $2, $17
    /* D4DF4 001D4DF4 7042013C */  lui        $1, (0x42700000 >> 16)
    /* D4DF8 001D4DF8 00A08144 */  mtc1       $1, $f20
    /* D4DFC 001D4DFC 40B6878F */  lw         $7, %gp_rel(D_0062C230)($28)
    /* D4E00 001D4E00 01006050 */  beql       $3, $0, .L001D4E08
    /* D4E04 001D4E04 CD010000 */   break     0, 7
.align 2
  .L001D4E08:
    /* D4E08 001D4E08 2D286002 */  daddu      $5, $19, $0
    /* D4E0C 001D4E0C 2D20C002 */  daddu      $4, $22, $0
    /* D4E10 001D4E10 B003E0C4 */  lwc1       $f0, 0x3B0($7)
    /* D4E14 001D4E14 2D30C002 */  daddu      $6, $22, $0
    /* D4E18 001D4E18 23104202 */  subu       $2, $18, $2
    /* D4E1C 001D4E1C 1A004300 */  div        $0, $2, $3
    /* D4E20 001D4E20 12100000 */  mflo       $2
    /* D4E24 001D4E24 00608244 */  mtc1       $2, $f12
    /* D4E28 001D4E28 20638046 */  cvt.s.w    $f12, $f12
    /* D4E2C 001D4E2C 00000000 */  nop
    /* D4E30 001D4E30 00000000 */  nop
    /* D4E34 001D4E34 03A30C46 */  div.s      $f12, $f20, $f12
    /* D4E38 001D4E38 8237040C */  jal        GetCurrentQuaternion
    /* D4E3C 001D4E3C 02030C46 */   mul.s     $f12, $f0, $f12
    /* D4E40 001D4E40 40B6848F */  lw         $4, %gp_rel(D_0062C230)($28)
    /* D4E44 001D4E44 2002828C */  lw         $2, 0x220($4)
    /* D4E48 001D4E48 18004010 */  beqz       $2, .L001D4EAC
    /* D4E4C 001D4E4C 2700033C */   lui       $3, %hi(D_00271240)
    /* D4E50 001D4E50 0000A3C6 */  lwc1       $f3, 0x0($21)
    /* D4E54 001D4E54 4012628C */  lw         $2, %lo(D_00271240)($3)
    /* D4E58 001D4E58 0400038E */  lw         $3, 0x4($16)
    /* D4E5C 001D4E5C 18105100 */  mult       $2, $2, $17
    /* D4E60 001D4E60 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* D4E64 001D4E64 00088144 */  mtc1       $1, $f1
    /* D4E68 001D4E68 01006050 */  beql       $3, $0, .L001D4E70
    /* D4E6C 001D4E6C CD010000 */   break     0, 7
.align 2
  .L001D4E70:
    /* D4E70 001D4E70 B00382C4 */  lwc1       $f2, 0x3B0($4)
    /* D4E74 001D4E74 41080346 */  sub.s      $f1, $f1, $f3
    /* D4E78 001D4E78 23104202 */  subu       $2, $18, $2
    /* D4E7C 001D4E7C 1A004300 */  div        $0, $2, $3
    /* D4E80 001D4E80 12100000 */  mflo       $2
    /* D4E84 001D4E84 00008244 */  mtc1       $2, $f0
    /* D4E88 001D4E88 20008046 */  cvt.s.w    $f0, $f0
    /* D4E8C 001D4E8C 00000000 */  nop
    /* D4E90 001D4E90 00000000 */  nop
    /* D4E94 001D4E94 03A00046 */  div.s      $f0, $f20, $f0
    /* D4E98 001D4E98 82100046 */  mul.s      $f2, $f2, $f0
    /* D4E9C 001D4E9C 42080246 */  mul.s      $f1, $f1, $f2
    /* D4EA0 001D4EA0 C0180146 */  add.s      $f3, $f3, $f1
    /* D4EA4 001D4EA4 16000010 */  b          .L001D4F00
    /* D4EA8 001D4EA8 0000A3E6 */   swc1      $f3, 0x0($21)
.align 2
  .L001D4EAC:
    /* D4EAC 001D4EAC 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* D4EB0 001D4EB0 00188144 */  mtc1       $1, $f3
    /* D4EB4 001D4EB4 4012628C */  lw         $2, %lo(D_00271240)($3)
    /* D4EB8 001D4EB8 0400038E */  lw         $3, 0x4($16)
    /* D4EBC 001D4EBC 18105100 */  mult       $2, $2, $17
    /* D4EC0 001D4EC0 01006050 */  beql       $3, $0, .L001D4EC8
    /* D4EC4 001D4EC4 CD010000 */   break     0, 7
.align 2
  .L001D4EC8:
    /* D4EC8 001D4EC8 B00381C4 */  lwc1       $f1, 0x3B0($4)
    /* D4ECC 001D4ECC 0000A2C6 */  lwc1       $f2, 0x0($21)
    /* D4ED0 001D4ED0 23104202 */  subu       $2, $18, $2
    /* D4ED4 001D4ED4 1A004300 */  div        $0, $2, $3
    /* D4ED8 001D4ED8 12100000 */  mflo       $2
    /* D4EDC 001D4EDC 00008244 */  mtc1       $2, $f0
    /* D4EE0 001D4EE0 20008046 */  cvt.s.w    $f0, $f0
    /* D4EE4 001D4EE4 00000000 */  nop
    /* D4EE8 001D4EE8 00000000 */  nop
    /* D4EEC 001D4EEC 03A00046 */  div.s      $f0, $f20, $f0
    /* D4EF0 001D4EF0 42080046 */  mul.s      $f1, $f1, $f0
    /* D4EF4 001D4EF4 C1180146 */  sub.s      $f3, $f3, $f1
    /* D4EF8 001D4EF8 82100346 */  mul.s      $f2, $f2, $f3
    /* D4EFC 001D4EFC 0000A2E6 */  swc1       $f2, 0x0($21)
.align 2
  .L001D4F00:
    /* D4F00 001D4F00 0000ACC6 */  lwc1       $f12, 0x0($21)
    /* D4F04 001D4F04 2D28C002 */  daddu      $5, $22, $0
    /* D4F08 001D4F08 C001A48F */  lw         $4, 0x1C0($29)
    /* D4F0C 001D4F0C 8237040C */  jal        GetCurrentQuaternion
    /* D4F10 001D4F10 2D308002 */   daddu     $6, $20, $0
    /* D4F14 001D4F14 AC01A48F */  lw         $4, 0x1AC($29)
    /* D4F18 001D4F18 C001A68F */  lw         $6, 0x1C0($29)
    /* D4F1C 001D4F1C 5238040C */  jal        func_0010E148
    /* D4F20 001D4F20 2D288000 */   daddu     $5, $4, $0
    /* D4F24 001D4F24 DC35040C */  jal        InvertCurrentQuaternion
    /* D4F28 001D4F28 AC01A48F */   lw        $4, 0x1AC($29)
    /* D4F2C 001D4F2C 1E14040C */  jal        func_00105078
    /* D4F30 001D4F30 00000000 */   nop
    /* D4F34 001D4F34 8C37040C */  jal        GetLastQuaternion
    /* D4F38 001D4F38 2D804000 */   daddu     $16, $2, $0
    /* D4F3C 001D4F3C 2D200002 */  daddu      $4, $16, $0
    /* D4F40 001D4F40 7438040C */  jal        func_0010E1D0
    /* D4F44 001D4F44 2D284000 */   daddu     $5, $2, $0
    /* D4F48 001D4F48 0000A0C6 */  lwc1       $f0, 0x0($21)
    /* D4F4C 001D4F4C F9010010 */  b          .L001D5734
    /* D4F50 001D4F50 24B680E7 */   swc1      $f0, %gp_rel(D_0062C214)($28)
.align 2
  jlabel .L001D4F54
    /* D4F54 001D4F54 8C37040C */  jal        GetLastQuaternion
    /* D4F58 001D4F58 2000D127 */   addiu     $17, $30, 0x20
    /* D4F5C 001D4F5C 9237040C */  jal        GetTableSin
    /* D4F60 001D4F60 2D804000 */   daddu     $16, $2, $0
    /* D4F64 001D4F64 2D200002 */  daddu      $4, $16, $0
    /* D4F68 001D4F68 2D302002 */  daddu      $6, $17, $0
    /* D4F6C 001D4F6C 5238040C */  jal        func_0010E148
    /* D4F70 001D4F70 2D284000 */   daddu     $5, $2, $0
    /* D4F74 001D4F74 1E14040C */  jal        func_00105078
    /* D4F78 001D4F78 00000000 */   nop
    /* D4F7C 001D4F7C 8C37040C */  jal        GetLastQuaternion
    /* D4F80 001D4F80 2D804000 */   daddu     $16, $2, $0
    /* D4F84 001D4F84 2D200002 */  daddu      $4, $16, $0
    /* D4F88 001D4F88 7438040C */  jal        func_0010E1D0
    /* D4F8C 001D4F8C 2D284000 */   daddu     $5, $2, $0
    /* D4F90 001D4F90 3000B327 */  addiu      $19, $29, 0x30
    /* D4F94 001D4F94 2700053C */  lui        $5, %hi(D_002724B0)
    /* D4F98 001D4F98 B024A524 */  addiu      $5, $5, %lo(D_002724B0)
    /* D4F9C 001D4F9C F036040C */  jal        GetInverseQuaternion
    /* D4FA0 001D4FA0 2D206002 */   daddu     $4, $19, $0
    /* D4FA4 001D4FA4 2000B427 */  addiu      $20, $29, 0x20
    /* D4FA8 001D4FA8 2D302002 */  daddu      $6, $17, $0
    /* D4FAC 001D4FAC 1000C526 */  addiu      $5, $22, 0x10
    /* D4FB0 001D4FB0 6238040C */  jal        func_0010E188
    /* D4FB4 001D4FB4 2D208002 */   daddu     $4, $20, $0
    /* D4FB8 001D4FB8 6001B127 */  addiu      $17, $29, 0x160
    /* D4FBC 001D4FBC 2D288002 */  daddu      $5, $20, $0
    /* D4FC0 001D4FC0 F036040C */  jal        GetInverseQuaternion
    /* D4FC4 001D4FC4 2D202002 */   daddu     $4, $17, $0
    /* D4FC8 001D4FC8 40B6898F */  lw         $9, %gp_rel(D_0062C230)($28)
    /* D4FCC 001D4FCC 01000324 */  addiu      $3, $0, 0x1
    /* D4FD0 001D4FD0 2002228D */  lw         $2, 0x220($9)
    /* D4FD4 001D4FD4 0F004314 */  bne        $2, $3, .L001D5014
    /* D4FD8 001D4FD8 2700023C */   lui       $2, %hi(D_00271240)
    /* D4FDC 001D4FDC 38AB8597 */  lhu        $5, %gp_rel(D_0062B728)($28)
    /* D4FE0 001D4FE0 2D202002 */  daddu      $4, $17, $0
    /* D4FE4 001D4FE4 3AAB8297 */  lhu        $2, %gp_rel(D_0062B72A)($28)
    /* D4FE8 001D4FE8 00608044 */  mtc1       $0, $f12
    /* D4FEC 001D4FEC 2128A200 */  addu       $5, $5, $2
    /* D4FF0 001D4FF0 80BF013C */  lui        $1, (0xBF800000 >> 16)
    /* D4FF4 001D4FF4 00708144 */  mtc1       $1, $f14
    /* D4FF8 001D4FF8 23280500 */  negu       $5, $5
    /* D4FFC 001D4FFC 46630046 */  mov.s      $f13, $f12
    /* D5000 001D5000 002C0500 */  sll        $5, $5, 16
    /* D5004 001D5004 D837040C */  jal        GetTableArcCos
    /* D5008 001D5008 032C0500 */   sra       $5, $5, 16
    /* D500C 001D500C 40B6898F */  lw         $9, %gp_rel(D_0062C230)($28)
    /* D5010 001D5010 2700023C */  lui        $2, %hi(D_00271240)
.align 2
  .L001D5014:
    /* D5014 001D5014 0A000424 */  addiu      $4, $0, 0xA
    /* D5018 001D5018 4012488C */  lw         $8, %lo(D_00271240)($2)
    /* D501C 001D501C 3C000324 */  addiu      $3, $0, 0x3C
    /* D5020 001D5020 40124224 */  addiu      $2, $2, %lo(D_00271240)
    /* D5024 001D5024 7042013C */  lui        $1, (0x42700000 >> 16)
    /* D5028 001D5028 00608144 */  mtc1       $1, $f12
    /* D502C 001D502C 18400401 */  mult       $8, $8, $4
    /* D5030 001D5030 0400478C */  lw         $7, 0x4($2)
    /* D5034 001D5034 1000B026 */  addiu      $16, $21, 0x10
    /* D5038 001D5038 2D282002 */  daddu      $5, $17, $0
    /* D503C 001D503C 0100E050 */  beql       $7, $0, .L001D5044
    /* D5040 001D5040 CD010000 */   break     0, 7
.align 2
  .L001D5044:
    /* D5044 001D5044 2D200002 */  daddu      $4, $16, $0
    /* D5048 001D5048 B00321C5 */  lwc1       $f1, 0x3B0($9)
    /* D504C 001D504C 2D300002 */  daddu      $6, $16, $0
    /* D5050 001D5050 23186800 */  subu       $3, $3, $8
    /* D5054 001D5054 1A006700 */  div        $0, $3, $7
    /* D5058 001D5058 12180000 */  mflo       $3
    /* D505C 001D505C 00008344 */  mtc1       $3, $f0
    /* D5060 001D5060 20008046 */  cvt.s.w    $f0, $f0
    /* D5064 001D5064 00000000 */  nop
    /* D5068 001D5068 00000000 */  nop
    /* D506C 001D506C 03630046 */  div.s      $f12, $f12, $f0
    /* D5070 001D5070 8237040C */  jal        GetCurrentQuaternion
    /* D5074 001D5074 020B0C46 */   mul.s     $f12, $f1, $f12
    /* D5078 001D5078 7001B127 */  addiu      $17, $29, 0x170
    /* D507C 001D507C 24B68CC7 */  lwc1       $f12, %gp_rel(D_0062C214)($28)
    /* D5080 001D5080 2D280002 */  daddu      $5, $16, $0
    /* D5084 001D5084 2D308002 */  daddu      $6, $20, $0
    /* D5088 001D5088 8237040C */  jal        GetCurrentQuaternion
    /* D508C 001D508C 2D202002 */   daddu     $4, $17, $0
    /* D5090 001D5090 2D302002 */  daddu      $6, $17, $0
    /* D5094 001D5094 2D206002 */  daddu      $4, $19, $0
    /* D5098 001D5098 5238040C */  jal        func_0010E148
    /* D509C 001D509C 2D286002 */   daddu     $5, $19, $0
    /* D50A0 001D50A0 DC35040C */  jal        InvertCurrentQuaternion
    /* D50A4 001D50A4 2D206002 */   daddu     $4, $19, $0
    /* D50A8 001D50A8 8A010010 */  b          .L001D56D4
    /* D50AC 001D50AC 00000000 */   nop
.align 2
  jlabel .L001D50B0
    /* D50B0 001D50B0 8C37040C */  jal        GetLastQuaternion
    /* D50B4 001D50B4 2000D127 */   addiu     $17, $30, 0x20
    /* D50B8 001D50B8 9237040C */  jal        GetTableSin
    /* D50BC 001D50BC 2D804000 */   daddu     $16, $2, $0
    /* D50C0 001D50C0 2D200002 */  daddu      $4, $16, $0
    /* D50C4 001D50C4 2D284000 */  daddu      $5, $2, $0
    /* D50C8 001D50C8 5238040C */  jal        func_0010E148
    /* D50CC 001D50CC 2D302002 */   daddu     $6, $17, $0
    /* D50D0 001D50D0 1E14040C */  jal        func_00105078
    /* D50D4 001D50D4 00000000 */   nop
    /* D50D8 001D50D8 8C37040C */  jal        GetLastQuaternion
    /* D50DC 001D50DC 2D804000 */   daddu     $16, $2, $0
    /* D50E0 001D50E0 2D200002 */  daddu      $4, $16, $0
    /* D50E4 001D50E4 7438040C */  jal        func_0010E1D0
    /* D50E8 001D50E8 2D284000 */   daddu     $5, $2, $0
    /* D50EC 001D50EC 2700023C */  lui        $2, %hi(D_002724B0)
    /* D50F0 001D50F0 3000B427 */  addiu      $20, $29, 0x30
    /* D50F4 001D50F4 B0245024 */  addiu      $16, $2, %lo(D_002724B0)
    /* D50F8 001D50F8 2D208002 */  daddu      $4, $20, $0
    /* D50FC 001D50FC F036040C */  jal        GetInverseQuaternion
    /* D5100 001D5100 2D280002 */   daddu     $5, $16, $0
    /* D5104 001D5104 2000B327 */  addiu      $19, $29, 0x20
    /* D5108 001D5108 1000C526 */  addiu      $5, $22, 0x10
    /* D510C 001D510C 2D302002 */  daddu      $6, $17, $0
    /* D5110 001D5110 6238040C */  jal        func_0010E188
    /* D5114 001D5114 2D206002 */   daddu     $4, $19, $0
    /* D5118 001D5118 40B6828F */  lw         $2, %gp_rel(D_0062C230)($28)
    /* D511C 001D511C 2403438C */  lw         $3, 0x324($2)
    /* D5120 001D5120 06006010 */  beqz       $3, .L001D513C
    /* D5124 001D5124 1000B626 */   addiu     $22, $21, 0x10
    /* D5128 001D5128 2D280002 */  daddu      $5, $16, $0
    /* D512C 001D512C F036040C */  jal        GetInverseQuaternion
    /* D5130 001D5130 2D20C002 */   daddu     $4, $22, $0
    /* D5134 001D5134 05000010 */  b          .L001D514C
    /* D5138 001D5138 6001B027 */   addiu     $16, $29, 0x160
.align 2
  .L001D513C:
    /* D513C 001D513C 2D286002 */  daddu      $5, $19, $0
    /* D5140 001D5140 F036040C */  jal        GetInverseQuaternion
    /* D5144 001D5144 2D20C002 */   daddu     $4, $22, $0
    /* D5148 001D5148 6001B027 */  addiu      $16, $29, 0x160
.align 2
  .L001D514C:
    /* D514C 001D514C 24B68CC7 */  lwc1       $f12, %gp_rel(D_0062C214)($28)
    /* D5150 001D5150 2D200002 */  daddu      $4, $16, $0
    /* D5154 001D5154 2D28C002 */  daddu      $5, $22, $0
    /* D5158 001D5158 8237040C */  jal        GetCurrentQuaternion
    /* D515C 001D515C 2D306002 */   daddu     $6, $19, $0
    /* D5160 001D5160 2D300002 */  daddu      $6, $16, $0
    /* D5164 001D5164 2D208002 */  daddu      $4, $20, $0
    /* D5168 001D5168 5238040C */  jal        func_0010E148
    /* D516C 001D516C 2D288002 */   daddu     $5, $20, $0
    /* D5170 001D5170 DC35040C */  jal        InvertCurrentQuaternion
    /* D5174 001D5174 2D208002 */   daddu     $4, $20, $0
    /* D5178 001D5178 56010010 */  b          .L001D56D4
    /* D517C 001D517C 00000000 */   nop
.align 2
  jlabel .L001D5180
    /* D5180 001D5180 8C37040C */  jal        GetLastQuaternion
    /* D5184 001D5184 2000D127 */   addiu     $17, $30, 0x20
    /* D5188 001D5188 9237040C */  jal        GetTableSin
    /* D518C 001D518C 2D804000 */   daddu     $16, $2, $0
    /* D5190 001D5190 2D200002 */  daddu      $4, $16, $0
    /* D5194 001D5194 2D284000 */  daddu      $5, $2, $0
    /* D5198 001D5198 5238040C */  jal        func_0010E148
    /* D519C 001D519C 2D302002 */   daddu     $6, $17, $0
    /* D51A0 001D51A0 1E14040C */  jal        func_00105078
    /* D51A4 001D51A4 00000000 */   nop
    /* D51A8 001D51A8 8C37040C */  jal        GetLastQuaternion
    /* D51AC 001D51AC 2D804000 */   daddu     $16, $2, $0
    /* D51B0 001D51B0 2D200002 */  daddu      $4, $16, $0
    /* D51B4 001D51B4 7438040C */  jal        func_0010E1D0
    /* D51B8 001D51B8 2D284000 */   daddu     $5, $2, $0
    /* D51BC 001D51BC 3000B327 */  addiu      $19, $29, 0x30
    /* D51C0 001D51C0 2700053C */  lui        $5, %hi(D_002724B0)
    /* D51C4 001D51C4 B024A524 */  addiu      $5, $5, %lo(D_002724B0)
    /* D51C8 001D51C8 F036040C */  jal        GetInverseQuaternion
    /* D51CC 001D51CC 2D206002 */   daddu     $4, $19, $0
    /* D51D0 001D51D0 2000B027 */  addiu      $16, $29, 0x20
    /* D51D4 001D51D4 1000C526 */  addiu      $5, $22, 0x10
    /* D51D8 001D51D8 2D302002 */  daddu      $6, $17, $0
    /* D51DC 001D51DC 6238040C */  jal        func_0010E188
    /* D51E0 001D51E0 2D200002 */   daddu     $4, $16, $0
    /* D51E4 001D51E4 40B6828F */  lw         $2, %gp_rel(D_0062C230)($28)
    /* D51E8 001D51E8 2002438C */  lw         $3, 0x220($2)
    /* D51EC 001D51EC 08006010 */  beqz       $3, .L001D5210
    /* D51F0 001D51F0 01000224 */   addiu     $2, $0, 0x1
    /* D51F4 001D51F4 0A006210 */  beq        $3, $2, .L001D5220
    /* D51F8 001D51F8 2D300002 */   daddu     $6, $16, $0
    /* D51FC 001D51FC 2D206002 */  daddu      $4, $19, $0
    /* D5200 001D5200 5238040C */  jal        func_0010E148
    /* D5204 001D5204 2D286002 */   daddu     $5, $19, $0
    /* D5208 001D5208 05000010 */  b          .L001D5220
    /* D520C 001D520C 00000000 */   nop
.align 2
  .L001D5210:
    /* D5210 001D5210 2D300002 */  daddu      $6, $16, $0
    /* D5214 001D5214 2D206002 */  daddu      $4, $19, $0
    /* D5218 001D5218 5238040C */  jal        func_0010E148
    /* D521C 001D521C 2D286002 */   daddu     $5, $19, $0
.align 2
  .L001D5220:
    /* D5220 001D5220 DC35040C */  jal        InvertCurrentQuaternion
    /* D5224 001D5224 2D206002 */   daddu     $4, $19, $0
    /* D5228 001D5228 2A010010 */  b          .L001D56D4
    /* D522C 001D522C 00000000 */   nop
.align 2
  jlabel .L001D5230
    /* D5230 001D5230 40B6828F */  lw         $2, %gp_rel(D_0062C230)($28)
    /* D5234 001D5234 F401438C */  lw         $3, 0x1F4($2)
    /* D5238 001D5238 1D016010 */  beqz       $3, .L001D56B0
    /* D523C 001D523C 00000000 */   nop
    /* D5240 001D5240 8C37040C */  jal        GetLastQuaternion
    /* D5244 001D5244 2000D127 */   addiu     $17, $30, 0x20
    /* D5248 001D5248 2D804000 */  daddu      $16, $2, $0
    /* D524C 001D524C 9237040C */  jal        GetTableSin
    /* D5250 001D5250 B401A0AF */   sw        $0, 0x1B4($29)
    /* D5254 001D5254 2DA80000 */  daddu      $21, $0, $0
    /* D5258 001D5258 2D200002 */  daddu      $4, $16, $0
    /* D525C 001D525C 2D302002 */  daddu      $6, $17, $0
    /* D5260 001D5260 5238040C */  jal        func_0010E148
    /* D5264 001D5264 2D284000 */   daddu     $5, $2, $0
    /* D5268 001D5268 1E14040C */  jal        func_00105078
    /* D526C 001D526C 00000000 */   nop
    /* D5270 001D5270 8C37040C */  jal        GetLastQuaternion
    /* D5274 001D5274 2D804000 */   daddu     $16, $2, $0
    /* D5278 001D5278 2D200002 */  daddu      $4, $16, $0
    /* D527C 001D527C 7438040C */  jal        func_0010E1D0
    /* D5280 001D5280 2D284000 */   daddu     $5, $2, $0
    /* D5284 001D5284 3000B727 */  addiu      $23, $29, 0x30
    /* D5288 001D5288 2700053C */  lui        $5, %hi(D_002724B0)
    /* D528C 001D528C B024A524 */  addiu      $5, $5, %lo(D_002724B0)
    /* D5290 001D5290 F036040C */  jal        GetInverseQuaternion
    /* D5294 001D5294 2D20E002 */   daddu     $4, $23, $0
    /* D5298 001D5298 2000A227 */  addiu      $2, $29, 0x20
    /* D529C 001D529C 2D302002 */  daddu      $6, $17, $0
    /* D52A0 001D52A0 B001A2AF */  sw         $2, 0x1B0($29)
    /* D52A4 001D52A4 1000C526 */  addiu      $5, $22, 0x10
    /* D52A8 001D52A8 6238040C */  jal        func_0010E188
    /* D52AC 001D52AC 2D204000 */   daddu     $4, $2, $0
    /* D52B0 001D52B0 4813040C */  jal        func_00104D20
    /* D52B4 001D52B4 00000000 */   nop
    /* D52B8 001D52B8 1E14040C */  jal        func_00105078
    /* D52BC 001D52BC 00000000 */   nop
    /* D52C0 001D52C0 2700053C */  lui        $5, %hi(D_00271BE0)
    /* D52C4 001D52C4 30004424 */  addiu      $4, $2, 0x30
    /* D52C8 001D52C8 4017040C */  jal        MatrixDrive_TurnObjectMatrix
    /* D52CC 001D52CC E01BA524 */   addiu     $5, $5, %lo(D_00271BE0)
    /* D52D0 001D52D0 C038040C */  jal        func_0010E300
    /* D52D4 001D52D4 B001A48F */   lw        $4, 0x1B0($29)
    /* D52D8 001D52D8 4813040C */  jal        func_00104D20
    /* D52DC 001D52DC 00000000 */   nop
    /* D52E0 001D52E0 3000D18F */  lw         $17, 0x30($30)
    /* D52E4 001D52E4 FFFF0224 */  addiu      $2, $0, -0x1
    /* D52E8 001D52E8 05002216 */  bne        $17, $2, .L001D5300
    /* D52EC 001D52EC 6001A227 */   addiu     $2, $29, 0x160
    /* D52F0 001D52F0 01000324 */  addiu      $3, $0, 0x1
    /* D52F4 001D52F4 7001B427 */  addiu      $20, $29, 0x170
    /* D52F8 001D52F8 24000010 */  b          .L001D538C
    /* D52FC 001D52FC B401A3AF */   sw        $3, 0x1B4($29)
.align 2
  .L001D5300:
    /* D5300 001D5300 7001B427 */  addiu      $20, $29, 0x170
    /* D5304 001D5304 C001A2AF */  sw         $2, 0x1C0($29)
    /* D5308 001D5308 9001B327 */  addiu      $19, $29, 0x190
    /* D530C 001D530C 68AB838F */  lw         $3, %gp_rel(D_0062B758)($28)
.align 2
  .L001D5310:
    /* D5310 001D5310 80111100 */  sll        $2, $17, 6
    /* D5314 001D5314 30AB8CC7 */  lwc1       $f12, %gp_rel(D_0062B720)($28)
    /* D5318 001D5318 2D206002 */  daddu      $4, $19, $0
    /* D531C 001D531C 21906200 */  addu       $18, $3, $2
    /* D5320 001D5320 10005026 */  addiu      $16, $18, 0x10
    /* D5324 001D5324 5A02090C */  jal        func_00240968
    /* D5328 001D5328 2D280002 */   daddu     $5, $16, $0
    /* D532C 001D532C 2A14040C */  jal        func_001050A8
    /* D5330 001D5330 2D206002 */   daddu     $4, $19, $0
    /* D5334 001D5334 28B6848F */  lw         $4, %gp_rel(D_0062C218)($28)
    /* D5338 001D5338 40111100 */  sll        $2, $17, 5
    /* D533C 001D533C 21208200 */  addu       $4, $4, $2
    /* D5340 001D5340 C038040C */  jal        func_0010E300
    /* D5344 001D5344 10008424 */   addiu     $4, $4, 0x10
    /* D5348 001D5348 8017040C */  jal        MatrixDrive_GetTurnYEAngleXZ
    /* D534C 001D534C 2D200002 */   daddu     $4, $16, $0
    /* D5350 001D5350 30AB81C7 */  lwc1       $f1, %gp_rel(D_0062B720)($28)
    /* D5354 001D5354 80101500 */  sll        $2, $21, 2
    /* D5358 001D5358 C001A38F */  lw         $3, 0x1C0($29)
    /* D535C 001D535C 0100B526 */  addiu      $21, $21, 0x1
    /* D5360 001D5360 42080046 */  mul.s      $f1, $f1, $f0
    /* D5364 001D5364 21106200 */  addu       $2, $3, $2
    /* D5368 001D5368 0200A32A */  slti       $3, $21, 0x2
    /* D536C 001D536C 07006010 */  beqz       $3, .L001D538C
    /* D5370 001D5370 000041E4 */   swc1      $f1, 0x0($2)
    /* D5374 001D5374 3000518E */  lw         $17, 0x30($18)
    /* D5378 001D5378 FFFF0224 */  addiu      $2, $0, -0x1
    /* D537C 001D537C E4FF2216 */  bne        $17, $2, .L001D5310
    /* D5380 001D5380 68AB838F */   lw        $3, %gp_rel(D_0062B758)($28)
    /* D5384 001D5384 01000224 */  addiu      $2, $0, 0x1
    /* D5388 001D5388 B401A2AF */  sw         $2, 0x1B4($29)
.align 2
  .L001D538C:
    /* D538C 001D538C 1E14040C */  jal        func_00105078
    /* D5390 001D5390 00000000 */   nop
    /* D5394 001D5394 30004524 */  addiu      $5, $2, 0x30
    /* D5398 001D5398 4017040C */  jal        MatrixDrive_TurnObjectMatrix
    /* D539C 001D539C 2D208002 */   daddu     $4, $20, $0
    /* D53A0 001D53A0 0400C58F */  lw         $5, 0x4($30)
    /* D53A4 001D53A4 2D000224 */  addiu      $2, $0, 0x2D
    /* D53A8 001D53A8 0500A210 */  beq        $5, $2, .L001D53C0
    /* D53AC 001D53AC 31000224 */   addiu     $2, $0, 0x31
    /* D53B0 001D53B0 0700A210 */  beq        $5, $2, .L001D53D0
    /* D53B4 001D53B4 40B6828F */   lw        $2, %gp_rel(D_0062C230)($28)
    /* D53B8 001D53B8 09000010 */  b          .L001D53E0
    /* D53BC 001D53BC 00000000 */   nop
.align 2
  .L001D53C0:
    /* D53C0 001D53C0 40B6828F */  lw         $2, %gp_rel(D_0062C230)($28)
    /* D53C4 001D53C4 7401A0C7 */  lwc1       $f0, 0x174($29)
    /* D53C8 001D53C8 03000010 */  b          .L001D53D8
    /* D53CC 001D53CC F80141C4 */   lwc1      $f1, 0x1F8($2)
.align 2
  .L001D53D0:
    /* D53D0 001D53D0 7401A0C7 */  lwc1       $f0, 0x174($29)
    /* D53D4 001D53D4 FC0141C4 */  lwc1       $f1, 0x1FC($2)
.align 2
  .L001D53D8:
    /* D53D8 001D53D8 00000146 */  add.s      $f0, $f0, $f1
    /* D53DC 001D53DC 7401A0E7 */  swc1       $f0, 0x174($29)
.align 2
  .L001D53E0:
    /* D53E0 001D53E0 8017040C */  jal        MatrixDrive_GetTurnYEAngleXZ
    /* D53E4 001D53E4 2D208002 */   daddu     $4, $20, $0
    /* D53E8 001D53E8 1A14040C */  jal        func_00105068
    /* D53EC 001D53EC 46050046 */   mov.s     $f21, $f0
    /* D53F0 001D53F0 1E14040C */  jal        func_00105078
    /* D53F4 001D53F4 02AD1546 */   mul.s     $f20, $f21, $f21
    /* D53F8 001D53F8 2D804000 */  daddu      $16, $2, $0
    /* D53FC 001D53FC 2D200002 */  daddu      $4, $16, $0
    /* D5400 001D5400 B4FF080C */  jal        func_0023FED0
    /* D5404 001D5404 2D280002 */   daddu     $5, $16, $0
    /* D5408 001D5408 2D280002 */  daddu      $5, $16, $0
    /* D540C 001D540C 2D208002 */  daddu      $4, $20, $0
    /* D5410 001D5410 76FF080C */  jal        func_0023FDD8
    /* D5414 001D5414 2D308002 */   daddu     $6, $20, $0
    /* D5418 001D5418 2D208002 */  daddu      $4, $20, $0
    /* D541C 001D541C A6FF080C */  jal        func_0023FE98
    /* D5420 001D5420 2D288000 */   daddu     $5, $4, $0
    /* D5424 001D5424 983B040C */  jal        func_0010EE60
    /* D5428 001D5428 7401ACC7 */   lwc1      $f12, 0x174($29)
    /* D542C 001D542C 7801ACC7 */  lwc1       $f12, 0x178($29)
    /* D5430 001D5430 983B040C */  jal        func_0010EE60
    /* D5434 001D5434 34AB82A7 */   sh        $2, %gp_rel(D_0062B724)($28)
    /* D5438 001D5438 6001ACC7 */  lwc1       $f12, 0x160($29)
    /* D543C 001D543C 23100200 */  negu       $2, $2
    /* D5440 001D5440 6401A1C7 */  lwc1       $f1, 0x164($29)
    /* D5444 001D5444 02600C46 */  mul.s      $f0, $f12, $f12
    /* D5448 001D5448 42080146 */  mul.s      $f1, $f1, $f1
    /* D544C 001D544C 00630C46 */  add.s      $f12, $f12, $f12
    /* D5450 001D5450 00A00046 */  add.s      $f0, $f20, $f0
    /* D5454 001D5454 02631546 */  mul.s      $f12, $f12, $f21
    /* D5458 001D5458 01000146 */  sub.s      $f0, $f0, $f1
    /* D545C 001D545C 00000000 */  nop
    /* D5460 001D5460 00000000 */  nop
    /* D5464 001D5464 03030C46 */  div.s      $f12, $f0, $f12
    /* D5468 001D5468 BC3B040C */  jal        func_0010EEF0
    /* D546C 001D546C 36AB82A7 */   sh        $2, %gp_rel(D_0062B726)($28)
    /* D5470 001D5470 6401ACC7 */  lwc1       $f12, 0x164($29)
    /* D5474 001D5474 6001A0C7 */  lwc1       $f0, 0x160($29)
    /* D5478 001D5478 42600C46 */  mul.s      $f1, $f12, $f12
    /* D547C 001D547C 02000046 */  mul.s      $f0, $f0, $f0
    /* D5480 001D5480 00630C46 */  add.s      $f12, $f12, $f12
    /* D5484 001D5484 00A50146 */  add.s      $f20, $f20, $f1
    /* D5488 001D5488 02631546 */  mul.s      $f12, $f12, $f21
    /* D548C 001D548C 01A50046 */  sub.s      $f20, $f20, $f0
    /* D5490 001D5490 00000000 */  nop
    /* D5494 001D5494 00000000 */  nop
    /* D5498 001D5498 03A30C46 */  div.s      $f12, $f20, $f12
    /* D549C 001D549C BC3B040C */  jal        func_0010EEF0
    /* D54A0 001D54A0 38AB82A7 */   sh        $2, %gp_rel(D_0062B728)($28)
    /* D54A4 001D54A4 1A14040C */  jal        func_00105068
    /* D54A8 001D54A8 3AAB82A7 */   sh        $2, %gp_rel(D_0062B72A)($28)
    /* D54AC 001D54AC B401A38F */  lw         $3, 0x1B4($29)
    /* D54B0 001D54B0 12006014 */  bnez       $3, .L001D54FC
    /* D54B4 001D54B4 B001A68F */   lw        $6, 0x1B0($29)
    /* D54B8 001D54B8 2D20E002 */  daddu      $4, $23, $0
    /* D54BC 001D54BC 5238040C */  jal        func_0010E148
    /* D54C0 001D54C0 2D28E002 */   daddu     $5, $23, $0
    /* D54C4 001D54C4 34AB8587 */  lh         $5, %gp_rel(D_0062B724)($28)
    /* D54C8 001D54C8 6239040C */  jal        func_0010E588
    /* D54CC 001D54CC 2D20E002 */   daddu     $4, $23, $0
    /* D54D0 001D54D0 36AB8587 */  lh         $5, %gp_rel(D_0062B726)($28)
    /* D54D4 001D54D4 3A39040C */  jal        func_0010E4E8
    /* D54D8 001D54D8 2D20E002 */   daddu     $4, $23, $0
    /* D54DC 001D54DC 38AB8597 */  lhu        $5, %gp_rel(D_0062B728)($28)
    /* D54E0 001D54E0 2D20E002 */  daddu      $4, $23, $0
    /* D54E4 001D54E4 23280500 */  negu       $5, $5
    /* D54E8 001D54E8 002C0500 */  sll        $5, $5, 16
    /* D54EC 001D54EC 6239040C */  jal        func_0010E588
    /* D54F0 001D54F0 032C0500 */   sra       $5, $5, 16
    /* D54F4 001D54F4 04000010 */  b          .L001D5508
    /* D54F8 001D54F8 00000000 */   nop
.align 2
  .L001D54FC:
    /* D54FC 001D54FC 2D20E002 */  daddu      $4, $23, $0
    /* D5500 001D5500 5238040C */  jal        func_0010E148
    /* D5504 001D5504 2D28E002 */   daddu     $5, $23, $0
.align 2
  .L001D5508:
    /* D5508 001D5508 DC35040C */  jal        InvertCurrentQuaternion
    /* D550C 001D550C 2D20E002 */   daddu     $4, $23, $0
    /* D5510 001D5510 70000010 */  b          .L001D56D4
    /* D5514 001D5514 00000000 */   nop
.align 2
  jlabel .L001D5518
    /* D5518 001D5518 40B6828F */  lw         $2, %gp_rel(D_0062C230)($28)
    /* D551C 001D551C F401438C */  lw         $3, 0x1F4($2)
    /* D5520 001D5520 63006010 */  beqz       $3, .L001D56B0
    /* D5524 001D5524 00000000 */   nop
    /* D5528 001D5528 8C37040C */  jal        GetLastQuaternion
    /* D552C 001D552C 2000D127 */   addiu     $17, $30, 0x20
    /* D5530 001D5530 9237040C */  jal        GetTableSin
    /* D5534 001D5534 2D804000 */   daddu     $16, $2, $0
    /* D5538 001D5538 2D200002 */  daddu      $4, $16, $0
    /* D553C 001D553C 2D284000 */  daddu      $5, $2, $0
    /* D5540 001D5540 5238040C */  jal        func_0010E148
    /* D5544 001D5544 2D302002 */   daddu     $6, $17, $0
    /* D5548 001D5548 1E14040C */  jal        func_00105078
    /* D554C 001D554C 00000000 */   nop
    /* D5550 001D5550 8C37040C */  jal        GetLastQuaternion
    /* D5554 001D5554 2D804000 */   daddu     $16, $2, $0
    /* D5558 001D5558 2D200002 */  daddu      $4, $16, $0
    /* D555C 001D555C 7438040C */  jal        func_0010E1D0
    /* D5560 001D5560 2D284000 */   daddu     $5, $2, $0
    /* D5564 001D5564 3000B027 */  addiu      $16, $29, 0x30
    /* D5568 001D5568 2700053C */  lui        $5, %hi(D_002724B0)
    /* D556C 001D556C 2D200002 */  daddu      $4, $16, $0
    /* D5570 001D5570 F036040C */  jal        GetInverseQuaternion
    /* D5574 001D5574 B024A524 */   addiu     $5, $5, %lo(D_002724B0)
    /* D5578 001D5578 1000C526 */  addiu      $5, $22, 0x10
    /* D557C 001D557C 2D302002 */  daddu      $6, $17, $0
    /* D5580 001D5580 6238040C */  jal        func_0010E188
    /* D5584 001D5584 2000A427 */   addiu     $4, $29, 0x20
    /* D5588 001D5588 38AB8597 */  lhu        $5, %gp_rel(D_0062B728)($28)
    /* D558C 001D558C 2D200002 */  daddu      $4, $16, $0
    /* D5590 001D5590 3AAB8297 */  lhu        $2, %gp_rel(D_0062B72A)($28)
    /* D5594 001D5594 2128A200 */  addu       $5, $5, $2
    /* D5598 001D5598 002C0500 */  sll        $5, $5, 16
    /* D559C 001D559C 6239040C */  jal        func_0010E588
    /* D55A0 001D55A0 032C0500 */   sra       $5, $5, 16
    /* D55A4 001D55A4 DC35040C */  jal        InvertCurrentQuaternion
    /* D55A8 001D55A8 2D200002 */   daddu     $4, $16, $0
    /* D55AC 001D55AC 49000010 */  b          .L001D56D4
    /* D55B0 001D55B0 00000000 */   nop
.align 2
  jlabel .L001D55B4
    /* D55B4 001D55B4 40B6828F */  lw         $2, %gp_rel(D_0062C230)($28)
    /* D55B8 001D55B8 F401438C */  lw         $3, 0x1F4($2)
    /* D55BC 001D55BC 3C006010 */  beqz       $3, .L001D56B0
    /* D55C0 001D55C0 00000000 */   nop
    /* D55C4 001D55C4 8C37040C */  jal        GetLastQuaternion
    /* D55C8 001D55C8 2000D127 */   addiu     $17, $30, 0x20
    /* D55CC 001D55CC 9237040C */  jal        GetTableSin
    /* D55D0 001D55D0 2D804000 */   daddu     $16, $2, $0
    /* D55D4 001D55D4 2D200002 */  daddu      $4, $16, $0
    /* D55D8 001D55D8 2D284000 */  daddu      $5, $2, $0
    /* D55DC 001D55DC 5238040C */  jal        func_0010E148
    /* D55E0 001D55E0 2D302002 */   daddu     $6, $17, $0
    /* D55E4 001D55E4 1E14040C */  jal        func_00105078
    /* D55E8 001D55E8 00000000 */   nop
    /* D55EC 001D55EC 8C37040C */  jal        GetLastQuaternion
    /* D55F0 001D55F0 2D804000 */   daddu     $16, $2, $0
    /* D55F4 001D55F4 2D200002 */  daddu      $4, $16, $0
    /* D55F8 001D55F8 7438040C */  jal        func_0010E1D0
    /* D55FC 001D55FC 2D284000 */   daddu     $5, $2, $0
    /* D5600 001D5600 3000B027 */  addiu      $16, $29, 0x30
    /* D5604 001D5604 2700053C */  lui        $5, %hi(D_002724B0)
    /* D5608 001D5608 2D200002 */  daddu      $4, $16, $0
    /* D560C 001D560C F036040C */  jal        GetInverseQuaternion
    /* D5610 001D5610 B024A524 */   addiu     $5, $5, %lo(D_002724B0)
    /* D5614 001D5614 2000B227 */  addiu      $18, $29, 0x20
    /* D5618 001D5618 1000C526 */  addiu      $5, $22, 0x10
    /* D561C 001D561C 2D302002 */  daddu      $6, $17, $0
    /* D5620 001D5620 6238040C */  jal        func_0010E188
    /* D5624 001D5624 2D204002 */   daddu     $4, $18, $0
    /* D5628 001D5628 3AAB8597 */  lhu        $5, %gp_rel(D_0062B72A)($28)
    /* D562C 001D562C 2D200002 */  daddu      $4, $16, $0
    /* D5630 001D5630 23280500 */  negu       $5, $5
    /* D5634 001D5634 002C0500 */  sll        $5, $5, 16
    /* D5638 001D5638 6239040C */  jal        func_0010E588
    /* D563C 001D563C 032C0500 */   sra       $5, $5, 16
    /* D5640 001D5640 36AB8597 */  lhu        $5, %gp_rel(D_0062B726)($28)
    /* D5644 001D5644 2D200002 */  daddu      $4, $16, $0
    /* D5648 001D5648 23280500 */  negu       $5, $5
    /* D564C 001D564C 002C0500 */  sll        $5, $5, 16
    /* D5650 001D5650 3A39040C */  jal        func_0010E4E8
    /* D5654 001D5654 032C0500 */   sra       $5, $5, 16
    /* D5658 001D5658 34AB8597 */  lhu        $5, %gp_rel(D_0062B724)($28)
    /* D565C 001D565C 2D200002 */  daddu      $4, $16, $0
    /* D5660 001D5660 23280500 */  negu       $5, $5
    /* D5664 001D5664 002C0500 */  sll        $5, $5, 16
    /* D5668 001D5668 6239040C */  jal        func_0010E588
    /* D566C 001D566C 032C0500 */   sra       $5, $5, 16
    /* D5670 001D5670 3800C28F */  lw         $2, 0x38($30)
    /* D5674 001D5674 2D200002 */  daddu      $4, $16, $0
    /* D5678 001D5678 28B6868F */  lw         $6, %gp_rel(D_0062C218)($28)
    /* D567C 001D567C 2D280002 */  daddu      $5, $16, $0
    /* D5680 001D5680 40110200 */  sll        $2, $2, 5
    /* D5684 001D5684 2130C200 */  addu       $6, $6, $2
    /* D5688 001D5688 5238040C */  jal        func_0010E148
    /* D568C 001D568C 1000C624 */   addiu     $6, $6, 0x10
    /* D5690 001D5690 2D200002 */  daddu      $4, $16, $0
    /* D5694 001D5694 2D280002 */  daddu      $5, $16, $0
    /* D5698 001D5698 5238040C */  jal        func_0010E148
    /* D569C 001D569C 2D304002 */   daddu     $6, $18, $0
    /* D56A0 001D56A0 DC35040C */  jal        InvertCurrentQuaternion
    /* D56A4 001D56A4 2D200002 */   daddu     $4, $16, $0
    /* D56A8 001D56A8 0A000010 */  b          .L001D56D4
    /* D56AC 001D56AC 00000000 */   nop
.align 2
  .L001D56B0:
    /* D56B0 001D56B0 8C37040C */  jal        GetLastQuaternion
    /* D56B4 001D56B4 00000000 */   nop
    /* D56B8 001D56B8 9237040C */  jal        GetTableSin
    /* D56BC 001D56BC 2D804000 */   daddu     $16, $2, $0
    /* D56C0 001D56C0 2D200002 */  daddu      $4, $16, $0
.align 2
  .L001D56C4:
    /* D56C4 001D56C4 2D284000 */  daddu      $5, $2, $0
    /* D56C8 001D56C8 1000C626 */  addiu      $6, $22, 0x10
.align 2
  .L001D56CC:
    /* D56CC 001D56CC 5238040C */  jal        func_0010E148
    /* D56D0 001D56D0 00000000 */   nop
.align 2
  .L001D56D4:
    /* D56D4 001D56D4 1E14040C */  jal        func_00105078
    /* D56D8 001D56D8 00000000 */   nop
    /* D56DC 001D56DC 8C37040C */  jal        GetLastQuaternion
    /* D56E0 001D56E0 2D804000 */   daddu     $16, $2, $0
    /* D56E4 001D56E4 2D200002 */  daddu      $4, $16, $0
    /* D56E8 001D56E8 7438040C */  jal        func_0010E1D0
    /* D56EC 001D56EC 2D284000 */   daddu     $5, $2, $0
    /* D56F0 001D56F0 11000010 */  b          .L001D5738
    /* D56F4 001D56F4 6002BFDF */   ld        $31, 0x260($29)
.align 2
  jlabel .L001D56F8
    /* D56F8 001D56F8 8C37040C */  jal        GetLastQuaternion
    /* D56FC 001D56FC 00000000 */   nop
    /* D5700 001D5700 9237040C */  jal        GetTableSin
    /* D5704 001D5704 2D804000 */   daddu     $16, $2, $0
    /* D5708 001D5708 2D200002 */  daddu      $4, $16, $0
    /* D570C 001D570C 2D284000 */  daddu      $5, $2, $0
    /* D5710 001D5710 5238040C */  jal        func_0010E148
    /* D5714 001D5714 1000C626 */   addiu     $6, $22, 0x10
    /* D5718 001D5718 1E14040C */  jal        func_00105078
    /* D571C 001D571C 00000000 */   nop
    /* D5720 001D5720 8C37040C */  jal        GetLastQuaternion
    /* D5724 001D5724 2D804000 */   daddu     $16, $2, $0
    /* D5728 001D5728 2D200002 */  daddu      $4, $16, $0
    /* D572C 001D572C 7438040C */  jal        func_0010E1D0
    /* D5730 001D5730 2D284000 */   daddu     $5, $2, $0
.align 2
  .L001D5734:
    /* D5734 001D5734 6002BFDF */  ld         $31, 0x260($29)
.align 2
  .L001D5738:
    /* D5738 001D5738 5002BEDF */  ld         $30, 0x250($29)
    /* D573C 001D573C 4002B7DF */  ld         $23, 0x240($29)
    /* D5740 001D5740 3002B6DF */  ld         $22, 0x230($29)
    /* D5744 001D5744 2002B5DF */  ld         $21, 0x220($29)
    /* D5748 001D5748 1002B4DF */  ld         $20, 0x210($29)
    /* D574C 001D574C 0002B3DF */  ld         $19, 0x200($29)
    /* D5750 001D5750 F001B2DF */  ld         $18, 0x1F0($29)
    /* D5754 001D5754 E001B1DF */  ld         $17, 0x1E0($29)
    /* D5758 001D5758 D001B0DF */  ld         $16, 0x1D0($29)
    /* D575C 001D575C 8002B6C7 */  lwc1       $f22, 0x280($29)
    /* D5760 001D5760 7802B5C7 */  lwc1       $f21, 0x278($29)
    /* D5764 001D5764 7002B4C7 */  lwc1       $f20, 0x270($29)
    /* D5768 001D5768 0800E003 */  jr         $31
    /* D576C 001D576C 9002BD27 */   addiu     $29, $29, 0x290
endlabel ResetStatic2MotionManager
```

## Resume session 2026-07-09 (worktree agent-aab2f8616e9162da0)

Result: best unchanged at rc606 (driver stall 7/30, verdict iterate at session end).
Two rc-neutral but ROM-shape-correct edits are now installed in the TU (kept):
- cases 0x13/0x3: `t = 1.0f;` routed through the reused float temp (ROM keeps
  1.0 in $f22..$f20 from case head: `qA0[3]=t` / `v110[3]=t` + AddMotionMemorySize
  w-arg = t). Verified: built now emits `swc1 $f20,172(sp)` exactly like ROM.
- cases 0x13/0x3 tails: `t = 60.0f;` hoisted before the f_280/f_220 branch;
  the three rate exprs use `(t / (float)((0x3C - D_00271240[0]*0xA)/D_00271240[1]))`.
  ROM keeps 60.0 in $f20 across the three uses (mtc1 at 0x42700000 -> f20).

### THE KNOT (why rc606 is stuck): whole-function global-alloc misassignment

ROM callee-saved layout:  b(blend elem)->s5, nd(D_0062C218 elem)->s6, e(mot elem)->s8,
with s4 and s7 held by case-local classes. Ours: nd->s4, b->s5, e->s6. Nearly all
606 diffs cascade from this (plus a0/a1 scratch and $f swaps downstream).

Mechanism fully mapped this session (use the disposition oracle, below):
- gcc 2.9 global-alloc order = floor_log2(refs)*refs/live_length descending
  (confirmed against the `-dg` dump header "Pass 1 registers ... sorted order").
- find_reg = FIRST free non-conflicting reg in numeric order s0..s7,s8
  (no local-avoidance preference: disproved by probe4).
- Our priorities: nd=2121, b=2112(64 refs exactly at the log2(64) boundary!),
  e=1862. Trio positions 54/55/59 of 135 global allocnos.
- b->s5 in ROM requires an s4-taker with pri>2112 conflicting b (i.e. anything);
  nd->s6 additionally requires b before nd (nd refs-1 flips it: `default: goto
  sin_tail` single-source-site = T1, rc668 standalone) plus an nd-conflicting
  (case-head-live) s4/s5 blocker; e->s8 requires two e-conflicting blockers on
  s6/s7 (deep-case-0x13/0x2D-live allocnos with pri in (1862, ~2100)).

### Fold experiments (dev_data_model "fold to ONE" costume):
- int-scratch fold (function-scope q/n/i): b LOCKS to s5 correctly, e s6->s7
  (i-shared 15refs/238=pri1890 takes s6 pre-e). rc 612.
- full scratch fold (+pv/w/w2/s0/t/rot/ang/len2): e LANDS ON s8 (mem wrongly
  gets a reg though). rc 763.
- qa/qb fold: qa-shared = 76refs/1277 pri 3570 -> takes s3 pre-trio. rc 769.
- The rc regressions are insn-level traffic changes (spill/copy shapes), not the
  trio: the right subset is BETWEEN int-fold and full-fold. Missing pieces:
  (1) an s4-taker with pri>2112 (nothing legit found yet — all per-case pointer
  temps top out ~2884 but their own conflicts don't reach past s3);
  (2) a second e-conflicting s7 blocker in (1862,2100);
  (3) mem must stay spilled (0x1A0 reloads) once regs free up.

### ROM micro-evidence for the dev shapes (found, partially applied):
- per-arm `q1p = b->q1` materialization in 0x13 (3 arms + both loop sub-arms),
  0x14, 0x16 (applied this session; rc-neutral at 607->606 with rest).
- case-0x13 loop-arm bundle: pv(spill 0x1B8), q1p, v120p(spill 0x1BC),
  v70p(s3), qF0p(s4!), v110p(s7!), qn=v130(s2); tbl0=D_00271BF0 (s1) set after
  the merge; fzero(f21)=0.0 set after DebugDisp1 jal. (Tried as H3b: rc708 while
  trio still wrong — retry AFTER the trio is fixed, order matters.)
- pv spill slot 0x1B8 is SHARED by cases 0x13 and 0x3 => pv really is ONE
  function-scope variable in dev (seed already has this).
- case-2D: qb spilled to 0x1B0; qa-2D = s7 in ROM (the e-blocker!); i-2D on s5
  (shares dead-b), w170->s4, w190->s3. Case-2D loop cluster is the s7-chain.
- case-0x13 head: qa spilled to 0x1A4, qb to 0x1A8 (first spill slots after mem).
- case 0x1: hold=0 is zeroed BEFORE the n==1 branch (tried alone: rc635 — only
  works with the rest of the knot).

### Tooling for resume (fast, no driver roundtrip):
Disposition oracle (~20s): compile the TU with `-dl`/`-dg` using
tools/cc/ee-gcc2.9-991111 and grep the `.greg` "Register dispositions:" for
pseudos 86(e)/87(b)/88(nd): target `87 in 21, 88 in 22, 86 in 30`.
The `.greg` dump also prints the exact allocation order ("N regs to allocate:")
and per-allocno conflict lists (";; N conflicts: ...") — simulate find_reg
directly instead of guessing. Script kept at (scratchpad)/oracle.sh pattern:
see notes in this file.

Levers tried this session (driver ledger): T1 default-goto (668), hold=0 hoist
(635), per-arm q1p (607), 0x13 bundle (708), pv loop-arm scoping (607),
t=1.0f routing (606=), t=60.0f routing (606=), scratch-fold (763),
int-fold (612). Best remains 606; stall 7/30 at handoff.

## Resume session 2026-07-09b (worktree agent-aa7b4d4948fecf57d)

Result: best UNCHANGED at rc606 (tree restored to seed). Driver: 3 novel steps
(727, 695, 669) + 3 non-novel; stall 3/30, verdict iterate at session end.
BUT: 2/3 of the trio is now SOLVED and verified via the disposition oracle.

### TRIO STATUS: b->s5 OK, nd->s6 OK (recipe below), e stuck at s4 (needs s8)

The MINIMAL costume that locks b->s5 AND nd->s6 (oracle-verified twice):
  seed + T1 (default: goto sin_tail) + ONE FUNCTION-SCOPE `float *eqp;`
  with every case head rewritten as:
      eqp = e->quat;
      func_0010E148(GetLastQuaternion(), GetTableSin(), eqp);
      ...
      func_0010E188(qb, nd->quat, eqp);
  (rc669 = T1's +62 tax +1; the tax only pays off once e->s8 lands.)
  - eqp is ROM-CONFIRMED: `addiu $17, $30, 0x20` in the GetLastQuaternion
    delay slot of EVERY e->quat case head (0x22 0x23 0x13 2D 2F...), always
    $17/s1 => consistent with ONE fn-scope var. OURS lands s2 (hard-17 from
    a local-alloc'd s1 in some head block) — a residual site diff.
  - Mechanism: eqp produces an ndX allocno holding s4 before nd's turn
    (pos ~621, refs5/len35 piece), so nd skips s4 (ndX) and s5 (b) -> s6.
  - Per-case eqp does NOT flip nd (tested; nd->s4 again). Fn-scope only.

### find_reg LAW (empirically confirmed many times this session):
first NON-CONFLICTING hard reg in numeric order s0..s7 then s8; SHARING with
non-conflicting earlier holders is preferred over virgin regs (nd repeatedly
shared s4 with 0x13-bundle temps that conflict b but not nd). Plus HARD-reg
conflicts from local-alloc'd block pseudos (e/nd/b all carry hard {16,17,18}
= s0/s1/s2 smears from case-head block-locals).

### THE REMAINING PROBLEM — e: s4-shared instead of s8
e (25 refs/537, pri 186) ladder: s0/s1/s2 hard-blocked; s3 blocked by an eX
allocno (qa-2D-class); s4 held only by NON-eX holders => e SHARES s4. To get
s8, e needs eX holders (or hard smears) on BOTH s4 and s7 before pos ~729:
  - s4 candidate: w170-2D (pseudo w/ 2 arm sets, refs~7/len~69, pri 202 > 186,
    eX via e->state read at line ~1144 inside its range). Ours lands s2;
    ROM has o-loop(s2) + w190(s3) forcing it to s4. Our loop currently gets
    n=s1(ROM-match), i-2D=s8, o=s5, w190=s6-share — the whole 2D cluster is
    one permutation knot that should snap once e vacates s4/s8.
  - s7: NO global allocno holds s7 pre-e in ROM either. ROM 0x23 materializes
    D_002724B0 into $23 (lui $23 at D3160, GetTableSin delay slot) — i.e. ROM
    e is HARD-blocked from s7 by that block-local. Replicating with a `tbl`
    local in 0x23 put it on s1, not s7 (UNSOLVED — why does ROM's tbl-0x23
    pick $23? Suspect local-alloc order/interaction not yet understood).

### ROM register map recovered this session (use for shaping):
- 0x22: qa=s2 qb=s3 q40=s1 v50=s0; head eqp=s1.
- 0x23: qb=s4(!! set D319C, live to tail E148) — the late s4-sharer;
  q1p=b->q1=s6-share (D3444), q2p=s2, q3p=s3; tbl(D_002724B0)=s7(!).
- 0x13 head: mgr=D_0062C230 cached in s0 (lw $16 gp_rel at D3EAC!);
  qa spilled 0x1A4, qb spilled 0x1A8; t=1.0f set at case head into $f20
  (lui/mtc1 BEFORE GetTableSin), qA0[3]=t via swc1 $f20,0xAC.
- 0x13 f_280 arms: qF0p=s4 set at D403C in the SECOND beq's DELAY SLOT
  (covers arms A and B with one set!), q1p=s6-share per-arm (D404C/D4428),
  pv=v60 spilled 0x1B8 (sw in arm, e.g. D4074).
- 0x13 loop arm: i=s1 (PER-CASE i! int-fold is WRONG), qn(v130)=s2,
  v70p=s3, v110p=s7 set TWICE (D40B0/D4128, the n!=-1 / n==-1 sub-arms),
  used at TurnObjectMatrix/_ApplyCurrentMatrix/Transpose/MulL/E088;
  tbl0(D_00271BF0)=s1-region, fzero=0.0f in $f21 (passed as
  func_00105108(5.0f,-3.0f,fzero)); v60[1] accessed DIRECT at 0x64(sp)
  (do NOT rewrite v60 accesses through pv).
- 2D: eqp=s1, t1=s0, qa=s7, qb spilled 0x1B0, pv(SEPARATE case-local!)
  spilled 0x1C0, endflag spilled 0x1B4, i=s5 (shares dead b, set very early
  D5254), n=s1 (after eqp dead), o=s2, o->pos temp=s0, w190=s3,
  w170=s4 (set in BOTH arms D52F4/D5300), ang=$f21, len2=$f20
  (our build ALREADY matches the f21/f20 choice); e->state RELOADED from
  4($30) after the merge (dev used e->state, not st).
- 0x2F: qa=s0, qb=s2, eqp=s1.

### Session steps (driver ledger): knot-costume-v1 (int-fold+T1+bundle) 727;
ROM-costume-v2 (per-case q/n/i + fn-scope eqp + T1 + 0x13 per-arm
qF0p/q1p/v110p bundle + t-routing) 695; minimal knot (seed+T1+eqp) 669.
t=1.0f/t=60.0f re-application on the plain seed: NON-NOVEL (no codegen
change in seed context; only bites with the 0x13 head shape from ROM).

### NEXT SESSION ATTACK (in order):
1. Fix eqp s2->s1 (find/dislodge the local s1 in the eqp-live head block;
   candidates printed by lreg ';; Register N in 17' list — blocks 30/31/66).
2. Crack e's s7 hard-block: understand ROM tbl-0x23 -> $23. Try shaping the
   0x23 head so the D_002724B0 temp is forced past s0..s6 (its block also
   holds t1=s0(local), eqp=s1, qb... maybe with q2p/q3p/qb early-set the
   local stack deepens). Also try mgr-13 s0-cache + qa/qb-13 SPILL shapes
   (function too fat -> spills) which deepen 0x13's stacks.
3. Then w170->s4 should follow once o(s2)/w190(s3) stack (check with oracle),
   giving e: s3(eX qa-2D) s4(eX w170) s5(b) s6(nd) s7(hard) -> s8.
4. Only then re-add the 0x13 bundle + per-arm q1p/qF0p/v110p (they were
   rc-noise while the trio was wrong) and re-apply t=1.0f/60.0f routing.
Oracle: scratchpad oracle2.sh (trio from prologue) + oracle.sh (-dl/-dg
dumps); parse greg 'Register dispositions:' with the FULL section (early
sessions truncated at 6000 chars and mis-read holders).
