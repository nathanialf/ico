# HandMgr_Print — parked

VRAM: 0x00171028 (file_off 0x071028)
Asm source: asm/aug6/nonmatchings/fumi/src/girl_act/HandMgr_Print.s

## Attempt at 2026-06-21

**Reason parked:** override=permute

**TU:** `fumi/src/girl_act.c`

**Seed:** `tough_nuts/HandMgr_Print/HandMgr_Print.c`

Disassembly:

```
.align 3
nonmatching HandMgr_Print, 0x108

glabel HandMgr_Print
    /* 71028 00171028 94A3838F */  lw         $3, %gp_rel(D_0062AF84)($28)
    /* 7102C 0017102C B0FFBD27 */  addiu      $29, $29, -0x50
    /* 71030 00171030 4000BFFF */  sd         $31, 0x40($29)
    /* 71034 00171034 3000B2FF */  sd         $18, 0x30($29)
    /* 71038 00171038 01006330 */  andi       $3, $3, 0x1
    /* 7103C 0017103C 2000B1FF */  sd         $17, 0x20($29)
    /* 71040 00171040 1000B0FF */  sd         $16, 0x10($29)
    /* 71044 00171044 34006010 */  beqz       $3, .L00171118
    /* 71048 00171048 0000A2AF */   sw        $2, 0x0($29)
    /* 7104C 0017104C 2800023C */  lui        $2, %hi(D_00284740)
    /* 71050 00171050 5500073C */  lui        $7, %hi(D_00553BF0)
    /* 71054 00171054 40475224 */  addiu      $18, $2, %lo(D_00284740)
    /* 71058 00171058 FF0F063C */  lui        $6, (0xFFFFFFF >> 16)
    /* 7105C 0017105C 500040C6 */  lwc1       $f0, 0x50($18)
    /* 71060 00171060 F03BE724 */  addiu      $7, $7, %lo(D_00553BF0)
    /* 71064 00171064 540041C6 */  lwc1       $f1, 0x54($18)
    /* 71068 00171068 0A000424 */  addiu      $4, $0, 0xA
    /* 7106C 0017106C A4000046 */  .word      0x460000A4                    # cvt.w.s    $f2, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* 71070 00171070 00100844 */  mfc1       $8, $f2
    /* 71074 00171074 3C000524 */  addiu      $5, $0, 0x3C
    /* 71078 00171078 24080046 */  .word      0x46000824                    # cvt.w.s    $f0, $f1 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* 7107C 0017107C 00000944 */  mfc1       $9, $f0
    /* 71080 00171080 F48F060C */  jal        traceLine
    /* 71084 00171084 FFFFC634 */   ori       $6, $6, (0xFFFFFFF & 0xFFFF)
    /* 71088 00171088 94A3828F */  lw         $2, %gp_rel(D_0062AF84)($28)
    /* 7108C 0017108C 01004230 */  andi       $2, $2, 0x1
    /* 71090 00171090 21004010 */  beqz       $2, .L00171118
    /* 71094 00171094 5500073C */   lui       $7, %hi(D_00553C00)
    /* 71098 00171098 FF0F063C */  lui        $6, (0xFFFFFFF >> 16)
    /* 7109C 0017109C 58004892 */  lbu        $8, 0x58($18)
    /* 710A0 001710A0 003CE724 */  addiu      $7, $7, %lo(D_00553C00)
    /* 710A4 001710A4 59004992 */  lbu        $9, 0x59($18)
    /* 710A8 001710A8 0A000424 */  addiu      $4, $0, 0xA
    /* 710AC 001710AC 5B004A92 */  lbu        $10, 0x5B($18)
    /* 710B0 001710B0 46000524 */  addiu      $5, $0, 0x46
    /* 710B4 001710B4 5D004B92 */  lbu        $11, 0x5D($18)
    /* 710B8 001710B8 F48F060C */  jal        traceLine
    /* 710BC 001710BC FFFFC634 */   ori       $6, $6, (0xFFFFFFF & 0xFFFF)
    /* 710C0 001710C0 94A3828F */  lw         $2, %gp_rel(D_0062AF84)($28)
    /* 710C4 001710C4 01004230 */  andi       $2, $2, 0x1
    /* 710C8 001710C8 13004010 */  beqz       $2, .L00171118
    /* 710CC 001710CC 5500103C */   lui       $16, %hi(D_00553C20)
    /* 710D0 001710D0 200040C6 */  lwc1       $f0, 0x20($18)
    /* 710D4 001710D4 203C1026 */  addiu      $16, $16, %lo(D_00553C20)
    /* 710D8 001710D8 40004426 */  addiu      $4, $18, 0x40
    /* 710DC 001710DC 64000046 */  .word      0x46000064                    # cvt.w.s    $f1, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* 710E0 001710E0 00081144 */  mfc1       $17, $f1
    /* 710E4 001710E4 4247060C */  jal        _RotyGV
    /* 710E8 001710E8 30004526 */   addiu     $5, $18, 0x30
    /* 710EC 001710EC 500040C6 */  lwc1       $f0, 0x50($18)
    /* 710F0 001710F0 FF0F063C */  lui        $6, (0xFFFFFFF >> 16)
    /* 710F4 001710F4 2D380002 */  daddu      $7, $16, $0
    /* 710F8 001710F8 2D402002 */  daddu      $8, $17, $0
    /* 710FC 001710FC 64000046 */  .word      0x46000064                    # cvt.w.s    $f1, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* 71100 00171100 00080A44 */  mfc1       $10, $f1
    /* 71104 00171104 2D484000 */  daddu      $9, $2, $0
    /* 71108 00171108 0A000424 */  addiu      $4, $0, 0xA
    /* 7110C 0017110C 50000524 */  addiu      $5, $0, 0x50
    /* 71110 00171110 F48F060C */  jal        traceLine
    /* 71114 00171114 FFFFC634 */   ori       $6, $6, (0xFFFFFFF & 0xFFFF)
.align 2
  .L00171118:
    /* 71118 00171118 4000BFDF */  ld         $31, 0x40($29)
    /* 7111C 0017111C 3000B2DF */  ld         $18, 0x30($29)
    /* 71120 00171120 2000B1DF */  ld         $17, 0x20($29)
    /* 71124 00171124 1000B0DF */  ld         $16, 0x10($29)
    /* 71128 00171128 0800E003 */  jr         $31
    /* 7112C 0017112C 5000BD27 */   addiu     $29, $29, 0x50
endlabel HandMgr_Print
```

