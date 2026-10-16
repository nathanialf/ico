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

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec stairSubPos = {{0.0f, 0.0f, -5000.0f, 1.0f}}; /* derived name */

/* .sdata: the room's stream handles, the shake and its volume, and the
   sekizo's pad shake and its volume (aug6 MAIN.MAP order). */
SqEntry *ball1_4l = 0;

SqEntry *ball2_4l = 0;

SqEntry *ball3_4l = 0;

SqEntry *crest1 = 0;

SqEntry *crest2 = 0;

SqEntry *crest3 = 0;

SqEntry *solar4l = 0;

SqEntry *stair4d = 0;

SqEntry *st04d_hasi = 0;

SqEntry *sekizo4c = 0;

SqEntry *oriup4c = 0;

SqEntry *oridown4c = 0;

unsigned int st04l_yure = 0;

unsigned char st04l_yure_vol = 0;

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

void actSt04lC1BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

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
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt04lC2BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

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
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt04lC3BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

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
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

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

    stage_SetAnimation(259, 1, 0);

    while (stage_CheckAnimationFinish(259) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    RequestStageChange(7, boyGObj, 0, 2.0f, 8.0f);
}

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

void actSt04lTuriEvent(int x)
{
    volatile int local = x;
}

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

void actSt04lGondolaCharaChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttr(boyGObj, 0xA000000)) {
        _ACTWait(1);
    }

    gondola_chara[0].func = actSt04lGondolaChk;
    sub->mail = gondola_chara;
    ACTSendMailCorrect(self, 397);
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
