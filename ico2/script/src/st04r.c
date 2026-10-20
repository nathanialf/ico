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

static ActMail c1_ball_main_mes[2] = {{356, actSt04rC1BallSwitch}, {376}}; /* derived name */

static ActMail c1_ball_mes[2] = {{377}, {376}}; /* derived name */

static ActMail c1_ball_switch_mes[2] = {{377}, {376}}; /* derived name */

static ActMail c2_ball_main_mes[2] = {{356, actSt04rC2BallSwitch}, {376}}; /* derived name */

static ActMail c2_ball_mes[2] = {{377}, {376}}; /* derived name */

static ActMail c2_ball_switch_mes[2] = {{377}, {376}}; /* derived name */

static ActMail c3_ball_main_mes[2] = {{357, actSt04rC3BallSwitch}, {376}}; /* derived name */

static ActMail c3_ball_mes[2] = {{377}, {376}}; /* derived name */

static ActMail c3_ball_switch_mes[2] = {{377}, {376}}; /* derived name */

static ActMail crest01_mes[2] = {{377}, {376}}; /* derived name */

static ActMail crest02_mes[2] = {{377}, {376}}; /* derived name */

static ActMail crest03_mes[2] = {{377}, {376}}; /* derived name */

static ActMail solar_beam_mes[2] = {{377}, {376}}; /* derived name */

static ActMail solar_stage_change_mes[2] = {{377}, {376}}; /* derived name */

static ActMail stair_mes[2] = {{377}, {376}}; /* derived name */

static ActMail sekizo_mes[2] = {{377}, {376}}; /* derived name */

static ActMail rope1_mes[2] = {{377}, {376}}; /* derived name */

static ActMail rope2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail brg1_mes[2] = {{377}, {376}}; /* derived name */

static ActMail rope3_mes[2] = {{377}, {376}}; /* derived name */

static ActMail rope4_mes[2] = {{377}, {376}}; /* derived name */

static ActMail brg2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail brg1_way_mes[2] = {{377}, {376}}; /* derived name */

static ActMail brg2_way_mes[2] = {{377}, {376}}; /* derived name */

static ActMail monyou01_mes[2] = {{377}, {376}}; /* derived name */

static ActMail monyou02_mes[2] = {{377}, {376}}; /* derived name */

static ActMail monyou03_mes[2] = {{377}, {376}}; /* derived name */

static ActMail monyou04_mes[2] = {{377}, {376}}; /* derived name */

static ActMail monyou05_mes[2] = {{377}, {376}}; /* derived name */

static ActMail monyou06_mes[2] = {{377}, {376}}; /* derived name */

static ActMail monyou07_mes[2] = {{377}, {376}}; /* derived name */

static ActMail barricade_mes[2] = {{377}, {376}}; /* derived name */

static ActMail gondola_mes[2] = {{377}, {376}}; /* derived name */

static ActMail gondola2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail gondola_chk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail gondola_chara_chk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail torch1_1_mes[2] = {{377}, {376}}; /* derived name */

static ActMail torch1_2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail torch2_1_mes[2] = {{377}, {376}}; /* derived name */

static ActMail torch2_2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail torch3_1_mes[2] = {{377}, {376}}; /* derived name */

static ActMail torch3_2_mes[2] = {{377}, {376}}; /* derived name */

static ActMail torch2_1xl_mes[2] = {{377}, {376}}; /* derived name */

static ActMail torch2_2xl_mes[2] = {{377}, {376}}; /* derived name */

/* No .sbss here in this build: no function of the demo addresses these flags. */

/* The look-at point both characters face in the crest cutscene. */
static const ConstVec crestFacePos = {{0.0f, 0.0f, -5000.0f, 1.0f}}; /* derived name */

/* .sdata: the room's stream handles and shakes, the same nine slots as
   st04l.c's: the solar beam's and the three crests' handles, the bridge's
   handle (actSt04rBrg1Chk and actSt04rBrg2Chk), the crest and stair shake with
   its volume, the statue's shake with its volume (actSt04rSekizoChk). No ball,
   stair or statue stream handle: no function of the demo addresses one. */
SqEntry *solar4r = 0;

SqEntry *crest1_4r = 0;

SqEntry *crest2_4r = 0;

SqEntry *crest3_4r = 0;

SqEntry *st05d_hasi = 0;

int st04r_yure = 0;

unsigned char st04r_yure_vol = 0;

