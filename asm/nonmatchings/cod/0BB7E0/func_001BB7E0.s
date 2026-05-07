.align 3
nonmatching func_001BB7E0, 0x1C

glabel func_001BB7E0
    /* BB7E0 001BB7E0 6401838C */  lw         $3, 0x164($4)
    /* BB7E4 001BB7E4 1C00629C */  lwu        $2, 0x1C($3)
    /* BB7E8 001BB7E8 3C100200 */  dsll32     $2, $2, 0
    /* BB7EC 001BB7EC 3F100200 */  dsra32     $2, $2, 0
    /* BB7F0 001BB7F0 01004230 */  andi       $2, $2, 0x1
    /* BB7F4 001BB7F4 0800E003 */  jr         $31
    /* BB7F8 001BB7F8 01004238 */   xori      $2, $2, 0x1
endlabel func_001BB7E0
