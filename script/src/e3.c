#include "common.h"

void actE3WarningChk(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x14B)==0){ _ACTWait(1); }
 _ACTWait(0x190); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
void actE3Title(volatile int a0){
 int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x14B)==0){ _ACTWait(1); }
 Generator_Call(a0); _ACTWait(0x78); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);

void actE3TitleChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
}

typedef struct ActB4Obj { char pad[0xB4]; int *unkB4; } ActB4Obj;
extern void func_0017C0B8(void);
extern void BoxBarSoundOn(int a0, int a1);
extern void actE3St09aSekizoChk();
extern int D_004CB730[];
extern int D_00629DE8;
void actE3TitleFrameChk(volatile int a0){
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (D_00629DE8 == 0) func_0017C0B8();
    if (func_00178DB0(0x149) == 0) {
        D_004CB730[1] = (int)actE3St09aSekizoChk;
        gobj->unkB4 = D_004CB730;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


void actE3Inst1Chk(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x149)==0){ _ACTWait(1); }
 _ACTWait(0x1E); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

void actE3Capsule(volatile int a0){
 int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x149)==0){ _ACTWait(1); }
 Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0);
}

void actE3CapsuleDemoCancel(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x149)==0){ _ACTWait(1); }
 Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

extern int actSt25aQueenDeadChk(int a0);
extern void func_001790A8(int a0);
extern void gflagOff(int a0, int a1);
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void func_002068A8();
extern int D_004CB780[];
extern int D_00629DE4;
extern int D_0062A894;
void actE3CapsuleDemo(volatile int a0){
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0xC19) + 0x16C) = 0;
    D_0062A894 = 1;
    func_001790A8(D_00629DE4);
    gflagOff(D_00629DE4, 0);
    actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
    stage_KillPlayBgAnimation(0xED, 0, 0);
    stage_KillPlayBgAnimation(0xF0, 0, 0);
    D_004CB780[1] = (int)func_002068A8;
    gobj->unkB4 = D_004CB780;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


#include "common.h"
extern void func_00179F88(void);
extern void func_00178DD8(int a0);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern void _ACTWait(int a0);
extern void actConte11Jimaku(float f);
extern int actCreateSubThread(void *fn, int a1);
extern void actEnemySleep();
extern int D_0062BBF8;
extern int D_0062C290;
void actE3St13cInit(volatile int a0) {
    func_00179F88();
    func_00178DD8(0x145);
    scpPlayStart(2, &D_0062BBF8, 1, 1, 1);
    while (D_0062BBF8 == 0) {
        _ACTWait(1);
    }
    actConte11Jimaku(6.0f);
    D_0062C290 = actCreateSubThread(actEnemySleep, 0x15);
}

extern void gflagOff(int a0, int a1);
extern int func_0012A958(int a0);
extern void gflagChk(int a0, void *a1);
extern void *ContinueCorrectPosition(int a0);
extern void func_00240008(void *a0, void *a1, void *a2);
extern void func_001790E8(int a0);
extern void lt_fade_status(int a0);
extern int D_0062B320;
typedef struct { long long _0; long long _8; } WpData16;
extern WpData16 D_006143A0;
void actE3CageFall(volatile int a0){
    WpData16 local10, local20;
    gflagOff(D_00629DE4, 0x12D);
    while (func_0012A958(0x228) == 0) { _ACTWait(1); }
    _ACTWait(1);
    gflagOff(D_00629DE4, 0);
    local10 = D_006143A0;
    func_00240008(&local20, &local10, ContinueCorrectPosition(D_00629DE4));
    gflagChk(D_00629DE4, &local20);
    func_001790E8(D_00629DE4);
    D_0062A894 = 0;
    lt_fade_status(0x32);
    D_0062B320 = 1;
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3CageFallChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", func_002078C8);

#include "common.h"
extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern int func_0012A958(int a0);
extern int D_004CB6C0[];
extern int D_0062A894;
void actE3CageFallDemo(volatile int a0) {
    lt_fade_status(0x33);
    func_00178DD8(0x146);
    _ACTWait(0x3C);
    stage_KillPlayBgAnimation(0x31F, 1, 0);
    soundSeDefPlayWithVolumeRate(0x4AD, 0, (int)D_004CB6C0, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, (int)D_004CB6C0, 1);
    while (func_0012A958(0x31F) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_0062A894 = 0;
    lt_fade_status(0x32);
}

extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void stage_KillPlayBgAnimation(int,int,int);
extern int func_0012A958(int a0);
extern int D_0062A894;
void actE3CageFallEffect(volatile int a0){
 lt_fade_status(0x33); func_00178DD8(0x14A); D_0062A894=1; _ACTWait(0x78);
 stage_KillPlayBgAnimation(0x320,1,0);
 while(func_0012A958(0x320)==0) _ACTWait(1); _ACTWait(1); lt_fade_status(0x32); D_0062A894=0; }

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int D_0062BBFC;
extern int D_00629DE4;
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
void actE3St09aSekizo(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    D_0062BBFC = 0;
    _ACTWait(1);
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x2000000) == 0) { _ACTWait(1); }
    scpPlayStart(3, &D_0062BBFC, 1, 1, 0);
}

