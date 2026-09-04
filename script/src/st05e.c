#include "common.h"

extern int func_00178DB0(int a0);
extern void SetWayGroupActive(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int actSt25aQueenDeadChk(int a0);
void actSt05eSolarChk(void) {
    if (func_00178DB0(0xEA) == 0) {
        stage_KillPlayBgAnimation(0x126, 0, 0);
        SetWayGroupActive(3, 0);
    } else {
        stage_KillPlayBgAnimation(0x126, 0, -1);
        SetWayGroupActive(3, 1);
    }
    if (func_00178DB0(0xEB) == 0) {
        stage_KillPlayBgAnimation(0x127, 0, 0);
        SetWayGroupActive(4, 0);
    } else {
        stage_KillPlayBgAnimation(0x127, 0, -1);
        SetWayGroupActive(4, 1);
    }
    if (func_00178DB0(0xE4) == 0) {
        stage_KillPlayBgAnimation(0x128, 0, 0);
        stage_KillPlayBgAnimation(0x13C, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x128, 0, -1);
        stage_KillPlayBgAnimation(0x13C, 0, -1);
    }
    if (func_00178DB0(0xF9) == 0) {
        stage_KillPlayBgAnimation(0x12F, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x12F, 0, -1);
    }
    if (func_00178DB0(0xFA) == 0) {
        stage_KillPlayBgAnimation(0x130, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x130, 0, -1);
    }
    if (func_00178DB0(0xFB) == 0) {
        stage_KillPlayBgAnimation(0x131, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x131, 0, -1);
    }
    if (func_00178DB0(0xFC) == 0) {
        stage_KillPlayBgAnimation(0x132, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x132, 0, -1);
    }
    if (func_00178DB0(0xFD) == 0) {
        stage_KillPlayBgAnimation(0x133, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x133, 0, -1);
    }
    if (func_00178DB0(0xFE) == 0) {
        stage_KillPlayBgAnimation(0x134, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x134, 0, -1);
    }
    if (func_00178DB0(0xFF) == 0) {
        stage_KillPlayBgAnimation(0x135, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x135, 0, -1);
    }
    if (func_00178DB0(0x94) != 0 && func_00178DB0(0xD1) == 0) {
        stage_KillPlayBgAnimation(0x139, 0, -1);
    }
    if (func_00178DB0(0x94) == 0 || func_00178DB0(0xD1) != 0) {
        stage_KillPlayBgAnimation(0x139, 0, 0);
    }
    if (func_00178DB0(0x101) != 0) {
        stage_KillPlayBgAnimation(0xC8, 0, 0xC8);
    } else {
        stage_KillPlayBgAnimation(0xC8, 0, 0);
    }
    if (func_00178DB0(0xCF) == 0) {
        *(int *)(actSt25aQueenDeadChk(0x545) + 0x16C) = 0;
    } else {
        *(int *)(actSt25aQueenDeadChk(0x544) + 0x16C) = 0;
    }
}

extern int func_00178DB0(int a0);
extern void SetWayGroupActive(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt05eWater(void) {
    if (func_00178DB0(0xCE) == 0) {
        SetWayGroupActive(5, 0);
    } else {
        SetWayGroupActive(5, 1);
    }
    if (func_00178DB0(0xEA) == 0) {
        stage_KillPlayBgAnimation(0x126, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x126, 0, -1);
    }
    if (func_00178DB0(0xEB) == 0) {
        stage_KillPlayBgAnimation(0x127, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x127, 0, -1);
    }
}

extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void func_00178DD8(int a0);
extern void _ACTWait(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern int func_0012A958(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void scpActivateAllWithKind(void);
extern int D_0062BD0C;
extern int D_00271240[];
extern int D_0062A894;
void actSt05eSolar(volatile int a0) {
    lt_fade_status(0x33);
    scpDispOnAllWithKind();
    func_00178DD8(0xE1);
    _ACTWait(0x3C);
    scpPlayStart(0x50, (int)&D_0062BD0C, 1, 1, 1);
    while (D_0062BD0C == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x11B, 1, 0);
    while (func_0012A958(0x11B) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x514) + 0x16C) = 1;
    *(int *)(actSt25aQueenDeadChk(0x515) + 0x16C) = 1;
    _ACTWait((0x3C - D_00271240[0] * 0xA) / D_00271240[1] * 6);
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}


extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void func_00178DD8(int a0);
extern void _ACTWait(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern int func_0012A958(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void scpActivateAllWithKind(void);
extern int D_0062BD10;
extern int D_00271240[];
extern int D_0062A894;
void actSt05eWaterMain(volatile int a0) {
    lt_fade_status(0x33);
    scpDispOnAllWithKind();
    func_00178DD8(0xE2);
    _ACTWait(0x3C);
    scpPlayStart(0x50, (int)&D_0062BD10, 1, 1, 1);
    while (D_0062BD10 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x11C, 1, 0);
    while (func_0012A958(0x11C) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x560) + 0x16C) = 1;
    *(int *)(actSt25aQueenDeadChk(0x561) + 0x16C) = 1;
    _ACTWait((0x3C - D_00271240[0] * 0xA) / D_00271240[1] * 6);
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}

#include "common.h"
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void func_00178DD8(int a0);
extern void _ACTWait(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void scpActivateAllWithKind(void);
extern int D_0062BD14;
extern int D_0062A894;
void actSt05eWaterSwitch(volatile int a0) {
    lt_fade_status(0x33);
    scpDispOnAllWithKind();
    func_00178DD8(0xE3);
    _ACTWait(0x3C);
    scpPlayStart(0x50, (int)&D_0062BD14, 1, 1, 1);
    while (D_0062BD14 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x11D, 1, 0);
    while (func_0012A958(0x11D) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x562) + 0x16C) = 1;
    *(int *)(actSt25aQueenDeadChk(0x563) + 0x16C) = 1;
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}

typedef struct GObjB4 { char pad[0xB4]; int *unkB4; } GObjB4;
extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void BoxBarSoundOn(int a0, int a1);
extern void func_0021D370(volatile int a0);
extern int D_00629E14;
extern int D_0062A894;
extern int D_004CCBA0[];
void actSt05eWaterStop(volatile int a0) {
    int x = a0;
    GObjB4 *gobj = (GObjB4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xDB) == 0) {
        if (D_00629E14 == 0x1C) {
            stage_KillPlayBgAnimation(0x115, 0, 0);
        } else {
            stage_KillPlayBgAnimation(0x116, 0, 0);
        }
        D_004CCBA0[1] = (int)func_0021D370;
        gobj->unkB4 = D_004CCBA0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        if (D_00629E14 == 0x1C) {
            stage_KillPlayBgAnimation(0x115, 0, -1);
        } else {
            stage_KillPlayBgAnimation(0x116, 0, -1);
        }
        D_0062A894 = 0;
    }
}


extern void _ACTWait(int a0);
extern int scpIsTorchLightOn(int a0);
extern int func_00178DB0(int a0);
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012AA28(int a0, int a1, int a2);
extern int iosPadDevRead(int a0, int a1);
extern void iosPadActVolumeSet(int a0, int a1);
extern void Vibration_ShotDecode(int a0);
extern int func_0012A958(int a0);
extern void scpActivateAllWithKind(void);
extern void func_00178DD8(int a0);
extern void func_00178E08(int a0);
extern int D_0062A894;
extern int D_0062BD18;
extern int D_00629DEC;
extern unsigned char D_0062BD34;
extern int D_0062BD30;
void actSt05eWaterFlagOn(volatile int a0) {
    while (scpIsTorchLightOn(0x514) == 0 || scpIsTorchLightOn(0x515) == 0 ||
           func_00178DB0(0xE1) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpDispOnAllWithKind();
    scpPlayStart(0x1A, (int)&D_0062BD18, 0, 1, 1);
    while (D_0062BD18 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x113, 1, 0);
    while (func_0012AA28(0x113, 0x1E, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_0062BD30 = iosPadDevRead(D_00629DEC, 0xA);
    D_0062BD34 = 0x80;
    iosPadActVolumeSet(D_0062BD30, 0x80);
    while (func_0012AA28(0x113, 0xBE, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    Vibration_ShotDecode(D_0062BD30);
    while (func_0012A958(0x113) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    lt_fade_status(0x32);
    D_0062A894 = 0;
    _ACTWait(1);
    func_00178DD8(0xDA);
    func_00178DD8(0xDD);
    func_00178E08(0xDE);
    func_00178E08(0xE0);
    func_00178E08(0xD0);
}

extern void _ACTWait(int a0);
extern int scpIsTorchLightOn(int a0);
extern int func_00178DB0(int a0);
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012AA28(int a0, int a1, int a2);
extern int iosPadDevRead(int a0, int a1);
extern void iosPadActVolumeSet(int a0, int a1);
extern void Vibration_ShotDecode(int a0);
extern int func_0012A958(int a0);
extern void func_00178DD8(int a0);
extern void scpActivateAllWithKind(void);
extern void func_00178E08(int a0);
extern int D_00629E14;
extern int D_0062A894;
extern int D_0062BD1C;
extern int D_00629DEC;
extern unsigned char D_0062BD34;
extern int D_0062BD30;
void func_0021D370(volatile int a0) {
    if (D_00629E14 == 0x1C) {
        while (scpIsTorchLightOn(0x518) == 0 || scpIsTorchLightOn(0x519) == 0 ||
               func_00178DB0(0xE2) == 0) { _ACTWait(1); }
    }
    if (D_00629E14 == 0x1D) {
        while (scpIsTorchLightOn(0x560) == 0 || scpIsTorchLightOn(0x561) == 0 ||
               func_00178DB0(0xE2) == 0) { _ACTWait(1); }
    }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpDispOnAllWithKind();
    scpPlayStart(0x18, (int)&D_0062BD1C, 0, 1, 1);
    while (D_0062BD1C == 0) { _ACTWait(1); }
    if (D_00629E14 == 0x1C) {
        stage_KillPlayBgAnimation(0x115, 1, 0);
        while (func_0012AA28(0x115, 0x1E, 0) == 0) { _ACTWait(1); }
        _ACTWait(1);
        D_0062BD30 = iosPadDevRead(D_00629DEC, 0xA);
        D_0062BD34 = 0x80;
        iosPadActVolumeSet(D_0062BD30, 0x80);
        while (func_0012AA28(0x115, 0xBE, 0) == 0) { _ACTWait(1); }
        _ACTWait(1);
        Vibration_ShotDecode(D_0062BD30);
        while (func_0012A958(0x115) == 0) { _ACTWait(1); }
        _ACTWait(1);
        func_00178DD8(0xDF);
    } else {
        stage_KillPlayBgAnimation(0x116, 1, 0);
        while (func_0012AA28(0x116, 0x1E, 0) == 0) { _ACTWait(1); }
        _ACTWait(1);
        D_0062BD30 = iosPadDevRead(D_00629DEC, 0xA);
        D_0062BD34 = 0x80;
        iosPadActVolumeSet(D_0062BD30, 0x80);
        while (func_0012AA28(0x116, 0xBE, 0) == 0) { _ACTWait(1); }
        _ACTWait(1);
        Vibration_ShotDecode(D_0062BD30);
        while (func_0012A958(0x116) == 0) { _ACTWait(1); }
        _ACTWait(1);
        func_00178DD8(0xDE);
    }
    lt_fade_status(0x32);
    D_0062A894 = 0;
    scpActivateAllWithKind();
    _ACTWait(1);
    func_00178DD8(0xDB);
    func_00178E08(0xDD);
    func_00178E08(0xE0);
    func_00178E08(0xD0);
}

extern void _ACTWait(int a0);
extern int scpIsTorchLightOn(int a0);
extern int func_00178DB0(int a0);
extern void lt_fade_status(int a0);
extern void scpSleepEnemyOne(int a0);
extern void func_00178DD8(int a0);
extern void func_0018F940(void);
extern int fightSoundClose(void);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012AA28(int a0, int a1, int a2);
extern int iosPadDevRead(int a0, int a1);
extern void iosPadActVolumeSet(int a0, int a1);
extern void Vibration_ShotDecode(int a0);
extern int func_0012A958(int a0);
extern void scpWakeupEnemyOne(int a0);
extern void fightSoundProcess(void);
extern void func_00178E08(int a0);
extern int D_0062A894;
extern int D_0062BD20;
extern int D_00629DEC;
extern unsigned char D_0062BD34;
extern int D_0062BD30;
void func_0021D668(volatile int a0) {
    while (scpIsTorchLightOn(0x562) == 0 || scpIsTorchLightOn(0x563) == 0 ||
           func_00178DB0(0xE3) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpSleepEnemyOne(0xD57);
    func_00178DD8(0x98);
    func_0018F940();
    while (fightSoundClose() != 0) { _ACTWait(1); }
    scpPlayStart(0x17, (int)&D_0062BD20, 0, 1, 1);
    while (D_0062BD20 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x117, 1, 0);
    while (func_0012AA28(0x117, 0x1E, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_0062BD30 = iosPadDevRead(D_00629DEC, 0xA);
    D_0062BD34 = 0x80;
    iosPadActVolumeSet(D_0062BD30, 0x80);
    while (func_0012AA28(0x117, 0xBE, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    Vibration_ShotDecode(D_0062BD30);
    while (func_0012A958(0x117) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpWakeupEnemyOne(0xD57);
    D_0062A894 = 0;
    lt_fade_status(0x32);
    fightSoundProcess();
    _ACTWait(1);
    func_00178DD8(0xDC);
    func_00178E08(0xDD);
    func_00178E08(0xDE);
    func_00178DD8(0xE0);
    func_00178E08(0xD0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void gflagOff(int a0, int a1);
extern void func_00178DD8(int a0);
extern void scpFadeOut(int a0, int a1, int a2, float f12);
extern void scpFadeIn(float f12);
extern void BoxBarSoundOn(int a0, int a1);
extern void func_0021D9C0(volatile int a0);
extern int D_0062BD08;
extern int D_0062A894;
extern int D_00629DE4;
extern int D_004CCBE0[];
void func_0021D850(volatile int a0) {
    int x = a0;
    GObjB4 *gobj = (GObjB4 *)actInitialize(a0);
    _ACTWait(1);
    D_0062BD08 = 0;
    if (func_00178DB0(0xD1) == 0) {
        scpPlayStart(0x1B, (int)&D_0062BD08, 0, 1, 0);
        if (func_00178DB0(0xDA) != 0 && func_00178DB0(0xDB) != 0 &&
            func_00178DB0(0xDC) != 0 && func_00178DB0(0xCF) != 0) {
            if (D_00629DE4 != 0) {
                gflagOff(D_00629DE4, 0);
            }
            D_0062A894 = 1;
            func_00178DD8(0x163);
            scpFadeOut(0, 0, 0, 255.0f);
            while (D_0062BD08 == 0) { _ACTWait(1); }
            scpFadeIn(6.0f);
        }
        D_004CCBE0[1] = (int)func_0021D9C0;
        gobj->unkB4 = D_004CCBE0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        D_0062A894 = 0;
    }
}

extern int func_00178DB0(int a0);
extern void _ACTWait(int a0);
extern void func_00178DD8(int a0);
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void AdpcmClose(int a0);
extern void func_0017A0F8(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void scpActivateAllWithKind(void);
extern void RequestStageChange(int a0, int a1, int a2, float f12, float f13);
extern int D_0062A894;
extern int D_0062BD08;
extern int D_00629DE4;
extern int D_00629DE8;
void func_0021D9C0(volatile int a0) {
    while (func_00178DB0(0xDA) == 0 || func_00178DB0(0xDB) == 0 ||
           func_00178DB0(0xDC) == 0 || func_00178DB0(0xCF) == 0) { _ACTWait(1); }
    func_00178DD8(0xD1);
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpDispOnAllWithKind();
    while (D_0062BD08 == 0) { _ACTWait(1); }
    AdpcmClose(*(int *)(D_0062BD08 + 0x2C));
    func_0017A0F8(0xF);
    stage_KillPlayBgAnimation(0x138, 1, 0);
    stage_KillPlayBgAnimation(0x104, 1, 0);
    _ACTWait(0x1E);
    while (func_0012A958(0x104) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_0062A894 = 0;
    scpActivateAllWithKind();
    RequestStageChange(0xF, D_00629DE4, D_00629DE8, 2.0f, 8.0f);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021DAF8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021DDC8);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern int fallDownStartSE(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void func_00178DD8(int a0);
void func_0021E080(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (func_00178DB0(0xEC) == 0) {
        int st = fallDownStartSE(actSt25aQueenDeadChk(0x547));
        switch (st) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_KillPlayBgAnimation(0x122, 1, 0);
            while (func_0012A958(0x122) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        case 2:
            *(int *)(actSt25aQueenDeadChk(0x547) + 0x16C) = 0;
            func_00178DD8(0xEC);
            stage_KillPlayBgAnimation(0x11E, 1, 0);
            while (func_0012A958(0x11E) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        }
    }
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern int fallDownStartSE(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void func_00178DD8(int a0);
void func_0021E1C0(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (func_00178DB0(0xED) == 0) {
        int st = fallDownStartSE(actSt25aQueenDeadChk(0x548));
        switch (st) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_KillPlayBgAnimation(0x123, 1, 0);
            while (func_0012A958(0x123) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        case 2:
            *(int *)(actSt25aQueenDeadChk(0x548) + 0x16C) = 0;
            func_00178DD8(0xED);
            stage_KillPlayBgAnimation(0x11F, 1, 0);
            while (func_0012A958(0x11F) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        }
    }
}

extern int func_00178DB0(int a0);
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void func_00178DD8(int a0);
extern void _ACTWait(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012AA28(int a0, int a1, int a2);
extern int iosPadDevRead(int a0, int a1);
extern int func_0012A958(int a0);
extern void scpActivateAllWithKind(void);
extern int D_0062BD2C;
extern int D_00629DEC;
extern int D_0062A894;
void func_0021E300(volatile int a0) {
    while (func_00178DB0(0xEC) == 0 || func_00178DB0(0xED) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpDispOnAllWithKind();
    func_00178DD8(0xEA);
    _ACTWait(0x3C);
    scpPlayStart(0x54, (int)&D_0062BD2C, 1, 1, 1);
    while (D_0062BD2C == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x126, 1, 0);
    while (func_0012AA28(0x126, 0x4B, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x10);
    while (func_0012A958(0x126) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern int fallDownStartSE(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void func_00178DD8(int a0);
void func_0021E430(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (func_00178DB0(0xEE) == 0) {
        int st = fallDownStartSE(actSt25aQueenDeadChk(0x549));
        switch (st) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_KillPlayBgAnimation(0x124, 1, 0);
            while (func_0012A958(0x124) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        case 2:
            *(int *)(actSt25aQueenDeadChk(0x549) + 0x16C) = 0;
            func_00178DD8(0xEE);
            stage_KillPlayBgAnimation(0x120, 1, 0);
            while (func_0012A958(0x120) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        }
    }
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern int fallDownStartSE(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void func_00178DD8(int a0);
void func_0021E570(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (func_00178DB0(0xEF) == 0) {
        int st = fallDownStartSE(actSt25aQueenDeadChk(0x54A));
        switch (st) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_KillPlayBgAnimation(0x125, 1, 0);
            while (func_0012A958(0x125) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        case 2:
            *(int *)(actSt25aQueenDeadChk(0x54A) + 0x16C) = 0;
            func_00178DD8(0xEF);
            stage_KillPlayBgAnimation(0x121, 1, 0);
            while (func_0012A958(0x121) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        }
    }
}

extern int func_00178DB0(int a0);
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void func_00178DD8(int a0);
extern void _ACTWait(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012AA28(int a0, int a1, int a2);
extern int iosPadDevRead(int a0, int a1);
extern int func_0012A958(int a0);
extern void scpActivateAllWithKind(void);
extern int D_0062BD2C;
extern int D_00629DEC;
extern int D_0062A894;
void func_0021E6B0(volatile int a0) {
    while (func_00178DB0(0xEE) == 0 || func_00178DB0(0xEF) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpDispOnAllWithKind();
    func_00178DD8(0xEB);
    _ACTWait(0x3C);
    scpPlayStart(0x54, (int)&D_0062BD2C, 1, 1, 1);
    while (D_0062BD2C == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x127, 1, 0);
    while (func_0012AA28(0x127, 0x4B, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x10);
    while (func_0012A958(0x127) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
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
void func_0021E7E0(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x1000000) == 0 ||
           scpSleepSpiderGroupOne(D_00629DE8, 0x1000000) == 0) {
        _ACTWait(1);
    }
    D_0062A894 = 1;
    gflagOff(D_00629DE4, 0);
    gflagOff(D_00629DE8, 0x202);
    func_00178DD8(0xF9);
    scpDispOnAllWithKind();
    _ACTWait(5);
    stage_KillPlayBgAnimation(0x12F, 1, 0);
    soundSeDefPlayWithVolumeRate(0x51C, 0, 0, 1);
    while (func_0012AA28(0x12F, 0x1E, 0) == 0) { _ACTWait(1); }
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
void func_0021E8D8(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x2000000) == 0 ||
           scpSleepSpiderGroupOne(D_00629DE8, 0x2000000) == 0) {
        _ACTWait(1);
    }
    D_0062A894 = 1;
    gflagOff(D_00629DE4, 0);
    gflagOff(D_00629DE8, 0x202);
    func_00178DD8(0xFA);
    scpDispOnAllWithKind();
    _ACTWait(5);
    stage_KillPlayBgAnimation(0x130, 1, 0);
    soundSeDefPlayWithVolumeRate(0x51C, 0, 0, 1);
    while (func_0012AA28(0x130, 0x1E, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
}
