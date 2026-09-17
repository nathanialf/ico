#include "common.h"
#include "typedef.h"
#include "quaternion.h"
#include "tableSin.h"
#include <libvu0.h>

/* Quadword copies this TU alone issues; the wrappers shared with other
   programmers' trees are in ../common/include/typedef.h.  dst/src are
   implicit in $a0/$a1: each macro is the BODY of a two-pointer wrapper. */

/* 64 bytes, serial form: every lq immediately followed by its sq through one
   scratch GPR.  Trailing nop fills the jr-ra delay slot. */
#define QCOPY64_SERIAL(scratch)                                                                    \
    __asm__ __volatile__("lq " scratch ", 0($a1)" : : : "memory");                                 \
    __asm__ __volatile__("sq " scratch ", 0($a0)" : : : "memory");                                 \
    __asm__ __volatile__("lq " scratch ", 0x10($a1)" : : : "memory");                              \
    __asm__ __volatile__("sq " scratch ", 0x10($a0)" : : : "memory");                              \
    __asm__ __volatile__("lq " scratch ", 0x20($a1)" : : : "memory");                              \
    __asm__ __volatile__("sq " scratch ", 0x20($a0)" : : : "memory");                              \
    __asm__ __volatile__("lq " scratch ", 0x30($a1)" : : : "memory");                              \
    __asm__ __volatile__("sq " scratch ", 0x30($a0)" : : : "memory");                              \
    __asm__ __volatile__("nop")
/* Map $a0 into EE scratchpad (SPR) addressing by OR-ing 0x20000000, through
   $a3.  Prelude to QCOPY64_SERIAL in CopyMatrixUncached. */
#define MAP_A0_TO_SPR()                                                                            \
    __asm__ __volatile__("lui $a3, 0x2000");                                                       \
    __asm__ __volatile__("or $a0, $a0, $a3")
/* lq/sq of 16 bytes through $a2, with the base bound from a C pointer. */
#define LQ16_FROM(p) __asm__ __volatile__("lq $a2, 0(%0)" : : "r"(p) : "memory")
#define SQ16_TO(p) __asm__ __volatile__("sq $a2, 0(%0)" : : "r"(p) : "memory")

typedef int Qw128 __attribute__((mode(TI)));

typedef struct {
    char pad[0x30];
    Qw128 q;
} MatDrive;

extern int D_00639F00;

/* .bss, owned by matrixDrive.o and reached only from this file (MAIN.MAP names
   no symbol in the run; its matrixDrive.o .bss size 0x1000 is what fixes the
   length, and geometryManager's 0x100 and quaternion's 0x400 tile the same
   region exactly).  The 64-deep matrix stack; MatrixDrive_GetLastMatrix reads
   one slot below the current one, which is the ROM's second %hi/%lo base. */
static char matrixStack[64 * 64];

void InitMatrixDrive(void)
{
    D_00639F00 = 0;
    sceVu0UnitMatrix(matrixStack);
    InitTableSin();
    InitQuaternionDrive();
}

/* kept local: this TU's uses of CopyMatrix do not fit the prototype in matrixDrive.h */
extern void CopyMatrix(void *dst, void *src);
extern int D_00639F00;

void MatrixDrive_PushMatrix(void)
{
    D_00639F00 += 1;
    CopyMatrix(&matrixStack[D_00639F00 * 0x40], &matrixStack[D_00639F00 * 0x40 - 0x40]);
}

/* matrixDrive.o's .data run, in source order.  The six leading objects are
   the engine-wide constant vectors and the identity matrix; MAIN.MAP names
   them and other objects reach them by name.  The four matrices that follow
   are this file's own scratch templates: each rotate/scale entry point writes
   its varying terms into one of them and multiplies it through. */
float ZeroVector[4] = {0.0f, 0.0f, 0.0f, 0.0f};

float ZeroPoint[4] = {0.0f, 0.0f, 0.0f, 1.0f};

float XUnitVector[4] = {1.0f, 0.0f, 0.0f, 0.0f};

