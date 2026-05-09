/* Symbols accessed via $gp register */
.extern D_00631AE8, 1

.align 3
nonmatching func_0014A0D8, 0x24

glabel func_0014A0D8
    /* 4A0D8 0014A0D8 F891828F */  lw         $2, %gp_rel(D_00631AE8)($gp) /* gp_rel: (D_00631AE8) */
    /* 4A0DC 0014A0DC 03004054 */  bnel       $2, $0, .L0014A0EC
    /* 4A0E0 0014A0E0 6401438C */   lw        $3, 0x164($2)
    /* 4A0E4 0014A0E4 0800E003 */  jr         $31
    /* 4A0E8 0014A0E8 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0014A0EC:
    /* 4A0EC 0014A0EC 180062DC */  ld         $2, 0x18($3)
    /* 4A0F0 0014A0F0 3E110200 */  dsrl32     $2, $2, 4
    /* 4A0F4 0014A0F4 0800E003 */  jr         $31
    /* 4A0F8 0014A0F8 01004230 */   andi      $2, $2, 0x1
endlabel func_0014A0D8
    /* 4A0FC 0014A0FC 00000000 */  nop
