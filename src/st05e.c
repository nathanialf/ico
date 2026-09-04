#include "common.h"

typedef struct GObjB4 { char pad[0xC4]; int *unkC4; } GObjB4;

extern void SetWayGroupActive(int a0, int a1);
extern int actSt25aQueenDeadChk(int a0);
extern int func_0017B230(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt05eSolarChk(void) {
    if (func_0017B230(0xEA) == 0) {
        stage_KillPlayBgAnimation(0x127, 0, 0);
        SetWayGroupActive(3, 0);
    } else {
        stage_KillPlayBgAnimation(0x127, 0, -1);
        SetWayGroupActive(3, 1);
    }
    if (func_0017B230(0xEB) == 0) {
        stage_KillPlayBgAnimation(0x128, 0, 0);
        SetWayGroupActive(4, 0);
    } else {
        stage_KillPlayBgAnimation(0x128, 0, -1);
        SetWayGroupActive(4, 1);
    }
    if (func_0017B230(0xE4) == 0) {
        stage_KillPlayBgAnimation(0x129, 0, 0);
        stage_KillPlayBgAnimation(0x13D, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x129, 0, -1);
        stage_KillPlayBgAnimation(0x13D, 0, -1);
    }
    if (func_0017B230(0xF9) == 0) {
        stage_KillPlayBgAnimation(0x130, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x130, 0, -1);
    }
    if (func_0017B230(0xFA) == 0) {
        stage_KillPlayBgAnimation(0x131, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x131, 0, -1);
    }
    if (func_0017B230(0xFB) == 0) {
        stage_KillPlayBgAnimation(0x132, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x132, 0, -1);
    }
    if (func_0017B230(0xFC) == 0) {
        stage_KillPlayBgAnimation(0x133, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x133, 0, -1);
    }
    if (func_0017B230(0xFD) == 0) {
        stage_KillPlayBgAnimation(0x134, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x134, 0, -1);
    }
    if (func_0017B230(0xFE) == 0) {
        stage_KillPlayBgAnimation(0x135, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x135, 0, -1);
    }
    if (func_0017B230(0xFF) == 0) {
        stage_KillPlayBgAnimation(0x136, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x136, 0, -1);
    }
    if (func_0017B230(0x94) != 0 && func_0017B230(0xD1) == 0) {
        stage_KillPlayBgAnimation(0x13A, 0, -1);
    }
    if (func_0017B230(0x94) == 0 || func_0017B230(0xD1) != 0) {
        stage_KillPlayBgAnimation(0x13A, 0, 0);
    }
    if (func_0017B230(0x101) != 0) {
        stage_KillPlayBgAnimation(0xC9, 0, 0xC8);
    } else {
        stage_KillPlayBgAnimation(0xC9, 0, 0);
    }
    if (func_0017B230(0xCF) == 0) {
        *(int *)(actSt25aQueenDeadChk(0x549) + 0x16C) = 0;
    } else {
        *(int *)(actSt25aQueenDeadChk(0x548) + 0x16C) = 0;
    }
}

extern void SetWayGroupActive(int a0, int a1);
extern int func_0017B230(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt05eWater(void) {
    if (func_0017B230(0xCE) == 0) {
        SetWayGroupActive(5, 0);
    } else {
        SetWayGroupActive(5, 1);
    }
    if (func_0017B230(0xEA) == 0) {
        stage_KillPlayBgAnimation(0x127, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x127, 0, -1);
    }
    if (func_0017B230(0xEB) == 0) {
        stage_KillPlayBgAnimation(0x128, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x128, 0, -1);
    }
}

extern int D_00274EC0[];
extern int D_006325B4;
extern int D_00633A04;
extern void _ACTWait(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern int func_0012AA80(int a0);
extern void func_0017B258(int a0);
extern void lt_fade_status(int a0);
extern void scpActivateAllWithKind(void);
extern void scpDispOnAllWithKind(void);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);

void actSt05eSolar(volatile int a0) {
    lt_fade_status(0x33);
    scpDispOnAllWithKind();
    func_0017B258(0xE1);
    _ACTWait(0x3C);
    scpPlayStart(0x50, (int)&D_00633A04, 1, 1, 1);
    while (D_00633A04 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x11C, 1, 0);
    while (func_0012AA80(0x11C) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x518) + 0x16C) = 1;
    *(int *)(actSt25aQueenDeadChk(0x519) + 0x16C) = 1;
    _ACTWait((0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1] * 6);
    scpActivateAllWithKind();
    D_006325B4 = 0;
    lt_fade_status(0x32);
}

extern int D_00633A08;

void actSt05eWaterMain(volatile int a0) {
    lt_fade_status(0x33);
    scpDispOnAllWithKind();
    func_0017B258(0xE2);
    _ACTWait(0x3C);
    scpPlayStart(0x50, (int)&D_00633A08, 1, 1, 1);
    while (D_00633A08 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x11D, 1, 0);
    while (func_0012AA80(0x11D) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x566) + 0x16C) = 1;
    *(int *)(actSt25aQueenDeadChk(0x567) + 0x16C) = 1;
    _ACTWait((0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1] * 6);
    scpActivateAllWithKind();
    D_006325B4 = 0;
    lt_fade_status(0x32);
}

