#include "common.h"

typedef struct {
    char name[16];
    float angle;
    float pos[3];
    float pos2[3];
} StageOrientDef;

extern char D_005F5D70[][404];
extern StageOrientDef D_00556E50[41];
extern short D_006EA800[];
extern char D_0063AC68[];
extern int sscanf(const char *, const char *, ...);
extern int strcmp(const char *, const char *);

typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) VECTOR;

extern void sceVu0Normalize(VECTOR *out, VECTOR *in);
extern void sceVu0UnitMatrix(float *m);
extern void sceVu0RotMatrixY(float *m0, float *m1, float rot); /* sceVu0RotMatrixY */
extern void sceVu0InversMatrix(float *m0, float *m1);
extern void sceVu0ApplyMatrix(VECTOR *out, float *m, VECTOR *in);
/* prototypes: their order is the inline tail's emission order */
void StageOrientInit(void);
int StageOrientGet(VECTOR *ret, int stA, int stB);

inline void StageOrientInit(void)
{
    int i, j;
    char buf[64];

    for (i = 0; i < 106; i++) {
        sscanf(D_005F5D70[i], D_0063AC68, buf);
        D_006EA800[i] = -1;
        for (j = 0; j < sizeof(D_00556E50) / sizeof(D_00556E50[0]); j++) {
            if (strcmp(buf, D_00556E50[j].name) == 0) {
                D_006EA800[i] = j;
                break;
            }
        }
    }
}

extern void _UnitMatrix(float *m);
extern void _MulMatrix(float *out, float *a, float *b);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern float *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_TransMatrixV(VECTOR *v);
extern void MatrixDrive_RotMatrixY(short rot);
extern void MatrixDrive_SetTransposeMatrix(float *out, float *m);
extern void CopyMatrix(float *out, float *m);

/* census: the rows 52-63 that appear twice inside GetStageDifferenceMatrix and
   again in StageOrientGet2 are a static inline with no standalone copy in the
   listing, so the listing carries no name for it. */
static inline void MakeStageOrientMatrix(float *m, StageOrientDef *p)
{
    /* ROM's frame proves a second 16-byte local ahead of `v` here: every caller
       that inlines this helper carries an unwritten 16-byte slot immediately
       below `v` (sp+0xC0 in GetStageDifferenceMatrix, sp+0x00 in
       StageOrientGet2) and gcc materialises that slot's address as the base
       register for the aggregate temp. */
    VECTOR unused;
    VECTOR v = {p->pos[0], p->pos[1], p->pos[2], 1.0f};

    MatrixDrive_PushMatrix();
    _UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrixV(&v);
    MatrixDrive_RotMatrixY((short)(p->angle * 10430.37793f));
    CopyMatrix(m, MatrixDrive_GetMatrix());
    MatrixDrive_PopMatrix();
}

int GetStageDifferenceMatrix(float *out, int stA, int stB)
{
    int a = D_006EA800[stA];
    int b = D_006EA800[stB];
    StageOrientDef *pa;
    StageOrientDef *pb;
    float m1[16];
    float m2[16];
    float mt[16];

    if (a < 0 || b < 0) {
        _UnitMatrix(out);
        return 0;
    }

    pa = &D_00556E50[a];
    pb = &D_00556E50[b];

    MakeStageOrientMatrix(m1, pa);
    MakeStageOrientMatrix(m2, pb);

    MatrixDrive_SetTransposeMatrix(mt, m1);
    _MulMatrix(out, mt, m2);
    return 1;
}

