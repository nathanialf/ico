#include "common.h"

extern void _ACTWait();
extern int actInitialize(int a0);
extern void _ACTWait__pn(int a0) __asm__("_ACTWait");

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

extern ActMail D_004FB050[];
extern int lightning2;
extern void ScpCallCameraSetTarget(float x, float y, float z);
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
extern int gflagChk(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern void actSt17bCheckChk(volatile int a0);

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
        D_004FB050[0].func = actSt17bCheckChk;
        self->mail = D_004FB050;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSt17bCheckChk(volatile int a0)
{
    _ACTWait(1);
    CheckPoint();
    gflagOn(0x22);
}
