#include "common.h"

extern void _ACTWait(int a0);
extern void scpDispOffAllWithKind(int *buf, int a1);
extern long long D_0061BE70[];
extern long long D_0061BE80[];
extern long long D_0061BE90[];

void actSt10rFloor(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rCage);

extern int D_00274EC0[];
extern void func_0017B258(int a0);
extern int func_00262BE8(int a0, long a1);
extern int func_00263160(int a0);
extern int func_00263218(int a0);

void actSt10rTower(volatile int a0) {
    _ACTWait(func_00263218(func_00262BE8(func_00263160((0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1]), (long)0x8054 << 47)));
    func_0017B258(0x5F);
}

void actSt10rExit(int x) {
    volatile int local = x;
}

extern long long D_0061BEB0[];
extern long long D_0061BEC0[];

void actSt10rChain(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061BEB0[0]; long long v0b=D_0061BEC0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061BEB0[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061BEC0[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

void actSt10rSekizo(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061BEC0[0]; long long v0b=D_0061BEB0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061BEC0[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061BEB0[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

extern int D_004D2630[];
extern int D_006325B4;

void actSt10rEne(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_006325B4 = 0;
    *(int *)(gobj + 0xC0) = (int)D_004D2630;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct { char pad[0xC0]; void *f_C0; void *f_C4; } St10rBox;
extern int *D_004D2670[];
extern void func_002265F0(volatile int a0);

void func_002276F8(volatile int a0) {
    St10rBox *obj = *(St10rBox **)(a0 + 0x164);
    D_006325B4 = 1;
    D_004D2670[1] = (int *)func_002265F0;
    obj->f_C0 = 0;
    obj->f_C4 = (void *)D_004D2670;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_00631AE4;
extern void actSt25aQueenDead(int a0, int a1, int a2, float f12, float f13);
extern int func_0017B230(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);

void actSt10rEnemy1(volatile int a0) {
    while (func_0017B230(0x5F) != 0 || scpSleepEnemyOne(a0, D_00631AE4, 400.0f) == 0) {
        _ACTWait(1);
    }
    actSt25aQueenDead(3, D_00631AE4, 0, 16.0f, 16.0f);
}

extern int D_00631AE8;
extern long long D_0061BED0[];
extern void actSwordEffXL(int a0, int a1, long long *a2, int a3);

void func_002277C0(volatile int a0) {
    long long buf[2];
    if (D_00631AE8 == 0) { _ACTWait(0); }
    while (func_0017B230(0x5F) != 0 ||
           scpSleepEnemyOne(a0, D_00631AE8, 400.0f) == 0) { _ACTWait(1); }
    buf[0] = D_0061BED0[0];
    buf[1] = D_0061BED0[1];
    actSwordEffXL(D_00631AE8, 0x16, buf, 0xB4);
}

extern int actSt25aQueenDeadChk(int a0);

void func_00227868(volatile int a0) {
    while (scpSleepEnemyOne(a0, actSt25aQueenDeadChk(0x66B), 200.0f) == 0 ||
           func_0017B230(0x5F) == 0) { _ACTWait(1); }
    func_0017B258(0x61);
    *(int *)(actSt25aQueenDeadChk(0x66B) + 0x16C) = 0;
}

void func_002278E0(volatile int a0) {
    while (scpSleepEnemyOne(a0, actSt25aQueenDeadChk(0x66B), 200.0f) == 0 ||
           func_0017B230(0x5F) != 0) { _ACTWait(1); }
}

void func_00227940(volatile int a0) {
    while (scpSleepEnemyOne(a0, actSt25aQueenDeadChk(0x667), 200.0f) == 0 ||
           func_0017B230(0x5F) != 0) { _ACTWait(1); }
    *(int *)(actSt25aQueenDeadChk(0x667) + 0x16C) = 0;
}

typedef struct ActB4Obj { char pad[0xC4]; int *unkC4; } ActB4Obj;

extern int scpSleepSpiderGroupOne(int a0, int a1);

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_002279B0);

extern void func_002279B0(volatile int a0);
extern int D_004D27B0[];
extern void func_0017B288(int a0);

void func_00227A48(volatile int a0) {
    ActB4Obj *gobj = *(ActB4Obj **)(a0 + 0x164);
    while (scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x66B), 0x2000000) != 0) { _ACTWait(1); }
    func_0017B288(0x63);
    D_004D27B0[1] = (int)func_002279B0;
    gobj->unkC4 = D_004D27B0;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D27F0[];
extern void AddWayPointTop(int a0, int a1);
extern int func_0017EB50(void);
extern void func_00227BA8(volatile int a0);

void func_00227AE0(volatile int a0) {
    ActB4Obj *gobj = *(ActB4Obj **)(a0 + 0x164);
    if (D_00631AE8 == 0) { _ACTWait(0); }
    while (func_0017EB50() != 0 ||
           scpSleepSpiderGroupOne(D_00631AE8, 0x4000000) == 0) { _ACTWait(1); }
    AddWayPointTop(0x13, 1);
    AddWayPointTop(0x17, 1);
    AddWayPointTop(0x18, 1);
    D_004D27F0[1] = (int)func_00227BA8;
    gobj->unkC4 = D_004D27F0;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_00227BA8);

extern int D_004D2870[];
extern int _SCPBoySupportGirl(int a0, int a1, int a2);
extern void func_00227D18(volatile int a0);

void func_00227C70(volatile int a0) {
    ActB4Obj *gobj = *(ActB4Obj **)(a0 + 0x164);
    while (_SCPBoySupportGirl(0x66D, 0xF0, 0x12C) == 0) { _ACTWait(1); }
    AddWayPointTop(0x19, 1);
    AddWayPointTop(0x1A, 1);
    func_0017B258(0x64);
    D_004D2870[1] = (int)func_00227D18;
    gobj->unkC4 = D_004D2870;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_00227D18);

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_00227DC0);

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_00227E68);

extern void DrawLine(void);
extern int GetSkeltonFocusNode(int a0);

void func_00227F10(volatile int a0) {
    while (scpSleepEnemyOne(a0, D_00631AE4, 150.0f) == 0 ||
           (GetSkeltonFocusNode(D_00631AE4) != 0x2E &&
            GetSkeltonFocusNode(D_00631AE4) != 0x2F &&
            GetSkeltonFocusNode(D_00631AE4) != 0x30 &&
            GetSkeltonFocusNode(D_00631AE4) != 0x3E)) { _ACTWait(1); }
    *(int *)(actSt25aQueenDeadChk(0x667) + 0x16C) = 1;
    DrawLine();
}

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_00227FD8);

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_002280B8);

extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void func_00228198(void) {
    if (func_0017B230(0x71) != 0) {
        if (func_0017B230(0x72) != 0) {
            AddWayPointTop(0xB, 0);
            AddWayPointTop(0xC, 0);
            stage_KillPlayBgAnimation(0x143, 0, -1);
        } else {
            AddWayPointTop(0xD, 0);
            AddWayPointTop(0xE, 0);
            AddWayPointTop(0xF, 0);
            stage_KillPlayBgAnimation(0x142, 0, -1);
        }
    } else {
        AddWayPointTop(0xD, 0);
        AddWayPointTop(0xE, 0);
        AddWayPointTop(0xF, 0);
        stage_KillPlayBgAnimation(0x142, 0, 0);
    }
}


void func_00228260(void) {
    if (D_00631AE8 != 0 && func_0017B230(0x75) == 0 && func_0017B230(0x72) != 0) {
        func_0017B258(0x166);
    }
    if (D_00631AE8 != 0 && func_0017B230(0x78) == 0 && func_0017B230(0x9B) != 0) {
        func_0017B258(0x166);
    }
}

extern int D_00275254[];
extern long long D_0061BEE0[];
extern int D_00633FAC;
extern int ContinueCorrectPosition(int a0);
extern void actConte11Jimaku(float f12);
extern int actCreateSubThread(void *fn, int a1);
extern void actSt13aCheckChk();
extern void actSt13bElevUp();
extern void actSt13bElevUpChk();
extern void actSt13bSekizo();
extern void actSt13bSekizo2();
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f12);
extern int actSt25aQueenDeadEvent(void);
extern void func_0017B528(int a0);
extern void func_0017B568(int a0);
extern void func_001C3270(void);
extern void func_00243AE8(int a0, int a1, int a2);
extern void gflagChk(int a0, int a1);
extern void gflagInit(int a0);
extern void gflagOff(int a0, int a1);
extern void iosSemaWait(int a0, int a1);
extern void lt_fade_status(int a0);
extern void scpActivateAllWithKind(void);
extern void scpDispOnAllWithKind(void);
extern int scpPlayEnd(void);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void scpTrans(int a0, int a1);
extern int soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);

