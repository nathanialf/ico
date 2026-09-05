#include "common.h"

#include "vu0.h"

#include "r5900.h"

extern float GetTableCos(short a0);
extern float GetTableSin(int x);
extern float D_002908E0[4][4];
/* prototypes: their order is the inline tail's emission order */
void _Sqrt(void *p0, void *p1, void *p2, void *p3, void *p4, void *p5);
void _InitCurrentMatrix(void);
void _UnitCurrentMatrix(void);
void _PushCurrentMatrix(void);
void _PopCurrentMatrix(void);
void _TransCurrentMatrix(void *p0);
void _SetTransCurrentMatrix(void *p0);
void _ClearTransCurrentMatrix(void);
void _RotCurrentMatrixX(short a0);
void _RotCurrentMatrixY(short a0);
void _RotCurrentMatrixZ(short a0);
void _ScaleCurrentMatrix(float a0, float a1, float a2);
void _GetCurrentMatrix(void *p0);
void _GetCurrentMatrixTrans(void *p0);
void _SetCurrentMatrix(void *p0);
void _MulCurrentMatrixR(void *a0);
void _MulCurrentMatrixL(void *m);
void _ApplyCurrentMatrix(void *p0, void *p1, void *p2);
void _RotTransPersCurrentMatrix(void *p0, void *p1, void *p2);
void _TransposeCurrentMatrix(void);
void _TransposeRotationCurrentMatrix(void);
void _InverseCurrentMatrix(void);
void _NormalizeVector(void *p0, void *p1, void *p2);
void _InnerProduct(void *p0, void *p1, void *p2);
void _OuterProduct(void *p0, void *p1, void *p2, void *p3);
void _AddVector(void *p0, void *p1, void *p2, void *p3);
void _AddVectorXYZ(void *p0, void *p1, void *p2, void *p3);
void _SubVector(void *p0, void *p1, void *p2, void *p3);
void _SubVectorXYZ(void *p0, void *p1, void *p2, void *p3);
void _ScaleVector(void *p0, void *p1, void *p2);
void _ScaleVectorXYZ(void *p0, void *p1, void *p2);
void _ScaleVector2XYZ(void *p0, void *p1, void *p2, void *p3);
void _FTOI4Vector(void *p0, void *p1, void *p2);
void _FTOI0Vector(void *p0, void *p1, void *p2);
void _CopyVector(void *dst, void *src);
void _CopyIVector(void *dst, void *src);
void _UnitVector(void *p0);
void _InterVector(void *p0, void *p1, void *p2, void *p3);
void _InterVectorXYZ(void *p0, void *p1, void *p2, void *p3);
void _GetNorm(void *p0);
void _GetLength(void *p0, void *p1, void *p2);
void _GetLengthXY(void *p0, void *p1, void *p2);
void _GetLengthXZ(void *p0, void *p1, void *p2);
void _CopyMatrix(void *dst, void *src);
void _MulMatrix(void *p0, void *p1, void *p2);
void _ApplyMatrix(void *p0, void *p1, void *p2, void *p3);
void _UnitMatrix(void *p0);
void _UnitRotation(void *p0);
void _TransposeMatrix(void *dst, void *src);
void _InversMatrix(void *dst, void *src);
void _ScaleMatrixV(void *dst, void *src, void *v);
void _SetCameraMatrix(void *dst, void *pos, void *dir, void *up);
void _MakeNormalLightMatrix(void *dst, void *s0, void *s1, void *s2);
void _MakeLightColorMatrix(void *dst, void *s0, void *s1, void *s2, void *s3);
void _InitRandom(void *p0, void *p1, void *p2, void *p3);
float _GetRandom(void);
void _GetRandomVector(void *p0);
void _GetRandomVector0(void *p0);
void _RotTransCurrentMatrix(void *p0, void *p1);
inline void _InitCurrentMatrix(void)
{
    VU0_V2OP(vmove.xyzw, 7, 0);
    VU0_V2OP(vmr32.xyzw, 6, 7);
    VU0_V2OP(vmr32.xyzw, 5, 6);
    VU0_V2OP(vmr32.xyzw, 4, 5);
    VU0_REG("viaddi $vi15, $vi0, 0x0");
}
inline void _UnitCurrentMatrix(void)
{
    VU0_V2OP(vmove.xyzw, 7, 0);
    VU0_V2OP(vmr32.xyzw, 6, 7);
    VU0_V2OP(vmr32.xyzw, 5, 6);
    VU0_V2OP(vmr32.xyzw, 4, 5);
    VU0_REG("viaddi $vi15, $vi0, 0x0");
}
inline void _PushCurrentMatrix(void)
{
    VU0_REG("vsqi.xyzw $vf4, ($vi15++)");
    VU0_REG("vsqi.xyzw $vf5, ($vi15++)");
    VU0_REG("vsqi.xyzw $vf6, ($vi15++)");
    VU0_REG("vsqi.xyzw $vf7, ($vi15++)");
}
inline void _PopCurrentMatrix(void)
{
    VU0_REG("vlqd.xyzw $vf7, (--$vi15)");
    VU0_REG("vlqd.xyzw $vf6, (--$vi15)");
    VU0_REG("vlqd.xyzw $vf5, (--$vi15)");
    VU0_REG("vlqd.xyzw $vf4, (--$vi15)");
}
inline void _TransCurrentMatrix(void *p0)
{
    VU0_LSV(lqc2, 8, 0x0, a0);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 8, z);
    VU0_V3OP_BC(vmaddw.xyzw, 7, 7, 8, w);
}
inline void _SetTransCurrentMatrix(void *p0)
{
    VU0_LSV(lqc2, 8, 0x0, a0);
    VU0_V2OP(vmove.xyzw, 7, 8);
}
inline void _ClearTransCurrentMatrix(void)
{
    VU0_V2OP(vmove.xyzw, 7, 0);
}
inline void _RotCurrentMatrixX(short a0)
{
    float c = GetTableCos(a0);
    float s = GetTableSin(a0);
    __asm__ __volatile__("mfc1 $8, %0" : : "f"(c) : "$8");
    __asm__ __volatile__("mfc1 $9, %0" : : "f"(s) : "$9");
    VU0_QMTC2_NI(8, 1);
    VU0_QMTC2_NI(9, 2);
    VU0_V2OP(vmove.xyzw, 17, 0);
    VU0_V2OP(vmr32.xyzw, 16, 17);
    VU0_V2OP(vmr32.xyzw, 15, 16);
    VU0_V2OP(vmr32.xyzw, 14, 15);
    VU0_V3OP_BC(vaddx.y, 15, 0, 1, x);
    VU0_V3OP_BC(vsubx.y, 16, 0, 2, x);
    VU0_V3OP_BC(vaddx.z, 15, 0, 2, x);
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
inline void _RotCurrentMatrixY(short a0)
{
    float c = GetTableCos(a0);
    float s = GetTableSin(a0);
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
inline void _RotCurrentMatrixZ(short a0)
{
    float c = GetTableCos(a0);
    float s = GetTableSin(a0);
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
inline void _ScaleCurrentMatrix(float a0, float a1, float a2)
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
}
inline void _GetCurrentMatrix(void *p0)
{
    VU0_LSV(sqc2, 4, 0x0, a0);
    VU0_LSV(sqc2, 5, 0x10, a0);
    VU0_LSV(sqc2, 6, 0x20, a0);
    VU0_LSV(sqc2, 7, 0x30, a0);
}
inline void _GetCurrentMatrixTrans(void *p0)
{
    VU0_LSV(sqc2, 7, 0x0, a0);
}
inline void _SetCurrentMatrix(void *p0)
{
    VU0_LSV(lqc2, 4, 0x0, a0);
    VU0_LSV(lqc2, 5, 0x10, a0);
    VU0_LSV(lqc2, 6, 0x20, a0);
    VU0_LSV(lqc2, 7, 0x30, a0);
}
inline void _MulCurrentMatrixR(void *a0)
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
}
inline void _MulCurrentMatrixL(void *m)
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
}
inline void _ApplyCurrentMatrix(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 8, 0x0, a1);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 8, z);
    VU0_V3OP_BC(vmaddw.xyzw, 10, 7, 8, w);
    VU0_LSV(sqc2, 10, 0x0, a0);
}
inline void _RotTransPersCurrentMatrix(void *p0, void *p1, void *p2)
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
}
inline void _RotTransCurrentMatrix(void *p0, void *p1)
{
    VU0_LSV(lqc2, 8, 0x0, a1);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 8, z);
    VU0_V3OP_BC(vmaddw.xyzw, 10, 7, 8, w);
    VU0_REG("vdiv Q, $vf0w, $vf10w");
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf10, $vf10, Q");
    VU0_V2OP(vftoi4.xyz, 10, 10);
    VU0_V3OP(vsub.xy, 14, 10, 11);
    VU0_V3OP(vsub.xy, 15, 12, 11);
    VU0_V3OP(vsub.zw, 14, 14, 14);
    VU0_V3OP(vsub.zw, 15, 15, 15);
    VU0_V3OP_ACC(vopmula.xyz, 14, 15);
    VU0_V3OP(vopmsub.xyz, 16, 15, 14);
    VU0_V2OP(vmr32.y, 16, 16);
    VU0_V2OP(vmr32.x, 16, 16);
    VU0_LSV(sqc2, 10, 0x0, a0);
    VU0_QMFC2_NI(a3, 16);
    VU0_MTC1(a3, 0);
    VU0_V2OP(vmove.xy, 12, 11);
    VU0_V2OP(vmove.xy, 11, 10);
}
inline void _TransposeCurrentMatrix(void)
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
}
inline void _TransposeRotationCurrentMatrix(void)
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
}
inline void _InverseCurrentMatrix(void)
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
}
INCLUDE_ASM("asm/nonmatchings/src/Matrix", _PushVu0Registers);
INCLUDE_ASM("asm/nonmatchings/src/Matrix", _PopVu0Registers);
inline void _NormalizeVector(void *p0, void *p1, void *p2)
{
    __asm__ __volatile__(
        "lqc2 $vf1, 0x0(%1)\n\t"
        "vmul.xyz $vf3, $vf1, $vf1\n\t"
        "vmulax.w ACC, $vf0, $vf3x\n\t"
        "vmadday.w ACC, $vf0, $vf3y\n\t"
        "vmaddz.w $vf3, $vf0, $vf3z\n\t"
        "vrsqrt Q, $vf0w, $vf3w\n\t"
        "vwaitq\n\t"
        "vmulq.xyz $vf1, $vf1, Q\n\t"
        "sqc2 $vf1, 0x0(%0)"
        :
        : "r"(p0), "r"(p1)
        : "memory");
}
inline void _InnerProduct(void *p0, void *p1, void *p2)
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
}
inline void _OuterProduct(void *p0, void *p1, void *p2, void *p3)
{
    __asm__ __volatile__(
        "lqc2 $vf1, 0x0(%1)\n\t"
        "lqc2 $vf2, 0x0(%2)\n\t"
        "vopmula.xyz ACC, $vf1, $vf2\n\t"
        "vopmsub.xyz $vf3, $vf2, $vf1\n\t"
        "vsub.w $vf3, $vf3, $vf3\n\t"
        "sqc2 $vf3, 0x0(%0)"
        :
        : "r"(p0), "r"(p1), "r"(p2)
        : "memory");
}
inline void _AddVector(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP(vadd.xyzw, 3, 1, 2);
    VU0_LSV(sqc2, 3, 0x0, a0);
}
inline void _AddVectorXYZ(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP(vadd.xyz, 1, 1, 2);
    VU0_LSV(sqc2, 1, 0x0, a0);
}
inline void _SubVector(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP(vsub.xyzw, 3, 1, 2);
    VU0_LSV(sqc2, 3, 0x0, a0);
}
inline void _SubVectorXYZ(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP(vsub.xyz, 1, 1, 2);
    VU0_LSV(sqc2, 1, 0x0, a0);
}
inline void _ScaleVector(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 2);
    VU0_NOREORDER_END();
    VU0_V3OP_BC(vmulx.xyzw, 3, 1, 2, x);
    VU0_LSV(sqc2, 3, 0x0, a0);
}
inline void _ScaleVectorXYZ(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 2);
    VU0_NOREORDER_END();
    VU0_V3OP_BC(vmulx.xyz, 1, 1, 2, x);
    VU0_LSV(sqc2, 1, 0x0, a0);
}
inline void _ScaleVector2XYZ(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP_BC(vmulx.x, 1, 1, 2, x);
    VU0_V3OP_BC(vmuly.y, 1, 1, 2, y);
    VU0_V3OP_BC(vmulz.z, 1, 1, 2, z);
    VU0_LSV(sqc2, 1, 0x0, a0);
}
inline void _FTOI4Vector(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_V2OP(vftoi4.xyzw, 2, 1);
    VU0_LSV(sqc2, 2, 0x0, a0);
}
inline void _FTOI0Vector(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_V2OP(vftoi0.xyzw, 2, 1);
    VU0_LSV(sqc2, 2, 0x0, a0);
}
inline void _CopyVector(void *dst, void *src)
{
    __asm__ __volatile__(
        "lq $t0, 0x0(%1)\n\t"
        "sq $t0, 0x0(%0)"
        :
        : "r"(dst), "r"(src)
        : "$8", "memory");
}
inline void _CopyIVector(void *dst, void *src)
{
    QCOPY16("$t0");
}
inline void _UnitVector(void *p0)
{
    VU0_LSV(sqc2, 0, 0x0, a0);
}
inline void _InterVector(void *p0, void *p1, void *p2, void *p3)
{
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 3);
    VU0_NOREORDER_END();
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP_BC(vsubx.w, 8, 0, 3, x);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 1, 3, x);
    VU0_V3OP_BC(vmaddw.xyzw, 9, 2, 8, w);
    VU0_LSV(sqc2, 9, 0x0, a0);
}
inline void _InterVectorXYZ(void *p0, void *p1, void *p2, void *p3)
{
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 3);
    VU0_NOREORDER_END();
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP_BC(vsubx.w, 8, 0, 3, x);
    VU0_V3OP_ACC_BC(vmulax.xyz, 1, 3, x);
    VU0_V3OP_BC(vmaddw.xyz, 1, 2, 8, w);
    VU0_LSV(sqc2, 1, 0x0, a0);
}
inline void _GetNorm(void *p0)
{
    VU0_LSV(lqc2, 3, 0x0, a0);
    VU0_V3OP(vmul.xyz, 3, 3, 3);
    VU0_V3OP_ACC_BC(vmulax.w, 0, 3, x);
    VU0_V3OP_ACC_BC(vmadday.w, 0, 3, y);
    VU0_V3OP_BC(vmaddz.w, 3, 0, 3, z);
    VU0_WORD(0x4B8303BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}
inline void _GetLength(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 1, 0x0, a0);
    VU0_LSV(lqc2, 2, 0x0, a1);
    VU0_V3OP(vsub.xyzw, 3, 1, 2);
    VU0_V3OP(vmul.xyz, 3, 3, 3);
    VU0_V3OP_ACC_BC(vmulax.w, 0, 3, x);
    VU0_V3OP_ACC_BC(vmadday.w, 0, 3, y);
    VU0_V3OP_BC(vmaddz.w, 3, 0, 3, z);
    VU0_WORD(0x4B8303BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}
inline void _GetLengthXY(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 1, 0x0, a0);
    VU0_LSV(lqc2, 2, 0x0, a1);
    VU0_V3OP(vsub.xyzw, 3, 1, 2);
    VU0_V3OP(vmul.xy, 3, 3, 3);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_WORD(0x4A0303BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}
inline void _GetLengthXZ(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 1, 0x0, a0);
    VU0_LSV(lqc2, 2, 0x0, a1);
    VU0_V3OP(vsub.xyzw, 3, 1, 2);
    VU0_V3OP(vmul.xz, 3, 3, 3);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_WORD(0x4A0303BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}
inline void _CopyMatrix(void *dst, void *src)
{
    QCOPY64_PARALLEL("$a2", "$a3", "$t0", "$t1");
}
inline void _MulMatrix(void *p0, void *p1, void *p2)
{
    __asm__ __volatile__(
        "lqc2 $vf14, 0x0(%1)\n\t"
        "lqc2 $vf15, 0x10(%1)\n\t"
        "lqc2 $vf16, 0x20(%1)\n\t"
        "lqc2 $vf17, 0x30(%1)\n\t"
        "lqc2 $vf24, 0x0(%2)\n\t"
        "lqc2 $vf25, 0x10(%2)\n\t"
        "lqc2 $vf26, 0x20(%2)\n\t"
        "lqc2 $vf27, 0x30(%2)\n\t"
        "vmulax.xyzw ACC, $vf14, $vf24x\n\t"
        "vmadday.xyzw ACC, $vf15, $vf24y\n\t"
        "vmaddaz.xyzw ACC, $vf16, $vf24z\n\t"
        "vmaddw.xyzw $vf24, $vf17, $vf24w\n\t"
        "vmulax.xyzw ACC, $vf14, $vf25x\n\t"
        "vmadday.xyzw ACC, $vf15, $vf25y\n\t"
        "vmaddaz.xyzw ACC, $vf16, $vf25z\n\t"
        "vmaddw.xyzw $vf25, $vf17, $vf25w\n\t"
        "vmulax.xyzw ACC, $vf14, $vf26x\n\t"
        "vmadday.xyzw ACC, $vf15, $vf26y\n\t"
        "vmaddaz.xyzw ACC, $vf16, $vf26z\n\t"
        "vmaddw.xyzw $vf26, $vf17, $vf26w\n\t"
        "vmulax.xyzw ACC, $vf14, $vf27x\n\t"
        "vmadday.xyzw ACC, $vf15, $vf27y\n\t"
        "vmaddaz.xyzw ACC, $vf16, $vf27z\n\t"
        "vmaddw.xyzw $vf27, $vf17, $vf27w\n\t"
        "sqc2 $vf24, 0x0(%0)\n\t"
        "sqc2 $vf25, 0x10(%0)\n\t"
        "sqc2 $vf26, 0x20(%0)\n\t"
        "sqc2 $vf27, 0x30(%0)\n\t"
        "nop"
        :
        : "r"(p0), "r"(p1), "r"(p2)
        : "memory");
}
inline void _ApplyMatrix(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 8, 0x0, a2);
    VU0_LSV(lqc2, 14, 0x0, a1);
    VU0_LSV(lqc2, 15, 0x10, a1);
    VU0_LSV(lqc2, 16, 0x20, a1);
    VU0_LSV(lqc2, 17, 0x30, a1);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 14, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 15, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 16, 8, z);
    VU0_V3OP_BC(vmaddw.xyzw, 10, 17, 8, w);
    VU0_LSV(sqc2, 10, 0x0, a0);
}
inline void _UnitMatrix(void *p0)
{
    __asm__ __volatile__(
        "vmove.xyzw $vf17, $vf0\n\t"
        "vmr32.xyzw $vf16, $vf17\n\t"
        "vmr32.xyzw $vf15, $vf16\n\t"
        "vmr32.xyzw $vf14, $vf15\n\t"
        "sqc2 $vf14, 0x0(%0)\n\t"
        "sqc2 $vf15, 0x10(%0)\n\t"
        "sqc2 $vf16, 0x20(%0)\n\t"
        "sqc2 $vf17, 0x30(%0)"
        :
        : "r"(p0)
        : "memory");
}
inline void _UnitRotation(void *p0)
{
    VU0_V2OP(vmove.xyzw, 17, 0);
    VU0_V2OP(vmr32.xyzw, 16, 17);
    VU0_V2OP(vmr32.xyzw, 15, 16);
    VU0_V2OP(vmr32.xyzw, 14, 15);
    VU0_LSV(sqc2, 14, 0x0, a0);
    VU0_LSV(sqc2, 15, 0x10, a0);
    VU0_LSV(sqc2, 16, 0x20, a0);
}
inline void _ScaleMatrixV(void *dst, void *src, void *v)
{
    float *m = &D_002908E0[0][0];

    m[0] = ((float *)v)[0];
    m[5] = ((float *)v)[1];
    m[10] = ((float *)v)[2];
    _MulMatrix(dst, src, m);
}
inline void _TransposeMatrix(void *dst, void *src)
{
    __asm__ __volatile__("lq $t0, 0x0($a1)"  : : : "memory");
    __asm__ __volatile__("lq $t1, 0x10($a1)" : : : "memory");
    __asm__ __volatile__("lq $t2, 0x20($a1)" : : : "memory");
    __asm__ __volatile__("lq $t3, 0x30($a1)" : : : "memory");
    __asm__ __volatile__("pextlw $t4, $t1, $t0");
    __asm__ __volatile__("pextuw $t5, $t1, $t0");
    __asm__ __volatile__("pextlw $t6, $t3, $t2");
    __asm__ __volatile__("pextuw $t7, $t3, $t2");
    __asm__ __volatile__("pcpyld $t0, $t6, $t4");
    __asm__ __volatile__("pcpyud $t1, $t4, $t6");
    __asm__ __volatile__("pcpyld $t2, $t7, $t5");
    __asm__ __volatile__("pcpyud $t3, $t5, $t7");
    __asm__ __volatile__("sq $t0, 0x0($a0)"  : : : "memory");
    __asm__ __volatile__("sq $t1, 0x10($a0)" : : : "memory");
    __asm__ __volatile__("sq $t2, 0x20($a0)" : : : "memory");
    __asm__ __volatile__("sq $t3, 0x30($a0)" : : : "memory");
}
inline void _InversMatrix(void *dst, void *src)
{
    __asm__ __volatile__(
        "lq $t0, 0x0(%1)\n\t"
        "lq $t1, 0x10(%1)\n\t"
        "lq $t2, 0x20(%1)\n\t"
        "lqc2 $vf4, 0x30(%1)\n\t"
        "vmove.xyzw $vf5, $vf4\n\t"
        "vsub.xyz $vf4, $vf4, $vf4\n\t"
        "vmove.xyzw $vf9, $vf4\n\t"
        "qmfc2.ni $t3, $vf4\n\t"
        "pextlw $t4, $t1, $t0\n\t"
        "pextuw $t5, $t1, $t0\n\t"
        "pextlw $t6, $t3, $t2\n\t"
        "pextuw $t7, $t3, $t2\n\t"
        "pcpyld $t0, $t6, $t4\n\t"
        "pcpyud $t1, $t4, $t6\n\t"
        "pcpyld $t2, $t7, $t5\n\t"
        "qmtc2.ni $t0, $vf6\n\t"
        "qmtc2.ni $t1, $vf7\n\t"
        "qmtc2.ni $t2, $vf8\n\t"
        "vmulax.xyz ACC, $vf6, $vf5x\n\t"
        "vmadday.xyz ACC, $vf7, $vf5y\n\t"
        "vmaddz.xyz $vf4, $vf8, $vf5z\n\t"
        "vsub.xyz $vf4, $vf9, $vf4\n\t"
        "sq $t0, 0x0(%0)\n\t"
        "sq $t1, 0x10(%0)\n\t"
        "sq $t2, 0x20(%0)\n\t"
        "sqc2 $vf4, 0x30(%0)"
        :
        : "r"(dst), "r"(src)
        : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}
inline void _SetCameraMatrix(void *dst, void *pos, void *dir, void *up)
{
    float m[4][4];
    float t[4];

    _UnitMatrix(m);
    _OuterProduct(t, up, dir, 0);
    _NormalizeVector(m[0], t, 0);
    _NormalizeVector(m[2], dir, 0);
    _OuterProduct(m[1], m[2], m[0], 0);
    _CopyVector(m[3], pos);
    _InversMatrix(dst, m);
}

inline void _Sqrt(void *p0, void *p1, void *p2, void *p3, void *p4, void *p5)
{
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(a2, 12);
    VU0_QMTC2_NI(a2, 1);
    VU0_NOREORDER_END();
    VU0_WORD(0x4A0103BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(a3, 22);
    VU0_MTC1(a3, 0);
    VU0_NOREORDER_END();
}
inline void _MakeNormalLightMatrix(void *dst, void *s0, void *s1, void *s2)
{
    __asm__ __volatile__(
        "vsubw.x $vf1, $vf0, $vf0w\n\t"
        "lqc2 $vf24, 0(%1)\n\t"
        "lqc2 $vf25, 0(%2)\n\t"
        "lqc2 $vf26, 0(%3)\n\t"
        "vmulx.xyz $vf24, $vf24, $vf1x\n\t"
        "vmulx.xyz $vf25, $vf25, $vf1x\n\t"
        "vmulx.xyz $vf26, $vf26, $vf1x\n\t"
        "vmul.xyz $vf14, $vf24, $vf24\n\t"
        "vaddy.x $vf14, $vf14, $vf14y\n\t"
        "vaddz.x $vf14, $vf14, $vf14z\n\t"
        "vrsqrt Q, $vf0w, $vf14x\n\t"
        "vmul.xyz $vf15, $vf25, $vf25\n\t"
        "vaddy.x $vf15, $vf15, $vf15y\n\t"
        "vaddz.x $vf15, $vf15, $vf15z\n\t"
        "vwaitq\n\t"
        "vmulq.xyz $vf24, $vf24, Q\n\t"
        "vnop\n\t"
        "vnop\n\t"
        "vrsqrt Q, $vf0w, $vf15x\n\t"
        "vmul.xyz $vf16, $vf26, $vf26\n\t"
        "vaddy.x $vf16, $vf16, $vf16y\n\t"
        "vaddz.x $vf16, $vf16, $vf16z\n\t"
        "vwaitq\n\t"
        "vmulq.xyz $vf25, $vf25, Q\n\t"
        "vnop\n\t"
        "vnop\n\t"
        "vrsqrt Q, $vf0w, $vf16x\n\t"
        "vwaitq\n\t"
        "vmulq.xyz $vf26, $vf26, Q\n\t"
        "vmove.xyzw $vf27, $vf0\n\t"
        "vmove.xyzw $vf14, $vf24\n\t"
        "vmove.xyzw $vf15, $vf25\n\t"
        "vmove.xyzw $vf16, $vf26\n\t"
        "vmove.xyzw $vf17, $vf27\n\t"
        "vsub.xyzw $vf1, $vf0, $vf0\n\t"
        "vaddx.y $vf14, $vf1, $vf25x\n\t"
        "vaddx.z $vf14, $vf1, $vf26x\n\t"
        "vaddx.w $vf14, $vf1, $vf27x\n\t"
        "vaddy.x $vf15, $vf1, $vf24y\n\t"
        "vaddy.z $vf15, $vf1, $vf26y\n\t"
        "vaddy.w $vf15, $vf1, $vf27y\n\t"
        "vaddz.x $vf16, $vf1, $vf24z\n\t"
        "vaddz.y $vf16, $vf1, $vf25z\n\t"
        "vaddz.w $vf16, $vf1, $vf27z\n\t"
        "vaddw.x $vf17, $vf1, $vf24w\n\t"
        "vaddw.y $vf17, $vf1, $vf25w\n\t"
        "vaddw.z $vf17, $vf1, $vf26w\n\t"
        "sqc2 $vf14, 0x0(%0)\n\t"
        "sqc2 $vf15, 0x10(%0)\n\t"
        "sqc2 $vf16, 0x20(%0)\n\t"
        "sqc2 $vf17, 0x30(%0)\n\t"
        "nop"
        :
        : "r"(dst), "r"(s0), "r"(s1), "r"(s2)
        : "$6", "$7", "$8", "$9", "memory");
}
inline void _MakeLightColorMatrix(void *dst, void *s0, void *s1, void *s2, void *s3)
{
    __asm__ __volatile__(
        "lq $6, 0(%1)\n\t"
        "lq $7, 0(%2)\n\t"
        "lq $8, 0(%3)\n\t"
        "lq $9, 0(%4)\n\t"
        "sq $6, 0(%0)\n\t"
        "sq $7, 0x10(%0)\n\t"
        "sq $8, 0x20(%0)\n\t"
        "sq $9, 0x30(%0)\n\t"
        "nop"
        :
        : "r"(dst), "r"(s0), "r"(s1), "r"(s2), "r"(s3)
        : "$6", "$7", "$8", "$9", "memory");
}
inline void _InitRandom(void *p0, void *p1, void *p2, void *p3)
{
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(a2, 12);
    VU0_QMTC2_NI(a2, 1);
    VU0_NOREORDER_END();
    VU0_V3OP_BC(vaddw.x, 2, 1, 0, w);
    VU0_V3OP(vadd.x, 1, 1, 1);
    VU0_REG("vrinit R, $vf2x");
    VU0_REG("vrxor R, $vf1x");
}
inline float _GetRandom(void) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "vrnext.x $vf1, R\n"
        "vsubw.x $vf1, $vf1, $vf0w\n"
        "qmfc2.ni $7, $vf1\n"
        "mtc1 $7, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$7");
    return ret;
}
inline void _GetRandomVector(void *p0)
{
    VU0_REG("vrnext.x $vf1, R");
    VU0_REG("vrnext.y $vf1, R");
    VU0_REG("vrnext.z $vf1, R");
    VU0_V3OP_BC(vsubw.xyz, 1, 1, 0, w);
    VU0_LSV(sqc2, 1, 0x0, a0);
}
inline void _GetRandomVector0(void *p0)
{
    VU0_REG("vrnext.xyz $vf1, R");
    VU0_V3OP_BC(vsubw.xyz, 1, 1, 0, w);
    VU0_LSV(sqc2, 1, 0x0, a0);
}
INCLUDE_ASM("asm/nonmatchings/src/Matrix", _RemakeNormal);
