#include "common.h"
#include "st04r.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
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

static ActMail c1_ball_main_mes[2] = {{406, actSt04rC1BallSwitch}, {429}};

static ActMail c1_ball_mes[2] = {{430}, {429}};

static ActMail c1_ball_switch_mes[2] = {{430}, {429}};

static ActMail c2_ball_main_mes[2] = {{406, actSt04rC2BallSwitch}, {429}};

static ActMail c2_ball_mes[2] = {{430}, {429}};

static ActMail c2_ball_switch_mes[2] = {{430}, {429}};

static ActMail c3_ball_main_mes[2] = {{407, actSt04rC3BallSwitch}, {429}};

static ActMail c3_ball_mes[2] = {{430}, {429}};

static ActMail c3_ball_switch_mes[2] = {{430}, {429}};

static ActMail crest01_mes[2] = {{430}, {429}};

static ActMail crest02_mes[2] = {{430}, {429}};

static ActMail crest03_mes[2] = {{430}, {429}};

static ActMail solar_beam_mes[2] = {{430}, {429}};

static ActMail solar_stage_change_mes[2] = {{430}, {429}};

static ActMail stair_mes[2] = {{430}, {429}};

static ActMail sekizo_mes[2] = {{430}, {429}};

static ActMail rope1_mes[2] = {{430}, {429}};

static ActMail rope2_mes[2] = {{430}, {429}};

static ActMail brg1_mes[2] = {{430}, {429}};

static ActMail brg1_chk_mes[2] = {{430}, {429}};

static ActMail rope3_mes[2] = {{430}, {429}};

static ActMail rope4_mes[2] = {{430}, {429}};

static ActMail brg2_mes[2] = {{430}, {429}};

static ActMail brg2_chk_mes[2] = {{430}, {429}};

static ActMail brg1_way_mes[2] = {{430}, {429}};

static ActMail brg2_way_mes[2] = {{430}, {429}};

static ActMail monyou01_mes[2] = {{430}, {429}};

static ActMail monyou02_mes[2] = {{430}, {429}};

static ActMail monyou03_mes[2] = {{430}, {429}};

static ActMail monyou04_mes[2] = {{430}, {429}};

static ActMail monyou05_mes[2] = {{430}, {429}};

static ActMail monyou06_mes[2] = {{430}, {429}};

static ActMail monyou07_mes[2] = {{430}, {429}};

static ActMail barricade_mes[2] = {{430}, {429}};

static ActMail gondola_mes[2] = {{430}, {429}};

static ActMail gondola2_mes[2] = {{430}, {429}};

static ActMail gondola_chk_mes[2] = {{430}, {429}};

static ActMail gondola_chara_chk_mes[2] = {{430}, {429}};

static ActMail torch1_1_mes[2] = {{430}, {429}};

static ActMail torch1_2_mes[2] = {{430}, {429}};

static ActMail torch2_1_mes[2] = {{430}, {429}};

static ActMail torch2_2_mes[2] = {{430}, {429}};

static ActMail torch3_1_mes[2] = {{430}, {429}};

static ActMail torch3_2_mes[2] = {{430}, {429}};

static ActMail torch2_1xl_mes[2] = {{430}, {429}};

static ActMail torch2_2xl_mes[2] = {{430}, {429}};

/* as script.h declares it; this TU does not include that header */
extern int scpIsTorchLightOn(int a0);
/* as script.h declares it; this TU does not include that header */
extern void scpTorchLightOn(int a0);
extern int D_0063AA08;
/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);
/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern int D_00639EA4;
extern int D_00639EA8;
/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(int a0, int a1);
extern int sekizo_4r;

/* .sbss, owned by st04r.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the pad actuator handle openGate
   holds, the demo's own end flag, the gate animation and voice clip openGate
   plays, and the flag the stair subthread raises once it is past its setup. */
static int padAct;

static int demoEnd;

static int gateAnim;

static int gateAdpcm;

static int subStarted;

extern int D_00639EAC;
extern int D_00639ED4;
extern char *sekizo5c;
extern unsigned char st05d_hasi;
extern int crest1_4r;
extern int D_0028F8F4[];
/* as script.h declares it; this TU does not include that header */
extern void scpSleepEnemyAll(void);
/* as script.h declares it; this TU does not include that header */
extern void scpWakeupEnemyAll(void);
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern int scpAdpcmFadeCloseFunc(int *a0, int a1);
/* as script.h declares it; this TU does not include that header */
extern int scpAdpcmPlayRequestNum(void);
/* as script.h declares it; this TU does not include that header */
extern void scpFadeOut(float t, int a1, int a2, int a3);
/* as script.h declares it; this TU does not include that header */
extern void scpFadeIn(float f);
/* as script.h declares it; this TU does not include that header */
extern int scpFadeChk(void);
/* as script.h declares it; this TU does not include that header */
extern void scpPlayStart(int a0);
/* as script.h declares it; this TU does not include that header */
extern void scpPlayEnd(int a0);
/* kept local: this TU's uses of scpPlayMotReq do not fit the prototype in script.h */
extern void scpPlayMotReq(int a0, int mot);
/* kept local: this TU's uses of scpIsBombExplode do not fit the prototype in script.h */
extern int scpIsBombExplode(int a0);
/* kept local: this TU's uses of scpTriggerBall do not fit the prototype in script.h */
extern int scpTriggerBall(int a0, int gobj, float r);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
extern int D_0028F4C0[];
/* as script.h declares it; this TU does not include that header */
extern void preload(int a0);
/* kept local: this TU's uses of scpPlayMotDir do not fit the prototype in script.h */
extern void scpPlayMotDir(int a0, void *dir);
/* kept local: this TU's uses of scpPlayPosSet do not fit the prototype in script.h */
extern void scpPlayPosSet(int a0, float x, float y, float z);
/* kept local: this TU's uses of scpPlayWaitMotEnd do not fit the prototype in script.h */
extern void scpPlayWaitMotEnd(int a0);
extern int crest3_4r;

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads, which is what makes gcc
   emit the ld/sd pair the ROM has. */

