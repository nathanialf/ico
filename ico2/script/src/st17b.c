#include "st17b.h"

#ifdef VERSION_NTSC
#include "layout_texture.h"
#endif

#ifdef VERSION_AUG6
#include "layout_texture.h"
#endif

#include "act.h"
#include "commonact.h"
#include "gflag.h"

#ifdef VERSION_NTSC
#include "StageAnimation.h"
#endif

#ifdef VERSION_AUG6
#include "StageAnimation.h"
#endif

#include "StageManager.h"
#include "script.h"
#include "typedef.h"

#ifdef VERSION_AUG6
#include "main.h"

static ActMail check_mes[2] = {{393}, {392}}; /* derived name */

static ActMail intro_mes[2] = {{393}, {392}}; /* derived name */
#else
#ifdef VERSION_NTSC
#include "main.h"

static ActMail check_mes[2] = {{397}, {396}}; /* derived name */

static ActMail intro_mes[2] = {{397}, {396}}; /* derived name */
#else
static ActMail check_mes[2] = {{430}, {429}}; /* derived name */
#endif
#endif

/* .sdata: the lightning stream handle. */
struct SqEntry *lightning2 = 0;

void actSt17bTest(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
}

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
void actSt17bCheck(GObj *volatile self)
{
    GObj *x = self;
    Act *act = (Act *)actInitialize(self);

    _ACTWait(1);
    ScpCallCameraSetTarget(14990.0f, 7074.0f, -4694.0f);
    scpAdpcmPlayRequestFunc(92, &lightning2, 1, 0, 1);

    if (gflagChk(33) == 0) {
        check_mes[0].func = actSt17bCheckChk;
        act->mail = check_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 397);
#endif
        _ACTWait(0);
    }
}

void actSt17bIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(34) == 0) {
        intro_mes[0].func = actSt17bIntroChk;
        act->mail = intro_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 397);
#endif
        _ACTWait(0);
    }
}

void actSt17bCheckChk(GObj *volatile self)
{
    _ACTWait(1);
    CheckPoint();
    gflagOn(32);
}

void actSt17bIntroChk(GObj *volatile self)
{
    while (scpTriggerFloorAttr(boyGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    gflagOn(34);
#ifdef VERSION_AUG6
    stage_SetAnimation(115, 1, 0);
    while (stage_CheckAnimationFinish(115) == 0) {
#else
    stage_SetAnimation(116, 1, 0);
    while (stage_CheckAnimationFinish(116) == 0) {
#endif
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}
#else
void actSt17bCheck(GObj *volatile self)
{
    GObj *x = self;
    Act *act = (Act *)actInitialize(self);

    _ACTWait(1);
    ScpCallCameraSetTarget(14990.0f, 7074.0f, -4694.0f);
    scpAdpcmPlayRequestFunc(94, &lightning2, 1, 0, 1);

    if (gflagChk(36) == 0) {
        check_mes[0].func = actSt17bCheckChk;
        act->mail = check_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt17bCheckChk(GObj *volatile self)
{
    _ACTWait(1);
    CheckPoint();
    gflagOn(34);
}
#endif
