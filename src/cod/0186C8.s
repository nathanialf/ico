.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

/* Handwritten function — MMI 4x4 quadword transpose */
nonmatching func_001186C8, 0x48

glabel func_001186C8
    /* 186C8 001186C8 0000A878 */  lq         $t0, 0x0($a1)
    /* 186CC 001186CC 1000A978 */  lq         $t1, 0x10($a1)
    /* 186D0 001186D0 2000AA78 */  lq         $t2, 0x20($a1)
    /* 186D4 001186D4 3000AB78 */  lq         $t3, 0x30($a1)
    /* 186D8 001186D8 88642871 */  pextlw     $t4, $t1, $t0
    /* 186DC 001186DC A86C2871 */  pextuw     $t5, $t1, $t0
    /* 186E0 001186E0 88746A71 */  pextlw     $t6, $t3, $t2
    /* 186E4 001186E4 A87C6A71 */  pextuw     $t7, $t3, $t2
    /* 186E8 001186E8 8943CC71 */  pcpyld     $t0, $t6, $t4
    /* 186EC 001186EC A94B8E71 */  pcpyud     $t1, $t4, $t6
    /* 186F0 001186F0 8953ED71 */  pcpyld     $t2, $t7, $t5
    /* 186F4 001186F4 A95BAF71 */  pcpyud     $t3, $t5, $t7
    /* 186F8 001186F8 0000887C */  sq         $t0, 0x0($a0)
    /* 186FC 001186FC 1000897C */  sq         $t1, 0x10($a0)
    /* 18700 00118700 20008A7C */  sq         $t2, 0x20($a0)
    /* 18704 00118704 30008B7C */  sq         $t3, 0x30($a0)
    /* 18708 00118708 0800E003 */  jr         $ra
    /* 1870C 0011870C 00000000 */   nop
endlabel func_001186C8
