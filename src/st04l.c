#include "common.h"

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;
typedef struct Act {
    char unk00[0xD0];  /* 0x00 */
    ActMail *mainMail; /* 0xD0 */
    ActMail *mail;     /* 0xD4 */
} Act;
typedef struct PObjGObj {
    char pad00[0x164]; /* 0x000 */
    Act *act;          /* 0x164 */
    char pad168[0x4];  /* 0x168 */
    int f16C;          /* 0x16C */
} PObjGObj;

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void gflagOn(int a0);
extern PObjGObj *scpSearchGobj(int a0);
extern void SetWayGroupActive(int a0, int a1);
extern int scpIsTorchLightOn(int a0);
extern void scpTorchLightOn(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int D_0063AA08;
typedef struct Pad {
    int on;  /* 0x00 */
    int trg; /* 0x04 */
} Pad;
extern Pad D_0028F8F0[];
extern int D_0028F8F4[];
extern int crest2;
extern int crest1;
extern int ball2_4l;
extern int ball3_4l;
extern void fightSoundProcessRequestPause(void);
extern int fightSoundPlayChk(void);
extern void SetCameraFlag_LwsCutBack(void);
extern int scpGameStat_BoyWeaponkind(void);
extern int ForMotionViewer_GetCurrentMotion(void *a0);
extern void gflagOff(int a0);
extern int actCreateSubThread(void *entry, int prio);
extern void iosThreadSetPri(int a0, int a1);
extern int scpAdpcmFadeCloseFunc(void *a0, int a1);
extern int scpAdpcmPlayRequestNum(void);
extern int scpFadeChk(void);
extern void scpFadeIn(float f);
extern int lt_fade_status(void);
extern void preload(int idx);
extern int RequestStageChange(int a0, void *a1, int a2, float a3, float a4);
extern void scpWakeupEnemyAll(void);
typedef struct AdpcmReq {
    char pad00[0x2C]; /* 0x00 */
    int unk2C;        /* 0x2C */
} AdpcmReq;
extern AdpcmReq *st04d_hasi;
extern AdpcmReq *sekizo4c;
extern int D_00639EAC;
extern unsigned char oridown4c;
extern unsigned int oriup4c;
extern int D_0063C530;
extern unsigned int ball1_4l;
extern int D_0028F4C0[];
extern int iosPadActRequest(int port, int id);
extern int *iosPadActVolumeSet(int key, unsigned int val);
extern void iosPadActStop(int key);
extern void AdpcmPlay(int a0);
extern void scpAdpcmPlayRequestFunc(int a0, void *a1, int a2, int a3, int a4);
extern float D_0063AA0C;
extern int D_00639ED4;
extern int sekizo_4r;
extern void actSt04rBrgCommon(volatile int a0);
extern void lt_switch_layout(int a0);
extern void WakeupHint(int a0);
extern int scpTriggerBall(int a0, void *a1, float radius);
extern void scpPlayMot(void *a0, int mot);
extern void SetGirlDangerGObj(void *a0);
extern void ClearGirlDangerGObj(void);
extern int ACTGame_NoWeapon(void *a0);
extern void *GetBoyWeaponGObj(void);
extern void LightTorchOffOfWeapon(void *o);
extern void scpFadeOut(float t, int a1, int a2, int a3);
extern int GetAttackCheckBoundaryManagerStatus(PObjGObj *a0);
extern void *D_00639EA4;
extern void *D_00639EA8;
extern int scpTriggerFloorAttr(void *obj, int attr);
extern void scpPlayStart(void *a0);
extern void scpPlayEnd(void *a0);
extern void scpPlayMotReq(void *a0, int mot);
extern void iosOmSendMail(void *gobj, int mail, void *src);
extern int soundSeDefPlay(int se, int a1, int a2, int a3);
extern void scpSleepEnemyAll(void);
extern void scpWakeupEnemyAll(void);
extern int ACTGame_FLAG_TETSUNAGI(void);
extern void ACTGame_ConnectHand(void);
extern void FinishHint(int a0);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern int D_0063C52C;
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
extern void SleepHint(int a0);
extern int stage_CheckAnimationFinish(int a0);
extern int D_0063C51C;
extern int D_0063C520;
extern int D_0063C524;
extern int D_0063C528;
extern void actSt04lBallTurnCommon(volatile int a0);
extern AdpcmReq *crest3;
extern AdpcmReq *stair4d;
extern const long long D_00622AB0[];
extern int D_0063C534;
extern unsigned int st04l_yure;
extern unsigned char st04l_yure_vol;
extern void scpKillEnemyAll(void);
extern void scpMaskGeneratorAll(void);
extern void scpPlayPosSet(void *a0, float x, float y, float z);
extern void scpPlayMotDir(void *a0, float *dir);
extern void sceVu0SubVector(float *d, const void *a, const void *b);
extern void *test_CURRENTROOT(void *a0);
extern void scpSekizouCheckPoint(void);
extern void scpPlayWaitMotEnd(void *a0);
extern void scpSleepEnemyOne(int a0);
extern void scpWakeupEnemyOne(int a0);

void actSt04cInit(void)
{
    if (gflagChk(0xD4) == 0) {
        stage_SetAnimation(0xEA, 0, 0);
    } else {
        stage_SetAnimation(0xEA, 0, -1);
    }

    if (gflagChk(0xD5) == 0) {
        stage_SetAnimation(0xEB, 0, 0);
    } else {
        stage_SetAnimation(0xEB, 0, -1);
    }

    if (gflagChk(0xD6) == 0) {
        stage_SetAnimation(0xEC, 0, 0);
    } else {
        stage_SetAnimation(0xEC, 0, -1);
    }

    if (gflagChk(0xD7) == 0) {
        stage_SetAnimation(0xED, 0, 0);
    } else {
        stage_SetAnimation(0xED, 0, -1);
    }

    if (gflagChk(0xD8) == 0) {
        stage_SetAnimation(0xEE, 0, 0);
    } else {
        stage_SetAnimation(0xEE, 0, -1);
    }

    if (gflagChk(0xD9) == 0) {
        stage_SetAnimation(0xEF, 0, 0);
    } else {
        stage_SetAnimation(0xEF, 0, -1);
    }

    if (gflagChk(0xDA) == 0) {
        stage_SetAnimation(0xF0, 0, 0);
    } else {
        stage_SetAnimation(0xF0, 0, -1);
    }

    if (gflagChk(0xBC) == 0) {
        SetWayGroupActive(1, 0);
    } else {
        SetWayGroupActive(1, 1);
    }

    if (gflagChk(0xB6) == 0) {
        stage_SetAnimation(0xE0, 0, 0);
    } else {
        stage_SetAnimation(0xE0, 0, -1);
    }

    if (gflagChk(0xB7) == 0) {
        stage_SetAnimation(0xE1, 0, 0);
    } else {
        stage_SetAnimation(0xE1, 0, -1);
    }
}
void actSt04dInit(void)
{
    if (gflagChk(0xB4) == 0) {
        stage_SetAnimation(0xE3, 0, 0);
        stage_SetAnimation(0x102, 0, 0);
    } else {
        stage_SetAnimation(0xE3, 0, -1);
        stage_SetAnimation(0x102, 0, -1);
        FinishHint(0x11);
    }

    if (gflagChk(0xB6) == 0) {
        stage_SetAnimation(0xE0, 0, 0);
        SetWayGroupActive(3, 0);
    } else {
        stage_SetAnimation(0xE0, 0, -1);
        SetWayGroupActive(3, 1);
    }

    if (gflagChk(0xB7) == 0) {
        stage_SetAnimation(0xE1, 0, 0);
        SetWayGroupActive(4, 0);
    } else {
        stage_SetAnimation(0xE1, 0, -1);
        SetWayGroupActive(4, 1);
    }

    if (gflagChk(0xD4) == 0) {
        stage_SetAnimation(0xEA, 0, 0);
    } else {
        stage_SetAnimation(0xEA, 0, -1);
    }

    if (gflagChk(0xD5) == 0) {
        stage_SetAnimation(0xEB, 0, 0);
    } else {
        stage_SetAnimation(0xEB, 0, -1);
    }

    if (gflagChk(0xD6) == 0) {
        stage_SetAnimation(0xEC, 0, 0);
    } else {
        stage_SetAnimation(0xEC, 0, -1);
    }

    if (gflagChk(0xD7) == 0) {
        stage_SetAnimation(0xED, 0, 0);
    } else {
        stage_SetAnimation(0xED, 0, -1);
    }

    if (gflagChk(0xD8) == 0) {
        stage_SetAnimation(0xEE, 0, 0);
    } else {
        stage_SetAnimation(0xEE, 0, -1);
    }

    if (gflagChk(0xD9) == 0) {
        stage_SetAnimation(0xEF, 0, 0);
    } else {
        stage_SetAnimation(0xEF, 0, -1);
    }

    if (gflagChk(0xDA) == 0) {
        stage_SetAnimation(0xF0, 0, 0);
    } else {
        stage_SetAnimation(0xF0, 0, -1);
    }

    if (gflagChk(0xA2) != 0 && gflagChk(0xAE) == 0) {
        stage_SetAnimation(0xFD, 0, -1);
    }

    if (gflagChk(0xA2) == 0 || gflagChk(0xAE) != 0) {
        stage_SetAnimation(0xFD, 0, 0);
    }

    if (gflagChk(0xBE) != 0) {
        stage_SetAnimation(0xE4, 0, 0xC8);
    } else {
        stage_SetAnimation(0xE4, 0, 0);
    }
}
void actSt04eInit(void)
{
    if (gflagChk(0xE6) == 0) {
        SetWayGroupActive(5, 0);
    } else {
        SetWayGroupActive(5, 1);
    }

    if (gflagChk(0xB6) == 0) {
        stage_SetAnimation(0xE0, 0, 0);
    } else {
        stage_SetAnimation(0xE0, 0, -1);
    }

    if (gflagChk(0xB7) == 0) {
        stage_SetAnimation(0xE1, 0, 0);
    } else {
        stage_SetAnimation(0xE1, 0, -1);
    }
}
void actSt04lBallTurnCommonSub(volatile int a0)
{
    _ACTWait(0x3C);

    scpAdpcmPlayRequestFunc(0x52, &ball1_4l, 1, 1, 1);

    while (ball1_4l == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(D_0063C520, 1, 0);

    while (stage_CheckAnimationFinish(D_0063C520) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    _ACTWait((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 6);

    D_0063C52C = 1;
    _ACTWait(0);
}
extern void actSt04lBallTurnCommonSub(volatile int a0);

void actSt04lBallTurnCommon(volatile int a0)
{
    int h;

    lt_switch_layout(0x37);
    gflagOn(D_0063C51C);
    scpSleepEnemyAll();

    h = actCreateSubThread(actSt04lBallTurnCommonSub, 0x15);

    D_0063C52C = 0;
    ball1_4l = 0xFFFFFFFF;

    while (D_0063C52C == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(h + 0x24, 0x22);

    if (D_0063C52C == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (ball1_4l == 0) {
            _ACTWait(1);
        }

        if (ball1_4l != 0xFFFFFFFF) {
            scpAdpcmFadeCloseFunc(&ball1_4l, 0x200);
        }

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(D_0063C520, 0, -1);
        scpFadeIn(5.0f);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    scpSearchGobj(D_0063C524)->f16C = 1;
    scpSearchGobj(D_0063C528)->f16C = 1;
    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}

extern ActMail D_004F8B20[];

void turnBall(int a0, int a1, int a2, int a3, int a4)
{
    /* the 0x164 chase is spelled int-typed: ROM re-chases it in the int
       alias set of the D_0063C51C.. stores, so it cannot be sunk below them */
    Act *sub = (Act *)*(int *)(a0 + 0x164);

    D_0063C51C = a1;
    D_0063C520 = a2;
    D_0063C524 = a3;
    D_0063C528 = a4;

    D_004F8B20[0].func = actSt04lBallTurnCommon;
    sub->mail = D_004F8B20;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern ActMail D_004F8C60[];
extern void actSt04lCrest2Main(volatile int a0);

void actSt04lCrest02(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xAF) == 0) {
        if (D_00639ED4 == 0x13) {
            stage_SetAnimation(0xC9, 0, 0);
        } else {
            stage_SetAnimation(0xCA, 0, 0);
        }

        D_004F8C60[0].func = actSt04lCrest2Main;
        self->mail = D_004F8C60;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        if (D_00639ED4 == 0x13) {
            stage_SetAnimation(0xC9, 0, -1);
        } else {
            stage_SetAnimation(0xCA, 0, -1);
        }
    }
}
void actSt04lCrestSub(volatile int a0)
{
    stage_SetAnimation(0xFC, 1, 0);
    stage_SetAnimation(0xC7, 1, 0);

    while (stage_CheckAnimationFrame(0xC7, 0x1E, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    oriup4c = iosPadActRequest(D_00639EAC, 0xA);
    oridown4c = 0x80;
    iosPadActVolumeSet(oriup4c, 0x80);

    while (stage_CheckAnimationFrame(0xC7, 0xBE, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(oriup4c);

    while (stage_CheckAnimationFinish(0xC7) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    D_0063C52C = 1;
    _ACTWait(0);
}
extern void actSt04lCrestSub(volatile int a0);

void actSt04lCrestMain(volatile int a0)
{
    int h;

    while (scpIsTorchLightOn(0x45A) == 0 || scpIsTorchLightOn(0x45B) == 0 || gflagChk(0xB1) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    fightSoundProcessRequestPause();

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(0x1B, &ball2_4l, 0, 1, 1);

    while (ball2_4l == 0) {
        _ACTWait(1);
    }

    preload(3);
    gflagOn(0xAE);
    gflagOn(0xE0);

    h = actCreateSubThread(actSt04lCrestSub, 0x15);

    D_0063C52C = 0;
    oriup4c = 0xFFFFFFFF;

    while (D_0063C52C == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(h + 0x24, 0x22);

    if (D_0063C52C == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&ball2_4l, 0x100);
        iosPadActStop(oriup4c);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(0xFC, 0, -1);
        stage_SetAnimation(0xC7, 0, -1);
        scpFadeIn(3.0f);
    }

    scpWakeupEnemyAll();
    RequestStageChange(3, D_00639EA4, 0, 2.0f, 8.0f);
}
void actSt04lCrest2Sub(volatile int a0)
{
    stage_SetAnimation(D_0063C530, 1, 0);

    while (stage_CheckAnimationFrame(D_0063C530, 0x1E, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    oriup4c = iosPadActRequest(D_00639EAC, 0xA);
    oridown4c = 0x80;
    iosPadActVolumeSet(oriup4c, 0x80);

    while (stage_CheckAnimationFrame(D_0063C530, 0xBE, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(oriup4c);
    oriup4c = 0xFFFFFFFF;

    while (stage_CheckAnimationFinish(D_0063C530) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    if (D_00639ED4 == 0x13) {
        scpSearchGobj(0x462)->f16C = 1;
    }

    D_0063C52C = 1;
    _ACTWait(0);
}
extern void actSt04lCrest2Sub(volatile int a0);

void actSt04lCrest2Main(volatile int a0)
{
    int h;

    if (D_00639ED4 == 0x13) {
        D_0063C530 = 0xC9;

        while (scpIsTorchLightOn(0x45E) == 0 || scpIsTorchLightOn(0x45F) == 0 ||
               gflagChk(0xB2) == 0) {
            _ACTWait(1);
        }
    }

    if (D_00639ED4 == 0x14) {
        D_0063C530 = 0xCA;

        while (scpIsTorchLightOn(0x4B2) == 0 || scpIsTorchLightOn(0x4B3) == 0 ||
               gflagChk(0xB2) == 0) {
            _ACTWait(1);
        }
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(0x1A, &ball3_4l, 1, 1, 1);

    while (ball3_4l == 0) {
        _ACTWait(1);
    }

    gflagOn(0xAF);

    h = actCreateSubThread(actSt04lCrest2Sub, 0x15);

    D_0063C52C = 0;
    oriup4c = 0xFFFFFFFF;

    while (D_0063C52C == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(h + 0x24, 0x22);

    if (D_0063C52C == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&ball3_4l, 0x100);
        iosPadActStop(oriup4c);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(D_0063C530, 0, -1);

        if (D_00639ED4 == 0x13) {
            scpSearchGobj(0x462)->f16C = 1;
        }

        SetCameraFlag_LwsCutBack();
        scpFadeIn(3.0f);
    }

    lt_switch_layout(0x36);
    D_0063AA08 = 0;
    scpWakeupEnemyAll();
}
void actSt04lCrest3Sub(volatile int a0)
{
    while (stage_CheckAnimationFrame(0xCB, 0x1E, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    oriup4c = iosPadActRequest(D_00639EAC, 0xA);
    oridown4c = 0x80;
    iosPadActVolumeSet(oriup4c, 0x80);

    while (stage_CheckAnimationFrame(0xCB, 0xBE, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(oriup4c);

    while (stage_CheckAnimationFinish(0xCB) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    D_0063C52C = 1;
    _ACTWait(0);
}
extern void actSt04lCrest3Sub(volatile int a0);

void actSt04lCrest3Main(volatile int a0)
{
    int h;

    while (scpIsTorchLightOn(0x4B4) == 0 || scpIsTorchLightOn(0x4B5) == 0 || gflagChk(0xB3) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(0x18, &crest1, 0, 1, 1);

    while (crest1 == 0) {
        _ACTWait(1);
    }

    gflagOn(0xB0);
    stage_SetAnimation(0xCB, 1, 0);

    h = actCreateSubThread(actSt04lCrest3Sub, 0x15);

    D_0063C52C = 0;
    oriup4c = 0xFFFFFFFF;

    while (D_0063C52C == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(h + 0x24, 0x22);

    if (D_0063C52C == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&crest1, 0x100);
        iosPadActStop(oriup4c);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(0xCB, 0, -1);
        scpFadeIn(3.0f);
    }

    lt_switch_layout(0x36);
    D_0063AA08 = 0;
    scpWakeupEnemyAll();
}
extern void actSt04eSolarBeamChkSub(volatile int a0);

void actSt04eSolarBeamChk(volatile int a0)
{
    int h;

    gflagOff(0xE0);
    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    scpAdpcmPlayRequestFunc(0x1C, &crest2, 0, 1, 1);

    while (crest2 == 0) {
        _ACTWait(1);
    }

    preload(7);
    scpFadeIn(16.0f);

    h = actCreateSubThread(actSt04eSolarBeamChkSub, 0x15);

    D_0063C52C = 0;

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    while (D_0063C52C == 0 && ((D_0028F8F0[0].trg & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(h + 0x24, 0x22);

    if (D_0063C52C == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&crest2, 0x100);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(0x124, 0, -1);
        scpFadeIn(3.0f);
    }

    RequestStageChange(7, D_00639EA4, 0, 2.0f, 8.0f);
}
void actSt04lStairSub(volatile int a0)
{
    long long ofs[2];
    float dir[4];

    _ACTWait(0x3C);

    while (crest3 == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(crest3->unk2C);

    stage_SetAnimation(0x102, 1, 0);

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);
    scpPlayMot(D_00639EA4, 0);
    scpPlayMot(D_00639EA8, 0x214);
    scpPlayPosSet(D_00639EA4, 55.0f, 28.0f, -3881.0f);
    scpPlayPosSet(D_00639EA8, -58.0f, 28.0f, -3891.0f);

    ofs[0] = D_00622AB0[0];
    ofs[1] = D_00622AB0[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    ofs[0] = D_00622AB0[0];
    ofs[1] = D_00622AB0[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, dir);

    D_0063C534 = 1;

    while (stage_CheckAnimationFinish(0x102) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x11);

    stage_SetAnimation(0xE3, 1, 0);

    while (stage_CheckAnimationFrame(0xE3, 0x8C, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    oriup4c = iosPadActRequest(D_00639EAC, 9);
    oridown4c = 0x80;
    iosPadActVolumeSet(oriup4c, 0x80);

    while (stage_CheckAnimationFinish(0xE3) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C52C = 1;
    _ACTWait(0);
}
extern void actSt04lStairSub(volatile int a0);

void actSt04lStairChk(volatile int a0)
{
    int h;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0xB000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0xB000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyOne(0xEAD);
    gflagOn(0xB4);
    FinishHint(0x11);

    scpSearchGobj(0x4DA)->f16C = 0;

    stage_SetAnimation(0x103, -1, -2);

    scpAdpcmPlayRequestFunc(0x3D, &crest3, 1, 1, 0);

    h = actCreateSubThread(actSt04lStairSub, 0x15);

    D_0063C52C = 0;
    D_0063C534 = 0;
    oriup4c = 0xFFFFFFFF;

    while (D_0063C52C == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    if (D_0063C52C == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (crest3 == 0) {
            _ACTWait(1);
        }

        scpAdpcmFadeCloseFunc(&crest3, 0x200);

        while (D_0063C534 == 0) {
            _ACTWait(1);
        }

        iosThreadSetPri(h + 0x24, 0x22);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(0x102, 0, -1);
        stage_SetAnimation(0xE3, 0, -1);

        _ACTWait(1);

        scpPlayMot(D_00639EA4, 0);
        scpPlayMot(D_00639EA8, 0x214);
        scpPlayPosSet(D_00639EA4, 55.0f, 234.0f, -3881.0f);
        scpPlayPosSet(D_00639EA8, -58.0f, 234.0f, -3891.0f);

        _ACTWait(1);
        iosOmSendMail(D_00639EA8, 0x3E, D_00639EA4);

        scpFadeIn(3.0f);
    } else {
        iosThreadSetPri(h + 0x24, 0x22);
    }

    iosPadActStop(oriup4c);

    scpPlayMot(D_00639EA4, 0);
    scpPlayMot(D_00639EA8, 0x214);
    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);

    D_0063AA08 = 0;
    lt_switch_layout(0x36);
    gflagOn(0xDC);
    scpWakeupEnemyOne(0xEAD);
}
void actSt04lRope1Chk(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(0xB8) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(0x49F))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(0xDC, 1, 0);

            while (stage_CheckAnimationFinish(0xDC) == 0) {
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(0x49F)->f16C = 0;
            gflagOn(0xB8);
            stage_SetAnimation(0xD8, 1, 0);

            while (stage_CheckAnimationFinish(0xD8) == 0) {
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        }
    }
}
void actSt04lRope2Chk(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(0xB9) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(0x4A0))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(0xDD, 1, 0);

            while (stage_CheckAnimationFinish(0xDD) == 0) {
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(0x4A0)->f16C = 0;
            gflagOn(0xB9);
            stage_SetAnimation(0xD9, 1, 0);

            while (stage_CheckAnimationFinish(0xD9) == 0) {
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        }
    }
}
void actSt04lRope3Chk(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(0xBA) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(0x4A1))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(0xDE, 1, 0);

            while (stage_CheckAnimationFinish(0xDE) == 0) {
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(0x4A1)->f16C = 0;
            gflagOn(0xBA);
            stage_SetAnimation(0xDA, 1, 0);

            while (stage_CheckAnimationFinish(0xDA) == 0) {
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        }
    }
}
void actSt04lRope4Chk(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(0xBB) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(0x4A2))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(0xDF, 1, 0);

            while (stage_CheckAnimationFinish(0xDF) == 0) {
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(0x4A2)->f16C = 0;
            gflagOn(0xBB);
            stage_SetAnimation(0xDB, 1, 0);

            while (stage_CheckAnimationFinish(0xDB) == 0) {
                _ACTWait(1);
            }

            _ACTWait(1);
            break;
        }
    }
}
void actSt04lSekizoChk(volatile int a0)
{
    float dir[4];

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0 ||
           scpTriggerBall(a0, D_00639EA8, 200.0f) == 0 ||
           scpTriggerFloorAttr(D_00639EA4, 0x8000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x8000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpKillEnemyAll();
    scpMaskGeneratorAll();

    scpAdpcmPlayRequestFunc(0x12, &stair4d, 1, 1, 1);

    while (stair4d == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(1, 1);

    stage_SetAnimation(0xE2, 1, 0);

    st04l_yure = iosPadActRequest(D_00639EAC, 9);
    st04l_yure_vol = 0x80;
    iosPadActVolumeSet(st04l_yure, 0x80);

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);
    scpPlayMot(D_00639EA4, 0);
    scpPlayMot(D_00639EA8, 0x214);
    scpPlayPosSet(D_00639EA8, 0.0f, -1300.0f, -1700.0f);
    scpPlayPosSet(D_00639EA4, 20.0f, -1300.0f, -1700.0f);

    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT((void *)a0), test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, dir);

    D_0063AA08 = 1;

    sceVu0SubVector(dir, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    scpSekizouCheckPoint();

    scpPlayMot(D_00639EA8, 0x285);
    scpPlayWaitMotEnd(D_00639EA8);

    gflagOn(0xBC);

    while (stage_CheckAnimationFrame(0xE2, 0x97, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(st04l_yure);

    while (stage_CheckAnimationFinish(0xE2) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(D_00639EA8, 0x214);
    scpPlayEnd(D_00639EA8);
    scpPlayMot(D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);

    _ACTWait(1);
    iosOmSendMail(D_00639EA8, 0x3F, D_00639EA4);

    lt_switch_layout(0x36);
    D_0063AA08 = 0;
}
extern ActMail D_004F8EA0[];
extern void actSt04lGondolaCharaChk(volatile int a0);

void actSt04lGondolaChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttr(D_00639EA4, 0xA000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();
    _ACTWait(0xF);

    if (gflagChk(0xBE) != 0) {
        stage_SetAnimation(0xE4, 1, 0xC8);

        while (stage_CheckAnimationFrame(0xE4, 0xDC, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        soundSeDefPlay(0x529, 0, 0, 1);

        while (stage_CheckAnimationFrame(0xE4, 0xF0, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        soundSeDefPlay(0x52A, 0, 0, 1);

        while (stage_CheckAnimationFrame(0xE4, 0xFA, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        soundSeDefPlay(0x527, 0, 0, 1);

        while (stage_CheckAnimationFrame(0xE4, 0x19F, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        soundSeDefPlay(0x528, 0, 0, 1);

        while (stage_CheckAnimationFinish(0xE4) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        gflagOff(0xBE);
    } else {
        stage_SetAnimation(0xE4, 1, 0);
        SetGirlDangerGObj(D_00639EA4);
        soundSeDefPlay(0x527, 0, 0, 1);

        while (stage_CheckAnimationFrame(0xE4, 0x91, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        soundSeDefPlay(0x528, 0, 0, 1);
        soundSeDefPlay(0x529, 0, 0, 1);

        while (stage_CheckAnimationFrame(0xE4, 0xAA, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        soundSeDefPlay(0x52A, 0, 0, 1);

        while (stage_CheckAnimationFrame(0xE4, 0xC8, 1) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        ClearGirlDangerGObj();
        gflagOn(0xBE);
    }

    if (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0xA000000) == 0) {
        gflagOn(0xC2);
    } else {
        gflagOff(0xC2);
    }

    D_0063AA08 = 0;
    lt_switch_layout(0x36);
    scpWakeupEnemyAll();

    D_004F8EA0[0].func = actSt04lGondolaCharaChk;
    sub->mail = D_004F8EA0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt04lMonyou01Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x1000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x1000000) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;
    gflagOn(0xD4);
    FinishHint(0x10);
    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(D_00639EA4);
        scpPlayStart(D_00639EA8);
        scpPlayMotReq(D_00639EA4, 1);
        scpPlayMotReq(D_00639EA8, 1);
        _ACTWait(1);
        ACTGame_ConnectHand();
    }

    stage_SetAnimation(0xEA, 1, 0);
    soundSeDefPlay(0x534, 0, 0, 1);

    while (stage_CheckAnimationFrame(0xEA, 0x1E, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(D_00639EA8, 0x3F, D_00639EA4);
    }

    D_0063AA08 = 0;
}
void actSt04lMonyou02Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x2000000) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;
    gflagOn(0xD5);
    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(D_00639EA4);
        scpPlayStart(D_00639EA8);
        scpPlayMotReq(D_00639EA4, 1);
        scpPlayMotReq(D_00639EA8, 1);
        _ACTWait(1);
        ACTGame_ConnectHand();
    }

    stage_SetAnimation(0xEB, 1, 0);
    soundSeDefPlay(0x534, 0, 0, 1);

    while (stage_CheckAnimationFrame(0xEB, 0x1E, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(D_00639EA8, 0x3F, D_00639EA4);
    }

    D_0063AA08 = 0;
}
void actSt04lMonyou03Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x3000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x3000000) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;
    gflagOn(0xD6);
    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(D_00639EA4);
        scpPlayStart(D_00639EA8);
        scpPlayMotReq(D_00639EA4, 1);
        scpPlayMotReq(D_00639EA8, 1);
        _ACTWait(1);
        ACTGame_ConnectHand();
    }

    stage_SetAnimation(0xEC, 1, 0);
    soundSeDefPlay(0x534, 0, 0, 1);

    while (stage_CheckAnimationFrame(0xEC, 0x1E, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(D_00639EA8, 0x3F, D_00639EA4);
    }

    D_0063AA08 = 0;
}
void actSt04lMonyou04Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x4000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x4000000) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;
    gflagOn(0xD7);
    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(D_00639EA4);
        scpPlayStart(D_00639EA8);
        scpPlayMotReq(D_00639EA4, 1);
        scpPlayMotReq(D_00639EA8, 1);
        _ACTWait(1);
        ACTGame_ConnectHand();
    }

    stage_SetAnimation(0xED, 1, 0);
    soundSeDefPlay(0x534, 0, 0, 1);

    while (stage_CheckAnimationFrame(0xED, 0x1E, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(D_00639EA8, 0x3F, D_00639EA4);
    }

    D_0063AA08 = 0;
}
void actSt04lMonyou05Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x5000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x5000000) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;
    gflagOn(0xD8);
    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(D_00639EA4);
        scpPlayStart(D_00639EA8);
        scpPlayMotReq(D_00639EA4, 1);
        scpPlayMotReq(D_00639EA8, 1);
        _ACTWait(1);
        ACTGame_ConnectHand();
    }

    stage_SetAnimation(0xEE, 1, 0);
    soundSeDefPlay(0x534, 0, 0, 1);

    while (stage_CheckAnimationFrame(0xEE, 0x1E, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(D_00639EA8, 0x3F, D_00639EA4);
    }

    D_0063AA08 = 0;
}
void actSt04lMonyou06Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x6000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x6000000) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;
    gflagOn(0xD9);
    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(D_00639EA4);
        scpPlayStart(D_00639EA8);
        scpPlayMotReq(D_00639EA4, 1);
        scpPlayMotReq(D_00639EA8, 1);
        _ACTWait(1);
        ACTGame_ConnectHand();
    }

    stage_SetAnimation(0xEF, 1, 0);
    soundSeDefPlay(0x534, 0, 0, 1);

    while (stage_CheckAnimationFrame(0xEF, 0x1E, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(D_00639EA8, 0x3F, D_00639EA4);
    }

    D_0063AA08 = 0;
}
void actSt04lMonyou07Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x7000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x7000000) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;
    gflagOn(0xDA);
    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        scpPlayStart(D_00639EA4);
        scpPlayStart(D_00639EA8);
        scpPlayMotReq(D_00639EA4, 1);
        scpPlayMotReq(D_00639EA8, 1);
        _ACTWait(1);
        ACTGame_ConnectHand();
    }

    stage_SetAnimation(0xF0, 1, 0);
    soundSeDefPlay(0x534, 0, 0, 1);

    while (stage_CheckAnimationFrame(0xF0, 0x1E, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpWakeupEnemyAll();
    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);
    _ACTWait(1);

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        iosOmSendMail(D_00639EA8, 0x3F, D_00639EA4);
    }

    D_0063AA08 = 0;
}
void actSt04lOriSub(volatile int a0)
{
    _ACTWait(0x3C);

    while (st04d_hasi == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(st04d_hasi->unk2C);

    stage_SetAnimation(0xF3, 1, 0);
    stage_SetAnimation(0xF5, 1, 0);
    stage_SetAnimation(0xF4, 1, 0);

    while (stage_CheckAnimationFrame(0xF3, 0x5A, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0xF);

    if (D_00639EA8 != 0) {
        scpPlayMotReq(D_00639EA8, 0xD8);
    }

    while (stage_CheckAnimationFinish(0xF3) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    D_0063C52C = 1;
    _ACTWait(0);
}
extern void actSt04lOriSub(volatile int a0);

void actSt04lOriChk(volatile int a0)
{
    int h;

    while (gflagChk(0xAF) == 0 || scpGameStat_BoyWeaponkind() != 4 ||
           scpTriggerBall(a0, D_00639EA4, 1000.0f) == 0) {
        _ACTWait(1);
    }

    scpSleepEnemyAll();
    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    scpPlayMot(D_00639EA4, 0);

    if (D_00639EA8 != 0) {
        iosOmSendMail(D_00639EA8, 0x3E, D_00639EA4);
    }

    gflagOn(0xC8);
    SetWayGroupActive(0xE, 0);
    SetWayGroupActive(0xF, 0);

    scpAdpcmPlayRequestFunc(0x3E, &st04d_hasi, 1, 1, 0);

    h = actCreateSubThread(actSt04lOriSub, 0x15);

    D_0063C52C = 0;

    while (D_0063C52C == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(h + 0x24, 0x22);

    if (D_0063C52C == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (st04d_hasi == 0) {
            _ACTWait(1);
        }

        scpAdpcmFadeCloseFunc(&st04d_hasi, 0x200);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(0xF3, 0, -1);
        stage_SetAnimation(0xF5, 0, -1);
        stage_SetAnimation(0xF4, 0, -1);
        scpFadeIn(3.0f);
    }

    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}
void actSt04lOriRopeCutRChk(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    while (1) {
        if (scpGameStat_BoyWeaponkind() == 4 && scpTriggerBall(a0, D_00639EA4, 100.0f) != 0 &&
            (ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0x26 ||
             ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0x2B ||
             ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0x2D ||
             ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0x27 ||
             ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0x28 ||
             ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0x3C))
            break;
        _ACTWait(1);
    }

    _ACTWait(0xF);
    gflagOn(0xC9);

    stage_SetAnimation(0xF6, 1, 0);
    soundSeDefPlay(0x52B, 0, 0, 1);

    while (stage_CheckAnimationFrame(0xF6, 0x20, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    soundSeDefPlay(0x52C, 0, 0, 1);

    while (stage_CheckAnimationFinish(0xF6) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
}
void actSt04lOriRopeCutLChk(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    while (1) {
        if (scpGameStat_BoyWeaponkind() == 4 && scpTriggerBall(a0, D_00639EA4, 100.0f) != 0 &&
            (ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0x26 ||
             ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0x2B ||
             ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0x2D ||
             ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0x27 ||
             ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0x28 ||
             ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0x3C))
            break;
        _ACTWait(1);
    }

    _ACTWait(0xF);
    gflagOn(0xCA);

    stage_SetAnimation(0xF7, 1, 0);
    soundSeDefPlay(0x52B, 0, 0, 1);

    while (stage_CheckAnimationFrame(0xF7, 0x20, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    soundSeDefPlay(0x52C, 0, 0, 1);

    while (stage_CheckAnimationFinish(0xF7) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
}
extern ActMail D_004F9020[];
extern void actSt04lOri2Chk(volatile int a0);

void actSt04lOri2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xCB) == 0) {
        SleepHint(0xF);

        D_004F9020[0].func = actSt04lOri2Chk;
        self->mail = D_004F9020;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xF3, -1, -2);
        stage_SetAnimation(0xF5, -1, -2);
        stage_SetAnimation(0xF4, -1, -2);
        stage_SetAnimation(0xF8, 0, -1);
        stage_SetAnimation(0xF7, 0, -1);
        stage_SetAnimation(0xF6, 0, -1);
    }
}
void actSt04lOri2Sub(volatile int a0)
{
    iosPadActRequest(D_00639EAC, 0x11);
    _ACTWait(0x1E);

    while (sekizo4c == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(sekizo4c->unk2C);

    stage_SetAnimation(0xF8, 1, 0);

    while (stage_CheckAnimationFrame(0xF8, 0x1E, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0xF);

    if (D_00639EA8 != 0) {
        scpPlayMotReq(D_00639EA8, 0xD8);
    }

    while (stage_CheckAnimationFinish(0xF8) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    D_0063C52C = 1;
    _ACTWait(0);
}
extern void actSt04lOri2Sub(volatile int a0);

void actSt04lOri2Chk(volatile int a0)
{
    int h;

    while (gflagChk(0xC9) == 0 || gflagChk(0xCA) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    gflagOn(0xCB);
    WakeupHint(0xF);
    SetWayGroupActive(0xE, 1);
    SetWayGroupActive(0xF, 1);
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(0x3F, &sekizo4c, 1, 1, 0);

    h = actCreateSubThread(actSt04lOri2Sub, 0x15);

    D_0063C52C = 0;

    while (D_0063C52C == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(h + 0x24, 0x22);

    if (D_0063C52C == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (sekizo4c == 0) {
            _ACTWait(1);
        }

        scpAdpcmFadeCloseFunc(&sekizo4c, 0x200);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(0xF8, 0, -1);
        scpFadeIn(3.0f);
    }

    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}
extern ActMail D_004F8C40[];
extern void actSt04lCrestMain(volatile int a0);

void actSt04lCrest01(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xAE) == 0) {
        stage_SetAnimation(0xC7, 0, 0);

        D_004F8C40[0].func = actSt04lCrestMain;
        self->mail = D_004F8C40;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xC7, 0, -1);

        D_0063AA08 = 0;
    }
}
extern ActMail D_004F8C80[];
extern void actSt04lCrest3Main(volatile int a0);

void actSt04lCrest03(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xB0) == 0) {
        stage_SetAnimation(0xCB, 0, 0);

        D_004F8C80[0].func = actSt04lCrest3Main;
        self->mail = D_004F8C80;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xCB, 0, -1);
    }
}
extern ActMail D_004F8AC0[];
extern void actSt04lC1BallMain(volatile int a0);

void actSt04lC1Ball(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xB1) == 0) {
        scpSearchGobj(0x45A)->f16C = 0;
        scpSearchGobj(0x45B)->f16C = 0;

        stage_SetAnimation(0xCF, 0, 0);

        D_004F8AC0[0].func = actSt04lC1BallMain;
        self->mail = D_004F8AC0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xCF, 0, -1);
    }
}
extern ActMail D_004F8B60[];
extern void actSt04lC2BallMain(volatile int a0);

void actSt04lC2Ball(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xB2) == 0) {
        scpSearchGobj(0x4B2)->f16C = 0;
        scpSearchGobj(0x4B3)->f16C = 0;

        stage_SetAnimation(0xD0, 0, 0);

        D_004F8B60[0].func = actSt04lC2BallMain;
        self->mail = D_004F8B60;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xD0, 0, -1);
    }
}
extern ActMail D_004F8BE0[];
extern void actSt04lC3BallMain(volatile int a0);

void actSt04lC3Ball(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xB3) == 0) {
        scpSearchGobj(0x4B4)->f16C = 0;
        scpSearchGobj(0x4B5)->f16C = 0;

        stage_SetAnimation(0xD1, 0, 0);

        D_004F8BE0[0].func = actSt04lC3BallMain;
        self->mail = D_004F8BE0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xD1, 0, -1);
    }
}
extern ActMail D_004F8CC0[];
extern void actSt04lStairChk(volatile int a0);

void actSt04lStair(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xB4) == 0) {
        if (D_00639EA8 != 0) {
            D_004F8CC0[0].func = actSt04lStairChk;
            self->mail = D_004F8CC0;
            ACTSendMailCorrect(a0, 0x1AE);
            _ACTWait(0);
        }
    } else {
        scpSearchGobj(0x4DA)->f16C = 0;

        stage_SetAnimation(0x103, -1, -2);
    }
}
extern ActMail D_004F8D20[];
extern void actSt04lBrg1Chk(volatile int a0);

void actSt04lBrg1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xB6) == 0) {
        D_004F8D20[0].func = actSt04lBrg1Chk;
        self->mail = D_004F8D20;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004F8DA0[];
extern void actSt04lBrg2Chk(volatile int a0);

void actSt04lBrg2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xB7) == 0) {
        SleepHint(0x10);

        D_004F8DA0[0].func = actSt04lBrg2Chk;
        self->mail = D_004F8DA0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004F8DE0[];
extern void actSt04lBrg1WayChk(volatile int a0);

void actSt04lBrg1Way(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xB6) == 0) {
        D_004F8DE0[0].func = actSt04lBrg1WayChk;
        self->mail = D_004F8DE0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004F8E00[];
extern void actSt04lBrg2WayChk(volatile int a0);

void actSt04lBrg2Way(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xB7) == 0) {
        D_004F8E00[0].func = actSt04lBrg2WayChk;
        self->mail = D_004F8E00;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004F8CE0[];
extern void actSt04lRope1Chk(volatile int a0);

void actSt04lRope1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xB8) == 0) {
        stage_SetAnimation(0xD8, 0, 0);

        D_004F8CE0[0].func = actSt04lRope1Chk;
        self->mail = D_004F8CE0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xD8, 0, -1);

        scpSearchGobj(0x49F)->f16C = 0;
    }
}
extern ActMail D_004F8D00[];
extern void actSt04lRope2Chk(volatile int a0);

void actSt04lRope2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xB9) == 0) {
        stage_SetAnimation(0xD9, 0, 0);

        D_004F8D00[0].func = actSt04lRope2Chk;
        self->mail = D_004F8D00;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xD9, 0, -1);

        scpSearchGobj(0x4A0)->f16C = 0;
    }
}
extern ActMail D_004F8D60[];
extern void actSt04lRope3Chk(volatile int a0);

void actSt04lRope3(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xBA) == 0) {
        stage_SetAnimation(0xDA, 0, 0);

        D_004F8D60[0].func = actSt04lRope3Chk;
        self->mail = D_004F8D60;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xDA, 0, -1);

        scpSearchGobj(0x4A1)->f16C = 0;
    }
}
extern ActMail D_004F8D80[];
extern void actSt04lRope4Chk(volatile int a0);

void actSt04lRope4(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xBB) == 0) {
        stage_SetAnimation(0xDB, 0, 0);

        D_004F8D80[0].func = actSt04lRope4Chk;
        self->mail = D_004F8D80;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xDB, 0, -1);

        scpSearchGobj(0x4A2)->f16C = 0;
    }
}
extern ActMail D_004F8E20[];
extern void actSt04lSekizoChk(volatile int a0);

void actSt04lSekizo(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xBC) == 0) {
        stage_SetAnimation(0xE2, 0, 0);

        D_004F8E20[0].func = actSt04lSekizoChk;
        self->mail = D_004F8E20;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xE2, 0, -1);
    }
}
extern ActMail D_004F8E40[];
extern void actSt04lTuriChk(volatile int a0);

void actSt04lTuri(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xBD) == 0) {
        stage_SetAnimation(0xE6, 0, 0);

        if (D_00639EA8 != 0) {
            D_004F8E40[0].func = actSt04lTuriChk;
            self->mail = D_004F8E40;
            ACTSendMailCorrect(a0, 0x1AE);
            _ACTWait(0);
        }
    } else {
        stage_SetAnimation(0xE6, 0, -1);
    }
}
extern ActMail D_004F8FC0[];
extern void actSt04lOriChk(volatile int a0);

