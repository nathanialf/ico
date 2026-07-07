# actCommonRopeCliff — parked

VRAM: 0x00156D88 (file_off 0x056D88)
Asm source: asm/aug6/nonmatchings/fumi/src/commonact/actCommonRopeCliff.s

## Attempt at 2026-07-07

**Reason parked:** rc31 near-miss: switch(state)+shared 'one'=1 const gives correct body+comparison shape; residual = s0/s1 callee-saved swap (obj vs a1) + climb-block ordering/cross-jump. permuter territory.

**TU:** `fumi/src/commonact.c`

**Seed:** `tough_nuts/actCommonRopeCliff/actCommonRopeCliff.c`

Disassembly:

```
.align 3
nonmatching actCommonRopeCliff, 0xEC

glabel actCommonRopeCliff
    /* 56D88 00156D88 C0FFBD27 */  addiu      $29, $29, -0x40
    /* 56D8C 00156D8C 2000B2FF */  sd         $18, 0x20($29)
    /* 56D90 00156D90 1000B1FF */  sd         $17, 0x10($29)
    /* 56D94 00156D94 01001224 */  addiu      $18, $0, 0x1
    /* 56D98 00156D98 0000B0FF */  sd         $16, 0x0($29)
    /* 56D9C 00156D9C 3000BFFF */  sd         $31, 0x30($29)
    /* 56DA0 00156DA0 2D808000 */  daddu      $16, $4, $0
    /* 56DA4 00156DA4 6401028E */  lw         $2, 0x164($16)
    /* 56DA8 00156DA8 7006448C */  lw         $4, 0x670($2)
    /* 56DAC 00156DAC 1003838C */  lw         $3, 0x310($4)
    /* 56DB0 00156DB0 10007210 */  beq        $3, $18, .L00156DF4
    /* 56DB4 00156DB4 2D88A000 */   daddu     $17, $5, $0
    /* 56DB8 00156DB8 02006228 */  slti       $2, $3, 0x2
    /* 56DBC 00156DBC 05004050 */  beql       $2, $0, .L00156DD4
    /* 56DC0 00156DC0 02000224 */   addiu     $2, $0, 0x2
    /* 56DC4 00156DC4 07006010 */  beqz       $3, .L00156DE4
    /* 56DC8 00156DC8 3000BFDF */   ld        $31, 0x30($29)
    /* 56DCC 00156DCC 25000010 */  b          .L00156E64
    /* 56DD0 00156DD0 2000B2DF */   ld        $18, 0x20($29)
.align 2
  .L00156DD4:
    /* 56DD4 00156DD4 17006210 */  beq        $3, $2, .L00156E34
    /* 56DD8 00156DD8 3000BFDF */   ld        $31, 0x30($29)
    /* 56DDC 00156DDC 21000010 */  b          .L00156E64
    /* 56DE0 00156DE0 2000B2DF */   ld        $18, 0x20($29)
.align 2
  .L00156DE4:
    /* 56DE4 00156DE4 1F003256 */  bnel       $17, $18, .L00156E64
    /* 56DE8 00156DE8 2000B2DF */   ld        $18, 0x20($29)
    /* 56DEC 00156DEC 16000010 */  b          .L00156E48
    /* 56DF0 00156DF0 00000000 */   nop
.align 2
  .L00156DF4:
    /* 56DF4 00156DF4 03002012 */  beqz       $17, .L00156E04
    /* 56DF8 00156DF8 02000224 */   addiu     $2, $0, 0x2
    /* 56DFC 00156DFC 07002216 */  bne        $17, $2, .L00156E1C
    /* 56E00 00156E00 2D200002 */   daddu     $4, $16, $0
.align 2
  .L00156E04:
    /* 56E04 00156E04 545B050C */  jal        actCommonRopeClimbEnd1
    /* 56E08 00156E08 2D200002 */   daddu     $4, $16, $0
    /* 56E0C 00156E0C 6401028E */  lw         $2, 0x164($16)
    /* 56E10 00156E10 7006438C */  lw         $3, 0x670($2)
    /* 56E14 00156E14 11000010 */  b          .L00156E5C
    /* 56E18 00156E18 100371AC */   sw        $17, 0x310($3)
.align 2
  .L00156E1C:
    /* 56E1C 00156E1C 3000BFDF */  ld         $31, 0x30($29)
    /* 56E20 00156E20 2000B2DF */  ld         $18, 0x20($29)
    /* 56E24 00156E24 1000B1DF */  ld         $17, 0x10($29)
    /* 56E28 00156E28 0000B0DF */  ld         $16, 0x0($29)
    /* 56E2C 00156E2C 465B0508 */  j          func_00156D18
    /* 56E30 00156E30 4000BD27 */   addiu     $29, $29, 0x40
.align 2
  .L00156E34:
    /* 56E34 00156E34 01002052 */  beql       $17, $0, .L00156E3C
    /* 56E38 00156E38 100380AC */   sw        $0, 0x310($4)
.align 2
  .L00156E3C:
    /* 56E3C 00156E3C 03000224 */  addiu      $2, $0, 0x3
    /* 56E40 00156E40 07002216 */  bne        $17, $2, .L00156E60
    /* 56E44 00156E44 3000BFDF */   ld        $31, 0x30($29)
.align 2
  .L00156E48:
    /* 56E48 00156E48 465B050C */  jal        func_00156D18
    /* 56E4C 00156E4C 2D200002 */   daddu     $4, $16, $0
    /* 56E50 00156E50 6401028E */  lw         $2, 0x164($16)
    /* 56E54 00156E54 7006438C */  lw         $3, 0x670($2)
    /* 56E58 00156E58 100372AC */  sw         $18, 0x310($3)
.align 2
  .L00156E5C:
    /* 56E5C 00156E5C 3000BFDF */  ld         $31, 0x30($29)
.align 2
  .L00156E60:
    /* 56E60 00156E60 2000B2DF */  ld         $18, 0x20($29)
.align 2
  .L00156E64:
    /* 56E64 00156E64 1000B1DF */  ld         $17, 0x10($29)
    /* 56E68 00156E68 0000B0DF */  ld         $16, 0x0($29)
    /* 56E6C 00156E6C 0800E003 */  jr         $31
    /* 56E70 00156E70 4000BD27 */   addiu     $29, $29, 0x40
endlabel actCommonRopeCliff
    /* 56E74 00156E74 00000000 */  nop
```
