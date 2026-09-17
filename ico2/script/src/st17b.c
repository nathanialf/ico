#include "common.h"
#include "st17b.h"
#include "act.h"
#include "commonact.h"
#include "gflag.h"
#include "script.h"
#include "typedef.h"

static ActMail check_mes[2] = {{430}, {429}};

extern int lightning2;

void actSt17bTest(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
}

void actSt17bCheck(volatile int a0)
{
    int x = a0;
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

void actSt17bCheckChk(volatile int a0)
{
    _ACTWait(1);
    CheckPoint();
    gflagOn(34);
}
