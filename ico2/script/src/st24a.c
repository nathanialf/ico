#include "common.h"
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

/* The actor mail table entries this TU installs live in the shared
 * src/cod .data carve, so they stay extern here. */
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

static ActMail sword_mes[2] = {{430}, {429}};

static ActMail demoCam_mes[2] = {{430}, {429}};

typedef struct EditPad {
    char _p0[0x4];
    int trg; /* 0x04 */
    char _p8[0x58 - 0x8];
} EditPad;

extern void *D_00639EA4;
extern EditPad D_0028F8F0;
extern int D_0063AA08;
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float t);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float t, int a1, int a2, int a3);
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);
/* kept local: this TU's uses of scpAdpcmPlayRequestNum do not fit the prototype in script.h */
extern int scpAdpcmPlayRequestNum(void);
/* kept local: this TU's uses of scpTriggerBall do not fit the prototype in script.h */
extern int scpTriggerBall(int self, void *target, float r);

/* the 16-byte vector this file copies whole */
typedef union Vec16 {
    float f[4];
    long long q[2];
} Vec16;

typedef struct SwordObj {
    char unk00[0x2C]; /* 0x00 */
    void *unk2C;      /* 0x2C */
} SwordObj;

extern SwordObj *sword;
extern int D_0063C5B0;

static const Vec16 swordChkPos = {{1685.0f, -1080.0f, -1000.0f, 1.0f}};

extern int D_0028F8F4[];
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, SwordObj **h, int a2, int a3, int a4);
/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern void scpAdpcmFadeCloseFunc(SwordObj **h, int a1);
/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
extern void scpPlayStart(void *a0);
/* kept local: this TU's uses of scpPlayEnd do not fit the prototype in script.h */
extern void scpPlayEnd(void *a0);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(void *a0, int a1);
/* kept local: this TU's uses of scpPlayMotDir do not fit the prototype in script.h */
extern void scpPlayMotDir(void *a0, float *dir);
/* kept local: this TU's uses of scpPlayPosSet do not fit the prototype in script.h */
extern void scpPlayPosSet(void *a0, float x, float y, float z);
extern void sceVu0SubVector(float *dst, float *a, void *b);
/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern int scpSearchGobj(int a0);
/* kept local: this TU's uses of scpSetBoyWeaponGObj do not fit the prototype in script.h */
extern void scpSetBoyWeaponGObj(int a0);

void actSt24aSwordChk(volatile int self)
{
    float v[4];
    float dir[4];
    char *th;

    while ((*(int *)(*(int *)((char *)D_00639EA4 + 0x164) + 0x2E4) & 0x20) == 0 ||
           scpTriggerBall(self, D_00639EA4, 100.0f) == 0) {
        _ACTWait(1);
    }
    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpPlayStart(D_00639EA4);
    gflagOn(0x149);
    soundSeDefPlay(0x53F, 0, 0, 1);
    scpAdpcmPlayRequestFunc(0x22, &sword, 1, 1, 0);
    th = (char *)actCreateSubThread(actSt24aSwordSub, 0x15);
    D_0063C5B0 = 0;
    while (D_0063C5B0 == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }
    iosThreadSetPri(th + 0x24, 0x22);
    if (D_0063C5B0 == 0) {
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
        stage_SetAnimation(0x99, 0, -1);
        scpPlayPosSet(D_00639EA4, 1685.0f, -1080.0f, -550.0f);
        *(Vec16 *)v = swordChkPos;
        sceVu0SubVector(dir, v, test_CURRENTROOT(D_00639EA4));
        scpPlayMotDir(D_00639EA4, dir);
        SetCameraFlag_LwsCutBack();
        scpSetBoyWeaponGObj(scpSearchGobj(0x832));
        scpFadeIn(3.0f);
    }
    scpPlayMot(D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);
    lt_switch_layout(0x36);
    D_0063AA08 = 0;
}

void actSt24aDemoCamChk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 700.0f) == 0) {
        _ACTWait(1);
    }
    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    gflagOn(0x14A);
    stage_SetAnimation(0x9A, 1, 0);
    SetCameraFlag_LwsCutBack();
    while (stage_CheckAnimationFinish(0x9A) == 0) {
        if (D_0028F8F0.trg & 0x800) {
            if (scpAdpcmPlayRequestNum() == 0) {
                scpFadeOut(16.0f, 0, 0, 0);
                while (scpFadeChk() != 0) {
                    _ACTWait(1);
                }
                while (lt_fade_status() != 2) {
                    _ACTWait(1);
                }
                stage_SetAnimation(0x9A, 0, -1);
                scpFadeIn(3.0f);
                break;
            }
        }
        _ACTWait(1);
    }
    lt_switch_layout(0x36);
    D_0063AA08 = 0;
}

/* kept local: this TU's uses of ScpCallCameraSetTarget do not fit the prototype in script.h */
extern void ScpCallCameraSetTarget(float x, float y, float z);

void actSt24aSword(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    ScpCallCameraSetTarget(363.0f, 1307.0f, -3297.0f);

    if (gflagChk(0x149) == 0) {
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

    stage_SetAnimation(0x97, 0, 0);
}

void actSt24aDemoCam(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x14A) == 0) {
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

    stage_SetAnimation(0x99, 1, 0);

    scpPlayMot(D_00639EA4, 250);

    while (stage_CheckAnimationFrame(0x99, 0x15, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSetBoyWeaponGObj(scpSearchGobj(0x832));

    while (stage_CheckAnimationFinish(0x99) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C5B0 = 1;
    _ACTWait(0);
}
