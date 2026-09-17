/* libc.a member strcpy.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
/* MAIN.MAP member strlen.o starts at 0x0027F86C inside this file: not 8-aligned
 * in the shipped ELF, so it cannot open its own subsegment and is kept here. */
#include "common.h"
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern int D_0054CEAC[];
extern char D_00637E38[];
extern void fiprintf();
extern void abort(void);

INCLUDE_ASM("asm/nonmatchings/sce/libc/machine/r5900/strcpy", strcpy);
INCLUDE_ASM("asm/nonmatchings/sce/libc/machine/r5900/strcpy", strlen);
