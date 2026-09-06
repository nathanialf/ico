#include "common.h"

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
extern int gflagChk(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F87D0[];
extern ActMail D_004F87B0[];
extern void actSt04bEne1Chk(int a0);
extern void actSt04bSekizoChk(int a0);
extern void ScpCallCameraSetTarget(float x, float y, float z);
extern void scpTorchLightOn(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
extern int D_00639EA8;
extern void _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);
extern void RequestStageChangeDirect(int a0, int a1, int *buf, int a3);
extern void brainUnlockGirl(void);

INCLUDE_ASM("asm/nonmatchings/src/st04b", actSt04bEnd);
ASM_LIT4_SLOT(D_00639928, -10325.0f);
ASM_LIT4_SLOT(D_0063992C, -2150.0f);
ASM_LIT4_SLOT(D_00639930, 10793.0f);
ASM_LIT4_SLOT(D_00639934, 2122.0f);
INCLUDE_ASM("asm/nonmatchings/src/st04b", actSt04bSekizoChk);
INCLUDE_ASM("asm/nonmatchings/src/st04b", actSt04bEne1Chk);
void actSt04bCrest01XL(volatile int a0) {
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xAE) == 0) {
        stage_SetAnimation(0xB9, 0, 0);
        stage_SetAnimation(0xBA, 0, 0);
    } else {
        stage_SetAnimation(0xB9, 0, -1);
        stage_SetAnimation(0xBA, 0, -1);
        scpTorchLightOn(0x420);
        scpTorchLightOn(0x421);
    }
}
void actSt04bDoorXL(volatile int a0) {
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    stage_SetAnimation(0xF9, 0, 0);
}
void actSt04bMonyoDoorXL(volatile int a0) {
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xAE) == 0) {
        stage_SetAnimation(0xFA, 0, 0);
    } else {
        stage_SetAnimation(0xFA, 0, -1);
    }
}
void actSt04bSekizo(volatile int a0) {
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x9F) == 0) {
        stage_SetAnimation(0xBF, 0, 0);
        D_004F87B0[0].func = actSt04bSekizoChk;
        self->mail = D_004F87B0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xBF, 0, -1);
        if (gflagChk(0xAE) == 0) {
            ScpCallCameraSetTarget(10793.0f, 2122.0f, 0.0f);
        }
    }
}
void actSt04bEne1(volatile int a0) {
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x9D) == 0) {
        D_004F87D0[0].func = actSt04bEne1Chk;
        self->mail = D_004F87D0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt04bEnemy1(volatile int a0) {
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);
    while (gflagChk(0x9E) == 0) {
        _ACTWait(1);
    }
    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}
void actSt04bEnemy2(volatile int a0) {
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);
    while (gflagChk(0x9E) == 0) {
        _ACTWait(1);
    }
    Generator_MaskOff(a0);

    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}
void actSt04bBallXL(volatile int a0) {
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x8A) == 0) {
        stage_SetAnimation(0x12B, -1, -2);
    } else {
        stage_SetAnimation(0x129, -1, -2);
    }
}
void actSt04bSolarXL(volatile int a0) {
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x8A) == 0) {
        stage_SetAnimation(0x12D, -1, -2);
        stage_SetAnimation(0x131, -1, -2);
    }
}
void actSt04bSekizoEvent(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/st04b", actSt04bGirlWay);
