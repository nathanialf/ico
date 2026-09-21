# crt0: the SDK's start-up module, the head of .text.  SRCFILE.TXT attributes
# every instruction of it to /usr/local/sce/ee/lib/crt0.s (listing line 10 on,
# <_start> at listing line 9), so it was assembled, not compiled; sq, syscall
# and ei have no C spelling either.  Transcribed from the shipped instruction
# stream (rungs: ROM bytes for the instructions, the listing rows for the
# source file).  The eight zero bytes the listing labels <_start-0x8> are
# crt0.s's pre-entry pad, not a function, and are emitted here as data so the
# run starts at the same address.  The January 2002 link built a 0xC8-byte crt0
# against this run of 0x110, so no size tiling is claimed.
    .section .text
    .set at
    .set noreorder
    .align 3
    .global D_00100000
D_00100000:
    .word 0, 0
    .set reorder
    .set at
    .section .text
    .set noat
    .set noreorder
    .align 3
    .globl _start
    .type _start, @function
_start:
    lui $2, %hi(_fbss)
    lui $3, %hi(_end)
    addiu $2, $2, %lo(_fbss)
    addiu $3, $3, %lo(_end)
    .align 2
    .L1:
    sq $0, 0x0($2)
    sltu $1, $2, $3
    nop
    nop
    nop
    bnez $1, .L1
    addiu $2, $2, 0x10
    lui $4, %hi(D_00640AF0)
    lui $5, %hi(D_1FF0000)
    lui $6, %hi(D_10000)
    lui $7, %hi(D_0063C600)
    lui $8, %hi(_root)
    addiu $4, $4, %lo(D_00640AF0)
    addiu $5, $5, %lo(D_1FF0000)
    addiu $6, $6, %lo(D_10000)
    addiu $7, $7, %lo(D_0063C600)
    addiu $8, $8, %lo(_root)
    daddu $28, $4, $0
    addiu $3, $0, 0x3C
    syscall 0
    daddu $29, $2, $0
    lui $4, %hi(_end)
    lui $5, %hi(D_10000)
    addiu $4, $4, %lo(_end)
    addiu $5, $5, %lo(D_10000)
    addiu $3, $0, 0x3D
    syscall 0
    jal _InitSys
    nop
    jal FlushCache
    daddu $4, $0, $0
    ei
    lui $2, %hi(D_0063C600)
    addiu $2, $2, %lo(D_0063C600)
    lw $4, 0x0($2)
    jal main
    addiu $5, $2, 0x4
    j Exit
    daddu $4, $2, $0
    .size _start, . - _start
    .set reorder
    .set at
    .section .text
    .set at
    .set noreorder
    .align 3
    .globl _exit
    .type _exit, @function
_exit:
    j Exit
    daddu $4, $0, $0
    .size _exit, . - _exit
    .set reorder
    .set at
    .section .text
    .set at
    .set noreorder
    .align 3
    .globl _root
    .type _root, @function
_root:
    addiu $3, $0, 0x23
    syscall 0
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    addiu $3, $0, 0x0
    syscall 0
    jr $31
    nop
    .size _root, . - _root
    .set reorder
    .set at