/* The look-at point both characters face in the crest cutscene. */
static const ConstVec crestFacePos = {{0.0f, 0.0f, -5000.0f, 1.0f}};

/* as script.h declares it; this TU does not include that header */
extern void scpWakeupItemWithBoundary(float a0, float a1, float a2, float a3);
/* as script.h declares it; this TU does not include that header */
extern void scpKillEnemyAll(void);
/* as script.h declares it; this TU does not include that header */
extern void scpMaskGeneratorAll(void);
/* as script.h declares it; this TU does not include that header */
extern void scpSekizouCheckPoint(void);
extern int stair5d;
extern int st04r_yure;
extern unsigned char st04r_yure_vol;

/* the shared pad-state array (op.c's PadState, GsBase.c's GsbPad): 0x58 per
   pad, trg at 0x4. */

extern Pad D_0028F8F0[];
/* as script.h declares it; this TU does not include that header */
extern void scpSleepEnemyOne(int a0);
/* as script.h declares it; this TU does not include that header */
extern void scpWakeupEnemyOne(int a0);
extern int solar4r;

void actSt05eEnd(void)
{
    if (solar4r != 0) {
        if (gflagChk(234) == 0) {
            scpAdpcmCloseFunc(&solar4r);
        }
    }
}

void actSt05cInit(void)
{
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

    if (gflagChk(254) == 0) {
        SetWayGroupActive(1, 0);
    } else {
        SetWayGroupActive(1, 1);
    }

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
        scpSearchGobj(1379)->f16C = 0;
    }
}

void actSt05dInit(void)
{
    if (gflagChk(259) == 0) {
        stage_SetAnimation(328, 0, 0);

        SetWayGroupActive(3, 0);
    } else {
        stage_SetAnimation(328, 0, -1);

        SetWayGroupActive(3, 1);
    }

    if (gflagChk(260) == 0) {
        stage_SetAnimation(329, 0, 0);

        SetWayGroupActive(4, 0);
    } else {
        stage_SetAnimation(329, 0, -1);

        SetWayGroupActive(4, 1);
    }

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
        stage_SetAnimation(229, 0, 0xC8);
    } else {
        stage_SetAnimation(229, 0, 0);
    }
}

void actSt05eInit(void)
{
    if (gflagChk(231) == 0) {
        SetWayGroupActive(5, 0);
    } else {
        SetWayGroupActive(5, 1);
    }

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
}

void actSt04rCrest02(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(244) == 0) {
        if (D_00639ED4 == 0x1C) {
            stage_SetAnimation(311, 0, 0);
        } else {
            stage_SetAnimation(312, 0, 0);
        }

        crest02_mes[0].func = actSt04rCrest2Main;
        self->mail = crest02_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        if (D_00639ED4 == 0x1C) {
            stage_SetAnimation(311, 0, -1);
        } else {
            stage_SetAnimation(312, 0, -1);
        }

        D_0063AA08 = 0;
    }
}

