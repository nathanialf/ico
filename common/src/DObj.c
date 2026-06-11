#include "common.h"

int initGeometryState(volatile int *a0) {
    return a0[3] != a0[4] ? a0[0] + a0[2] * 0x151800 : 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/DObj", initMatrixDObj);

void allocObjectData(void *a0) {
    if (*(volatile int *)((char *)a0 + 0xC) > 0) {
        *(volatile int *)((char *)a0 + 0xC) = *(volatile int *)((char *)a0 + 0xC) - 1;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/DObj", initInitialInverseMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/DObj", initPolygonState);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/DObj", CSVSYSTEM_InitDObj);

extern int D_0062A310;
extern int iosFree(int a0, int a1, int *a2, int a3);
extern void SetDirectRootPositionNoFittingWithNodePoint(int v, int *self);

extern char D_0060B090[];

void FreeDObj(int *self) {
    int v = iosFree(D_0062A310, self[0x88/4] << 6, (int*)D_0060B090, 0x14C);
    self[0x90/4] = v;
    SetDirectRootPositionNoFittingWithNodePoint(v, self);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/DObj", LinkParentOfDObj);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/DObj", UnlinkParentOfDObj);

void func_0019CAA0(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/DObj", func_0019CAA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/DObj", func_0019CAF0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/DObj", func_0019CB28);
