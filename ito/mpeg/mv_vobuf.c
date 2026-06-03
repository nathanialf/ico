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

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vobuf", voBufIncCount);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vobuf", voBufGetData);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vobuf", voBufGetTag);
