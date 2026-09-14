#include "common.h"

extern void CopyVector(void *dst, void *src);
extern void *isysGObjSearchFromObjKindID_begin(int kind);
extern void *isysGObjSearchFromObjKindID_next(void *gobj);
extern void HotInitCageGeo(char *gobj);
/* prototypes: their order is the inline tail's emission order */
int GetCageChainPoint(char *a0, char *a1, char *a2);
void SetCageVelocityFriction(char *a0, float a1);
void StabilizeAllLayoutedCage(void);
void SetCageChainHangableFlag(char *a0, int a1);
extern void sceVu0Normalize(void *dst, void *src);
extern void sceVu0ScaleVector(void *dst, void *src, float k);
extern void sceVu0AddVector(void *dst, void *a, void *b);
extern void sceVu0SubVector(void *dst, void *a, void *b);
extern float FSqrt(float x);
extern float VectorLength(void *v);

int CageRideFunc(char **self, char *rider)
{
    float v[4];
    float n[4];
    char *w;
    float d;
    float t;

    w = *(char **)(*(char **)(*self + 0x15C) + 0x830);
    CopyVector(v, *(char **)(rider + 0x15C) + 0xA0);
    v[1] = v[1] - 250.0f;
    sceVu0Normalize(n, v);
    d = FSqrt(n[0] * n[0] + n[2] * n[2]) * 50.0f;
    t = VectorLength(v) * d / 250.0f;
    if (t < 0.0f) {
        t = -t;
    }
    v[1] = 0.0f;
    sceVu0ScaleVector(v, v, t * 0.06f / *(float *)(w + 0x38));

    sceVu0AddVector((void *)(*(int *)(w + 0x24) * 80 + *(int *)(*(char **)(w + 0x20) + 8) + 0x40),
                    (void *)(*(int *)(w + 0x24) * 80 + *(int *)(*(char **)(w + 0x20) + 8) + 0x40),
                    v);

    sceVu0SubVector((void *)(*(int *)(w + 0x28) * 80 + *(int *)(*(char **)(w + 0x20) + 8) + 0x40),
                    (void *)(*(int *)(w + 0x28) * 80 + *(int *)(*(char **)(w + 0x20) + 8) + 0x40),
                    v);

    return 1;
}

void SetCageFixGeometry(char *self, void *pos, void *dir)
{
    char *w = *(char **)(*(char **)(self + 0x15C) + 0x830);

    CopyVector(*(char **)(*(char **)(w + 0x20)) + 0x20, pos);
    CopyVector(w + 0x10, dir);
}

inline int GetCageChainPoint(char *a0, char *a1, char *a2)
{
    char *w = *(char **)(*(char **)(a2 + 0x15C) + 0x830);
    CopyVector(a0, *(char **)(*(char **)(*(char **)(w + 0x20) + 8)));
    CopyVector(a1, *(char **)(*(char **)(*(char **)(w + 0x20) + 8)) + 0x10);
    *(float *)(a0 + 4) = *(float *)(a0 + 4) + 50.0f;
    *(float *)(a1 + 4) = *(float *)(a1 + 4) - 150.0f;
    return *(int *)(w + 0x40);
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/cage", InitCageGeo);
ASM_LIT4_SLOT(D_00639460, 0.995f);
ASM_LIT4_SLOT(D_00639464, 10430.378f);

inline void SetCageChainHangableFlag(char *a0, int a1)
{
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x40) = a1;
}

extern char D_0028FEF0[];

