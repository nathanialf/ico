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

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
/* The functions stand in the order of the stage's source (aug6's TRFILE and the
   PAL listing number them so). The ones defined inline are output at
   the end of the file, in the order of the declarations below, which gives
   this build's .text order; the others are output where they stand. The
   mail tables are file-scope statics, except girlCamEndChk_mes, a static
   local of its poster: .data keeps the source order and the table takes
   gcc's local name.N symbol. */

inline void actSt03tGirlCam(GObj *volatile self);
inline void actSt03tSekizo(GObj *volatile self);
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

#ifdef VERSION_AUG6
static ActMail switchL_mes[2] = {{393}, {392}}; /* derived name */

static ActMail switchLUp_mes[2] = {{393}, {392}}; /* derived name */

static ActMail switchLChk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail switchLUpChk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail switchR_mes[2] = {{393}, {392}}; /* derived name */

static ActMail switchRUp_mes[2] = {{393}, {392}}; /* derived name */

static ActMail switchRChk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail switchRUpChk_mes[2] = {{393}, {392}}; /* derived name */
#else
static ActMail switchL_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchLUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchLChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchLUpChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchR_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchRUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchRChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail switchRUpChk_mes[2] = {{397}, {396}}; /* derived name */
#endif

void actSt03tSwitchL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(80) == 0) {
#ifdef VERSION_AUG6
        stage_SetAnimation(328, 0, 0);
        stage_SetAnimation(330, 0, 0);
#else
        stage_SetAnimation(329, 0, 0);
        stage_SetAnimation(331, 0, 0);
#endif

        switchL_mes[0].func = actSt03tSwitchLChk;
        act->mail = switchL_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(328, 0, 45);
        stage_SetAnimation(330, 0, -1);
#else
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(329, 0, 45);
        stage_SetAnimation(331, 0, -1);
#endif

        switchLUp_mes[0].func = actSt03tSwitchLUpChk;
        act->mail = switchLUp_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 397);
#endif
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

