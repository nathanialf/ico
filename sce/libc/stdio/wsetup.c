/* libc.a member wsetup.o.  MAIN.MAP member spans tile this run exactly and
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
extern void fiprintf();
extern void abort(void);
extern void __sinit(void *a0);
extern void _free_r(void *a0, void *a1);
extern void __smakebuf(void *a0);

int __swsetup(void *fp)
{
    do {
        if (*(char **)((char *)fp + 0x54) == 0) {
            *(char **)((char *)fp + 0x54) = (char *)D_0054CEAC[0];
        }
        if (*(int *)(*(char **)((char *)fp + 0x54) + 0x38) == 0) {
            __sinit(*(char **)((char *)fp + 0x54));
        }
    } while (0);

    if ((*(short *)((char *)fp + 0xC) & 8) == 0) {
        if ((*(short *)((char *)fp + 0xC) & 0x10) == 0) {
            return -1;
        }
        if (*(short *)((char *)fp + 0xC) & 4) {
            if (*(char **)((char *)fp + 0x30) != 0) {
                if (*(char **)((char *)fp + 0x30) != (char *)fp + 0x40) {
                    _free_r(*(void **)((char *)fp + 0x54), *(void **)((char *)fp + 0x30));
                }
                *(char **)((char *)fp + 0x30) = 0;
            }
            *(short *)((char *)fp + 0xC) &= ~0x24;
            *(int *)((char *)fp + 4) = 0;
            *(char **)fp = *(char **)((char *)fp + 0x10);
        }
        *(short *)((char *)fp + 0xC) |= 8;
    }

    if (*(char **)((char *)fp + 0x10) == 0) {
        __smakebuf(fp);
    }
    if (*(short *)((char *)fp + 0xC) & 1) {
        *(int *)((char *)fp + 8) = 0;
        *(int *)((char *)fp + 0x18) = -*(int *)((char *)fp + 0x14);
    } else {
        *(int *)((char *)fp + 8) =
            (*(short *)((char *)fp + 0xC) & 2) ? 0 : *(int *)((char *)fp + 0x14);
    }
    return 0;
}
