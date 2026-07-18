#include "common.h"

typedef struct ActB4Obj {
    char pad[0xB4];
    int *unkB4;
} ActB4Obj;
extern int actInitialize(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int func_00178DB0(int a0);

extern void _ACTWait(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void scpPlayStart(int a0, void *a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void func_0012AAB8(int a0, int a1);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, void *a2, int a3);
extern int func_0012A958(int a0);
extern int D_0062A894;
extern int D_0062BE00;
struct Q { long long a, b; };
extern struct Q D_00614E30;

void actExplode(volatile int a0) {
    struct Q buf;
    while (scpSleepEnemyOne(a0, actSt25aQueenDeadChk(0x6F2), 220.0f) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    func_00178DD8(0x11B);
    scpPlayStart(0x4A, &D_0062BE00, 1, 1, 1);
    while (D_0062BE00 == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x3C);
    stage_KillPlayBgAnimation(0x78, 1, 0);
    _ACTWait(0x5A);
    stage_KillPlayBgAnimation(0x76, 1, 0);
    stage_KillPlayBgAnimation(0x77, 1, 0);
    *(int *)(actSt25aQueenDeadChk(0x6F2) + 0x16C) = 0;
    *(int *)(actSt25aQueenDeadChk(0x6F1) + 0x16C) = 1;
    func_0012AAB8(0x76, 1);
    func_0012AAB8(0x77, 1);
    buf = D_00614E30;
    soundSeDefPlayWithVolumeRate(0x52B, 0, &buf, 1);
    soundSeDefPlayWithVolumeRate(0x52C, 0, &buf, 1);
    soundSeDefPlayWithVolumeRate(0x52D, 0, &buf, 1);
    while (func_0012A958(0x78) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0062A894 = 0;
    lt_fade_status(0x32);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actSplash1);


#include "common.h"
extern void lt_fade_status(int a0);
extern void _ACTWait(int a0);
extern void scpPlayStart(int a0, void *a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void func_00178DD8(int a0);
extern void func_0018A380(void);
extern int func_0012AA28(int a0, int a1, int a2);
extern int actSt25aQueenDeadChk(int a0);
extern void scpTrans(int a0, int a1);
extern int D_0062BE08;
extern int D_0062A894;
void actSplash2(volatile int a0) {
    lt_fade_status(0x33);
    _ACTWait(0x3C);
    scpPlayStart(0x5F, &D_0062BE08, 1, 1, 1);
    while (D_0062BE08 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x7B, 1, 0);
    func_00178DD8(0x11D);
    func_0018A380();
    while (func_0012AA28(0x7B, 0xF0, 1) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x6F4) + 0x16C) = 1;
    stage_KillPlayBgAnimation(0x7B, 0, 0x169);
    if (D_0062BE08 != 0) {
        scpTrans(D_0062BE08, 0x100);
    }
    D_0062A894 = 0;
    lt_fade_status(0x32);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actWave);


extern void warpGirlInStage(float a0, float a1, float a2);
extern float D_006299EC, D_006299F0, D_006299F4;
extern int D_004CE600[];
extern void actSplash2Chk(volatile int a0);
void actSpider(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    warpGirlInStage(*(volatile float *)&D_006299EC, *(volatile float *)&D_006299F0, *(volatile float *)&D_006299F4);
    if (func_00178DB0(0x11A) != 0) {
        stage_KillPlayBgAnimation(0x79, 0, 0x59);
    } else {
        stage_KillPlayBgAnimation(0x79, 0, 0);
    }
    D_004CE600[1] = (int)actSplash2Chk;
    gobj->unkB4 = D_004CE600;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, void *a2, int a3);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
typedef struct { long a, b; } S16;
extern S16 D_00614E20;
void actDevilLightning(volatile int a0) {
    S16 buf;
    int x = a0;
    actInitialize(a0); _ACTWait(1);
    buf = D_00614E20;
    soundSeDefPlayWithVolumeRate(0x52A, 0, &buf, 1);
    stage_KillPlayBgAnimation(0x79, 0, 0);
}

extern int D_004CE6A0[];
extern void actSplash1(int a0);
void actQueenLightning(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x11C) == 0) {
        *(int *)(actSt25aQueenDeadChk(0x6F0) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0x7A, 0, 0);
        D_004CE6A0[1] = (int)actSplash1;
        gobj->unkB4 = D_004CE6A0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        *(int *)(actSt25aQueenDeadChk(0x6EF) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0x7A, 0, -1);
    }
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt27aWave(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x11C) == 0) {
        stage_KillPlayBgAnimation(0x7A, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x7A, 0, -1);
    }
}

extern void actWave1(int a0);
extern int D_004CE6E0[];
void actExplodeChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x11D) == 0) {
        *(int *)(actSt25aQueenDeadChk(0x6F4) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0x7B, 0, 0);
    }
    D_004CE6E0[1] = (int)actWave1;
    gobj->unkB4 = D_004CE6E0;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


