.align 3
nonmatching func_0010D180, 0x14

glabel func_0010D180
    /* D180 0010D180 5C01828C */  lw         $2, 0x15C($4)
    /* D184 0010D184 0008438C */  lw         $3, 0x800($2)
    /* D188 0010D188 3000628C */  lw         $2, 0x30($3)
    /* D18C 0010D18C 0800E003 */  jr         $31
    /* D190 0010D190 2B100200 */   sltu      $2, $0, $2
endlabel func_0010D180
    /* D194 0010D194 00000000 */  nop
