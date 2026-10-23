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

static ActMail sword_mes[2] = {{393}, {392}}; /* derived name */

static const Vec16 swordChkPos = {{1685.0f, -1080.0f, -1000.0f, 1.0f}}; /* derived name */

/* .sdata: the sword's object. */
SqEntry *sword = 0;

void actSt24aSwordChk(GObj *volatile self)
{
    float v[4];
    float dir[4];

    while (scpGameStat_BoyWeaponkind() != 5 || scpTriggerBall(self, boyGObj, 300.0f) == 0) {
        _ACTWait(1);
    }
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    scpPlayMot(boyGObj, 0);
    gflagOn(299);
    soundSeDefPlay(1316, 0, 0, 1);
    _ACTWait(60);
    scpAdpcmPlayRequestFunc(33, &sword, 1, 1, 1);
    while (sword == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(132, 1, 0);
    scpPlayPosSet(boyGObj, 1685.0f, -1080.0f, -550.0f);
    *(Vec16 *)v = swordChkPos;
    sceVu0SubVector(dir, v, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);
    _ACTWait(300);
    scpPlayMot(boyGObj, 246);
    while (stage_CheckAnimationFinish(132) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

void actSt24aSword(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    ScpCallCameraSetTarget(363.0f, 1307.0f, -3297.0f);

    if (gflagChk(299) == 0) {
        sword_mes[0].func = actSt24aSwordChk;
        act->mail = sword_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
}

void actSt24aSaku(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);
    _ACTWait(1);

    stage_SetAnimation(130, 0, 0);
}
