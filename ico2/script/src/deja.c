#include "deja.h"
#include "StageManager.h"
#include "layout_texture.h"
#include "act.h"
#include "commonact.h"
#include "fightSound.h"
#include "gflag.h"
#include "script.h"
#include "Shadow.h"
#include "StageAnimation.h"
#include <libvu0.h>
#include "typedef.h"
#include "main.h"

/* actDeja installs actDejaChk as the actor's next mail handler. */

static ActMail _mes[2] = {{377}, {376}}; /* derived name */

static ActMail after_mes[2] = {{377}, {376}}; /* derived name */

/* .sbss: the demo's own end flag, raised by the handler the wait loop below
   is spinning for. */
static int demoEnd;

void actDejaDemo(GObj *volatile self);
void actDejaAfterChk(GObj *volatile self);

/* .sdata: the scene's stream handle */
struct SqEntry *deja = 0;

static const Vec16 afterChkPos = {{-1000.0f, 0.0f, -2200.0f, 1.0f}}; /* derived name */

inline void actEnemySleep(GObj *volatile self)
{
    while (1) {
        scpSleepEnemyAll();
        _ACTWait(1);
    }
}

void actDejaChk(GObj *volatile self)
{
    gflagOn(6);
    actCreateSubThread(actEnemySleep, 21);
    scpAdpcmPlayRequestFunc(15, &deja, 0, 1, 1);
    actCreateSubThread(actDejaDemo, 21);
    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }
    demoEnd = 0;
    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }
    if (demoEnd == 0 && deja != 0) {
        scpAdpcmFadeClose(deja, 128);
        deja = 0;
    }
    RequestStageChange(1, boyGObj, 0, 0.025f, 1.0f);
}

void actDejaDemo(GObj *volatile self)
{
    stgmgrNextStagePreLoadForceStageSet(exitData[stageData[stage_no].ent[0]].nextStage);
    scpPlayStart(boyGObj);
    stage_SetAnimation(487, 1, 0);
    scpPlayMot(boyGObj, 301);
    while (stage_ContinueAnimation(487, 488) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 302);
    while (stage_ContinueAnimation(488, 489) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 303);
    while (stage_ContinueAnimation(489, 490) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 304);
    while (stage_ContinueAnimation(490, 491) == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(498, 1, 0);
    scpPlayMot(boyGObj, 305);
    while (stage_ContinueAnimation(491, 492) == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(499, 1, 0);
    while (stage_ContinueAnimation(492, 493) == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(500, 1, 0);
    scpPlayMot(scpSearchGobj(2205), 702);
    scpSearchGobj(2205)->active = 1;
    while (stage_ContinueAnimation(493, 494) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 306);
    while (stage_ContinueAnimation(494, 495) == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(501, 1, 0);
    scpPlayMot(boyGObj, 307);
    scpPlayMot(scpSearchGobj(2205), 703);
    while (stage_ContinueAnimation(495, 496) == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(502, 1, 0);
    scpPlayMot(boyGObj, 308);
    scpPlayStart(scpSearchGobj(2206));
    scpPlayMot(scpSearchGobj(2206), 990);
    while (stage_ContinueAnimation(496, 497) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 309);
    scpPlayMot(scpSearchGobj(2206), 991);
    while (stage_CheckAnimationFrame(497, 125, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
}

void actDejaAfter(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(7) == 0 && gflagChk(6) != 0) {
        stage_SetAnimation(27, 0, -1);
        stage_SetAnimation(21, 0, -1);
        stage_SetAnimation(30, 0, 0);
        stage_SetAnimation(28, 0, 0);
        stage_SetAnimation(31, 0, 0);
        stage_SetAnimation(33, 0, 0);
        after_mes[0].func = actDejaAfterChk;
        act->mail = after_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(27, 0, -1);
        stage_SetAnimation(21, 0, -1);
        stage_SetAnimation(30, 0, 0);
        stage_SetAnimation(28, 0, 0);
        stage_SetAnimation(31, 0, 0);
        stage_SetAnimation(33, 0, 0);
    }
}

void actDejaAfterChk(GObj *volatile self)
{
    Vec16 target;
    Vec16 dir;

    CheckPoint();
    gflagOn(7);
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    stage_SetAnimation(503, 1, 0);
    scpPlayMot(boyGObj, 310);
    while (stage_CheckAnimationFinish(503) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpPlayMot(boyGObj, 0);
    target = afterChkPos;
    sceVu0SubVector(dir.f, target.f, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir.f);
    scpPlayEnd(boyGObj);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
    _ACTWait(60);
    if (deja != 0) {
        scpAdpcmFadeClose(deja, 80);
    }
    deja = 0;
    _ACTWait(0);
}

void actDeja(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(6) == 0) {
        lt_switch_layout(51);
        stage_SetAnimation(53, 0, 0);
        _mes[0].func = actDejaChk;
        act->mail = _mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}
