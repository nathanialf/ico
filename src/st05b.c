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
extern void ACTSendMailCorrect(int a0, int mail);
extern ActMail D_004F9720[];
extern void actSt05bSekizoChk(int a0);
extern void ScpCallCameraSetTarget(float x, float y, float z);
extern void _ACTWait(int a0);
extern int gflagChk(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);

INCLUDE_ASM("asm/nonmatchings/src/st05b", actSt05bCrest01XL);
ASM_LIT4_SLOT(D_00639980, -2150.0f);
ASM_LIT4_SLOT(D_00639984, -10793.0f);
ASM_LIT4_SLOT(D_00639988, 2122.0f);
INCLUDE_ASM("asm/nonmatchings/src/st05b", actSt05bSekizoChk);
void actSt05bDoorXL(volatile int a0) {
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xF3) != 0 && gflagChk(0x8B) == 0) {
        stage_SetAnimation(0x159, 0, -1);
    } else {
        stage_SetAnimation(0x159, 0, 0);
    }
}
void actSt05bMonyoDoorXL(volatile int a0) {
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xEA) == 0) {
        stage_SetAnimation(0xFB, 0, 0);
    } else {
        stage_SetAnimation(0xFB, 0, -1);
    }
}
void actSt05bSekizo(volatile int a0) {
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xA0) == 0) {
        stage_SetAnimation(0xC0, 0, 0);
        D_004F9720[0].func = actSt05bSekizoChk;
        self->mail = D_004F9720;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xC0, 0, -1);
        if (gflagChk(0xF3) == 0) {
            ScpCallCameraSetTarget(-10793.0f, 2122.0f, 0.0f);
        }
    }
}
void actSt05bBallXL(volatile int a0) {
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x8B) == 0) {
        stage_SetAnimation(0x12C, -1, -2);
    } else {
        stage_SetAnimation(0x12A, -1, -2);
    }
}
void actSt05bSolarXL(volatile int a0) {
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x8B) == 0) {
        stage_SetAnimation(0x12F, -1, -2);
        stage_SetAnimation(0x132, -1, -2);
    }
}
void actSt05bSekizoEvent(int x) {
    volatile int local = x;
}
extern const long long D_00622AD0[];
extern const long long D_00622AE0[];
extern int D_00639EA8;
extern void _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);
extern void RequestStageChangeDirect(int a0, int a1, int *buf, int a3);
extern void brainUnlockGirl(void);

INCLUDE_ASM("asm/nonmatchings/src/st05b", actSt05bGirlWay);
