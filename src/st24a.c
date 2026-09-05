#include "common.h"

/* The actor mail table entries this TU installs live in the shared
 * src/cod .data carve, so they stay extern here. */
typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(int);          /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;
typedef struct Act {
    char unk00[0xD4];           /* 0x00 */
    ActMail *mail;              /* 0xD4 */
} Act;
extern Act *actInitialize(int a0);
extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int gflagChk(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern ActMail D_004FB610[];
extern void actSt24aDemoCamChk(int a0);

ASM_LIT4_SLOT(D_00639AE8, -550.0f);
ASM_LIT4_SLOT(D_00639AEC, 1685.0f);
INCLUDE_ASM("asm/nonmatchings/src/st24a", actSt24aSwordChk);
INCLUDE_ASM("asm/nonmatchings/src/st24a", actSt24aDemoCamChk);
extern ActMail D_004FB5F0[];
extern void actSt24aSwordChk(int a0);
extern void ScpCallCameraSetTarget(float x, float y, float z);

void actSt24aSword(volatile int a0) {
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
void actSt24aSaku(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    stage_SetAnimation(0x97, 0, 0);
}
void actSt24aDemoCam(volatile int a0) {
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
typedef struct SwordObj {
    char unk00[0x2C];           /* 0x00 */
    void *unk2C;                /* 0x2C */
} SwordObj;
extern SwordObj *sword;
extern void *D_00639EA4;
extern int D_0063C5B0;
extern void AdpcmPlay(void *a0);
extern void scpPlayMot(void *a0, int a1);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int scpSearchGobj(int a0);
extern void scpSetBoyWeaponGObj(int a0);

void actSt24aSwordSub(volatile int a0) {
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
