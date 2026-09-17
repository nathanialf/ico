#include "common.h"

/* kept local: this TU's uses of ACTCheckCollis_WAY do not fit the prototype in act-game.h */
extern int ACTCheckCollis_WAY(void *a0, void *a1, float a2, void *a3, void *a4);

#include "act-way.h"

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/act-way", DetourCheck);

/* the 0x194-byte enemy parameter rows, the same record ico2/fumi/src/enemy_act
   reads the 0x18C flag word out of */
typedef struct {
    char pad00[0x18C];
    unsigned int flags18C; /* 0x18C */
    char pad190[4];
} EnemyParaRow;

extern EnemyParaRow D_0055FE58[];
/* kept local: this TU's uses of test_CURRENTROOT do not fit the prototype in commonact.h */
extern float *test_CURRENTROOT();
extern void debug_NMarker(float *pos, int r, int g, int b, float size);
extern float GetDifferenceFromLastField(char *self, int a1);

int checkPositionIllegal(char *self, float *pos)
{
    float v[4];
    float r[4];
    float dy;
    char *act = *(char **)(self + 0x164);

    if (*(int *)(act + 0x34) == 0x70) {
        return 1;
    }
    if (*(int *)(act + 0x34) == 0x26 ||
        ((((EnemyParaRow *)((char *)D_0055FE58 +
                            *(int *)(*(char **)(self + 0x15C) + 0x4A0) * 0x194))
              ->flags18C >>
          12) &
         1)) {
        return 1;
    }
    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    debug_NMarker(v, 0, 255, 0, 100.0f);
    r[0] = test_CURRENTROOT(self)[0];
    r[1] = test_CURRENTROOT(self)[1];
    r[2] = test_CURRENTROOT(self)[2];
    r[1] = r[1] - GetDifferenceFromLastField(self, 0x2C);
    debug_NMarker(r, 0, 0, 255, 100.0f);
    dy = v[1] - r[1];
    if (dy < 0.0f) {
        if (-dy > 40.0f) {
            return 1;
        }
        return 0;
    }
    return dy > 40.0f;
}

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

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/act-way", ACTWayMove_BeginDetail);
INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/act-way", ACTWayMove_NextDetail);
INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/act-way", ACTWayExec_Position);

/* kept local: this TU's uses of _DistxzSqGV do not fit the prototype in gv.h */
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
