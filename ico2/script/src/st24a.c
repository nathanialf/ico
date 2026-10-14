#include "st24a.h"
#include "layout_texture.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "camera-root.h"
#include "gflag.h"
#include "StageAnimation.h"
#include <libvu0.h>
#include "typedef.h"
#include "script.h"
#include "main.h"
#include "include_asm.h"

static void actSt24aSwordSub(GObj *volatile self);

static ActMail sword_mes[2] = {{430}, {429}}; /* derived name */

static ActMail demoCam_mes[2] = {{430}, {429}}; /* derived name */

/* .sbss: the demo's own end flag, raised by the subthread the wait loop below
   spins for. */
static int demoEnd;

static const Vec16 swordChkPos = {{1685.0f, -1080.0f, -1000.0f, 1.0f}}; /* derived name */

/* .sdata: the sword's object. */
SqEntry *sword = 0;

void actSt24aSwordChk(GObj *volatile self);

INCLUDE_ASM(actSt24aSwordChk);

static void actSt24aDemoCamChk(GObj *volatile self);

INCLUDE_ASM(actSt24aDemoCamChk);

void actSt24aSword(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    ScpCallCameraSetTarget(363.0f, 1307.0f, -3297.0f);

    if (gflagChk(329) == 0) {
        sword_mes[0].func = actSt24aSwordChk;
        act->mail = sword_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

INCLUDE_ASM(actSt24aSaku);

void actSt24aDemoCam(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(330) == 0) {
        demoCam_mes[0].func = actSt24aDemoCamChk;
        act->mail = demoCam_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

INCLUDE_ASM(actSt24aSwordSub);
