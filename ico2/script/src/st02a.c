#include "st02a.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "way_llf.h"
#include "camera-root.h"
#include "generator.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "box.h"
#include "matrixDrive.h"
#include "motionManager2.h"
#include "particleLayout.h"
#include "pool.h"
#include "typedef.h"
#include "main.h"

#ifdef VERSION_JUN26
#include "act-game.h"
#include <libvu0.h>
#include "script.h"
#else
#include "script.h"

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
static void actSt02aFenceOpenSub(GObj *volatile self);
#endif
#endif

/* .data: one mail record per posting site. Word 0 of each entry is the mail id
 * the entry answers (430 the actor post, 429 the trailing entry); .func is
 * filled in at run time before the post, except in the two main-mail records,
 * which answer 406 and 407 with their switch threads. Each record is named for
 * the thread that owns and posts it; where one thread owns two, for the
 * watcher it installs. */
void actSt02aFenceSwitch(GObj *volatile self);
void actSt02aGondolaSwitch(GObj *volatile self);

#ifdef VERSION_JUN26
static ActMail door_down_start_mail[2] = {{377}, {376}}; /* derived name */

static ActMail door_up_start_mail[2] = {{377}, {376}}; /* derived name */

static ActMail door_up_chk_mail[2] = {{377}, {376}}; /* derived name */

static ActMail door_down_chk_mail[2] = {{377}, {376}}; /* derived name */

static ActMail fence_main_mail[2] = {{356, actSt02aFenceSwitch}, {376}}; /* derived name */

static ActMail fence_mail[2] = {{377}, {376}}; /* derived name */

static ActMail fence_switch_mail[2] = {{377}, {376}}; /* derived name */

static ActMail waterfall_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gondola_main_mail[2] = {{357, actSt02aGondolaSwitch}, {376}}; /* derived name */

static ActMail gondola_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gondola_switch_down_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gondola_switch_up_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gondola_up_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gondola_down_mail[2] = {{377}, {376}}; /* derived name */

static ActMail girl_jump_mail[2] = {{377}, {376}}; /* derived name */

static ActMail ene_mail[2] = {{377}, {376}}; /* derived name */

static ActMail way_off_start_mail[2] = {{377}, {376}}; /* derived name */

static ActMail way_on_start_mail[2] = {{377}, {376}}; /* derived name */

static ActMail way_on_chk_mail[2] = {{377}, {376}}; /* derived name */

static ActMail way_off_chk_mail[2] = {{377}, {376}}; /* derived name */

void actSt02aInit(void)
{
    if (gflagChk(102) == 0) {
        SetWayGroupActive(26, 0);
        stage_SetAnimation(76, 0, 0);
    } else {
        stage_SetAnimation(76, 0, -1);
    }

    if (gflagChk(104) == 0) {
        stage_SetAnimation(78, 0, 0);
    } else {
        stage_SetAnimation(78, 0, -1);
    }
}
#else
#ifdef VERSION_NTSC
static ActMail door_down_start_mail[2] = {{397}, {396}}; /* derived name */

static ActMail door_up_start_mail[2] = {{397}, {396}}; /* derived name */

static ActMail door_up_chk_mail[2] = {{397}, {396}}; /* derived name */

static ActMail door_down_chk_mail[2] = {{397}, {396}}; /* derived name */

static ActMail fence_main_mail[2] = {{376, actSt02aFenceSwitch}, {396}}; /* derived name */

static ActMail fence_mail[2] = {{397}, {396}}; /* derived name */

static ActMail fence_switch_mail[2] = {{397}, {396}}; /* derived name */

static ActMail waterfall_mail[2] = {{397}, {396}}; /* derived name */

static ActMail gondola_main_mail[2] = {{377, actSt02aGondolaSwitch}, {396}}; /* derived name */

static ActMail gondola_mail[2] = {{397}, {396}}; /* derived name */

static ActMail gondola_switch_down_mail[2] = {{397}, {396}}; /* derived name */

static ActMail gondola_switch_up_mail[2] = {{397}, {396}}; /* derived name */

static ActMail gondola_up_mail[2] = {{397}, {396}}; /* derived name */

static ActMail gondola_down_mail[2] = {{397}, {396}}; /* derived name */

static ActMail ene_mail[2] = {{397}, {396}}; /* derived name */

static ActMail way_off_start_mail[2] = {{397}, {396}}; /* derived name */

static ActMail way_on_start_mail[2] = {{397}, {396}}; /* derived name */

static ActMail way_on_mail[2] = {{397}, {396}}; /* derived name */

static ActMail way_off_mail[2] = {{397}, {396}}; /* derived name */

static ActMail taki_way_mail[2] = {{397}, {396}}; /* derived name */

static ActMail taki_on_mail[2] = {{397}, {396}}; /* derived name */

static ActMail taki_off_mail[2] = {{397}, {396}}; /* derived name */

static ActMail secret_item_mail[2] = {{397}, {396}}; /* derived name */

void actSt02aInit(void)
{
    if (gflagChk(105) == 0) {
        SetWayGroupActive(26, 0);
        stage_SetAnimation(85, 0, 0);
    } else {
        stage_SetAnimation(85, 0, -1);
    }
}
#else
#ifdef VERSION_AUG6
static ActMail door_down_start_mail[2] = {{393}, {392}}; /* derived name */

static ActMail door_up_start_mail[2] = {{393}, {392}}; /* derived name */

static ActMail door_up_chk_mail[2] = {{393}, {392}}; /* derived name */

static ActMail door_down_chk_mail[2] = {{393}, {392}}; /* derived name */

static ActMail fence_main_mail[2] = {{372, actSt02aFenceSwitch}, {392}}; /* derived name */

static ActMail fence_mail[2] = {{393}, {392}}; /* derived name */

static ActMail fence_switch_mail[2] = {{393}, {392}}; /* derived name */

static ActMail waterfall_mail[2] = {{393}, {392}}; /* derived name */

static ActMail gondola_main_mail[2] = {{373, actSt02aGondolaSwitch}, {392}}; /* derived name */

static ActMail gondola_mail[2] = {{393}, {392}}; /* derived name */

static ActMail gondola_switch_down_mail[2] = {{393}, {392}}; /* derived name */

static ActMail gondola_switch_up_mail[2] = {{393}, {392}}; /* derived name */

static ActMail gondola_up_mail[2] = {{393}, {392}}; /* derived name */

static ActMail gondola_down_mail[2] = {{393}, {392}}; /* derived name */

static ActMail ene_mail[2] = {{393}, {392}}; /* derived name */

static ActMail way_off_start_mail[2] = {{393}, {392}}; /* derived name */

static ActMail way_on_start_mail[2] = {{393}, {392}}; /* derived name */

static ActMail way_on_mail[2] = {{393}, {392}}; /* derived name */

static ActMail way_off_mail[2] = {{393}, {392}}; /* derived name */

