# libc.a member strcat.o, assembled from newlib's
# src/newlib/libc/machine/r5900/strcat.S.
    .section .text
    .set noat
    .set noreorder
    .global strcat
    .type strcat, @function
    .align 3
strcat:
    addiu  $29, $29, -0x20
    sq     $16, 0x0($29)
    daddu  $16, $4, $0
    andi   $2, $16, 0x7
    bnez   $2, .L1
    sq     $31, 0x10($29)
    andi   $2, $16, 0xF
    lui    $3, 0x101
    ori    $3, $3, 0x101
    dsll   $3, $3, 16
    ori    $3, $3, 0x101
    dsll   $3, $3, 16
    ori    $3, $3, 0x101
    lui    $4, 0x8080
    ori    $4, $4, 0x8080
    dsll   $4, $4, 16
    ori    $4, $4, 0x8080
    dsll   $4, $4, 16
    ori    $4, $4, 0x8080
    bnez   $2, .L2
    ld     $6, 0x0($16)
    lq     $2, 0x0($16)
    pcpyld $7, $3, $3
    pcpyld $8, $4, $4
    psubb  $3, $2, $7
    pnor   $2, $0, $2
    pand   $3, $3, $2
    pand   $3, $3, $8
    pcpyud $2, $3, $3
    or     $3, $2, $3
    bnez   $3, .L1
    daddu  $4, $16, $0
    addiu  $6, $4, 0x10
    .align 2
    .L3:
    lq     $2, 0x0($6)
    pnor   $3, $0, $2
    psubb  $2, $2, $7
    pand   $2, $2, $3
    pand   $2, $2, $8
    pcpyud $3, $2, $2
    or     $2, $2, $3
    beql   $2, $0, .L3
    addiu  $6, $6, 0x10
    b      .L1
    daddu  $4, $6, $0
    .align 2
    .L2:
    daddu  $7, $3, $0
    daddu  $8, $4, $0
    dsubu  $3, $6, $3
    nor    $2, $0, $6
    and    $3, $3, $2
    and    $3, $3, $4
    bnez   $3, .L1
    daddu  $4, $16, $0
    addiu  $6, $16, 0x8
    .align 2
    .L4:
    ld     $2, 0x0($6)
    nor    $3, $0, $2
    dsubu  $2, $2, $7
    and    $2, $2, $3
    and    $2, $2, $8
    beql   $2, $0, .L4
    addiu  $6, $6, 0x8
    daddu  $4, $6, $0
    .align 2
    .L1:
    lb     $2, 0x0($4)
    nop
    nop
    nop
    nop
    bnel   $2, $0, .L1
    addiu  $4, $4, 0x1
    jal    strcpy
    nop
    daddu  $2, $16, $0
    lq     $31, 0x10($29)
    lq     $16, 0x0($29)
    jr     $31
    addiu  $29, $29, 0x20
    .size strcat, . - strcat
    .set reorder
    .set at
