#include "st22a.h"
#include "StageManager.h"
#include "layout_texture.h"
#include "thread.h"
#include "adpcm_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "camera-root.h"
#include "gflag.h"
#include "script.h"
#include "StageAnimation.h"
#include <libvu0.h>
#include "st04c.h"
#include "typedef.h"
#include "main.h"

/* .sdata: the intro's stream handle. */
struct SqEntry *lightning = 0;

static ActMail intro_mes[2] = {{377}, {376}}; /* derived name */

/* the point the boy turns to face at the end of the intro */
static const StVec introFacePos = {{-2000.0f, 0.0f, -1129.0f, 1.0f}}; /* derived name */

void actSt22aIntroChk(GObj *volatile self)
{
    StVec pos;
    float dir[4];

    while (scpTriggerBall(self, boyGObj, 1000.0f) == 0) {
        _ACTWait(1);
    }
    CheckPoint();
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    gflagOn(281);
    stage_SetAnimation(634, 1, 0);
    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 10);
    scpFadeIn(6.0f);
    stage_SetAnimation(634, 1, 0);
    scpPlayMot(boyGObj, 400);
    while (stage_ContinueAnimation(634, 635) == 0) {
        _ACTWait(1);
    }
    scpPlayPosSet(boyGObj, -707.0f, 148.0f, -1112.0f);
    pos = introFacePos;
    sceVu0SubVector(dir, &pos, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);
    scpPlayMot(boyGObj, 401);
    while (stage_CheckAnimationFinish(635) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

void actSt22aIntro(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);
    scpAdpcmPlayRequestFunc(87, &lightning, 1, 0, 1);
    if (gflagChk(281) == 0) {
        scpFadeOut(255.0f, 0, 0, 0);
        intro_mes[0].func = actSt22aIntroChk;
        act->mail = intro_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}
