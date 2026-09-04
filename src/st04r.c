#include "common.h"

typedef struct GObj__p4 {
    char pad[0xC4];
    int *unkC4;
} GObj__p4;

extern int D_00631AE4;
extern int GetSkeltonFocusNode(int a0);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern int actItouQueenAttackChk(void);
extern int func_0012AA80(int a0);
extern int func_0012AB50(int a0, int a1, int a2);
extern void func_0017B258(int a0);
extern int scpTriggerBall(int a0, int a1, float a2);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt05eEnd(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (1) {
        if (actItouQueenAttackChk() == 4 &&
            scpTriggerBall(a0, D_00631AE4, 100.0f) != 0 &&
            (GetSkeltonFocusNode(D_00631AE4) == 0x25 ||
             GetSkeltonFocusNode(D_00631AE4) == 0x2A ||
             GetSkeltonFocusNode(D_00631AE4) == 0x2C ||
             GetSkeltonFocusNode(D_00631AE4) == 0x26 ||
             GetSkeltonFocusNode(D_00631AE4) == 0x27 ||
             GetSkeltonFocusNode(D_00631AE4) == 0x3C))
            break;
        _ACTWait(1);
    }
    func_0017B258(0xB6);
    stage_KillPlayBgAnimation(0xDB, 1, 0);
    soundSeDefPlayWithVolumeRate(0x513, 0, 0, 1);
    while (func_0012AB50(0xDB, 0x2D, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    soundSeDefPlayWithVolumeRate(0x514, 0, 0, 1);
    while (func_0012AA80(0xDB) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D1D10[];
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void actSt05dInit(volatile int a0);
extern int func_0017B230(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt05cInit(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xB7) == 0) {
        D_004D1D10[1] = (int)actSt05dInit;
        gobj->unkC4 = D_004D1D10;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xD7, -1, -2);
        stage_KillPlayBgAnimation(0xD9, -1, -2);
        stage_KillPlayBgAnimation(0xD8, -1, -2);
        stage_KillPlayBgAnimation(0xDC, 0, -1);
        stage_KillPlayBgAnimation(0xDB, 0, -1);
        stage_KillPlayBgAnimation(0xDA, 0, -1);
    }
}

extern int D_00631AEC;
extern int D_006325B4;
extern int D_006339EC;
extern int func_0012AA80(int a0);
extern int func_0012AB50(int a0, int a1, int a2);
extern void func_0017B258(int a0);
extern void iosPadDevRead(int a0, int a1);
extern void lt_fade_status(int a0);
extern void scpActivateAllWithKind(void);
extern void scpDispOnAllWithKind(void);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);

void actSt05dInit(volatile int a0) {
    while (func_0017B230(0xB5) == 0 || func_0017B230(0xB6) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    func_0017B258(0xB7);
    scpDispOnAllWithKind();
    iosPadDevRead(D_00631AEC, 0x11);
    _ACTWait(0x1E);
    scpPlayStart(0x3D, &D_006339EC, 1, 1, 1);
    while (D_006339EC == 0) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0xDC, 1, 0);
    while (func_0012AB50(0xDC, 0x1E, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0xF);
    while (func_0012AA80(0xDC) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_006325B4 = 0;
    lt_fade_status(0x32);
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D1970[];
extern int D_006325B4;
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void actSt04dInit(void);
extern int func_0017B230(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt05eInit(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x9B) == 0) {
        stage_KillPlayBgAnimation(0xB1, 0, 0);
        D_004D1970[1] = (int)actSt04dInit;
        gobj->unkC4 = D_004D1970;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xB1, 0, -1);
        D_006325B4 = 0;
    }
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D19B0[];
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void actSt04lC1BallTurn(void);
extern int func_0017B230(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt04rC1BallTurn(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x9D) == 0) {
        stage_KillPlayBgAnimation(0xB5, 0, 0);
        D_004D19B0[1] = (int)actSt04lC1BallTurn;
        gobj->unkC4 = D_004D19B0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xB5, 0, -1);
    }
}

extern int D_004D1870[];
extern void actSt05cEne(void);
extern void *actSt25aQueenDeadChk(int a0);

void actSt04rC2BallTurn(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x9E) == 0) {
        *(int *)((char *)actSt25aQueenDeadChk(0x402) + 0x16C) = 0;
        *(int *)((char *)actSt25aQueenDeadChk(0x403) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0xB9, 0, 0);
        D_004D1870[1] = (int)actSt05cEne;
        gobj->unkC4 = D_004D1870;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xB9, 0, -1);
    }
}

extern int D_004D18D0[];
extern void actSt05cEnemy1(void);

void actSt04rC3BallTurn(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x9F) == 0) {
        *(int *)((char *)actSt25aQueenDeadChk(0x454) + 0x16C) = 0;
        *(int *)((char *)actSt25aQueenDeadChk(0x455) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0xBA, 0, 0);
        D_004D18D0[1] = (int)actSt05cEnemy1;
        gobj->unkC4 = D_004D18D0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xBA, 0, -1);
    }
}

extern int D_004D1930[];
extern void actSt05cEnemy2(void);

void actSt04rCrest02(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xA0) == 0) {
        *(int *)((char *)actSt25aQueenDeadChk(0x456) + 0x16C) = 0;
        *(int *)((char *)actSt25aQueenDeadChk(0x457) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0xBB, 0, 0);
        D_004D1930[1] = (int)actSt05cEnemy2;
        gobj->unkC4 = D_004D1930;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xBB, 0, -1);
    }
}

