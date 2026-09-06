#include "common.h"

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;
typedef struct Act {
    char unk00[0xD0];           /* 0x00 */
    ActMail *mainMail;          /* 0xD0 */
    ActMail *mail;              /* 0xD4 */
} Act;
typedef struct PObjGObj {
    char pad00[0x8];            /* 0x000 */
    int f08;                    /* 0x008 */
    int f0C;                    /* 0x00C */
    char pad10[0x14C];          /* 0x010 */
    char *f15C;                 /* 0x15C */
    char pad160[0x4];           /* 0x160 */
    Act *act;                   /* 0x164 */
    char pad168[0x4];           /* 0x168 */
    int f16C;                   /* 0x16C */
} PObjGObj;

extern void _ACTWait(int a0);
extern Act *actInitialize(int a0);
extern PObjGObj *scpSearchGobj(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int gflagChk(int a0);
extern void gflagOn(int a0);
extern void gamesysObjInfoCls(int kind, int no);
extern ActMail D_004FA740[];
extern void actSt10rFloorChk(volatile int a0);
extern void SleepHint(int a0);
extern ActMail D_004FA760[];
extern void actSt10rFloorHitChk(volatile int a0);
extern ActMail D_004FA780[];
extern void actSt10rCageMain(volatile int a0);
extern void scpSetCageVelocityFriction(int id, float f);
extern void SetRotObjectLockFlag(PObjGObj *a0, int a1);
extern ActMail D_004FA7A0[];
extern void actSt10rTowerChk(volatile int a0);
extern ActMail D_004FA980[];
extern void actSt10rTowerResqueChk(volatile int a0);
extern ActMail D_004FA7C0[];
extern void actSt10rExitChk(volatile int a0);
extern ActMail D_004FA800[];
extern void actSt10rChainMain(volatile int a0);
extern ActMail D_004FA840[];
extern void actSt10rEneChk(volatile int a0);
extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void gflagOff(int a0);
extern ActMail D_004FA920[];
extern void actSt10rWayOnChk(volatile int a0);
extern char *cage10r;
extern int D_00639EAC;
extern int D_0063C574;
extern void AdpcmPlay(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int iosPadActRequest(int port, int id);
extern long long D_00622DF0[];
extern int D_00639EA8;
extern void _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);
extern int D_004FA7E0[];
extern ActMail D_004FA820[];
extern int D_0063AA08;
extern void actSt10rChainMove(volatile int a0);
extern char *chain10r;
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);
extern void soundSeDefStop(int handle);
extern int D_00639EA4;
extern int scpTriggerFloorAttr(int a0, int a1);
extern void FinishHint(int a0);
extern ActMail D_004FA8C0[];
extern void actSt10rFenceDownChk(volatile int a0);
extern ActMail D_004FA900[];
extern void actSt10rFenceDownChk2(volatile int a0);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern int scpTriggerBall(int a0, int a1, float radius);
extern void OnGirlEscortFlag(void);
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern ActMail D_004FA940[];
extern void actSt10rWayOffChk(volatile int a0);
extern int scpCheckExistAliveEnemy(void);
extern void SetWayGroupActive(int a0, int a1);
extern ActMail D_004FA960[];
extern int ForMotionViewer_GetCurrentMotion(int a0);
extern void scpPlayStart(int a0);
extern void scpPlayPosSet(int a0, float f12, float f13, float f14);
extern void scpPlayMot(int a0, int mot);
extern void scpPlayEnd(int a0);


void actSt10rInit(void)
{
    if (gflagChk(0x12C) != 0) {
        stage_SetAnimation(0x181, 0, -1);
        SetWayGroupActive(0xF, 1);
    } else {
        stage_SetAnimation(0x181, 0, 0);
    }

    if (gflagChk(0x12E) == 0) {
        SetWayGroupActive(0x17, 0);
        stage_SetAnimation(0x185, 0, 0);
    } else {
        SetWayGroupActive(0x17, 1);
        stage_SetAnimation(0x185, 0, -1);
        FinishHint(0x15);
    }

    if (gflagChk(0x12D) == 0) {
        stage_SetAnimation(0x184, 0, 0);
    } else {
        stage_SetAnimation(0x184, 0, -1);
        FinishHint(0x16);
    }
}

