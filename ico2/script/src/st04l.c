#include "st04l.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "obj_manager.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act-game.h"
#include "act.h"
#include "gobj_process.h"
#include "boyact.h"
#include "commonact.h"
#include "girl_act.h"
#include "way_llf.h"
#include "camera-root.h"
#include "fightSound.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "st04r.h"
#include "StageAnimation.h"
#include "attackCheckBoundary.h"
#include "motionManager2.h"
#include "weapon.h"
#include <libvu0.h>
#include "typedef.h"
#include "st04r.h"
#include "script.h"
#include "main.h"

/* No .sbss here in this build: no function of the demo addresses these flags. */

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec stairSubPos = {{0.0f, 0.0f, -5000.0f, 1.0f}}; /* derived name */

/* .sdata: the room's stream handles and shakes. This build has the three
   crest handles, solar4l (actSt04eSolarBeamChk's), the bridge's handle, the
   crests' pad shake and the sekizo's pad shake with their volumes (the
   demo's crest and sekizo functions address them in this order): no ball
   handles, no stair or statue handle (no function of the demo addresses
   one). */
SqEntry *crest1 = 0;

SqEntry *crest2 = 0;

SqEntry *crest3 = 0;

SqEntry *solar4l = 0;

SqEntry *st04d_hasi = 0;

unsigned int st04l_yure = 0;

unsigned char st04l_yure_vol = 0;

unsigned int sekizo_4l = 0;

unsigned char sekizo_4l_vol = 0;

void actSt04cInit(void)
{
    if (gflagChk(183) == 0) {
        stage_SetAnimation(184, 0, 0);
    } else {
        stage_SetAnimation(184, 0, -1);
    }

    if (gflagChk(184) == 0) {
        stage_SetAnimation(185, 0, 0);
    } else {
        stage_SetAnimation(185, 0, -1);
    }

    if (gflagChk(185) == 0) {
        stage_SetAnimation(186, 0, 0);
    } else {
        stage_SetAnimation(186, 0, -1);
    }

    if (gflagChk(186) == 0) {
        stage_SetAnimation(187, 0, 0);
    } else {
        stage_SetAnimation(187, 0, -1);
    }

    if (gflagChk(187) == 0) {
        stage_SetAnimation(188, 0, 0);
    } else {
        stage_SetAnimation(188, 0, -1);
    }

    if (gflagChk(188) == 0) {
        stage_SetAnimation(189, 0, 0);
    } else {
        stage_SetAnimation(189, 0, -1);
    }

    if (gflagChk(189) == 0) {
        SetWayGroupActive(1, 0);
        stage_SetAnimation(190, 0, 0);
    } else {
        SetWayGroupActive(1, 1);
        stage_SetAnimation(190, 0, -1);
    }

    if (gflagChk(156) == 0) {
        stage_SetAnimation(175, 0, 0);
    } else {
        stage_SetAnimation(175, 0, -1);
    }

    if (gflagChk(157) == 0) {
        stage_SetAnimation(176, 0, 0);
    } else {
        stage_SetAnimation(176, 0, -1);
    }
}

void actSt04dInit(void)
{
    if (gflagChk(154) == 0) {
        stage_SetAnimation(178, 0, 0);
        stage_SetAnimation(204, 0, 0);
    } else {
        stage_SetAnimation(178, 0, -1);
        stage_SetAnimation(204, 0, -1);
    }

    if (gflagChk(156) == 0) {
        stage_SetAnimation(175, 0, 0);
        SetWayGroupActive(3, 0);
    } else {
        stage_SetAnimation(175, 0, -1);
        SetWayGroupActive(3, 1);
    }

    if (gflagChk(157) == 0) {
        stage_SetAnimation(176, 0, 0);
        SetWayGroupActive(4, 0);
    } else {
        stage_SetAnimation(176, 0, -1);
        SetWayGroupActive(4, 1);
    }

    if (gflagChk(183) == 0) {
        stage_SetAnimation(184, 0, 0);
    } else {
        stage_SetAnimation(184, 0, -1);
    }

    if (gflagChk(184) == 0) {
        stage_SetAnimation(185, 0, 0);
    } else {
        stage_SetAnimation(185, 0, -1);
    }

    if (gflagChk(185) == 0) {
        stage_SetAnimation(186, 0, 0);
    } else {
        stage_SetAnimation(186, 0, -1);
    }

    if (gflagChk(186) == 0) {
        stage_SetAnimation(187, 0, 0);
    } else {
        stage_SetAnimation(187, 0, -1);
    }

    if (gflagChk(187) == 0) {
        stage_SetAnimation(188, 0, 0);
    } else {
        stage_SetAnimation(188, 0, -1);
    }

    if (gflagChk(188) == 0) {
        stage_SetAnimation(189, 0, 0);
    } else {
        stage_SetAnimation(189, 0, -1);
    }

    if (gflagChk(189) == 0) {
        stage_SetAnimation(190, 0, 0);
    } else {
        stage_SetAnimation(190, 0, -1);
    }

    if (gflagChk(138) != 0 && gflagChk(148) == 0) {
        stage_SetAnimation(199, 0, -1);
    }

    if (gflagChk(138) == 0 || gflagChk(148) != 0) {
        stage_SetAnimation(199, 0, 0);
    }

    if (gflagChk(164) != 0) {
        stage_SetAnimation(179, 0, 200);
    } else {
        stage_SetAnimation(179, 0, 0);
    }
}

