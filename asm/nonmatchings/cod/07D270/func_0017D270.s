.align 3
nonmatching func_0017D270, 0x54

glabel func_0017D270
    /* 7D270 0017D270 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 7D274 0017D274 0000B0FF */  sd         $16, 0x0($29)
    /* 7D278 0017D278 1000BFFF */  sd         $31, 0x10($29)
    /* 7D27C 0017D27C D4FA040C */  jal        func_0013EB50
    /* 7D280 0017D280 00000000 */   nop
    /* 7D284 0017D284 2D804000 */  daddu      $16, $2, $0
    /* 7D288 0017D288 0A000012 */  beqz       $16, .L0017D2B4
    /* 7D28C 0017D28C 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0017D290:
    /* 7D290 0017D290 664F070C */  jal        func_001D3D98
    /* 7D294 0017D294 2D200002 */   daddu     $4, $16, $0
    /* 7D298 0017D298 06004014 */  bnez       $2, .L0017D2B4
    /* 7D29C 0017D29C 2D100002 */   daddu     $2, $16, $0
    /* 7D2A0 0017D2A0 F8FA040C */  jal        func_0013EBE0
    /* 7D2A4 0017D2A4 2D200002 */   daddu     $4, $16, $0
    /* 7D2A8 0017D2A8 2D804000 */  daddu      $16, $2, $0
    /* 7D2AC 0017D2AC F8FF0016 */  bnez       $16, .L0017D290
    /* 7D2B0 0017D2B0 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0017D2B4:
    /* 7D2B4 0017D2B4 1000BFDF */  ld         $31, 0x10($29)
    /* 7D2B8 0017D2B8 0000B0DF */  ld         $16, 0x0($29)
    /* 7D2BC 0017D2BC 0800E003 */  jr         $31
    /* 7D2C0 0017D2C0 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_0017D270
    /* 7D2C4 0017D2C4 00000000 */  nop
