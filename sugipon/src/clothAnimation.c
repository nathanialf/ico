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

float InitChainVelocity(float a0) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "mfc1 $8, $f12\n"
        "qmtc2.ni $8, $vf4\n"
        "vrsqrt $Q, $vf0w, $vf4x\n"
        "vwaitq\n"
        "cfc2.ni $2, $vi22\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2", "$8");
    return ret;
}

float DeleteChainExtendedWeight(void *a0) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf4, 0x0($4)\n"
        "vmul.xz $vf4, $vf4, $vf4\n"
        "vaddz.x $vf4, $vf4, $vf4z\n"
        ".word 0x4A0403BD\n"
        "vwaitq\n"
        "cfc2.ni $2, $vi22\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2");
    return ret;
}

float GetChainNodeID(void *a0) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf4, 0x0($4)\n"
        "vmul.xz $vf4, $vf4, $vf4\n"
        "vaddz.x $vf4, $vf4, $vf4z\n"
        "vrsqrt $Q, $vf0w, $vf4x\n"
        "vwaitq\n"
        "cfc2.ni $2, $vi22\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2");
    return ret;
}