static ActMail taki_way_mail[2] = {{393}, {392}}; /* derived name */

/* The two waterfall-way records are named for the watcher each posts:
 * TakiWayOnChk posts taki_off_mail, TakiWayOffChk posts taki_on_mail.  The
 * name decides the order gcse hoists the record's address against the
 * watcher's, so it shows in the words (s1/s0). */
static ActMail taki_off_mail[2] = {{393}, {392}}; /* derived name */

static ActMail taki_on_mail[2] = {{393}, {392}}; /* derived name */

static ActMail secret_item_mail[2] = {{393}, {392}}; /* derived name */
#else
static ActMail door_down_start_mail[2] = {{430}, {429}}; /* derived name */

static ActMail door_up_start_mail[2] = {{430}, {429}}; /* derived name */

static ActMail door_up_chk_mail[2] = {{430}, {429}}; /* derived name */

static ActMail door_down_chk_mail[2] = {{430}, {429}}; /* derived name */

static ActMail fence_main_mail[2] = {{406, actSt02aFenceSwitch}, {429}}; /* derived name */

static ActMail fence_mail[2] = {{430}, {429}}; /* derived name */

static ActMail fence_switch_mail[2] = {{430}, {429}}; /* derived name */

static ActMail waterfall_mail[2] = {{430}, {429}}; /* derived name */

static ActMail gondola_main_mail[2] = {{407, actSt02aGondolaSwitch}, {429}}; /* derived name */

static ActMail gondola_mail[2] = {{430}, {429}}; /* derived name */

static ActMail gondola_switch_down_mail[2] = {{430}, {429}}; /* derived name */

static ActMail gondola_switch_up_mail[2] = {{430}, {429}}; /* derived name */

static ActMail gondola_up_mail[2] = {{430}, {429}}; /* derived name */

static ActMail gondola_down_mail[2] = {{430}, {429}}; /* derived name */

static ActMail ene_mail[2] = {{430}, {429}}; /* derived name */

static ActMail way_off_start_mail[2] = {{430}, {429}}; /* derived name */

static ActMail way_on_start_mail[2] = {{430}, {429}}; /* derived name */

static ActMail way_on_mail[2] = {{430}, {429}}; /* derived name */

static ActMail way_off_mail[2] = {{430}, {429}}; /* derived name */

static ActMail taki_way_mail[2] = {{430}, {429}}; /* derived name */

static ActMail taki_on_mail[2] = {{430}, {429}}; /* derived name */

static ActMail taki_off_mail[2] = {{430}, {429}}; /* derived name */

static ActMail secret_item_mail[2] = {{430}, {429}}; /* derived name */
#endif

void actSt02aInit(void)
{
#ifdef VERSION_AUG6
    if (gflagChk(105) == 0) {
        SetWayGroupActive(26, 0);
        stage_SetAnimation(84, 0, 0);
    } else {
        stage_SetAnimation(84, 0, -1);
#else
    if (gflagChk(118) == 0) {
        SetWayGroupActive(26, 0);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(95, 0, 0);
#else
        stage_SetAnimation(99, 0, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(95, 0, -1);
#else
        stage_SetAnimation(99, 0, -1);
#endif
#endif
    }
}
#endif

void actSt02aDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);
    if (scpTriggerBall(self, boyGObj, 200.0f) != 0 ||
        (girlGObj != 0 && scpTriggerBall(self, girlGObj, 400.0f) != 0)) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(94, 0, 0);
#else
#ifdef VERSION_NTSC
        stage_SetAnimation(84, 0, 0);
#else
#ifdef VERSION_AUG6
        stage_SetAnimation(83, 0, 0);
#else
        stage_SetAnimation(98, 0, 0);
#endif
#endif
#endif
        _ACTWait(60);
        door_down_start_mail[0].func = actSt02aDoorDownChk;
        act->mail = door_down_start_mail;
#ifdef VERSION_NTSC
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        stage_SetAnimation(83, 0, 0);
        door_up_start_mail[0].func = actSt02aDoorUpChk;
        act->mail = door_up_start_mail;
        ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        stage_SetAnimation(82, 0, 0);
        door_up_start_mail[0].func = actSt02aDoorUpChk;
        act->mail = door_up_start_mail;
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(93, 0, 0);
#else
        stage_SetAnimation(97, 0, 0);
#endif
        door_up_start_mail[0].func = actSt02aDoorUpChk;
        act->mail = door_up_start_mail;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}
#endif

/* The two-part door's SE position, copied into the local the sound call reads. */
static const ConstVec doorSePos = {{-1823.0f, -1174.0f, 2429.0f, 0.0f}}; /* derived name */

/* The door's two effect positions; the up sequence plays them in this order and
 * the down sequence in the other.  ico2/script/src/st08b.c carries the same two
 * points for its own door. */
static const ConstVec doorUpEffectPos = {{-505.0f, -1200.0f, -5671.0f, 1.0f}}; /* derived name */

static const ConstVec doorUpEffect2Pos = {{-505.0f, -1447.0f, -5671.0f, 1.0f}}; /* derived name */

/* The two boundary points the boy's splash check tests against. */
static const ConstVec boySplashPos[2] = {{{840.0f, 235.0f, 560.0f, 1.0f}},
                                         {{740.0f, 235.0f, 560.0f, 1.0f}}};

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
/* The waterfall's reflection mesh and the layout quad it is stretched over:
 * the quad drops from y 280 to y 0, which is the falling water (August has no
 * pool mesh).  The value at offset 0x1C is a hardware field. */
static const PoolMesh fallReflactionMesh = {40, 20, 0, 0, 0, 0, 0, 0x60687080}; /* derived name */

#ifdef VERSION_JUN26
static const PoolMeshQuad fallReflactionQuad = {
    { {650.0f, 280.0f, 550.0f, 1.0f},
      {650.0f, 0.0f, 700.0f, 1.0f},
      {900.0f, 280.0f, 550.0f, 1.0f},
      {900.0f, 0.0f, 700.0f, 1.0f} }}; /* derived name */

/* The girl's jump: the SE position, the point she turns to before she jumps,
 * and the seven points of the effect sequence. */
static const ConstVec girlJumpSePos = {{892.0f, 777.0f, 174.0f, 0.0f}}; /* derived name */

static const ConstVec girlJumpPos = {{1400.0f, 0.0f, 175.0f, 1.0f}}; /* derived name */

static const ConstVec girlJumpEffectPos = {{3645.0f, -1966.0f, 1122.0f, 1.0f}}; /* derived name */

static const ConstVec girlJumpEffect2Pos = {{3753.0f, -1936.0f, 1090.0f, 1.0f}}; /* derived name */

static const ConstVec girlJumpEffect3Pos = {{3605.0f, -1866.0f, 1150.0f, 1.0f}}; /* derived name */

