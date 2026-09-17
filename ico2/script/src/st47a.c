#include "common.h"
#include "st47a.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "way_llf.h"
#include "brain.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "attackCheckBoundary.h"
#include "item.h"
#include "motionManager2.h"
#include <libvu0.h>
#include <string.h>
#include "typedef.h"

/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);

void actSt47aInit(void)
{
    if (gflagChk(0x2F) != 0) {
        stage_SetAnimation(0xA6, 0, 0);
        SetWayGroupActive(0x21, 1);
    } else {
        stage_SetAnimation(0xA5, 0, 0);
        SetWayGroupActive(0x21, 0);
    }

    if (gflagChk(0x30) != 0) {
        stage_SetAnimation(0xA8, 0, 0);
        SetWayGroupActive(0x22, 1);
    } else {
        stage_SetAnimation(0xA7, 0, 0);
        SetWayGroupActive(0x22, 0);
    }
}

extern int D_00639EA8;

void actSt47aEnd(void)
{
    if (D_00639EA8 != 0) {
        if (gflagChk(0x34) == 0) {
            gflagOn(0x187);
        }
    }
}

/* the 16-byte work vector the stone-statue cutscene reuses for both motion
   directions (src/script.c's scpSekizou uses the same union) */

extern int D_00639EA4;
extern char *D_00639EAC;
extern int D_0063AA08;
/* kept local: this TU's uses of scpTriggerBall do not fit the prototype in script.h */
extern int scpTriggerBall(int a0, int gobj, float r);
/* kept local: this TU's uses of scpSleepEnemyAll do not fit the prototype in script.h */
extern void scpSleepEnemyAll(void);
/* kept local: this TU's uses of scpWakeupEnemyAll do not fit the prototype in script.h */
extern void scpWakeupEnemyAll(void);
/* kept local: this TU's uses of scpKillEnemyAll do not fit the prototype in script.h */
extern void scpKillEnemyAll(void);
/* kept local: this TU's uses of scpMaskGeneratorAll do not fit the prototype in script.h */
extern void scpMaskGeneratorAll(void);
/* kept local: this TU's uses of scpSekizouCheckPoint do not fit the prototype in script.h */
extern void scpSekizouCheckPoint(void);
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
extern void scpPlayStart(int a0);
/* kept local: this TU's uses of scpPlayEnd do not fit the prototype in script.h */
extern void scpPlayEnd(int a0);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpPlayMotDir do not fit the prototype in script.h */
extern void scpPlayMotDir(int a0, float *dir);
/* kept local: this TU's uses of scpPlayPosSet do not fit the prototype in script.h */
extern void scpPlayPosSet(int a0, float x, float y, float z);
/* kept local: this TU's uses of scpPlayWaitMotEnd do not fit the prototype in script.h */
extern void scpPlayWaitMotEnd(int a0);
/* kept local: this TU's uses of ScpCallCameraSetTarget do not fit the prototype in script.h */
extern void ScpCallCameraSetTarget(float x, float y, float z);
/* file-static sound / pad handles, .sbss 0x0063C05C..0x0063C078 */
extern int sekizo47a;
extern int sekizo_47a;
extern unsigned char sekizo_47a_vol;

