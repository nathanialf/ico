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

static ActMail _mes[2] = {{393}, {392}}; /* derived name */

static ActMail after_mes[2] = {{393}, {392}}; /* derived name */

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
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

void actDejaChk(GObj *volatile self)
{
    gflagOn(6);
    scpSearchGobj(2311)->active = 0;
    scpSearchGobj(2312)->active = 0;
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
        shadow_DispCancel(67, 0);
        scpAdpcmFadeClose(deja, 128);
        deja = 0;
    }
    RequestStageChange(1, boyGObj, 0, 0.025f, 1.0f);
}

void actDejaDemo(GObj *volatile self)
{
    stgmgrNextStagePreLoadForceStageSet(exitData[stageData[stage_no].ent[0]].nextStage);
    scpPlayStart(boyGObj);
    stage_SetAnimation(536, 1, 0);
    scpPlayMot(boyGObj, 292);
    while (stage_ContinueAnimation(536, 537) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 293);
    while (stage_ContinueAnimation(537, 538) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 294);
    while (stage_ContinueAnimation(538, 539) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 295);
    while (stage_ContinueAnimation(539, 540) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 296);
    _ACTWait(1);
    stage_SetAnimation(547, 1, 0);
    while (stage_CheckAnimationFrame(540, 120, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpSearchGobj(50)->active = 0;
    while (stage_ContinueAnimation(540, 541) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    stage_SetAnimation(547, -1, -2);
    stage_SetAnimation(548, 1, 0);
    while (stage_ContinueAnimation(541, 542) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(scpSearchGobj(2311), 681);
    scpSearchGobj(2311)->active = 1;
    _ACTWait(1);
    stage_SetAnimation(548, -1, -2);
    stage_SetAnimation(549, 1, 0);
    shadow_DispCancel(67, 1);
    while (stage_ContinueAnimation(542, 543) == 0) {
        _ACTWait(1);
    }
    scpSearchGobj(50)->active = 1;
    scpPlayMot(boyGObj, 297);
    _ACTWait(1);
    stage_SetAnimation(549, -1, -2);
    while (stage_ContinueAnimation(543, 544) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 298);
    scpPlayMot(scpSearchGobj(2311), 682);
    _ACTWait(1);
    stage_SetAnimation(550, 1, 0);
    while (stage_ContinueAnimation(544, 545) == 0) {
        _ACTWait(1);
    }
    scpSearchGobj(2312)->active = 1;
    scpPlayMot(boyGObj, 299);
    scpPlayStart(scpSearchGobj(2312));
    scpPlayMot(scpSearchGobj(2312), 915);
    _ACTWait(1);
    stage_SetAnimation(550, -1, -2);
    stage_SetAnimation(551, 1, 0);
    while (stage_ContinueAnimation(545, 546) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 300);
    scpPlayMot(scpSearchGobj(2312), 916);
    shadow_DispCancel(67, 0);
    while (stage_CheckAnimationFrame(546, 125, 0) == 0) {
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
        ACTSendMailCorrect(self, 393);
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

void actDejaAfterChk(GObj *volatile self)
{
    Vec16 target;
    Vec16 dir;

    CheckPoint();
    gflagOn(7);
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    stage_SetAnimation(552, 1, 0);
    scpPlayMot(boyGObj, 301);
    while (stage_CheckAnimationFinish(552) == 0) {
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
