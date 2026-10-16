#include "st04r.h"
#include "st04l.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "gobj_process.h"
#include "obj_manager.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act-game.h"
#include "act.h"
#include "commonact.h"
#include "girl_act.h"
#include "way_llf.h"
#include "camera-root.h"
#include "fightSound.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "attackCheckBoundary.h"
#include "item.h"
#include <libvu0.h>
#include "typedef.h"
#include "script.h"
#include "main.h"

static ActMail c1_ball_main_mes[2] = {{376, actSt04rC1BallSwitch}, {396}}; /* derived name */

static ActMail c1_ball_mes[2] = {{397}, {396}}; /* derived name */

static ActMail c1_ball_switch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail c2_ball_main_mes[2] = {{376, actSt04rC2BallSwitch}, {396}}; /* derived name */

static ActMail c2_ball_mes[2] = {{397}, {396}}; /* derived name */

static ActMail c2_ball_switch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail c3_ball_main_mes[2] = {{377, actSt04rC3BallSwitch}, {396}}; /* derived name */

static ActMail c3_ball_mes[2] = {{397}, {396}}; /* derived name */

static ActMail c3_ball_switch_mes[2] = {{397}, {396}}; /* derived name */

static ActMail crest01_mes[2] = {{397}, {396}}; /* derived name */

static ActMail crest02_mes[2] = {{397}, {396}}; /* derived name */

static ActMail crest03_mes[2] = {{397}, {396}}; /* derived name */

static ActMail solar_beam_mes[2] = {{397}, {396}}; /* derived name */

static ActMail solar_stage_change_mes[2] = {{397}, {396}}; /* derived name */

static ActMail stair_mes[2] = {{397}, {396}}; /* derived name */

static ActMail sekizo_mes[2] = {{397}, {396}}; /* derived name */

static ActMail rope1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail rope2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail brg1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail rope3_mes[2] = {{397}, {396}}; /* derived name */

static ActMail rope4_mes[2] = {{397}, {396}}; /* derived name */

static ActMail brg2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail brg1_way_mes[2] = {{397}, {396}}; /* derived name */

static ActMail brg2_way_mes[2] = {{397}, {396}}; /* derived name */

static ActMail monyou01_mes[2] = {{397}, {396}}; /* derived name */

static ActMail monyou02_mes[2] = {{397}, {396}}; /* derived name */

static ActMail monyou03_mes[2] = {{397}, {396}}; /* derived name */

static ActMail monyou04_mes[2] = {{397}, {396}}; /* derived name */

static ActMail monyou05_mes[2] = {{397}, {396}}; /* derived name */

static ActMail monyou06_mes[2] = {{397}, {396}}; /* derived name */

static ActMail monyou07_mes[2] = {{397}, {396}}; /* derived name */

static ActMail barricade_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondola_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondola2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondola_chk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail gondola_chara_chk_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch1_1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch1_2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch2_1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch2_2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch3_1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch3_2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch2_1xl_mes[2] = {{397}, {396}}; /* derived name */

static ActMail torch2_2xl_mes[2] = {{397}, {396}}; /* derived name */

/* The look-at point both characters face in the crest cutscene. */
static const ConstVec crestFacePos = {{0.0f, 0.0f, -5000.0f, 1.0f}}; /* derived name */

/* .sdata: the room's stream handles and shakes. */
SqEntry *solar4r = 0;

SqEntry *ball1_4r = 0;

SqEntry *ball2_4r = 0;

SqEntry *ball3_4r = 0;

SqEntry *crest1_4r = 0;

SqEntry *crest2_4r = 0;

SqEntry *crest3_4r = 0;

SqEntry *stair5d = 0;

SqEntry *sekizo5c = 0;

SqEntry *st05d_hasi = 0;

int st04r_yure = 0;

unsigned char st04r_yure_vol = 0;

int sekizo_4r = 0;

unsigned char sekizo_4r_vol = 0;

void actSt05eEnd(void)
{
    if (solar4r != 0) {
        if (gflagChk(209) == 0) {
            soundDataClose(solar4r);
        }
    }
}

