#include "st17b.h"
#include "act.h"
#include "commonact.h"
#include "gflag.h"
#include "StageManager.h"
#include "script.h"
#include "typedef.h"

static ActMail check_mes[2] = {{430}, {429}}; /* derived name */

/* .sdata: the lightning stream handle. */
struct SqEntry *lightning2 = 0;

void actSt17bTest(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);
}

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
