#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", TestDispChainAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", GetChainExWeightGlobalPos);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", bindExWeight);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", bind2);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", calc2);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", GetChainAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", SetChainExtendedWeight);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", GetClothAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", clipCylinderCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", InitChains);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", InitClothes);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", DispClothMesh);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", DispMeshWire);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", DispCloth4D);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", getCloth4D_preProcess);

void proc(void *a0, int a1, float a2) {
    *(float *)((char *)a0 + a1 * 0x50 + 0x10) = a2;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", getCloth4D);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", getCloth4D_postProcess);

float GetCloth4D(void *a0, float a1) {
    return a1 / *(float *)((char *)a0 + 0x14);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", InitCloth4D);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", GetChainNodeGlobalQuaternion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", MoveChainExtendedWeight);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", InitChainVelocity);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", DeleteChainExtendedWeight);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", GetChainNodeID);
