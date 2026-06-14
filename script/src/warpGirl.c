#include "common.h"

/* warpGirl 0x164 actor-state view (local) */
typedef struct { char _0[0x20]; long f_20; } WarpState;

extern int execNormalMove(void);

int warpGirlOutStage(void) {
    return execNormalMove() != 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", warpGirlInStage);

extern float D_006C9220[];

void warpGirlInit(float *a0) {
    a0[0] = D_006C9220[0];
    a0[1] = D_006C9220[1];
    a0[2] = D_006C9220[2];
}

extern void *D_00629DE4;

void func_0017C0B8(void) {
    void *o = D_00629DE4;
    if (o) {
        WarpState *s = *(WarpState **)((char *)o + 0x164);
        s->f_20 &= -0x201;
    }
}

void func_0017C0E0(void) {
    void *o = D_00629DE4;
    if (o) {
        WarpState *s = *(WarpState **)((char *)o + 0x164);
        s->f_20 |= 0x200;
    }
}

void func_0017C108(void) {
    void *o = D_00629DE4;
    if (o) {
        WarpState *s = *(WarpState **)((char *)o + 0x164);
        s->f_20 &= -0x401;
    }
}

extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void GetCylinderCollisionWithExceptOwnCollision(void *a0, void *a1);

void func_0017C130(void *a0, float f12, float f13, float f14) {
    float buf[4];
    GetRootMatrixByDObj(buf, a0);
    buf[0] = buf[0] + f12;
    buf[1] = buf[1] + f13;
    buf[2] = buf[2] + f14;
    GetCylinderCollisionWithExceptOwnCollision(a0, buf);
}

extern void *isysGObjSearchFromObjLayoutID(int id);
extern void *isysGObjSearchFromObjKindID_begin(void *o);
extern int Draw2DLineSeg_Start(void *o);
extern int func_001D1438(void *o);
extern void ItemDL(void *o);

void func_0017C1B0(void) {
    void *o = isysGObjSearchFromObjLayoutID(0x13);
    while (o) {
        if (Draw2DLineSeg_Start(o) == 6 && func_001D1438(o) == 0) {
            ItemDL(o);
            return;
        }
        o = isysGObjSearchFromObjKindID_begin(o);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C230);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C308);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C3D0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C560);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C658);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C910);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017CE38);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017D318);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017D560);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DA68);

extern void func_0012FEC8(void *a0, float a1, float a2, float a3, float a4, float a5, float a6, int a7);
extern char D_00554540[];
extern float D_00629198;

void func_0017DC10(void) {
    func_0012FEC8(D_00554540, 0.0f, 0.0f, 0.0f, D_00629198, 0.0f, 0.5f, 1);
}

extern void Generator_Mask(int a0);

void func_0017DC40(volatile int a0) {
    Generator_Mask(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DC68);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DCE0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DD70);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DDD8);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void scpTorchLightOn(int a0, int a1);

void func_0017DE40(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    scpTorchLightOn(0x76E, 0x1A6);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DE80);

extern int D_0062A8B0;
extern int D_00286840[];
extern int scpSleepSpiderGroupOne(void *a0, int a1);
extern void func_00178DD8(int a0);
extern void func_00174698(void *a0);
extern int scpPlayStart(int a0, void *a1, int a2, int a3, int a4);

void func_0017DEE8(int a0) {
    volatile int x;
    x = a0;
    D_0062A8B0 = 0;
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x1000000) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0x12C);
    func_00174698(D_00286840);
    scpPlayStart(0x26, &D_0062A8B0, 1, 1, 0);
}
