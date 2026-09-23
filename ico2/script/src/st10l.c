#include "common.h"
#include "st10l.h"
#include "layout_texture.h"
#include "pad.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "girl_act.h"
#include "way_llf.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "typedef.h"

/* kept local: this TU's bytes only come out with its own view of ActSt10L. */
/* kept local: this TU's bytes only come out with its own view of Act, so it
   keeps one under its own name; the shared view is in ico2/common/include/typedef.h. */
typedef struct ActSt10L {
    char unk00[0x34];  /* 0x00 */
    int f34;           /* 0x34 */
    char unk38[0x98];  /* 0x38 */
    ActMail *mainMail; /* 0xD0 */
    ActMail *mail;     /* 0xD4 */
} ActSt10L;

/* kept local: this TU's bytes only come out with its own view of PObjGObj, so it
   keeps one under its own name; the shared view is in ico2/common/include/typedef.h. */
typedef struct PObjGObjSt10L {
    char pad00[0x164]; /* 0x000 */
    ActSt10L *act;     /* 0x164 */
    char pad168[0x4];  /* 0x168 */
    int f16C;          /* 0x16C */
} PObjGObjSt10L;

/* the shared pad-state array (op.c's PadState, GsBase.c's GsbPad): 0x58 per
   pad, trg at 0x4. */

extern Pad D_0028F8F0[];
/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObjSt10L *scpSearchGobj(int a0);
/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
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
/* kept local: this TU's uses of scpTriggerBall do not fit the prototype in script.h */
extern int scpTriggerBall(int a0, int a1, float radius);
/* as script.h declares it; this TU does not include that header */
extern void scpSleepEnemyAll(void);
/* as script.h declares it; this TU does not include that header */
extern void scpKillEnemyOne(int a0);
/* as script.h declares it; this TU does not include that header */
extern void scpKillSpiderGroup(int a0);
/* as script.h declares it; this TU does not include that header */
extern void scpWakeupEnemyAll(void);
/* kept local: this TU's uses of _SCPMoveCharactorByWay do not fit the prototype in script.h */
extern void _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);
extern int D_0028F4C0[];
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern void scpAdpcmFadeCloseFunc(int *handle, int mask);
/* kept local: this TU's uses of scpAdpcmCloseChkFunc do not fit the prototype in script.h */
extern int scpAdpcmCloseChkFunc(int *handle);
/* as script.h declares it; this TU does not include that header */
extern void scpSleepEnemyOne(int a0);
/* as script.h declares it; this TU does not include that header */
extern void scpWakeupEnemyOne(int a0);
/* as script.h declares it; this TU does not include that header */
extern void scpSleepSpiderGroupOne(int a0);
/* as script.h declares it; this TU does not include that header */
extern void scpWakeupSpiderGroupOne(int a0);
/* as script.h declares it; this TU does not include that header */
extern int scpAdpcmPlayRequestNum(void);
/* as script.h declares it; this TU does not include that header */
extern void scpFadeOut(float a0, int a1, int a2, int a3);
/* as script.h declares it; this TU does not include that header */
extern void scpFadeIn(float f);
/* as script.h declares it; this TU does not include that header */
extern int scpFadeChk(void);
/* kept local: this TU's uses of scpPlayPosSet do not fit the prototype in script.h */
extern void scpPlayPosSet(int a0, float f12, float f13, float f14);
/* as script.h declares it; this TU does not include that header */
extern void scpPlayStart(int a0);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* as script.h declares it; this TU does not include that header */
extern void scpPlayEnd(int a0);
/* kept local: this TU's uses of scpSekizou do not fit the prototype in script.h */
extern void scpSekizou(int a0, int a1, int a2, int a3, int a4, float x1, float y1, float z1,
                       float x2, float y2, float z2);

/* st10l.o's own .rodata run 0x00622DE0..0x00622DF0 (no MAIN.MAP symbol):
   the girl's way-point packet for actSt10lEneCam3Chk. */