void openGateSub(volatile int a0)
{
    stage_SetAnimation(gateAnim, 1, 0);

    while (stage_CheckAnimationFrame(gateAnim, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    padAct = iosPadActRequest(D_00639EAC, 0xA);
    st05d_hasi = 0x80;
    iosPadActVolumeSet(padAct, 0x80);

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

void openGate(int a0)
{
    int th;

    lt_switch_layout(55);

    D_0063AA08 = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(gateAdpcm, &crest1_4r, 0, 1, 1);

    while (crest1_4r == 0) {
        _ACTWait(1);
    }

    th = actCreateSubThread(openGateSub, 21);

    demoEnd = 0;
    padAct = -1;

    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri((int *)(th + 0x24), 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&crest1_4r, 0x100);

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

    lt_switch_layout(54);

    D_0063AA08 = 0;
}

void actSt04rCrest2Main(volatile int a0)
{
    int anim;

    if (D_00639ED4 == 0x1C) {
        anim = 0x137;
        while (scpIsTorchLightOn(1408) == 0 || scpIsTorchLightOn(1409) == 0 || gflagChk(251) == 0) {
            _ACTWait(1);
        }

        gateAnim = anim;
    }

    if (D_00639ED4 == 0x1D) {
        anim = 0x138;

        while (scpIsTorchLightOn(1487) == 0 || scpIsTorchLightOn(1488) == 0 || gflagChk(251) == 0) {
            _ACTWait(1);
        }

        gateAnim = anim;
    }

    gateAdpcm = 0x19;
    openGate(a0);

    if (D_00639ED4 == 0x1C) {
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

void actSt04rCrest3Main(volatile int a0)
{
    while (scpIsTorchLightOn(1489) == 0 || scpIsTorchLightOn(1490) == 0 || gflagChk(252) == 0) {
        _ACTWait(1);
    }

    scpSleepEnemyOne(3757);

    gflagOn(170);

    fightSoundProcessRequestPause();

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    gateAnim = 0x139;
    gateAdpcm = 0x18;
    openGate(a0);

    scpWakeupEnemyOne(3757);

    fightSoundProcessRequestStart();
    _ACTWait(1);

    gflagOn(245);
    gflagOff(246);
    gflagOff(247);
    gflagOff(248);
    gflagOn(249);
    gflagOff(233);
}

void actSt04rSolarBeam(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    solar4r = 0;

    if (gflagChk(234) == 0) {
        scpAdpcmPlayRequestFunc(28, &solar4r, 0, 1, 0);

        if (gflagChk(243) != 0 && gflagChk(244) != 0 && gflagChk(245) != 0 && gflagChk(232) != 0) {
            if (D_00639EA4 != 0) {
                scpPlayMot(D_00639EA4, 0);
            }

            lt_switch_layout(55);

            D_0063AA08 = 1;
            gflagOn(389);

            scpFadeOut(255.0f, 0, 0, 0);

            while (solar4r == 0) {
                _ACTWait(1);
            }

            scpFadeIn(6.0f);
        }

        solar_beam_mes[0].func = actSt04rSolarBeamChk;
        self->mail = solar_beam_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        D_0063AA08 = 0;
    }
}

void actSt04rSolarBeamChk(volatile int a0)
{
    while (gflagChk(243) == 0 || gflagChk(244) == 0 || gflagChk(245) == 0 || gflagChk(232) == 0) {
        _ACTWait(1);
    }

    gflagOn(234);

    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    while (solar4r == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(solar4r + 0x2C));

    preload(0xF);

    stage_SetAnimation(346, 1, 0);
    stage_SetAnimation(294, 1, 0);

    while (stage_CheckAnimationFinish(294) == 0) {
        if ((D_0028F8F0[0].trg & 0x800) != 0 && scpAdpcmPlayRequestNum() == 0) {
            scpFadeOut(16.0f, 0, 0, 0);

            scpAdpcmFadeCloseFunc(&solar4r, 0x100);

            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }

            stage_SetAnimation(346, 0, -1);
            stage_SetAnimation(294, 0, -1);

            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }

    D_0063AA08 = 0;

    scpWakeupEnemyAll();

    RequestStageChange(0xF, D_00639EA4, 0, 2.0f, 8.0f);
}

void actSt04rStairSub(volatile int a0)
{
    long long buf[2];
    float dir[4];

    _ACTWait(60);

    while (crest3_4r == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(crest3_4r + 0x2C));

    stage_SetAnimation(350, 1, 0);

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);

    scpPlayMot(D_00639EA4, 0);
    scpPlayMot(D_00639EA8, 532);

    scpPlayPosSet(D_00639EA4, -55.0f, 28.0f, -3881.0f);
    scpPlayPosSet(D_00639EA8, 58.0f, 28.0f, -3891.0f);

    buf[0] = crestFacePos.d[0];
    buf[1] = crestFacePos.d[1];
    sceVu0SubVector(dir, buf, test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    buf[0] = crestFacePos.d[0];
    buf[1] = crestFacePos.d[1];
    sceVu0SubVector(dir, buf, test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, dir);

    subStarted = 1;

    while (stage_CheckAnimationFinish(350) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x11);

    stage_SetAnimation(330, 1, 0);

    while (stage_CheckAnimationFrame(330, 140, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    padAct = iosPadActRequest(D_00639EAC, 9);
    st05d_hasi = 0x80;
    iosPadActVolumeSet(padAct, 0x80);

    while (stage_CheckAnimationFinish(330) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt04rStairChk(volatile int a0)
{
    int th;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0xB000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0xB000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);

    D_0063AA08 = 1;
    gflagOn(253);

    FinishHint(24);

    scpSleepEnemyAll();

    scpSearchGobj(1523)->f16C = 0;

    stage_SetAnimation(351, -1, -2);

    scpAdpcmPlayRequestFunc(61, &crest3_4r, 1, 1, 0);

    th = actCreateSubThread(actSt04rStairSub, 21);

    demoEnd = 0;
    padAct = -1;
    subStarted = 0;

    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (crest3_4r == 0) {
            _ACTWait(1);
        }

        scpAdpcmFadeCloseFunc(&crest3_4r, 0x200);

        while (subStarted == 0) {
            _ACTWait(1);
        }

        iosThreadSetPri((int *)(th + 0x24), 34);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(350, 0, -1);
        stage_SetAnimation(330, 0, -1);
        _ACTWait(1);

        scpPlayMot(D_00639EA4, 0);
        scpPlayMot(D_00639EA8, 532);

        scpPlayPosSet(D_00639EA4, -55.0f, 234.0f, -3881.0f);
        scpPlayPosSet(D_00639EA8, 58.0f, 234.0f, -3891.0f);

        _ACTWait(1);

        iosOmSendMail(D_00639EA8, 0x3E, D_00639EA4);

        scpFadeIn(3.0f);
    } else {
        iosThreadSetPri((int *)(th + 0x24), 34);
    }

    if (padAct >= 0) {
        iosPadActStop(padAct);
    }

    scpPlayMot(D_00639EA4, 0);
    scpPlayMot(D_00639EA8, 532);

    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);

    scpWakeupEnemyAll();

    D_0063AA08 = 0;

    lt_switch_layout(54);
}

void actSt04rSekizoChk(volatile int a0)
{
    float dir[4];

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0 ||
           scpTriggerBall(a0, D_00639EA8, 200.0f) == 0 ||
           scpTriggerFloorAttr(D_00639EA4, 0x8000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x8000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);

    D_0063AA08 = 1;
    scpKillEnemyAll();

    scpMaskGeneratorAll();

    scpAdpcmPlayRequestFunc(18, &stair5d, 1, 1, 1);

    while (stair5d == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(1, 1);

    stage_SetAnimation(331, 1, 0);

    st04r_yure = iosPadActRequest(D_00639EAC, 9);
    st04r_yure_vol = 0x80;
    iosPadActVolumeSet(st04r_yure, 0x80);

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);

    scpPlayMot(D_00639EA4, 0);
    scpPlayMot(D_00639EA8, 532);

    scpPlayPosSet(D_00639EA8, 0.0f, -1300.0f, -1700.0f);
    scpPlayPosSet(D_00639EA4, 20.0f, -1300.0f, -1700.0f);
    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(a0), test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, dir);

    D_0063AA08 = 1;

    sceVu0SubVector(dir, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    scpSekizouCheckPoint();

    scpPlayMot(D_00639EA8, 645);
    scpPlayWaitMotEnd(D_00639EA8);

    gflagOn(254);

    while (stage_CheckAnimationFrame(331, 151, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(st04r_yure);

    while (stage_CheckAnimationFinish(331) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(D_00639EA8, 532);
    scpPlayEnd(D_00639EA8);

    scpPlayMot(D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);
    _ACTWait(1);

    iosOmSendMail(D_00639EA8, 0x3F, D_00639EA4);

    lt_switch_layout(54);

    D_0063AA08 = 0;
}

void actSt04rRope1Chk(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(261) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1459))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(324, 1, 0);

            while (stage_CheckAnimationFinish(324) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1459)->f16C = 0;

            gflagOn(261);

            stage_SetAnimation(320, 1, 0);

            while (stage_CheckAnimationFinish(320) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        }
    }
}

void actSt04rRope2Chk(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(262) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1460))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(325, 1, 0);

            while (stage_CheckAnimationFinish(325) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1460)->f16C = 0;

            gflagOn(262);

            stage_SetAnimation(321, 1, 0);

            while (stage_CheckAnimationFinish(321) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        }
    }
}

void actSt04rBrgCommon(volatile int a0)
{
    int th;

    lt_switch_layout(55);

    D_0063AA08 = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(86, (int *)&sekizo5c, 1, 1, 0);

    th = actCreateSubThread(actSt04rBrg1Sub, 21);

    demoEnd = 0;

    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri((int *)(th + 0x24), 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc((int *)&sekizo5c, 0x100);

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

    D_0063AA08 = 0;

    lt_switch_layout(54);
}

void actSt04rRope3Chk(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(263) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1461))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(326, 1, 0);

            while (stage_CheckAnimationFinish(326) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1461)->f16C = 0;

            gflagOn(263);

            stage_SetAnimation(322, 1, 0);

            while (stage_CheckAnimationFinish(322) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        }
    }
}

void actSt04rRope4Chk(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(264) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(1462))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(327, 1, 0);

            while (stage_CheckAnimationFinish(327) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(1462)->f16C = 0;

            gflagOn(264);

            stage_SetAnimation(323, 1, 0);

            while (stage_CheckAnimationFinish(323) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        }
    }
}

