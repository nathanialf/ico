#include "common.h"


extern void SetMotionBlendlessNode();
INCLUDE_ASM("asm/nonmatchings/src/cage", CageRideFunc);

void SetCageFixGeometry(int *self)
{
    int *p;
    p = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    SetMotionBlendlessNode(self);
    p[0x14 / 4] = 0;
    p[0x10 / 4] = 1;
    ((int *)self[0x15C / 4])[0x62C / 4] = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cage", InitCageGeo);

INCLUDE_ASM("asm/nonmatchings/src/cage", HotInitCageGeo);

INCLUDE_ASM("asm/nonmatchings/src/cage", CageGeo);

INCLUDE_ASM("asm/nonmatchings/src/cage", CageDL);

INCLUDE_ASM("asm/nonmatchings/src/cage", GetCageChainPoint);

