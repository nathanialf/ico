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

static void actSt10lEneKillChk(GObj *volatile self);

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
SqEntry *floor10l = 0;

SqEntry *st10l_gondola_up = 0;

SqEntry *st10l_gondola_down = 0;

SqEntry *chain10l = 0;

void actSt10lInit(void)
{
    if (gflagChk(289) != 0) {
        SetWayGroupActive(22, 1);
        SetWayGroupActive(23, 1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(375, 0, 89);
#else
        stage_SetAnimation(379, 0, 89);
#endif
    } else {
        SetWayGroupActive(20, 1);
        SetWayGroupActive(21, 1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(375, 0, 0);
#else
        stage_SetAnimation(379, 0, 0);
#endif
    }
}

void actSt10lFloorLeft(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

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

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(375, 1, 0);
#else
    stage_SetAnimation(379, 1, 0);
#endif

    SetWayGroupActive(20, 0);
    SetWayGroupActive(21, 0);
    SetWayGroupActive(22, 1);
    SetWayGroupActive(23, 1);

    gflagOn(289);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(375, 89, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(379, 89, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    if (gflagChk(290) != 0) {
        gflagOn(296);
    }

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 10);

    if (gflagChk(295) == 0) {
        scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        lt_switch_layout(51);
#else
        lt_switch_layout(54);
#endif
        scpWakeupEnemyAll();

        if (girlGObj != 0) {
            scpPlayEnd(girlGObj);
        }
    }

    floorLeft_mes[0].func = actSt10lFloorMain;
    sub->mail = floorLeft_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt10lFloorRight(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (gflagChk(290) != 0 && girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        scpPlayPosSet(girlGObj, -196.0f, -72.0f, 62.0f);
        scpPlayStart(girlGObj);
        scpPlayMot(girlGObj, 532);
    }

    scpAdpcmPlayRequestFunc(91, &floor10l, 1, 1, 1);

    while (floor10l == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(375, 1, 90);
#else
    stage_SetAnimation(379, 1, 90);
#endif

    SetWayGroupActive(20, 1);
    SetWayGroupActive(21, 1);
    SetWayGroupActive(22, 0);
    SetWayGroupActive(23, 0);

    gflagOff(289);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(375, 180, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(379, 180, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 11);

    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    scpWakeupEnemyAll();

    if (girlGObj != 0) {
        scpPlayEnd(girlGObj);
    }

    floorRight_mes[0].func = actSt10lFloorMain;
    sub->mail = floorRight_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt10lGondolaUp(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpAdpcmPlayRequestFunc(88, &st10l_gondola_up, 1, 1, 1);

    while (st10l_gondola_up == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(376, 1, 0);
#else
    stage_SetAnimation(380, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(376, 169, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(380, 169, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(376, 179, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(380, 179, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(291);

    if (st10l_gondola_up != 0) {
        scpAdpcmFadeCloseFunc(&st10l_gondola_up, 256);
    }

    while (scpAdpcmCloseChkFunc(&st10l_gondola_up) != 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif

    gondolaUp_mes[0].func = actSt10lGondolaMain;
    sub->mail = gondolaUp_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt10lGondolaDown(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    SetGirlDangerGObj(boyGObj);

    scpAdpcmPlayRequestFunc(89, &st10l_gondola_down, 1, 1, 1);

    while (st10l_gondola_down == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(376, 1, 180);
#else
    stage_SetAnimation(380, 1, 180);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(376, 340, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(380, 340, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(376, 360, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(380, 360, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOff(291);

    if (st10l_gondola_down != 0) {
        scpAdpcmFadeCloseFunc(&st10l_gondola_down, 256);
    }

    while (scpAdpcmCloseChkFunc(&st10l_gondola_down) != 0) {
        _ACTWait(1);
    }

    ClearGirlDangerGObj();

    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif

    gondolaDown_mes[0].func = actSt10lGondolaMain;
    sub->mail = gondolaDown_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt10lEneCam2Chk(GObj *volatile self)
{
    int save;

    while (girlGObj == 0 || scpTriggerFloorAttr(boyGObj, 0x4000000) == 0 || gflagChk(287) == 0 ||
           GOBJ_ACT(girlGObj)->actMode == 111) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;

    save = iosPadActRequestEnable;
    iosPadActRequestEnable = 0;

    scpKillEnemyOne(992);
    scpKillEnemyOne(993);
    scpKillSpiderGroup(994);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpSleepEnemyOne(3734);
#else
    scpSleepEnemyOne(3757);
#endif
    scpSleepEnemyOne(991);
    scpSleepEnemyOne(1006);
    scpSleepSpiderGroupOne(1007);

    _ACTWait(30);

    gflagOn(294);

    iosPadActRequestEnable = save;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(377, 1, 0);
#else
    stage_SetAnimation(381, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(377) == 0) {
#else
    while (stage_CheckAnimationFinish(381) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 3);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    scpBoyControlReadDisable = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpWakeupEnemyOne(3734);
#else
    scpWakeupEnemyOne(3757);
#endif
    scpWakeupEnemyOne(992);
    scpWakeupEnemyOne(993);
    scpWakeupSpiderGroupOne(994);
    scpWakeupEnemyOne(991);
    scpWakeupEnemyOne(1006);
    scpWakeupSpiderGroupOne(1007);
}

void actSt10lEneCam3Chk(GObj *volatile self)
{
    long long buf[2];

    while (gflagChk(296) == 0) {
        _ACTWait(1);
    }

    gflagOn(295);
    FinishHint(14);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(378, 1, 0);
#else
    stage_SetAnimation(382, 1, 0);
#endif

    buf[0] = eneCam3ChkPos.d[0];
    buf[1] = eneCam3ChkPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(378) == 0) {
#else
    while (stage_CheckAnimationFinish(382) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOff(295);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 3);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
}

void actSt10lChainMove(GObj *volatile self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpSleepEnemyAll();

    gflagOn(287);
    FinishHint(13);

    _ACTWait(30);

    scpAdpcmPlayRequestFunc(97, &chain10l, 1, 1, 1);

    while (chain10l == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(380, 1, 0);
#else
    stage_SetAnimation(384, 1, 0);
#endif
    SetCameraFlag_LwsCutBack();

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(380, 240, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(384, 240, 0) == 0) {
#endif
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            scpFadeOut(16.0f, 0, 0, 0);
            scpAdpcmFadeCloseFunc(&chain10l, 512);

            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(380, 1, 239);
#else
            stage_SetAnimation(384, 1, 239);
#endif
            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1]);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(380, 0, 0);
#else
    stage_SetAnimation(384, 0, 0);
#endif

    scpSearchGobj(985)->active = 1;
}

void actSt10lChain(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(287) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(380, 0, 0);
#else
        stage_SetAnimation(384, 0, 0);
#endif

        scpSearchGobj(985)->active = 0;

        chain_mes[0].func = actSt10lChainMain;
        act->mail = chain_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(380, 0, 0);
#else
        stage_SetAnimation(384, 0, 0);
#endif
        FinishHint(13);
    }
}

void actSt10lFloor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    floor_mes[0].func = actSt10lFloorMain;
    act->mail = floor_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt10lGondola(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(291) != 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(376, 0, 0);
#else
        stage_SetAnimation(380, 0, 0);
#endif
        _ACTWait(10);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(376, 0, 179);
#else
        stage_SetAnimation(380, 0, 179);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(376, 0, 0);
#else
        stage_SetAnimation(380, 0, 0);
#endif
    }

    gondola_mes[0].func = actSt10lGondolaMain;
    act->mail = gondola_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt10lSekizo(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpSekizou(self, 288, 379, 0, 19, 0.0f, -72.0f, 1274.0f, 76.0f, -72.0f, 1274.0f);
#else
    scpSekizou(self, 288, 383, 0, 19, 0.0f, -72.0f, 1274.0f, 76.0f, -72.0f, 1274.0f);
#endif
}

void actSt10lBox(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    box_mes[0].func = actSt10lBoxChk;
    act->mail = box_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt10lEnemy1_1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);
    Generator_Mask(scpSearchGobj(997));

    while (gflagChk(293) == 0) {
        _ACTWait(1);
    }
    _ACTWait(116);

    Generator_Call(self);
    Generator_MaskOff(self);
    Generator_Call(scpSearchGobj(997));
}

void actSt10lEnemy1_2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(293) == 0) {
        _ACTWait(1);
    }
    _ACTWait(100);

    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt10lEnemy2_1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(294) == 0) {
        _ACTWait(1);
    }
    _ACTWait(116);

    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt10lEnemy2_2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(294) == 0) {
        _ACTWait(1);
    }
    _ACTWait(100);

    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt10lEnemy2_3(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(294) == 0) {
        _ACTWait(1);
    }
    _ACTWait(130);

    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt10lEnemy3_1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(295) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt10lEnemy3_2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(295) == 0) {
        _ACTWait(1);
    }
    _ACTWait(320);

    Generator_Call(self);
    Generator_MaskOff(self);
}

void actSt10lEneCam1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(293) == 0) {
        eneCam1_mes[0].func = actSt10lEneCam1Chk;
        act->mail = eneCam1_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt10lEneCam2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(294) == 0) {
        eneCam2_mes[0].func = actSt10lEneCam2Chk;
        act->mail = eneCam2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt10lEneCam3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(296) == 0) {
        eneCam3_mes[0].func = actSt10lEneCam3Chk;
        act->mail = eneCam3_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        FinishHint(14);
    }
}

void actSt10lEneKill(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(297) == 0) {
        eneKill_mes[0].func = actSt10lEneKillChk;
        act->mail = eneKill_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt10lBoxA(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(298) == 0) {
        boxA_mes[0].func = actSt10lBoxAChk;
        act->mail = boxA_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(977)->active = 0;
    }
}

void actSt10lBoxB(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(299) == 0) {
        boxB_mes[0].func = actSt10lBoxBChk;
        act->mail = boxB_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(978)->active = 0;
    }
}

void actSt10lGateXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(174) == 0) {
        scpSearchGobj(971)->active = 0;
    } else {
        scpSearchGobj(970)->active = 0;
    }
}

void actSt10lFloorMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = floorMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt10lFloorSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    if (gflagChk(289) != 0) {
        floorSwitchRight_mes[0].func = actSt10lFloorRight;
        sub->mail = floorSwitchRight_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }

    floorSwitchLeft_mes[0].func = actSt10lFloorLeft;
    sub->mail = floorSwitchLeft_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt10lGondolaMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = gondolaMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt10lGondolaSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    if (gflagChk(291) != 0) {
        gondolaSwitchDown_mes[0].func = actSt10lGondolaDown;
        sub->mail = gondolaSwitchDown_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }

    gondolaSwitchUp_mes[0].func = actSt10lGondolaUp;
    sub->mail = gondolaSwitchUp_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt10lEneCam1Chk(GObj *volatile self)
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

void actSt10lBoxChk(GObj *volatile self)
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

void actSt10lBoxAChk(GObj *volatile self)
{
    while (scpTriggerBall(self, scpSearchGobj(977), 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(298);
    scpSearchGobj(977)->active = 0;
    _ACTWait(30);
    soundSeDefPlay(1270, 0, 0, 1);
}

void actSt10lBoxBChk(GObj *volatile self)
{
    while (scpTriggerBall(self, scpSearchGobj(978), 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(299);
    scpSearchGobj(978)->active = 0;
    _ACTWait(30);
    soundSeDefPlay(1271, 0, 0, 1);
}

void actSt10lChainMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = chainMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt10lChainSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    scpBoyControlReadDisable = 1;

    chainSwitch_mes[0].func = actSt10lChainMove;
    sub->mail = chainSwitch_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

static void actSt10lEneKillChk(GObj *volatile self)
{
    int save;

    while (scpTriggerBall(self, boyGObj, 500.0f) == 0) {
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