void actSt47aSekizo1Chk(volatile int a0)
{
    /* sound handle owned by the sound subsystem: ROM homes it at 4(sp) across
       the whole cutscene and reloads it for soundSeDefStop. */
    volatile int se;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0 ||
           scpTriggerBall(a0, D_00639EA8, 200.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0x4B) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    brainLockGirl();

    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(0x13, &sekizo47a, 1, 1, 1);
    while (sekizo47a == 0) {
        _ACTWait(1);
    }

    gflagOn(0x186);

    stage_SetAnimation(0xA3, 1, 0);

    scpKillEnemyAll();
    scpMaskGeneratorAll();

    ReviveAllCarryableItemsWithNonSleepFrame(0x12C);

    sekizo_47a = iosPadActRequest(D_00639EAC, 9);
    sekizo_47a_vol = 128;
    iosPadActVolumeSet(sekizo_47a, 128);

    se = soundSeDefPlay(0x4C1, 0, 0, 1);

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);

    scpPlayMot(D_00639EA4, 0);
    scpPlayMot(D_00639EA8, 0x214);

    scpPlayPosSet(D_00639EA8, 1750.0f, -272.0f, 0.0f);
    scpPlayPosSet(D_00639EA4, 1750.0f, -272.0f, 50.0f);

    _ACTWait(1);
    {
        Vec16 v;

        sceVu0SubVector(v.f, test_CURRENTROOT(a0), test_CURRENTROOT(D_00639EA8));
        scpPlayMotDir(D_00639EA8, v.f);
        D_0063AA08 = 1;
        sceVu0SubVector(v.f, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
        scpPlayMotDir(D_00639EA4, v.f);

        scpSekizouCheckPoint();

        scpPlayMot(D_00639EA8, 0x285);
        scpPlayWaitMotEnd(D_00639EA8);

        gflagOn(0x2B);

        soundSeDefStop(se);
    }

    while (stage_CheckAnimationFrame(0xA3, 0x97, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(sekizo_47a);

    scpPlayMot(D_00639EA8, 0x214);
    scpPlayEnd(D_00639EA8);

    actCreateSubThread(actSt47aGirlWay, 0x15);

    _ACTWait(0x1E);

    scpPlayMot(D_00639EA4, 0xFC);
    scpPlayWaitMotEnd(D_00639EA4);

    scpPlayMot(D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);

    ScpCallCameraSetTarget(-3000.0f, 272.0f, 0.0f);

    while (stage_CheckAnimationFinish(0xA3) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpWakeupEnemyAll();

    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}

/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern int scpAdpcmFadeCloseFunc(int *a0, int a1);
/* kept local: this TU's uses of scpAdpcmPlayRequestNum do not fit the prototype in script.h */
extern int scpAdpcmPlayRequestNum(void);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float t, int a1, int a2, int a3);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);

/* the shared pad-state array (op.c's PadState, GsBase.c's GsbPad): 0x58 per
   pad, trg at 0x4. */

extern Pad D_0028F8F0[];
/* file-static sound handles, .sbss 0x0063C05C..0x0063C078 */
extern int hane1down;
/* kept local: this TU's uses of scpWakeupEnemyAll do not fit the prototype in script.h */
extern void scpWakeupEnemyAll(void);
extern int D_0063AA08;

static ActMail sekizo1_mes[2] = {{430}, {429}};

static ActMail hane1Main_mes[2] = {{406, actSt47aHane1Switch}, {429}};

static ActMail hane1_mes[2] = {{430}, {429}};

static ActMail hane1SwitchUp_mes[2] = {{430}, {429}};

static ActMail hane1SwitchDown_mes[2] = {{430}, {429}};

static ActMail hane1Down_mes[2] = {{430}, {429}};

static ActMail hane1Up_mes[2] = {{430}, {429}};

static ActMail hane2Main_mes[2] = {{407, actSt47aHane2Switch}, {429}};

static ActMail hane2_mes[2] = {{430}, {429}};

static ActMail hane2SwitchUp_mes[2] = {{430}, {429}};

static ActMail hane2SwitchDown_mes[2] = {{430}, {429}};

static ActMail hane2Down_mes[2] = {{430}, {429}};

static ActMail hane2Up_mes[2] = {{430}, {429}};

static ActMail rope_mes[2] = {{430}, {429}};

static ActMail barricade_mes[2] = {{430}, {429}};

static ActMail exit_mes[2] = {{430}, {429}};

static ActMail exit2_mes[2] = {{430}, {429}};

static ActMail ene_mes[2] = {{430}, {429}};

static ActMail hint2On_mes[2] = {{430}, {429}};

void actSt47aHane1Down(volatile int a0)
{
    Act *self = ((PObjGObj *)a0)->act;

    scpAdpcmPlayRequestFunc(0x40, &hane1down, 1, 1, 1);

    while (hane1down == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0xA5, 1, 0);

    gflagOn(0x2F);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(0xA5) == 0) {
        if ((D_0028F8F0[0].trg & 0x800) != 0 && scpAdpcmPlayRequestNum() == 0) {
            scpFadeOut(16.0f, 0, 0, 0);

            scpAdpcmFadeCloseFunc(&hane1down, 0x200);

            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }

            stage_SetAnimation(0xA5, 0, -1);

            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }

    D_0063AA08 = 0;

    lt_switch_layout(0x36);
    scpWakeupEnemyAll();

    SetWayGroupActive(0x21, 1);

    hane1Down_mes[0].func = actSt47aHane1Main;
    self->mail = hane1Down_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(int a0, int a1);
extern int hane1up;

void actSt47aHane1Up(volatile int a0)
{
    Act *self = ((PObjGObj *)a0)->act;

    if (D_00639EA8 != 0) {
        if (scpTriggerFloorAttr(D_00639EA8, 0x2000000) != 0) {
            actCreateSubThread(actSt47aHane1_1Girl, 0x15);
        }
        if (scpTriggerFloorAttr(D_00639EA8, 0x4000000) != 0) {
            actCreateSubThread(actSt47aHane1_2Girl, 0x15);
        }
    }

    scpAdpcmPlayRequestFunc(0x42, &hane1up, 1, 1, 1);

    while (hane1up == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0xA6, 1, 0);

    gflagOff(0x2F);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(0xA6) == 0) {
        if ((D_0028F8F0[0].trg & 0x800) != 0 && scpAdpcmPlayRequestNum() == 0) {
            scpFadeOut(16.0f, 0, 0, 0);

            scpAdpcmFadeCloseFunc(&hane1up, 0x200);

            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }

            stage_SetAnimation(0xA6, 0, -1);

            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }

    D_0063AA08 = 0;

    lt_switch_layout(0x36);
    scpWakeupEnemyAll();

    SetWayGroupActive(0x21, 0);

    hane1Up_mes[0].func = actSt47aHane1Main;
    self->mail = hane1Up_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern int hane2down;

void actSt47aHane2Down(volatile int a0)
{
    Act *self = ((PObjGObj *)a0)->act;

    scpAdpcmPlayRequestFunc(0x41, &hane2down, 1, 1, 1);

    while (hane2down == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0xA7, 1, 0);

    gflagOn(0x30);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(0xA7) == 0) {
        if ((D_0028F8F0[0].trg & 0x800) != 0 && scpAdpcmPlayRequestNum() == 0) {
            scpFadeOut(16.0f, 0, 0, 0);

            scpAdpcmFadeCloseFunc(&hane2down, 0x200);

            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }

            stage_SetAnimation(0xA7, 0, -1);

            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }

    D_0063AA08 = 0;

    lt_switch_layout(0x36);
    scpWakeupEnemyAll();

    SetWayGroupActive(0x22, 1);

    hane2Down_mes[0].func = actSt47aHane2Main;
    self->mail = hane2Down_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern int hane2up;

void actSt47aHane2Up(volatile int a0)
{
    Act *self = ((PObjGObj *)a0)->act;

    if (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x3000000) != 0) {
        actCreateSubThread(actSt47aHane2Girl, 0x15);
    }

    scpAdpcmPlayRequestFunc(0x43, &hane2up, 1, 1, 1);

    while (hane2up == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0xA8, 1, 0);

    gflagOff(0x30);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(0xA8) == 0) {
        if ((D_0028F8F0[0].trg & 0x800) != 0 && scpAdpcmPlayRequestNum() == 0) {
            scpFadeOut(16.0f, 0, 0, 0);

            scpAdpcmFadeCloseFunc(&hane2up, 0x200);

            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }

            stage_SetAnimation(0xA8, 0, -1);

            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }

    D_0063AA08 = 0;

    lt_switch_layout(0x36);
    scpWakeupEnemyAll();

    SetWayGroupActive(0x22, 0);

    hane2Up_mes[0].func = actSt47aHane2Main;
    self->mail = hane2Up_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt47aRope(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x31) == 0) {
        stage_SetAnimation(0xA9, 0, 0);
        scpSearchGobj(0x1F7)->f16C = 0;
        rope_mes[0].func = actSt47aRopeChk;
        self->mail = rope_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xAA, 0, -1);
        scpSearchGobj(0x1F7)->f16C = 1;
        scpSearchGobj(0x1E2)->f16C = 0;
        FinishHint(5);
    }
}