void actSt04rMonyou01Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x1000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x1000000) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;

    gflagOn(274);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        if (GetCharHeldItem(D_00639EA4) != 1) {
            scpPlayStart(D_00639EA4);
            scpPlayStart(D_00639EA8);
        }

        scpPlayMotReq(D_00639EA4, 1);
        scpPlayMotReq(D_00639EA8, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

    stage_SetAnimation(337, 1, 0);

    soundSeDefPlay(1332, 0, 0, 1);

    while (stage_CheckAnimationFrame(337, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(D_00639EA8, 0x3F, D_00639EA4);
    }

    D_0063AA08 = 0;
}

void actSt04rMonyou02Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x2000000) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;

    gflagOn(275);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        if (GetCharHeldItem(D_00639EA4) != 1) {
            scpPlayStart(D_00639EA4);
            scpPlayStart(D_00639EA8);
        }

        scpPlayMotReq(D_00639EA4, 1);
        scpPlayMotReq(D_00639EA8, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

    stage_SetAnimation(338, 1, 0);

    soundSeDefPlay(1332, 0, 0, 1);

    while (stage_CheckAnimationFrame(338, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(D_00639EA8, 0x3F, D_00639EA4);
    }

    D_0063AA08 = 0;
}

void actSt04rMonyou03Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x3000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x3000000) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;

    gflagOn(276);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        if (GetCharHeldItem(D_00639EA4) != 1) {
            scpPlayStart(D_00639EA4);
            scpPlayStart(D_00639EA8);
        }

        scpPlayMotReq(D_00639EA4, 1);
        scpPlayMotReq(D_00639EA8, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

    stage_SetAnimation(339, 1, 0);

    soundSeDefPlay(1332, 0, 0, 1);

    while (stage_CheckAnimationFrame(339, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(D_00639EA8, 0x3F, D_00639EA4);
    }

    D_0063AA08 = 0;
}

void actSt04rMonyou04Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x4000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x4000000) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;

    gflagOn(277);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        if (GetCharHeldItem(D_00639EA4) != 1) {
            scpPlayStart(D_00639EA4);
            scpPlayStart(D_00639EA8);
        }

        scpPlayMotReq(D_00639EA4, 1);
        scpPlayMotReq(D_00639EA8, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

    stage_SetAnimation(340, 1, 0);

    soundSeDefPlay(1332, 0, 0, 1);

    while (stage_CheckAnimationFrame(340, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(D_00639EA8, 0x3F, D_00639EA4);
    }

    D_0063AA08 = 0;
}

void actSt04rMonyou05Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x5000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x5000000) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;

    gflagOn(278);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        if (GetCharHeldItem(D_00639EA4) != 1) {
            scpPlayStart(D_00639EA4);
            scpPlayStart(D_00639EA8);
        }

        scpPlayMotReq(D_00639EA4, 1);
        scpPlayMotReq(D_00639EA8, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

    stage_SetAnimation(341, 1, 0);

    soundSeDefPlay(1332, 0, 0, 1);

    while (stage_CheckAnimationFrame(341, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(D_00639EA8, 0x3F, D_00639EA4);
    }

    D_0063AA08 = 0;
}

void actSt04rMonyou06Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x6000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x6000000) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;

    gflagOn(279);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        if (GetCharHeldItem(D_00639EA4) != 1) {
            scpPlayStart(D_00639EA4);
            scpPlayStart(D_00639EA8);
        }

        scpPlayMotReq(D_00639EA4, 1);
        scpPlayMotReq(D_00639EA8, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

    stage_SetAnimation(342, 1, 0);

    soundSeDefPlay(1332, 0, 0, 1);

    while (stage_CheckAnimationFrame(342, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(D_00639EA8, 0x3F, D_00639EA4);
    }

    D_0063AA08 = 0;
}

void actSt04rMonyou07Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x7000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x7000000) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;

    gflagOn(280);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        if (GetCharHeldItem(D_00639EA4) != 1) {
            scpPlayStart(D_00639EA4);
            scpPlayStart(D_00639EA8);
        }

        scpPlayMotReq(D_00639EA4, 1);
        scpPlayMotReq(D_00639EA8, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

    stage_SetAnimation(343, 1, 0);

    soundSeDefPlay(1332, 0, 0, 1);

    while (stage_CheckAnimationFrame(343, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(D_00639EA8, 0x3F, D_00639EA4);
    }

    D_0063AA08 = 0;
}

void actSt04rBarricadeChk(volatile int a0)
{
    int n;

    while ((n = scpIsBombExplode(19)) == 0 || scpTriggerBall(a0, n, 350.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    gflagOn(265);
    _ACTWait(5);

    stage_SetAnimation(344, 1, 0);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(344) == 0) {
        if ((D_0028F8F0[0].trg & 0x800) != 0 && scpAdpcmPlayRequestNum() == 0) {
            scpFadeOut(16.0f, 0, 0, 0);

            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }

            stage_SetAnimation(344, 0, -1);

            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 3);

    scpWakeupEnemyAll();

    D_0063AA08 = 0;

    lt_switch_layout(54);
}

void actSt04rGondolaChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttr(D_00639EA4, 0xA000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);

    D_0063AA08 = 1;
    scpSleepEnemyAll();

    _ACTWait(15);

    if (gflagChk(282) != 0) {
        stage_SetAnimation(229, 1, 0xC8);

        scpWakeupItemWithBoundary(-675.0f, -150.0f, -1600.0f, 200.0f);

        while (stage_CheckAnimationFrame(229, 220, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(1321, 0, 0, 1);

        while (stage_CheckAnimationFrame(229, 240, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(1322, 0, 0, 1);

        while (stage_CheckAnimationFrame(229, 250, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(1319, 0, 0, 1);

        while (stage_CheckAnimationFrame(229, 415, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(1320, 0, 0, 1);

        while (stage_CheckAnimationFinish(229) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        gflagOff(282);
    } else {
        stage_SetAnimation(229, 1, 0);

        scpWakeupItemWithBoundary(-675.0f, -1200.0f, -1600.0f, 200.0f);

        SetGirlDangerGObj(D_00639EA4);

        soundSeDefPlay(1319, 0, 0, 1);

        while (stage_CheckAnimationFrame(229, 145, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(1320, 0, 0, 1);
        soundSeDefPlay(1321, 0, 0, 1);

        while (stage_CheckAnimationFrame(229, 170, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(1322, 0, 0, 1);

        while (stage_CheckAnimationFrame(229, 200, 1) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        ClearGirlDangerGObj();

        gflagOn(282);
    }

    if (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0xA000000) == 0) {
        gflagOn(286);
    } else {
        gflagOff(286);
    }

    D_0063AA08 = 0;

    lt_switch_layout(54);

    scpWakeupEnemyAll();

    gondola_chk_mes[0].func = actSt04rGondolaCharaChk;
    sub->mail = gondola_chk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt04rSolarStageChange(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(234) == 0) {
        solar_stage_change_mes[0].func = actSt04rSolarStageChangeChk;
        self->mail = solar_stage_change_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt04rCrest01(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(243) == 0) {
        stage_SetAnimation(309, 0, 0);

        crest01_mes[0].func = actSt04rCrestMain;
        self->mail = crest01_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(309, 0, -1);
        D_0063AA08 = 0;
    }
}

void actSt04rCrest03(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(245) == 0) {
        stage_SetAnimation(313, 0, 0);

        crest03_mes[0].func = actSt04rCrest3Main;
        self->mail = crest03_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(313, 0, -1);
        D_0063AA08 = 0;
    }
}

void actSt04rC1Ball(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(250) == 0) {
        scpSearchGobj(1404)->f16C = 0;
        scpSearchGobj(1405)->f16C = 0;

        stage_SetAnimation(317, 0, 0);

        c1_ball_mes[0].func = actSt04rC1BallMain;
        self->mail = c1_ball_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(317, 0, -1);
    }
}

void actSt04rC2Ball(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(251) == 0) {
        scpSearchGobj(1487)->f16C = 0;
        scpSearchGobj(1488)->f16C = 0;

        stage_SetAnimation(318, 0, 0);

        c2_ball_mes[0].func = actSt04rC2BallMain;
        self->mail = c2_ball_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(318, 0, -1);
    }
}

void actSt04rC3Ball(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(252) == 0) {
        scpSearchGobj(1489)->f16C = 0;
        scpSearchGobj(1490)->f16C = 0;

        stage_SetAnimation(319, 0, 0);

        c3_ball_mes[0].func = actSt04rC3BallMain;
        self->mail = c3_ball_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(319, 0, -1);
    }
}

void actSt04rStair(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(253) == 0) {
        if (D_00639EA8 != 0) {
            stair_mes[0].func = actSt04rStairChk;
            self->mail = stair_mes;
            ACTSendMailCorrect(a0, 430);
            _ACTWait(0);
        }
    } else {
        scpSearchGobj(1523)->f16C = 0;

        stage_SetAnimation(351, -1, -2);
    }
}

void actSt04rBrg1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(259) == 0) {
        brg1_mes[0].func = actSt04rBrg1Chk;
        self->mail = brg1_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt04rBrg2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(260) == 0) {
        brg2_mes[0].func = actSt04rBrg2Chk;
        self->mail = brg2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt04rBrg1Way(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(259) == 0) {
        brg1_way_mes[0].func = actSt04rBrg1WayChk;
        self->mail = brg1_way_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt04rBrg2Way(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(260) == 0) {
        brg2_way_mes[0].func = actSt04rBrg2WayChk;
        self->mail = brg2_way_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt04rRope1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(261) == 0) {
        stage_SetAnimation(320, 0, 0);

        rope1_mes[0].func = actSt04rRope1Chk;
        self->mail = rope1_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(320, 0, -1);

        scpSearchGobj(1459)->f16C = 0;
    }
}

void actSt04rRope2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(262) == 0) {
        stage_SetAnimation(321, 0, 0);

        rope2_mes[0].func = actSt04rRope2Chk;
        self->mail = rope2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(321, 0, -1);

        scpSearchGobj(1460)->f16C = 0;
    }
}

void actSt04rRope3(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(263) == 0) {
        stage_SetAnimation(322, 0, 0);

        rope3_mes[0].func = actSt04rRope3Chk;
        self->mail = rope3_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(322, 0, -1);

        scpSearchGobj(1461)->f16C = 0;
    }
}

void actSt04rRope4(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(264) == 0) {
        stage_SetAnimation(323, 0, 0);

        rope4_mes[0].func = actSt04rRope4Chk;
        self->mail = rope4_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(323, 0, -1);

        scpSearchGobj(1462)->f16C = 0;
    }
}

void actSt04rSekizo(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(254) == 0) {
        stage_SetAnimation(331, 0, 0);

        sekizo_mes[0].func = actSt04rSekizoChk;
        self->mail = sekizo_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(331, 0, -1);
    }
}

void actSt04rBarricade(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(265) == 0) {
        stage_SetAnimation(344, 0, 0);

        barricade_mes[0].func = actSt04rBarricadeChk;
        self->mail = barricade_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(344, 0, -1);
    }
}

void actSt04rGondola(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(282) != 0) {
        stage_SetAnimation(229, 0, 0xC8);

        gondola_mes[0].func = actSt04rGondolaChk;
        self->mail = gondola_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(229, 0, 0);

        gondola2_mes[0].func = actSt04rGondolaChk;
        self->mail = gondola2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt04rCrest01XL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(243) == 0) {
        stage_SetAnimation(314, 0, 0);
    } else {
        stage_SetAnimation(314, 0, -1);
    }
}

void actSt04rCrest02XL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(244) == 0) {
        stage_SetAnimation(315, 0, 0);
    } else {
        stage_SetAnimation(315, 0, -1);
    }
}

void actSt04rCrest03XL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(245) == 0) {
        stage_SetAnimation(316, 0, 0);
    } else {
        stage_SetAnimation(316, 0, -1);
    }
}