void HotInitCageGeo(char *self)
{
    char *w = *(char **)(*(char **)(self + 0x15C) + 0x830);

    CopyVector((void *)(*(int *)(w + 0x24) * 80 + *(int *)(*(char **)(w + 0x20) + 8) + 0x40),
               D_0028FEF0);
    CopyVector((void *)(*(int *)(w + 0x28) * 80 + *(int *)(*(char **)(w + 0x20) + 8) + 0x40),
               D_0028FEF0);

    CopyVector((void *)(*(int *)(w + 0x24) * 80 + *(int *)(*(char **)(w + 0x20) + 8) + 0x30),
               *(char **)(*(char **)(w + 0x20)) + 0x20);
    CopyVector((void *)(*(int *)(w + 0x28) * 80 + *(int *)(*(char **)(w + 0x20) + 8) + 0x30),
               *(char **)(*(char **)(w + 0x20)) + 0x20);

    CopyVector(*(void **)(*(int *)(*(char **)(w + 0x20) + 8)),
               *(char **)(*(char **)(w + 0x20)) + 0x20);
    CopyVector((void *)(*(int *)(*(int *)(*(char **)(w + 0x20) + 8)) + 0x10),
               *(char **)(*(char **)(w + 0x20)) + 0x20);

    *(float *)(*(int *)(*(int *)(*(char **)(w + 0x20) + 8)) + 0x14) =
        *(float *)(*(int *)(*(int *)(*(char **)(w + 0x20) + 8)) + 0x14) +
        *(float *)(w + 0x30) * (float)*(int *)(w + 0x2C);

    *(float *)(*(int *)(*(char **)(w + 0x20) + 8) + *(int *)(w + 0x24) * 80 + 0x34) =
        *(float *)(*(int *)(*(char **)(w + 0x20) + 8) + *(int *)(w + 0x24) * 80 + 0x34) +
        *(float *)(w + 0x30) * (float)*(int *)(w + 0x2C);

    *(float *)(*(int *)(*(char **)(w + 0x20) + 8) + *(int *)(w + 0x28) * 80 + 0x34) =
        *(float *)(*(int *)(*(char **)(w + 0x20) + 8) + *(int *)(w + 0x28) * 80 + 0x34) +
        (*(float *)(w + 0x30) * (float)*(int *)(w + 0x2C) + 500.0f);
}

inline void StabilizeAllLayoutedCage(void)
{
    void *gobj;

    gobj = isysGObjSearchFromObjKindID_begin(0x2C);
    while (gobj != 0) {
        HotInitCageGeo(gobj);
        gobj = isysGObjSearchFromObjKindID_next(gobj);
    }
}

inline void SetCageVelocityFriction(char *a0, float a1)
{
    *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x3C) = a1;
}

extern void *GetWindVector(int kind, void *pos);
extern void _ScaleVector(void *dst, void *src, float k);
extern void _AddVector(void *dst, void *a, void *b);
extern void sceVu0OuterProduct(void *dst, void *a, void *b);
extern void SetQuaternionByAxisRotateV(void *q, int angle, void *axis);
extern float atan2f(float y, float x);
extern char D_004E6EC0[];

static inline void SetCageChainQuaternion(void *q, void *a, void *b)
{
    float d[4];
    float n[4];
    float axis[4];

    sceVu0SubVector(d, a, b);
    sceVu0Normalize(d, d);
    CopyVector(n, d);
    n[1] = 0.0f;
    sceVu0OuterProduct(axis, D_004E6EC0, n);
    SetQuaternionByAxisRotateV(
        q, (short)(atan2f(FSqrt(d[0] * d[0] + d[2] * d[2]), d[1]) * 10430.378f), axis);
}

static inline void AddCageWindForce(char *n, float k)
{
    float v[4];

    CopyVector(v, GetWindVector(0, n + 0x20));
    _ScaleVector(v, v, k / *(float *)(n + 0x44));
    _AddVector(n + 0x30, n + 0x30, v);
}

extern void *MatrixDrive_GetMatrix(void);
extern void sceVu0UnitMatrix(void *m);
extern void GetChainAnimation(void *chain, int a, void *m);
extern int GetTableArcTan2(float y, float x);
extern void sceVu0ScaleVectorXYZ(void *dst, void *src, float k);
extern void RotQuaternionY(void *q, int angle);
extern void MultiQuaternion(void *dst, void *a, void *b);
extern void RegularizeQuaternion(void *q);
extern void GetMatrixFromQuaternionPos(void *m, void *q, void *pos);
extern void MatrixDrive_TransMatrix(float x, float y, float z);
extern void CopyMatrix(void *dst, void *src);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void MatrixDrive_RotMatrixX(int angle);

