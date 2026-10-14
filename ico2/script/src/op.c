#include "op.h"
#include "StageManager.h"
#include "debug.h"
#include "layout_texture.h"
#include "commonact.h"
#include "jimaku.h"
#include "camera-root.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "act.h"
#include "e3.h"
#include "typedef.h"
#include "kanbanBoot.h"
#include "layout_action.h"
#include "thread.h"
#include "gobj_process.h"
#include "main.h"
#include "script.h"
#include "include_asm.h"

/* .sbss: titleSubEnd and demoSubEnd are the flags a title or demo sub-thread
   raises when it is done and its parent waits on, titleSubAdpcm and demoAdpcm
   the stream handles scpAdpcmPlayRequestFunc fills. */
static int titleSubEnd; /* derived name */

static struct SqEntry *titleSubAdpcm; /* derived name */

static int demoSubEnd; /* derived name */

static struct SqEntry *demoAdpcm; /* derived name */

/* .sdata: the opening demo's step and the step it returns to, ahead of the
   demo's "mode" traces; the globals follow the demo below. */
static int opDemoMode = 0; /* derived name */

static int opDemoNextMode = 0; /* derived name */

void actTitleCamera2(GObj *volatile self)
{
    GObj *x = self;

    enable_game_pause = 1;

    opTitleLogoMode = 0;
    actInitialize(self);
    _ACTWait(1);

    while (1) {
        switch (opTitleLogoMode) {
        case 1:
            stage_SetAnimation(0, 1, 0);
            while (stage_CheckAnimationFinish(0) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            while (opTitleLogoMode == 1) {
                _ACTWait(1);
            }
            break;

        case 2:
            stage_SetAnimation(2, 1, 0);
            while (stage_CheckAnimationFinish(2) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            while (opTitleLogoMode == 2) {
                _ACTWait(1);
            }
            break;

        case 0:
            stage_SetAnimation(2, 0, -1);
            while (opTitleLogoMode == 0) {
                _ACTWait(1);
            }
            break;

        default:
            _ACTWait(1);
            break;
        }
    }
}

void actTitleReadTimeDemo0(GObj *volatile self);
void actTitleShortCut(GObj *volatile self);

/* The timer countdown is a GNU nested function declared inline at the head
   of the body: it reads and writes the parent's `t` and is inlined at both of
   its calls.  The tail after each demo (the thread priority and the fade out)
   is written out in case 0 and again in case 1. */
INCLUDE_ASM(actOpDemo01);

/* .sdata, after actOpDemo01's traces: the second demo's and the first
   scene's stream handles, the title logo's step and the title's stream handle
   (declared in op.h). */
struct SqEntry *op2 = 0;

struct SqEntry *adpcm_conte01_sea = 0;

int opTitleLogoMode = 0;

struct SqEntry *titleAdpcm = 0;

void actTitleShortCut(GObj *volatile self)
{
    GObj *x = self;

    monitorCameraHold = 1;
    actInitialize(self);
    _ACTWait(1);

    if (boyGObj != 0) {
        scpPlayStart(boyGObj);
    }
    if (titleAdpcm == 0) {
        scpAdpcmPlayRequestFunc(56, &titleAdpcm, 0, 0, 1);
    }
    stage_SetAnimation(567, 1, 1351);

    SetHandCameraLimitInDemo(0, 0);
    SetZoomMaxValInDemo(0);

    scpSearchGobj(43)->active = 1;
    scpSearchGobj(44)->active = 1;
    scpSearchGobj(45)->active = 1;
    scpSearchGobj(48)->active = 1;
    scpSearchGobj(49)->active = 1;
    scpSearchGobj(50)->active = 1;
    scpSearchGobj(51)->active = 1;

    while (titleAdpcm != 0) {
        _ACTWait(1);
    }

    scpFadeIn(3.0f);

    while (stage_CheckAnimationFinish(567) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    titleSubEnd = 1;
    _ACTWait(0);
}

/* .data: the two demo mail pairs, each the mail the demo thread answers and
   the 429 end marker. */
static ActMail opDemo02_mes[2] = {{430}, {429}}; /* derived name */

static ActMail opDemo03_mes[2] = {{430}, {429}}; /* derived name */

inline void actSubMpegReturnPreload(GObj *volatile self)
{
    _ACTWait((int)((float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 5.0f));
    stgmgrNextStagePreLoadForceStageSet(1);
    stgmgrNextStagePreLoadForceNoCancel(1);
}

void actTitleReadTimeDemo0(GObj *volatile self)
{
    debug_StdPrintfDummy("realtime demo %d\n", frame_count);

    stage_SetAnimation(2, 0, -1);

    monitorCameraHold = 0;

    _ACTWait(1);
    lt_switch_layout(52);

    _ACTWait(1);

    scpSearchGobj(43)->active = 0;
    scpSearchGobj(44)->active = 0;
    scpSearchGobj(45)->active = 0;
    scpSearchGobj(48)->active = 0;
    scpSearchGobj(49)->active = 0;
    scpSearchGobj(50)->active = 0;
    scpSearchGobj(51)->active = 0;

    scpSearchGobj(46)->active = 1;

    scpAdpcmPlayRequestFunc(6, &titleSubAdpcm, 1, 1, 1);
    while (titleSubAdpcm == 0) {
        _ACTWait(1);
    }

    scpFadeIn(3.0f);

    ResetHandCameraLimitInDemo();
    ResetZoomMaxValInDemo();

    stage_SetAnimation(559, 1, 0);

    while (stage_ContinueAnimation(559, 560) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(59), 1051);
    scpSearchGobj(59)->active = 1;
    scpPlayMot(scpSearchGobj(60), 1058);
    scpSearchGobj(60)->active = 1;
    scpPlayMot(scpSearchGobj(61), 1065);
    scpSearchGobj(61)->active = 1;

    while (stage_ContinueAnimation(560, 561) == 0) {
        _ACTWait(1);
    }

    scpPlayStart(boyGObj);

    scpPlayMot(boyGObj, 263);

    scpPlayMot(scpSearchGobj(56), 983);
    scpSearchGobj(56)->active = 1;
    scpPlayMot(scpSearchGobj(57), 1005);
    scpSearchGobj(57)->active = 1;
    scpPlayMot(scpSearchGobj(58), 1028);
    scpSearchGobj(58)->active = 1;
    scpPlayMot(scpSearchGobj(59), 1052);
    scpPlayMot(scpSearchGobj(60), 1059);
    scpPlayMot(scpSearchGobj(61), 1066);

    while (stage_ContinueAnimation(561, 562) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 264);
    scpPlayMot(scpSearchGobj(56), 984);
    scpPlayMot(scpSearchGobj(57), 1006);
    scpPlayMot(scpSearchGobj(58), 1029);
    scpPlayMot(scpSearchGobj(59), 1053);
    scpPlayMot(scpSearchGobj(60), 1060);
    scpPlayMot(scpSearchGobj(61), 1067);

    while (stage_CheckAnimationFrame(562, 60, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(60)->active = 0;
    scpSearchGobj(57)->active = 0;

    while (stage_ContinueAnimation(562, 563) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(60)->active = 1;
    scpSearchGobj(57)->active = 1;

    scpPlayMot(boyGObj, 265);
    scpPlayMot(scpSearchGobj(56), 985);
    scpPlayMot(scpSearchGobj(57), 1007);
    scpPlayMot(scpSearchGobj(58), 1030);
    scpPlayMot(scpSearchGobj(59), 1054);
    scpPlayMot(scpSearchGobj(60), 1061);
    scpPlayMot(scpSearchGobj(61), 1068);

    while (stage_CheckAnimationFrame(563, 90, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(54)->active = 0;

    while (stage_ContinueAnimation(563, 564) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(56), 986);
    scpPlayMot(scpSearchGobj(57), 1008);
    scpPlayMot(scpSearchGobj(58), 1031);
    scpPlayMot(scpSearchGobj(59), 1055);
    scpPlayMot(scpSearchGobj(60), 1062);
    scpPlayMot(scpSearchGobj(61), 1069);

    _ACTWait(1);

    scpSearchGobj(57)->active = 0;

    while (stage_ContinueAnimation(564, 565) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 267);
    scpPlayMot(scpSearchGobj(56), 987);
    scpPlayMot(scpSearchGobj(57), 1009);
    scpPlayMot(scpSearchGobj(58), 1032);
    scpPlayMot(scpSearchGobj(59), 1056);
    scpPlayMot(scpSearchGobj(60), 1063);
    scpPlayMot(scpSearchGobj(61), 1070);

    _ACTWait(1);

    scpSearchGobj(54)->active = 1;
    scpSearchGobj(57)->active = 1;

    scpSearchGobj(43)->active = 1;
    scpSearchGobj(44)->active = 1;
    scpSearchGobj(45)->active = 1;
    scpSearchGobj(48)->active = 1;
    scpSearchGobj(49)->active = 1;
    scpSearchGobj(50)->active = 1;
    scpSearchGobj(51)->active = 1;

    scpSearchGobj(46)->active = 0;

    while (stage_ContinueAnimation(565, 567) == 0) {
        _ACTWait(1);
    }

    SetHandCameraLimitInDemo(0, 0);
    SetZoomMaxValInDemo(0);

    scpPlayMot(boyGObj, 268);
    scpPlayMot(scpSearchGobj(56), 988);
    scpPlayMot(scpSearchGobj(57), 1010);
    scpPlayMot(scpSearchGobj(58), 1033);
    scpPlayMot(scpSearchGobj(59), 1057);
    scpPlayMot(scpSearchGobj(60), 1064);
    scpPlayMot(scpSearchGobj(61), 1071);

    debug_StdPrintfDummy("finish anim %d\n", frame_count);

    debug_StdPrintfDummy("frame anim %d\n", frame_count);

    _ACTWait(900);

    _ACTWait(1000);

    opTitleLogoMode = 1;
    while (stage_CheckAnimationFrame(567, 1300, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    monitorCameraHold = 1;

    debug_StdPrintfDummy("game mode %d %d\n", frame_count, gflagChk(386));

    lt_switch_layout(9);

    if (titleAdpcm == 0) {
        scpAdpcmPlayRequestFunc(56, &titleAdpcm, 0, 0, 1);
    }
    titleSubEnd = 1;

    _ACTWait(0);
}

inline void actSt26aConte01_1_newgame(GObj *volatile self)
{
    _ACTWait(1);

    while (gflagChk(382) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy("newgame demo\n");

    debug_StdPrintfDummy("demo layout\n");

    gflagOn(2);

    RequestStageChange(1, boyGObj, 0, 0.25f, 2.0f);
}

void actOpDemo01_2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    scpFadeOut(255.0f, 0, 0, 0);

    adpcm_conte01_sea = 0;
    op2 = 0;

    lt_switch_layout(52);
    scpBoyControlReadDisable = 1;

    scpAdpcmPlayRequestFunc(7, &adpcm_conte01_sea, 0, 0, 1);
    while (adpcm_conte01_sea != 0) {
        _ACTWait(1);
    }
    scpFadeIn(2.0f);

    actCreateSubThread(actOpDemo01_2Chk, 21);

    demoSubEnd = 0;
    while (demoSubEnd == 0) {
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            break;
        }
        _ACTWait(1);
    }

    if (adpcm_conte01_sea != 0) {
        scpAdpcmFadeCloseFunc(&adpcm_conte01_sea, 128);
    }

    RequestStageChangeWithColor(1, boyGObj, 0, 1.0f, 4.0f, 255, 255, 255);
}

void actOpDemo01_2Chk(GObj *volatile self)
{
    stgmgrNextStagePreLoadForceStageSet(0);

    scpPlayStart(boyGObj);

    stage_SetAnimation(568, 1, 0);

    stgmgrNextStagePreLoadForceStageSet(exitData[stageData[stage_no].ent[0]].nextStage);

    stage_SetAnimation(7, 1, 0);

    scpPlayMot(boyGObj, 269);
    scpPlayMot(scpSearchGobj(2312), 989);
    scpSearchGobj(2312)->active = 1;
    scpPlayMot(scpSearchGobj(2313), 1011);
    scpSearchGobj(2313)->active = 1;
    scpPlayMot(scpSearchGobj(2314), 1034);
    scpSearchGobj(2314)->active = 1;

    while (stage_ContinueAnimation(568, 569) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 270);
    scpPlayMot(scpSearchGobj(2312), 990);
    scpPlayMot(scpSearchGobj(2313), 1012);
    scpPlayMot(scpSearchGobj(2314), 1035);

    _ACTWait(1);

    stage_SetAnimation(8, 1, 0);

    while (stage_CheckAnimationFrame(569, 340, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpFadeOut(3.0f, 255, 255, 255);
    while (scpFadeChk() != 0) {
        _ACTWait(45);
    }
    stage_SetAnimation(569, -1, -2);
    scpFadeIn(3.0f);

    stage_SetAnimation(570, 1, 0);

    scpAdpcmPlayRequestFunc(10, &op2, 0, 1, 1);

    stage_SetAnimation(9, 1, 0);

    scpPlayMot(boyGObj, 271);
    scpPlayMot(scpSearchGobj(2312), 991);
    scpPlayMot(scpSearchGobj(2313), 1013);
    scpPlayMot(scpSearchGobj(2314), 1036);

    while (stage_ContinueAnimation(570, 571) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 272);
    scpPlayMot(scpSearchGobj(2312), 992);
    scpPlayMot(scpSearchGobj(2313), 1014);
    scpPlayMot(scpSearchGobj(2314), 1037);

    _ACTWait(1);

    stage_SetAnimation(10, 1, 0);

    while (stage_CheckAnimationFinish(571) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoSubEnd = 1;
}

void actOpDemo02(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (boyGObj != 0) {
        scpPlayMot(boyGObj, 0);
    }

    lt_switch_layout(52);
    scpBoyControlReadDisable = 1;

    stage_SetAnimation(147, 0, 0);

    scpAdpcmPlayRequestFunc(8, &demoAdpcm, 0, 1, 1);
    while (demoAdpcm == 0) {
        _ACTWait(1);
    }

    if (op2 == 0) {
        scpAdpcmPlayRequestFunc(10, &op2, 0, 1, 1);
    }

    opDemo02_mes[0].func = actOpDemo02Chk;
    act->mail = opDemo02_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

inline void actOpDemo02Chk(GObj *volatile self)
{
    gflagOn(3);

    actCreateSubThread(actSt24aConte01_2, 21);

    actCreateSubThread(actSt24aConte01_2_Jimaku, 21);

    demoSubEnd = 0;
    while (demoSubEnd == 0) {
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            break;
        }
        _ACTWait(1);
    }

    if (demoSubEnd == 0) {
        if (demoAdpcm != 0) {
            scpAdpcmFadeCloseFunc(&demoAdpcm, 512);
        }
        if (op2 != 0) {
            scpAdpcmFadeCloseFunc(&op2, 64);
        }
    }

    RequestStageChange(2, boyGObj, 0, 0.5f, 4.0f);
}

void actSt24aConte01_2(GObj *volatile self)
{
    stgmgrNextStagePreLoadForceStageSet(exitData[stageData[stage_no].ent[1]].nextStage);

    scpPlayStart(boyGObj);

    stage_SetAnimation(572, 1, 0);

    stage_SetAnimation(11, 1, 0);

    scpPlayMot(boyGObj, 273);

    scpPlayMot(scpSearchGobj(2336), 993);
    scpSearchGobj(2336)->active = 1;
    scpPlayMot(scpSearchGobj(2337), 1015);
    scpSearchGobj(2337)->active = 1;
    scpPlayMot(scpSearchGobj(2338), 1038);
    scpSearchGobj(2338)->active = 1;

    while (stage_ContinueAnimation(572, 573) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 274);
    scpPlayMot(scpSearchGobj(2336), 994);
    scpPlayMot(scpSearchGobj(2337), 1016);

    scpPlayMot(scpSearchGobj(2338), 1041);

    _ACTWait(1);

    stage_SetAnimation(12, 1, 0);

    _ACTWait(120);

    stage_SetAnimation(147, 1, 0);

    while (stage_ContinueAnimation(573, 574) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 275);
    scpPlayMot(scpSearchGobj(2336), 995);
    scpPlayMot(scpSearchGobj(2337), 1017);
    scpPlayMot(scpSearchGobj(2338), 1039);

    _ACTWait(1);

    stage_SetAnimation(13, 1, 0);

    while (stage_ContinueAnimation(574, 575) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 276);
    scpPlayMot(scpSearchGobj(2336), 996);
    scpPlayMot(scpSearchGobj(2337), 1018);
    scpPlayMot(scpSearchGobj(2338), 1040);

    _ACTWait(1);

    stage_SetAnimation(14, 1, 0);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 10);

    scpFadeOut(6.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(45);
    }
    stage_SetAnimation(575, -1, -2);
    scpFadeIn(3.0f);

    stage_SetAnimation(576, 1, 0);

    stage_SetAnimation(15, 0, 0);

    scpPlayMot(boyGObj, 277);
    scpPlayMot(scpSearchGobj(2336), 997);
    scpPlayMot(scpSearchGobj(2337), 1019);
    scpPlayMot(scpSearchGobj(2338), 1041);

    while (stage_CheckAnimationFinish(576) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoSubEnd = 1;
}

inline void actSt24aConte01_2_Jimaku(GObj *volatile self)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 100:
            jimakuBegin(&jimaku_msg);
            break;
        case 2400:
            jimaku_msg.sub.block = 0;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        }

        n = (int)t;
        tn = t + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 2700.0f);
}

inline void actOpDemo03(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    lt_switch_layout(52);
    scpBoyControlReadDisable = 1;

    stage_SetAnimation(172, 0, 0);
    stage_SetAnimation(168, 0, 0);

    opDemo03_mes[0].func = actOpDemo03Chk;
    act->mail = opDemo03_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actOpDemo03Chk(GObj *volatile self)
{
    float t = 4.0f;

    gflagOn(4);

    scpFadeOut(255.0f, 0, 0, 0);

    scpAdpcmPlayRequestFunc(9, &op2, 0, 1, 1);
    while (op2 == 0) {
        _ACTWait(1);
    }
    scpFadeIn(3.0f);

    actCreateSubThread(actSt13aConte01_3, 21);

    demoSubEnd = 0;
    while (demoSubEnd == 0) {
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            break;
        }
        _ACTWait(1);
    }

    if (demoSubEnd == 0) {
        if (op2 != 0) {
            scpAdpcmFadeCloseFunc(&op2, 128);
            t = 16.0f;
        }
    }

    scpFadeOut(t, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    RequestStageChange(4, boyGObj, 0, 255.0f, 2.0f);
}

void actSt13aConte01_3(GObj *volatile self)
{
    stgmgrNextStagePreLoadForceStageSet(exitData[stageData[stage_no].ent[3]].nextStage);

    scpPlayStart(boyGObj);

    stage_SetAnimation(577, 1, 0);

    scpPlayMot(boyGObj, 278);
    scpPlayMot(scpSearchGobj(2364), 998);
    scpSearchGobj(2364)->active = 1;
    scpPlayMot(scpSearchGobj(2365), 1020);
    scpSearchGobj(2365)->active = 1;
    scpPlayMot(scpSearchGobj(2366), 1042);
    scpSearchGobj(2366)->active = 1;

    _ACTWait(1);
    stage_SetAnimation(16, 1, 0);

    while (stage_ContinueAnimation(577, 578) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2366), 1043);

    scpPlayMot(scpSearchGobj(2364), 999);
    scpPlayMot(scpSearchGobj(2365), 1021);

    _ACTWait(1);
    stage_SetAnimation(17, 1, 0);

    while (stage_ContinueAnimation(578, 579) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 279);
    scpPlayMot(scpSearchGobj(2366), 1044);

    _ACTWait(1);
    stage_SetAnimation(18, 1, 0);
    stage_SetAnimation(172, 1, 0);

    while (stage_ContinueAnimation(579, 580) == 0) {
        _ACTWait(1);
    }

    scpFadeIn(3.0f);

    scpPlayMot(boyGObj, 280);
    scpPlayMot(scpSearchGobj(2364), 999);
    scpPlayMot(scpSearchGobj(2365), 1021);
    scpPlayMot(scpSearchGobj(2366), 1045);

    _ACTWait(1);
    stage_SetAnimation(19, 1, 0);
    stage_SetAnimation(168, 1, 0);

    while (stage_ContinueAnimation(580, 581) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 281);
    scpPlayMot(scpSearchGobj(2364), 1000);
    scpPlayMot(scpSearchGobj(2365), 1022);
    scpPlayMot(scpSearchGobj(2366), 1046);

    _ACTWait(1);
    stage_SetAnimation(20, 1, 0);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 8);

    demoSubEnd = 1;
    _ACTWait(0);
}