int sekizo_4r = 0;

unsigned char sekizo_4r_vol = 0; /* derived name */

void actSt05eEnd(void)
{
    if (gflagChk(200) == 0) {
        soundDataClose(solar4r);
    }
}

void actSt05cInit(void)
{
    if (gflagChk(240) == 0) {
        stage_SetAnimation(271, 0, 0);
    } else {
        stage_SetAnimation(271, 0, -1);
    }

    if (gflagChk(241) == 0) {
        stage_SetAnimation(272, 0, 0);
    } else {
        stage_SetAnimation(272, 0, -1);
    }

    if (gflagChk(242) == 0) {
        stage_SetAnimation(273, 0, 0);
    } else {
        stage_SetAnimation(273, 0, -1);
    }

    if (gflagChk(243) == 0) {
        stage_SetAnimation(274, 0, 0);
    } else {
        stage_SetAnimation(274, 0, -1);
    }

    if (gflagChk(244) == 0) {
        stage_SetAnimation(275, 0, 0);
    } else {
        stage_SetAnimation(275, 0, -1);
    }

    if (gflagChk(245) == 0) {
        stage_SetAnimation(276, 0, 0);
    } else {
        stage_SetAnimation(276, 0, -1);
    }

    if (gflagChk(246) == 0) {
        SetWayGroupActive(1, 0);
        stage_SetAnimation(277, 0, 0);
    } else {
        SetWayGroupActive(1, 1);
        stage_SetAnimation(277, 0, -1);
    }

    if (gflagChk(225) == 0) {
        stage_SetAnimation(264, 0, 0);
    } else {
        stage_SetAnimation(264, 0, -1);
    }

    if (gflagChk(226) == 0) {
        stage_SetAnimation(265, 0, 0);
    } else {
        stage_SetAnimation(265, 0, -1);
    }
}

void actSt05dInit(void)
{
    if (gflagChk(225) == 0) {
        stage_SetAnimation(264, 0, 0);

        SetWayGroupActive(3, 0);
    } else {
        stage_SetAnimation(264, 0, -1);

        SetWayGroupActive(3, 1);
    }

    if (gflagChk(226) == 0) {
        stage_SetAnimation(265, 0, 0);

        SetWayGroupActive(4, 0);
    } else {
        stage_SetAnimation(265, 0, -1);

        SetWayGroupActive(4, 1);
    }

    if (gflagChk(219) == 0) {
        stage_SetAnimation(266, 0, 0);
        stage_SetAnimation(284, 0, 0);
    } else {
        stage_SetAnimation(266, 0, -1);
        stage_SetAnimation(284, 0, -1);
    }

    if (gflagChk(240) == 0) {
        stage_SetAnimation(271, 0, 0);
    } else {
        stage_SetAnimation(271, 0, -1);
    }

    if (gflagChk(241) == 0) {
        stage_SetAnimation(272, 0, 0);
    } else {
        stage_SetAnimation(272, 0, -1);
    }

    if (gflagChk(242) == 0) {
        stage_SetAnimation(273, 0, 0);
    } else {
        stage_SetAnimation(273, 0, -1);
    }

    if (gflagChk(243) == 0) {
        stage_SetAnimation(274, 0, 0);
    } else {
        stage_SetAnimation(274, 0, -1);
    }

    if (gflagChk(244) == 0) {
        stage_SetAnimation(275, 0, 0);
    } else {
        stage_SetAnimation(275, 0, -1);
    }

    if (gflagChk(245) == 0) {
        stage_SetAnimation(276, 0, 0);
    } else {
        stage_SetAnimation(276, 0, -1);
    }

    if (gflagChk(246) == 0) {
        stage_SetAnimation(277, 0, 0);
    } else {
        stage_SetAnimation(277, 0, -1);
    }

    if (gflagChk(141) != 0 && gflagChk(200) == 0) {
        stage_SetAnimation(281, 0, -1);
    }

    if (gflagChk(141) == 0 || gflagChk(200) != 0) {
        stage_SetAnimation(281, 0, 0);
    }

    if (gflagChk(248) != 0) {
        stage_SetAnimation(180, 0, 200);
    } else {
        stage_SetAnimation(180, 0, 0);
    }

    if (gflagChk(198) == 0) {
        scpSearchGobj(1287)->active = 0;
    } else {
        scpSearchGobj(1286)->active = 0;
    }
}

