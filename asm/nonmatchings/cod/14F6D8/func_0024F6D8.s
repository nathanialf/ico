.align 3
nonmatching func_0024F6D8, 0x34

glabel func_0024F6D8
    /* 14F6D8 0024F6D8 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 14F6DC 0024F6DC 0000BFFF */  sd         $31, 0x0($29)
    /* 14F6E0 0024F6E0 683D090C */  jal        func_0024F5A0
    /* 14F6E4 0024F6E4 40000724 */   addiu     $7, $0, 0x40
    /* 14F6E8 0024F6E8 2D204000 */  daddu      $4, $2, $0
    /* 14F6EC 0024F6EC 04008014 */  bnez       $4, .L0024F700
    /* 14F6F0 0024F6F0 0000BFDF */   ld        $31, 0x0($29)
    /* 14F6F4 0024F6F4 5500033C */  lui        $3, %hi(D_005523D0)
    /* 14F6F8 0024F6F8 0B000224 */  addiu      $2, $0, 0xB
    /* 14F6FC 0024F6FC D02362AC */  sw         $2, %lo(D_005523D0)($3)
.align 2
  .L0024F700:
    /* 14F700 0024F700 2D108000 */  daddu      $2, $4, $0
    /* 14F704 0024F704 0800E003 */  jr         $31
    /* 14F708 0024F708 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_0024F6D8
    /* 14F70C 0024F70C 00000000 */  nop
