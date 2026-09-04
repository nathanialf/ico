#include "common.h"

typedef struct ActB4Obj {
    char pad[0xB4];
    int *unkB4;
} ActB4Obj;
extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_00629E14;
extern int D_004CC5A0[];
extern void actSt04eInit(volatile int a0);

void actSt04cInit(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x9C) == 0) {
        if (D_00629E14 == 0x13) {
            stage_KillPlayBgAnimation(0xB2, 0, 0);
        } else {
            stage_KillPlayBgAnimation(0xB3, 0, 0);
        }
        D_004CC5A0[1] = (int)actSt04eInit;
        gobj->unkB4 = D_004CC5A0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        if (D_00629E14 == 0x13) {
            stage_KillPlayBgAnimation(0xB2, 0, -1);
        } else {
            stage_KillPlayBgAnimation(0xB3, 0, -1);
        }
    }
}


extern int scpIsTorchLightOn(int a0);
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void func_0018F940(void);
extern int fightSoundClose(void);
extern void scpPlayStart(int a0, void *a1, int a2, int a3, int a4);
extern void func_0017A0F8(int a0);
extern void func_00178DD8(int a0);
extern int func_0012AA28(int a0, int a1, int a2);
extern int iosPadDevRead(int a0, int a1);
extern int iosPadActVolumeSet(int a0, int a1);
extern void Vibration_ShotDecode(int a0);
extern int func_0012A958(int a0);
extern void scpActivateAllWithKind(void);
extern void RequestStageChange(int a0, int a1, int a2, float f0, float f1);
extern int D_0062A894;
extern int D_0062BCD4;
extern unsigned char D_0062BCFC;
extern int D_0062BCF8;
extern int D_00629DEC;
extern int D_00629DE4;
extern int D_00629DE8;
void actSt04dInit(volatile int a0) {
    while (scpIsTorchLightOn(0x3FF) == 0 || scpIsTorchLightOn(0x400) == 0 ||
           func_00178DB0(0x9E) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpDispOnAllWithKind();
    func_0018F940();
    while (fightSoundClose() != 0) {
        _ACTWait(1);
    }
    scpPlayStart(0x1A, &D_0062BCD4, 0, 1, 1);
    while (D_0062BCD4 == 0) {
        _ACTWait(1);
    }
    func_0017A0F8(3);
    func_00178DD8(0x9B);
    func_00178DD8(0xCC);
    stage_KillPlayBgAnimation(0xDF, 1, 0);
    stage_KillPlayBgAnimation(0xB0, 1, 0);
    while (func_0012AA28(0xB0, 0x1E, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    {
        int pad = iosPadDevRead(D_00629DEC, 0xA);
        D_0062BCFC = 0x80;
        D_0062BCF8 = pad;
        iosPadActVolumeSet(pad, 0x80);
    }
    while (func_0012AA28(0xB0, 0xBE, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Vibration_ShotDecode(D_0062BCF8);
    while (func_0012A958(0xB0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpActivateAllWithKind();
    RequestStageChange(3, D_00629DE4, D_00629DE8, 2.0f, 8.0f);
}


extern int actSt25aQueenDeadChk(int a0);
extern int D_0062BCD8;
void actSt04eInit(volatile int a0) {
    if (D_00629E14 == 0x13) {
        while (scpIsTorchLightOn(0x403) == 0 || scpIsTorchLightOn(0x404) == 0 ||
               func_00178DB0(0x9F) == 0) {
            _ACTWait(1);
        }
    }
    if (D_00629E14 == 0x14) {
        while (scpIsTorchLightOn(0x451) == 0 || scpIsTorchLightOn(0x452) == 0 ||
               func_00178DB0(0x9F) == 0) {
            _ACTWait(1);
        }
    }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpDispOnAllWithKind();
    scpPlayStart(0x19, &D_0062BCD8, 1, 1, 1);
    while (D_0062BCD8 == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0x9C);
    if (D_00629E14 == 0x13) {
        stage_KillPlayBgAnimation(0xB2, 1, 0);
        while (func_0012AA28(0xB2, 0x1E, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        {
            int pad = iosPadDevRead(D_00629DEC, 0xA);
            D_0062BCFC = 0x80;
            D_0062BCF8 = pad;
            iosPadActVolumeSet(pad, 0x80);
        }
        while (func_0012AA28(0xB2, 0xBE, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        Vibration_ShotDecode(D_0062BCF8);
        while (func_0012A958(0xB2) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        *(int *)(actSt25aQueenDeadChk(0x407) + 0x16C) = 1;
    } else {
        stage_KillPlayBgAnimation(0xB3, 1, 0);
        while (func_0012AA28(0xB3, 0x1E, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        {
            int pad = iosPadDevRead(D_00629DEC, 0xA);
            D_0062BCFC = 0x80;
            D_0062BCF8 = pad;
            iosPadActVolumeSet(pad, 0x80);
        }
        while (func_0012AA28(0xB3, 0xBE, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        Vibration_ShotDecode(D_0062BCF8);
        while (func_0012A958(0xB3) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
    }
    lt_fade_status(0x32);
    D_0062A894 = 0;
    scpActivateAllWithKind();
}


extern int scpIsTorchLightOn(int a0);
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void scpPlayStart(int a0, void *a1, int a2, int a3, int a4);
extern void func_00178DD8(int a0);
extern int func_0012AA28(int a0, int a1, int a2);
extern int iosPadDevRead(int a0, int a1);
extern int iosPadActVolumeSet(int a0, int a1);
extern void Vibration_ShotDecode(int a0);
extern int func_0012A958(int a0);
extern void scpActivateAllWithKind(void);
extern int D_0062A894;
extern int D_0062BCDC;
extern unsigned char D_0062BCFC;
extern int D_0062BCF8;
extern int D_00629DEC;
void actSt04lC1BallTurn(volatile int a0) {
    int pad;
    while (scpIsTorchLightOn(0x453) == 0 || scpIsTorchLightOn(0x454) == 0 ||
           func_00178DB0(0xA0) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpDispOnAllWithKind();
    scpPlayStart(0x17, &D_0062BCDC, 0, 1, 1);
    while (D_0062BCDC == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0x9D);
    stage_KillPlayBgAnimation(0xB4, 1, 0);
    while (func_0012AA28(0xB4, 0x1E, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    pad = iosPadDevRead(D_00629DEC, 0xA);
    D_0062BCFC = 0x80;
    D_0062BCF8 = pad;
    iosPadActVolumeSet(pad, 0x80);
    while (func_0012AA28(0xB4, 0xBE, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Vibration_ShotDecode(D_0062BCF8);
    while (func_0012A958(0xB4) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_0062A894 = 0;
    scpActivateAllWithKind();
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lC2BallTurn);

extern int actSt25aQueenDeadChk(int a0);
extern int fallDownStartSE(int a0);
extern int func_0012A958(int a0);
extern void func_00178DD8(int a0);
void actSt04lC3BallTurn(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (func_00178DB0(0xA5) == 0) {
        int r = fallDownStartSE(actSt25aQueenDeadChk(0x43D));
        switch (r) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_KillPlayBgAnimation(0xBF, 1, 0);
            while (func_0012A958(0xBF) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        case 2:
            *(int *)(actSt25aQueenDeadChk(0x43D) + 0x16C) = 0;
            func_00178DD8(0xA5);
            stage_KillPlayBgAnimation(0xBB, 1, 0);
            while (func_0012A958(0xBB) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        }
    }
}


extern int actSt25aQueenDeadChk(int a0);
extern int fallDownStartSE(int a0);
extern int func_0012A958(int a0);
extern void func_00178DD8(int a0);
void actSt04lCrest02(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (func_00178DB0(0xA6) == 0) {
        int r = fallDownStartSE(actSt25aQueenDeadChk(0x43E));
        switch (r) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_KillPlayBgAnimation(0xC0, 1, 0);
            while (func_0012A958(0xC0) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        case 2:
            *(int *)(actSt25aQueenDeadChk(0x43E) + 0x16C) = 0;
            func_00178DD8(0xA6);
            stage_KillPlayBgAnimation(0xBC, 1, 0);
            while (func_0012A958(0xBC) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        }
    }
}


extern void lt_fade_status(int a0);
extern void scpPlayStart(int a0, void *a1, int a2, int a3, int a4);
extern int iosPadDevRead(int a0, int a1);
extern int func_0012A958(int a0);
extern void func_00178DD8(int a0);
extern void scpDispOnAllWithKind(void);
extern void scpActivateAllWithKind(void);
extern int func_0012AA28(int a0, int a1, int a2);
extern int D_00629DEC;
extern int D_0062BCE8;
extern int D_0062A894;
void actSt04lCrestMain(volatile int a0) {
    while (func_00178DB0(0xA5) == 0 || func_00178DB0(0xA6) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpDispOnAllWithKind();
    func_00178DD8(0xA3);
    _ACTWait(0x3C);
    scpPlayStart(0x54, &D_0062BCE8, 1, 1, 1);
    while (D_0062BCE8 == 0) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0xC3, 1, 0);
    while (func_0012AA28(0xC3, 0x4B, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x10);
    while (func_0012A958(0xC3) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}


void actSt04lCrest2Main(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (func_00178DB0(0xA7) == 0) {
        int r = fallDownStartSE(actSt25aQueenDeadChk(0x43F));
        switch (r) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_KillPlayBgAnimation(0xC1, 1, 0);
            while (func_0012A958(0xC1) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        case 2:
            *(int *)(actSt25aQueenDeadChk(0x43F) + 0x16C) = 0;
            func_00178DD8(0xA7);
            stage_KillPlayBgAnimation(0xBD, 1, 0);
            while (func_0012A958(0xBD) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        }
    }
}


void actSt04lCrest3Main(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (func_00178DB0(0xA8) == 0) {
        int r = fallDownStartSE(actSt25aQueenDeadChk(0x440));
        switch (r) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_KillPlayBgAnimation(0xC2, 1, 0);
            while (func_0012A958(0xC2) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        case 2:
            *(int *)(actSt25aQueenDeadChk(0x440) + 0x16C) = 0;
            func_00178DD8(0xA8);
            stage_KillPlayBgAnimation(0xBE, 1, 0);
            while (func_0012A958(0xBE) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        }
    }
}


extern void lt_fade_status(int a0);
extern void scpPlayStart(int a0, void *a1, int a2, int a3, int a4);
extern int iosPadDevRead(int a0, int a1);
extern int func_0012A958(int a0);
extern void func_00178DD8(int a0);
extern void scpDispOnAllWithKind(void);
extern void scpActivateAllWithKind(void);
extern int func_0012AA28(int a0, int a1, int a2);
extern int D_00629DEC;
extern int D_0062BCE8;
extern int D_0062A894;
void actSt04lStairChk(volatile int a0) {
    while (func_00178DB0(0xA7) == 0 || func_00178DB0(0xA8) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpDispOnAllWithKind();
    func_00178DD8(0xA4);
    _ACTWait(0x3C);
    scpPlayStart(0x54, &D_0062BCE8, 1, 1, 1);
    while (D_0062BCE8 == 0) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0xC4, 1, 0);
    while (func_0012AA28(0xC4, 0x4B, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x10);
    while (func_0012A958(0xC4) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lRope1Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lRope2Chk);


#include "common.h"
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void gflagOff(int a0, int a1);
extern void func_00178DD8(int a0);
extern void scpDispOnAllWithKind(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern int func_0012AA28(int a0, int a1, int a2);
extern void scpActivateAllWithKind(void);
extern int D_00629DE4;
extern int D_00629DE8;
extern int D_0062A894;
void actSt04lBrg1Chk(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x1000000) == 0 ||
           scpSleepSpiderGroupOne(D_00629DE8, 0x1000000) == 0) {
        _ACTWait(1);
    }
    D_0062A894 = 1;
    gflagOff(D_00629DE4, 0);
    gflagOff(D_00629DE8, 0x202);
    func_00178DD8(0xC0);
    scpDispOnAllWithKind();
    _ACTWait(5);
    stage_KillPlayBgAnimation(0xCD, 1, 0);
    soundSeDefPlayWithVolumeRate(0x51C, 0, 0, 1);
    while (func_0012AA28(0xCD, 0x1E, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
}

#include "common.h"
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void gflagOff(int a0, int a1);
extern void func_00178DD8(int a0);
extern void scpDispOnAllWithKind(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern int func_0012AA28(int a0, int a1, int a2);
extern void scpActivateAllWithKind(void);
extern int D_00629DE4;
extern int D_00629DE8;
extern int D_0062A894;
void actSt04lRope3Chk(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x2000000) == 0 ||
           scpSleepSpiderGroupOne(D_00629DE8, 0x2000000) == 0) {
        _ACTWait(1);
    }
    D_0062A894 = 1;
    gflagOff(D_00629DE4, 0);
    gflagOff(D_00629DE8, 0x202);
    func_00178DD8(0xC1);
    scpDispOnAllWithKind();
    _ACTWait(5);
    stage_KillPlayBgAnimation(0xCE, 1, 0);
    soundSeDefPlayWithVolumeRate(0x51C, 0, 0, 1);
    while (func_0012AA28(0xCE, 0x1E, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
}

#include "common.h"
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void gflagOff(int a0, int a1);
extern void func_00178DD8(int a0);
extern void scpDispOnAllWithKind(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern int func_0012AA28(int a0, int a1, int a2);
extern void scpActivateAllWithKind(void);
extern int D_00629DE4;
extern int D_00629DE8;
extern int D_0062A894;
void actSt04lRope4Chk(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x3000000) == 0 ||
           scpSleepSpiderGroupOne(D_00629DE8, 0x3000000) == 0) {
        _ACTWait(1);
    }
    D_0062A894 = 1;
    gflagOff(D_00629DE4, 0);
    gflagOff(D_00629DE8, 0x202);
    func_00178DD8(0xC2);
    scpDispOnAllWithKind();
    _ACTWait(5);
    stage_KillPlayBgAnimation(0xCF, 1, 0);
    soundSeDefPlayWithVolumeRate(0x51C, 0, 0, 1);
    while (func_0012AA28(0xCF, 0x1E, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
}

#include "common.h"
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void gflagOff(int a0, int a1);
extern void func_00178DD8(int a0);
extern void scpDispOnAllWithKind(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern int func_0012AA28(int a0, int a1, int a2);
extern void scpActivateAllWithKind(void);
extern int D_00629DE4;
extern int D_00629DE8;
extern int D_0062A894;
void actSt04lBrg2Chk(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x4000000) == 0 ||
           scpSleepSpiderGroupOne(D_00629DE8, 0x4000000) == 0) {
        _ACTWait(1);
    }
    D_0062A894 = 1;
    gflagOff(D_00629DE4, 0);
    gflagOff(D_00629DE8, 0x202);
    func_00178DD8(0xC3);
    scpDispOnAllWithKind();
    _ACTWait(5);
    stage_KillPlayBgAnimation(0xD0, 1, 0);
    soundSeDefPlayWithVolumeRate(0x51C, 0, 0, 1);
    while (func_0012AA28(0xD0, 0x1E, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
}

#include "common.h"
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void gflagOff(int a0, int a1);
extern void func_00178DD8(int a0);
extern void scpDispOnAllWithKind(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern int func_0012AA28(int a0, int a1, int a2);
extern void scpActivateAllWithKind(void);
extern int D_00629DE4;
extern int D_00629DE8;
extern int D_0062A894;
void actSt04lSekizoChk(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x5000000) == 0 ||
           scpSleepSpiderGroupOne(D_00629DE8, 0x5000000) == 0) {
        _ACTWait(1);
    }
    D_0062A894 = 1;
    gflagOff(D_00629DE4, 0);
    gflagOff(D_00629DE8, 0x202);
    func_00178DD8(0xC4);
    scpDispOnAllWithKind();
    _ACTWait(5);
    stage_KillPlayBgAnimation(0xD1, 1, 0);
    soundSeDefPlayWithVolumeRate(0x51C, 0, 0, 1);
    while (func_0012AA28(0xD1, 0x1E, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
}

#include "common.h"
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void gflagOff(int a0, int a1);
extern void func_00178DD8(int a0);
extern void scpDispOnAllWithKind(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern int func_0012AA28(int a0, int a1, int a2);
extern void scpActivateAllWithKind(void);
extern int D_00629DE4;
extern int D_00629DE8;
extern int D_0062A894;
void actSt04lGondolaChk(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x6000000) == 0 ||
           scpSleepSpiderGroupOne(D_00629DE8, 0x6000000) == 0) {
        _ACTWait(1);
    }
    D_0062A894 = 1;
    gflagOff(D_00629DE4, 0);
    gflagOff(D_00629DE8, 0x202);
    func_00178DD8(0xC5);
    scpDispOnAllWithKind();
    _ACTWait(5);
    stage_KillPlayBgAnimation(0xD2, 1, 0);
    soundSeDefPlayWithVolumeRate(0x51C, 0, 0, 1);
    while (func_0012AA28(0xD2, 0x1E, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
}

#include "common.h"
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void gflagOff(int a0, int a1);
extern void func_00178DD8(int a0);
extern void scpDispOnAllWithKind(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern int func_0012AA28(int a0, int a1, int a2);
extern void scpActivateAllWithKind(void);
extern int D_00629DE4;
extern int D_00629DE8;
extern int D_0062A894;
void actSt04lMonyou01Chk(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x7000000) == 0 ||
           scpSleepSpiderGroupOne(D_00629DE8, 0x7000000) == 0) {
        _ACTWait(1);
    }
    D_0062A894 = 1;
    gflagOff(D_00629DE4, 0);
    gflagOff(D_00629DE8, 0x202);
    func_00178DD8(0xC6);
    scpDispOnAllWithKind();
    _ACTWait(5);
    stage_KillPlayBgAnimation(0xD3, 1, 0);
    soundSeDefPlayWithVolumeRate(0x51C, 0, 0, 1);
    while (func_0012AA28(0xD3, 0x1E, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
}

extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern int actItouQueenAttackChk(void);
extern int scpTriggerBall(int a0, int a1, float f);
extern void scpDispOnAllWithKind(void);
extern void lt_fade_status(int a0);
extern void gflagOff(int a0, int a1);
extern void iosOmSendMail(int a0, int a1, int a2);
extern void func_00178DD8(int a0);
extern void scpPlayStart(int a0, void *a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012AA28(int a0, int a1, int a2);
extern int iosPadDevRead(int a0, int a1);
extern int func_0012A958(int a0);
extern void scpActivateAllWithKind(void);
extern int D_00629DE4;
extern int D_00629DE8;
extern int D_00629DEC;
extern int D_0062A894;
extern int D_0062BCF0;

void actSt04lMonyou02Chk(volatile int a0) {
    while (func_00178DB0(0x9C) == 0 || actItouQueenAttackChk() != 4 || scpTriggerBall(a0, D_00629DE4, 1000.0f) == 0) {
        _ACTWait(1);
    }
    scpDispOnAllWithKind();
    lt_fade_status(0x33);
    D_0062A894 = 1;
    gflagOff(D_00629DE4, 0);
    if (D_00629DE8 != 0) {
        iosOmSendMail(D_00629DE8, 0x3A, D_00629DE4);
    }
    func_00178DD8(0xB4);
    _ACTWait(0x3C);
    scpPlayStart(0x3C, &D_0062BCF0, 1, 1, 1);
    while (D_0062BCF0 == 0) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0xD6, 1, 0);
    stage_KillPlayBgAnimation(0xD8, 1, 0);
    stage_KillPlayBgAnimation(0xD7, 1, 0);
    while (func_0012AA28(0xD6, 0x5A, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0xF);
    while (func_0012A958(0xD6) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lMonyou03Chk);