/* kept local: this TU's uses of scpSleepEnemyAll do not fit the prototype in script.h */
extern void scpSleepEnemyAll(void);
extern int D_0063C5B4;

void actSt47aRopeChk(volatile int a0)
{
    int x = a0;
    int th;

    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(0x31) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(0x1E2))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(0xA9, 1, 0);
            while (stage_CheckAnimationFinish(0xA9) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(0x1E2)->f16C = 0;

            lt_switch_layout(0x37);
            D_0063AA08 = 1;

            gflagOn(0x31);
            FinishHint(5);

            scpSleepEnemyAll();

            th = actCreateSubThread(actSt47aRopeSub, 0x15);

            D_0063C5B4 = 0;
            while (D_0063C5B4 == 0 &&
                   ((D_0028F8F0[0].trg & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
                _ACTWait(1);
            }

            iosThreadSetPri(th + 0x24, 0x22);

            if (D_0063C5B4 == 0) {
                scpFadeOut(16.0f, 0, 0, 0);
                while (scpFadeChk() != 0) {
                    _ACTWait(1);
                }
                while (lt_fade_status() != 2) {
                    _ACTWait(1);
                }
                stage_SetAnimation(0xAA, 0, -1);
                scpSearchGobj(0x1F7)->f16C = 1;
                scpFadeIn(3.0f);
            }

            scpWakeupEnemyAll();
            D_0063AA08 = 0;
            lt_switch_layout(0x36);
            break;
        }
    }
}

