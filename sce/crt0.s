# crt0: the SDK's start-up module, the head of .text.  SRCFILE.TXT attributes
# every instruction of it to /usr/local/sce/ee/lib/crt0.s (listing line 10 on,
# <_start> at listing line 9), so it was assembled, not compiled; sq, syscall
# and ei have no C spelling either.  Transcribed from the shipped instruction
# stream (rungs: ROM bytes for the instructions, the listing rows for the
# source file).  The eight zero bytes the listing labels <_start-0x8> are
# crt0.s's pre-entry pad, not a function and carrying no symbol of its own,
# and are emitted here as data so the run starts at the same address.  The module ends after _root's syscall at
# 0x1000C8, as the listing shows; the zero fill to 0x100100 is klib.o's 64-byte
# alignment (sce/libkernl/klib.s), not part of crt0.
# The module's .bss (MAIN.MAP crt0.o 0x144): the argument block _start hands
# main, argc then argv's sixteen pointers and the 256 bytes they point into.
# Local in the source: the .globl below is transitional.  This tree's SDK
# assembler writes a .symtab whose sh_info omits a local symbol that is not a
# section symbol; the period linker (ld 2.10, the plain build) reads such an
# object and keeps the symbol local, the splat build's modern ld refuses it
# ("local symbol at index 6 (>= sh_info of 6)"), so the .globl goes at the
# cut-over.
    .section .bss
    .globl _args
_args: /* derived name */
    .space 4 + 16 * 4 + 256
    .section .text
    .set at
    .set noreorder
    .align 3
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
    lui $4, %hi(_gp)
    lui $5, %hi(_stack)
    lui $6, %hi(_stack_size)
    lui $7, %hi(_args)
    lui $8, %hi(_root)
    addiu $4, $4, %lo(_gp)
    addiu $5, $5, %lo(_stack)
    addiu $6, $6, %lo(_stack_size)
    addiu $7, $7, %lo(_args)
    addiu $8, $8, %lo(_root)
    daddu $28, $4, $0
    addiu $3, $0, 0x3C
    syscall 0
    daddu $29, $2, $0
    lui $4, %hi(_end)
    lui $5, %hi(_heap_size)
    addiu $4, $4, %lo(_end)
    addiu $5, $5, %lo(_heap_size)
    addiu $3, $0, 0x3D
    syscall 0
    jal _InitSys
    nop
    jal FlushCache
    daddu $4, $0, $0
    ei
    lui $2, %hi(_args)
    addiu $2, $2, %lo(_args)
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
    .size _root, . - _root
    .set reorder
    .set at
