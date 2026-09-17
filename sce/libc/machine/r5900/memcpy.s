# libc.a member memcpy.o.  SRCFILE.TXT attributes every instruction to
# src/newlib/libc/machine/r5900/memcpy.S (listing line 517563 on), so this
# member was assembled, not compiled; the quadword lq/sq copy loop has no C
# spelling either.  Transcribed from the shipped instruction stream (rungs: ROM
# bytes for the instructions, the listing rows for the source file).  MAIN.MAP
# sizes memcpy.o at 0xB0, the whole of this member's run.
    .section .text
    .set    at
    .set    noreorder
    .align 3
    .globl  memcpy
    .ent    memcpy
memcpy:
    daddu      $8, $4, $0
    sltiu      $2, $6, 0x20
    bnez       $2, .L3
    daddu      $3, $8, $0
    or         $2, $5, $8
    andi       $2, $2, 0xF
    bnel       $2, $0, .L4
    addiu      $6, $6, -0x1
    daddu      $7, $8, $0
    .align 2
.L1:
    lq         $3, 0x0($5)
    addiu      $6, $6, -0x20
    addiu      $5, $5, 0x10
    sltiu      $4, $6, 0x20
    sq         $3, 0x0($7)
    addiu      $7, $7, 0x10
    lq         $2, 0x0($5)
    addiu      $5, $5, 0x10
    sq         $2, 0x0($7)
    beqz       $4, .L1
    addiu      $7, $7, 0x10
    sltiu      $2, $6, 0x8
    bnez       $2, .L3
    daddu      $3, $7, $0
    .align 2
.L2:
    ld         $3, 0x0($5)
    addiu      $6, $6, -0x8
    addiu      $5, $5, 0x8
    sltiu      $2, $6, 0x8
    sd         $3, 0x0($7)
    beqz       $2, .L2
    addiu      $7, $7, 0x8
    daddu      $3, $7, $0
    .align 2
.L3:
    addiu      $6, $6, -0x1
    .align 2
.L4:
    addiu      $2, $0, -0x1
    beq        $6, $2, .L6
    daddu      $4, $2, $0
    .align 2
.L5:
    lbu        $2, 0x0($5)
    addiu      $6, $6, -0x1
    addiu      $5, $5, 0x1
    sb         $2, 0x0($3)
    nop
    bne        $6, $4, .L5
    addiu      $3, $3, 0x1
    .align 2
.L6:
    jr         $31
    daddu      $2, $8, $0
    .end    memcpy
    .set    reorder
