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

#ifdef VERSION_JUN26
#include "s_init.h"
#include "adpcm_init.h"

/* .sbss: titleAdpcm is the title's stream handle (a file static in this
   build, which only actTitleShortCut addresses);
   titleSubEnd and demoSubEnd are the flags a title or demo sub-thread raises
   when it is done and its parent waits on, titleSubAdpcm the stream handle
   scpAdpcmPlayRequestFunc fills. This build has no second demo handle and no
   title logo step word: no function of the demo addresses one. */
static struct SqEntry *titleAdpcm;
#else
/* .sbss: titleSubEnd and demoSubEnd are the flags a title or demo sub-thread
   raises when it is done and its parent waits on, titleSubAdpcm and demoAdpcm
   the stream handles scpAdpcmPlayRequestFunc fills. */
#endif

static int titleSubEnd; /* derived name */

static struct SqEntry *titleSubAdpcm; /* derived name */

static int demoSubEnd; /* derived name */

#ifndef VERSION_JUN26
static struct SqEntry *demoAdpcm; /* derived name */
#endif

/* .sdata: the opening demo's step and the step it returns to, ahead of the
   demo's "mode" traces; the globals follow the demo below. */
static int opDemoMode = 0; /* derived name */

static int opDemoNextMode = 0; /* derived name */

#ifndef VERSION_JUN26
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
#endif

void actTitleReadTimeDemo0(GObj *volatile self);
void actTitleShortCut(GObj *volatile self);

#ifdef VERSION_NTSC
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
                scpAdpcmFadeClose(titleAdpcm, 288);
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
                scpAdpcmFadeClose(titleAdpcm, 1024);
                while (scpAdpcmCloseChk(titleAdpcm) != 0) {
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
#else
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
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN) || defined(VERSION_AUG6)
        if ((current_layout_id == 9 || current_layout_id == 10) && lt_continue_selected == 0) {
#else
#ifdef VERSION_JUN26
        if (current_layout_id == 9 || current_layout_id == 10) {
#else
        if ((current_layout_id == 12 || current_layout_id == 13) && lt_continue_selected == 0) {
#endif
#endif
            t--;
        } else {
            t = (60 - systemStatus[0] * 10) / systemStatus[1] * 10;
        }
        if (t < 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            current_layout_id = 52;
#else
#ifdef VERSION_AUG6
            current_layout_id = 51;
#else
#ifndef VERSION_JUN26
            current_layout_id = 55;
#endif
#endif
#endif
            return 1;
        }
        return 0;
    }

    actInitialize(self);
    _ACTWait(1);

#ifndef VERSION_JUN26
#ifndef VERSION_AUG6
    gFlagGameClear = 0;
    optionScreenMode = 0;
    girlControlMode = 0;
#endif
    stgmgrNextStagePreLoadForceStageSet(0);

    actCreateSubThread(actSubMpegReturnPreload, 21);
#endif

    actCreateSubThread(actSt26aConte01_1_newgame, 21);

    scpBoyControlReadDisable = 1;

    while (kanbanBootEnd == 0) {
        _ACTWait(1);
    }

    scpFadeOut(255.0f, 0, 0, 0);
#ifndef VERSION_JUN26
    titleAdpcm = 0;
#endif

    while (1) {
        titleSubEnd = 0;
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
#ifdef VERSION_JUN26

        stage_SetAnimation(450, -1, -2);
        stage_SetAnimation(442, -1, -2);
        stage_SetAnimation(443, -1, -2);
        stage_SetAnimation(444, -1, -2);
        stage_SetAnimation(446, -1, -2);
        stage_SetAnimation(447, -1, -2);
        stage_SetAnimation(448, -1, -2);
#else
        opTitleLogoMode = 0;

#ifdef VERSION_AUG6
        stage_SetAnimation(499, -1, -2);
        stage_SetAnimation(491, -1, -2);
        stage_SetAnimation(492, -1, -2);
        stage_SetAnimation(493, -1, -2);
        stage_SetAnimation(495, -1, -2);
        stage_SetAnimation(496, -1, -2);
        stage_SetAnimation(497, -1, -2);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        stage_SetAnimation(567, -1, -2);
        stage_SetAnimation(559, -1, -2);
        stage_SetAnimation(560, -1, -2);
        stage_SetAnimation(561, -1, -2);
#else
        stage_SetAnimation(571, -1, -2);
#endif
        stage_SetAnimation(563, -1, -2);
        stage_SetAnimation(564, -1, -2);
        stage_SetAnimation(565, -1, -2);
#if !defined(VERSION_JPN) && !defined(VERSION_KOR) && !defined(VERSION_CN)
        stage_SetAnimation(567, -1, -2);
        stage_SetAnimation(568, -1, -2);
        stage_SetAnimation(569, -1, -2);
#endif
#endif
#endif

        switch (opDemoMode) {
        case 0:
            debug_StdPrintfDummy("mode 0");
#ifdef VERSION_JUN26
            current_layout_id = 51;
#else
#ifdef VERSION_AUG6
            current_layout_id = 51;

            if (titleAdpcm != 0) {
                scpAdpcmFadeClose(titleAdpcm, 288);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            current_layout_id = 52;
#else
            current_layout_id = 55;
#endif

            if (titleAdpcm != 0) {
                scpAdpcmFadeCloseFunc(&titleAdpcm, 288);
#endif
            }
            titleAdpcm = 0;
#endif
            titleSubAdpcm = 0;
            th = actCreateSubThread(actTitleReadTimeDemo0, 21);

            t = (60 - systemStatus[0] * 10) / systemStatus[1] * 10;
            while (titleSubAdpcm == 0) {
                _ACTWait(1);
            }
#ifndef VERSION_JUN26
            _ACTWait(30);
#endif

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
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
                soundDataClose(titleSubAdpcm);
#else
                scpAdpcmCloseFunc(&titleSubAdpcm);
#endif
            }
            iosThreadSetPri(&((GProc *)th)->thread, 34);
            scpFadeOut(16.0f, 0, 0, 0);
            break;

        case 1:
            debug_StdPrintfDummy("mode 1");
#ifdef VERSION_JUN26
            lt_switch_layout(9);
#else
            opTitleLogoMode = 1;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN) || defined(VERSION_AUG6)
            lt_switch_layout(9);
#else
            lt_switch_layout(12);
#endif
#endif
            th = actCreateSubThread(actTitleShortCut, 21);

            t = (60 - systemStatus[0] * 10) / systemStatus[1] * 10;

            while (1) {
                _ACTWait(1);
                if (titleSubEnd != 0 && tick()) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
                    lt_switch_layout(52);
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
                    lt_switch_layout(51);
#else
                    lt_switch_layout(55);
#endif
#endif
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
#ifdef VERSION_JUN26
            stgmgrForceSwitchWithFade(58, 256.0f, 4.0f);
#else
            if (titleAdpcm != 0) {
#ifdef VERSION_AUG6
                scpAdpcmFadeClose(titleAdpcm, 1024);
                while (scpAdpcmCloseChk(titleAdpcm) != 0) {
#else
                scpAdpcmFadeCloseFunc(&titleAdpcm, 1024);
                while (scpAdpcmCloseChkFunc(&titleAdpcm) != 0) {
#endif
                    _ACTWait(1);
                }
            }
            titleAdpcm = 0;
            _ACTWait(1);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN) || defined(VERSION_AUG6)
            stgmgrForceSwitchWithFade(57, 256.0f, 4.0f);
#else
            stgmgrForceSwitchWithFade(systemStatus[0] != 0 ? 58 : 57, 256.0f, 4.0f);
#endif
#endif
            _ACTWait(0);
            break;
        }
    }
}
#endif

