#include "common.h"


#include "vu0.h"
extern float GetTableCos(short a0);
extern float p2o_SetDefaultEnviroment(int x);

void _RotCurrentMatrixY(short a0)
{
    float c = GetTableCos(a0);
    float s = p2o_SetDefaultEnviroment(a0);
    __asm__ __volatile__("mfc1 $8, %0" : : "f"(c) : "$8");
    __asm__ __volatile__("mfc1 $9, %0" : : "f"(s) : "$9");
    VU0_QMTC2_NI(8, 1);
    VU0_QMTC2_NI(9, 2);
    VU0_V2OP(vmove.xyzw, 17, 0);
    VU0_V2OP(vmr32.xyzw, 16, 17);
    VU0_V2OP(vmr32.xyzw, 15, 16);
    VU0_V2OP(vmr32.xyzw, 14, 15);
    VU0_V3OP_BC(vaddx.x, 14, 0, 1, x);
    VU0_V3OP_BC(vaddx.x, 16, 0, 2, x);
    VU0_V3OP_BC(vsubx.z, 14, 0, 2, x);
    VU0_V3OP_BC(vaddx.z, 16, 0, 1, x);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 14, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 14, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 14, z);
    VU0_V3OP_BC(vmaddw.xyzw, 14, 7, 14, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 15, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 15, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 15, z);
    VU0_V3OP_BC(vmaddw.xyzw, 15, 7, 15, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 16, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 16, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 16, z);
    VU0_V3OP_BC(vmaddw.xyzw, 16, 7, 16, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 17, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 17, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 17, z);
    VU0_V3OP_BC(vmaddw.xyzw, 17, 7, 17, w);
    VU0_V2OP(vmove.xyzw, 4, 14);
    VU0_V2OP(vmove.xyzw, 5, 15);
    VU0_V2OP(vmove.xyzw, 6, 16);
    VU0_V2OP(vmove.xyzw, 7, 17);
}

void _RotCurrentMatrixZ(short a0)
{
    float c = GetTableCos(a0);
    float s = p2o_SetDefaultEnviroment(a0);
    __asm__ __volatile__("mfc1 $8, %0" : : "f"(c) : "$8");
    __asm__ __volatile__("mfc1 $9, %0" : : "f"(s) : "$9");
    VU0_QMTC2_NI(8, 1);
    VU0_QMTC2_NI(9, 2);
    VU0_V2OP(vmove.xyzw, 17, 0);
    VU0_V2OP(vmr32.xyzw, 16, 17);
    VU0_V2OP(vmr32.xyzw, 15, 16);
    VU0_V2OP(vmr32.xyzw, 14, 15);
    VU0_V3OP_BC(vaddx.x, 14, 0, 1, x);
    VU0_V3OP_BC(vsubx.x, 15, 0, 2, x);
    VU0_V3OP_BC(vaddx.y, 14, 0, 2, x);
    VU0_V3OP_BC(vaddx.y, 15, 0, 1, x);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 14, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 14, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 14, z);
    VU0_V3OP_BC(vmaddw.xyzw, 14, 7, 14, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 15, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 15, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 15, z);
    VU0_V3OP_BC(vmaddw.xyzw, 15, 7, 15, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 16, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 16, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 16, z);
    VU0_V3OP_BC(vmaddw.xyzw, 16, 7, 16, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 17, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 17, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 17, z);
    VU0_V3OP_BC(vmaddw.xyzw, 17, 7, 17, w);
    VU0_V2OP(vmove.xyzw, 4, 14);
    VU0_V2OP(vmove.xyzw, 5, 15);
    VU0_V2OP(vmove.xyzw, 6, 16);
    VU0_V2OP(vmove.xyzw, 7, 17);
}

void _ScaleCurrentMatrix(float a0, float a1, float a2)
{
    VU0_MFC1(6, 12);
    VU0_MFC1(7, 13);
    VU0_MFC1(8, 14);
    VU0_QMTC2_NI(6, 1);
    VU0_QMTC2_NI(7, 2);
    VU0_QMTC2_NI(8, 3);
    VU0_V2OP(vmove.xyzw, 17, 0);
    VU0_V2OP(vmr32.xyzw, 16, 17);
    VU0_V2OP(vmr32.xyzw, 15, 16);
    VU0_V2OP(vmr32.xyzw, 14, 15);
    VU0_V3OP_BC(vaddx.x, 14, 0, 1, x);
    VU0_V3OP_BC(vaddx.y, 15, 0, 2, x);
    VU0_V3OP_BC(vaddx.z, 16, 0, 3, x);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 14, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 14, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 14, z);
    VU0_V3OP_BC(vmaddw.xyzw, 14, 7, 14, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 15, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 15, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 15, z);
    VU0_V3OP_BC(vmaddw.xyzw, 15, 7, 15, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 16, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 16, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 16, z);
    VU0_V3OP_BC(vmaddw.xyzw, 16, 7, 16, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 17, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 17, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 17, z);
    VU0_V3OP_BC(vmaddw.xyzw, 17, 7, 17, w);
    VU0_V2OP(vmove.xyzw, 4, 14);
    VU0_V2OP(vmove.xyzw, 5, 15);
    VU0_V2OP(vmove.xyzw, 6, 16);
    VU0_V2OP(vmove.xyzw, 7, 17);
    VU0_NOP();
}

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

