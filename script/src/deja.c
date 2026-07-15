#include "common.h"

typedef struct GObj {
    char pad[0xB4];
    int *unkB4;
} GObj;
extern int actInitialize(int a0);
extern void BoxBarSoundOn(int a0, int a1);

extern void _ACTWait(int a0);
extern void actCreateSubThread(void *fn, int a1);
extern void actDejaDemo(volatile int a0);
extern int func_00178DB0(int a0);
extern int func_00178DD8(int a0);
extern void debug_assertMessage(int *a0);
extern int D_00614380[];
extern int D_0062BBF4;
extern void AdpcmClose(int a0);
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f);
extern int actSt25aQueenDeadEvent(void);
extern void actSt25aQueenDead(int a0, int a1, int a2, float f12, float f13);
extern int D_002715D0[];
extern int D_00629DE4;

void actDejaChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    actCreateSubThread(actDejaDemo, 0x15);
    while (func_00178DB0(0x143) != 0 || (D_002715D0[1] & 0x840) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0x144);
    debug_assertMessage(D_00614380);
    AdpcmClose(*(int *)(D_0062BBF4 + 0x2C));
    actSt25aQueenBeforeChk(0, 0, 0, 4.0f);
    while (actSt25aQueenDeadEvent() != 0) {
        _ACTWait(1);
    }
    actSt25aQueenDead(1, D_00629DE4, 0, 255.0f, 16.0f);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", actDejaDemo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", actDejaAfter);

extern void func_0017C0B8(void);
extern void gflagOff(int a0, int a1);
extern void lt_fade_status(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_00629DE8;
extern int D_004CB640[];
extern void actE3St13cInit(volatile int a0);

void actDejaAfterChk(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (D_00629DE8 == 0) {
        func_0017C0B8();
    }
    if (func_00178DB0(0x145) == 0) {
        if (D_00629DE4 != 0) {
            gflagOff(D_00629DE4, 0);
        }
        actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
        lt_fade_status(0x33);
        stage_KillPlayBgAnimation(0x1F, 0, 0);
        stage_KillPlayBgAnimation(0x19, 0, -1);
        stage_KillPlayBgAnimation(0x22, 0, 0);
        stage_KillPlayBgAnimation(0x20, 0, 0);
        stage_KillPlayBgAnimation(0x23, 0, 0);
        stage_KillPlayBgAnimation(0x25, 0, 0);
        D_004CB640[1] = (int)actE3St13cInit;
        gobj->unkB4 = D_004CB640;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x1F, 0, -1);
        stage_KillPlayBgAnimation(0x19, 0, -1);
        stage_KillPlayBgAnimation(0x22, 0, 0);
        stage_KillPlayBgAnimation(0x20, 0, 0);
        stage_KillPlayBgAnimation(0x23, 0, 0);
        stage_KillPlayBgAnimation(0x25, 0, 0);
    }
}


