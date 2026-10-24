#include "st22a.h"

#ifdef VERSION_JUN26
#include "StageManager.h"
#endif

#include "layout_texture.h"
#include "thread.h"
#include "adpcm_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "camera-root.h"
#include "gflag.h"
#include "script.h"
#include "StageAnimation.h"

#ifndef VERSION_JUN26
#include "cage.h"
#endif

#include <libvu0.h>
#include "st04c.h"
#include "typedef.h"

#ifdef VERSION_JUN26
#include "main.h"

/* .sdata: the intro's stream handle. */
struct SqEntry *lightning = 0;

static ActMail intro_mes[2] = {{377}, {376}}; /* derived name */

/* the point the boy turns to face at the end of the intro */
static const StVec introFacePos = {{-2000.0f, 0.0f, -1129.0f, 1.0f}}; /* derived name */
#else
#include "gamesys.h"
#include "main.h"

/* declared ahead with no size for actSt22aIntroChk; the sized definition
   follows the stream handle in .sdata */
static int lightningAnims[];

/* .sdata: the lightning stream handle and the two animation numbers the
   lightning plays. */
struct SqEntry *lightning = 0;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
static int lightningAnims[2] = {754, 755}; /* derived name */
#else
#ifdef VERSION_NTSC
static int lightningAnims[2] = {684, 685}; /* derived name */
#else
#ifdef VERSION_AUG6
static int lightningAnims[2] = {683, 684}; /* derived name */
#else
static int lightningAnims[2] = {758, 759}; /* derived name */
#endif
#endif
#endif

void actSt22aLightningVolime(GObj *volatile self)
{
    /* the lightning's volume for height y, nested in this function */
    inline float getVolume(float y) /* derived name */
    {
        float lo = -8000.0f, hi = -1355.0f;

        if (y < lo) {
            return 0.0f;
        } else if (hi < y) {
            return 1.0f;
        }
        return (y - lo) / (hi - lo);
    }
    float *pos;
    float v;

    while (lightning == 0) {
        _ACTWait(1);
    }
    for (;;) {
        pos = GetCameraPos();
        v = getVolume(pos[2]);
        if (v < 0.1f) {
            v = 0.1f;
        }
        AdpcmVolumeSet(lightning, (int)(v * 16383.0f));
        _ACTWait(1);
    }
}

#ifdef VERSION_NTSC
static ActMail intro_mes[2] = {{397}, {396}}; /* derived name */
#else
#ifdef VERSION_AUG6
static ActMail intro_mes[2] = {{393}, {392}}; /* derived name */
#else
static ActMail intro_mes[2] = {{430}, {429}}; /* derived name */
#endif
#endif

/* the point the boy turns to face when the intro is skipped */
static const StVec introFacePos = {{-2000.0f, 0.0f, -1129.0f, 1.0f}}; /* derived name */

/* no header declares it; gamesys.c defines it */
void actSt22aIntroChk(GObj *volatile self);

#ifdef VERSION_NTSC
void actSt22aIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    StVec pos;
    float dir[4];

    _ACTWait(1);
    lightning = 0;
    scpAdpcmPlayRequestFunc(92, &lightning, 1, 0, 1);
    actCreateSubThread(actSt22aLightningVolime, 21);
    ScpCallCameraSetTarget(7000.0f, 280.0f, 4938.0f);
    SetCageChainHangableFlag(scpSearchGobj(1704), 0);
    SetCageChainHangableFlag(scpSearchGobj(1705), 0);
    SetCageChainHangableFlag(scpSearchGobj(1706), 0);
    SetCageChainHangableFlag(scpSearchGobj(1707), 0);
    SetCageChainHangableFlag(scpSearchGobj(1708), 0);
    SetCageChainHangableFlag(scpSearchGobj(1709), 0);
    SetCageChainHangableFlag(scpSearchGobj(1710), 0);
    SetCageChainHangableFlag(scpSearchGobj(1711), 0);
    SetCageChainHangableFlag(scpSearchGobj(1712), 0);
    if (gflagChk(295) != 0) {
        return;
    }
    scpPlayPosSet(boyGObj, -808.0f, 148.0f, -1053.0f);
    if (gflagChk(294) == 0) {
        scpFadeOut(255.0f, 0, 0, 0);
        gamesysNObjInfoInit();
        intro_mes[0].func = actSt22aIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    } else {
        gflagOn(295);
        pos = introFacePos;
        sceVu0SubVector(dir, &pos, test_CURRENTROOT(boyGObj));
        scpPlayMotDir(boyGObj, dir);
        _ACTWait(1);
        SetCameraFlag_GamecamCutBack();
    }
}
#else
void actSt22aIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    StVec pos;
    float dir[4];

    _ACTWait(1);
    lightning = 0;
