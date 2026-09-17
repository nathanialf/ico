#include "common.h"
#include "st18a.h"
#include "layout_texture.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "script.h"
#include "StageAnimation.h"
#include "st04r.h"
#include "typedef.h"

static ActMail intro_mes[2] = {{430}, {429}};

static ActMail switchL_mes[2] = {{430}, {429}};

static ActMail switchLUp_mes[2] = {{430}, {429}};

static ActMail switchLChk_mes[2] = {{430}, {429}};

static ActMail switchLUpChk_mes[2] = {{430}, {429}};

static ActMail switchR_mes[2] = {{430}, {429}};

static ActMail switchRUp_mes[2] = {{430}, {429}};

static ActMail switchRChk_mes[2] = {{430}, {429}};

static ActMail switchRUpChk_mes[2] = {{430}, {429}};

static ActMail door_mes[2] = {{430}, {429}};

static ActMail doorDown_mes[2] = {{430}, {429}};

static ActMail doorChk_mes[2] = {{430}, {429}};

static ActMail doorDownChk_mes[2] = {{430}, {429}};

static ActMail ene_mes[2] = {{430}, {429}};

static ActMail ene2_mes[2] = {{430}, {429}};

extern char *D_00639EA8;

void actSt18aEnd(void)
{
    if (D_00639EA8 != 0) {
        if (gflagChk(61) == 0) {
            gflagOn(391);
        }
    }
}

/* the shared pad-state array (op.c's PadStateSt18A): 0x58 per pad, trg at 0x4 */
/* kept local: this TU's bytes only come out with its own view of PadStateSt18A. */
/* kept local: this TU's bytes only come out with its own view of PadState, so it
   keeps one under its own name; the shared view is in ico2/common/include/typedef.h. */
typedef struct PadStateSt18A {
    int unk00;        /* 0x00 */
    int trg;          /* 0x04 */
    char unk08[0x50]; /* 0x08 */
} PadStateSt18A;

extern PadStateSt18A D_0028F8F0[];
extern int D_00639EA4;
extern int D_0063AA08;

void actSt18aIntroChk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 1000.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);

    gflagOn(55);

    D_0063AA08 = 1;

    _ACTWait(1);

    stage_SetAnimation(354, 1, 0);

    while (stage_CheckAnimationFinish(354) == 0) {
        if ((D_0028F8F0[0].trg & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            scpFadeOut(16.0f, 0, 0, 0);

            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }

            stage_SetAnimation(354, 1, -1);
            SetCameraFlag_LwsCutBack();
            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }

    lt_switch_layout(54);
    D_0063AA08 = 0;
}

extern int D_0028F4C0[];

