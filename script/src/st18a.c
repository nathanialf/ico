#include "common.h"

typedef struct ActB4Obj {
    char pad[0xB4];
    int *unkB4;
} ActB4Obj;
extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_004CDE50[];
void actSt18aSwitchRUpChk(volatile int a0);

void actSt18aEnd(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    D_004CDE50[1] = (int)actSt18aSwitchRUpChk;
    gobj->unkB4 = D_004CDE50;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


extern int func_00178DB0(int a0);
extern int D_004CDE70[];
void actSt18aDoorChk(volatile int a0);

void actSt18aSwitchLChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x129) == 0) {
        D_004CDE70[1] = (int)actSt18aDoorChk;
        gobj->unkB4 = D_004CDE70;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CDE90[];
extern int D_004CDEB0[];
void actSt18aEnemy1_1(volatile int a0);
void actSt18aDoorDownChk(volatile int a0);

void actSt18aSwitchLUpChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x12A) == 0) {
        D_004CDE90[1] = (int)actSt18aEnemy1_1;
        gobj->unkB4 = D_004CDE90;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        D_004CDEB0[1] = (int)actSt18aDoorDownChk;
        gobj->unkB4 = D_004CDEB0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


typedef struct { char pad[0xB0]; int *unkB0; } ActB0Obj;
extern int D_004CDDB0[];

void actSt18aSwitchRChk(volatile int a0) {
    ActB0Obj *gobj = *(ActB0Obj **)(a0 + 0x164);
    gobj->unkB0 = D_004CDDB0;
    for (;;) {
        _ACTWait(1);
    }
}

/* NEAR-MISS (rc7). BoxBar/lt_fade wrapper, byte-identical TWIN of func_0020FD50
 * (st03t.c — see its full analysis). Recovered dev shape (rc7):
 *   void func_0022BEA8(volatile int a0) {
 *       int gobj = *(int *)(a0 + 0x164);
 *       *(int *)(gobj + 0xB0) = 0;                 // in lt_fade delay
 *       lt_fade_status(0x33);
 *       *(int *)(gobj + 0xB4) = (int)D_004CDDF0;
 *       D_0062A894 = 1;
 *       D_004CDDF0[1] = (int)func_0022B5F0;        // in BoxBar delay (ROM)
 *       BoxBarSoundOn((int)a0, 0x189); _ACTWait(0);
 *   }
 * Two coupled residuals (both twins): (a) v0/v1 COLORING SWAP — ROM &D_004CDDF0=v0
 * (D[1] store BASE), &func_0022B5F0=v1 (value); gcc gives them v1/v0. (b) a0 RELOAD
 * TIMING — ROM reloads the volatile a0 (BoxBar arg) EARLY into the addiu load-latency
 * bubble so D[1]=&chk lands in BoxBar's delay; gcc reloads LATE (BoxBar delay=nop).
 * The simpler siblings (actSt18aEnd, D[1]-first + no A894/lt_fade) DO match this
 * exact pattern — but here the gp_rel D_0062A894 store between blocks sched2 from
 * hoisting the a0 reload. Tried (fan-3): store reorders (unkB4-first rc7, D[1]-first
 * rc13), typed-member gobj->unkB4 (rc10). NEXT: force the volatile a0 reload to hoist
 * past the gp_rel store so D[1] fills the BoxBar delay -> coloring follows. NOT a floor. */
extern void lt_fade_status(int a0);
extern int D_004CDDF0[];
extern void func_0022B5F0(volatile int a0);
extern int D_0062A894;

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", func_0022BEA8);

#include "common.h"
extern void _ACTWait(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);
extern void actSt25aQueenDead(int a0, int a1, int a2, float f0, float f1);
extern int D_00629DE4;
void actSt18aSwitchRUpChk(volatile int a0) {
    while (scpSleepEnemyOne(a0, D_00629DE4, 400.0f) == 0 || func_00178DB0(0xF) != 0) {
        _ACTWait(1);
    }
    func_00178DD8(0x127);
    actSt25aQueenDead(0xF, D_00629DE4, 0, 16.0f, 16.0f);
}

extern void _ACTWait(int a0);
extern void backStageProcessMain(void);
extern void func_00178DD8(int a0);

void actSt18aDoorChk(volatile int a0) {
    _ACTWait(1);
    backStageProcessMain();
    func_00178DD8(0x129);
}

extern int actSt25aQueenDeadChk(int a0);
extern int GetStageFromLabel(int a0);
extern void func_00178E08(int a0);
extern int D_004CDED0[];

void actSt18aDoorDownChk(volatile int a0) {
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    while (scpSleepEnemyOne(a0, actSt25aQueenDeadChk(0x754), 200.0f) != 0) {
        _ACTWait(1);
    }
    GetStageFromLabel(actSt25aQueenDeadChk(0x753));
    func_00178E08(0x12A);
    D_004CDED0[1] = (int)actSt18aEnemy1_1;
    obj->unkB4 = D_004CDED0;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


extern void eBrainGetTargetGeneratorFromLabelStage(int a0);
extern int D_004CDEF0[];

void actSt18aEnemy1_1(volatile int a0) {
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    while (scpSleepEnemyOne(a0, actSt25aQueenDeadChk(0x754), 200.0f) == 0) {
        _ACTWait(1);
    }
    eBrainGetTargetGeneratorFromLabelStage(actSt25aQueenDeadChk(0x753));
    func_00178DD8(0x12A);
    D_004CDEF0[1] = (int)actSt18aDoorDownChk;
    obj->unkB4 = D_004CDEF0;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}

extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f0);
extern void lt_fade_status(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_0062A894;
extern int D_004CDF10[];
void actSt18aIntro(volatile int a0);

void actSt18aEnemy2_1(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x5) == 0) {
        actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
        lt_fade_status(0x33);
        D_0062A894 = 1;
        stage_KillPlayBgAnimation(0x1D, 0, 0);
        stage_KillPlayBgAnimation(0x19, 0, 0);
        stage_KillPlayBgAnimation(0x20, 0, 0);
        stage_KillPlayBgAnimation(0x21, 0, 0);
        stage_KillPlayBgAnimation(0x23, 0, 0);
        stage_KillPlayBgAnimation(0x25, 0, 0);
        stage_KillPlayBgAnimation(0x27, 0, 0xEB);
        stage_KillPlayBgAnimation(0x28, 0, 0);
        D_004CDF10[1] = (int)actSt18aIntro;
        gobj->unkB4 = D_004CDF10;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x1F, 0, -1);
        stage_KillPlayBgAnimation(0x19, 0, -1);
        stage_KillPlayBgAnimation(0x23, 0, 0);
        stage_KillPlayBgAnimation(0x25, 0, 0);
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aIntro);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aDoor);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aSwitchL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st18a", actSt18aSwitchR);