float YUnitVector[4] = {0.0f, 1.0f, 0.0f, 0.0f};

float ZUnitVector[4] = {0.0f, 0.0f, 1.0f, 0.0f};

float InitialMatrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                           0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

/* the scratch matrix MatrixDrive_RotMatrixX fills in and multiplies through */
static float rotXWorkMatrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

void MatrixDrive_RotMatrixX(short a0)
{
    float c = GetTableCos(a0);
    float s = GetTableSin(a0);
    rotXWorkMatrix[10] = c;
    rotXWorkMatrix[9] = -s;
    rotXWorkMatrix[6] = s;
    rotXWorkMatrix[5] = c;
    sceVu0MulMatrix(&matrixStack[D_00639F00 * 0x40], &matrixStack[D_00639F00 * 0x40],
                    (int)rotXWorkMatrix);
}

/* the scratch matrix MatrixDrive_RotMatrixY fills in and multiplies through */
static float rotYWorkMatrix[16] = {1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                                   1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

void MatrixDrive_RotMatrixY(short a0)
{
    float c = GetTableCos(a0);
    float s = GetTableSin(a0);
    rotYWorkMatrix[10] = c;
    rotYWorkMatrix[8] = s;
    rotYWorkMatrix[2] = -s;
    rotYWorkMatrix[0] = c;
    sceVu0MulMatrix(&matrixStack[D_00639F00 * 0x40], &matrixStack[D_00639F00 * 0x40],
                    (int)rotYWorkMatrix);
}

/* the scratch matrix MatrixDrive_RotMatrixZ fills in and multiplies through */
static float rotZWorkMatrix[16] = {1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

void MatrixDrive_RotMatrixZ(short a0)
{
    float c = GetTableCos(a0);
    float s = GetTableSin(a0);
    rotZWorkMatrix[5] = c;
    rotZWorkMatrix[4] = -s;
    rotZWorkMatrix[1] = s;
    rotZWorkMatrix[0] = c;
    sceVu0MulMatrix(&matrixStack[D_00639F00 * 0x40], &matrixStack[D_00639F00 * 0x40],
                    (int)rotZWorkMatrix);
}

/* the scratch matrix MatrixDrive_ScaleMatrix fills in and multiplies through */
static float scaleWorkMatrix[16] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                                    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

void MatrixDrive_ScaleMatrix(float x, float y, float z)
{
    scaleWorkMatrix[0] = x;
    scaleWorkMatrix[5] = y;
    scaleWorkMatrix[10] = z;
    sceVu0MulMatrix(&matrixStack[D_00639F00 * 0x40], &matrixStack[D_00639F00 * 0x40],
                    (int)scaleWorkMatrix);
}

/* kept local: this TU's uses of FSqrt do not fit the prototype in matrixDrive.h */
extern float FSqrt(float a0);

void MatrixDrive_TurnViewMatrix(float x, float y, float z)
{
    float v0[4] = {x, y, z, 1.0f};
    float v1[4] = {x, 0.0f, z, 1.0f};

    sceVu0Normalize(v0, v0);
    sceVu0Normalize(v1, v1);
    {
        float c = v1[2];
        float s = v1[0];
        float m[4][4] = {{c, 0.0f, -s, 0.0f},
                         {0.0f, 1.0f, 0.0f, 0.0f},
                         {s, 0.0f, c, 0.0f},
                         {0.0f, 0.0f, 0.0f, 1.0f}};
        sceVu0MulMatrix(&matrixStack[D_00639F00 * 0x40], (int)m, &matrixStack[D_00639F00 * 0x40]);
    }
    {
        float len = FSqrt(v0[0] * v0[0] + v0[2] * v0[2]);
        float t = v0[1];
        float m[4][4] = {{1.0f, 0.0f, 0.0f, 0.0f},
                         {0.0f, len, t, 0.0f},
                         {0.0f, -t, len, 0.0f},
                         {0.0f, 0.0f, 0.0f, 1.0f}};
        sceVu0MulMatrix(&matrixStack[D_00639F00 * 0x40], (int)m, &matrixStack[D_00639F00 * 0x40]);
    }
}

void MatrixDrive_PushMatrixWithNoCopy(void)
{
    D_00639F00 += 1;
}

void MatrixDrive_PopMatrix(void)
{
    D_00639F00 -= 1;
}

void *MatrixDrive_GetMatrix(void)
{
    return &matrixStack[D_00639F00 * 0x40];
}

void *MatrixDrive_GetLastMatrix(void)
{
    return &matrixStack[D_00639F00 * 0x40 - 0x40];
}

/* kept local: this TU's uses of CopyVector do not fit the prototype in matrixDrive.h */
extern void CopyVector(void *dst, void *src);

void MatrixDrive_TransMatrixV(char *a0)
{
    float buf[4];
    sceVu0ApplyMatrix((int *)buf, &matrixStack[D_00639F00 * 0x40], (int)a0);
    buf[3] = 1.0f;
    CopyVector(&matrixStack[D_00639F00 * 0x40 + 0x30], buf);
}

void MatrixDrive_TransMatrix(float x, float y, float z)
{
    float v[4];
    float buf[4];
    float *m = buf;
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 1.0f;
    sceVu0ApplyMatrix((int *)m, &matrixStack[D_00639F00 * 0x40], (int)v);
    m[3] = 1.0f;
    CopyVector(&matrixStack[D_00639F00 * 0x40 + 0x30], m);
}

/* kept local: this TU's uses of FSqrt do not fit the prototype in matrixDrive.h */
extern float FSqrt(float a0);

/* INTERIM stand-in: MatrixDrive_GetTurnZAngleYX is `inline` in the 2001 source, so its
   out-of-line copy lands in the deferred inline tail BELOW this caller and gcc
   cannot inline it from there. Same body. */
static inline void GetTurnZAngleYX_i(short *a0, short *a1, float x, float y, float z)
{
    float v0[4] = {x, y, -z, 1.0f};
    float v1[4] = {x, 0.0f, -z, 1.0f};
    float len;
    float p;
    float q;
    float yy;

    sceVu0Normalize(v0, v0);
    if (0.01f < FSqrt(x * x + z * z)) {
        sceVu0Normalize(v1, v1);
        p = v1[2];
        q = v1[0];
        *a0 = GetTableArcTan2(-q, -p);
    }
    len = FSqrt(v0[0] * v0[0] + v0[2] * v0[2]);
    yy = v0[1];
    *a1 = -GetTableArcTan2(yy, len);
}

void MatrixDrive_TurnObjectMatrix(float x, float y, float z)
{
    short ay;
    short ax;

    GetTurnZAngleYX_i(&ay, &ax, x, y, z);
    MatrixDrive_RotMatrixY(ay);
    MatrixDrive_RotMatrixX(ax);
}

/* INTERIM stand-in: MatrixDrive_GetTurnXAngleZY is `inline` in the 2001 source,
   so its out-of-line copy lands in the deferred inline tail BELOW this caller and
   gcc cannot inline it from there. This carries the same body for the callers
   above the tail. */
static inline void GetTurnXAngleZY_i(short *a0, short *a1, float x, float y, float z)
{
    float v0[4] = {x, y, z, 1.0f};
    float v1[4] = {x, y, 0.0f, 1.0f};
    float len;
    float zz;

    sceVu0Normalize(v0, v0);
    if (0.01f < FSqrt(x * x + y * y)) {
        sceVu0Normalize(v1, v1);
        *a0 = GetTableArcTan2(v1[1], v1[0]);
    }
    len = FSqrt(v0[0] * v0[0] + v0[1] * v0[1]);
    zz = v0[2];
    *a1 = -GetTableArcTan2(zz, len);
}

void MatrixDrive_TurnXObjectMatrixZY(float x, float y, float z)
{
    short az;
    short ay;

    GetTurnXAngleZY_i(&az, &ay, x, y, z);
    MatrixDrive_RotMatrixZ(az);
    MatrixDrive_RotMatrixY(ay);
}

/* INTERIM stand-in: MatrixDrive_GetTurnXAngleYZ is `inline` in the 2001 source, so its
   out-of-line copy lands in the deferred inline tail BELOW this caller and gcc
   cannot inline it from there. Same body. */
static inline void GetTurnXAngleYZ_i(short *a0, short *a1, float x, float y, float z)
{
    float v0[4] = {x, y, z, 1.0f};
    float v1[4] = {x, 0.0f, z, 1.0f};
    float len;
    float t;

    sceVu0Normalize(v0, v0);
    if (0.01f < FSqrt(x * x + z * z)) {
        sceVu0Normalize(v1, v1);
        *a0 = -GetTableArcTan2(v1[2], v1[0]);
    }
    len = FSqrt(v0[0] * v0[0] + v0[2] * v0[2]);
    t = v0[1];
    *a1 = GetTableArcTan2(t, len);
}

void MatrixDrive_TurnXObjectMatrixYZ(float x, float y, float z)
{
    short ay;
    short az;

    GetTurnXAngleYZ_i(&ay, &az, x, y, z);
    MatrixDrive_RotMatrixY(ay);
    MatrixDrive_RotMatrixZ(az);
}

/* INTERIM stand-in: MatrixDrive_GetTurnYAngleXZ is `inline` in the 2001 source, so its
   out-of-line copy lands in the deferred inline tail BELOW this caller and gcc
   cannot inline it from there. Same body. */
static inline void GetTurnYAngleXZ_i(short *a0, short *a1, float x, float y, float z)
{
    float v0[4] = {x, y, z, 1.0f};
    float v1[4] = {0.0f, y, z, 1.0f};
    float len;

    sceVu0Normalize(v0, v0);
    if (0.01f < FSqrt(y * y + z * z)) {
        sceVu0Normalize(v1, v1);
        *a0 = -GetTableArcTan2(v1[2], v1[1]);
    }
    len = FSqrt(v0[1] * v0[1] + v0[2] * v0[2]);
    *a1 = GetTableArcTan2(v0[0], len);
}

void MatrixDrive_TurnYObjectMatrixXZ(float x, float y, float z)
{
    short ax;
    short az;

    GetTurnYAngleXZ_i(&ax, &az, x, y, z);
    MatrixDrive_RotMatrixX(ax);
    MatrixDrive_RotMatrixZ(az);
}

/* INTERIM stand-in: MatrixDrive_GetTurnZAngleXY is `inline` in the 2001 source, so its
   out-of-line copy lands in the deferred inline tail BELOW this caller and gcc
   cannot inline it from there. Same body. */
static inline void GetTurnZAngleXY_i(short *a0, short *a1, float x, float y, float z)
{
    float v0[4] = {x, y, z, 1.0f};
    float v1[4] = {0.0f, y, z, 1.0f};
    float len;

    sceVu0Normalize(v0, v0);
    if (0.01f < FSqrt(y * y + z * z)) {
        sceVu0Normalize(v1, v1);
        *a0 = -GetTableArcTan2(v1[1], v1[2]);
    }
    len = FSqrt(v0[1] * v0[1] + v0[2] * v0[2]);
    *a1 = GetTableArcTan2(v0[0], len);
}

void MatrixDrive_TurnZObjectMatrixXY(float x, float y, float z)
{
    short ax;
    short ay;

    GetTurnZAngleXY_i(&ax, &ay, x, y, z);
    MatrixDrive_RotMatrixX(ax);
    MatrixDrive_RotMatrixY(ay);
}

/* kept local: this TU's uses of FSqrt do not fit the prototype in matrixDrive.h */
extern float FSqrt(float a0);

void MatrixDrive_GetTurnXAngleZY(short *a0, short *a1, float x, float y, float z)
{
    float v0[4] = {x, y, z, 1.0f};
    float v1[4] = {x, y, 0.0f, 1.0f};
    float len;
    float zz;

    sceVu0Normalize(v0, v0);
    if (0.01f < FSqrt(x * x + y * y)) {
        sceVu0Normalize(v1, v1);
        *a0 = GetTableArcTan2(v1[1], v1[0]);
    }
    len = FSqrt(v0[0] * v0[0] + v0[1] * v0[1]);
    zz = v0[2];
    *a1 = -GetTableArcTan2(zz, len);
}

void MatrixDrive_GetTurnXAngleYZ(short *a0, short *a1, float x, float y, float z)
{
    float v0[4] = {x, y, z, 1.0f};
    float v1[4] = {x, 0.0f, z, 1.0f};
    float len;
    float t;

    sceVu0Normalize(v0, v0);
    if (0.01f < FSqrt(x * x + z * z)) {
        sceVu0Normalize(v1, v1);
        *a0 = -GetTableArcTan2(v1[2], v1[0]);
    }
    len = FSqrt(v0[0] * v0[0] + v0[2] * v0[2]);
    t = v0[1];
    *a1 = GetTableArcTan2(t, len);
}

void MatrixDrive_GetTurnYAngleXZ(short *a0, short *a1, float x, float y, float z)
{
    float v0[4] = {x, y, z, 1.0f};
    float v1[4] = {0.0f, y, z, 1.0f};
    float len;

    sceVu0Normalize(v0, v0);
    if (0.01f < FSqrt(y * y + z * z)) {
        sceVu0Normalize(v1, v1);
        *a0 = -GetTableArcTan2(v1[2], v1[1]);
    }
    len = FSqrt(v0[1] * v0[1] + v0[2] * v0[2]);
    *a1 = GetTableArcTan2(v0[0], len);
}

/* kept local: this TU's uses of FSqrt do not fit the prototype in matrixDrive.h */
extern float FSqrt(float a0);

void MatrixDrive_GetTurnYEAngleXZ(float *a0, float *a1, float x, float y, float z)
{
    float v0[4];
    float v1[4];
    float t;

    v0[0] = x;
    v0[1] = y;
    v0[2] = z;
    v0[3] = 1.0f;
    v1[0] = 0.0f;
    v1[1] = y;
    v1[2] = z;
    v1[3] = 1.0f;
    sceVu0Normalize(v0, v0);
    t = FSqrt(y * y + z * z);
    if (0.01f < t) {
        sceVu0Normalize(v1, v1);
        a0[0] = v1[1];
        a0[1] = v1[2];
    } else {
        a0[0] = 1.0f;
        a0[1] = 0.0f;
    }
    a1[0] = FSqrt(v0[1] * v0[1] + v0[2] * v0[2]);
    a1[1] = v0[0];
}

void MatrixDrive_GetTurnZAngleXY(short *a0, short *a1, float x, float y, float z)
{
    float v0[4] = {x, y, z, 1.0f};
    float v1[4] = {0.0f, y, z, 1.0f};
    float len;

    sceVu0Normalize(v0, v0);
    if (0.01f < FSqrt(y * y + z * z)) {
        sceVu0Normalize(v1, v1);
        *a0 = -GetTableArcTan2(v1[1], v1[2]);
    }
    len = FSqrt(v0[1] * v0[1] + v0[2] * v0[2]);
    *a1 = GetTableArcTan2(v0[0], len);
}

void MatrixDrive_GetTurnZAngleYX(short *a0, short *a1, float x, float y, float z)
{
    float v0[4] = {x, y, -z, 1.0f};
    float v1[4] = {x, 0.0f, -z, 1.0f};
    float len;
    float p;
    float q;
    float yy;

    sceVu0Normalize(v0, v0);
    if (0.01f < FSqrt(x * x + z * z)) {
        sceVu0Normalize(v1, v1);
        p = v1[2];
        q = v1[0];
        *a0 = GetTableArcTan2(-q, -p);
    }
    len = FSqrt(v0[0] * v0[0] + v0[2] * v0[2]);
    yy = v0[1];
    *a1 = -GetTableArcTan2(yy, len);
}

void MatrixDrive_GetTurnMinusZAngleXY(short *a0, short *a1, float x, float y, float z)
{
    float v0[4] = {x, y, z, 1.0f};
    float v1[4] = {0.0f, y, z, 1.0f};
    float len;
    float p;
    float q;

    sceVu0Normalize(v0, v0);
    if (0.01f < FSqrt(y * y + z * z)) {
        sceVu0Normalize(v1, v1);
        p = v1[2];
        q = v1[1];
        *a0 = GetTableArcTan2(-q, -p);
    }
    len = FSqrt(v0[1] * v0[1] + v0[2] * v0[2]);
    *a1 = GetTableArcTan2(v0[0], len);
}

typedef struct {
    float x;
    float y;
    float z;
    float w;
} __attribute__((aligned(16))) MdVec;

void MatrixDrive_SetTransposeMatrix(float *dst, float *src)
{
    MdVec v = {-src[12], -src[13], -src[14], 0.0f};

    sceVu0TransposeMatrix(dst, src);
    dst[3] = dst[7] = dst[11] = 0.0f;
    sceVu0ApplyMatrix((int *)&dst[12], (char *)dst, (int)&v);
    dst[15] = 1.0f;
}

void CopyVector(void *dst, void *src)
{
    QCOPY16("$a2");
}

void CopyIVector(void *dst, void *src)
{
    QCOPY16("$a2");
}

void CopyMatrix(void *dst, void *src)
{
    QCOPY64_SERIAL("$a2");
}

void CopyMatrixUncached(void *dst, void *src)
{
    MAP_A0_TO_SPR();
    QCOPY64_SERIAL("$a2");
}

void AddVectorXYZ(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 4, 0x0, a1);
    VU0_LSV(lqc2, 5, 0x0, a2);
    VU0_V3OP(vadd.xyz, 4, 4, 5);
    VU0_LSV(sqc2, 4, 0x0, a0);
}

void SubVectorXYZ(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 4, 0x0, a1);
    VU0_LSV(lqc2, 5, 0x0, a2);
    VU0_V3OP(vsub.xyz, 4, 4, 5);
    VU0_LSV(sqc2, 4, 0x0, a0);
}