void actSt05cInit(void)
{
    if (gflagChk(249) == 0) {
        stage_SetAnimation(304, 0, 0);
    } else {
        stage_SetAnimation(304, 0, -1);
    }

    if (gflagChk(250) == 0) {
        stage_SetAnimation(305, 0, 0);
    } else {
        stage_SetAnimation(305, 0, -1);
    }

    if (gflagChk(251) == 0) {
        stage_SetAnimation(306, 0, 0);
    } else {
        stage_SetAnimation(306, 0, -1);
    }

    if (gflagChk(252) == 0) {
        stage_SetAnimation(307, 0, 0);
    } else {
        stage_SetAnimation(307, 0, -1);
    }

    if (gflagChk(253) == 0) {
        stage_SetAnimation(308, 0, 0);
    } else {
        stage_SetAnimation(308, 0, -1);
    }

    if (gflagChk(254) == 0) {
        stage_SetAnimation(309, 0, 0);
    } else {
        stage_SetAnimation(309, 0, -1);
    }

    if (gflagChk(255) == 0) {
        stage_SetAnimation(310, 0, 0);
    } else {
        stage_SetAnimation(310, 0, -1);
    }

    if (gflagChk(229) == 0) {
        SetWayGroupActive(1, 0);
    } else {
        SetWayGroupActive(1, 1);
    }

    if (gflagChk(234) == 0) {
        stage_SetAnimation(295, 0, 0);
    } else {
        stage_SetAnimation(295, 0, -1);
    }

    if (gflagChk(235) == 0) {
        stage_SetAnimation(296, 0, 0);
    } else {
        stage_SetAnimation(296, 0, -1);
    }

    if (gflagChk(228) == 0) {
        scpSearchGobj(1279)->active = 0;
    }
}

void actSt05dInit(void)
{
    if (gflagChk(234) == 0) {
        stage_SetAnimation(295, 0, 0);

        SetWayGroupActive(3, 0);
    } else {
        stage_SetAnimation(295, 0, -1);

        SetWayGroupActive(3, 1);
    }

    if (gflagChk(235) == 0) {
        stage_SetAnimation(296, 0, 0);

        SetWayGroupActive(4, 0);
    } else {
        stage_SetAnimation(296, 0, -1);

        SetWayGroupActive(4, 1);
    }

    if (gflagChk(228) == 0) {
        stage_SetAnimation(297, 0, 0);
        stage_SetAnimation(317, 0, 0);
    } else {
        stage_SetAnimation(297, 0, -1);
        stage_SetAnimation(317, 0, -1);
    }

    if (gflagChk(249) == 0) {
        stage_SetAnimation(304, 0, 0);
    } else {
        stage_SetAnimation(304, 0, -1);
    }

    if (gflagChk(250) == 0) {
        stage_SetAnimation(305, 0, 0);
    } else {
        stage_SetAnimation(305, 0, -1);
    }

    if (gflagChk(251) == 0) {
        stage_SetAnimation(306, 0, 0);
    } else {
        stage_SetAnimation(306, 0, -1);
    }

    if (gflagChk(252) == 0) {
        stage_SetAnimation(307, 0, 0);
    } else {
        stage_SetAnimation(307, 0, -1);
    }

    if (gflagChk(253) == 0) {
        stage_SetAnimation(308, 0, 0);
    } else {
        stage_SetAnimation(308, 0, -1);
    }

    if (gflagChk(254) == 0) {
        stage_SetAnimation(309, 0, 0);
    } else {
        stage_SetAnimation(309, 0, -1);
    }

    if (gflagChk(255) == 0) {
        stage_SetAnimation(310, 0, 0);
    } else {
        stage_SetAnimation(310, 0, -1);
    }

    if (gflagChk(148) != 0 && gflagChk(209) == 0) {
        stage_SetAnimation(314, 0, -1);
    }

    if (gflagChk(148) == 0 || gflagChk(209) != 0) {
        stage_SetAnimation(314, 0, 0);
    }

    if (gflagChk(257) != 0) {
        stage_SetAnimation(201, 0, 200);
    } else {
        stage_SetAnimation(201, 0, 0);
    }

    if (gflagChk(207) == 0) {
        scpSearchGobj(1353)->active = 0;
    } else {
        scpSearchGobj(1352)->active = 0;
    }
}

void actSt05eInit(void)
{
    if (gflagChk(206) == 0) {
        SetWayGroupActive(5, 0);
    } else {
        SetWayGroupActive(5, 1);
    }

    if (gflagChk(234) == 0) {
        stage_SetAnimation(295, 0, 0);
    } else {
        stage_SetAnimation(295, 0, -1);
    }

    if (gflagChk(235) == 0) {
        stage_SetAnimation(296, 0, 0);
    } else {
        stage_SetAnimation(296, 0, -1);
    }
}