void actSt04eInit(void)
{
    if (gflagChk(196) == 0) {
        SetWayGroupActive(5, 0);
    } else {
        SetWayGroupActive(5, 1);
    }

    if (gflagChk(156) == 0) {
        stage_SetAnimation(175, 0, 0);
    } else {
        stage_SetAnimation(175, 0, -1);
    }

    if (gflagChk(157) == 0) {
        stage_SetAnimation(176, 0, 0);
    } else {
        stage_SetAnimation(176, 0, -1);
    }
}

/* The tables a handler installs through its own `sub` are static locals (the
   ball switches, GondolaCharaChk), the rest file-scope; the inline handlers
   precede the actors, which are defined last. */
void actSt04lC1BallMain(GObj *volatile self);
inline void actSt04lC1BallSwitch(GObj *volatile self);

static ActMail c1BallMain_mes[2] = {{356, actSt04lC1BallSwitch}, {376}}; /* derived name */

static ActMail c1Ball_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt04lC1BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

    sub->mainMail = c1BallMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

inline void actSt04lC1BallSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail c1BallSwitch_mes[2] = {{377}, {376}}; /* derived name */

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    c1BallSwitch_mes[0].func = actSt04lC1BallTurn;
    sub->mail = c1BallSwitch_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt04lC1BallTurn(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(151);
    scpSleepEnemyAll();

    _ACTWait(60);

    stage_SetAnimation(168, 1, 0);
    scpAdpcmPlayRequestFunc(75, 0, 1, 1, 1);

    while (stage_CheckAnimationFinish(168) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpSearchGobj(973)->active = 1;
    scpSearchGobj(974)->active = 1;

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 6);

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt04lC2BallMain(GObj *volatile self);
inline void actSt04lC2BallSwitch(GObj *volatile self);

static ActMail c2BallMain_mes[2] = {{356, actSt04lC2BallSwitch}, {376}}; /* derived name */

static ActMail c2Ball_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt04lC2BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

    sub->mainMail = c2BallMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

inline void actSt04lC2BallSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail c2BallSwitch_mes[2] = {{377}, {376}}; /* derived name */

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    c2BallSwitch_mes[0].func = actSt04lC2BallTurn;
    sub->mail = c2BallSwitch_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt04lC2BallTurn(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(152);
    scpSleepEnemyAll();

    _ACTWait(60);

    stage_SetAnimation(169, 1, 0);
    scpAdpcmPlayRequestFunc(75, 0, 1, 1, 1);

    while (stage_CheckAnimationFinish(169) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpSearchGobj(1053)->active = 1;
    scpSearchGobj(1054)->active = 1;

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 6);

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt04lC3BallMain(GObj *volatile self);
inline void actSt04lC3BallSwitch(GObj *volatile self);
inline void actSt04lC3BallTurn(GObj *volatile self);

static ActMail c3BallMain_mes[2] = {{357, actSt04lC3BallSwitch}, {376}}; /* derived name */

static ActMail c3Ball_mes[2] = {{377}, {376}}; /* derived name */

inline void actSt04lC3BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

    sub->mainMail = c3BallMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

inline void actSt04lC3BallSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail c3BallSwitch_mes[2] = {{377}, {376}}; /* derived name */

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    c3BallSwitch_mes[0].func = actSt04lC3BallTurn;
    sub->mail = c3BallSwitch_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt04lC3BallTurn(GObj *volatile self)
{
    lt_switch_layout(51);
    scpSleepEnemyAll();
    gflagOn(153);

    _ACTWait(60);

    stage_SetAnimation(170, 1, 0);
    scpAdpcmPlayRequestFunc(75, 0, 1, 1, 1);

    while (stage_CheckAnimationFinish(170) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpSearchGobj(1055)->active = 1;
    scpSearchGobj(1056)->active = 1;

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

static ActMail crest01_mes[2] = {{377}, {376}}; /* derived name */

static ActMail crest02_mes[2] = {{377}, {376}}; /* derived name */

static ActMail crest03_mes[2] = {{377}, {376}}; /* derived name */

static ActMail st04eSolarBeam_mes[2] = {{377}, {376}}; /* derived name */

static ActMail stair_mes[2] = {{377}, {376}}; /* derived name */

static ActMail rope1_mes[2] = {{377}, {376}}; /* derived name */

static ActMail rope2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail brg1_mes[2] = {{377}, {376}}; /* derived name */

static ActMail rope3_mes[2] = {{377}, {376}}; /* derived name */

static ActMail rope4_mes[2] = {{377}, {376}}; /* derived name */

static ActMail brg2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail brg1Way_mes[2] = {{377}, {376}}; /* derived name */

static ActMail brg2Way_mes[2] = {{377}, {376}}; /* derived name */

static ActMail sekizo_mes[2] = {{377}, {376}}; /* derived name */

static ActMail turi_mes[2] = {{377}, {376}}; /* derived name */

static ActMail gondola_mes[2] = {{377}, {376}}; /* derived name */

static ActMail gondola2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail gondolaChk_mes[2] = {{377}, {376}}; /* derived name */

void actSt04lCrest02(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(149) == 0) {
        if (current_stage_no == 19) {
            stage_SetAnimation(162, 0, 0);
        } else {
            stage_SetAnimation(163, 0, 0);
        }

        crest02_mes[0].func = actSt04lCrest2Main;
        act->mail = crest02_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        if (current_stage_no == 19) {
            stage_SetAnimation(162, 0, -1);
        } else {
            stage_SetAnimation(163, 0, -1);
        }
    }
}

void actSt04lCrestMain(GObj *volatile self)
{
    while (scpIsTorchLightOn(973) == 0 || scpIsTorchLightOn(974) == 0 || gflagChk(151) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(29, &crest1, 0, 1, 1);

    while (crest1 == 0) {
        _ACTWait(1);
    }

    gflagOn(148);
    gflagOn(195);

    stage_SetAnimation(198, 1, 0);
    stage_SetAnimation(160, 1, 0);

    while (stage_CheckAnimationFrame(160, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    st04l_yure = iosPadActRequest(boyPad, 10);
    st04l_yure_vol = 128;
    iosPadActVolumeSet(st04l_yure, 128);

    while (stage_CheckAnimationFrame(160, 190, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(st04l_yure);

    while (stage_CheckAnimationFinish(160) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpWakeupEnemyAll();
    RequestStageChange(3, boyGObj, girlGObj, 16.0f, 16.0f);
}

void actSt04lCrest2Main(GObj *volatile self)
{
    if (current_stage_no == 19) {
        while (scpIsTorchLightOn(977) == 0 || scpIsTorchLightOn(978) == 0 || gflagChk(152) == 0) {
            _ACTWait(1);
        }
    }

    if (current_stage_no == 20) {
        while (scpIsTorchLightOn(1053) == 0 || scpIsTorchLightOn(1054) == 0 || gflagChk(152) == 0) {
            _ACTWait(1);
        }
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(28, &crest2, 1, 1, 1);

    while (crest2 == 0) {
        _ACTWait(1);
    }

    gflagOn(149);

    if (current_stage_no == 19) {
        stage_SetAnimation(162, 1, 0);

        while (stage_CheckAnimationFrame(162, 30, 0) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);

        st04l_yure = iosPadActRequest(boyPad, 10);
        st04l_yure_vol = 128;
        iosPadActVolumeSet(st04l_yure, 128);

        while (stage_CheckAnimationFrame(162, 190, 0) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);
        iosPadActStop(st04l_yure);

        while (stage_CheckAnimationFinish(162) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);
        scpSearchGobj(981)->active = 1;
    } else {
        stage_SetAnimation(163, 1, 0);

        while (stage_CheckAnimationFrame(163, 30, 0) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);

        st04l_yure = iosPadActRequest(boyPad, 10);
        st04l_yure_vol = 128;
        iosPadActVolumeSet(st04l_yure, 128);

        while (stage_CheckAnimationFrame(163, 190, 0) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);
        iosPadActStop(st04l_yure);

        while (stage_CheckAnimationFinish(163) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);
    }

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
}

void actSt04lCrest3Main(GObj *volatile self)
{
    while (scpIsTorchLightOn(1055) == 0 || scpIsTorchLightOn(1056) == 0 || gflagChk(153) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(26, &crest3, 0, 1, 1);

    while (crest3 == 0) {
        _ACTWait(1);
    }

    gflagOn(150);
    stage_SetAnimation(164, 1, 0);

    while (stage_CheckAnimationFrame(164, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    st04l_yure = iosPadActRequest(boyPad, 10);
    st04l_yure_vol = 128;
    iosPadActVolumeSet(st04l_yure, 128);

    while (stage_CheckAnimationFrame(164, 190, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(st04l_yure);

    while (stage_CheckAnimationFinish(164) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
}

void actSt04lStairChk(GObj *volatile self)
{
    long long ofs[2];
    float dir[4];

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0xB000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0xB000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    gflagOn(154);

    scpSearchGobj(1089)->active = 0;

    stage_SetAnimation(205, -1, -2);

    _ACTWait(60);

    scpAdpcmPlayRequestFunc(56, 0, 1, 1, 1);

    stage_SetAnimation(204, 1, 0);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 521);
    scpPlayPosSet(boyGObj, 55.0f, 28.0f, -3881.0f);
    scpPlayPosSet(girlGObj, -58.0f, 28.0f, -3891.0f);

    ofs[0] = stairSubPos.d[0];
    ofs[1] = stairSubPos.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    ofs[0] = stairSubPos.d[0];
    ofs[1] = stairSubPos.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, dir);

    while (stage_CheckAnimationFinish(204) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

    stage_SetAnimation(178, 1, 0);

    while (stage_CheckAnimationFrame(178, 140, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    st04l_yure = iosPadActRequest(boyPad, 9);
    st04l_yure_vol = 128;
    iosPadActVolumeSet(st04l_yure, 128);

    while (stage_CheckAnimationFinish(178) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(st04l_yure);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 521);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
    gflagOn(191);
}

void actSt04lBrg1Chk(GObj *volatile self)
{
    while (gflagChk(158) == 0 || gflagChk(159) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    gflagOn(156);

    _ACTWait(60);

    scpAdpcmPlayRequestFunc(79, &st04d_hasi, 1, 1, 1);

    while (st04d_hasi == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(175, 1, 0);

    while (stage_CheckAnimationFrame(175, 120, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFinish(175) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt04lBrg2Chk(GObj *volatile self)
{
    while (gflagChk(160) == 0 || gflagChk(161) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    gflagOn(157);

    _ACTWait(60);

    scpAdpcmPlayRequestFunc(79, &st04d_hasi, 1, 1, 1);

    while (st04d_hasi == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(176, 1, 0);

    while (stage_CheckAnimationFrame(176, 120, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFinish(176) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt04lSekizoChk(GObj *volatile self)
{
    float dir[4];

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(self, boyGObj, 200.0f) == 0 ||
           scpTriggerBall(self, girlGObj, 200.0f) == 0 ||
           scpTriggerFloorAttr(boyGObj, 0x8000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x8000000) == 0) {
        _ACTWait(1);
    }

    scpSekizouCheckPoint();

    scpAdpcmPlayRequestFunc(21, 0, 1, 1, 1);

    scpKillEnemyAll();
    scpMaskGeneratorAll();

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    gflagOn(162);

    _ACTWait(60);

    stage_SetAnimation(177, 1, 0);

    sekizo_4l = iosPadActRequest(boyPad, 9);
    sekizo_4l_vol = 128;
    iosPadActVolumeSet(sekizo_4l, 128);

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);
    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 521);
    scpPlayPosSet(girlGObj, 0.0f, -1300.0f, -1700.0f);
    scpPlayPosSet(boyGObj, 20.0f, -1300.0f, -1700.0f);

    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT((void *)self), test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, dir);

    scpBoyControlReadDisable = 1;

    sceVu0SubVector(dir, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    scpPlayMot(girlGObj, 584);
    scpPlayWaitMotEnd(girlGObj);

    while (stage_CheckAnimationFrame(177, 151, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(sekizo_4l);

    scpPlayMot(girlGObj, 521);
    scpPlayEnd(girlGObj);
    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

inline void actSt04eSolarBeamChk(GObj *volatile self)
{
    gflagOff(195);
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    scpAdpcmPlayRequestFunc(30, &solar4l, 0, 1, 1);

    while (solar4l == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    stage_SetAnimation(232, 1, 0);

    while (stage_CheckAnimationFinish(232) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    RequestStageChange(7, boyGObj, girlGObj, 16.0f, 16.0f);
}

inline void actSt04lRope1Event(int x)
{
    volatile int local = x;
}

inline void actSt04lRope1Chk(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(158) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1031))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1031)->active = 0;
            gflagOn(158);
            stage_SetAnimation(171, 1, 0);

            while (stage_CheckAnimationFinish(171) == 0) {
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        }
    }
}

inline void actSt04lRope2Event(int x)
{
    volatile int local = x;
}

inline void actSt04lRope2Chk(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(159) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1032))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1032)->active = 0;
            gflagOn(159);
            stage_SetAnimation(172, 1, 0);

            while (stage_CheckAnimationFinish(172) == 0) {
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        }
    }
}

inline void actSt04lBrg1Event(int x)
{
    volatile int local = x;
}

inline void actSt04lRope3Event(int x)
{
    volatile int local = x;
}

inline void actSt04lRope3Chk(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(160) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1033))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1033)->active = 0;
            gflagOn(160);
            stage_SetAnimation(173, 1, 0);

            while (stage_CheckAnimationFinish(173) == 0) {
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        }
    }
}

inline void actSt04lRope4Event(int x)
{
    volatile int local = x;
}

inline void actSt04lRope4Chk(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(161) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1034))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1034)->active = 0;
            gflagOn(161);
            stage_SetAnimation(174, 1, 0);

            while (stage_CheckAnimationFinish(174) == 0) {
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        }
    }
}

inline void actSt04lBrg2Event(int x)
{
    volatile int local = x;
}

inline void actSt04lBrg1WayChk(GObj *volatile self)
{
    while (gflagChk(156) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(3, 1);
}

inline void actSt04lBrg2WayChk(GObj *volatile self)
{
    while (gflagChk(156) == 0 || gflagChk(157) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(4, 1);
}

inline void actSt04lTuriEvent(int x)
{
    volatile int local = x;
}

inline void actSt04lTuriChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(self, girlGObj, 200.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    gflagOn(163);
    _ACTWait(10);

    stage_SetAnimation(181, 1, 0);

    while (stage_CheckAnimationFinish(181) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    lt_switch_layout(50);
}

inline void actSt04lGondolaCharaChk(GObj *volatile self);

void actSt04lGondolaChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttr(boyGObj, 0xA000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    _ACTWait(15);

    if (gflagChk(164) != 0) {
        stage_SetAnimation(179, 1, 200);
        soundSeDefPlay(1266, 0, 0, 1);

        while (stage_CheckAnimationFinish(179) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        soundSeDefPlay(1267, 0, 0, 1);

        gflagOff(164);
    } else {
        stage_SetAnimation(179, 1, 0);
        soundSeDefPlay(1266, 0, 0, 1);

        while (stage_CheckAnimationFrame(179, 200, 1) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        soundSeDefPlay(1267, 0, 0, 1);

        gflagOn(164);
    }

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);

    gondolaChk_mes[0].func = actSt04lGondolaCharaChk;
    sub->mail = gondolaChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void actSt04lGondolaCharaChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    static ActMail gondolaCharaChk_mes[2] = {{377}, {376}}; /* derived name */

    while (scpTriggerFloorAttr(boyGObj, 0xA000000)) {
        _ACTWait(1);
    }

    gondolaCharaChk_mes[0].func = actSt04lGondolaChk;
    sub->mail = gondolaCharaChk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

static ActMail monyou01_mes[2] = {{377}, {376}}; /* derived name */

static ActMail monyou02_mes[2] = {{377}, {376}}; /* derived name */

static ActMail monyou03_mes[2] = {{377}, {376}}; /* derived name */

static ActMail monyou04_mes[2] = {{377}, {376}}; /* derived name */

static ActMail monyou05_mes[2] = {{377}, {376}}; /* derived name */

static ActMail monyou06_mes[2] = {{377}, {376}}; /* derived name */

static ActMail monyou07_mes[2] = {{377}, {376}}; /* derived name */

static ActMail ori_mes[2] = {{377}, {376}}; /* derived name */

static ActMail ori2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail sword_mes[2] = {{377}, {376}}; /* derived name */

static ActMail torch1_1_mes[2] = {{377}, {376}}; /* derived name */

static ActMail torch1_2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail torch2_1_mes[2] = {{377}, {376}}; /* derived name */

static ActMail torch2_2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail torch3_1_mes[2] = {{377}, {376}}; /* derived name */

static ActMail torch3_2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail torch2_1XL_mes[2] = {{377}, {376}}; /* derived name */

static ActMail torch2_2XL_mes[2] = {{377}, {376}}; /* derived name */

void actSt04lMonyou07Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x7000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x7000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
    gflagOn(189);
    _ACTWait(5);

    stage_SetAnimation(190, 1, 0);
    soundSeDefPlay(1277, 0, 0, 1);

    while (stage_CheckAnimationFrame(190, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    SetWayGroupActive(1, 1);

    scpBoyControlReadDisable = 0;
}

void actSt04lOriChk(GObj *volatile self)
{
    while (gflagChk(149) == 0 || scpGameStat_BoyWeaponkind() != 4 ||
           scpTriggerBall(self, boyGObj, 1000.0f) == 0) {
        _ACTWait(1);
    }

    scpSleepEnemyAll();
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    scpPlayMot(boyGObj, 0);

    gflagOn(173);

    _ACTWait(60);

    scpAdpcmPlayRequestFunc(57, 0, 1, 1, 1);

    stage_SetAnimation(193, 1, 0);

    while (stage_CheckAnimationFrame(193, 90, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActRequest(boyPad, 15);

    while (stage_CheckAnimationFinish(193) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt04lOri2Chk(GObj *volatile self) /* derived name */
{
    while (1) {
        if (scpGameStat_BoyWeaponkind() == 4 && scpTriggerBall(self, boyGObj, 100.0f) != 0 &&
            (ForMotionViewer_GetCurrentMotion(boyGObj) == 39 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 44 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 46 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 40 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 41 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 62))
            break;
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    gflagOn(174);
    scpSleepEnemyAll();

    iosPadActRequest(boyPad, 17);
    _ACTWait(30);

    scpAdpcmPlayRequestFunc(58, 0, 1, 1, 1);

    stage_SetAnimation(194, 1, 0);

    while (stage_CheckAnimationFrame(194, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActRequest(boyPad, 15);

    while (stage_CheckAnimationFinish(194) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

inline void actSt04lMonyou01Event(int x)
{
    volatile int local = x;
}

inline void actSt04lMonyou01Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x1000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
    gflagOn(183);
    _ACTWait(5);

    stage_SetAnimation(184, 1, 0);
    soundSeDefPlay(1277, 0, 0, 1);

    while (stage_CheckAnimationFrame(184, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpBoyControlReadDisable = 0;
}

inline void actSt04lMonyou02Event(int x)
{
    volatile int local = x;
}

inline void actSt04lMonyou02Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x2000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
    gflagOn(184);
    _ACTWait(5);

    stage_SetAnimation(185, 1, 0);
    soundSeDefPlay(1277, 0, 0, 1);

    while (stage_CheckAnimationFrame(185, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpBoyControlReadDisable = 0;
}

inline void actSt04lMonyou03Event(int x)
{
    volatile int local = x;
}

inline void actSt04lMonyou03Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x3000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
    gflagOn(185);
    _ACTWait(5);

    stage_SetAnimation(186, 1, 0);
    soundSeDefPlay(1277, 0, 0, 1);

    while (stage_CheckAnimationFrame(186, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpBoyControlReadDisable = 0;
}

inline void actSt04lMonyou04Event(int x)
{
    volatile int local = x;
}

inline void actSt04lMonyou04Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x4000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x4000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
    gflagOn(186);
    _ACTWait(5);

    stage_SetAnimation(187, 1, 0);
    soundSeDefPlay(1277, 0, 0, 1);

    while (stage_CheckAnimationFrame(187, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpBoyControlReadDisable = 0;
}

inline void actSt04lMonyou05Event(int x)
{
    volatile int local = x;
}

inline void actSt04lMonyou05Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x5000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x5000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
    gflagOn(187);
    _ACTWait(5);

    stage_SetAnimation(188, 1, 0);
    soundSeDefPlay(1277, 0, 0, 1);

    while (stage_CheckAnimationFrame(188, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpBoyControlReadDisable = 0;
}

inline void actSt04lMonyou06Event(int x)
{
    volatile int local = x;
}

inline void actSt04lMonyou06Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x6000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x6000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
    gflagOn(188);
    _ACTWait(5);

    stage_SetAnimation(189, 1, 0);
    soundSeDefPlay(1277, 0, 0, 1);

    while (stage_CheckAnimationFrame(189, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpBoyControlReadDisable = 0;
}

inline void actSt04lMonyou07Event(int x)
{
    volatile int local = x;
}

inline void actSt04lOriEvent(int x)
{
    volatile int local = x;
}

inline void actSt04lOri2Event(int x)
{
    volatile int local = x;
}

inline void actSt04lSwordChk(GObj *volatile self)
{
    scpSearchGobj(981)->active = 0;
}

inline void actSt04lTorch1_1Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(973) == 0) {
        _ACTWait(1);
    }

    gflagOn(175);
}

inline void actSt04lTorch1_2Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(974) == 0) {
        _ACTWait(1);
    }

    gflagOn(176);
}

inline void actSt04lTorch2_1Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1053) == 0) {
        _ACTWait(1);
    }

    gflagOn(177);
}

inline void actSt04lTorch2_2Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1054) == 0) {
        _ACTWait(1);
    }

    gflagOn(178);
}

inline void actSt04lTorch3_1Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1055) == 0) {
        _ACTWait(1);
    }

    gflagOn(181);
}

inline void actSt04lTorch3_2Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1056) == 0) {
        _ACTWait(1);
    }

    gflagOn(182);
}

inline void actSt04lTorch2_1XLChk(GObj *volatile self)
{
    while (scpIsTorchLightOn(977) == 0) {
        _ACTWait(1);
    }

    gflagOn(179);
}

inline void actSt04lTorch2_2XLChk(GObj *volatile self)
{
    while (scpIsTorchLightOn(978) == 0) {
        _ACTWait(1);
    }

    gflagOn(180);
}

void actSt04lCrest01(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(148) == 0) {
        stage_SetAnimation(160, 0, 0);

        crest01_mes[0].func = actSt04lCrestMain;
        act->mail = crest01_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(160, 0, -1);
    }
}

void actSt04lCrest03(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(150) == 0) {
        stage_SetAnimation(164, 0, 0);

        crest03_mes[0].func = actSt04lCrest3Main;
        act->mail = crest03_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(164, 0, -1);
    }
}

void actSt04lC1Ball(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(151) == 0) {
        scpSearchGobj(973)->active = 0;
        scpSearchGobj(974)->active = 0;

        stage_SetAnimation(168, 0, 0);

        c1Ball_mes[0].func = actSt04lC1BallMain;
        act->mail = c1Ball_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(168, 0, -1);
    }
}

void actSt04lC2Ball(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(152) == 0) {
        scpSearchGobj(1053)->active = 0;
        scpSearchGobj(1054)->active = 0;

        stage_SetAnimation(169, 0, 0);

        c2Ball_mes[0].func = actSt04lC2BallMain;
        act->mail = c2Ball_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(169, 0, -1);
    }
}

void actSt04lC3Ball(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(153) == 0) {
        scpSearchGobj(1055)->active = 0;
        scpSearchGobj(1056)->active = 0;

        stage_SetAnimation(170, 0, 0);

        c3Ball_mes[0].func = actSt04lC3BallMain;
        act->mail = c3Ball_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(170, 0, -1);
    }
}

void actSt04lStair(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(154) == 0) {
        if (girlGObj != 0) {
            stair_mes[0].func = actSt04lStairChk;
            act->mail = stair_mes;
            ACTSendMailCorrect(self, 377);
            _ACTWait(0);
        }
    } else {
        scpSearchGobj(1089)->active = 0;

        stage_SetAnimation(205, -1, -2);
    }
}

void actSt04lBrg1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(156) == 0) {
        brg1_mes[0].func = actSt04lBrg1Chk;
        act->mail = brg1_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04lBrg2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(157) == 0) {
        brg2_mes[0].func = actSt04lBrg2Chk;
        act->mail = brg2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04lBrg1Way(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(156) == 0) {
        brg1Way_mes[0].func = actSt04lBrg1WayChk;
        act->mail = brg1Way_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04lBrg2Way(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(157) == 0) {
        brg2Way_mes[0].func = actSt04lBrg2WayChk;
        act->mail = brg2Way_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04lRope1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(158) == 0) {
        stage_SetAnimation(171, 0, 0);

        rope1_mes[0].func = actSt04lRope1Chk;
        act->mail = rope1_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(171, 0, -1);

        scpSearchGobj(1031)->active = 0;
    }
}

void actSt04lRope2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(159) == 0) {
        stage_SetAnimation(172, 0, 0);

        rope2_mes[0].func = actSt04lRope2Chk;
        act->mail = rope2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(172, 0, -1);

        scpSearchGobj(1032)->active = 0;
    }
}

void actSt04lRope3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(160) == 0) {
        stage_SetAnimation(173, 0, 0);

        rope3_mes[0].func = actSt04lRope3Chk;
        act->mail = rope3_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(173, 0, -1);

        scpSearchGobj(1033)->active = 0;
    }
}

void actSt04lRope4(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(161) == 0) {
        stage_SetAnimation(174, 0, 0);

        rope4_mes[0].func = actSt04lRope4Chk;
        act->mail = rope4_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(174, 0, -1);

        scpSearchGobj(1034)->active = 0;
    }
}

void actSt04lSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(162) == 0) {
        stage_SetAnimation(177, 0, 0);

        sekizo_mes[0].func = actSt04lSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(177, 0, -1);
    }
}

void actSt04lTuri(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(163) == 0) {
        stage_SetAnimation(181, 0, 0);

        if (girlGObj != 0) {
            turi_mes[0].func = actSt04lTuriChk;
            act->mail = turi_mes;
            ACTSendMailCorrect(self, 377);
            _ACTWait(0);
        }
    } else {
        stage_SetAnimation(181, 0, -1);
    }
}

void actSt04lOri(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(173) == 0) {
        stage_SetAnimation(193, 0, 0);

        ori_mes[0].func = actSt04lOriChk;
        act->mail = ori_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(193, 0, -1);
    }
}

void actSt04lOri2(GObj *volatile self) /* derived name */
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(174) == 0) {
        ori2_mes[0].func = actSt04lOri2Chk;
        act->mail = ori2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(194, 0, -1);
    }
}

void actSt04lSword(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(149) == 0) {
        sword_mes[0].func = actSt04lSwordChk;
        act->mail = sword_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04lGondola(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(164) != 0) {
        stage_SetAnimation(179, 0, 200);

        gondola_mes[0].func = actSt04lGondolaChk;
        act->mail = gondola_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(179, 0, 0);

        gondola2_mes[0].func = actSt04lGondolaChk;
        act->mail = gondola2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04lMonyou01(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(183) == 0) {
        stage_SetAnimation(184, 0, 0);

        monyou01_mes[0].func = actSt04lMonyou01Chk;
        act->mail = monyou01_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(184, 0, -1);
    }
}

void actSt04lMonyou02(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(184) == 0) {
        stage_SetAnimation(185, 0, 0);

        monyou02_mes[0].func = actSt04lMonyou02Chk;
        act->mail = monyou02_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(185, 0, -1);
    }
}

void actSt04lMonyou03(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(185) == 0) {
        stage_SetAnimation(186, 0, 0);

        monyou03_mes[0].func = actSt04lMonyou03Chk;
        act->mail = monyou03_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(186, 0, -1);
    }
}

