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

#ifdef VERSION_NTSC
static ActMail _mes[2] = {{397}, {396}}; /* derived name */

static ActMail after_mes[2] = {{397}, {396}}; /* derived name */
#else
#ifdef VERSION_AUG6
static ActMail _mes[2] = {{393}, {392}}; /* derived name */

static ActMail after_mes[2] = {{393}, {392}}; /* derived name */
#else
#ifdef VERSION_JUN26
static ActMail _mes[2] = {{377}, {376}}; /* derived name */

static ActMail after_mes[2] = {{377}, {376}}; /* derived name */
#else
static ActMail _mes[2] = {{430}, {429}}; /* derived name */

static ActMail after_mes[2] = {{430}, {429}}; /* derived name */
#endif
#endif
#endif

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

#ifndef VERSION_JUN26
inline void actDeja(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(6) == 0) {
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
        lt_switch_layout(51);
        scpBoyControlReadDisable = 1;
        scpFadeOut(255.0f, 0, 0, 0);
        stage_SetAnimation(59, 0, 0);
        _mes[0].func = actDejaChk;
        act->mail = _mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 397);
#endif
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        lt_switch_layout(52);
#else
        lt_switch_layout(55);
#endif
        scpBoyControlReadDisable = 1;
        scpFadeOut(255.0f, 0, 0, 0);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(68, 0, 0);
#else
        stage_SetAnimation(72, 0, 0);
#endif
        _mes[0].func = actDejaChk;
        act->mail = _mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}
#endif

void actDejaChk(GObj *volatile self)
{
    gflagOn(6);
#ifdef VERSION_JUN26
    actCreateSubThread(actEnemySleep, 21);
    scpAdpcmPlayRequestFunc(15, &deja, 0, 1, 1);
#else
#ifdef VERSION_NTSC
    scpSearchGobj(2340)->active = 0;
    scpSearchGobj(2341)->active = 0;
#else
#ifdef VERSION_AUG6
    scpSearchGobj(2311)->active = 0;
    scpSearchGobj(2312)->active = 0;
#else
    scpSearchGobj(2548)->active = 0;
    scpSearchGobj(2549)->active = 0;
#endif
#endif
    actCreateSubThread(actEnemySleep, 21);
    scpAdpcmPlayRequestFunc(12, &deja, 0, 1, 1);
    while (deja == 0) {
        _ACTWait(1);
    }
    scpFadeIn(6.0f);
#endif
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
#ifdef VERSION_NTSC
        shadow_DispCancel(68, 0);
        scpAdpcmFadeClose(deja, 128);
#else
#ifdef VERSION_AUG6
        shadow_DispCancel(67, 0);
        scpAdpcmFadeClose(deja, 128);
#else
#ifdef VERSION_JUN26
        scpAdpcmFadeClose(deja, 128);
#else
        shadow_DispCancel(74, 0);
        scpAdpcmFadeCloseFunc(&deja, 128);
#endif
#endif
#endif
        deja = 0;
    }
    RequestStageChange(1, boyGObj, 0, 0.025f, 1.0f);
}

