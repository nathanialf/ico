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
#include "s_init.h"
#include "adpcm_init.h"

/* .sbss: titleAdpcm is the title's stream handle (a file static in this
   build, which only actTitleShortCut addresses);
   titleSubEnd and demoSubEnd are the flags a title or demo sub-thread raises
   when it is done and its parent waits on, titleSubAdpcm the stream handle
   scpAdpcmPlayRequestFunc fills. This build has no second demo handle and no
   title logo step word: no function of the demo addresses one. */
static struct SqEntry *titleAdpcm;

static int titleSubEnd; /* derived name */

static struct SqEntry *titleSubAdpcm; /* derived name */

static int demoSubEnd; /* derived name */

/* .sdata: the opening demo's step and the step it returns to, ahead of the
   demo's "mode" traces; the globals follow the demo below. */
static int opDemoMode = 0; /* derived name */

static int opDemoNextMode = 0; /* derived name */

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
        if (current_layout_id == 9 || current_layout_id == 10) {
            t--;
        } else {
            t = (60 - systemStatus[0] * 10) / systemStatus[1] * 10;
        }
        if (t < 0) {
            return 1;
        }
        return 0;
    }

    actInitialize(self);
    _ACTWait(1);

    actCreateSubThread(actSt26aConte01_1_newgame, 21);

    scpBoyControlReadDisable = 1;

    while (kanbanBootEnd == 0) {
        _ACTWait(1);
    }

    scpFadeOut(255.0f, 0, 0, 0);

    while (1) {
        titleSubEnd = 0;
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        stage_SetAnimation(450, -1, -2);
        stage_SetAnimation(442, -1, -2);
        stage_SetAnimation(443, -1, -2);
        stage_SetAnimation(444, -1, -2);
        stage_SetAnimation(446, -1, -2);
        stage_SetAnimation(447, -1, -2);
        stage_SetAnimation(448, -1, -2);

        switch (opDemoMode) {
        case 0:
            debug_StdPrintfDummy("mode 0");
            current_layout_id = 51;
            titleSubAdpcm = 0;
            th = actCreateSubThread(actTitleReadTimeDemo0, 21);

            t = (60 - systemStatus[0] * 10) / systemStatus[1] * 10;
            while (titleSubAdpcm == 0) {
                _ACTWait(1);
            }

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
            stgmgrForceSwitchWithFade(58, 256.0f, 4.0f);
            _ACTWait(0);
            break;
        }
    }
}

/* .sdata, after actOpDemo01's traces: the second demo's and the first
   scene's stream handles (declared in op.h). */
struct SqEntry *op2 = 0;

struct SqEntry *adpcm_conte01_sea = 0;

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

    if (op2 != 0) {
        scpAdpcmFadeClose(op2, 32);
    }

    RequestStageChange(2, boyGObj, 0, 0.5f, 4.0f);
}

void actSt24aConte01_2(GObj *volatile self)
{
    stgmgrNextStagePreLoadForceStageSet(exitData[stageData[stage_no].ent[1]].nextStage);

    scpPlayStart(boyGObj);

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
        _ACTWait(1);
    }

    stage_SetAnimation(8, 1, 0);

    _ACTWait(120);

    stage_SetAnimation(117, 1, 0);

    scpPlayMot(boyGObj, 277);
    scpPlayMot(scpSearchGobj(2015), 1013);
    scpPlayMot(scpSearchGobj(2016), 1035);
    scpPlayMot(scpSearchGobj(2017), 1060);

    while (stage_ContinueAnimation(456, 457) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(9, 1, 0);

    scpPlayMot(boyGObj, 278);
    scpPlayMot(scpSearchGobj(2015), 1014);
    scpPlayMot(scpSearchGobj(2016), 1036);
    scpPlayMot(scpSearchGobj(2017), 1058);

    while (stage_ContinueAnimation(457, 458) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 279);
    scpPlayMot(scpSearchGobj(2015), 1015);
    scpPlayMot(scpSearchGobj(2016), 1037);
    scpPlayMot(scpSearchGobj(2017), 1059);

    stage_SetAnimation(10, 1, 0);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 10);

    scpFadeOut(6.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(45);
    }
    stage_SetAnimation(458, -1, -2);
    scpFadeIn(3.0f);

    stage_SetAnimation(459, 1, 0);

    scpPlayMot(boyGObj, 280);
    scpPlayMot(scpSearchGobj(2015), 1016);
    scpPlayMot(scpSearchGobj(2016), 1038);
    scpPlayMot(scpSearchGobj(2017), 1060);

    while (stage_CheckAnimationFinish(459) == 0) {
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

    stage_SetAnimation(141, 0, 0);
    stage_SetAnimation(137, 0, 0);

    lt_switch_layout(51);

    opDemo03_mes[0].func = actOpDemo03Chk;
    act->mail = opDemo03_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actOpDemo03Chk(GObj *volatile self)
{
    float t = 4.0f;

    gflagOn(4);

    actCreateSubThread(actSt13aConte01_3, 21);

    demoSubEnd = 0;
    op2 = 0;
    while (demoSubEnd == 0) {
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            break;
        }
        _ACTWait(1);
    }

    if (demoSubEnd == 0) {
        if (op2 != 0) {
            scpAdpcmFadeClose(op2, 128);
            t = 16.0f;
        }
    }

    scpFadeOut(t, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    if (demoSubEnd != 0) {
        if (op2 != 0) {
            scpAdpcmFadeClose(op2, 128);
        }
    }

    RequestStageChange(4, boyGObj, 0, 255.0f, 2.0f);
}

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
