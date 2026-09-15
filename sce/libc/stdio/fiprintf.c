/* libc.a member fiprintf.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
/* MAIN.MAP member memcmp.o starts at 0x0027E684 inside this file: not 8-aligned
 * in the shipped ELF, so it cannot open its own subsegment and is kept here. */
#include "common.h"

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
extern int fiprintf(void *fp, void *fmt, ...);
extern void abort(void);
extern int vfiprintf(void *fp, void *fmt, void *args);

int fiprintf(void *fp, void *fmt, ...)
{
    void *args = (char *)__builtin_next_arg(fmt) - 0x30;
    return vfiprintf(fp, fmt, args);
}

INCLUDE_ASM("asm/nonmatchings/sce/libc/stdio/fiprintf", memcmp);
