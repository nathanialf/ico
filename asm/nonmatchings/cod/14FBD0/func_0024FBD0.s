.align 3
/* Handwritten function */
nonmatching func_0024FBD0, 0x24

glabel func_0024FBD0
    /* 14FBD0 0024FBD0 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 14FBD4 0024FBD4 0000BFFF */  sd         $31, 0x0($29)
    /* 14FBD8 0024FBD8 C603040C */  jal        func_00100F18
    /* 14FBDC 0024FBDC 2D20C000 */   daddu     $4, $6, $0
    /* 14FBE0 0024FBE0 0F000000 */  sync
    /* 14FBE4 0024FBE4 38000042 */  ei /* handwritten instruction */
    /* 14FBE8 0024FBE8 0000BFDF */  ld         $31, 0x0($29)
    /* 14FBEC 0024FBEC 0800E003 */  jr         $31
    /* 14FBF0 0024FBF0 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_0024FBD0
    /* 14FBF4 0024FBF4 00000000 */  nop