void CageGeo(char *self)
{
    char *w;
    char *n0;
    char *n1;
    int i;

    w = *(char **)(*(char **)(self + 0x15C) + 0x830);

    n0 = *(char **)(*(char **)(w + 0x20) + 8) + (*(int *)(w + 0x24) * 80 + 16);
    n1 = *(char **)(*(char **)(w + 0x20) + 8) + (*(int *)(w + 0x28) * 80 + 16);
    AddCageWindForce(n0, 1.0f);
    AddCageWindForce(n1, 10.0f);

    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    GetChainAnimation(*(char **)(w + 0x20), 0, MatrixDrive_GetMatrix());

    {
        float v[4];
        int angle;
        float f;

        sceVu0SubVector(
            v, (void *)(*(int *)(w + 0x28) * 80 + *(int *)(*(char **)(w + 0x20) + 8) + 0x30),
            (void *)(*(int *)(w + 0x24) * 80 + *(int *)(*(char **)(w + 0x20) + 8) + 0x30));
        sceVu0Normalize(v, v);
        angle = GetTableArcTan2(FSqrt(v[0] * v[0] + v[2] * v[2]), v[1]);
        if (angle >= 2731) {
            f = (float)angle / 2730.0f;
            v[1] = 0.0f;
            sceVu0ScaleVector(v, v, f);
            sceVu0SubVector(
                (void *)(*(int *)(w + 0x28) * 80 + *(int *)(*(char **)(w + 0x20) + 8) + 0x40),
                (void *)(*(int *)(w + 0x28) * 80 + *(int *)(*(char **)(w + 0x20) + 8) + 0x40), v);
            sceVu0AddVector(
                (void *)(*(int *)(w + 0x24) * 80 + *(int *)(*(char **)(w + 0x20) + 8) + 0x40),
                (void *)(*(int *)(w + 0x24) * 80 + *(int *)(*(char **)(w + 0x20) + 8) + 0x40), v);
        }
    }

    sceVu0ScaleVectorXYZ(
        (void *)(*(int *)(w + 0x28) * 80 + *(int *)(*(char **)(w + 0x20) + 8) + 0x40),
        (void *)(*(int *)(w + 0x28) * 80 + *(int *)(*(char **)(w + 0x20) + 8) + 0x40),
        *(float *)(w + 0x3C));
    sceVu0ScaleVectorXYZ(
        (void *)(*(int *)(w + 0x24) * 80 + *(int *)(*(char **)(w + 0x20) + 8) + 0x40),
        (void *)(*(int *)(w + 0x24) * 80 + *(int *)(*(char **)(w + 0x20) + 8) + 0x40),
        *(float *)(w + 0x3C));

    SetCageChainQuaternion(
        *(char **)(*(char **)(self + 0x15C) + 0x10),
        (void *)(*(int *)(w + 0x28) * 80 + *(int *)(*(char **)(w + 0x20) + 8) + 0x30),
        (void *)(*(int *)(w + 0x24) * 80 + *(int *)(*(char **)(w + 0x20) + 8) + 0x30));
    RotQuaternionY(*(char **)(*(char **)(self + 0x15C) + 0x10), *(short *)(w + 0x34));
    MultiQuaternion(*(char **)(*(char **)(self + 0x15C) + 0x10),
                    *(char **)(*(char **)(self + 0x15C) + 0x10), w + 0x10);
    RegularizeQuaternion(*(char **)(*(char **)(self + 0x15C) + 0x10));
    GetMatrixFromQuaternionPos(
        MatrixDrive_GetMatrix(), *(char **)(*(char **)(self + 0x15C) + 0x10),
        (void *)(*(int *)(w + 0x24) * 80 + *(int *)(*(char **)(w + 0x20) + 8) + 0x30));
    MatrixDrive_TransMatrix(0.0f, 0.0f, 0.0f);
    CopyMatrix(*(char **)(*(char **)(self + 0x15C) + 0x0C), MatrixDrive_GetMatrix());

    {
        float q[4];

        SetCageChainQuaternion(q, *(char **)(*(char **)(*(char **)(w + 0x20) + 8)) + 0x10,
                               *(char **)(*(char **)(*(char **)(w + 0x20) + 8)));
        GetMatrixFromQuaternionPos(MatrixDrive_GetMatrix(), q,
                                   *(char **)(*(char **)(*(char **)(w + 0x20) + 8)));
        CopyVector((char *)MatrixDrive_GetMatrix() + 0x30,
                   *(char **)(*(char **)(*(char **)(w + 0x20) + 8)) + 0x10);
    }
    MatrixDrive_TransMatrix(0.0f, -(*(float *)(w + 0x30) * 0.5f - 20.0f), 0.0f);

    for (i = 0; i < *(int *)(w + 0x2C); i++) {
        MatrixDrive_PushMatrix();
        MatrixDrive_RotMatrixX(-32768);
        CopyMatrix(*(char **)(*(char **)w + 0x0C) + i * 64, MatrixDrive_GetMatrix());
        MatrixDrive_PopMatrix();
        MatrixDrive_TransMatrix(0.0f, -*(float *)(w + 0x30), 0.0f);
    }
}

extern void p2o_DispVU1(void *a0);
extern void p2o_DispVU1DObjMulti(void *a0);

void CageDL(char *self)
{
    char *w = *(char **)(*(char **)(self + 0x15C) + 0x830);

    p2o_DispVU1(self);
    p2o_DispVU1DObjMulti(*(void **)w);
}