void actSt04rC2BallXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(251) == 0) {
        stage_SetAnimation(318, 0, 0);

        scpSearchGobj(1408)->f16C = 0;
        scpSearchGobj(1409)->f16C = 0;
    } else {
        stage_SetAnimation(318, 0, -1);
    }
}

void actSt04rC3BallXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(252) == 0) {
        stage_SetAnimation(319, 0, 0);

        scpSearchGobj(1562)->f16C = 0;
        scpSearchGobj(1563)->f16C = 0;
    } else {
        stage_SetAnimation(319, 0, -1);
    }
}

void actSt04rTorch1_1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(266) == 0) {
        torch1_1_mes[0].func = actSt04rTorch1_1Chk;
        self->mail = torch1_1_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1404);
        stage_SetAnimation(210, 0, -1);
    }
}

void actSt04rTorch1_2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(267) == 0) {
        torch1_2_mes[0].func = actSt04rTorch1_2Chk;
        self->mail = torch1_2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1405);
        stage_SetAnimation(211, 0, -1);
    }
}

void actSt04rTorch2_1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(268) != 0 || gflagChk(270) != 0) {
        scpTorchLightOn(1487);
    } else {
        torch2_1_mes[0].func = actSt04rTorch2_1Chk;
        self->mail = torch2_1_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt04rTorch2_2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(269) != 0 || gflagChk(271) != 0) {
        scpTorchLightOn(1488);
    } else {
        torch2_2_mes[0].func = actSt04rTorch2_2Chk;
        self->mail = torch2_2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt04rTorch3_1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(272) == 0) {
        torch3_1_mes[0].func = actSt04rTorch3_1Chk;
        self->mail = torch3_1_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1489);
    }
}

