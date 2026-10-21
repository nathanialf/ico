#include "st03t.h"
#include "debug.h"
#include "layout_texture.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "way_llf.h"
#include "camera-ico2.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "box.h"
#include "motionManager2.h"
#include "typedef.h"
#include "main.h"
#include "script.h"

/* The functions stand in the order of the stage's source (aug6's TRFILE and the
   PAL listing number them so). The ones defined inline are output at
   the end of the file, in the order of the declarations below, which gives
   this build's .text order; the others are output where they stand. The
   tables the actors and the switch checks install are file-scope statics;
   the girl camera and way checks keep theirs as static locals. */

inline void actSt03tGirlCam(GObj *volatile self);
inline void actSt03tSekizo(GObj *volatile self);
inline void actSt03tObj776(GObj *volatile self);
inline void actSt03tWay(GObj *volatile self);
inline void actSt03tEne(GObj *volatile self);
inline void actSt03tGene(GObj *volatile self);
inline void actSt03tGirlCamEvent(int x);
inline void actSt03tGirlCamStartChk(GObj *volatile self);
inline void actSt03tGirlCamEndChk(GObj *volatile self);
inline void actSt03tSekizoEvent(int x);
inline void actSt03tEneChk(GObj *volatile self);
inline void actSt03tWayOnChk(GObj *volatile self);
inline void actSt03tWayOffChk(GObj *volatile self);

static ActMail switchL_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchLUp_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchLChk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchLUpChk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchR_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchRUp_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchRChk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail switchRUpChk_mes[2] = {{377}, {376}}; /* derived name */

