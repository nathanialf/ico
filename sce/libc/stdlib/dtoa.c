/* libc.a member dtoa.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
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

INCLUDE_ASM("asm/nonmatchings/sce/libc/stdlib/dtoa", quorem);
INCLUDE_ASM("asm/nonmatchings/sce/libc/stdlib/dtoa", _dtoa_r);
