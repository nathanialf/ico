#include "common.h"
#include "st17b.h"
#include "act.h"
#include "commonact.h"
#include "gflag.h"
#include "script.h"

typedef struct ActMail {
    int mail;          /* 0x00 */
    void (*func)(int); /* 0x04 */
    int unk08;         /* 0x08 */
    int unk0C;         /* 0x0C */
} ActMail;

typedef struct Act {
    char unk00[0xD4]; /* 0x00 */
    ActMail *mail;    /* 0xD4 */
} Act;

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
    scpAdpcmPlayRequestFunc(0x5E, &lightning2, 1, 0, 1);

    if (gflagChk(0x24) == 0) {
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
    gflagOn(0x22);
}
