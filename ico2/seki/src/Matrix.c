#include "typedef.h"
#include "tableSin.h"
#include "debug_exception.h"
#include <assert.h>

/* Quadword copy of 64 bytes, parallel form: four lq into four distinct
   scratch GPRs, then four sq.  Only this file has it, so it is defined here
   rather than in ../common/include/typedef.h with the wrappers other trees
   share. */
#define QCOPY64_PARALLEL(s0, s1, s2, s3) /* derived name */                                        \
    __asm__ __volatile__("lq " s0 ", 0($5)" : : : "memory");                                       \
    __asm__ __volatile__("lq " s1 ", 0x10($5)" : : : "memory");                                    \
    __asm__ __volatile__("lq " s2 ", 0x20($5)" : : : "memory");                                    \
    __asm__ __volatile__("lq " s3 ", 0x30($5)" : : : "memory");                                    \
    __asm__ __volatile__("sq " s0 ", 0($4)" : : : "memory");                                       \
    __asm__ __volatile__("sq " s1 ", 0x10($4)" : : : "memory");                                    \
    __asm__ __volatile__("sq " s2 ", 0x20($4)" : : : "memory");                                    \
    __asm__ __volatile__("sq " s3 ", 0x30($4)" : : : "memory")

/* the scratch matrix _ScaleMatrixV fills in and multiplies through */
static float scaleWorkMatrix[4][4] = {{1.0f, 0.0f, 0.0f, 0.0f},
                                      {0.0f, 1.0f, 0.0f, 0.0f},
                                      {0.0f, 0.0f, 1.0f, 0.0f},
                                      {0.0f, 0.0f, 0.0f, 1.0f}}; /* derived name */

#include "Matrix.h"
#include "include_asm.h"

inline void _RotTransCurrentMatrix(void *dst, void *src)
{
    VU0_LSV(lqc2, 8, 0x0, 5);
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
    VU0_LSV(sqc2, 10, 0x0, 4);
    VU0_QMFC2_NI(7, 16);
    VU0_MTC1(7, 0);
    VU0_V2OP(vmove.xy, 12, 11);
    VU0_V2OP(vmove.xy, 11, 10);
}

/* 32 quadwords, the size of the VU0 register file the push and pop save;
   nothing addresses it (the saves go to VU0 memory through vi15). */
static float vu0RegisterSave[32][4] = {{0.0f}}; /* derived name */

/* the VU0 register save depth the push and pop check */
static int vu0PushDepth = 0; /* derived name */

INCLUDE_ASM(_RemakeNormal);

