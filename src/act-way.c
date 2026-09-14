#include "common.h"

extern int ACTCheckCollis_WAY(void *a0, void *a1, float a2, void *a3, void *a4);
/* prototypes: their order is the inline tail's emission order */
int WayMove_CheckCollis(float *p0, float *p1, void *a2, void *a3);

INCLUDE_ASM("asm/nonmatchings/src/act-way", DetourCheck);
INCLUDE_ASM("asm/nonmatchings/src/act-way", checkPositionIllegal);

inline int WayMove_CheckCollis(float *p0, float *p1, void *a2, void *a3)
{
    float a[4];
    float b[4];

    a[0] = p0[0];
    a[1] = p0[1];
    a[2] = p0[2];
    b[0] = p1[0];
    b[1] = p1[1];
    b[2] = p1[2];
    a[1] -= 50.0f;
    b[1] -= 50.0f;
    return ACTCheckCollis_WAY(a, b, 10.0f, a2, a3);
}

INCLUDE_ASM("asm/nonmatchings/src/act-way", ACTWayMove_BeginDetail);
INCLUDE_ASM("asm/nonmatchings/src/act-way", ACTWayMove_NextDetail);
INCLUDE_ASM("asm/nonmatchings/src/act-way", ACTWayExec_Position);

extern void *test_CURRENTROOT(void);
extern float _DistxzSqGV(void *a, void *b);

int ACTWay_IsMustWalkFromWay(char *a0)
{
    char *w = *(char **)(*(char **)(a0 + 0x164) + 0x380);
    float d;

    if (w == 0) {
        return 0;
    }
    d = *(float *)(w + 0x2C);
    if (d != 0.0f) {
        return _DistxzSqGV(w + 0x10, test_CURRENTROOT()) < d * d;
    }
    return 0;
}

void ACTWay_SetBeginPositionIllegal(char *a0)
{
    char *p = *(char **)(a0 + 0x164);
    *(long long *)(p + 0x438) |= 0x200000;
}
