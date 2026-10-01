# libc.a member memcmp.o, assembled from newlib's
# src/newlib/libc/machine/r5900/memcmp.S.  When both pointers are 16-aligned
# it compares a quadword at a time (lq, pxor, pcpyud: MMI, no C spelling),
# stopping at the first quadword that differs; the remainder, and any
# unaligned call, is compared byte by byte.
#
# The member starts 4-aligned right after fiprintf.o's 0x34 bytes, so the
# section is only word-aligned.
    .section .text
    .align 2
    .set noreorder
    .globl memcmp
    .type memcmp, @function
    .ent memcmp
memcmp:
    sltiu  $2, $6, 0x10
    bnez   $2, 2f
    or     $2, $4, $5
    andi   $2, $2, 0xF
    bnez   $2, 2f
    nop
    .align 2
1:
    lq     $3, 0x0($4)
    sltiu  $7, $6, 0x20
    lq     $2, 0x0($5)
    addiu  $4, $4, 0x10
    pxor   $8, $2, $3
    addiu  $2, $5, 0x10
    pcpyud $10, $8, $7
    or     $9, $10, $8
    movz   $5, $2, $9
    bnel   $9, $0, 2f
    addiu  $4, $4, -0x10
    beqz   $7, 1b
    addiu  $6, $6, -0x10
    .align 2
2:
    lui    $2, 0xFFFF
    addiu  $6, $6, -0x1
    ori    $2, $2, 0xFFFF
    beq    $6, $2, 5f
    nop
    lui    $7, 0xFFFF
    ori    $7, $7, 0xFFFF
    .align 2
3:
    lbu    $3, 0x0($4)
    lbu    $2, 0x0($5)
    beq    $3, $2, 4f
    addiu  $4, $4, 0x1
    jr     $31
    subu   $2, $3, $2
    .align 2
4:
    addiu  $6, $6, -0x1
    bne    $6, $7, 3b
    addiu  $5, $5, 0x1
    .align 2
5:
    jr     $31
    daddu  $2, $0, $0
    .end memcmp
    .set reorder