void func_002282D8(volatile int a0) {
    long long buf[2];
    long long v[2];
    int h;
    int th1;
    int th2;
    int th3;

    h = 0;
    while (scpSleepSpiderGroupOne(D_00631AE4, 0x1000000) == 0) { _ACTWait(1); }
    soundSeDefPlayWithVolumeRate(0x509, 0, 0, 1);
    if (D_00631AE8 != 0 && scpSleepSpiderGroupOne(D_00631AE8, 0x3000000) != 0) {
        actCreateSubThread(actSt13bSekizo, 0x15);
    }
    if (D_00631AE8 != 0 && scpSleepSpiderGroupOne(D_00631AE8, 0x5000000) != 0) {
        actCreateSubThread(actSt13bSekizo2, 0x15);
    }
    scpDispOnAllWithKind();
    lt_fade_status(0x33);
    D_006325B4 = 1;
    func_0017B528(D_00631AE4);
    func_0017B258(0x71);
    _ACTWait(0x5A);
    scpPlayStart(0x39, (int)&h, 1, 1, 1);
    while (h == 0) { _ACTWait(1); }
    th1 = actCreateSubThread(actSt13aCheckChk, 0x15);
    th2 = actCreateSubThread(actSt13bElevUpChk, 0x15);
    th3 = actCreateSubThread(actSt13bElevUp, 0x15);
    D_00633FAC = 0;
    for (;;) {
        if (D_00633FAC != 0) { goto sema; }
        if ((D_00275254[0] & 0x800) != 0 && scpPlayEnd() == 0) {
            if (D_00633FAC != 0) { goto sema; }
            break;
        }
        _ACTWait(1);
    }
    scpTrans(h, 0xC0);
    actSt25aQueenBeforeChk(0, 0, 0, 16.0f);
    while (actSt25aQueenDeadEvent() != 0) { _ACTWait(1); }
    iosSemaWait(th1 + 0x24, 0x22);
    iosSemaWait(th2 + 0x24, 0x22);
    iosSemaWait(th3 + 0x24, 0x22);
    stage_KillPlayBgAnimation(0x142, 1, -1);
    gflagOff(D_00631AE4, 0x1D1);
    func_001C3270();
    _ACTWait(1);
    gflagInit(0x18A);
    gflagInit(0x18B);
    actConte11Jimaku(3.0f);
    goto tail;
sema:
    iosSemaWait(th1 + 0x24, 0x22);
    iosSemaWait(th2 + 0x24, 0x22);
    iosSemaWait(th3 + 0x24, 0x22);
tail:
    buf[0] = D_0061BEE0[0];
    buf[1] = D_0061BEE0[1];
    func_00243AE8((int)v, (int)buf, ContinueCorrectPosition(D_00631AE4));
    gflagChk(D_00631AE4, (int)v);
    gflagOff(D_00631AE4, 0);
    func_0017B568(D_00631AE4);
    D_006325B4 = 0;
    lt_fade_status(0x32);
    scpActivateAllWithKind();
}

