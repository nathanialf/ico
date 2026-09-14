#include "common.h"

typedef struct {
    long long x;
} __attribute__((packed, aligned(4))) PackedLL_19CAF0;

typedef struct {
    unsigned int lo;
    unsigned char m[3];
    unsigned char hi;
} DObjBlk8;

extern char D_00618F30[];
extern int D_0063A438;
extern void LocalizeGeometry();
extern DObjBlk8 D_0063A810;
extern void GlobalizeGeometry(void *a0);
/* prototypes: their order is the inline tail's emission order */
void FreeDObj(void);
void LinkParentOfDObj(void *a0, PackedLL_19CAF0 *a1);
void UnlinkParentOfDObj(void *a0);

typedef union {
    char *p;
    int i;
    float f;
} DObjWord;

typedef struct {
    char pad[0x15C];
    DObjWord data;
    char pad2[0x20];
} DObjGObj;

typedef struct {
    long long w[4];
} DObjBlk20;

typedef struct {
    long long w[2];
} DObjBlk10;

typedef struct {
    long long w[8];
} DObjBlk40;

typedef struct {
    long long w[24];
} DObjBlkC0;

extern char D_0028FEF0[];
extern char D_0028FF00[];
extern DObjBlk40 D_003198A0;
extern DObjBlk20 D_003198E0;
extern DObjBlkC0 D_00319900;
extern DObjBlk40 D_003199C0;
extern DObjBlk10 D_00618F40;
extern void *iosMallocDebug(int heap, int size, char *file, int line);
extern void InitMotionGeoInfo(void *p, float a, float b, float c, float d, float e, float f);
extern void InitMotionStateInfo(void *p);
extern void InitFrameDependSequence(void *p);
extern void InitMotionRotElem(void *p, int n);
extern void CopyVector(void *dst, void *src);
extern void _ApplyRyGV(void *v, float ry);
extern void SetMotionDirection(void *gobj, void *v);

static inline void initGeometryScaleRatio(char *d)
{
    float r;
    float t;

    r = 1.0f;
    if (*(char **)(d + 0x8C) != 0) {
        t = (*(float *)(*(char **)(d + 0x870) + 0x20) + *(float *)(*(char **)(d + 0x870) + 0x24) +
             *(float *)(*(char **)(d + 0x870) + 0x28)) *
            0.333f;
        r = 1.0f / (*(float *)(*(char **)(d + 0x8C) + 0x14) * t * 2.0f * 1.5f);
    }
    *(float *)(d + 0x824) = r;
}

