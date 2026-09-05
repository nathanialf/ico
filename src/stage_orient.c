#include "common.h"

typedef struct {
    char  name[16];
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
INCLUDE_ASM("asm/nonmatchings/src/stage_orient", GetStageDifferenceMatrix);
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
        VECTOR d = { vb[0] - va[0], vb[1] - va[1], vb[2] - va[2], 1.0f };

        sceVu0Normalize(ret, &d);

        sceVu0UnitMatrix(m);
        sceVu0RotMatrixY(m, m, pa->angle);
        sceVu0InversMatrix(m, m);
        sceVu0ApplyMatrix(ret, m, ret);
    }
    ret->y = -ret->y;
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/stage_orient", StageOrientGet2);
INCLUDE_ASM("asm/nonmatchings/src/stage_orient", OtherStagePositionGet);