void actSt04rC1BallTurn(GObj *volatile self)
{
    lt_switch_layout(51);

    scpSleepEnemyAll();

    gflagOn(225);
    _ACTWait(60);

    scpAdpcmPlayRequestFunc(80, &ball1_4r, 1, 1, 1);

    while (ball1_4r == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(284, 1, 0);

    while (stage_CheckAnimationFinish(284) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(1304)->active = 1;
    scpSearchGobj(1305)->active = 1;

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 6);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}

void actSt04rC2BallTurn(GObj *volatile self)
{
    lt_switch_layout(51);

    scpSleepEnemyAll();

    gflagOn(226);
    _ACTWait(60);

    scpAdpcmPlayRequestFunc(80, &ball2_4r, 1, 1, 1);

    while (ball2_4r == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(285, 1, 0);

    while (stage_CheckAnimationFinish(285) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(1382)->active = 1;
    scpSearchGobj(1383)->active = 1;

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 6);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}

void actSt04rC3BallTurn(GObj *volatile self)
{
    lt_switch_layout(51);

    scpSleepEnemyAll();

    gflagOn(227);
    _ACTWait(60);

    scpAdpcmPlayRequestFunc(80, &ball3_4r, 1, 1, 1);

    while (ball3_4r == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(286, 1, 0);

    while (stage_CheckAnimationFinish(286) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(1384)->active = 1;
    scpSearchGobj(1385)->active = 1;

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}

void actSt04rCrest02(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(219) == 0) {
        if (current_stage_no == 28) {
            stage_SetAnimation(278, 0, 0);
        } else {
            stage_SetAnimation(279, 0, 0);
        }

        crest02_mes[0].func = actSt04rCrest2Main;
        act->mail = crest02_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        if (current_stage_no == 28) {
            stage_SetAnimation(278, 0, -1);
        } else {
            stage_SetAnimation(279, 0, -1);
        }

        scpBoyControlReadDisable = 0;
    }
}

void actSt04rCrestMain(GObj *volatile self)
{
    while (scpIsTorchLightOn(1304) == 0 || scpIsTorchLightOn(1305) == 0 || gflagChk(225) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(26, &crest1_4r, 0, 1, 1);

    while (crest1_4r == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(276, 1, 0);

    while (stage_CheckAnimationFrame(276, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    st04r_yure = iosPadActRequest(boyPad, 10);
    st04r_yure_vol = 128;
    iosPadActVolumeSet(st04r_yure, 128);

    while (stage_CheckAnimationFrame(276, 190, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(st04r_yure);

    while (stage_CheckAnimationFinish(276) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    lt_switch_layout(50);

    scpBoyControlReadDisable = 0;
    _ACTWait(1);

    gflagOn(218);
    gflagOn(221);
    gflagOff(222);
    gflagOff(224);
    gflagOff(208);
}

void actSt04rCrest2Main(GObj *volatile self)
{
    if (current_stage_no == 28) {
        while (scpIsTorchLightOn(1308) == 0 || scpIsTorchLightOn(1309) == 0 || gflagChk(226) == 0) {
            _ACTWait(1);
        }
    }

    if (current_stage_no == 29) {
        while (scpIsTorchLightOn(1382) == 0 || scpIsTorchLightOn(1383) == 0 || gflagChk(226) == 0) {
            _ACTWait(1);
        }
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(24, &crest2_4r, 0, 1, 1);

    while (crest2_4r == 0) {
        _ACTWait(1);
    }

    if (current_stage_no == 28) {
        stage_SetAnimation(278, 1, 0);

        while (stage_CheckAnimationFrame(278, 30, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        st04r_yure = iosPadActRequest(boyPad, 10);
        st04r_yure_vol = 128;
        iosPadActVolumeSet(st04r_yure, 128);

        while (stage_CheckAnimationFrame(278, 190, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        iosPadActStop(st04r_yure);

        while (stage_CheckAnimationFinish(278) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        gflagOn(223);
    } else {
        stage_SetAnimation(279, 1, 0);

        while (stage_CheckAnimationFrame(279, 30, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        st04r_yure = iosPadActRequest(boyPad, 10);
        st04r_yure_vol = 128;
        iosPadActVolumeSet(st04r_yure, 128);

        while (stage_CheckAnimationFrame(279, 190, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        iosPadActStop(st04r_yure);

        while (stage_CheckAnimationFinish(279) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        gflagOn(222);
    }

    lt_switch_layout(50);

    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
    _ACTWait(1);

    gflagOn(219);
    gflagOff(221);
    gflagOff(224);
    gflagOff(208);
}

void actSt04rCrest3Main(GObj *volatile self)
{
    while (scpIsTorchLightOn(1384) == 0 || scpIsTorchLightOn(1385) == 0 || gflagChk(227) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    scpSleepEnemyOne(3453);

    gflagOn(152);

    fightSoundProcessRequestPause();

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(23, &crest3_4r, 0, 1, 1);

    while (crest3_4r == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(280, 1, 0);

    while (stage_CheckAnimationFrame(280, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    st04r_yure = iosPadActRequest(boyPad, 10);
    st04r_yure_vol = 128;
    iosPadActVolumeSet(st04r_yure, 128);

    while (stage_CheckAnimationFrame(280, 190, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(st04r_yure);

    while (stage_CheckAnimationFinish(280) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyOne(3453);

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);

    fightSoundProcessRequestStart();
    _ACTWait(1);

    gflagOn(220);
    gflagOff(221);
    gflagOff(222);
    gflagOn(224);
    gflagOff(208);
}

void actSt04rSolarBeam(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    solar4r = 0;

    if (gflagChk(209) == 0) {
        scpAdpcmPlayRequestFunc(27, &solar4r, 0, 1, 0);

        if (gflagChk(218) != 0 && gflagChk(219) != 0 && gflagChk(220) != 0 && gflagChk(207) != 0) {
            if (boyGObj != 0) {
                scpPlayMot(boyGObj, 0);
            }

            scpBoyControlReadDisable = 1;
            gflagOn(356);

            scpFadeOut(255.0f, 0, 0, 0);

            while (solar4r == 0) {
                _ACTWait(1);
            }

            scpFadeIn(6.0f);
        }

        solar_beam_mes[0].func = actSt04rSolarBeamChk;
        act->mail = solar_beam_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        scpBoyControlReadDisable = 0;
    }
}

void actSt04rSolarBeamChk(GObj *volatile self)
{
    while (gflagChk(218) == 0 || gflagChk(219) == 0 || gflagChk(220) == 0 || gflagChk(207) == 0) {
        _ACTWait(1);
    }

    gflagOn(209);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    while (solar4r == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(solar4r->stream);

    preload(15);

    stage_SetAnimation(313, 1, 0);
    stage_SetAnimation(261, 1, 0);
    _ACTWait(30);

    while (stage_CheckAnimationFinish(261) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;

    scpWakeupEnemyAll();

    RequestStageChange(15, boyGObj, girlGObj, 2.0f, 8.0f);
}

void actSt04rStairChk(GObj *volatile self)
{
    long long buf[2];
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
    gflagOn(228);

    scpSleepEnemyAll();

    scpSearchGobj(1420)->active = 0;

    stage_SetAnimation(318, -1, -2);
    _ACTWait(60);

    scpAdpcmPlayRequestFunc(59, &stair5d, 1, 1, 1);

    while (stair5d == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(317, 1, 0);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);

    scpPlayPosSet(boyGObj, -55.0f, 28.0f, -3881.0f);
    scpPlayPosSet(girlGObj, 58.0f, 28.0f, -3891.0f);

    buf[0] = crestFacePos.d[0];
    buf[1] = crestFacePos.d[1];
    sceVu0SubVector(dir, buf, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    buf[0] = crestFacePos.d[0];
    buf[1] = crestFacePos.d[1];
    sceVu0SubVector(dir, buf, test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, dir);

    while (stage_CheckAnimationFinish(317) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

    stage_SetAnimation(297, 1, 0);

    while (stage_CheckAnimationFrame(297, 140, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    st04r_yure = iosPadActRequest(boyPad, 9);
    st04r_yure_vol = 128;
    iosPadActVolumeSet(st04r_yure, 128);

    while (stage_CheckAnimationFinish(297) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(st04r_yure);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}

void actSt04rSekizoChk(GObj *volatile self)
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

    scpAdpcmPlayRequestFunc(18, &sekizo5c, 1, 1, 1);

    while (sekizo5c == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(1, 1);
    _ACTWait(60);

    stage_SetAnimation(298, 1, 0);

    sekizo_4r = iosPadActRequest(boyPad, 9);
    sekizo_4r_vol = 128;
    iosPadActVolumeSet(sekizo_4r, 128);

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);

    scpPlayPosSet(girlGObj, 0.0f, -1300.0f, -1700.0f);
    scpPlayPosSet(boyGObj, 20.0f, -1300.0f, -1700.0f);
    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(self), test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, dir);

    scpBoyControlReadDisable = 1;

    sceVu0SubVector(dir, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    scpSekizouCheckPoint();

    scpPlayMot(girlGObj, 572);
    scpPlayWaitMotEnd(girlGObj);

    gflagOn(229);

    while (stage_CheckAnimationFrame(298, 151, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(sekizo_4r);

    while (stage_CheckAnimationFinish(298) == 0) {
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

void actSt04rRope1Chk(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(236) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1355))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(291, 1, 0);

            while (stage_CheckAnimationFinish(291) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1355)->active = 0;

            gflagOn(236);

            stage_SetAnimation(287, 1, 0);

            while (stage_CheckAnimationFinish(287) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        }
    }
}

void actSt04rRope2Chk(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(237) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1356))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(292, 1, 0);

            while (stage_CheckAnimationFinish(292) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1356)->active = 0;

            gflagOn(237);

            stage_SetAnimation(288, 1, 0);

            while (stage_CheckAnimationFinish(288) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        }
    }
}

void actSt04rBrg1Chk(GObj *volatile self)
{
    while (gflagChk(236) == 0 || gflagChk(237) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    gflagOn(234);
    _ACTWait(60);

    scpAdpcmPlayRequestFunc(84, &st05d_hasi, 1, 1, 1);

    while (st05d_hasi == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(295, 1, 0);

    while (stage_CheckAnimationFrame(295, 75, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFinish(295) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}

void actSt04rRope3Chk(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(238) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1357))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(293, 1, 0);

            while (stage_CheckAnimationFinish(293) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1357)->active = 0;

            gflagOn(238);

            stage_SetAnimation(289, 1, 0);

            while (stage_CheckAnimationFinish(289) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        }
    }
}

void actSt04rRope4Chk(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(239) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1358))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(294, 1, 0);

            while (stage_CheckAnimationFinish(294) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1358)->active = 0;

            gflagOn(239);

            stage_SetAnimation(290, 1, 0);

            while (stage_CheckAnimationFinish(290) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        }
    }
}

void actSt04rBrg2Chk(GObj *volatile self)
{
    while (gflagChk(238) == 0 || gflagChk(239) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    gflagOn(235);
    _ACTWait(60);

    scpAdpcmPlayRequestFunc(84, &st05d_hasi, 1, 1, 1);

    while (st05d_hasi == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(296, 1, 0);

    while (stage_CheckAnimationFrame(296, 75, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFinish(296) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}

void actSt04rMonyou01Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x1000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;

    gflagOn(249);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(boyGObj);
        scpPlayStart(girlGObj);

        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

    stage_SetAnimation(304, 1, 0);

    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(304, 30, 0) == 0) {
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

void actSt04rMonyou02Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x2000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;

    gflagOn(250);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(boyGObj);
        scpPlayStart(girlGObj);

        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

    stage_SetAnimation(305, 1, 0);

    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(305, 30, 0) == 0) {
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

void actSt04rMonyou03Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x3000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;

    gflagOn(251);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(boyGObj);
        scpPlayStart(girlGObj);

        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

    stage_SetAnimation(306, 1, 0);

    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(306, 30, 0) == 0) {
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

void actSt04rMonyou04Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x4000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x4000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;

    gflagOn(252);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(boyGObj);
        scpPlayStart(girlGObj);

        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

    stage_SetAnimation(307, 1, 0);

    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(307, 30, 0) == 0) {
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

void actSt04rMonyou05Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x5000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x5000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;

    gflagOn(253);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(boyGObj);
        scpPlayStart(girlGObj);

        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

    stage_SetAnimation(308, 1, 0);

    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(308, 30, 0) == 0) {
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

void actSt04rMonyou06Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x6000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x6000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;

    gflagOn(254);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(boyGObj);
        scpPlayStart(girlGObj);

        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

    stage_SetAnimation(309, 1, 0);

    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(309, 30, 0) == 0) {
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

void actSt04rMonyou07Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0x7000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0x7000000) == 0) {
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 1;

    gflagOn(255);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(boyGObj);
        scpPlayStart(girlGObj);

        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

    stage_SetAnimation(310, 1, 0);

    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(310, 30, 0) == 0) {
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

void actSt04rGondolaChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttr(boyGObj, 0xA000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    _ACTWait(15);

    if (gflagChk(257) != 0) {
        stage_SetAnimation(201, 1, 200);

        scpWakeupItemWithBoundary(-675.0f, -150.0f, -1600.0f, 200.0f);

        while (stage_CheckAnimationFrame(201, 220, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(1297, 0, 0, 1);

        while (stage_CheckAnimationFrame(201, 240, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(1298, 0, 0, 1);

        while (stage_CheckAnimationFrame(201, 250, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(1295, 0, 0, 1);

        while (stage_CheckAnimationFrame(201, 415, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(1296, 0, 0, 1);

        while (stage_CheckAnimationFinish(201) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        gflagOff(257);
    } else {
        stage_SetAnimation(201, 1, 0);

        scpWakeupItemWithBoundary(-675.0f, -1200.0f, -1600.0f, 200.0f);

        soundSeDefPlay(1295, 0, 0, 1);

        while (stage_CheckAnimationFrame(201, 145, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(1296, 0, 0, 1);
        soundSeDefPlay(1297, 0, 0, 1);

        while (stage_CheckAnimationFrame(201, 170, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(1298, 0, 0, 1);

        while (stage_CheckAnimationFrame(201, 200, 1) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        gflagOn(257);
    }

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);

    scpWakeupEnemyAll();

    gondola_chk_mes[0].func = actSt04rGondolaCharaChk;
    sub->mail = gondola_chk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt04rSolarStageChange(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(209) == 0) {
        solar_stage_change_mes[0].func = actSt04rSolarStageChangeChk;
        act->mail = solar_stage_change_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04rCrest01(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(218) == 0) {
        stage_SetAnimation(276, 0, 0);

        crest01_mes[0].func = actSt04rCrestMain;
        act->mail = crest01_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(276, 0, -1);
        scpBoyControlReadDisable = 0;
    }
}

void actSt04rCrest03(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(220) == 0) {
        stage_SetAnimation(280, 0, 0);

        crest03_mes[0].func = actSt04rCrest3Main;
        act->mail = crest03_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(280, 0, -1);
        scpBoyControlReadDisable = 0;
    }
}

void actSt04rC1Ball(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(225) == 0) {
        scpSearchGobj(1304)->active = 0;
        scpSearchGobj(1305)->active = 0;

        stage_SetAnimation(284, 0, 0);

        c1_ball_mes[0].func = actSt04rC1BallMain;
        act->mail = c1_ball_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(284, 0, -1);
    }
}

void actSt04rC2Ball(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(226) == 0) {
        scpSearchGobj(1382)->active = 0;
        scpSearchGobj(1383)->active = 0;

        stage_SetAnimation(285, 0, 0);

        c2_ball_mes[0].func = actSt04rC2BallMain;
        act->mail = c2_ball_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(285, 0, -1);
    }
}

void actSt04rC3Ball(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(227) == 0) {
        scpSearchGobj(1384)->active = 0;
        scpSearchGobj(1385)->active = 0;

        stage_SetAnimation(286, 0, 0);

        c3_ball_mes[0].func = actSt04rC3BallMain;
        act->mail = c3_ball_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(286, 0, -1);
    }
}

void actSt04rStair(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(228) == 0) {
        if (girlGObj != 0) {
            stair_mes[0].func = actSt04rStairChk;
            act->mail = stair_mes;
            ACTSendMailCorrect(self, 397);
            _ACTWait(0);
        }
    } else {
        scpSearchGobj(1420)->active = 0;

        stage_SetAnimation(318, -1, -2);
    }
}

void actSt04rBrg1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(234) == 0) {
        brg1_mes[0].func = actSt04rBrg1Chk;
        act->mail = brg1_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04rBrg2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(235) == 0) {
        brg2_mes[0].func = actSt04rBrg2Chk;
        act->mail = brg2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04rBrg1Way(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(234) == 0) {
        brg1_way_mes[0].func = actSt04rBrg1WayChk;
        act->mail = brg1_way_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04rBrg2Way(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(235) == 0) {
        brg2_way_mes[0].func = actSt04rBrg2WayChk;
        act->mail = brg2_way_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04rRope1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(236) == 0) {
        stage_SetAnimation(287, 0, 0);

        rope1_mes[0].func = actSt04rRope1Chk;
        act->mail = rope1_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(287, 0, -1);

        scpSearchGobj(1355)->active = 0;
    }
}

void actSt04rRope2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(237) == 0) {
        stage_SetAnimation(288, 0, 0);

        rope2_mes[0].func = actSt04rRope2Chk;
        act->mail = rope2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(288, 0, -1);

        scpSearchGobj(1356)->active = 0;
    }
}

void actSt04rRope3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(238) == 0) {
        stage_SetAnimation(289, 0, 0);

        rope3_mes[0].func = actSt04rRope3Chk;
        act->mail = rope3_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(289, 0, -1);

        scpSearchGobj(1357)->active = 0;
    }
}

void actSt04rRope4(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(239) == 0) {
        stage_SetAnimation(290, 0, 0);

        rope4_mes[0].func = actSt04rRope4Chk;
        act->mail = rope4_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(290, 0, -1);

        scpSearchGobj(1358)->active = 0;
    }
}

void actSt04rSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(229) == 0) {
        stage_SetAnimation(298, 0, 0);

        sekizo_mes[0].func = actSt04rSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(298, 0, -1);
    }
}

void actSt04rBarricade(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(240) == 0) {
        stage_SetAnimation(311, 0, 0);

        barricade_mes[0].func = actSt04rBarricadeChk;
        act->mail = barricade_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(311, 0, -1);
    }
}

void actSt04rGondola(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(257) != 0) {
        stage_SetAnimation(201, 0, 200);

        gondola_mes[0].func = actSt04rGondolaChk;
        act->mail = gondola_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(201, 0, 0);

        gondola2_mes[0].func = actSt04rGondolaChk;
        act->mail = gondola2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04rCrest01XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(218) == 0) {
        stage_SetAnimation(281, 0, 0);
    } else {
        stage_SetAnimation(281, 0, -1);
    }
}

void actSt04rCrest02XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(219) == 0) {
        stage_SetAnimation(282, 0, 0);
    } else {
        stage_SetAnimation(282, 0, -1);
    }
}

void actSt04rCrest03XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(220) == 0) {
        stage_SetAnimation(283, 0, 0);
    } else {
        stage_SetAnimation(283, 0, -1);
    }
}

void actSt04rC2BallXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(226) == 0) {
        stage_SetAnimation(285, 0, 0);

        scpSearchGobj(1308)->active = 0;
        scpSearchGobj(1309)->active = 0;
    } else {
        stage_SetAnimation(285, 0, -1);
    }
}

void actSt04rC3BallXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(227) == 0) {
        stage_SetAnimation(286, 0, 0);

        scpSearchGobj(1459)->active = 0;
        scpSearchGobj(1460)->active = 0;
    } else {
        stage_SetAnimation(286, 0, -1);
    }
}

void actSt04rTorch1_1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(241) == 0) {
        torch1_1_mes[0].func = actSt04rTorch1_1Chk;
        act->mail = torch1_1_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1304);
    }
}

void actSt04rTorch1_2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(242) == 0) {
        torch1_2_mes[0].func = actSt04rTorch1_2Chk;
        act->mail = torch1_2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1305);
    }
}

void actSt04rTorch2_1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(243) != 0 || gflagChk(245) != 0) {
        scpTorchLightOn(1382);
    } else {
        torch2_1_mes[0].func = actSt04rTorch2_1Chk;
        act->mail = torch2_1_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04rTorch2_2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(244) != 0 || gflagChk(246) != 0) {
        scpTorchLightOn(1383);
    } else {
        torch2_2_mes[0].func = actSt04rTorch2_2Chk;
        act->mail = torch2_2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04rTorch3_1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(247) == 0) {
        torch3_1_mes[0].func = actSt04rTorch3_1Chk;
        act->mail = torch3_1_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1384);
    }
}

void actSt04rTorch3_2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(248) == 0) {
        torch3_2_mes[0].func = actSt04rTorch3_2Chk;
        act->mail = torch3_2_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1385);
    }
}

void actSt04rTorch2_1XL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(243) != 0 || gflagChk(245) != 0) {
        scpTorchLightOn(1308);
    } else {
        torch2_1xl_mes[0].func = actSt04rTorch2_1XLChk;
        act->mail = torch2_1xl_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04rTorch2_2XL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(244) != 0 || gflagChk(246) != 0) {
        scpTorchLightOn(1309);
    } else {
        torch2_2xl_mes[0].func = actSt04rTorch2_2XLChk;
        act->mail = torch2_2xl_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt04rTorch3_1XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(247) != 0) {
        scpTorchLightOn(1459);
    }
}

void actSt04rTorch3_2XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(248) != 0) {
        scpTorchLightOn(1460);
    }
}

void actSt04rMonyou01(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(249) == 0) {
        stage_SetAnimation(304, 0, 0);

        monyou01_mes[0].func = actSt04rMonyou01Chk;
        act->mail = monyou01_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(304, 0, -1);
    }
}

void actSt04rMonyou02(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(250) == 0) {
        stage_SetAnimation(305, 0, 0);

        monyou02_mes[0].func = actSt04rMonyou02Chk;
        act->mail = monyou02_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(305, 0, -1);
    }
}

void actSt04rMonyou03(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(251) == 0) {
        stage_SetAnimation(306, 0, 0);

        monyou03_mes[0].func = actSt04rMonyou03Chk;
        act->mail = monyou03_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(306, 0, -1);
    }
}

void actSt04rMonyou04(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(252) == 0) {
        stage_SetAnimation(307, 0, 0);

        monyou04_mes[0].func = actSt04rMonyou04Chk;
        act->mail = monyou04_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(307, 0, -1);
    }
}

void actSt04rMonyou05(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(253) == 0) {
        stage_SetAnimation(308, 0, 0);

        monyou05_mes[0].func = actSt04rMonyou05Chk;
        act->mail = monyou05_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(308, 0, -1);
    }
}

void actSt04rMonyou06(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(254) == 0) {
        stage_SetAnimation(309, 0, 0);

        monyou06_mes[0].func = actSt04rMonyou06Chk;
        act->mail = monyou06_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(309, 0, -1);
    }
}

void actSt04rMonyou07(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(255) == 0) {
        stage_SetAnimation(310, 0, 0);

        monyou07_mes[0].func = actSt04rMonyou07Chk;
        act->mail = monyou07_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(310, 0, -1);
    }
}

void actSt05cDoorInit(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(148) != 0 && gflagChk(209) == 0) {
        stage_SetAnimation(314, 0, -1);
    }

    if (gflagChk(148) == 0 || gflagChk(209) != 0) {
        stage_SetAnimation(314, 0, 0);
    }
}