---

## Attempt at 2026-07-07

**Reason parked:** rc4 permuter-domain v0/v1 prologue swap: ROM flag->$3 + dead-home-store $2 in beqz delay; mine flag->$2 + home $3 before branch. Hand idioms fold. Already permuter-seeded (override=permute).

**TU:** `fumi/src/girl_act.c`

**Seed:** `tough_nuts/HandMgr_Print/HandMgr_Print.1.c`

Disassembly:

```
.align 3
nonmatching HandMgr_Print, 0x108

glabel HandMgr_Print
    /* 71028 00171028 94A3838F */  lw         $3, %gp_rel(D_0062AF84)($28)
    /* 7102C 0017102C B0FFBD27 */  addiu      $29, $29, -0x50
    /* 71030 00171030 4000BFFF */  sd         $31, 0x40($29)
    /* 71034 00171034 3000B2FF */  sd         $18, 0x30($29)
    /* 71038 00171038 01006330 */  andi       $3, $3, 0x1
    /* 7103C 0017103C 2000B1FF */  sd         $17, 0x20($29)
    /* 71040 00171040 1000B0FF */  sd         $16, 0x10($29)
    /* 71044 00171044 34006010 */  beqz       $3, .L00171118
    /* 71048 00171048 0000A2AF */   sw        $2, 0x0($29)
    /* 7104C 0017104C 2800023C */  lui        $2, %hi(D_00284740)
    /* 71050 00171050 5500073C */  lui        $7, %hi(D_00553BF0)
    /* 71054 00171054 40475224 */  addiu      $18, $2, %lo(D_00284740)
    /* 71058 00171058 FF0F063C */  lui        $6, (0xFFFFFFF >> 16)
    /* 7105C 0017105C 500040C6 */  lwc1       $f0, 0x50($18)
    /* 71060 00171060 F03BE724 */  addiu      $7, $7, %lo(D_00553BF0)
    /* 71064 00171064 540041C6 */  lwc1       $f1, 0x54($18)
    /* 71068 00171068 0A000424 */  addiu      $4, $0, 0xA
    /* 7106C 0017106C A4000046 */  .word      0x460000A4                    # cvt.w.s    $f2, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* 71070 00171070 00100844 */  mfc1       $8, $f2
    /* 71074 00171074 3C000524 */  addiu      $5, $0, 0x3C
    /* 71078 00171078 24080046 */  .word      0x46000824                    # cvt.w.s    $f0, $f1 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* 7107C 0017107C 00000944 */  mfc1       $9, $f0
    /* 71080 00171080 F48F060C */  jal        traceLine
    /* 71084 00171084 FFFFC634 */   ori       $6, $6, (0xFFFFFFF & 0xFFFF)
    /* 71088 00171088 94A3828F */  lw         $2, %gp_rel(D_0062AF84)($28)
    /* 7108C 0017108C 01004230 */  andi       $2, $2, 0x1
    /* 71090 00171090 21004010 */  beqz       $2, .L00171118
    /* 71094 00171094 5500073C */   lui       $7, %hi(D_00553C00)
    /* 71098 00171098 FF0F063C */  lui        $6, (0xFFFFFFF >> 16)
    /* 7109C 0017109C 58004892 */  lbu        $8, 0x58($18)
    /* 710A0 001710A0 003CE724 */  addiu      $7, $7, %lo(D_00553C00)
    /* 710A4 001710A4 59004992 */  lbu        $9, 0x59($18)
    /* 710A8 001710A8 0A000424 */  addiu      $4, $0, 0xA
    /* 710AC 001710AC 5B004A92 */  lbu        $10, 0x5B($18)
    /* 710B0 001710B0 46000524 */  addiu      $5, $0, 0x46
    /* 710B4 001710B4 5D004B92 */  lbu        $11, 0x5D($18)
    /* 710B8 001710B8 F48F060C */  jal        traceLine
    /* 710BC 001710BC FFFFC634 */   ori       $6, $6, (0xFFFFFFF & 0xFFFF)
    /* 710C0 001710C0 94A3828F */  lw         $2, %gp_rel(D_0062AF84)($28)
    /* 710C4 001710C4 01004230 */  andi       $2, $2, 0x1
    /* 710C8 001710C8 13004010 */  beqz       $2, .L00171118
    /* 710CC 001710CC 5500103C */   lui       $16, %hi(D_00553C20)
    /* 710D0 001710D0 200040C6 */  lwc1       $f0, 0x20($18)
    /* 710D4 001710D4 203C1026 */  addiu      $16, $16, %lo(D_00553C20)
    /* 710D8 001710D8 40004426 */  addiu      $4, $18, 0x40
    /* 710DC 001710DC 64000046 */  .word      0x46000064                    # cvt.w.s    $f1, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* 710E0 001710E0 00081144 */  mfc1       $17, $f1
    /* 710E4 001710E4 4247060C */  jal        _RotyGV
    /* 710E8 001710E8 30004526 */   addiu     $5, $18, 0x30
    /* 710EC 001710EC 500040C6 */  lwc1       $f0, 0x50($18)
    /* 710F0 001710F0 FF0F063C */  lui        $6, (0xFFFFFFF >> 16)
    /* 710F4 001710F4 2D380002 */  daddu      $7, $16, $0
    /* 710F8 001710F8 2D402002 */  daddu      $8, $17, $0
    /* 710FC 001710FC 64000046 */  .word      0x46000064                    # cvt.w.s    $f1, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* 71100 00171100 00080A44 */  mfc1       $10, $f1
    /* 71104 00171104 2D484000 */  daddu      $9, $2, $0
    /* 71108 00171108 0A000424 */  addiu      $4, $0, 0xA
    /* 7110C 0017110C 50000524 */  addiu      $5, $0, 0x50
    /* 71110 00171110 F48F060C */  jal        traceLine
    /* 71114 00171114 FFFFC634 */   ori       $6, $6, (0xFFFFFFF & 0xFFFF)
.align 2
  .L00171118:
    /* 71118 00171118 4000BFDF */  ld         $31, 0x40($29)
    /* 7111C 0017111C 3000B2DF */  ld         $18, 0x30($29)
    /* 71120 00171120 2000B1DF */  ld         $17, 0x20($29)
    /* 71124 00171124 1000B0DF */  ld         $16, 0x10($29)
    /* 71128 00171128 0800E003 */  jr         $31
    /* 7112C 0017112C 5000BD27 */   addiu     $29, $29, 0x50
endlabel HandMgr_Print
```
