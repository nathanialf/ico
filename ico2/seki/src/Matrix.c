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

/* PAL's two 32-quadword VU0 register save areas, which nothing addresses
   (the saves go to VU0 memory through vi15), are not in this build: the
   object has no .bss. */

/* the VU0 register save depth the push and pop check */
static int vu0PushDepth = 0; /* derived name */

INCLUDE_ASM(_RemakeNormal);

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

INCLUDE_ASM(_MakeLightColorMatrix);

INCLUDE_ASM(_InitRandom);

INCLUDE_ASM(_GetRandom);

INCLUDE_ASM(_GetRandomVector);

INCLUDE_ASM(_GetRandomVector0);

INCLUDE_ASM(_RotTransCurrentMatrix);