void actSt04lOri(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xC8) == 0) {
        stage_SetAnimation(0xF3, 0, 0);
        stage_SetAnimation(0xF5, 0, 0);
        stage_SetAnimation(0xF4, 0, 0);

        D_004F8FC0[0].func = actSt04lOriChk;
        self->mail = D_004F8FC0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004F8FE0[];
extern void actSt04lOriRopeCutRChk(volatile int a0);

void actSt04lOriRopeCutR(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xC9) == 0) {
        D_004F8FE0[0].func = actSt04lOriRopeCutRChk;
        self->mail = D_004F8FE0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004F9000[];
extern void actSt04lOriRopeCutLChk(volatile int a0);

void actSt04lOriRopeCutL(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xCA) == 0) {
        D_004F9000[0].func = actSt04lOriRopeCutLChk;
        self->mail = D_004F9000;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004F9040[];
extern void actSt04lSwordChk(volatile int a0);

void actSt04lSword(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xAF) == 0) {
        D_004F9040[0].func = actSt04lSwordChk;
        self->mail = D_004F9040;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004F8E60[];
extern ActMail D_004F8E80[];
extern void actSt04lGondolaChk(volatile int a0);

void actSt04lGondola(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xBE) != 0) {
        stage_SetAnimation(0xE4, 0, 0xC8);

        D_004F8E60[0].func = actSt04lGondolaChk;
        self->mail = D_004F8E60;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xE4, 0, 0);

        D_004F8E80[0].func = actSt04lGondolaChk;
        self->mail = D_004F8E80;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004F8EE0[];