extern void _ACTWait(int a0);
extern void iosSemaWait(int a0, int a1);
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f);
extern int actSt25aQueenDeadEvent(void);
extern void soundSeVolSet(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void actConte11Jimaku(float f);
extern void actCreateSubThread(void *fn, int a1);
extern void actE3CageFall(volatile int a0);
extern int D_0062C294;
extern int D_0062C290;
extern int D_0062BBF8;
extern int D_002715D0[];

void actDeja(volatile int a0) {
    while (D_0062C294 == 0 || (D_002715D0[1] & 0x800) == 0) {
        _ACTWait(1);
    }
    iosSemaWait(D_0062C290 + 0x24, 0x22);
    actSt25aQueenBeforeChk(0, 0, 0, 8.0f);
    while (actSt25aQueenDeadEvent() != 0) {
        _ACTWait(1);
    }
    soundSeVolSet(D_0062BBF8);
    stage_KillPlayBgAnimation(0x1F, 0, -1);
    stage_KillPlayBgAnimation(0x19, 0, -1);
    stage_KillPlayBgAnimation(0x20A, -1, -2);
    stage_KillPlayBgAnimation(0x20F, -1, -2);
    stage_KillPlayBgAnimation(0x211, -1, -2);
    stage_KillPlayBgAnimation(0x212, -1, -2);
    stage_KillPlayBgAnimation(0x213, -1, -2);
    stage_KillPlayBgAnimation(0x214, -1, -2);
    stage_KillPlayBgAnimation(0x215, -1, -2);
    stage_KillPlayBgAnimation(0x216, -1, -2);
    stage_KillPlayBgAnimation(0x228, 1, 0);
    actConte11Jimaku(6.0f);
    actCreateSubThread(actE3CageFall, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", actEnemySleep);

extern void AddWayPointTop(int a0, int a1);
extern int func_00178DB0(int a0);

void func_00205BA8(void) {
    AddWayPointTop(7, 0);
    if (func_00178DB0(0x147) != 0) {
        AddWayPointTop(9, 0);
    }
}

extern void actSt25aGenerator(void *a0, float f12, float f13, float f14);
extern int D_004CB710[];
extern void func_00205CE8(volatile int a0);
extern int D_00629DE8;

void func_00205BE8(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x147) == 0) {
        stage_KillPlayBgAnimation(0x3F, 0, 0);
        stage_KillPlayBgAnimation(0x3B, 0, -1);
        if (D_00629DE8 == 0) {
            _ACTWait(0);
        }
        actSt25aGenerator((void *)D_00629DE8, -30.0f, -436.0f, -1.0f);
        D_004CB710[1] = (int)func_00205CE8;
        gobj->unkB4 = D_004CB710;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x3F, 0, 0);
        stage_KillPlayBgAnimation(0x3D, 0, -1);
        stage_KillPlayBgAnimation(0x3E, 0, -1);
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00205CE8);


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00205E18);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00206128);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_002064E8);


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_002065F8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_002068A8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00206A20);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00206D70);

extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void func_00206F18(void) {
    stage_KillPlayBgAnimation(0xA1, 0, -1);
}

extern void InitSceneObjects(int a0);
extern void gflagOff(int a0, int a1);
extern int D_0062B320;
extern int D_00629C90;
extern int D_0062A894;
extern int D_00629DE4;
extern int D_004CB5E0[];
extern int func_00204F18[];

void func_00206F28(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
    D_0062B320 = 0;
    _ACTWait(1);
    D_0062A894 = 1;
    InitSceneObjects(D_00629C90);
    actConte11Jimaku(6.0f);
    if (D_00629DE4 != 0) {
        gflagOff(D_00629DE4, 0);
    }
    D_004CB5E0[1] = (int)func_00204F18;
    gobj->unkB4 = D_004CB5E0;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern void stgmgrForceSwitchWithFade(int a0);
extern void actDejaAfter(volatile int a0);
extern int D_004CB620[];

typedef struct { char _p0[0xA0]; short f_A0; char _p1[0x190 - 0xA2]; } DejaStgTbl;
typedef struct { char _p0[0x24]; int f_24; } DejaStgEnt;
extern DejaStgTbl D_005EBC48[];
extern DejaStgEnt D_0055A2D8[];

void func_00206FE0(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    D_0062A894 = 1;
    if (D_00629DE4 != 0) {
        gflagOff(D_00629DE4, 0);
    }
    {
        short s = ((DejaStgTbl *)(D_00629C90 * 0x190 + (char *)D_005EBC48))->f_A0;
        stgmgrForceSwitchWithFade(D_0055A2D8[s].f_24);
    }
    D_004CB620[1] = (int)actDejaAfter;
    gobj->unkB4 = D_004CB620;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern int D_004CB680[];
extern void actE3CageFallChk(volatile int a0);

void func_00207098(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x146) == 0) {
        stage_KillPlayBgAnimation(0x31F, 0, 0);
        D_004CB680[1] = (int)actE3CageFallChk;
        gobj->unkB4 = D_004CB680;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x31F, 0, -1);
    }
}


extern int D_004CB6F0[];
extern void actE3St09aSekizo(volatile int a0);

void func_00207130(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x147) == 0) {
        D_004CB6F0[1] = (int)actE3St09aSekizo;
        gobj->unkB4 = D_004CB6F0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_00629DE8;
extern void func_0017C0B8(void);
extern int D_004CB6D0[];
extern void actE3CageFallEffect(volatile int a0);

void func_002071A8(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (D_00629DE8 == 0) {
        func_0017C0B8();
    }
    if (func_00178DB0(0x14A) == 0) {
        D_004CB6D0[1] = (int)actE3CageFallEffect;
        gobj->unkB4 = D_004CB6D0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}

