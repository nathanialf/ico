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
#include "layout_action.h"
#include "script.h"
#include "main.h"

/* this file's own view of Act (the shared one is in typedef.h) */
typedef struct ActSt10L { /* field names derived */
    char pad0[52];        /* 0x00 */
    int f34;              /* 0x34 */
    char pad38[152];      /* 0x38 */
    ActMail *mainMail;    /* 0xD0 */
    ActMail *mail;        /* 0xD4 */
} ActSt10L;               /* derived name */

/* this file's own view of GObj (the shared one is in typedef.h) */
typedef struct PObjGObjSt10L { /* field names derived */
    char pad00[356];           /* 0x000 */
    ActSt10L *act;             /* 0x164 */
    char pad168[4];            /* 0x168 */
    int f16C;                  /* 0x16C */
} PObjGObjSt10L;               /* derived name */

/* .rodata: the girl's way-point packet for actSt10lEneCam3Chk, a 16-byte
   constant vector template whose long long view the copy reads */

static const ConstVec eneCam3ChkPos = {{-33.0f, -72.0f, 470.0f, 0.0f}}; /* derived name */

/* .data: actor mail packets. */

static ActMail floorMain_mes[2] = {{406, actSt10lFloorSwitch}, {429}}; /* derived name */

static ActMail floor_mes[2] = {{430}, {429}}; /* derived name */

static ActMail floorSwitchRight_mes[2] = {{430}, {429}}; /* derived name */

static ActMail floorSwitchLeft_mes[2] = {{430}, {429}}; /* derived name */

static ActMail floorLeft_mes[2] = {{430}, {429}}; /* derived name */

static ActMail floorRight_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaMain_mes[2] = {{407, actSt10lGondolaSwitch}, {429}}; /* derived name */

static ActMail gondola_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaSwitchDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaSwitchUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail eneCam1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail box_mes[2] = {{430}, {429}}; /* derived name */

static ActMail eneCam2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail eneCam3_mes[2] = {{430}, {429}}; /* derived name */

static ActMail boxA_mes[2] = {{430}, {429}}; /* derived name */

static ActMail boxB_mes[2] = {{430}, {429}}; /* derived name */

static ActMail chainMain_mes[2] = {{408, actSt10lChainSwitch}, {429}}; /* derived name */

static ActMail chain_mes[2] = {{430}, {429}}; /* derived name */

static ActMail chainSwitch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail eneKill_mes[2] = {{430}, {429}}; /* derived name */

/* .sdata: the floor, gondola and chain stream handles. */
char *floor10l = 0;

char *st10l_gondola_up = 0;

char *st10l_gondola_down = 0;

char *chain10l = 0;

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