extern void actSt04lMonyou01Chk(volatile int a0);

void actSt04lMonyou01(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xD4) == 0) {
        stage_SetAnimation(0xEA, 0, 0);

        D_004F8EE0[0].func = actSt04lMonyou01Chk;
        self->mail = D_004F8EE0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xEA, 0, -1);
        FinishHint(0x10);
    }
}
extern ActMail D_004F8F00[];
extern void actSt04lMonyou02Chk(volatile int a0);

void actSt04lMonyou02(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xD5) == 0) {
        stage_SetAnimation(0xEB, 0, 0);

        D_004F8F00[0].func = actSt04lMonyou02Chk;
        self->mail = D_004F8F00;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xEB, 0, -1);
    }
}
extern ActMail D_004F8F20[];
extern void actSt04lMonyou03Chk(volatile int a0);

void actSt04lMonyou03(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xD6) == 0) {
        stage_SetAnimation(0xEC, 0, 0);

        D_004F8F20[0].func = actSt04lMonyou03Chk;
        self->mail = D_004F8F20;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xEC, 0, -1);
    }
}
extern ActMail D_004F8F40[];
extern void actSt04lMonyou04Chk(volatile int a0);

void actSt04lMonyou04(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xD7) == 0) {
        stage_SetAnimation(0xED, 0, 0);

        D_004F8F40[0].func = actSt04lMonyou04Chk;
        self->mail = D_004F8F40;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xED, 0, -1);
    }
}
extern ActMail D_004F8F60[];
extern void actSt04lMonyou05Chk(volatile int a0);