void actSt18aSwitchLChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    int i;

    i = 0;
    while (i < (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) {
        if (scpTriggerFloorAttr(scpSearchGobj(773), 0x1000000) != 0 ||
            scpTriggerFloorAttr(scpSearchGobj(774), 0x1000000) != 0 ||
            scpTriggerFloorAttr(D_00639EA4, 0x1000000) != 0 ||
            (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x1000000) != 0)) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }

    stage_SetAnimation(121, 1, 0);

    soundSeDefPlay(1220, 0, 0, 1);

    while (stage_CheckAnimationFrame(121, 45, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (scpTriggerFloorAttr(scpSearchGobj(773), 0x1000000) != 0 ||
        scpTriggerFloorAttr(scpSearchGobj(774), 0x1000000) != 0 ||
        scpTriggerFloorAttr(D_00639EA4, 0x1000000) != 0 ||
        (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x1000000) != 0)) {
        gflagOn(58);
        FinishHint(7);
    }

    switchLChk_mes[0].func = actSt18aSwitchLUpChk;
    sub->mail = switchLChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* TU-owned .data record (VMA 0x004FB0F0..0x004FB10F, ROM 0x3FB0F0). */

void actSt18aSwitchLUpChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttrTargetMan(a0, 0x1000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(15);
    gflagOff(58);

    stage_SetAnimation(121, 1, 0x2E);
    soundSeDefPlay(1220, 0, 0, 1);

    while (stage_CheckAnimationFrame(121, 50, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupItemWithBoundary(3054.0f, 1530.0f, -3061.0f, 100.0f);

    while (stage_CheckAnimationFrame(121, 90, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    switchLUpChk_mes[0].func = actSt18aSwitchLChk;
    sub->mail = switchLUpChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt18aSwitchRChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    int i;

    i = 0;
    while (i < (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) {
        if (scpTriggerFloorAttr(scpSearchGobj(773), 0x2000000) != 0 ||
            scpTriggerFloorAttr(scpSearchGobj(774), 0x2000000) != 0 ||
            scpTriggerFloorAttr(D_00639EA4, 0x2000000) != 0 ||
            (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x2000000) != 0)) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }

    stage_SetAnimation(122, 1, 0);

    soundSeDefPlay(1220, 0, 0, 1);

    while (stage_CheckAnimationFrame(122, 45, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (scpTriggerFloorAttr(scpSearchGobj(773), 0x2000000) != 0 ||
        scpTriggerFloorAttr(scpSearchGobj(774), 0x2000000) != 0 ||
        scpTriggerFloorAttr(D_00639EA4, 0x2000000) != 0 ||
        (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x2000000) != 0)) {
        gflagOn(59);
        FinishHint(7);
    }

    switchRChk_mes[0].func = actSt18aSwitchRUpChk;
    sub->mail = switchRChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt18aSwitchRUpChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttrTargetMan(a0, 0x2000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(15);
    gflagOff(59);

    stage_SetAnimation(122, 1, 0x2E);
    soundSeDefPlay(1220, 0, 0, 1);

    while (stage_CheckAnimationFrame(122, 50, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupItemWithBoundary(1451.0f, 1530.0f, -3039.0f, 100.0f);

    while (stage_CheckAnimationFrame(122, 90, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    switchRUpChk_mes[0].func = actSt18aSwitchRChk;
    sub->mail = switchRUpChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* .sbss, owned by st18a.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, raised by the
   subthread the wait loop below spins for, and the flag actSt18aDoorChkSub
   raises when the door check is done. */
static int demoEnd;

static int doorChkDone;

void actSt18aDoorChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    int th;

    while (gflagChk(58) == 0 || gflagChk(59) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    gflagOn(60);

    th = actCreateSubThread(actSt18aDoorChkSub, 21);
    demoEnd = 0;
    doorChkDone = 0;

    while (demoEnd == 0 && ((D_0028F8F0[0].trg & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 0x24, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(123, 0, -1);

        if (doorChkDone == 0) {
            soundSeDefPlay(1222, 0, 0, 1);
        }

        scpFadeIn(3.0f);
    }

    scpWakeupEnemyAll();
    lt_switch_layout(54);

    doorChk_mes[0].func = actSt18aDoorDownChk;
    sub->mail = doorChk_mes;
    D_0063AA08 = 0;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* TU-owned .data record (VMA 0x004FB1F0..0x004FB20F, ROM 0x3FB1F0): the mail
   table actSt18aDoorDownChk hands back to the door actor. Role-named file
   static per the 2026-09-07 ruling, same shape as st17a's doorDownChk_mes. */

void actSt18aDoorDownChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    while (gflagChk(58) != 0 && gflagChk(59) != 0) {
        _ACTWait(1);
    }

    _ACTWait(15);
    gflagOff(60);

    stage_SetAnimation(124, 1, 0);

    soundSeDefPlay(1221, 0, 0, 1);
    _ACTWait(50);
    soundSeDefPlay(1222, 0, 0, 1);
    while (stage_CheckAnimationFinish(124) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    doorDownChk_mes[0].func = actSt18aDoorChk;
    sub->mail = doorDownChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt18aEnemy1_1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    Generator_Mask(scpSearchGobj(765));
    Generator_Mask(scpSearchGobj(766));

    while (gflagChk(62) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
    Generator_Call(scpSearchGobj(765));
    Generator_Call(scpSearchGobj(766));
}

void actSt18aEnemy2_1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    Generator_Mask(scpSearchGobj(766));

    while (gflagChk(64) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    Generator_Call(scpSearchGobj(766));
}

void actSt18aIntro(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(55) == 0) {
        intro_mes[0].func = actSt18aIntroChk;
        self->mail = intro_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt18aDoor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(60) == 0) {
        stage_SetAnimation(123, 0, 0);

        door_mes[0].func = actSt18aDoorChk;
        self->mail = door_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(123, 0, -1);

        doorDown_mes[0].func = actSt18aDoorDownChk;
        self->mail = doorDown_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt18aSwitchL(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(58) == 0) {
        stage_SetAnimation(121, 0, 0);

        switchL_mes[0].func = actSt18aSwitchLChk;
        self->mail = switchL_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(121, 0, 0x2D);

        switchLUp_mes[0].func = actSt18aSwitchLUpChk;
        self->mail = switchLUp_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt18aSwitchR(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(59) == 0) {
        stage_SetAnimation(122, 0, 0);

        switchR_mes[0].func = actSt18aSwitchRChk;
        self->mail = switchR_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(122, 0, 0x2D);

        switchRUp_mes[0].func = actSt18aSwitchRUpChk;
        self->mail = switchRUp_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt18aEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(61) == 0) {
        ene_mes[0].func = actSt18aEneChk;
        self->mail = ene_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt18aEnemy1_2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(62) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
    _ACTWait(30);
    Generator_Call(a0);
}

void actSt18aEne2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(63) == 0) {
        ene2_mes[0].func = actSt18aEne2Chk;
        self->mail = ene2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt18aEnemy2_2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(64) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}

void actSt18aCamera(int x)
{
    volatile int local = x;
}

void actSt18aDoorChkSub(volatile int a0)
{
    _ACTWait(60);

    stage_SetAnimation(123, 1, 0);

    if (scpTriggerFloorAttr(D_00639EA4, 0x5000000) != 0) {
        SetCameraFlag_LwsCutBack();
    }

    soundSeDefPlay(1221, 0, 0, 1);
    _ACTWait(50);
    doorChkDone = 1;
    soundSeDefPlay(1222, 0, 0, 1);
    while (stage_CheckAnimationFinish(123) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt18aEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOff(391);
    gflagOn(61);
    gflagOn(62);
}

void actSt18aEne2Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (D_00639EA8 == 0 || scpTriggerFloorAttr(scpSearchGobj(774), 0x4000000) == 0) {
        _ACTWait(1);
    }
    FinishHint(8);
    _ACTWait(300);
    gflagOn(63);
    gflagOn(64);
}
