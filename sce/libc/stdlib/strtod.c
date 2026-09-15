/* libc.a member strtod.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
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
extern void fiprintf();
extern void abort(void);
extern int strtod();

INCLUDE_ASM("asm/nonmatchings/sce/libc/stdlib/strtod", _strtod_r);

int strtod(s, end)
char *s;

char **end;

{
    return _strtod_r(D_0054CEAC[0], s, end);
}

extern int dptofp(long a0);
extern int strtod();

int strtodf(void)
{
    return dptofp(strtod());
}
