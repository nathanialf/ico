#include "common.h"

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void *actSt25aQueenDeadChk(int a0);

typedef struct GObj {
    char pad[0xB4];
    int *unkB4;
} GObj;

extern int actItouQueenAttackChk(void);
extern int scpSleepEnemyOne(int a0, int a1, float a2);
extern int GetSkeltonFocusNode(int a0);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern void func_00178DD8(int a0);
extern int func_0012AA28(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern int D_00629DE4;

void actSt05eEnd(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (1) {
        if (actItouQueenAttackChk() == 4 &&
            scpSleepEnemyOne(a0, D_00629DE4, 100.0f) != 0 &&
            (GetSkeltonFocusNode(D_00629DE4) == 0x25 ||
             GetSkeltonFocusNode(D_00629DE4) == 0x2A ||
             GetSkeltonFocusNode(D_00629DE4) == 0x2C ||
             GetSkeltonFocusNode(D_00629DE4) == 0x26 ||
             GetSkeltonFocusNode(D_00629DE4) == 0x27 ||
             GetSkeltonFocusNode(D_00629DE4) == 0x3C))
            break;
        _ACTWait(1);
    }
    func_00178DD8(0xB6);
    stage_KillPlayBgAnimation(0xDA, 1, 0);
    soundSeDefPlayWithVolumeRate(0x513, 0, 0, 1);
    while (func_0012AA28(0xDA, 0x2D, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    soundSeDefPlayWithVolumeRate(0x514, 0, 0, 1);
    while (func_0012A958(0xDA) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}


extern int D_004CC920[];
extern void actSt05dInit(volatile int a0);

void actSt05cInit(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xB7) == 0) {
        D_004CC920[1] = (int)actSt05dInit;
        gobj->unkB4 = D_004CC920;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xD6, -1, -2);
        stage_KillPlayBgAnimation(0xD8, -1, -2);
        stage_KillPlayBgAnimation(0xD7, -1, -2);
        stage_KillPlayBgAnimation(0xDB, 0, -1);
        stage_KillPlayBgAnimation(0xDA, 0, -1);
        stage_KillPlayBgAnimation(0xD9, 0, -1);
    }
}


extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void scpDispOnAllWithKind(void);
extern void iosPadDevRead(int a0, int a1);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern int func_0012AA28(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void scpActivateAllWithKind(void);
extern int D_00629DEC;
extern int D_0062BCF4;
extern int D_0062A894;

void actSt05dInit(volatile int a0) {
    while (func_00178DB0(0xB5) == 0 || func_00178DB0(0xB6) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    func_00178DD8(0xB7);
    scpDispOnAllWithKind();
    iosPadDevRead(D_00629DEC, 0x11);
    _ACTWait(0x1E);
    scpPlayStart(0x3D, &D_0062BCF4, 1, 1, 1);
    while (D_0062BCF4 == 0) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0xDB, 1, 0);
    while (func_0012AA28(0xDB, 0x1E, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0xF);
    while (func_0012A958(0xDB) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}


extern int D_004CC580[];
extern void actSt04dInit(void);
extern int D_0062A894;

void actSt05eInit(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x9B) == 0) {
        stage_KillPlayBgAnimation(0xB0, 0, 0);
        D_004CC580[1] = (int)actSt04dInit;
        gobj->unkB4 = D_004CC580;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xB0, 0, -1);
        D_0062A894 = 0;
    }
}


extern int D_004CC5C0[];
extern void actSt04lC1BallTurn(void);

void actSt04rC1BallTurn(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x9D) == 0) {
        stage_KillPlayBgAnimation(0xB4, 0, 0);
        D_004CC5C0[1] = (int)actSt04lC1BallTurn;
        gobj->unkB4 = D_004CC5C0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xB4, 0, -1);
    }
}


extern int D_004CC480[];
extern void actSt05cEne(void);

void actSt04rC2BallTurn(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x9E) == 0) {
        *(int *)((char *)actSt25aQueenDeadChk(0x3FF) + 0x16C) = 0;
        *(int *)((char *)actSt25aQueenDeadChk(0x400) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0xB8, 0, 0);
        D_004CC480[1] = (int)actSt05cEne;
        gobj->unkB4 = D_004CC480;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xB8, 0, -1);
    }
}


extern int D_004CC4E0[];
extern void actSt05cEnemy1(void);

void actSt04rC3BallTurn(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x9F) == 0) {
        *(int *)((char *)actSt25aQueenDeadChk(0x451) + 0x16C) = 0;
        *(int *)((char *)actSt25aQueenDeadChk(0x452) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0xB9, 0, 0);
        D_004CC4E0[1] = (int)actSt05cEnemy1;
        gobj->unkB4 = D_004CC4E0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xB9, 0, -1);
    }
}


extern int D_004CC540[];
extern void actSt05cEnemy2(void);

void actSt04rCrest02(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xA0) == 0) {
        *(int *)((char *)actSt25aQueenDeadChk(0x453) + 0x16C) = 0;
        *(int *)((char *)actSt25aQueenDeadChk(0x454) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0xBA, 0, 0);
        D_004CC540[1] = (int)actSt05cEnemy2;
        gobj->unkB4 = D_004CC540;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xBA, 0, -1);
    }
}