static const ConstVec girlJumpEffect4Pos = {{3759.0f, -1666.0f, 1152.0f, 1.0f}}; /* derived name */

static const ConstVec girlJumpEffect5Pos = {{3305.0f, -1566.0f, 1082.0f, 1.0f}}; /* derived name */

static const ConstVec girlJumpEffect6Pos = {{3545.0f, -1466.0f, 1120.0f, 1.0f}}; /* derived name */

static const ConstVec girlJumpEffect7Pos = {{3655.0f, -1066.0f, 1477.0f, 1.0f}}; /* derived name */
#else
static const PoolMeshQuad fallReflactionQuad = {
    { {650.0f, 280.0f, 550.0f, 1.0f},
      {650.0f, 0.0f, 700.0f, 1.0f},
      {900.0f, 280.0f, 550.0f, 1.0f},
      {900.0f, 0.0f, 700.0f, 1.0f} }}; /* derived name */
#endif
#else
/* The waterfall's two reflection meshes and the two layout quads they are
 * stretched over: the first quad drops from y 280 to y 0, which is the falling
 * water, and the second is flat at y 0, which is the pool below it.  The value
 * at offset 0x1C is a hardware field. */
static const PoolMesh fallReflactionMesh = {30, 20, 0, 0, 0, 0, 0, 0x60687080}; /* derived name */

static const PoolMesh poolReflactionMesh = {10, 10, 0, 0, 0, 0, 0, 0x60687080}; /* derived name */

static const PoolMeshQuad fallReflactionQuad = {{{650.0f, 280.0f, 550.0f, 1.0f},
                                                 {650.0f, 0.0f, 700.0f, 1.0f},
                                                 {920.0f, 280.0f, 550.0f, 1.0f},
                                                 {920.0f, 0.0f, 700.0f, 1.0f}}};

static const PoolMeshQuad poolReflactionQuad = {{{650.0f, 0.0f, 700.0f, 1.0f},
                                                 {650.0f, 0.0f, 1200.0f, 1.0f},
                                                 {920.0f, 0.0f, 700.0f, 1.0f},
                                                 {920.0f, 0.0f, 1200.0f, 1.0f}}};
#endif

