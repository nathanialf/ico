#include "common.h"

/* act-way 0x164 actor-state view (local) */
typedef struct { char _0[0x428]; long long f_428; } AWayState;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-way", DetourCheck);

typedef struct { float f0, f4, f8; } Vec3;
typedef struct {
    float f0, f4, f8;
    char _c[0x30 - 0xc];
    int f30;
} CheckSub;

extern void debug_Marker(void *pos, int r, int g, int b, float size);
extern Vec3 *ContinueCorrectPosition(void *a0);
extern float CheckPureWallAttribute(void *a0, int a1);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-way", checkPositionIllegal);



INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-way", ACTWayMove_BeginDetail);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-way", ACTWayMove_NextDetail);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-way", ACTWayExec_Position);

extern float RotateAccordingToStick_PatternThree(void *a0, void *a1);

int ACTWay_IsMustWalkFromWay(void *a0) {
    char *w = *(char **)(*(char **)((char *)a0 + 0x164) + 0x370);
    float f;
    if (w == 0) goto ret0;
    f = *(float *)(w + 0x2C);
    if (f == 0.0f) goto ret0;
    if (RotateAccordingToStick_PatternThree(w + 0x10, ContinueCorrectPosition(a0)) < f * f)
        return 1;
ret0:
    return 0;
}

void ACTWay_SetBeginPositionIllegal(void *a0) {
    AWayState *p = *(AWayState **)((char *)a0 + 0x164);
    p->f_428 |= 0x200000;
}


/* recovered struct shapes */
typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
} S_004C6FD0;

/* end struct shapes */
