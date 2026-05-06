.align 3
nonmatching func_00251E00, 0x14

glabel func_00251E00
    /* 151E00 00251E00 4000838C */  lw         $3, 0x40($4)
    /* 151E04 00251E04 01000224 */  addiu      $2, $0, 0x1
    /* 151E08 00251E08 F80062AC */  sw         $2, 0xF8($3)
    /* 151E0C 00251E0C 0800E003 */  jr         $31
    /* 151E10 00251E10 F00065FC */   sd        $5, 0xF0($3)
endlabel func_00251E00
