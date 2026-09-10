#include "common.h"

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

extern Act *actInitialize(int a0);
extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int gflagChk(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern ActMail D_004FB610[];
extern void actSt24aDemoCamChk(int a0);

typedef struct EditPad {
    char _p0[0x4];
    int trg; /* 0x04 */
    char _p8[0x58 - 0x8];
} EditPad;

extern void *D_00639EA4;
extern EditPad D_0028F8F0;
extern int D_0063AA08;
extern void gflagOn(int flag);
extern void lt_switch_layout(int n);
extern int lt_fade_status(void);
extern void scpFadeIn(float t);
extern void scpFadeOut(float t, int a1, int a2, int a3);
extern int scpFadeChk(void);
extern int scpAdpcmPlayRequestNum(void);
extern int scpTriggerBall(int self, void *target, float r);
extern int stage_CheckAnimationFinish(int a0);
extern void SetCameraFlag_LwsCutBack(void);

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
extern Vec16 D_006230A0;
extern int D_0028F8F4[];
extern void actSt24aSwordSub(int a0);
extern int actCreateSubThread(void *fn, int pri);
extern void iosThreadSetPri(char *th, int pri);
extern void scpAdpcmPlayRequestFunc(int a0, SwordObj **h, int a2, int a3, int a4);
extern void scpAdpcmFadeCloseFunc(SwordObj **h, int a1);
extern void soundSeDefPlay(int a0, int a1, int a2, int a3);
extern void scpPlayStart(void *a0);
extern void scpPlayEnd(void *a0);
extern void scpPlayMot(void *a0, int a1);
extern void scpPlayMotDir(void *a0, float *dir);
extern void scpPlayPosSet(void *a0, float x, float y, float z);
extern void *test_CURRENTROOT(void *gobj);
extern void sceVu0SubVector(float *dst, float *a, void *b);
extern int scpSearchGobj(int a0);
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
        *(Vec16 *)v = D_006230A0;
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

extern ActMail D_004FB5F0[];
extern void actSt24aSwordChk(int a0);
extern void ScpCallCameraSetTarget(float x, float y, float z);

void actSt24aSword(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    ScpCallCameraSetTarget(363.0f, 1307.0f, -3297.0f);

    if (gflagChk(0x149) == 0) {
        D_004FB5F0[0].func = actSt24aSwordChk;
        self->mail = D_004FB5F0;
        ACTSendMailCorrect(a0, 0x1AE);
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
        D_004FB610[0].func = actSt24aDemoCamChk;
        self->mail = D_004FB610;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern void AdpcmPlay(void *a0);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);

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
