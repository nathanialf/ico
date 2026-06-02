.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

nonmatching func_00243C78, 0xA4

glabel func_00243C78
    /* 143C78 00243C78 00008044 */  mtc1       $zero, $f0
    /* 143C7C 00243C7C 34600046 */  c.lt.s     $f12, $f0
    /* 143C80 00243C80 C93F013C */  lui        $at, (0x3FC90FDB >> 16)
    /* 143C84 00243C84 DB0F2134 */  ori        $at, $at, (0x3FC90FDB & 0xFFFF)
    /* 143C88 00243C88 00008144 */  mtc1       $at, $f0
    /* 143C8C 00243C8C 04000045 */  bc1f       .L00243CA0
    /* 143C90 00243C90 00000000 */   nop
    /* 143C94 00243C94 00030C46 */  add.s      $f12, $f0, $f12
    /* 143C98 00243C98 2A0F0908 */  j          func_00243CA8
    /* 143C9C 00243C9C 01000724 */   addiu     $a3, $zero, 0x1
.align 2
  .L00243CA0:
    /* 143CA0 00243CA0 01030C46 */  sub.s      $f12, $f0, $f12
    /* 143CA4 00243CA4 2D380000 */  daddu      $a3, $zero, $zero
.align 2
  alabel func_00243CA8
    /* 143CA8 00243CA8 00600844 */  mfc1       $t0, $f12
    /* 143CAC 00243CAC 0030A848 */  qmtc2.ni   $t0, $vf6
    /* 143CB0 00243CB0 2D30E003 */  daddu      $a2, $ra, $zero
    /* 143CB4 00243CB4 000F090C */  jal        func_00243C00
    /* 143CB8 00243CB8 00000000 */   nop
    /* 143CBC 00243CBC 2DF8C000 */  daddu      $ra, $a2, $zero
    /* 143CC0 00243CC0 3C2BE64B */  vmove.xyzw $vf6, $vf5
    /* 143CC4 00243CC4 3C2BE74B */  vmove.xyzw $vf7, $vf5
    /* 143CC8 00243CC8 3C03E94B */  vmove.xyzw $vf9, $vf0
    /* 143CCC 00243CCC 6C4AC94B */  vsub.xyz   $vf9, $vf9, $vf9
    /* 143CD0 00243CD0 3D4BE84B */  vmr32.xyzw $vf8, $vf9
    /* 143CD4 00243CD4 2C21644A */  vsub.zw    $vf4, $vf4, $vf4
    /* 143CD8 00243CD8 8029844A */  vaddx.y    $vf6, $vf5, $vf4x
    /* 143CDC 00243CDC 8129044B */  vaddy.x    $vf6, $vf5, $vf4y
    /* 143CE0 00243CE0 C429044B */  vsubx.x    $vf7, $vf5, $vf4x
    /* 143CE4 00243CE4 C129844A */  vaddy.y    $vf7, $vf5, $vf4y
    /* 143CE8 00243CE8 04000724 */  addiu      $a3, $zero, 0x4
.align 2
  .L00243CEC:
    /* 143CEC 00243CEC 0000A4D8 */  lqc2       $vf4, 0x0($a1)
    /* 143CF0 00243CF0 BC31E44B */  vmulax.xyzw $ACC, $vf6, $vf4x
    /* 143CF4 00243CF4 BD38E44B */  vmadday.xyzw $ACC, $vf7, $vf4y
    /* 143CF8 00243CF8 BE40E44B */  vmaddaz.xyzw $ACC, $vf8, $vf4z
    /* 143CFC 00243CFC 4B49E44B */  vmaddw.xyzw $vf5, $vf9, $vf4w
    /* 143D00 00243D00 000085F8 */  sqc2       $vf5, 0x0($a0)
    /* 143D04 00243D04 FFFFE720 */  addi       $a3, $a3, -0x1 /* handwritten instruction */
    /* 143D08 00243D08 1000A520 */  addi       $a1, $a1, 0x10 /* handwritten instruction */
    /* 143D0C 00243D0C F7FF0714 */  bne        $zero, $a3, .L00243CEC
    /* 143D10 00243D10 10008420 */   addi      $a0, $a0, 0x10 /* handwritten instruction */
    /* 143D14 00243D14 0800E003 */  jr         $ra
    /* 143D18 00243D18 00000000 */   nop
endlabel func_00243C78
    /* 143D1C 00243D1C 00000000 */  nop