extern int D_004D19F0[];
extern int D_00631AE8;
extern void actSt04lC2BallTurn(void);
extern void *actSt25aQueenDeadChk(int a0);

void actSt04rCrestMain(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xA1) == 0) {
        if (D_00631AE8 != 0) {
            D_004D19F0[1] = (int)actSt04lC2BallTurn;
            gobj->unkC4 = D_004D19F0;
            BoxBarSoundOn(a0, 0x18D);
            _ACTWait(0);
        }
    } else {
        *(int *)((char *)actSt25aQueenDeadChk(0x47C) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0xE7, -1, -2);
    }
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D1A50[];
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void actSt04lCrestMain(void);
extern int func_0017B230(int a0);

void actSt04rCrest2Main(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xA3) == 0) {
        D_004D1A50[1] = (int)actSt04lCrestMain;
        gobj->unkC4 = D_004D1A50;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D1AB0[];
extern void actSt04lStairChk(void);

void actSt04rCrest3Main(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xA4) == 0) {
        D_004D1AB0[1] = (int)actSt04lStairChk;
        gobj->unkC4 = D_004D1AB0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D1AD0[];
extern void func_0021F308(void);

void actSt04rSolarBeam(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xA3) == 0) {
        D_004D1AD0[1] = (int)func_0021F308;
        gobj->unkC4 = D_004D1AD0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D1AF0[];
extern void func_0021F350(void);

void actSt04rSolarBeamChk(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xA4) == 0) {
        D_004D1AF0[1] = (int)func_0021F350;
        gobj->unkC4 = D_004D1AF0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D1A10[];
extern void actSt04lC3BallTurn(void);

void actSt04rStairChk(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xA5) == 0) {
        stage_KillPlayBgAnimation(0xBC, 0, 0);
        D_004D1A10[1] = (int)actSt04lC3BallTurn;
        gobj->unkC4 = D_004D1A10;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xBC, 0, -1);
        *(int *)((char *)actSt25aQueenDeadChk(0x440) + 0x16C) = 0;
    }
}

extern int D_004D1A30[];
extern void actSt04lCrest02(void);

void actSt04rSekizoChk(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xA6) == 0) {
        stage_KillPlayBgAnimation(0xBD, 0, 0);
        D_004D1A30[1] = (int)actSt04lCrest02;
        gobj->unkC4 = D_004D1A30;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xBD, 0, -1);
        *(int *)((char *)actSt25aQueenDeadChk(0x441) + 0x16C) = 0;
    }
}

extern int D_004D1A70[];
extern void actSt04lCrest2Main(void);

void actSt04rRope1Chk(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xA7) == 0) {
        stage_KillPlayBgAnimation(0xBE, 0, 0);
        D_004D1A70[1] = (int)actSt04lCrest2Main;
        gobj->unkC4 = D_004D1A70;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xBE, 0, -1);
        *(int *)((char *)actSt25aQueenDeadChk(0x442) + 0x16C) = 0;
    }
}

extern int D_004D1A90[];
extern void actSt04lCrest3Main(void);

void actSt04rRope2Chk(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xA8) == 0) {
        stage_KillPlayBgAnimation(0xBF, 0, 0);
        D_004D1A90[1] = (int)actSt04lCrest3Main;
        gobj->unkC4 = D_004D1A90;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xBF, 0, -1);
        *(int *)((char *)actSt25aQueenDeadChk(0x443) + 0x16C) = 0;
    }
}

extern int D_004D1B10[];
extern void actSt04lRope1Chk(void);

void actSt04rBrg1Chk(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xA9) == 0) {
        stage_KillPlayBgAnimation(0xC6, 0, 0);
        D_004D1B10[1] = (int)actSt04lRope1Chk;
        gobj->unkC4 = D_004D1B10;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xC6, 0, -1);
    }
}

extern int D_004D1B30[];
extern int D_00631AE8;
extern void actSt05dDoor2(void);

void actSt04rRope3Chk(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xAA) == 0) {
        stage_KillPlayBgAnimation(0xCA, 0, 0);
        if (D_00631AE8 != 0) {
            D_004D1B30[1] = (int)actSt05dDoor2;
            gobj->unkC4 = D_004D1B30;
            BoxBarSoundOn(a0, 0x18D);
            _ACTWait(0);
        }
    } else {
        stage_KillPlayBgAnimation(0xCA, 0, -1);
    }
}

extern int D_004D1CB0[];
extern void actSt04lMonyou02Chk(void);

void actSt04rRope4Chk(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xB4) == 0) {
        stage_KillPlayBgAnimation(0xD7, 0, 0);
        stage_KillPlayBgAnimation(0xD9, 0, 0);
        stage_KillPlayBgAnimation(0xD8, 0, 0);
        D_004D1CB0[1] = (int)actSt04lMonyou02Chk;
        gobj->unkC4 = D_004D1CB0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D1CD0[];
extern void actSt04lMonyou03Chk(void);

void actSt04rBrg2Chk(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xB5) == 0) {
        D_004D1CD0[1] = (int)actSt04lMonyou03Chk;
        gobj->unkC4 = D_004D1CD0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

