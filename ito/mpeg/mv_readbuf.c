#include "common.h"

int free_buffer(void *a0, int a1) {
    int *p = (int *)a0;
    int n = p[3];
    int t = n;
    if (a1 < n) {
        n = a1;
    }
    p[3] = t - n;
    return n;
}

extern void func_002614F8(void *a0);
extern void iosCdvdSync(void *a0);

int readBufDelete(char *a0) {
    func_002614F8(a0 + 0x34);
    iosCdvdSync(a0);
    return 1;
}

extern int inflate_dynamic(void);

int readBufCreate(void)
{
    inflate_dynamic();
    return 1;
}

extern int inflate_start(void *a0);

int readBufBeginPut(void *a0) {
    return inflate_start(a0);
}

extern void func_0019B720(void *a0);

void readBufEndPut(void *a0) {
    func_0019B720(*(void **)((char *)a0 + 0x48));
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_readbuf", readBufBeginGet);

extern void func_0023C1D8(void *a0);

void readBufEndGet(void *a0) {
    func_0023C1D8((char *)a0 + 0x50);
}
