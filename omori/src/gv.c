#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _InterGV);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", GetMatrixDirectionToZ);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _InterRotGV);

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

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _RotGV);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _RotGVF);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _OrientXZGV);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _OrientGV);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/gv", _FrontGV);
