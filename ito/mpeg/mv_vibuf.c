#include "common.h"

void func_0023B4D0(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufCreate);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufReset);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufBeginPut);

extern int D_0062BE90;
extern int D_0062C2DC;

void viBufEndPut(void) {
    D_0062BE90 = 0;
    D_0062C2DC = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufAddDMA);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufStopDMA);

void *viBufRestartDMA(int *a0, int a1, long long a2) {
    a0[0] = (int)(a2 & 0xFFFFFFFFLL);
    a0[1] = (int)(a2 >> 32);
    a0[2] = a1;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

void *viBufFlush(void *a0) {
    int *p = (int *)a0;
    p[0] = 0;
    p[2] = 0x3F;
    p[1] = 0;
    p[3] = 0;
    return (char *)a0 + 0x10;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufModifyPts);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufGetTs);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufDelete);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufCount);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", viBufPutTs);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", func_0023B920);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", func_0023B970);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", func_0023B9D0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", func_0023BA60);

void *func_0023BAB8(int *a0, unsigned int a1, unsigned int a2) {
    unsigned long long v = (unsigned int)a1 | ((unsigned long long)a2 << 32);
    int new_var;
    a0[0] = (int)(v << 32 >> 32);
    new_var = (int)(v >> 32);
    a0[1] = new_var;
    a0[2] = 0x18;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

void *func_0023BAF0(int *a0, unsigned int a1) {
    unsigned long long v = (unsigned int)a1;
    int new_var;
    a0[2] = 0x1A;
    a0[0] = (int)v;
    new_var = (int)(v >> 32);
    a0[1] = new_var;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_vibuf", func_0023BB20);
