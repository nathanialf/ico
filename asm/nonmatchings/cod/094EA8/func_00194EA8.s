.align 3
nonmatching func_00194EA8, 0x14

glabel func_00194EA8
    /* 94EA8 00194EA8 6D00023C */  lui        $2, %hi(D_006D35C0)
    /* 94EAC 00194EAC C0354224 */  addiu      $2, $2, %lo(D_006D35C0)
    /* 94EB0 00194EB0 18004DE4 */  swc1       $f13, 0x18($2)
    /* 94EB4 00194EB4 0800E003 */  jr         $31
    /* 94EB8 00194EB8 14004CE4 */   swc1      $f12, 0x14($2)
endlabel func_00194EA8