void actSt10lFloorLeft(GObj *volatile a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    if (gflagChk(290) == 0 && girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        gflagOn(290);
    }

    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x2000000) != 0) {
        scpPlayStart(girlGObj);
        scpPlayMot(girlGObj, 532);
    }

    if (gflagChk(290) != 0 && girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        scpPlayPosSet(girlGObj, -167.0f, -72.0f, -705.0f);
        scpPlayStart(girlGObj);
        scpPlayMot(girlGObj, 532);
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

    _ACTWait((0x3C - systemStatus[0] * 0xA) / systemStatus[1] * 0xA);

    if (gflagChk(295) == 0) {
        scpBoyControlReadDisable = 0;
        lt_switch_layout(54);
        scpWakeupEnemyAll();

        if (girlGObj != 0) {
            scpPlayEnd(girlGObj);
        }
    }

    floorLeft_mes[0].func = actSt10lFloorMain;
    sub->mail = floorLeft_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lFloorRight(GObj *volatile a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    if (gflagChk(290) != 0 && girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        scpPlayPosSet(girlGObj, -196.0f, -72.0f, 62.0f);
        scpPlayStart(girlGObj);
        scpPlayMot(girlGObj, 532);
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

    _ACTWait((0x3C - systemStatus[0] * 0xA) / systemStatus[1] * 0xB);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(54);
    scpWakeupEnemyAll();

    if (girlGObj != 0) {
        scpPlayEnd(girlGObj);
    }

    floorRight_mes[0].func = actSt10lFloorMain;
    sub->mail = floorRight_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lGondolaUp(GObj *volatile a0)
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

    iosPadActRequest(boyPad, 0x10);

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

    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
    lt_switch_layout(54);

    gondolaUp_mes[0].func = actSt10lGondolaMain;
    sub->mail = gondolaUp_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lGondolaDown(GObj *volatile a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    SetGirlDangerGObj(boyGObj);

    scpAdpcmPlayRequestFunc(89, &st10l_gondola_down, 1, 1, 1);

    while (st10l_gondola_down == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(380, 1, 0xB4);

    while (stage_CheckAnimationFrame(380, 340, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 0x11);

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

    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
    lt_switch_layout(54);

    gondolaDown_mes[0].func = actSt10lGondolaMain;
    sub->mail = gondolaDown_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lEneCam2Chk(GObj *volatile a0)
{
    int save;

    while (girlGObj == 0 || scpTriggerFloorAttr(boyGObj, 0x4000000) == 0 || gflagChk(287) == 0 ||
           ((PObjGObjSt10L *)girlGObj)->act->f34 == 0x6F) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    scpBoyControlReadDisable = 1;

    save = iosPadActRequestEnable;
    iosPadActRequestEnable = 0;

    scpKillEnemyOne(992);
    scpKillEnemyOne(993);
    scpKillSpiderGroup(994);
    scpSleepEnemyOne(3757);
    scpSleepEnemyOne(991);
    scpSleepEnemyOne(1006);
    scpSleepSpiderGroupOne(0x3EF);

    _ACTWait(30);

    gflagOn(294);

    iosPadActRequestEnable = save;

    stage_SetAnimation(381, 1, 0);

    while (stage_CheckAnimationFinish(381) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait((0x3C - systemStatus[0] * 0xA) / systemStatus[1] * 0x3);

    lt_switch_layout(54);
    scpBoyControlReadDisable = 0;

    scpWakeupEnemyOne(3757);
    scpWakeupEnemyOne(992);
    scpWakeupEnemyOne(993);
    scpWakeupSpiderGroupOne(0x3E2);
    scpWakeupEnemyOne(991);
    scpWakeupEnemyOne(1006);
    scpWakeupSpiderGroupOne(0x3EF);
}

void actSt10lEneCam3Chk(GObj *volatile a0)
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
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);

    while (stage_CheckAnimationFinish(382) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOff(295);

    _ACTWait((0x3C - systemStatus[0] * 0xA) / systemStatus[1] * 0x3);

    lt_switch_layout(54);
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
}

void actSt10lChainMove(GObj *volatile a0)
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
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
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
    scpBoyControlReadDisable = 0;
    lt_switch_layout(54);

    _ACTWait((0x3C - systemStatus[0] * 0xA) / systemStatus[1]);

    stage_SetAnimation(384, 0, 0);

    scpSearchGobj(985)->active = 1;
}

void actSt10lChain(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(287) == 0) {
        stage_SetAnimation(384, 0, 0);

        scpSearchGobj(985)->active = 0;

        chain_mes[0].func = actSt10lChainMain;
        self->mail = chain_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(384, 0, 0);
        FinishHint(13);
    }
}

void actSt10lFloor(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    floor_mes[0].func = actSt10lFloorMain;
    self->mail = floor_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lGondola(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

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

void actSt10lSekizo(GObj *volatile a0)
{
    GObj *x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x120, 0x17F, 0, 0x13, 0.0f, -72.0f, 1274.0f, 76.0f, -72.0f, 1274.0f);
}

void actSt10lBox(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    box_mes[0].func = actSt10lBoxChk;
    self->mail = box_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lEnemy1_1(GObj *volatile a0)
{
    GObj *x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);
    Generator_Mask(scpSearchGobj(997));

    while (gflagChk(293) == 0) {
        _ACTWait(1);
    }
    _ACTWait(116);

    Generator_Call(a0);
    Generator_MaskOff(a0);
    Generator_Call(scpSearchGobj(997));
}

void actSt10lEnemy1_2(GObj *volatile a0)
{
    GObj *x = a0;

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

void actSt10lEnemy2_1(GObj *volatile a0)
{
    GObj *x = a0;

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

void actSt10lEnemy2_2(GObj *volatile a0)
{
    GObj *x = a0;

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

void actSt10lEnemy2_3(GObj *volatile a0)
{
    GObj *x = a0;

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

void actSt10lEnemy3_1(GObj *volatile a0)
{
    GObj *x = a0;

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

void actSt10lEnemy3_2(GObj *volatile a0)
{
    GObj *x = a0;

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

void actSt10lEneCam1(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(293) == 0) {
        eneCam1_mes[0].func = actSt10lEneCam1Chk;
        self->mail = eneCam1_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt10lEneCam2(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(294) == 0) {
        eneCam2_mes[0].func = actSt10lEneCam2Chk;
        self->mail = eneCam2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt10lEneCam3(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

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

void actSt10lEneKill(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(297) == 0) {
        eneKill_mes[0].func = actSt10lEneKillChk;
        self->mail = eneKill_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt10lBoxA(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(298) == 0) {
        boxA_mes[0].func = actSt10lBoxAChk;
        self->mail = boxA_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(977)->active = 0;
    }
}

void actSt10lBoxB(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(299) == 0) {
        boxB_mes[0].func = actSt10lBoxBChk;
        self->mail = boxB_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(978)->active = 0;
    }
}

void actSt10lGateXL(GObj *volatile a0)
{
    GObj *x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(174) == 0) {
        scpSearchGobj(971)->active = 0;
    } else {
        scpSearchGobj(970)->active = 0;
    }
}

void actSt10lFloorMain(GObj *volatile a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    sub->mainMail = floorMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt10lFloorSwitch(GObj *volatile a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    sub->mainMail = 0;
    lt_switch_layout(55);
    scpBoyControlReadDisable = 1;
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

void actSt10lGondolaMain(GObj *volatile a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    sub->mainMail = gondolaMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt10lGondolaSwitch(GObj *volatile a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    sub->mainMail = 0;
    lt_switch_layout(55);
    scpBoyControlReadDisable = 1;
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

void actSt10lEneCam1Chk(GObj *volatile a0)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while ((girlGObj == 0 || gflagChk(292) == 0) &&
           (scpTriggerFloorAttr(boyGObj, 0x2000000) == 0 ||
            scpTriggerFloorAttr(girlGObj, 0x2000000) == 0)) {
        _ACTWait(1);
    }

    gflagOn(293);
}

void actSt10lBoxChk(GObj *volatile a0)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(scpSearchGobj(988), 0x1000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(292);
}

void actSt10lSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt10lBoxAChk(GObj *volatile a0)
{
    while (scpTriggerBall(a0, scpSearchGobj(977), 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(298);
    scpSearchGobj(977)->active = 0;
    _ACTWait(30);
    soundSeDefPlay(1270, 0, 0, 1);
}

void actSt10lBoxBChk(GObj *volatile a0)
{
    while (scpTriggerBall(a0, scpSearchGobj(978), 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(299);
    scpSearchGobj(978)->active = 0;
    _ACTWait(30);
    soundSeDefPlay(1271, 0, 0, 1);
}

void actSt10lChainMain(GObj *volatile a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    sub->mainMail = chainMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt10lChainSwitch(GObj *volatile a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    sub->mainMail = 0;
    scpBoyControlReadDisable = 1;

    chainSwitch_mes[0].func = actSt10lChainMove;
    sub->mail = chainSwitch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lEneKillChk(GObj *volatile a0)
{
    int save;

    while (scpTriggerBall(a0, boyGObj, 500.0f) == 0) {
        _ACTWait(1);
    }

    enable_game_pause = 0;
    _ACTWait(1);

    save = iosPadActRequestEnable;
    iosPadActRequestEnable = 0;
    _ACTWait(30);

    gflagOn(297);
    scpKillEnemyOne(1000);
    scpKillEnemyOne(1001);
    scpKillSpiderGroup(1002);
    _ACTWait(30);

    iosPadActRequestEnable = save;
    _ACTWait(1);
    enable_game_pause = 1;
}
