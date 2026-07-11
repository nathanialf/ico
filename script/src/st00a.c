#include "common.h"

extern void actEndDemo10(void);
extern void actSt00aEnd_ext(void);

void actSt00aInit(volatile int a0) {
    actCreateSubThread(actEndDemo10, 0x15);
    actCreateSubThread(actSt00aEnd_ext, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aEnd);


extern void func_00178DD8(int a0);
extern void actCreateSubThread(void *entry, int a1);
extern void actConte14_13(void);

void actSt00aEneChk(volatile int a0) {
    func_00178DD8(0x140);
    actCreateSubThread(actConte14_13, 0x15);
}

extern int D_0062A894;
extern int D_0062B320;
extern void func_0017A0F8(int a0);
extern int D_00271240[];
extern void _ACTWait(int a0);
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f0);
extern int actSt25aQueenDeadEvent(void);
extern int D_00629DE4;
extern void actSt25aQueenDead(int a0, int a1, int a2, float f0, float f1);

void actSt00aStairChk(volatile int a0) {
    D_0062A894 = 1;
    D_0062B320 = 0;
    func_0017A0F8(1);
    _ACTWait((0x3C - D_00271240[0] * 0xA) / D_00271240[1] * 0x1E);
    actSt25aQueenBeforeChk(0, 0, 0, 6.0f);
    while (actSt25aQueenDeadEvent() != 0) {
        _ACTWait(1);
    }
    actSt25aQueenDead(1, D_00629DE4, 0, 255.0f, 8.0f);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aDoor2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aDoor2UpChk);

extern void *actInitialize(int a0);
extern void lt_fade_status(int a0);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern void actConte11Jimaku(float f0);
extern void actSt00aDoor1();
extern int D_0062BC54;
extern int D_0062BC50;
extern int D_0062C2A0;
extern int D_002715D0[];
extern int scpPlayEnd(void);
extern void scpTrans(int a0, int a1);
extern void actItouQueenAttack(int a0, int a1, int a2, int a3, int a4, int a5, float f0, float f1);
extern int actCreateSubThreadI2(void *entry, int a1) __asm__("actCreateSubThread");

void actSt00aDoor2DownChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
    D_0062BC54 = 0;
    D_0062BC50 = 0;
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpPlayStart(7, &D_0062BC54, 0, 0, 1);
    while (D_0062BC54 != 0) {
        _ACTWait(1);
    }
    actConte11Jimaku(2.0f);
    actCreateSubThreadI2(actSt00aDoor1, 0x15);
    D_0062C2A0 = 0;
    while (D_0062C2A0 == 0 &&
           ((D_002715D0[1] & 0x800) == 0 || scpPlayEnd() != 0)) {
        _ACTWait(1);
    }
    if (D_0062BC54 != 0) {
        scpTrans(D_0062BC54, 0x80);
    }
    actItouQueenAttack(1, D_00629DE4, 0, 0xFF, 0xFF, 0xFF, 1.0f, 4.0f);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aDoor1);

typedef struct { char pad[0xB4]; int *unkB4; } B4ObjU;
extern void *actInitialize(int a0);
extern void _ACTWait(int a0);
extern int D_00629DE4;
extern void gflagOff(int a0, int a1);
extern void lt_fade_status(int a0);
extern int D_0062A894;
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern int D_0062C2A4;
extern int D_0062BC50;
extern int D_004CB9C0[];
extern void actSt00aAtr2Chk();
extern void BoxBarSoundOn(int a0, int a1);

void actSt00aDoor1UpChk(volatile int a0) {
    int x = a0;
    B4ObjU *gobj = (B4ObjU *)actInitialize(a0);
    _ACTWait(1);
    if (D_00629DE4 != 0) {
        gflagOff(D_00629DE4, 0);
    }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    stage_KillPlayBgAnimation(0x82, 0, 0);
    scpPlayStart(8, &D_0062C2A4, 0, 1, 1);
    while (D_0062C2A4 == 0) {
        _ACTWait(1);
    }
    if (D_0062BC50 == 0) {
        scpPlayStart(0xA, &D_0062BC50, 0, 1, 1);
    }
    D_004CB9C0[1] = (int)actSt00aAtr2Chk;
    gobj->unkB4 = D_004CB9C0;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}



INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aDoor1DownChk);

extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f0);
extern void actConte11Jimaku(float f0);
extern void actSt00aEnemy1();
extern int D_0062C2A0;
extern int D_002715D0[];
extern int scpPlayEnd(void);
extern void scpTrans(int a0, int a1);
extern int actCreateSubThreadIE(void *entry, int a1) __asm__("actCreateSubThread");

void actSt00aEne(volatile int a0) {
    float vol = 4.0f;
    func_00178DD8(4);
    actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
    scpPlayStart(9, &D_0062BC50, 0, 1, 1);
    while (D_0062BC50 == 0) {
        _ACTWait(1);
    }
    actConte11Jimaku(3.0f);
    actCreateSubThreadIE(actSt00aEnemy1, 0x15);
    D_0062C2A0 = 0;
    while (D_0062C2A0 == 0 &&
           ((D_002715D0[1] & 0x800) == 0 || scpPlayEnd() != 0)) {
        _ACTWait(1);
    }
    if (D_0062C2A0 == 0) {
        if (D_0062BC50 != 0) {
            vol = 16.0f;
            scpTrans(D_0062BC50, 0x80);
        }
    }
    actSt25aQueenBeforeChk(0, 0, 0, vol);
    while (actSt25aQueenDeadEvent() != 0) {
        _ACTWait(1);
    }
    actSt25aQueenDead(4, D_00629DE4, 0, 255.0f, 2.0f);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aEnemy1);

