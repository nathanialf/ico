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

#ifdef VERSION_NTSC
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
#else
#ifdef VERSION_AUG6
static ActMail c1_ball_main_mes[2] = {{372, actSt04rC1BallSwitch}, {392}}; /* derived name */

static ActMail c1_ball_mes[2] = {{393}, {392}}; /* derived name */

static ActMail c1_ball_switch_mes[2] = {{393}, {392}}; /* derived name */

static ActMail c2_ball_main_mes[2] = {{372, actSt04rC2BallSwitch}, {392}}; /* derived name */

static ActMail c2_ball_mes[2] = {{393}, {392}}; /* derived name */

static ActMail c2_ball_switch_mes[2] = {{393}, {392}}; /* derived name */

static ActMail c3_ball_main_mes[2] = {{373, actSt04rC3BallSwitch}, {392}}; /* derived name */

static ActMail c3_ball_mes[2] = {{393}, {392}}; /* derived name */

static ActMail c3_ball_switch_mes[2] = {{393}, {392}}; /* derived name */

static ActMail crest01_mes[2] = {{393}, {392}}; /* derived name */

static ActMail crest02_mes[2] = {{393}, {392}}; /* derived name */

static ActMail crest03_mes[2] = {{393}, {392}}; /* derived name */

static ActMail solar_beam_mes[2] = {{393}, {392}}; /* derived name */

static ActMail solar_stage_change_mes[2] = {{393}, {392}}; /* derived name */

static ActMail stair_mes[2] = {{393}, {392}}; /* derived name */

static ActMail sekizo_mes[2] = {{393}, {392}}; /* derived name */

static ActMail rope1_mes[2] = {{393}, {392}}; /* derived name */

static ActMail rope2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail brg1_mes[2] = {{393}, {392}}; /* derived name */

static ActMail rope3_mes[2] = {{393}, {392}}; /* derived name */

static ActMail rope4_mes[2] = {{393}, {392}}; /* derived name */

static ActMail brg2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail brg1_way_mes[2] = {{393}, {392}}; /* derived name */

static ActMail brg2_way_mes[2] = {{393}, {392}}; /* derived name */

static ActMail monyou01_mes[2] = {{393}, {392}}; /* derived name */

static ActMail monyou02_mes[2] = {{393}, {392}}; /* derived name */

static ActMail monyou03_mes[2] = {{393}, {392}}; /* derived name */

static ActMail monyou04_mes[2] = {{393}, {392}}; /* derived name */

static ActMail monyou05_mes[2] = {{393}, {392}}; /* derived name */

static ActMail monyou06_mes[2] = {{393}, {392}}; /* derived name */

static ActMail monyou07_mes[2] = {{393}, {392}}; /* derived name */

static ActMail barricade_mes[2] = {{393}, {392}}; /* derived name */

static ActMail gondola_mes[2] = {{393}, {392}}; /* derived name */

static ActMail gondola2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail gondola_chk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail gondola_chara_chk_mes[2] = {{393}, {392}}; /* derived name */

static ActMail torch1_1_mes[2] = {{393}, {392}}; /* derived name */

static ActMail torch1_2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail torch2_1_mes[2] = {{393}, {392}}; /* derived name */

static ActMail torch2_2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail torch3_1_mes[2] = {{393}, {392}}; /* derived name */

static ActMail torch3_2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail torch2_1xl_mes[2] = {{393}, {392}}; /* derived name */

static ActMail torch2_2xl_mes[2] = {{393}, {392}}; /* derived name */
#else
static void actSt04rBrg1Sub(GObj *volatile self);
static void openGate(struct GObj *self);

static ActMail c1_ball_main_mes[2] = {{406, actSt04rC1BallSwitch}, {429}}; /* derived name */

static ActMail c1_ball_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c1_ball_switch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c2_ball_main_mes[2] = {{406, actSt04rC2BallSwitch}, {429}}; /* derived name */

static ActMail c2_ball_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c2_ball_switch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c3_ball_main_mes[2] = {{407, actSt04rC3BallSwitch}, {429}}; /* derived name */

static ActMail c3_ball_mes[2] = {{430}, {429}}; /* derived name */

static ActMail c3_ball_switch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail crest01_mes[2] = {{430}, {429}}; /* derived name */

static ActMail crest02_mes[2] = {{430}, {429}}; /* derived name */

static ActMail crest03_mes[2] = {{430}, {429}}; /* derived name */

static ActMail solar_beam_mes[2] = {{430}, {429}}; /* derived name */

static ActMail solar_stage_change_mes[2] = {{430}, {429}}; /* derived name */

static ActMail stair_mes[2] = {{430}, {429}}; /* derived name */

static ActMail sekizo_mes[2] = {{430}, {429}}; /* derived name */

static ActMail rope1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail rope2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg1_chk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail rope3_mes[2] = {{430}, {429}}; /* derived name */

static ActMail rope4_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg2_chk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg1_way_mes[2] = {{430}, {429}}; /* derived name */

static ActMail brg2_way_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou01_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou02_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou03_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou04_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou05_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou06_mes[2] = {{430}, {429}}; /* derived name */

static ActMail monyou07_mes[2] = {{430}, {429}}; /* derived name */

static ActMail barricade_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondola_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondola2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondola_chk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail gondola_chara_chk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch1_1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch1_2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch2_1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch2_2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch3_1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch3_2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch2_1xl_mes[2] = {{430}, {429}}; /* derived name */

static ActMail torch2_2xl_mes[2] = {{430}, {429}}; /* derived name */

/* .sbss: the pad actuator handle openGate holds, the demo's own end flag, the
   gate animation and voice clip openGate plays, and the flag the stair
   subthread raises once it is past its setup. */
static int padAct; /* derived name */

static int demoEnd;

static int gateAnim; /* derived name */

static int gateAdpcm; /* derived name */

static int subStarted; /* derived name */
#endif
#endif

/* The look-at point both characters face in the crest cutscene. */
static const ConstVec crestFacePos = {{0.0f, 0.0f, -5000.0f, 1.0f}}; /* derived name */

/* .sdata: the room's stream handles and shakes (the three balls and crest2_4r
   unused). */
SqEntry *solar4r = 0;

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
SqEntry *ball1_4r = 0;

SqEntry *ball2_4r = 0;

SqEntry *ball3_4r = 0;
#else
int ball1_4r = 0;

int ball2_4r = 0;

int ball3_4r = 0;
#endif

SqEntry *crest1_4r = 0;

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
SqEntry *crest2_4r = 0;
#else
int crest2_4r = 0;
#endif

SqEntry *crest3_4r = 0;

SqEntry *stair5d = 0;

SqEntry *sekizo5c = 0;

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
SqEntry *st05d_hasi = 0;
#else
unsigned char st05d_hasi = 0;
#endif

int st04r_yure = 0;

unsigned char st04r_yure_vol = 0;

int sekizo_4r = 0;

#ifdef VERSION_AUG6
unsigned char sekizo_4r_vol = 0;
#endif