.align 3
/* Handwritten function */
nonmatching func_00243D20, 0xA8

glabel func_00243D20
    /* 143D20 00243D20 00008044 */  mtc1       $zero, $f0
    /* 143D24 00243D24 34600046 */  c.lt.s     $f12, $f0
    /* 143D28 00243D28 C93F013C */  lui        $at, (0x3FC90FDB >> 16)
    /* 143D2C 00243D2C DB0F2134 */  ori        $at, $at, (0x3FC90FDB & 0xFFFF)
    /* 143D30 00243D30 00008144 */  mtc1       $at, $f0
    /* 143D34 00243D34 04000045 */  bc1f       .L00243D48
    /* 143D38 00243D38 00000000 */   nop
    /* 143D3C 00243D3C 00030C46 */  add.s      $f12, $f0, $f12
    /* 143D40 00243D40 540F0908 */  j          func_00243D50
    /* 143D44 00243D44 01000724 */   addiu     $a3, $zero, 0x1
.align 2
  .L00243D48:
    /* 143D48 00243D48 01030C46 */  sub.s      $f12, $f0, $f12
    /* 143D4C 00243D4C 2D380000 */  daddu      $a3, $zero, $zero
.align 2
  alabel func_00243D50
    /* 143D50 00243D50 00600844 */  mfc1       $t0, $f12
    /* 143D54 00243D54 0030A848 */  qmtc2.ni   $t0, $vf6
    /* 143D58 00243D58 2D30E003 */  daddu      $a2, $ra, $zero
    /* 143D5C 00243D5C 000F090C */  jal        func_00243C00
    /* 143D60 00243D60 00000000 */   nop
    /* 143D64 00243D64 2DF8C000 */  daddu      $ra, $a2, $zero
    /* 143D68 00243D68 3C2BE64B */  vmove.xyzw $vf6, $vf5
    /* 143D6C 00243D6C 3C2BE74B */  vmove.xyzw $vf7, $vf5
    /* 143D70 00243D70 3C2BE84B */  vmove.xyzw $vf8, $vf5
    /* 143D74 00243D74 3C2BE94B */  vmove.xyzw $vf9, $vf5
    /* 143D78 00243D78 8329004B */  vaddw.x    $vf6, $vf5, $vf0w
    /* 143D7C 00243D7C 432A204A */  vaddw.w    $vf9, $vf5, $vf0w
    /* 143D80 00243D80 2C21644A */  vsub.zw    $vf4, $vf4, $vf4
    /* 143D84 00243D84 C029444A */  vaddx.z    $vf7, $vf5, $vf4x
    /* 143D88 00243D88 C129844A */  vaddy.y    $vf7, $vf5, $vf4y
    /* 143D8C 00243D8C 042A844A */  vsubx.y    $vf8, $vf5, $vf4x
    /* 143D90 00243D90 012A444A */  vaddy.z    $vf8, $vf5, $vf4y
    /* 143D94 00243D94 04000724 */  addiu      $a3, $zero, 0x4
.align 2
  .L00243D98:
    /* 143D98 00243D98 0000A4D8 */  lqc2       $vf4, 0x0($a1)
    /* 143D9C 00243D9C BC31E44B */  vmulax.xyzw $ACC, $vf6, $vf4x
    /* 143DA0 00243DA0 BD38E44B */  vmadday.xyzw $ACC, $vf7, $vf4y
    /* 143DA4 00243DA4 BE40E44B */  vmaddaz.xyzw $ACC, $vf8, $vf4z
    /* 143DA8 00243DA8 4B49E44B */  vmaddw.xyzw $vf5, $vf9, $vf4w
    /* 143DAC 00243DAC 000085F8 */  sqc2       $vf5, 0x0($a0)
    /* 143DB0 00243DB0 FFFFE720 */  addi       $a3, $a3, -0x1 /* handwritten instruction */
    /* 143DB4 00243DB4 1000A520 */  addi       $a1, $a1, 0x10 /* handwritten instruction */
    /* 143DB8 00243DB8 F7FF0714 */  bne        $zero, $a3, .L00243D98
    /* 143DBC 00243DBC 10008420 */   addi      $a0, $a0, 0x10 /* handwritten instruction */
    /* 143DC0 00243DC0 0800E003 */  jr         $ra
    /* 143DC4 00243DC4 00000000 */   nop
endlabel func_00243D20

