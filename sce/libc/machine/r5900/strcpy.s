# libc.a member strcpy.o.  SRCFILE.TXT attributes every instruction to
# src/newlib/libc/machine/r5900/strcpy.S (listing line 519160 on), so it was
# assembled, not compiled.  Transcribed from the shipped instruction stream
# (rungs: ROM bytes, the listing rows).  MAIN.MAP sizes strcpy.o at 0x114.
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
    .set    reorder