extern int D_004CDF70[];
void actSt19aOriXL(volatile int a0);

void actSt18aEne(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xC) == 0) {
        stage_KillPlayBgAnimation(0x1F, 0, -1);
        stage_KillPlayBgAnimation(0x19, 0, 0);
        stage_KillPlayBgAnimation(0x22, 0, 0);
        stage_KillPlayBgAnimation(0x23, 0, 0);
        stage_KillPlayBgAnimation(0x25, 0, 0);
        D_004CDF70[1] = (int)actSt19aOriXL;
        gobj->unkB4 = D_004CDF70;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x1F, 0, -1);
        stage_KillPlayBgAnimation(0x19, 0, 0);
        stage_KillPlayBgAnimation(0x22, 0, 0);
        stage_KillPlayBgAnimation(0x23, 0, 0);
        stage_KillPlayBgAnimation(0x25, 0, 0);
    }
}


extern void warpGirlInStage(float f0, float f1, float f2);
extern void func_0018F940(void);
extern int fightSoundClose(void);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern float D_0062997C, D_00629980, D_0062A898;
extern int D_004CDF90[];
extern int D_0062BDBC;
void actSt19aPipeXL(volatile int a0);

void actSt18aEnemy1_2(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    warpGirlInStage(*(volatile float *)&D_0062997C, *(volatile float *)&D_00629980, -4.0f);
    func_0018F940();
    while (fightSoundClose() != 0) {
        _ACTWait(1);
    }
    if (func_00178DB0(0xD) == 0) {
        D_004CDF90[1] = (int)actSt19aPipeXL;
        gobj->unkB4 = D_004CDF90;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else if (func_00178DB0(0xE) == 0) {
        scpPlayStart(0x24, &D_0062BDBC, 1, 0, 1);
        D_0062A898 = 0.5f;
    }
}


extern int func_0012A958(int a0);
extern void BossCtrlGeo(void);
extern int D_00271240[];
extern int D_0062BDBC;
extern void AdpcmClose(int a0);
extern void gflagOff(int a0, int a1);
extern void func_001790E8(int a0);

void actSt18aEne2(volatile int a0) {
    stage_KillPlayBgAnimation(0x2AF, 1, 0);
    while (func_0012A958(0x2AF) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    BossCtrlGeo();
    _ACTWait(((0x3C - D_00271240[0] * 0xA) / D_00271240[1]) * 2);
    while (D_0062BDBC == 0) {
        _ACTWait(1);
    }
    AdpcmClose(*(int *)(D_0062BDBC + 0x2C));
    gflagOff(D_00629DE4, 0);
    func_001790E8(D_00629DE4);
    D_0062A894 = 0;
    lt_fade_status(0x32);
}


extern int func_0012AA28(int a0, int a1, int a2);
extern int iosPadDevRead(int a0, int a1);
extern void Shock_Request(int a0, int a1);
extern void Vibration_ShotDecode(int a0);
extern int D_0062BDCC;
extern int D_00629DEC;
extern int D_0062BDD8;
extern unsigned char D_0062BDDC;

void actSt18aEnemy2_2(volatile int a0) {
    lt_fade_status(0x33);
    func_00178DD8(0xF);
    scpPlayStart(0x4D, &D_0062BDCC, 0, 1, 1);
    while (D_0062BDCC == 0) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0x27, 1, 0xEB);
    while (func_0012AA28(0x27, 0x141, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x11);
    while (func_0012AA28(0x27, 0x15E, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    {
        int r = iosPadDevRead(D_00629DEC, 0x9);
        D_0062BDDC = 0x80;
        D_0062BDD8 = r;
        Shock_Request(r, 0x80);
    }
    while (func_0012AA28(0x27, 0x1C2, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Vibration_ShotDecode(D_0062BDD8);
    actSt25aQueenDead(0x3, D_00629DE4, 0, 2.0f, 4.0f);
    D_0062A894 = 0;
    lt_fade_status(0x32);
}


extern int D_004CE050[];
void actSt18aIntroChk(volatile int a0);

void actSt18aCamera(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x127) != 0) {
        lt_fade_status(0x33);
        D_0062A894 = 1;
        actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
        stage_KillPlayBgAnimation(0x27, 0, 0xEB);
        _ACTWait(0xA);
        D_0062A894 = 1;
        stage_KillPlayBgAnimation(0x27, 0, 0);
        D_004CE050[1] = (int)actSt18aIntroChk;
        gobj->unkB4 = D_004CE050;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x27, 0, 0xEB);
    }
}


extern int D_0062BDC8;
extern void actConte11Jimaku(float f0);

void actSt18aIntroChk(volatile int a0) {
    scpPlayStart(0x4C, &D_0062BDC8, 1, 1, 1);
    while (D_0062BDC8 == 0) {
        _ACTWait(1);
    }
    actConte11Jimaku(6.0f);
    stage_KillPlayBgAnimation(0x27, 1, 0);
    {
        int r = iosPadDevRead(D_00629DEC, 0x9);
        D_0062BDDC = 0x80;
        D_0062BDD8 = r;
        Shock_Request(r, 0x80);
    }
    while (func_0012AA28(0x27, 0xC8, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x11);
    Vibration_ShotDecode(D_0062BDD8);
    while (func_0012AA28(0x27, 0xEA, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0062A894 = 0;
    lt_fade_status(0x32);
    func_00178E08(0x127);
}


extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004CDF30[];
void actSt18aSwitchL(volatile int a0);

void actSt18aEneChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xA) == 0) {
        stage_KillPlayBgAnimation(0x20, 0, 0);
        D_004CDF30[1] = (int)actSt18aSwitchL;
        gobj->unkB4 = D_004CDF30;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x20, 0, -1);
    }
}


extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004CDF50[];
void actSt18aSwitchR(volatile int a0);

void actSt18aEne2Chk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xB) == 0) {
        stage_KillPlayBgAnimation(0x21, 0, 0);
        D_004CDF50[1] = (int)actSt18aSwitchR;
        gobj->unkB4 = D_004CDF50;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x21, 0, -1);
    }
}


extern int D_004CDFB0[];
void actSt19aChain(volatile int a0);

void func_0022D7F8(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xE) == 0) {
        stage_KillPlayBgAnimation(0x22, 0, 0);
        D_004CDFB0[1] = (int)actSt19aChain;
        gobj->unkB4 = D_004CDFB0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x22, 0, -1);
    }
}