void actSt05eInit(void)
{
    if (gflagChk(197) == 0) {
        SetWayGroupActive(5, 0);
    } else {
        SetWayGroupActive(5, 1);
    }

    if (gflagChk(225) == 0) {
        stage_SetAnimation(264, 0, 0);
    } else {
        stage_SetAnimation(264, 0, -1);
    }

    if (gflagChk(226) == 0) {
        stage_SetAnimation(265, 0, 0);
    } else {
        stage_SetAnimation(265, 0, -1);
    }
}

void actSt04rC1BallTurn(GObj *volatile self)
{
    lt_switch_layout(51);

    scpSleepEnemyAll();

    gflagOn(216);
    _ACTWait(60);

    stage_SetAnimation(257, 1, 0);
    scpAdpcmPlayRequestFunc(75, 0, 1, 1, 1);

    while (stage_CheckAnimationFinish(257) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(1239)->active = 1;
    scpSearchGobj(1240)->active = 1;

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 6);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}

void actSt04rC2BallTurn(GObj *volatile self)
{
    lt_switch_layout(51);

    scpSleepEnemyAll();

    gflagOn(217);
    _ACTWait(60);

    stage_SetAnimation(258, 1, 0);
    scpAdpcmPlayRequestFunc(75, 0, 1, 1, 1);

    while (stage_CheckAnimationFinish(258) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(1315)->active = 1;
    scpSearchGobj(1316)->active = 1;

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 6);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}

void actSt04rCrest02(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(210) == 0) {
        if (current_stage_no == 28) {
            stage_SetAnimation(251, 0, 0);
        } else {
            stage_SetAnimation(252, 0, 0);
        }

        crest02_mes[0].func = actSt04rCrest2Main;
        act->mail = crest02_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        if (current_stage_no == 28) {
            stage_SetAnimation(251, 0, -1);
        } else {
            stage_SetAnimation(252, 0, -1);
        }
    }
}

