# libc.a member memchr.o, assembled from newlib's
# src/newlib/libc/machine/r5900/memchr.S; the MMI byte search (pcpyh, pcpyld,
# pnor, psubb, pand, pcpyud) has no C spelling. The section is only
# word-aligned.
    .section .text
    .align 2
    .set noat
    .set noreorder
    .global memchr
    .type memchr, @function
memchr:
    sltiu   $2, $6, 0x10
    bnez    $2, .Lmemchr0028638C
    andi    $5, $5, 0xFF
    andi    $2, $4, 0xF
    bnez    $2, .Lmemchr0028638C
    daddu   $7, $4, $0
    dsll    $3, $5, 8
    lui     $2, (0x1010101 >> 16)
    ori     $2, $2, (0x1010101 & 0xFFFF)
    dsll    $2, $2, 16
    ori     $2, $2, 0x101
    dsll    $2, $2, 16
    ori     $2, $2, 0x101
    daddu   $10, $3, $5
    lui     $3, (0x80808080 >> 16)
    ori     $3, $3, (0x80808080 & 0xFFFF)
    dsll    $3, $3, 16
    ori     $3, $3, 0x8080
    dsll    $3, $3, 16
    ori     $3, $3, 0x8080
    pcpyh   $8, $10
    pcpyld  $9, $8, $8
    daddu   $4, $2, $0
    pcpyld  $8, $3, $3
    .align 2
.Lmemchr0028634C:
    lq      $2, 0x0($7)
    pxor    $2, $2, $9
    pcpyld  $10, $4, $4
    pnor    $3, $0, $2
    psubb   $2, $2, $10
    pand    $2, $2, $3
    pand    $2, $2, $8
    pcpyud  $3, $2, $9
    or      $2, $2, $3
    bnel    $2, $0, .Lmemchr0028638C
    daddu   $4, $7, $0
    addiu   $6, $6, -0x10
    sltiu   $2, $6, 0x10
    beqz    $2, .Lmemchr0028634C
    addiu   $7, $7, 0x10
    daddu   $4, $7, $0
    .align 2
.Lmemchr0028638C:
    lui     $2, (0xFFFFFFFF >> 16)
    addiu   $6, $6, -0x1
    ori     $2, $2, (0xFFFFFFFF & 0xFFFF)
    beq     $6, $2, .Lmemchr002863BC
    nop
    lui     $3, (0xFFFFFFFF >> 16)
    ori     $3, $3, (0xFFFFFFFF & 0xFFFF)
    .align 2
.Lmemchr002863A8:
    lbu     $2, 0x0($4)
    beq     $2, $5, .Lmemchr002863C4
    addiu   $6, $6, -0x1
    bne     $6, $3, .Lmemchr002863A8
    addiu   $4, $4, 0x1
    .align 2
.Lmemchr002863BC:
    jr      $31
    daddu   $2, $0, $0
    .align 2
.Lmemchr002863C4:
    jr      $31
    daddu   $2, $4, $0
    .size memchr, . - memchr
    .set reorder
    .set at