typedef struct ActB4Obj { char pad[0xB4]; int *unkB4; } ActB4Obj;
extern void *actInitialize(int a0);
extern void lt_fade_status(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_004CB9E0[];
extern void actSt00aEne();

void actSt00aEnemy2(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    lt_fade_status(0x33);
    D_0062A894 = 1;
    stage_KillPlayBgAnimation(0x9A, 0, 0);
    stage_KillPlayBgAnimation(0x96, 0, 0);
    D_004CB9E0[1] = (int)actSt00aEne;
    gobj->unkB4 = D_004CB9E0;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


extern int D_00271240[];
extern void _ACTWait(int a0);
extern void stgmgrForceSwitchWithFade(int a0);
extern void backStageProcessOutStage(int a0);

void actSt00aStair(int a0) {
    volatile int x;
    x = a0;
    _ACTWait((int)((float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1]) * 5.0f));
    stgmgrForceSwitchWithFade(1);
    backStageProcessOutStage(1);
}

#include "common.h"
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void debug_assertMessage();
extern void func_00178DD8(int a0);
extern void actSt25aQueenDead(int a0, int a1, int a2, float f0, float f1);
extern char D_00614510[];
extern char D_00614520[];
extern int D_00629DE4;
void actSt00aAtr2(volatile int a0) {
    _ACTWait(1);
    while (func_00178DB0(0x15C) == 0) {
        _ACTWait(1);
    }
    debug_assertMessage(D_00614510);
    debug_assertMessage(D_00614520);
    func_00178DD8(2);
    actSt25aQueenDead(1, D_00629DE4, 0, 0.25f, 2.0f);
}

extern void actSt00aDoor1DownChk(void);
extern void actSt00aDoor2Event(void);
extern int D_0062C2A0;
extern int D_002715D0[];
extern int scpPlayEnd(void);
extern int D_0062C2A4;
extern int D_0062BC50;
extern void scpTrans(int a0, int a1);
extern int actCreateSubThreadI(void *entry, int a1) __asm__("actCreateSubThread");

void actSt00aAtr2Chk(volatile int a0) {
    func_00178DD8(3);
    actCreateSubThreadI(actSt00aDoor1DownChk, 0x15);
    actCreateSubThreadI(actSt00aDoor2Event, 0x15);
    D_0062C2A0 = 0;
    while (D_0062C2A0 == 0 &&
           ((D_002715D0[1] & 0x800) == 0 || scpPlayEnd() != 0)) {
        _ACTWait(1);
    }
    if (D_0062C2A0 == 0) {
        if (D_0062C2A4 != 0) {
            scpTrans(D_0062C2A4, 0x200);
        }
        if (D_0062BC50 != 0) {
            scpTrans(D_0062BC50, 0x40);
        }
    }
    actSt25aQueenDead(2, D_00629DE4, 0, 0.5f, 4.0f);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aDoor2Event);

extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt00aDoor2UpEffect(void) {
    if (func_00178DB0(0x26) == 0) {
        stage_KillPlayBgAnimation(0x4C, 0, 0);
        stage_KillPlayBgAnimation(0x49, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x4A, 0, -1);
        stage_KillPlayBgAnimation(0x49, 0, -1);
    }
}

extern int D_00629DE8;
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);

void actSt00aDoor2DownEffect(void) {
    if (D_00629DE8 == 0) return;
    if (func_00178DB0(0x27) != 0) return;
    func_00178DD8(0x165);
}

#include "common.h"
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void func_0017A040(int a0);
extern void func_00178E08(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void func_0017A008(int a0);
extern int D_00629DE8;
extern int D_0062A894;
void actSt00aDoor1Event(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (func_00178DB0(0x27) == 0 || func_00178DB0(0x23) != 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    func_00178DD8(0x24);
    func_0017A040(0xD57);
    func_00178E08(0x165);
    _ACTWait(0x3C);
    func_00178DD8(0x25);
    stage_KillPlayBgAnimation(0x9B, 1, 0);
    _ACTWait(0x96);
    while (func_0012A958(0x9B) == 0) { _ACTWait(1); }
    _ACTWait(1);
    lt_fade_status(0x32);
    _ACTWait(0x78);
    D_0062A894 = 0;
    func_00178E08(0x24);
    func_0017A008(0xD57);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st00a", actSt00aDoor1UpEffect);

extern int scpSleepEnemyOne(int a0, int a1, float f0);
extern int D_004CBA60[];
extern int D_004CBA80[];
extern void actSt01bEneChk(void);
extern void actSt01bInit(void);

void actSt00aDoor1DownEffect(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (scpSleepEnemyOne(a0, D_00629DE4, 200.0f) != 0 ||
        (D_00629DE8 != 0 && scpSleepEnemyOne(a0, D_00629DE8, 400.0f) != 0)) {
        stage_KillPlayBgAnimation(0x50, 0, 0);
        _ACTWait(0x3C);
        D_004CBA60[1] = (int)actSt01bEneChk;
        gobj->unkB4 = D_004CBA60;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x4F, 0, 0);
        D_004CBA80[1] = (int)actSt01bInit;
        gobj->unkB4 = D_004CBA80;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}



/* recovered struct shapes */
typedef struct {
    unsigned int       f_1C;  /* 0x1C */
    unsigned int       f_20;  /* 0x20 */
} S_0055A2D8;  /* stride 0x28 */

/* end struct shapes */
