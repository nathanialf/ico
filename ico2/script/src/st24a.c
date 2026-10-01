#include "st24a.h"
#include "layout_texture.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "camera-root.h"
#include "gflag.h"
#include "StageAnimation.h"
#include <libvu0.h>
#include "typedef.h"

/* The actor mail table entries this TU installs live in the shared
 * src/cod .data carve, so they stay extern here. */

static ActMail sword_mes[2] = {{430}, {429}};

static ActMail demoCam_mes[2] = {{430}, {429}};

typedef struct EditPad {
    char _p0[0x4];
    int trg; /* 0x04 */
    char _p8[0x58 - 0x8];
} EditPad;

/* kept local: void * here, GObj * in main.h */
extern void *boyGObj;
/* kept local: EditPad here, PadState [16] in main.h */
extern EditPad pad;
/* kept local: agrees with script.h, which this TU does not include (scpAdpcmFadeCloseFunc, scpAdpcmPlayRequestFunc differ) */
extern int scpBoyControlReadDisable;
/* kept local: agrees with script.h, which this TU does not include (scpAdpcmFadeCloseFunc, scpAdpcmPlayRequestFunc differ) */
extern void scpFadeIn(float t);
/* kept local: agrees with script.h, which this TU does not include (scpAdpcmFadeCloseFunc, scpAdpcmPlayRequestFunc differ) */
extern void scpFadeOut(float t, int a1, int a2, int a3);
/* kept local: agrees with script.h, which this TU does not include (scpAdpcmFadeCloseFunc, scpAdpcmPlayRequestFunc differ) */
extern int scpFadeChk(void);
/* kept local: agrees with script.h, which this TU does not include (scpAdpcmFadeCloseFunc, scpAdpcmPlayRequestFunc differ) */
extern int scpAdpcmPlayRequestNum(void);
/* kept local: int (int, void *, float) here, int (char *, char *, float) in script.h */
extern int scpTriggerBall(int self, void *target, float r);

/* the 16-byte vector this file copies whole */

typedef struct SwordObj {
    char unk00[0x2C]; /* 0x00 */
    void *unk2C;      /* 0x2C */
} SwordObj;

/* .sbss, owned by st24a.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, raised by the
   subthread the wait loop below spins for. */
static int demoEnd;

static const Vec16 swordChkPos = {{1685.0f, -1080.0f, -1000.0f, 1.0f}};

/* kept local: void (int, SwordObj **, int, int, int) here, void (int, char **, int, int, int) in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, SwordObj **h, int a2, int a3, int a4);
/* kept local: void (SwordObj **, int) here, int (char **, short) in script.h */
extern void scpAdpcmFadeCloseFunc(SwordObj **h, int a1);
/* kept local: void (void *) here, void (int) in script.h */
extern void scpPlayStart(void *a0);
/* kept local: void (void *) here, void (int) in script.h */
extern void scpPlayEnd(void *a0);
/* kept local: void (void *, int) here, void (char *, int) in script.h */
extern void scpPlayMot(void *a0, int a1);
/* kept local: void (void *, float *) here, void (char *, float *) in script.h */
extern void scpPlayMotDir(void *a0, float *dir);
/* kept local: agrees with script.h, which this TU does not include (scpAdpcmFadeCloseFunc, scpAdpcmPlayRequestFunc differ) */
extern void scpPlayPosSet(void *a0, float x, float y, float z);
/* kept local: agrees with script.h, which this TU does not include (scpAdpcmFadeCloseFunc, scpAdpcmPlayRequestFunc differ) */
extern int scpSearchGobj(int a0);
/* kept local: void (int) here, void (int, int, int, int) in script.h */
extern void scpSetBoyWeaponGObj(int a0);

/* .sdata, owned by st24a.o, in the ROM's order: the sword's object. */
SwordObj *sword = 0;

void actSt24aSwordChk(volatile int self)
{
    float v[4];
    float dir[4];
    char *th;

    while ((*(int *)(*(int *)((char *)boyGObj + 0x164) + 0x2E4) & 0x20) == 0 ||
           scpTriggerBall(self, boyGObj, 100.0f) == 0) {
        _ACTWait(1);
    }
    lt_switch_layout(55);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    gflagOn(329);
    soundSeDefPlay(1343, 0, 0, 1);
    scpAdpcmPlayRequestFunc(34, &sword, 1, 1, 0);
    th = (char *)actCreateSubThread(actSt24aSwordSub, 21);
    demoEnd = 0;
    while (demoEnd == 0 && ((pad.trg & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }
    iosThreadSetPri(th + 0x24, 34);
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

void actSt24aDemoCamChk(volatile int a0)
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
        if (pad.trg & 0x800) {
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

/* kept local: agrees with script.h, which this TU does not include (scpAdpcmFadeCloseFunc, scpAdpcmPlayRequestFunc differ) */
extern void ScpCallCameraSetTarget(float x, float y, float z);

void actSt24aSword(volatile int a0)
{
    int x = a0;
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

void actSt24aSaku(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    stage_SetAnimation(151, 0, 0);
}

void actSt24aDemoCam(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(330) == 0) {
        demoCam_mes[0].func = actSt24aDemoCamChk;
        self->mail = demoCam_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt24aSwordSub(volatile int a0)
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