void actSt04lMonyou04(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(186) == 0) {
        stage_SetAnimation(187, 0, 0);

        monyou04_mes[0].func = actSt04lMonyou04Chk;
        act->mail = monyou04_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(187, 0, -1);
    }
}

void actSt04lMonyou05(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(187) == 0) {
        stage_SetAnimation(188, 0, 0);

        monyou05_mes[0].func = actSt04lMonyou05Chk;
        act->mail = monyou05_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(188, 0, -1);
    }
}

void actSt04lMonyou06(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(188) == 0) {
        stage_SetAnimation(189, 0, 0);

        monyou06_mes[0].func = actSt04lMonyou06Chk;
        act->mail = monyou06_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(189, 0, -1);
    }
}

void actSt04lMonyou07(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(189) == 0) {
        stage_SetAnimation(190, 0, 0);

        monyou07_mes[0].func = actSt04lMonyou07Chk;
        act->mail = monyou07_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(190, 0, -1);
    }
}

void actSt04lCrest01XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(148) == 0) {
        stage_SetAnimation(165, 0, 0);
    } else {
        stage_SetAnimation(165, 0, -1);
    }
}

void actSt04lCrest02XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(149) == 0) {
        stage_SetAnimation(166, 0, 0);
    } else {
        stage_SetAnimation(166, 0, -1);
    }
}

