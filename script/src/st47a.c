#include "common.h"

typedef struct ActB4Obj {
    char pad[0xB4];
    int *unkB4;
} ActB4Obj;
extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void BoxBarSoundOn(int a0, int a1);

extern int D_00271240[];
extern int actSt25aQueenDeadChk(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern int *D_00629DE4;
extern int D_00629DE8;
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern int func_0012AA28(int a0, int a1, int a2);
extern void func_00178DD8(int a0);
extern int D_004CE460[];
extern void actSt47aEnd(volatile int a0);
void actSt47aInit(volatile int a0) {
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    int i = 0;
    while (i < (0x3C - D_00271240[0] * 0xA) / D_00271240[1]) {
        if (scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x2D2), 0x1000000) != 0 ||
            scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x2D3), 0x1000000) != 0 ||
            scpSleepSpiderGroupOne((int)D_00629DE4, 0x1000000) != 0 ||
            (D_00629DE8 != 0 && scpSleepSpiderGroupOne(D_00629DE8, 0x1000000) != 0)) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0x64, 1, 0);
    soundSeDefPlayWithVolumeRate(0x4AC, 0, 0, 1);
    while (func_0012AA28(0x64, 0x2D, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    if (scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x2D2), 0x1000000) != 0 ||
        scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x2D3), 0x1000000) != 0 ||
        scpSleepSpiderGroupOne((int)D_00629DE4, 0x1000000) != 0 ||
        scpSleepSpiderGroupOne(D_00629DE8, 0x1000000) != 0) {
        func_00178DD8(0x36);
    }
    D_004CE460[1] = (int)actSt47aEnd;
    obj->unkB4 = D_004CE460;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}



extern int scpKillSpiderGroup(int a0, int a1);
extern void func_00178E08(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern int func_0012AA28(int a0, int a1, int a2);
extern void scpWakeupItemWithBoundary(float a0, float a1, float a2, float a3);
extern volatile float D_006299D4;
extern volatile float D_006299D8;
extern volatile float D_006299DC;
extern int D_004CE480[];
extern void actSt47aInit(volatile int a0);
void actSt47aEnd(volatile int a0) {
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    while (scpKillSpiderGroup((int)a0, 0x1000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);
    func_00178E08(0x36);
    stage_KillPlayBgAnimation(0x64, 1, 0x2E);
    soundSeDefPlayWithVolumeRate(0x4AC, 0, 0, 1);
    while (func_0012AA28(0x64, 0x32, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpWakeupItemWithBoundary(D_006299D4, D_006299D8, D_006299DC, 100.0f);
    while (func_0012AA28(0x64, 0x5A, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_004CE480[1] = (int)actSt47aInit;
    obj->unkB4 = D_004CE480;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


extern int D_00271240[];
extern int actSt25aQueenDeadChk(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern int *D_00629DE4;
extern int D_00629DE8;
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern int func_0012AA28(int a0, int a1, int a2);
extern void func_00178DD8(int a0);
extern int D_004CE4E0[];
extern void actSt47aHane1Up(volatile int a0);
void actSt47aSekizo1Chk(volatile int a0) {
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    int i = 0;
    while (i < (0x3C - D_00271240[0] * 0xA) / D_00271240[1]) {
        if (scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x2D2), 0x2000000) != 0 ||
            scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x2D3), 0x2000000) != 0 ||
            scpSleepSpiderGroupOne((int)D_00629DE4, 0x2000000) != 0 ||
            (D_00629DE8 != 0 && scpSleepSpiderGroupOne(D_00629DE8, 0x2000000) != 0)) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0x65, 1, 0);
    soundSeDefPlayWithVolumeRate(0x4AC, 0, 0, 1);
    while (func_0012AA28(0x65, 0x2D, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    if (scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x2D2), 0x2000000) != 0 ||
        scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x2D3), 0x2000000) != 0 ||
        scpSleepSpiderGroupOne((int)D_00629DE4, 0x2000000) != 0 ||
        scpSleepSpiderGroupOne(D_00629DE8, 0x2000000) != 0) {
        func_00178DD8(0x37);
    }
    D_004CE4E0[1] = (int)actSt47aHane1Up;
    obj->unkB4 = D_004CE4E0;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aHane1Up);


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aHane2Up);


extern void func_00178E08(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern int func_0012A958(int a0);
extern int D_004CE580[];
extern void actSt47aHane2Up(volatile int a0);
void actSt47aRopeChk(volatile int a0) {
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    while (func_00178DB0(0x36) != 0 && func_00178DB0(0x37) != 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);
    func_00178E08(0x38);
    stage_KillPlayBgAnimation(0x67, 1, 0);
    soundSeDefPlayWithVolumeRate(0x4AD, 0, 0, 1);
    _ACTWait(0x3C);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, 0, 1);
    while (func_0012A958(0x67) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_004CE580[1] = (int)actSt47aHane2Up;
    obj->unkB4 = D_004CE580;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


void actSt47aEnemy1(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0); Generator_Mask(actSt25aQueenDeadChk(0x2CA));
 while(func_00178DB0(0x3A)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); Generator_Call(actSt25aQueenDeadChk(0x2CA)); }

extern int actSt25aQueenDeadChk(int a0);
void actSt47aTorch(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0); Generator_Mask(actSt25aQueenDeadChk(0x2CB));
 while(func_00178DB0(0x3C)==0){ _ACTWait(1); }
 Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_Call(actSt25aQueenDeadChk(0x2CB)); }

extern int D_004CE400[];
extern void actSt47aExit2(volatile int a0);
void actSt47aSekizo1(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x33) == 0) {
        D_004CE400[1] = (int)actSt47aExit2;
        gobj->unkB4 = D_004CE400;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004CE520[];
extern int D_004CE540[];
extern void actSt47aHane2Up(volatile int a0);
extern void actSt47aRopeChk(volatile int a0);
void actSt47aSekizo2(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x38) == 0) {
        stage_KillPlayBgAnimation(0x66, 0, 0);
        D_004CE520[1] = (int)actSt47aHane2Up;
        gobj->unkB4 = D_004CE520;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x66, 0, -1);
        D_004CE540[1] = (int)actSt47aRopeChk;
        gobj->unkB4 = D_004CE540;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CE420[];
