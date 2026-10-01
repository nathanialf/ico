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

/* The actor mail table entries this TU installs live in the shared
 * src/cod .data carve, so they stay extern here. */

static ActMail sword_mes[2] = {{430}, {429}};

static ActMail demoCam_mes[2] = {{430}, {429}};

/* the 16-byte vector this file copies whole */

typedef struct SwordObj {
    char pad0[44]; /* 0x00 */
    void *unk2C;   /* 0x2C */
} SwordObj;

/* .sbss, owned by st24a.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, raised by the
   subthread the wait loop below spins for. */
static int demoEnd;

static const Vec16 swordChkPos = {{1685.0f, -1080.0f, -1000.0f, 1.0f}};

/* .sdata, owned by st24a.o, in the ROM's order: the sword's object. */
SwordObj *sword = 0;

void actSt24aSwordChk(volatile int self)
{
    float v[4];
    float dir[4];
    GProc *th;

    while ((GOBJ_ACT(boyGObj)->padTrg & 0x20) == 0 || scpTriggerBall(self, boyGObj, 100.0f) == 0) {
        _ACTWait(1);
    }
    lt_switch_layout(55);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    gflagOn(329);
    soundSeDefPlay(1343, 0, 0, 1);
    scpAdpcmPlayRequestFunc(34, &sword, 1, 1, 0);
    th = actCreateSubThread(actSt24aSwordSub, 21);
    demoEnd = 0;
    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }
    iosThreadSetPri(&th->thread, 34);
    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        while (sword == 0) {
            _ACTWait(1);
        }
        scpAdpcmFadeCloseFunc(&sword, 0x200);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
        stage_SetAnimation(153, 0, -1);
        scpPlayPosSet(boyGObj, 1685.0f, -1080.0f, -550.0f);
        *(Vec16 *)v = swordChkPos;
        sceVu0SubVector(dir, v, test_CURRENTROOT(boyGObj));
        scpPlayMotDir(boyGObj, dir);
        SetCameraFlag_LwsCutBack();
        scpSetBoyWeaponGObj(scpSearchGobj(2098));
        scpFadeIn(3.0f);
    }
    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    lt_switch_layout(54);
    scpBoyControlReadDisable = 0;
}

void actSt24aDemoCamChk(GObj *volatile a0)
{
    while (scpTriggerBall(a0, boyGObj, 700.0f) == 0) {
        _ACTWait(1);
    }
    lt_switch_layout(55);
    scpBoyControlReadDisable = 1;
    gflagOn(330);
    stage_SetAnimation(154, 1, 0);
    SetCameraFlag_LwsCutBack();
    while (stage_CheckAnimationFinish(154) == 0) {
        if (pad[0].flags & 0x800) {
            if (scpAdpcmPlayRequestNum() == 0) {
                scpFadeOut(16.0f, 0, 0, 0);
                while (scpFadeChk() != 0) {
                    _ACTWait(1);
                }
                while (lt_fade_status() != 2) {
                    _ACTWait(1);
                }
                stage_SetAnimation(154, 0, -1);
                scpFadeIn(3.0f);
                break;
            }
        }
        _ACTWait(1);
    }
    lt_switch_layout(54);
    scpBoyControlReadDisable = 0;
}

void actSt24aSword(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    ScpCallCameraSetTarget(363.0f, 1307.0f, -3297.0f);

    if (gflagChk(329) == 0) {
        sword_mes[0].func = actSt24aSwordChk;
        self->mail = sword_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt24aSaku(GObj *volatile a0)
{
    GObj *x = a0;
    actInitialize(a0);
    _ACTWait(1);

    stage_SetAnimation(151, 0, 0);
}

void actSt24aDemoCam(GObj *volatile a0)
{
    GObj *x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(330) == 0) {
        demoCam_mes[0].func = actSt24aDemoCamChk;
        self->mail = demoCam_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt24aSwordSub(GObj *volatile a0)
{
    while (sword == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(sword->unk2C);

    stage_SetAnimation(153, 1, 0);

    scpPlayMot(boyGObj, 250);

    while (stage_CheckAnimationFrame(153, 21, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSetBoyWeaponGObj(scpSearchGobj(2098));

    while (stage_CheckAnimationFinish(153) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}