void actSt04lCrest03XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(150) == 0) {
        stage_SetAnimation(167, 0, 0);
    } else {
        stage_SetAnimation(167, 0, -1);
    }
}

void actSt04lC2BallXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(152) == 0) {
        scpSearchGobj(977)->active = 0;
        scpSearchGobj(978)->active = 0;

        stage_SetAnimation(169, 0, 0);
    } else {
        stage_SetAnimation(169, 0, -1);
    }
}

void actSt04lC3BallXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(153) == 0) {
        stage_SetAnimation(170, 0, 0);

        scpSearchGobj(1129)->active = 0;
        scpSearchGobj(1130)->active = 0;
    } else {
        stage_SetAnimation(170, 0, -1);
    }
}

void actSt04lTorch1_1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(175) == 0) {
        torch1_1_mes[0].func = actSt04lTorch1_1Chk;
        act->mail = torch1_1_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpTorchLightOn(973);
    }
}

void actSt04lTorch1_2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(176) == 0) {
        torch1_2_mes[0].func = actSt04lTorch1_2Chk;
        act->mail = torch1_2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpTorchLightOn(974);
    }
}

void actSt04lTorch2_1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(177) != 0 || gflagChk(179) != 0) {
        scpTorchLightOn(1053);
    } else {
        torch2_1_mes[0].func = actSt04lTorch2_1Chk;
        act->mail = torch2_1_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04lTorch2_2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(178) != 0 || gflagChk(180) != 0) {
        scpTorchLightOn(1054);
    } else {
        torch2_2_mes[0].func = actSt04lTorch2_2Chk;
        act->mail = torch2_2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04lTorch3_1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(181) == 0) {
        torch3_1_mes[0].func = actSt04lTorch3_1Chk;
        act->mail = torch3_1_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1055);
    }
}

