.align 3
nonmatching func_001AE420, 0x40

glabel func_001AE420
    /* AE420 001AE420 D0FFBD27 */  addiu      $29, $29, -0x30
    /* AE424 001AE424 0000B0FF */  sd         $16, 0x0($29)
    /* AE428 001AE428 2D80A000 */  daddu      $16, $5, $0
    /* AE42C 001AE42C 1000B1FF */  sd         $17, 0x10($29)
    /* AE430 001AE430 2D88C000 */  daddu      $17, $6, $0
    /* AE434 001AE434 2000BFFF */  sd         $31, 0x20($29)
    /* AE438 001AE438 B6B7060C */  jal        func_001ADED8
    /* AE43C 001AE43C 2D28E000 */   daddu     $5, $7, $0
    /* AE440 001AE440 2D184000 */  daddu      $3, $2, $0
    /* AE444 001AE444 2000BFDF */  ld         $31, 0x20($29)
    /* AE448 001AE448 300070AC */  sw         $16, 0x30($3)
    /* AE44C 001AE44C 340071AC */  sw         $17, 0x34($3)
    /* AE450 001AE450 1000B1DF */  ld         $17, 0x10($29)
    /* AE454 001AE454 0000B0DF */  ld         $16, 0x0($29)
    /* AE458 001AE458 0800E003 */  jr         $31
    /* AE45C 001AE45C 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_001AE420