void actSt04rTorch3_2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(273) == 0) {
        torch3_2_mes[0].func = actSt04rTorch3_2Chk;
        self->mail = torch3_2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        scpTorchLightOn(1490);
    }
}

void actSt04rTorch2_1XL(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(268) != 0 || gflagChk(270) != 0) {
        scpTorchLightOn(1408);
        stage_SetAnimation(212, 0, -1);
    } else {
        torch2_1xl_mes[0].func = actSt04rTorch2_1XLChk;
        self->mail = torch2_1xl_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt04rTorch2_2XL(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(269) != 0 || gflagChk(271) != 0) {
        scpTorchLightOn(1409);
        stage_SetAnimation(213, 0, -1);
    } else {
        torch2_2xl_mes[0].func = actSt04rTorch2_2XLChk;
        self->mail = torch2_2xl_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt04rTorch3_1XL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(272) != 0) {
        scpTorchLightOn(1562);
    }
}

void actSt04rTorch3_2XL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(273) != 0) {
        scpTorchLightOn(1563);
    }
}

void actSt04rMonyou01(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(274) == 0) {
        stage_SetAnimation(337, 0, 0);

        monyou01_mes[0].func = actSt04rMonyou01Chk;
        self->mail = monyou01_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(337, 0, -1);
    }
}

