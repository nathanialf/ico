#include "common.h"

typedef struct ActB4Obj {
    char pad[0xC4];
    int *unkC4;
} ActB4Obj;

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D1990[];
extern int D_00631B14;
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void actSt04eInit(volatile int a0);
extern int func_0017B230(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt04cInit(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x9C) == 0) {
        if (D_00631B14 == 0x13) {
            stage_KillPlayBgAnimation(0xB3, 0, 0);
        } else {
            stage_KillPlayBgAnimation(0xB4, 0, 0);
        }
        D_004D1990[1] = (int)actSt04eInit;
        gobj->unkC4 = D_004D1990;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        if (D_00631B14 == 0x13) {
            stage_KillPlayBgAnimation(0xB3, 0, -1);
        } else {
            stage_KillPlayBgAnimation(0xB4, 0, -1);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/st04l", actSt04dInit);

extern int D_00631AEC;
extern int D_006325B4;
extern int D_006339D0;
extern int D_006339F0;
extern unsigned char D_006339F4;
extern int Shock_Request(int a0, int a1);
extern void Vibration_ShotDecode(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern int func_0012AA80(int a0);
extern int func_0012AB50(int a0, int a1, int a2);
extern void func_0017B258(int a0);
extern int iosPadDevRead(int a0, int a1);
extern void lt_fade_status(int a0);
extern void scpActivateAllWithKind(void);
extern void scpDispOnAllWithKind(void);
extern int scpDoorTypeUpUp(int a0);
extern void scpPlayStart(int a0, void *a1, int a2, int a3, int a4);

void actSt04eInit(volatile int a0) {
    if (D_00631B14 == 0x13) {
        while (scpDoorTypeUpUp(0x406) == 0 || scpDoorTypeUpUp(0x407) == 0 ||
               func_0017B230(0x9F) == 0) {
            _ACTWait(1);
        }
    }
    if (D_00631B14 == 0x14) {
        while (scpDoorTypeUpUp(0x454) == 0 || scpDoorTypeUpUp(0x455) == 0 ||
               func_0017B230(0x9F) == 0) {
            _ACTWait(1);
        }
    }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpDispOnAllWithKind();
    scpPlayStart(0x19, &D_006339D0, 1, 1, 1);
    while (D_006339D0 == 0) {
        _ACTWait(1);
    }
    func_0017B258(0x9C);
    if (D_00631B14 == 0x13) {
        stage_KillPlayBgAnimation(0xB3, 1, 0);
        while (func_0012AB50(0xB3, 0x1E, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        {
            int pad = iosPadDevRead(D_00631AEC, 0xA);
            D_006339F4 = 0x80;
            D_006339F0 = pad;
            Shock_Request(pad, 0x80);
        }
        while (func_0012AB50(0xB3, 0xBE, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        Vibration_ShotDecode(D_006339F0);
        while (func_0012AA80(0xB3) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        *(int *)(actSt25aQueenDeadChk(0x40A) + 0x16C) = 1;
    } else {
        stage_KillPlayBgAnimation(0xB4, 1, 0);
        while (func_0012AB50(0xB4, 0x1E, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        {
            int pad = iosPadDevRead(D_00631AEC, 0xA);
            D_006339F4 = 0x80;
            D_006339F0 = pad;
            Shock_Request(pad, 0x80);
        }
        while (func_0012AB50(0xB4, 0xBE, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        Vibration_ShotDecode(D_006339F0);
        while (func_0012AA80(0xB4) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
    }
    lt_fade_status(0x32);
    D_006325B4 = 0;
    scpActivateAllWithKind();
}

extern int D_00631AEC;
extern int D_006325B4;
extern int D_006339D4;
extern int D_006339F0;
extern unsigned char D_006339F4;
extern int Shock_Request(int a0, int a1);
extern void Vibration_ShotDecode(int a0);
extern int func_0012AA80(int a0);
extern int func_0012AB50(int a0, int a1, int a2);
extern void func_0017B258(int a0);
extern int iosPadDevRead(int a0, int a1);
extern void lt_fade_status(int a0);
extern void scpActivateAllWithKind(void);
extern void scpDispOnAllWithKind(void);
extern int scpDoorTypeUpUp(int a0);
extern void scpPlayStart(int a0, void *a1, int a2, int a3, int a4);

void actSt04lC1BallTurn(volatile int a0) {
    int pad;
    while (scpDoorTypeUpUp(0x456) == 0 || scpDoorTypeUpUp(0x457) == 0 ||
           func_0017B230(0xA0) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpDispOnAllWithKind();
    scpPlayStart(0x17, &D_006339D4, 0, 1, 1);
    while (D_006339D4 == 0) {
        _ACTWait(1);
    }
    func_0017B258(0x9D);
    stage_KillPlayBgAnimation(0xB5, 1, 0);
    while (func_0012AB50(0xB5, 0x1E, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    pad = iosPadDevRead(D_00631AEC, 0xA);
    D_006339F4 = 0x80;
    D_006339F0 = pad;
    Shock_Request(pad, 0x80);
    while (func_0012AB50(0xB5, 0xBE, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Vibration_ShotDecode(D_006339F0);
    while (func_0012AA80(0xB5) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_006325B4 = 0;
    scpActivateAllWithKind();
}

INCLUDE_ASM("asm/nonmatchings/src/st04l", actSt04lC2BallTurn);

extern int actSt25aQueenDeadChk(int a0);
extern int func_0012AA80(int a0);
extern void func_0017B258(int a0);
extern int func_001BC088(int a0);

void actSt04lC3BallTurn(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (func_0017B230(0xA5) == 0) {
        int r = func_001BC088(actSt25aQueenDeadChk(0x440));
        switch (r) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_KillPlayBgAnimation(0xC0, 1, 0);
            while (func_0012AA80(0xC0) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        case 2:
            *(int *)(actSt25aQueenDeadChk(0x440) + 0x16C) = 0;
            func_0017B258(0xA5);
            stage_KillPlayBgAnimation(0xBC, 1, 0);
            while (func_0012AA80(0xBC) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        }
    }
}

void actSt04lCrest02(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (func_0017B230(0xA6) == 0) {
        int r = func_001BC088(actSt25aQueenDeadChk(0x441));
        switch (r) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_KillPlayBgAnimation(0xC1, 1, 0);
            while (func_0012AA80(0xC1) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        case 2:
            *(int *)(actSt25aQueenDeadChk(0x441) + 0x16C) = 0;
            func_0017B258(0xA6);
            stage_KillPlayBgAnimation(0xBD, 1, 0);
            while (func_0012AA80(0xBD) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        }
    }
}

extern int D_00631AEC;
extern int D_006325B4;
extern int D_006339E0;
extern int func_0012AA80(int a0);
extern int func_0012AB50(int a0, int a1, int a2);
extern void func_0017B258(int a0);
extern int iosPadDevRead(int a0, int a1);
extern void lt_fade_status(int a0);
extern void scpActivateAllWithKind(void);
extern void scpDispOnAllWithKind(void);
extern void scpPlayStart(int a0, void *a1, int a2, int a3, int a4);

void actSt04lCrestMain(volatile int a0) {
    while (func_0017B230(0xA5) == 0 || func_0017B230(0xA6) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpDispOnAllWithKind();
    func_0017B258(0xA3);
    _ACTWait(0x3C);
    scpPlayStart(0x54, &D_006339E0, 1, 1, 1);
    while (D_006339E0 == 0) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0xC4, 1, 0);
    while (func_0012AB50(0xC4, 0x4B, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0x10);
    while (func_0012AA80(0xC4) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_006325B4 = 0;
    lt_fade_status(0x32);
}

void actSt04lCrest2Main(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (func_0017B230(0xA7) == 0) {
        int r = func_001BC088(actSt25aQueenDeadChk(0x442));
        switch (r) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_KillPlayBgAnimation(0xC2, 1, 0);
            while (func_0012AA80(0xC2) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        case 2:
            *(int *)(actSt25aQueenDeadChk(0x442) + 0x16C) = 0;
            func_0017B258(0xA7);
            stage_KillPlayBgAnimation(0xBE, 1, 0);
            while (func_0012AA80(0xBE) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        }
    }
}

void actSt04lCrest3Main(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (func_0017B230(0xA8) == 0) {
        int r = func_001BC088(actSt25aQueenDeadChk(0x443));
        switch (r) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_KillPlayBgAnimation(0xC3, 1, 0);
            while (func_0012AA80(0xC3) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        case 2:
            *(int *)(actSt25aQueenDeadChk(0x443) + 0x16C) = 0;
            func_0017B258(0xA8);
            stage_KillPlayBgAnimation(0xBF, 1, 0);
            while (func_0012AA80(0xBF) == 0) { _ACTWait(1); }
            _ACTWait(1);
            break;
        }
    }
}

void actSt04lStairChk(volatile int a0) {
    while (func_0017B230(0xA7) == 0 || func_0017B230(0xA8) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpDispOnAllWithKind();
    func_0017B258(0xA4);
    _ACTWait(0x3C);
    scpPlayStart(0x54, &D_006339E0, 1, 1, 1);
    while (D_006339E0 == 0) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0xC5, 1, 0);
    while (func_0012AB50(0xC5, 0x4B, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0x10);
    while (func_0012AA80(0xC5) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_006325B4 = 0;
    lt_fade_status(0x32);
}

INCLUDE_ASM("asm/nonmatchings/src/st04l", actSt04lRope1Chk);

INCLUDE_ASM("asm/nonmatchings/src/st04l", actSt04lRope2Chk);

INCLUDE_ASM("asm/nonmatchings/src/st04l", actSt04lBrg1Chk);

INCLUDE_ASM("asm/nonmatchings/src/st04l", actSt04lRope3Chk);

INCLUDE_ASM("asm/nonmatchings/src/st04l", actSt04lRope4Chk);

INCLUDE_ASM("asm/nonmatchings/src/st04l", actSt04lBrg2Chk);

INCLUDE_ASM("asm/nonmatchings/src/st04l", actSt04lSekizoChk);

INCLUDE_ASM("asm/nonmatchings/src/st04l", actSt04lGondolaChk);

INCLUDE_ASM("asm/nonmatchings/src/st04l", actSt04lMonyou01Chk);

extern int D_00631AE4;
extern int D_00631AE8;
extern int D_006339E8;
extern int actItouQueenAttackChk(void);
extern void gflagOff(int a0, int a1);
extern void iosOmBeforeFuncStandard(int a0, int a1, int a2);
extern int scpSleepEnemyOne(int a0, int a1, float f);

void actSt04lMonyou02Chk(volatile int a0) {
    while (func_0017B230(0x9C) == 0 || actItouQueenAttackChk() != 4 || scpSleepEnemyOne(a0, D_00631AE4, 1000.0f) == 0) {
        _ACTWait(1);
    }
    scpDispOnAllWithKind();
    lt_fade_status(0x33);
    D_006325B4 = 1;
    gflagOff(D_00631AE4, 0);
    if (D_00631AE8 != 0) {
        iosOmBeforeFuncStandard(D_00631AE8, 0x3B, D_00631AE4);
    }
    func_0017B258(0xB4);
    _ACTWait(0x3C);
    scpPlayStart(0x3C, &D_006339E8, 1, 1, 1);
    while (D_006339E8 == 0) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0xD7, 1, 0);
    stage_KillPlayBgAnimation(0xD9, 1, 0);
    stage_KillPlayBgAnimation(0xD8, 1, 0);
    while (func_0012AB50(0xD7, 0x5A, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0xF);
    while (func_0012AA80(0xD7) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_006325B4 = 0;
    lt_fade_status(0x32);
}

INCLUDE_ASM("asm/nonmatchings/src/st04l", actSt04lMonyou03Chk);

