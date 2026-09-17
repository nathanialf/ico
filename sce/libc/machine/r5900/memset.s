# libc.a member memset.o.  SRCFILE.TXT attributes every instruction to
# src/newlib/libc/machine/r5900/memset.S (listing line 517665 on), so this
# member was assembled, not compiled; the quadword sq store loop and the
# pcpyh/pcpyld broadcast have no C spelling either.  Transcribed from the
# shipped instruction stream (rungs: ROM bytes, the listing rows).  MAIN.MAP
# sizes memset.o at 0xC0, the whole of this member's run.
    .section .text
    .set noat
    .set noreorder
    .global memset
    .type memset, @function
    .align 3
memset:
    sltiu  $2, $6, 0x8
    bnez   $2, .L1
    daddu  $3, $4, $0
    andi   $2, $4, 0xF
    bnez   $2, .L1
    daddu  $7, $4, $0
    andi   $9, $5, 0xFF
    sltiu  $10, $6, 0x20
    daddu  $8, $9, $0
    dsll   $3, $8, 8
    or     $8, $3, $9
    pcpyh  $3, $8
    bnez   $10, .L2
    sltiu  $2, $6, 0x8
    pcpyld $8, $3, $3
    .align 2
    .L3:
    sq     $8, 0x0($7)
    addiu  $6, $6, -0x20
    addiu  $7, $7, 0x10
    sltiu  $2, $6, 0x20
    sq     $8, 0x0($7)
    beqz   $2, .L3
    addiu  $7, $7, 0x10
    b      .L2
    sltiu  $2, $6, 0x8
    .align 2
    .L4:
    addiu  $6, $6, -0x8
    addiu  $7, $7, 0x8
    sltiu  $2, $6, 0x8
    .align 2
    .L2:
    nop
    nop
    beql   $2, $0, .L4
    sd     $3, 0x0($7)
    daddu  $3, $7, $0
    .align 2
    .L1:
    lui    $2, 0xFFFF
    addiu  $6, $6, -0x1
    ori    $2, $2, 0xFFFF
    beq    $6, $2, .L5
    nop
    lui    $2, 0xFFFF
    ori    $2, $2, 0xFFFF
    .align 2
    .L6:
    sb     $5, 0x0($3)
    addiu  $6, $6, -0x1
    nop
    nop
    nop
    bne    $6, $2, .L6
    addiu  $3, $3, 0x1
    .align 2
    .L5:
    jr     $31
    daddu  $2, $4, $0
    .size memset, . - memset
    .set reorder
    .set at
