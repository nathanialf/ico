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

typedef struct { long long x; } __attribute__((packed, aligned(4))) PackedLL_19CAF0;
extern void GetRootMatrixRotOffsetByDObj();

void func_0019CAA8(void *a0, PackedLL_19CAF0 *a1) {
    PackedLL_19CAF0 *p;
    GetRootMatrixRotOffsetByDObj(a0, a1);
    p = *(PackedLL_19CAF0 **)((char *)a0 + 0x15C);
    *p = *a1;
}

extern PackedLL_19CAF0 D_0062A6A0;
extern void SetRootMatrixRotOffsetByDObj(void *a0);
void func_0019CAF0(void *a0) {
    PackedLL_19CAF0 *p;
    SetRootMatrixRotOffsetByDObj(a0);
    p = *(PackedLL_19CAF0 **)((char *)a0 + 0x15C);
    *p = D_0062A6A0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/DObj", func_0019CB28);