extern int D_004CE760[];
extern void actSt27aWaveChk(volatile int a0);
void actSplash1Chk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x11E) == 0) {
        D_004CE760[1] = (int)actSt27aWaveChk;
        gobj->unkB4 = D_004CE760;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CE5E0[];

void actSplash2Chk(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_0062A894 = 0;
    *(int *)(gobj + 0xB0) = (int)D_004CE5E0;
    for (;;) {
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", func_00234040);

#include "common.h"
extern void lt_fade_status(int a0);
extern void _ACTWait(int a0);
extern void scpPlayStart(int a0, void *a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void func_00178DD8(int a0);
extern int func_0012AA28(int a0, int a1, int a2);
extern void scpTrans(int a0, int a1);
extern int D_0062BDF8;
extern int D_0062A894;
void actWaveChk(volatile int a0) {
    lt_fade_status(0x33);
    _ACTWait(0x3C);
    scpPlayStart(0x48, &D_0062BDF8, 1, 1, 1);
    while (D_0062BDF8 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x79, 1, 0);
    func_00178DD8(0x11A);
    while (func_0012AA28(0x79, 0x59, 1) == 0) { _ACTWait(1); }
    _ACTWait(1);
    _ACTWait(0x78);
    if (D_0062BDF8 != 0) {
        scpTrans(D_0062BDF8, 0x100);
    }
    D_0062A894 = 0;
    lt_fade_status(0x32);
}

extern int D_004CE6C0[];

void actWave1(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_0062A894 = 0;
    *(int *)(gobj + 0xB0) = (int)D_004CE6C0;
    for (;;) {
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", func_002341E0);

#include "common.h"
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern int D_00629DE4;
extern int D_0062A894;
void actSt27aWaveChk(volatile int a0) {
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x1000000) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    func_00178DD8(0x11E);
    stage_KillPlayBgAnimation(0x74, 1, 0);
    while (func_0012A958(0x74) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_0062A894 = 0;
}

extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void AddWayPointTop(int a0, int a1);

void actSt27aWave1(void) {
    if (func_00178DB0(0x11F) == 0) {
        stage_KillPlayBgAnimation(0x7F, 0, 0);
        AddWayPointTop(4, 0);
    } else {
        stage_KillPlayBgAnimation(0x7F, 0, -1);
        AddWayPointTop(4, 1);
    }
}

extern int D_00629DE8;
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);

void actSpiderChk(void) {
    if (D_00629DE8) {
        if (func_00178DB0(0x11F)) {
            if (!func_00178DB0(0x122)) {
                func_00178DD8(0x165);
            }
        }
    }
}

extern void scpDispOnAllWithKind(void);
extern void func_00178E08(int a0);
extern int iosPadDevRead(int a0, int a1);
extern void Shock_Request(int a0, int a1);
extern void Vibration_ShotDecode(int a0);
extern void AddWayPointTop(int a0, int a1);
extern void scpActivateAllWithKind(void);
extern int D_0062BE0C;
extern int D_00629DEC;
extern int D_0062BE18;
extern unsigned char D_0062BE1C;
void func_002343C0(volatile int a0) {
    int pad;
    lt_fade_status(0x33);
    scpDispOnAllWithKind();
    func_00178DD8(0x11F);
    func_00178E08(0x165);
    _ACTWait(0x1E);
    scpPlayStart(0x45, &D_0062BE0C, 1, 1, 1);
    while (D_0062BE0C == 0) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0x7F, 1, 0);
    pad = iosPadDevRead(D_00629DEC, 9);
    D_0062BE1C = 0x80;
    D_0062BE18 = pad;
    Shock_Request(pad, 0x80);
    while (func_0012A958(0x7F) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Vibration_ShotDecode(D_0062BE18);
    AddWayPointTop(4, 1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}


extern void jimakuMgrJump(int a0);
extern void jimakuMgrEnd(void);
extern int func_0012AA28(int a0, int a1, int a2);
extern int iosPadDevRead(int a0, int a1);
extern void scpTrans(int a0, int a1);
extern int scpTriggerBallTargetMan(int a0);
extern int D_00629DE4;
extern int D_0062BE14;
extern int D_00629DEC;
extern int D_004CE860[];
extern void stageSE04ewind(int a0);
void func_002344C0(volatile int a0) {
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    jimakuMgrJump(D_00629DE4);
    scpPlayStart(0x43, &D_0062BE14, 1, 1, 1);
    while (D_0062BE14 == 0) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0x7E, 1, 0);
    func_00178DD8(0x120);
    while (func_0012AA28(0x7E, 0x96, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x11);
    while (func_0012AA28(0x7E, 0x1F4, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x10);
    if (D_0062BE14 != 0) {
        scpTrans(D_0062BE14, 0x100);
    }
    while (scpTriggerBallTargetMan(D_0062BE14) != 0) {
        _ACTWait(1);
    }
    jimakuMgrEnd();
    D_004CE860[1] = (int)stageSE04ewind;
    obj->unkB4 = D_004CE860;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


extern int func_0012AA28(int a0, int a1, int a2);
extern void func_00178E08(int a0);
extern int iosPadDevRead(int a0, int a1);
extern void scpTrans(int a0, int a1);
extern int scpTriggerBallTargetMan(int a0);
extern int D_0062BE10;
extern int D_00629DEC;
extern int D_004CE880[];
extern void stageSE04ewind(int a0);
void func_00234640(volatile int a0) {
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    scpPlayStart(0x44, &D_0062BE10, 1, 1, 1);
    while (D_0062BE10 == 0) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0x7E, 1, 0x1F4);
    func_00178E08(0x120);
    while (func_0012AA28(0x7E, 0x334, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x11);
    while (func_0012AA28(0x7E, 0x3E8, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x10);
    if (D_0062BE10 != 0) {
        scpTrans(D_0062BE10, 0x100);
    }
    while (scpTriggerBallTargetMan(D_0062BE10) != 0) {
        _ACTWait(1);
    }
    D_004CE880[1] = (int)stageSE04ewind;
    obj->unkB4 = D_004CE880;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


extern void AddWayPointTop(int a0, int a1);
extern void scpTorchLightOn(int a0, int a1);
extern void func_00178E08(int a0);
extern int D_004CE8E0[];
extern int D_004CE900[];
extern void stageSEtaimatsu(int a0);
extern void stageSE04eriver(int a0);
void func_002347A8(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x119) == 0) {
        AddWayPointTop(0x13, 1);
        *(int *)(actSt25aQueenDeadChk(0x730) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x731) + 0x16C) = 0;
        scpTorchLightOn(0x72E, 0x80);
        stage_KillPlayBgAnimation(0x80, 0, 0x1E);
        D_004CE8E0[1] = (int)stageSEtaimatsu;
        gobj->unkB4 = D_004CE8E0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        AddWayPointTop(0x13, 0);
        *(int *)(actSt25aQueenDeadChk(0x72E) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x72F) + 0x16C) = 0;
        func_00178E08(0x119);
        scpTorchLightOn(0x730, 0x80);
        stage_KillPlayBgAnimation(0x80, 0, 0);
        D_004CE900[1] = (int)stageSE04eriver;
        gobj->unkB4 = D_004CE900;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", func_002348D8);