#ifdef VERSION_AUG6
    scpAdpcmPlayRequestFunc(92, &lightning, 1, 0, 1);
    actCreateSubThread(actSt22aLightningVolime, 21);
    ScpCallCameraSetTarget(7000.0f, 280.0f, 4938.0f);
    SetCageChainHangableFlag(scpSearchGobj(1688), 0);
    SetCageChainHangableFlag(scpSearchGobj(1689), 0);
    SetCageChainHangableFlag(scpSearchGobj(1690), 0);
    SetCageChainHangableFlag(scpSearchGobj(1691), 0);
    SetCageChainHangableFlag(scpSearchGobj(1692), 0);
    SetCageChainHangableFlag(scpSearchGobj(1693), 0);
    SetCageChainHangableFlag(scpSearchGobj(1694), 0);
    SetCageChainHangableFlag(scpSearchGobj(1695), 0);
    SetCageChainHangableFlag(scpSearchGobj(1696), 0);
    if (gflagChk(294) != 0) {
#else
    scpAdpcmPlayRequestFunc(94, &lightning, 1, 0, 1);
    actCreateSubThread(actSt22aLightningVolime, 21);
    ScpCallCameraSetTarget(7000.0f, 280.0f, 4938.0f);
    SetCageChainHangableFlag(scpSearchGobj(1847), 0);
    SetCageChainHangableFlag(scpSearchGobj(1848), 0);
    SetCageChainHangableFlag(scpSearchGobj(1849), 0);
    SetCageChainHangableFlag(scpSearchGobj(1850), 0);
    SetCageChainHangableFlag(scpSearchGobj(1851), 0);
    SetCageChainHangableFlag(scpSearchGobj(1852), 0);
    SetCageChainHangableFlag(scpSearchGobj(1853), 0);
    SetCageChainHangableFlag(scpSearchGobj(1854), 0);
    SetCageChainHangableFlag(scpSearchGobj(1855), 0);
    if (gflagChk(324) != 0) {
#endif
        return;
    }
    scpPlayPosSet(boyGObj, -808.0f, 148.0f, -1053.0f);
#ifdef VERSION_AUG6
    if (gflagChk(293) == 0) {
#else
    if (gflagChk(323) == 0) {
#endif
        scpFadeOut(255.0f, 0, 0, 0);
        gamesysNObjInfoInit();
        intro_mes[0].func = actSt22aIntroChk;
        act->mail = intro_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    } else {
        gflagOn(294);
#else
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    } else {
        gflagOn(324);
#endif
        pos = introFacePos;
        sceVu0SubVector(dir, &pos, test_CURRENTROOT(boyGObj));
        scpPlayMotDir(boyGObj, dir);
        _ACTWait(1);
        SetCameraFlag_GamecamCutBack();
    }
}
#endif

/* .sbss: the demo's own end flag, raised by the subthread the wait loop below
   spins for. */
static int demoEnd;

typedef struct St22Anims { /* field names derived */
    int id[2];
} St22Anims; /* derived name */
#endif

#ifdef VERSION_JUN26
void actSt22aIntroChk(GObj *volatile self)
{
    StVec pos;
    float dir[4];

    while (scpTriggerBall(self, boyGObj, 1000.0f) == 0) {
        _ACTWait(1);
    }
    CheckPoint();
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    gflagOn(281);
    stage_SetAnimation(634, 1, 0);
    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 10);
    scpFadeIn(6.0f);
    stage_SetAnimation(634, 1, 0);
    scpPlayMot(boyGObj, 400);
    while (stage_ContinueAnimation(634, 635) == 0) {
        _ACTWait(1);
    }
    scpPlayPosSet(boyGObj, -707.0f, 148.0f, -1112.0f);
    pos = introFacePos;
    sceVu0SubVector(dir, &pos, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);
    scpPlayMot(boyGObj, 401);
    while (stage_CheckAnimationFinish(635) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}
#else
void actSt22aIntroChk(GObj *volatile self)
{
    St22Anims anims;
    StVec pos;
    float dir[4];
    GProc *th;
    int fin;
    unsigned int i;

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
#ifdef VERSION_AUG6
    gflagOn(293);
#else
    gflagOn(294);
#endif
    scpSekizouCheckPoint();
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
#ifdef VERSION_AUG6
    gflagOn(294);
    stage_SetAnimation(683, 1, 0);
#else
    gflagOn(295);
    stage_SetAnimation(684, 1, 0);
#endif
#else
    gflagOn(323);
    scpSekizouCheckPoint();
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    gflagOn(324);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(754, 1, 0);
#else
    stage_SetAnimation(758, 1, 0);
#endif
#endif
    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 10);
    scpFadeIn(6.0f);
    th = actCreateSubThread(actSt22aIntroSub, 21);
    demoEnd = 0;
    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }
    fin = demoEnd ^ 1;
    if (fin != 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }
    iosThreadSetPri(&th->thread, 34);
    if (fin != 0) {
        anims = *(St22Anims *)lightningAnims;
        for (i = 0; i < 2; i++) {
            stage_SetAnimation(anims.id[i], 1, -1);
            _ACTWait(1);
        }
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(755, 1, -1);
#else
#ifdef VERSION_NTSC
        stage_SetAnimation(685, 1, -1);
#else
#ifdef VERSION_AUG6
        stage_SetAnimation(684, 1, -1);
#else
        stage_SetAnimation(759, 1, -1);
#endif
#endif
#endif
        StabilizeAllLayoutedCage();
        scpPlayPosSet(boyGObj, -808.0f, 148.0f, -1053.0f);
        pos = introFacePos;
        sceVu0SubVector(dir, &pos, test_CURRENTROOT(boyGObj));
        scpPlayMotDir(boyGObj, dir);
        scpPlayMot(boyGObj, 0);
        _ACTWait(1);
        SetCameraFlag_GamecamCutBack();
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
        scpFadeIn(3.0f);
#else
        scpFadeIn(6.0f);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
#endif
    } else {
        scpPlayMot(boyGObj, 0);
    }
    scpPlayEnd(boyGObj);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    lt_switch_layout(50);