/* kept local: this TU's uses of scpIsBombExplode do not fit the prototype in script.h */
extern int scpIsBombExplode(int a0);
/* kept local: this TU's uses of scpTriggerBall do not fit the prototype in script.h */
extern int scpTriggerBall(int a0, int gobj, float r);
/* kept local: this TU's uses of scpSleepEnemyAll do not fit the prototype in script.h */
extern void scpSleepEnemyAll(void);
/* kept local: this TU's uses of scpWakeupEnemyAll do not fit the prototype in script.h */
extern void scpWakeupEnemyAll(void);
extern int D_0028F4C0[];
extern int D_0063AA08;

void actSt47aBarricadeChk(volatile int a0)
{
    int n;

    while ((n = scpIsBombExplode(0x13)) == 0 || scpTriggerBall(a0, n, 350.0f) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    FinishHint(4);
    FinishHint(6);

    scpSleepEnemyAll();

    _ACTWait(5);

    stage_SetAnimation(0xAB, 1, 0);

    gflagOn(0x32);

    while (stage_CheckAnimationFinish(0xAB) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 3);

    D_0063AA08 = 0;
    lt_switch_layout(0x36);

    scpWakeupEnemyAll();
}

void actSt47aEnemy1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    Generator_Mask((int)scpSearchGobj(0x201));

    while (gflagChk(0x35) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);

    Generator_Call((int)scpSearchGobj(0x201));
}

/* kept local: this TU's uses of scpTorchLightOn do not fit the prototype in script.h */
extern void scpTorchLightOn(int a0);

