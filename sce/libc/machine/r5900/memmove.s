# libc.a member memmove.o.  SRCFILE.TXT attributes every instruction to
# src/newlib/libc/machine/r5900/memmove.S (listing line 528736 on), so this
# member was assembled, not compiled.  Transcribed from the shipped instruction
# stream (rungs: ROM bytes, the listing rows).  MAIN.MAP sizes memmove.o at
# 0x104.  It starts at 0x002863CC, right after memchr.o: the ROM start is
# 4-aligned, so the section is only word-aligned.
    .section .text
    .set noat
    .set noreorder
    .align 2
    .global memmove
    .type memmove, @function
memmove:
    daddu   $8, $4, $0
    sltu    $2, $5, $8
    beqz    $2, .Lmemmove00286424
    daddu   $3, $8, $0
    addu    $7, $5, $6
    sltu    $2, $8, $7
    beqz    $2, .Lmemmove00286424
    addiu   $2, $0, -0x1
    addu    $3, $8, $6
    addiu   $6, $6, -0x1
    beq     $6, $2, .Lmemmove002864C8
    daddu   $5, $7, $0
    daddu   $4, $2, $0
    .align 2
.Lmemmove00286400:
    addiu   $5, $5, -0x1
    addiu   $3, $3, -0x1
    lbu     $2, 0x0($5)
    addiu   $6, $6, -0x1
    nop
    bne     $6, $4, .Lmemmove00286400
    sb      $2, 0x0($3)
    jr      $31
    daddu   $2, $8, $0
    .align 2
.Lmemmove00286424:
    sltiu   $2, $6, 0x20
    bnel    $2, $0, .Lmemmove002864A0
    addiu   $6, $6, -0x1
    or      $2, $5, $3
    andi    $2, $2, 0xF
    bnel    $2, $0, .Lmemmove002864A0
    addiu   $6, $6, -0x1
    daddu   $7, $3, $0
    .align 2
.Lmemmove00286444:
    lq      $3, 0x0($5)
    addiu   $6, $6, -0x20
    addiu   $5, $5, 0x10
    sltiu   $4, $6, 0x20
    sq      $3, 0x0($7)
    addiu   $7, $7, 0x10
    lq      $2, 0x0($5)
    addiu   $5, $5, 0x10
    sq      $2, 0x0($7)
    beqz    $4, .Lmemmove00286444
    addiu   $7, $7, 0x10
    sltiu   $2, $6, 0x8
    bnez    $2, .Lmemmove0028649C
    daddu   $3, $7, $0
    .align 2
.Lmemmove0028647C:
    ld      $3, 0x0($5)
    addiu   $6, $6, -0x8
    addiu   $5, $5, 0x8
    sltiu   $2, $6, 0x8
    sd      $3, 0x0($7)
    beqz    $2, .Lmemmove0028647C
    addiu   $7, $7, 0x8
    daddu   $3, $7, $0
    .align 2
.Lmemmove0028649C:
    addiu   $6, $6, -0x1
    .align 2
.Lmemmove002864A0:
    addiu   $2, $0, -0x1
    beq     $6, $2, .Lmemmove002864C8
    daddu   $4, $2, $0
    .align 2
.Lmemmove002864AC:
    lbu     $2, 0x0($5)
    addiu   $6, $6, -0x1
    addiu   $5, $5, 0x1
    sb      $2, 0x0($3)
    nop
    bne     $6, $4, .Lmemmove002864AC
    addiu   $3, $3, 0x1
    .align 2
.Lmemmove002864C8:
    jr      $31
    daddu   $2, $8, $0
    .size memmove, . - memmove
    .set reorder
    .set at
