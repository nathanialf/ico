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
#include "include_asm.h"

/* actDeja installs actDejaChk as the actor's next mail handler. */

static ActMail _mes[2] = {{397}, {396}}; /* derived name */

static ActMail after_mes[2] = {{397}, {396}}; /* derived name */

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

inline void actDeja(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(6) == 0) {
        lt_switch_layout(51);
        scpBoyControlReadDisable = 1;
        scpFadeOut(255.0f, 0, 0, 0);
        stage_SetAnimation(59, 0, 0);
        _mes[0].func = actDejaChk;
        act->mail = _mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actDejaChk(GObj *volatile self)
{
    gflagOn(6);
    scpSearchGobj(2340)->active = 0;
    scpSearchGobj(2341)->active = 0;
    actCreateSubThread(actEnemySleep, 21);
    scpAdpcmPlayRequestFunc(12, &deja, 0, 1, 1);
    while (deja == 0) {
        _ACTWait(1);
    }
    scpFadeIn(6.0f);
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
        shadow_DispCancel(68, 0);
        scpAdpcmFadeCloseFunc(deja, 128);
        deja = 0;
    }
    RequestStageChange(1, boyGObj, 0, 0.025f, 1.0f);
}

void actDejaDemo(GObj *volatile self)
{
    stgmgrNextStagePreLoadForceStageSet(exitData[stageData[stage_no].ent[0]].nextStage);
    scpPlayStart(boyGObj);
    stage_SetAnimation(537, 1, 0);
    scpPlayMot(boyGObj, 292);
    while (stage_ContinueAnimation(537, 538) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 293);
    while (stage_ContinueAnimation(538, 539) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 294);
    while (stage_ContinueAnimation(539, 540) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 295);
    while (stage_ContinueAnimation(540, 541) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 296);
    _ACTWait(1);
    stage_SetAnimation(548, 1, 0);
    while (stage_CheckAnimationFrame(541, 120, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpSearchGobj(51)->active = 0;
    while (stage_ContinueAnimation(541, 542) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    stage_SetAnimation(548, -1, -2);
    stage_SetAnimation(549, 1, 0);
    while (stage_ContinueAnimation(542, 543) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(scpSearchGobj(2340), 679);
    scpSearchGobj(2340)->active = 1;
    _ACTWait(1);
    stage_SetAnimation(549, -1, -2);
    stage_SetAnimation(550, 1, 0);
    shadow_DispCancel(68, 1);
    while (stage_ContinueAnimation(543, 544) == 0) {
        _ACTWait(1);
    }
    scpSearchGobj(51)->active = 1;
    scpPlayMot(boyGObj, 297);
    _ACTWait(1);
    stage_SetAnimation(550, -1, -2);
    while (stage_ContinueAnimation(544, 545) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 298);
    scpPlayMot(scpSearchGobj(2340), 680);
    _ACTWait(1);
    stage_SetAnimation(551, 1, 0);
    while (stage_ContinueAnimation(545, 546) == 0) {
        _ACTWait(1);
    }
    scpSearchGobj(2341)->active = 1;
    scpPlayMot(boyGObj, 299);
    scpPlayStart(scpSearchGobj(2341));
    scpPlayMot(scpSearchGobj(2341), 913);
    _ACTWait(1);
    stage_SetAnimation(551, -1, -2);
    stage_SetAnimation(552, 1, 0);
    while (stage_ContinueAnimation(546, 547) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 300);
    scpPlayMot(scpSearchGobj(2341), 914);
    shadow_DispCancel(68, 0);
    while (stage_CheckAnimationFrame(547, 125, 0) == 0) {
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

    ScpCallCameraOff();
    if (gflagChk(7) == 0 && gflagChk(6) != 0) {
        stage_SetAnimation(31, 0, -1);
        stage_SetAnimation(25, 0, -1);
        stage_SetAnimation(34, 0, 0);
        stage_SetAnimation(32, 0, 0);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(37, 0, 0);
        after_mes[0].func = actDejaAfterChk;
        act->mail = after_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(31, 0, -1);
        stage_SetAnimation(25, 0, -1);
        stage_SetAnimation(34, 0, 0);
        stage_SetAnimation(32, 0, 0);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(37, 0, 0);
    }
}

INCLUDE_ASM(actDejaAfterChk);
