#include "st17b.h"
#include "act.h"
#include "commonact.h"
#include "gflag.h"
#include "StageManager.h"
#include "script.h"
#include "typedef.h"

static ActMail check_mes[2] = {{430}, {429}}; /* derived name */

/* .sdata: the lightning stream handle. */
char *lightning2 = 0;

void actSt17bTest(GObj *volatile a0)
{
    GObj *x = a0;

    actInitialize(a0);
    _ACTWait(1);
}

void actSt17bCheck(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = (Act *)actInitialize(a0);

    _ACTWait(1);
    ScpCallCameraSetTarget(14990.0f, 7074.0f, -4694.0f);
    scpAdpcmPlayRequestFunc(94, &lightning2, 1, 0, 1);

    if (gflagChk(36) == 0) {
        check_mes[0].func = actSt17bCheckChk;
        self->mail = check_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt17bCheckChk(GObj *volatile a0)
{
    _ACTWait(1);
    CheckPoint();
    gflagOn(34);
}
