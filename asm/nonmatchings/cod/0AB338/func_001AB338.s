.align 3
nonmatching func_001AB338, 0x3C

glabel func_001AB338
    /* AB338 001AB338 E0FFBD27 */  addiu      $29, $29, -0x20
    /* AB33C 001AB33C 0000B0FF */  sd         $16, 0x0($29)
    /* AB340 001AB340 1000BFFF */  sd         $31, 0x10($29)
    /* AB344 001AB344 9C14090C */  jal        func_00245270
    /* AB348 001AB348 2D808000 */   daddu     $16, $4, $0
    /* AB34C 001AB34C 8A14090C */  jal        func_00245228
    /* AB350 001AB350 2D200002 */   daddu     $4, $16, $0
    /* AB354 001AB354 2D200002 */  daddu      $4, $16, $0
    /* AB358 001AB358 5E14090C */  jal        func_00245178
    /* AB35C 001AB35C 2D280000 */   daddu     $5, $0, $0
    /* AB360 001AB360 2D200002 */  daddu      $4, $16, $0
    /* AB364 001AB364 1000BFDF */  ld         $31, 0x10($29)
    /* AB368 001AB368 0000B0DF */  ld         $16, 0x0($29)
    /* AB36C 001AB36C 32140908 */  j          func_002450C8
    /* AB370 001AB370 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_001AB338
    /* AB374 001AB374 00000000 */  nop