#ifdef VERSION_NTSC
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
#else
#ifdef VERSION_JUN26
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
#else
void actDejaDemo(GObj *volatile self)
{
    stgmgrNextStagePreLoadForceStageSet(exitData[stageData[stage_no].ent[0]].nextStage);
    scpPlayStart(boyGObj);
#ifdef VERSION_AUG6
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
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(604, 1, 0);
#else
    stage_SetAnimation(608, 1, 0);
#endif
    scpPlayMot(boyGObj, 298);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(604, 605) == 0) {
#else
    while (stage_ContinueAnimation(608, 609) == 0) {
#endif
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 299);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(605, 606) == 0) {
#else
    while (stage_ContinueAnimation(609, 610) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 300);
#ifdef VERSION_AUG6
    scpPlayMot(scpSearchGobj(2312), 916);
    shadow_DispCancel(67, 0);
    while (stage_CheckAnimationFrame(546, 125, 0) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(606, 607) == 0) {
#else
    while (stage_ContinueAnimation(610, 611) == 0) {
#endif
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 301);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(607, 608) == 0) {
#else
    while (stage_ContinueAnimation(611, 612) == 0) {
#endif
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 302);
    _ACTWait(1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(615, 1, 0);
    while (stage_CheckAnimationFrame(608, 120, 0) == 0) {
#else
    stage_SetAnimation(619, 1, 0);
    while (stage_CheckAnimationFrame(612, 120, 0) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    scpSearchGobj(54)->active = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(608, 609) == 0) {
#else
    while (stage_ContinueAnimation(612, 613) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(615, -1, -2);
    stage_SetAnimation(616, 1, 0);
    while (stage_ContinueAnimation(609, 610) == 0) {
#else
    stage_SetAnimation(619, -1, -2);
    stage_SetAnimation(620, 1, 0);
    while (stage_ContinueAnimation(613, 614) == 0) {
#endif
        _ACTWait(1);
    }
    scpPlayMot(scpSearchGobj(2548), 724);
    scpSearchGobj(2548)->active = 1;
    _ACTWait(1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(616, -1, -2);
    stage_SetAnimation(617, 1, 0);
#else
    stage_SetAnimation(620, -1, -2);
    stage_SetAnimation(621, 1, 0);
#endif
    shadow_DispCancel(74, 1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(610, 611) == 0) {
#else
    while (stage_ContinueAnimation(614, 615) == 0) {
#endif
        _ACTWait(1);
    }
    scpSearchGobj(54)->active = 1;
    scpPlayMot(boyGObj, 303);
    _ACTWait(1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(617, -1, -2);
    while (stage_ContinueAnimation(611, 612) == 0) {
#else
    stage_SetAnimation(621, -1, -2);
    while (stage_ContinueAnimation(615, 616) == 0) {
#endif
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 304);
    scpPlayMot(scpSearchGobj(2548), 725);
    _ACTWait(1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(618, 1, 0);
    while (stage_ContinueAnimation(612, 613) == 0) {
#else
    stage_SetAnimation(622, 1, 0);
    while (stage_ContinueAnimation(616, 617) == 0) {
#endif
        _ACTWait(1);
    }
    scpSearchGobj(2549)->active = 1;
    scpPlayMot(boyGObj, 305);
    scpPlayStart(scpSearchGobj(2549));
    scpPlayMot(scpSearchGobj(2549), 962);
    _ACTWait(1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(618, -1, -2);
    stage_SetAnimation(619, 1, 0);
    while (stage_ContinueAnimation(613, 614) == 0) {
#else
    stage_SetAnimation(622, -1, -2);
    stage_SetAnimation(623, 1, 0);
    while (stage_ContinueAnimation(617, 618) == 0) {
#endif
        _ACTWait(1);
    }
    scpPlayMot(boyGObj, 306);
    scpPlayMot(scpSearchGobj(2549), 963);
    shadow_DispCancel(74, 0);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(614, 125, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(618, 125, 0) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
}
#endif
#endif

void actDejaAfter(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

#ifdef VERSION_JUN26
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
#else
    ScpCallCameraOff();
    if (gflagChk(7) == 0 && gflagChk(6) != 0) {
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
        stage_SetAnimation(31, 0, -1);
        stage_SetAnimation(25, 0, -1);
        stage_SetAnimation(34, 0, 0);
        stage_SetAnimation(32, 0, 0);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(37, 0, 0);
        after_mes[0].func = actDejaAfterChk;
        act->mail = after_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 397);
#endif
        _ACTWait(0);
    } else {
        stage_SetAnimation(31, 0, -1);
        stage_SetAnimation(25, 0, -1);
        stage_SetAnimation(34, 0, 0);
        stage_SetAnimation(32, 0, 0);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(37, 0, 0);
#else
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(26, 0, -1);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(33, 0, 0);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);
        after_mes[0].func = actDejaAfterChk;
        act->mail = after_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(26, 0, -1);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(33, 0, 0);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);
#endif
#endif
    }
}

#ifdef VERSION_NTSC
void actDejaAfterChk(GObj *volatile self)
{
    Vec16 target;
    Vec16 dir;

    CheckPoint();
    gflagOn(7);
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    stage_SetAnimation(553, 1, 0);
    scpPlayMot(boyGObj, 301);
    while (stage_CheckAnimationFinish(553) == 0) {
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
#else
void actDejaAfterChk(GObj *volatile self)
{
    Vec16 target;
    Vec16 dir;

    CheckPoint();
    gflagOn(7);
#ifdef VERSION_AUG6
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    stage_SetAnimation(552, 1, 0);
    scpPlayMot(boyGObj, 301);
    while (stage_CheckAnimationFinish(552) == 0) {
#else
#ifdef VERSION_JUN26
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    stage_SetAnimation(503, 1, 0);
    scpPlayMot(boyGObj, 310);
    while (stage_CheckAnimationFinish(503) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(620, 1, 0);
#else
    stage_SetAnimation(624, 1, 0);
#endif
    scpPlayMot(boyGObj, 307);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(620) == 0) {
#else
    while (stage_CheckAnimationFinish(624) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    scpPlayMot(boyGObj, 0);
    target = afterChkPos;
    sceVu0SubVector(dir.f, target.f, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir.f);
    scpPlayEnd(boyGObj);
    scpBoyControlReadDisable = 0;
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    lt_switch_layout(50);
    _ACTWait(60);
    if (deja != 0) {
        scpAdpcmFadeClose(deja, 80);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    _ACTWait(60);
    if (deja != 0) {
        scpAdpcmFadeCloseFunc(&deja, 80);
#endif
    }
    deja = 0;
    _ACTWait(0);
}
#endif

#ifdef VERSION_JUN26
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
#endif