void actSt04rMonyou02(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(275) == 0) {
        stage_SetAnimation(338, 0, 0);

        monyou02_mes[0].func = actSt04rMonyou02Chk;
        self->mail = monyou02_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(338, 0, -1);
    }
}

void actSt04rMonyou03(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(276) == 0) {
        stage_SetAnimation(339, 0, 0);

        monyou03_mes[0].func = actSt04rMonyou03Chk;
        self->mail = monyou03_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(339, 0, -1);
    }
}

void actSt04rMonyou04(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(277) == 0) {
        stage_SetAnimation(340, 0, 0);

        monyou04_mes[0].func = actSt04rMonyou04Chk;
        self->mail = monyou04_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(340, 0, -1);
    }
}

void actSt04rMonyou05(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(278) == 0) {
        stage_SetAnimation(341, 0, 0);

        monyou05_mes[0].func = actSt04rMonyou05Chk;
        self->mail = monyou05_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(341, 0, -1);
    }
}

void actSt04rMonyou06(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(279) == 0) {
        stage_SetAnimation(342, 0, 0);

        monyou06_mes[0].func = actSt04rMonyou06Chk;
        self->mail = monyou06_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(342, 0, -1);
    }
}

void actSt04rMonyou07(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(280) == 0) {
        stage_SetAnimation(343, 0, 0);

        monyou07_mes[0].func = actSt04rMonyou07Chk;
        self->mail = monyou07_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(343, 0, -1);
    }
}

void actSt05cDoorInit(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(165) != 0 && gflagChk(234) == 0) {
        stage_SetAnimation(347, 0, -1);
    }

    if (gflagChk(165) == 0 || gflagChk(234) != 0) {
        stage_SetAnimation(347, 0, 0);
    }
}

