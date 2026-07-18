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

extern float func_00149D00(int a0);
extern int D_005542F0[];

int func_0017C230(int self) {
    int i;
    for (i = 0; D_005542F0[i] != -1; i++) {
        if (*(int *)(self + 0xC) == D_005542F0[i]) {
            int sub = *(int *)(self + 0x15C);
            if (func_00149D00(2) < *(float *)(sub + 0x550)) {
                return 1;
            }
            if (*(int *)(*(int *)(self + 0x164) + 0x30) == 0x16) {
                return 1;
            }
        }
    }
    return 0;
}

extern void _ACTWait(int a0);
typedef struct { char _0[0xB0]; int f_B0; char _b4[0x39C]; int f_450; } Obj0017C308;

void func_0017C308(volatile int a0) {
    Obj0017C308 *p = *(Obj0017C308 **)(a0 + 0x164);
    p->f_B0 = p->f_450;
    for (;;) {
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C338);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C3D0);

extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(void *a0, int a1);
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);
extern void actCreateSubThread(void *fn, int a1);
extern void MakeAttackPack_Actor(volatile int a0);
extern void func_0017C658(volatile int a0);
extern void AdpcmClose(int a0);
extern void *D_00629DE4;
extern int D_0062A8B0;
extern int D_0062A894;
extern int D_00271240[];

void func_0017C560(volatile int a0) {
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x2000000) == 0 || func_00178DB0(0x12C) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0x12D);
    actCreateSubThread(MakeAttackPack_Actor, 0x15);
    while (D_0062A8B0 == 0) {
        _ACTWait(1);
    }
    AdpcmClose(*(int *)(D_0062A8B0 + 0x2C));
    D_0062A894 = 1;
    _ACTWait(((0x3C - D_00271240[0] * 0xA) / D_00271240[1]) * 3);
    actCreateSubThread(func_0017C658, 0x15);
}

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

typedef struct ActB4Obj {
    char pad[0xB4];
    int *unkB4;
} ActB4Obj;
extern int actInitialize(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_002869F0[];
extern void func_0017DEE8(int a0);

void func_0017DC68(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x12C) == 0) {
        D_002869F0[1] = (int)func_0017DEE8;
        gobj->unkB4 = D_002869F0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DCE0);

extern int D_00286A50[];
extern void func_0017D560(volatile int a0);

void func_0017DD70(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    D_00286A50[1] = (int)func_0017D560;
    gobj->unkB4 = D_00286A50;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


extern int D_00286A70[];
extern void AttackMail(volatile int a0);

void func_0017DDD8(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    D_00286A70[1] = (int)AttackMail;
    gobj->unkB4 = D_00286A70;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void scpTorchLightOn(int a0, int a1);

void func_0017DE40(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    scpTorchLightOn(0x76E, 0x1A6);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int actItouQueenAttackChk(void);
extern void scpTorchLightOn(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void func_0017DE80(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (actItouQueenAttackChk() == 5) {
        scpTorchLightOn(0x76E, 0x1A6);
    } else {
        stage_KillPlayBgAnimation(0x1A6, -1, -2);
    }
}

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
