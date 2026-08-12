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

void birdBeforeFunc(a0, a1, a2, a3)
int a0, a1, a2, a3;
{
    iosOmBeforeFuncStandard(a0, a1, a2, a3);
}

extern float func_00243950(void *a0, void *a1);
extern void func_00243978(void *dst, void *src);
extern float func_0025E3D8(float a0);

float trans_bird(void *a0, void *a1) {
    float v0[4];
    float v1[4];
    func_00243978(v0, a0);
    func_00243978(v1, a1);
    return func_0025E3D8(func_00243950(v0, v1)) * 360.0f / 6.2831855f;
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

extern void *func_0013A0F8(int heap, int size, const char *file, int line);
extern char D_0055AFD8[];
extern void func_002641D8(void *a0, int a1, int a2);
extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);
extern void func_001E4798(void *a0, int a1, int a2, int a3, int a4, int a5);
extern void func_001D4B40(void *a0, int a1);
extern int D_00632010;
extern float pac_DispQW(void);

#define BIRD_HDR(o) (*(volatile int *)((char *)(o) + 0x15C))

void *Debug_WireString_Bird(void *a0, void *a1) {
    void *obj = func_0013A0F8(D_00632010, 0x40, D_0055AFD8, 0x3D2);
    func_002641D8(obj, 0, 0x40);
    MatrixDrive_TurnObjectMatrix(obj, a1);
    *(char *)((char *)obj + 0x10) = 0;
    func_001E4798(a0, 0x847, 0x875, -1, -1, 0x431);
    *(int *)(BIRD_HDR(a0) + 0x544) = 1;
    *(int *)(BIRD_HDR(a0) + 0x54C) = 0;
    *(int *)(BIRD_HDR(a0) + 0x548) = 1;
    *(int *)(BIRD_HDR(a0) + 0x550) = 0;
    *(volatile float *)(BIRD_HDR(a0) + 0x4AC) = pac_DispQW() * 100.0f;
    {
        int hdr = BIRD_HDR(a0);
        *(volatile float *)(hdr + 0x4B0) = *(volatile float *)(hdr + 0x4AC);
    }
    *(int *)(BIRD_HDR(a0) + 0x4C4) = 0;
    func_001D4B40(a0, 3);
    return obj;
}

void Debug_StickControl(void) {}

extern void *isysGObjSearchFromObjKindID_begin(void *o);
extern void *isysGObjSearchFromObjLayoutID(int id);

void BirdGeo(void *a0, void *a1) {
    void *obj = isysGObjSearchFromObjLayoutID(0x20);
    while (obj != 0) {
        birdBeforeFunc(obj, a0, a1);
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

