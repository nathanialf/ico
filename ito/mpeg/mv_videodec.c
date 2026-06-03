#include "common.h"

int free_buf(int a0) {
    return *(int *)(a0 + 0xB8);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_videodec", videoDecCreate);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_videodec", videoDecBeginPut);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_videodec", videoDecEndPut);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_videodec", videoDecFlush);

extern void func_0023C5B0(void *a0);

int videoCallback(int a0, int a1, void *a2) {
    func_0023C5B0((char *)a2 + 0x50);
    return 1;
}

extern void func_0023C738(void *a0);

int decBitStrm0(void *a0, void *a1, void *a2) {
    func_0023C738((char *)a2 + 0x50);
    return 1;
}