void actSt04rCrestMain(GObj *volatile self)
{
    while (scpIsTorchLightOn(1239) == 0 || scpIsTorchLightOn(1240) == 0 || gflagChk(216) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(29, &crest1_4r, 0, 1, 1);

    while (crest1_4r == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(249, 1, 0);

    while (stage_CheckAnimationFrame(249, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    st04r_yure = iosPadActRequest(boyPad, 10);
    st04r_yure_vol = 128;
    iosPadActVolumeSet(st04r_yure, 128);

    while (stage_CheckAnimationFrame(249, 190, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(st04r_yure);

    while (stage_CheckAnimationFinish(249) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    lt_switch_layout(50);

    scpBoyControlReadDisable = 0;
    _ACTWait(1);

    gflagOn(209);
    gflagOn(212);
    gflagOff(213);
    gflagOff(215);
    gflagOff(199);
}

void actSt04rCrest2Main(GObj *volatile self)
{
    if (current_stage_no == 28) {
        while (scpIsTorchLightOn(1243) == 0 || scpIsTorchLightOn(1244) == 0 || gflagChk(217) == 0) {
            _ACTWait(1);
        }
    }

    if (current_stage_no == 29) {
        while (scpIsTorchLightOn(1315) == 0 || scpIsTorchLightOn(1316) == 0 || gflagChk(217) == 0) {
            _ACTWait(1);
        }
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(27, &crest2_4r, 0, 1, 1);

    while (crest2_4r == 0) {
        _ACTWait(1);
    }

    if (current_stage_no == 28) {
        stage_SetAnimation(251, 1, 0);

        while (stage_CheckAnimationFrame(251, 30, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        st04r_yure = iosPadActRequest(boyPad, 10);
        st04r_yure_vol = 128;
        iosPadActVolumeSet(st04r_yure, 128);

        while (stage_CheckAnimationFrame(251, 190, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        iosPadActStop(st04r_yure);

        while (stage_CheckAnimationFinish(251) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        gflagOn(214);
    } else {
        stage_SetAnimation(252, 1, 0);

        while (stage_CheckAnimationFrame(252, 30, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        st04r_yure = iosPadActRequest(boyPad, 10);
        st04r_yure_vol = 128;
        iosPadActVolumeSet(st04r_yure, 128);

        while (stage_CheckAnimationFrame(252, 190, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        iosPadActStop(st04r_yure);

        while (stage_CheckAnimationFinish(252) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        gflagOn(213);
    }

    lt_switch_layout(50);

    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
    _ACTWait(1);

    gflagOn(210);
    gflagOff(212);
    gflagOff(215);
    gflagOff(199);
}

void actSt04rCrest3Main(GObj *volatile self)
{
    while (scpIsTorchLightOn(1317) == 0 || scpIsTorchLightOn(1318) == 0 || gflagChk(218) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;

    gflagOn(145);

    fightSoundProcessRequestPause();

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(26, &crest3_4r, 0, 1, 1);

    while (crest3_4r == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(253, 1, 0);

    while (stage_CheckAnimationFrame(253, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    st04r_yure = iosPadActRequest(boyPad, 10);
    st04r_yure_vol = 128;
    iosPadActVolumeSet(st04r_yure, 128);

    while (stage_CheckAnimationFrame(253, 190, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(st04r_yure);

    while (stage_CheckAnimationFinish(253) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(50);

    scpBoyControlReadDisable = 0;

    fightSoundProcessRequestStart();
    _ACTWait(1);

    gflagOn(211);
    gflagOff(212);
    gflagOff(213);
    gflagOn(215);
    gflagOff(199);
}

void actSt04rSolarBeam(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    solar4r = 0;

    if (gflagChk(200) == 0) {
        scpAdpcmPlayRequestFunc(30, &solar4r, 0, 1, 0);

        if (gflagChk(209) != 0 && gflagChk(210) != 0 && gflagChk(211) != 0 && gflagChk(198) != 0) {
            scpFadeOut(255.0f, 0, 0, 0);

            while (solar4r == 0) {
                _ACTWait(1);
            }

            scpFadeIn(6.0f);
        }

        solar_beam_mes[0].func = actSt04rSolarBeamChk;
        act->mail = solar_beam_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04rSolarBeamChk(GObj *volatile self)
{
    while (gflagChk(209) == 0 || gflagChk(210) == 0 || gflagChk(211) == 0 || gflagChk(198) == 0) {
        _ACTWait(1);
    }

    gflagOn(200);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    while (solar4r == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(solar4r->stream);

    stage_SetAnimation(280, 1, 0);
    stage_SetAnimation(234, 1, 0);
    _ACTWait(30);

    while (stage_CheckAnimationFinish(234) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;

    RequestStageChange(15, boyGObj, girlGObj, 16.0f, 16.0f);
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
    gflagOn(219);

    scpSleepEnemyAll();

    scpSearchGobj(1348)->active = 0;

    stage_SetAnimation(285, -1, -2);
    _ACTWait(60);

    scpAdpcmPlayRequestFunc(56, 0, 1, 1, 1);

    stage_SetAnimation(284, 1, 0);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 521);

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

    while (stage_CheckAnimationFinish(284) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

    stage_SetAnimation(266, 1, 0);

    while (stage_CheckAnimationFrame(266, 140, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    st04r_yure = iosPadActRequest(boyPad, 9);
    st04r_yure_vol = 128;
    iosPadActVolumeSet(st04r_yure, 128);

    while (stage_CheckAnimationFinish(266) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(st04r_yure);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 521);

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

    scpSekizouCheckPoint();

    scpAdpcmPlayRequestFunc(21, 0, 1, 1, 1);

    scpKillEnemyAll();

    scpMaskGeneratorAll();

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;

    gflagOn(220);
    _ACTWait(60);

    stage_SetAnimation(267, 1, 0);

    sekizo_4r = iosPadActRequest(boyPad, 9);
    sekizo_4r_vol = 128;
    iosPadActVolumeSet(sekizo_4r, 128);

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 521);

    scpPlayPosSet(girlGObj, 0.0f, -1300.0f, -1700.0f);
    scpPlayPosSet(boyGObj, 20.0f, -1300.0f, -1700.0f);
    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(self), test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, dir);

    scpBoyControlReadDisable = 1;

    sceVu0SubVector(dir, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    scpPlayMot(girlGObj, 584);
    scpPlayWaitMotEnd(girlGObj);

    while (stage_CheckAnimationFrame(267, 151, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(sekizo_4r);

    scpPlayMot(girlGObj, 521);
    scpPlayEnd(girlGObj);

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);

    lt_switch_layout(50);

    scpBoyControlReadDisable = 0;
}

void actSt04rBrg1Chk(GObj *volatile self)
{
    while (gflagChk(227) == 0 || gflagChk(228) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    gflagOn(225);
    _ACTWait(60);

    scpAdpcmPlayRequestFunc(79, &st05d_hasi, 1, 1, 1);

    while (st05d_hasi == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(264, 1, 0);

    while (stage_CheckAnimationFrame(264, 120, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFinish(264) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}

void actSt04rBrg2Chk(GObj *volatile self)
{
    while (gflagChk(229) == 0 || gflagChk(230) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    gflagOn(226);
    _ACTWait(60);

    scpAdpcmPlayRequestFunc(79, &st05d_hasi, 1, 1, 1);

    while (st05d_hasi == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(265, 1, 0);

    while (stage_CheckAnimationFrame(265, 120, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFinish(265) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}

void actSt04rRope1Chk(GObj *volatile self);
void actSt04rRope2Chk(GObj *volatile self);
void actSt04rRope3Chk(GObj *volatile self);
void actSt04rRope4Chk(GObj *volatile self);

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

    gflagOn(246);
    _ACTWait(5);

    stage_SetAnimation(277, 1, 0);

    soundSeDefPlay(1277, 0, 0, 1);

    while (stage_CheckAnimationFrame(277, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(1, 1);

    scpBoyControlReadDisable = 0;
}

void actSt04rMonyou01Chk(GObj *volatile self);
void actSt04rMonyou02Chk(GObj *volatile self);
void actSt04rMonyou03Chk(GObj *volatile self);
void actSt04rMonyou04Chk(GObj *volatile self);
void actSt04rMonyou05Chk(GObj *volatile self);
void actSt04rMonyou06Chk(GObj *volatile self);

void actSt04rGondolaChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttr(boyGObj, 0xA000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;

    _ACTWait(15);

    if (gflagChk(248) != 0) {
        stage_SetAnimation(180, 1, 200);

        scpWakeupItemWithBoundary(-675.0f, -150.0f, -1600.0f, 200.0f);

        soundSeDefPlay(1266, 0, 0, 1);

        while (stage_CheckAnimationFinish(180) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(1267, 0, 0, 1);

        gflagOff(248);
    } else {
        stage_SetAnimation(180, 1, 0);

        scpWakeupItemWithBoundary(-675.0f, -1200.0f, -1600.0f, 200.0f);

        soundSeDefPlay(1266, 0, 0, 1);

        while (stage_CheckAnimationFrame(180, 200, 1) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(1267, 0, 0, 1);

        gflagOn(248);
    }

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);

    gondola_chk_mes[0].func = actSt04rGondolaCharaChk;
    sub->mail = gondola_chk_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt04rSolarStageChange(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(200) == 0) {
        solar_stage_change_mes[0].func = actSt04rSolarStageChangeChk;
        act->mail = solar_stage_change_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04rCrest01(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(209) == 0) {
        stage_SetAnimation(249, 0, 0);

        crest01_mes[0].func = actSt04rCrestMain;
        act->mail = crest01_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(249, 0, -1);
    }
}

void actSt04rCrest03(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(211) == 0) {
        stage_SetAnimation(253, 0, 0);

        crest03_mes[0].func = actSt04rCrest3Main;
        act->mail = crest03_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(253, 0, -1);
    }
}

void actSt04rC1Ball(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(216) == 0) {
        scpSearchGobj(1239)->active = 0;
        scpSearchGobj(1240)->active = 0;

        stage_SetAnimation(257, 0, 0);

        c1_ball_mes[0].func = actSt04rC1BallMain;
        act->mail = c1_ball_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(257, 0, -1);
    }
}

void actSt04rC2Ball(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(217) == 0) {
        scpSearchGobj(1315)->active = 0;
        scpSearchGobj(1316)->active = 0;

        stage_SetAnimation(258, 0, 0);

        c2_ball_mes[0].func = actSt04rC2BallMain;
        act->mail = c2_ball_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(258, 0, -1);
    }
}

void actSt04rC3Ball(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(218) == 0) {
        scpSearchGobj(1317)->active = 0;
        scpSearchGobj(1318)->active = 0;

        stage_SetAnimation(259, 0, 0);

        c3_ball_mes[0].func = actSt04rC3BallMain;
        act->mail = c3_ball_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(259, 0, -1);
    }
}

void actSt04rStair(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(219) == 0) {
        if (girlGObj != 0) {
            stair_mes[0].func = actSt04rStairChk;
            act->mail = stair_mes;
            ACTSendMailCorrect(self, 377);
            _ACTWait(0);
        }
    } else {
        scpSearchGobj(1348)->active = 0;

        stage_SetAnimation(285, -1, -2);
    }
}

void actSt04rBrg1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(225) == 0) {
        brg1_mes[0].func = actSt04rBrg1Chk;
        act->mail = brg1_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04rBrg2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(226) == 0) {
        brg2_mes[0].func = actSt04rBrg2Chk;
        act->mail = brg2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04rBrg1Way(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(225) == 0) {
        brg1_way_mes[0].func = actSt04rBrg1WayChk;
        act->mail = brg1_way_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04rBrg2Way(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(226) == 0) {
        brg2_way_mes[0].func = actSt04rBrg2WayChk;
        act->mail = brg2_way_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04rRope1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(227) == 0) {
        stage_SetAnimation(260, 0, 0);

        rope1_mes[0].func = actSt04rRope1Chk;
        act->mail = rope1_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(260, 0, -1);

        scpSearchGobj(1289)->active = 0;
    }
}

void actSt04rRope2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(228) == 0) {
        stage_SetAnimation(261, 0, 0);

        rope2_mes[0].func = actSt04rRope2Chk;
        act->mail = rope2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(261, 0, -1);

        scpSearchGobj(1290)->active = 0;
    }
}

void actSt04rRope3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(229) == 0) {
        stage_SetAnimation(262, 0, 0);

        rope3_mes[0].func = actSt04rRope3Chk;
        act->mail = rope3_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(262, 0, -1);

        scpSearchGobj(1291)->active = 0;
    }
}

void actSt04rRope4(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(230) == 0) {
        stage_SetAnimation(263, 0, 0);

        rope4_mes[0].func = actSt04rRope4Chk;
        act->mail = rope4_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(263, 0, -1);

        scpSearchGobj(1292)->active = 0;
    }
}

void actSt04rSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(220) == 0) {
        stage_SetAnimation(267, 0, 0);

        sekizo_mes[0].func = actSt04rSekizoChk;
        act->mail = sekizo_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(267, 0, -1);
    }
}

void actSt04rBarricade(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(231) == 0) {
        stage_SetAnimation(278, 0, 0);

        barricade_mes[0].func = actSt04rBarricadeChk;
        act->mail = barricade_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(278, 0, -1);
    }
}

void actSt04rGondola(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(248) != 0) {
        stage_SetAnimation(180, 0, 200);

        gondola_mes[0].func = actSt04rGondolaChk;
        act->mail = gondola_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(180, 0, 0);

        gondola2_mes[0].func = actSt04rGondolaChk;
        act->mail = gondola2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04rCrest01XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(209) == 0) {
        stage_SetAnimation(254, 0, 0);
    } else {
        stage_SetAnimation(254, 0, -1);
    }
}

void actSt04rCrest02XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(210) == 0) {
        stage_SetAnimation(255, 0, 0);
    } else {
        stage_SetAnimation(255, 0, -1);
    }
}

void actSt04rCrest03XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(211) == 0) {
        stage_SetAnimation(256, 0, 0);
    } else {
        stage_SetAnimation(256, 0, -1);
    }
}

void actSt04rC2BallXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(217) == 0) {
        stage_SetAnimation(258, 0, 0);

        scpSearchGobj(1243)->active = 0;
        scpSearchGobj(1244)->active = 0;
    } else {
        stage_SetAnimation(258, 0, -1);
    }
}

void actSt04rC3BallXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(218) == 0) {
        stage_SetAnimation(259, 0, 0);

        scpSearchGobj(1388)->active = 0;
        scpSearchGobj(1389)->active = 0;
    } else {
        stage_SetAnimation(259, 0, -1);
    }
}

void actSt04rTorch1_1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(232) == 0) {
        torch1_1_mes[0].func = actSt04rTorch1_1Chk;
        act->mail = torch1_1_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1239);
    }
}

void actSt04rTorch1_2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(233) == 0) {
        torch1_2_mes[0].func = actSt04rTorch1_2Chk;
        act->mail = torch1_2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1240);
    }
}

void actSt04rTorch2_1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(234) != 0 || gflagChk(236) != 0) {
        scpTorchLightOn(1315);
    } else {
        torch2_1_mes[0].func = actSt04rTorch2_1Chk;
        act->mail = torch2_1_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04rTorch2_2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(235) != 0 || gflagChk(237) != 0) {
        scpTorchLightOn(1316);
    } else {
        torch2_2_mes[0].func = actSt04rTorch2_2Chk;
        act->mail = torch2_2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04rTorch3_1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(238) == 0) {
        torch3_1_mes[0].func = actSt04rTorch3_1Chk;
        act->mail = torch3_1_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1317);
    }
}

void actSt04rTorch3_2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(239) == 0) {
        torch3_2_mes[0].func = actSt04rTorch3_2Chk;
        act->mail = torch3_2_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1318);
    }
}

void actSt04rTorch2_1XL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(234) != 0 || gflagChk(236) != 0) {
        scpTorchLightOn(1243);
    } else {
        torch2_1xl_mes[0].func = actSt04rTorch2_1XLChk;
        act->mail = torch2_1xl_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04rTorch2_2XL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(235) != 0 || gflagChk(237) != 0) {
        scpTorchLightOn(1244);
    } else {
        torch2_2xl_mes[0].func = actSt04rTorch2_2XLChk;
        act->mail = torch2_2xl_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04rTorch3_1XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(238) != 0) {
        scpTorchLightOn(1388);
    }
}

void actSt04rTorch3_2XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(239) != 0) {
        scpTorchLightOn(1389);
    }
}

void actSt04rMonyou01(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(240) == 0) {
        stage_SetAnimation(271, 0, 0);

        monyou01_mes[0].func = actSt04rMonyou01Chk;
        act->mail = monyou01_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(271, 0, -1);
    }
}

void actSt04rMonyou02(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(241) == 0) {
        stage_SetAnimation(272, 0, 0);

        monyou02_mes[0].func = actSt04rMonyou02Chk;
        act->mail = monyou02_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(272, 0, -1);
    }
}

void actSt04rMonyou03(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(242) == 0) {
        stage_SetAnimation(273, 0, 0);

        monyou03_mes[0].func = actSt04rMonyou03Chk;
        act->mail = monyou03_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(273, 0, -1);
    }
}

void actSt04rMonyou04(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(243) == 0) {
        stage_SetAnimation(274, 0, 0);

        monyou04_mes[0].func = actSt04rMonyou04Chk;
        act->mail = monyou04_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(274, 0, -1);
    }
}