void actSt04lMonyou05(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xD8) == 0) {
        stage_SetAnimation(0xEE, 0, 0);

        D_004F8F60[0].func = actSt04lMonyou05Chk;
        self->mail = D_004F8F60;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xEE, 0, -1);
    }
}
extern ActMail D_004F8F80[];
extern void actSt04lMonyou06Chk(volatile int a0);

void actSt04lMonyou06(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xD9) == 0) {
        stage_SetAnimation(0xEF, 0, 0);

        D_004F8F80[0].func = actSt04lMonyou06Chk;
        self->mail = D_004F8F80;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xEF, 0, -1);
    }
}
extern ActMail D_004F8FA0[];
extern void actSt04lMonyou07Chk(volatile int a0);

void actSt04lMonyou07(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xDA) == 0) {
        stage_SetAnimation(0xF0, 0, 0);

        D_004F8FA0[0].func = actSt04lMonyou07Chk;
        self->mail = D_004F8FA0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xF0, 0, -1);
    }
}
void actSt04lCrest01XL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xAE) == 0) {
        stage_SetAnimation(0xCC, 0, 0);
    } else {
        stage_SetAnimation(0xCC, 0, -1);
    }
}
void actSt04lCrest02XL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xAF) == 0) {
        stage_SetAnimation(0xCD, 0, 0);
    } else {
        stage_SetAnimation(0xCD, 0, -1);
    }
}
void actSt04lCrest03XL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xB0) == 0) {
        stage_SetAnimation(0xCE, 0, 0);
    } else {
        stage_SetAnimation(0xCE, 0, -1);
    }
}
void actSt04lC2BallXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xB2) == 0) {
        scpSearchGobj(0x45E)->f16C = 0;
        scpSearchGobj(0x45F)->f16C = 0;

        stage_SetAnimation(0xD0, 0, 0);
    } else {
        stage_SetAnimation(0xD0, 0, -1);
    }
}
void actSt04lC3BallXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xB3) == 0) {
        stage_SetAnimation(0xD1, 0, 0);

        scpSearchGobj(0x503)->f16C = 0;
        scpSearchGobj(0x504)->f16C = 0;
    } else {
        stage_SetAnimation(0xD1, 0, -1);
    }
}
extern ActMail D_004F9060[];
extern void actSt04lTorch1_1Chk(volatile int a0);

