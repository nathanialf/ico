/* libc.a member fiprintf.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
/* MAIN.MAP member memcmp.o starts at 0x0027E684 inside this file: not 8-aligned
 * in the shipped ELF, so it cannot open its own subsegment and is kept here. */
#include "common.h"
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern int D_0054CEAC[];
extern char D_00637E38[];
extern int fiprintf(void *fp, void *fmt, ...);
extern void abort(void);
extern int vfiprintf(void *fp, void *fmt, void *args);

int fiprintf(void *fp, void *fmt, ...)
{
    void *args = (char *)__builtin_next_arg(fmt) - 0x30;
    return vfiprintf(fp, fmt, args);
}

/* libc.a member memcmp.o.  SRCFILE.TXT attributes every one of these 37
 * instructions to src/newlib/libc/machine/r5900/memcmp.S, one instruction per
 * source line (listing rows 517478 on), so this member was ASSEMBLED, not
 * compiled, exactly like the memcpy / memset / strcat / strcpy / strncmp /
 * strncpy members of the same newlib r5900 directory that already live as .s
 * files here.  There is no C spelling: the body is an MMI quadword compare
 * (lq / pxor / pcpyud) and the pcpyud's third operand is the loop-continue
 * flag, a value the operation cannot even read.  memcmp.o starts at 0x0027E684
 * in the shipped ELF, which is not 8-aligned, so it cannot open its own
 * subsegment and the member is transcribed here instead (rungs: ROM bytes for
 * the instructions, the listing rows for the source file). */
__asm__(".section .text\n"
        "    .set noreorder\n"
        "    .globl memcmp\n"
        "    .type memcmp, @function\n"
        "    .ent memcmp\n"
        "memcmp:\n"
        "    sltiu  $2, $6, 0x10\n"
        "    bnez   $2, 2f\n"
        "    or     $2, $4, $5\n"
        "    andi   $2, $2, 0xF\n"
        "    bnez   $2, 2f\n"
        "    nop\n"
        "    .align 2\n"
        "1:\n"
        "    lq     $3, 0x0($4)\n"
        "    sltiu  $7, $6, 0x20\n"
        "    lq     $2, 0x0($5)\n"
        "    addiu  $4, $4, 0x10\n"
        "    pxor   $8, $2, $3\n"
        "    addiu  $2, $5, 0x10\n"
        "    pcpyud $10, $8, $7\n"
        "    or     $9, $10, $8\n"
        "    movz   $5, $2, $9\n"
        "    bnel   $9, $0, 2f\n"
        "    addiu  $4, $4, -0x10\n"
        "    beqz   $7, 1b\n"
        "    addiu  $6, $6, -0x10\n"
        "    .align 2\n"
        "2:\n"
        "    lui    $2, 0xFFFF\n"
        "    addiu  $6, $6, -0x1\n"
        "    ori    $2, $2, 0xFFFF\n"
        "    beq    $6, $2, 5f\n"
        "    nop\n"
        "    lui    $7, 0xFFFF\n"
        "    ori    $7, $7, 0xFFFF\n"
        "    .align 2\n"
        "3:\n"
        "    lbu    $3, 0x0($4)\n"
        "    lbu    $2, 0x0($5)\n"
        "    beq    $3, $2, 4f\n"
        "    addiu  $4, $4, 0x1\n"
        "    jr     $31\n"
        "    subu   $2, $3, $2\n"
        "    .align 2\n"
        "4:\n"
        "    addiu  $6, $6, -0x1\n"
        "    bne    $6, $7, 3b\n"
        "    addiu  $5, $5, 0x1\n"
        "    .align 2\n"
        "5:\n"
        "    jr     $31\n"
        "    daddu  $2, $0, $0\n"
        "    .end memcmp\n"
        "    .set reorder\n");
