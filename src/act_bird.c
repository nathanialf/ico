#include "common.h"



extern void func_00243B60(void *dst, void *src);
extern int InitParticleLayoutGeo();
extern int iosOmBeforeFuncStandard();
extern int D_00631990;
extern void DrawLightningN(void);
extern void func_0010ECC0(void *a0);
extern int stage_CheckAnimationFrameIn(void *a0);

void interp_vector_sa(void *a0) {
    int *r;
    func_0010ECC0(a0);
    r = *(int **)(*(char **)((char *)a0 + 0x15C) + 0x800);
    if (r[0xC] != 0) {
        if (stage_CheckAnimationFrameIn(r + 0xC) != 0) {
            r[0xC] = 0;
        }
    }
    if (D_00631990 == 0x52) {
        DrawLightningN();
    }
}

void birdBeforeFunc(int a0, int a1, int a2, int a3)
{
    iosOmBeforeFuncStandard(a0, a1, a2, a3);
}

extern float D_00631038;
extern float func_00243950(void *a0, void *a1);
extern void func_00243978(void *dst, void *src);
extern float func_0025E3D8(float a0);

float trans_bird(void *a0, void *a1) {
    float v0[4];
    float v1[4];
    func_00243978(v0, a0);
    func_00243978(v1, a1);
    return func_0025E3D8(func_00243950(v0, v1)) * 360.0f / D_00631038;
}

extern void _ACTWait(int a0);
extern void func_00196F78(void *a0);

void subBirdBrainMain(void * volatile a0) {
    _ACTWait(1);
    for (;;) {
        func_00196F78(a0);
        _ACTWait(1);
    }
}

void func_00197198(void * volatile a0) {
    _ACTWait(1);
    for (;;) {
        _ACTWait(1);
    }
}

extern void *actInitialize(void *a0);
extern void actCreateSubThread(void *entry, int prio);
extern void *ExecMotionOrient(void *a0, int a1, void *a2);
extern void IsPointIsInScreen(void *a0);

void func_001971C0(void *a0) {
    void *s = actInitialize(a0);
    _ACTWait(1);
    actCreateSubThread(IsPointIsInScreen, 0x14);
    actCreateSubThread(subBirdBrainMain, 0x15);
    actCreateSubThread(func_00197198, 0x15);
    *(void **)((char *)s + 0x120) = ExecMotionOrient(a0, 0xEE, (char *)s + 0x610);
}

INCLUDE_ASM("asm/nonmatchings/src/act_bird", Debug_WireString_Bird);

void Debug_StickControl(void) {}

extern void birdBeforeFunc__p4(void *a0, void *a1, void *a2) __asm__("birdBeforeFunc");
extern void *isysGObjSearchFromObjKindID_begin(void *o);
extern void *isysGObjSearchFromObjLayoutID(int id);

void BirdGeo(void *a0, void *a1) {
    void *obj = isysGObjSearchFromObjLayoutID(0x20);
    while (obj != 0) {
        birdBeforeFunc__p4(obj, a0, a1);
        obj = isysGObjSearchFromObjKindID_begin(obj);
    }
}

void BirdDL(int a0, int a1)
{
    if (a0 >= 0) {
        int v;
        v = InitParticleLayoutGeo(a0);
        func_00243B60(v + 0x40, a1);
    }
}