#ifdef VERSION_NTSC
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
#else
void actSt05eEnd(void)
{
    if (solar4r != 0) {
#ifdef VERSION_AUG6
        if (gflagChk(209) == 0) {
            soundDataClose(solar4r);
#else
        if (gflagChk(234) == 0) {
            scpAdpcmCloseFunc(&solar4r);
#endif
        }
    }
}

#if defined(VERSION_JPN) || defined(VERSION_KOR)
void actSt05cInit(void)
{
    if (gflagChk(274) == 0) {
        stage_SetAnimation(333, 0, 0);
    } else {
        stage_SetAnimation(333, 0, -1);
    }

    if (gflagChk(275) == 0) {
        stage_SetAnimation(334, 0, 0);
    } else {
        stage_SetAnimation(334, 0, -1);
    }

    if (gflagChk(276) == 0) {
        stage_SetAnimation(335, 0, 0);
    } else {
        stage_SetAnimation(335, 0, -1);
    }

    if (gflagChk(277) == 0) {
        stage_SetAnimation(336, 0, 0);
    } else {
        stage_SetAnimation(336, 0, -1);
    }

    if (gflagChk(278) == 0) {
        stage_SetAnimation(337, 0, 0);
    } else {
        stage_SetAnimation(337, 0, -1);
    }

    if (gflagChk(279) == 0) {
        stage_SetAnimation(338, 0, 0);
    } else {
        stage_SetAnimation(338, 0, -1);
    }

    if (gflagChk(280) == 0) {
        stage_SetAnimation(339, 0, 0);
    } else {
        stage_SetAnimation(339, 0, -1);
    }

    if (gflagChk(254) == 0) {
        SetWayGroupActive(1, 0);
    } else {
        SetWayGroupActive(1, 1);
    }

    if (gflagChk(259) == 0) {
        stage_SetAnimation(324, 0, 0);
    } else {
        stage_SetAnimation(324, 0, -1);
    }

    if (gflagChk(260) == 0) {
        stage_SetAnimation(325, 0, 0);
    } else {
        stage_SetAnimation(325, 0, -1);
    }

    if (gflagChk(253) == 0) {
        scpSearchGobj(1379)->active = 0;
    }
}
#else
void actSt05cInit(void)
{
#ifdef VERSION_AUG6
    if (gflagChk(249) == 0) {
        stage_SetAnimation(303, 0, 0);
    } else {
        stage_SetAnimation(303, 0, -1);
    }

    if (gflagChk(250) == 0) {
        stage_SetAnimation(304, 0, 0);
    } else {
        stage_SetAnimation(304, 0, -1);
    }

    if (gflagChk(251) == 0) {
        stage_SetAnimation(305, 0, 0);
    } else {
        stage_SetAnimation(305, 0, -1);
    }

    if (gflagChk(252) == 0) {
        stage_SetAnimation(306, 0, 0);
    } else {
        stage_SetAnimation(306, 0, -1);
    }

    if (gflagChk(253) == 0) {
        stage_SetAnimation(307, 0, 0);
    } else {
        stage_SetAnimation(307, 0, -1);
#else
    if (gflagChk(274) == 0) {
        stage_SetAnimation(337, 0, 0);
    } else {
        stage_SetAnimation(337, 0, -1);
    }

    if (gflagChk(275) == 0) {
        stage_SetAnimation(338, 0, 0);
    } else {
        stage_SetAnimation(338, 0, -1);
    }

    if (gflagChk(276) == 0) {
        stage_SetAnimation(339, 0, 0);
    } else {
        stage_SetAnimation(339, 0, -1);
    }

    if (gflagChk(277) == 0) {
        stage_SetAnimation(340, 0, 0);
    } else {
        stage_SetAnimation(340, 0, -1);
    }

    if (gflagChk(278) == 0) {
        stage_SetAnimation(341, 0, 0);
    } else {
        stage_SetAnimation(341, 0, -1);
    }

    if (gflagChk(279) == 0) {
        stage_SetAnimation(342, 0, 0);
    } else {
        stage_SetAnimation(342, 0, -1);
    }

    if (gflagChk(280) == 0) {
        stage_SetAnimation(343, 0, 0);
    } else {
        stage_SetAnimation(343, 0, -1);
#endif
    }

    if (gflagChk(254) == 0) {
#ifdef VERSION_AUG6
        stage_SetAnimation(308, 0, 0);
    } else {
        stage_SetAnimation(308, 0, -1);
    }

    if (gflagChk(255) == 0) {
        stage_SetAnimation(309, 0, 0);
    } else {
        stage_SetAnimation(309, 0, -1);
    }

    if (gflagChk(229) == 0) {
#endif
        SetWayGroupActive(1, 0);
    } else {
        SetWayGroupActive(1, 1);
    }

#ifdef VERSION_AUG6
    if (gflagChk(234) == 0) {
        stage_SetAnimation(294, 0, 0);
    } else {
        stage_SetAnimation(294, 0, -1);
    }

    if (gflagChk(235) == 0) {
        stage_SetAnimation(295, 0, 0);
    } else {
        stage_SetAnimation(295, 0, -1);
    }

    if (gflagChk(228) == 0) {
        scpSearchGobj(1275)->active = 0;
#else
    if (gflagChk(259) == 0) {
        stage_SetAnimation(328, 0, 0);
    } else {
        stage_SetAnimation(328, 0, -1);
    }

    if (gflagChk(260) == 0) {
        stage_SetAnimation(329, 0, 0);
    } else {
        stage_SetAnimation(329, 0, -1);
    }

    if (gflagChk(253) == 0) {
        scpSearchGobj(1379)->active = 0;
#endif
    }
}
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
void actSt05dInit(void)
{
    if (gflagChk(259) == 0) {
        stage_SetAnimation(324, 0, 0);

        SetWayGroupActive(3, 0);
    } else {
        stage_SetAnimation(324, 0, -1);

        SetWayGroupActive(3, 1);
    }

    if (gflagChk(260) == 0) {
        stage_SetAnimation(325, 0, 0);

        SetWayGroupActive(4, 0);
    } else {
        stage_SetAnimation(325, 0, -1);

        SetWayGroupActive(4, 1);
    }

    if (gflagChk(253) == 0) {
        stage_SetAnimation(326, 0, 0);
        stage_SetAnimation(346, 0, 0);
    } else {
        stage_SetAnimation(326, 0, -1);
        stage_SetAnimation(346, 0, -1);

        FinishHint(24);
    }

    if (gflagChk(274) == 0) {
        stage_SetAnimation(333, 0, 0);
    } else {
        stage_SetAnimation(333, 0, -1);
    }

    if (gflagChk(275) == 0) {
        stage_SetAnimation(334, 0, 0);
    } else {
        stage_SetAnimation(334, 0, -1);
    }

    if (gflagChk(276) == 0) {
        stage_SetAnimation(335, 0, 0);
    } else {
        stage_SetAnimation(335, 0, -1);
    }

    if (gflagChk(277) == 0) {
        stage_SetAnimation(336, 0, 0);
    } else {
        stage_SetAnimation(336, 0, -1);
    }

    if (gflagChk(278) == 0) {
        stage_SetAnimation(337, 0, 0);
    } else {
        stage_SetAnimation(337, 0, -1);
    }

    if (gflagChk(279) == 0) {
        stage_SetAnimation(338, 0, 0);
    } else {
        stage_SetAnimation(338, 0, -1);
    }

    if (gflagChk(280) == 0) {
        stage_SetAnimation(339, 0, 0);
    } else {
        stage_SetAnimation(339, 0, -1);
    }

    if (gflagChk(165) != 0 && gflagChk(234) == 0) {
        stage_SetAnimation(343, 0, -1);
    }

    if (gflagChk(165) == 0 || gflagChk(234) != 0) {
        stage_SetAnimation(343, 0, 0);
    }

    if (gflagChk(282) != 0) {
        stage_SetAnimation(225, 0, 200);
    } else {
        stage_SetAnimation(225, 0, 0);
    }
}
#else
void actSt05dInit(void)
{
#ifdef VERSION_AUG6
    if (gflagChk(234) == 0) {
        stage_SetAnimation(294, 0, 0);
#else
    if (gflagChk(259) == 0) {
        stage_SetAnimation(328, 0, 0);
#endif

        SetWayGroupActive(3, 0);
    } else {
#ifdef VERSION_AUG6
        stage_SetAnimation(294, 0, -1);
#else
        stage_SetAnimation(328, 0, -1);
#endif

        SetWayGroupActive(3, 1);
    }

#ifdef VERSION_AUG6
    if (gflagChk(235) == 0) {
        stage_SetAnimation(295, 0, 0);
#else
    if (gflagChk(260) == 0) {
        stage_SetAnimation(329, 0, 0);
#endif

        SetWayGroupActive(4, 0);
    } else {
#ifdef VERSION_AUG6
        stage_SetAnimation(295, 0, -1);
#else
        stage_SetAnimation(329, 0, -1);
#endif

        SetWayGroupActive(4, 1);
    }

#ifdef VERSION_AUG6
    if (gflagChk(228) == 0) {
        stage_SetAnimation(296, 0, 0);
        stage_SetAnimation(316, 0, 0);
    } else {
        stage_SetAnimation(296, 0, -1);
        stage_SetAnimation(316, 0, -1);
    }

    if (gflagChk(249) == 0) {
        stage_SetAnimation(303, 0, 0);
    } else {
        stage_SetAnimation(303, 0, -1);
    }

    if (gflagChk(250) == 0) {
        stage_SetAnimation(304, 0, 0);
    } else {
        stage_SetAnimation(304, 0, -1);
    }

    if (gflagChk(251) == 0) {
        stage_SetAnimation(305, 0, 0);
    } else {
        stage_SetAnimation(305, 0, -1);
    }

    if (gflagChk(252) == 0) {
        stage_SetAnimation(306, 0, 0);
    } else {
        stage_SetAnimation(306, 0, -1);
    }

    if (gflagChk(253) == 0) {
        stage_SetAnimation(307, 0, 0);
    } else {
        stage_SetAnimation(307, 0, -1);
    }

    if (gflagChk(254) == 0) {
        stage_SetAnimation(308, 0, 0);
    } else {
        stage_SetAnimation(308, 0, -1);
    }

    if (gflagChk(255) == 0) {
        stage_SetAnimation(309, 0, 0);
    } else {
        stage_SetAnimation(309, 0, -1);
    }

    if (gflagChk(148) != 0 && gflagChk(209) == 0) {
        stage_SetAnimation(313, 0, -1);
    }

    if (gflagChk(148) == 0 || gflagChk(209) != 0) {
        stage_SetAnimation(313, 0, 0);
    }

    if (gflagChk(257) != 0) {
        stage_SetAnimation(200, 0, 200);
    } else {
        stage_SetAnimation(200, 0, 0);
    }

    if (gflagChk(207) == 0) {
        scpSearchGobj(1349)->active = 0;
    } else {
        scpSearchGobj(1348)->active = 0;
#else
    if (gflagChk(253) == 0) {
        stage_SetAnimation(330, 0, 0);
        stage_SetAnimation(350, 0, 0);
    } else {
        stage_SetAnimation(330, 0, -1);
        stage_SetAnimation(350, 0, -1);

        FinishHint(24);
    }

    if (gflagChk(274) == 0) {
        stage_SetAnimation(337, 0, 0);
    } else {
        stage_SetAnimation(337, 0, -1);
    }

    if (gflagChk(275) == 0) {
        stage_SetAnimation(338, 0, 0);
    } else {
        stage_SetAnimation(338, 0, -1);
    }

    if (gflagChk(276) == 0) {
        stage_SetAnimation(339, 0, 0);
    } else {
        stage_SetAnimation(339, 0, -1);
    }

    if (gflagChk(277) == 0) {
        stage_SetAnimation(340, 0, 0);
    } else {
        stage_SetAnimation(340, 0, -1);
    }

    if (gflagChk(278) == 0) {
        stage_SetAnimation(341, 0, 0);
    } else {
        stage_SetAnimation(341, 0, -1);
    }

    if (gflagChk(279) == 0) {
        stage_SetAnimation(342, 0, 0);
    } else {
        stage_SetAnimation(342, 0, -1);
    }

    if (gflagChk(280) == 0) {
        stage_SetAnimation(343, 0, 0);
    } else {
        stage_SetAnimation(343, 0, -1);
    }

    if (gflagChk(165) != 0 && gflagChk(234) == 0) {
        stage_SetAnimation(347, 0, -1);
    }

    if (gflagChk(165) == 0 || gflagChk(234) != 0) {
        stage_SetAnimation(347, 0, 0);
    }

    if (gflagChk(282) != 0) {
        stage_SetAnimation(229, 0, 200);
    } else {
        stage_SetAnimation(229, 0, 0);
#endif
    }
}
#endif

void actSt05eInit(void)
{
#ifdef VERSION_AUG6
    if (gflagChk(206) == 0) {
#else
    if (gflagChk(231) == 0) {
#endif
        SetWayGroupActive(5, 0);
    } else {
        SetWayGroupActive(5, 1);
    }

#ifdef VERSION_AUG6
    if (gflagChk(234) == 0) {
        stage_SetAnimation(294, 0, 0);
    } else {
        stage_SetAnimation(294, 0, -1);
    }

    if (gflagChk(235) == 0) {
        stage_SetAnimation(295, 0, 0);
    } else {
        stage_SetAnimation(295, 0, -1);
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

    stage_SetAnimation(283, 1, 0);

    while (stage_CheckAnimationFinish(283) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(1300)->active = 1;
    scpSearchGobj(1301)->active = 1;

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

    stage_SetAnimation(284, 1, 0);

    while (stage_CheckAnimationFinish(284) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(1376)->active = 1;
    scpSearchGobj(1377)->active = 1;

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

    stage_SetAnimation(285, 1, 0);

    while (stage_CheckAnimationFinish(285) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(1378)->active = 1;
    scpSearchGobj(1379)->active = 1;

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
#else
    if (gflagChk(259) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(324, 0, 0);
#else
        stage_SetAnimation(328, 0, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(324, 0, -1);
#else
        stage_SetAnimation(328, 0, -1);
#endif
    }

    if (gflagChk(260) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(325, 0, 0);
#else
        stage_SetAnimation(329, 0, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(325, 0, -1);
#else
        stage_SetAnimation(329, 0, -1);
#endif
    }
#endif
}

void actSt04rCrest02(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(219) == 0) {
        if (current_stage_no == 28) {
            stage_SetAnimation(277, 0, 0);
        } else {
            stage_SetAnimation(278, 0, 0);
#else
    if (gflagChk(244) == 0) {
        if (current_stage_no == 28) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(307, 0, 0);
#else
            stage_SetAnimation(311, 0, 0);
#endif
        } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(308, 0, 0);
#else
            stage_SetAnimation(312, 0, 0);
#endif
#endif
        }

        crest02_mes[0].func = actSt04rCrest2Main;
        act->mail = crest02_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    } else {
        if (current_stage_no == 28) {
#ifdef VERSION_AUG6
            stage_SetAnimation(277, 0, -1);
        } else {
            stage_SetAnimation(278, 0, -1);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(307, 0, -1);
#else
            stage_SetAnimation(311, 0, -1);
#endif
        } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(308, 0, -1);
#else
            stage_SetAnimation(312, 0, -1);
#endif
#endif
        }

        scpBoyControlReadDisable = 0;
    }
}

#ifdef VERSION_AUG6
void actSt04rCrestMain(GObj *volatile self)
{
    while (scpIsTorchLightOn(1300) == 0 || scpIsTorchLightOn(1301) == 0 || gflagChk(225) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(26, &crest1_4r, 0, 1, 1);

    while (crest1_4r == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(275, 1, 0);

    while (stage_CheckAnimationFrame(275, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    st04r_yure = iosPadActRequest(boyPad, 10);
    st04r_yure_vol = 128;
    iosPadActVolumeSet(st04r_yure, 128);

    while (stage_CheckAnimationFrame(275, 190, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(st04r_yure);

    while (stage_CheckAnimationFinish(275) == 0) {
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
        while (scpIsTorchLightOn(1304) == 0 || scpIsTorchLightOn(1305) == 0 || gflagChk(226) == 0) {
            _ACTWait(1);
        }
    }

    if (current_stage_no == 29) {
        while (scpIsTorchLightOn(1376) == 0 || scpIsTorchLightOn(1377) == 0 || gflagChk(226) == 0) {
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
        stage_SetAnimation(277, 1, 0);

        while (stage_CheckAnimationFrame(277, 30, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        st04r_yure = iosPadActRequest(boyPad, 10);
        st04r_yure_vol = 128;
        iosPadActVolumeSet(st04r_yure, 128);

        while (stage_CheckAnimationFrame(277, 190, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        iosPadActStop(st04r_yure);

        while (stage_CheckAnimationFinish(277) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        gflagOn(223);
    } else {
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
    while (scpIsTorchLightOn(1378) == 0 || scpIsTorchLightOn(1379) == 0 || gflagChk(227) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    scpSleepEnemyOne(3415);

    gflagOn(152);

    fightSoundProcessRequestPause();

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(23, &crest3_4r, 0, 1, 1);

    while (crest3_4r == 0) {
        _ACTWait(1);
    }

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

    scpWakeupEnemyOne(3415);

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
#else
static void openGateSub(GObj *volatile self)
{
    stage_SetAnimation(gateAnim, 1, 0);

    while (stage_CheckAnimationFrame(gateAnim, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    padAct = iosPadActRequest(boyPad, 10);
    st05d_hasi = 128;
    iosPadActVolumeSet(padAct, 128);

    while (stage_CheckAnimationFrame(gateAnim, 190, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(padAct);

    while (stage_CheckAnimationFinish(gateAnim) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

static void openGate(GObj *self)
{
    GProc *th;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif

    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(gateAdpcm, &crest1_4r, 0, 1, 1);

    while (crest1_4r == 0) {
        _ACTWait(1);
    }

    th = actCreateSubThread(openGateSub, 21);

    demoEnd = 0;
    padAct = -1;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&((GProc *)th)->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&crest1_4r, 256);

        if (padAct >= 0) {
            iosPadActStop(padAct);
        }

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(gateAnim, 0, -1);

        scpFadeIn(3.0f);
    }

    scpWakeupEnemyAll();

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif

    scpBoyControlReadDisable = 0;
}

void actSt04rCrest2Main(GObj *volatile self)
{
    int anim;

    if (current_stage_no == 28) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        anim = 307;
#else
        anim = 311;
#endif
        while (scpIsTorchLightOn(1408) == 0 || scpIsTorchLightOn(1409) == 0 || gflagChk(251) == 0) {
            _ACTWait(1);
        }

        gateAnim = anim;
    }

    if (current_stage_no == 29) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        anim = 308;
#else
        anim = 312;
#endif

        while (scpIsTorchLightOn(1487) == 0 || scpIsTorchLightOn(1488) == 0 || gflagChk(251) == 0) {
            _ACTWait(1);
        }

        gateAnim = anim;
    }

    gateAdpcm = 25;
    openGate(self);

    if (current_stage_no == 28) {
        gflagOn(248);
    } else {
        gflagOn(247);
    }

    _ACTWait(1);

    gflagOn(244);
    gflagOff(246);
    gflagOff(249);
    gflagOff(233);
}

void actSt04rCrest3Main(GObj *volatile self)
{
    while (scpIsTorchLightOn(1489) == 0 || scpIsTorchLightOn(1490) == 0 || gflagChk(252) == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpSleepEnemyOne(3734);
#else
    scpSleepEnemyOne(3757);
#endif

    gflagOn(170);

    fightSoundProcessRequestPause();

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    gateAnim = 309;
#else
    gateAnim = 313;
#endif
    gateAdpcm = 24;
    openGate(self);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpWakeupEnemyOne(3734);
#else
    scpWakeupEnemyOne(3757);
#endif

    fightSoundProcessRequestStart();
    _ACTWait(1);

    gflagOn(245);
    gflagOff(246);
    gflagOff(247);
    gflagOff(248);
    gflagOn(249);
    gflagOff(233);
}
#endif

void actSt04rSolarBeam(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    solar4r = 0;

#ifdef VERSION_AUG6
    if (gflagChk(209) == 0) {
        scpAdpcmPlayRequestFunc(27, &solar4r, 0, 1, 0);

        if (gflagChk(218) != 0 && gflagChk(219) != 0 && gflagChk(220) != 0 && gflagChk(207) != 0) {
#else
    if (gflagChk(234) == 0) {
        scpAdpcmPlayRequestFunc(28, &solar4r, 0, 1, 0);

        if (gflagChk(243) != 0 && gflagChk(244) != 0 && gflagChk(245) != 0 && gflagChk(232) != 0) {
#endif
            if (boyGObj != 0) {
                scpPlayMot(boyGObj, 0);
            }

#ifdef VERSION_AUG6
            scpBoyControlReadDisable = 1;
            gflagOn(355);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            lt_switch_layout(52);
#else
            lt_switch_layout(55);
#endif

            scpBoyControlReadDisable = 1;
            gflagOn(389);
#endif

            scpFadeOut(255.0f, 0, 0, 0);

            while (solar4r == 0) {
                _ACTWait(1);
            }

            scpFadeIn(6.0f);
        }

        solar_beam_mes[0].func = actSt04rSolarBeamChk;
        act->mail = solar_beam_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    } else {
        scpBoyControlReadDisable = 0;
    }
}

#ifdef VERSION_AUG6
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

    stage_SetAnimation(312, 1, 0);
    stage_SetAnimation(260, 1, 0);
    _ACTWait(30);

    while (stage_CheckAnimationFinish(260) == 0) {
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

    scpSearchGobj(1414)->active = 0;

    stage_SetAnimation(317, -1, -2);
    _ACTWait(60);

    scpAdpcmPlayRequestFunc(59, &stair5d, 1, 1, 1);

    while (stair5d == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(316, 1, 0);

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

    while (stage_CheckAnimationFinish(316) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

    stage_SetAnimation(296, 1, 0);

    while (stage_CheckAnimationFrame(296, 140, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    st04r_yure = iosPadActRequest(boyPad, 9);
    st04r_yure_vol = 128;
    iosPadActVolumeSet(st04r_yure, 128);

    while (stage_CheckAnimationFinish(296) == 0) {
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
#else
void actSt04rSolarBeamChk(GObj *volatile self)
{
    while (gflagChk(243) == 0 || gflagChk(244) == 0 || gflagChk(245) == 0 || gflagChk(232) == 0) {
        _ACTWait(1);
    }

    gflagOn(234);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    while (solar4r == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(solar4r->stream);

    preload(15);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(342, 1, 0);
    stage_SetAnimation(290, 1, 0);
#else
    stage_SetAnimation(346, 1, 0);
    stage_SetAnimation(294, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(290) == 0) {
#else
    while (stage_CheckAnimationFinish(294) == 0) {
#endif
        if ((pad[0].flags & 0x800) != 0 && scpAdpcmPlayRequestNum() == 0) {
            scpFadeOut(16.0f, 0, 0, 0);

            scpAdpcmFadeCloseFunc(&solar4r, 256);

            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(342, 0, -1);
            stage_SetAnimation(290, 0, -1);
#else
            stage_SetAnimation(346, 0, -1);
            stage_SetAnimation(294, 0, -1);
#endif

            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }

    scpBoyControlReadDisable = 0;

    scpWakeupEnemyAll();

    RequestStageChange(15, boyGObj, 0, 2.0f, 8.0f);
}

static void actSt04rStairSub(GObj *volatile self)
{
    long long buf[2];
    float dir[4];

    _ACTWait(60);

    while (crest3_4r == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(crest3_4r->stream);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(346, 1, 0);
#else
    stage_SetAnimation(350, 1, 0);

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);
#endif

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 532);

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

    subStarted = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(346) == 0) {
#else
    while (stage_CheckAnimationFinish(350) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 17);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(326, 1, 0);
#else
    stage_SetAnimation(330, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(326, 140, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(330, 140, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    padAct = iosPadActRequest(boyPad, 9);
    st05d_hasi = 128;
    iosPadActVolumeSet(padAct, 128);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(326) == 0) {
#else
    while (stage_CheckAnimationFinish(330) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt04rStairChk(GObj *volatile self)
{
    GProc *th;

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(boyGObj, 0xB000000) == 0 ||
           scpTriggerFloorAttr(girlGObj, 0xB000000) == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif

    scpBoyControlReadDisable = 1;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);
#endif
    gflagOn(253);

    FinishHint(24);

    scpSleepEnemyAll();

    scpSearchGobj(1523)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(347, -1, -2);
#else
    stage_SetAnimation(351, -1, -2);
#endif

    scpAdpcmPlayRequestFunc(61, &crest3_4r, 1, 1, 0);

    th = actCreateSubThread(actSt04rStairSub, 21);

    demoEnd = 0;
    padAct = -1;
    subStarted = 0;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (crest3_4r == 0) {
            _ACTWait(1);
        }

        scpAdpcmFadeCloseFunc(&crest3_4r, 512);

        while (subStarted == 0) {
            _ACTWait(1);
        }

        iosThreadSetPri(&((GProc *)th)->thread, 34);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(346, 0, -1);
        stage_SetAnimation(326, 0, -1);
#else
        stage_SetAnimation(350, 0, -1);
        stage_SetAnimation(330, 0, -1);
#endif
        _ACTWait(1);

        scpPlayMot(boyGObj, 0);
        scpPlayMot(girlGObj, 532);

        scpPlayPosSet(boyGObj, -55.0f, 234.0f, -3881.0f);
        scpPlayPosSet(girlGObj, 58.0f, 234.0f, -3891.0f);

        _ACTWait(1);

        iosOmSendMail(girlGObj, 62, boyGObj);

        scpFadeIn(3.0f);
    } else {
        iosThreadSetPri(&((GProc *)th)->thread, 34);
    }

    if (padAct >= 0) {
        iosPadActStop(padAct);
    }

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 532);

    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
}
#endif

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

#ifdef VERSION_AUG6
    scpAdpcmPlayRequestFunc(18, &sekizo5c, 1, 1, 1);

    while (sekizo5c == 0) {
        _ACTWait(1);
    }
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
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

    stage_SetAnimation(297, 1, 0);

    sekizo_4r = iosPadActRequest(boyPad, 9);
    sekizo_4r_vol = 128;
    iosPadActVolumeSet(sekizo_4r, 128);
#else
    scpAdpcmPlayRequestFunc(18, &stair5d, 1, 1, 1);

    while (stair5d == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(1, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(327, 1, 0);
#else
    stage_SetAnimation(331, 1, 0);
#endif

    st04r_yure = iosPadActRequest(boyPad, 9);
    st04r_yure_vol = 128;
    iosPadActVolumeSet(st04r_yure, 128);
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

    sceVu0SubVector(dir, test_CURRENTROOT(self), test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, dir);

    scpBoyControlReadDisable = 1;

    sceVu0SubVector(dir, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    scpSekizouCheckPoint();

#ifdef VERSION_AUG6
    scpPlayMot(girlGObj, 573);
    scpPlayWaitMotEnd(girlGObj);

    gflagOn(229);

    while (stage_CheckAnimationFrame(297, 151, 0) == 0) {
#else
    scpPlayMot(girlGObj, 645);
    scpPlayWaitMotEnd(girlGObj);

    gflagOn(254);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(327, 151, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(331, 151, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#ifdef VERSION_AUG6
    iosPadActStop(sekizo_4r);

    scpPlayMot(girlGObj, 514);
#else
    iosPadActStop(st04r_yure);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(327) == 0) {
#else
    while (stage_CheckAnimationFinish(331) == 0) {
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

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
#endif

    scpBoyControlReadDisable = 0;
}

void actSt04rRope1Chk(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    while (gflagChk(236) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1351))) {
#else
    while (gflagChk(261) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1459))) {
#endif
        case 0:
            _ACTWait(1);
            break;
        case 1:
#ifdef VERSION_AUG6
            stage_SetAnimation(290, 1, 0);

            while (stage_CheckAnimationFinish(290) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(320, 1, 0);
#else
            stage_SetAnimation(324, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
            while (stage_CheckAnimationFinish(320) == 0) {
#else
            while (stage_CheckAnimationFinish(324) == 0) {
#endif
#endif
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
#ifdef VERSION_AUG6
            scpSearchGobj(1351)->active = 0;

            gflagOn(236);

            stage_SetAnimation(286, 1, 0);

            while (stage_CheckAnimationFinish(286) == 0) {
#else
            scpSearchGobj(1459)->active = 0;

            gflagOn(261);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(316, 1, 0);
#else
            stage_SetAnimation(320, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
            while (stage_CheckAnimationFinish(316) == 0) {
#else
            while (stage_CheckAnimationFinish(320) == 0) {
#endif
#endif
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

#ifdef VERSION_AUG6
    while (gflagChk(237) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1352))) {
#else
    while (gflagChk(262) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1460))) {
#endif
        case 0:
            _ACTWait(1);
            break;
        case 1:
#ifdef VERSION_AUG6
            stage_SetAnimation(291, 1, 0);

            while (stage_CheckAnimationFinish(291) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(321, 1, 0);
#else
            stage_SetAnimation(325, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
            while (stage_CheckAnimationFinish(321) == 0) {
#else
            while (stage_CheckAnimationFinish(325) == 0) {
#endif
#endif
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
#ifdef VERSION_AUG6
            scpSearchGobj(1352)->active = 0;

            gflagOn(237);

            stage_SetAnimation(287, 1, 0);

            while (stage_CheckAnimationFinish(287) == 0) {
#else
            scpSearchGobj(1460)->active = 0;

            gflagOn(262);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(317, 1, 0);
#else
            stage_SetAnimation(321, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
            while (stage_CheckAnimationFinish(317) == 0) {
#else
            while (stage_CheckAnimationFinish(321) == 0) {
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

    stage_SetAnimation(294, 1, 0);

    while (stage_CheckAnimationFrame(294, 75, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFinish(294) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}
#else
void actSt04rBrgCommon(GObj *volatile self)
{
    GProc *th;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif

    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(86, &sekizo5c, 1, 1, 0);

    th = actCreateSubThread(actSt04rBrg1Sub, 21);

    demoEnd = 0;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&((GProc *)th)->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&sekizo5c, 256);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(sekizo_4r, 0, -1);

        scpFadeIn(3.0f);
    }

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
}
#endif

void actSt04rRope3Chk(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    while (gflagChk(238) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1353))) {
#else
    while (gflagChk(263) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1461))) {
#endif
        case 0:
            _ACTWait(1);
            break;
        case 1:
#ifdef VERSION_AUG6
            stage_SetAnimation(292, 1, 0);

            while (stage_CheckAnimationFinish(292) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(322, 1, 0);
#else
            stage_SetAnimation(326, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
            while (stage_CheckAnimationFinish(322) == 0) {
#else
            while (stage_CheckAnimationFinish(326) == 0) {
#endif
#endif
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
#ifdef VERSION_AUG6
            scpSearchGobj(1353)->active = 0;

            gflagOn(238);

            stage_SetAnimation(288, 1, 0);

            while (stage_CheckAnimationFinish(288) == 0) {
#else
            scpSearchGobj(1461)->active = 0;

            gflagOn(263);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(318, 1, 0);
#else
            stage_SetAnimation(322, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
            while (stage_CheckAnimationFinish(318) == 0) {
#else
            while (stage_CheckAnimationFinish(322) == 0) {
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
void actSt04rRope4Chk(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(239) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1354))) {
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
            scpSearchGobj(1354)->active = 0;

            gflagOn(239);

            stage_SetAnimation(289, 1, 0);

            while (stage_CheckAnimationFinish(289) == 0) {
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

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);

    gflagOn(249);

    scpSleepEnemyAll();
    _ACTWait(5);

    stage_SetAnimation(303, 1, 0);

    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(303, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;
}
#else
void actSt04rRope4Chk(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    while (gflagChk(264) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1462))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(323, 1, 0);
#else
            stage_SetAnimation(327, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
            while (stage_CheckAnimationFinish(323) == 0) {
#else
            while (stage_CheckAnimationFinish(327) == 0) {
#endif
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1462)->active = 0;

            gflagOn(264);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(319, 1, 0);
#else
            stage_SetAnimation(323, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
            while (stage_CheckAnimationFinish(319) == 0) {
#else
            while (stage_CheckAnimationFinish(323) == 0) {
#endif
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        }
    }
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

    gflagOn(274);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        if (GetCharHeldItem(boyGObj) != 1) {
            scpPlayStart(boyGObj);
            scpPlayStart(girlGObj);
        }

        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(333, 1, 0);
#else
    stage_SetAnimation(337, 1, 0);
#endif

    soundSeDefPlay(1332, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(333, 30, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(337, 30, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(girlGObj, 63, boyGObj);
    }

    scpBoyControlReadDisable = 0;
}
#endif

#ifdef VERSION_AUG6
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

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);

    gflagOn(250);

    scpSleepEnemyAll();
    _ACTWait(5);

    stage_SetAnimation(304, 1, 0);

    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(304, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;
}
#else
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

    gflagOn(275);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        if (GetCharHeldItem(boyGObj) != 1) {
            scpPlayStart(boyGObj);
            scpPlayStart(girlGObj);
        }

        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(334, 1, 0);
#else
    stage_SetAnimation(338, 1, 0);
#endif

    soundSeDefPlay(1332, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(334, 30, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(338, 30, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(girlGObj, 63, boyGObj);
    }

    scpBoyControlReadDisable = 0;
}
#endif

#ifdef VERSION_AUG6
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

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);

    gflagOn(251);

    scpSleepEnemyAll();
    _ACTWait(5);

    stage_SetAnimation(305, 1, 0);

    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(305, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;
}
#else
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

    gflagOn(276);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        if (GetCharHeldItem(boyGObj) != 1) {
            scpPlayStart(boyGObj);
            scpPlayStart(girlGObj);
        }

        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(335, 1, 0);
#else
    stage_SetAnimation(339, 1, 0);
#endif

    soundSeDefPlay(1332, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(335, 30, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(339, 30, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(girlGObj, 63, boyGObj);
    }

    scpBoyControlReadDisable = 0;
}
#endif

#ifdef VERSION_AUG6
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

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);

    gflagOn(252);

    scpSleepEnemyAll();
    _ACTWait(5);

    stage_SetAnimation(306, 1, 0);

    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(306, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;
}
#else
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

    gflagOn(277);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        if (GetCharHeldItem(boyGObj) != 1) {
            scpPlayStart(boyGObj);
            scpPlayStart(girlGObj);
        }

        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(336, 1, 0);
#else
    stage_SetAnimation(340, 1, 0);
#endif

    soundSeDefPlay(1332, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(336, 30, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(340, 30, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(girlGObj, 63, boyGObj);
    }

    scpBoyControlReadDisable = 0;
}
#endif

#ifdef VERSION_AUG6
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

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);

    gflagOn(253);

    scpSleepEnemyAll();
    _ACTWait(5);

    stage_SetAnimation(307, 1, 0);

    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(307, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;
}
#else
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

    gflagOn(278);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        if (GetCharHeldItem(boyGObj) != 1) {
            scpPlayStart(boyGObj);
            scpPlayStart(girlGObj);
        }

        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(337, 1, 0);
#else
    stage_SetAnimation(341, 1, 0);
#endif

    soundSeDefPlay(1332, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(337, 30, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(341, 30, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(girlGObj, 63, boyGObj);
    }

    scpBoyControlReadDisable = 0;
}
#endif

#ifdef VERSION_AUG6
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

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);

    gflagOn(254);

    scpSleepEnemyAll();
    _ACTWait(5);

    stage_SetAnimation(308, 1, 0);

    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(308, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;
}
#else
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

    gflagOn(279);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        if (GetCharHeldItem(boyGObj) != 1) {
            scpPlayStart(boyGObj);
            scpPlayStart(girlGObj);
        }

        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(338, 1, 0);
#else
    stage_SetAnimation(342, 1, 0);
#endif

    soundSeDefPlay(1332, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(338, 30, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(342, 30, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(girlGObj, 63, boyGObj);
    }

    scpBoyControlReadDisable = 0;
}
#endif

#ifdef VERSION_AUG6
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

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 514);

    gflagOn(255);

    scpSleepEnemyAll();
    _ACTWait(5);

    stage_SetAnimation(309, 1, 0);

    soundSeDefPlay(1308, 0, 0, 1);

    while (stage_CheckAnimationFrame(309, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;
}
#else
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

    gflagOn(280);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        if (GetCharHeldItem(boyGObj) != 1) {
            scpPlayStart(boyGObj);
            scpPlayStart(girlGObj);
        }

        scpPlayMotReq(boyGObj, 1);
        scpPlayMotReq(girlGObj, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(339, 1, 0);
#else
    stage_SetAnimation(343, 1, 0);
#endif

    soundSeDefPlay(1332, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(339, 30, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(343, 30, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(girlGObj, 63, boyGObj);
    }

    scpBoyControlReadDisable = 0;
}

void actSt04rBarricadeChk(GObj *volatile self)
{
    GObj *n;

    while ((n = scpIsBombExplode(19)) == 0 || scpTriggerBall(self, n, 350.0f) == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    gflagOn(265);
    _ACTWait(5);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(340, 1, 0);
#else
    stage_SetAnimation(344, 1, 0);
#endif

    SetCameraFlag_LwsCutBack();

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(340) == 0) {
#else
    while (stage_CheckAnimationFinish(344) == 0) {
#endif
        if ((pad[0].flags & 0x800) != 0 && scpAdpcmPlayRequestNum() == 0) {
            scpFadeOut(16.0f, 0, 0, 0);

            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
            stage_SetAnimation(340, 0, -1);
#else
            stage_SetAnimation(344, 0, -1);
#endif

            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 3);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
}
#endif

void actSt04rGondolaChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (scpTriggerFloorAttr(boyGObj, 0xA000000) == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
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
    if (gflagChk(257) != 0) {
        stage_SetAnimation(200, 1, 200);
#else
    if (gflagChk(282) != 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(225, 1, 200);
#else
        stage_SetAnimation(229, 1, 200);
#endif
#endif

        scpWakeupItemWithBoundary(-675.0f, -150.0f, -1600.0f, 200.0f);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        while (stage_CheckAnimationFrame(225, 220, 0) == 0) {
#else
#ifdef VERSION_AUG6
        while (stage_CheckAnimationFrame(200, 220, 0) == 0) {
#else
        while (stage_CheckAnimationFrame(229, 220, 0) == 0) {
#endif
#endif
            _ACTWait(1);
        }
        _ACTWait(1);

#ifdef VERSION_AUG6
        soundSeDefPlay(1297, 0, 0, 1);

        while (stage_CheckAnimationFrame(200, 240, 0) == 0) {
#else
        soundSeDefPlay(1321, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        while (stage_CheckAnimationFrame(225, 240, 0) == 0) {
#else
        while (stage_CheckAnimationFrame(229, 240, 0) == 0) {
#endif
#endif
            _ACTWait(1);
        }
        _ACTWait(1);

#ifdef VERSION_AUG6
        soundSeDefPlay(1298, 0, 0, 1);

        while (stage_CheckAnimationFrame(200, 250, 0) == 0) {
#else
        soundSeDefPlay(1322, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        while (stage_CheckAnimationFrame(225, 250, 0) == 0) {
#else
        while (stage_CheckAnimationFrame(229, 250, 0) == 0) {
#endif
#endif
            _ACTWait(1);
        }
        _ACTWait(1);

#ifdef VERSION_AUG6
        soundSeDefPlay(1295, 0, 0, 1);

        while (stage_CheckAnimationFrame(200, 415, 0) == 0) {
#else
        soundSeDefPlay(1319, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        while (stage_CheckAnimationFrame(225, 415, 0) == 0) {
#else
        while (stage_CheckAnimationFrame(229, 415, 0) == 0) {
#endif
#endif
            _ACTWait(1);
        }
        _ACTWait(1);

#ifdef VERSION_AUG6
        soundSeDefPlay(1296, 0, 0, 1);

        while (stage_CheckAnimationFinish(200) == 0) {
#else
        soundSeDefPlay(1320, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        while (stage_CheckAnimationFinish(225) == 0) {
#else
        while (stage_CheckAnimationFinish(229) == 0) {
#endif
#endif
            _ACTWait(1);
        }
        _ACTWait(1);

#ifdef VERSION_AUG6
        gflagOff(257);
    } else {
        stage_SetAnimation(200, 1, 0);
#else
        gflagOff(282);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(225, 1, 0);
#else
        stage_SetAnimation(229, 1, 0);
#endif
#endif

        scpWakeupItemWithBoundary(-675.0f, -1200.0f, -1600.0f, 200.0f);

#ifdef VERSION_AUG6
        soundSeDefPlay(1295, 0, 0, 1);

        while (stage_CheckAnimationFrame(200, 145, 0) == 0) {
#else
        SetGirlDangerGObj(boyGObj);

        soundSeDefPlay(1319, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        while (stage_CheckAnimationFrame(225, 145, 0) == 0) {
#else
        while (stage_CheckAnimationFrame(229, 145, 0) == 0) {
#endif
#endif
            _ACTWait(1);
        }
        _ACTWait(1);

#ifdef VERSION_AUG6
        soundSeDefPlay(1296, 0, 0, 1);
        soundSeDefPlay(1297, 0, 0, 1);

        while (stage_CheckAnimationFrame(200, 170, 0) == 0) {
#else
        soundSeDefPlay(1320, 0, 0, 1);
        soundSeDefPlay(1321, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        while (stage_CheckAnimationFrame(225, 170, 0) == 0) {
#else
        while (stage_CheckAnimationFrame(229, 170, 0) == 0) {
#endif
#endif
            _ACTWait(1);
        }
        _ACTWait(1);

#ifdef VERSION_AUG6
        soundSeDefPlay(1298, 0, 0, 1);

        while (stage_CheckAnimationFrame(200, 200, 1) == 0) {
#else
        soundSeDefPlay(1322, 0, 0, 1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        while (stage_CheckAnimationFrame(225, 200, 1) == 0) {
#else
        while (stage_CheckAnimationFrame(229, 200, 1) == 0) {
#endif
#endif
            _ACTWait(1);
        }
        _ACTWait(1);

#ifdef VERSION_AUG6
        gflagOn(257);
#else
        ClearGirlDangerGObj();

        gflagOn(282);
    }

    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0xA000000) == 0) {
        gflagOn(286);
    } else {
        gflagOff(286);
#endif
    }

    scpBoyControlReadDisable = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
#ifdef VERSION_AUG6
    lt_switch_layout(50);
#else
    lt_switch_layout(54);
#endif
#endif

    scpWakeupEnemyAll();

    gondola_chk_mes[0].func = actSt04rGondolaCharaChk;
    sub->mail = gondola_chk_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actSt04rSolarStageChange(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(209) == 0) {
        solar_stage_change_mes[0].func = actSt04rSolarStageChangeChk;
        act->mail = solar_stage_change_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(234) == 0) {
        solar_stage_change_mes[0].func = actSt04rSolarStageChangeChk;
        act->mail = solar_stage_change_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt04rCrest01(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(218) == 0) {
        stage_SetAnimation(275, 0, 0);
#else
    if (gflagChk(243) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(305, 0, 0);
#else
        stage_SetAnimation(309, 0, 0);
#endif
#endif

        crest01_mes[0].func = actSt04rCrestMain;
        act->mail = crest01_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(275, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(305, 0, -1);
#else
        stage_SetAnimation(309, 0, -1);
#endif
#endif
        scpBoyControlReadDisable = 0;
    }
}

void actSt04rCrest03(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(220) == 0) {
        stage_SetAnimation(279, 0, 0);
#else
    if (gflagChk(245) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(309, 0, 0);
#else
        stage_SetAnimation(313, 0, 0);
#endif
#endif

        crest03_mes[0].func = actSt04rCrest3Main;
        act->mail = crest03_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(279, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(309, 0, -1);
#else
        stage_SetAnimation(313, 0, -1);
#endif
#endif
        scpBoyControlReadDisable = 0;
    }
}

void actSt04rC1Ball(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(225) == 0) {
        scpSearchGobj(1300)->active = 0;
        scpSearchGobj(1301)->active = 0;

        stage_SetAnimation(283, 0, 0);
#else
    if (gflagChk(250) == 0) {
        scpSearchGobj(1404)->active = 0;
        scpSearchGobj(1405)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(313, 0, 0);
#else
        stage_SetAnimation(317, 0, 0);
#endif
#endif

        c1_ball_mes[0].func = actSt04rC1BallMain;
        act->mail = c1_ball_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(283, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(313, 0, -1);
#else
        stage_SetAnimation(317, 0, -1);
#endif
#endif
    }
}

void actSt04rC2Ball(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(226) == 0) {
        scpSearchGobj(1376)->active = 0;
        scpSearchGobj(1377)->active = 0;

        stage_SetAnimation(284, 0, 0);
#else
    if (gflagChk(251) == 0) {
        scpSearchGobj(1487)->active = 0;
        scpSearchGobj(1488)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(314, 0, 0);
#else
        stage_SetAnimation(318, 0, 0);
#endif
#endif

        c2_ball_mes[0].func = actSt04rC2BallMain;
        act->mail = c2_ball_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(284, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(314, 0, -1);
#else
        stage_SetAnimation(318, 0, -1);
#endif
#endif
    }
}

void actSt04rC3Ball(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(227) == 0) {
        scpSearchGobj(1378)->active = 0;
        scpSearchGobj(1379)->active = 0;

        stage_SetAnimation(285, 0, 0);
#else
    if (gflagChk(252) == 0) {
        scpSearchGobj(1489)->active = 0;
        scpSearchGobj(1490)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(315, 0, 0);
#else
        stage_SetAnimation(319, 0, 0);
#endif
#endif

        c3_ball_mes[0].func = actSt04rC3BallMain;
        act->mail = c3_ball_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(285, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(315, 0, -1);
#else
        stage_SetAnimation(319, 0, -1);
#endif
#endif
    }
}

void actSt04rStair(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(228) == 0) {
#else
    if (gflagChk(253) == 0) {
#endif
        if (girlGObj != 0) {
            stair_mes[0].func = actSt04rStairChk;
            act->mail = stair_mes;
#ifdef VERSION_AUG6
            ACTSendMailCorrect(self, 393);
#else
            ACTSendMailCorrect(self, 430);
#endif
            _ACTWait(0);
        }
    } else {
#ifdef VERSION_AUG6
        scpSearchGobj(1414)->active = 0;

        stage_SetAnimation(317, -1, -2);
#else
        scpSearchGobj(1523)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(347, -1, -2);
#else
        stage_SetAnimation(351, -1, -2);
#endif
#endif
    }
}

void actSt04rBrg1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(234) == 0) {
        brg1_mes[0].func = actSt04rBrg1Chk;
        act->mail = brg1_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(259) == 0) {
        brg1_mes[0].func = actSt04rBrg1Chk;
        act->mail = brg1_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt04rBrg2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(235) == 0) {
        brg2_mes[0].func = actSt04rBrg2Chk;
        act->mail = brg2_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(260) == 0) {
        brg2_mes[0].func = actSt04rBrg2Chk;
        act->mail = brg2_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt04rBrg1Way(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(234) == 0) {
        brg1_way_mes[0].func = actSt04rBrg1WayChk;
        act->mail = brg1_way_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(259) == 0) {
        brg1_way_mes[0].func = actSt04rBrg1WayChk;
        act->mail = brg1_way_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt04rBrg2Way(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(235) == 0) {
        brg2_way_mes[0].func = actSt04rBrg2WayChk;
        act->mail = brg2_way_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(260) == 0) {
        brg2_way_mes[0].func = actSt04rBrg2WayChk;
        act->mail = brg2_way_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt04rRope1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(236) == 0) {
        stage_SetAnimation(286, 0, 0);
#else
    if (gflagChk(261) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(316, 0, 0);
#else
        stage_SetAnimation(320, 0, 0);
#endif
#endif

        rope1_mes[0].func = actSt04rRope1Chk;
        act->mail = rope1_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(286, 0, -1);

        scpSearchGobj(1351)->active = 0;
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(316, 0, -1);
#else
        stage_SetAnimation(320, 0, -1);
#endif

        scpSearchGobj(1459)->active = 0;
#endif
    }
}

void actSt04rRope2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(237) == 0) {
        stage_SetAnimation(287, 0, 0);
#else
    if (gflagChk(262) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(317, 0, 0);
#else
        stage_SetAnimation(321, 0, 0);
#endif
#endif

        rope2_mes[0].func = actSt04rRope2Chk;
        act->mail = rope2_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(287, 0, -1);

        scpSearchGobj(1352)->active = 0;
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(317, 0, -1);
#else
        stage_SetAnimation(321, 0, -1);
#endif

        scpSearchGobj(1460)->active = 0;
#endif
    }
}

void actSt04rRope3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(238) == 0) {
        stage_SetAnimation(288, 0, 0);
#else
    if (gflagChk(263) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(318, 0, 0);
#else
        stage_SetAnimation(322, 0, 0);
#endif
#endif

        rope3_mes[0].func = actSt04rRope3Chk;
        act->mail = rope3_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(288, 0, -1);

        scpSearchGobj(1353)->active = 0;
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(318, 0, -1);
#else
        stage_SetAnimation(322, 0, -1);
#endif

        scpSearchGobj(1461)->active = 0;
#endif
    }
}

void actSt04rRope4(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(239) == 0) {
        stage_SetAnimation(289, 0, 0);
#else
    if (gflagChk(264) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(319, 0, 0);
#else
        stage_SetAnimation(323, 0, 0);
#endif
#endif

        rope4_mes[0].func = actSt04rRope4Chk;
        act->mail = rope4_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(289, 0, -1);

        scpSearchGobj(1354)->active = 0;
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(319, 0, -1);
#else
        stage_SetAnimation(323, 0, -1);
#endif

        scpSearchGobj(1462)->active = 0;
#endif
    }
}

void actSt04rSekizo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(229) == 0) {
        stage_SetAnimation(297, 0, 0);
#else
    if (gflagChk(254) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(327, 0, 0);
#else
        stage_SetAnimation(331, 0, 0);
#endif
#endif

        sekizo_mes[0].func = actSt04rSekizoChk;
        act->mail = sekizo_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(297, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(327, 0, -1);
#else
        stage_SetAnimation(331, 0, -1);
#endif
#endif
    }
}

void actSt04rBarricade(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(240) == 0) {
        stage_SetAnimation(310, 0, 0);
#else
    if (gflagChk(265) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(340, 0, 0);
#else
        stage_SetAnimation(344, 0, 0);
#endif
#endif

        barricade_mes[0].func = actSt04rBarricadeChk;
        act->mail = barricade_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(310, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(340, 0, -1);
#else
        stage_SetAnimation(344, 0, -1);
#endif
#endif
    }
}

void actSt04rGondola(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(257) != 0) {
        stage_SetAnimation(200, 0, 200);
#else
    if (gflagChk(282) != 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(225, 0, 200);
#else
        stage_SetAnimation(229, 0, 200);
#endif
#endif

        gondola_mes[0].func = actSt04rGondolaChk;
        act->mail = gondola_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(200, 0, 0);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(225, 0, 0);
#else
        stage_SetAnimation(229, 0, 0);
#endif
#endif

        gondola2_mes[0].func = actSt04rGondolaChk;
        act->mail = gondola2_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt04rCrest01XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(218) == 0) {
        stage_SetAnimation(280, 0, 0);
    } else {
        stage_SetAnimation(280, 0, -1);
#else
    if (gflagChk(243) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(310, 0, 0);
#else
        stage_SetAnimation(314, 0, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(310, 0, -1);
#else
        stage_SetAnimation(314, 0, -1);
#endif
#endif
    }
}

void actSt04rCrest02XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(219) == 0) {
        stage_SetAnimation(281, 0, 0);
    } else {
        stage_SetAnimation(281, 0, -1);
#else
    if (gflagChk(244) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(311, 0, 0);
#else
        stage_SetAnimation(315, 0, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(311, 0, -1);
#else
        stage_SetAnimation(315, 0, -1);
#endif
#endif
    }
}

void actSt04rCrest03XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(220) == 0) {
        stage_SetAnimation(282, 0, 0);
    } else {
        stage_SetAnimation(282, 0, -1);
#else
    if (gflagChk(245) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(312, 0, 0);
#else
        stage_SetAnimation(316, 0, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(312, 0, -1);
#else
        stage_SetAnimation(316, 0, -1);
#endif
#endif
    }
}

void actSt04rC2BallXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(226) == 0) {
        stage_SetAnimation(284, 0, 0);

        scpSearchGobj(1304)->active = 0;
        scpSearchGobj(1305)->active = 0;
    } else {
        stage_SetAnimation(284, 0, -1);
#else
    if (gflagChk(251) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(314, 0, 0);
#else
        stage_SetAnimation(318, 0, 0);
#endif

        scpSearchGobj(1408)->active = 0;
        scpSearchGobj(1409)->active = 0;
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(314, 0, -1);
#else
        stage_SetAnimation(318, 0, -1);
#endif
#endif
    }
}

void actSt04rC3BallXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(227) == 0) {
        stage_SetAnimation(285, 0, 0);

        scpSearchGobj(1453)->active = 0;
        scpSearchGobj(1454)->active = 0;
    } else {
        stage_SetAnimation(285, 0, -1);
#else
    if (gflagChk(252) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(315, 0, 0);
#else
        stage_SetAnimation(319, 0, 0);
#endif

        scpSearchGobj(1562)->active = 0;
        scpSearchGobj(1563)->active = 0;
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(315, 0, -1);
#else
        stage_SetAnimation(319, 0, -1);
#endif
#endif
    }
}

void actSt04rTorch1_1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(241) == 0) {
        torch1_1_mes[0].func = actSt04rTorch1_1Chk;
        act->mail = torch1_1_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1300);
#else
    if (gflagChk(266) == 0) {
        torch1_1_mes[0].func = actSt04rTorch1_1Chk;
        act->mail = torch1_1_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1404);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(206, 0, -1);
#else
        stage_SetAnimation(210, 0, -1);
#endif
#endif
    }
}

void actSt04rTorch1_2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(242) == 0) {
        torch1_2_mes[0].func = actSt04rTorch1_2Chk;
        act->mail = torch1_2_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1301);
#else
    if (gflagChk(267) == 0) {
        torch1_2_mes[0].func = actSt04rTorch1_2Chk;
        act->mail = torch1_2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1405);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(207, 0, -1);
#else
        stage_SetAnimation(211, 0, -1);
#endif
#endif
    }
}

void actSt04rTorch2_1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(243) != 0 || gflagChk(245) != 0) {
        scpTorchLightOn(1376);
#else
    if (gflagChk(268) != 0 || gflagChk(270) != 0) {
        scpTorchLightOn(1487);
#endif
    } else {
        torch2_1_mes[0].func = actSt04rTorch2_1Chk;
        act->mail = torch2_1_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt04rTorch2_2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(244) != 0 || gflagChk(246) != 0) {
        scpTorchLightOn(1377);
#else
    if (gflagChk(269) != 0 || gflagChk(271) != 0) {
        scpTorchLightOn(1488);
#endif
    } else {
        torch2_2_mes[0].func = actSt04rTorch2_2Chk;
        act->mail = torch2_2_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt04rTorch3_1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(247) == 0) {
        torch3_1_mes[0].func = actSt04rTorch3_1Chk;
        act->mail = torch3_1_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1378);
#else
    if (gflagChk(272) == 0) {
        torch3_1_mes[0].func = actSt04rTorch3_1Chk;
        act->mail = torch3_1_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1489);
#endif
    }
}

void actSt04rTorch3_2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(248) == 0) {
        torch3_2_mes[0].func = actSt04rTorch3_2Chk;
        act->mail = torch3_2_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1379);
#else
    if (gflagChk(273) == 0) {
        torch3_2_mes[0].func = actSt04rTorch3_2Chk;
        act->mail = torch3_2_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1490);
#endif
    }
}

void actSt04rTorch2_1XL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(243) != 0 || gflagChk(245) != 0) {
        scpTorchLightOn(1304);
#else
    if (gflagChk(268) != 0 || gflagChk(270) != 0) {
        scpTorchLightOn(1408);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(208, 0, -1);
#else
        stage_SetAnimation(212, 0, -1);
#endif
#endif
    } else {
        torch2_1xl_mes[0].func = actSt04rTorch2_1XLChk;
        act->mail = torch2_1xl_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt04rTorch2_2XL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(244) != 0 || gflagChk(246) != 0) {
        scpTorchLightOn(1305);
#else
    if (gflagChk(269) != 0 || gflagChk(271) != 0) {
        scpTorchLightOn(1409);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(209, 0, -1);
#else
        stage_SetAnimation(213, 0, -1);
#endif
#endif
    } else {
        torch2_2xl_mes[0].func = actSt04rTorch2_2XLChk;
        act->mail = torch2_2xl_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt04rTorch3_1XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(247) != 0) {
        scpTorchLightOn(1453);
#else
    if (gflagChk(272) != 0) {
        scpTorchLightOn(1562);
#endif
    }
}

void actSt04rTorch3_2XL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(248) != 0) {
        scpTorchLightOn(1454);
#else
    if (gflagChk(273) != 0) {
        scpTorchLightOn(1563);
#endif
    }
}

void actSt04rMonyou01(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(249) == 0) {
        stage_SetAnimation(303, 0, 0);
#else
    if (gflagChk(274) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(333, 0, 0);
#else
        stage_SetAnimation(337, 0, 0);
#endif
#endif

        monyou01_mes[0].func = actSt04rMonyou01Chk;
        act->mail = monyou01_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(303, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(333, 0, -1);
#else
        stage_SetAnimation(337, 0, -1);
#endif
#endif
    }
}

void actSt04rMonyou02(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(250) == 0) {
        stage_SetAnimation(304, 0, 0);
#else
    if (gflagChk(275) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(334, 0, 0);
#else
        stage_SetAnimation(338, 0, 0);
#endif
#endif

        monyou02_mes[0].func = actSt04rMonyou02Chk;
        act->mail = monyou02_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(304, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(334, 0, -1);
#else
        stage_SetAnimation(338, 0, -1);
#endif
#endif
    }
}

void actSt04rMonyou03(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(251) == 0) {
        stage_SetAnimation(305, 0, 0);
#else
    if (gflagChk(276) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(335, 0, 0);
#else
        stage_SetAnimation(339, 0, 0);
#endif
#endif

        monyou03_mes[0].func = actSt04rMonyou03Chk;
        act->mail = monyou03_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(305, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(335, 0, -1);
#else
        stage_SetAnimation(339, 0, -1);
#endif
#endif
    }
}

void actSt04rMonyou04(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(252) == 0) {
        stage_SetAnimation(306, 0, 0);
#else
    if (gflagChk(277) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(336, 0, 0);
#else
        stage_SetAnimation(340, 0, 0);
#endif
#endif

        monyou04_mes[0].func = actSt04rMonyou04Chk;
        act->mail = monyou04_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(306, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(336, 0, -1);
#else
        stage_SetAnimation(340, 0, -1);
#endif
#endif
    }
}

void actSt04rMonyou05(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(253) == 0) {
        stage_SetAnimation(307, 0, 0);
#else
    if (gflagChk(278) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(337, 0, 0);
#else
        stage_SetAnimation(341, 0, 0);
#endif
#endif

        monyou05_mes[0].func = actSt04rMonyou05Chk;
        act->mail = monyou05_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(307, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(337, 0, -1);
#else
        stage_SetAnimation(341, 0, -1);
#endif
#endif
    }
}

void actSt04rMonyou06(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(254) == 0) {
        stage_SetAnimation(308, 0, 0);
#else
    if (gflagChk(279) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(338, 0, 0);
#else
        stage_SetAnimation(342, 0, 0);
#endif
#endif

        monyou06_mes[0].func = actSt04rMonyou06Chk;
        act->mail = monyou06_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(308, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(338, 0, -1);
#else
        stage_SetAnimation(342, 0, -1);
#endif
#endif
    }
}

void actSt04rMonyou07(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(255) == 0) {
        stage_SetAnimation(309, 0, 0);
#else
    if (gflagChk(280) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(339, 0, 0);
#else
        stage_SetAnimation(343, 0, 0);
#endif
#endif

        monyou07_mes[0].func = actSt04rMonyou07Chk;
        act->mail = monyou07_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(309, 0, -1);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(339, 0, -1);
#else
        stage_SetAnimation(343, 0, -1);
#endif
#endif
    }
}

void actSt05cDoorInit(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(148) != 0 && gflagChk(209) == 0) {
        stage_SetAnimation(313, 0, -1);
    }

    if (gflagChk(148) == 0 || gflagChk(209) != 0) {
        stage_SetAnimation(313, 0, 0);
#else
    if (gflagChk(165) != 0 && gflagChk(234) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(343, 0, -1);
#else
        stage_SetAnimation(347, 0, -1);
#endif
    }

    if (gflagChk(165) == 0 || gflagChk(234) != 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(343, 0, 0);
#else
        stage_SetAnimation(347, 0, 0);
#endif
#endif
    }
}
#endif

void actSt04rC1BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
#ifdef VERSION_AUG6
    scpBoyControlReadDisable = 0;
#endif

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
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
#else
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt04rC1BallTurn(GObj *volatile self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    turnBall(self, 250, 313, 1404, 1405);
#else
    turnBall(self, 250, 317, 1404, 1405);
#endif
#endif
#endif
}

void actSt04rC2BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
#ifdef VERSION_AUG6
    scpBoyControlReadDisable = 0;
#endif

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
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
#else
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt04rC2BallTurn(GObj *volatile self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    turnBall(self, 251, 314, 1487, 1488);
#else
    turnBall(self, 251, 318, 1487, 1488);
#endif
#endif
#endif
}

void actSt04rC3BallMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
#ifdef VERSION_AUG6
    scpBoyControlReadDisable = 0;
#endif

    sub->mainMail = c3_ball_main_mes;
    while (1) {
        _ACTWait(1);
    }
}

#ifdef VERSION_NTSC
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
#else
void actSt04rC3BallSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 1;

    sub->mainMail = 0;

    c3_ball_switch_mes[0].func = actSt04rC3BallTurn;
    sub->mail = c3_ball_switch_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
    _ACTWait(0);
#else
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt04rC3BallTurn(GObj *volatile self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    turnBall(self, 252, 315, 1489, 1490);
#else
    turnBall(self, 252, 319, 1489, 1490);
#endif
}

void actSt04rCrestMain(GObj *volatile self)
{
    while (scpIsTorchLightOn(1404) == 0 || scpIsTorchLightOn(1405) == 0 || gflagChk(250) == 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    gateAnim = 305;
#else
    gateAnim = 309;
#endif
    gateAdpcm = 27;
    openGate(self);
    _ACTWait(1);

    gflagOn(243);
    gflagOn(246);
    gflagOff(247);
    gflagOff(248);
    gflagOff(249);
    gflagOff(233);
#endif
}

void actSt04rSolarStageChangeChk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (gflagChk(218) == 0 || gflagChk(219) == 0 || gflagChk(220) == 0 || gflagChk(207) == 0) {
#else
    while (gflagChk(243) == 0 || gflagChk(244) == 0 || gflagChk(245) == 0 || gflagChk(232) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    RequestStageChange(8, boyGObj, girlGObj, 2.0f, 8.0f);
#else
    RequestStageChange(8, boyGObj, 0, 2.0f, 8.0f);
#endif
}
#endif

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

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
void actSt04rBrg1Chk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (gflagChk(261) == 0 || gflagChk(262) == 0) {
        _ACTWait(1);
    }

    gflagOn(259);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    sekizo_4r = 324;
#else
    sekizo_4r = 328;
#endif

    brg1_chk_mes[0].func = actSt04rBrgCommon;
    sub->mail = brg1_chk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

static void actSt04rBrg1Sub(GObj *volatile self)
{
    _ACTWait(60);

    while (sekizo5c == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(sekizo5c->stream);

    stage_SetAnimation(sekizo_4r, 1, 0);

    while (stage_CheckAnimationFrame(sekizo_4r, 75, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

    while (stage_CheckAnimationFinish(sekizo_4r) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}
#endif

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

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
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
#else
void actSt04rBrg2Chk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (gflagChk(263) == 0 || gflagChk(264) == 0) {
        _ACTWait(1);
    }

    gflagOn(260);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    sekizo_4r = 325;
#else
    sekizo_4r = 329;
#endif

    brg2_chk_mes[0].func = actSt04rBrgCommon;
    sub->mail = brg2_chk_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt04rBrg1WayChk(GObj *volatile self)
{
    while (gflagChk(259) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(3, 1);
}

void actSt04rBrg2WayChk(GObj *volatile self)
{
    while (gflagChk(259) == 0 || gflagChk(260) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(4, 1);
}
#endif

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

#ifdef VERSION_AUG6
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

    stage_SetAnimation(310, 1, 0);

    while (stage_CheckAnimationFinish(310) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);
}
#endif

#ifdef VERSION_NTSC
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
#else
void actSt04rGondolaCharaChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

#ifdef VERSION_AUG6
    while (scpTriggerFloorAttr(boyGObj, 0xA000000) != 0) {
#else
    while (scpTriggerFloorAttr(boyGObj, 0xA000000) != 0 &&
           (gflagChk(286) == 0 || scpTriggerFloorAttr(girlGObj, 0xA000000) == 0)) {
#endif
        _ACTWait(1);
    }

    gondola_chara_chk_mes[0].func = actSt04rGondolaChk;
    sub->mail = gondola_chara_chk_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actSt04rTorch1_1Chk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (scpIsTorchLightOn(1300) == 0) {
#else
    while (scpIsTorchLightOn(1404) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(241);
#else
    gflagOn(266);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(206, 1, 0);
#else
    stage_SetAnimation(210, 1, 0);
#endif
#endif
}

void actSt04rTorch1_2Chk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (scpIsTorchLightOn(1301) == 0) {
#else
    while (scpIsTorchLightOn(1405) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(242);
#else
    gflagOn(267);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(207, 1, 0);
#else
    stage_SetAnimation(211, 1, 0);
#endif
#endif
}

void actSt04rTorch2_1Chk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (scpIsTorchLightOn(1376) == 0) {
#else
    while (scpIsTorchLightOn(1487) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(243);
#else
    gflagOn(268);
#endif
}

void actSt04rTorch2_2Chk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (scpIsTorchLightOn(1377) == 0) {
#else
    while (scpIsTorchLightOn(1488) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(244);
#else
    gflagOn(269);
#endif
}

void actSt04rTorch3_1Chk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (scpIsTorchLightOn(1378) == 0) {
#else
    while (scpIsTorchLightOn(1489) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(247);
#else
    gflagOn(272);
#endif
}

void actSt04rTorch3_2Chk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (scpIsTorchLightOn(1379) == 0) {
#else
    while (scpIsTorchLightOn(1490) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(248);
#else
    gflagOn(273);
#endif
}

void actSt04rTorch2_1XLChk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (scpIsTorchLightOn(1304) == 0) {
#else
    while (scpIsTorchLightOn(1408) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(245);
#else
    gflagOn(270);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(208, 1, 0);
#else
    stage_SetAnimation(212, 1, 0);
#endif
#endif
}

void actSt04rTorch2_2XLChk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (scpIsTorchLightOn(1305) == 0) {
#else
    while (scpIsTorchLightOn(1409) == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(246);
#else
    gflagOn(271);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(209, 1, 0);
#else
    stage_SetAnimation(213, 1, 0);
#endif
#endif
}
#endif
