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
void actOpDemo01(GObj *volatile self)
{
    GObj *x = self;
    GProc *th;
    int t = (60 - systemStatus[0] * 10) / systemStatus[1] * 10;

    inline int tick(void) /* derived name */
    {
        if ((current_layout_id == 9 || current_layout_id == 10) && lt_continue_selected == 0) {
            t--;
        } else {
            t = (60 - systemStatus[0] * 10) / systemStatus[1] * 10;
        }
        if (t < 0) {
            current_layout_id = 51;
            return 1;
        }
        return 0;
    }

    actInitialize(self);
    _ACTWait(1);

    stgmgrNextStagePreLoadForceStageSet(0);

    actCreateSubThread(actSubMpegReturnPreload, 21);

    actCreateSubThread(actSt26aConte01_1_newgame, 21);

    scpBoyControlReadDisable = 1;

    while (kanbanBootEnd == 0) {
        _ACTWait(1);
    }

    scpFadeOut(255.0f, 0, 0, 0);
    titleAdpcm = 0;

    while (1) {
        titleSubEnd = 0;
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        opTitleLogoMode = 0;

        stage_SetAnimation(500, -1, -2);
        stage_SetAnimation(492, -1, -2);
        stage_SetAnimation(493, -1, -2);
        stage_SetAnimation(494, -1, -2);
        stage_SetAnimation(496, -1, -2);
        stage_SetAnimation(497, -1, -2);
        stage_SetAnimation(498, -1, -2);

        switch (opDemoMode) {
        case 0:
            debug_StdPrintfDummy("mode 0");
            current_layout_id = 51;

            if (titleAdpcm != 0) {
                scpAdpcmFadeCloseFunc(titleAdpcm, 288);
            }
            titleAdpcm = 0;
            titleSubAdpcm = 0;
            th = actCreateSubThread(actTitleReadTimeDemo0, 21);

            t = (60 - systemStatus[0] * 10) / systemStatus[1] * 10;
            while (titleSubAdpcm == 0) {
                _ACTWait(1);
            }
            _ACTWait(30);

            while (1) {
                _ACTWait(1);
                if (titleSubEnd == 0) {
                    if (pad[0].flags & 0x800) {
                        opDemoMode = 1;
                        opDemoNextMode = 2;
                        break;
                    }
                } else if (tick()) {
                    opDemoMode = 2;
                    break;
                }
            }

            if (titleSubAdpcm != 0) {
                soundDataClose(titleSubAdpcm);
            }
            iosThreadSetPri(&((GProc *)th)->thread, 34);
            scpFadeOut(16.0f, 0, 0, 0);
            break;

        case 1:
            debug_StdPrintfDummy("mode 1");
            opTitleLogoMode = 1;
            lt_switch_layout(9);
            th = actCreateSubThread(actTitleShortCut, 21);

            t = (60 - systemStatus[0] * 10) / systemStatus[1] * 10;

            while (1) {
                _ACTWait(1);
                if (titleSubEnd != 0 && tick()) {
                    lt_switch_layout(51);
                    opDemoMode = opDemoNextMode;
                    break;
                }
            }
            iosThreadSetPri(&((GProc *)th)->thread, 34);
            scpFadeOut(16.0f, 0, 0, 0);
            break;

        case 2:
            debug_StdPrintfDummy("mode 2");
            opDemoMode = 1;
            opDemoNextMode = 0;
            mpegPlayReturnStage = 1;
            if (titleAdpcm != 0) {
                scpAdpcmFadeCloseFunc(titleAdpcm, 1024);
                while (scpAdpcmCloseChkFunc(titleAdpcm) != 0) {
                    _ACTWait(1);
                }
            }
            titleAdpcm = 0;
            _ACTWait(1);
            stgmgrForceSwitchWithFade(57, 256.0f, 4.0f);
            _ACTWait(0);
            break;
        }
    }
}

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
        scpAdpcmPlayRequestFunc(54, &titleAdpcm, 0, 0, 1);
    }
    stage_SetAnimation(500, 1, 1351);

    scpSearchGobj(41)->active = 1;
    scpSearchGobj(42)->active = 1;
    scpSearchGobj(43)->active = 1;
    scpSearchGobj(45)->active = 1;
    scpSearchGobj(46)->active = 1;
    scpSearchGobj(47)->active = 1;
    scpSearchGobj(48)->active = 1;

    while (titleAdpcm != 0) {
        _ACTWait(1);
    }

    scpFadeIn(3.0f);

    while (stage_CheckAnimationFinish(500) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    titleSubEnd = 1;
    _ACTWait(0);
}

