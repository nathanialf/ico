#include "st04d.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "script.h"
#include "StageAnimation.h"
#include "typedef.h"
#include "main.h"
#include "include_asm.h"

inline void actSt04dDoor1Event(int x)
{
    volatile int local = x;
}

static ActMail door1_down_mes[2] = {{377}, {376}}; /* derived name */

static ActMail door1_up_mes[2] = {{377}, {376}}; /* derived name */

INCLUDE_ASM(actSt04dDoor1);

inline void actSt04dDoor1UpEffect(GObj *volatile self);

static const ConstVec door1SoundPos = {{-498.0f, -1418.0f, -5663.0f, 0.0f}}; /* derived name */

static const ConstVec door1UpEffectPos = {{-505.0f, -1200.0f, -5671.0f, 1.0f}}; /* derived name */

static const ConstVec door1DownEffectPos = {{-505.0f, -1447.0f, -5671.0f, 1.0f}}; /* derived name */

static ActMail door1_up_chk_mes[2] = {{377}, {376}}; /* derived name */

INCLUDE_ASM(actSt04dDoor1UpChk);

inline void actSt04dDoor1UpEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = door1UpEffectPos.d[0];
    long long v0b = door1DownEffectPos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = door1UpEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = door1DownEffectPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

inline void actSt04dDoor1DownEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = door1DownEffectPos.d[0];
    long long v0b = door1UpEffectPos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = door1DownEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = door1UpEffectPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

static ActMail door1_down_chk_mes[2] = {{377}, {376}}; /* derived name */

INCLUDE_ASM(actSt04dDoor1DownChk);

inline void actSt04dDoor2Event(int x)
{
    volatile int local = x;
}

static ActMail door2_down_mes[2] = {{377}, {376}}; /* derived name */

static ActMail door2_up_mes[2] = {{377}, {376}}; /* derived name */

INCLUDE_ASM(actSt04dDoor2);

inline void actSt04dDoor2UpEffect(GObj *volatile self);

static const ConstVec door2SoundPos = {{702.0f, -1886.0f, -5680.0f, 0.0f}}; /* derived name */

static const ConstVec door2UpEffectPos = {{704.0f, -1700.0f, -5679.0f, 1.0f}}; /* derived name */

static const ConstVec door2DownEffectPos = {{704.0f, -1955.0f, -5679.0f, 1.0f}}; /* derived name */

static ActMail door2_up_chk_mes[2] = {{377}, {376}}; /* derived name */

INCLUDE_ASM(actSt04dDoor2UpChk);

inline void actSt04dDoor2UpEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = door2UpEffectPos.d[0];
    long long v0b = door2DownEffectPos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = door2UpEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = door2DownEffectPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

inline void actSt04dDoor2DownEffect(GObj *volatile self)
{
    long long b1[2];
    long long b2[2];
    long long v0a = door2DownEffectPos.d[0];
    long long v0b = door2UpEffectPos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = door2DownEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = door2UpEffectPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

static ActMail door2_down_chk_mes[2] = {{377}, {376}}; /* derived name */

INCLUDE_ASM(actSt04dDoor2DownChk);
