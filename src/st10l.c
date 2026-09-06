#include "common.h"

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;
typedef struct Act {
    char unk00[0x34];           /* 0x00 */
    int f34;                    /* 0x34 */
    char unk38[0x98];           /* 0x38 */
    ActMail *mainMail;          /* 0xD0 */
    ActMail *mail;              /* 0xD4 */
} Act;
typedef struct PObjGObj {
    char pad00[0x164];          /* 0x000 */
    Act *act;                   /* 0x164 */
    char pad168[0x4];           /* 0x168 */
    int f16C;                   /* 0x16C */
} PObjGObj;

/* the shared pad-state array (op.c's PadState, GsBase.c's GsbPad): 0x58 per
   pad, trg at 0x4. */
typedef struct Pad {
    int unk00;                  /* 0x00 */
    int trg;                    /* 0x04 */
    char unk08[0x50];           /* 0x08 */
} Pad;
extern Pad D_0028F8F0[];

extern void _ACTWait(int a0);
extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern PObjGObj *scpSearchGobj(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern void gflagOn(int a0);
extern int scpTriggerFloorAttr(int a0, int a1);
extern int D_0063A538;
extern int floor10l;
extern int st10l_gondola_up;
extern int st10l_gondola_down;
extern int chain10l;
extern int D_0063AA08;
extern int enable_game_pause;
extern int D_00639EA4;
extern int D_00639EA8;
extern int D_00639EAC;
extern void SetWayGroupActive(int a0, int a1);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int scpTriggerBall(int a0, int a1, float radius);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);
extern void FinishHint(int a0);
extern void lt_switch_layout(int a0);
extern void scpSleepEnemyAll(void);
extern void scpKillEnemyOne(int a0);
extern void scpKillSpiderGroup(int a0);
extern void scpWakeupEnemyAll(void);
extern void gflagOff(int a0);
extern int stage_CheckAnimationFinish(int a0);
extern void _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);
extern int D_0028F4C0[];
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern void iosPadActRequest(int a0, int a1);
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
extern void scpAdpcmFadeCloseFunc(int *handle, int mask);
extern int scpAdpcmCloseChkFunc(int *handle);
extern void SetGirlDangerGObj(int a0);
extern void ClearGirlDangerGObj(void);
extern void scpSleepEnemyOne(int a0);
extern void scpWakeupEnemyOne(int a0);
extern void scpSleepSpiderGroupOne(int a0);
extern void scpWakeupSpiderGroupOne(int a0);
extern void SetCameraFlag_LwsCutBack(void);
extern int scpAdpcmPlayRequestNum(void);
extern void scpFadeOut(float a0, int a1, int a2, int a3);
extern void scpFadeIn(float f);
extern int scpFadeChk(void);
extern int lt_fade_status(void);
extern void scpPlayPosSet(int a0, float f12, float f13, float f14);
extern void scpPlayStart(int a0);
extern void scpPlayMot(int a0, int mot);
extern void scpPlayEnd(int a0);
extern void scpSekizou(int a0, int a1, int a2, int a3, int a4,
                       float x1, float y1, float z1,
                       float x2, float y2, float z2);

extern void actSt10lChainMain(volatile int a0);
extern void actSt10lChainMove(volatile int a0);
extern void actSt10lGondolaMain(volatile int a0);
extern void actSt10lFloorMain(volatile int a0);
extern void actSt10lFloorLeft(volatile int a0);
extern void actSt10lFloorRight(volatile int a0);
extern void actSt10lGondolaUp(volatile int a0);
extern void actSt10lGondolaDown(volatile int a0);
extern void actSt10lBoxChk(volatile int a0);
extern void actSt10lEneCam1Chk(volatile int a0);
extern void actSt10lEneCam2Chk(volatile int a0);
extern void actSt10lEneCam3Chk(volatile int a0);
extern void actSt10lBoxAChk(volatile int a0);
extern void actSt10lBoxBChk(volatile int a0);
extern void actSt10lEneKillChk(volatile int a0);