inline int StageOrientGet(VECTOR *ret, int stA, int stB)
{
    int a = D_006EA800[stA];
    int b = D_006EA800[stB];

    if (a < 0 || b < 0) {
        ret->x = 1.0f;
        ret->y = 0.0f;
        ret->z = 0.0f;
        ret->w = 1.0f;
        return 0;
    }
    {
        StageOrientDef *pa = &D_00556E50[a];
        float *va = pa->pos;
        float *vb = D_00556E50[b].pos;
        float m[16];
        VECTOR d = {vb[0] - va[0], vb[1] - va[1], vb[2] - va[2], 1.0f};

        sceVu0Normalize(ret, &d);

        sceVu0UnitMatrix(m);
        sceVu0RotMatrixY(m, m, pa->angle);
        sceVu0InversMatrix(m, m);
        sceVu0ApplyMatrix(ret, m, ret);
    }
    ret->y = -ret->y;
    return 1;
}

extern void sceVu0SubVector(VECTOR *out, VECTOR *a, VECTOR *b);

int StageOrientGet2(VECTOR *ret, int stA, VECTOR *posA, int stB, VECTOR *posB)
{
    int a = D_006EA800[stA];
    int b = D_006EA800[stB];

    if (a < 0 || b < 0) {
        ret->x = 1.0f;
        ret->y = 0.0f;
        ret->z = 0.0f;
        ret->w = 1.0f;
        return 0;
    }
    {
        StageOrientDef *pa = &D_00556E50[a];
        StageOrientDef *pb = &D_00556E50[b];
        VECTOR va = {posA->x, -posA->y, posA->z, 1.0f};
        VECTOR vb = {posB->x, -posB->y, posB->z, 1.0f};
        VECTOR ta;
        float m1[16];
        float m2[16];
        VECTOR tb;
        float m3[16];

        sceVu0UnitMatrix(m1);
        sceVu0RotMatrixY(m1, m1, pa->angle);
        m1[12] = pa->pos2[0];
        m1[13] = pa->pos2[1];
        m1[14] = pa->pos2[2];
        m1[15] = 1.0f;
        sceVu0ApplyMatrix(&ta, m1, &va);

        sceVu0UnitMatrix(m2);
        sceVu0RotMatrixY(m2, m2, pb->angle);
        m2[12] = pb->pos2[0];
        m2[13] = pb->pos2[1];
        m2[14] = pb->pos2[2];
        m2[15] = 1.0f;
        sceVu0ApplyMatrix(&tb, m2, &vb);

        sceVu0SubVector(ret, &tb, &ta);

        sceVu0UnitMatrix(m3);
        sceVu0RotMatrixY(m3, m3, pa->angle);
        sceVu0InversMatrix(m3, m3);
        sceVu0ApplyMatrix(ret, m3, ret);
        sceVu0Normalize(ret, ret);
    }
    ret->y = -ret->y;
    return 1;
}

int OtherStagePositionGet(VECTOR *ret, int stA, int stB, VECTOR *pos)
{
    int a = D_006EA800[stA];
    int b = D_006EA800[stB];

    if (a < 0 || b < 0) {
        ret->x = 0.0f;
        ret->y = 0.0f;
        ret->z = 0.0f;
        ret->w = 1.0f;
        return 0;
    }
    {
        StageOrientDef *pa = &D_00556E50[a];
        StageOrientDef *pb = &D_00556E50[b];
        VECTOR v = {pos->x, -pos->y, pos->z, 1.0f};
        VECTOR t;
        float m1[16];
        float m2[16];
        float m3[16];

        sceVu0UnitMatrix(m1);
        sceVu0RotMatrixY(m1, m1, pb->angle);
        m1[12] = pb->pos2[0];
        m1[13] = pb->pos2[1];
        m1[14] = pb->pos2[2];
        m1[15] = 1.0f;
        sceVu0ApplyMatrix(&t, m1, &v);

        sceVu0UnitMatrix(m2);
        sceVu0RotMatrixY(m2, m2, pa->angle);
        m2[12] = pa->pos2[0];
        m2[13] = pa->pos2[1];
        m2[14] = pa->pos2[2];
        m2[15] = 1.0f;
        sceVu0InversMatrix(m3, m2);
        sceVu0ApplyMatrix(ret, m3, &t);
    }
    ret->y = -ret->y;
    return 1;
}