void actSt04rC1BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = c1_ball_main_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt04rC1BallSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    c1_ball_switch_mes[0].func = actSt04rC1BallTurn;
    sub->mail = c1_ball_switch_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt04rC2BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = c2_ball_main_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt04rC2BallSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    c2_ball_switch_mes[0].func = actSt04rC2BallTurn;
    sub->mail = c2_ball_switch_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt04rC3BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = c3_ball_main_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt04rC3BallSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    c3_ball_switch_mes[0].func = actSt04rC3BallTurn;
    sub->mail = c3_ball_switch_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt04rSolarStageChangeChk(GObj *volatile self)
{
    while (gflagChk(218) == 0 || gflagChk(219) == 0 || gflagChk(220) == 0 || gflagChk(207) == 0) {
        _ACTWait(1);
    }

    RequestStageChange(8, boyGObj, girlGObj, 2.0f, 8.0f);
}

void actSt04rStairEvent(int x)
{
    volatile int local = x;
}

void actSt04rRope1Event(int x)
{
    volatile int local = x;
}

void actSt04rRope2Event(int x)
{
    volatile int local = x;
}

void actSt04rBrg1Event(int x)
{
    volatile int local = x;
}

void actSt04rRope3Event(int x)
{
    volatile int local = x;
}

void actSt04rRope4Event(int x)
{
    volatile int local = x;
}