void actSt47aTorch(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x99) != 0) {
        scpTorchLightOn(0x1E9);
        scpTorchLightOn(0x1EA);
        scpTorchLightOn(0x1EB);
        scpTorchLightOn(0x1EC);
        scpTorchLightOn(0x1ED);
        scpTorchLightOn(0x1EE);
        scpTorchLightOn(0x1EF);
        scpTorchLightOn(0x1F0);
        scpTorchLightOn(0x1F1);
        scpTorchLightOn(0x1F2);
        scpTorchLightOn(0x1F3);
        scpTorchLightOn(0x1F4);
        scpTorchLightOn(0x1F5);
        scpTorchLightOn(0x1F6);
    }
}

/* kept local: this TU's uses of ScpCallCameraSetTarget do not fit the prototype in script.h */
extern void ScpCallCameraSetTarget(float x, float y, float z);

void actSt47aSekizo1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x2B) == 0) {
        stage_SetAnimation(0xA3, 0, 0);
        sekizo1_mes[0].func = actSt47aSekizo1Chk;
        self->mail = sekizo1_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xA3, 0, -1);
        if (gflagChk(0x89) == 0) {
            ScpCallCameraSetTarget(-3000.0f, 272.0f, 0.0f);
        }
    }
}

/* kept local: this TU's uses of scpSekizou do not fit the prototype in script.h */
extern void scpSekizou(int a0, int a1, int a2, int a3, int a4, float x1, float y1, float z1,
                       float x2, float y2, float z2);

void actSt47aSekizo2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x2C, 0xA4, 0, 0x12, -2450.0f, -1372.0f, -1150.0f, -2450.0f, -1372.0f, -1250.0f);
}

void actSt47aHane1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    gflagChk(0x2F);

    hane1_mes[0].func = actSt47aHane1Main;
    self->mail = hane1_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt47aHane2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    hane2_mes[0].func = actSt47aHane2Main;
    self->mail = hane2_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt47aBarricade(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x32) == 0) {
        stage_SetAnimation(0xAB, 0, 0);
        barricade_mes[0].func = actSt47aBarricadeChk;
        self->mail = barricade_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        FinishHint(4);
        FinishHint(6);
        stage_SetAnimation(0xAB, 0, -1);
    }
}

void actSt47aExit(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    exit_mes[0].func = actSt47aExitChk;
    self->mail = exit_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt47aExit2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x90) != 0) {
        exit2_mes[0].func = actSt47aExit2Chk;
        self->mail = exit2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt47aEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x34) == 0) {
        ene_mes[0].func = actSt47aEneChk;
        self->mail = ene_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt47aEnemy2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x35) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0xB4);

    Generator_MaskOff(a0);
    Generator_Call(a0);

    _ACTWait(0x3C);

    Generator_Call(a0);
}

void actSt47aEnemy3(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x35) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0xB4);

    Generator_MaskOff(a0);
    Generator_Call(a0);

    _ACTWait(0x3C);

    Generator_Call(a0);
}

void actSt47aEnemy4(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x35) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(a0);
}

void actSt47aHint2On(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x36) == 0) {
        SleepHint(5);

        hint2On_mes[0].func = actSt47aHint2OnChk;
        self->mail = hint2On_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt47aSekizo1Event(int x)
{
    volatile int local = x;
}

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads, which is what makes gcc
   emit the ld/sd pair the ROM has. */

static const ConstVec girlWayPos = {{2266.0f, -272.0f, 0.0f, 0.0f}};

static const ConstVec hane1_1GirlPos = {{-1076.0f, -1972.0f, 755.0f, 0.0f}};

static const ConstVec hane1_2GirlPos = {{1028.0f, -1972.0f, 744.0f, 0.0f}};

static const ConstVec hane2GirlPos = {{-1031.0f, -1972.0f, -747.0f, 0.0f}};

/* kept local: this TU's uses of _SCPMoveCharactorByWay do not fit the prototype in script.h */
extern void _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);
/* kept local: this TU's uses of RequestStageChangeDirect do not fit the prototype in script.h */
extern void RequestStageChangeDirect(int a0, int a1, int *buf, int a3);

