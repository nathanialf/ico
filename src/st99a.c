#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st99a", actExplode);
INCLUDE_ASM("asm/nonmatchings/src/st99a", actSplash1);
INCLUDE_ASM("asm/nonmatchings/src/st99a", actSplash2);
INCLUDE_ASM("asm/nonmatchings/src/st99a", actWave);
INCLUDE_ASM("asm/nonmatchings/src/st99a", actSpider);
INCLUDE_ASM("asm/nonmatchings/src/st99a", actDevilLightning);
INCLUDE_ASM("asm/nonmatchings/src/st99a", actQueenLightning);
INCLUDE_ASM("asm/nonmatchings/src/st99a", actSt17aTest);
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
extern ActMail D_004FB910[];
extern void actSt27aWaveChk(int a0);

void actSt27aWave(volatile int a0) {
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    D_004FB910[0].func = actSt27aWaveChk;
    self->mail = D_004FB910;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern int scpSearchGobj(int a0);
extern void scpGetWallCollision(float a0, float a1, float a2, float a3, float a4, float a5);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void scpLinkBGAtoLayoutedTarget(int a0, int a1);
extern int stage_CheckAnimationFinish(int a0);

void actExplodeChk(volatile int a0)
{
    *(int *)(*(int *)(scpSearchGobj(0xBC6) + 0x15C) + 0x4E8) = 1;
    *(int *)(*(int *)(scpSearchGobj(0xBC6) + 0x15C) + 0x4E8) = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(0x3C);
    stage_SetAnimation(0x1FF, 1, 0);
    scpLinkBGAtoLayoutedTarget(0xBC6, 0x1FF);
    while (stage_CheckAnimationFinish(0x1FF) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}
void actSplash1Chk(volatile int a0)
{
    *(int *)(*(int *)(scpSearchGobj(0xBC7) + 0x15C) + 0x4E8) = 1;
    *(int *)(*(int *)(scpSearchGobj(0xBC7) + 0x15C) + 0x4E8) = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(0x3C);
    stage_SetAnimation(0x1F2, 1, 0);
    scpLinkBGAtoLayoutedTarget(0xBC7, 0x1F2);
    while (stage_CheckAnimationFinish(0x1F2) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}
void actSplash2Chk(volatile int a0)
{
    *(int *)(*(int *)(scpSearchGobj(0xBC8) + 0x15C) + 0x4E8) = 1;
    *(int *)(*(int *)(scpSearchGobj(0xBC8) + 0x15C) + 0x4E8) = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(0x3C);
    stage_SetAnimation(0x1F3, 1, 0);
    scpLinkBGAtoLayoutedTarget(0xBC8, 0x1F3);
    while (stage_CheckAnimationFinish(0x1F3) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}
extern void actCreateSubThread(void *entry, int prio);
extern void actWave1(int a0);

void actWaveChk(volatile int a0) {
    actCreateSubThread(actWave1, 0x15);
}
void actWave1(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    while (1) {
        stage_SetAnimation(0x207, 1, 0);
        _ACTWait(0xB3);
        stage_SetAnimation(0x208, 1, 0);
        _ACTWait(0xB3);
        stage_SetAnimation(0x209, 1, 0);
        _ACTWait(0xB3);
        stage_SetAnimation(0x20A, 1, 0);
        _ACTWait(0xB3);
    }
}
extern void actSt27aWave1(int a0);

void actSt27aWaveChk(volatile int a0) {
    actCreateSubThread(actSt27aWave1, 0x15);
}
void actSt27aWave1(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    while (1) {
        stage_SetAnimation(0xC2, 1, 0);
        _ACTWait(0xC8);
        stage_SetAnimation(0xC3, 1, 0);
        _ACTWait(0xC8);
        stage_SetAnimation(0xC4, 1, 0);
        _ACTWait(0xC8);
        stage_SetAnimation(0xC5, 1, 0);
        _ACTWait(0xC8);
    }
}
extern int D_00639EA4;
extern void scpBornSpider(int n, float a, float b, float c, float d);

void actSpiderChk(volatile int a0)
{
    while (1) {
        while ((*(int *)(*(int *)(D_00639EA4 + 0x164) + 0x2E4) & 0x400) == 0) {
            _ACTWait(1);
        }
        scpBornSpider(2, 0.0f, -500.0f, 0.0f, 500.0f);
        _ACTWait(1);
    }
}
typedef struct PadState {
    int unk00;                  /* 0x00 */
    int flags;                  /* 0x04 */
    char unk08[0x50];           /* 0x08 */
} PadState;
extern PadState D_0028F8F0[];

void actSt17aTestChk(volatile int a0)
{
    while (1) {
        while ((D_0028F8F0[1].flags & 0x20) == 0) {
            _ACTWait(1);
        }
        stage_SetAnimation(0x54, 1, 0);
        _ACTWait(1);
    }
}
