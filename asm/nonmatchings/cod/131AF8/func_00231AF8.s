.align 3
nonmatching func_00231AF8, 0x3C

glabel func_00231AF8
    /* 131AF8 00231AF8 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 131AFC 00231AFC 0000BFFF */  sd         $31, 0x0($29)
    /* 131B00 00231B00 8CEC050C */  jal        func_0017B230
    /* 131B04 00231B04 1D000424 */   addiu     $4, $0, 0x1D
    /* 131B08 00231B08 08004014 */  bnez       $2, .L00231B2C
    /* 131B0C 00231B0C 0000BFDF */   ld        $31, 0x0($29)
    /* 131B10 00231B10 6200043C */  lui        $4, %hi(D_0061C0D0)
    /* 131B14 00231B14 8A9B060C */  jal        func_001A6E28
    /* 131B18 00231B18 D0C08424 */   addiu     $4, $4, %lo(D_0061C0D0)
    /* 131B1C 00231B1C 0000BFDF */  ld         $31, 0x0($29)
    /* 131B20 00231B20 65010424 */  addiu      $4, $0, 0x165
    /* 131B24 00231B24 96EC0508 */  j          func_0017B258
    /* 131B28 00231B28 1000BD27 */   addiu     $29, $29, 0x10
.align 2
  .L00231B2C:
    /* 131B2C 00231B2C 0800E003 */  jr         $31
    /* 131B30 00231B30 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_00231AF8
    /* 131B34 00231B34 00000000 */  nop