void actSt04lTorch1_1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xCC) == 0) {
        D_004F9060[0].func = actSt04lTorch1_1Chk;
        self->mail = D_004F9060;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        scpTorchLightOn(0x45A);
        stage_SetAnimation(0xD2, 0, -1);
    }
}
extern ActMail D_004F9080[];
extern void actSt04lTorch1_2Chk(volatile int a0);

void actSt04lTorch1_2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xCD) == 0) {
        D_004F9080[0].func = actSt04lTorch1_2Chk;
        self->mail = D_004F9080;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        scpTorchLightOn(0x45B);
        stage_SetAnimation(0xD3, 0, -1);
    }
}
extern ActMail D_004F90A0[];
extern void actSt04lTorch2_1Chk(volatile int a0);

void actSt04lTorch2_1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xCE) != 0 || gflagChk(0xD0) != 0) {
        scpTorchLightOn(0x4B2);
        stage_SetAnimation(0xD4, 0, -1);
    } else {
        D_004F90A0[0].func = actSt04lTorch2_1Chk;
        self->mail = D_004F90A0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004F90C0[];
extern void actSt04lTorch2_2Chk(volatile int a0);

void actSt04lTorch2_2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xCF) != 0 || gflagChk(0xD1) != 0) {
        scpTorchLightOn(0x4B3);
        stage_SetAnimation(0xD5, 0, -1);
    } else {
        D_004F90C0[0].func = actSt04lTorch2_2Chk;
        self->mail = D_004F90C0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004F90E0[];
extern void actSt04lTorch3_1Chk(volatile int a0);

void actSt04lTorch3_1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xD2) == 0) {
        D_004F90E0[0].func = actSt04lTorch3_1Chk;
        self->mail = D_004F90E0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        scpTorchLightOn(0x4B4);
        stage_SetAnimation(0xD6, 0, -1);
    }
}
extern ActMail D_004F9100[];
extern void actSt04lTorch3_2Chk(volatile int a0);

