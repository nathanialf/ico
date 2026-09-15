/* libc.a member ungetc.o.  MAIN.MAP member spans tile this run exactly and
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

INCLUDE_ASM("asm/nonmatchings/sce/libc/stdio/ungetc", __submore);

extern void __sinit(void *r);
extern int fflush();
extern int __submore(char *fp);

int ungetc(int c, char *fp)
{
    if (c == -1)
        return -1;
    /* newlib's CHECK_INIT(fp), a do-while-zero macro wrapper */
    do {
        if (*(char **)(fp + 0x54) == 0)
            *(char **)(fp + 0x54) = (char *)D_0054CEAC[0];
        if (*(int *)(*(char **)(fp + 0x54) + 0x38) == 0)
            __sinit(*(char **)(fp + 0x54));
    } while (0);
    *(short *)(fp + 0xC) = *(unsigned short *)(fp + 0xC) & ~0x20;
    if ((*(unsigned short *)(fp + 0xC) & 4) == 0) {
        if ((*(unsigned short *)(fp + 0xC) & 0x10) == 0)
            return -1;
        if (*(unsigned short *)(fp + 0xC) & 8) {
            if (fflush(fp))
                return -1;
            *(short *)(fp + 0xC) = *(unsigned short *)(fp + 0xC) & ~8;
            *(int *)(fp + 0x8) = 0;
            *(int *)(fp + 0x18) = 0;
        }
        *(short *)(fp + 0xC) = *(unsigned short *)(fp + 0xC) | 4;
    }
    c = (unsigned char)c;
    if (*(char **)(fp + 0x30) != 0) {
        if (*(int *)(fp + 0x4) >= *(int *)(fp + 0x34) && __submore(fp))
            return -1;
        *--*(unsigned char **)(fp + 0x0) = c;
        *(int *)(fp + 0x4) += 1;
        return c;
    }
    if (*(char **)(fp + 0x10) != 0 &&
        *(unsigned char **)(fp + 0x0) > *(unsigned char **)(fp + 0x10) &&
        (*(unsigned char **)(fp + 0x0))[-1] == c) {
        *(unsigned char **)(fp + 0x0) -= 1;
        *(int *)(fp + 0x4) += 1;
        return c;
    }
    *(int *)(fp + 0x3C) = *(int *)(fp + 0x4);
    *(char **)(fp + 0x38) = *(char **)(fp + 0x0);
    *(char **)(fp + 0x30) = fp + 0x40;
    *(int *)(fp + 0x34) = 3;
    *(char *)(fp + 0x42) = c;
    *(char **)(fp + 0x0) = fp + 0x42;
    *(int *)(fp + 0x4) = 1;
    return c;
}