void actSt47aGirlWay(volatile int a0)
{
    long long buf[2];
    long long way[2];

    buf[0] = girlWayPos.d[0];
    buf[1] = girlWayPos.d[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);

    memset(way, 0, 0x10);
    RequestStageChangeDirect(D_00639EA8, 0xB, (int *)way, 0xB4);
    brainUnlockGirl();
}

void actSt47aSekizo2Event(int x)
{
    volatile int local = x;
}

void actSt47aHane1Main(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = hane1Main_mes;
    while (1) {
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of scpSleepEnemyAll do not fit the prototype in script.h */
extern void scpSleepEnemyAll(void);
extern int D_0063AA08;

void actSt47aHane1Switch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    if (gflagChk(0x2F) != 0) {
        hane1SwitchUp_mes[0].func = actSt47aHane1Up;
        sub->mail = hane1SwitchUp_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }

    hane1SwitchDown_mes[0].func = actSt47aHane1Down;
    sub->mail = hane1SwitchDown_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern int D_00639EA8;
/* kept local: this TU's uses of _SCPMoveCharactorByWay do not fit the prototype in script.h */
extern void _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);

void actSt47aHane1_1Girl(volatile int a0)
{
    long long buf[2];
    buf[0] = hane1_1GirlPos.d[0];
    buf[1] = hane1_1GirlPos.d[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);
}

void actSt47aHane1_2Girl(volatile int a0)
{
    long long buf[2];
    buf[0] = hane1_2GirlPos.d[0];
    buf[1] = hane1_2GirlPos.d[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);
}

void actSt47aHane2Main(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = hane2Main_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt47aHane2Switch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    if (gflagChk(0x30) != 0) {
        hane2SwitchUp_mes[0].func = actSt47aHane2Up;
        sub->mail = hane2SwitchUp_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }

    hane2SwitchDown_mes[0].func = actSt47aHane2Down;
    sub->mail = hane2SwitchDown_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt47aHane2Girl(volatile int a0)
{
    long long buf[2];
    buf[0] = hane2GirlPos.d[0];
    buf[1] = hane2GirlPos.d[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);
}

extern int D_0063C5B4;

void actSt47aRopeSub(volatile int a0)
{
    _ACTWait(0xF);

    stage_SetAnimation(0xAA, 1, 0);

    while (stage_CheckAnimationFrame(0xAA, 0x94, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSearchGobj(0x1F7)->f16C = 1;

    while (stage_CheckAnimationFinish(0xAA) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C5B4 = 1;
    _ACTWait(0);
}

void actSt47aBarricadeEvent(int x)
{
    volatile int local = x;
}

void actSt47aExitChk(volatile int a0)
{
    scpSearchGobj(0x1E1)->f16C = 0;

    while ((gflagChk(0xAE) == 0) || (gflagChk(0xEA) == 0)) {
        _ACTWait(1);
    }

    gflagOn(0x33);
    scpSearchGobj(0x1E0)->f16C = 0;
    scpSearchGobj(0x1E1)->f16C = 1;
}

void actSt47aExit2Chk(volatile int a0)
{
    scpSearchGobj(0x1E0)->f16C = 1;
    scpSearchGobj(0x1E1)->f16C = 0;
}

/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(int a0, int a1);

void actSt47aEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA8, 0x1000000) == 0) {
        _ACTWait(1);
    }

    gflagOff(0x187);
    _ACTWait(1);
    gflagOn(0x34);
    gflagOn(0x35);
}

void actSt47aHint2OnChk(volatile int a0)
{
    while (gflagChk(0x2F) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x36);
    WakeupHint(5);
}