void actSt10rEnd(void)
{
    gamesysObjInfoCls(scpSearchGobj(0x662)->f0C, scpSearchGobj(0x662)->f08);
    gamesysObjInfoCls(scpSearchGobj(0x660)->f0C, scpSearchGobj(0x660)->f08);
}
extern void lt_switch_layout(int a0);
extern void scpSleepEnemyAll(void);
extern void scpWakeupEnemyAll(void);
extern void scpAdpcmPlayRequestFunc(int a0, void *a1, int a2, int a3, int a4);
extern int scpAdpcmPlayRequestNum(void);
extern void scpAdpcmFadeCloseFunc(void *a0, int a1);
extern int actCreateSubThread(void *entry, int prio);
extern void iosThreadSetPri(int *a0, int a1);
extern void scpFadeOut(float t, int a1, int a2, int a3);
extern void scpFadeIn(float f);
extern int scpFadeChk(void);
extern int lt_fade_status(void);
extern int D_0028F8F4[];
extern void actSt10rChainMoveSub(volatile int a0);

extern void WakeupHint(int a0);
extern int st10r_floor;
extern void actSt10rFloorSub(volatile int a0);

void actSt10rFloorChk(volatile int a0)
{
    int th;

    while (scpTriggerBall(a0, D_00639EA4, 50.0f) == 0) {
        _ACTWait(1);
    }

    iosPadActRequest(D_00639EAC, 0x10);

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    gflagOn(0x12C);
    WakeupHint(0x15);

    scpAdpcmPlayRequestFunc(0x5C, &st10r_floor, 1, 1, 1);
    while (st10r_floor == 0) { _ACTWait(1); }

    D_0063C574 = 0;
    th = actCreateSubThread(actSt10rFloorSub, 0x15);
    while (D_0063C574 == 0 &&
           ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri((int *)(th + 0x24), 0x22);

    if (D_0063C574 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        scpAdpcmFadeCloseFunc(&st10r_floor, 0x200);
        while (scpFadeChk() != 0) { _ACTWait(1); }
        while (lt_fade_status() != 2) { _ACTWait(1); }
        stage_SetAnimation(0x181, 0, -1);
        scpFadeIn(3.0f);
    }

    SetWayGroupActive(0xF, 1);
    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}
extern float scpGetRotObjectRotCount(int a0);
extern void HotInitCageGeo(PObjGObj *a0);
extern void actSt10rCageSub(volatile int a0);

void actSt10rFloorHitChk(volatile int a0)
{
    for (;;) {
        while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0 ||
               gflagChk(0x12C) != 0 ||
               (ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0x2F &&
                ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0x30 &&
                ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0x31 &&
                ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0x3E)) {
            _ACTWait(1);
        }

        stage_SetAnimation(0x182, 1, 0);

        while (stage_CheckAnimationFrame(0x182, 0xC, 0) == 0) { _ACTWait(1); }
        _ACTWait(1);

        soundSeDefPlay(0x537, 0, 0, 1);
        soundSeDefPlay(0x537, 0, 0, 1);

        while (stage_CheckAnimationFinish(0x182) == 0) { _ACTWait(1); }
        _ACTWait(1);
    }
}

