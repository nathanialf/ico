# libc.a member strncmp.o.  SRCFILE.TXT attributes every instruction to
# src/newlib/libc/machine/r5900/strncmp.S (listing line 519441 on), so this
# member was assembled, not compiled.  Transcribed from the shipped instruction
# stream (rungs: ROM bytes, the listing rows).  MAIN.MAP sizes strncmp.o at the
# whole of this member's run.
    .section .text
    .set    at
    .set    noreorder
    .align 3
    .globl  strncmp
    .ent    strncmp
strncmp:
    bnez       $6, .L2
    or         $3, $4, $5
    .align 2
.L1:
    jr         $31
    daddu      $2, $0, $0
    .align 2
.L2:
    andi       $2, $3, 0x7
    bnez       $2, .L8
    daddu      $2, $6, $0
    andi       $2, $3, 0xF
    sltiu      $7, $6, 0x10
    lui        $9, (0x1010101 >> 16)
    ori        $9, $9, (0x1010101 & 0xFFFF)
    dsll       $9, $9, 16
    ori        $9, $9, 0x101
    dsll       $9, $9, 16
    ori        $9, $9, 0x101
    or         $2, $2, $7
    bnez       $2, .L4
    daddu      $7, $4, $0
    lq         $3, 0x0($4)
    pcpyld     $10, $9, $9
    lq         $2, 0x0($5)
    lui        $8, (0x80808080 >> 16)
    ori        $8, $8, (0x80808080 & 0xFFFF)
    dsll       $8, $8, 16
    ori        $8, $8, 0x8080
    dsll       $8, $8, 16
    ori        $8, $8, 0x8080
    psubw      $3, $3, $2
    pcpyld     $9, $8, $8
    pcpyud     $2, $3, $4
    daddu      $8, $5, $0
    or         $3, $2, $3
    bnez       $3, .L8
    daddu      $2, $6, $0
    addiu      $6, $6, -0x10
    .align 2
.L3:
    beqz       $6, .L1
    nop
    lq         $2, 0x0($7)
    pnor       $3, $0, $2
    psubb      $2, $2, $10
    pand       $2, $2, $3
    pand       $3, $2, $9
    pcpyud     $2, $3, $4
    or         $2, $2, $3
    bnez       $2, .L1
    addiu      $7, $7, 0x10
    sltiu      $2, $6, 0x10
    lq         $3, 0x0($7)
    bnez       $2, .L6
    addiu      $8, $8, 0x10
    lq         $2, 0x0($8)
    psubw      $3, $3, $2
    pcpyud     $2, $3, $4
    or         $2, $2, $3
    beql       $2, $0, .L3
    addiu      $6, $6, -0x10
    b          .L7
    daddu      $4, $7, $0
    .align 2
.L4:
    sltiu      $2, $6, 0x8
    bnez       $2, .L6
    daddu      $8, $5, $0
    ld         $3, 0x0($4)
    ld         $2, 0x0($5)
    bne        $3, $2, .L8
    daddu      $2, $6, $0
    addiu      $6, $6, -0x8
    lui        $10, (0x80808080 >> 16)
    ori        $10, $10, (0x80808080 & 0xFFFF)
    dsll       $10, $10, 16
    ori        $10, $10, 0x8080
    dsll       $10, $10, 16
    ori        $10, $10, 0x8080
    .align 2
.L5:
    beqz       $6, .L1
    nop
    ld         $2, 0x0($7)
    nor        $3, $0, $2
    dsubu      $2, $2, $9
    and        $2, $2, $3
    and        $2, $2, $10
    bnez       $2, .L1
    addiu      $7, $7, 0x8
    sltiu      $2, $6, 0x8
    bnez       $2, .L6
    addiu      $8, $8, 0x8
    ld         $3, 0x0($7)
    ld         $2, 0x0($8)
    beql       $3, $2, .L5
    addiu      $6, $6, -0x8
    .align 2
.L6:
    daddu      $4, $7, $0
    .align 2
.L7:
    daddu      $5, $8, $0
    daddu      $2, $6, $0
    .align 2
.L8:
    beqz       $2, .L11
    addiu      $6, $6, -0x1
    b          .L10
    lb         $3, 0x0($4)
    nop
    .align 2
.L9:
    beqz       $6, .L1
    nop
    beqz       $7, .L1
    addiu      $4, $4, 0x1
    addiu      $5, $5, 0x1
    lb         $3, 0x0($4)
    addiu      $6, $6, -0x1
    .align 2
.L10:
    lb         $2, 0x0($5)
    beq        $3, $2, .L9
    lbu        $7, 0x0($4)
    .align 2
.L11:
    lbu        $2, 0x0($5)
    lbu        $3, 0x0($4)
    jr         $31
    subu       $2, $3, $2
    .end    strncmp
    .set    reorder
