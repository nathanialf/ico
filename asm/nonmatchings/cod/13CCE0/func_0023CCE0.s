.align 3
nonmatching func_0023CCE0, 0x3C

glabel func_0023CCE0
    /* 13CCE0 0023CCE0 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 13CCE4 0023CCE4 0000BFFF */  sd         $31, 0x0($29)
    /* 13CCE8 0023CCE8 D833060C */  jal        func_0018CF60
    /* 13CCEC 0023CCEC 00000000 */   nop
    /* 13CCF0 0023CCF0 040041C4 */  lwc1       $f1, 0x4($2)
    /* 13CCF4 0023CCF4 7AC4013C */  lui        $1, (0xC47A0000 >> 16)
    /* 13CCF8 0023CCF8 00008144 */  mtc1       $1, $f0
    /* 13CCFC 0023CCFC 34000146 */  c.lt.s     $f0, $f1
    /* 13CD00 0023CD00 00000000 */  nop
    /* 13CD04 0023CD04 02000045 */  bc1f       .L0023CD10
    /* 13CD08 0023CD08 FFFF0224 */   addiu     $2, $0, -0x1
    /* 13CD0C 0023CD0C 2D100000 */  daddu      $2, $0, $0
.align 2
  .L0023CD10:
    /* 13CD10 0023CD10 0000BFDF */  ld         $31, 0x0($29)
    /* 13CD14 0023CD14 0800E003 */  jr         $31
    /* 13CD18 0023CD18 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_0023CCE0