#include "common.h"
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern int D_00629DE8;
extern int D_0062A894;
void actE3St09aSekizoChk(volatile int a0) {
    if (D_00629DE8 == 0) {
        _ACTWait(0);
    }
    while (scpSleepSpiderGroupOne(D_00629DE8, 0x1000000) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    _ACTWait(0x1E);
    func_00178DD8(0x149);
    stage_KillPlayBgAnimation(0xA0, 1, 0);
    while (func_0012A958(0xA0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_0062A894 = 0;
}

#include "common.h"
struct GateS { long long a, b; };
extern struct GateS D_00614440;
extern int actSt25aQueenTalkChk(int a0, int a1, void *a2, int a3, float f);
extern void func_00260568(void *a0, int a1, int a2);
extern void actSwordEffXL(int a0, int a1, void *a2, int a3);
extern void lt_fade_status(int a0);
extern void saveEditedDataBinary(void);
extern int D_00629DE8;
extern int D_0062A894;
void actE3GateChk(volatile int a0) {
    struct GateS buf1 = D_00614440;
    int buf2[4];
    actSt25aQueenTalkChk(D_00629DE8, 0, &buf1, 0, 100.0f);
    func_00260568(buf2, 0, 0x10);
    actSwordEffXL(D_00629DE8, 0x64, buf2, 0xB4);
    lt_fade_status(0x32);
    D_0062A894 = 0;
    saveEditedDataBinary();
}

extern void actTitleShortCut();
extern int D_004CB7A0[];
void actE3GateDemo(volatile int a0){
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x133) == 0) {
        if (func_00178DB0(0x137) == 0) {
            lt_fade_status(0x33);
            D_0062A894 = 1;
            actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
            stage_KillPlayBgAnimation(0x2FD, 0, 0);
            stage_KillPlayBgAnimation(0x1F, 0, -1);
            stage_KillPlayBgAnimation(0x19, 0, 0);
            stage_KillPlayBgAnimation(0x22, 0, -1);
            stage_KillPlayBgAnimation(0x20, 0, -1);
            stage_KillPlayBgAnimation(0x21, 0, -1);
            D_004CB7A0[1] = (int)actTitleShortCut;
            gobj->unkB4 = D_004CB7A0;
            BoxBarSoundOn((int)a0, 0x189);
            _ACTWait(0);
        }
    }
}


extern int stage_DispBgAnimation(int a0, int a1);
extern void scpSetCageVelocityFriction(int a0, int a1, int a2, int a3);
extern void func_0012AAB8(int a0, int a1);
extern void actSt25aQueenDead(int a0, int a1, int a2, float f12, float f13);
void actE3GateJimaku(volatile int a0){
    func_001790A8(D_00629DE4);
    stage_KillPlayBgAnimation(0x2E3, 1, 0);
    gflagOff(actSt25aQueenDeadChk(0x8E6), 0x2FE);
    *(int *)(actSt25aQueenDeadChk(0x8E6) + 0x16C) = 1;
    while (stage_DispBgAnimation(0x2E3, 0x2E4) == 0) { _ACTWait(1); }
    while (stage_DispBgAnimation(0x2E4, 0x2E5) == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x34, 1, 0);
    while (stage_DispBgAnimation(0x2E5, 0x2E6) == 0) { _ACTWait(1); }
    while (stage_DispBgAnimation(0x2E6, 0x2E7) == 0) { _ACTWait(1); }
    while (stage_DispBgAnimation(0x2E7, 0x2E8) == 0) { _ACTWait(1); }
    gflagOff(actSt25aQueenDeadChk(0x8E6), 0x2FF);
    while (stage_DispBgAnimation(0x2E8, 0x2E9) == 0) { _ACTWait(1); }
    *(int *)(actSt25aQueenDeadChk(0x8E6) + 0x16C) = 0;
    gflagOff(actSt25aQueenDeadChk(0x8E7), 0x300);
    *(int *)(actSt25aQueenDeadChk(0x8E7) + 0x16C) = 1;
    scpSetCageVelocityFriction(0x8E7, 0, 0x1E2, 0);
    func_0012AAB8(0x1E2, 1);
    stage_KillPlayBgAnimation(0x1E2, 1, 0);
    while (stage_DispBgAnimation(0x2E9, 0x2EA) == 0) { _ACTWait(1); }
    gflagOff(actSt25aQueenDeadChk(0x8E7), 0x301);
    while (stage_DispBgAnimation(0x2EA, 0x2EB) == 0) { _ACTWait(1); }
    gflagOff(actSt25aQueenDeadChk(0x8E7), 0x302);
    while (stage_DispBgAnimation(0x2EB, 0x2EC) == 0) { _ACTWait(1); }
    gflagOff(actSt25aQueenDeadChk(0x8E7), 0x303);
    while (func_0012A958(0x2EC) == 0) { _ACTWait(1); }
    _ACTWait(1);
    actSt25aQueenDead(2, D_00629DE4, 0, 1.0f, 8.0f);
}


extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f0);
extern void scpPlayMotDir(int a0, int a1, int a2, int a3);
extern void func_0012AAB8(int a0, int a1);
extern void LightLineGeo(int a0, int a1);
extern void actTitleReadTimeDemo0();
extern int D_004CB7C0[];
void actE3St01bInit(volatile int a0){
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (D_00629DE4 != 0) gflagOff(D_00629DE4, 0);
    lt_fade_status(0x33);
    D_0062A894 = 1;
    actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
    scpPlayMotDir(3, 0, 0x1E2, 0);
    func_0012AAB8(0x1E2, 1);
    stage_KillPlayBgAnimation(0x1E2, 1, 0);
    stage_KillPlayBgAnimation(0x2EE, 0, 0);
    stage_KillPlayBgAnimation(0x1E4, 0, -1);
    stage_KillPlayBgAnimation(0x1E5, 0, -1);
    stage_KillPlayBgAnimation(0x1E7, 0, -1);
    stage_KillPlayBgAnimation(0x1E8, 0, -1);
    stage_KillPlayBgAnimation(0x1E9, 0, -1);
    LightLineGeo(D_00629DE4, 2);
    D_004CB7C0[1] = (int)actTitleReadTimeDemo0;
    gobj->unkB4 = D_004CB7C0;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


extern int stage_DispBgAnimation(int a0, int a1);
extern void actSt25aQueenDead(int a0, int a1, int a2, float f12, float f13);
void actE3Warning(volatile int a0){
    func_001790A8(D_00629DE4);
    stage_KillPlayBgAnimation(0x2ED, 1, 0);
    gflagOff(D_00629DE4, 0x1B3);
    while (stage_DispBgAnimation(0x2ED, 0x2EE) == 0) { _ACTWait(1); }
    while (stage_DispBgAnimation(0x2EE, 0x2EF) == 0) { _ACTWait(1); }
    gflagOff(actSt25aQueenDeadChk(0x989), 0x304);
    *(int *)(actSt25aQueenDeadChk(0x989) + 0x16C) = 1;
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x2F0, 1, 0);
    while (stage_DispBgAnimation(0x2EF, 0x2F1) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x1B4);
    gflagOff(actSt25aQueenDeadChk(0x989), 0x305);
    while (stage_DispBgAnimation(0x2F1, 0x2F2) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x1B5);
    gflagOff(actSt25aQueenDeadChk(0x989), 0x306);
    while (stage_DispBgAnimation(0x2F2, 0x2F3) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x1B6);
    gflagOff(actSt25aQueenDeadChk(0x989), 0x307);
    while (stage_DispBgAnimation(0x2F3, 0x2F4) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x1B7);
    gflagOff(actSt25aQueenDeadChk(0x989), 0x308);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x2F5, 1, 0);
    while (func_0012A958(0x2F4) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_001790E8(D_00629DE4);
    lt_fade_status(0x32);
    actSt25aQueenDead(3, D_00629DE4, 0, 1.0f, 8.0f);
}


extern void scpSetCageVelocityFriction(int a0, int a1, int a2, int a3);
extern void actOpDemo03();
extern int D_004CB840[];
void actE3Inst1(volatile int a0){
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x138) == 0) {
        if (func_00178DB0(0x137) != 0) {
            lt_fade_status(0x33);
            D_0062A894 = 1;
            scpSetCageVelocityFriction(0x8E7, 0, 0x1E2, 0);
            func_0012AAB8(0x1E2, 1);
            stage_KillPlayBgAnimation(0x1E2, 1, 0);
            stage_KillPlayBgAnimation(0x2FD, 0, 0);
            stage_KillPlayBgAnimation(0x1F, 0, -1);
            stage_KillPlayBgAnimation(0x19, 0, 0);
            stage_KillPlayBgAnimation(0x22, 0, -1);
            stage_KillPlayBgAnimation(0x20, 0, -1);
            stage_KillPlayBgAnimation(0x21, 0, -1);
            LightLineGeo(D_00629DE4, 2);
            D_004CB840[1] = (int)actOpDemo03;
            gobj->unkB4 = D_004CB840;
            BoxBarSoundOn((int)a0, 0x189);
            _ACTWait(0);
        }
    }
}