void actSt04lTorch3_2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(182) == 0) {
        torch3_2_mes[0].func = actSt04lTorch3_2Chk;
        act->mail = torch3_2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1056);
    }
}

void actSt04lTorch2_1XL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(177) != 0 || gflagChk(179) != 0) {
        scpTorchLightOn(977);
    } else {
        torch2_1XL_mes[0].func = actSt04lTorch2_1XLChk;
        act->mail = torch2_1XL_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04lTorch2_2XL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(178) != 0 || gflagChk(180) != 0) {
        scpTorchLightOn(978);
    } else {
        torch2_2XL_mes[0].func = actSt04lTorch2_2XLChk;
        act->mail = torch2_2XL_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04lTorch3_1XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(181) != 0) {
        scpTorchLightOn(1129);
    }
}

void actSt04lTorch3_2XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(182) != 0) {
        scpTorchLightOn(1130);
    }
}

void actSt04cDoorInit(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(138) != 0 && gflagChk(148) == 0) {
        stage_SetAnimation(199, 0, -1);
    }

    if (gflagChk(138) == 0 || gflagChk(148) != 0) {
        stage_SetAnimation(199, 0, 0);
    }
}

void actSt04dEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    Generator_Mask(scpSearchGobj(1043));

    while (gflagChk(191) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    Generator_Call(scpSearchGobj(1043));
}

void actSt04dEnemy2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);

    while (gflagChk(191) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt04dEnemy3(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);

    while (gflagChk(191) == 0) {
        _ACTWait(1);
    }

    Generator_Call(self);
}

void actSt04eSolarBeam(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(195) != 0) {
        scpFadeOut(255.0f, 0, 0, 0);

        st04eSolarBeam_mes[0].func = actSt04eSolarBeamChk;
        act->mail = st04eSolarBeam_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}
