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

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
static void actSt04eSolarBeamChkSub(GObj *volatile self);

/* .sbss: the four arguments turnBall hands to the ball-turn actor through file
   scope, the demo's own end flag, the crest-2 animation the room selects, and
   the flag the stair subthread raises once it is past its setup. */
static int turnFlag; /* derived name */

static int turnAnim; /* derived name */

static int turnGobj1; /* derived name */

static int turnGobj2; /* derived name */

static int demoEnd;

static int crest2Anim; /* derived name */

static int subStarted; /* derived name */
#endif

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec stairSubPos = {{0.0f, 0.0f, -5000.0f, 1.0f}}; /* derived name */

#ifndef VERSION_JUN26
/* .sdata: the room's stream handles and shakes (solar4l unused). */
SqEntry *ball1_4l = 0;

SqEntry *ball2_4l = 0;

SqEntry *ball3_4l = 0;
#endif

SqEntry *crest1 = 0;

SqEntry *crest2 = 0;

SqEntry *crest3 = 0;

#ifdef VERSION_JUN26
SqEntry *solar4l = 0;

SqEntry *st04d_hasi = 0;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
SqEntry *solar4l = 0;
#else
int solar4l = 0;
#endif

SqEntry *stair4d = 0;

SqEntry *st04d_hasi = 0;

SqEntry *sekizo4c = 0;

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
SqEntry *oriup4c = 0;

SqEntry *oridown4c = 0;
#else
unsigned int oriup4c = 0;

unsigned char oridown4c = 0;
#endif
#endif

unsigned int st04l_yure = 0;

unsigned char st04l_yure_vol = 0;

#ifdef VERSION_NTSC
unsigned int sekizo_4l = 0;

unsigned char sekizo_4l_vol = 0;

void actSt04cInit(void)
{
    if (gflagChk(192) == 0) {
        stage_SetAnimation(206, 0, 0);
    } else {
        stage_SetAnimation(206, 0, -1);
    }

    if (gflagChk(193) == 0) {
        stage_SetAnimation(207, 0, 0);
    } else {
        stage_SetAnimation(207, 0, -1);
    }

    if (gflagChk(194) == 0) {
        stage_SetAnimation(208, 0, 0);
    } else {
        stage_SetAnimation(208, 0, -1);
    }

    if (gflagChk(195) == 0) {
        stage_SetAnimation(209, 0, 0);
    } else {
        stage_SetAnimation(209, 0, -1);
    }

    if (gflagChk(196) == 0) {
        stage_SetAnimation(210, 0, 0);
    } else {
        stage_SetAnimation(210, 0, -1);
    }

    if (gflagChk(197) == 0) {
        stage_SetAnimation(211, 0, 0);
    } else {
        stage_SetAnimation(211, 0, -1);
    }

    if (gflagChk(198) == 0) {
        stage_SetAnimation(212, 0, 0);
    } else {
        stage_SetAnimation(212, 0, -1);
    }

    if (gflagChk(169) == 0) {
        SetWayGroupActive(1, 0);
    } else {
        SetWayGroupActive(1, 1);
    }

    if (gflagChk(163) == 0) {
        stage_SetAnimation(196, 0, 0);
    } else {
        stage_SetAnimation(196, 0, -1);
    }

    if (gflagChk(164) == 0) {
        stage_SetAnimation(197, 0, 0);
    } else {
        stage_SetAnimation(197, 0, -1);
    }
}

void actSt04dInit(void)
{
    if (gflagChk(161) == 0) {
        stage_SetAnimation(199, 0, 0);
        stage_SetAnimation(230, 0, 0);
    } else {
        stage_SetAnimation(199, 0, -1);
        stage_SetAnimation(230, 0, -1);
    }

    if (gflagChk(163) == 0) {
        stage_SetAnimation(196, 0, 0);
        SetWayGroupActive(3, 0);
    } else {
        stage_SetAnimation(196, 0, -1);
        SetWayGroupActive(3, 1);
    }

    if (gflagChk(164) == 0) {
        stage_SetAnimation(197, 0, 0);
        SetWayGroupActive(4, 0);
    } else {
        stage_SetAnimation(197, 0, -1);
        SetWayGroupActive(4, 1);
    }

    if (gflagChk(192) == 0) {
        stage_SetAnimation(206, 0, 0);
    } else {
        stage_SetAnimation(206, 0, -1);
    }

    if (gflagChk(193) == 0) {
        stage_SetAnimation(207, 0, 0);
    } else {
        stage_SetAnimation(207, 0, -1);
    }

    if (gflagChk(194) == 0) {
        stage_SetAnimation(208, 0, 0);
    } else {
        stage_SetAnimation(208, 0, -1);
    }

    if (gflagChk(195) == 0) {
        stage_SetAnimation(209, 0, 0);
    } else {
        stage_SetAnimation(209, 0, -1);
    }

    if (gflagChk(196) == 0) {
        stage_SetAnimation(210, 0, 0);
    } else {
        stage_SetAnimation(210, 0, -1);
    }

    if (gflagChk(197) == 0) {
        stage_SetAnimation(211, 0, 0);
    } else {
        stage_SetAnimation(211, 0, -1);
    }

    if (gflagChk(198) == 0) {
        stage_SetAnimation(212, 0, 0);
    } else {
        stage_SetAnimation(212, 0, -1);
    }

    if (gflagChk(145) != 0 && gflagChk(155) == 0) {
        stage_SetAnimation(225, 0, -1);
    }

    if (gflagChk(145) == 0 || gflagChk(155) != 0) {
        stage_SetAnimation(225, 0, 0);
    }

    if (gflagChk(171) != 0) {
        stage_SetAnimation(200, 0, 200);
    } else {
        stage_SetAnimation(200, 0, 0);
    }
}

void actSt04eInit(void)
{
    if (gflagChk(205) == 0) {
        SetWayGroupActive(5, 0);
    } else {
        SetWayGroupActive(5, 1);
    }

    if (gflagChk(163) == 0) {
        stage_SetAnimation(196, 0, 0);
    } else {
        stage_SetAnimation(196, 0, -1);
    }

    if (gflagChk(164) == 0) {
        stage_SetAnimation(197, 0, 0);
    } else {
        stage_SetAnimation(197, 0, -1);
    }
}

