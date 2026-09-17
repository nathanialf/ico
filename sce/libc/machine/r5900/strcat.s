# libc.a member strcat.o, and strcmp.o behind it.  SRCFILE.TXT attributes every
# instruction to src/newlib/libc/machine/r5900/strcat.S (listing line 518844
# on) and strcmp.S (listing line 518989 on), so both were assembled, not
# compiled.  strcmp.o starts inside this file at an address that is not
# 8-aligned in the shipped ELF, so it cannot open a subsegment of its own and
# is assembled here behind strcat.  Transcribed from the shipped instruction
# stream (rungs: ROM bytes, the listing rows).
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
    .section .text
    .set noat
    .set noreorder
    .global strcmp
    .type strcmp, @function
strcmp:
    or $8, $4, $5
    andi $2, $8, 0x7
    bnel $2, $0, .L5
    lb $2, 0x0($4)
    andi $9, $8, 0xF
    lui $7, (0x1010101 >> 16)
    ori $7, $7, (0x1010101 & 0xFFFF)
    dsll $7, $7, 16
    ori $7, $7, 0x101
    dsll $7, $7, 16
    ori $7, $7, 0x101
    lui $6, (0x80808080 >> 16)
    ori $6, $6, (0x80808080 & 0xFFFF)
    dsll $6, $6, 16
    ori $6, $6, 0x8080
    dsll $6, $6, 16
    ori $6, $6, 0x8080
    bnez $9, .L6
    ld $2, 0x0($5)
    lq $3, 0x0($4)
    pcpyld $8, $7, $7
    lq $2, 0x0($5)
    pcpyld $10, $6, $6
    psubw $7, $2, $3
    pcpyud $6, $7, $4
    or $3, $6, $7
    bnel $3, $0, .L5
    lb $2, 0x0($4)
    lq $2, 0x0($4)
    pnor $3, $0, $2
    .align 2
    .L7:
    psubb $2, $2, $8
    pand $2, $2, $3
    pand $2, $2, $10
    pcpyud $3, $2, $4
    or $6, $3, $2
    beqz $6, .L8
    addiu $4, $4, 0x10
    jr $31
    daddu $2, $0, $0
    .align 2
    .L8:
    addiu $5, $5, 0x10
    lq $2, 0x0($4)
    lq $3, 0x0($5)
    psubw $7, $2, $3
    pcpyud $6, $7, $4
    or $9, $6, $7
    beql $9, $0, .L7
    pnor $3, $0, $2
    b .L5
    lb $2, 0x0($4)
    .align 2
    .L6:
    ld $3, 0x0($4)
    bnel $3, $2, .L5
    lb $2, 0x0($4)
    ld $2, 0x0($4)
    nor $8, $0, $2
    .align 2
    .L9:
    dsubu $2, $2, $7
    and $2, $2, $8
    and $2, $2, $6
    beqz $2, .L10
    addiu $4, $4, 0x8
    jr $31
    daddu $2, $0, $0
    .align 2
    .L10:
    addiu $5, $5, 0x8
    ld $2, 0x0($4)
    ld $3, 0x0($5)
    beql $3, $2, .L9
    nor $8, $0, $2
    b .L5
    lb $2, 0x0($4)
    .align 2
    .L11:
    sll $2, $3, 24
    lb $3, 0x0($5)
    sra $2, $2, 24
    bnel $2, $3, .L12
    lbu $3, 0x0($4)
    addiu $4, $4, 0x1
    addiu $5, $5, 0x1
    lb $2, 0x0($4)
    .align 2
    .L5:
    bnez $2, .L11
    lbu $3, 0x0($4)
    .align 2
    .L12:
    lbu $2, 0x0($5)
    jr $31
    subu $2, $3, $2
    .size strcmp, . - strcmp
    .set reorder
    .set at