#ifdef VERSION_AUG6
    stage_SetAnimation(328, 1, 0);
    soundSeDefPlay(1196, 0, 0, 1);

    while (stage_CheckAnimationFrame(328, 45, 1) == 0) {
#else
    stage_SetAnimation(329, 1, 0);
    soundSeDefPlay(1196, 0, 0, 1);

    while (stage_CheckAnimationFrame(329, 45, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(80);

#ifdef VERSION_AUG6
    stage_SetAnimation(330, 1, 0);
#else
    stage_SetAnimation(331, 1, 0);

    SetWayGroupActive(7, 1);
#endif

    gflagOn(82);

#ifdef VERSION_AUG6
    while (stage_CheckAnimationFrame(330, 75, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(331, 75, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1194, 0, 0, 1);

#ifdef VERSION_AUG6
    while (stage_CheckAnimationFrame(330, 90, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(331, 90, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1195, 0, 0, 1);

    SetCameraFlag_LwsCutBack();

#ifdef VERSION_AUG6
    while (stage_CheckAnimationFinish(330) == 0) {
#else
    while (stage_CheckAnimationFinish(331) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    switchLChk_mes[0].func = actSt03tSwitchLUpChk;
    act->mail = switchLChk_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 397);
#endif
    _ACTWait(0);
}

void actSt03tSwitchLUpChk(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    while (scpTriggerFloorAttrTargetMan(self, 0x1000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(60);

    gflagOff(80);

#ifdef VERSION_AUG6
    stage_SetAnimation(328, 1, 46);
    soundSeDefPlay(1196, 0, 0, 1);

    while (stage_CheckAnimationFrame(328, 90, 1) == 0) {
#else
    stage_SetAnimation(329, 1, 46);
    soundSeDefPlay(1196, 0, 0, 1);

    while (stage_CheckAnimationFrame(329, 90, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#ifdef VERSION_AUG6
    stage_SetAnimation(331, 1, 0);
#else
    stage_SetAnimation(332, 1, 0);

    SetWayGroupActive(7, 0);
#endif

    soundSeDefPlay(1194, 0, 0, 1);
    _ACTWait(30);
    soundSeDefPlay(1195, 0, 0, 1);

    SetCameraFlag_LwsCutBack();

#ifdef VERSION_AUG6
    while (stage_CheckAnimationFrame(331, 120, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(332, 120, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    switchLUpChk_mes[0].func = actSt03tSwitchLChk;
    act->mail = switchLUpChk_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 397);
#endif
    _ACTWait(0);
}

void actSt03tSwitchR(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(81) == 0) {
#ifdef VERSION_AUG6
        stage_SetAnimation(329, 0, 0);
        stage_SetAnimation(332, 0, 0);
#else
        stage_SetAnimation(330, 0, 0);
        stage_SetAnimation(333, 0, 0);
#endif

        switchR_mes[0].func = actSt03tSwitchRChk;
        act->mail = switchR_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(329, 0, 45);
        stage_SetAnimation(332, 0, -1);
#else
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(330, 0, 45);
        stage_SetAnimation(333, 0, -1);
#endif

        switchRUp_mes[0].func = actSt03tSwitchRUpChk;
        act->mail = switchRUp_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 397);
#endif
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

#ifdef VERSION_AUG6
    stage_SetAnimation(329, 1, 0);
    soundSeDefPlay(1196, 0, 0, 1);

    while (stage_CheckAnimationFrame(329, 45, 1) == 0) {
#else
    stage_SetAnimation(330, 1, 0);
    soundSeDefPlay(1196, 0, 0, 1);

    while (stage_CheckAnimationFrame(330, 45, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#ifdef VERSION_AUG6
    stage_SetAnimation(332, 1, 0);
#else
    stage_SetAnimation(333, 1, 0);
#endif

    SetWayGroupActive(5, 1);

    gflagOn(82);

    soundSeDefPlay(1194, 0, 0, 1);
    _ACTWait(30);
    soundSeDefPlay(1195, 0, 0, 1);

#ifdef VERSION_AUG6
    while (stage_CheckAnimationFinish(332) == 0) {
#else
    while (stage_CheckAnimationFinish(333) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(81);

    switchRChk_mes[0].func = actSt03tSwitchRUpChk;
    act->mail = switchRChk_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 397);
#endif
    _ACTWait(0);
}

void actSt03tSwitchRUpChk(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    while (scpTriggerFloorAttrTargetMan(self, 0x2000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(((60 - systemStatus[0] * 10) / systemStatus[1]) * 10);

    gflagOff(81);

#ifdef VERSION_AUG6
    stage_SetAnimation(329, 1, 46);
    soundSeDefPlay(1196, 0, 0, 1);

    while (stage_CheckAnimationFrame(329, 90, 1) == 0) {
#else
    stage_SetAnimation(330, 1, 46);
    soundSeDefPlay(1196, 0, 0, 1);

    while (stage_CheckAnimationFrame(330, 90, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#ifdef VERSION_AUG6
    stage_SetAnimation(333, 1, 0);
#else
    stage_SetAnimation(334, 1, 0);
#endif

    SetWayGroupActive(5, 0);

    soundSeDefPlay(1194, 0, 0, 1);
    _ACTWait(30);
    soundSeDefPlay(1195, 0, 0, 1);

#ifdef VERSION_AUG6
    while (stage_CheckAnimationFinish(333) == 0) {
#else
    while (stage_CheckAnimationFinish(334) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    switchRUpChk_mes[0].func = actSt03tSwitchRChk;
    act->mail = switchRUpChk_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 397);
#endif
    _ACTWait(0);
}

inline void actSt03tGirlCamEvent(int x)
{
    volatile int local = x;
}

#ifdef VERSION_AUG6
static ActMail girlCam_mes[2] = {{393}, {392}}; /* derived name */
#else
static ActMail girlCam_mes[2] = {{397}, {396}}; /* derived name */

static ActMail girlCamStartChk_mes[2] = {{397}, {396}}; /* derived name */
#endif

inline void actSt03tGirlCam(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    girlCam_mes[0].func = actSt03tGirlCamStartChk;
    act->mail = girlCam_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 397);
#endif
    _ACTWait(0);
}

inline void actSt03tGirlCamStartChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
#ifdef VERSION_AUG6
    static ActMail girlCamStartChk_mes[2] = {{393}, {392}}; /* derived name */
#endif

    while (scpTriggerBall(self, boyGObj, 100.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) != 198) {
        _ACTWait(1);
    }

    CameraGetTarget();
    Camctrl_SetTarget(girlGObj, 0, 3);
    _ACTWait(15);
    CameraSetCameraSet(48);

    girlCamStartChk_mes[0].func = actSt03tGirlCamEndChk;
    sub->mail = girlCamStartChk_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 397);
#endif
    _ACTWait(0);
}

inline void actSt03tGirlCamEndChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
#ifdef VERSION_AUG6
    static ActMail girlCamEndChk_mes[2] = {{393}, {392}}; /* derived name */
#else
    static ActMail girlCamEndChk_mes[2] = {{397}, {396}}; /* derived name */
#endif

    while (scpTriggerBall(self, boyGObj, 100.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 198) {
        _ACTWait(1);
    }

    CameraGetTarget();
    _ACTWait(90);
    CameraSetCameraSet_Default();
    Camctrl_SetTarget(boyGObj, 0, 3);

    girlCamEndChk_mes[0].func = actSt03tGirlCamStartChk;
    sub->mail = girlCamEndChk_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 397);
#endif
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

    scpSekizou(self, 86, 67, 0, 18, -913.0f, -400.0f, 605.0f, -1000.0f, -400.0f, 550.0f);
}

#ifdef VERSION_AUG6
static ActMail ene_mes[2] = {{393}, {392}}; /* derived name */
#else
static ActMail ene_mes[2] = {{397}, {396}}; /* derived name */
#endif

inline void actSt03tEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(93) == 0) {
        ene_mes[0].func = actSt03tEneChk;
        act->mail = ene_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 397);
#endif
        _ACTWait(0);
    }
}

#ifdef VERSION_AUG6
inline void actSt03tEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerBall(self, boyGObj, 100.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyOne(3415);
    gflagOn(93);
    gflagOn(94);
    stage_SetAnimation(68, 1, 0);

    while (stage_CheckAnimationFinish(68) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyOne(3415);
}

inline void actSt03tGene(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    Generator_Mask(scpSearchGobj(817));

    while (gflagChk(94) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(20);
    Generator_Call(self);

    Generator_Call(scpSearchGobj(817));
}

void actSt03tBoxA(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(271) == 0) {
        scpSearchGobj(805)->active = 0;
    } else {
        scpSearchGobj(792)->active = 0;
        scpSearchGobj(803)->active = 0;
        scpSearchGobj(805)->active = 1;

        scpTransGObj(scpSearchGobj(805), 0.0f, -200.0f, 0.0f);
        _ACTWait(1);
        ReInitBoxGeo(scpSearchGobj(805));
    }
}

void actSt03tBoxB(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(272) == 0) {
        scpSearchGobj(806)->active = 0;
    } else {
        scpSearchGobj(793)->active = 0;
        scpSearchGobj(804)->active = 0;
        scpSearchGobj(806)->active = 1;

        gflagOn(89);

        scpTransGObj(scpSearchGobj(806), 0.0f, -400.0f, 0.0f);
        _ACTWait(1);
        ReInitBoxGeo(scpSearchGobj(806));
    }
}
#else
inline void actSt03tEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerBall(self, boyGObj, 100.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyOne(3453);
    gflagOn(93);
    gflagOn(94);
    stage_SetAnimation(68, 1, 0);

    while (stage_CheckAnimationFinish(68) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyOne(3453);
}

inline void actSt03tGene(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    Generator_Mask(scpSearchGobj(818));

    while (gflagChk(94) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(20);
    Generator_Call(self);

    Generator_Call(scpSearchGobj(818));
}

void actSt03tBoxA(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(272) == 0) {
        scpSearchGobj(806)->active = 0;
    } else {
        scpSearchGobj(793)->active = 0;
        scpSearchGobj(804)->active = 0;
        scpSearchGobj(806)->active = 1;

        scpTransGObj(scpSearchGobj(806), 0.0f, -200.0f, 0.0f);
        _ACTWait(1);
        ReInitBoxGeo(scpSearchGobj(806));
    }
}
#endif

#ifdef VERSION_AUG6
static ActMail wayOn_mes[2] = {{393}, {392}}; /* derived name */

static ActMail wayOff_mes[2] = {{393}, {392}}; /* derived name */
#else
void actSt03tBoxB(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(273) == 0) {
        scpSearchGobj(807)->active = 0;
    } else {
        scpSearchGobj(794)->active = 0;
        scpSearchGobj(805)->active = 0;
        scpSearchGobj(807)->active = 1;

        gflagOn(89);

        scpTransGObj(scpSearchGobj(807), 0.0f, -400.0f, 0.0f);
        _ACTWait(1);
        ReInitBoxGeo(scpSearchGobj(807));
    }
}

static ActMail wayOn_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wayOff_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wayOnChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wayOffChk_mes[2] = {{397}, {396}}; /* derived name */
#endif

inline void actSt03tWay(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(91) == 0) {
        wayOn_mes[0].func = actSt03tWayOnChk;
        act->mail = wayOn_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 397);
#endif
        _ACTWait(0);
    } else {
        wayOff_mes[0].func = actSt03tWayOffChk;
        act->mail = wayOff_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 397);
#endif
        _ACTWait(0);
    }
}

inline void actSt03tWayOnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
#ifdef VERSION_AUG6
    static ActMail wayOnChk_mes[2] = {{393}, {392}}; /* derived name */
#endif

    if (girlGObj == 0) {
        _ACTWait(0);
    }
#ifdef VERSION_AUG6
    while (scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
#else
    while (scpCheckExistAliveEnemy() != 0 || scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
#endif
        _ACTWait(1);
    }

    SetWayGroupActive(17, 1);
    gflagOn(91);

    wayOnChk_mes[0].func = actSt03tWayOffChk;
    sub->mail = wayOnChk_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 397);
#endif
    _ACTWait(0);
}

inline void actSt03tWayOffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
#ifdef VERSION_AUG6
    static ActMail wayOffChk_mes[2] = {{393}, {392}}; /* derived name */
#endif

    if (girlGObj == 0) {
        _ACTWait(0);
    }
#ifdef VERSION_AUG6
    while (scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
#else
    while (scpCheckExistAliveEnemy() == 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
#endif
        _ACTWait(1);
    }

    SetWayGroupActive(17, 0);
    gflagOff(91);

    wayOffChk_mes[0].func = actSt03tWayOnChk;
    sub->mail = wayOffChk_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 397);
#endif
    _ACTWait(0);
}

void actSt03tInit(void)
{
#ifdef VERSION_AUG6
    if (gflagChk(82) == 0) {
#else
    if (gflagChk(82) != 0) {
        SetWayGroupActive(7, 1);
    } else {
#endif
        SetWayGroupActive(7, 0);
    }

    if (gflagChk(83) != 0) {
        SetWayGroupActive(5, 1);
    } else {
        SetWayGroupActive(5, 0);
    }
}
#else
static void actSt03tGirlPosChk(GObj *volatile self);
static void actSt03tGirlUpChk(GObj *volatile self);
static void actSt03tHint1OffChk(GObj *volatile self);

static ActMail switchL_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchLUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchLChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchLUpChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchR_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchRUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchRChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail switchRUpChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail girlCam_mes[2] = {{430}, {429}}; /* derived name */

static ActMail girlCamStartChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail girlCamEndChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene_mes[2] = {{430}, {429}}; /* derived name */

static ActMail wayOn_mes[2] = {{430}, {429}}; /* derived name */

static ActMail wayOff_mes[2] = {{430}, {429}}; /* derived name */

static ActMail wayOnChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail wayOffChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail girlPos_mes[2] = {{430}, {429}}; /* derived name */

static ActMail girlUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hint1Sleep_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hint1OffChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail hint1OnChk_mes[2] = {{430}, {429}}; /* derived name */

void actSt03tSwitchL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(89) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(360, 0, 0);
        stage_SetAnimation(362, 0, 0);
#else
        stage_SetAnimation(364, 0, 0);
        stage_SetAnimation(366, 0, 0);
#endif

        switchL_mes[0].func = actSt03tSwitchLChk;
        act->mail = switchL_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(360, 0, 45);
        stage_SetAnimation(362, 0, -1);
#else
        stage_SetAnimation(364, 0, 45);
        stage_SetAnimation(366, 0, -1);
#endif

        switchLUp_mes[0].func = actSt03tSwitchLUpChk;
        act->mail = switchLUp_mes;
        ACTSendMailCorrect(self, 430);
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

    gflagOn(102);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(360, 1, 0);
#else
    stage_SetAnimation(364, 1, 0);
#endif
    soundSeDefPlay(1220, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(360, 45, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(364, 45, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(89);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(362, 1, 0);
#else
    stage_SetAnimation(366, 1, 0);
#endif

    SetWayGroupActive(7, 1);

    gflagOn(91);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(362, 75, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(366, 75, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1218, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(362, 90, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(366, 90, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1219, 0, 0, 1);

    SetCameraFlag_LwsCutBack();

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(362) == 0) {
#else
    while (stage_CheckAnimationFinish(366) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    switchLChk_mes[0].func = actSt03tSwitchLUpChk;
    act->mail = switchLChk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt03tSwitchLUpChk(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    while (scpTriggerFloorAttrTargetMan(self, 0x1000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(60);

    gflagOff(89);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(360, 1, 46);
#else
    stage_SetAnimation(364, 1, 46);
#endif
    soundSeDefPlay(1220, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(360, 90, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(364, 90, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(363, 1, 0);
#else
    stage_SetAnimation(367, 1, 0);
#endif

    if (girlGObj != 0) {
        scpCheckDisconnectWallStart(girlGObj);
    }

    SetWayGroupActive(7, 0);

    soundSeDefPlay(1218, 0, 0, 1);
    _ACTWait(30);
    soundSeDefPlay(1219, 0, 0, 1);

    SetCameraFlag_LwsCutBack();

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(363, 120, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(367, 120, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    if (girlGObj != 0) {
        scpCheckDisconnectWallEnd(girlGObj);
    }

    switchLUpChk_mes[0].func = actSt03tSwitchLChk;
    act->mail = switchLUpChk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt03tSwitchR(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(90) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(361, 0, 0);
        stage_SetAnimation(364, 0, 0);
#else
        stage_SetAnimation(365, 0, 0);
        stage_SetAnimation(368, 0, 0);
#endif

        switchR_mes[0].func = actSt03tSwitchRChk;
        act->mail = switchR_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(361, 0, 45);
        stage_SetAnimation(364, 0, -1);
#else
        stage_SetAnimation(365, 0, 45);
        stage_SetAnimation(368, 0, -1);
#endif

        switchRUp_mes[0].func = actSt03tSwitchRUpChk;
        act->mail = switchRUp_mes;
        ACTSendMailCorrect(self, 430);
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

    gflagOn(102);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(361, 1, 0);
#else
    stage_SetAnimation(365, 1, 0);
#endif
    soundSeDefPlay(1220, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(361, 45, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(365, 45, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(364, 1, 0);
#else
    stage_SetAnimation(368, 1, 0);
#endif

    SetWayGroupActive(5, 1);

    gflagOn(91);

    soundSeDefPlay(1218, 0, 0, 1);
    _ACTWait(30);
    soundSeDefPlay(1219, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(364) == 0) {
#else
    while (stage_CheckAnimationFinish(368) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(90);

    switchRChk_mes[0].func = actSt03tSwitchRUpChk;
    act->mail = switchRChk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt03tSwitchRUpChk(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    while (scpTriggerFloorAttrTargetMan(self, 0x2000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(((60 - systemStatus[0] * 10) / systemStatus[1]) * 10);

    gflagOff(90);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(361, 1, 46);
#else
    stage_SetAnimation(365, 1, 46);
#endif
    soundSeDefPlay(1220, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(361, 90, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(365, 90, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(365, 1, 0);
#else
    stage_SetAnimation(369, 1, 0);
#endif

    SetWayGroupActive(5, 0);

    soundSeDefPlay(1218, 0, 0, 1);
    _ACTWait(30);
    soundSeDefPlay(1219, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(365) == 0) {
#else
    while (stage_CheckAnimationFinish(369) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    switchRUpChk_mes[0].func = actSt03tSwitchRChk;
    act->mail = switchRUpChk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt03tGene(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    Generator_Mask(self);

    Generator_Mask(scpSearchGobj(877));
    Generator_Mask(scpSearchGobj(878));

    while (gflagChk(105) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(self);

    Generator_Call(self);
    _ACTWait(20);
    Generator_Call(self);

    Generator_Call(scpSearchGobj(877));
    Generator_Call(scpSearchGobj(878));
}

void actSt03tBoxA(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(298) == 0) {
        scpSearchGobj(865)->active = 0;
    } else {
        scpSearchGobj(852)->active = 0;
        scpSearchGobj(863)->active = 0;
        scpSearchGobj(865)->active = 1;

        scpTransGObj(scpSearchGobj(865), 0.0f, -200.0f, 0.0f);
        _ACTWait(1);
        ReInitBoxGeo(scpSearchGobj(865));
    }
}

void actSt03tBoxB(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(299) == 0) {
        scpSearchGobj(866)->active = 0;
    } else {
        scpSearchGobj(853)->active = 0;
        scpSearchGobj(864)->active = 0;
        scpSearchGobj(866)->active = 1;

        gflagOn(98);

        scpTransGObj(scpSearchGobj(866), 0.0f, -400.0f, 0.0f);
        _ACTWait(1);
        ReInitBoxGeo(scpSearchGobj(866));
    }
}

void actSt03tInit(void)
{
    if (gflagChk(91) != 0) {
        SetWayGroupActive(7, 1);
    } else {
        SetWayGroupActive(7, 0);
    }

    if (gflagChk(92) != 0) {
        SetWayGroupActive(5, 1);
    } else {
        SetWayGroupActive(5, 0);
    }
}

void actSt03tGirlUp(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(93) == 0) {
        girlUp_mes[0].func = actSt03tGirlUpChk;
        act->mail = girlUp_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        FinishHint(12);
    }
}

void actSt03tGirlCam(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    girlCam_mes[0].func = actSt03tGirlCamStartChk;
    act->mail = girlCam_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt03tSekizo(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpSekizou(self, 95, 76, 0, 18, -913.0f, -400.0f, 605.0f, -1000.0f, -400.0f, 550.0f);
#else
    scpSekizou(self, 95, 80, 0, 18, -913.0f, -400.0f, 605.0f, -1000.0f, -400.0f, 550.0f);
#endif
}

void actSt03tWay(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(100) == 0) {
        wayOn_mes[0].func = actSt03tWayOnChk;
        act->mail = wayOn_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        wayOff_mes[0].func = actSt03tWayOffChk;
        act->mail = wayOff_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt03tEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(104) == 0) {
        ene_mes[0].func = actSt03tEneChk;
        act->mail = ene_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt03tGirlPos(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(101) == 0) {
        SleepHint(12);

        girlPos_mes[0].func = actSt03tGirlPosChk;
        act->mail = girlPos_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt03tHint1Sleep(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    hint1Sleep_mes[0].func = actSt03tHint1OffChk;
    act->mail = hint1Sleep_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt03tGirlCamEvent(int x)
{
    volatile int local = x;
}

void actSt03tGirlCamStartChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, boyGObj, 100.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) != 202) {
        _ACTWait(1);
    }

    CameraGetTarget();
    Camctrl_SetTarget(girlGObj, 0, 3);
    _ACTWait(15);
    CameraSetCameraSet(48);

    girlCamStartChk_mes[0].func = actSt03tGirlCamEndChk;
    sub->mail = girlCamStartChk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt03tGirlCamEndChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerBall(self, boyGObj, 100.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(boyGObj) == 202) {
        _ACTWait(1);
    }

    CameraGetTarget();
    _ACTWait(90);
    CameraSetCameraSet_Default();
    Camctrl_ExitEveRock();

    girlCamEndChk_mes[0].func = actSt03tGirlCamStartChk;
    sub->mail = girlCamEndChk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt03tSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt03tEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerBall(self, boyGObj, 100.0f) == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpSleepEnemyOne(3734);
#else
    scpSleepEnemyOne(3757);
#endif
    gflagOn(104);
    gflagOn(105);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(77, 1, 0);
#else
    stage_SetAnimation(81, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(77) == 0) {
#else
    while (stage_CheckAnimationFinish(81) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

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
}

void actSt03tWayOnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() != 0 || scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(17, 1);
    gflagOn(100);

    wayOnChk_mes[0].func = actSt03tWayOffChk;
    sub->mail = wayOnChk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt03tWayOffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() == 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) != 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(17, 0);
    gflagOff(100);

    wayOffChk_mes[0].func = actSt03tWayOnChk;
    sub->mail = wayOffChk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

static void actSt03tGirlPosChk(GObj *volatile self)
{
    while (girlGObj == 0 || scpTriggerFloorAttr(girlGObj, 0x5000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(101);
    WakeupHint(12);
}

static void actSt03tGirlUpChk(GObj *volatile self)
{
    while (girlGObj == 0 || scpTriggerFloorAttr(girlGObj, 0x4000000) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy("HINT1_FINISH!!!!!!!!!!!!!!!\n");
    gflagOn(93);
    FinishHint(12);
}

static void actSt03tHint1OnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 60);
    WakeupHint(12);

    hint1OnChk_mes[0].func = actSt03tHint1OffChk;
    sub->mail = hint1OnChk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

static void actSt03tHint1OffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (gflagChk(102) == 0) {
        _ACTWait(1);
    }

    SleepHint(12);
    gflagOff(102);

    hint1OffChk_mes[0].func = actSt03tHint1OnChk;
    sub->mail = hint1OffChk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}
#endif