inline void _MakeLightColorMatrix(void *dst, void *s0, void *s1, void *s2, void *s3)
{
    __asm__ __volatile__("lq $6, 0(%1)\n\t"
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

inline void _InitRandom(float seed)
{
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(6, 12);
    VU0_QMTC2_NI(6, 1);
    VU0_NOREORDER_END();
    VU0_V3OP_BC(vaddw.x, 2, 1, 0, w);
    VU0_V3OP(vadd.x, 1, 1, 1);
    VU0_REG("vrinit R, $vf2x");
    VU0_REG("vrxor R, $vf1x");
}

inline float _GetRandom(void)
{
    float ret;
    __asm__ __volatile__(".set noreorder\n"
                         "vrnext.x $vf1, R\n"
                         "vsubw.x $vf1, $vf1, $vf0w\n"
                         "qmfc2.ni $7, $vf1\n"
                         "mtc1 $7, %0\n"
                         ".set reorder\n"
                         : "=f"(ret)::"$7");
    return ret;
}

inline void _GetRandomVector(void *dst)
{
    VU0_REG("vrnext.x $vf1, R");
    VU0_REG("vrnext.y $vf1, R");
    VU0_REG("vrnext.z $vf1, R");
    VU0_V3OP_BC(vsubw.xyz, 1, 1, 0, w);
    VU0_LSV(sqc2, 1, 0x0, 4);
}

inline void _GetRandomVector0(void *dst)
{
    VU0_REG("vrnext.xyz $vf1, R");
    VU0_V3OP_BC(vsubw.xyz, 1, 1, 0, w);
    VU0_LSV(sqc2, 1, 0x0, 4);
}

static inline void _MakeNormal3(void *dst, void *verts, int i0, int i1, int i2) /* derived name */
{
    char *v0 = (char *)((i0 << 4) + (int)verts);
    char *v1 = (char *)((i1 << 4) + (int)verts);
    char *v2 = (char *)((i2 << 4) + (int)verts);
    VU0_LSV_R(lqc2, 10, 0x0, v0);
    VU0_LSV_R(lqc2, 11, 0x0, v1);
    VU0_LSV_R(lqc2, 12, 0x0, v2);
    VU0_V3OP(vsub.w, 26, 0, 0);
    VU0_V3OP(vsub.xyz, 11, 11, 10);
    VU0_V3OP(vsub.xyz, 12, 12, 10);
    VU0_V3OP(vmul.xyz, 16, 11, 11);
    VU0_V3OP_BC(vaddz.x, 16, 16, 16, z);
    VU0_V3OP_BC(vaddy.x, 16, 16, 16, y);
    VU0_REG("vrsqrt Q, $vf0w, $vf16x");
    VU0_V3OP(vmul.xyz, 17, 12, 12);
    VU0_V3OP_BC(vaddz.x, 17, 17, 17, z);
    VU0_V3OP_BC(vaddy.x, 17, 17, 17, y);
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf21, $vf11, Q");
    VU0_REG("vnop");
    VU0_REG("vnop");
    VU0_REG("vrsqrt Q, $vf0w, $vf17x");
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf22, $vf12, Q");
    VU0_V3OP_ACC(vopmula.xyz, 21, 22);
    VU0_V3OP(vopmsub.xyz, 26, 22, 21);
    VU0_LSV_R(sqc2, 26, 0x0, dst);
}

static inline void _MakeNormal4(void *dst, void *verts, int i0, int i1, int i2,
                                int i3) /* derived name */
{
    float k;
    char *v0 = (char *)((i0 << 4) + (int)verts);
    char *v1 = (char *)((i1 << 4) + (int)verts);
    char *v2 = (char *)((i2 << 4) + (int)verts);
    char *v3 = (char *)((i3 << 4) + (int)verts);
    k = 0.5f;
    VU0_LSV_R(lqc2, 10, 0x0, v0);
    VU0_LSV_R(lqc2, 11, 0x0, v1);
    VU0_LSV_R(lqc2, 12, 0x0, v2);
    VU0_LSV_R(lqc2, 13, 0x0, v3);
    VU0_V3OP(vsub.xyz, 11, 11, 10);
    VU0_V3OP(vsub.xyz, 12, 12, 10);
    VU0_V3OP(vsub.xyz, 13, 13, 10);
    VU0_V3OP(vmul.xyz, 16, 11, 11);
    VU0_V3OP_BC(vaddz.x, 16, 16, 16, z);
    VU0_V3OP_BC(vaddy.x, 16, 16, 16, y);
    VU0_REG("vrsqrt Q, $vf0w, $vf16x");
    VU0_V3OP(vmul.xyz, 17, 12, 12);
    VU0_V3OP_BC(vaddz.x, 17, 17, 17, z);
    VU0_V3OP_BC(vaddy.x, 17, 17, 17, y);
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf21, $vf11, Q");
    VU0_REG("vnop");
    VU0_REG("vnop");
    VU0_REG("vrsqrt Q, $vf0w, $vf17x");
    VU0_V3OP(vmul.xyz, 18, 13, 13);
    VU0_V3OP_BC(vaddz.x, 18, 18, 18, z);
    VU0_V3OP_BC(vaddy.x, 18, 18, 18, y);
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf22, $vf12, Q");
    VU0_REG("vnop");
    VU0_REG("vnop");
    VU0_REG("vrsqrt Q, $vf0w, $vf18x");
    VU0_NOREORDER_BEGIN();
    __asm__ __volatile__("mfc1 $8, $f3" : : "f"(k) : "$8");
    VU0_QMTC2_NI(8, 2);
    VU0_NOREORDER_END();
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf23, $vf18, Q");
    VU0_V3OP_ACC(vopmula.xyz, 21, 22);
    VU0_V3OP(vopmsub.xyz, 26, 22, 21);
    VU0_V3OP_ACC(vopmula.xyz, 22, 23);
    VU0_V3OP(vopmsub.xyz, 27, 23, 22);
    VU0_V3OP(vsub.w, 30, 0, 0);
    VU0_V3OP(vadd.xyz, 30, 0, 26);
    VU0_V3OP(vadd.xyz, 30, 30, 27);
    VU0_V3OP_BC(vmulx.xyz, 30, 30, 2, x);
    VU0_LSV_R(sqc2, 30, 0x0, dst);
}

static inline void _MakeNormal5(void *dst, void *verts, int i0, int i1, int i2, int i3,
                                int i4) /* derived name */
{
    float k;
    char *v0 = (char *)((i0 << 4) + (int)verts);
    char *v1 = (char *)((i1 << 4) + (int)verts);
    char *v2 = (char *)((i2 << 4) + (int)verts);
    char *v3 = (char *)((i3 << 4) + (int)verts);
    char *v4 = (char *)((i4 << 4) + (int)verts);
    k = 0.25f;
    VU0_LSV_R(lqc2, 10, 0x0, v0);
    VU0_LSV_R(lqc2, 11, 0x0, v1);
    VU0_LSV_R(lqc2, 12, 0x0, v2);
    VU0_LSV_R(lqc2, 13, 0x0, v3);
    VU0_LSV_R(lqc2, 14, 0x0, v4);
    VU0_V3OP(vsub.xyz, 11, 11, 10);
    VU0_V3OP(vsub.xyz, 12, 12, 10);
    VU0_V3OP(vsub.xyz, 13, 13, 10);
    VU0_V3OP(vsub.xyz, 14, 14, 10);
    VU0_V3OP(vmul.xyz, 16, 11, 11);
    VU0_V3OP_BC(vaddz.x, 16, 16, 16, z);
    VU0_V3OP_BC(vaddy.x, 16, 16, 16, y);
    VU0_REG("vrsqrt Q, $vf0w, $vf16x");
    VU0_V3OP(vmul.xyz, 17, 12, 12);
    VU0_V3OP_BC(vaddz.x, 17, 17, 17, z);
    VU0_V3OP_BC(vaddy.x, 17, 17, 17, y);
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf21, $vf11, Q");
    VU0_REG("vnop");
    VU0_REG("vnop");
    VU0_REG("vrsqrt Q, $vf0w, $vf17x");
    VU0_V3OP(vmul.xyz, 18, 13, 13);
    VU0_V3OP_BC(vaddz.x, 18, 18, 18, z);
    VU0_V3OP_BC(vaddy.x, 18, 18, 18, y);
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf22, $vf12, Q");
    VU0_REG("vnop");
    VU0_REG("vnop");
    VU0_REG("vrsqrt Q, $vf0w, $vf18x");
    VU0_V3OP(vmul.xyz, 19, 14, 14);
    VU0_V3OP_BC(vaddz.x, 19, 19, 19, z);
    VU0_V3OP_BC(vaddy.x, 19, 19, 19, y);
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf23, $vf18, Q");
    VU0_REG("vnop");
    VU0_REG("vnop");
    VU0_REG("vrsqrt Q, $vf0w, $vf19x");
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf24, $vf19, Q");
    VU0_V3OP_ACC(vopmula.xyz, 21, 22);
    VU0_V3OP(vopmsub.xyz, 26, 22, 21);
    VU0_V3OP_ACC(vopmula.xyz, 22, 23);
    VU0_V3OP(vopmsub.xyz, 27, 23, 22);
    VU0_V3OP_ACC(vopmula.xyz, 23, 24);
    VU0_V3OP(vopmsub.xyz, 28, 24, 23);
    VU0_V3OP_ACC(vopmula.xyz, 24, 21);
    VU0_V3OP(vopmsub.xyz, 29, 21, 24);
    VU0_V3OP(vsub.w, 30, 0, 0);
    VU0_V3OP(vadd.xyz, 30, 0, 26);
    __asm__ __volatile__("mfc1 $8, $f4" : : "f"(k) : "$8");
    VU0_V3OP(vadd.xyz, 30, 30, 27);
    VU0_QMTC2_NI(8, 2);
    VU0_V3OP(vadd.xyz, 30, 30, 28);
    VU0_V3OP(vadd.xyz, 30, 30, 29);
    VU0_V3OP_BC(vmulx.xyz, 30, 30, 2, x);
    VU0_LSV_R(sqc2, 30, 0x0, dst);
}

INCLUDE_ASM(_Sqrt);

INCLUDE_ASM(_InitCurrentMatrix);

INCLUDE_ASM(_UnitCurrentMatrix);

INCLUDE_ASM(_PushCurrentMatrix);

INCLUDE_ASM(_PopCurrentMatrix);

INCLUDE_ASM(_TransCurrentMatrix);

INCLUDE_ASM(_SetTransCurrentMatrix);

INCLUDE_ASM(_ClearTransCurrentMatrix);

INCLUDE_ASM(_RotCurrentMatrixX);

INCLUDE_ASM(_RotCurrentMatrixY);

INCLUDE_ASM(_RotCurrentMatrixZ);

INCLUDE_ASM(_ScaleCurrentMatrix);

INCLUDE_ASM(_GetCurrentMatrix);

INCLUDE_ASM(_GetCurrentMatrixTrans);

INCLUDE_ASM(_SetCurrentMatrix);

INCLUDE_ASM(_MulCurrentMatrixR);

INCLUDE_ASM(_MulCurrentMatrixL);

INCLUDE_ASM(_ApplyCurrentMatrix);

INCLUDE_ASM(_RotTransPersCurrentMatrix);

INCLUDE_ASM(_TransposeCurrentMatrix);

INCLUDE_ASM(_TransposeRotationCurrentMatrix);

INCLUDE_ASM(_InverseCurrentMatrix);

INCLUDE_ASM(_PushVu0Registers);

INCLUDE_ASM(_PopVu0Registers);

INCLUDE_ASM(_NormalizeVector);

INCLUDE_ASM(_InnerProduct);

INCLUDE_ASM(_OuterProduct);

INCLUDE_ASM(_AddVector);

INCLUDE_ASM(_AddVectorXYZ);

INCLUDE_ASM(_SubVector);

INCLUDE_ASM(_SubVectorXYZ);

INCLUDE_ASM(_ScaleVector);

INCLUDE_ASM(_ScaleVectorXYZ);

INCLUDE_ASM(_ScaleVector2XYZ);

INCLUDE_ASM(_FTOI4Vector);

INCLUDE_ASM(_FTOI0Vector);

INCLUDE_ASM(_CopyVector);

INCLUDE_ASM(_CopyIVector);

INCLUDE_ASM(_UnitVector);

INCLUDE_ASM(_InterVector);

INCLUDE_ASM(_InterVectorXYZ);

INCLUDE_ASM(_GetNorm);

INCLUDE_ASM(_GetLength);

INCLUDE_ASM(_GetLengthXY);

INCLUDE_ASM(_GetLengthXZ);

INCLUDE_ASM(_CopyMatrix);

INCLUDE_ASM(_MulMatrix);

INCLUDE_ASM(_ApplyMatrix);

INCLUDE_ASM(_UnitMatrix);

INCLUDE_ASM(_UnitRotation);

INCLUDE_ASM(_TransposeMatrix);

INCLUDE_ASM(_InversMatrix);

INCLUDE_ASM(_ScaleMatrixV);

INCLUDE_ASM(_SetCameraMatrix);

INCLUDE_ASM(_MakeNormalLightMatrix);
