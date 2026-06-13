#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/cage", CageRideFunc);

extern void SetMotionBlendlessNode(void *a0);

void SetCageFixGeometry(void *a0)
{
    int q = *(int *)(*(int *)((char *)a0 + 0x15C) + 0x7F0);
    SetMotionBlendlessNode(a0);
    *(int *)(q + 0x14) = 0;
    *(int *)(q + 0x10) = 1;
    *(int *)(*(int *)((char *)a0 + 0x15C) + 0x61C) = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/cage", InitCageGeo);

extern void MatrixDrive_TurnObjectMatrix(int a0, int a1);

void HotInitCageGeo(int a0, int a1, int a2)
{
    int q = *(int *)(*(int *)(a0 + 0x15C) + 0x7F0);
    int node = *(int *)(q + 0x20);
    MatrixDrive_TurnObjectMatrix(*(int *)node + 0x20, a1);
    MatrixDrive_TurnObjectMatrix(q + 0x10, a2);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/cage", CageGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/cage", CageDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/cage", GetCageChainPoint);