void initGeometryState(char *self, float *lay)
{
    DObjGObj g;
    DObjGObj *p;
    float dir[4];
    int i;
    int j;
    int k;
    int m;
    int n;

    p = &g;
    g.data.p = self;
    InitMotionGeoInfo(self + 0xA0, lay[0], lay[1], lay[2], lay[4], lay[5], lay[6]);
    InitMotionStateInfo(p->data.p + 0x470);
    InitFrameDependSequence(p->data.p + 0x740);
    *(DObjBlkC0 *)(p->data.p + 0x680) = D_00319900;

    if (*(char **)(p->data.p + 0x8C) != 0) {
        *(float *)(p->data.p + 0x1DC) =
            *(float *)(p->data.p + 0x1DC) + *(float *)(*(char **)(p->data.p + 0x8C) + 0x14) *
                                                *(float *)(*(char **)(self + 0x870) + 0x20);
        *(void **)(p->data.p + 0x7D0) =
            iosMallocDebug(D_0063A438, *(int *)(p->data.p + 0x88) << 5, D_00618F30, 125);
        *(void **)(p->data.p + 0x7B4) =
            iosMallocDebug(D_0063A438, *(int *)(p->data.p + 0x88) << 5, D_00618F30, 127);
        InitMotionRotElem(*(void **)(p->data.p + 0x7D0), *(int *)(p->data.p + 0x88));
        InitMotionRotElem(*(void **)(p->data.p + 0x7B4), *(int *)(p->data.p + 0x88));
        CopyVector(p->data.p + 0x7E0, D_0028FF00);
        CopyVector(p->data.p + 0x7E0, D_0028FF00);
        CopyVector(p->data.p + 0x7F0, D_0028FEF0);
        *(int *)(p->data.p + 0x808) = 0;
        *(DObjBlk8 *)(p->data.p + 0x800) = D_0063A810;
        *(void **)(p->data.p + 0x80C) =
            iosMallocDebug(D_0063A438, *(int *)(p->data.p + 0x88) << 6, D_00618F30, 137);
        for (i = 0; i < *(int *)(p->data.p + 0x88); i++) {
            *(DObjBlk40 *)(*(char **)(p->data.p + 0x80C) + i * 64) = D_003198A0;
        }
        *(void **)(p->data.p + 0x810) =
            iosMallocDebug(D_0063A438, *(int *)(p->data.p + 0x88) << 2, D_00618F30, 145);
        for (j = 0; j < *(int *)(p->data.p + 0x88); j++) {
            *(int *)(*(char **)(p->data.p + 0x810) + j * 4) = 0;
        }
        *(void **)(p->data.p + 0x814) =
            iosMallocDebug(D_0063A438, *(int *)(p->data.p + 0x88) << 4, D_00618F30, 153);
        for (k = 0; k < *(int *)(p->data.p + 0x88); k++) {
            CopyVector(*(char **)(p->data.p + 0x814) + k * 16, D_0028FEF0);
        }
        *(void **)(p->data.p + 0x818) =
            iosMallocDebug(D_0063A438, *(int *)(p->data.p + 0x88) << 6, D_00618F30, 161);
        for (m = 0; m < *(int *)(p->data.p + 0x88); m++) {
            *(DObjBlk40 *)(*(char **)(p->data.p + 0x818) + m * 64) = D_003199C0;
        }
        *(void **)(p->data.p + 0x820) =
            iosMallocDebug(D_0063A438, *(int *)(p->data.p + 0x88), D_00618F30, 169);
        for (n = 0; n < *(int *)(p->data.p + 0x88); n++) {
            *(char *)(*(char **)(p->data.p + 0x820) + n) = 0;
        }

        *(DObjBlk10 *)dir = D_00618F40;
        _ApplyRyGV(dir, -lay[5]);
        SetMotionDirection(p, dir);
    } else {
        *(void **)(p->data.p + 0x7D0) = 0;
        *(void **)(p->data.p + 0x80C) = 0;
        *(void **)(p->data.p + 0x810) = 0;
        *(void **)(p->data.p + 0x814) = 0;
        *(void **)(p->data.p + 0x818) = 0;
        *(void **)(p->data.p + 0x820) = 0;
    }
    *(void **)(p->data.p + 0x81C) = 0;
    *(DObjBlk20 *)(p->data.p + 0x660) = D_003198E0;
    initGeometryScaleRatio(p->data.p);
}

extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_TransMatrixV(void *v);
extern void MatrixDrive_RotMatrixX(short a);
extern void MatrixDrive_RotMatrixY(short a);
extern void MatrixDrive_RotMatrixZ(short a);
extern void _UnitMatrix(void *m);
extern void CopyVector(void *dst, void *src);
extern void CopyMatrix(void *dst, void *src);
extern void SetIdentityQuaternion(void *q);
extern void RotQuaternionX(void *q, short a);
extern void RotQuaternionY(void *q, short a);
extern void RotQuaternionZ(void *q, short a);

void initMatrixDObj(char *self, float *lay)
{
    float v[4];
    float d;

    MatrixDrive_PushMatrix();
    CopyVector(v, lay);
    d = 3.1415927f;
    v[3] = 1.0f;
    _UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrixV(v);
    MatrixDrive_RotMatrixY((short)(lay[5] * 32768.0f / d));
    MatrixDrive_RotMatrixX((short)(lay[4] * 32768.0f / d));
    MatrixDrive_RotMatrixZ((short)(lay[6] * 32768.0f / d));
    CopyMatrix(self + 0x20, MatrixDrive_GetMatrix());

    SetIdentityQuaternion(self + 0x60);
    RotQuaternionY(self + 0x60, (short)(lay[5] * 32768.0f / d));
    RotQuaternionX(self + 0x60, (short)(lay[4] * 32768.0f / d));
    RotQuaternionZ(self + 0x60, (short)(lay[6] * 32768.0f / d));
    MatrixDrive_PopMatrix();
}