void actSt04rMonyou05(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(244) == 0) {
        stage_SetAnimation(275, 0, 0);

        monyou05_mes[0].func = actSt04rMonyou05Chk;
        act->mail = monyou05_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(275, 0, -1);
    }
}

void actSt04rMonyou06(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(245) == 0) {
        stage_SetAnimation(276, 0, 0);

        monyou06_mes[0].func = actSt04rMonyou06Chk;
        act->mail = monyou06_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(276, 0, -1);
    }
}

void actSt04rMonyou07(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(246) == 0) {
        stage_SetAnimation(277, 0, 0);

        monyou07_mes[0].func = actSt04rMonyou07Chk;
        act->mail = monyou07_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(277, 0, -1);
    }
}

void actSt05cDoorInit(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (gflagChk(141) != 0 && gflagChk(200) == 0) {
        stage_SetAnimation(281, 0, -1);
    }

    if (gflagChk(141) == 0 || gflagChk(200) != 0) {
        stage_SetAnimation(281, 0, 0);
    }
}

void actSt04rC1BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

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
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt04rC2BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

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
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt04rC3BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;

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
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt04rC3BallTurn(GObj *volatile self)
{
    lt_switch_layout(51);

    scpSleepEnemyAll();

    gflagOn(218);
    _ACTWait(60);

    stage_SetAnimation(259, 1, 0);
    scpAdpcmPlayRequestFunc(75, 0, 1, 1, 1);

    while (stage_CheckAnimationFinish(259) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(1317)->active = 1;
    scpSearchGobj(1318)->active = 1;

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}

void actSt04rSolarStageChangeChk(GObj *volatile self)
{
    while (gflagChk(209) == 0 || gflagChk(210) == 0 || gflagChk(211) == 0 || gflagChk(198) == 0) {
        _ACTWait(1);
    }

    RequestStageChange(8, boyGObj, girlGObj, 16.0f, 16.0f);
}

void actSt04rStairEvent(int x)
{
    volatile int local = x;
}

void actSt04rRope1Event(int x)
{
    volatile int local = x;
}

void actSt04rRope1Chk(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(227) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1289))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1289)->active = 0;

            gflagOn(227);

            stage_SetAnimation(260, 1, 0);

            while (stage_CheckAnimationFinish(260) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        }
    }
}

