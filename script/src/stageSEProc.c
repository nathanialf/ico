#include "common.h"

typedef struct GObj {
    char pad[0xB4];
    int *unkB4;
} GObj;

extern void _ACTWait(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int actSt25aQueenDeadChk(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float a2);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012AA28(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern void AddWayPointTop(int a0, int a1);
extern void func_00178DD8(int a0);
extern int D_004CE940[];
extern void func_002348D8(volatile int a0);
void stageSEtaimatsu(volatile int a0) {
    GObj *obj = *(GObj **)(a0 + 0x164);
    while (scpSleepEnemyOne(a0, actSt25aQueenDeadChk(0x72E), 5.0f) != 0) { _ACTWait(1); }
    AddWayPointTop(0x13, 0);
    stage_KillPlayBgAnimation(0x80, 1, 0x1F);
    while (func_0012AA28(0x80, 0x28, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    soundSeDefPlayWithVolumeRate(0x522, 0, 0, 1);
    while (func_0012A958(0x80) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_00178DD8(0x124);
    D_004CE940[1] = (int)func_002348D8;
    obj->unkB4 = D_004CE940;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern void _ACTWait(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int actSt25aQueenDeadChk(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float a2);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012AA28(int a0, int a1, int a2);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern void AddWayPointTop(int a0, int a1);
extern void func_00178E08(int a0);
extern int D_004CE960[];
extern void stageSE06ariver(volatile int a0);
void stageSE04eriver(volatile int a0) {
    GObj *obj = *(GObj **)(a0 + 0x164);
    while (scpSleepEnemyOne(a0, actSt25aQueenDeadChk(0x730), 5.0f) == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x80, 1, 0);
    while (func_0012AA28(0x80, 0xA, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    soundSeDefPlayWithVolumeRate(0x522, 0, 0, 1);
    while (func_0012AA28(0x80, 0x1E, 1) == 0) { _ACTWait(1); }
    _ACTWait(1);
    AddWayPointTop(0x13, 1);
    func_00178E08(0x124);
    D_004CE960[1] = (int)stageSE06ariver;
    obj->unkB4 = D_004CE960;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern void _ACTWait(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int actSt25aQueenDeadChk(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float a2);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012AA28(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern void AddWayPointTop(int a0, int a1);
extern void func_00178DD8(int a0);
extern int D_004CE980[];
extern void stageSE04eriver(volatile int a0);
void stageSE06ariver(volatile int a0) {
    GObj *obj = *(GObj **)(a0 + 0x164);
    while (scpSleepEnemyOne(a0, actSt25aQueenDeadChk(0x730), 5.0f) != 0) { _ACTWait(1); }
    AddWayPointTop(0x13, 0);
    stage_KillPlayBgAnimation(0x80, 1, 0x1F);
    while (func_0012AA28(0x80, 0x28, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    soundSeDefPlayWithVolumeRate(0x522, 0, 0, 1);
    while (func_0012A958(0x80) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_00178DD8(0x124);
    D_004CE980[1] = (int)stageSE04eriver;
    obj->unkB4 = D_004CE980;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int func_00178DB0(int a0);
extern int D_004CE7A0[];
extern void stageSE04bstrong(volatile int a0);
void stageSE10lstrong2(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x11F) == 0) {
        D_004CE7A0[1] = (int)stageSE04bstrong;
        gobj->unkB4 = D_004CE7A0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004CE800[];
extern void stageSE04ewind(volatile int a0);
void stageSE19ataki(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x120) != 0) {
        stage_KillPlayBgAnimation(0x7E, 0, 0);
        _ACTWait(0xA);
        stage_KillPlayBgAnimation(0x7E, 0, 0x1F4);
    } else {
        stage_KillPlayBgAnimation(0x7E, 0, 0);
    }
    D_004CE800[1] = (int)stageSE04ewind;
    gobj->unkB4 = D_004CE800;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_004CE8A0[];
extern void stageSE04eriverDown(volatile int a0);
void stageSE02astrong(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    D_004CE8A0[1] = (int)stageSE04eriverDown;
    gobj->unkB4 = D_004CE8A0;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern void func_00178E08(int a0);
extern int actSt25aQueenDeadChk(int a0);
void stageSE02ataki(volatile int a0){ int x=a0; actInitialize(a0); _ACTWait(1);
if(func_00178DB0(0x119)){ *(int*)(actSt25aQueenDeadChk(0x72E) + 0x16C) = 0; *(int*)(actSt25aQueenDeadChk(0x72F) + 0x16C) = 0; func_00178E08(0x119); } else { *(int*)(actSt25aQueenDeadChk(0x730) + 0x16C) = 0; *(int*)(actSt25aQueenDeadChk(0x731) + 0x16C) = 0; } }

extern int func_00178DB0(int a0);
extern int D_004CE8C0[];
extern void stageSE06astrong(volatile int a0);
void stageSE02atakib(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x122) == 0) {
        D_004CE8C0[1] = (int)stageSE06astrong;
        gobj->unkB4 = D_004CE8C0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern void Generator_Call(int a0);
void stageSE03tsuiro(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x123)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

void stageSE03tnotSuiro(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x123)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
void stageSE04agate(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x123) == 0) { _ACTWait(1); }
    _ACTWait(1); Generator_MaskOff(a0);
}

extern int D_0062A894;
extern int D_004CE780[];

void stageSE04bstrong(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_0062A894 = 0;
    *(int *)(gobj + 0xB0) = (int)D_004CE780;
    for (;;) {
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", func_00235218);

extern void lt_fade_status(int a0);
extern void scpActivateAllWithKind(void);
extern int D_004CE7E0[];

void stageSE04ewind(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    lt_fade_status(0x32);
    D_0062A894 = 0;
    scpActivateAllWithKind();
    *(int *)(gobj + 0xB0) = (int)D_004CE7E0;
    for (;;) {
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", func_002352B8);

extern int scpSleepEnemyOne(int a0, int a1, float a2);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void actBoyBHang(void);
extern void actSt25aQueenDead(int a0, int a1, int a2, float a3, float a4);
extern void func_00178DD8(int a0);
extern void _ACTWait(int a0);
extern int D_00629DE4;
extern int D_00629DE8;

void stageSE04eriverDown(volatile int a0) {
    while (scpSleepEnemyOne(a0, D_00629DE4, 400.0f) == 0 ||
           scpSleepSpiderGroupOne(D_00629DE4, 0x2000000) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0x121);
    func_00178E08(0x119);
    if (D_00629DE8 != 0) {
        if (scpSleepSpiderGroupOne(D_00629DE8, 0x2000000) != 0) {
            actBoyBHang();
            actSt25aQueenDead(4, D_00629DE4, D_00629DE8, 2.0f, 8.0f);
        }
    }
    actSt25aQueenDead(4, D_00629DE4, 0, 2.0f, 8.0f);
}

extern int D_00629DE8;
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void func_00178DD8(int a0);
void stageSE06astrong(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (func_00178DB0(0x11F) == 0 || scpSleepSpiderGroupOne(D_00629DE8, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    func_00178DD8(0x122);
    func_00178DD8(0x123);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE06abirdIn);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", func_00235568);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE06abirdOut);

extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void gflagOff(int a0, int a1);
extern void gflagChk(int a0, void *a1);
extern int stage_DispBgAnimation(int a0, int a1);
extern void actSt25aGenerator(void *a0, float f0, float f1, float f2);
extern int func_0012A958(int a0);
extern void *ContinueCorrectPosition(int a0);
extern void func_00240008(void *a0, void *a1, void *a2);
extern float D_00629A18;
extern int D_0062C2CC;
typedef struct { long long _0; long long _8; } WpData16;
extern WpData16 D_00614E40;
void stageSE06ataimatsu(volatile int a0) {
    WpData16 local10, local20;
    stage_KillPlayBgAnimation(0x2AB, 1, 0);
    gflagOff(D_00629DE4, 0x187);
    while (stage_DispBgAnimation(0x2AB, 0x2AC) == 0) { _ACTWait(1); }
    {
        float t12 = *(volatile float *)&D_00629A18;
        actSt25aGenerator((void *)D_00629DE4, t12, 148.0f, -1112.0f);
    }
    local10 = D_00614E40;
    func_00240008(&local20, &local10, ContinueCorrectPosition(D_00629DE4));
    gflagChk(D_00629DE4, &local20);
    gflagOff(D_00629DE4, 0x188);
    while (func_0012A958(0x2AC) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_0062C2CC = 1;
    _ACTWait(0);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE08astrong);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int func_00178DB0(int a0);
extern void warpGirlInStage(float a0, float a1, float a2);
extern float D_00629A24, D_00629A28, D_00629A2C;
extern int D_004CE9C0[];
extern void stageSE08astrong(volatile int a0);
void stageSE08astrong2(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    warpGirlInStage(*(volatile float *)&D_00629A24, *(volatile float *)&D_00629A28,
                    *(volatile float *)&D_00629A2C);
    if (func_00178DB0(0x12B) == 0) {
        D_004CE9C0[1] = (int)stageSE08astrong;
        gobj->unkB4 = D_004CE9C0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void stageSE08anoise3(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x82, 0, 0);
}

extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);

void stageSE08ataimatsu(void) {
    if (func_00178DB0(0x2C) != 0) {
        stage_KillPlayBgAnimation(0x90, 0, 0);
        AddWayPointTop(0x21, 1);
    } else {
        stage_KillPlayBgAnimation(0x8F, 0, 0);
        AddWayPointTop(0x21, 0);
    }
    if (func_00178DB0(0x2D) != 0) {
        stage_KillPlayBgAnimation(0x92, 0, 0);
        AddWayPointTop(0x22, 1);
    } else {
        stage_KillPlayBgAnimation(0x91, 0, 0);
        AddWayPointTop(0x22, 0);
    }
}
