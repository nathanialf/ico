#include "common.h"

typedef struct ActB4Obj {
    char pad[0xC4];
    int *unkC4;
} ActB4Obj;

INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aIntro);
ASM_LIT4_SLOT(D_00631680, 0.025f);

INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aDoor);

INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aSwitchL);
ASM_LIT4_SLOT(D_00631684, -1338.0f);
ASM_LIT4_SLOT(D_00631688, 3085.0f);

INCLUDE_ASM("asm/nonmatchings/src/st18a", actSt18aSwitchR);
ASM_LIT4_SLOT(D_0063168C, 527.0f);
ASM_LIT4_SLOT(D_00631690, -1563.0f);

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D33E0[];
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void actSt19aOriXL();
extern int func_0017B230(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt18aEne(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xC) == 0) {
        stage_KillPlayBgAnimation(0x1F, 0, -1);
        stage_KillPlayBgAnimation(0x19, 0, 0);
        stage_KillPlayBgAnimation(0x22, 0, 0);
        stage_KillPlayBgAnimation(0x23, 0, 0);
        stage_KillPlayBgAnimation(0x25, 0, 0);
        D_004D33E0[1] = (int)actSt19aOriXL;
        gobj->unkC4 = D_004D33E0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x1F, 0, -1);
        stage_KillPlayBgAnimation(0x19, 0, 0);
        stage_KillPlayBgAnimation(0x22, 0, 0);
        stage_KillPlayBgAnimation(0x23, 0, 0);
        stage_KillPlayBgAnimation(0x25, 0, 0);
    }
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D3400[];
extern float D_006325B8;
extern int D_00633AB4;
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void actSt19aPipeXL();
extern int fightSoundClose(void);
extern int func_0017B230(int a0);
extern void func_00192040(void);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern void warpGirlInStage(float f0, float f1, float f2);