void actSt04lTorch3_2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xD3) == 0) {
        D_004F9100[0].func = actSt04lTorch3_2Chk;
        self->mail = D_004F9100;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        scpTorchLightOn(0x4B5);
        stage_SetAnimation(0xD7, 0, -1);
    }
}
extern ActMail D_004F9120[];
extern void actSt04lTorch2_1XLChk(volatile int a0);

void actSt04lTorch2_1XL(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xCE) != 0 || gflagChk(0xD0) != 0) {
        scpTorchLightOn(0x45E);
        stage_SetAnimation(0xD4, 0, -1);
    } else {
        D_004F9120[0].func = actSt04lTorch2_1XLChk;
        self->mail = D_004F9120;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004F9140[];
extern void actSt04lTorch2_2XLChk(volatile int a0);

void actSt04lTorch2_2XL(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xCF) != 0 || gflagChk(0xD1) != 0) {
        scpTorchLightOn(0x45F);
        stage_SetAnimation(0xD5, 0, -1);
    } else {
        D_004F9140[0].func = actSt04lTorch2_2XLChk;
        self->mail = D_004F9140;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt04lTorch3_1XL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xD2) != 0) {
        scpTorchLightOn(0x503);
    }
}
void actSt04lTorch3_2XL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xD3) != 0) {
        scpTorchLightOn(0x504);
    }
}
void actSt04cDoorInit(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xA2) != 0 && gflagChk(0xAE) == 0) {
        stage_SetAnimation(0xFD, 0, -1);
    }

    if (gflagChk(0xA2) == 0 || gflagChk(0xAE) != 0) {
        stage_SetAnimation(0xFD, 0, 0);
    }
}
void actSt04dEnemy1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);

    while (gflagChk(0xDC) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}