/* .data: the two demo mail pairs, each the mail the demo thread answers and
   the 396 end marker. */
static ActMail opDemo02_mes[2] = {{397}, {396}}; /* derived name */

static ActMail opDemo03_mes[2] = {{397}, {396}}; /* derived name */

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
    lt_switch_layout(51);

    _ACTWait(1);

    scpSearchGobj(41)->active = 0;
    scpSearchGobj(42)->active = 0;
    scpSearchGobj(43)->active = 0;
    scpSearchGobj(45)->active = 0;
    scpSearchGobj(46)->active = 0;
    scpSearchGobj(47)->active = 0;
    scpSearchGobj(48)->active = 0;

    scpSearchGobj(44)->active = 1;

    scpAdpcmPlayRequestFunc(6, &titleSubAdpcm, 1, 1, 1);
    while (titleSubAdpcm == 0) {
        _ACTWait(1);
    }

    scpFadeIn(3.0f);

    stage_SetAnimation(492, 1, 0);

    while (stage_ContinueAnimation(492, 493) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(56), 990);
    scpSearchGobj(56)->active = 1;
    scpPlayMot(scpSearchGobj(57), 997);
    scpSearchGobj(57)->active = 1;
    scpPlayMot(scpSearchGobj(58), 1004);
    scpSearchGobj(58)->active = 1;

    while (stage_ContinueAnimation(493, 494) == 0) {
        _ACTWait(1);
    }

    scpPlayStart(boyGObj);

    scpPlayMot(boyGObj, 257);

    scpPlayMot(scpSearchGobj(53), 922);
    scpSearchGobj(53)->active = 1;
    scpPlayMot(scpSearchGobj(54), 944);
    scpSearchGobj(54)->active = 1;
    scpPlayMot(scpSearchGobj(55), 967);
    scpSearchGobj(55)->active = 1;
    scpPlayMot(scpSearchGobj(56), 991);
    scpPlayMot(scpSearchGobj(57), 998);
    scpPlayMot(scpSearchGobj(58), 1005);

    while (stage_ContinueAnimation(494, 495) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 258);
    scpPlayMot(scpSearchGobj(53), 923);
    scpPlayMot(scpSearchGobj(54), 945);
    scpPlayMot(scpSearchGobj(55), 968);
    scpPlayMot(scpSearchGobj(56), 992);
    scpPlayMot(scpSearchGobj(57), 999);
    scpPlayMot(scpSearchGobj(58), 1006);

    while (stage_CheckAnimationFrame(495, 60, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(57)->active = 0;
    scpSearchGobj(54)->active = 0;

    while (stage_ContinueAnimation(495, 496) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(57)->active = 1;
    scpSearchGobj(54)->active = 1;

    scpPlayMot(boyGObj, 259);
    scpPlayMot(scpSearchGobj(53), 924);
    scpPlayMot(scpSearchGobj(54), 946);
    scpPlayMot(scpSearchGobj(55), 969);
    scpPlayMot(scpSearchGobj(56), 993);
    scpPlayMot(scpSearchGobj(57), 1000);
    scpPlayMot(scpSearchGobj(58), 1007);

    while (stage_CheckAnimationFrame(496, 90, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(51)->active = 0;

    while (stage_ContinueAnimation(496, 497) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(53), 925);
    scpPlayMot(scpSearchGobj(54), 947);
    scpPlayMot(scpSearchGobj(55), 970);
    scpPlayMot(scpSearchGobj(56), 994);
    scpPlayMot(scpSearchGobj(57), 1001);
    scpPlayMot(scpSearchGobj(58), 1008);

    _ACTWait(1);

    scpSearchGobj(54)->active = 0;

    while (stage_ContinueAnimation(497, 498) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 261);
    scpPlayMot(scpSearchGobj(53), 926);
    scpPlayMot(scpSearchGobj(54), 948);
    scpPlayMot(scpSearchGobj(55), 971);
    scpPlayMot(scpSearchGobj(56), 995);
    scpPlayMot(scpSearchGobj(57), 1002);
    scpPlayMot(scpSearchGobj(58), 1009);

    _ACTWait(1);

    scpSearchGobj(51)->active = 1;
    scpSearchGobj(54)->active = 1;

    scpSearchGobj(41)->active = 1;
    scpSearchGobj(42)->active = 1;
    scpSearchGobj(43)->active = 1;
    scpSearchGobj(45)->active = 1;
    scpSearchGobj(46)->active = 1;
    scpSearchGobj(47)->active = 1;
    scpSearchGobj(48)->active = 1;

    scpSearchGobj(44)->active = 0;

    while (stage_ContinueAnimation(498, 500) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 262);
    scpPlayMot(scpSearchGobj(53), 927);
    scpPlayMot(scpSearchGobj(54), 949);
    scpPlayMot(scpSearchGobj(55), 972);
    scpPlayMot(scpSearchGobj(56), 996);
    scpPlayMot(scpSearchGobj(57), 1003);
    scpPlayMot(scpSearchGobj(58), 1010);

    debug_StdPrintfDummy("finish anim %d\n", frame_count);

    debug_StdPrintfDummy("frame anim %d\n", frame_count);

    _ACTWait(900);

    _ACTWait(1000);

    opTitleLogoMode = 1;
    while (stage_CheckAnimationFrame(500, 1300, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    monitorCameraHold = 1;

    debug_StdPrintfDummy("game mode %d %d\n", frame_count, gflagChk(353));

    lt_switch_layout(9);

    if (titleAdpcm == 0) {
        scpAdpcmPlayRequestFunc(54, &titleAdpcm, 0, 0, 1);
    }
    titleSubEnd = 1;

    _ACTWait(0);
}

inline void actSt26aConte01_1_newgame(GObj *volatile self)
{
    _ACTWait(1);

    while (gflagChk(349) == 0) {
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

    lt_switch_layout(51);
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
        scpAdpcmFadeCloseFunc(adpcm_conte01_sea, 128);
    }

    RequestStageChangeWithColor(1, boyGObj, 0, 1.0f, 4.0f, 255, 255, 255);
}

void actOpDemo01_2Chk(GObj *volatile self)
{
    stgmgrNextStagePreLoadForceStageSet(0);

    scpPlayStart(boyGObj);

    stage_SetAnimation(501, 1, 0);

    stgmgrNextStagePreLoadForceStageSet(exitData[stageData[stage_no].ent[0]].nextStage);

    stage_SetAnimation(7, 1, 0);

    scpPlayMot(boyGObj, 263);
    scpPlayMot(scpSearchGobj(2105), 928);
    scpSearchGobj(2105)->active = 1;
    scpPlayMot(scpSearchGobj(2106), 950);
    scpSearchGobj(2106)->active = 1;
    scpPlayMot(scpSearchGobj(2107), 973);
    scpSearchGobj(2107)->active = 1;

    while (stage_ContinueAnimation(501, 502) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 264);
    scpPlayMot(scpSearchGobj(2105), 929);
    scpPlayMot(scpSearchGobj(2106), 951);
    scpPlayMot(scpSearchGobj(2107), 974);

    _ACTWait(1);

    stage_SetAnimation(8, 1, 0);

    while (stage_CheckAnimationFrame(502, 340, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpFadeOut(3.0f, 255, 255, 255);
    while (scpFadeChk() != 0) {
        _ACTWait(45);
    }
    stage_SetAnimation(502, -1, -2);
    scpFadeIn(3.0f);

    stage_SetAnimation(503, 1, 0);

    scpAdpcmPlayRequestFunc(10, &op2, 0, 1, 1);

    stage_SetAnimation(9, 1, 0);

    scpPlayMot(boyGObj, 265);
    scpPlayMot(scpSearchGobj(2105), 930);
    scpPlayMot(scpSearchGobj(2106), 952);
    scpPlayMot(scpSearchGobj(2107), 975);

    while (stage_ContinueAnimation(503, 504) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 266);
    scpPlayMot(scpSearchGobj(2105), 931);
    scpPlayMot(scpSearchGobj(2106), 953);
    scpPlayMot(scpSearchGobj(2107), 976);

    _ACTWait(1);

    stage_SetAnimation(10, 1, 0);

    while (stage_CheckAnimationFinish(504) == 0) {
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

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    stage_SetAnimation(131, 0, 0);

    scpAdpcmPlayRequestFunc(8, &demoAdpcm, 0, 1, 1);
    while (demoAdpcm == 0) {
        _ACTWait(1);
    }

    if (op2 == 0) {
        scpAdpcmPlayRequestFunc(10, &op2, 0, 1, 1);
    }

    opDemo02_mes[0].func = actOpDemo02Chk;
    act->mail = opDemo02_mes;
    ACTSendMailCorrect(self, 397);
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
            scpAdpcmFadeCloseFunc(demoAdpcm, 512);
        }
        if (op2 != 0) {
            scpAdpcmFadeCloseFunc(op2, 64);
        }
    }

    RequestStageChange(2, boyGObj, 0, 0.5f, 4.0f);
}

void actSt24aConte01_2(GObj *volatile self)
{
    stgmgrNextStagePreLoadForceStageSet(exitData[stageData[stage_no].ent[1]].nextStage);

    scpPlayStart(boyGObj);

    stage_SetAnimation(505, 1, 0);

    stage_SetAnimation(11, 1, 0);

    scpPlayMot(boyGObj, 267);

    scpPlayMot(scpSearchGobj(2129), 932);
    scpSearchGobj(2129)->active = 1;
    scpPlayMot(scpSearchGobj(2130), 954);
    scpSearchGobj(2130)->active = 1;
    scpPlayMot(scpSearchGobj(2131), 977);
    scpSearchGobj(2131)->active = 1;

    while (stage_ContinueAnimation(505, 506) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 268);
    scpPlayMot(scpSearchGobj(2129), 933);
    scpPlayMot(scpSearchGobj(2130), 955);

    scpPlayMot(scpSearchGobj(2131), 980);

    _ACTWait(1);

    stage_SetAnimation(12, 1, 0);

    _ACTWait(120);

    stage_SetAnimation(131, 1, 0);

    while (stage_ContinueAnimation(506, 507) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 269);
    scpPlayMot(scpSearchGobj(2129), 934);
    scpPlayMot(scpSearchGobj(2130), 956);
    scpPlayMot(scpSearchGobj(2131), 978);

    _ACTWait(1);

    stage_SetAnimation(13, 1, 0);

    while (stage_ContinueAnimation(507, 508) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 270);
    scpPlayMot(scpSearchGobj(2129), 935);
    scpPlayMot(scpSearchGobj(2130), 957);
    scpPlayMot(scpSearchGobj(2131), 979);

    _ACTWait(1);

    stage_SetAnimation(14, 1, 0);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 10);

    scpFadeOut(6.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(45);
    }
    stage_SetAnimation(508, -1, -2);
    scpFadeIn(3.0f);

    stage_SetAnimation(509, 1, 0);

    scpPlayMot(boyGObj, 271);
    scpPlayMot(scpSearchGobj(2129), 936);
    scpPlayMot(scpSearchGobj(2130), 958);
    scpPlayMot(scpSearchGobj(2131), 980);

    while (stage_CheckAnimationFinish(509) == 0) {
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

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    stage_SetAnimation(155, 0, 0);
    stage_SetAnimation(151, 0, 0);

    opDemo03_mes[0].func = actOpDemo03Chk;
    act->mail = opDemo03_mes;
    ACTSendMailCorrect(self, 397);
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
            scpAdpcmFadeCloseFunc(op2, 128);
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

    stage_SetAnimation(510, 1, 0);

    scpPlayMot(boyGObj, 272);
    scpPlayMot(scpSearchGobj(2156), 937);
    scpSearchGobj(2156)->active = 1;
    scpPlayMot(scpSearchGobj(2157), 959);
    scpSearchGobj(2157)->active = 1;
    scpPlayMot(scpSearchGobj(2158), 981);
    scpSearchGobj(2158)->active = 1;

    _ACTWait(1);
    stage_SetAnimation(15, 1, 0);

    while (stage_ContinueAnimation(510, 511) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2158), 982);

    scpPlayMot(scpSearchGobj(2156), 938);
    scpPlayMot(scpSearchGobj(2157), 960);

    _ACTWait(1);
    stage_SetAnimation(16, 1, 0);

    while (stage_ContinueAnimation(511, 512) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 273);
    scpPlayMot(scpSearchGobj(2158), 983);

    _ACTWait(1);
    stage_SetAnimation(17, 1, 0);
    stage_SetAnimation(155, 1, 0);

    while (stage_ContinueAnimation(512, 513) == 0) {
        _ACTWait(1);
    }

    scpFadeIn(3.0f);

    scpPlayMot(boyGObj, 274);
    scpPlayMot(scpSearchGobj(2156), 938);
    scpPlayMot(scpSearchGobj(2157), 960);
    scpPlayMot(scpSearchGobj(2158), 984);

    _ACTWait(1);
    stage_SetAnimation(18, 1, 0);
    stage_SetAnimation(151, 1, 0);

    while (stage_ContinueAnimation(513, 514) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 275);
    scpPlayMot(scpSearchGobj(2156), 939);
    scpPlayMot(scpSearchGobj(2157), 961);
    scpPlayMot(scpSearchGobj(2158), 985);

    _ACTWait(1);
    stage_SetAnimation(19, 1, 0);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 8);

    demoSubEnd = 1;
    _ACTWait(0);
}