/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads, which is what makes gcc
   emit the ld/sd pair the ROM has. */

static const ConstVec eneCam3ChkPos = {{-33.0f, -72.0f, 470.0f, 0.0f}};

/* st10l.o's own .data run (no MAIN.MAP symbols): actor mail packets. */

static ActMail floorMain_mes[2] = {{406, actSt10lFloorSwitch}, {429}};

static ActMail floor_mes[2] = {{430}, {429}};

static ActMail floorSwitchRight_mes[2] = {{430}, {429}};

static ActMail floorSwitchLeft_mes[2] = {{430}, {429}};

static ActMail floorLeft_mes[2] = {{430}, {429}};

static ActMail floorRight_mes[2] = {{430}, {429}};

static ActMail gondolaMain_mes[2] = {{407, actSt10lGondolaSwitch}, {429}};

static ActMail gondola_mes[2] = {{430}, {429}};

static ActMail gondolaSwitchDown_mes[2] = {{430}, {429}};

static ActMail gondolaSwitchUp_mes[2] = {{430}, {429}};

static ActMail gondolaUp_mes[2] = {{430}, {429}};

static ActMail gondolaDown_mes[2] = {{430}, {429}};

static ActMail eneCam1_mes[2] = {{430}, {429}};

static ActMail box_mes[2] = {{430}, {429}};

static ActMail eneCam2_mes[2] = {{430}, {429}};

static ActMail eneCam3_mes[2] = {{430}, {429}};

static ActMail boxA_mes[2] = {{430}, {429}};

static ActMail boxB_mes[2] = {{430}, {429}};

static ActMail chainMain_mes[2] = {{408, actSt10lChainSwitch}, {429}};

static ActMail chain_mes[2] = {{430}, {429}};

static ActMail chainSwitch_mes[2] = {{430}, {429}};

static ActMail eneKill_mes[2] = {{430}, {429}};

void actSt10lInit(void)
{
    if (gflagChk(289) != 0) {
        SetWayGroupActive(22, 1);
        SetWayGroupActive(23, 1);
        stage_SetAnimation(379, 0, 0x59);
    } else {
        SetWayGroupActive(20, 1);
        SetWayGroupActive(21, 1);
        stage_SetAnimation(379, 0, 0);
    }
}

