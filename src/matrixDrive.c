#include "common.h"
#include "ico/types.h"
#include "vu0.h"
#include "r5900.h"

typedef int Qw128 __attribute__((mode(TI)));

typedef struct {
    char pad[0x30];
    Qw128 q;
} MatDrive;

extern int D_00639F00;
extern char D_00668640[];
extern void InitQuaternionDrive(void);
extern void InitTableSin(void);
extern void sceVu0UnitMatrix(void *a0);

void InitMatrixDrive(void)
{
    D_00639F00 = 0;
    sceVu0UnitMatrix(D_00668640);
    InitTableSin();
    InitQuaternionDrive();
}

extern void CopyMatrix(void *dst, void *src);
extern int D_00639F00;
extern char D_00668640[];

void MatrixDrive_PushMatrix(void)
{
    D_00639F00 += 1;
    CopyMatrix(&D_00668640[D_00639F00 * 0x40], &D_00668640[D_00639F00 * 0x40 - 0x40]);
}

extern float D_0028FF80[];
extern float GetTableCos(short a0);
extern float GetTableSin(short a0);
extern void func_0025D440();

void MatrixDrive_RotMatrixX(short a0)
{
    float c = GetTableCos(a0);
    float s = GetTableSin(a0);
    D_0028FF80[10] = c;
    D_0028FF80[9] = -s;
    D_0028FF80[6] = s;
    D_0028FF80[5] = c;
    func_0025D440(&D_00668640[D_00639F00 * 0x40], &D_00668640[D_00639F00 * 0x40], (int)D_0028FF80);
}

extern float D_0028FFC0[];

void MatrixDrive_RotMatrixY(short a0)
{
    float c = GetTableCos(a0);
    float s = GetTableSin(a0);
    D_0028FFC0[10] = c;
    D_0028FFC0[8] = s;
    D_0028FFC0[2] = -s;
    D_0028FFC0[0] = c;
    func_0025D440(&D_00668640[D_00639F00 * 0x40], &D_00668640[D_00639F00 * 0x40], (int)D_0028FFC0);
}

extern float D_00290000[];

void MatrixDrive_RotMatrixZ(short a0)
{
    float c = GetTableCos(a0);
    float s = GetTableSin(a0);
    D_00290000[5] = c;
    D_00290000[4] = -s;
    D_00290000[1] = s;
    D_00290000[0] = c;
    func_0025D440(&D_00668640[D_00639F00 * 0x40], &D_00668640[D_00639F00 * 0x40], (int)D_00290000);
}

extern float D_00290040[];

void MatrixDrive_ScaleMatrix(float x, float y, float z)
{
    D_00290040[0] = x;
    D_00290040[5] = y;
    D_00290040[10] = z;
    func_0025D440(&D_00668640[D_00639F00 * 0x40], &D_00668640[D_00639F00 * 0x40], (int)D_00290040);
}

extern float FSqrt(float a0);
extern void sceVu0Normalize(void *a0, void *a1);

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
        func_0025D440(&D_00668640[D_00639F00 * 0x40], (int)m, &D_00668640[D_00639F00 * 0x40]);
    }
    {
        float len = FSqrt(v0[0] * v0[0] + v0[2] * v0[2]);
        float t = v0[1];
        float m[4][4] = {{1.0f, 0.0f, 0.0f, 0.0f},
                         {0.0f, len, t, 0.0f},
                         {0.0f, -t, len, 0.0f},
                         {0.0f, 0.0f, 0.0f, 1.0f}};
        func_0025D440(&D_00668640[D_00639F00 * 0x40], (int)m, &D_00668640[D_00639F00 * 0x40]);
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
    return &D_00668640[D_00639F00 * 0x40];
}

extern char D_00668600[];

void *MatrixDrive_GetLastMatrix(void)
{
    return &D_00668600[D_00639F00 * 0x40];
}

extern void CopyVector(void *dst, void *src);
extern void sceVu0ApplyMatrix(int *buf, char *p, int x);

void MatrixDrive_TransMatrixV(char *a0)
{
    float buf[4];
    sceVu0ApplyMatrix((int *)buf, &D_00668640[D_00639F00 * 0x40], (int)a0);
    buf[3] = 1.0f;
    CopyVector(&D_00668640[D_00639F00 * 0x40 + 0x30], buf);
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
    sceVu0ApplyMatrix((int *)m, &D_00668640[D_00639F00 * 0x40], (int)v);
    m[3] = 1.0f;
    CopyVector(&D_00668640[D_00639F00 * 0x40 + 0x30], m);
}

extern int GetTableArcTan2(float a0, float a1);
extern float FSqrt(float a0);
extern void sceVu0Normalize(void *a0, void *a1);

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

extern int GetTableArcTan2(float a0, float a1);
extern float FSqrt(float a0);
extern void sceVu0Normalize(void *a0, void *a1);

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

extern float FSqrt(float a0);
extern void sceVu0Normalize(void *a0, void *a1);

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

extern void sceVu0TransposeMatrix(void *dst, void *src);

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

extern void sceVu0UnitMatrix(void *);

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

extern void sceVu0SubVector();

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
