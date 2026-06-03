#include "common.h"

void free_buffer(void *a0, int a1) {
    int *p = (int *)a0;
    int n = p[3];
    int t = n;
    if (a1 < n) {
        n = a1;
    }
    p[3] = t - n;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_readbuf", readBufDelete);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_readbuf", readBufCreate);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_readbuf", readBufBeginPut);

extern void func_0019B720(void *a0);

void readBufEndPut(void *a0) {
    func_0019B720(*(void **)((char *)a0 + 0x48));
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_readbuf", readBufBeginGet);

extern void func_0023C1D8(void *a0);

void readBufEndGet(void *a0) {
    func_0023C1D8((char *)a0 + 0x50);
}
