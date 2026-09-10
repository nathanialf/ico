#include "common.h"

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;

typedef struct Act {
    char unk00[0xD0];  /* 0x00 */
    ActMail *mainMail; /* 0xD0 */
    ActMail *mail;     /* 0xD4 */
} Act;

extern Act *actInitialize(int a0);

typedef struct PObjGObj {
    char pad00[0x164]; /* 0x000 */
    int act;           /* 0x164 */
    char pad168[0x4];  /* 0x168 */
    int f16C;          /* 0x16C */
} PObjGObj;

extern void _ACTWait(int a0);
extern int gflagChk(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern ActMail D_004F8330[];
extern ActMail D_004F8350[];
extern void actSt03tSwitchLChk(volatile int a0);
extern void actSt03tSwitchLUpChk(volatile int a0);

void actSt03tSwitchL(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x59) == 0) {
        stage_SetAnimation(0x16C, 0, 0);
        stage_SetAnimation(0x16E, 0, 0);

        D_004F8330[0].func = actSt03tSwitchLChk;
        self->mail = D_004F8330;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x16C, 0, 0x2D);
        stage_SetAnimation(0x16E, 0, -1);

        D_004F8350[0].func = actSt03tSwitchLUpChk;
        self->mail = D_004F8350;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern void gflagOn(int a0);
extern void SetWayGroupActive(int a0, int a1);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int scpTriggerFloorAttrTargetMan(int a0, int a1);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);
extern void SetCameraFlag_LwsCutBack(void);
extern int D_0028F4C0[];
extern ActMail D_004F8370[];
extern void actSt03tSwitchLUpChk(volatile int a0);