void UnitRotation(MatDrive *a0)
{
    Qw128 tmp[1];
    void *p = &a0->q;
    LQ16_FROM(p);
    SQ16_TO(tmp);
    sceVu0UnitMatrix(a0);
    LQ16_FROM(tmp);
    SQ16_TO(p);
}

float FSqrt(float a0)
{
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 4);
    VU0_NOREORDER_END();
    VU0_WORD(0x4A0403BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}

void VectorLength(void *p0)
{
    VU0_LSV(lqc2, 4, 0x0, a0);
    VU0_V3OP(vmul.xyz, 4, 4, 4);
    VU0_V3OP_BC(vaddy.x, 4, 4, 4, y);
    VU0_V3OP_BC(vaddz.x, 4, 4, 4, z);
    VU0_WORD(0x4A0403BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}

void VectorLengthSquare(void *p0)
{
    VU0_LSV(lqc2, 3, 0x0, a0);
    VU0_V3OP(vmul.xyz, 3, 3, 3);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_QMFC2_NI(v0, 3);
    VU0_MTC1(v0, 0);
}

float GetPointDistance(void *a0, void *a1)
{
    float v[4] __attribute__((aligned(16)));
    float r;
    sceVu0SubVector(v, a0, a1);
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 $vf4, 0x0(%1)\n"
                         "vmul.xyz $vf4, $vf4, $vf4\n"
                         "vaddy.x $vf4, $vf4, $vf4y\n"
                         "vaddz.x $vf4, $vf4, $vf4z\n"
                         ".word 0x4A0403BD\n"
                         "vwaitq\n"
                         "cfc2.ni %0, $vi22\n"
                         ".set reorder\n"
                         : "=r"(r)
                         : "r"(v));
    return r;
}