extern int D_004CE440[];
extern void actSt47aInit(volatile int a0);
extern void actSt47aEnd(volatile int a0);
void actSt47aSekizo3(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x36) == 0) {
        stage_KillPlayBgAnimation(0x64, 0, 0);
        D_004CE420[1] = (int)actSt47aInit;
        gobj->unkB4 = D_004CE420;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x64, 0, 0x2D);
        D_004CE440[1] = (int)actSt47aEnd;
        gobj->unkB4 = D_004CE440;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CE4A0[];
extern int D_004CE4C0[];
extern void actSt47aSekizo1Chk(volatile int a0);
extern void actSt47aHane1Up(volatile int a0);
void actSt47aSekizo4(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x37) == 0) {
        stage_KillPlayBgAnimation(0x65, 0, 0);
        D_004CE4A0[1] = (int)actSt47aSekizo1Chk;
        gobj->unkB4 = D_004CE4A0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x65, 0, 0x2D);
        D_004CE4C0[1] = (int)actSt47aHane1Up;
        gobj->unkB4 = D_004CE4C0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CE5A0[];
extern void actSt47aEne(volatile int a0);
void actSt47aHane1(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x39) == 0) {
        D_004CE5A0[1] = (int)actSt47aEne;
        gobj->unkB4 = D_004CE5A0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern int actInitialize(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
void actSt47aHane2(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x3A)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); }

extern int D_004CE5C0[];
extern void actSt47aEnemy2(volatile int a0);
void actSt47aRope(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x3B) == 0) {
        D_004CE5C0[1] = (int)actSt47aEnemy2;
        gobj->unkB4 = D_004CE5C0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


void actSt47aBarricade(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x3C)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

void actSt47aExit(int a0) {
    int buf[4];
    buf[0] = a0;
}

#include "common.h"
extern void _ACTWait(int a0);
extern int scpTriggerBall(int a0, int *a1, float f);
extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern int *D_00629DE4;
extern int D_0062A894;
void actSt47aExit2(volatile int a0) {
    while (scpTriggerBall(a0, D_00629DE4, 1000.0f) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    func_00178DD8(0x33);
    D_0062A894 = 1;
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x140, 1, 0);
    while (func_0012A958(0x140) == 0) { _ACTWait(1); }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_0062A894 = 0;
}

extern int D_00629DE8;
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void func_00178E08(int a0);
extern void func_00178DD8(int a0);
void actSt47aEne(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE8, 0x3000000) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_00178E08(0x165);
    func_00178DD8(0x39);
    func_00178DD8(0x3A);
}

void actSt47aEnemy2(volatile int a0){
 if(D_00629DE8 == 0) _ACTWait(0);
 while(D_00629DE8 == 0 || scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x2D3), 0x4000000)==0) _ACTWait(1);
 _ACTWait(0x258); func_00178DD8(0x3B); func_00178DD8(0x3C); }

extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern int func_0012AA28(int a0, int a1, int a2);
extern void scpTrans(int a0, int a1);
extern int D_0062BDFC;
extern int D_004CE660[];
extern void actSplash2Chk(volatile int a0);
void actSt47aEnemy3(volatile int a0) {
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    lt_fade_status(0x33);
    _ACTWait(0x3C);
    scpPlayStart(0x49, &D_0062BDFC, 1, 1, 1);
    while (D_0062BDFC == 0) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0x79, 1, 0x5A);
    func_00178E08(0x11A);
    while (func_0012AA28(0x79, 0xB4, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    _ACTWait(0x78);
    if (D_0062BDFC != 0) {
        scpTrans(D_0062BDFC, 0x100);
    }
    lt_fade_status(0x32);
    _ACTWait(0x3C);
    D_004CE660[1] = (int)actSplash2Chk;
    obj->unkB4 = D_004CE660;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


typedef struct { long long a; long long b; } S16;
extern S16 D_00614E20;
extern S16 D_00614E30;
extern int D_004CE680[];
extern void actExplode(volatile int a0);
extern void func_0012AAB8(int a0, int a1);
void actSt47aEnemy4(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    {
        S16 buf = D_00614E20;
        soundSeDefPlayWithVolumeRate(0x52A, 0, (int)&buf, 1);
    }
    if (func_00178DB0(0x11B) == 0) {
        *(int *)(actSt25aQueenDeadChk(0x6F1) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0x76, 0, 0);
        D_004CE680[1] = (int)actExplode;
        gobj->unkB4 = D_004CE680;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        S16 buf2 = D_00614E30;
        soundSeDefPlayWithVolumeRate(0x52B, 0, (int)&buf2, 1);
        soundSeDefPlayWithVolumeRate(0x52C, 0, (int)&buf2, 1);
        soundSeDefPlayWithVolumeRate(0x52D, 0, (int)&buf2, 1);
        *(int *)(actSt25aQueenDeadChk(0x6F2) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0x76, 1, 0);
        func_0012AAB8(0x76, 1);
        func_0012AAB8(0x77, 1);
    }
}