void actSt03tSwitchLChk(volatile int a0)
{
    Act *self = (Act *)((PObjGObj *)a0)->act;
    int i;

    i = 0;
    while (i < (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) {
        if (scpTriggerFloorAttrTargetMan(a0, 0x1000000) != 0) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }

    gflagOn(0x66);

    stage_SetAnimation(0x16C, 1, 0);
    soundSeDefPlay(0x4C4, 0, 0, 1);

    while (stage_CheckAnimationFrame(0x16C, 0x2D, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(0x59);

    stage_SetAnimation(0x16E, 1, 0);

    SetWayGroupActive(7, 1);

    gflagOn(0x5B);

    while (stage_CheckAnimationFrame(0x16E, 0x4B, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(0x4C2, 0, 0, 1);

    while (stage_CheckAnimationFrame(0x16E, 0x5A, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(0x4C3, 0, 0, 1);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(0x16E) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_004F8370[0].func = actSt03tSwitchLUpChk;
    self->mail = D_004F8370;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern void gflagOff(int a0);
extern int scpTriggerFloorAttrTargetMan(int a0, int a1);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern void scpCheckDisconnectWallStart(char *a0);
extern void scpCheckDisconnectWallEnd(char *a0);
extern void SetCameraFlag_LwsCutBack(void);
extern void SetWayGroupActive(int a0, int a1);
extern int D_00639EA8;
extern ActMail D_004F8390[];

void actSt03tSwitchLUpChk(volatile int a0)
{
    Act *self = (Act *)((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttrTargetMan(a0, 0x1000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(0x3C);

    gflagOff(0x59);

    stage_SetAnimation(0x16C, 1, 0x2E);
    soundSeDefPlay(0x4C4, 0, 0, 1);

    while (stage_CheckAnimationFrame(0x16C, 0x5A, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(0x16F, 1, 0);

    if (D_00639EA8 != 0) {
        scpCheckDisconnectWallStart((char *)D_00639EA8);
    }

    SetWayGroupActive(7, 0);

    soundSeDefPlay(0x4C2, 0, 0, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C3, 0, 0, 1);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFrame(0x16F, 0x78, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (D_00639EA8 != 0) {
        scpCheckDisconnectWallEnd((char *)D_00639EA8);
    }

    D_004F8390[0].func = actSt03tSwitchLChk;
    self->mail = D_004F8390;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern void _ACTWait(int a0);
extern int gflagChk(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern ActMail D_004F83B0[];
extern ActMail D_004F83D0[];
extern void actSt03tSwitchRChk(volatile int a0);
extern void actSt03tSwitchRUpChk(volatile int a0);

void actSt03tSwitchR(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x5A) == 0) {
        stage_SetAnimation(0x16D, 0, 0);
        stage_SetAnimation(0x170, 0, 0);

        D_004F83B0[0].func = actSt03tSwitchRChk;
        self->mail = D_004F83B0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x16D, 0, 0x2D);
        stage_SetAnimation(0x170, 0, -1);

        D_004F83D0[0].func = actSt03tSwitchRUpChk;
        self->mail = D_004F83D0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern ActMail D_004F83F0[];

void actSt03tSwitchRChk(volatile int a0)
{
    Act *self = (Act *)((PObjGObj *)a0)->act;
    int i;

    i = 0;
    while (i < (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) {
        if (scpTriggerFloorAttrTargetMan(a0, 0x2000000) != 0) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }

    gflagOn(0x66);

    stage_SetAnimation(0x16D, 1, 0);
    soundSeDefPlay(0x4C4, 0, 0, 1);

    while (stage_CheckAnimationFrame(0x16D, 0x2D, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(0x170, 1, 0);

    SetWayGroupActive(5, 1);

    gflagOn(0x5B);

    soundSeDefPlay(0x4C2, 0, 0, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C3, 0, 0, 1);

    while (stage_CheckAnimationFinish(0x170) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(0x5A);

    D_004F83F0[0].func = actSt03tSwitchRUpChk;
    self->mail = D_004F83F0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern int stage_CheckAnimationFinish(int a0);
extern int D_0028F4C0[];
extern ActMail D_004F8410[];

void actSt03tSwitchRUpChk(volatile int a0)
{
    Act *self = (Act *)((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttrTargetMan(a0, 0x2000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) * 0xA);

    gflagOff(0x5A);

    stage_SetAnimation(0x16D, 1, 0x2E);
    soundSeDefPlay(0x4C4, 0, 0, 1);

    while (stage_CheckAnimationFrame(0x16D, 0x5A, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(0x171, 1, 0);

    SetWayGroupActive(5, 0);

    soundSeDefPlay(0x4C2, 0, 0, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C3, 0, 0, 1);

    while (stage_CheckAnimationFinish(0x171) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_004F8410[0].func = actSt03tSwitchRChk;
    self->mail = D_004F8410;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern void _ACTWait(int a0);
extern int gflagChk(int a0);
extern PObjGObj *scpSearchGobj(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);

void actSt03tGene(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    Generator_Mask((int)scpSearchGobj(0x36D));
    Generator_Mask((int)scpSearchGobj(0x36E));

    while (gflagChk(0x69) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(0x14);
    Generator_Call(a0);

    Generator_Call((int)scpSearchGobj(0x36D));
    Generator_Call((int)scpSearchGobj(0x36E));
}

extern void scpTransGObj(void *a0, float x, float y, float z);
extern void ReInitBoxGeo(PObjGObj *a0);
extern void gflagOn(int a0);

void actSt03tBoxA(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x12A) == 0) {
        scpSearchGobj(0x361)->f16C = 0;
    } else {
        scpSearchGobj(0x354)->f16C = 0;
        scpSearchGobj(0x35F)->f16C = 0;
        scpSearchGobj(0x361)->f16C = 1;

        scpTransGObj(scpSearchGobj(0x361), 0.0f, -200.0f, 0.0f);
        _ACTWait(1);
        ReInitBoxGeo(scpSearchGobj(0x361));
    }
}

void actSt03tBoxB(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x12B) == 0) {
        scpSearchGobj(0x362)->f16C = 0;
    } else {
        scpSearchGobj(0x355)->f16C = 0;
        scpSearchGobj(0x360)->f16C = 0;
        scpSearchGobj(0x362)->f16C = 1;

        gflagOn(0x62);

        scpTransGObj(scpSearchGobj(0x362), 0.0f, -400.0f, 0.0f);
        _ACTWait(1);
        ReInitBoxGeo(scpSearchGobj(0x362));
    }
}

extern int gflagChk(int a0);
extern void SetWayGroupActive(int a0, int a1);

void actSt03tInit(void)
{
    if (gflagChk(0x5B) != 0) {
        SetWayGroupActive(7, 1);
    } else {
        SetWayGroupActive(7, 0);
    }

    if (gflagChk(0x5C) != 0) {
        SetWayGroupActive(5, 1);
    } else {
        SetWayGroupActive(5, 0);
    }
}

extern void _ACTWait(int a0);
extern int gflagChk(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern void FinishHint(int a0);
extern ActMail D_004F8550[];
extern void actSt03tGirlUpChk(volatile int a0);

void actSt03tGirlUp(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x5D) == 0) {
        D_004F8550[0].func = actSt03tGirlUpChk;
        self->mail = D_004F8550;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        FinishHint(0xC);
    }
}

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F8430[];
extern void actSt03tGirlCamStartChk(volatile int a0);

void actSt03tGirlCam(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    D_004F8430[0].func = actSt03tGirlCamStartChk;
    self->mail = D_004F8430;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern void _ACTWait(int a0);
extern void scpSekizou(int a0, int a1, int a2, int a3, int a4, float x1, float y1, float z1,
                       float x2, float y2, float z2);

void actSt03tSekizo(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x5F, 0x50, 0, 0x12, -913.0f, -400.0f, 605.0f, -1000.0f, -400.0f, 550.0f);
}

extern void _ACTWait(int a0);
extern int gflagChk(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F84B0[];
extern ActMail D_004F84D0[];
extern void actSt03tWayOnChk(volatile int a0);
extern void actSt03tWayOffChk(volatile int a0);

void actSt03tWay(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x64) == 0) {
        D_004F84B0[0].func = actSt03tWayOnChk;
        self->mail = D_004F84B0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        D_004F84D0[0].func = actSt03tWayOffChk;
        self->mail = D_004F84D0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern void _ACTWait(int a0);
extern int gflagChk(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F8490[];
extern void actSt03tEneChk(volatile int a0);

void actSt03tEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x68) == 0) {
        D_004F8490[0].func = actSt03tEneChk;
        self->mail = D_004F8490;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern void _ACTWait(int a0);
extern int gflagChk(int a0);
extern void SleepHint(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F8530[];
extern void actSt03tGirlPosChk(volatile int a0);

void actSt03tGirlPos(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x65) == 0) {
        SleepHint(0xC);

        D_004F8530[0].func = actSt03tGirlPosChk;
        self->mail = D_004F8530;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F8570[];
extern void actSt03tHint1OffChk(volatile int a0);

void actSt03tHint1Sleep(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    D_004F8570[0].func = actSt03tHint1OffChk;
    self->mail = D_004F8570;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt03tGirlCamEvent(int x)
{
    volatile int local = x;
}

extern int D_00639EA4;
extern int D_00639EA8;
extern void _ACTWait(int a0);
extern int scpTriggerBall(int a0, int a1, float radius);
extern int ForMotionViewer_GetCurrentMotion(int a0);
extern int CameraGetTarget(void);
extern void Camctrl_SetTarget(int a0, int a1, int a2);
extern void CameraSetCameraSet(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F8450[];
extern void actSt03tGirlCamEndChk(volatile int a0);

void actSt03tGirlCamStartChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0xCA) {
        _ACTWait(1);
    }

    CameraGetTarget();
    Camctrl_SetTarget(D_00639EA8, 0, 3);
    _ACTWait(0xF);
    CameraSetCameraSet(0x30);

    D_004F8450[0].func = actSt03tGirlCamEndChk;
    sub->mail = D_004F8450;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern int D_00639EA4;
extern void _ACTWait(int a0);
extern int scpTriggerBall(int a0, int a1, float radius);
extern int ForMotionViewer_GetCurrentMotion(int a0);
extern int CameraGetTarget(void);
extern void CameraSetCameraSet_Default(void);
extern void Camctrl_ExitEveRock(void);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F8470[];
extern void actSt03tGirlCamStartChk(volatile int a0);

void actSt03tGirlCamEndChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0xCA) {
        _ACTWait(1);
    }

    CameraGetTarget();
    _ACTWait(0x5A);
    CameraSetCameraSet_Default();
    Camctrl_ExitEveRock();

    D_004F8470[0].func = actSt03tGirlCamStartChk;
    sub->mail = D_004F8470;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt03tSekizoEvent(int x)
{
    volatile int local = x;
}

extern int D_00639EA4;
extern int D_00639EA8;
extern int D_0063AA08;
extern void _ACTWait(int a0);
extern int scpTriggerBall(int a0, int a1, float radius);
extern void lt_switch_layout(int a0);
extern void scpSleepEnemyOne(int a0);
extern void scpWakeupEnemyOne(int a0);
extern void gflagOn(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);

void actSt03tEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerBall(a0, D_00639EA4, 100.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyOne(0xEAD);
    gflagOn(0x68);
    gflagOn(0x69);
    stage_SetAnimation(0x51, 1, 0);

    while (stage_CheckAnimationFinish(0x51) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(0x36);
    D_0063AA08 = 0;
    scpWakeupEnemyOne(0xEAD);
}

extern int D_00639EA8;
extern void _ACTWait(int a0);
extern int scpCheckExistAliveEnemy(void);
extern int scpTriggerFloorAttr(int a0, int a1);
extern void SetWayGroupActive(int a0, int a1);
extern void gflagOn(int a0);
extern void ACTSendMailCorrect(int a0, int mail);

/* The way-on watcher's mail record: it installs actSt03tWayOffChk here and
   posts it. Word 0 of each entry is the mail id the entry answers (0x1AE the
   actor post, 0x1AD the trailing entry); .func is filled in at run time.
   Named for the thread that owns and posts it. */
static ActMail way_on_mes[2] = {{0x1AE}, {0x1AD}};

extern void actSt03tWayOffChk(volatile int a0);

void actSt03tWayOnChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() != 0 || scpTriggerFloorAttr(D_00639EA8, 0x3000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(0x11, 1);
    gflagOn(0x64);

    way_on_mes[0].func = actSt03tWayOffChk;
    sub->mail = way_on_mes;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern int D_00639EA8;
extern void _ACTWait(int a0);
extern int scpCheckExistAliveEnemy(void);
extern int scpTriggerFloorAttr(int a0, int a1);
extern void SetWayGroupActive(int a0, int a1);
extern void gflagOff(int a0);
extern void ACTSendMailCorrect(int a0, int mail);

/* The way-off watcher's own mail record (installs actSt03tWayOnChk). */
static ActMail way_off_mes[2] = {{0x1AE}, {0x1AD}};

extern void actSt03tWayOnChk(volatile int a0);

void actSt03tWayOffChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() == 0 && scpTriggerFloorAttr(D_00639EA8, 0x3000000) != 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(0x11, 0);
    gflagOff(0x64);

    way_off_mes[0].func = actSt03tWayOnChk;
    sub->mail = way_off_mes;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern int D_00639EA8;
extern void _ACTWait(int a0);
extern int scpTriggerFloorAttr(int a0, int a1);
extern void gflagOn(int a0);
extern void WakeupHint(int a0);

void actSt03tGirlPosChk(volatile int a0)
{
    while (D_00639EA8 == 0 || scpTriggerFloorAttr(D_00639EA8, 0x5000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x65);
    WakeupHint(0xC);
}

extern char D_00622820[];
extern void debug_StdPrintfDummy();
extern void FinishHint(int a0);

void actSt03tGirlUpChk(volatile int a0)
{
    while (D_00639EA8 == 0 || scpTriggerFloorAttr(D_00639EA8, 0x4000000) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy(D_00622820);
    gflagOn(0x5D);
    FinishHint(0xC);
}

extern int D_0028F4C0[];
extern void _ACTWait(int a0);
extern void WakeupHint(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F85B0[];
extern void actSt03tHint1OffChk(volatile int a0);

void actSt03tHint1OnChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0x3C);
    WakeupHint(0xC);

    D_004F85B0[0].func = actSt03tHint1OffChk;
    sub->mail = D_004F85B0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern void _ACTWait(int a0);
extern int gflagChk(int a0);
extern void SleepHint(int a0);
extern void gflagOff(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F8590[];
extern void actSt03tHint1OnChk(volatile int a0);

void actSt03tHint1OffChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (gflagChk(0x66) == 0) {
        _ACTWait(1);
    }

    SleepHint(0xC);
    gflagOff(0x66);

    D_004F8590[0].func = actSt03tHint1OnChk;
    sub->mail = D_004F8590;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
