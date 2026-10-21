#include "st17b.h"
#include "act.h"
#include "commonact.h"
#include "gflag.h"
#include "StageManager.h"
#include "script.h"
#include "typedef.h"

static ActMail check_mes[2] = {{377}, {376}}; /* derived name */

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
    scpAdpcmPlayRequestFunc(87, &lightning2, 1, 0, 1);

    if (gflagChk(33) == 0) {
        check_mes[0].func = actSt17bCheckChk;
        act->mail = check_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt17bCheckChk(GObj *volatile self)
{
    _ACTWait(1);
    CheckPoint();
    gflagOn(32);
}
