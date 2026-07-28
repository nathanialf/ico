#include "common.h"


#include "vu0.h"
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", TestDispChainAnimation);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", GetChainExWeightGlobalPos);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", bindExWeight);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", bind2);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", calc2);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", GetChainAnimation);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", SetChainExtendedWeight);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", GetClothAnimation);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", clipCylinderCollision);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", InitChains);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", InitClothes);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", DispClothMesh);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", DispMeshWire);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", DispCloth4D);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", getCloth4D_preProcess);

void proc(int a0, int a1, float f)
{
    *(float *)(a0 + a1 * 0x50 + 0x10) = f;
}

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", getCloth4D);

void getCloth4D_postProcess(int *a0, int a1)
{
    int *p = (int *)((char *)a0 + a1 * 0x50);
    *(float *)((char *)p + 0x10) = -1.0f;
    a0[3] = a0[3] - 1;
}

float GetCloth4D(int a0, float f)
{
    return f / *(float *)(a0 + 0x14);
}

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", InitCloth4D);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", GetChainNodeGlobalQuaternion);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", MoveChainExtendedWeight);

void InitChainVelocity(void)
{
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 4);
    VU0_NOREORDER_END();
    VU0_REG("vrsqrt $Q, $vf0w, $vf4x");
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}

void DeleteChainExtendedWeight(void *p0)
{
    VU0_LSV(lqc2, 4, 0x0, a0);
    VU0_V3OP(vmul.xz, 4, 4, 4);
    VU0_V3OP_BC(vaddz.x, 4, 4, 4, z);
    VU0_WORD(0x4A0403BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}

void GetChainNodeID(void *p0)
{
    VU0_LSV(lqc2, 4, 0x0, a0);
    VU0_V3OP(vmul.xz, 4, 4, 4);
    VU0_V3OP_BC(vaddz.x, 4, 4, 4, z);
    VU0_REG("vrsqrt $Q, $vf0w, $vf4x");
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}