void actSt04lC1BallTurn(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(158);
    scpSleepEnemyAll();

    _ACTWait(60);

    scpAdpcmPlayRequestFunc(80, &ball1_4l, 1, 1, 1);

    while (ball1_4l == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(185, 1, 0);

    while (stage_CheckAnimationFinish(185) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpSearchGobj(1026)->active = 1;
    scpSearchGobj(1027)->active = 1;

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 6);

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt04lC2BallTurn(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(159);
    scpSleepEnemyAll();

    _ACTWait(60);

    scpAdpcmPlayRequestFunc(80, &ball2_4l, 1, 1, 1);

    while (ball2_4l == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(186, 1, 0);

    while (stage_CheckAnimationFinish(186) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpSearchGobj(1108)->active = 1;
    scpSearchGobj(1109)->active = 1;

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 6);

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt04lC3BallTurn(GObj *volatile self)
{
    lt_switch_layout(51);
    scpSleepEnemyAll();
    gflagOn(160);

    _ACTWait(60);

    scpAdpcmPlayRequestFunc(80, &ball3_4l, 1, 1, 1);

    while (ball3_4l == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(187, 1, 0);

    while (stage_CheckAnimationFinish(187) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpSearchGobj(1110)->active = 1;
    scpSearchGobj(1111)->active = 1;

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

static ActMail c1BallMain_mes[2] = {{376, actSt04lC1BallSwitch}, {396}}; /* derived name */

static ActMail c1Ball_mes[2] = {{397}, {396}}; /* derived name */

static ActMail c1BallSwitch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail c2BallMain_mes[2] = {{376, actSt04lC2BallSwitch}, {396}}; /* derived name */

static ActMail c2Ball_mes[2] = {{397}, {396}}; /* derived name */

static ActMail c2BallSwitch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail c3BallMain_mes[2] = {{377, actSt04lC3BallSwitch}, {396}}; /* derived name */

static ActMail c3Ball_mes[2] = {{397}, {396}}; /* derived name */

static ActMail c3BallSwitch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail crest01_mes[2] = {{397}, {396}}; /* derived name */

static ActMail crest02_mes[2] = {{397}, {396}}; /* derived name */

static ActMail crest03_mes[2] = {{397}, {396}}; /* derived name */

static ActMail st04eSolarBeam_mes[2] = {{397}, {396}}; /* derived name */

static ActMail stair_mes[2] = {{397}, {396}}; /* derived name */

static ActMail rope1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail rope2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail brg1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail rope3_mes[2] = {{397}, {396}}; /* derived name */

static ActMail rope4_mes[2] = {{397}, {396}}; /* derived name */

static ActMail brg2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail brg1Way_mes[2] = {{397}, {396}}; /* derived name */

static ActMail brg2Way_mes[2] = {{397}, {396}}; /* derived name */

static ActMail sekizo_mes[2] = {{397}, {396}}; /* derived name */

static ActMail turi_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondola_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondola2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondolaChk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondola_chara[2] = {{397}, {396}}; /* derived name */

static ActMail monyou01_mes[2] = {{397}, {396}}; /* derived name */

static ActMail monyou02_mes[2] = {{397}, {396}}; /* derived name */

static ActMail monyou03_mes[2] = {{397}, {396}}; /* derived name */

static ActMail monyou04_mes[2] = {{397}, {396}}; /* derived name */

static ActMail monyou05_mes[2] = {{397}, {396}}; /* derived name */

static ActMail monyou06_mes[2] = {{397}, {396}}; /* derived name */

static ActMail monyou07_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ori_mes[2] = {{397}, {396}}; /* derived name */

static ActMail oriRopeCutR_mes[2] = {{397}, {396}}; /* derived name */

static ActMail oriRopeCutL_mes[2] = {{397}, {396}}; /* derived name */

static ActMail ori2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail sword_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch1_1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch1_2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch2_1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch2_2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch3_1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch3_2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch2_1XL_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch2_2XL_mes[2] = {{397}, {396}}; /* derived name */

void actSt04lCrest02(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(156) == 0) {
        if (current_stage_no == 19) {
            stage_SetAnimation(179, 0, 0);
        } else {
            stage_SetAnimation(180, 0, 0);
        }

        crest02_mes[0].func = actSt04lCrest2Main;
        act->mail = crest02_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        if (current_stage_no == 19) {
            stage_SetAnimation(179, 0, -1);
        } else {
            stage_SetAnimation(180, 0, -1);
        }
    }
}

void actSt04lCrestMain(GObj *volatile self)
{
    while (scpIsTorchLightOn(1026) == 0 || scpIsTorchLightOn(1027) == 0 || gflagChk(158) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    fightSoundProcessRequestPause();

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(26, &crest1, 0, 1, 1);

    while (crest1 == 0) {
        _ACTWait(1);
    }

    preload(3);
    gflagOn(155);
    gflagOn(204);

    stage_SetAnimation(224, 1, 0);
    stage_SetAnimation(177, 1, 0);

    while (stage_CheckAnimationFrame(177, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    st04l_yure = iosPadActRequest(boyPad, 10);
    st04l_yure_vol = 128;
    iosPadActVolumeSet(st04l_yure, 128);

    while (stage_CheckAnimationFrame(177, 190, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(st04l_yure);

    while (stage_CheckAnimationFinish(177) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpWakeupEnemyAll();
    RequestStageChange(3, boyGObj, 0, 2.0f, 8.0f);
}

void actSt04lCrest2Main(GObj *volatile self)
{
    if (current_stage_no == 19) {
        while (scpIsTorchLightOn(1030) == 0 || scpIsTorchLightOn(1031) == 0 || gflagChk(159) == 0) {
            _ACTWait(1);
        }
    }

    if (current_stage_no == 20) {
        while (scpIsTorchLightOn(1108) == 0 || scpIsTorchLightOn(1109) == 0 || gflagChk(159) == 0) {
            _ACTWait(1);
        }
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(25, &crest2, 1, 1, 1);

    while (crest2 == 0) {
        _ACTWait(1);
    }

    gflagOn(156);

    if (current_stage_no == 19) {
        stage_SetAnimation(179, 1, 0);

        while (stage_CheckAnimationFrame(179, 30, 0) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);

        st04l_yure = iosPadActRequest(boyPad, 10);
        st04l_yure_vol = 128;
        iosPadActVolumeSet(st04l_yure, 128);

        while (stage_CheckAnimationFrame(179, 190, 0) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);
        iosPadActStop(st04l_yure);

        while (stage_CheckAnimationFinish(179) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);
        scpSearchGobj(1034)->active = 1;
    } else {
        stage_SetAnimation(180, 1, 0);

        while (stage_CheckAnimationFrame(180, 30, 0) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);

        st04l_yure = iosPadActRequest(boyPad, 10);
        st04l_yure_vol = 128;
        iosPadActVolumeSet(st04l_yure, 128);

        while (stage_CheckAnimationFrame(180, 190, 0) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);
        iosPadActStop(st04l_yure);

        while (stage_CheckAnimationFinish(180) == 0) {
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
    while (scpIsTorchLightOn(1110) == 0 || scpIsTorchLightOn(1111) == 0 || gflagChk(160) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(23, &crest3, 0, 1, 1);

    while (crest3 == 0) {
        _ACTWait(1);
    }

    gflagOn(157);
    stage_SetAnimation(181, 1, 0);

    while (stage_CheckAnimationFrame(181, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    st04l_yure = iosPadActRequest(boyPad, 10);
    st04l_yure_vol = 128;
    iosPadActVolumeSet(st04l_yure, 128);

    while (stage_CheckAnimationFrame(181, 190, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(st04l_yure);

    while (stage_CheckAnimationFinish(181) == 0) {
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
    scpSleepEnemyOne(3453);
    gflagOn(161);

    scpSearchGobj(1148)->active = 0;

    stage_SetAnimation(231, -1, -2);

    _ACTWait(60);

    scpAdpcmPlayRequestFunc(59, &stair4d, 1, 1, 1);

    while (stair4d == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(230, 1, 0);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);
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

    while (stage_CheckAnimationFinish(230) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

    stage_SetAnimation(199, 1, 0);

    while (stage_CheckAnimationFrame(199, 140, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    st04l_yure = iosPadActRequest(boyPad, 9);
    st04l_yure_vol = 128;
    iosPadActVolumeSet(st04l_yure, 128);

    while (stage_CheckAnimationFinish(199) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(st04l_yure);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
    gflagOn(200);
    scpWakeupEnemyOne(3453);
}

void actSt04lRope1Chk(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(165) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1088))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(192, 1, 0);

            while (stage_CheckAnimationFinish(192) == 0) {
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1088)->active = 0;
            gflagOn(165);
            stage_SetAnimation(188, 1, 0);

            while (stage_CheckAnimationFinish(188) == 0) {
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        }
    }
}

void actSt04lRope2Chk(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(166) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1089))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(193, 1, 0);

            while (stage_CheckAnimationFinish(193) == 0) {
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1089)->active = 0;
            gflagOn(166);
            stage_SetAnimation(189, 1, 0);

            while (stage_CheckAnimationFinish(189) == 0) {
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        }
    }
}

void actSt04lBrg1Chk(GObj *volatile self)
{
    while (gflagChk(165) == 0 || gflagChk(166) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    gflagOn(163);

    _ACTWait(60);

    scpAdpcmPlayRequestFunc(84, &st04d_hasi, 1, 1, 1);

    while (st04d_hasi == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(196, 1, 0);

    while (stage_CheckAnimationFrame(196, 75, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFinish(196) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt04lRope3Chk(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(167) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1090))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(194, 1, 0);

            while (stage_CheckAnimationFinish(194) == 0) {
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1090)->active = 0;
            gflagOn(167);
            stage_SetAnimation(190, 1, 0);

            while (stage_CheckAnimationFinish(190) == 0) {
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        }
    }
}

void actSt04lRope4Chk(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(168) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1091))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(195, 1, 0);

            while (stage_CheckAnimationFinish(195) == 0) {
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1091)->active = 0;
            gflagOn(168);
            stage_SetAnimation(191, 1, 0);

            while (stage_CheckAnimationFinish(191) == 0) {
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        }
    }
}

void actSt04lBrg2Chk(GObj *volatile self)
{
    while (gflagChk(167) == 0 || gflagChk(168) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    gflagOn(164);

    _ACTWait(60);

    scpAdpcmPlayRequestFunc(84, &st04d_hasi, 1, 1, 1);

    while (st04d_hasi == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(197, 1, 0);

    while (stage_CheckAnimationFrame(197, 75, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFinish(197) == 0) {
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

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpKillEnemyAll();
    scpMaskGeneratorAll();

    scpAdpcmPlayRequestFunc(18, &sekizo4c, 1, 1, 1);

    while (sekizo4c == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(1, 1);

    _ACTWait(60);

    stage_SetAnimation(198, 1, 0);

    sekizo_4l = iosPadActRequest(boyPad, 9);
    sekizo_4l_vol = 128;
    iosPadActVolumeSet(sekizo_4l, 128);

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);
    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);
    scpPlayPosSet(girlGObj, 0.0f, -1300.0f, -1700.0f);
    scpPlayPosSet(boyGObj, 20.0f, -1300.0f, -1700.0f);

    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT((void *)self), test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, dir);

    scpBoyControlReadDisable = 1;

    sceVu0SubVector(dir, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    scpSekizouCheckPoint();

    scpPlayMot(girlGObj, 572);
    scpPlayWaitMotEnd(girlGObj);

    gflagOn(169);

    while (stage_CheckAnimationFrame(198, 151, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(sekizo_4l);

    while (stage_CheckAnimationFinish(198) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(girlGObj, 514);
    scpPlayEnd(girlGObj);
    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);

    _ACTWait(1);
    iosOmSendMail(girlGObj, 60, boyGObj);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

void actSt04lGondolaChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttr(boyGObj, 0xA000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    _ACTWait(15);

    if (gflagChk(171) != 0) {
        stage_SetAnimation(200, 1, 200);

        while (stage_CheckAnimationFrame(200, 220, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        soundSeDefPlay(1297, 0, 0, 1);

        while (stage_CheckAnimationFrame(200, 240, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        soundSeDefPlay(1298, 0, 0, 1);

        while (stage_CheckAnimationFrame(200, 250, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        soundSeDefPlay(1295, 0, 0, 1);

        while (stage_CheckAnimationFrame(200, 415, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        soundSeDefPlay(1296, 0, 0, 1);

        while (stage_CheckAnimationFinish(200) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        gflagOff(171);
    } else {
        stage_SetAnimation(200, 1, 0);
        soundSeDefPlay(1295, 0, 0, 1);

        while (stage_CheckAnimationFrame(200, 145, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        soundSeDefPlay(1296, 0, 0, 1);
        soundSeDefPlay(1297, 0, 0, 1);

        while (stage_CheckAnimationFrame(200, 170, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        soundSeDefPlay(1298, 0, 0, 1);

        while (stage_CheckAnimationFrame(200, 200, 1) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        gflagOn(171);
    }

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
    scpWakeupEnemyAll();

    gondolaChk_mes[0].func = actSt04lGondolaCharaChk;
    sub->mail = gondolaChk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt04lMonyou01Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x1000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
    gflagOn(192);
    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(boyGObj);
        scpPlayStart(girlGObj);
        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);
        ACTGame_ConnectHand();
    }

    stage_SetAnimation(206, 1, 0);
    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(206, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(girlGObj, 60, boyGObj);
    }

    scpBoyControlReadDisable = 0;
}

void actSt04lMonyou02Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x2000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
    gflagOn(193);
    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(boyGObj);
        scpPlayStart(girlGObj);
        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);
        ACTGame_ConnectHand();
    }

    stage_SetAnimation(207, 1, 0);
    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(207, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(girlGObj, 60, boyGObj);
    }

    scpBoyControlReadDisable = 0;
}

void actSt04lMonyou03Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x3000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
    gflagOn(194);
    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(boyGObj);
        scpPlayStart(girlGObj);
        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);
        ACTGame_ConnectHand();
    }

    stage_SetAnimation(208, 1, 0);
    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(208, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(girlGObj, 60, boyGObj);
    }

    scpBoyControlReadDisable = 0;
}

void actSt04lMonyou04Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x4000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x4000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
    gflagOn(195);
    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(boyGObj);
        scpPlayStart(girlGObj);
        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);
        ACTGame_ConnectHand();
    }

    stage_SetAnimation(209, 1, 0);
    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(209, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(girlGObj, 60, boyGObj);
    }

    scpBoyControlReadDisable = 0;
}

void actSt04lMonyou05Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x5000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x5000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
    gflagOn(196);
    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(boyGObj);
        scpPlayStart(girlGObj);
        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);
        ACTGame_ConnectHand();
    }

    stage_SetAnimation(210, 1, 0);
    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(210, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(girlGObj, 60, boyGObj);
    }

    scpBoyControlReadDisable = 0;
}

void actSt04lMonyou06Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x6000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x6000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
    gflagOn(197);
    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(boyGObj);
        scpPlayStart(girlGObj);
        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);
        ACTGame_ConnectHand();
    }

    stage_SetAnimation(211, 1, 0);
    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(211, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(girlGObj, 60, boyGObj);
    }

    scpBoyControlReadDisable = 0;
}

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
    gflagOn(198);
    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(boyGObj);
        scpPlayStart(girlGObj);
        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);
        ACTGame_ConnectHand();
    }

    stage_SetAnimation(212, 1, 0);
    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(212, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(girlGObj, 60, boyGObj);
    }

    scpBoyControlReadDisable = 0;
}

void actSt04lOriChk(GObj *volatile self)
{
    while (gflagChk(156) == 0 || scpGameStat_BoyWeaponkind() != 4 ||
           scpTriggerBall(self, boyGObj, 1000.0f) == 0) {
        _ACTWait(1);
    }

    scpSleepEnemyAll();
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    scpPlayMot(boyGObj, 0);

    if (girlGObj != 0) {
        iosOmSendMail(girlGObj, 59, boyGObj);
    }

    gflagOn(180);

    _ACTWait(60);

    scpAdpcmPlayRequestFunc(60, &oriup4c, 1, 1, 1);

    while (oriup4c == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(215, 1, 0);
    stage_SetAnimation(217, 1, 0);
    stage_SetAnimation(216, 1, 0);

    while (stage_CheckAnimationFrame(215, 90, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActRequest(boyPad, 15);

    while (stage_CheckAnimationFinish(215) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt04lOriRopeCutRChk(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    while (1) {
        if (scpGameStat_BoyWeaponkind() == 4 && scpTriggerBall(self, boyGObj, 100.0f) != 0 &&
            (ForMotionViewer_GetCurrentMotion(boyGObj) == 37 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 42 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 44 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 38 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 39 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 60))
            break;
        _ACTWait(1);
    }

    gflagOn(181);

    stage_SetAnimation(218, 1, 0);
    soundSeDefPlay(1299, 0, 0, 1);

    while (stage_CheckAnimationFrame(218, 45, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    soundSeDefPlay(1300, 0, 0, 1);

    while (stage_CheckAnimationFinish(218) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
}

void actSt04lOriRopeCutLChk(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    while (1) {
        if (scpGameStat_BoyWeaponkind() == 4 && scpTriggerBall(self, boyGObj, 100.0f) != 0 &&
            (ForMotionViewer_GetCurrentMotion(boyGObj) == 37 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 42 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 44 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 38 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 39 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 60))
            break;
        _ACTWait(1);
    }

    gflagOn(182);

    stage_SetAnimation(219, 1, 0);
    soundSeDefPlay(1299, 0, 0, 1);

    while (stage_CheckAnimationFrame(219, 45, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    soundSeDefPlay(1300, 0, 0, 1);

    while (stage_CheckAnimationFinish(219) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
}

void actSt04lOri2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(183) == 0) {
        ori2_mes[0].func = actSt04lOri2Chk;
        act->mail = ori2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(215, -1, -2);
        stage_SetAnimation(217, -1, -2);
        stage_SetAnimation(216, -1, -2);
        stage_SetAnimation(220, 0, -1);
        stage_SetAnimation(219, 0, -1);
        stage_SetAnimation(218, 0, -1);
    }
}

void actSt04lOri2Chk(GObj *volatile self)
{
    while (gflagChk(181) == 0 || gflagChk(182) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    gflagOn(183);
    scpSleepEnemyAll();

    iosPadActRequest(boyPad, 17);
    _ACTWait(30);

    scpAdpcmPlayRequestFunc(61, &oridown4c, 1, 1, 1);

    while (oridown4c == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(220, 1, 0);

    while (stage_CheckAnimationFrame(220, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActRequest(boyPad, 15);

    while (stage_CheckAnimationFinish(220) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt04lCrest01(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(155) == 0) {
        stage_SetAnimation(177, 0, 0);

        crest01_mes[0].func = actSt04lCrestMain;
        act->mail = crest01_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(177, 0, -1);

        scpBoyControlReadDisable = 0;
    }
}

void actSt04lCrest03(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(157) == 0) {
        stage_SetAnimation(181, 0, 0);

        crest03_mes[0].func = actSt04lCrest3Main;
        act->mail = crest03_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(181, 0, -1);
    }
}

void actSt04lC1Ball(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(158) == 0) {
        scpSearchGobj(1026)->active = 0;
        scpSearchGobj(1027)->active = 0;

        stage_SetAnimation(185, 0, 0);

        c1Ball_mes[0].func = actSt04lC1BallMain;
        act->mail = c1Ball_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(185, 0, -1);
    }
}

void actSt04lC2Ball(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(159) == 0) {
        scpSearchGobj(1108)->active = 0;
        scpSearchGobj(1109)->active = 0;

        stage_SetAnimation(186, 0, 0);

        c2Ball_mes[0].func = actSt04lC2BallMain;
        act->mail = c2Ball_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(186, 0, -1);
    }
}

void actSt04lC3Ball(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(160) == 0) {
        scpSearchGobj(1110)->active = 0;
        scpSearchGobj(1111)->active = 0;

        stage_SetAnimation(187, 0, 0);

        c3Ball_mes[0].func = actSt04lC3BallMain;
        act->mail = c3Ball_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(187, 0, -1);
    }
}

void actSt04lStair(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(161) == 0) {
        if (girlGObj != 0) {
            stair_mes[0].func = actSt04lStairChk;
            act->mail = stair_mes;
            ACTSendMailCorrect(self, 397);
            _ACTWait(0);
        }
    } else {
        scpSearchGobj(1148)->active = 0;

        stage_SetAnimation(231, -1, -2);
    }
}

void actSt04lBrg1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(163) == 0) {
        brg1_mes[0].func = actSt04lBrg1Chk;
        act->mail = brg1_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04lBrg2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(164) == 0) {
        brg2_mes[0].func = actSt04lBrg2Chk;
        act->mail = brg2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04lBrg1Way(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(163) == 0) {
        brg1Way_mes[0].func = actSt04lBrg1WayChk;
        act->mail = brg1Way_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04lBrg2Way(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(164) == 0) {
        brg2Way_mes[0].func = actSt04lBrg2WayChk;
        act->mail = brg2Way_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04lRope1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(165) == 0) {
        stage_SetAnimation(188, 0, 0);

        rope1_mes[0].func = actSt04lRope1Chk;
        act->mail = rope1_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(188, 0, -1);

        scpSearchGobj(1088)->active = 0;
    }
}

void actSt04lRope2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(166) == 0) {
        stage_SetAnimation(189, 0, 0);

        rope2_mes[0].func = actSt04lRope2Chk;
        act->mail = rope2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(189, 0, -1);

        scpSearchGobj(1089)->active = 0;
    }
}

void actSt04lRope3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(167) == 0) {
        stage_SetAnimation(190, 0, 0);

        rope3_mes[0].func = actSt04lRope3Chk;
        act->mail = rope3_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(190, 0, -1);

        scpSearchGobj(1090)->active = 0;
    }
}

void actSt04lRope4(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(168) == 0) {
        stage_SetAnimation(191, 0, 0);

        rope4_mes[0].func = actSt04lRope4Chk;
        act->mail = rope4_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(191, 0, -1);

        scpSearchGobj(1091)->active = 0;
    }
}

void actSt04lSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(169) == 0) {
        stage_SetAnimation(198, 0, 0);

        sekizo_mes[0].func = actSt04lSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(198, 0, -1);
    }
}

void actSt04lTuri(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(170) == 0) {
        stage_SetAnimation(202, 0, 0);

        if (girlGObj != 0) {
            turi_mes[0].func = actSt04lTuriChk;
            act->mail = turi_mes;
            ACTSendMailCorrect(self, 397);
            _ACTWait(0);
        }
    } else {
        stage_SetAnimation(202, 0, -1);
    }
}

void actSt04lOri(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(180) == 0) {
        stage_SetAnimation(215, 0, 0);
        stage_SetAnimation(217, 0, 0);
        stage_SetAnimation(216, 0, 0);

        ori_mes[0].func = actSt04lOriChk;
        act->mail = ori_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04lOriRopeCutR(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(181) == 0) {
        oriRopeCutR_mes[0].func = actSt04lOriRopeCutRChk;
        act->mail = oriRopeCutR_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04lOriRopeCutL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(182) == 0) {
        oriRopeCutL_mes[0].func = actSt04lOriRopeCutLChk;
        act->mail = oriRopeCutL_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04lSword(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(156) == 0) {
        sword_mes[0].func = actSt04lSwordChk;
        act->mail = sword_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04lGondola(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(171) != 0) {
        stage_SetAnimation(200, 0, 200);

        gondola_mes[0].func = actSt04lGondolaChk;
        act->mail = gondola_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(200, 0, 0);

        gondola2_mes[0].func = actSt04lGondolaChk;
        act->mail = gondola2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04lMonyou01(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(192) == 0) {
        stage_SetAnimation(206, 0, 0);

        monyou01_mes[0].func = actSt04lMonyou01Chk;
        act->mail = monyou01_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(206, 0, -1);
    }
}

void actSt04lMonyou02(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(193) == 0) {
        stage_SetAnimation(207, 0, 0);

        monyou02_mes[0].func = actSt04lMonyou02Chk;
        act->mail = monyou02_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(207, 0, -1);
    }
}

void actSt04lMonyou03(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(194) == 0) {
        stage_SetAnimation(208, 0, 0);

        monyou03_mes[0].func = actSt04lMonyou03Chk;
        act->mail = monyou03_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(208, 0, -1);
    }
}

void actSt04lMonyou04(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(195) == 0) {
        stage_SetAnimation(209, 0, 0);

        monyou04_mes[0].func = actSt04lMonyou04Chk;
        act->mail = monyou04_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(209, 0, -1);
    }
}

void actSt04lMonyou05(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(196) == 0) {
        stage_SetAnimation(210, 0, 0);

        monyou05_mes[0].func = actSt04lMonyou05Chk;
        act->mail = monyou05_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(210, 0, -1);
    }
}

void actSt04lMonyou06(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(197) == 0) {
        stage_SetAnimation(211, 0, 0);

        monyou06_mes[0].func = actSt04lMonyou06Chk;
        act->mail = monyou06_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(211, 0, -1);
    }
}

void actSt04lMonyou07(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(198) == 0) {
        stage_SetAnimation(212, 0, 0);

        monyou07_mes[0].func = actSt04lMonyou07Chk;
        act->mail = monyou07_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(212, 0, -1);
    }
}

void actSt04lCrest01XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(155) == 0) {
        stage_SetAnimation(182, 0, 0);
    } else {
        stage_SetAnimation(182, 0, -1);
    }
}

void actSt04lCrest02XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(156) == 0) {
        stage_SetAnimation(183, 0, 0);
    } else {
        stage_SetAnimation(183, 0, -1);
    }
}

void actSt04lCrest03XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(157) == 0) {
        stage_SetAnimation(184, 0, 0);
    } else {
        stage_SetAnimation(184, 0, -1);
    }
}

void actSt04lC2BallXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(159) == 0) {
        scpSearchGobj(1030)->active = 0;
        scpSearchGobj(1031)->active = 0;

        stage_SetAnimation(186, 0, 0);
    } else {
        stage_SetAnimation(186, 0, -1);
    }
}

void actSt04lC3BallXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(160) == 0) {
        stage_SetAnimation(187, 0, 0);

        scpSearchGobj(1187)->active = 0;
        scpSearchGobj(1188)->active = 0;
    } else {
        stage_SetAnimation(187, 0, -1);
    }
}

void actSt04lTorch1_1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(184) == 0) {
        torch1_1_mes[0].func = actSt04lTorch1_1Chk;
        act->mail = torch1_1_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1026);
    }
}

void actSt04lTorch1_2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(185) == 0) {
        torch1_2_mes[0].func = actSt04lTorch1_2Chk;
        act->mail = torch1_2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1027);
    }
}

void actSt04lTorch2_1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(186) != 0 || gflagChk(188) != 0) {
        scpTorchLightOn(1108);
    } else {
        torch2_1_mes[0].func = actSt04lTorch2_1Chk;
        act->mail = torch2_1_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04lTorch2_2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(187) != 0 || gflagChk(189) != 0) {
        scpTorchLightOn(1109);
    } else {
        torch2_2_mes[0].func = actSt04lTorch2_2Chk;
        act->mail = torch2_2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04lTorch3_1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(190) == 0) {
        torch3_1_mes[0].func = actSt04lTorch3_1Chk;
        act->mail = torch3_1_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1110);
    }
}

void actSt04lTorch3_2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(191) == 0) {
        torch3_2_mes[0].func = actSt04lTorch3_2Chk;
        act->mail = torch3_2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1111);
    }
}

void actSt04lTorch2_1XL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(186) != 0 || gflagChk(188) != 0) {
        scpTorchLightOn(1030);
    } else {
        torch2_1XL_mes[0].func = actSt04lTorch2_1XLChk;
        act->mail = torch2_1XL_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04lTorch2_2XL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(187) != 0 || gflagChk(189) != 0) {
        scpTorchLightOn(1031);
    } else {
        torch2_2XL_mes[0].func = actSt04lTorch2_2XLChk;
        act->mail = torch2_2XL_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04lTorch3_1XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(190) != 0) {
        scpTorchLightOn(1187);
    }
}

void actSt04lTorch3_2XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(191) != 0) {
        scpTorchLightOn(1188);
    }
}

void actSt04cDoorInit(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(145) != 0 && gflagChk(155) == 0) {
        stage_SetAnimation(225, 0, -1);
    }

    if (gflagChk(145) == 0 || gflagChk(155) != 0) {
        stage_SetAnimation(225, 0, 0);
    }
}