void actSt04dEnemy2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);

    while (gflagChk(0xDC) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}
void actSt04dEnemy3(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);

    while (gflagChk(0xDC) == 0) {
        _ACTWait(1);
    }

    Generator_Call(a0);
}
extern ActMail D_004F8CA0[];
extern void actSt04eSolarBeamChk(volatile int a0);

void actSt04eSolarBeam(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xE0) != 0) {
        if (D_00639EA4 != 0) {
            scpPlayMot(D_00639EA4, 0);

            if (ACTGame_NoWeapon(D_00639EA4) == 0) {
                LightTorchOffOfWeapon(GetBoyWeaponGObj());
            }
        }

        gflagOn(0x185);

        D_0063AA0C = 0.0f;
        scpFadeOut(255.0f, 0, 0, 0);

        D_004F8CA0[0].func = actSt04eSolarBeamChk;
        self->mail = D_004F8CA0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
extern ActMail D_004F8AA0[];

void actSt04lC1BallMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = D_004F8AA0;
    while (1) {
        _ACTWait(1);
    }
}
extern ActMail D_004F8AE0[];
extern void actSt04lC1BallTurn(volatile int a0);

void actSt04lC1BallSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    D_004F8AE0[0].func = actSt04lC1BallTurn;
    sub->mail = D_004F8AE0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern ActMail D_004F8B00[];