extern int D_004CC600[];
extern void actSt04lC2BallTurn(void);
extern int D_00629DE8;

void actSt04rCrestMain(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xA1) == 0) {
        if (D_00629DE8 != 0) {
            D_004CC600[1] = (int)actSt04lC2BallTurn;
            gobj->unkB4 = D_004CC600;
            BoxBarSoundOn(a0, 0x189);
            _ACTWait(0);
        }
    } else {
        *(int *)((char *)actSt25aQueenDeadChk(0x479) + 0x16C) = 0;
        stage_KillPlayBgAnimation(0xE6, -1, -2);
    }
}


extern int D_004CC660[];
extern void actSt04lCrestMain(void);

void actSt04rCrest2Main(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xA3) == 0) {
        D_004CC660[1] = (int)actSt04lCrestMain;
        gobj->unkB4 = D_004CC660;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CC6C0[];
extern void actSt04lStairChk(void);

void actSt04rCrest3Main(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xA4) == 0) {
        D_004CC6C0[1] = (int)actSt04lStairChk;
        gobj->unkB4 = D_004CC6C0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}

extern int D_004CC6E0[];
extern void func_0021C300(void);

void actSt04rSolarBeam(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xA3) == 0) {
        D_004CC6E0[1] = (int)func_0021C300;
        gobj->unkB4 = D_004CC6E0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}

extern int D_004CC700[];
extern void func_0021C348(void);

void actSt04rSolarBeamChk(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xA4) == 0) {
        D_004CC700[1] = (int)func_0021C348;
        gobj->unkB4 = D_004CC700;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CC620[];
extern void actSt04lC3BallTurn(void);

void actSt04rStairChk(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xA5) == 0) {
        stage_KillPlayBgAnimation(0xBB, 0, 0);
        D_004CC620[1] = (int)actSt04lC3BallTurn;
        gobj->unkB4 = D_004CC620;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xBB, 0, -1);
        *(int *)((char *)actSt25aQueenDeadChk(0x43D) + 0x16C) = 0;
    }
}


extern int D_004CC640[];
extern void actSt04lCrest02(void);

void actSt04rSekizoChk(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xA6) == 0) {
        stage_KillPlayBgAnimation(0xBC, 0, 0);
        D_004CC640[1] = (int)actSt04lCrest02;
        gobj->unkB4 = D_004CC640;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xBC, 0, -1);
        *(int *)((char *)actSt25aQueenDeadChk(0x43E) + 0x16C) = 0;
    }
}


extern int D_004CC680[];
extern void actSt04lCrest2Main(void);

void actSt04rRope1Chk(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xA7) == 0) {
        stage_KillPlayBgAnimation(0xBD, 0, 0);
        D_004CC680[1] = (int)actSt04lCrest2Main;
        gobj->unkB4 = D_004CC680;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xBD, 0, -1);
        *(int *)((char *)actSt25aQueenDeadChk(0x43F) + 0x16C) = 0;
    }
}


extern int D_004CC6A0[];
extern void actSt04lCrest3Main(void);

void actSt04rRope2Chk(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xA8) == 0) {
        stage_KillPlayBgAnimation(0xBE, 0, 0);
        D_004CC6A0[1] = (int)actSt04lCrest3Main;
        gobj->unkB4 = D_004CC6A0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xBE, 0, -1);
        *(int *)((char *)actSt25aQueenDeadChk(0x440) + 0x16C) = 0;
    }
}


extern int D_004CC720[];
extern void actSt04lRope1Chk(void);

void actSt04rBrg1Chk(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xA9) == 0) {
        stage_KillPlayBgAnimation(0xC5, 0, 0);
        D_004CC720[1] = (int)actSt04lRope1Chk;
        gobj->unkB4 = D_004CC720;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xC5, 0, -1);
    }
}


extern int D_004CC740[];
extern void actSt05dDoor2(void);
extern int D_00629DE8;

void actSt04rRope3Chk(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xAA) == 0) {
        stage_KillPlayBgAnimation(0xC9, 0, 0);
        if (D_00629DE8 != 0) {
            D_004CC740[1] = (int)actSt05dDoor2;
            gobj->unkB4 = D_004CC740;
            BoxBarSoundOn(a0, 0x189);
            _ACTWait(0);
        }
    } else {
        stage_KillPlayBgAnimation(0xC9, 0, -1);
    }
}


extern int D_004CC8C0[];
extern void actSt04lMonyou02Chk(void);

void actSt04rRope4Chk(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xB4) == 0) {
        stage_KillPlayBgAnimation(0xD6, 0, 0);
        stage_KillPlayBgAnimation(0xD8, 0, 0);
        stage_KillPlayBgAnimation(0xD7, 0, 0);
        D_004CC8C0[1] = (int)actSt04lMonyou02Chk;
        gobj->unkB4 = D_004CC8C0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CC8E0[];
extern void actSt04lMonyou03Chk(void);

void actSt04rBrg2Chk(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xB5) == 0) {
        D_004CC8E0[1] = (int)actSt04lMonyou03Chk;
        gobj->unkB4 = D_004CC8E0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}