typedef struct DObjNode DObjNode;

typedef union {
    long long ll;
    int i[2];
} DObjFlags;

extern int D_0063A44C;
extern void _CopyVector(void *dst, void *src);

void allocObjectData(char *self, char *lay, int n)
{
    int i;
    int j;
    int k;

    *(DObjNode **)(self + 0x870) = (DObjNode *)iosMallocDebug(D_0063A44C, n * 80, D_00618F30, 299);
    for (i = 0; i < n; i++) {
        {
            char *e = (char *)(i * 80 + (int)*(DObjNode **)(self + 0x870));
            ((DObjFlags *)(e + 0x38))->ll &= ~1;
        }
        {
            char *e = (char *)(i * 80 + (int)*(DObjNode **)(self + 0x870));
            ((DObjFlags *)(e + 0x38))->ll &= ~2;
        }
        {
            char *e = (char *)(i * 80 + (int)*(DObjNode **)(self + 0x870));
            ((DObjFlags *)(e + 0x38))->ll &= ~4;
            *(float *)(e + 0x44) = 0.0f;
            *(float *)(e + 0x48) = 0.0f;
            *(float *)(e + 0x4C) = 1.0f;
            *(float *)(e + 0x40) = 0.0f;
        }
        {
            char *e = (char *)(i * 80 + (int)*(DObjNode **)(self + 0x870));
            *(int *)(e + 0x30) = 0;
            *(float *)(e + 0x34) = 1.0f;
            *(short *)(e + 0x3A) = 0;
            *(float *)(e + 0x20) = 1.0f;
            *(float *)(e + 0x24) = 1.0f;
            *(float *)(e + 0x28) = 1.0f;
        }
    }
    for (j = 0; j < n; j++) {
        for (k = 0; k < 4; k++) {
            char *e = (char *)(j * 80 + (int)*(DObjNode **)(self + 0x870));
            *(int *)(e + k * 4) = 0;
            *(int *)(e + 0x10 + k * 4) = 0;
        }
        {
            char *e = (char *)(j * 80 + (int)*(DObjNode **)(self + 0x870));
            ((DObjFlags *)(e + 0x38))->ll &= ~2;
        }
        {
            char *e = (char *)(j * 80 + (int)*(DObjNode **)(self + 0x870));
            *(float *)(e + 0x40) = *(float *)(e + 0x44) = *(float *)(e + 0x48) = 0.0f;
            *(float *)(e + 0x4C) = 1.0f;
            ((DObjFlags *)(e + 0x38))->ll &= ~4;
        }
        {
            char *e = (char *)(j * 80 + (int)*(DObjNode **)(self + 0x870));
            ((DObjFlags *)(e + 0x38))->ll &= ~1;
        }
        {
            char *e = (char *)(j * 80 + (int)*(DObjNode **)(self + 0x870));
            *(float *)(e + 0x30) = 0.0f;
            *(float *)(e + 0x34) = 1.0f;
            *(short *)(e + 0x3A) = 0;
            _CopyVector(e + 0x20, lay + 0x20);
        }
    }
}

void initInitialInverseMatrix(char *a0)
{
    char *m = iosMallocDebug(D_0063A438, *(int *)(a0 + 0x88) << 6, D_00618F30, 0x14D);
    *(char **)(a0 + 0x90) = m;
    GetInitialInverseMatrixByDObj(m, a0);
}

INCLUDE_ASM("asm/nonmatchings/src/DObj", initPolygonState);

inline void FreeDObj(void) {}

INCLUDE_ASM("asm/nonmatchings/src/DObj", CSVSYSTEM_InitDObj);

inline void LinkParentOfDObj(void *a0, PackedLL_19CAF0 *a1)
{
    PackedLL_19CAF0 *p;
    LocalizeGeometry(a0, a1);
    p = *(PackedLL_19CAF0 **)((char *)a0 + 0x15C);
    *p = *a1;
}

inline void UnlinkParentOfDObj(void *a0)
{
    GlobalizeGeometry(a0);
    *(DObjBlk8 *)(*(char **)((char *)a0 + 0x15C)) = D_0063A810;
}