void actSt04rC1BallMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = c1_ball_main_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt04rC1BallSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    c1_ball_switch_mes[0].func = actSt04rC1BallTurn;
    sub->mail = c1_ball_switch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt04rC1BallTurn(volatile int a0)
{
    turnBall(a0, 0xFA, 0x13D, 0x57C, 0x57D);
}

void actSt04rC2BallMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = c2_ball_main_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt04rC2BallSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    c2_ball_switch_mes[0].func = actSt04rC2BallTurn;
    sub->mail = c2_ball_switch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt04rC2BallTurn(volatile int a0)
{
    turnBall(a0, 0xFB, 0x13E, 0x5CF, 0x5D0);
}

void actSt04rC3BallMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = c3_ball_main_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt04rC3BallSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    c3_ball_switch_mes[0].func = actSt04rC3BallTurn;
    sub->mail = c3_ball_switch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt04rC3BallTurn(volatile int a0)
{
    turnBall(a0, 0xFC, 0x13F, 0x5D1, 0x5D2);
}

void actSt04rCrestMain(volatile int a0)
{
    while (scpIsTorchLightOn(1404) == 0 || scpIsTorchLightOn(1405) == 0 || gflagChk(250) == 0) {
        _ACTWait(1);
    }

    gateAnim = 0x135;
    gateAdpcm = 0x1B;
    openGate(a0);
    _ACTWait(1);

    gflagOn(243);
    gflagOn(246);
    gflagOff(247);
    gflagOff(248);
    gflagOff(249);
    gflagOff(233);
}

void actSt04rSolarStageChangeChk(volatile int a0)
{
    while (gflagChk(243) == 0 || gflagChk(244) == 0 || gflagChk(245) == 0 || gflagChk(232) == 0) {
        _ACTWait(1);
    }

    RequestStageChange(8, D_00639EA4, 0, 2.0f, 8.0f);
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

void actSt04rBrg1Chk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (gflagChk(261) == 0 || gflagChk(262) == 0) {
        _ACTWait(1);
    }

    gflagOn(259);

    sekizo_4r = 0x148;

    brg1_chk_mes[0].func = actSt04rBrgCommon;
    sub->mail = brg1_chk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt04rBrg1Sub(volatile int a0)
{
    _ACTWait(60);

    while (sekizo5c == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(sekizo5c + 0x2C));

    stage_SetAnimation(sekizo_4r, 1, 0);

    while (stage_CheckAnimationFrame(sekizo_4r, 75, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_CheckAnimationFinish(sekizo_4r) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
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

void actSt04rBrg2Chk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (gflagChk(263) == 0 || gflagChk(264) == 0) {
        _ACTWait(1);
    }

    gflagOn(260);

    sekizo_4r = 0x149;

    brg2_chk_mes[0].func = actSt04rBrgCommon;
    sub->mail = brg2_chk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt04rBrg1WayChk(volatile int a0)
{
    while (gflagChk(259) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(3, 1);
}

void actSt04rBrg2WayChk(volatile int a0)
{
    while (gflagChk(259) == 0 || gflagChk(260) == 0) {
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

void actSt04rGondolaCharaChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttr(D_00639EA4, 0xA000000) != 0 &&
           (gflagChk(286) == 0 || scpTriggerFloorAttr(D_00639EA8, 0xA000000) == 0)) {
        _ACTWait(1);
    }

    gondola_chara_chk_mes[0].func = actSt04rGondolaChk;
    sub->mail = gondola_chara_chk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt04rTorch1_1Chk(volatile int a0)
{
    while (scpIsTorchLightOn(1404) == 0) {
        _ACTWait(1);
    }

    gflagOn(266);
    stage_SetAnimation(210, 1, 0);
}

void actSt04rTorch1_2Chk(volatile int a0)
{
    while (scpIsTorchLightOn(1405) == 0) {
        _ACTWait(1);
    }

    gflagOn(267);
    stage_SetAnimation(211, 1, 0);
}

void actSt04rTorch2_1Chk(volatile int a0)
{
    while (scpIsTorchLightOn(1487) == 0) {
        _ACTWait(1);
    }

    gflagOn(268);
}

void actSt04rTorch2_2Chk(volatile int a0)
{
    while (scpIsTorchLightOn(1488) == 0) {
        _ACTWait(1);
    }

    gflagOn(269);
}

void actSt04rTorch3_1Chk(volatile int a0)
{
    while (scpIsTorchLightOn(1489) == 0) {
        _ACTWait(1);
    }

    gflagOn(272);
}

void actSt04rTorch3_2Chk(volatile int a0)
{
    while (scpIsTorchLightOn(1490) == 0) {
        _ACTWait(1);
    }

    gflagOn(273);
}

void actSt04rTorch2_1XLChk(volatile int a0)
{
    while (scpIsTorchLightOn(1408) == 0) {
        _ACTWait(1);
    }

    gflagOn(270);
    stage_SetAnimation(212, 1, 0);
}

void actSt04rTorch2_2XLChk(volatile int a0)
{
    while (scpIsTorchLightOn(1409) == 0) {
        _ACTWait(1);
    }

    gflagOn(271);
    stage_SetAnimation(213, 1, 0);
}