void actSt03tSwitchL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(78) == 0) {
        stage_SetAnimation(295, 0, 0);
        stage_SetAnimation(297, 0, 0);

        switchL_mes[0].func = actSt03tSwitchLChk;
        act->mail = switchL_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(295, 0, 45);
        stage_SetAnimation(297, 0, -1);

        switchLUp_mes[0].func = actSt03tSwitchLUpChk;
        act->mail = switchLUp_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt03tSwitchLChk(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);
    int i;

    i = 0;
    while (i < (60 - systemStatus[0] * 10) / systemStatus[1]) {
        if (scpTriggerFloorAttrTargetMan(self, 0x1000000) != 0) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }

    stage_SetAnimation(295, 1, 0);
    soundSeDefPlay(1170, 0, 0, 1);

    while (stage_CheckAnimationFrame(295, 45, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(78);

    stage_SetAnimation(297, 1, 0);

    gflagOn(80);

    while (stage_CheckAnimationFrame(297, 75, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1168, 0, 0, 1);

    while (stage_CheckAnimationFrame(297, 90, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1169, 0, 0, 1);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(297) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    switchLChk_mes[0].func = actSt03tSwitchLUpChk;
    act->mail = switchLChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt03tSwitchLUpChk(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    while (scpTriggerFloorAttrTargetMan(self, 0x1000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(60);

    gflagOff(78);

    stage_SetAnimation(295, 1, 46);
    soundSeDefPlay(1170, 0, 0, 1);

    while (stage_CheckAnimationFrame(295, 90, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(298, 1, 0);

    soundSeDefPlay(1168, 0, 0, 1);
    _ACTWait(30);
    soundSeDefPlay(1169, 0, 0, 1);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(298) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    switchLUpChk_mes[0].func = actSt03tSwitchLChk;
    act->mail = switchLUpChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt03tSwitchR(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(79) == 0) {
        stage_SetAnimation(296, 0, 0);
        stage_SetAnimation(299, 0, 0);

        switchR_mes[0].func = actSt03tSwitchRChk;
        act->mail = switchR_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(296, 0, 45);
        stage_SetAnimation(299, 0, -1);

        switchRUp_mes[0].func = actSt03tSwitchRUpChk;
        act->mail = switchRUp_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt03tSwitchRChk(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);
    int i;

    i = 0;
    while (i < (60 - systemStatus[0] * 10) / systemStatus[1]) {
        if (scpTriggerFloorAttrTargetMan(self, 0x2000000) != 0) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }

    stage_SetAnimation(296, 1, 0);
    soundSeDefPlay(1170, 0, 0, 1);

    while (stage_CheckAnimationFrame(296, 45, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(299, 1, 0);

    SetWayGroupActive(5, 1);

    gflagOn(80);

    soundSeDefPlay(1168, 0, 0, 1);
    _ACTWait(30);
    soundSeDefPlay(1169, 0, 0, 1);

    while (stage_CheckAnimationFinish(299) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(79);

    switchRChk_mes[0].func = actSt03tSwitchRUpChk;
    act->mail = switchRChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt03tSwitchRUpChk(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    while (scpTriggerFloorAttrTargetMan(self, 0x2000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(((60 - systemStatus[0] * 10) / systemStatus[1]) * 10);

    gflagOff(79);

    stage_SetAnimation(296, 1, 46);
    soundSeDefPlay(1170, 0, 0, 1);

    while (stage_CheckAnimationFrame(296, 90, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(300, 1, 0);

    SetWayGroupActive(5, 0);

    soundSeDefPlay(1168, 0, 0, 1);
    _ACTWait(30);
    soundSeDefPlay(1169, 0, 0, 1);

    while (stage_CheckAnimationFinish(300) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    switchRUpChk_mes[0].func = actSt03tSwitchRChk;
    act->mail = switchRUpChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt03tGirlCamEvent(int x)
{
    volatile int local = x;
}

static ActMail girlCam_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt03tGirlCam(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    girlCam_mes[0].func = actSt03tGirlCamStartChk;
    act->mail = girlCam_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt03tGirlCamStartChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail girlCamStartChk_mes[2] = {{377}, {376}}; /* derived name */

    while (scpTriggerBall(self, boyGObj, 100.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) != 207) {
        _ACTWait(1);
    }

    CameraGetTarget();
    Camctrl_SetTarget(girlGObj, 0, 3);
    _ACTWait(15);
    CameraSetCameraSet(48);

    girlCamStartChk_mes[0].func = actSt03tGirlCamEndChk;
    sub->mail = girlCamStartChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt03tGirlCamEndChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail girlCamEndChk_mes[2] = {{377}, {376}}; /* derived name */

    while (scpTriggerBall(self, boyGObj, 100.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 207) {
        _ACTWait(1);
    }

    CameraGetTarget();
    _ACTWait(90);
    CameraSetCameraSet_Default();
    Camctrl_SetTarget(boyGObj, 0, 3);

    girlCamEndChk_mes[0].func = actSt03tGirlCamStartChk;
    sub->mail = girlCamEndChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt03tSekizoEvent(int x)
{
    volatile int local = x;
}

inline void actSt03tSekizo(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    scpSekizou(self, 84, 61, 0, 21, -913.0f, -400.0f, 605.0f, -1000.0f, -400.0f, 550.0f);
}

static ActMail ene_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt03tEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(90) == 0) {
        ene_mes[0].func = actSt03tEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

inline void actSt03tEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x4000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    gflagOn(90);
    gflagOn(91);
    stage_SetAnimation(62, 1, 0);

    while (stage_CheckAnimationFinish(62) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

inline void actSt03tGene(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    Generator_Mask(scpSearchGobj(784));

    while (gflagChk(91) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(20);
    Generator_Call(self);

    Generator_Call(scpSearchGobj(784));
}

/* obj-layout row 776's process: the box flag 262 has dropped stays down */
inline void actSt03tObj776(GObj *volatile self) /* derived name */
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(262) == 0) {
        scpSearchGobj(773)->active = 0;
    } else {
        gflagOn(87);
        scpSearchGobj(771)->active = 0;
        scpSearchGobj(773)->active = 1;
    }
}

void actSt03tBoxB(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(261) == 0) {
        scpSearchGobj(772)->active = 0;
    } else {
        scpSearchGobj(770)->active = 0;
        scpSearchGobj(772)->active = 1;

        if (gflagChk(86) == 0) {
            scpPlayPosSet(scpSearchGobj(772), 600.0f, -150.0f, 675.0f);
            _ACTWait(1);
            ReInitBoxGeo(scpSearchGobj(772));
            gflagOn(86);
        }
    }
}

static ActMail wayOn_mes[2] = {{377}, {376}}; /* derived name */

static ActMail wayOff_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt03tWay(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(88) == 0) {
        wayOn_mes[0].func = actSt03tWayOnChk;
        act->mail = wayOn_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        wayOff_mes[0].func = actSt03tWayOffChk;
        act->mail = wayOff_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

inline void actSt03tWayOnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail wayOnChk_mes[2] = {{377}, {376}}; /* derived name */

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(17, 1);
    gflagOn(88);

    wayOnChk_mes[0].func = actSt03tWayOffChk;
    sub->mail = wayOnChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt03tWayOffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail wayOffChk_mes[2] = {{377}, {376}}; /* derived name */

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(17, 0);
    gflagOff(88);

    wayOffChk_mes[0].func = actSt03tWayOnChk;
    sub->mail = wayOffChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt03tInit(void)
{
    if (gflagChk(80) == 0) {
        SetWayGroupActive(7, 0);
    }

    if (gflagChk(81) != 0) {
        SetWayGroupActive(5, 1);
    } else {
        SetWayGroupActive(5, 0);
    }
}