/*SWEEPactSt10lFloorLeft*/
void actSt10lFloorLeft(volatile int a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    if (gflagChk(290) == 0 && D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x3000000) != 0) {
        gflagOn(290);
    }

    if (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x2000000) != 0) {
        scpPlayStart(D_00639EA8);
        scpPlayMot(D_00639EA8, 532);
    }

    if (gflagChk(290) != 0 && D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x3000000) != 0) {
        scpPlayPosSet(D_00639EA8, -167.0f, -72.0f, -705.0f);
        scpPlayStart(D_00639EA8);
        scpPlayMot(D_00639EA8, 532);
    }

    scpAdpcmPlayRequestFunc(91, &floor10l, 1, 1, 1);

    while (floor10l == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(379, 1, 0);

    SetWayGroupActive(20, 0);
    SetWayGroupActive(21, 0);
    SetWayGroupActive(22, 1);
    SetWayGroupActive(23, 1);

    gflagOn(289);

    while (stage_CheckAnimationFrame(379, 89, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (gflagChk(290) != 0) {
        gflagOn(296);
    }

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0xA);

    if (gflagChk(295) == 0) {
        D_0063AA08 = 0;
        lt_switch_layout(54);
        scpWakeupEnemyAll();

        if (D_00639EA8 != 0) {
            scpPlayEnd(D_00639EA8);
        }
    }

    floorLeft_mes[0].func = actSt10lFloorMain;
    sub->mail = floorLeft_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/*SWEEP-ENDactSt10lFloorLeft*/
void actSt10lFloorRight(volatile int a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    if (gflagChk(290) != 0 && D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x3000000) != 0) {
        scpPlayPosSet(D_00639EA8, -196.0f, -72.0f, 62.0f);
        scpPlayStart(D_00639EA8);
        scpPlayMot(D_00639EA8, 532);
    }

    scpAdpcmPlayRequestFunc(91, &floor10l, 1, 1, 1);

    while (floor10l == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(379, 1, 0x5A);

    SetWayGroupActive(20, 1);
    SetWayGroupActive(21, 1);
    SetWayGroupActive(22, 0);
    SetWayGroupActive(23, 0);

    gflagOff(289);

    while (stage_CheckAnimationFrame(379, 180, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0xB);

    D_0063AA08 = 0;
    lt_switch_layout(54);
    scpWakeupEnemyAll();

    if (D_00639EA8 != 0) {
        scpPlayEnd(D_00639EA8);
    }

    floorRight_mes[0].func = actSt10lFloorMain;
    sub->mail = floorRight_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lGondolaUp(volatile int a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    scpAdpcmPlayRequestFunc(88, &st10l_gondola_up, 1, 1, 1);

    while (st10l_gondola_up == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(380, 1, 0);

    while (stage_CheckAnimationFrame(380, 169, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_CheckAnimationFrame(380, 179, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(291);

    if (st10l_gondola_up != 0) {
        scpAdpcmFadeCloseFunc(&st10l_gondola_up, 0x100);
    }

    while (scpAdpcmCloseChkFunc(&st10l_gondola_up) != 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 0;
    scpWakeupEnemyAll();
    lt_switch_layout(54);

    gondolaUp_mes[0].func = actSt10lGondolaMain;
    sub->mail = gondolaUp_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lGondolaDown(volatile int a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    SetGirlDangerGObj(D_00639EA4);

    scpAdpcmPlayRequestFunc(89, &st10l_gondola_down, 1, 1, 1);

    while (st10l_gondola_down == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(380, 1, 0xB4);

    while (stage_CheckAnimationFrame(380, 340, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFrame(380, 360, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOff(291);

    if (st10l_gondola_down != 0) {
        scpAdpcmFadeCloseFunc(&st10l_gondola_down, 0x100);
    }

    while (scpAdpcmCloseChkFunc(&st10l_gondola_down) != 0) {
        _ACTWait(1);
    }

    ClearGirlDangerGObj();

    D_0063AA08 = 0;
    scpWakeupEnemyAll();
    lt_switch_layout(54);

    gondolaDown_mes[0].func = actSt10lGondolaMain;
    sub->mail = gondolaDown_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lEneCam2Chk(volatile int a0)
{
    int save;

    while (D_00639EA8 == 0 || scpTriggerFloorAttr(D_00639EA4, 0x4000000) == 0 ||
           gflagChk(287) == 0 || ((PObjGObjSt10L *)D_00639EA8)->act->f34 == 0x6F) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    D_0063AA08 = 1;

    save = D_0063A538;
    D_0063A538 = 0;

    scpKillEnemyOne(992);
    scpKillEnemyOne(993);
    scpKillSpiderGroup(994);
    scpSleepEnemyOne(3757);
    scpSleepEnemyOne(991);
    scpSleepEnemyOne(1006);
    scpSleepSpiderGroupOne(0x3EF);

    _ACTWait(30);

    gflagOn(294);

    D_0063A538 = save;

    stage_SetAnimation(381, 1, 0);

    while (stage_CheckAnimationFinish(381) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0x3);

    lt_switch_layout(54);
    D_0063AA08 = 0;

    scpWakeupEnemyOne(3757);
    scpWakeupEnemyOne(992);
    scpWakeupEnemyOne(993);
    scpWakeupSpiderGroupOne(0x3E2);
    scpWakeupEnemyOne(991);
    scpWakeupEnemyOne(1006);
    scpWakeupSpiderGroupOne(0x3EF);
}

void actSt10lEneCam3Chk(volatile int a0)
{
    long long buf[2];

    while (gflagChk(296) == 0) {
        _ACTWait(1);
    }

    gflagOn(295);
    FinishHint(14);

    stage_SetAnimation(382, 1, 0);

    buf[0] = eneCam3ChkPos.d[0];
    buf[1] = eneCam3ChkPos.d[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);

    while (stage_CheckAnimationFinish(382) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOff(295);

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0x3);

    lt_switch_layout(54);
    D_0063AA08 = 0;
    scpWakeupEnemyAll();
}

void actSt10lChainMove(volatile int a0)
{
    lt_switch_layout(55);
    scpSleepEnemyAll();

    gflagOn(287);
    FinishHint(13);

    _ACTWait(30);

    scpAdpcmPlayRequestFunc(97, &chain10l, 1, 1, 1);

    while (chain10l == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(384, 1, 0);
    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFrame(384, 240, 0) == 0) {
        if ((D_0028F8F0[0].trg & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            scpFadeOut(16.0f, 0, 0, 0);
            scpAdpcmFadeCloseFunc(&chain10l, 0x200);

            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }

            stage_SetAnimation(384, 1, 0xEF);
            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }

    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(54);

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]);

    stage_SetAnimation(384, 0, 0);

    scpSearchGobj(985)->f16C = 1;
}

void actSt10lChain(volatile int a0)
{
    int x = a0;
    ActSt10L *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(287) == 0) {
        stage_SetAnimation(384, 0, 0);

        scpSearchGobj(985)->f16C = 0;

        chain_mes[0].func = actSt10lChainMain;
        self->mail = chain_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(384, 0, 0);
        FinishHint(13);
    }
}

void actSt10lFloor(volatile int a0)
{
    int x = a0;
    ActSt10L *self = actInitialize(a0);

    _ACTWait(1);

    floor_mes[0].func = actSt10lFloorMain;
    self->mail = floor_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lGondola(volatile int a0)
{
    int x = a0;
    ActSt10L *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(291) != 0) {
        stage_SetAnimation(380, 0, 0);
        _ACTWait(10);
        stage_SetAnimation(380, 0, 0xB3);
    } else {
        stage_SetAnimation(380, 0, 0);
    }

    gondola_mes[0].func = actSt10lGondolaMain;
    self->mail = gondola_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lSekizo(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x120, 0x17F, 0, 0x13, 0.0f, -72.0f, 1274.0f, 76.0f, -72.0f, 1274.0f);
}

void actSt10lBox(volatile int a0)
{
    int x = a0;
    ActSt10L *self = actInitialize(a0);

    _ACTWait(1);

    box_mes[0].func = actSt10lBoxChk;
    self->mail = box_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lEnemy1_1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);
    Generator_Mask((int)scpSearchGobj(997));

    while (gflagChk(293) == 0) {
        _ACTWait(1);
    }
    _ACTWait(116);

    Generator_Call(a0);
    Generator_MaskOff(a0);
    Generator_Call((int)scpSearchGobj(997));
}

void actSt10lEnemy1_2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(293) == 0) {
        _ACTWait(1);
    }
    _ACTWait(100);

    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt10lEnemy2_1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(294) == 0) {
        _ACTWait(1);
    }
    _ACTWait(116);

    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt10lEnemy2_2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(294) == 0) {
        _ACTWait(1);
    }
    _ACTWait(100);

    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt10lEnemy2_3(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(294) == 0) {
        _ACTWait(1);
    }
    _ACTWait(130);

    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt10lEnemy3_1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(295) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt10lEnemy3_2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(295) == 0) {
        _ACTWait(1);
    }
    _ACTWait(320);

    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt10lEneCam1(volatile int a0)
{
    int x = a0;
    ActSt10L *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(293) == 0) {
        eneCam1_mes[0].func = actSt10lEneCam1Chk;
        self->mail = eneCam1_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt10lEneCam2(volatile int a0)
{
    int x = a0;
    ActSt10L *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(294) == 0) {
        eneCam2_mes[0].func = actSt10lEneCam2Chk;
        self->mail = eneCam2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt10lEneCam3(volatile int a0)
{
    int x = a0;
    ActSt10L *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(296) == 0) {
        eneCam3_mes[0].func = actSt10lEneCam3Chk;
        self->mail = eneCam3_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        FinishHint(14);
    }
}

void actSt10lEneKill(volatile int a0)
{
    int x = a0;
    ActSt10L *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(297) == 0) {
        eneKill_mes[0].func = actSt10lEneKillChk;
        self->mail = eneKill_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt10lBoxA(volatile int a0)
{
    int x = a0;
    ActSt10L *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(298) == 0) {
        boxA_mes[0].func = actSt10lBoxAChk;
        self->mail = boxA_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(977)->f16C = 0;
    }
}

void actSt10lBoxB(volatile int a0)
{
    int x = a0;
    ActSt10L *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(299) == 0) {
        boxB_mes[0].func = actSt10lBoxBChk;
        self->mail = boxB_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(978)->f16C = 0;
    }
}

void actSt10lGateXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(174) == 0) {
        scpSearchGobj(971)->f16C = 0;
    } else {
        scpSearchGobj(970)->f16C = 0;
    }
}

void actSt10lFloorMain(volatile int a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    sub->mainMail = floorMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt10lFloorSwitch(volatile int a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    sub->mainMail = 0;
    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    if (gflagChk(289) != 0) {
        floorSwitchRight_mes[0].func = actSt10lFloorRight;
        sub->mail = floorSwitchRight_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }

    floorSwitchLeft_mes[0].func = actSt10lFloorLeft;
    sub->mail = floorSwitchLeft_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lGondolaMain(volatile int a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    sub->mainMail = gondolaMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt10lGondolaSwitch(volatile int a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    sub->mainMail = 0;
    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    if (gflagChk(291) != 0) {
        gondolaSwitchDown_mes[0].func = actSt10lGondolaDown;
        sub->mail = gondolaSwitchDown_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }

    gondolaSwitchUp_mes[0].func = actSt10lGondolaUp;
    sub->mail = gondolaSwitchUp_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lEneCam1Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while ((D_00639EA8 == 0 || gflagChk(292) == 0) &&
           (scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0 ||
            scpTriggerFloorAttr(D_00639EA8, 0x2000000) == 0)) {
        _ACTWait(1);
    }

    gflagOn(293);
}

void actSt10lBoxChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr((int)scpSearchGobj(988), 0x1000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(292);
}

void actSt10lSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt10lBoxAChk(volatile int a0)
{
    while (scpTriggerBall(a0, (int)scpSearchGobj(977), 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(298);
    scpSearchGobj(977)->f16C = 0;
    _ACTWait(30);
    soundSeDefPlay(1270, 0, 0, 1);
}

void actSt10lBoxBChk(volatile int a0)
{
    while (scpTriggerBall(a0, (int)scpSearchGobj(978), 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(299);
    scpSearchGobj(978)->f16C = 0;
    _ACTWait(30);
    soundSeDefPlay(1271, 0, 0, 1);
}

void actSt10lChainMain(volatile int a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    sub->mainMail = chainMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt10lChainSwitch(volatile int a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    sub->mainMail = 0;
    D_0063AA08 = 1;

    chainSwitch_mes[0].func = actSt10lChainMove;
    sub->mail = chainSwitch_mes;
    ACTSendMailCorrect(a0, 430);
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
    _ACTWait(30);

    gflagOn(297);
    scpKillEnemyOne(1000);
    scpKillEnemyOne(1001);
    scpKillSpiderGroup(1002);
    _ACTWait(30);

    D_0063A538 = save;
    _ACTWait(1);
    enable_game_pause = 1;
}
