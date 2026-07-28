#include "common.h"

typedef union { float f[4]; struct { long long _0, _8; } q; } WpData16;

typedef struct ActB4Obj { char pad[0xC4]; int *unkC4; } ActB4Obj;

extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern int func_0017B230(int a0);

void actE3WarningChk(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_0017B230(0x14C)==0){ _ACTWait(1); }
 _ACTWait(0x190); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern int func_0017B230(int a0);

void actE3Title(volatile int a0){
 int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_0017B230(0x14C)==0){ _ACTWait(1); }
 Generator_Call(a0); _ACTWait(0x78); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0);
}

extern void _ACTWait(int a0);
extern int actInitialize(int a0);

void actE3TitleChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D0B20[];
extern int D_00631AE8;
extern void actE3St09aSekizoChk();
extern int func_0017B230(int a0);
extern void func_0017E9D8(void);

void actE3TitleFrameChk(volatile int a0){
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (D_00631AE8 == 0) func_0017E9D8();
    if (func_0017B230(0x14A) == 0) {
        D_004D0B20[1] = (int)actE3St09aSekizoChk;
        gobj->unkC4 = D_004D0B20;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

void actE3Inst1Chk(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_0017B230(0x14A)==0){ _ACTWait(1); }
 _ACTWait(0x1E); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

void actE3Capsule(volatile int a0){
 int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_0017B230(0x14A)==0){ _ACTWait(1); }
 Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0);
}

void actE3CapsuleDemoCancel(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_0017B230(0x14A)==0){ _ACTWait(1); }
 Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

