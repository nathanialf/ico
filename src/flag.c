#include "common.h"

extern float D_004E7A20[];
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_RotMatrixZ(short ang);
extern void _UnitMatrix(void *m);
extern void _ApplyMatrix(void *dst, void *m, void *src);
extern void RotQuaternionZ(void *q, short ang);
extern void prim_UpdateMesh3D(void *mesh, int a1, int a2);

/* The January listing puts these rows at flag.c:28-37, inside
   SetFlag4PointFixID's own span and below its def line, with no out-of-line
   body of their own: a helper gcc inlined whole into its single call site
   at line 70. */
static inline void setFlag4PointMesh(char *mesh, char *cl, float k, int id)
{
    float *tbl = (float *)(id * 0x40 + (int)D_004E7A20);
    float *v = *(float **)(mesh + 0x74);
    int n = *(int *)cl;
    int m = *(int *)(cl + 0x8);
    int i;
    int j;
    float a;
    float b;
    float c;
    float d;

    for (i = 0; i < n; i++) {
        a = tbl[0] + (tbl[4] - tbl[0]) * i / (n - 1);
        b = tbl[8] + (tbl[12] - tbl[8]) * i / (n - 1);
        for (j = 0; j < m; j++) {
            c = tbl[1] + (tbl[9] - tbl[1]) * j / (m - 1) + k;
            d = tbl[5] + (tbl[13] - tbl[5]) * j / (m - 1) + k;
            *(float *)((i * m + j) * 0x10 + (int)v + 0x4) = c + (d - c) * i / (n - 1);
            *(float *)((i * m + j) * 0x10 + (int)v) = a + (b - a) * j / (m - 1);
        }
    }
}

void SetFlag4PointFixID(char *self, int a1, int id)
{
    char *w;
    short ang;

    w = *(char **)(*(char **)(self + 0x15C) + 0x830);
    *(int *)(w + 0x10) = a1;
    _UnitMatrix(MatrixDrive_GetMatrix());
    ang = -a1 * 0x4000;
    MatrixDrive_RotMatrixZ(ang);
    _ApplyMatrix(*(char **)(self + 0x15C) + 0xA0, MatrixDrive_GetMatrix(),
                 *(char **)(self + 0x15C) + 0xA0);
    RotQuaternionZ(*(char **)(self + 0x15C) + 0xD0, ang);
    setFlag4PointMesh(*(char **)(*(char **)(*(char **)(w + 0x4) + 0x4)), *(char **)(w + 0x8),
                      a1 * 0.25f, id);
    prim_UpdateMesh3D(*(char **)(*(char **)(*(char **)(w + 0x4) + 0x4)), 8, 0);
    prim_UpdateMesh3D(*(char **)(*(char **)(*(char **)(w + 0x4) + 0x4)), 8, 1);
}

/* InitFlagGeo is seeded, not landed: the body is reconstructed at 507/507
   instructions with the whole structure correct and 192 word diffs left, all
   of them register allocation and scheduling.  See
   seeds/flag.r10_InitFlagGeo_507insn_192worddiffs_TU.c and the r10 ledger
   row for the five mechanisms already found. */
INCLUDE_ASM("asm/nonmatchings/src/flag", InitFlagGeo);

typedef struct {
    float m[4];
} Vec4;

extern void *MatrixDrive_GetMatrix(void);
extern void GetRootMatrix(void *m, void *gobj);
extern void GetClothAnimation(void *a0, void *a1, int a2, void *m, int a4, int a5, void *a6,
                              int a7);
extern void GetClothAnimationFix4Points(void *a0, void *a1, int a2, void *m);

