/* libc.a member strcat.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
/* MAIN.MAP member strcmp.o starts at 0x0027F614 inside this file: not 8-aligned
 * in the shipped ELF, so it cannot open its own subsegment and is kept here. */
#include "common.h"
#include "r5900.h"
#include "vu0.h"
#include "math_private.h"

typedef struct PObjBlk {
    char pad0[4];
    unsigned int size; /* 0x4 */
} PObjBlk;

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

typedef struct {
    char *pos; /* 0x0 */
    int len;   /* 0x4 */
} StreamBuf;

extern int D_0054CEAC[];
extern char D_00637E38[];
extern void fiprintf();
extern void abort(void);
extern int _vfprintf_r(int *self, int subj, int b, void *args);

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        "    .global strcat\n"
        "    .type strcat, @function\n"
        "    .align 3\n"
        "strcat:\n"
        "    addiu  $29, $29, -0x20\n"
        "    sq     $16, 0x0($29)\n"
        "    daddu  $16, $4, $0\n"
        "    andi   $2, $16, 0x7\n"
        "    bnez   $2, .Lstrcat0026137C\n"
        "    sq     $31, 0x10($29)\n"
        "    andi   $2, $16, 0xF\n"
        "    lui    $3, 0x101\n"
        "    ori    $3, $3, 0x101\n"
        "    dsll   $3, $3, 16\n"
        "    ori    $3, $3, 0x101\n"
        "    dsll   $3, $3, 16\n"
        "    ori    $3, $3, 0x101\n"
        "    lui    $4, 0x8080\n"
        "    ori    $4, $4, 0x8080\n"
        "    dsll   $4, $4, 16\n"
        "    ori    $4, $4, 0x8080\n"
        "    dsll   $4, $4, 16\n"
        "    ori    $4, $4, 0x8080\n"
        "    bnez   $2, .Lstrcat00261338\n"
        "    ld     $6, 0x0($16)\n"
        "    lq     $2, 0x0($16)\n"
        "    pcpyld $7, $3, $3\n"
        "    pcpyld $8, $4, $4\n"
        "    psubb  $3, $2, $7\n"
        "    pnor   $2, $0, $2\n"
        "    pand   $3, $3, $2\n"
        "    pand   $3, $3, $8\n"
        "    pcpyud $2, $3, $3\n"
        "    or     $3, $2, $3\n"
        "    bnez   $3, .Lstrcat0026137C\n"
        "    daddu  $4, $16, $0\n"
        "    addiu  $6, $4, 0x10\n"
        "    .align 2\n"
        ".Lstrcat0026130C:\n"
        "    lq     $2, 0x0($6)\n"
        "    pnor   $3, $0, $2\n"
        "    psubb  $2, $2, $7\n"
        "    pand   $2, $2, $3\n"
        "    pand   $2, $2, $8\n"
        "    pcpyud $3, $2, $2\n"
        "    or     $2, $2, $3\n"
        "    beql   $2, $0, .Lstrcat0026130C\n"
        "    addiu  $6, $6, 0x10\n"
        "    b      .Lstrcat0026137C\n"
        "    daddu  $4, $6, $0\n"
        "    .align 2\n"
        ".Lstrcat00261338:\n"
        "    daddu  $7, $3, $0\n"
        "    daddu  $8, $4, $0\n"
        "    dsubu  $3, $6, $3\n"
        "    nor    $2, $0, $6\n"
        "    and    $3, $3, $2\n"
        "    and    $3, $3, $4\n"
        "    bnez   $3, .Lstrcat0026137C\n"
        "    daddu  $4, $16, $0\n"
        "    addiu  $6, $16, 0x8\n"
        "    .align 2\n"
        ".Lstrcat0026135C:\n"
        "    ld     $2, 0x0($6)\n"
        "    nor    $3, $0, $2\n"
        "    dsubu  $2, $2, $7\n"
        "    and    $2, $2, $3\n"
        "    and    $2, $2, $8\n"
        "    beql   $2, $0, .Lstrcat0026135C\n"
        "    addiu  $6, $6, 0x8\n"
        "    daddu  $4, $6, $0\n"
        "    .align 2\n"
        ".Lstrcat0026137C:\n"
        "    lb     $2, 0x0($4)\n"
        "    nop\n"
        "    nop\n"
        "    nop\n"
        "    nop\n"
        "    bnel   $2, $0, .Lstrcat0026137C\n"
        "    addiu  $4, $4, 0x1\n"
        "    jal    strcpy\n"
        "    nop\n"
        "    daddu  $2, $16, $0\n"
        "    lq     $31, 0x10($29)\n"
        "    lq     $16, 0x0($29)\n"
        "    jr     $31\n"
        "    addiu  $29, $29, 0x20\n"
        "    .size strcat, . - strcat\n"
        "    .set reorder\n"
        "    .set at\n");

INCLUDE_ASM("asm/nonmatchings/sce/libc/machine/r5900/strcat", strcmp);

extern int strcmp(int *p, int *buf);
