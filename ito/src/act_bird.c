#include "common.h"

extern void func_0010F050(void *a0);
extern int stage_CheckAnimationFrameIn(void *a0);
extern void DrawLightningN(void);
extern int D_00629C90;

void interp_vector_sa(void *a0) {
    int *r;
    func_0010F050(a0);
    r = *(int **)(*(char **)((char *)a0 + 0x15C) + 0x7F0);
    if (r[0xC] != 0) {
        if (stage_CheckAnimationFrameIn(r + 0xC) != 0) {
            r[0xC] = 0;
        }
    }
    if (D_00629C90 == 0x52) {
        DrawLightningN();
    }
}

extern void iosOmBeforeFuncStandard(void *a0);

void birdBeforeFunc(void *a0, void *a1, void *a2) {
    iosOmBeforeFuncStandard(a0);
}

extern void func_0023FE98(void *dst, void *src);
extern float func_0023FE70(void *a0, void *a1);
extern float func_0025A768(float a0);
extern float D_00629330;

float trans_bird(void *a0, void *a1) {
    float v0[4];
    float v1[4];
    func_0023FE98(v0, a0);
    func_0023FE98(v1, a1);
    return func_0025A768(func_0023FE70(v0, v1)) * 360.0f / D_00629330;
}

extern void func_001946F8(void *a0);
extern void *actInitialize(void);
extern void actCreateSubThread(void *entry, int prio);
extern void *ExecMotionOrient(void *a0, int a1, void *a2);
extern void IsPointIsInScreen(void *a0);

void subBirdBrainMain(void * volatile a0) {
    _ACTWait(1);
    for (;;) {
        void *p = a0;
        func_001946F8(a0);
        _ACTWait(1);
    }
}

static void subBirdBrainSub(void * volatile a0) {
    _ACTWait(1);
    for (;;) {
        _ACTWait(1);
    }
}

void BirdBrainMain(void *a0) {
    void *s = actInitialize();
    _ACTWait(1);
    actCreateSubThread(IsPointIsInScreen, 0x14);
    actCreateSubThread(subBirdBrainMain, 0x15);
    actCreateSubThread(subBirdBrainSub, 0x15);
    __asm__("" : : "r"(a0));
    *(void **)((char *)s + 0x110) = ExecMotionOrient(a0, 0xEC, (char *)s + 0x610);
}

extern void *iosFree(int heap, int size, const char *file, int line);
extern void func_00260568(void *a0, int a1, int a2);
extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);
extern void func_001E1A18(void *a0, int a1, int a2, int a3, int a4, int a5);
extern int D_0062A310;
extern float pac_DispQW(void);

#define BIRD_HDR(o) (*(volatile int *)((char *)(o) + 0x15C))

void *Debug_WireString_Bird(void *a0, void *a1) {
    void *obj = iosFree(D_0062A310, 0x40, "src/act_bird.c", 0x3BF);
    func_00260568(obj, 0, 0x40);
    MatrixDrive_TurnObjectMatrix(obj, a1);
    *(char *)((char *)obj + 0x10) = 0;
    func_001E1A18(a0, 0x82E, 0x85A, -1, -1, 0x433);
    *(int *)(BIRD_HDR(a0) + 0x534) = 1;
    *(int *)(BIRD_HDR(a0) + 0x53C) = 0;
    *(int *)(BIRD_HDR(a0) + 0x538) = 1;
    *(int *)(BIRD_HDR(a0) + 0x540) = 0;
    *(volatile float *)(BIRD_HDR(a0) + 0x49C) = pac_DispQW() * 100.0f;
    {
        int hdr = BIRD_HDR(a0);
        *(volatile float *)(hdr + 0x4A0) = *(volatile float *)(hdr + 0x49C);
    }
    *(int *)(BIRD_HDR(a0) + 0x4B4) = 0;
    return obj;
}

void Debug_StickControl(void) {
}

extern void *isysGObjSearchFromObjLayoutID(int id);
extern void *isysGObjSearchFromObjKindID_begin(void *o);

void BirdGeo(void *a0, void *a1) {
    void *obj = isysGObjSearchFromObjLayoutID(0x20);
    while (obj != 0) {
        birdBeforeFunc(obj, a0, a1);
        obj = isysGObjSearchFromObjKindID_begin(obj);
    }
}

extern void *InitParticleLayoutGeo(void);
extern void func_00240080(void *a0, void *a1);

void BirdDL(int a0, void *a1) {
    if (a0 >= 0) {
        void *r = InitParticleLayoutGeo();
        func_00240080((char *)r + 0x40, a1);
    }
}