void actSt10rCageMain(volatile int a0)
{
    int th;

    while (!(scpGetRotObjectRotCount(0x645) < -2.0f)) { _ACTWait(1); }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    gflagOn(0x12D);
    FinishHint(0x16);

    SetRotObjectLockFlag(scpSearchGobj(0x645), 1);

    D_0063C574 = 0;
    scpAdpcmPlayRequestFunc(0x49, &cage10r, 1, 1, 0);

    th = actCreateSubThread(actSt10rCageSub, 0x15);

    while (D_0063C574 == 0 &&
           ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri((int *)(th + 0x24), 0x22);

    if (D_0063C574 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (cage10r == 0) { _ACTWait(1); }

        scpAdpcmFadeCloseFunc(&cage10r, 0x200);

        while (scpFadeChk() != 0) { _ACTWait(1); }
        while (lt_fade_status() != 2) { _ACTWait(1); }

        stage_SetAnimation(0x184, 0, -1);
        _ACTWait(1);

        HotInitCageGeo(scpSearchGobj(0x65B));
        _ACTWait(1);

        scpFadeIn(3.0f);
    }

    scpWakeupEnemyAll();

    D_0063AA08 = 0;

    lt_switch_layout(0x36);
}
extern char *D_0063BF9C;
extern int scpIsBombExplode(int a0);
extern void reg_SetScissorSw(int a0);
extern void iosPadActStopAll(void);
extern void SetCameraFlag_GamecamCutBack(void);
extern void scpPlayMot(int a0, int mot);
extern void actSt10rGirlWay(volatile unsigned int a0);
extern void actSt10rTowerConte(volatile int a0);

void actSt10rTowerChk(volatile int a0)
{
    int th;
    int n;
    int f;

    while ((n = scpIsBombExplode(0x13)) == 0 ||
           scpTriggerBall(a0, n, 350.0f) == 0) {
        _ACTWait(1);
    }

    if (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x4000000) != 0) {
        actCreateSubThread(actSt10rGirlWay, 0x15);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    FinishHint(0x15);

    reg_SetScissorSw(1);

    scpAdpcmPlayRequestFunc(0x48, &D_0063BF9C, 1, 1, 0);

    _ACTWait(0x3C);
    while (D_0063BF9C == 0) { _ACTWait(1); }

    gflagOn(0x12E);

    th = actCreateSubThread(actSt10rTowerConte, 0x15);
    D_0063C574 = 0;

    while (D_0063C574 == 0 &&
           ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    f = D_0063C574 ^ 1;

    if (f) {
        scpAdpcmFadeCloseFunc(&D_0063BF9C, 0xC0);
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) { _ACTWait(1); }
    }

    iosPadActStopAll();

    iosThreadSetPri((int *)(th + 0x24), 0x22);

    if (f) {
        stage_SetAnimation(0x185, 1, -1);
        SetCameraFlag_GamecamCutBack();
        scpPlayMot(D_00639EA4, 0);
        SetCameraFlag_GamecamCutBack();
        scpFadeIn(8.0f);
        while (scpFadeChk() != 0) { _ACTWait(1); }
    }

    scpSearchGobj(0x63A)->f16C = 1;
    scpSearchGobj(0x63B)->f16C = 1;

    scpWakeupEnemyAll();

    D_0063AA08 = 0;

    lt_switch_layout(0x36);

    reg_SetScissorSw(0);

    SetWayGroupActive(0x17, 1);

    gflagOn(0x12F);
}
extern int D_0028F4C0[];

void actSt10rTowerConte(volatile int a0)
{
    stage_SetAnimation(0x185, 1, 0);

    AdpcmPlay(*(int *)(D_0063BF9C + 0x2C));

    scpSearchGobj(0x63A)->f16C = 0;
    scpSearchGobj(0x63B)->f16C = 0;

    while (stage_CheckAnimationFrame(0x185, 0xD7, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0xF);

    while (stage_CheckAnimationFrame(0x185, 0x10E, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFrame(0x185, 0x118, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0xF);

    while (stage_CheckAnimationFrame(0x185, 0x12C, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_CheckAnimationFinish(0x185) == 0) { _ACTWait(1); }
    _ACTWait(1);

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 6);

    D_0063C574 = 1;
    _ACTWait(0);
}
void actSt10rChainMove(volatile int a0)
{
    int th;

    lt_switch_layout(0x37);

    scpSleepEnemyAll();

    gflagOn(0x130);

    scpSearchGobj(0x656)->f16C = 1;

    scpAdpcmPlayRequestFunc(0x5D, &chain10r, 1, 1, 0);

    D_0063C574 = 0;

    th = actCreateSubThread(actSt10rChainMoveSub, 0x15);

    while (D_0063C574 == 0 &&
           ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri((int *)(th + 0x24), 0x22);

    if (D_0063C574 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (chain10r == 0) {
            _ACTWait(1);
        }

        scpAdpcmFadeCloseFunc(&chain10r, 0x200);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(0x183, 0, -1);

        scpFadeIn(3.0f);
    }

    soundSeDefPlay(0x508, 0, 0, 1);

    iosPadActRequest(D_00639EAC, 0x11);

    scpWakeupEnemyAll();

    D_0063AA08 = 0;

    lt_switch_layout(0x36);
}
extern ActMail D_004FA860[];
extern void actSt10rFenceUpChk(volatile int a0);
extern ActMail D_004FA880[];
extern void scpLinkBGAtoLayoutedTarget(int a0, int a1);

void actSt10rFence(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x13D) == 0) {
        scpSearchGobj(0x65F)->f16C = 0;
        scpSearchGobj(0x660)->f16C = 0;
        scpSearchGobj(0x663)->f16C = 0;
        scpSearchGobj(0x664)->f16C = 0;
        scpSearchGobj(0x665)->f16C = 0;
        scpSearchGobj(0x666)->f16C = 0;
        scpSearchGobj(0x667)->f16C = 0;
        scpSearchGobj(0x668)->f16C = 0;
        scpSearchGobj(0x669)->f16C = 0;
        scpSearchGobj(0x66A)->f16C = 0;

        scpLinkBGAtoLayoutedTarget(0x661, 0x95);

        stage_SetAnimation(0x95, 0, 0x1E);

        SetWayGroupActive(0x25, 1);
        SetWayGroupActive(0x26, 1);

        D_004FA860[0].func = actSt10rFenceUpChk;
        self->mail = D_004FA860;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        scpSearchGobj(0x661)->f16C = 0;
        scpSearchGobj(0x662)->f16C = 0;
        scpSearchGobj(0x667)->f16C = 0;
        scpSearchGobj(0x668)->f16C = 0;
        scpSearchGobj(0x669)->f16C = 0;
        scpSearchGobj(0x66A)->f16C = 0;

        gflagOff(0x13D);

        scpLinkBGAtoLayoutedTarget(0x65F, 0x95);

        stage_SetAnimation(0x95, 0, 0);

        if (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x2000000) != 0) {
            scpPlayPosSet(D_00639EA8, 417.0f, 900.0f, -1096.0f);
        }

        D_004FA880[0].func = actSt10rFenceDownChk2;
        self->mail = D_004FA880;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004FA8A0[];
extern void actSt10rFenceUpChk(volatile int a0);

void actSt10rFenceDownChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (scpTriggerBall(a0, (int)scpSearchGobj(0x661), 5.0f) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(0x667)->f16C = 0;
    scpSearchGobj(0x668)->f16C = 0;
    scpSearchGobj(0x669)->f16C = 0;
    scpSearchGobj(0x66A)->f16C = 0;

    stage_SetAnimation(0x95, 1, 0);

    while (stage_CheckAnimationFrame(0x95, 0xA, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(0x53B, 0, 0, 1);

    while (stage_CheckAnimationFrame(0x95, 0x1E, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(0x25, 1);
    SetWayGroupActive(0x26, 1);

    gflagOff(0x134);

    D_004FA8A0[0].func = actSt10rFenceUpChk;
    sub->mail = D_004FA8A0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
/*SWEEPactSt10rFenceUpChk*/

void actSt10rFenceUpChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (scpTriggerBall(a0, (int)scpSearchGobj(0x661), 5.0f) != 0) {
        _ACTWait(1);
    }

    scpSearchGobj(0x667)->f16C = 1;
    scpSearchGobj(0x668)->f16C = 1;
    scpSearchGobj(0x669)->f16C = 1;
    scpSearchGobj(0x66A)->f16C = 1;

    stage_SetAnimation(0x95, 1, 0x1F);

    while (stage_CheckAnimationFrame(0x95, 0x28, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(0x53B, 0, 0, 1);

    while (stage_CheckAnimationFinish(0x95) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(0x25, 0);
    SetWayGroupActive(0x26, 0);

    gflagOn(0x134);

    D_004FA8C0[0].func = actSt10rFenceDownChk;
    sub->mail = D_004FA8C0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
/*SWEEP-ENDactSt10rFenceUpChk*/
extern ActMail D_004FA8E0[];
extern void actSt10rFenceUpChk2(volatile int a0);

void actSt10rFenceDownChk2(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (scpTriggerBall(a0, (int)scpSearchGobj(0x65F), 5.0f) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(0x663)->f16C = 0;
    scpSearchGobj(0x664)->f16C = 0;
    scpSearchGobj(0x665)->f16C = 0;
    scpSearchGobj(0x666)->f16C = 0;

    stage_SetAnimation(0x95, 1, 0);

    while (stage_CheckAnimationFrame(0x95, 0xA, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(0x53B, 0, 0, 1);

    while (stage_CheckAnimationFrame(0x95, 0x1E, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(0x25, 1);
    SetWayGroupActive(0x26, 1);

    gflagOff(0x134);

    D_004FA8E0[0].func = actSt10rFenceUpChk2;
    sub->mail = D_004FA8E0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rFenceUpChk2);

void actSt10rFloor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x12C) == 0) {
        SleepHint(0x15);

        D_004FA740[0].func = actSt10rFloorChk;
        self->mail = D_004FA740;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSt10rFloorHit(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x12C) == 0) {
        D_004FA760[0].func = actSt10rFloorHitChk;
        self->mail = D_004FA760;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSt10rCage(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    scpSetCageVelocityFriction(0x65B, 0.95f);

    if (gflagChk(0x12D) == 0) {
        D_004FA780[0].func = actSt10rCageMain;
        self->mail = D_004FA780;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        SetRotObjectLockFlag(scpSearchGobj(0x645), 1);
    }
}

void actSt10rTower(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x12E) == 0) {
        D_004FA7A0[0].func = actSt10rTowerChk;
        self->mail = D_004FA7A0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSt10rTowerResque(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x12E) == 0) {
        D_004FA980[0].func = actSt10rTowerResqueChk;
        self->mail = D_004FA980;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSt10rExit(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    D_004FA7C0[0].func = actSt10rExitChk;
    self->mail = D_004FA7C0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt10rChain(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x130) == 0) {
        stage_SetAnimation(0x183, 0, 0);
        scpSearchGobj(0x656)->f16C = 0;

        D_004FA800[0].func = actSt10rChainMain;
        self->mail = D_004FA800;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x183, 0, -1);
    }
}
extern void scpSekizou(int a0, int a1, int a2, int a3, int a4,
                       float x1, float y1, float z1,
                       float x2, float y2, float z2);

void actSt10rSekizo(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x131, 0x186, 0, 0x12,
               0.0f, 327.0f, 4649.0f,
               -75.0f, 327.0f, 4649.0f);
}

void actSt10rEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x132) == 0) {
        D_004FA840[0].func = actSt10rEneChk;
        self->mail = D_004FA840;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSt10rEnemy1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x133) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);

    Generator_MaskOff(a0);
}

void actSt10rEnemy2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x133) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(a0);
}

void actSt10rElv(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x13D) != 0) {
        scpSearchGobj(0x661)->f16C = 0;
        scpSearchGobj(0x662)->f16C = 0;
        gflagOff(0x13D);
    } else {
        scpSearchGobj(0x65F)->f16C = 0;
        scpSearchGobj(0x660)->f16C = 0;
    }
}
void actSt10rGateXL(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xF3) == 0) {
        scpSearchGobj(0x63E)->f16C = 0;
    } else {
        scpSearchGobj(0x63D)->f16C = 0;
    }
}

void actSt10rWay(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    D_004FA920[0].func = actSt10rWayOnChk;
    self->mail = D_004FA920;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt10rFloorSub(volatile int a0)
{
    stage_SetAnimation(0x181, 1, 0);

    while (stage_CheckAnimationFrame(0x181, 0x43, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_CheckAnimationFrame(0x181, 0x50, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFinish(0x181) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C574 = 1;
    _ACTWait(0);
}

void actSt10rCageSub(volatile int a0)
{
    _ACTWait(0x1E);

    while (cage10r == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(cage10r + 0x2C));

    stage_SetAnimation(0x184, 1, 0);

    while (stage_CheckAnimationFinish(0x184) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x11);

    D_0063C574 = 1;
    _ACTWait(0);
}

void actSt10rGirlWay(volatile unsigned int a0)
{
    long long buf[2];
    buf[0] = D_00622DF0[0];
    buf[1] = D_00622DF0[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}

void actSt10rExitChk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 400.0f) == 0 ||
           scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x135);
    gflagOff(0x13D);

    if (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x2000000) != 0) {
        OnGirlEscortFlag();
        RequestStageChange(1, D_00639EA4, D_00639EA8, 2.0f, 8.0f);
    }
    RequestStageChange(1, D_00639EA4, 0, 2.0f, 8.0f);
}

void actSt10rChainMain(volatile int a0)
{
    int sub = *(int *)(a0 + 0x164);

    *(int *)(sub + 0xD0) = (int)D_004FA7E0;
    while (1) {
        _ACTWait(1);
    }
}

void actSt10rChainSwitch(volatile int a0)
{
    Act *self = ((PObjGObj *)a0)->act;

    D_0063AA08 = 1;
    self->mainMail = 0;
    D_004FA820[0].func = actSt10rChainMove;
    self->mail = D_004FA820;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt10rChainMoveSub(volatile int a0)
{
    int se;

    _ACTWait(0x1E);

    while (chain10r == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(chain10r + 0x2C));

    stage_SetAnimation(0x183, 1, 0);

    se = soundSeDefPlay(0x507, 0, 0, 1);

    _ACTWait(0xB4);

    soundSeDefStop(se);

    D_0063C574 = 1;
    _ACTWait(0);
}
void actSt10rSekizoEvent(int x) {
    volatile int local = x;
}

void actSt10rEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0x1000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA4, 0x3000000) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    gflagOn(0x132);
    gflagOn(0x133);
}

void actSt10rWayOnChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() != 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x5000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(0x14, 1);

    D_004FA940[0].func = actSt10rWayOffChk;
    sub->mail = D_004FA940;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt10rWayOffChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() == 0 &&
           scpTriggerFloorAttr(D_00639EA8, 0x6000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(0x14, 0);

    D_004FA960[0].func = actSt10rWayOnChk;
    sub->mail = D_004FA960;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt10rTowerResqueChk(volatile int a0)
{
    while (gflagChk(0x12F) != 0 ||
           gflagChk(0x12E) == 0 ||
           scpTriggerBall(a0, D_00639EA4, 500.0f) == 0 ||
           (ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0x54 &&
            ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0x55)) {
        _ACTWait(1);
    }

    scpPlayStart(D_00639EA4);
    scpPlayPosSet(D_00639EA4, 135.0f, 321.0f, 2101.0f);
    scpPlayMot(D_00639EA4, 0);
    _ACTWait(0x78);
    scpPlayEnd(D_00639EA4);
}