void actSt04rBrg2Event(int x)
{
    volatile int local = x;
}

void actSt04rBrg1WayChk(GObj *volatile self)
{
    while (gflagChk(234) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(3, 1);
}

void actSt04rBrg2WayChk(GObj *volatile self)
{
    while (gflagChk(234) == 0 || gflagChk(235) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(4, 1);
}

void actSt04rMonyou01Event(int x)
{
    volatile int local = x;
}

void actSt04rMonyou02Event(int x)
{
    volatile int local = x;
}

void actSt04rMonyou03Event(int x)
{
    volatile int local = x;
}

void actSt04rMonyou04Event(int x)
{
    volatile int local = x;
}

void actSt04rMonyou05Event(int x)
{
    volatile int local = x;
}

void actSt04rMonyou06Event(int x)
{
    volatile int local = x;
}

void actSt04rMonyou07Event(int x)
{
    volatile int local = x;
}

void actSt04rBarricadeEvent(int x)
{
    volatile int local = x;
}

void actSt04rBarricadeChk(GObj *volatile self)
{
    GObj *n;

    while ((n = scpIsBombExplode(19)) == 0 || scpTriggerBall(self, n, 350.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    gflagOn(240);
    _ACTWait(5);

    stage_SetAnimation(311, 1, 0);

    while (stage_CheckAnimationFinish(311) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}

void actSt04rGondolaCharaChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttr(boyGObj, 0xA000000) != 0) {
        _ACTWait(1);
    }

    gondola_chara_chk_mes[0].func = actSt04rGondolaChk;
    sub->mail = gondola_chara_chk_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt04rTorch1_1Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1304) == 0) {
        _ACTWait(1);
    }

    gflagOn(241);
}

void actSt04rTorch1_2Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1305) == 0) {
        _ACTWait(1);
    }

    gflagOn(242);
}

void actSt04rTorch2_1Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1382) == 0) {
        _ACTWait(1);
    }

    gflagOn(243);
}

void actSt04rTorch2_2Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1383) == 0) {
        _ACTWait(1);
    }

    gflagOn(244);
}

void actSt04rTorch3_1Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1384) == 0) {
        _ACTWait(1);
    }

    gflagOn(247);
}

void actSt04rTorch3_2Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1385) == 0) {
        _ACTWait(1);
    }

    gflagOn(248);
}

void actSt04rTorch2_1XLChk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1308) == 0) {
        _ACTWait(1);
    }

    gflagOn(245);
}

void actSt04rTorch2_2XLChk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1309) == 0) {
        _ACTWait(1);
    }

    gflagOn(246);
}
