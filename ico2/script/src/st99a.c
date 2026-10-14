#include "st99a.h"
#include "act.h"
#include "commonact.h"
#include "script.h"
#include "StageAnimation.h"
#include "typedef.h"
#include "main.h"
#include "include_asm.h"

static void actSt17aTestChk(GObj *volatile self);

static ActMail explode_mes[2] = {{397}, {396}}; /* derived name */

static ActMail splash1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail splash2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail wave_mes[2] = {{397}, {396}}; /* derived name */

static ActMail st27aWave_mes[2] = {{397}, {396}}; /* derived name */

static ActMail spider_mes[2] = {{397}, {396}}; /* derived name */

static ActMail st17aTest_mes[2] = {{397}, {396}}; /* derived name */

INCLUDE_ASM(actExplode);

INCLUDE_ASM(actSplash1);

INCLUDE_ASM(actSplash2);

INCLUDE_ASM(actWave);

INCLUDE_ASM(actSpider);

INCLUDE_ASM(actDevilLightning);

INCLUDE_ASM(actQueenLightning);

INCLUDE_ASM(actSt17aTest);

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

INCLUDE_ASM(actSpiderChk);

INCLUDE_ASM(actSt17aTestChk);
