#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_readbuf", free_buffer);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_readbuf", readBufDelete);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_readbuf", readBufCreate);

extern void inflate_start(void *a0);

void readBufBeginPut(void *a0) {
    inflate_start(a0);
    __asm__ __volatile__("");
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