void FlagGeo(char *self)
{
    char *gd;
    char *o;

    gd = *(char **)(*(char **)(self + 0x15C) + 0x830);
    o = *(char **)(gd + 0x4);
    if (*(char **)(*(char **)(self + 0x15C)) != 0 &&
        *(int *)(*(char **)(*(char **)(self + 0x15C)) + 0x16C) == 0) {
        return;
    }
    GetRootMatrix(MatrixDrive_GetMatrix(), self);
    switch (*(int *)gd) {
    case 0:
    case 1:
        GetClothAnimation(*(void **)(*(char **)(o + 0x4) + 0x4),
                          *(void **)(*(char **)(o + 0x4) + 0x8), 0, MatrixDrive_GetMatrix(),
                          *(int *)(gd + 0x8), *(int *)(gd + 0xC),
                          *(int *)(gd + 0xC) != 0 ? self : 0, 0);
        break;
    case 2:
        GetClothAnimation(*(void **)(*(char **)(o + 0x4) + 0x4),
                          *(void **)(*(char **)(o + 0x4) + 0x8), 0, MatrixDrive_GetMatrix(),
                          *(int *)(gd + 0x8), *(int *)(gd + 0xC),
                          *(int *)(gd + 0xC) != 0 ? self : 0, 1);
        break;
    case 4:
        GetClothAnimationFix4Points(*(void **)(*(char **)(o + 0x4) + 0x4),
                                    *(void **)(*(char **)(o + 0x4) + 0x8), *(int *)(gd + 0x8),
                                    MatrixDrive_GetMatrix());
        break;
    }
}

extern void memset(void *dst, int c, int n);
extern void _SubVector(void *dst, void *a, void *b);
extern void _NormalizeVector(void *dst, void *src);
extern void GetDifferencialQuaternionWithNoRegularize(void *dst, void *a, void *b);
extern void MultiQuaternion(void *dst, void *a, void *b);
extern void CopyVector(void *dst, void *src);
extern void GetMatrixFromQuaternionPos(void *m, void *q, void *pos);
extern void p2o_DispVU1Multi(void *self);
extern void light_MakeLightMatrix(void *o, int idx);
extern void DispClothMesh(void *a0, void *a1, void *a2);

void FlagDL(char *self)
{
    Vec4 l0;
    Vec4 l10;
    Vec4 l20;
    Vec4 l30;
    Vec4 l40;
    char *gd;
    char *o;
    char *base;
    char *m;
    int i;
    int n;

    gd = *(char **)(*(char **)(self + 0x15C) + 0x830);
    o = *(char **)(gd + 0x4);
    if (*(char **)(*(char **)(self + 0x15C)) != 0 &&
        *(int *)(*(char **)(*(char **)(self + 0x15C)) + 0x16C) == 0) {
        return;
    }
    switch (*(int *)gd) {
    case 1:
    case 2:
        n = *(int *)(*(char **)(gd + 0x8) + 0x8);
        base = *(char **)(*(char **)(*(char **)(o + 0x4) + 0x4));
        memset(&l0, 0, 0x10);
        l0.m[3] = 1.0f;
        memset(&l10, 0, 0x10);
        l10.m[1] = 1.0f;
        for (i = 1; i < n; i++) {
            _SubVector(&l20, base + i * 0x10, base + (i * 0x10 - 0x10));
            _NormalizeVector(&l30, &l20);
            GetDifferencialQuaternionWithNoRegularize(&l40, &l30, &l10);
            MultiQuaternion(&l0, &l40, &l0);
            CopyVector(&l10, &l30);
            GetMatrixFromQuaternionPos(*(char **)(*(char **)(self + 0x15C) + 0xC) +
                                           (i * 0x40 - 0x40),
                                       &l0, base + (i * 0x10 - 0x10));
        }
        p2o_DispVU1Multi(self);
        break;
    case 0:
        light_MakeLightMatrix(*(char **)(self + 0x15C), 0);
        m = *(char **)(*(char **)(self + 0x15C) + 0x874);
        DispClothMesh(*(char **)(o + 0x4), m + 0x40, m);
        break;
    case 4:
        light_MakeLightMatrix(*(char **)(self + 0x15C), 0);
        m = *(char **)(*(char **)(self + 0x15C) + 0x874);
        DispClothMesh(*(char **)(o + 0x4), m + 0x40, m);
        break;
    }
}