.align 3
/* Handwritten function */
nonmatching func_00243DC8, 0xA8

glabel func_00243DC8
    /* 143DC8 00243DC8 00008044 */  mtc1       $zero, $f0
    /* 143DCC 00243DCC 34600046 */  c.lt.s     $f12, $f0
    /* 143DD0 00243DD0 C93F013C */  lui        $at, (0x3FC90FDB >> 16)
    /* 143DD4 00243DD4 DB0F2134 */  ori        $at, $at, (0x3FC90FDB & 0xFFFF)
    /* 143DD8 00243DD8 00008144 */  mtc1       $at, $f0
    /* 143DDC 00243DDC 04000045 */  bc1f       .L00243DF0
    /* 143DE0 00243DE0 00000000 */   nop
    /* 143DE4 00243DE4 00030C46 */  add.s      $f12, $f0, $f12
    /* 143DE8 00243DE8 7E0F0908 */  j          func_00243DF8
    /* 143DEC 00243DEC 01000724 */   addiu     $a3, $zero, 0x1
.align 2
  .L00243DF0:
    /* 143DF0 00243DF0 01030C46 */  sub.s      $f12, $f0, $f12
    /* 143DF4 00243DF4 2D380000 */  daddu      $a3, $zero, $zero
.align 2
  alabel func_00243DF8
    /* 143DF8 00243DF8 00600844 */  mfc1       $t0, $f12
    /* 143DFC 00243DFC 0030A848 */  qmtc2.ni   $t0, $vf6
    /* 143E00 00243E00 2D30E003 */  daddu      $a2, $ra, $zero
    /* 143E04 00243E04 000F090C */  jal        func_00243C00
    /* 143E08 00243E08 00000000 */   nop
    /* 143E0C 00243E0C 2DF8C000 */  daddu      $ra, $a2, $zero
    /* 143E10 00243E10 3C2BE64B */  vmove.xyzw $vf6, $vf5
    /* 143E14 00243E14 3C2BE74B */  vmove.xyzw $vf7, $vf5
    /* 143E18 00243E18 3C2BE84B */  vmove.xyzw $vf8, $vf5
    /* 143E1C 00243E1C 3C2BE94B */  vmove.xyzw $vf9, $vf5
    /* 143E20 00243E20 C329804A */  vaddw.y    $vf7, $vf5, $vf0w
    /* 143E24 00243E24 432A204A */  vaddw.w    $vf9, $vf5, $vf0w
    /* 143E28 00243E28 2C21644A */  vsub.zw    $vf4, $vf4, $vf4
    /* 143E2C 00243E2C 8429444A */  vsubx.z    $vf6, $vf5, $vf4x
    /* 143E30 00243E30 8129044B */  vaddy.x    $vf6, $vf5, $vf4y
    /* 143E34 00243E34 002A044B */  vaddx.x    $vf8, $vf5, $vf4x
    /* 143E38 00243E38 012A444A */  vaddy.z    $vf8, $vf5, $vf4y
    /* 143E3C 00243E3C 04000724 */  addiu      $a3, $zero, 0x4
.align 2
  .L00243E40:
    /* 143E40 00243E40 0000A4D8 */  lqc2       $vf4, 0x0($a1)
    /* 143E44 00243E44 BC31E44B */  vmulax.xyzw $ACC, $vf6, $vf4x
    /* 143E48 00243E48 BD38E44B */  vmadday.xyzw $ACC, $vf7, $vf4y
    /* 143E4C 00243E4C BE40E44B */  vmaddaz.xyzw $ACC, $vf8, $vf4z
    /* 143E50 00243E50 4B49E44B */  vmaddw.xyzw $vf5, $vf9, $vf4w
    /* 143E54 00243E54 000085F8 */  sqc2       $vf5, 0x0($a0)
    /* 143E58 00243E58 FFFFE720 */  addi       $a3, $a3, -0x1 /* handwritten instruction */
    /* 143E5C 00243E5C 1000A520 */  addi       $a1, $a1, 0x10 /* handwritten instruction */
    /* 143E60 00243E60 F7FF0714 */  bne        $zero, $a3, .L00243E40
    /* 143E64 00243E64 10008420 */   addi      $a0, $a0, 0x10 /* handwritten instruction */
    /* 143E68 00243E68 0800E003 */  jr         $ra
    /* 143E6C 00243E6C 00000000 */   nop
endlabel func_00243DC8