void _SetCurrentMatrix(void *p0)
{
    VU0_LSV(lqc2, 4, 0x0, a0);
    VU0_LSV(lqc2, 5, 0x10, a0);
    VU0_LSV(lqc2, 6, 0x20, a0);
    VU0_LSV(lqc2, 7, 0x30, a0);
    VU0_NOP();
}

void _MulCurrentMatrixR(void *a0)
{
    VU0_LSV(lqc2, 14, 0x0, 4);
    VU0_LSV(lqc2, 15, 0x10, 4);
    VU0_LSV(lqc2, 16, 0x20, 4);
    VU0_LSV(lqc2, 17, 0x30, 4);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 14, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 14, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 14, z);
    VU0_V3OP_BC(vmaddw.xyzw, 14, 7, 14, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 15, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 15, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 15, z);
    VU0_V3OP_BC(vmaddw.xyzw, 15, 7, 15, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 16, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 16, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 16, z);
    VU0_V3OP_BC(vmaddw.xyzw, 16, 7, 16, w);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 17, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 17, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 17, z);
    VU0_V3OP_BC(vmaddw.xyzw, 17, 7, 17, w);
    VU0_V2OP(vmove.xyzw, 4, 14);
    VU0_V2OP(vmove.xyzw, 5, 15);
    VU0_V2OP(vmove.xyzw, 6, 16);
    VU0_V2OP(vmove.xyzw, 7, 17);
    VU0_NOP();
}

void _MulCurrentMatrixL(void *m)
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

void _ApplyCurrentMatrix(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 8, 0x0, a1);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 8, z);
    VU0_V3OP_BC(vmaddw.xyzw, 10, 7, 8, w);
    VU0_LSV(sqc2, 10, 0x0, a0);
    VU0_NOP();
}

void _RotTransPersCurrentMatrix(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 8, 0x0, a1);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 8, z);
    VU0_V3OP_BC(vmaddw.xyzw, 10, 7, 8, w);
    VU0_REG("vdiv Q, $vf0w, $vf10w");
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf10, $vf10, Q");
    VU0_LSV(sqc2, 10, 0x0, a0);
    VU0_NOP();
}

void _TransposeCurrentMatrix(void)
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

void _TransposeRotationCurrentMatrix(void)
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

void _InverseCurrentMatrix(void)
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

void _GetCurrentMatrix(void)
{
    VU0_MEM("vsqi.xyzw $vf1, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf2, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf3, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf4, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf5, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf6, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf7, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf8, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf9, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf10, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf11, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf12, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf13, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf14, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf15, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf16, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf17, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf18, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf19, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf20, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf21, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf22, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf23, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf24, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf25, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf26, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf27, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf28, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf29, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf30, ($vi15++)");
    VU0_MEM("vsqi.xyzw $vf31, ($vi15++)");
    VU0_NOP();
}

void _GetCurrentMatrixTrans(void)
{
    VU0_MEM("vlqd.xyzw $vf31, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf30, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf29, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf28, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf27, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf26, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf25, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf24, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf23, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf22, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf21, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf20, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf19, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf18, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf17, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf16, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf15, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf14, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf13, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf12, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf11, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf10, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf9, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf8, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf7, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf6, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf5, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf4, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf3, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf2, (--$vi15)");
    VU0_MEM("vlqd.xyzw $vf1, (--$vi15)");
    VU0_NOP();
}

void _NormalizeVector(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_V3OP(vmul.xyz, 3, 1, 1);
    VU0_V3OP_ACC_BC(vmulax.w, 0, 3, x);
    VU0_V3OP_ACC_BC(vmadday.w, 0, 3, y);
    VU0_V3OP_BC(vmaddz.w, 3, 0, 3, z);
    VU0_REG("vrsqrt Q, $vf0w, $vf3w");
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf1, $vf1, Q");
    VU0_LSV(sqc2, 1, 0x0, a0);
    VU0_NOP();
}

void _InnerProduct(void *p0, void *p1, void *p2)
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

void _OuterProduct(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP_ACC(vopmula.xyz, 1, 2);
    VU0_V3OP(vopmsub.xyz, 3, 2, 1);
    VU0_V3OP(vsub.w, 3, 3, 3);
    VU0_LSV(sqc2, 3, 0x0, a0);
    VU0_NOP();
}

void _AddVector(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP(vadd.xyzw, 3, 1, 2);
    VU0_LSV(sqc2, 3, 0x0, a0);
    VU0_NOP();
}

void _AddVectorXYZ(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP(vadd.xyz, 1, 1, 2);
    VU0_LSV(sqc2, 1, 0x0, a0);
    VU0_NOP();
}

void _SubVector(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP(vsub.xyzw, 3, 1, 2);
    VU0_LSV(sqc2, 3, 0x0, a0);
    VU0_NOP();
}

void _SubVectorXYZ(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP(vsub.xyz, 1, 1, 2);
    VU0_LSV(sqc2, 1, 0x0, a0);
    VU0_NOP();
}

void _ScaleVector(void *p0, void *p1, void *p2)
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

void _ScaleVectorXYZ(void *p0, void *p1, void *p2)
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

void _ScaleVector2XYZ(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP_BC(vmulx.x, 1, 1, 2, x);
    VU0_V3OP_BC(vmuly.y, 1, 1, 2, y);
    VU0_V3OP_BC(vmulz.z, 1, 1, 2, z);
    VU0_LSV(sqc2, 1, 0x0, a0);
    VU0_NOP();
}

