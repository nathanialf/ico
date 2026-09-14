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
extern float D_0063945C;

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
    sceVu0ScaleVector(v, v, t * D_0063945C / *(float *)(w + 0x38));

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

INCLUDE_ASM("asm/nonmatchings/src/cage", InitCageGeo);

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

INCLUDE_ASM("asm/nonmatchings/src/cage", CageGeo);

extern void p2o_DispVU1(void *a0);
extern void p2o_DispVU1DObjMulti(void *a0);

void CageDL(char *self)
{
    char *w = *(char **)(*(char **)(self + 0x15C) + 0x830);

    p2o_DispVU1(self);
    p2o_DispVU1DObjMulti(*(void **)w);
}