void actSt04rRope2Event(int x)
{
    volatile int local = x;
}

void actSt04rRope2Chk(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(228) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1290))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1290)->active = 0;

            gflagOn(228);

            stage_SetAnimation(261, 1, 0);

            while (stage_CheckAnimationFinish(261) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        }
    }
}

void actSt04rBrg1Event(int x)
{
    volatile int local = x;
}

void actSt04rRope3Event(int x)
{
    volatile int local = x;
}

void actSt04rRope3Chk(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(229) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1291))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1291)->active = 0;

            gflagOn(229);

            stage_SetAnimation(262, 1, 0);

            while (stage_CheckAnimationFinish(262) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        }
    }
}

void actSt04rRope4Event(int x)
{
    volatile int local = x;
}

void actSt04rRope4Chk(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(230) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1292))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1292)->active = 0;

            gflagOn(230);

            stage_SetAnimation(263, 1, 0);

            while (stage_CheckAnimationFinish(263) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        }
    }
}

void actSt04rBrg2Event(int x)
{
    volatile int local = x;
}

void actSt04rBrg1WayChk(GObj *volatile self)
{
    while (gflagChk(225) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(3, 1);
}

void actSt04rBrg2WayChk(GObj *volatile self)
{
    while (gflagChk(225) == 0 || gflagChk(226) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(4, 1);
}

void actSt04rMonyou01Event(int x)
{
    volatile int local = x;
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

    gflagOn(240);
    _ACTWait(5);

    stage_SetAnimation(271, 1, 0);

    soundSeDefPlay(1277, 0, 0, 1);

    while (stage_CheckAnimationFrame(271, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;
}

void actSt04rMonyou02Event(int x)
{
    volatile int local = x;
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

    gflagOn(241);
    _ACTWait(5);

    stage_SetAnimation(272, 1, 0);

    soundSeDefPlay(1277, 0, 0, 1);

    while (stage_CheckAnimationFrame(272, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;
}

void actSt04rMonyou03Event(int x)
{
    volatile int local = x;
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

    gflagOn(242);
    _ACTWait(5);

    stage_SetAnimation(273, 1, 0);

    soundSeDefPlay(1277, 0, 0, 1);

    while (stage_CheckAnimationFrame(273, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;
}

void actSt04rMonyou04Event(int x)
{
    volatile int local = x;
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

    gflagOn(243);
    _ACTWait(5);

    stage_SetAnimation(274, 1, 0);

    soundSeDefPlay(1277, 0, 0, 1);

    while (stage_CheckAnimationFrame(274, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;
}

void actSt04rMonyou05Event(int x)
{
    volatile int local = x;
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

    gflagOn(244);
    _ACTWait(5);

    stage_SetAnimation(275, 1, 0);

    soundSeDefPlay(1277, 0, 0, 1);

    while (stage_CheckAnimationFrame(275, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;
}

void actSt04rMonyou06Event(int x)
{
    volatile int local = x;
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

    gflagOn(245);
    _ACTWait(5);

    stage_SetAnimation(276, 1, 0);

    soundSeDefPlay(1277, 0, 0, 1);

    while (stage_CheckAnimationFrame(276, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpBoyControlReadDisable = 0;
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

    while ((n = scpIsBombExplode(19)) == 0 || scpTriggerBall(self, n, 500.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    gflagOn(231);
    _ACTWait(5);

    stage_SetAnimation(278, 1, 0);

    while (stage_CheckAnimationFinish(278) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

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
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt04rTorch1_1Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1239) == 0) {
        _ACTWait(1);
    }

    gflagOn(232);
}

void actSt04rTorch1_2Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1240) == 0) {
        _ACTWait(1);
    }

    gflagOn(233);
}

void actSt04rTorch2_1Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1315) == 0) {
        _ACTWait(1);
    }

    gflagOn(234);
}

void actSt04rTorch2_2Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1316) == 0) {
        _ACTWait(1);
    }

    gflagOn(235);
}

void actSt04rTorch3_1Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1317) == 0) {
        _ACTWait(1);
    }

    gflagOn(238);
}

void actSt04rTorch3_2Chk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1318) == 0) {
        _ACTWait(1);
    }

    gflagOn(239);
}

void actSt04rTorch2_1XLChk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1243) == 0) {
        _ACTWait(1);
    }

    gflagOn(236);
}

void actSt04rTorch2_2XLChk(GObj *volatile self)
{
    while (scpIsTorchLightOn(1244) == 0) {
        _ACTWait(1);
    }

    gflagOn(237);
}