/* .sdata, after actOpDemo01's traces: the second demo's and the first
   scene's stream handles, the title logo's step and the title's stream handle
   (declared in op.h). */
struct SqEntry *op2 = 0;

struct SqEntry *adpcm_conte01_sea = 0;

#ifdef VERSION_JUN26
void actTitleShortCut(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    titleAdpcm = 0;
    if (boyGObj != 0) {
        scpPlayStart(boyGObj);
    }
    scpAdpcmPlayRequestFunc(51, &titleAdpcm, 1, 0, 1);
    stage_SetAnimation(450, 1, 1351);

    while (titleAdpcm != 0) {
        _ACTWait(1);
    }

    scpFadeIn(3.0f);

    while (stage_CheckAnimationFinish(450) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (titleAdpcm != 0) {
        scpAdpcmFadeClose(titleAdpcm, 80);
    }
    while (titleAdpcm->stream->bg != 0) {
        _ACTWait(1);
    }

    titleSubEnd = 1;
    _ACTWait(0);
}

/* .data: the two demo mail pairs, each the mail the demo thread answers and
   the 429 end marker. */
static ActMail opDemo02_mes[2] = {{377}, {376}}; /* derived name */

static ActMail opDemo03_mes[2] = {{377}, {376}}; /* derived name */

void actTitleReadTimeDemo0(GObj *volatile self)
{
    debug_StdPrintfDummy("realtime demo %d\n", frame_count);

    _ACTWait(1);
    lt_switch_layout(51);

    _ACTWait(1);

    scpAdpcmPlayRequestFunc(9, &titleSubAdpcm, 1, 1, 1);
    while (titleSubAdpcm == 0) {
        _ACTWait(1);
    }

    scpFadeIn(3.0f);

    stage_SetAnimation(442, 1, 0);

    while (stage_ContinueAnimation(442, 443) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(52), 1070);
    scpSearchGobj(52)->active = 1;
    scpPlayMot(scpSearchGobj(53), 1077);
    scpSearchGobj(53)->active = 1;
    scpPlayMot(scpSearchGobj(54), 1084);
    scpSearchGobj(54)->active = 1;

    while (stage_ContinueAnimation(443, 444) == 0) {
        _ACTWait(1);
    }

    scpPlayStart(boyGObj);

    scpPlayMot(boyGObj, 266);
    scpPlayMot(scpSearchGobj(49), 1002);
    scpSearchGobj(49)->active = 1;
    scpPlayMot(scpSearchGobj(50), 1024);
    scpSearchGobj(50)->active = 1;
    scpPlayMot(scpSearchGobj(51), 1047);
    scpSearchGobj(51)->active = 1;

    scpPlayMot(scpSearchGobj(52), 1071);
    scpPlayMot(scpSearchGobj(53), 1078);
    scpPlayMot(scpSearchGobj(54), 1085);

    while (stage_ContinueAnimation(444, 445) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 267);
    scpPlayMot(scpSearchGobj(49), 1003);
    scpPlayMot(scpSearchGobj(50), 1025);
    scpPlayMot(scpSearchGobj(51), 1048);
    scpPlayMot(scpSearchGobj(52), 1072);
    scpPlayMot(scpSearchGobj(53), 1079);
    scpPlayMot(scpSearchGobj(54), 1086);

    while (stage_ContinueAnimation(445, 446) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 268);
    scpPlayMot(scpSearchGobj(49), 1004);
    scpPlayMot(scpSearchGobj(50), 1026);
    scpPlayMot(scpSearchGobj(51), 1049);
    scpPlayMot(scpSearchGobj(52), 1073);
    scpPlayMot(scpSearchGobj(53), 1080);
    scpPlayMot(scpSearchGobj(54), 1087);

    while (stage_ContinueAnimation(446, 447) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 269);
    scpPlayMot(scpSearchGobj(49), 1005);
    scpPlayMot(scpSearchGobj(50), 1027);
    scpPlayMot(scpSearchGobj(51), 1050);
    scpPlayMot(scpSearchGobj(52), 1074);
    scpPlayMot(scpSearchGobj(53), 1081);
    scpPlayMot(scpSearchGobj(54), 1088);

    while (stage_ContinueAnimation(447, 448) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 270);
    scpPlayMot(scpSearchGobj(49), 1006);
    scpPlayMot(scpSearchGobj(50), 1028);
    scpPlayMot(scpSearchGobj(51), 1051);
    scpPlayMot(scpSearchGobj(52), 1075);
    scpPlayMot(scpSearchGobj(53), 1082);
    scpPlayMot(scpSearchGobj(54), 1089);

    while (stage_ContinueAnimation(448, 450) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 271);
    scpPlayMot(scpSearchGobj(49), 1007);
    scpPlayMot(scpSearchGobj(50), 1029);
    scpPlayMot(scpSearchGobj(51), 1052);
    scpPlayMot(scpSearchGobj(52), 1076);
    scpPlayMot(scpSearchGobj(53), 1083);
    scpPlayMot(scpSearchGobj(54), 1090);

    debug_StdPrintfDummy("finish anim %d\n", frame_count);

    debug_StdPrintfDummy("frame anim %d\n", frame_count);

    _ACTWait(900);

    while (stage_CheckAnimationFrame(450, 1300, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    debug_StdPrintfDummy("game mode %d %d\n", frame_count, gflagChk(337));

    lt_switch_layout(9);

    titleSubEnd = 1;

    _ACTWait(0);
}

inline void actSt26aConte01_1_newgame(GObj *volatile self)
{
    _ACTWait(1);

    while (gflagChk(333) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy("newgame demo\n");

    lt_switch_layout(51);

    debug_StdPrintfDummy("demo layout\n");

    _ACTWait((int)((float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 1.0f));

    gflagOn(2);

    RequestStageChange(1, boyGObj, 0, 0.25f, 4.0f);
}

inline void actTitleCamera2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(0);
}

inline void actOpDemo01_2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    adpcm_conte01_sea = 0;
    op2 = 0;

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    actCreateSubThread(actOpDemo01_2Chk, 21);

    demoSubEnd = 0;
    while (demoSubEnd == 0) {
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            break;
        }
        _ACTWait(1);
    }

    if (adpcm_conte01_sea != 0) {
        scpAdpcmFadeClose(adpcm_conte01_sea, 128);
    }

    RequestStageChangeWithColor(1, boyGObj, 0, 1.0f, 8.0f, 255, 255, 255);
}

void actOpDemo01_2Chk(GObj *volatile self)
{
    adpcm_conte01_sea = 0;

    stgmgrNextStagePreLoadForceStageSet(0);

    scpPlayStart(boyGObj);

    stage_SetAnimation(451, 1, 0);

    scpAdpcmPlayRequestFunc(10, &adpcm_conte01_sea, 0, 0, 1);

    stgmgrNextStagePreLoadForceStageSet(exitData[stageData[stage_no].ent[0]].nextStage);

    stage_SetAnimation(4, 1, 0);

    scpPlayMot(boyGObj, 272);
    scpPlayMot(scpSearchGobj(1992), 1008);
    scpSearchGobj(1992)->active = 1;
    scpPlayMot(scpSearchGobj(1993), 1030);
    scpSearchGobj(1993)->active = 1;
    scpPlayMot(scpSearchGobj(1994), 1053);
    scpSearchGobj(1994)->active = 1;

    while (stage_ContinueAnimation(451, 452) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 273);
    scpPlayMot(scpSearchGobj(1992), 1009);
    scpPlayMot(scpSearchGobj(1993), 1031);
    scpPlayMot(scpSearchGobj(1994), 1054);

    while (stage_CheckAnimationFrame(452, 340, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpFadeOut(3.0f, 255, 255, 255);
    while (scpFadeChk() != 0) {
        _ACTWait(45);
    }
    stage_SetAnimation(452, -1, -2);
    scpFadeIn(3.0f);

    stage_SetAnimation(453, 1, 0);

    scpAdpcmPlayRequestFunc(13, &op2, 0, 0, 1);

    stage_SetAnimation(5, 1, 0);

    scpPlayMot(boyGObj, 274);
    scpPlayMot(scpSearchGobj(1992), 1010);
    scpPlayMot(scpSearchGobj(1993), 1032);
    scpPlayMot(scpSearchGobj(1994), 1055);

    while (stage_ContinueAnimation(453, 454) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(6, 1, 0);

    scpPlayMot(boyGObj, 275);
    scpPlayMot(scpSearchGobj(1992), 1011);
    scpPlayMot(scpSearchGobj(1993), 1033);
    scpPlayMot(scpSearchGobj(1994), 1056);

    while (stage_CheckAnimationFinish(454) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoSubEnd = 1;
}

inline void actOpDemo02(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    stage_SetAnimation(117, 0, 0);

    if (op2 == 0) {
        scpAdpcmPlayRequestFunc(13, &op2, 0, 0, 1);
    }

    opDemo02_mes[0].func = actOpDemo02Chk;
    act->mail = opDemo02_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}
#else
int opTitleLogoMode = 0;

struct SqEntry *titleAdpcm = 0;

#ifdef VERSION_NTSC
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
#else
void actTitleShortCut(GObj *volatile self)
{
    GObj *x = self;

#ifdef VERSION_AUG6
    FixViewInGameCameraFlag = 1;
#else
    monitorCameraHold = 1;
#endif
    actInitialize(self);
    _ACTWait(1);

    if (boyGObj != 0) {
        scpPlayStart(boyGObj);
    }
    if (titleAdpcm == 0) {
#ifdef VERSION_AUG6
        scpAdpcmPlayRequestFunc(54, &titleAdpcm, 0, 0, 1);
    }
    stage_SetAnimation(499, 1, 1351);

    scpSearchGobj(40)->active = 1;
    scpSearchGobj(41)->active = 1;
    scpSearchGobj(42)->active = 1;
    scpSearchGobj(44)->active = 1;
    scpSearchGobj(45)->active = 1;
    scpSearchGobj(46)->active = 1;
    scpSearchGobj(47)->active = 1;
#else
        scpAdpcmPlayRequestFunc(56, &titleAdpcm, 0, 0, 1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(567, 1, 1351);
#else
    stage_SetAnimation(571, 1, 1351);
#endif

    SetHandCameraLimitInDemo(0, 0);
    SetZoomMaxValInDemo(0);

    scpSearchGobj(43)->active = 1;
    scpSearchGobj(44)->active = 1;
    scpSearchGobj(45)->active = 1;
    scpSearchGobj(48)->active = 1;
    scpSearchGobj(49)->active = 1;
    scpSearchGobj(50)->active = 1;
    scpSearchGobj(51)->active = 1;
#endif

    while (titleAdpcm != 0) {
        _ACTWait(1);
    }

    scpFadeIn(3.0f);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(567) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFinish(499) == 0) {
#else
    while (stage_CheckAnimationFinish(571) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    titleSubEnd = 1;
    _ACTWait(0);
}

#ifdef VERSION_AUG6
/* .data: the two demo mail pairs, each the mail the demo thread answers and
   the 392 end marker. */
static ActMail opDemo02_mes[2] = {{393}, {392}}; /* derived name */

static ActMail opDemo03_mes[2] = {{393}, {392}}; /* derived name */
#else
/* .data: the two demo mail pairs, each the mail the demo thread answers and
   the 429 end marker. */
static ActMail opDemo02_mes[2] = {{430}, {429}}; /* derived name */

static ActMail opDemo03_mes[2] = {{430}, {429}}; /* derived name */
#endif
#endif

inline void actSubMpegReturnPreload(GObj *volatile self)
{
    _ACTWait((int)((float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 5.0f));
    stgmgrNextStagePreLoadForceStageSet(1);
    stgmgrNextStagePreLoadForceNoCancel(1);
}

#ifdef VERSION_NTSC
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
#else
void actTitleReadTimeDemo0(GObj *volatile self)
{
    debug_StdPrintfDummy("realtime demo %d\n", frame_count);

    stage_SetAnimation(2, 0, -1);

#ifdef VERSION_AUG6
    FixViewInGameCameraFlag = 0;

    _ACTWait(1);
    lt_switch_layout(51);
#else
    monitorCameraHold = 0;

    _ACTWait(1);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
#endif

    _ACTWait(1);

#ifdef VERSION_AUG6
    scpSearchGobj(40)->active = 0;
    scpSearchGobj(41)->active = 0;
    scpSearchGobj(42)->active = 0;
    scpSearchGobj(44)->active = 0;
    scpSearchGobj(45)->active = 0;
    scpSearchGobj(46)->active = 0;
    scpSearchGobj(47)->active = 0;

    scpSearchGobj(43)->active = 1;
#else
    scpSearchGobj(43)->active = 0;
    scpSearchGobj(44)->active = 0;
    scpSearchGobj(45)->active = 0;
    scpSearchGobj(48)->active = 0;
    scpSearchGobj(49)->active = 0;
    scpSearchGobj(50)->active = 0;
    scpSearchGobj(51)->active = 0;

    scpSearchGobj(46)->active = 1;
#endif

    scpAdpcmPlayRequestFunc(6, &titleSubAdpcm, 1, 1, 1);
    while (titleSubAdpcm == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    _ACTWait(30);
    scpFadeIn(3.0f);

    stage_SetAnimation(491, 1, 0);

    while (stage_ContinueAnimation(491, 492) == 0) {
#else
    scpFadeIn(3.0f);

    ResetHandCameraLimitInDemo();
    ResetZoomMaxValInDemo();

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(559, 1, 0);
#else
    stage_SetAnimation(563, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_ContinueAnimation(559, 560) == 0) {
#else
    while (stage_ContinueAnimation(563, 564) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(scpSearchGobj(55), 992);
    scpSearchGobj(55)->active = 1;
    scpPlayMot(scpSearchGobj(56), 999);
    scpSearchGobj(56)->active = 1;
    scpPlayMot(scpSearchGobj(57), 1006);
    scpSearchGobj(57)->active = 1;

    while (stage_ContinueAnimation(492, 493) == 0) {
#else
    scpPlayMot(scpSearchGobj(59), 1051);
    scpSearchGobj(59)->active = 1;
    scpPlayMot(scpSearchGobj(60), 1058);
    scpSearchGobj(60)->active = 1;
    scpPlayMot(scpSearchGobj(61), 1065);
    scpSearchGobj(61)->active = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_ContinueAnimation(560, 561) == 0) {
#else
    while (stage_ContinueAnimation(564, 565) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    scpPlayStart(boyGObj);

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 257);

    scpPlayMot(scpSearchGobj(52), 924);
    scpSearchGobj(52)->active = 1;
    scpPlayMot(scpSearchGobj(53), 946);
    scpSearchGobj(53)->active = 1;
    scpPlayMot(scpSearchGobj(54), 969);
    scpSearchGobj(54)->active = 1;
    scpPlayMot(scpSearchGobj(55), 993);
    scpPlayMot(scpSearchGobj(56), 1000);
    scpPlayMot(scpSearchGobj(57), 1007);

    while (stage_ContinueAnimation(493, 494) == 0) {
#else
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

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_ContinueAnimation(561, 562) == 0) {
#else
    while (stage_ContinueAnimation(565, 566) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 258);
    scpPlayMot(scpSearchGobj(52), 925);
    scpPlayMot(scpSearchGobj(53), 947);
    scpPlayMot(scpSearchGobj(54), 970);
    scpPlayMot(scpSearchGobj(55), 994);
    scpPlayMot(scpSearchGobj(56), 1001);
    scpPlayMot(scpSearchGobj(57), 1008);

    while (stage_CheckAnimationFrame(494, 60, 0) == 0) {
#else
    scpPlayMot(boyGObj, 264);
    scpPlayMot(scpSearchGobj(56), 984);
    scpPlayMot(scpSearchGobj(57), 1006);
    scpPlayMot(scpSearchGobj(58), 1029);
    scpPlayMot(scpSearchGobj(59), 1053);
    scpPlayMot(scpSearchGobj(60), 1060);
    scpPlayMot(scpSearchGobj(61), 1067);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(562, 60, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(566, 60, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#ifdef VERSION_AUG6
    scpSearchGobj(56)->active = 0;
    scpSearchGobj(53)->active = 0;

    while (stage_ContinueAnimation(494, 495) == 0) {
#else
    scpSearchGobj(60)->active = 0;
    scpSearchGobj(57)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_ContinueAnimation(562, 563) == 0) {
#else
    while (stage_ContinueAnimation(566, 567) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpSearchGobj(56)->active = 1;
    scpSearchGobj(53)->active = 1;

    scpPlayMot(boyGObj, 259);
    scpPlayMot(scpSearchGobj(52), 926);
    scpPlayMot(scpSearchGobj(53), 948);
    scpPlayMot(scpSearchGobj(54), 971);
    scpPlayMot(scpSearchGobj(55), 995);
    scpPlayMot(scpSearchGobj(56), 1002);
    scpPlayMot(scpSearchGobj(57), 1009);

    while (stage_CheckAnimationFrame(495, 90, 0) == 0) {
#else
    scpSearchGobj(60)->active = 1;
    scpSearchGobj(57)->active = 1;

    scpPlayMot(boyGObj, 265);
    scpPlayMot(scpSearchGobj(56), 985);
    scpPlayMot(scpSearchGobj(57), 1007);
    scpPlayMot(scpSearchGobj(58), 1030);
    scpPlayMot(scpSearchGobj(59), 1054);
    scpPlayMot(scpSearchGobj(60), 1061);
    scpPlayMot(scpSearchGobj(61), 1068);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(563, 90, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(567, 90, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#ifdef VERSION_AUG6
    scpSearchGobj(50)->active = 0;

    while (stage_ContinueAnimation(495, 496) == 0) {
#else
    scpSearchGobj(54)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_ContinueAnimation(563, 564) == 0) {
#else
    while (stage_ContinueAnimation(567, 568) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(scpSearchGobj(52), 927);
    scpPlayMot(scpSearchGobj(53), 949);
    scpPlayMot(scpSearchGobj(54), 972);
    scpPlayMot(scpSearchGobj(55), 996);
    scpPlayMot(scpSearchGobj(56), 1003);
    scpPlayMot(scpSearchGobj(57), 1010);
#else
    scpPlayMot(scpSearchGobj(56), 986);
    scpPlayMot(scpSearchGobj(57), 1008);
    scpPlayMot(scpSearchGobj(58), 1031);
    scpPlayMot(scpSearchGobj(59), 1055);
    scpPlayMot(scpSearchGobj(60), 1062);
    scpPlayMot(scpSearchGobj(61), 1069);
#endif

    _ACTWait(1);

#ifdef VERSION_AUG6
    scpSearchGobj(53)->active = 0;

    while (stage_ContinueAnimation(496, 497) == 0) {
#else
    scpSearchGobj(57)->active = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_ContinueAnimation(564, 565) == 0) {
#else
    while (stage_ContinueAnimation(568, 569) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 261);
    scpPlayMot(scpSearchGobj(52), 928);
    scpPlayMot(scpSearchGobj(53), 950);
    scpPlayMot(scpSearchGobj(54), 973);
    scpPlayMot(scpSearchGobj(55), 997);
    scpPlayMot(scpSearchGobj(56), 1004);
    scpPlayMot(scpSearchGobj(57), 1011);
#else
    scpPlayMot(boyGObj, 267);
    scpPlayMot(scpSearchGobj(56), 987);
    scpPlayMot(scpSearchGobj(57), 1009);
    scpPlayMot(scpSearchGobj(58), 1032);
    scpPlayMot(scpSearchGobj(59), 1056);
    scpPlayMot(scpSearchGobj(60), 1063);
    scpPlayMot(scpSearchGobj(61), 1070);
#endif

    _ACTWait(1);

#ifdef VERSION_AUG6
    scpSearchGobj(50)->active = 1;
    scpSearchGobj(53)->active = 1;

    scpSearchGobj(40)->active = 1;
    scpSearchGobj(41)->active = 1;
    scpSearchGobj(42)->active = 1;
    scpSearchGobj(44)->active = 1;
    scpSearchGobj(45)->active = 1;
    scpSearchGobj(46)->active = 1;
    scpSearchGobj(47)->active = 1;

    scpSearchGobj(43)->active = 0;

    while (stage_ContinueAnimation(497, 499) == 0) {
#else
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

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_ContinueAnimation(565, 567) == 0) {
#else
    while (stage_ContinueAnimation(569, 571) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 262);
    scpPlayMot(scpSearchGobj(52), 929);
    scpPlayMot(scpSearchGobj(53), 951);
    scpPlayMot(scpSearchGobj(54), 974);
    scpPlayMot(scpSearchGobj(55), 998);
    scpPlayMot(scpSearchGobj(56), 1005);
    scpPlayMot(scpSearchGobj(57), 1012);
#else
    SetHandCameraLimitInDemo(0, 0);
    SetZoomMaxValInDemo(0);

    scpPlayMot(boyGObj, 268);
    scpPlayMot(scpSearchGobj(56), 988);
    scpPlayMot(scpSearchGobj(57), 1010);
    scpPlayMot(scpSearchGobj(58), 1033);
    scpPlayMot(scpSearchGobj(59), 1057);
    scpPlayMot(scpSearchGobj(60), 1064);
    scpPlayMot(scpSearchGobj(61), 1071);
#endif

    debug_StdPrintfDummy("finish anim %d\n", frame_count);

    debug_StdPrintfDummy("frame anim %d\n", frame_count);

    _ACTWait(900);

    _ACTWait(1000);

    opTitleLogoMode = 1;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(567, 1300, 0) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFrame(499, 1300, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(571, 1300, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#ifdef VERSION_AUG6
    FixViewInGameCameraFlag = 1;

    debug_StdPrintfDummy("game mode %d %d\n", frame_count, gflagChk(352));

    lt_switch_layout(9);

    if (titleAdpcm == 0) {
        scpAdpcmPlayRequestFunc(54, &titleAdpcm, 0, 0, 1);
#else
    monitorCameraHold = 1;

    debug_StdPrintfDummy("game mode %d %d\n", frame_count, gflagChk(386));

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(9);
#else
    lt_switch_layout(12);
#endif

    if (titleAdpcm == 0) {
        scpAdpcmPlayRequestFunc(56, &titleAdpcm, 0, 0, 1);
#endif
    }
    titleSubEnd = 1;

    _ACTWait(0);
}

inline void actSt26aConte01_1_newgame(GObj *volatile self)
{
    _ACTWait(1);

#ifdef VERSION_AUG6
    while (gflagChk(348) == 0) {
#else
    while (gflagChk(382) == 0) {
#endif
        _ACTWait(1);
    }

    debug_StdPrintfDummy("newgame demo\n");

    debug_StdPrintfDummy("demo layout\n");

    gflagOn(2);

    RequestStageChange(1, boyGObj, 0, 0.25f, 2.0f);
}
#endif

void actOpDemo01_2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    scpFadeOut(255.0f, 0, 0, 0);

    adpcm_conte01_sea = 0;
    op2 = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    lt_switch_layout(51);
#else
    lt_switch_layout(55);
#endif
#endif
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
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
        scpAdpcmFadeClose(adpcm_conte01_sea, 128);
#else
        scpAdpcmFadeCloseFunc(&adpcm_conte01_sea, 128);
#endif
    }

    RequestStageChangeWithColor(1, boyGObj, 0, 1.0f, 4.0f, 255, 255, 255);
}

#ifdef VERSION_NTSC
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
#else
void actOpDemo01_2Chk(GObj *volatile self)
{
    stgmgrNextStagePreLoadForceStageSet(0);

    scpPlayStart(boyGObj);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(568, 1, 0);
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(500, 1, 0);
#else
    stage_SetAnimation(572, 1, 0);
#endif
#endif

    stgmgrNextStagePreLoadForceStageSet(exitData[stageData[stage_no].ent[0]].nextStage);

    stage_SetAnimation(7, 1, 0);

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 263);
    scpPlayMot(scpSearchGobj(2080), 930);
    scpSearchGobj(2080)->active = 1;
    scpPlayMot(scpSearchGobj(2081), 952);
    scpSearchGobj(2081)->active = 1;
    scpPlayMot(scpSearchGobj(2082), 975);
    scpSearchGobj(2082)->active = 1;

    while (stage_ContinueAnimation(500, 501) == 0) {
#else
    scpPlayMot(boyGObj, 269);
    scpPlayMot(scpSearchGobj(2312), 989);
    scpSearchGobj(2312)->active = 1;
    scpPlayMot(scpSearchGobj(2313), 1011);
    scpSearchGobj(2313)->active = 1;
    scpPlayMot(scpSearchGobj(2314), 1034);
    scpSearchGobj(2314)->active = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_ContinueAnimation(568, 569) == 0) {
#else
    while (stage_ContinueAnimation(572, 573) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    stage_SetAnimation(8, 1, 0);

    scpPlayMot(boyGObj, 264);
    scpPlayMot(scpSearchGobj(2080), 931);
    scpPlayMot(scpSearchGobj(2081), 953);
    scpPlayMot(scpSearchGobj(2082), 976);

    while (stage_CheckAnimationFrame(501, 340, 0) == 0) {
#else
    scpPlayMot(boyGObj, 270);
    scpPlayMot(scpSearchGobj(2312), 990);
    scpPlayMot(scpSearchGobj(2313), 1012);
    scpPlayMot(scpSearchGobj(2314), 1035);

    _ACTWait(1);

    stage_SetAnimation(8, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFrame(569, 340, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(573, 340, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    scpFadeOut(3.0f, 255, 255, 255);
    while (scpFadeChk() != 0) {
        _ACTWait(45);
    }
#ifdef VERSION_AUG6
    stage_SetAnimation(501, -1, -2);
    scpFadeIn(3.0f);

    stage_SetAnimation(502, 1, 0);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(569, -1, -2);
#else
    stage_SetAnimation(573, -1, -2);
#endif
    scpFadeIn(3.0f);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(570, 1, 0);
#else
    stage_SetAnimation(574, 1, 0);
#endif
#endif

    scpAdpcmPlayRequestFunc(10, &op2, 0, 1, 1);

    stage_SetAnimation(9, 1, 0);

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 265);
    scpPlayMot(scpSearchGobj(2080), 932);
    scpPlayMot(scpSearchGobj(2081), 954);
    scpPlayMot(scpSearchGobj(2082), 977);

    while (stage_ContinueAnimation(502, 503) == 0) {
#else
    scpPlayMot(boyGObj, 271);
    scpPlayMot(scpSearchGobj(2312), 991);
    scpPlayMot(scpSearchGobj(2313), 1013);
    scpPlayMot(scpSearchGobj(2314), 1036);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_ContinueAnimation(570, 571) == 0) {
#else
    while (stage_ContinueAnimation(574, 575) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    stage_SetAnimation(10, 1, 0);

    scpPlayMot(boyGObj, 266);
    scpPlayMot(scpSearchGobj(2080), 933);
    scpPlayMot(scpSearchGobj(2081), 955);
    scpPlayMot(scpSearchGobj(2082), 978);

    while (stage_CheckAnimationFinish(503) == 0) {
#else
    scpPlayMot(boyGObj, 272);
    scpPlayMot(scpSearchGobj(2312), 992);
    scpPlayMot(scpSearchGobj(2313), 1014);
    scpPlayMot(scpSearchGobj(2314), 1037);

    _ACTWait(1);

    stage_SetAnimation(10, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(571) == 0) {
#else
    while (stage_CheckAnimationFinish(575) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    demoSubEnd = 1;
}
#endif

void actOpDemo02(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (boyGObj != 0) {
        scpPlayMot(boyGObj, 0);
    }

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

#ifdef VERSION_AUG6
    stage_SetAnimation(130, 0, 0);
#else
    stage_SetAnimation(131, 0, 0);
#endif
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(147, 0, 0);
#else
    stage_SetAnimation(151, 0, 0);
#endif
#endif

    scpAdpcmPlayRequestFunc(8, &demoAdpcm, 0, 1, 1);
    while (demoAdpcm == 0) {
        _ACTWait(1);
    }

    if (op2 == 0) {
        scpAdpcmPlayRequestFunc(10, &op2, 0, 1, 1);
    }

    opDemo02_mes[0].func = actOpDemo02Chk;
    act->mail = opDemo02_mes;
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
#endif

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

#ifdef VERSION_JUN26
    if (op2 != 0) {
        scpAdpcmFadeClose(op2, 32);
#else
    if (demoSubEnd == 0) {
        if (demoAdpcm != 0) {
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
            scpAdpcmFadeClose(demoAdpcm, 512);
        }
        if (op2 != 0) {
            scpAdpcmFadeClose(op2, 64);
#else
            scpAdpcmFadeCloseFunc(&demoAdpcm, 512);
        }
        if (op2 != 0) {
            scpAdpcmFadeCloseFunc(&op2, 64);
#endif
        }
#endif
    }

    RequestStageChange(2, boyGObj, 0, 0.5f, 4.0f);
}

#ifdef VERSION_NTSC
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
#else
void actSt24aConte01_2(GObj *volatile self)
{
    stgmgrNextStagePreLoadForceStageSet(exitData[stageData[stage_no].ent[1]].nextStage);

    scpPlayStart(boyGObj);

#ifdef VERSION_JUN26
    stage_SetAnimation(455, 1, 0);

    scpAdpcmPlayRequestFunc(11, 0, 1, 0, 1);

    stage_SetAnimation(7, 1, 0);

    scpPlayMot(boyGObj, 276);
    scpPlayMot(scpSearchGobj(2015), 1012);
    scpSearchGobj(2015)->active = 1;
    scpPlayMot(scpSearchGobj(2016), 1034);
    scpSearchGobj(2016)->active = 1;
    scpPlayMot(scpSearchGobj(2017), 1057);
    scpSearchGobj(2017)->active = 1;

    while (stage_ContinueAnimation(455, 456) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(572, 1, 0);
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(504, 1, 0);
#else
    stage_SetAnimation(576, 1, 0);
#endif
#endif

    stage_SetAnimation(11, 1, 0);

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 267);

    scpPlayMot(scpSearchGobj(2104), 934);
    scpSearchGobj(2104)->active = 1;
    scpPlayMot(scpSearchGobj(2105), 956);
    scpSearchGobj(2105)->active = 1;
    scpPlayMot(scpSearchGobj(2106), 979);
    scpSearchGobj(2106)->active = 1;

    while (stage_ContinueAnimation(504, 505) == 0) {
#else
    scpPlayMot(boyGObj, 273);

    scpPlayMot(scpSearchGobj(2336), 993);
    scpSearchGobj(2336)->active = 1;
    scpPlayMot(scpSearchGobj(2337), 1015);
    scpSearchGobj(2337)->active = 1;
    scpPlayMot(scpSearchGobj(2338), 1038);
    scpSearchGobj(2338)->active = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_ContinueAnimation(572, 573) == 0) {
#else
    while (stage_ContinueAnimation(576, 577) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    stage_SetAnimation(8, 1, 0);
#else
#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 268);
    scpPlayMot(scpSearchGobj(2104), 935);
    scpPlayMot(scpSearchGobj(2105), 957);

    scpPlayMot(scpSearchGobj(2106), 982);
#else
    scpPlayMot(boyGObj, 274);
    scpPlayMot(scpSearchGobj(2336), 994);
    scpPlayMot(scpSearchGobj(2337), 1016);

    scpPlayMot(scpSearchGobj(2338), 1041);
#endif

    _ACTWait(1);

    stage_SetAnimation(12, 1, 0);
#endif

    _ACTWait(120);

#ifdef VERSION_AUG6
    stage_SetAnimation(130, 1, 0);

    while (stage_ContinueAnimation(505, 506) == 0) {
#else
#ifdef VERSION_JUN26
    stage_SetAnimation(117, 1, 0);

    scpPlayMot(boyGObj, 277);
    scpPlayMot(scpSearchGobj(2015), 1013);
    scpPlayMot(scpSearchGobj(2016), 1035);
    scpPlayMot(scpSearchGobj(2017), 1060);

    while (stage_ContinueAnimation(456, 457) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(147, 1, 0);
#else
    stage_SetAnimation(151, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_ContinueAnimation(573, 574) == 0) {
#else
    while (stage_ContinueAnimation(577, 578) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    stage_SetAnimation(9, 1, 0);

    scpPlayMot(boyGObj, 278);
    scpPlayMot(scpSearchGobj(2015), 1014);
    scpPlayMot(scpSearchGobj(2016), 1036);
    scpPlayMot(scpSearchGobj(2017), 1058);

    while (stage_ContinueAnimation(457, 458) == 0) {
#else
#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 269);
    scpPlayMot(scpSearchGobj(2104), 936);
    scpPlayMot(scpSearchGobj(2105), 958);
    scpPlayMot(scpSearchGobj(2106), 980);
#else
    scpPlayMot(boyGObj, 275);
    scpPlayMot(scpSearchGobj(2336), 995);
    scpPlayMot(scpSearchGobj(2337), 1017);
    scpPlayMot(scpSearchGobj(2338), 1039);
#endif

    _ACTWait(1);

    stage_SetAnimation(13, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_ContinueAnimation(574, 575) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(506, 507) == 0) {
#else
    while (stage_ContinueAnimation(578, 579) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    scpPlayMot(boyGObj, 279);
    scpPlayMot(scpSearchGobj(2015), 1015);
    scpPlayMot(scpSearchGobj(2016), 1037);
    scpPlayMot(scpSearchGobj(2017), 1059);

    stage_SetAnimation(10, 1, 0);
#else
#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 270);
    scpPlayMot(scpSearchGobj(2104), 937);
    scpPlayMot(scpSearchGobj(2105), 959);
    scpPlayMot(scpSearchGobj(2106), 981);
#else
    scpPlayMot(boyGObj, 276);
    scpPlayMot(scpSearchGobj(2336), 996);
    scpPlayMot(scpSearchGobj(2337), 1018);
    scpPlayMot(scpSearchGobj(2338), 1040);
#endif

    _ACTWait(1);

    stage_SetAnimation(14, 1, 0);
#endif

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 10);

    scpFadeOut(6.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(45);
    }
#ifdef VERSION_AUG6
    stage_SetAnimation(507, -1, -2);
    scpFadeIn(3.0f);

    stage_SetAnimation(508, 1, 0);

    scpPlayMot(boyGObj, 271);
    scpPlayMot(scpSearchGobj(2104), 938);
    scpPlayMot(scpSearchGobj(2105), 960);
    scpPlayMot(scpSearchGobj(2106), 982);

    while (stage_CheckAnimationFinish(508) == 0) {
#else
#ifdef VERSION_JUN26
    stage_SetAnimation(458, -1, -2);
    scpFadeIn(3.0f);

    stage_SetAnimation(459, 1, 0);

    scpPlayMot(boyGObj, 280);
    scpPlayMot(scpSearchGobj(2015), 1016);
    scpPlayMot(scpSearchGobj(2016), 1038);
    scpPlayMot(scpSearchGobj(2017), 1060);

    while (stage_CheckAnimationFinish(459) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(575, -1, -2);
#else
    stage_SetAnimation(579, -1, -2);
#endif
    scpFadeIn(3.0f);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(576, 1, 0);
#else
    stage_SetAnimation(580, 1, 0);
#endif

    stage_SetAnimation(15, 0, 0);

    scpPlayMot(boyGObj, 277);
    scpPlayMot(scpSearchGobj(2336), 997);
    scpPlayMot(scpSearchGobj(2337), 1019);
    scpPlayMot(scpSearchGobj(2338), 1041);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_CheckAnimationFinish(576) == 0) {
#else
    while (stage_CheckAnimationFinish(580) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    demoSubEnd = 1;
}
#endif

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

#ifdef VERSION_NTSC
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    stage_SetAnimation(155, 0, 0);
    stage_SetAnimation(151, 0, 0);
#else
#ifdef VERSION_AUG6
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    stage_SetAnimation(154, 0, 0);
    stage_SetAnimation(150, 0, 0);
#else
#ifdef VERSION_JUN26
    stage_SetAnimation(141, 0, 0);
    stage_SetAnimation(137, 0, 0);

    lt_switch_layout(51);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;

#if !defined(VERSION_JPN) && !defined(VERSION_KOR) && !defined(VERSION_CN)
    stage_SetAnimation(176, 0, 0);
#endif
    stage_SetAnimation(172, 0, 0);
#endif
#endif
#endif
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(168, 0, 0);
#endif

    opDemo03_mes[0].func = actOpDemo03Chk;
    act->mail = opDemo03_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
    ACTSendMailCorrect(self, 377);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
#endif
    _ACTWait(0);
}

void actOpDemo03Chk(GObj *volatile self)
{
    float t = 4.0f;

    gflagOn(4);

#ifndef VERSION_JUN26
    scpFadeOut(255.0f, 0, 0, 0);

    scpAdpcmPlayRequestFunc(9, &op2, 0, 1, 1);
    while (op2 == 0) {
        _ACTWait(1);
    }
    scpFadeIn(3.0f);
#endif

    actCreateSubThread(actSt13aConte01_3, 21);

    demoSubEnd = 0;
#ifdef VERSION_JUN26
    op2 = 0;
#endif
    while (demoSubEnd == 0) {
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            break;
        }
        _ACTWait(1);
    }

    if (demoSubEnd == 0) {
        if (op2 != 0) {
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
            scpAdpcmFadeClose(op2, 128);
#else
            scpAdpcmFadeCloseFunc(&op2, 128);
#endif
            t = 16.0f;
        }
    }

    scpFadeOut(t, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
#ifdef VERSION_JUN26
    }

    if (demoSubEnd != 0) {
        if (op2 != 0) {
            scpAdpcmFadeClose(op2, 128);
        }
#endif
    }

    RequestStageChange(4, boyGObj, 0, 255.0f, 2.0f);
}

#ifdef VERSION_NTSC
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
#else
#ifdef VERSION_JUN26
void actSt13aConte01_3(GObj *volatile self)
{
    stgmgrNextStagePreLoadForceStageSet(exitData[stageData[stage_no].ent[3]].nextStage);

    scpPlayStart(boyGObj);

    stage_SetAnimation(460, 1, 0);

    scpAdpcmPlayRequestFunc(12, &op2, 0, 0, 1);

    stage_SetAnimation(11, 1, 0);

    scpPlayMot(boyGObj, 281);
    scpPlayMot(scpSearchGobj(2041), 1017);
    scpSearchGobj(2041)->active = 1;
    scpPlayMot(scpSearchGobj(2042), 1039);
    scpSearchGobj(2042)->active = 1;
    scpPlayMot(scpSearchGobj(2043), 1061);
    scpSearchGobj(2043)->active = 1;

    while (stage_ContinueAnimation(460, 461) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(12, 1, 0);

    scpPlayMot(scpSearchGobj(2043), 1062);
    scpPlayMot(scpSearchGobj(2041), 1018);
    scpPlayMot(scpSearchGobj(2042), 1040);

    while (stage_ContinueAnimation(461, 462) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(13, 1, 0);
    stage_SetAnimation(141, 1, 0);

    scpPlayMot(boyGObj, 282);
    scpPlayMot(scpSearchGobj(2043), 1063);

    while (stage_ContinueAnimation(462, 463) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(14, 1, 0);

    scpFadeIn(3.0f);

    stage_SetAnimation(137, 1, 0);

    scpPlayMot(boyGObj, 283);
    scpPlayMot(scpSearchGobj(2041), 1018);
    scpPlayMot(scpSearchGobj(2042), 1040);
    scpPlayMot(scpSearchGobj(2043), 1064);

    while (stage_ContinueAnimation(463, 464) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(15, 1, 0);

    scpPlayMot(boyGObj, 284);
    scpPlayMot(scpSearchGobj(2041), 1019);
    scpPlayMot(scpSearchGobj(2042), 1041);
    scpPlayMot(scpSearchGobj(2043), 1065);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 8);

    demoSubEnd = 1;
}
#else
void actSt13aConte01_3(GObj *volatile self)
{
    stgmgrNextStagePreLoadForceStageSet(exitData[stageData[stage_no].ent[3]].nextStage);

    scpPlayStart(boyGObj);

#ifdef VERSION_AUG6
    stage_SetAnimation(509, 1, 0);

    scpPlayMot(boyGObj, 272);
    scpPlayMot(scpSearchGobj(2131), 939);
    scpSearchGobj(2131)->active = 1;
    scpPlayMot(scpSearchGobj(2132), 961);
    scpSearchGobj(2132)->active = 1;
    scpPlayMot(scpSearchGobj(2133), 983);
    scpSearchGobj(2133)->active = 1;

    _ACTWait(1);
    stage_SetAnimation(15, 1, 0);

    while (stage_ContinueAnimation(509, 510) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2133), 984);

    scpPlayMot(scpSearchGobj(2131), 940);
    scpPlayMot(scpSearchGobj(2132), 962);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(577, 1, 0);
#else
    stage_SetAnimation(581, 1, 0);
#endif

    scpPlayMot(boyGObj, 278);
    scpPlayMot(scpSearchGobj(2364), 998);
    scpSearchGobj(2364)->active = 1;
    scpPlayMot(scpSearchGobj(2365), 1020);
    scpSearchGobj(2365)->active = 1;
    scpPlayMot(scpSearchGobj(2366), 1042);
    scpSearchGobj(2366)->active = 1;
#endif

    _ACTWait(1);
    stage_SetAnimation(16, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_ContinueAnimation(577, 578) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(510, 511) == 0) {
#else
    while (stage_ContinueAnimation(581, 582) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 273);
    scpPlayMot(scpSearchGobj(2133), 985);
#else
    scpPlayMot(scpSearchGobj(2366), 1043);

    scpPlayMot(scpSearchGobj(2364), 999);
    scpPlayMot(scpSearchGobj(2365), 1021);
#endif

    _ACTWait(1);
    stage_SetAnimation(17, 1, 0);
#ifdef VERSION_AUG6
    stage_SetAnimation(154, 1, 0);

    while (stage_ContinueAnimation(511, 512) == 0) {
#else

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_ContinueAnimation(578, 579) == 0) {
#else
    while (stage_ContinueAnimation(582, 583) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 279);
    scpPlayMot(scpSearchGobj(2366), 1044);

    _ACTWait(1);
    stage_SetAnimation(18, 1, 0);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(172, 1, 0);
#else
    stage_SetAnimation(176, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_ContinueAnimation(579, 580) == 0) {
#else
    while (stage_ContinueAnimation(583, 584) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    scpFadeIn(3.0f);

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 274);
    scpPlayMot(scpSearchGobj(2131), 940);
    scpPlayMot(scpSearchGobj(2132), 962);
    scpPlayMot(scpSearchGobj(2133), 986);

    _ACTWait(1);
    stage_SetAnimation(18, 1, 0);
    stage_SetAnimation(150, 1, 0);

    while (stage_ContinueAnimation(512, 513) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 275);
    scpPlayMot(scpSearchGobj(2131), 941);
    scpPlayMot(scpSearchGobj(2132), 963);
    scpPlayMot(scpSearchGobj(2133), 987);
#else
    scpPlayMot(boyGObj, 280);
    scpPlayMot(scpSearchGobj(2364), 999);
    scpPlayMot(scpSearchGobj(2365), 1021);
    scpPlayMot(scpSearchGobj(2366), 1045);
#endif

    _ACTWait(1);
    stage_SetAnimation(19, 1, 0);
#ifndef VERSION_AUG6
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    stage_SetAnimation(168, 1, 0);
#else
    stage_SetAnimation(172, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    while (stage_ContinueAnimation(580, 581) == 0) {
#else
    while (stage_ContinueAnimation(584, 585) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 281);
    scpPlayMot(scpSearchGobj(2364), 1000);
    scpPlayMot(scpSearchGobj(2365), 1022);
    scpPlayMot(scpSearchGobj(2366), 1046);

    _ACTWait(1);
    stage_SetAnimation(20, 1, 0);
#endif

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 8);

    demoSubEnd = 1;
    _ACTWait(0);
}
#endif
#endif