#else
    lt_switch_layout(54);
#endif
#endif
    scpBoyControlReadDisable = 0;
}

#ifdef VERSION_NTSC
void actSt22aIntroSub(GObj *volatile self)
{
    StVec pos;
    float dir[4];

    stage_SetAnimation(684, 1, 0);
    scpPlayMot(boyGObj, 391);
    while (stage_ContinueAnimation(684, 685) == 0) {
        _ACTWait(1);
    }
    scpPlayPosSet(boyGObj, -707.0f, 148.0f, -1112.0f);
    pos = introFacePos;
    sceVu0SubVector(dir, &pos, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);
    scpPlayMot(boyGObj, 392);
    while (stage_CheckAnimationFinish(685) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}
#else
void actSt22aIntroSub(GObj *volatile self)
{
    StVec pos;
    float dir[4];

#ifdef VERSION_AUG6
    stage_SetAnimation(683, 1, 0);
    scpPlayMot(boyGObj, 391);
    while (stage_ContinueAnimation(683, 684) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(754, 1, 0);
#else
    stage_SetAnimation(758, 1, 0);
#endif
    scpPlayMot(boyGObj, 397);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(754, 755) == 0) {
#else
    while (stage_ContinueAnimation(758, 759) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    scpPlayPosSet(boyGObj, -707.0f, 148.0f, -1112.0f);
    pos = introFacePos;
    sceVu0SubVector(dir, &pos, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);
#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 392);
    while (stage_CheckAnimationFinish(684) == 0) {
#else
    scpPlayMot(boyGObj, 398);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(755) == 0) {
#else
    while (stage_CheckAnimationFinish(759) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}
#endif
#endif

#ifdef VERSION_JUN26
void actSt22aIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);
    scpAdpcmPlayRequestFunc(87, &lightning, 1, 0, 1);
    if (gflagChk(281) == 0) {
        scpFadeOut(255.0f, 0, 0, 0);
        intro_mes[0].func = actSt22aIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}
#endif