/* st10l.o's own .rodata run 0x00622DE0..0x00622DF0 (no MAIN.MAP symbol):
   the girl's way-point packet for actSt10lEneCam3Chk. */
extern long long D_00622DE0[];

/* st10l.o's own .data run (no MAIN.MAP symbols): actor mail packets. */
extern ActMail D_004FA480[];
extern ActMail D_004FA4A0[];
extern ActMail D_004FA4C0[];
extern ActMail D_004FA4E0[];
extern ActMail D_004FA500[];
extern ActMail D_004FA520[];
extern ActMail D_004FA540[];
extern ActMail D_004FA560[];
extern ActMail D_004FA580[];
extern ActMail D_004FA5A0[];
extern ActMail D_004FA5C0[];
extern ActMail D_004FA5E0[];
extern ActMail D_004FA600[];
extern ActMail D_004FA620[];
extern ActMail D_004FA640[];
extern ActMail D_004FA660[];
extern ActMail D_004FA680[];
extern ActMail D_004FA6A0[];
extern ActMail D_004FA6C0[];
extern ActMail D_004FA6E0[];
extern ActMail D_004FA700[];
extern ActMail D_004FA720[];

void actSt10lInit(void)
{
    if (gflagChk(0x121) != 0) {
        SetWayGroupActive(0x16, 1);
        SetWayGroupActive(0x17, 1);
        stage_SetAnimation(0x17B, 0, 0x59);
    } else {
        SetWayGroupActive(0x14, 1);
        SetWayGroupActive(0x15, 1);
        stage_SetAnimation(0x17B, 0, 0);
    }
}
/*SWEEPactSt10lFloorLeft*/
void actSt10lFloorLeft(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    if (gflagChk(0x122) == 0 && D_00639EA8 != 0
        && scpTriggerFloorAttr(D_00639EA8, 0x3000000) != 0) {
        gflagOn(0x122);
    }

    if (D_00639EA8 != 0
        && scpTriggerFloorAttr(D_00639EA8, 0x2000000) != 0) {
        scpPlayStart(D_00639EA8);
        scpPlayMot(D_00639EA8, 0x214);
    }

    if (gflagChk(0x122) != 0 && D_00639EA8 != 0
        && scpTriggerFloorAttr(D_00639EA8, 0x3000000) != 0) {
        scpPlayPosSet(D_00639EA8, -167.0f, -72.0f, -705.0f);
        scpPlayStart(D_00639EA8);
        scpPlayMot(D_00639EA8, 0x214);
    }

    scpAdpcmPlayRequestFunc(0x5B, &floor10l, 1, 1, 1);

    while (floor10l == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x17B, 1, 0);

    SetWayGroupActive(0x14, 0);
    SetWayGroupActive(0x15, 0);
    SetWayGroupActive(0x16, 1);
    SetWayGroupActive(0x17, 1);

    gflagOn(0x121);

    while (stage_CheckAnimationFrame(0x17B, 0x59, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (gflagChk(0x122) != 0) {
        gflagOn(0x128);
    }

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0xA);

    if (gflagChk(0x127) == 0) {
        D_0063AA08 = 0;
        lt_switch_layout(0x36);
        scpWakeupEnemyAll();

        if (D_00639EA8 != 0) {
            scpPlayEnd(D_00639EA8);
        }
    }

    D_004FA500[0].func = actSt10lFloorMain;
    sub->mail = D_004FA500;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
/*SWEEP-ENDactSt10lFloorLeft*/
void actSt10lFloorRight(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    if (gflagChk(0x122) != 0 && D_00639EA8 != 0
        && scpTriggerFloorAttr(D_00639EA8, 0x3000000) != 0) {
        scpPlayPosSet(D_00639EA8, -196.0f, -72.0f, 62.0f);
        scpPlayStart(D_00639EA8);
        scpPlayMot(D_00639EA8, 0x214);
    }

    scpAdpcmPlayRequestFunc(0x5B, &floor10l, 1, 1, 1);

    while (floor10l == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x17B, 1, 0x5A);

    SetWayGroupActive(0x14, 1);
    SetWayGroupActive(0x15, 1);
    SetWayGroupActive(0x16, 0);
    SetWayGroupActive(0x17, 0);

    gflagOff(0x121);

    while (stage_CheckAnimationFrame(0x17B, 0xB4, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0xB);

    D_0063AA08 = 0;
    lt_switch_layout(0x36);
    scpWakeupEnemyAll();

    if (D_00639EA8 != 0) {
        scpPlayEnd(D_00639EA8);
    }

    D_004FA520[0].func = actSt10lFloorMain;
    sub->mail = D_004FA520;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt10lGondolaUp(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    scpAdpcmPlayRequestFunc(0x58, &st10l_gondola_up, 1, 1, 1);

    while (st10l_gondola_up == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x17C, 1, 0);

    while (stage_CheckAnimationFrame(0x17C, 0xA9, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_CheckAnimationFrame(0x17C, 0xB3, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(0x123);

    if (st10l_gondola_up != 0) {
        scpAdpcmFadeCloseFunc(&st10l_gondola_up, 0x100);
    }

    while (scpAdpcmCloseChkFunc(&st10l_gondola_up) != 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 0;
    scpWakeupEnemyAll();
    lt_switch_layout(0x36);

    D_004FA5C0[0].func = actSt10lGondolaMain;
    sub->mail = D_004FA5C0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt10lGondolaDown(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    SetGirlDangerGObj(D_00639EA4);

    scpAdpcmPlayRequestFunc(0x59, &st10l_gondola_down, 1, 1, 1);

    while (st10l_gondola_down == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x17C, 1, 0xB4);

    while (stage_CheckAnimationFrame(0x17C, 0x154, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFrame(0x17C, 0x168, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOff(0x123);

    if (st10l_gondola_down != 0) {
        scpAdpcmFadeCloseFunc(&st10l_gondola_down, 0x100);
    }

    while (scpAdpcmCloseChkFunc(&st10l_gondola_down) != 0) {
        _ACTWait(1);
    }

    ClearGirlDangerGObj();

    D_0063AA08 = 0;
    scpWakeupEnemyAll();
    lt_switch_layout(0x36);

    D_004FA5E0[0].func = actSt10lGondolaMain;
    sub->mail = D_004FA5E0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt10lEneCam2Chk(volatile int a0)
{
    int save;

    while (D_00639EA8 == 0
        || scpTriggerFloorAttr(D_00639EA4, 0x4000000) == 0
        || gflagChk(0x11F) == 0
        || ((PObjGObj *)D_00639EA8)->act->f34 == 0x6F) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    save = D_0063A538;
    D_0063A538 = 0;

    scpKillEnemyOne(0x3E0);
    scpKillEnemyOne(0x3E1);
    scpKillSpiderGroup(0x3E2);
    scpSleepEnemyOne(0xEAD);
    scpSleepEnemyOne(0x3DF);
    scpSleepEnemyOne(0x3EE);
    scpSleepSpiderGroupOne(0x3EF);

    _ACTWait(0x1E);

    gflagOn(0x126);

    D_0063A538 = save;

    stage_SetAnimation(0x17D, 1, 0);

    while (stage_CheckAnimationFinish(0x17D) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0x3);

    lt_switch_layout(0x36);
    D_0063AA08 = 0;

    scpWakeupEnemyOne(0xEAD);
    scpWakeupEnemyOne(0x3E0);
    scpWakeupEnemyOne(0x3E1);
    scpWakeupSpiderGroupOne(0x3E2);
    scpWakeupEnemyOne(0x3DF);
    scpWakeupEnemyOne(0x3EE);
    scpWakeupSpiderGroupOne(0x3EF);
}
void actSt10lEneCam3Chk(volatile int a0)
{
    long long buf[2];

    while (gflagChk(0x128) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x127);
    FinishHint(0xE);

    stage_SetAnimation(0x17E, 1, 0);

    buf[0] = D_00622DE0[0];
    buf[1] = D_00622DE0[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);

    while (stage_CheckAnimationFinish(0x17E) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOff(0x127);

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0x3);

    lt_switch_layout(0x36);
    D_0063AA08 = 0;
    scpWakeupEnemyAll();
}
void actSt10lChainMove(volatile int a0)
{
    lt_switch_layout(0x37);
    scpSleepEnemyAll();

    gflagOn(0x11F);
    FinishHint(0xD);

    _ACTWait(0x1E);

    scpAdpcmPlayRequestFunc(0x61, &chain10l, 1, 1, 1);

    while (chain10l == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x180, 1, 0);
    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFrame(0x180, 0xF0, 0) == 0) {
        if ((D_0028F8F0[0].trg & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            scpFadeOut(16.0f, 0, 0, 0);
            scpAdpcmFadeCloseFunc(&chain10l, 0x200);

            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }

            stage_SetAnimation(0x180, 1, 0xEF);
            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }

    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(0x36);

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]);

    stage_SetAnimation(0x180, 0, 0);

    scpSearchGobj(0x3D9)->f16C = 1;
}
void actSt10lChain(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x11F) == 0) {
        stage_SetAnimation(0x180, 0, 0);

        scpSearchGobj(0x3D9)->f16C = 0;

        D_004FA6E0[0].func = actSt10lChainMain;
        self->mail = D_004FA6E0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x180, 0, 0);
        FinishHint(0xD);
    }
}
void actSt10lFloor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    D_004FA4A0[0].func = actSt10lFloorMain;
    self->mail = D_004FA4A0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt10lGondola(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x123) != 0) {
        stage_SetAnimation(0x17C, 0, 0);
        _ACTWait(0xA);
        stage_SetAnimation(0x17C, 0, 0xB3);
    } else {
        stage_SetAnimation(0x17C, 0, 0);
    }

    D_004FA560[0].func = actSt10lGondolaMain;
    self->mail = D_004FA560;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt10lSekizo(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x120, 0x17F, 0, 0x13,
               0.0f, -72.0f, 1274.0f,
               76.0f, -72.0f, 1274.0f);
}
void actSt10lBox(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    D_004FA620[0].func = actSt10lBoxChk;
    self->mail = D_004FA620;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt10lEnemy1_1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);
    Generator_Mask((int)scpSearchGobj(0x3E5));

    while (gflagChk(0x125) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x74);

    Generator_Call(a0);
    Generator_MaskOff(a0);
    Generator_Call((int)scpSearchGobj(0x3E5));
}
void actSt10lEnemy1_2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x125) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x64);

    Generator_Call(a0);
    Generator_MaskOff(a0);
}
void actSt10lEnemy2_1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x126) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x74);

    Generator_Call(a0);
    Generator_MaskOff(a0);
}
void actSt10lEnemy2_2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x126) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x64);

    Generator_Call(a0);
    Generator_MaskOff(a0);
}
void actSt10lEnemy2_3(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x126) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x82);

    Generator_Call(a0);
    Generator_MaskOff(a0);
}
void actSt10lEnemy3_1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x127) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x1);

    Generator_Call(a0);
    Generator_MaskOff(a0);
}
void actSt10lEnemy3_2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x127) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x140);

    Generator_Call(a0);
    Generator_MaskOff(a0);
}
void actSt10lEneCam1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x125) == 0) {
        D_004FA600[0].func = actSt10lEneCam1Chk;
        self->mail = D_004FA600;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt10lEneCam2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x126) == 0) {
        D_004FA640[0].func = actSt10lEneCam2Chk;
        self->mail = D_004FA640;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt10lEneCam3(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x128) == 0) {
        D_004FA660[0].func = actSt10lEneCam3Chk;
        self->mail = D_004FA660;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        FinishHint(0xE);
    }
}
void actSt10lEneKill(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x129) == 0) {
        D_004FA720[0].func = actSt10lEneKillChk;
        self->mail = D_004FA720;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt10lBoxA(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x12A) == 0) {
        D_004FA680[0].func = actSt10lBoxAChk;
        self->mail = D_004FA680;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        scpSearchGobj(0x3D1)->f16C = 0;
    }
}
void actSt10lBoxB(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x12B) == 0) {
        D_004FA6A0[0].func = actSt10lBoxBChk;
        self->mail = D_004FA6A0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        scpSearchGobj(0x3D2)->f16C = 0;
    }
}
void actSt10lGateXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xAE) == 0) {
        scpSearchGobj(0x3CB)->f16C = 0;
    } else {
        scpSearchGobj(0x3CA)->f16C = 0;
    }
}
void actSt10lFloorMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = D_004FA480;
    while (1) {
        _ACTWait(1);
    }
}
void actSt10lFloorSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    if (gflagChk(0x121) != 0) {
        D_004FA4C0[0].func = actSt10lFloorRight;
        sub->mail = D_004FA4C0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }

    D_004FA4E0[0].func = actSt10lFloorLeft;
    sub->mail = D_004FA4E0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt10lGondolaMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = D_004FA540;
    while (1) {
        _ACTWait(1);
    }
}
void actSt10lGondolaSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    if (gflagChk(0x123) != 0) {
        D_004FA580[0].func = actSt10lGondolaDown;
        sub->mail = D_004FA580;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }

    D_004FA5A0[0].func = actSt10lGondolaUp;
    sub->mail = D_004FA5A0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt10lEneCam1Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while ((D_00639EA8 == 0 || gflagChk(0x124) == 0)
        && (scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0
         || scpTriggerFloorAttr(D_00639EA8, 0x2000000) == 0)) {
        _ACTWait(1);
    }

    gflagOn(0x125);
}
void actSt10lBoxChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr((int)scpSearchGobj(0x3DC), 0x1000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x124);
}
void actSt10lSekizoEvent(int x) {
    volatile int local = x;
}
void actSt10lBoxAChk(volatile int a0)
{
    while (scpTriggerBall(a0, (int)scpSearchGobj(0x3D1), 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x12A);
    scpSearchGobj(0x3D1)->f16C = 0;
    _ACTWait(0x1E);
    soundSeDefPlay(0x4F6, 0, 0, 1);
}
void actSt10lBoxBChk(volatile int a0)
{
    while (scpTriggerBall(a0, (int)scpSearchGobj(0x3D2), 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x12B);
    scpSearchGobj(0x3D2)->f16C = 0;
    _ACTWait(0x1E);
    soundSeDefPlay(0x4F7, 0, 0, 1);
}
void actSt10lChainMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = D_004FA6C0;
    while (1) {
        _ACTWait(1);
    }
}
void actSt10lChainSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    D_0063AA08 = 1;

    D_004FA700[0].func = actSt10lChainMove;
    sub->mail = D_004FA700;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt10lEneKillChk(volatile int a0)
{
    int save;

    while (scpTriggerBall(a0, (int)D_00639EA4, 500.0f) == 0) {
        _ACTWait(1);
    }

    enable_game_pause = 0;
    _ACTWait(1);

    save = D_0063A538;
    D_0063A538 = 0;
    _ACTWait(0x1E);

    gflagOn(0x129);
    scpKillEnemyOne(0x3E8);
    scpKillEnemyOne(0x3E9);
    scpKillSpiderGroup(0x3EA);
    _ACTWait(0x1E);

    D_0063A538 = save;
    _ACTWait(1);
    enable_game_pause = 1;
}