void actSt18aEnemy1_2(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    warpGirlInStage(-1886.0f, 625.0f, -4.0f);
    func_00192040();
    while (fightSoundClose() != 0) {
        _ACTWait(1);
    }
    if (func_0017B230(0xD) == 0) {
        D_004D3400[1] = (int)actSt19aPipeXL;
        gobj->unkC4 = D_004D3400;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else if (func_0017B230(0xE) == 0) {
        scpPlayStart(0x24, &D_00633AB4, 1, 0, 1);
        D_006325B8 = 0.5f;
    }
}

extern int D_00631AE4;
extern int D_006325B4;
extern int D_00633AB8;
extern void actCreateSubThread(void *fn, int a1);
extern void actSt18aEne2();
extern void func_0017B258(int a0);
extern void func_0017B528(int a0);
extern void gflagOff(int a0, int a1);
extern void lt_fade_status(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);

extern int D_00633AB0;
extern int scpTriggerBallTargetMan(int a0);

void actSt19aPipeXL(volatile int a0) {
    while (scpSleepSpiderGroupOne(D_00631AE4, 0x2000000) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    func_0017B258(0xD);
    D_006325B4 = 1;
    func_0017B528(D_00631AE4);
    gflagOff(D_00631AE4, 0);
    scpPlayStart(0x23, &D_00633AB8, 1, 1, 1);
    while (D_00633AB8 == 0) { _ACTWait(1); }
    D_006325B8 = 0.5f;
    actCreateSubThread(actSt18aEne2, 0x15);
    while (scpTriggerBallTargetMan(D_00633AB0) == 0) { _ACTWait(1); }
    scpPlayStart(0x24, &D_00633AB4, 1, 0, 0);
}

extern void AdpcmPlay(int a0);
extern void CapsuleGhostBossStart(void);
extern int D_00274EC0[];
extern int D_00631AE4;
extern int D_006325B4;
extern int func_0012AA80(int a0);
extern void func_0017B568(int a0);
extern void gflagOff(int a0, int a1);
extern void lt_fade_status(int a0);

void actSt18aEne2(volatile int a0) {
    stage_KillPlayBgAnimation(0x2B0, 1, 0);
    while (func_0012AA80(0x2B0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    CapsuleGhostBossStart();
    _ACTWait(((0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1]) * 2);
    while (D_00633AB4 == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(*(int *)(D_00633AB4 + 0x2C));
    gflagOff(D_00631AE4, 0);
    func_0017B568(D_00631AE4);
    D_006325B4 = 0;
    lt_fade_status(0x32);
}

extern int D_00631AEC;
extern int D_00633AC4;
extern int D_00633AD0;
extern unsigned char D_00633AD4;
extern void iosPadActVolumeSet(int a0, int a1);
extern void Vibration_ShotDecode(int a0);
extern void RequestStageChange(int a0, int a1, int a2, float f0, float f1);
extern int func_0012AB50(int a0, int a1, int a2);
extern void func_0017B258(int a0);
extern int iosPadDevRead(int a0, int a1);

extern void preload(int a0);

void actSt18aEnemy2_2(volatile int a0) {
    lt_fade_status(0x33);
    func_0017B258(0xF);
    scpPlayStart(0x4D, &D_00633AC4, 0, 1, 1);
    while (D_00633AC4 == 0) {
        _ACTWait(1);
    }
    preload(3);
    stage_KillPlayBgAnimation(0x27, 1, 0xEB);
    while (func_0012AB50(0x27, 0x141, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0x11);
    while (func_0012AB50(0x27, 0x15E, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    {
        int r = iosPadDevRead(D_00631AEC, 0x9);
        D_00633AD4 = 0x80;
        D_00633AD0 = r;
        iosPadActVolumeSet(r, 0x80);
    }
    while (func_0012AB50(0x27, 0x1C2, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Vibration_ShotDecode(D_00633AD0);
    RequestStageChange(0x3, D_00631AE4, 0, 2.0f, 4.0f);
    D_006325B4 = 0;
    lt_fade_status(0x32);
}

extern int D_004D34A0[];
extern void actSt18aIntroChk();
extern void scpFadeOut(int a0, int a1, int a2, float f0);

void actSt18aCamera(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x128) != 0) {
        lt_fade_status(0x33);
        D_006325B4 = 1;
        scpFadeOut(0, 0, 0, 255.0f);
        stage_KillPlayBgAnimation(0x27, 0, 0xEB);
        _ACTWait(0xA);
        D_006325B4 = 1;
        stage_KillPlayBgAnimation(0x27, 0, 0);
        D_004D34A0[1] = (int)actSt18aIntroChk;
        gobj->unkC4 = D_004D34A0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x27, 0, 0xEB);
    }
}

extern int D_00631AEC;
extern int D_00633AC0;
extern int D_00633AD0;
extern unsigned char D_00633AD4;
extern void iosPadActVolumeSet(int a0, int a1);
extern void Vibration_ShotDecode(int a0);
extern void scpFadeIn(float f0);
extern int func_0012AB50(int a0, int a1, int a2);
extern void func_0017B288(int a0);
extern int iosPadDevRead(int a0, int a1);

void actSt18aIntroChk(volatile int a0) {
    scpPlayStart(0x4C, &D_00633AC0, 1, 1, 1);
    while (D_00633AC0 == 0) {
        _ACTWait(1);
    }
    scpFadeIn(6.0f);
    stage_KillPlayBgAnimation(0x27, 1, 0);
    {
        int r = iosPadDevRead(D_00631AEC, 0x9);
        D_00633AD4 = 0x80;
        D_00633AD0 = r;
        iosPadActVolumeSet(r, 0x80);
    }
    while (func_0012AB50(0x27, 0xC8, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0x11);
    Vibration_ShotDecode(D_00633AD0);
    while (func_0012AB50(0x27, 0xEA, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_006325B4 = 0;
    lt_fade_status(0x32);
    func_0017B288(0x128);
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D33A0[];
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void actSt18aSwitchL();
extern int func_0017B230(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt18aEneChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xA) == 0) {
        stage_KillPlayBgAnimation(0x20, 0, 0);
        D_004D33A0[1] = (int)actSt18aSwitchL;
        gobj->unkC4 = D_004D33A0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x20, 0, -1);
    }
}

extern int D_004D33C0[];
extern void actSt18aSwitchR();

void actSt18aEne2Chk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xB) == 0) {
        stage_KillPlayBgAnimation(0x21, 0, 0);
        D_004D33C0[1] = (int)actSt18aSwitchR;
        gobj->unkC4 = D_004D33C0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x21, 0, -1);
    }
}