extern int D_006325B4;
extern int D_00633A0C;
extern void _ACTWait(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern int func_0012AA80(int a0);
extern void func_0017B258(int a0);
extern void lt_fade_status(int a0);
extern void scpActivateAllWithKind(void);
extern void scpDispOnAllWithKind(void);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);

void actSt05eWaterSwitch(volatile int a0) {
    lt_fade_status(0x33);
    scpDispOnAllWithKind();
    func_0017B258(0xE3);
    _ACTWait(0x3C);
    scpPlayStart(0x50, (int)&D_00633A0C, 1, 1, 1);
    while (D_00633A0C == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x11E, 1, 0);
    while (func_0012AA80(0x11E) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x568) + 0x16C) = 1;
    *(int *)(actSt25aQueenDeadChk(0x569) + 0x16C) = 1;
    scpActivateAllWithKind();
    D_006325B4 = 0;
    lt_fade_status(0x32);
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D1F90[];
extern int D_00631B14;
extern int actInitialize(int a0);
extern void func_00220378(volatile int a0);

void actSt05eWaterStop(volatile int a0) {
    int x = a0;
    GObjB4 *gobj = (GObjB4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xDB) == 0) {
        if (D_00631B14 == 0x1C) {
            stage_KillPlayBgAnimation(0x116, 0, 0);
        } else {
            stage_KillPlayBgAnimation(0x117, 0, 0);
        }
        D_004D1F90[1] = (int)func_00220378;
        gobj->unkC4 = D_004D1F90;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        if (D_00631B14 == 0x1C) {
            stage_KillPlayBgAnimation(0x116, 0, -1);
        } else {
            stage_KillPlayBgAnimation(0x117, 0, -1);
        }
        D_006325B4 = 0;
    }
}

extern int D_00631AEC;
extern int D_00633A10;
extern int D_00633A28;
extern unsigned char D_00633A2C;
extern void iosPadActVolumeSet(int a0, int a1);
extern void Vibration_ShotDecode(int a0);
extern int func_0012AB50(int a0, int a1, int a2);
extern void func_0017B288(int a0);
extern int iosPadDevRead(int a0, int a1);
extern int scpIsTorchLightOn(int a0);

void actSt05eWaterFlagOn(volatile int a0) {
    while (scpIsTorchLightOn(0x518) == 0 || scpIsTorchLightOn(0x519) == 0 ||
           func_0017B230(0xE1) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpDispOnAllWithKind();
    scpPlayStart(0x1A, (int)&D_00633A10, 0, 1, 1);
    while (D_00633A10 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x114, 1, 0);
    while (func_0012AB50(0x114, 0x1E, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_00633A28 = iosPadDevRead(D_00631AEC, 0xA);
    D_00633A2C = 0x80;
    iosPadActVolumeSet(D_00633A28, 0x80);
    while (func_0012AB50(0x114, 0xBE, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    Vibration_ShotDecode(D_00633A28);
    while (func_0012AA80(0x114) == 0) { _ACTWait(1); }
    _ACTWait(1);
    scpActivateAllWithKind();
    lt_fade_status(0x32);
    D_006325B4 = 0;
    _ACTWait(1);
    func_0017B258(0xDA);
    func_0017B258(0xDD);
    func_0017B288(0xDE);
    func_0017B288(0xE0);
    func_0017B288(0xD0);
}

INCLUDE_ASM("asm/nonmatchings/src/st05e", func_00220378);

INCLUDE_ASM("asm/nonmatchings/src/st05e", func_00220670);

INCLUDE_ASM("asm/nonmatchings/src/st05e", func_00220858);

INCLUDE_ASM("asm/nonmatchings/src/st05e", func_002209C8);

INCLUDE_ASM("asm/nonmatchings/src/st05e", func_00220B00);

INCLUDE_ASM("asm/nonmatchings/src/st05e", func_00220DD0);

INCLUDE_ASM("asm/nonmatchings/src/st05e", func_002210C0);

INCLUDE_ASM("asm/nonmatchings/src/st05e", func_00221200);

INCLUDE_ASM("asm/nonmatchings/src/st05e", func_00221340);

INCLUDE_ASM("asm/nonmatchings/src/st05e", func_00221470);

INCLUDE_ASM("asm/nonmatchings/src/st05e", func_002215B0);

INCLUDE_ASM("asm/nonmatchings/src/st05e", func_002216F0);

INCLUDE_ASM("asm/nonmatchings/src/st05e", func_00221820);

INCLUDE_ASM("asm/nonmatchings/src/st05e", func_00221978);

