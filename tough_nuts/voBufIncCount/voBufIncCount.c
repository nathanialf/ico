#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vobuf", func_0019B8E0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vobuf", voBufCreate);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vobuf", voBufDelete);

extern void voBufCreate(void);

void voBufReset(void) {
    voBufCreate();
}

extern int iosMallocCheckLeak2(int a0);

void voBufIsFull(int a0) {
    iosMallocCheckLeak2(a0 & 0xFFFFFFF);
}

void voBufIncCount(int *a0) {
    a0[3] = 0;
    a0[2] = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vobuf", voBufGetData);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vobuf", voBufGetTag);
