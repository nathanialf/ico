/* Symbols accessed via $gp register */
.extern D_00633798, 1

.align 3
nonmatching func_0017E588, 0x24

glabel func_0017E588
    /* 7E588 0017E588 A8AE838F */  lw         $3, (D_00633798) /* gp_rel: (D_00633798) */
    /* 7E58C 0017E58C 03006010 */  beqz       $3, .L0017E59C
    /* 7E590 0017E590 03000224 */   addiu     $2, $0, 0x3
    /* 7E594 0017E594 03006214 */  bne        $3, $2, .L0017E5A4
    /* 7E598 0017E598 00000000 */   nop
.align 2
  .L0017E59C:
    /* 7E59C 0017E59C 0800E003 */  jr         $31
    /* 7E5A0 0017E5A0 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0017E5A4:
    /* 7E5A4 0017E5A4 0800E003 */  jr         $31
    /* 7E5A8 0017E5A8 01000224 */   addiu     $2, $0, 0x1
endlabel func_0017E588
    /* 7E5AC 0017E5AC 00000000 */  nop