extern int D_004D0B70[];
extern int D_00631AE4;
extern int D_006325B4;
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f0);
extern int actSt25aQueenDeadChk(int a0);
extern void func_0017B528(int a0);
extern void func_00209440();
extern void func_001F0DA8(void);
extern void gflagOff(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actE3CapsuleDemo(volatile int a0){
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    func_001F0DA8();
    *(int *)(actSt25aQueenDeadChk(0xC37) + 0x16C) = 0;
    D_006325B4 = 1;
    func_0017B528(D_00631AE4);
    gflagOff(D_00631AE4, 0);
    actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
    stage_KillPlayBgAnimation(0xEE, 0, 0);
    stage_KillPlayBgAnimation(0xF1, 0, 0);
    D_004D0B70[1] = (int)func_00209440;
    gobj->unkC4 = D_004D0B70;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_006338F0;
extern int D_00633F90;
extern void actConte11Jimaku(float f);
extern int actCreateSubThread(void *fn, int a1);
extern void actEnemySleep();
extern void func_0017B258(int a0);
extern void func_0017C840(void);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);

void actE3St13cInit(volatile int a0) {
    func_0017C840();
    func_0017B258(0x146);
    scpPlayStart(2, &D_006338F0, 1, 1, 1);
    while (D_006338F0 == 0) {
        _ACTWait(1);
    }
    actConte11Jimaku(6.0f);
    D_00633F90 = actCreateSubThread(actEnemySleep, 0x15);
}

extern void *ContinueCorrectPosition(int a0);
extern WpData16 D_0061B810;
extern int D_00631AE4;
extern int D_006325B4;
extern int D_00633060;
extern int func_0012AA80(int a0);
extern void func_0017B568(int a0);
extern void func_00243AE8(void *a0, void *a1, void *a2);
extern void gflagChk(int a0, void *a1);
extern void gflagOff(int a0, int a1);
extern void lt_fade_status(int a0);

void actE3CageFall(volatile int a0){
    WpData16 local10, local20;
    gflagOff(D_00631AE4, 0x12D);
    while (func_0012AA80(0x229) == 0) { _ACTWait(1); }
    _ACTWait(1);
    gflagOff(D_00631AE4, 0);
    local10 = D_0061B810;
    func_00243AE8(&local20, &local10, ContinueCorrectPosition(D_00631AE4));
    gflagChk(D_00631AE4, &local20);
    func_0017B568(D_00631AE4);
    D_006325B4 = 0;
    lt_fade_status(0x32);
    D_00633060 = 1;
}

extern int D_004D0A50[];

void actE3CageFallChk(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_006325B4 = 0;
    *(int *)(gobj + 0xC0) = (int)D_004D0A50;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct { char pad[0xC0]; void *f_C0; void *unkC4; } GObjC0;
extern int *D_004D0A90[];
extern void actE3CageFallDemo(volatile int a0);
void func_0020A468(volatile int a0) {
    GObjC0 *obj = *(GObjC0 **)(a0 + 0x164);
    D_006325B4 = 1;
    D_004D0A90[1] = (int *)actE3CageFallDemo;
    obj->f_C0 = 0;
    obj->unkC4 = (void *)D_004D0A90;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D0AB0[];
extern int D_006325B4;
extern int func_0012AA80(int a0);
extern void lt_fade_status(int a0);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actE3CageFallDemo(volatile int a0) {
    lt_fade_status(0x33);
    func_0017B258(0x147);
    _ACTWait(0x3C);
    stage_KillPlayBgAnimation(0x320, 1, 0);
    soundSeDefPlayWithVolumeRate(0x4AD, 0, (int)D_004D0AB0, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, (int)D_004D0AB0, 1);
    while (func_0012AA80(0x320) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_006325B4 = 0;
    lt_fade_status(0x32);
}

extern int D_006325B4;
extern int func_0012AA80(int a0);
extern void func_0017B258(int a0);
extern void lt_fade_status(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actE3CageFallEffect(volatile int a0){
 lt_fade_status(0x33); func_0017B258(0x14B); D_006325B4=1; _ACTWait(0x78);
 stage_KillPlayBgAnimation(0x321,1,0);
 while(func_0012AA80(0x321)==0) _ACTWait(1); _ACTWait(1); lt_fade_status(0x32); D_006325B4=0; }

extern int D_00631AE4;
extern int D_006338F4;
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern int scpSleepSpiderGroupOne(int a0, int a1);

void actE3St09aSekizo(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    D_006338F4 = 0;
    _ACTWait(1);
    while (scpSleepSpiderGroupOne(D_00631AE4, 0x2000000) == 0) { _ACTWait(1); }
    scpPlayStart(3, &D_006338F4, 1, 1, 0);
}

void actE3St09aSekizoChk(volatile int a0) {
    if (D_00631AE8 == 0) {
        _ACTWait(0);
    }
    while (scpSleepSpiderGroupOne(D_00631AE8, 0x1000000) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    _ACTWait(0x1E);
    func_0017B258(0x14A);
    stage_KillPlayBgAnimation(0xA1, 1, 0);
    while (func_0012AA80(0xA1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_006325B4 = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3GateChk);

extern int D_004D0B90[];
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f0);
extern void actTitleShortCut();

void actE3GateDemo(volatile int a0){
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x134) == 0) {
        if (func_0017B230(0x138) == 0) {
            lt_fade_status(0x33);
            D_006325B4 = 1;
            actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
            stage_KillPlayBgAnimation(0x2FE, 0, 0);
            stage_KillPlayBgAnimation(0x1F, 0, -1);
            stage_KillPlayBgAnimation(0x19, 0, 0);
            stage_KillPlayBgAnimation(0x22, 0, -1);
            stage_KillPlayBgAnimation(0x20, 0, -1);
            stage_KillPlayBgAnimation(0x21, 0, -1);
            D_004D0B90[1] = (int)actTitleShortCut;
            gobj->unkC4 = D_004D0B90;
            BoxBarSoundOn((int)a0, 0x18D);
            _ACTWait(0);
        }
    }
}

extern void actSt25aQueenDead(int a0, int a1, int a2, float f12, float f13);
extern int actSt25aQueenDeadChk(int a0);
extern void func_0012ABE0(int a0, int a1);
extern void func_0017B528(int a0);
extern void scpSetCageVelocityFriction(int a0, int a1, int a2, int a3);
extern int stage_DispBgAnimation(int a0, int a1);

void actE3GateJimaku(volatile int a0){
    func_0017B528(D_00631AE4);
    stage_KillPlayBgAnimation(0x2E4, 1, 0);
    gflagOff(actSt25aQueenDeadChk(0x903), 0x2FC);
    *(int *)(actSt25aQueenDeadChk(0x903) + 0x16C) = 1;
    while (stage_DispBgAnimation(0x2E4, 0x2E5) == 0) { _ACTWait(1); }
    while (stage_DispBgAnimation(0x2E5, 0x2E6) == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x34, 1, 0);
    while (stage_DispBgAnimation(0x2E6, 0x2E7) == 0) { _ACTWait(1); }
    while (stage_DispBgAnimation(0x2E7, 0x2E8) == 0) { _ACTWait(1); }
    while (stage_DispBgAnimation(0x2E8, 0x2E9) == 0) { _ACTWait(1); }
    gflagOff(actSt25aQueenDeadChk(0x903), 0x2FD);
    while (stage_DispBgAnimation(0x2E9, 0x2EA) == 0) { _ACTWait(1); }
    *(int *)(actSt25aQueenDeadChk(0x903) + 0x16C) = 0;
    gflagOff(actSt25aQueenDeadChk(0x904), 0x2FE);
    *(int *)(actSt25aQueenDeadChk(0x904) + 0x16C) = 1;
    scpSetCageVelocityFriction(0x904, 0, 0x1E3, 0);
    func_0012ABE0(0x1E3, 1);
    stage_KillPlayBgAnimation(0x1E3, 1, 0);
    while (stage_DispBgAnimation(0x2EA, 0x2EB) == 0) { _ACTWait(1); }
    gflagOff(actSt25aQueenDeadChk(0x904), 0x2FF);
    while (stage_DispBgAnimation(0x2EB, 0x2EC) == 0) { _ACTWait(1); }
    gflagOff(actSt25aQueenDeadChk(0x904), 0x300);
    while (stage_DispBgAnimation(0x2EC, 0x2ED) == 0) { _ACTWait(1); }
    gflagOff(actSt25aQueenDeadChk(0x904), 0x301);
    while (func_0012AA80(0x2ED) == 0) { _ACTWait(1); }
    _ACTWait(1);
    actSt25aQueenDead(2, D_00631AE4, 0, 1.0f, 8.0f);
}

extern int D_004D0BB0[];
extern void actTitleReadTimeDemo0();
extern void func_0012ABE0(int a0, int a1);
extern void func_001C2098(int a0, int a1);
extern void scpPlayMotDir(int a0, int a1, int a2, int a3);

void actE3St01bInit(volatile int a0){
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (D_00631AE4 != 0) gflagOff(D_00631AE4, 0);
    lt_fade_status(0x33);
    D_006325B4 = 1;
    actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
    scpPlayMotDir(3, 0, 0x1E3, 0);
    func_0012ABE0(0x1E3, 1);
    stage_KillPlayBgAnimation(0x1E3, 1, 0);
    stage_KillPlayBgAnimation(0x2EF, 0, 0);
    stage_KillPlayBgAnimation(0x1E5, 0, -1);
    stage_KillPlayBgAnimation(0x1E6, 0, -1);
    stage_KillPlayBgAnimation(0x1E8, 0, -1);
    stage_KillPlayBgAnimation(0x1E9, 0, -1);
    stage_KillPlayBgAnimation(0x1EA, 0, -1);
    func_001C2098(D_00631AE4, 2);
    D_004D0BB0[1] = (int)actTitleReadTimeDemo0;
    gobj->unkC4 = D_004D0BB0;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern void actSt25aQueenDead(int a0, int a1, int a2, float f12, float f13);
extern int actSt25aQueenDeadChk(int a0);
extern void func_0017B528(int a0);
extern int stage_DispBgAnimation(int a0, int a1);

void actE3Warning(volatile int a0){
    func_0017B528(D_00631AE4);
    stage_KillPlayBgAnimation(0x2EE, 1, 0);
    gflagOff(D_00631AE4, 0x1B3);
    while (stage_DispBgAnimation(0x2EE, 0x2EF) == 0) { _ACTWait(1); }
    while (stage_DispBgAnimation(0x2EF, 0x2F0) == 0) { _ACTWait(1); }
    gflagOff(actSt25aQueenDeadChk(0x9A6), 0x302);
    *(int *)(actSt25aQueenDeadChk(0x9A6) + 0x16C) = 1;
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x2F1, 1, 0);
    while (stage_DispBgAnimation(0x2F0, 0x2F2) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x1B4);
    gflagOff(actSt25aQueenDeadChk(0x9A6), 0x303);
    while (stage_DispBgAnimation(0x2F2, 0x2F3) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x1B5);
    gflagOff(actSt25aQueenDeadChk(0x9A6), 0x304);
    while (stage_DispBgAnimation(0x2F3, 0x2F4) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x1B6);
    gflagOff(actSt25aQueenDeadChk(0x9A6), 0x305);
    while (stage_DispBgAnimation(0x2F4, 0x2F5) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x1B7);
    gflagOff(actSt25aQueenDeadChk(0x9A6), 0x306);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x2F6, 1, 0);
    while (func_0012AA80(0x2F5) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_0017B568(D_00631AE4);
    lt_fade_status(0x32);
    actSt25aQueenDead(3, D_00631AE4, 0, 1.0f, 8.0f);
}

extern int D_004D0C30[];
extern void actOpDemo03();
extern void func_0012ABE0(int a0, int a1);
extern void func_001C2098(int a0, int a1);
extern void scpSetCageVelocityFriction(int a0, int a1, int a2, int a3);

void actE3Inst1(volatile int a0){
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x139) == 0) {
        if (func_0017B230(0x138) != 0) {
            lt_fade_status(0x33);
            D_006325B4 = 1;
            scpSetCageVelocityFriction(0x904, 0, 0x1E3, 0);
            func_0012ABE0(0x1E3, 1);
            stage_KillPlayBgAnimation(0x1E3, 1, 0);
            stage_KillPlayBgAnimation(0x2FE, 0, 0);
            stage_KillPlayBgAnimation(0x1F, 0, -1);
            stage_KillPlayBgAnimation(0x19, 0, 0);
            stage_KillPlayBgAnimation(0x22, 0, -1);
            stage_KillPlayBgAnimation(0x20, 0, -1);
            stage_KillPlayBgAnimation(0x21, 0, -1);
            func_001C2098(D_00631AE4, 2);
            D_004D0C30[1] = (int)actOpDemo03;
            gobj->unkC4 = D_004D0C30;
            BoxBarSoundOn((int)a0, 0x18D);
            _ACTWait(0);
        }
    }
}