void actSt04dEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
    Generator_Mask(scpSearchGobj(1098));

    while (gflagChk(200) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
    Generator_Call(scpSearchGobj(1098));
}

void actSt04dEnemy2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);

    while (gflagChk(200) == 0) {
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

    while (gflagChk(200) == 0) {
        _ACTWait(1);
    }

    Generator_Call(self);
}

void actSt04eSolarBeam(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(204) != 0) {
        if (boyGObj != 0) {
            scpPlayMot(boyGObj, 0);

            if (ACTGame_NoWeapon(boyGObj) == 0) {
                LightTorchOffOfWeapon(GetBoyWeaponGObj());
            }
        }

        gflagOn(356);

        scpSeEnvMasterVolRate = 0.0f;
        scpFadeOut(255.0f, 0, 0, 0);

        st04eSolarBeam_mes[0].func = actSt04eSolarBeamChk;
        act->mail = st04eSolarBeam_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}
#else
#ifdef VERSION_AUG6
int sekizo_4l = 0;

unsigned char sekizo_4l_vol = 0;

void actSt04cInit(void)
{
    if (gflagChk(192) == 0) {
        stage_SetAnimation(205, 0, 0);
    } else {
        stage_SetAnimation(205, 0, -1);
    }

    if (gflagChk(193) == 0) {
        stage_SetAnimation(206, 0, 0);
    } else {
        stage_SetAnimation(206, 0, -1);
    }

    if (gflagChk(194) == 0) {
        stage_SetAnimation(207, 0, 0);
    } else {
        stage_SetAnimation(207, 0, -1);
    }

    if (gflagChk(195) == 0) {
        stage_SetAnimation(208, 0, 0);
    } else {
        stage_SetAnimation(208, 0, -1);
    }

    if (gflagChk(196) == 0) {
        stage_SetAnimation(209, 0, 0);
    } else {
        stage_SetAnimation(209, 0, -1);
    }

    if (gflagChk(197) == 0) {
        stage_SetAnimation(210, 0, 0);
    } else {
        stage_SetAnimation(210, 0, -1);
    }

    if (gflagChk(198) == 0) {
        stage_SetAnimation(211, 0, 0);
    } else {
        stage_SetAnimation(211, 0, -1);
    }

    if (gflagChk(169) == 0) {
        SetWayGroupActive(1, 0);
    } else {
        SetWayGroupActive(1, 1);
    }

    if (gflagChk(163) == 0) {
        stage_SetAnimation(195, 0, 0);
    } else {
        stage_SetAnimation(195, 0, -1);
    }

    if (gflagChk(164) == 0) {
        stage_SetAnimation(196, 0, 0);
    } else {
        stage_SetAnimation(196, 0, -1);
    }
}

void actSt04dInit(void)
{
    if (gflagChk(161) == 0) {
        stage_SetAnimation(198, 0, 0);
        stage_SetAnimation(229, 0, 0);
    } else {
        stage_SetAnimation(198, 0, -1);
        stage_SetAnimation(229, 0, -1);
    }

    if (gflagChk(163) == 0) {
        stage_SetAnimation(195, 0, 0);
        SetWayGroupActive(3, 0);
    } else {
        stage_SetAnimation(195, 0, -1);
        SetWayGroupActive(3, 1);
    }

    if (gflagChk(164) == 0) {
        stage_SetAnimation(196, 0, 0);
        SetWayGroupActive(4, 0);
    } else {
        stage_SetAnimation(196, 0, -1);
        SetWayGroupActive(4, 1);
    }

    if (gflagChk(192) == 0) {
        stage_SetAnimation(205, 0, 0);
    } else {
        stage_SetAnimation(205, 0, -1);
    }

    if (gflagChk(193) == 0) {
        stage_SetAnimation(206, 0, 0);
    } else {
        stage_SetAnimation(206, 0, -1);
    }

    if (gflagChk(194) == 0) {
        stage_SetAnimation(207, 0, 0);
    } else {
        stage_SetAnimation(207, 0, -1);
    }

    if (gflagChk(195) == 0) {
        stage_SetAnimation(208, 0, 0);
    } else {
        stage_SetAnimation(208, 0, -1);
    }

    if (gflagChk(196) == 0) {
        stage_SetAnimation(209, 0, 0);
    } else {
        stage_SetAnimation(209, 0, -1);
    }

    if (gflagChk(197) == 0) {
        stage_SetAnimation(210, 0, 0);
    } else {
        stage_SetAnimation(210, 0, -1);
    }

    if (gflagChk(198) == 0) {
        stage_SetAnimation(211, 0, 0);
    } else {
        stage_SetAnimation(211, 0, -1);
    }

    if (gflagChk(145) != 0 && gflagChk(155) == 0) {
        stage_SetAnimation(224, 0, -1);
    }

    if (gflagChk(145) == 0 || gflagChk(155) != 0) {
        stage_SetAnimation(224, 0, 0);
    }

    if (gflagChk(171) != 0) {
        stage_SetAnimation(199, 0, 200);
    } else {
        stage_SetAnimation(199, 0, 0);
    }
}

void actSt04eInit(void)
{
    if (gflagChk(205) == 0) {
        SetWayGroupActive(5, 0);
    } else {
        SetWayGroupActive(5, 1);
    }

    if (gflagChk(163) == 0) {
        stage_SetAnimation(195, 0, 0);
    } else {
        stage_SetAnimation(195, 0, -1);
    }

    if (gflagChk(164) == 0) {
        stage_SetAnimation(196, 0, 0);
    } else {
        stage_SetAnimation(196, 0, -1);
    }
}
#else
#ifdef VERSION_JUN26
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
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
void actSt04cInit(void)
{
    if (gflagChk(212) == 0) {
        stage_SetAnimation(230, 0, 0);
    } else {
        stage_SetAnimation(230, 0, -1);
    }

    if (gflagChk(213) == 0) {
        stage_SetAnimation(231, 0, 0);
    } else {
        stage_SetAnimation(231, 0, -1);
    }

    if (gflagChk(214) == 0) {
        stage_SetAnimation(232, 0, 0);
    } else {
        stage_SetAnimation(232, 0, -1);
    }

    if (gflagChk(215) == 0) {
        stage_SetAnimation(233, 0, 0);
    } else {
        stage_SetAnimation(233, 0, -1);
    }

    if (gflagChk(216) == 0) {
        stage_SetAnimation(234, 0, 0);
    } else {
        stage_SetAnimation(234, 0, -1);
    }

    if (gflagChk(217) == 0) {
        stage_SetAnimation(235, 0, 0);
    } else {
        stage_SetAnimation(235, 0, -1);
    }

    if (gflagChk(218) == 0) {
        stage_SetAnimation(236, 0, 0);
    } else {
        stage_SetAnimation(236, 0, -1);
    }

    if (gflagChk(188) == 0) {
        SetWayGroupActive(1, 0);
    } else {
        SetWayGroupActive(1, 1);
    }

    if (gflagChk(182) == 0) {
        stage_SetAnimation(220, 0, 0);
    } else {
        stage_SetAnimation(220, 0, -1);
    }

    if (gflagChk(183) == 0) {
        stage_SetAnimation(221, 0, 0);
    } else {
        stage_SetAnimation(221, 0, -1);
    }
}
#else
void actSt04cInit(void)
{
    if (gflagChk(212) == 0) {
        stage_SetAnimation(234, 0, 0);
    } else {
        stage_SetAnimation(234, 0, -1);
    }

    if (gflagChk(213) == 0) {
        stage_SetAnimation(235, 0, 0);
    } else {
        stage_SetAnimation(235, 0, -1);
    }

    if (gflagChk(214) == 0) {
        stage_SetAnimation(236, 0, 0);
    } else {
        stage_SetAnimation(236, 0, -1);
    }

    if (gflagChk(215) == 0) {
        stage_SetAnimation(237, 0, 0);
    } else {
        stage_SetAnimation(237, 0, -1);
    }

    if (gflagChk(216) == 0) {
        stage_SetAnimation(238, 0, 0);
    } else {
        stage_SetAnimation(238, 0, -1);
    }

    if (gflagChk(217) == 0) {
        stage_SetAnimation(239, 0, 0);
    } else {
        stage_SetAnimation(239, 0, -1);
    }

    if (gflagChk(218) == 0) {
        stage_SetAnimation(240, 0, 0);
    } else {
        stage_SetAnimation(240, 0, -1);
    }

    if (gflagChk(188) == 0) {
        SetWayGroupActive(1, 0);
    } else {
        SetWayGroupActive(1, 1);
    }

    if (gflagChk(182) == 0) {
        stage_SetAnimation(224, 0, 0);
    } else {
        stage_SetAnimation(224, 0, -1);
    }

    if (gflagChk(183) == 0) {
        stage_SetAnimation(225, 0, 0);
    } else {
        stage_SetAnimation(225, 0, -1);
    }
}
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
void actSt04dInit(void)
{
    if (gflagChk(180) == 0) {
        stage_SetAnimation(223, 0, 0);
        stage_SetAnimation(254, 0, 0);
    } else {
        stage_SetAnimation(223, 0, -1);
        stage_SetAnimation(254, 0, -1);
        FinishHint(17);
    }

    if (gflagChk(182) == 0) {
        stage_SetAnimation(220, 0, 0);
        SetWayGroupActive(3, 0);
    } else {
        stage_SetAnimation(220, 0, -1);
        SetWayGroupActive(3, 1);
    }

    if (gflagChk(183) == 0) {
        stage_SetAnimation(221, 0, 0);
        SetWayGroupActive(4, 0);
    } else {
        stage_SetAnimation(221, 0, -1);
        SetWayGroupActive(4, 1);
    }

    if (gflagChk(212) == 0) {
        stage_SetAnimation(230, 0, 0);
    } else {
        stage_SetAnimation(230, 0, -1);
    }

    if (gflagChk(213) == 0) {
        stage_SetAnimation(231, 0, 0);
    } else {
        stage_SetAnimation(231, 0, -1);
    }

    if (gflagChk(214) == 0) {
        stage_SetAnimation(232, 0, 0);
    } else {
        stage_SetAnimation(232, 0, -1);
    }

    if (gflagChk(215) == 0) {
        stage_SetAnimation(233, 0, 0);
    } else {
        stage_SetAnimation(233, 0, -1);
    }

    if (gflagChk(216) == 0) {
        stage_SetAnimation(234, 0, 0);
    } else {
        stage_SetAnimation(234, 0, -1);
    }

    if (gflagChk(217) == 0) {
        stage_SetAnimation(235, 0, 0);
    } else {
        stage_SetAnimation(235, 0, -1);
    }

    if (gflagChk(218) == 0) {
        stage_SetAnimation(236, 0, 0);
    } else {
        stage_SetAnimation(236, 0, -1);
    }

    if (gflagChk(162) != 0 && gflagChk(174) == 0) {
        stage_SetAnimation(249, 0, -1);
    }

    if (gflagChk(162) == 0 || gflagChk(174) != 0) {
        stage_SetAnimation(249, 0, 0);
    }

    if (gflagChk(190) != 0) {
        stage_SetAnimation(224, 0, 200);
    } else {
        stage_SetAnimation(224, 0, 0);
    }
}
#else
void actSt04dInit(void)
{
    if (gflagChk(180) == 0) {
        stage_SetAnimation(227, 0, 0);
        stage_SetAnimation(258, 0, 0);
    } else {
        stage_SetAnimation(227, 0, -1);
        stage_SetAnimation(258, 0, -1);
        FinishHint(17);
    }

    if (gflagChk(182) == 0) {
        stage_SetAnimation(224, 0, 0);
        SetWayGroupActive(3, 0);
    } else {
        stage_SetAnimation(224, 0, -1);
        SetWayGroupActive(3, 1);
    }

    if (gflagChk(183) == 0) {
        stage_SetAnimation(225, 0, 0);
        SetWayGroupActive(4, 0);
    } else {
        stage_SetAnimation(225, 0, -1);
        SetWayGroupActive(4, 1);
    }

    if (gflagChk(212) == 0) {
        stage_SetAnimation(234, 0, 0);
    } else {
        stage_SetAnimation(234, 0, -1);
    }

    if (gflagChk(213) == 0) {
        stage_SetAnimation(235, 0, 0);
    } else {
        stage_SetAnimation(235, 0, -1);
    }

    if (gflagChk(214) == 0) {
        stage_SetAnimation(236, 0, 0);
    } else {
        stage_SetAnimation(236, 0, -1);
    }

    if (gflagChk(215) == 0) {
        stage_SetAnimation(237, 0, 0);
    } else {
        stage_SetAnimation(237, 0, -1);
    }

    if (gflagChk(216) == 0) {
        stage_SetAnimation(238, 0, 0);
    } else {
        stage_SetAnimation(238, 0, -1);
    }

    if (gflagChk(217) == 0) {
        stage_SetAnimation(239, 0, 0);
    } else {
        stage_SetAnimation(239, 0, -1);
    }

    if (gflagChk(218) == 0) {
        stage_SetAnimation(240, 0, 0);
    } else {
        stage_SetAnimation(240, 0, -1);
    }

    if (gflagChk(162) != 0 && gflagChk(174) == 0) {
        stage_SetAnimation(253, 0, -1);
    }

    if (gflagChk(162) == 0 || gflagChk(174) != 0) {
        stage_SetAnimation(253, 0, 0);
    }

    if (gflagChk(190) != 0) {
        stage_SetAnimation(228, 0, 200);
    } else {
        stage_SetAnimation(228, 0, 0);
    }
}
#endif