#ifdef VERSION_NTSC
void actSt02aDoorUpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    ConstVec pos;
    int h;

    while (scpTriggerFloorAttrTargetMan(self, 0x1000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(15);
    actCreateSubThread(actSt02aDoorUpEffect, 21);
    scpWakeupItemWithBoundary(-1827.0f, -1072.0f, 2285.0f, 100.0f);
    stage_SetAnimation(83, 1, 0);
    pos = doorSePos;
    soundSeDefPlay(1196, 0, pos.f, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1197, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1198, 0, pos.f, 1);
    while (stage_CheckAnimationFinish(83) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    door_up_chk_mail[0].func = actSt02aDoorDownChk;
    sub->mail = door_up_chk_mail;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt02aDoorDownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    ConstVec pos;
    int h;

    while (scpTriggerFloorAttrTargetMan(self, 0x1000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(15);
    actCreateSubThread(actSt02aDoorDownEffect, 21);
    scpWakeupItemWithBoundary(-1827.0f, -1072.0f, 2285.0f, 100.0f);
    stage_SetAnimation(84, 1, 0);
    pos = doorSePos;
    soundSeDefPlay(1196, 0, pos.f, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1197, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1198, 0, pos.f, 1);
    while (stage_CheckAnimationFinish(84) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    door_down_chk_mail[0].func = actSt02aDoorUpChk;
    sub->mail = door_down_chk_mail;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

/* .sdata */
SqEntry *st02a_fence = 0;
#else
void actSt02aDoorUpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    ConstVec pos;
    int h;

    while (scpTriggerFloorAttrTargetMan(self, 0x1000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(15);
    actCreateSubThread(actSt02aDoorUpEffect, 21);
    scpWakeupItemWithBoundary(-1827.0f, -1072.0f, 2285.0f, 100.0f);
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
    stage_SetAnimation(74, 1, 0);
    pos = doorSePos;
    soundSeDefPlay(1170, 0, pos.f, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1171, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1172, 0, pos.f, 1);
    while (stage_CheckAnimationFinish(74) == 0) {
#else
    stage_SetAnimation(82, 1, 0);
    pos = doorSePos;
    soundSeDefPlay(1196, 0, pos.f, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1197, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1198, 0, pos.f, 1);
    while (stage_CheckAnimationFinish(82) == 0) {
#endif
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(93, 1, 0);
#else
    stage_SetAnimation(97, 1, 0);
#endif
    pos = doorSePos;
    soundSeDefPlay(1220, 0, pos.f, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1221, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1222, 0, pos.f, 1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(93) == 0) {
#else
    while (stage_CheckAnimationFinish(97) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    door_up_chk_mail[0].func = actSt02aDoorDownChk;
    sub->mail = door_up_chk_mail;
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
    ACTSendMailCorrect(self, 377);
#else
    ACTSendMailCorrect(self, 393);
#endif
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actSt02aDoorDownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    ConstVec pos;
    int h;

    while (scpTriggerFloorAttrTargetMan(self, 0x1000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(15);
    actCreateSubThread(actSt02aDoorDownEffect, 21);
    scpWakeupItemWithBoundary(-1827.0f, -1072.0f, 2285.0f, 100.0f);
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
    stage_SetAnimation(75, 1, 0);
    pos = doorSePos;
    soundSeDefPlay(1170, 0, pos.f, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1171, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1172, 0, pos.f, 1);
    while (stage_CheckAnimationFinish(75) == 0) {
#else
    stage_SetAnimation(83, 1, 0);
    pos = doorSePos;
    soundSeDefPlay(1196, 0, pos.f, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1197, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1198, 0, pos.f, 1);
    while (stage_CheckAnimationFinish(83) == 0) {
#endif
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(94, 1, 0);
#else
    stage_SetAnimation(98, 1, 0);
#endif
    pos = doorSePos;
    soundSeDefPlay(1220, 0, pos.f, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1221, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1222, 0, pos.f, 1);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(94) == 0) {
#else
    while (stage_CheckAnimationFinish(98) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    door_down_chk_mail[0].func = actSt02aDoorUpChk;
    sub->mail = door_down_chk_mail;
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
    ACTSendMailCorrect(self, 377);
#else
    ACTSendMailCorrect(self, 393);
#endif
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

/* .sdata */
SqEntry *st02a_fence = 0;

#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
/* .sbss: the demo's own end flag, raised by the subthread the wait loop below
   spins for. */
static int demoEnd;

void actSt02aFenceOpen(GObj *volatile self)
{
    GProc *th;

    scpSleepEnemyAll();
    gflagOn(118);
    scpAdpcmPlayRequestFunc(96, &st02a_fence, 1, 1, 1);
    th = actCreateSubThread(actSt02aFenceOpenSub, 21);
    demoEnd = 0;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(&th->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        while (st02a_fence == 0) {
            _ACTWait(1);
        }
        scpAdpcmFadeCloseFunc(&st02a_fence, 512);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(95, 0, -1);
        stage_SetAnimation(96, 0, -1);
#else
        stage_SetAnimation(99, 0, -1);
        stage_SetAnimation(100, 0, -1);
#endif
        SetCameraFlag_GamecamCutBack();
        scpFadeIn(8.0f);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }
    SetWayGroupActive(26, 1);
    scpBoyControlReadDisable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    scpWakeupEnemyAll();
}
#endif
#endif

void actSt02WaterFallBoySplashCheck(GObj *volatile self)
{
    ConstVec buf[2];
    ConstVec buf2;
    int idx;
    if (boyGObj == 0)
        return;
    buf[0].d[0] = boySplashPos[0].d[0];
    buf[0].d[1] = boySplashPos[0].d[1];
    buf[1].d[0] = boySplashPos[1].d[0];
    buf[1].d[1] = boySplashPos[1].d[1];
    for (;;) {
        idx = GetSkeltonFocusNode(boyGObj, 35);
        CopyVector(buf2.f, (float *)(GOBJ_SUB(boyGObj)->nodeMtx + (idx << 6) + 48));
#ifdef VERSION_JUN26
        if (scpTriggerPosBall(buf[0].f, buf2.f, 100.0f))
            scpEffectStart(buf2.f, 46);
#else
        if (scpTriggerPosBall(buf[0].f, buf2.f, 100.0f))
            scpEffectStart(buf2.f, 47);
#endif
        _ACTWait(10);
        idx = GetSkeltonFocusNode(boyGObj, 35);
        CopyVector(buf2.f, (float *)(GOBJ_SUB(boyGObj)->nodeMtx + (idx << 6) + 48));
#ifdef VERSION_JUN26
        if (scpTriggerPosBall(buf[1].f, buf2.f, 100.0f))
            scpEffectStart(buf2.f, 46);
        _ACTWait(10);
    }
#else
        if (scpTriggerPosBall(buf[1].f, buf2.f, 100.0f))
            scpEffectStart(buf2.f, 47);
        _ACTWait(10);
    }
}

#ifndef VERSION_AUG6
void actSt02aWaterFallReflactionEffect(GObj *volatile self)
{
    PoolMesh m0 = fallReflactionMesh;
    PoolMesh m1 = poolReflactionMesh;
    PoolMeshQuad q0 = fallReflactionQuad;
    PoolMeshQuad q1 = poolReflactionQuad;

    InitLayoutedPoolReflactionMesh(&m0, &q0);
    InitLayoutedPoolReflactionMesh(&m1, &q1);
    for (;;) {
        SetLayoutedPoolReflactionMesh(&m0);
        DispLimitedPoolReflactionMesh(&m0);
        SetLayoutedPoolReflactionMesh(&m1);
        DispLimitedPoolReflactionMesh(&m1);
        _ACTWait(1);
    }
}
#endif

void actSt02aWaterFallChk(GObj *volatile self)
{
    Act *act = GOBJ_ACT(boyGObj);

#ifdef VERSION_NTSC
    act->flags20.ll &= ~0x4000000LL;
    scpSearchGobj(1562)->active = 1;
    scpSearchGobj(1558)->active = 0;
    scpSearchGobj(1567)->active = 0;
    scpSearchGobj(1568)->active = 0;
    scpSearchGobj(1571)->active = 0;
    DeleteParticleLayout(scpSearchGobj(1600));
    DeleteParticleLayout(scpSearchGobj(1601));
    DeleteParticleLayout(scpSearchGobj(1602));
    DeleteParticleLayout(scpSearchGobj(1603));
    stage_SetAnimation(355, -1, -2);
    scpTransGObj(scpSearchGobj(1584), 0.0f, -200.0f, 0.0f);
    scpTransGObj(scpSearchGobj(1586), 0.0f, -200.0f, 0.0f);
    _ACTWait(5);
    ReInitBoxGeo(scpSearchGobj(1584));
    ReInitBoxGeo(scpSearchGobj(1586));
#else
#ifdef VERSION_AUG6
    act->flags20.ll &= ~0x80000LL;
    scpSearchGobj(1548)->active = 1;
    scpSearchGobj(1544)->active = 0;
    scpSearchGobj(1553)->active = 0;
    scpSearchGobj(1554)->active = 0;
    scpSearchGobj(1557)->active = 0;
    DeleteParticleLayout(scpSearchGobj(1590));
    DeleteParticleLayout(scpSearchGobj(1591));
    DeleteParticleLayout(scpSearchGobj(1592));
    DeleteParticleLayout(scpSearchGobj(1593));
    stage_SetAnimation(354, -1, -2);
    scpTransGObj(scpSearchGobj(1574), 0.0f, -200.0f, 0.0f);
    scpTransGObj(scpSearchGobj(1576), 0.0f, -200.0f, 0.0f);
    _ACTWait(5);
    ReInitBoxGeo(scpSearchGobj(1574));
    ReInitBoxGeo(scpSearchGobj(1576));
#else
    act->flags20.ll &= ~0x80000000000LL;
    scpSearchGobj(1713)->active = 1;
    scpSearchGobj(1670)->active = 0;
    scpSearchGobj(1687)->active = 0;
    scpSearchGobj(1688)->active = 0;
    scpSearchGobj(1691)->active = 0;
    DeleteParticleLayout(scpSearchGobj(1722));
    DeleteParticleLayout(scpSearchGobj(1723));
    DeleteParticleLayout(scpSearchGobj(1724));
    DeleteParticleLayout(scpSearchGobj(1725));
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(387, -1, -2);
#else
    stage_SetAnimation(391, -1, -2);
#endif
    scpTransGObj(scpSearchGobj(1705), 0.0f, -200.0f, 0.0f);
    scpTransGObj(scpSearchGobj(1707), 0.0f, -200.0f, 0.0f);
    _ACTWait(5);
    ReInitBoxGeo(scpSearchGobj(1705));
    ReInitBoxGeo(scpSearchGobj(1707));
#endif
#endif
#endif
}

SqEntry *gondola = 0;

#ifdef VERSION_NTSC
void actSt02aGondolaUp(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpAdpcmPlayRequestFunc(85, &gondola, 1, 1, 1);

    while (gondola == 0) {
        _ACTWait(1);
    }

    _ACTWait(16);
    stage_SetAnimation(87, 1, 0);
    gflagOn(106);

    while (stage_CheckAnimationFrame(87, 149, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

    _ACTWait(120);

    if (gondola != 0) {
        soundDataClose(gondola);
    }

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();

    gondola_up_mail[0].func = actSt02aGondolaMain;
    sub->mail = gondola_up_mail;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

SqEntry *gondola_test = 0;

void actSt02aGondolaDown(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpAdpcmPlayRequestFunc(85, &gondola_test, 1, 1, 1);

    while (gondola_test == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(87, 1, 150);
    gflagOff(106);

    while (stage_CheckAnimationFrame(87, 300, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

    _ACTWait(120);

    if (gondola_test != 0) {
        soundDataClose(gondola_test);
    }

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();

    gondola_down_mail[0].func = actSt02aGondolaMain;
    sub->mail = gondola_down_mail;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt02aBox(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
    if (gflagChk(98) != 0) {
        scpSearchGobj(1584)->active = 0;
        if (gflagChk(95) != 0) {
            scpSearchGobj(1584)->active = 0;
            scpSearchGobj(1585)->active = 0;
        } else {
            scpSearchGobj(1586)->active = 0;
        }
    }
    if (gflagChk(97) != 0) {
        scpSearchGobj(1585)->active = 0;
        scpSearchGobj(1586)->active = 0;
    }
    if (gflagChk(97) == 0 && gflagChk(98) == 0) {
        scpSearchGobj(1584)->active = 0;
        scpSearchGobj(1585)->active = 0;
        scpSearchGobj(1586)->active = 0;
    }
}

void actSt02aGondola(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(106) != 0) {
        stage_SetAnimation(87, 0, 0);
        _ACTWait(10);
        stage_SetAnimation(87, 0, 149);
    } else {
        stage_SetAnimation(87, 0, 300);
    }

    gondola_mail[0].func = actSt02aGondolaMain;
    act->mail = gondola_mail;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt02aFence(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(105) == 0) {
        fence_mail[0].func = actSt02aFenceMain;
        act->mail = fence_mail;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt02aWaterFall(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(95) != 0) {
        waterfall_mail[0].func = actSt02aWaterFallChk;
        act->mail = waterfall_mail;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }

    scpSearchGobj(1562)->active = 0;

    actCreateSubThread(actSt02WaterFallBoySplashCheck, 21);
    actCreateSubThread(actSt02aWaterFallReflactionEffect, 21);
}

void actSt02aBoxEvent2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    if (gflagChk(99) == 0) {
        scpSearchGobj(1588)->active = 0;
    }
}

void actSt02aEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(108) == 0) {
        ene_mail[0].func = actSt02aEneChk;
        act->mail = ene_mail;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt02aEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(109) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt02aEnemy2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(109) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt02aSekizo(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    scpSekizou(self, 110, 88, 0, 18, 900.0f, 1828.0f, 1150.0f, 800.0f, 1828.0f, 1150.0f);
}

void actSt02aWay(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(111) == 0) {
        way_off_start_mail[0].func = actSt02aWayOffChk;
        act->mail = way_off_start_mail;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        way_on_start_mail[0].func = actSt02aWayOnChk;
        act->mail = way_on_start_mail;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt02aTakiWay(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(95) != 0) {
        taki_way_mail[0].func = actSt02aTakiWayOnChk;
        act->mail = taki_way_mail;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actSt02aSecretItem(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(103) == 0) {
        secret_item_mail[0].func = actSt02aSecretItemChk;
        act->mail = secret_item_mail;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}
#else
void actSt02aGondolaUp(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

#ifdef VERSION_JUN26
    scpAdpcmPlayRequestFunc(80, &gondola, 1, 1, 1);
#else
#ifdef VERSION_AUG6
    scpAdpcmPlayRequestFunc(85, &gondola, 1, 1, 1);
#else
    scpAdpcmPlayRequestFunc(87, &gondola, 1, 1, 1);
#endif

#endif
    while (gondola == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_JUN26
    stage_SetAnimation(77, 1, 0);
    gflagOn(103);
    while (stage_CheckAnimationFrame(77, 120, 0) == 0) {
#else
    _ACTWait(16);
#ifdef VERSION_AUG6
    stage_SetAnimation(86, 1, 0);
    gflagOn(106);

    while (stage_CheckAnimationFrame(86, 149, 1) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(97, 1, 0);
#else
    stage_SetAnimation(101, 1, 0);
#endif
    gflagOn(119);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(97, 140, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(101, 140, 0) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

#ifdef VERSION_JUN26
    while (stage_CheckAnimationFrame(77, 149, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    if (gondola != 0) {
        soundDataClose(gondola);
    }
    gondola_up_mail[0].func = actSt02aGondolaMain;
    sub->mail = gondola_up_mail;
    ACTSendMailCorrect(self, 377);
#else
#ifndef VERSION_AUG6
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(97, 149, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(101, 149, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#endif
    _ACTWait(120);

    if (gondola != 0) {
#ifdef VERSION_AUG6
        soundDataClose(gondola);
    }
#else
        scpAdpcmCloseFunc(&gondola);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
#endif

    gondola_up_mail[0].func = actSt02aGondolaMain;
    sub->mail = gondola_up_mail;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

SqEntry *gondola_test = 0;

void actSt02aGondolaDown(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

#ifdef VERSION_JUN26
    scpAdpcmPlayRequestFunc(80, &gondola_test, 1, 1, 1);
#else
#ifdef VERSION_AUG6
    scpAdpcmPlayRequestFunc(85, &gondola_test, 1, 1, 1);
#else
    scpAdpcmPlayRequestFunc(87, &gondola_test, 1, 1, 1);
#endif

#endif
    while (gondola_test == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    stage_SetAnimation(86, 1, 150);
    gflagOff(106);

    while (stage_CheckAnimationFrame(86, 300, 1) == 0) {
#else
#ifdef VERSION_JUN26
    stage_SetAnimation(77, 1, 150);
    gflagOff(103);
    while (stage_CheckAnimationFrame(77, 260, 0) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(97, 1, 150);
#else
    stage_SetAnimation(101, 1, 150);
#endif
    gflagOff(119);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(97, 295, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(101, 295, 0) == 0) {
#endif
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 16);

#ifdef VERSION_JUN26
    while (stage_CheckAnimationFrame(77, 300, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    if (gondola_test != 0) {
        soundDataClose(gondola_test);
    }
    gondola_down_mail[0].func = actSt02aGondolaMain;
    sub->mail = gondola_down_mail;
    ACTSendMailCorrect(self, 377);
#else
#ifndef VERSION_AUG6
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(97, 300, 1) == 0) {
#else
    while (stage_CheckAnimationFrame(101, 300, 1) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
#endif
    _ACTWait(120);

    if (gondola_test != 0) {
#ifdef VERSION_AUG6
        soundDataClose(gondola_test);
    }
#else
        scpAdpcmCloseFunc(&gondola_test);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
#endif

    gondola_down_mail[0].func = actSt02aGondolaMain;
    sub->mail = gondola_down_mail;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

#ifdef VERSION_JUN26
void actSt02aGirlJumpChk(GObj *volatile self) /* derived name */
{
    ConstVec pos;
    ConstVec v;
    float dir[4];

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (girlGObj == 0 || scpTriggerFloorAttr(girlGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }
    gflagOn(104);
    pos = girlJumpSePos;
    soundSeDefPlay(1278, 0, pos.f, 1);
    if (ACTGame_FLAG_TETSUNAGI() == 0) {
        stage_SetAnimation(78, 1, 0);
        scpPlayMot(girlGObj, 521);
        _ACTWait(10);
        v = girlJumpPos;
        sceVu0SubVector(dir, v.f, test_CURRENTROOT(girlGObj));
        scpPlayMotDir(girlGObj, dir);
        _ACTWait(10);
        scpPlayJump(girlGObj, 259);
    } else {
        iosPadActRequest(boyPad, 16);
        _SCPBoySupportGirl(-875.0f, -900.0f, -175.0f, -1075.0f, -900.0f, -175.0f);
        stage_SetAnimation(78, 1, 0);
    }
    actCreateSubThread(actSt02aGirlJumpEffect, 21);
    while (stage_CheckAnimationFinish(78) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

void actSt02aGirlJumpEffect(GObj *volatile self) /* derived name */
{
    ConstVec b1;
    ConstVec b2;
    ConstVec b3;
    ConstVec b4;
    ConstVec b5;
    ConstVec b6;
    ConstVec b7;
    float f;
    float nf;

    for (f = 0.0f; f < 1000.0f;) {
        switch ((int)f) {
        case 0:
            b1 = girlJumpEffectPos;
            scpEffectStart(b1.f, 15);
            break;
        case 15:
            b2 = girlJumpEffect2Pos;
            scpEffectStart(b2.f, 0);
            b3 = girlJumpEffect3Pos;
            scpEffectStart(b3.f, 15);
            break;
        case 60:
            b4 = girlJumpEffect4Pos;
            scpEffectStart(b4.f, 15);
            b5 = girlJumpEffect5Pos;
            scpEffectStart(b5.f, 0);
            break;
        case 120:
            b6 = girlJumpEffect6Pos;
            scpEffectStart(b6.f, 0);
            b7 = girlJumpEffect7Pos;
            scpEffectStart(b7.f, 0);
            break;
        }
        nf = f + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if ((int)f != (int)nf) {
            _ACTWait(1);
            f = nf;
        } else {
            f = nf + 1.0f;
        }
    }
}

void actSt02aDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (scpTriggerBall(self, boyGObj, 200.0f) != 0) {
        stage_SetAnimation(75, 0, 0);
        _ACTWait(60);
        door_down_start_mail[0].func = actSt02aDoorDownChk;
        act->mail = door_down_start_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(74, 0, 0);
        door_up_start_mail[0].func = actSt02aDoorUpChk;
        act->mail = door_up_start_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}
#else
void actSt02aBox(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
#ifdef VERSION_AUG6
    if (gflagChk(98) != 0) {
        scpSearchGobj(1574)->active = 0;
        if (gflagChk(95) != 0) {
            scpSearchGobj(1574)->active = 0;
            scpSearchGobj(1575)->active = 0;
        } else {
            scpSearchGobj(1576)->active = 0;
        }
    }
    if (gflagChk(97) != 0) {
        scpSearchGobj(1575)->active = 0;
        scpSearchGobj(1576)->active = 0;
    }
    if (gflagChk(97) == 0 && gflagChk(98) == 0) {
        scpSearchGobj(1574)->active = 0;
        scpSearchGobj(1575)->active = 0;
        scpSearchGobj(1576)->active = 0;
#else
    if (gflagChk(109) != 0) {
        scpSearchGobj(1705)->active = 0;
        if (gflagChk(106) != 0) {
            scpSearchGobj(1705)->active = 0;
            scpSearchGobj(1706)->active = 0;
        } else {
            scpSearchGobj(1707)->active = 0;
        }
    }
    if (gflagChk(108) != 0) {
        scpSearchGobj(1706)->active = 0;
        scpSearchGobj(1707)->active = 0;
    }
    if (gflagChk(108) == 0 && gflagChk(109) == 0) {
        scpSearchGobj(1705)->active = 0;
        scpSearchGobj(1706)->active = 0;
        scpSearchGobj(1707)->active = 0;
#endif
    }
}
#endif

void actSt02aGondola(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(106) != 0) {
        stage_SetAnimation(86, 0, 0);
        _ACTWait(10);
        stage_SetAnimation(86, 0, 149);
    } else {
        stage_SetAnimation(86, 0, 300);
#else
#ifdef VERSION_JUN26
    if (gflagChk(103) != 0) {
        stage_SetAnimation(77, 0, 0);
        _ACTWait(10);
        stage_SetAnimation(77, 0, 149);
    } else {
        stage_SetAnimation(77, 0, 300);
#else
    if (gflagChk(119) != 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(97, 0, 0);
#else
        stage_SetAnimation(101, 0, 0);
#endif
        _ACTWait(10);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(97, 0, 149);
#else
        stage_SetAnimation(101, 0, 149);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(97, 0, 300);
#else
        stage_SetAnimation(101, 0, 300);
#endif
#endif
#endif
    }

    gondola_mail[0].func = actSt02aGondolaMain;
    act->mail = gondola_mail;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
    ACTSendMailCorrect(self, 377);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

void actSt02aFence(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(105) == 0) {
        fence_mail[0].func = actSt02aFenceMain;
        act->mail = fence_mail;
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
    if (gflagChk(102) == 0) {
        fence_mail[0].func = actSt02aFenceMain;
        act->mail = fence_mail;
        ACTSendMailCorrect(self, 377);
#else
    if (gflagChk(118) == 0) {
        fence_mail[0].func = actSt02aFenceMain;
        act->mail = fence_mail;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actSt02aWaterFall(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_JUN26
    if (gflagChk(92) != 0) {
        waterfall_mail[0].func = actSt02aWaterFallChk;
        act->mail = waterfall_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
    actCreateSubThread(actSt02WaterFallBoySplashCheck, 21);
    actCreateSubThread(actSt02aWaterFallReflactionEffect, 21);
}

void actSt02aGirlJump(GObj *volatile self) /* derived name */
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(104) == 0) {
        girl_jump_mail[0].func = actSt02aGirlJumpChk;
        act->mail = girl_jump_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt02aBox(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);

    _ACTWait(1);

    if (gflagChk(95) != 0) {
        scpSearchGobj(1504)->active = 0;
    }
    if (gflagChk(94) != 0) {
        scpSearchGobj(1505)->active = 0;
    }
    if (gflagChk(94) == 0 && gflagChk(95) == 0) {
        scpSearchGobj(1504)->active = 0;
        scpSearchGobj(1505)->active = 0;
    }
#else
#ifdef VERSION_AUG6
    if (gflagChk(95) != 0) {
        waterfall_mail[0].func = actSt02aWaterFallChk;
        act->mail = waterfall_mail;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(106) != 0) {
        waterfall_mail[0].func = actSt02aWaterFallChk;
        act->mail = waterfall_mail;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }

#ifdef VERSION_AUG6
    scpSearchGobj(1548)->active = 0;
#else
    scpSearchGobj(1713)->active = 0;
#endif

    actCreateSubThread(actSt02WaterFallBoySplashCheck, 21);
    actCreateSubThread(actSt02aWaterFallReflactionEffect, 21);
#endif
}

void actSt02aBoxEvent2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(99) == 0) {
        scpSearchGobj(1578)->active = 0;
#else
#ifdef VERSION_JUN26
    if (gflagChk(96) == 0) {
        scpSearchGobj(1507)->active = 0;
#else
    if (gflagChk(110) == 0) {
        scpSearchGobj(1709)->active = 0;
#endif
#endif
    }
}

void actSt02aEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(108) == 0) {
        ene_mail[0].func = actSt02aEneChk;
        act->mail = ene_mail;
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
    if (gflagChk(105) == 0) {
        ene_mail[0].func = actSt02aEneChk;
        act->mail = ene_mail;
        ACTSendMailCorrect(self, 377);
#else
    if (gflagChk(121) == 0) {
        ene_mail[0].func = actSt02aEneChk;
        act->mail = ene_mail;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}

void actSt02aEnemy1(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

#ifdef VERSION_AUG6
    while (gflagChk(109) == 0) {
#else
#ifdef VERSION_JUN26
    while (gflagChk(106) == 0) {
#else
    while (gflagChk(122) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt02aEnemy2(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);
#ifdef VERSION_AUG6

    while (gflagChk(109) == 0) {
#else
#ifdef VERSION_JUN26

    while (gflagChk(106) == 0) {
#else
    Generator_Mask(scpSearchGobj(1703));

    while (gflagChk(122) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
    Generator_Call(scpSearchGobj(1703));
#endif
}

void actSt02aSekizo(GObj *volatile self)
{
    GObj *x = self;
#ifdef VERSION_JUN26
    actInitialize(self);

    _ACTWait(1);

    scpSekizou(self, 107, 79, 0, 21, 900.0f, 1828.0f, 1150.0f, 800.0f, 1828.0f, 1150.0f);
#else

    actInitialize(self);
    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpSekizou(self, 123, 98, 0, 18, 900.0f, 1828.0f, 1150.0f, 800.0f, 1828.0f, 1150.0f);
#else
#ifdef VERSION_AUG6
    scpSekizou(self, 110, 87, 0, 18, 900.0f, 1828.0f, 1150.0f, 800.0f, 1828.0f, 1150.0f);
#else
    scpSekizou(self, 123, 102, 0, 18, 900.0f, 1828.0f, 1150.0f, 800.0f, 1828.0f, 1150.0f);
#endif
#endif
#endif
}

void actSt02aWay(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(111) == 0) {
        way_off_start_mail[0].func = actSt02aWayOffChk;
        act->mail = way_off_start_mail;
        ACTSendMailCorrect(self, 393);
#else
#ifdef VERSION_JUN26
    if (gflagChk(108) == 0) {
        way_off_start_mail[0].func = actSt02aWayOffChk;
        act->mail = way_off_start_mail;
        ACTSendMailCorrect(self, 377);
#else
    if (gflagChk(124) == 0) {
        way_off_start_mail[0].func = actSt02aWayOffChk;
        act->mail = way_off_start_mail;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    } else {
        way_on_start_mail[0].func = actSt02aWayOnChk;
        act->mail = way_on_start_mail;
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 377);
#else
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt02aTakiWay(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(95) != 0) {
        taki_way_mail[0].func = actSt02aTakiWayOnChk;
        act->mail = taki_way_mail;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(106) != 0) {
        taki_way_mail[0].func = actSt02aTakiWayOnChk;
        act->mail = taki_way_mail;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actSt02aSecretItem(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(103) == 0) {
        secret_item_mail[0].func = actSt02aSecretItemChk;
        act->mail = secret_item_mail;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(114) == 0) {
        secret_item_mail[0].func = actSt02aSecretItemChk;
        act->mail = secret_item_mail;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }
}
#endif

void actSt02aDoorEvent(int x)
{
    volatile int local = x;
}

void actSt02aDoorUpEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = doorUpEffectPos.d[0];
    long long v0b = doorUpEffect2Pos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = doorUpEffectPos.d[1];
            scpEffectStart(b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = doorUpEffect2Pos.d[1];
            scpEffectStart(b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt02aDoorDownEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = doorUpEffect2Pos.d[0];
    long long v0b = doorUpEffectPos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = doorUpEffect2Pos.d[1];
            scpEffectStart(b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = doorUpEffectPos.d[1];
            scpEffectStart(b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt02aFenceMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    scpBoyControlReadDisable = 0;
#endif
    sub->mainMail = fence_main_mail;
    while (1) {
        _ACTWait(1);
    }
}

void actSt02aFenceSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    lt_switch_layout(51);
#else
    lt_switch_layout(55);
#endif
#endif
    scpBoyControlReadDisable = 1;

    fence_switch_mail[0].func = actSt02aFenceOpen;
    sub->mail = fence_switch_mail;
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

#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
void actSt02aFenceOpen(GObj *volatile self)
{
#ifdef VERSION_JUN26
    gflagOn(102);
    scpAdpcmPlayRequestFunc(89, &st02a_fence, 1, 1, 1);
#else
    scpSleepEnemyAll();
    gflagOn(105);
    scpAdpcmPlayRequestFunc(94, &st02a_fence, 1, 1, 1);
#endif
    while (st02a_fence == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
    stage_SetAnimation(76, 1, 0);
    while (stage_CheckAnimationFinish(76) == 0) {
#else
    stage_SetAnimation(84, 1, 0);
    stage_SetAnimation(85, 1, 0);
    while (stage_CheckAnimationFinish(85) == 0) {
#endif
#else
    stage_SetAnimation(85, 1, 0);
    stage_SetAnimation(86, 1, 0);
    while (stage_CheckAnimationFinish(86) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    SetWayGroupActive(26, 1);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
#ifdef VERSION_JUN26
}

void actSt02aWaterFallChk(GObj *volatile self)
{
    scpSearchGobj(1486)->active = 0;
    DeleteParticleLayout(scpSearchGobj(1519));
    DeleteParticleLayout(scpSearchGobj(1520));
    DeleteParticleLayout(scpSearchGobj(1521));
    DeleteParticleLayout(scpSearchGobj(1522));
    stage_SetAnimation(321, -1, -2);
#else
    scpWakeupEnemyAll();
#endif
}

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
void actSt02aWaterFallReflactionEffect(GObj *volatile self)
{
    PoolMesh m0 = fallReflactionMesh;
    PoolMeshQuad q0 = fallReflactionQuad;

    InitLayoutedPoolReflactionMesh(&m0, &q0);
    for (;;) {
        SetLayoutedPoolReflactionMesh(&m0);
        DispLimitedPoolReflactionMesh(&m0);
        _ACTWait(1);
    }
}
#endif
#else
static void actSt02aFenceOpenSub(GObj *volatile self)
{
    while (st02a_fence == 0) {
        _ACTWait(1);
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(95, 1, 0);
    stage_SetAnimation(96, 1, 0);
    while (stage_CheckAnimationFinish(96) == 0) {
#else
    stage_SetAnimation(99, 1, 0);
    stage_SetAnimation(100, 1, 0);
    while (stage_CheckAnimationFinish(100) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}
#endif

void actSt02aGondolaMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

#ifdef VERSION_AUG6
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    scpWakeupEnemyAll();
#endif
#ifdef VERSION_JUN26
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
#endif
    sub->mainMail = gondola_main_mail;
    while (1) {
        _ACTWait(1);
    }
}

#ifdef VERSION_NTSC
void actSt02aGondolaSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    if (gflagChk(106) != 0) {
        gondola_switch_down_mail[0].func = actSt02aGondolaDown;
        sub->mail = gondola_switch_down_mail;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }

    gondola_switch_up_mail[0].func = actSt02aGondolaUp;
    sub->mail = gondola_switch_up_mail;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}
#else
void actSt02aGondolaSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
#ifdef VERSION_JUN26
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    if (gflagChk(103) != 0) {
        gondola_switch_down_mail[0].func = actSt02aGondolaDown;
        sub->mail = gondola_switch_down_mail;
        ACTSendMailCorrect(self, 377);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
#ifdef VERSION_AUG6
    lt_switch_layout(51);
#else
    lt_switch_layout(55);
#endif
#endif
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

#ifdef VERSION_AUG6
    if (gflagChk(106) != 0) {
        gondola_switch_down_mail[0].func = actSt02aGondolaDown;
        sub->mail = gondola_switch_down_mail;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(119) != 0) {
        gondola_switch_down_mail[0].func = actSt02aGondolaDown;
        sub->mail = gondola_switch_down_mail;
        ACTSendMailCorrect(self, 430);
#endif
#endif
        _ACTWait(0);
    }

    gondola_switch_up_mail[0].func = actSt02aGondolaUp;
    sub->mail = gondola_switch_up_mail;
#ifdef VERSION_JUN26
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt02aGirlJumpEvent(int x) /* derived name */
{
    volatile int local = x;
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
#endif
}
#endif

void actSt02aEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    while (scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
#else
    while (scpTriggerFloorAttr(girlGObj, 0x5000000) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    gflagOn(108);
    gflagOn(109);
#else
#ifdef VERSION_JUN26
    gflagOn(105);
    gflagOn(106);
#else
    gflagOn(121);
    gflagOn(122);
#endif
#endif
}

void actSt02aSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt02aWayOnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (girlGObj == 0) {
        _ACTWait(0);
    }
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    while (scpTriggerFloorAttr(girlGObj, 0x4000000) == 0) {
#else
    while (scpCheckExistAliveEnemy() != 0 || scpTriggerFloorAttr(girlGObj, 0x4000000) == 0) {
#endif
        _ACTWait(1);
    }

    SetWayGroupActive(53, 1);
#ifdef VERSION_JUN26
    gflagOff(108);
    way_on_chk_mail[0].func = actSt02aWayOffChk;
    sub->mail = way_on_chk_mail;
    ACTSendMailCorrect(self, 377);
#else
    SetWayGroupActive(55, 1);
    SetWayGroupActive(56, 1);
    SetWayGroupActive(57, 1);
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    gflagOff(111);
#else
    gflagOff(124);
#endif

    way_on_mail[0].func = actSt02aWayOffChk;
    sub->mail = way_on_mail;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
#endif
    _ACTWait(0);
}

void actSt02aWayOffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (girlGObj == 0) {
        _ACTWait(0);
    }
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    while (scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
#else
    while (scpCheckExistAliveEnemy() == 0 && scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
#endif
        _ACTWait(1);
    }

    SetWayGroupActive(53, 0);
#ifdef VERSION_JUN26
    gflagOn(108);
    way_off_chk_mail[0].func = actSt02aWayOnChk;
    sub->mail = way_off_chk_mail;
    ACTSendMailCorrect(self, 377);
#else
    SetWayGroupActive(55, 0);
    SetWayGroupActive(56, 0);
    SetWayGroupActive(57, 0);
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    gflagOn(111);
#else
    gflagOn(124);
#endif

    way_off_mail[0].func = actSt02aWayOnChk;
    sub->mail = way_off_mail;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
#endif
    _ACTWait(0);
}

#ifndef VERSION_JUN26
void actSt02aTakiWayOnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (girlGObj == 0) {
        _ACTWait(0);
    }
#ifdef VERSION_AUG6
    while (scpTriggerFloorAttr(girlGObj, 0x6000000) == 0) {
#else
    while (scpCheckExistAliveEnemy() != 0 || scpTriggerFloorAttr(girlGObj, 0x6000000) == 0) {
#endif
        _ACTWait(1);
    }

    SetWayGroupActive(35, 1);
    SetWayGroupActive(59, 1);

#ifdef VERSION_AUG6
    taki_off_mail[0].func = actSt02aTakiWayOffChk;
    sub->mail = taki_off_mail;
    ACTSendMailCorrect(self, 393);
#else
    taki_on_mail[0].func = actSt02aTakiWayOffChk;
    sub->mail = taki_on_mail;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

void actSt02aTakiWayOffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (girlGObj == 0) {
        _ACTWait(0);
    }
#ifdef VERSION_AUG6
    while (scpTriggerFloorAttr(girlGObj, 0x5000000) == 0) {
#else
    while (scpCheckExistAliveEnemy() == 0 && scpTriggerFloorAttr(girlGObj, 0x5000000) == 0) {
#endif
        _ACTWait(1);
    }

    SetWayGroupActive(35, 0);
    SetWayGroupActive(59, 0);

#ifdef VERSION_AUG6
    taki_on_mail[0].func = actSt02aTakiWayOnChk;
    sub->mail = taki_on_mail;
    ACTSendMailCorrect(self, 393);
#else
    taki_off_mail[0].func = actSt02aTakiWayOnChk;
    sub->mail = taki_off_mail;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

#ifdef VERSION_NTSC
void actSt02aSecretItemChk(GObj *volatile self)
{
    while (scpSearchGobj(1639) == 0) {
        _ACTWait(1);
    }
    _ACTWait(60);

    scpExplodeSecretItem();
}
#else
void actSt02aSecretItemChk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    while (scpSearchGobj(1625) == 0) {
#else
    while (scpSearchGobj(1770) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(60);

    scpExplodeSecretItem();
}
#endif
#endif
