#include "common.h"


#include "vu0.h"
INCLUDE_ASM("asm/nonmatchings/src/Matrix", _RemakeNormal);

INCLUDE_ASM("asm/nonmatchings/src/Matrix", _Sqrt);

INCLUDE_ASM("asm/nonmatchings/src/Matrix", _InitCurrentMatrix);

void _UnitCurrentMatrix(void *p0)
{
    VU0_LSV(sqc2, 4, 0x0, a0);
    VU0_LSV(sqc2, 5, 0x10, a0);
    VU0_LSV(sqc2, 6, 0x20, a0);
    VU0_LSV(sqc2, 7, 0x30, a0);
    VU0_NOP();
}

void _PushCurrentMatrix(void *p0)
{
    VU0_LSV(sqc2, 7, 0x0, a0);
    VU0_NOP();
}

void _PopCurrentMatrix(void *p0)
{
    VU0_LSV(lqc2, 4, 0x0, a0);
    VU0_LSV(lqc2, 5, 0x10, a0);
    VU0_LSV(lqc2, 6, 0x20, a0);
    VU0_LSV(lqc2, 7, 0x30, a0);
    VU0_NOP();
}

INCLUDE_ASM("asm/nonmatchings/src/Matrix", _TransCurrentMatrix);

void _SetTransCurrentMatrix(void *m)
{
    VU0_LSV(lqc2, 14, 0x0, a0);
    VU0_LSV(lqc2, 15, 0x10, a0);
    VU0_LSV(lqc2, 16, 0x20, a0);
    VU0_LSV(lqc2, 17, 0x30, a0);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 4, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 4, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 4, z);
    VU0_V3OP_BC(vmaddw.xyzw, 4, 17, 4, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 5, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 5, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 5, z);
    VU0_V3OP_BC(vmaddw.xyzw, 5, 17, 5, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 6, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 6, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 6, z);
    VU0_V3OP_BC(vmaddw.xyzw, 6, 17, 6, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 7, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 7, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 7, z);
    VU0_V3OP_BC(vmaddw.xyzw, 7, 17, 7, w);
    VU0_NOP();
}

void _ClearTransCurrentMatrix(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 8, 0x0, a1);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 8, z);
    VU0_V3OP_BC(vmaddw.xyzw, 10, 7, 8, w);
    VU0_LSV(sqc2, 10, 0x0, a0);
    VU0_NOP();
}

void _RotCurrentMatrixX(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 8, 0x0, a1);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 8, z);
    VU0_V3OP_BC(vmaddw.xyzw, 10, 7, 8, w);
    VU0_REG("vdiv $Q, $vf0w, $vf10w");
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf10, $vf10, $Q");
    VU0_LSV(sqc2, 10, 0x0, a0);
    VU0_NOP();
}

void _RotCurrentMatrixY(void)
{
    VU0_V3OP(vsub.xyzw, 1, 0, 0);
    VU0_V3OP_BC(vaddx.y, 14, 1, 5, x);
    VU0_V3OP_BC(vaddx.z, 14, 1, 6, x);
    VU0_V3OP_BC(vaddx.w, 14, 1, 7, x);
    VU0_V3OP_BC(vaddy.x, 15, 1, 4, y);
    VU0_V3OP_BC(vaddy.z, 15, 1, 6, y);
    VU0_V3OP_BC(vaddy.w, 15, 1, 7, y);
    VU0_V3OP_BC(vaddz.x, 16, 1, 4, z);
    VU0_V3OP_BC(vaddz.y, 16, 1, 5, z);
    VU0_V3OP_BC(vaddz.w, 16, 1, 7, z);
    VU0_V3OP_BC(vaddw.x, 17, 1, 4, w);
    VU0_V3OP_BC(vaddw.y, 17, 1, 5, w);
    VU0_V3OP_BC(vaddw.z, 17, 1, 6, w);
    VU0_V2OP(vmove.yzw, 4, 14);
    VU0_V2OP(vmove.xzw, 5, 15);
    VU0_V2OP(vmove.xyw, 6, 16);
    VU0_V2OP(vmove.xyz, 7, 17);
    VU0_NOP();
}

void _RotCurrentMatrixZ(void)
{
    VU0_V3OP(vsub.xyzw, 1, 0, 0);
    VU0_V3OP_BC(vaddx.y, 14, 1, 5, x);
    VU0_V3OP_BC(vaddx.z, 14, 1, 6, x);
    VU0_V3OP_BC(vaddy.x, 15, 1, 4, y);
    VU0_V3OP_BC(vaddy.z, 15, 1, 6, y);
    VU0_V3OP_BC(vaddz.x, 16, 1, 4, z);
    VU0_V3OP_BC(vaddz.y, 16, 1, 5, z);
    VU0_V2OP(vmove.yz, 4, 14);
    VU0_V2OP(vmove.xz, 5, 15);
    VU0_V2OP(vmove.xy, 6, 16);
    VU0_NOP();
}

