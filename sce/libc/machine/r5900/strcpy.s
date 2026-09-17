# libc.a member strcpy.o, and strlen.o behind it.  SRCFILE.TXT attributes every
# instruction to src/newlib/libc/machine/r5900/strcpy.S (listing line 519160
# on) and strlen.S (listing line 519300 on), so both were assembled, not
# compiled.  strlen.o starts inside this file at an address that is not
# 8-aligned in the shipped ELF, so it cannot open a subsegment of its own and
# is assembled here behind strcpy.  Transcribed from the shipped instruction
# stream (rungs: ROM bytes, the listing rows).
    .section .text
    .set    at
    .set    noreorder
    .align 3
    .globl  strcpy
    .ent    strcpy
strcpy:
    daddu      $7, $4, $0
    or         $8, $5, $7
    andi       $2, $8, 0x7
    bnez       $2, .L5
    daddu      $3, $7, $0
    andi       $2, $8, 0xF
    lui        $9, (0x1010101 >> 16)
    ori        $9, $9, (0x1010101 & 0xFFFF)
    dsll       $9, $9, 16
    ori        $9, $9, 0x101
    dsll       $9, $9, 16
    ori        $9, $9, 0x101
    lui        $4, (0x80808080 >> 16)
    ori        $4, $4, (0x80808080 & 0xFFFF)
    dsll       $4, $4, 16
    ori        $4, $4, 0x8080
    dsll       $4, $4, 16
    ori        $4, $4, 0x8080
    bnel       $2, $0, .L2
    ld         $10, 0x0($5)
    pcpyld     $10, $9, $9
    lq         $9, 0x0($5)
    pcpyld     $8, $4, $4
    psubb      $2, $9, $10
    pnor       $3, $0, $9
    pand       $2, $2, $3
    pand       $2, $2, $8
    pcpyud     $4, $2, $9
    or         $3, $2, $4
    bnez       $3, .L4
    daddu      $6, $7, $0
    .align 2
.L1:
    sq         $9, 0x0($6)
    addiu      $5, $5, 0x10
    lq         $9, 0x0($5)
    psubb      $2, $9, $10
    pnor       $3, $0, $9
    pand       $2, $2, $3
    pand       $2, $2, $8
    pcpyud     $4, $2, $9
    or         $3, $2, $4
    beqz       $3, .L1
    addiu      $6, $6, 0x10
    b          .L5
    daddu      $3, $6, $0
    .align 2
.L2:
    dsubu      $2, $10, $9
    nor        $3, $0, $10
    and        $2, $2, $3
    and        $2, $2, $4
    bnez       $2, .L4
    daddu      $6, $7, $0
    .align 2
.L3:
    sd         $10, 0x0($6)
    addiu      $5, $5, 0x8
    ld         $10, 0x0($5)
    nor        $2, $0, $10
    dsubu      $3, $10, $9
    and        $3, $3, $2
    and        $3, $3, $4
    beqz       $3, .L3
    addiu      $6, $6, 0x8
    .align 2
.L4:
    daddu      $3, $6, $0
    .align 2
.L5:
    lbu        $2, 0x0($5)
    addiu      $5, $5, 0x1
    sb         $2, 0x0($3)
    sll        $2, $2, 24
    nop
    bnez       $2, .L5
    addiu      $3, $3, 0x1
    jr         $31
    daddu      $2, $7, $0
    .end    strcpy
    .globl  strlen
    .ent    strlen
strlen:
    andi       $2, $4, 0x7
    bnez       $2, .L9
    daddu      $7, $4, $0
    andi       $3, $4, 0xF
    lui        $2, (0x1010101 >> 16)
    ori        $2, $2, (0x1010101 & 0xFFFF)
    dsll       $2, $2, 16
    ori        $2, $2, 0x101
    dsll       $2, $2, 16
    ori        $2, $2, 0x101
    bnez       $3, .L7
    daddu      $5, $4, $0
    lq         $3, 0x0($5)
    pcpyld     $8, $2, $2
    lui        $4, (0x80808080 >> 16)
    ori        $4, $4, (0x80808080 & 0xFFFF)
    dsll       $4, $4, 16
    ori        $4, $4, 0x8080
    dsll       $4, $4, 16
    ori        $4, $4, 0x8080
    psubb      $2, $3, $8
    pnor       $3, $0, $3
    pcpyld     $9, $4, $4
    pand       $2, $2, $3
    pand       $2, $2, $9
    pcpyud     $3, $2, $8
    or         $6, $3, $2
    bnel       $6, $0, .L9
    daddu      $4, $5, $0
    addiu      $5, $5, 0x10
    .align 2
.L6:
    lq         $2, 0x0($5)
    pnor       $3, $0, $2
    psubb      $2, $2, $8
    pand       $2, $2, $3
    pand       $4, $2, $9
    pcpyud     $3, $4, $6
    or         $3, $3, $4
    beql       $3, $0, .L6
    addiu      $5, $5, 0x10
    b          .L9
    daddu      $4, $5, $0
    .align 2
.L7:
    ld         $3, 0x0($5)
    lui        $4, (0x80808080 >> 16)
    ori        $4, $4, (0x80808080 & 0xFFFF)
    dsll       $4, $4, 16
    ori        $4, $4, 0x8080
    dsll       $4, $4, 16
    ori        $4, $4, 0x8080
    dsubu      $2, $3, $2
    nor        $3, $0, $3
    and        $2, $2, $3
    and        $2, $2, $4
    bnel       $2, $0, .L9
    daddu      $4, $5, $0
    lui        $6, (0x1010101 >> 16)
    ori        $6, $6, (0x1010101 & 0xFFFF)
    dsll       $6, $6, 16
    ori        $6, $6, 0x101
    dsll       $6, $6, 16
    ori        $6, $6, 0x101
    addiu      $5, $5, 0x8
    .align 2
.L8:
    ld         $2, 0x0($5)
    nor        $3, $0, $2
    dsubu      $2, $2, $6
    and        $2, $2, $3
    and        $2, $2, $4
    beql       $2, $0, .L8
    addiu      $5, $5, 0x8
    daddu      $4, $5, $0
    .align 2
.L9:
    lb         $2, 0x0($4)
    nop
    nop
    nop
    nop
    bnel       $2, $0, .L9
    addiu      $4, $4, 0x1
    jr         $31
    subu       $2, $4, $7
    nop
    .end    strlen
    .set    reorder
