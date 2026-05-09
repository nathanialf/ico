.align 3
nonmatching func_0017D2C8, 0x40

glabel func_0017D2C8
    /* 7D2C8 0017D2C8 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 7D2CC 0017D2CC 0000BFFF */  sd         $31, 0x0($29)
    /* 7D2D0 0017D2D0 62F8050C */  jal        func_0017E188
    /* 7D2D4 0017D2D4 00000000 */   nop
    /* 7D2D8 0017D2D8 05004010 */  beqz       $2, .L0017D2F0
    /* 7D2DC 0017D2DC 5600043C */   lui       $4, %hi(D_00559EA8)
    /* 7D2E0 0017D2E0 42A8070C */  jal        func_001EA108
    /* 7D2E4 0017D2E4 2D204000 */   daddu     $4, $2, $0
    /* 7D2E8 0017D2E8 05000010 */  b          .L0017D300
    /* 7D2EC 0017D2EC 0000BFDF */   ld        $31, 0x0($29)
.align 2
  .L0017D2F0:
    /* 7D2F0 0017D2F0 8A9B060C */  jal        func_001A6E28
    /* 7D2F4 0017D2F4 A89E8424 */   addiu     $4, $4, %lo(D_00559EA8)
    /* 7D2F8 0017D2F8 00008044 */  mtc1       $0, $f0
    /* 7D2FC 0017D2FC 0000BFDF */  ld         $31, 0x0($29)
.align 2
  .L0017D300:
    /* 7D300 0017D300 0800E003 */  jr         $31
    /* 7D304 0017D304 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_0017D2C8
