#include "st99a.h"
#include "act.h"
#include "commonact.h"
#include "script.h"
#include "StageAnimation.h"
#include "typedef.h"
#include "main.h"
#include "include_asm.h"

static ActMail explode_mes[2] = {{393}, {392}}; /* derived name */

static ActMail splash1_mes[2] = {{393}, {392}}; /* derived name */

static ActMail splash2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail wave_mes[2] = {{393}, {392}}; /* derived name */

static ActMail st27aWave_mes[2] = {{393}, {392}}; /* derived name */

static ActMail spider_mes[2] = {{393}, {392}}; /* derived name */

INCLUDE_ASM(actExplode);

INCLUDE_ASM(actSplash1);

INCLUDE_ASM(actSplash2);

INCLUDE_ASM(actWave);

INCLUDE_ASM(actSpider);

INCLUDE_ASM(actDevilLightning);

INCLUDE_ASM(actQueenLightning);

INCLUDE_ASM(actSt27aWave);

INCLUDE_ASM(actExplodeChk);

INCLUDE_ASM(actSplash1Chk);

INCLUDE_ASM(actSplash2Chk);

void actWaveChk(GObj *volatile self)
{
    actCreateSubThread(actWave1, 21);
}

INCLUDE_ASM(actWave1);

void actSt27aWaveChk(GObj *volatile self)
{
    actCreateSubThread(actSt27aWave1, 21);
}

INCLUDE_ASM(actSt27aWave1);

void actSpiderChk(GObj *volatile self)
{
    while (1) {
        while ((GOBJ_ACT(boyGObj)->pad.trg & 0x400) == 0) {
            _ACTWait(1);
        }
        scpBornSpider(2, 0.0f, -500.0f, 0.0f, 500.0f);
        _ACTWait(1);
    }
}