void actSt04eInit(void)
{
    if (gflagChk(230) == 0) {
        SetWayGroupActive(5, 0);
    } else {
        SetWayGroupActive(5, 1);
    }

    if (gflagChk(182) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(220, 0, 0);
#else
        stage_SetAnimation(224, 0, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(220, 0, -1);
#else
        stage_SetAnimation(224, 0, -1);
#endif
    }

    if (gflagChk(183) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(221, 0, 0);
#else
        stage_SetAnimation(225, 0, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(221, 0, -1);
#else
        stage_SetAnimation(225, 0, -1);
#endif
    }
}
#endif
#endif

#ifdef VERSION_AUG6
static ActMail c1BallMain_mes[2] = {{372, actSt04lC1BallSwitch}, {392}}; /* derived name */

static ActMail c1Ball_mes[2] = {{393}, {392}}; /* derived name */

static ActMail c1BallSwitch_mes[2] = {{393}, {392}}; /* derived name */

static ActMail c2BallMain_mes[2] = {{372, actSt04lC2BallSwitch}, {392}}; /* derived name */

static ActMail c2Ball_mes[2] = {{393}, {392}}; /* derived name */

static ActMail c2BallSwitch_mes[2] = {{393}, {392}}; /* derived name */

static ActMail c3BallMain_mes[2] = {{373, actSt04lC3BallSwitch}, {392}}; /* derived name */

static ActMail c3Ball_mes[2] = {{393}, {392}}; /* derived name */

static ActMail c3BallSwitch_mes[2] = {{393}, {392}}; /* derived name */

static ActMail crest01_mes[2] = {{393}, {392}}; /* derived name */

static ActMail crest02_mes[2] = {{393}, {392}}; /* derived name */

static ActMail crest03_mes[2] = {{393}, {392}}; /* derived name */

static ActMail st04eSolarBeam_mes[2] = {{393}, {392}}; /* derived name */

static ActMail stair_mes[2] = {{393}, {392}}; /* derived name */

static ActMail rope1_mes[2] = {{393}, {392}}; /* derived name */

static ActMail rope2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail brg1_mes[2] = {{393}, {392}}; /* derived name */

static ActMail rope3_mes[2] = {{393}, {392}}; /* derived name */

static ActMail rope4_mes[2] = {{393}, {392}}; /* derived name */

static ActMail brg2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail brg1Way_mes[2] = {{393}, {392}}; /* derived name */

static ActMail brg2Way_mes[2] = {{393}, {392}}; /* derived name */

static ActMail sekizo_mes[2] = {{393}, {392}}; /* derived name */

static ActMail turi_mes[2] = {{393}, {392}}; /* derived name */

static ActMail gondola_mes[2] = {{393}, {392}}; /* derived name */

static ActMail gondola2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail gondolaChk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail gondola_chara[2] = {{393}, {392}}; /* derived name */

static ActMail monyou01_mes[2] = {{393}, {392}}; /* derived name */

static ActMail monyou02_mes[2] = {{393}, {392}}; /* derived name */

static ActMail monyou03_mes[2] = {{393}, {392}}; /* derived name */

static ActMail monyou04_mes[2] = {{393}, {392}}; /* derived name */

static ActMail monyou05_mes[2] = {{393}, {392}}; /* derived name */

static ActMail monyou06_mes[2] = {{393}, {392}}; /* derived name */

static ActMail monyou07_mes[2] = {{393}, {392}}; /* derived name */

static ActMail ori_mes[2] = {{393}, {392}}; /* derived name */

static ActMail oriRopeCutR_mes[2] = {{393}, {392}}; /* derived name */

static ActMail oriRopeCutL_mes[2] = {{393}, {392}}; /* derived name */

static ActMail ori2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail sword_mes[2] = {{393}, {392}}; /* derived name */

static ActMail torch1_1_mes[2] = {{393}, {392}}; /* derived name */

static ActMail torch1_2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail torch2_1_mes[2] = {{393}, {392}}; /* derived name */

static ActMail torch2_2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail torch3_1_mes[2] = {{393}, {392}}; /* derived name */

static ActMail torch3_2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail torch2_1XL_mes[2] = {{393}, {392}}; /* derived name */

static ActMail torch2_2XL_mes[2] = {{393}, {392}}; /* derived name */

void actSt04lC1BallTurn(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(158);
    scpSleepEnemyAll();

    _ACTWait(60);

    scpAdpcmPlayRequestFunc(80, &ball1_4l, 1, 1, 1);

    while (ball1_4l == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(184, 1, 0);

    while (stage_CheckAnimationFinish(184) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpSearchGobj(1023)->active = 1;
    scpSearchGobj(1024)->active = 1;

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 6);

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt04lC2BallTurn(GObj *volatile self)
{
    lt_switch_layout(51);
    gflagOn(159);
    scpSleepEnemyAll();

    _ACTWait(60);

    scpAdpcmPlayRequestFunc(80, &ball2_4l, 1, 1, 1);

    while (ball2_4l == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(185, 1, 0);

    while (stage_CheckAnimationFinish(185) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpSearchGobj(1105)->active = 1;
    scpSearchGobj(1106)->active = 1;

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 6);

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt04lC3BallTurn(GObj *volatile self)
{
    lt_switch_layout(51);
    scpSleepEnemyAll();
    gflagOn(160);

    _ACTWait(60);

    scpAdpcmPlayRequestFunc(80, &ball3_4l, 1, 1, 1);

    while (ball3_4l == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(186, 1, 0);

    while (stage_CheckAnimationFinish(186) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpSearchGobj(1107)->active = 1;
    scpSearchGobj(1108)->active = 1;

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}
#else
#ifdef VERSION_JUN26
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
#else
static void actSt04lBallTurnCommonSub(GObj *volatile self)
{
    _ACTWait(60);

    scpAdpcmPlayRequestFunc(82, &ball1_4l, 1, 1, 1);

    while (ball1_4l == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(turnAnim, 1, 0);

    while (stage_CheckAnimationFinish(turnAnim) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 6);

    demoEnd = 1;
    _ACTWait(0);
}

static void actSt04lBallTurnCommon(GObj *volatile self)
{
    GProc *h;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    gflagOn(turnFlag);
    scpSleepEnemyAll();

    h = actCreateSubThread(actSt04lBallTurnCommonSub, 21);

    demoEnd = 0;
    ball1_4l = (SqEntry *)0xFFFFFFFF;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&h->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (ball1_4l == 0) {
            _ACTWait(1);
        }

        if (ball1_4l != (SqEntry *)0xFFFFFFFF) {
            scpAdpcmFadeCloseFunc(&ball1_4l, 512);
        }

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(turnAnim, 0, -1);
        scpFadeIn(5.0f);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    scpSearchGobj(turnGobj1)->active = 1;
    scpSearchGobj(turnGobj2)->active = 1;
    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
}

static ActMail c1BallMain_mes[2] = {{406, actSt04lC1BallSwitch}, {429}}; /* derived name */

static ActMail c1Ball_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c1BallSwitch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c1BallTurn_mes[2] = {{430}, {429}}; /* derived name */

static ActMail turnBall_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c2BallMain_mes[2] = {{406, actSt04lC2BallSwitch}, {429}}; /* derived name */

static ActMail c2Ball_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c2BallSwitch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c2BallTurn_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c3BallMain_mes[2] = {{407, actSt04lC3BallSwitch}, {429}}; /* derived name */

static ActMail c3Ball_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c3BallSwitch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c3BallTurn_mes[2] = {{430}, {429}}; /* derived name */

static ActMail crest01_mes[2] = {{430}, {429}}; /* derived name */

static ActMail crest02_mes[2] = {{430}, {429}}; /* derived name */

static ActMail crest03_mes[2] = {{430}, {429}}; /* derived name */

static ActMail st04eSolarBeam_mes[2] = {{430}, {429}}; /* derived name */

static ActMail stair_mes[2] = {{430}, {429}}; /* derived name */

static ActMail rope1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail rope2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg1Chk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail rope3_mes[2] = {{430}, {429}}; /* derived name */

static ActMail rope4_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg2Chk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg1Way_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg2Way_mes[2] = {{430}, {429}}; /* derived name */

static ActMail sekizo_mes[2] = {{430}, {429}}; /* derived name */

static ActMail turi_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondola_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondola2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondolaChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondola_chara[2] = {{430}, {429}}; /* derived name */

static ActMail monyou01_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou02_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou03_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou04_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou05_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou06_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou07_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ori_mes[2] = {{430}, {429}}; /* derived name */

static ActMail oriRopeCutR_mes[2] = {{430}, {429}}; /* derived name */

static ActMail oriRopeCutL_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ori2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail sword_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch1_1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch1_2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch2_1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch2_2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch3_1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch3_2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch2_1XL_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch2_2XL_mes[2] = {{430}, {429}}; /* derived name */

void turnBall(GObj *self, int flag, int anim, int gobj1, int gobj2)
{
    Act *sub = GOBJ_ACT(self);

    turnFlag = flag;
    turnAnim = anim;
    turnGobj1 = gobj1;
    turnGobj2 = gobj2;

    turnBall_mes[0].func = actSt04lBallTurnCommon;
    sub->mail = turnBall_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}
#endif
#endif

void actSt04lCrest02(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(156) == 0) {
        if (current_stage_no == 19) {
            stage_SetAnimation(178, 0, 0);
        } else {
            stage_SetAnimation(179, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(149) == 0) {
        if (current_stage_no == 19) {
            stage_SetAnimation(162, 0, 0);
        } else {
            stage_SetAnimation(163, 0, 0);
#else
    if (gflagChk(175) == 0) {
        if (current_stage_no == 19) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            stage_SetAnimation(197, 0, 0);
#else
            stage_SetAnimation(201, 0, 0);
#endif
        } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            stage_SetAnimation(198, 0, 0);
#else
            stage_SetAnimation(202, 0, 0);
#endif
#endif
#endif
        }

        crest02_mes[0].func = actSt04lCrest2Main;
        act->mail = crest02_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
#else
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    } else {
        if (current_stage_no == 19) {
#ifdef VERSION_AUG6
            stage_SetAnimation(178, 0, -1);
        } else {
            stage_SetAnimation(179, 0, -1);
#else
#ifdef VERSION_JUN26
            stage_SetAnimation(162, 0, -1);
        } else {
            stage_SetAnimation(163, 0, -1);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            stage_SetAnimation(197, 0, -1);
#else
            stage_SetAnimation(201, 0, -1);
#endif
        } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            stage_SetAnimation(198, 0, -1);
#else
            stage_SetAnimation(202, 0, -1);
#endif
#endif
#endif
        }
    }
}

#ifdef VERSION_JUN26
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
#else
#ifdef VERSION_AUG6
void actSt04lCrestMain(GObj *volatile self)
{
    while (scpIsTorchLightOn(1023) == 0 || scpIsTorchLightOn(1024) == 0 || gflagChk(158) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    fightSoundProcessRequestPause();

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(26, &crest1, 0, 1, 1);

    while (crest1 == 0) {
        _ACTWait(1);
    }

    preload(3);
    gflagOn(155);
    gflagOn(204);

    stage_SetAnimation(223, 1, 0);
    stage_SetAnimation(176, 1, 0);

    while (stage_CheckAnimationFrame(176, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    st04l_yure = iosPadActRequest(boyPad, 10);
    st04l_yure_vol = 128;
    iosPadActVolumeSet(st04l_yure, 128);

    while (stage_CheckAnimationFrame(176, 190, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(st04l_yure);

    while (stage_CheckAnimationFinish(176) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpWakeupEnemyAll();
    RequestStageChange(3, boyGObj, girlGObj, 2.0f, 8.0f);
}

void actSt04lCrest2Main(GObj *volatile self)
{
    if (current_stage_no == 19) {
        while (scpIsTorchLightOn(1027) == 0 || scpIsTorchLightOn(1028) == 0 || gflagChk(159) == 0) {
            _ACTWait(1);
        }
    }

    if (current_stage_no == 20) {
        while (scpIsTorchLightOn(1105) == 0 || scpIsTorchLightOn(1106) == 0 || gflagChk(159) == 0) {
            _ACTWait(1);
        }
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(25, &crest2, 1, 1, 1);

    while (crest2 == 0) {
        _ACTWait(1);
    }

    gflagOn(156);

    if (current_stage_no == 19) {
        stage_SetAnimation(178, 1, 0);

        while (stage_CheckAnimationFrame(178, 30, 0) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);

        st04l_yure = iosPadActRequest(boyPad, 10);
        st04l_yure_vol = 128;
        iosPadActVolumeSet(st04l_yure, 128);

        while (stage_CheckAnimationFrame(178, 190, 0) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);
        iosPadActStop(st04l_yure);

        while (stage_CheckAnimationFinish(178) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);
        scpSearchGobj(1031)->active = 1;
    } else {
        stage_SetAnimation(179, 1, 0);

        while (stage_CheckAnimationFrame(179, 30, 0) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);

        st04l_yure = iosPadActRequest(boyPad, 10);
        st04l_yure_vol = 128;
        iosPadActVolumeSet(st04l_yure, 128);

        while (stage_CheckAnimationFrame(179, 190, 0) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);
        iosPadActStop(st04l_yure);

        while (stage_CheckAnimationFinish(179) == 0) {
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
    while (scpIsTorchLightOn(1107) == 0 || scpIsTorchLightOn(1108) == 0 || gflagChk(160) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(23, &crest3, 0, 1, 1);

    while (crest3 == 0) {
        _ACTWait(1);
    }

    gflagOn(157);
    stage_SetAnimation(180, 1, 0);

    while (stage_CheckAnimationFrame(180, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    st04l_yure = iosPadActRequest(boyPad, 10);
    st04l_yure_vol = 128;
    iosPadActVolumeSet(st04l_yure, 128);

    while (stage_CheckAnimationFrame(180, 190, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(st04l_yure);

    while (stage_CheckAnimationFinish(180) == 0) {
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
    scpSleepEnemyOne(3415);
    gflagOn(161);

    scpSearchGobj(1145)->active = 0;

    stage_SetAnimation(230, -1, -2);

    _ACTWait(60);

    scpAdpcmPlayRequestFunc(59, &stair4d, 1, 1, 1);

    while (stair4d == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(229, 1, 0);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);
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

    while (stage_CheckAnimationFinish(229) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

    stage_SetAnimation(198, 1, 0);

    while (stage_CheckAnimationFrame(198, 140, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    st04l_yure = iosPadActRequest(boyPad, 9);
    st04l_yure_vol = 128;
    iosPadActVolumeSet(st04l_yure, 128);

    while (stage_CheckAnimationFinish(198) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(st04l_yure);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
    gflagOn(200);
    scpWakeupEnemyOne(3415);
}
#else
static void actSt04lCrestSub(GObj *volatile self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(248, 1, 0);
    stage_SetAnimation(195, 1, 0);
#else
    stage_SetAnimation(252, 1, 0);
    stage_SetAnimation(199, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(195, 30, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(199, 30, 0) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);

    oriup4c = iosPadActRequest(boyPad, 10);
    oridown4c = 128;
    iosPadActVolumeSet(oriup4c, 128);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(195, 190, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(199, 190, 0) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(oriup4c);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(195) == 0) {
#else
    while (stage_CheckAnimationFinish(199) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt04lCrestMain(GObj *volatile self)
{
    GProc *h;

    while (scpIsTorchLightOn(1114) == 0 || scpIsTorchLightOn(1115) == 0 || gflagChk(177) == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    fightSoundProcessRequestPause();

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(27, &ball2_4l, 0, 1, 1);

    while (ball2_4l == 0) {
        _ACTWait(1);
    }

    preload(3);
    gflagOn(174);
    gflagOn(224);

    h = actCreateSubThread(actSt04lCrestSub, 21);

    demoEnd = 0;
    oriup4c = 0xFFFFFFFF;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&h->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&ball2_4l, 256);
        iosPadActStop(oriup4c);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(248, 0, -1);
        stage_SetAnimation(195, 0, -1);
#else
        stage_SetAnimation(252, 0, -1);
        stage_SetAnimation(199, 0, -1);
#endif
        scpFadeIn(3.0f);
    }

    scpWakeupEnemyAll();
    RequestStageChange(3, boyGObj, 0, 2.0f, 8.0f);
}

static void actSt04lCrest2Sub(GObj *volatile self)
{
    stage_SetAnimation(crest2Anim, 1, 0);

    while (stage_CheckAnimationFrame(crest2Anim, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    oriup4c = iosPadActRequest(boyPad, 10);
    oridown4c = 128;
    iosPadActVolumeSet(oriup4c, 128);

    while (stage_CheckAnimationFrame(crest2Anim, 190, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(oriup4c);
    oriup4c = 0xFFFFFFFF;

    while (stage_CheckAnimationFinish(crest2Anim) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    if (current_stage_no == 19) {
        scpSearchGobj(1122)->active = 1;
    }

    demoEnd = 1;
    _ACTWait(0);
}

void actSt04lCrest2Main(GObj *volatile self)
{
    GProc *h;

    if (current_stage_no == 19) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        crest2Anim = 197;
#else
        crest2Anim = 201;
#endif

        while (scpIsTorchLightOn(1118) == 0 || scpIsTorchLightOn(1119) == 0 || gflagChk(178) == 0) {
            _ACTWait(1);
        }
    }

    if (current_stage_no == 20) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        crest2Anim = 198;
#else
        crest2Anim = 202;
#endif

        while (scpIsTorchLightOn(1202) == 0 || scpIsTorchLightOn(1203) == 0 || gflagChk(178) == 0) {
            _ACTWait(1);
        }
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(26, &ball3_4l, 1, 1, 1);

    while (ball3_4l == 0) {
        _ACTWait(1);
    }

    gflagOn(175);

    h = actCreateSubThread(actSt04lCrest2Sub, 21);

    demoEnd = 0;
    oriup4c = 0xFFFFFFFF;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&h->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&ball3_4l, 256);
        iosPadActStop(oriup4c);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(crest2Anim, 0, -1);

        if (current_stage_no == 19) {
            scpSearchGobj(1122)->active = 1;
        }

        SetCameraFlag_LwsCutBack();
        scpFadeIn(3.0f);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
}

static void actSt04lCrest3Sub(GObj *volatile self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(199, 30, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(203, 30, 0) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);

    oriup4c = iosPadActRequest(boyPad, 10);
    oridown4c = 128;
    iosPadActVolumeSet(oriup4c, 128);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(199, 190, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(203, 190, 0) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(oriup4c);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(199) == 0) {
#else
    while (stage_CheckAnimationFinish(203) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt04lCrest3Main(GObj *volatile self)
{
    GProc *h;

    while (scpIsTorchLightOn(1204) == 0 || scpIsTorchLightOn(1205) == 0 || gflagChk(179) == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(24, &crest1, 0, 1, 1);

    while (crest1 == 0) {
        _ACTWait(1);
    }

    gflagOn(176);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(199, 1, 0);
#else
    stage_SetAnimation(203, 1, 0);
#endif

    h = actCreateSubThread(actSt04lCrest3Sub, 21);

    demoEnd = 0;
    oriup4c = 0xFFFFFFFF;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&h->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&crest1, 256);
        iosPadActStop(oriup4c);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(199, 0, -1);
#else
        stage_SetAnimation(203, 0, -1);
#endif
        scpFadeIn(3.0f);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
}

void actSt04eSolarBeamChk(GObj *volatile self)
{
    GProc *h;

    gflagOff(224);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;

    scpAdpcmPlayRequestFunc(28, &crest2, 0, 1, 1);

    while (crest2 == 0) {
        _ACTWait(1);
    }

    preload(7);
    scpFadeIn(16.0f);

    h = actCreateSubThread(actSt04eSolarBeamChkSub, 21);

    demoEnd = 0;

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&h->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&crest2, 256);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(288, 0, -1);
#else
        stage_SetAnimation(292, 0, -1);
#endif
        scpFadeIn(3.0f);
    }

    RequestStageChange(7, boyGObj, 0, 2.0f, 8.0f);
}

static void actSt04lStairSub(GObj *volatile self)
{
    long long ofs[2];
    float dir[4];

    _ACTWait(60);

    while (crest3 == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(crest3->stream);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(254, 1, 0);
#else
    stage_SetAnimation(258, 1, 0);
#endif

#if !defined(VERSION_JPN) && !defined(VERSION_KOR) && !defined(VERSION_CN)
    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);
#endif
    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 532);
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

    subStarted = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(254) == 0) {
#else
    while (stage_CheckAnimationFinish(258) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(223, 1, 0);
#else
    stage_SetAnimation(227, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(223, 140, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(227, 140, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    oriup4c = iosPadActRequest(boyPad, 9);
    oridown4c = 128;
    iosPadActVolumeSet(oriup4c, 128);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(223) == 0) {
#else
    while (stage_CheckAnimationFinish(227) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt04lStairChk(GObj *volatile self)
{
    GProc *h;

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0xB000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0xB000000) == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);
    scpSleepEnemyOne(3734);
#else
    scpSleepEnemyOne(3757);
#endif
    gflagOn(180);
    FinishHint(17);

    scpSearchGobj(1242)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(255, -1, -2);
#else
    stage_SetAnimation(259, -1, -2);
#endif

    scpAdpcmPlayRequestFunc(61, &crest3, 1, 1, 0);

    h = actCreateSubThread(actSt04lStairSub, 21);

    demoEnd = 0;
    subStarted = 0;
    oriup4c = 0xFFFFFFFF;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (crest3 == 0) {
            _ACTWait(1);
        }

        scpAdpcmFadeCloseFunc(&crest3, 512);

        while (subStarted == 0) {
            _ACTWait(1);
        }

        iosThreadSetPri(&h->thread, 34);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(254, 0, -1);
        stage_SetAnimation(223, 0, -1);
#else
        stage_SetAnimation(258, 0, -1);
        stage_SetAnimation(227, 0, -1);
#endif

        _ACTWait(1);

        scpPlayMot(boyGObj, 0);
        scpPlayMot(girlGObj, 532);
        scpPlayPosSet(boyGObj, 55.0f, 234.0f, -3881.0f);
        scpPlayPosSet(girlGObj, -58.0f, 234.0f, -3891.0f);

        _ACTWait(1);
        iosOmSendMail(girlGObj, 62, boyGObj);

        scpFadeIn(3.0f);
    } else {
        iosThreadSetPri(&h->thread, 34);
    }

    iosPadActStop(oriup4c);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 532);
    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);

    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    gflagOn(220);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    scpWakeupEnemyOne(3734);
#else
    scpWakeupEnemyOne(3757);
#endif
}
#endif

void actSt04lRope1Chk(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    while (gflagChk(165) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1085))) {
#else
    while (gflagChk(184) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1183))) {
#endif
        case 0:
            _ACTWait(1);
            break;
        case 1:
#ifdef VERSION_AUG6
            stage_SetAnimation(191, 1, 0);

            while (stage_CheckAnimationFinish(191) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            stage_SetAnimation(216, 1, 0);
#else
            stage_SetAnimation(220, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            while (stage_CheckAnimationFinish(216) == 0) {
#else
            while (stage_CheckAnimationFinish(220) == 0) {
#endif
#endif
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        case 2:
#ifdef VERSION_AUG6
            scpSearchGobj(1085)->active = 0;
            gflagOn(165);
            stage_SetAnimation(187, 1, 0);

            while (stage_CheckAnimationFinish(187) == 0) {
#else
            scpSearchGobj(1183)->active = 0;
            gflagOn(184);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            stage_SetAnimation(212, 1, 0);
#else
            stage_SetAnimation(216, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            while (stage_CheckAnimationFinish(212) == 0) {
#else
            while (stage_CheckAnimationFinish(216) == 0) {
#endif
#endif
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        }
    }
}

void actSt04lRope2Chk(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    while (gflagChk(166) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1086))) {
#else
    while (gflagChk(185) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1184))) {
#endif
        case 0:
            _ACTWait(1);
            break;
        case 1:
#ifdef VERSION_AUG6
            stage_SetAnimation(192, 1, 0);

            while (stage_CheckAnimationFinish(192) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            stage_SetAnimation(217, 1, 0);
#else
            stage_SetAnimation(221, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            while (stage_CheckAnimationFinish(217) == 0) {
#else
            while (stage_CheckAnimationFinish(221) == 0) {
#endif
#endif
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        case 2:
#ifdef VERSION_AUG6
            scpSearchGobj(1086)->active = 0;
            gflagOn(166);
            stage_SetAnimation(188, 1, 0);

            while (stage_CheckAnimationFinish(188) == 0) {
#else
            scpSearchGobj(1184)->active = 0;
            gflagOn(185);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            stage_SetAnimation(213, 1, 0);
#else
            stage_SetAnimation(217, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            while (stage_CheckAnimationFinish(213) == 0) {
#else
            while (stage_CheckAnimationFinish(217) == 0) {
#endif
#endif
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        }
    }
}

#ifdef VERSION_AUG6
void actSt04lBrg1Chk(GObj *volatile self)
{
    while (gflagChk(165) == 0 || gflagChk(166) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    gflagOn(163);

    _ACTWait(60);

    scpAdpcmPlayRequestFunc(84, &st04d_hasi, 1, 1, 1);

    while (st04d_hasi == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(195, 1, 0);

    while (stage_CheckAnimationFrame(195, 75, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFinish(195) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}
#endif

void actSt04lRope3Chk(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    while (gflagChk(167) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1087))) {
#else
    while (gflagChk(186) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1185))) {
#endif
        case 0:
            _ACTWait(1);
            break;
        case 1:
#ifdef VERSION_AUG6
            stage_SetAnimation(193, 1, 0);

            while (stage_CheckAnimationFinish(193) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            stage_SetAnimation(218, 1, 0);
#else
            stage_SetAnimation(222, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            while (stage_CheckAnimationFinish(218) == 0) {
#else
            while (stage_CheckAnimationFinish(222) == 0) {
#endif
#endif
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        case 2:
#ifdef VERSION_AUG6
            scpSearchGobj(1087)->active = 0;
            gflagOn(167);
            stage_SetAnimation(189, 1, 0);

            while (stage_CheckAnimationFinish(189) == 0) {
#else
            scpSearchGobj(1185)->active = 0;
            gflagOn(186);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            stage_SetAnimation(214, 1, 0);
#else
            stage_SetAnimation(218, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            while (stage_CheckAnimationFinish(214) == 0) {
#else
            while (stage_CheckAnimationFinish(218) == 0) {
#endif
#endif
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        }
    }
}

void actSt04lRope4Chk(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    while (gflagChk(168) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1088))) {
#else
    while (gflagChk(187) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1186))) {
#endif
        case 0:
            _ACTWait(1);
            break;
        case 1:
#ifdef VERSION_AUG6
            stage_SetAnimation(194, 1, 0);

            while (stage_CheckAnimationFinish(194) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            stage_SetAnimation(219, 1, 0);
#else
            stage_SetAnimation(223, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            while (stage_CheckAnimationFinish(219) == 0) {
#else
            while (stage_CheckAnimationFinish(223) == 0) {
#endif
#endif
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        case 2:
#ifdef VERSION_AUG6
            scpSearchGobj(1088)->active = 0;
            gflagOn(168);
            stage_SetAnimation(190, 1, 0);

            while (stage_CheckAnimationFinish(190) == 0) {
#else
            scpSearchGobj(1186)->active = 0;
            gflagOn(187);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            stage_SetAnimation(215, 1, 0);
#else
            stage_SetAnimation(219, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            while (stage_CheckAnimationFinish(215) == 0) {
#else
            while (stage_CheckAnimationFinish(219) == 0) {
#endif
#endif
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        }
    }
#ifdef VERSION_AUG6
}

void actSt04lBrg2Chk(GObj *volatile self)
{
    while (gflagChk(167) == 0 || gflagChk(168) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    gflagOn(164);

    _ACTWait(60);

    scpAdpcmPlayRequestFunc(84, &st04d_hasi, 1, 1, 1);

    while (st04d_hasi == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(196, 1, 0);

    while (stage_CheckAnimationFrame(196, 75, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFinish(196) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
#endif
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

#ifdef VERSION_AUG6
    scpAdpcmPlayRequestFunc(18, &sekizo4c, 1, 1, 1);

    while (sekizo4c == 0) {
        _ACTWait(1);
    }
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
#endif
    scpKillEnemyAll();
    scpMaskGeneratorAll();

#ifdef VERSION_AUG6
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    SetWayGroupActive(1, 1);

    _ACTWait(60);

    stage_SetAnimation(197, 1, 0);

    sekizo_4l = iosPadActRequest(boyPad, 9);
    sekizo_4l_vol = 128;
    iosPadActVolumeSet(sekizo_4l, 128);
#else
    scpAdpcmPlayRequestFunc(18, &stair4d, 1, 1, 1);

    while (stair4d == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(1, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(222, 1, 0);
#else
    stage_SetAnimation(226, 1, 0);
#endif

    st04l_yure = iosPadActRequest(boyPad, 9);
    st04l_yure_vol = 128;
    iosPadActVolumeSet(st04l_yure, 128);
#endif

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);
    scpPlayMot(boyGObj, 0);
#ifdef VERSION_AUG6
    scpPlayMot(girlGObj, 514);
#else
    scpPlayMot(girlGObj, 532);
#endif
    scpPlayPosSet(girlGObj, 0.0f, -1300.0f, -1700.0f);
    scpPlayPosSet(boyGObj, 20.0f, -1300.0f, -1700.0f);

    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT((void *)self), test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, dir);

    scpBoyControlReadDisable = 1;

    sceVu0SubVector(dir, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    scpSekizouCheckPoint();

#ifdef VERSION_AUG6
    scpPlayMot(girlGObj, 573);
    scpPlayWaitMotEnd(girlGObj);

    gflagOn(169);

    while (stage_CheckAnimationFrame(197, 151, 0) == 0) {
#else
    scpPlayMot(girlGObj, 645);
    scpPlayWaitMotEnd(girlGObj);

    gflagOn(188);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(222, 151, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(226, 151, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#ifdef VERSION_AUG6
    iosPadActStop(sekizo_4l);

    scpPlayMot(girlGObj, 514);
#else
    iosPadActStop(st04l_yure);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(222) == 0) {
#else
    while (stage_CheckAnimationFinish(226) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(girlGObj, 532);
#endif
    scpPlayEnd(girlGObj);
    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);

#ifdef VERSION_AUG6
    lt_switch_layout(50);
#else
    _ACTWait(1);
    iosOmSendMail(girlGObj, 63, boyGObj);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
#endif
    scpBoyControlReadDisable = 0;
}
#endif

void actSt04lGondolaChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttr(boyGObj, 0xA000000) == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    _ACTWait(15);

    if (gflagChk(164) != 0) {
        stage_SetAnimation(179, 1, 200);
        soundSeDefPlay(1266, 0, 0, 1);

        while (stage_CheckAnimationFinish(179) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
#ifdef VERSION_AUG6
    lt_switch_layout(51);
#else
    lt_switch_layout(55);
#endif
#endif
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    _ACTWait(15);

#ifdef VERSION_AUG6
    if (gflagChk(171) != 0) {
        stage_SetAnimation(199, 1, 200);

        while (stage_CheckAnimationFrame(199, 220, 0) == 0) {
#else
    if (gflagChk(190) != 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(224, 1, 200);
#else
        stage_SetAnimation(228, 1, 200);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        while (stage_CheckAnimationFrame(224, 220, 0) == 0) {
#else
        while (stage_CheckAnimationFrame(228, 220, 0) == 0) {
#endif
#endif
#endif
            _ACTWait(1);
        }
        _ACTWait(1);
#ifdef VERSION_AUG6
        soundSeDefPlay(1297, 0, 0, 1);

        while (stage_CheckAnimationFrame(199, 240, 0) == 0) {
#else
#ifdef VERSION_JUN26
        soundSeDefPlay(1267, 0, 0, 1);

        gflagOff(164);
    } else {
        stage_SetAnimation(179, 1, 0);
        soundSeDefPlay(1266, 0, 0, 1);

        while (stage_CheckAnimationFrame(179, 200, 1) == 0) {
#else
        soundSeDefPlay(1321, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        while (stage_CheckAnimationFrame(224, 240, 0) == 0) {
#else
        while (stage_CheckAnimationFrame(228, 240, 0) == 0) {
#endif
#endif
#endif
            _ACTWait(1);
        }
        _ACTWait(1);
#ifdef VERSION_JUN26
        soundSeDefPlay(1267, 0, 0, 1);

        gflagOn(164);
#else
#ifdef VERSION_AUG6
        soundSeDefPlay(1298, 0, 0, 1);

        while (stage_CheckAnimationFrame(199, 250, 0) == 0) {
#else
        soundSeDefPlay(1322, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        while (stage_CheckAnimationFrame(224, 250, 0) == 0) {
#else
        while (stage_CheckAnimationFrame(228, 250, 0) == 0) {
#endif
#endif
            _ACTWait(1);
        }
        _ACTWait(1);
#ifdef VERSION_AUG6
        soundSeDefPlay(1295, 0, 0, 1);

        while (stage_CheckAnimationFrame(199, 415, 0) == 0) {
#else
        soundSeDefPlay(1319, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        while (stage_CheckAnimationFrame(224, 415, 0) == 0) {
#else
        while (stage_CheckAnimationFrame(228, 415, 0) == 0) {
#endif
#endif
            _ACTWait(1);
        }
        _ACTWait(1);
#ifdef VERSION_AUG6
        soundSeDefPlay(1296, 0, 0, 1);

        while (stage_CheckAnimationFinish(199) == 0) {
#else
        soundSeDefPlay(1320, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        while (stage_CheckAnimationFinish(224) == 0) {
#else
        while (stage_CheckAnimationFinish(228) == 0) {
#endif
#endif
            _ACTWait(1);
        }
        _ACTWait(1);

#ifdef VERSION_AUG6
        gflagOff(171);
    }
    else
    {
        stage_SetAnimation(199, 1, 0);
        soundSeDefPlay(1295, 0, 0, 1);

        while (stage_CheckAnimationFrame(199, 145, 0) == 0) {
#else
        gflagOff(190);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(224, 1, 0);
#else
        stage_SetAnimation(228, 1, 0);
#endif
        SetGirlDangerGObj(boyGObj);
        soundSeDefPlay(1319, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        while (stage_CheckAnimationFrame(224, 145, 0) == 0) {
#else
        while (stage_CheckAnimationFrame(228, 145, 0) == 0) {
#endif
#endif
            _ACTWait(1);
        }
        _ACTWait(1);
#ifdef VERSION_AUG6
        soundSeDefPlay(1296, 0, 0, 1);
        soundSeDefPlay(1297, 0, 0, 1);

        while (stage_CheckAnimationFrame(199, 170, 0) == 0) {
#else
        soundSeDefPlay(1320, 0, 0, 1);
        soundSeDefPlay(1321, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        while (stage_CheckAnimationFrame(224, 170, 0) == 0) {
#else
        while (stage_CheckAnimationFrame(228, 170, 0) == 0) {
#endif
#endif
            _ACTWait(1);
        }
        _ACTWait(1);
#ifdef VERSION_AUG6
        soundSeDefPlay(1298, 0, 0, 1);

        while (stage_CheckAnimationFrame(199, 200, 1) == 0) {
#else
        soundSeDefPlay(1322, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        while (stage_CheckAnimationFrame(224, 200, 1) == 0) {
#else
        while (stage_CheckAnimationFrame(228, 200, 1) == 0) {
#endif
#endif
            _ACTWait(1);
        }
        _ACTWait(1);

#ifdef VERSION_AUG6
        gflagOn(171);
#else
        ClearGirlDangerGObj();
        gflagOn(190);
    }

    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0xA000000) == 0) {
        gflagOn(194);
    } else {
        gflagOff(194);
#endif
#endif
    }

    scpBoyControlReadDisable = 0;
#ifdef VERSION_JUN26
    lt_switch_layout(50);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
#ifdef VERSION_AUG6
    lt_switch_layout(50);
#else
    lt_switch_layout(54);
#endif
#endif
    scpWakeupEnemyAll();
#endif

    gondolaChk_mes[0].func = actSt04lGondolaCharaChk;
    sub->mail = gondolaChk_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
    ACTSendMailCorrect(self, 377);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

#ifdef VERSION_JUN26
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
#else
void actSt04lMonyou01Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x1000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);
    gflagOn(192);
    scpSleepEnemyAll();
    _ACTWait(5);

    stage_SetAnimation(205, 1, 0);
    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(205, 30, 0) == 0) {
#else
    gflagOn(212);
    FinishHint(16);
    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(boyGObj);
        scpPlayStart(girlGObj);
        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);
        ACTGame_ConnectHand();
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(230, 1, 0);
#else
    stage_SetAnimation(234, 1, 0);
#endif
    soundSeDefPlay(1332, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(230, 30, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(234, 30, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
#ifndef VERSION_AUG6
    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(girlGObj, 63, boyGObj);
    }
#endif

    scpBoyControlReadDisable = 0;
}

void actSt04lMonyou02Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x2000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);
    gflagOn(193);
    scpSleepEnemyAll();
    _ACTWait(5);

    stage_SetAnimation(206, 1, 0);
    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(206, 30, 0) == 0) {
#else
    gflagOn(213);
    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(boyGObj);
        scpPlayStart(girlGObj);
        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);
        ACTGame_ConnectHand();
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(231, 1, 0);
#else
    stage_SetAnimation(235, 1, 0);
#endif
    soundSeDefPlay(1332, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(231, 30, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(235, 30, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
#ifndef VERSION_AUG6
    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(girlGObj, 63, boyGObj);
    }
#endif

    scpBoyControlReadDisable = 0;
}

void actSt04lMonyou03Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x3000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);
    gflagOn(194);
    scpSleepEnemyAll();
    _ACTWait(5);

    stage_SetAnimation(207, 1, 0);
    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(207, 30, 0) == 0) {
#else
    gflagOn(214);
    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(boyGObj);
        scpPlayStart(girlGObj);
        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);
        ACTGame_ConnectHand();
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(232, 1, 0);
#else
    stage_SetAnimation(236, 1, 0);
#endif
    soundSeDefPlay(1332, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(232, 30, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(236, 30, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
#ifndef VERSION_AUG6
    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(girlGObj, 63, boyGObj);
    }
#endif

    scpBoyControlReadDisable = 0;
}

void actSt04lMonyou04Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x4000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x4000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);
    gflagOn(195);
    scpSleepEnemyAll();
    _ACTWait(5);

    stage_SetAnimation(208, 1, 0);
    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(208, 30, 0) == 0) {
#else
    gflagOn(215);
    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(boyGObj);
        scpPlayStart(girlGObj);
        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);
        ACTGame_ConnectHand();
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(233, 1, 0);
#else
    stage_SetAnimation(237, 1, 0);
#endif
    soundSeDefPlay(1332, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(233, 30, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(237, 30, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
#ifndef VERSION_AUG6
    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(girlGObj, 63, boyGObj);
    }
#endif

    scpBoyControlReadDisable = 0;
}

void actSt04lMonyou05Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x5000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x5000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);
    gflagOn(196);
    scpSleepEnemyAll();
    _ACTWait(5);

    stage_SetAnimation(209, 1, 0);
    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(209, 30, 0) == 0) {
#else
    gflagOn(216);
    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(boyGObj);
        scpPlayStart(girlGObj);
        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);
        ACTGame_ConnectHand();
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(234, 1, 0);
#else
    stage_SetAnimation(238, 1, 0);
#endif
    soundSeDefPlay(1332, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(234, 30, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(238, 30, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
#ifndef VERSION_AUG6
    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(girlGObj, 63, boyGObj);
    }
#endif

    scpBoyControlReadDisable = 0;
}

void actSt04lMonyou06Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x6000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x6000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;
#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);
    gflagOn(197);
    scpSleepEnemyAll();
    _ACTWait(5);

    stage_SetAnimation(210, 1, 0);
    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(210, 30, 0) == 0) {
#else
    gflagOn(217);
    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(boyGObj);
        scpPlayStart(girlGObj);
        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);
        ACTGame_ConnectHand();
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(235, 1, 0);
#else
    stage_SetAnimation(239, 1, 0);
#endif
    soundSeDefPlay(1332, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(235, 30, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(239, 30, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
#ifndef VERSION_AUG6
    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(girlGObj, 63, boyGObj);
    }
#endif

    scpBoyControlReadDisable = 0;
}
#endif

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
#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);
    gflagOn(198);
    scpSleepEnemyAll();
    _ACTWait(5);

    stage_SetAnimation(211, 1, 0);
    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(211, 30, 0) == 0) {
#else
#ifdef VERSION_JUN26
    gflagOn(189);
    _ACTWait(5);

    stage_SetAnimation(190, 1, 0);
    soundSeDefPlay(1277, 0, 0, 1);

    while (stage_CheckAnimationFrame(190, 30, 0) == 0) {
#else
    gflagOn(218);
    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(boyGObj);
        scpPlayStart(girlGObj);
        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);
        ACTGame_ConnectHand();
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(236, 1, 0);
#else
    stage_SetAnimation(240, 1, 0);
#endif
    soundSeDefPlay(1332, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(236, 30, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(240, 30, 0) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
#ifdef VERSION_JUN26
    SetWayGroupActive(1, 1);
#else
    scpWakeupEnemyAll();
#ifndef VERSION_AUG6
    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(girlGObj, 63, boyGObj);
    }
#endif
#endif

    scpBoyControlReadDisable = 0;
}

#ifdef VERSION_JUN26
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
#else
#ifdef VERSION_AUG6
void actSt04lOriChk(GObj *volatile self)
{
    while (gflagChk(156) == 0 || scpGameStat_BoyWeaponkind() != 4 ||
           scpTriggerBall(self, boyGObj, 1000.0f) == 0) {
        _ACTWait(1);
    }

    scpSleepEnemyAll();
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    scpPlayMot(boyGObj, 0);

    if (girlGObj != 0) {
        iosOmSendMail(girlGObj, 58, boyGObj);
    }

    gflagOn(180);

    _ACTWait(60);

    scpAdpcmPlayRequestFunc(60, &oriup4c, 1, 1, 1);

    while (oriup4c == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(214, 1, 0);
    stage_SetAnimation(216, 1, 0);
    stage_SetAnimation(215, 1, 0);

    while (stage_CheckAnimationFrame(214, 90, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActRequest(boyPad, 15);

    while (stage_CheckAnimationFinish(214) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}
#else
static void actSt04lOriSub(GObj *volatile self)
{
    _ACTWait(60);

    while (st04d_hasi == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(st04d_hasi->stream);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(239, 1, 0);
    stage_SetAnimation(241, 1, 0);
    stage_SetAnimation(240, 1, 0);
#else
    stage_SetAnimation(243, 1, 0);
    stage_SetAnimation(245, 1, 0);
    stage_SetAnimation(244, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(239, 90, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(243, 90, 0) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActRequest(boyPad, 15);

    if (girlGObj != 0) {
        scpPlayMotReq(girlGObj, 216);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(239) == 0) {
#else
    while (stage_CheckAnimationFinish(243) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt04lOriChk(GObj *volatile self)
{
    GProc *h;

    while (gflagChk(175) == 0 || scpGameStat_BoyWeaponkind() != 4 ||
           scpTriggerBall(self, boyGObj, 1000.0f) == 0) {
        _ACTWait(1);
    }

    scpSleepEnemyAll();
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;

    scpPlayMot(boyGObj, 0);

    if (girlGObj != 0) {
        iosOmSendMail(girlGObj, 62, boyGObj);
    }

    gflagOn(200);
    SetWayGroupActive(14, 0);
    SetWayGroupActive(15, 0);

    scpAdpcmPlayRequestFunc(62, &st04d_hasi, 1, 1, 0);

    h = actCreateSubThread(actSt04lOriSub, 21);

    demoEnd = 0;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&h->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (st04d_hasi == 0) {
            _ACTWait(1);
        }

        scpAdpcmFadeCloseFunc(&st04d_hasi, 512);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(239, 0, -1);
        stage_SetAnimation(241, 0, -1);
        stage_SetAnimation(240, 0, -1);
#else
        stage_SetAnimation(243, 0, -1);
        stage_SetAnimation(245, 0, -1);
        stage_SetAnimation(244, 0, -1);
#endif
        scpFadeIn(3.0f);
    }

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
}
#endif

void actSt04lOriRopeCutRChk(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    while (1) {
#ifdef VERSION_AUG6
        if (scpGameStat_BoyWeaponkind() == 4 && scpTriggerBall(self, boyGObj, 100.0f) != 0 &&
            (ForMotionViewer_GetCurrentMotion(boyGObj) == 37 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 42 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 44 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 38 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 39 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 60))
            break;
#else
        if (scpGameStat_BoyWeaponkind() == 4 && scpTriggerBall(self, boyGObj, 100.0f) != 0 &&
            (ForMotionViewer_GetCurrentMotion(boyGObj) == 38 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 43 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 45 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 39 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 40 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 60))
            break;
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(181);

    stage_SetAnimation(217, 1, 0);
    soundSeDefPlay(1299, 0, 0, 1);

    while (stage_CheckAnimationFrame(217, 45, 0) == 0) {
#else
    _ACTWait(15);
    gflagOn(201);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(242, 1, 0);
#else
    stage_SetAnimation(246, 1, 0);
#endif
    soundSeDefPlay(1323, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(242, 32, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(246, 32, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
#ifdef VERSION_AUG6
    soundSeDefPlay(1300, 0, 0, 1);

    while (stage_CheckAnimationFinish(217) == 0) {
#else
    soundSeDefPlay(1324, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(242) == 0) {
#else
    while (stage_CheckAnimationFinish(246) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
}

void actSt04lOriRopeCutLChk(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    while (1) {
#ifdef VERSION_AUG6
        if (scpGameStat_BoyWeaponkind() == 4 && scpTriggerBall(self, boyGObj, 100.0f) != 0 &&
            (ForMotionViewer_GetCurrentMotion(boyGObj) == 37 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 42 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 44 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 38 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 39 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 60))
            break;
#else
        if (scpGameStat_BoyWeaponkind() == 4 && scpTriggerBall(self, boyGObj, 100.0f) != 0 &&
            (ForMotionViewer_GetCurrentMotion(boyGObj) == 38 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 43 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 45 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 39 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 40 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 60))
            break;
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(182);

    stage_SetAnimation(218, 1, 0);
    soundSeDefPlay(1299, 0, 0, 1);

    while (stage_CheckAnimationFrame(218, 45, 0) == 0) {
#else
    _ACTWait(15);
    gflagOn(202);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(243, 1, 0);
#else
    stage_SetAnimation(247, 1, 0);
#endif
    soundSeDefPlay(1323, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(243, 32, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(247, 32, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
#ifdef VERSION_AUG6
    soundSeDefPlay(1300, 0, 0, 1);

    while (stage_CheckAnimationFinish(218) == 0) {
#else
    soundSeDefPlay(1324, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(243) == 0) {
#else
    while (stage_CheckAnimationFinish(247) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
}

void actSt04lOri2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(183) == 0) {
        ori2_mes[0].func = actSt04lOri2Chk;
        act->mail = ori2_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(214, -1, -2);
        stage_SetAnimation(216, -1, -2);
        stage_SetAnimation(215, -1, -2);
        stage_SetAnimation(219, 0, -1);
        stage_SetAnimation(218, 0, -1);
        stage_SetAnimation(217, 0, -1);
#else
    if (gflagChk(203) == 0) {
        SleepHint(15);

        ori2_mes[0].func = actSt04lOri2Chk;
        act->mail = ori2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(239, -1, -2);
        stage_SetAnimation(241, -1, -2);
        stage_SetAnimation(240, -1, -2);
        stage_SetAnimation(244, 0, -1);
        stage_SetAnimation(243, 0, -1);
        stage_SetAnimation(242, 0, -1);
#else
        stage_SetAnimation(243, -1, -2);
        stage_SetAnimation(245, -1, -2);
        stage_SetAnimation(244, -1, -2);
        stage_SetAnimation(248, 0, -1);
        stage_SetAnimation(247, 0, -1);
        stage_SetAnimation(246, 0, -1);
#endif
#endif
    }
}

#ifdef VERSION_AUG6
void actSt04lOri2Chk(GObj *volatile self)
{
    while (gflagChk(181) == 0 || gflagChk(182) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    gflagOn(183);
    scpSleepEnemyAll();

    iosPadActRequest(boyPad, 17);
    _ACTWait(30);

    scpAdpcmPlayRequestFunc(61, &oridown4c, 1, 1, 1);

    while (oridown4c == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(219, 1, 0);

    while (stage_CheckAnimationFrame(219, 30, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActRequest(boyPad, 15);

    while (stage_CheckAnimationFinish(219) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}
#else
static void actSt04lOri2Sub(GObj *volatile self)
{
    iosPadActRequest(boyPad, 17);
    _ACTWait(30);

    while (sekizo4c == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(sekizo4c->stream);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(244, 1, 0);
#else
    stage_SetAnimation(248, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(244, 30, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(248, 30, 0) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActRequest(boyPad, 15);

    if (girlGObj != 0) {
        scpPlayMotReq(girlGObj, 216);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(244) == 0) {
#else
    while (stage_CheckAnimationFinish(248) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt04lOri2Chk(GObj *volatile self)
{
    GProc *h;

    while (gflagChk(201) == 0 || gflagChk(202) == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    gflagOn(203);
    WakeupHint(15);
    SetWayGroupActive(14, 1);
    SetWayGroupActive(15, 1);
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(63, &sekizo4c, 1, 1, 0);

    h = actCreateSubThread(actSt04lOri2Sub, 21);

    demoEnd = 0;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&h->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (sekizo4c == 0) {
            _ACTWait(1);
        }

        scpAdpcmFadeCloseFunc(&sekizo4c, 512);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(244, 0, -1);
#else
        stage_SetAnimation(248, 0, -1);
#endif
        scpFadeIn(3.0f);
    }

    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
}
#endif
#endif

void actSt04lCrest01(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(155) == 0) {
        stage_SetAnimation(176, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(148) == 0) {
        stage_SetAnimation(160, 0, 0);
#else
    if (gflagChk(174) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(195, 0, 0);
#else
        stage_SetAnimation(199, 0, 0);
#endif
#endif
#endif

        crest01_mes[0].func = actSt04lCrestMain;
        act->mail = crest01_mes;
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(160, 0, -1);
#else
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(176, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(195, 0, -1);
#else
        stage_SetAnimation(199, 0, -1);
#endif
#endif

        scpBoyControlReadDisable = 0;
#endif
    }
}

void actSt04lCrest03(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(157) == 0) {
        stage_SetAnimation(180, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(150) == 0) {
        stage_SetAnimation(164, 0, 0);
#else
    if (gflagChk(176) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(199, 0, 0);
#else
        stage_SetAnimation(203, 0, 0);
#endif
#endif
#endif

        crest03_mes[0].func = actSt04lCrest3Main;
        act->mail = crest03_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(180, 0, -1);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(164, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(199, 0, -1);
#else
        stage_SetAnimation(203, 0, -1);
#endif
#endif
#endif
    }
}

void actSt04lC1Ball(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(158) == 0) {
        scpSearchGobj(1023)->active = 0;
        scpSearchGobj(1024)->active = 0;

        stage_SetAnimation(184, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(151) == 0) {
        scpSearchGobj(973)->active = 0;
        scpSearchGobj(974)->active = 0;

        stage_SetAnimation(168, 0, 0);
#else
    if (gflagChk(177) == 0) {
        scpSearchGobj(1114)->active = 0;
        scpSearchGobj(1115)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(203, 0, 0);
#else
        stage_SetAnimation(207, 0, 0);
#endif
#endif
#endif

        c1Ball_mes[0].func = actSt04lC1BallMain;
        act->mail = c1Ball_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(184, 0, -1);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(168, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(203, 0, -1);
#else
        stage_SetAnimation(207, 0, -1);
#endif
#endif
#endif
    }
}

void actSt04lC2Ball(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(159) == 0) {
        scpSearchGobj(1105)->active = 0;
        scpSearchGobj(1106)->active = 0;

        stage_SetAnimation(185, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(152) == 0) {
        scpSearchGobj(1053)->active = 0;
        scpSearchGobj(1054)->active = 0;

        stage_SetAnimation(169, 0, 0);
#else
    if (gflagChk(178) == 0) {
        scpSearchGobj(1202)->active = 0;
        scpSearchGobj(1203)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(204, 0, 0);
#else
        stage_SetAnimation(208, 0, 0);
#endif
#endif
#endif

        c2Ball_mes[0].func = actSt04lC2BallMain;
        act->mail = c2Ball_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(185, 0, -1);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(169, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(204, 0, -1);
#else
        stage_SetAnimation(208, 0, -1);
#endif
#endif
#endif
    }
}

void actSt04lC3Ball(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(160) == 0) {
        scpSearchGobj(1107)->active = 0;
        scpSearchGobj(1108)->active = 0;

        stage_SetAnimation(186, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(153) == 0) {
        scpSearchGobj(1055)->active = 0;
        scpSearchGobj(1056)->active = 0;

        stage_SetAnimation(170, 0, 0);
#else
    if (gflagChk(179) == 0) {
        scpSearchGobj(1204)->active = 0;
        scpSearchGobj(1205)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(205, 0, 0);
#else
        stage_SetAnimation(209, 0, 0);
#endif
#endif
#endif

        c3Ball_mes[0].func = actSt04lC3BallMain;
        act->mail = c3Ball_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(186, 0, -1);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(170, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(205, 0, -1);
#else
        stage_SetAnimation(209, 0, -1);
#endif
#endif
#endif
    }
}

void actSt04lStair(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(161) == 0) {
#else
#ifdef VERSION_JUN26
    if (gflagChk(154) == 0) {
#else
    if (gflagChk(180) == 0) {
#endif
#endif
        if (girlGObj != 0) {
            stair_mes[0].func = actSt04lStairChk;
            act->mail = stair_mes;
#ifdef VERSION_AUG6
            ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
            ACTSendMailCorrect(self, 377);
#else
            ACTSendMailCorrect(self, 430);
#endif
#endif
            _ACTWait(0);
        }
    } else {
#ifdef VERSION_AUG6
        scpSearchGobj(1145)->active = 0;

        stage_SetAnimation(230, -1, -2);
#else
#ifdef VERSION_JUN26
        scpSearchGobj(1089)->active = 0;

        stage_SetAnimation(205, -1, -2);
#else
        scpSearchGobj(1242)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(255, -1, -2);
#else
        stage_SetAnimation(259, -1, -2);
#endif
#endif
#endif
    }
}

void actSt04lBrg1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(163) == 0) {
        brg1_mes[0].func = actSt04lBrg1Chk;
        act->mail = brg1_mes;
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
    if (gflagChk(156) == 0) {
        brg1_mes[0].func = actSt04lBrg1Chk;
        act->mail = brg1_mes;
        ACTSendMailCorrect(self, 377);
#else
    if (gflagChk(182) == 0) {
        brg1_mes[0].func = actSt04lBrg1Chk;
        act->mail = brg1_mes;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actSt04lBrg2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(164) == 0) {
        brg2_mes[0].func = actSt04lBrg2Chk;
        act->mail = brg2_mes;
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
    if (gflagChk(157) == 0) {
        brg2_mes[0].func = actSt04lBrg2Chk;
        act->mail = brg2_mes;
        ACTSendMailCorrect(self, 377);
#else
    if (gflagChk(183) == 0) {
        SleepHint(16);

        brg2_mes[0].func = actSt04lBrg2Chk;
        act->mail = brg2_mes;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actSt04lBrg1Way(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(163) == 0) {
        brg1Way_mes[0].func = actSt04lBrg1WayChk;
        act->mail = brg1Way_mes;
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
    if (gflagChk(156) == 0) {
        brg1Way_mes[0].func = actSt04lBrg1WayChk;
        act->mail = brg1Way_mes;
        ACTSendMailCorrect(self, 377);
#else
    if (gflagChk(182) == 0) {
        brg1Way_mes[0].func = actSt04lBrg1WayChk;
        act->mail = brg1Way_mes;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actSt04lBrg2Way(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(164) == 0) {
        brg2Way_mes[0].func = actSt04lBrg2WayChk;
        act->mail = brg2Way_mes;
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
    if (gflagChk(157) == 0) {
        brg2Way_mes[0].func = actSt04lBrg2WayChk;
        act->mail = brg2Way_mes;
        ACTSendMailCorrect(self, 377);
#else
    if (gflagChk(183) == 0) {
        brg2Way_mes[0].func = actSt04lBrg2WayChk;
        act->mail = brg2Way_mes;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actSt04lRope1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(165) == 0) {
        stage_SetAnimation(187, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(158) == 0) {
        stage_SetAnimation(171, 0, 0);
#else
    if (gflagChk(184) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(212, 0, 0);
#else
        stage_SetAnimation(216, 0, 0);
#endif
#endif
#endif

        rope1_mes[0].func = actSt04lRope1Chk;
        act->mail = rope1_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(187, 0, -1);

        scpSearchGobj(1085)->active = 0;
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(171, 0, -1);

        scpSearchGobj(1031)->active = 0;
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(212, 0, -1);
#else
        stage_SetAnimation(216, 0, -1);
#endif

        scpSearchGobj(1183)->active = 0;
#endif
#endif
    }
}

void actSt04lRope2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(166) == 0) {
        stage_SetAnimation(188, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(159) == 0) {
        stage_SetAnimation(172, 0, 0);
#else
    if (gflagChk(185) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(213, 0, 0);
#else
        stage_SetAnimation(217, 0, 0);
#endif
#endif
#endif

        rope2_mes[0].func = actSt04lRope2Chk;
        act->mail = rope2_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(188, 0, -1);

        scpSearchGobj(1086)->active = 0;
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(172, 0, -1);

        scpSearchGobj(1032)->active = 0;
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(213, 0, -1);
#else
        stage_SetAnimation(217, 0, -1);
#endif

        scpSearchGobj(1184)->active = 0;
#endif
#endif
    }
}

void actSt04lRope3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(167) == 0) {
        stage_SetAnimation(189, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(160) == 0) {
        stage_SetAnimation(173, 0, 0);
#else
    if (gflagChk(186) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(214, 0, 0);
#else
        stage_SetAnimation(218, 0, 0);
#endif
#endif
#endif

        rope3_mes[0].func = actSt04lRope3Chk;
        act->mail = rope3_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(189, 0, -1);

        scpSearchGobj(1087)->active = 0;
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(173, 0, -1);

        scpSearchGobj(1033)->active = 0;
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(214, 0, -1);
#else
        stage_SetAnimation(218, 0, -1);
#endif

        scpSearchGobj(1185)->active = 0;
#endif
#endif
    }
}

void actSt04lRope4(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(168) == 0) {
        stage_SetAnimation(190, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(161) == 0) {
        stage_SetAnimation(174, 0, 0);
#else
    if (gflagChk(187) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(215, 0, 0);
#else
        stage_SetAnimation(219, 0, 0);
#endif
#endif
#endif

        rope4_mes[0].func = actSt04lRope4Chk;
        act->mail = rope4_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(190, 0, -1);

        scpSearchGobj(1088)->active = 0;
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(174, 0, -1);

        scpSearchGobj(1034)->active = 0;
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(215, 0, -1);
#else
        stage_SetAnimation(219, 0, -1);
#endif

        scpSearchGobj(1186)->active = 0;
#endif
#endif
    }
}

void actSt04lSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(169) == 0) {
        stage_SetAnimation(197, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(162) == 0) {
        stage_SetAnimation(177, 0, 0);
#else
    if (gflagChk(188) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(222, 0, 0);
#else
        stage_SetAnimation(226, 0, 0);
#endif
#endif
#endif

        sekizo_mes[0].func = actSt04lSekizoChk;
        act->mail = sekizo_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(197, 0, -1);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(177, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(222, 0, -1);
#else
        stage_SetAnimation(226, 0, -1);
#endif
#endif
#endif
    }
}

void actSt04lTuri(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(170) == 0) {
        stage_SetAnimation(201, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(163) == 0) {
        stage_SetAnimation(181, 0, 0);
#else
    if (gflagChk(189) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(226, 0, 0);
#else
        stage_SetAnimation(230, 0, 0);
#endif
#endif
#endif

        if (girlGObj != 0) {
            turi_mes[0].func = actSt04lTuriChk;
            act->mail = turi_mes;
#ifdef VERSION_AUG6
            ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
            ACTSendMailCorrect(self, 377);
#else
            ACTSendMailCorrect(self, 430);
#endif
#endif
            _ACTWait(0);
        }
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(226, 0, -1);
#else
#ifdef VERSION_AUG6
        stage_SetAnimation(201, 0, -1);
#else
#ifdef VERSION_JUN26
        stage_SetAnimation(181, 0, -1);
#else
        stage_SetAnimation(230, 0, -1);
#endif
#endif
#endif
    }
}

void actSt04lOri(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(180) == 0) {
        stage_SetAnimation(214, 0, 0);
        stage_SetAnimation(216, 0, 0);
        stage_SetAnimation(215, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(173) == 0) {
        stage_SetAnimation(193, 0, 0);
#else
    if (gflagChk(200) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(239, 0, 0);
        stage_SetAnimation(241, 0, 0);
        stage_SetAnimation(240, 0, 0);
#else
        stage_SetAnimation(243, 0, 0);
        stage_SetAnimation(245, 0, 0);
        stage_SetAnimation(244, 0, 0);
#endif
#endif
#endif

        ori_mes[0].func = actSt04lOriChk;
        act->mail = ori_mes;
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(193, 0, -1);
#else
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
#endif
    }
}

#ifdef VERSION_JUN26
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
#else
void actSt04lOriRopeCutR(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(181) == 0) {
        oriRopeCutR_mes[0].func = actSt04lOriRopeCutRChk;
        act->mail = oriRopeCutR_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(201) == 0) {
        oriRopeCutR_mes[0].func = actSt04lOriRopeCutRChk;
        act->mail = oriRopeCutR_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt04lOriRopeCutL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(182) == 0) {
        oriRopeCutL_mes[0].func = actSt04lOriRopeCutLChk;
        act->mail = oriRopeCutL_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(202) == 0) {
        oriRopeCutL_mes[0].func = actSt04lOriRopeCutLChk;
        act->mail = oriRopeCutL_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}
#endif

void actSt04lSword(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(156) == 0) {
        sword_mes[0].func = actSt04lSwordChk;
        act->mail = sword_mes;
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
    if (gflagChk(149) == 0) {
        sword_mes[0].func = actSt04lSwordChk;
        act->mail = sword_mes;
        ACTSendMailCorrect(self, 377);
#else
    if (gflagChk(175) == 0) {
        sword_mes[0].func = actSt04lSwordChk;
        act->mail = sword_mes;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actSt04lGondola(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(171) != 0) {
        stage_SetAnimation(199, 0, 200);
#else
#ifdef VERSION_JUN26
    if (gflagChk(164) != 0) {
        stage_SetAnimation(179, 0, 200);
#else
    if (gflagChk(190) != 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(224, 0, 200);
#else
        stage_SetAnimation(228, 0, 200);
#endif
#endif
#endif

        gondola_mes[0].func = actSt04lGondolaChk;
        act->mail = gondola_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(199, 0, 0);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(179, 0, 0);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(224, 0, 0);
#else
        stage_SetAnimation(228, 0, 0);
#endif
#endif
#endif

        gondola2_mes[0].func = actSt04lGondolaChk;
        act->mail = gondola2_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
#else
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actSt04lMonyou01(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(192) == 0) {
        stage_SetAnimation(205, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(183) == 0) {
        stage_SetAnimation(184, 0, 0);
#else
    if (gflagChk(212) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(230, 0, 0);
#else
        stage_SetAnimation(234, 0, 0);
#endif
#endif
#endif

        monyou01_mes[0].func = actSt04lMonyou01Chk;
        act->mail = monyou01_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(205, 0, -1);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(184, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(230, 0, -1);
#else
        stage_SetAnimation(234, 0, -1);
#endif
        FinishHint(16);
#endif
#endif
    }
}

void actSt04lMonyou02(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(193) == 0) {
        stage_SetAnimation(206, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(184) == 0) {
        stage_SetAnimation(185, 0, 0);
#else
    if (gflagChk(213) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(231, 0, 0);
#else
        stage_SetAnimation(235, 0, 0);
#endif
#endif
#endif

        monyou02_mes[0].func = actSt04lMonyou02Chk;
        act->mail = monyou02_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(206, 0, -1);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(185, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(231, 0, -1);
#else
        stage_SetAnimation(235, 0, -1);
#endif
#endif
#endif
    }
}

void actSt04lMonyou03(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(194) == 0) {
        stage_SetAnimation(207, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(185) == 0) {
        stage_SetAnimation(186, 0, 0);
#else
    if (gflagChk(214) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(232, 0, 0);
#else
        stage_SetAnimation(236, 0, 0);
#endif
#endif
#endif

        monyou03_mes[0].func = actSt04lMonyou03Chk;
        act->mail = monyou03_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(207, 0, -1);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(186, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(232, 0, -1);
#else
        stage_SetAnimation(236, 0, -1);
#endif
#endif
#endif
    }
}

void actSt04lMonyou04(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(195) == 0) {
        stage_SetAnimation(208, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(186) == 0) {
        stage_SetAnimation(187, 0, 0);
#else
    if (gflagChk(215) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(233, 0, 0);
#else
        stage_SetAnimation(237, 0, 0);
#endif
#endif
#endif

        monyou04_mes[0].func = actSt04lMonyou04Chk;
        act->mail = monyou04_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(208, 0, -1);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(187, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(233, 0, -1);
#else
        stage_SetAnimation(237, 0, -1);
#endif
#endif
#endif
    }
}

void actSt04lMonyou05(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(196) == 0) {
        stage_SetAnimation(209, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(187) == 0) {
        stage_SetAnimation(188, 0, 0);
#else
    if (gflagChk(216) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(234, 0, 0);
#else
        stage_SetAnimation(238, 0, 0);
#endif
#endif
#endif

        monyou05_mes[0].func = actSt04lMonyou05Chk;
        act->mail = monyou05_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(209, 0, -1);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(188, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(234, 0, -1);
#else
        stage_SetAnimation(238, 0, -1);
#endif
#endif
#endif
    }
}

void actSt04lMonyou06(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(197) == 0) {
        stage_SetAnimation(210, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(188) == 0) {
        stage_SetAnimation(189, 0, 0);
#else
    if (gflagChk(217) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(235, 0, 0);
#else
        stage_SetAnimation(239, 0, 0);
#endif
#endif
#endif

        monyou06_mes[0].func = actSt04lMonyou06Chk;
        act->mail = monyou06_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(210, 0, -1);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(189, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(235, 0, -1);
#else
        stage_SetAnimation(239, 0, -1);
#endif
#endif
#endif
    }
}

void actSt04lMonyou07(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(198) == 0) {
        stage_SetAnimation(211, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(189) == 0) {
        stage_SetAnimation(190, 0, 0);
#else
    if (gflagChk(218) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(236, 0, 0);
#else
        stage_SetAnimation(240, 0, 0);
#endif
#endif
#endif

        monyou07_mes[0].func = actSt04lMonyou07Chk;
        act->mail = monyou07_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(211, 0, -1);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(190, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(236, 0, -1);
#else
        stage_SetAnimation(240, 0, -1);
#endif
#endif
#endif
    }
}

void actSt04lCrest01XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(155) == 0) {
        stage_SetAnimation(181, 0, 0);
    } else {
        stage_SetAnimation(181, 0, -1);
#else
#ifdef VERSION_JUN26
    if (gflagChk(148) == 0) {
        stage_SetAnimation(165, 0, 0);
    } else {
        stage_SetAnimation(165, 0, -1);
#else
    if (gflagChk(174) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(200, 0, 0);
#else
        stage_SetAnimation(204, 0, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(200, 0, -1);
#else
        stage_SetAnimation(204, 0, -1);
#endif
#endif
#endif
    }
}

void actSt04lCrest02XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(156) == 0) {
        stage_SetAnimation(182, 0, 0);
    } else {
        stage_SetAnimation(182, 0, -1);
#else
#ifdef VERSION_JUN26
    if (gflagChk(149) == 0) {
        stage_SetAnimation(166, 0, 0);
    } else {
        stage_SetAnimation(166, 0, -1);
#else
    if (gflagChk(175) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(201, 0, 0);
#else
        stage_SetAnimation(205, 0, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(201, 0, -1);
#else
        stage_SetAnimation(205, 0, -1);
#endif
#endif
#endif
    }
}

void actSt04lCrest03XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(157) == 0) {
        stage_SetAnimation(183, 0, 0);
    } else {
        stage_SetAnimation(183, 0, -1);
#else
#ifdef VERSION_JUN26
    if (gflagChk(150) == 0) {
        stage_SetAnimation(167, 0, 0);
    } else {
        stage_SetAnimation(167, 0, -1);
#else
    if (gflagChk(176) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(202, 0, 0);
#else
        stage_SetAnimation(206, 0, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(202, 0, -1);
#else
        stage_SetAnimation(206, 0, -1);
#endif
#endif
#endif
    }
}

void actSt04lC2BallXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(159) == 0) {
        scpSearchGobj(1027)->active = 0;
        scpSearchGobj(1028)->active = 0;

        stage_SetAnimation(185, 0, 0);
    } else {
        stage_SetAnimation(185, 0, -1);
#else
#ifdef VERSION_JUN26
    if (gflagChk(152) == 0) {
        scpSearchGobj(977)->active = 0;
        scpSearchGobj(978)->active = 0;

        stage_SetAnimation(169, 0, 0);
    } else {
        stage_SetAnimation(169, 0, -1);
#else
    if (gflagChk(178) == 0) {
        scpSearchGobj(1118)->active = 0;
        scpSearchGobj(1119)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(204, 0, 0);
#else
        stage_SetAnimation(208, 0, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(204, 0, -1);
#else
        stage_SetAnimation(208, 0, -1);
#endif
#endif
#endif
    }
}

void actSt04lC3BallXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(160) == 0) {
        stage_SetAnimation(186, 0, 0);

        scpSearchGobj(1183)->active = 0;
        scpSearchGobj(1184)->active = 0;
    } else {
        stage_SetAnimation(186, 0, -1);
#else
#ifdef VERSION_JUN26
    if (gflagChk(153) == 0) {
        stage_SetAnimation(170, 0, 0);

        scpSearchGobj(1129)->active = 0;
        scpSearchGobj(1130)->active = 0;
    } else {
        stage_SetAnimation(170, 0, -1);
#else
    if (gflagChk(179) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(205, 0, 0);
#else
        stage_SetAnimation(209, 0, 0);
#endif

        scpSearchGobj(1283)->active = 0;
        scpSearchGobj(1284)->active = 0;
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(205, 0, -1);
#else
        stage_SetAnimation(209, 0, -1);
#endif
#endif
#endif
    }
}

void actSt04lTorch1_1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
    if (gflagChk(175) == 0) {
        torch1_1_mes[0].func = actSt04lTorch1_1Chk;
        act->mail = torch1_1_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpTorchLightOn(973);
#else
    if (gflagChk(184) == 0) {
        torch1_1_mes[0].func = actSt04lTorch1_1Chk;
        act->mail = torch1_1_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1023);
#endif
#else
    if (gflagChk(204) == 0) {
        torch1_1_mes[0].func = actSt04lTorch1_1Chk;
        act->mail = torch1_1_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1114);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(206, 0, -1);
#else
        stage_SetAnimation(210, 0, -1);
#endif
#endif
    }
}

void actSt04lTorch1_2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
    if (gflagChk(176) == 0) {
        torch1_2_mes[0].func = actSt04lTorch1_2Chk;
        act->mail = torch1_2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpTorchLightOn(974);
#else
    if (gflagChk(185) == 0) {
        torch1_2_mes[0].func = actSt04lTorch1_2Chk;
        act->mail = torch1_2_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1024);
#endif
#else
    if (gflagChk(205) == 0) {
        torch1_2_mes[0].func = actSt04lTorch1_2Chk;
        act->mail = torch1_2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1115);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(207, 0, -1);
#else
        stage_SetAnimation(211, 0, -1);
#endif
#endif
    }
}

void actSt04lTorch2_1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(186) != 0 || gflagChk(188) != 0) {
        scpTorchLightOn(1105);
#else
#ifdef VERSION_JUN26
    if (gflagChk(177) != 0 || gflagChk(179) != 0) {
        scpTorchLightOn(1053);
#else
    if (gflagChk(206) != 0 || gflagChk(208) != 0) {
        scpTorchLightOn(1202);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(208, 0, -1);
#else
        stage_SetAnimation(212, 0, -1);
#endif
#endif
#endif
    } else {
        torch2_1_mes[0].func = actSt04lTorch2_1Chk;
        act->mail = torch2_1_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
#else
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actSt04lTorch2_2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(187) != 0 || gflagChk(189) != 0) {
        scpTorchLightOn(1106);
#else
#ifdef VERSION_JUN26
    if (gflagChk(178) != 0 || gflagChk(180) != 0) {
        scpTorchLightOn(1054);
#else
    if (gflagChk(207) != 0 || gflagChk(209) != 0) {
        scpTorchLightOn(1203);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(209, 0, -1);
#else
        stage_SetAnimation(213, 0, -1);
#endif
#endif
#endif
    } else {
        torch2_2_mes[0].func = actSt04lTorch2_2Chk;
        act->mail = torch2_2_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
#else
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actSt04lTorch3_1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
    if (gflagChk(181) == 0) {
        torch3_1_mes[0].func = actSt04lTorch3_1Chk;
        act->mail = torch3_1_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1055);
#else
    if (gflagChk(190) == 0) {
        torch3_1_mes[0].func = actSt04lTorch3_1Chk;
        act->mail = torch3_1_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1107);
#endif
#else
    if (gflagChk(210) == 0) {
        torch3_1_mes[0].func = actSt04lTorch3_1Chk;
        act->mail = torch3_1_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1204);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(210, 0, -1);
#else
        stage_SetAnimation(214, 0, -1);
#endif
#endif
    }
}

void actSt04lTorch3_2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
    if (gflagChk(182) == 0) {
        torch3_2_mes[0].func = actSt04lTorch3_2Chk;
        act->mail = torch3_2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1056);
#else
    if (gflagChk(191) == 0) {
        torch3_2_mes[0].func = actSt04lTorch3_2Chk;
        act->mail = torch3_2_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1108);
#endif
#else
    if (gflagChk(211) == 0) {
        torch3_2_mes[0].func = actSt04lTorch3_2Chk;
        act->mail = torch3_2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1205);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(211, 0, -1);
#else
        stage_SetAnimation(215, 0, -1);
#endif
#endif
    }
}

void actSt04lTorch2_1XL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(186) != 0 || gflagChk(188) != 0) {
        scpTorchLightOn(1027);
#else
#ifdef VERSION_JUN26
    if (gflagChk(177) != 0 || gflagChk(179) != 0) {
        scpTorchLightOn(977);
#else
    if (gflagChk(206) != 0 || gflagChk(208) != 0) {
        scpTorchLightOn(1118);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(208, 0, -1);
#else
        stage_SetAnimation(212, 0, -1);
#endif
#endif
#endif
    } else {
        torch2_1XL_mes[0].func = actSt04lTorch2_1XLChk;
        act->mail = torch2_1XL_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
#else
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actSt04lTorch2_2XL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(187) != 0 || gflagChk(189) != 0) {
        scpTorchLightOn(1028);
#else
#ifdef VERSION_JUN26
    if (gflagChk(178) != 0 || gflagChk(180) != 0) {
        scpTorchLightOn(978);
#else
    if (gflagChk(207) != 0 || gflagChk(209) != 0) {
        scpTorchLightOn(1119);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(209, 0, -1);
#else
        stage_SetAnimation(213, 0, -1);
#endif
#endif
#endif
    } else {
        torch2_2XL_mes[0].func = actSt04lTorch2_2XLChk;
        act->mail = torch2_2XL_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
#else
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actSt04lTorch3_1XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(190) != 0) {
        scpTorchLightOn(1183);
#else
#ifdef VERSION_JUN26
    if (gflagChk(181) != 0) {
        scpTorchLightOn(1129);
#else
    if (gflagChk(210) != 0) {
        scpTorchLightOn(1283);
#endif
#endif
    }
}

void actSt04lTorch3_2XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(191) != 0) {
        scpTorchLightOn(1184);
#else
#ifdef VERSION_JUN26
    if (gflagChk(182) != 0) {
        scpTorchLightOn(1130);
#else
    if (gflagChk(211) != 0) {
        scpTorchLightOn(1284);
#endif
#endif
    }
}

void actSt04cDoorInit(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(145) != 0 && gflagChk(155) == 0) {
        stage_SetAnimation(224, 0, -1);
    }

    if (gflagChk(145) == 0 || gflagChk(155) != 0) {
        stage_SetAnimation(224, 0, 0);
#else
#ifdef VERSION_JUN26
    if (gflagChk(138) != 0 && gflagChk(148) == 0) {
        stage_SetAnimation(199, 0, -1);
    }

    if (gflagChk(138) == 0 || gflagChk(148) != 0) {
        stage_SetAnimation(199, 0, 0);
#else
    if (gflagChk(162) != 0 && gflagChk(174) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(249, 0, -1);
#else
        stage_SetAnimation(253, 0, -1);
#endif
    }

    if (gflagChk(162) == 0 || gflagChk(174) != 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(249, 0, 0);
#else
        stage_SetAnimation(253, 0, 0);
#endif
#endif
#endif
    }
}

void actSt04dEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);
#ifdef VERSION_AUG6
    Generator_Mask(scpSearchGobj(1095));

    while (gflagChk(200) == 0) {
#else
#ifdef VERSION_JUN26
    Generator_Mask(scpSearchGobj(1043));

    while (gflagChk(191) == 0) {
#else

    while (gflagChk(220) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
#ifdef VERSION_AUG6
    Generator_Call(scpSearchGobj(1095));
#endif
#ifdef VERSION_JUN26
    Generator_Call(scpSearchGobj(1043));
#endif
}

void actSt04dEnemy2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    Generator_Mask(self);

#ifdef VERSION_AUG6
    while (gflagChk(200) == 0) {
#else
#ifdef VERSION_JUN26
    while (gflagChk(191) == 0) {
#else
    while (gflagChk(220) == 0) {
#endif
#endif
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

#ifdef VERSION_AUG6
    while (gflagChk(200) == 0) {
#else
#ifdef VERSION_JUN26
    while (gflagChk(191) == 0) {
#else
    while (gflagChk(220) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    Generator_Call(self);
}

void actSt04eSolarBeam(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_JUN26
    if (gflagChk(195) != 0) {
#else
#ifdef VERSION_AUG6
    if (gflagChk(204) != 0) {
        if (boyGObj != 0) {
            scpPlayMot(boyGObj, 0);
        }

        gflagOn(355);
#else
    if (gflagChk(224) != 0) {
        if (boyGObj != 0) {
            scpPlayMot(boyGObj, 0);

            if (ACTGame_NoWeapon(boyGObj) == 0) {
                LightTorchOffOfWeapon(GetBoyWeaponGObj());
            }
        }

        gflagOn(389);
#endif

        scpSeEnvMasterVolRate = 0.0f;
#endif
        scpFadeOut(255.0f, 0, 0, 0);

        st04eSolarBeam_mes[0].func = actSt04eSolarBeamChk;
        act->mail = st04eSolarBeam_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
#else
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}
#endif

#ifndef VERSION_JUN26
void actSt04lC1BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
#ifdef VERSION_AUG6
    scpBoyControlReadDisable = 0;
#endif

    sub->mainMail = c1BallMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt04lC1BallSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    c1BallSwitch_mes[0].func = actSt04lC1BallTurn;
    sub->mail = c1BallSwitch_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt04lC1BallTurn(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    turnFlag = 177;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    turnAnim = 203;
#else
    turnAnim = 207;
#endif
    turnGobj1 = 1114;
    turnGobj2 = 1115;

    c1BallTurn_mes[0].func = actSt04lBallTurnCommon;
    act->mail = c1BallTurn_mes;
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

void actSt04lC2BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
#ifdef VERSION_AUG6
    scpBoyControlReadDisable = 0;
#endif

    sub->mainMail = c2BallMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt04lC2BallSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    c2BallSwitch_mes[0].func = actSt04lC2BallTurn;
    sub->mail = c2BallSwitch_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt04lC2BallTurn(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    turnFlag = 178;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    turnAnim = 204;
#else
    turnAnim = 208;
#endif
    turnGobj1 = 1202;
    turnGobj2 = 1203;

    c2BallTurn_mes[0].func = actSt04lBallTurnCommon;
    act->mail = c2BallTurn_mes;
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

void actSt04lC3BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
#ifdef VERSION_AUG6
    scpBoyControlReadDisable = 0;
#endif

    sub->mainMail = c3BallMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt04lC3BallSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    c3BallSwitch_mes[0].func = actSt04lC3BallTurn;
    sub->mail = c3BallSwitch_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
void actSt04eSolarBeamChk(GObj *volatile self)
{
    gflagOff(204);
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    scpAdpcmPlayRequestFunc(27, &solar4l, 0, 1, 1);

    while (solar4l == 0) {
        _ACTWait(1);
    }

    preload(7);
    scpFadeIn(6.0f);

#ifdef VERSION_AUG6
    stage_SetAnimation(258, 1, 0);

    while (stage_CheckAnimationFinish(258) == 0) {
#else
    stage_SetAnimation(259, 1, 0);

    while (stage_CheckAnimationFinish(259) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);

#ifdef VERSION_AUG6
    RequestStageChange(7, boyGObj, girlGObj, 2.0f, 8.0f);
#else
    RequestStageChange(7, boyGObj, 0, 2.0f, 8.0f);
#endif
}
#else
void actSt04lC3BallTurn(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    turnFlag = 179;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    turnAnim = 205;
#else
    turnAnim = 209;
#endif
    turnGobj1 = 1204;
    turnGobj2 = 1205;

    c3BallTurn_mes[0].func = actSt04lBallTurnCommon;
    act->mail = c3BallTurn_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

static void actSt04eSolarBeamChkSub(GObj *volatile self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(288, 1, 0);
#else
    stage_SetAnimation(292, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(288) == 0) {
#else
    while (stage_CheckAnimationFinish(292) == 0) {
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}
#endif

void actSt04lRope1Event(int x)
{
    volatile int local = x;
}

void actSt04lRope2Event(int x)
{
    volatile int local = x;
}

void actSt04lBrg1Event(int x)
{
    volatile int local = x;
}

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
void actSt04lBrg1Chk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (gflagChk(184) == 0 || gflagChk(185) == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    gflagOn(182);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    sekizo_4r = 220;
#else
    sekizo_4r = 224;
#endif

    brg1Chk_mes[0].func = actSt04rBrgCommon;
    sub->mail = brg1Chk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}
#endif

void actSt04lRope3Event(int x)
{
    volatile int local = x;
}

void actSt04lRope4Event(int x)
{
    volatile int local = x;
}

void actSt04lBrg2Event(int x)
{
    volatile int local = x;
}

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
void actSt04lBrg1WayChk(GObj *volatile self)
{
    while (gflagChk(163) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(3, 1);
}

void actSt04lBrg2WayChk(GObj *volatile self)
{
    while (gflagChk(163) == 0 || gflagChk(164) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(4, 1);
}
#else
void actSt04lBrg2Chk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (gflagChk(186) == 0 || gflagChk(187) == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    gflagOn(183);
    WakeupHint(16);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    sekizo_4r = 221;
#else
    sekizo_4r = 225;
#endif

    brg2Chk_mes[0].func = actSt04rBrgCommon;
    sub->mail = brg2Chk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt04lBrg1WayChk(GObj *volatile self)
{
    while (gflagChk(182) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(3, 1);
}

void actSt04lBrg2WayChk(GObj *volatile self)
{
    while (gflagChk(182) == 0 || gflagChk(183) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(4, 1);
}
#endif

void actSt04lTuriEvent(int x)
{
    volatile int local = x;
}

#ifdef VERSION_NTSC
void actSt04lTuriChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(self, girlGObj, 200.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    gflagOn(170);
    _ACTWait(10);

    stage_SetAnimation(202, 1, 0);

    while (stage_CheckAnimationFinish(202) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    lt_switch_layout(50);
}
#else
void actSt04lTuriChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(self, girlGObj, 200.0f) == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    lt_switch_layout(51);
    gflagOn(170);
    _ACTWait(10);

    stage_SetAnimation(201, 1, 0);

    while (stage_CheckAnimationFinish(201) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    gflagOn(189);
    _ACTWait(10);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(226, 1, 0);
#else
    stage_SetAnimation(230, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(226) == 0) {
#else
    while (stage_CheckAnimationFinish(230) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    _ACTWait(1);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(51);
#else
#ifdef VERSION_AUG6
    lt_switch_layout(50);
#else
    lt_switch_layout(54);
#endif
#endif
}
#endif

void actSt04lGondolaCharaChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttr(boyGObj, 0xA000000)) {
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
        if (gflagChk(194) && scpTriggerFloorAttr(girlGObj, 0xA000000)) {
            break;
        }
#endif
        _ACTWait(1);
    }

    gondola_chara[0].func = actSt04lGondolaChk;
    sub->mail = gondola_chara;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

void actSt04lMonyou01Event(int x)
{
    volatile int local = x;
}

void actSt04lMonyou02Event(int x)
{
    volatile int local = x;
}

void actSt04lMonyou03Event(int x)
{
    volatile int local = x;
}

void actSt04lMonyou04Event(int x)
{
    volatile int local = x;
}

void actSt04lMonyou05Event(int x)
{
    volatile int local = x;
}

void actSt04lMonyou06Event(int x)
{
    volatile int local = x;
}

void actSt04lMonyou07Event(int x)
{
    volatile int local = x;
}

void actSt04lOriEvent(int x)
{
    volatile int local = x;
}

void actSt04lOri2Event(int x)
{
    volatile int local = x;
}

#ifdef VERSION_NTSC
void actSt04lSwordChk(GObj *volatile self)
{
    scpSearchGobj(1034)->active = 0;
}

void actSt04lTorch1_1Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1026) == 0) {
        _ACTWait(1);
    }

    gflagOn(184);
}

void actSt04lTorch1_2Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1027) == 0) {
        _ACTWait(1);
    }

    gflagOn(185);
}

void actSt04lTorch2_1Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1108) == 0) {
        _ACTWait(1);
    }

    gflagOn(186);
}

void actSt04lTorch2_2Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1109) == 0) {
        _ACTWait(1);
    }

    gflagOn(187);
}

void actSt04lTorch3_1Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1110) == 0) {
        _ACTWait(1);
    }

    gflagOn(190);
}

void actSt04lTorch3_2Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1111) == 0) {
        _ACTWait(1);
    }

    gflagOn(191);
}

void actSt04lTorch2_1XLChk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1030) == 0) {
        _ACTWait(1);
    }

    gflagOn(188);
}

void actSt04lTorch2_2XLChk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1031) == 0) {
        _ACTWait(1);
    }

    gflagOn(189);
}
#else
void actSt04lSwordChk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    scpSearchGobj(1031)->active = 0;
#else
    scpSearchGobj(1122)->active = 0;
#endif
}

void actSt04lTorch1_1Chk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (scpIsTorchLightOn(1023) == 0) {
#else
    while (scpIsTorchLightOn(1114) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(184);
#else
    gflagOn(204);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(206, 1, 0);
#else
    stage_SetAnimation(210, 1, 0);
#endif
#endif
}

void actSt04lTorch1_2Chk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (scpIsTorchLightOn(1024) == 0) {
#else
    while (scpIsTorchLightOn(1115) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(185);
#else
    gflagOn(205);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(207, 1, 0);
#else
    stage_SetAnimation(211, 1, 0);
#endif
#endif
}

void actSt04lTorch2_1Chk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (scpIsTorchLightOn(1105) == 0) {
#else
    while (scpIsTorchLightOn(1202) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(186);
#else
    gflagOn(206);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(208, 1, 0);
#else
    stage_SetAnimation(212, 1, 0);
#endif
#endif
}

void actSt04lTorch2_2Chk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (scpIsTorchLightOn(1106) == 0) {
#else
    while (scpIsTorchLightOn(1203) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(187);
#else
    gflagOn(207);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(209, 1, 0);
#else
    stage_SetAnimation(213, 1, 0);
#endif
#endif
}

void actSt04lTorch3_1Chk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (scpIsTorchLightOn(1107) == 0) {
#else
    while (scpIsTorchLightOn(1204) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(190);
#else
    gflagOn(210);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(210, 1, 0);
#else
    stage_SetAnimation(214, 1, 0);
#endif
#endif
}

void actSt04lTorch3_2Chk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (scpIsTorchLightOn(1108) == 0) {
#else
    while (scpIsTorchLightOn(1205) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(191);
#else
    gflagOn(211);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(211, 1, 0);
#else
    stage_SetAnimation(215, 1, 0);
#endif
#endif
}

void actSt04lTorch2_1XLChk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (scpIsTorchLightOn(1027) == 0) {
#else
    while (scpIsTorchLightOn(1118) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(188);
#else
    gflagOn(208);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(208, 1, 0);
#else
    stage_SetAnimation(212, 1, 0);
#endif
#endif
}

void actSt04lTorch2_2XLChk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (scpIsTorchLightOn(1028) == 0) {
#else
    while (scpIsTorchLightOn(1119) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(189);
#else
    gflagOn(209);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(209, 1, 0);
#else
    stage_SetAnimation(213, 1, 0);
#endif
#endif
}
#endif
#endif