void _ScaleCurrentMatrix(void)
{
    VU0_V3OP(vsub.xyzw, 1, 0, 0);
    VU0_V3OP_BC(vsubw.x, 2, 0, 0, w);
    VU0_V3OP_BC(vaddx.y, 14, 1, 5, x);
    VU0_V3OP_BC(vaddx.z, 14, 1, 6, x);
    VU0_V3OP_BC(vaddy.x, 15, 1, 4, y);
    VU0_V3OP_BC(vaddy.z, 15, 1, 6, y);
    VU0_V3OP_BC(vaddz.x, 16, 1, 4, z);
    VU0_V3OP_BC(vaddz.y, 16, 1, 5, z);
    VU0_V3OP_BC(vmulx.xyz, 17, 7, 2, x);
    VU0_V2OP(vmove.yz, 4, 14);
    VU0_V2OP(vmove.xz, 5, 15);
    VU0_V2OP(vmove.xy, 6, 16);
    VU0_V2OP(vmove.w, 17, 0);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 17, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 17, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 17, z);
    VU0_V3OP_BC(vmaddw.xyzw, 7, 0, 17, w);
    VU0_NOP();
}

INCLUDE_ASM("asm/nonmatchings/src/Matrix", _GetCurrentMatrix);

INCLUDE_ASM("asm/nonmatchings/src/Matrix", _GetCurrentMatrixTrans);

void _SetCurrentMatrix(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_V3OP(vmul.xyz, 3, 1, 1);
    VU0_V3OP_ACC_BC(vmulax.w, 0, 3, x);
    VU0_V3OP_ACC_BC(vmadday.w, 0, 3, y);
    VU0_V3OP_BC(vmaddz.w, 3, 0, 3, z);
    VU0_REG("vrsqrt $Q, $vf0w, $vf3w");
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf1, $vf1, $Q");
    VU0_LSV(sqc2, 1, 0x0, a0);
    VU0_NOP();
}

void _MulCurrentMatrixR(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 1, 0x0, a0);
    VU0_LSV(lqc2, 2, 0x0, a1);
    VU0_V3OP_BC(vaddw.x, 3, 0, 0, w);
    VU0_V3OP(vmul.xyz, 2, 1, 2);
    VU0_V3OP_ACC_BC(vaddax.x, 0, 2, x);
    VU0_V3OP_ACC_BC(vmadday.x, 3, 2, y);
    VU0_V3OP_BC(vmaddz.x, 2, 3, 2, z);
    VU0_QMFC2_NI(v0, 2);
    VU0_MTC1(v0, 0);
    VU0_NOP();
}

void _MulCurrentMatrixL(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP_ACC(vopmula.xyz, 1, 2);
    VU0_V3OP(vopmsub.xyz, 3, 2, 1);
    VU0_V3OP(vsub.w, 3, 3, 3);
    VU0_LSV(sqc2, 3, 0x0, a0);
    VU0_NOP();
}

void _ApplyCurrentMatrix(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP(vadd.xyzw, 3, 1, 2);
    VU0_LSV(sqc2, 3, 0x0, a0);
    VU0_NOP();
}

void _RotTransPersCurrentMatrix(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP(vadd.xyz, 1, 1, 2);
    VU0_LSV(sqc2, 1, 0x0, a0);
    VU0_NOP();
}

void _TransposeCurrentMatrix(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP(vsub.xyzw, 3, 1, 2);
    VU0_LSV(sqc2, 3, 0x0, a0);
    VU0_NOP();
}

void _TransposeRotationCurrentMatrix(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP(vsub.xyz, 1, 1, 2);
    VU0_LSV(sqc2, 1, 0x0, a0);
    VU0_NOP();
}

void _InverseCurrentMatrix(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 2);
    VU0_NOREORDER_END();
    VU0_V3OP_BC(vmulx.xyzw, 3, 1, 2, x);
    VU0_LSV(sqc2, 3, 0x0, a0);
    VU0_NOP();
}

void _PushVu0Registers(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 2);
    VU0_NOREORDER_END();
    VU0_V3OP_BC(vmulx.xyz, 1, 1, 2, x);
    VU0_LSV(sqc2, 1, 0x0, a0);
    VU0_NOP();
}

void _PopVu0Registers(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP_BC(vmulx.x, 1, 1, 2, x);
    VU0_V3OP_BC(vmuly.y, 1, 1, 2, y);
    VU0_V3OP_BC(vmulz.z, 1, 1, 2, z);
    VU0_LSV(sqc2, 1, 0x0, a0);
    VU0_NOP();
}

