#include "common.h"

int _InterGV(void *a0, void *a1) {
    *(float *)a0 = *(float *)((char *)a1 + 0x10);
    *(float *)((char *)a0 + 4) = *(float *)((char *)a1 + 0x14);
    *(float *)((char *)a0 + 8) = *(float *)((char *)a1 + 0x18);
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", GetMatrixDirectionToZ);

int _InterRotGV(void *a0, void *a1) {
    int *p = *(int **)((char *)a1 + 0x15C);
    unsigned short *q = *(unsigned short **)((char *)p + 0x7F0);
    *(unsigned short *)a0 = *(unsigned short *)((char *)q + 0x50);
    *(unsigned short *)((char *)a0 + 2) = *(unsigned short *)((char *)q + 0x8);
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _DistxzSqGV);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _DistSqGV);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _DistGV);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _DistxzGV);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _MoveGV);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _RotyGV);

int _AbsRotyGV(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return q[2] == 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _ApplyRyGV);

void _GetDirection(short *a0) {
    a0[0] = 1;
    a0[1] = 1;
}

typedef struct { char _[0x48]; int f48; } GVState;
extern GVState D_002E0064;

void _RotGV(void) {
    D_002E0064.f48 = (D_002E0064.f48 | 0x200000) & 0xFFFBFFFF;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _RotGVF);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _OrientXZGV);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _OrientGV);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _FrontGV);
