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

int checkPositionIllegal(void *a0, Vec3 *a1) {
    float buf1[4];
    float buf2[4];
    float f2;
    if ((*(CheckSub **) ((char *) a0 + 0x164))->f30 != 0x6C) {
        buf1[0] = a1->f0;
        buf1[1] = a1->f4;
        buf1[2] = a1->f8;
        debug_Marker(buf1, 0, 0xFF, 0, 100.0f);
        buf2[0] = ContinueCorrectPosition(a0)->f0;
        buf2[1] = ContinueCorrectPosition(a0)->f4;
        buf2[2] = ContinueCorrectPosition(a0)->f8;
        buf2[1] -= CheckPureWallAttribute(a0, 0x2C);
        debug_Marker(buf2, 0, 0, 0xFF, 100.0f);
        f2 = buf1[1] - buf2[1];
        if (f2 < 0.0f) {
            if (-f2 > 40.0f) {
                return 1;
            }
        } else if (f2 > 40.0f) {
            return 1;
        }
    }
    return 0;
}



INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-way", ACTWayMove_BeginDetail);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-way", ACTWayMove_NextDetail);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-way", ACTWayExec_Position);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-way", ACTWay_IsMustWalkFromWay);

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