void actSt04lC1BallTurn(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    D_0063C51C = 0xB1;
    D_0063C520 = 0xCF;
    D_0063C524 = 0x45A;
    D_0063C528 = 0x45B;

    D_004F8B00[0].func = actSt04lBallTurnCommon;
    self->mail = D_004F8B00;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern ActMail D_004F8B40[];

void actSt04lC2BallMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = D_004F8B40;
    while (1) {
        _ACTWait(1);
    }
}
extern ActMail D_004F8B80[];
extern void actSt04lC2BallTurn(volatile int a0);

void actSt04lC2BallSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    D_004F8B80[0].func = actSt04lC2BallTurn;
    sub->mail = D_004F8B80;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern ActMail D_004F8BA0[];

void actSt04lC2BallTurn(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    D_0063C51C = 0xB2;
    D_0063C520 = 0xD0;
    D_0063C524 = 0x4B2;
    D_0063C528 = 0x4B3;

    D_004F8BA0[0].func = actSt04lBallTurnCommon;
    self->mail = D_004F8BA0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern ActMail D_004F8BC0[];

void actSt04lC3BallMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = D_004F8BC0;
    while (1) {
        _ACTWait(1);
    }
}
extern ActMail D_004F8C00[];
extern void actSt04lC3BallTurn(volatile int a0);

void actSt04lC3BallSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    D_004F8C00[0].func = actSt04lC3BallTurn;
    sub->mail = D_004F8C00;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
extern ActMail D_004F8C20[];

void actSt04lC3BallTurn(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    D_0063C51C = 0xB3;
    D_0063C520 = 0xD1;
    D_0063C524 = 0x4B4;
    D_0063C528 = 0x4B5;

    D_004F8C20[0].func = actSt04lBallTurnCommon;
    self->mail = D_004F8C20;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt04eSolarBeamChkSub(volatile int a0)
{
    stage_SetAnimation(0x124, 1, 0);

    while (stage_CheckAnimationFinish(0x124) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    D_0063C52C = 1;
    _ACTWait(0);
}
void actSt04lRope1Event(int x)
{
    volatile int local = x;
}
void actSt04lRope2Event(int x)
{
    volatile int local = x;
}
void actSt04lBrg1Event(int x)
{
    volatile int local = x;
}
extern ActMail D_004F8D40[];

void actSt04lBrg1Chk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (gflagChk(0xB8) == 0 || gflagChk(0xB9) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();
    gflagOn(0xB6);

    sekizo_4r = 0xE0;

    D_004F8D40[0].func = actSt04rBrgCommon;
    sub->mail = D_004F8D40;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt04lRope3Event(int x)
{
    volatile int local = x;
}
void actSt04lRope4Event(int x)
{
    volatile int local = x;
}
void actSt04lBrg2Event(int x)
{
    volatile int local = x;
}
extern ActMail D_004F8DC0[];

void actSt04lBrg2Chk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (gflagChk(0xBA) == 0 || gflagChk(0xBB) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();
    gflagOn(0xB7);
    WakeupHint(0x10);

    sekizo_4r = 0xE1;

    D_004F8DC0[0].func = actSt04rBrgCommon;
    sub->mail = D_004F8DC0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt04lBrg1WayChk(volatile int a0)
{
    while (gflagChk(0xB6) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(3, 1);
}
void actSt04lBrg2WayChk(volatile int a0)
{
    while (gflagChk(0xB6) == 0 || gflagChk(0xB7) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(4, 1);
}
void actSt04lTuriEvent(int x)
{
    volatile int local = x;
}
void actSt04lTuriChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(a0, D_00639EA8, 200.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    gflagOn(0xBD);
    _ACTWait(0xA);

    stage_SetAnimation(0xE6, 1, 0);

    while (stage_CheckAnimationFinish(0xE6) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    lt_switch_layout(0x36);
}
extern void actSt04lGondolaChk(volatile int a0);

INCLUDE_ASM("asm/nonmatchings/src/st04l", actSt04lGondolaCharaChk);
void actSt04lMonyou01Event(int x)
{
    volatile int local = x;
}
void actSt04lMonyou02Event(int x)
{
    volatile int local = x;
}
void actSt04lMonyou03Event(int x)
{
    volatile int local = x;
}
void actSt04lMonyou04Event(int x)
{
    volatile int local = x;
}
void actSt04lMonyou05Event(int x)
{
    volatile int local = x;
}
void actSt04lMonyou06Event(int x)
{
    volatile int local = x;
}
void actSt04lMonyou07Event(int x)
{
    volatile int local = x;
}
void actSt04lOriEvent(int x)
{
    volatile int local = x;
}
void actSt04lOri2Event(int x)
{
    volatile int local = x;
}
void actSt04lSwordChk(volatile int a0)
{
    scpSearchGobj(0x462)->f16C = 0;
}
void actSt04lTorch1_1Chk(volatile int a0)
{
    while (scpIsTorchLightOn(0x45A) == 0) {
        _ACTWait(1);
    }

    gflagOn(0xCC);
    stage_SetAnimation(0xD2, 1, 0);
}
void actSt04lTorch1_2Chk(volatile int a0)
{
    while (scpIsTorchLightOn(0x45B) == 0) {
        _ACTWait(1);
    }

    gflagOn(0xCD);
    stage_SetAnimation(0xD3, 1, 0);
}
void actSt04lTorch2_1Chk(volatile int a0)
{
    while (scpIsTorchLightOn(0x4B2) == 0) {
        _ACTWait(1);
    }

    gflagOn(0xCE);
    stage_SetAnimation(0xD4, 1, 0);
}
void actSt04lTorch2_2Chk(volatile int a0)
{
    while (scpIsTorchLightOn(0x4B3) == 0) {
        _ACTWait(1);
    }

    gflagOn(0xCF);
    stage_SetAnimation(0xD5, 1, 0);
}
void actSt04lTorch3_1Chk(volatile int a0)
{
    while (scpIsTorchLightOn(0x4B4) == 0) {
        _ACTWait(1);
    }

    gflagOn(0xD2);
    stage_SetAnimation(0xD6, 1, 0);
}
void actSt04lTorch3_2Chk(volatile int a0)
{
    while (scpIsTorchLightOn(0x4B5) == 0) {
        _ACTWait(1);
    }

    gflagOn(0xD3);
    stage_SetAnimation(0xD7, 1, 0);
}
void actSt04lTorch2_1XLChk(volatile int a0)
{
    while (scpIsTorchLightOn(0x45E) == 0) {
        _ACTWait(1);
    }

    gflagOn(0xD0);
    stage_SetAnimation(0xD4, 1, 0);
}
void actSt04lTorch2_2XLChk(volatile int a0)
{
    while (scpIsTorchLightOn(0x45F) == 0) {
        _ACTWait(1);
    }

    gflagOn(0xD1);
    stage_SetAnimation(0xD5, 1, 0);
}
