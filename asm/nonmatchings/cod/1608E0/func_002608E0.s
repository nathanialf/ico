.align 3
nonmatching func_002608E0, 0x1C

glabel func_002608E0
    /* 1608E0 002608E0 00600344 */  mfc1       $3, $f12
    /* 1608E4 002608E4 FF7F023C */  lui        $2, (0x7FFFFFFF >> 16)
    /* 1608E8 002608E8 FFFF4234 */  ori        $2, $2, (0x7FFFFFFF & 0xFFFF)
    /* 1608EC 002608EC 24186200 */  and        $3, $3, $2
    /* 1608F0 002608F0 00008344 */  mtc1       $3, $f0
    /* 1608F4 002608F4 0800E003 */  jr         $31
    /* 1608F8 002608F8 00000000 */   nop
endlabel func_002608E0
    /* 1608FC 002608FC 00000000 */  nop
