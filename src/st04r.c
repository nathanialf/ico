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
extern int gflagChk(int a0);
extern void gflagOn(int a0);
extern void SetWayGroupActive(int a0, int a1);
extern int scpIsTorchLightOn(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern Act *actInitialize(int a0);
extern void scpTorchLightOn(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int D_0063AA08;
extern PObjGObj *scpSearchGobj(int a0);
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern int D_00639EA4;
extern int D_00639EA8;
extern int scpTriggerFloorAttr(int a0, int a1);
extern int sekizo_4r;
extern void gflagOff(int a0);
extern int D_0063C540;
extern int D_0063C544;
extern void openGate(int a0);
extern int stage_CheckAnimationFinish(int a0);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern int D_00639EAC;
extern int D_00639ED4;
extern int D_0063C53C;
extern char *sekizo5c;
extern void AdpcmPlay(int a0);
extern int iosPadActRequest(int a0, int a1);
extern void iosPadActVolumeSet(int a0, int a1);
extern void iosPadActStop(int a0);
extern unsigned char st05d_hasi;
extern int D_0063C538;
extern int crest1_4r;
extern int D_0028F8F4[];
extern void lt_switch_layout(int a0);
extern void scpSleepEnemyAll(void);
extern void scpWakeupEnemyAll(void);
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
extern int scpAdpcmFadeCloseFunc(int *a0, int a1);
extern int scpAdpcmPlayRequestNum(void);
extern int actCreateSubThread(void *entry, int prio);
extern void iosThreadSetPri(int *a0, int a1);
extern void scpFadeOut(float t, int a1, int a2, int a3);
extern void scpFadeIn(float f);
extern int scpFadeChk(void);
extern int lt_fade_status(void);
extern int GetAttackCheckBoundaryManagerStatus(PObjGObj *a0);
extern int ACTGame_FLAG_TETSUNAGI(void);
extern void ACTGame_ConnectHand(void);
extern int GetCharHeldItem(int a0);
extern void scpPlayStart(int a0);
extern void scpPlayEnd(int a0);
extern void scpPlayMotReq(int a0, int mot);
extern int soundSeDefPlay(int se, int a1, int a2, int a3);
extern void iosOmSendMail(int a0, int a1, int a2);
extern int scpIsBombExplode(int a0);
extern int scpTriggerBall(int a0, int gobj, float r);
extern void SetCameraFlag_LwsCutBack(void);
extern void scpPlayMot(int a0, int mot);
extern int D_0028F4C0[];
extern void preload(int a0);
extern void FinishHint(int a0);
extern void *test_CURRENTROOT(int a0);
extern void sceVu0SubVector(void *out, void *a, void *b);
extern void scpPlayMotDir(int a0, void *dir);
extern void scpPlayPosSet(int a0, float x, float y, float z);
extern void scpPlayWaitMotEnd(int a0);
extern int crest3_4r;
extern int D_0063C548;
extern const long long D_00622AC0[];
extern void scpWakeupItemWithBoundary(float a0, float a1, float a2, float a3);
extern void SetGirlDangerGObj(int a0);
extern void ClearGirlDangerGObj(void);
extern void scpKillEnemyAll(void);
extern void scpMaskGeneratorAll(void);
extern void scpSekizouCheckPoint(void);
extern int stair5d;
extern int st04r_yure;
extern unsigned char st04r_yure_vol;

/* the shared pad-state array (op.c's PadState, GsBase.c's GsbPad): 0x58 per
   pad, trg at 0x4. */
typedef struct Pad {
    int unk00;        /* 0x00 */
    int trg;          /* 0x04 */
    char unk08[0x50]; /* 0x08 */
} Pad;

extern Pad D_0028F8F0[];
extern void scpSleepEnemyOne(int a0);
extern void scpWakeupEnemyOne(int a0);
extern void fightSoundProcessRequestPause(void);
extern void fightSoundProcessRequestStart(void);
extern int fightSoundPlayChk(void);
extern int solar4r;

void actSt05eEnd(void)
{
    if (solar4r != 0) {
        if (gflagChk(0xEA) == 0) {
            scpAdpcmCloseFunc(&solar4r);
        }
    }
}

void actSt05cInit(void)
{
    if (gflagChk(0x112) == 0) {
        stage_SetAnimation(0x151, 0, 0);
    } else {
        stage_SetAnimation(0x151, 0, -1);
    }

    if (gflagChk(0x113) == 0) {
        stage_SetAnimation(0x152, 0, 0);
    } else {
        stage_SetAnimation(0x152, 0, -1);
    }

    if (gflagChk(0x114) == 0) {
        stage_SetAnimation(0x153, 0, 0);
    } else {
        stage_SetAnimation(0x153, 0, -1);
    }

    if (gflagChk(0x115) == 0) {
        stage_SetAnimation(0x154, 0, 0);
    } else {
        stage_SetAnimation(0x154, 0, -1);
    }

    if (gflagChk(0x116) == 0) {
        stage_SetAnimation(0x155, 0, 0);
    } else {
        stage_SetAnimation(0x155, 0, -1);
    }

    if (gflagChk(0x117) == 0) {
        stage_SetAnimation(0x156, 0, 0);
    } else {
        stage_SetAnimation(0x156, 0, -1);
    }

    if (gflagChk(0x118) == 0) {
        stage_SetAnimation(0x157, 0, 0);
    } else {
        stage_SetAnimation(0x157, 0, -1);
    }

    if (gflagChk(0xFE) == 0) {
        SetWayGroupActive(1, 0);
    } else {
        SetWayGroupActive(1, 1);
    }

    if (gflagChk(0x103) == 0) {
        stage_SetAnimation(0x148, 0, 0);
    } else {
        stage_SetAnimation(0x148, 0, -1);
    }

    if (gflagChk(0x104) == 0) {
        stage_SetAnimation(0x149, 0, 0);
    } else {
        stage_SetAnimation(0x149, 0, -1);
    }

    if (gflagChk(0xFD) == 0) {
        scpSearchGobj(0x563)->f16C = 0;
    }
}

void actSt05dInit(void)
{
    if (gflagChk(0x103) == 0) {
        stage_SetAnimation(0x148, 0, 0);

        SetWayGroupActive(3, 0);
    } else {
        stage_SetAnimation(0x148, 0, -1);

        SetWayGroupActive(3, 1);
    }

    if (gflagChk(0x104) == 0) {
        stage_SetAnimation(0x149, 0, 0);

        SetWayGroupActive(4, 0);
    } else {
        stage_SetAnimation(0x149, 0, -1);

        SetWayGroupActive(4, 1);
    }

    if (gflagChk(0xFD) == 0) {
        stage_SetAnimation(0x14A, 0, 0);
        stage_SetAnimation(0x15E, 0, 0);
    } else {
        stage_SetAnimation(0x14A, 0, -1);
        stage_SetAnimation(0x15E, 0, -1);

        FinishHint(0x18);
    }

    if (gflagChk(0x112) == 0) {
        stage_SetAnimation(0x151, 0, 0);
    } else {
        stage_SetAnimation(0x151, 0, -1);
    }

    if (gflagChk(0x113) == 0) {
        stage_SetAnimation(0x152, 0, 0);
    } else {
        stage_SetAnimation(0x152, 0, -1);
    }

    if (gflagChk(0x114) == 0) {
        stage_SetAnimation(0x153, 0, 0);
    } else {
        stage_SetAnimation(0x153, 0, -1);
    }

    if (gflagChk(0x115) == 0) {
        stage_SetAnimation(0x154, 0, 0);
    } else {
        stage_SetAnimation(0x154, 0, -1);
    }

    if (gflagChk(0x116) == 0) {
        stage_SetAnimation(0x155, 0, 0);
    } else {
        stage_SetAnimation(0x155, 0, -1);
    }

    if (gflagChk(0x117) == 0) {
        stage_SetAnimation(0x156, 0, 0);
    } else {
        stage_SetAnimation(0x156, 0, -1);
    }

    if (gflagChk(0x118) == 0) {
        stage_SetAnimation(0x157, 0, 0);
    } else {
        stage_SetAnimation(0x157, 0, -1);
    }

    if (gflagChk(0xA5) != 0 && gflagChk(0xEA) == 0) {
        stage_SetAnimation(0x15B, 0, -1);
    }

    if (gflagChk(0xA5) == 0 || gflagChk(0xEA) != 0) {
        stage_SetAnimation(0x15B, 0, 0);
    }

    if (gflagChk(0x11A) != 0) {
        stage_SetAnimation(0xE5, 0, 0xC8);
    } else {
        stage_SetAnimation(0xE5, 0, 0);
    }
}

void actSt05eInit(void)
{
    if (gflagChk(0xE7) == 0) {
        SetWayGroupActive(5, 0);
    } else {
        SetWayGroupActive(5, 1);
    }

    if (gflagChk(0x103) == 0) {
        stage_SetAnimation(0x148, 0, 0);
    } else {
        stage_SetAnimation(0x148, 0, -1);
    }

    if (gflagChk(0x104) == 0) {
        stage_SetAnimation(0x149, 0, 0);
    } else {
        stage_SetAnimation(0x149, 0, -1);
    }
}

extern ActMail D_004F92A0[];
extern void actSt04rCrest2Main(volatile int a0);

void actSt04rCrest02(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xF4) == 0) {
        if (D_00639ED4 == 0x1C) {
            stage_SetAnimation(0x137, 0, 0);
        } else {
            stage_SetAnimation(0x138, 0, 0);
        }

        D_004F92A0[0].func = actSt04rCrest2Main;
        self->mail = D_004F92A0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        if (D_00639ED4 == 0x1C) {
            stage_SetAnimation(0x137, 0, -1);
        } else {
            stage_SetAnimation(0x138, 0, -1);
        }

        D_0063AA08 = 0;
    }
}

void openGateSub(volatile int a0)
{
    stage_SetAnimation(D_0063C540, 1, 0);

    while (stage_CheckAnimationFrame(D_0063C540, 0x1E, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C538 = iosPadActRequest(D_00639EAC, 0xA);
    st05d_hasi = 0x80;
    iosPadActVolumeSet(D_0063C538, 0x80);

    while (stage_CheckAnimationFrame(D_0063C540, 0xBE, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(D_0063C538);

    while (stage_CheckAnimationFinish(D_0063C540) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C53C = 1;
    _ACTWait(0);
}

void openGate(int a0)
{
    int th;

    lt_switch_layout(0x37);

    D_0063AA08 = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(D_0063C544, &crest1_4r, 0, 1, 1);

    while (crest1_4r == 0) {
        _ACTWait(1);
    }

    th = actCreateSubThread(openGateSub, 0x15);

    D_0063C53C = 0;
    D_0063C538 = -1;

    while (D_0063C53C == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri((int *)(th + 0x24), 0x22);

    if (D_0063C53C == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&crest1_4r, 0x100);

        if (D_0063C538 >= 0) {
            iosPadActStop(D_0063C538);
        }

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(D_0063C540, 0, -1);

        scpFadeIn(3.0f);
    }

    scpWakeupEnemyAll();

    lt_switch_layout(0x36);

    D_0063AA08 = 0;
}

void actSt04rCrest2Main(volatile int a0)
{
    int anim;

    if (D_00639ED4 == 0x1C) {
        anim = 0x137;
        while (scpIsTorchLightOn(0x580) == 0 || scpIsTorchLightOn(0x581) == 0 ||
               gflagChk(0xFB) == 0) {
            _ACTWait(1);
        }

        D_0063C540 = anim;
    }

    if (D_00639ED4 == 0x1D) {
        anim = 0x138;

        while (scpIsTorchLightOn(0x5CF) == 0 || scpIsTorchLightOn(0x5D0) == 0 ||
               gflagChk(0xFB) == 0) {
            _ACTWait(1);
        }

        D_0063C540 = anim;
    }

    D_0063C544 = 0x19;
    openGate(a0);

    if (D_00639ED4 == 0x1C) {
        gflagOn(0xF8);
    } else {
        gflagOn(0xF7);
    }

    _ACTWait(1);

    gflagOn(0xF4);
    gflagOff(0xF6);
    gflagOff(0xF9);
    gflagOff(0xE9);
}

void actSt04rCrest3Main(volatile int a0)
{
    while (scpIsTorchLightOn(0x5D1) == 0 || scpIsTorchLightOn(0x5D2) == 0 || gflagChk(0xFC) == 0) {
        _ACTWait(1);
    }

    scpSleepEnemyOne(0xEAD);

    gflagOn(0xAA);

    fightSoundProcessRequestPause();

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    D_0063C540 = 0x139;
    D_0063C544 = 0x18;
    openGate(a0);

    scpWakeupEnemyOne(0xEAD);

    fightSoundProcessRequestStart();
    _ACTWait(1);

    gflagOn(0xF5);
    gflagOff(0xF6);
    gflagOff(0xF7);
    gflagOff(0xF8);
    gflagOn(0xF9);
    gflagOff(0xE9);
}

extern ActMail D_004F92E0[];
extern void actSt04rSolarBeamChk(volatile int a0);

void actSt04rSolarBeam(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    solar4r = 0;

    if (gflagChk(0xEA) == 0) {
        scpAdpcmPlayRequestFunc(0x1C, &solar4r, 0, 1, 0);

        if (gflagChk(0xF3) != 0 && gflagChk(0xF4) != 0 && gflagChk(0xF5) != 0 &&
            gflagChk(0xE8) != 0) {
            if (D_00639EA4 != 0) {
                scpPlayMot(D_00639EA4, 0);
            }

            lt_switch_layout(0x37);

            D_0063AA08 = 1;
            gflagOn(0x185);

            scpFadeOut(255.0f, 0, 0, 0);

            while (solar4r == 0) {
                _ACTWait(1);
            }

            scpFadeIn(6.0f);
        }

        D_004F92E0[0].func = actSt04rSolarBeamChk;
        self->mail = D_004F92E0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        D_0063AA08 = 0;
    }
}

void actSt04rSolarBeamChk(volatile int a0)
{
    while (gflagChk(0xF3) == 0 || gflagChk(0xF4) == 0 || gflagChk(0xF5) == 0 ||
           gflagChk(0xE8) == 0) {
        _ACTWait(1);
    }

    gflagOn(0xEA);

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    while (solar4r == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(solar4r + 0x2C));

    preload(0xF);

    stage_SetAnimation(0x15A, 1, 0);
    stage_SetAnimation(0x126, 1, 0);

    while (stage_CheckAnimationFinish(0x126) == 0) {
        if ((D_0028F8F0[0].trg & 0x800) != 0 && scpAdpcmPlayRequestNum() == 0) {
            scpFadeOut(16.0f, 0, 0, 0);

            scpAdpcmFadeCloseFunc(&solar4r, 0x100);

            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }

            stage_SetAnimation(0x15A, 0, -1);
            stage_SetAnimation(0x126, 0, -1);

            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }

    D_0063AA08 = 0;

    scpWakeupEnemyAll();

    RequestStageChange(0xF, D_00639EA4, 0, 2.0f, 8.0f);
}

void actSt04rStairSub(volatile int a0)
{
    long long buf[2];
    float dir[4];

    _ACTWait(0x3C);

    while (crest3_4r == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(crest3_4r + 0x2C));

    stage_SetAnimation(0x15E, 1, 0);

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);

    scpPlayMot(D_00639EA4, 0);
    scpPlayMot(D_00639EA8, 0x214);

    scpPlayPosSet(D_00639EA4, -55.0f, 28.0f, -3881.0f);
    scpPlayPosSet(D_00639EA8, 58.0f, 28.0f, -3891.0f);

    buf[0] = D_00622AC0[0];
    buf[1] = D_00622AC0[1];
    sceVu0SubVector(dir, buf, test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    buf[0] = D_00622AC0[0];
    buf[1] = D_00622AC0[1];
    sceVu0SubVector(dir, buf, test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, dir);

    D_0063C548 = 1;

    while (stage_CheckAnimationFinish(0x15E) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x11);

    stage_SetAnimation(0x14A, 1, 0);

    while (stage_CheckAnimationFrame(0x14A, 0x8C, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C538 = iosPadActRequest(D_00639EAC, 9);
    st05d_hasi = 0x80;
    iosPadActVolumeSet(D_0063C538, 0x80);

    while (stage_CheckAnimationFinish(0x14A) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C53C = 1;
    _ACTWait(0);
}

void actSt04rStairChk(volatile int a0)
{
    int th;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0xB000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0xB000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);

    D_0063AA08 = 1;
    gflagOn(0xFD);

    FinishHint(0x18);

    scpSleepEnemyAll();

    scpSearchGobj(0x5F3)->f16C = 0;

    stage_SetAnimation(0x15F, -1, -2);

    scpAdpcmPlayRequestFunc(0x3D, &crest3_4r, 1, 1, 0);

    th = actCreateSubThread(actSt04rStairSub, 0x15);

    D_0063C53C = 0;
    D_0063C538 = -1;
    D_0063C548 = 0;

    while (D_0063C53C == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    if (D_0063C53C == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (crest3_4r == 0) {
            _ACTWait(1);
        }

        scpAdpcmFadeCloseFunc(&crest3_4r, 0x200);

        while (D_0063C548 == 0) {
            _ACTWait(1);
        }

        iosThreadSetPri((int *)(th + 0x24), 0x22);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(0x15E, 0, -1);
        stage_SetAnimation(0x14A, 0, -1);
        _ACTWait(1);

        scpPlayMot(D_00639EA4, 0);
        scpPlayMot(D_00639EA8, 0x214);

        scpPlayPosSet(D_00639EA4, -55.0f, 234.0f, -3881.0f);
        scpPlayPosSet(D_00639EA8, 58.0f, 234.0f, -3891.0f);

        _ACTWait(1);

        iosOmSendMail(D_00639EA8, 0x3E, D_00639EA4);

        scpFadeIn(3.0f);
    } else {
        iosThreadSetPri((int *)(th + 0x24), 0x22);
    }

    if (D_0063C538 >= 0) {
        iosPadActStop(D_0063C538);
    }

    scpPlayMot(D_00639EA4, 0);
    scpPlayMot(D_00639EA8, 0x214);

    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);

    scpWakeupEnemyAll();

    D_0063AA08 = 0;

    lt_switch_layout(0x36);
}

void actSt04rSekizoChk(volatile int a0)
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

    scpAdpcmPlayRequestFunc(0x12, &stair5d, 1, 1, 1);

    while (stair5d == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(1, 1);

    stage_SetAnimation(0x14B, 1, 0);

    st04r_yure = iosPadActRequest(D_00639EAC, 9);
    st04r_yure_vol = 0x80;
    iosPadActVolumeSet(st04r_yure, 0x80);

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);

    scpPlayMot(D_00639EA4, 0);
    scpPlayMot(D_00639EA8, 0x214);

    scpPlayPosSet(D_00639EA8, 0.0f, -1300.0f, -1700.0f);
    scpPlayPosSet(D_00639EA4, 20.0f, -1300.0f, -1700.0f);
    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(a0), test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, dir);

    D_0063AA08 = 1;

    sceVu0SubVector(dir, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    scpSekizouCheckPoint();

    scpPlayMot(D_00639EA8, 0x285);
    scpPlayWaitMotEnd(D_00639EA8);

    gflagOn(0xFE);

    while (stage_CheckAnimationFrame(0x14B, 0x97, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(st04r_yure);

    while (stage_CheckAnimationFinish(0x14B) == 0) {
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

void actSt04rRope1Chk(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(0x105) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(0x5B3))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(0x144, 1, 0);

            while (stage_CheckAnimationFinish(0x144) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(0x5B3)->f16C = 0;

            gflagOn(0x105);

            stage_SetAnimation(0x140, 1, 0);

            while (stage_CheckAnimationFinish(0x140) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        }
    }
}

void actSt04rRope2Chk(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(0x106) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(0x5B4))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(0x145, 1, 0);

            while (stage_CheckAnimationFinish(0x145) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(0x5B4)->f16C = 0;

            gflagOn(0x106);

            stage_SetAnimation(0x141, 1, 0);

            while (stage_CheckAnimationFinish(0x141) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        }
    }
}

extern void actSt04rBrg1Sub(volatile int a0);

void actSt04rBrgCommon(volatile int a0)
{
    int th;

    lt_switch_layout(0x37);

    D_0063AA08 = 1;
    scpSleepEnemyAll();

    scpAdpcmPlayRequestFunc(0x56, (int *)&sekizo5c, 1, 1, 0);

    th = actCreateSubThread(actSt04rBrg1Sub, 0x15);

    D_0063C53C = 0;

    while (D_0063C53C == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri((int *)(th + 0x24), 0x22);

    if (D_0063C53C == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc((int *)&sekizo5c, 0x100);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(sekizo_4r, 0, -1);

        scpFadeIn(3.0f);
    }

    scpWakeupEnemyAll();

    D_0063AA08 = 0;

    lt_switch_layout(0x36);
}

void actSt04rRope3Chk(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(0x107) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(0x5B5))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(0x146, 1, 0);

            while (stage_CheckAnimationFinish(0x146) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(0x5B5)->f16C = 0;

            gflagOn(0x107);

            stage_SetAnimation(0x142, 1, 0);

            while (stage_CheckAnimationFinish(0x142) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        }
    }
}

void actSt04rRope4Chk(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(0x108) == 0) {
        switch (GetAttackCheckBoundaryManagerStatus(scpSearchGobj(0x5B6))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_SetAnimation(0x147, 1, 0);

            while (stage_CheckAnimationFinish(0x147) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            scpSearchGobj(0x5B6)->f16C = 0;

            gflagOn(0x108);

            stage_SetAnimation(0x143, 1, 0);

            while (stage_CheckAnimationFinish(0x143) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        }
    }
}

void actSt04rMonyou01Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x1000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x1000000) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;

    gflagOn(0x112);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        if (GetCharHeldItem(D_00639EA4) != 1) {
            scpPlayStart(D_00639EA4);
            scpPlayStart(D_00639EA8);
        }

        scpPlayMotReq(D_00639EA4, 1);
        scpPlayMotReq(D_00639EA8, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

    stage_SetAnimation(0x151, 1, 0);

    soundSeDefPlay(0x534, 0, 0, 1);

    while (stage_CheckAnimationFrame(0x151, 0x1E, 0) == 0) {
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

void actSt04rMonyou02Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x2000000) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;

    gflagOn(0x113);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        if (GetCharHeldItem(D_00639EA4) != 1) {
            scpPlayStart(D_00639EA4);
            scpPlayStart(D_00639EA8);
        }

        scpPlayMotReq(D_00639EA4, 1);
        scpPlayMotReq(D_00639EA8, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

    stage_SetAnimation(0x152, 1, 0);

    soundSeDefPlay(0x534, 0, 0, 1);

    while (stage_CheckAnimationFrame(0x152, 0x1E, 0) == 0) {
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

void actSt04rMonyou03Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x3000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x3000000) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;

    gflagOn(0x114);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        if (GetCharHeldItem(D_00639EA4) != 1) {
            scpPlayStart(D_00639EA4);
            scpPlayStart(D_00639EA8);
        }

        scpPlayMotReq(D_00639EA4, 1);
        scpPlayMotReq(D_00639EA8, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

    stage_SetAnimation(0x153, 1, 0);

    soundSeDefPlay(0x534, 0, 0, 1);

    while (stage_CheckAnimationFrame(0x153, 0x1E, 0) == 0) {
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

void actSt04rMonyou04Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x4000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x4000000) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;

    gflagOn(0x115);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        if (GetCharHeldItem(D_00639EA4) != 1) {
            scpPlayStart(D_00639EA4);
            scpPlayStart(D_00639EA8);
        }

        scpPlayMotReq(D_00639EA4, 1);
        scpPlayMotReq(D_00639EA8, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

    stage_SetAnimation(0x154, 1, 0);

    soundSeDefPlay(0x534, 0, 0, 1);

    while (stage_CheckAnimationFrame(0x154, 0x1E, 0) == 0) {
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

void actSt04rMonyou05Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x5000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x5000000) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;

    gflagOn(0x116);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        if (GetCharHeldItem(D_00639EA4) != 1) {
            scpPlayStart(D_00639EA4);
            scpPlayStart(D_00639EA8);
        }

        scpPlayMotReq(D_00639EA4, 1);
        scpPlayMotReq(D_00639EA8, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

    stage_SetAnimation(0x155, 1, 0);

    soundSeDefPlay(0x534, 0, 0, 1);

    while (stage_CheckAnimationFrame(0x155, 0x1E, 0) == 0) {
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

void actSt04rMonyou06Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x6000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x6000000) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;

    gflagOn(0x117);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        if (GetCharHeldItem(D_00639EA4) != 1) {
            scpPlayStart(D_00639EA4);
            scpPlayStart(D_00639EA8);
        }

        scpPlayMotReq(D_00639EA4, 1);
        scpPlayMotReq(D_00639EA8, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

    stage_SetAnimation(0x156, 1, 0);

    soundSeDefPlay(0x534, 0, 0, 1);

    while (stage_CheckAnimationFrame(0x156, 0x1E, 0) == 0) {
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

void actSt04rMonyou07Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA4, 0x7000000) == 0 ||
           scpTriggerFloorAttr(D_00639EA8, 0x7000000) == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;

    gflagOn(0x118);

    scpSleepEnemyAll();

    if (ACTGame_FLAG_TETSUNAGI() != 0) {
        if (GetCharHeldItem(D_00639EA4) != 1) {
            scpPlayStart(D_00639EA4);
            scpPlayStart(D_00639EA8);
        }

        scpPlayMotReq(D_00639EA4, 1);
        scpPlayMotReq(D_00639EA8, 1);
        _ACTWait(1);

        ACTGame_ConnectHand();
    }

    stage_SetAnimation(0x157, 1, 0);

    soundSeDefPlay(0x534, 0, 0, 1);

    while (stage_CheckAnimationFrame(0x157, 0x1E, 0) == 0) {
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

void actSt04rBarricadeChk(volatile int a0)
{
    int n;

    while ((n = scpIsBombExplode(0x13)) == 0 || scpTriggerBall(a0, n, 350.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    gflagOn(0x109);
    _ACTWait(5);

    stage_SetAnimation(0x158, 1, 0);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(0x158) == 0) {
        if ((D_0028F8F0[0].trg & 0x800) != 0 && scpAdpcmPlayRequestNum() == 0) {
            scpFadeOut(16.0f, 0, 0, 0);

            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }

            stage_SetAnimation(0x158, 0, -1);

            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 3);

    scpWakeupEnemyAll();

    D_0063AA08 = 0;

    lt_switch_layout(0x36);
}

extern ActMail D_004F95E0[];
extern void actSt04rGondolaCharaChk(volatile int a0);

void actSt04rGondolaChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttr(D_00639EA4, 0xA000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);

    D_0063AA08 = 1;
    scpSleepEnemyAll();

    _ACTWait(0xF);

    if (gflagChk(0x11A) != 0) {
        stage_SetAnimation(0xE5, 1, 0xC8);

        scpWakeupItemWithBoundary(-675.0f, -150.0f, -1600.0f, 200.0f);

        while (stage_CheckAnimationFrame(0xE5, 0xDC, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(0x529, 0, 0, 1);

        while (stage_CheckAnimationFrame(0xE5, 0xF0, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(0x52A, 0, 0, 1);

        while (stage_CheckAnimationFrame(0xE5, 0xFA, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(0x527, 0, 0, 1);

        while (stage_CheckAnimationFrame(0xE5, 0x19F, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(0x528, 0, 0, 1);

        while (stage_CheckAnimationFinish(0xE5) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        gflagOff(0x11A);
    } else {
        stage_SetAnimation(0xE5, 1, 0);

        scpWakeupItemWithBoundary(-675.0f, -1200.0f, -1600.0f, 200.0f);

        SetGirlDangerGObj(D_00639EA4);

        soundSeDefPlay(0x527, 0, 0, 1);

        while (stage_CheckAnimationFrame(0xE5, 0x91, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(0x528, 0, 0, 1);
        soundSeDefPlay(0x529, 0, 0, 1);

        while (stage_CheckAnimationFrame(0xE5, 0xAA, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(0x52A, 0, 0, 1);

        while (stage_CheckAnimationFrame(0xE5, 0xC8, 1) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        ClearGirlDangerGObj();

        gflagOn(0x11A);
    }

    if (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0xA000000) == 0) {
        gflagOn(0x11E);
    } else {
        gflagOff(0x11E);
    }

    D_0063AA08 = 0;

    lt_switch_layout(0x36);

    scpWakeupEnemyAll();

    D_004F95E0[0].func = actSt04rGondolaCharaChk;
    sub->mail = D_004F95E0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern ActMail D_004F9300[];
extern void actSt04rSolarStageChangeChk(volatile int a0);

void actSt04rSolarStageChange(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xEA) == 0) {
        D_004F9300[0].func = actSt04rSolarStageChangeChk;
        self->mail = D_004F9300;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern ActMail D_004F9280[];
extern void actSt04rCrestMain(volatile int a0);

void actSt04rCrest01(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xF3) == 0) {
        stage_SetAnimation(0x135, 0, 0);

        D_004F9280[0].func = actSt04rCrestMain;
        self->mail = D_004F9280;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x135, 0, -1);
        D_0063AA08 = 0;
    }
}

extern ActMail D_004F92C0[];

void actSt04rCrest03(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xF5) == 0) {
        stage_SetAnimation(0x139, 0, 0);

        D_004F92C0[0].func = actSt04rCrest3Main;
        self->mail = D_004F92C0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x139, 0, -1);
        D_0063AA08 = 0;
    }
}

extern ActMail D_004F9180[];
extern void actSt04rC1BallMain(volatile int a0);

void actSt04rC1Ball(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xFA) == 0) {
        scpSearchGobj(0x57C)->f16C = 0;
        scpSearchGobj(0x57D)->f16C = 0;

        stage_SetAnimation(0x13D, 0, 0);

        D_004F9180[0].func = actSt04rC1BallMain;
        self->mail = D_004F9180;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x13D, 0, -1);
    }
}

extern ActMail D_004F91E0[];
extern void actSt04rC2BallMain(volatile int a0);

void actSt04rC2Ball(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xFB) == 0) {
        scpSearchGobj(0x5CF)->f16C = 0;
        scpSearchGobj(0x5D0)->f16C = 0;

        stage_SetAnimation(0x13E, 0, 0);

        D_004F91E0[0].func = actSt04rC2BallMain;
        self->mail = D_004F91E0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x13E, 0, -1);
    }
}

extern ActMail D_004F9240[];
extern void actSt04rC3BallMain(volatile int a0);

void actSt04rC3Ball(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xFC) == 0) {
        scpSearchGobj(0x5D1)->f16C = 0;
        scpSearchGobj(0x5D2)->f16C = 0;

        stage_SetAnimation(0x13F, 0, 0);

        D_004F9240[0].func = actSt04rC3BallMain;
        self->mail = D_004F9240;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x13F, 0, -1);
    }
}

extern ActMail D_004F9320[];

void actSt04rStair(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xFD) == 0) {
        if (D_00639EA8 != 0) {
            D_004F9320[0].func = actSt04rStairChk;
            self->mail = D_004F9320;
            ACTSendMailCorrect(a0, 0x1AE);
            _ACTWait(0);
        }
    } else {
        scpSearchGobj(0x5F3)->f16C = 0;

        stage_SetAnimation(0x15F, -1, -2);
    }
}

extern ActMail D_004F93A0[];
extern void actSt04rBrg1Chk(volatile int a0);

void actSt04rBrg1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x103) == 0) {
        D_004F93A0[0].func = actSt04rBrg1Chk;
        self->mail = D_004F93A0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern ActMail D_004F9420[];
extern void actSt04rBrg2Chk(volatile int a0);

void actSt04rBrg2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x104) == 0) {
        D_004F9420[0].func = actSt04rBrg2Chk;
        self->mail = D_004F9420;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern ActMail D_004F9460[];
extern void actSt04rBrg1WayChk(volatile int a0);

void actSt04rBrg1Way(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x103) == 0) {
        D_004F9460[0].func = actSt04rBrg1WayChk;
        self->mail = D_004F9460;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern ActMail D_004F9480[];
extern void actSt04rBrg2WayChk(volatile int a0);

void actSt04rBrg2Way(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x104) == 0) {
        D_004F9480[0].func = actSt04rBrg2WayChk;
        self->mail = D_004F9480;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern ActMail D_004F9360[];

void actSt04rRope1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x105) == 0) {
        stage_SetAnimation(0x140, 0, 0);

        D_004F9360[0].func = actSt04rRope1Chk;
        self->mail = D_004F9360;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x140, 0, -1);

        scpSearchGobj(0x5B3)->f16C = 0;
    }
}

extern ActMail D_004F9380[];

void actSt04rRope2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x106) == 0) {
        stage_SetAnimation(0x141, 0, 0);

        D_004F9380[0].func = actSt04rRope2Chk;
        self->mail = D_004F9380;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x141, 0, -1);

        scpSearchGobj(0x5B4)->f16C = 0;
    }
}

extern ActMail D_004F93E0[];

void actSt04rRope3(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x107) == 0) {
        stage_SetAnimation(0x142, 0, 0);

        D_004F93E0[0].func = actSt04rRope3Chk;
        self->mail = D_004F93E0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x142, 0, -1);

        scpSearchGobj(0x5B5)->f16C = 0;
    }
}

extern ActMail D_004F9400[];

void actSt04rRope4(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x108) == 0) {
        stage_SetAnimation(0x143, 0, 0);

        D_004F9400[0].func = actSt04rRope4Chk;
        self->mail = D_004F9400;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x143, 0, -1);

        scpSearchGobj(0x5B6)->f16C = 0;
    }
}

extern ActMail D_004F9340[];

void actSt04rSekizo(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xFE) == 0) {
        stage_SetAnimation(0x14B, 0, 0);

        D_004F9340[0].func = actSt04rSekizoChk;
        self->mail = D_004F9340;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x14B, 0, -1);
    }
}

extern ActMail D_004F9580[];

void actSt04rBarricade(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x109) == 0) {
        stage_SetAnimation(0x158, 0, 0);

        D_004F9580[0].func = actSt04rBarricadeChk;
        self->mail = D_004F9580;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x158, 0, -1);
    }
}

extern ActMail D_004F95A0[];
extern ActMail D_004F95C0[];

void actSt04rGondola(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x11A) != 0) {
        stage_SetAnimation(0xE5, 0, 0xC8);

        D_004F95A0[0].func = actSt04rGondolaChk;
        self->mail = D_004F95A0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xE5, 0, 0);

        D_004F95C0[0].func = actSt04rGondolaChk;
        self->mail = D_004F95C0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSt04rCrest01XL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xF3) == 0) {
        stage_SetAnimation(0x13A, 0, 0);
    } else {
        stage_SetAnimation(0x13A, 0, -1);
    }
}

void actSt04rCrest02XL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xF4) == 0) {
        stage_SetAnimation(0x13B, 0, 0);
    } else {
        stage_SetAnimation(0x13B, 0, -1);
    }
}

void actSt04rCrest03XL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xF5) == 0) {
        stage_SetAnimation(0x13C, 0, 0);
    } else {
        stage_SetAnimation(0x13C, 0, -1);
    }
}

void actSt04rC2BallXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xFB) == 0) {
        stage_SetAnimation(0x13E, 0, 0);

        scpSearchGobj(0x580)->f16C = 0;
        scpSearchGobj(0x581)->f16C = 0;
    } else {
        stage_SetAnimation(0x13E, 0, -1);
    }
}

void actSt04rC3BallXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xFC) == 0) {
        stage_SetAnimation(0x13F, 0, 0);

        scpSearchGobj(0x61A)->f16C = 0;
        scpSearchGobj(0x61B)->f16C = 0;
    } else {
        stage_SetAnimation(0x13F, 0, -1);
    }
}

extern ActMail D_004F9620[];
extern void actSt04rTorch1_1Chk(volatile int a0);

void actSt04rTorch1_1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x10A) == 0) {
        D_004F9620[0].func = actSt04rTorch1_1Chk;
        self->mail = D_004F9620;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        scpTorchLightOn(0x57C);
        stage_SetAnimation(0xD2, 0, -1);
    }
}

extern ActMail D_004F9640[];
extern void actSt04rTorch1_2Chk(volatile int a0);

void actSt04rTorch1_2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x10B) == 0) {
        D_004F9640[0].func = actSt04rTorch1_2Chk;
        self->mail = D_004F9640;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        scpTorchLightOn(0x57D);
        stage_SetAnimation(0xD3, 0, -1);
    }
}

extern ActMail D_004F9660[];
extern void actSt04rTorch2_1Chk(volatile int a0);

void actSt04rTorch2_1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x10C) != 0 || gflagChk(0x10E) != 0) {
        scpTorchLightOn(0x5CF);
    } else {
        D_004F9660[0].func = actSt04rTorch2_1Chk;
        self->mail = D_004F9660;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern ActMail D_004F9680[];
extern void actSt04rTorch2_2Chk(volatile int a0);

void actSt04rTorch2_2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x10D) != 0 || gflagChk(0x10F) != 0) {
        scpTorchLightOn(0x5D0);
    } else {
        D_004F9680[0].func = actSt04rTorch2_2Chk;
        self->mail = D_004F9680;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern ActMail D_004F96A0[];
extern void actSt04rTorch3_1Chk(volatile int a0);

void actSt04rTorch3_1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x110) == 0) {
        D_004F96A0[0].func = actSt04rTorch3_1Chk;
        self->mail = D_004F96A0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        scpTorchLightOn(0x5D1);
    }
}

extern ActMail D_004F96C0[];
extern void actSt04rTorch3_2Chk(volatile int a0);

void actSt04rTorch3_2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x111) == 0) {
        D_004F96C0[0].func = actSt04rTorch3_2Chk;
        self->mail = D_004F96C0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        scpTorchLightOn(0x5D2);
    }
}

extern ActMail D_004F96E0[];
extern void actSt04rTorch2_1XLChk(volatile int a0);

void actSt04rTorch2_1XL(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x10C) != 0 || gflagChk(0x10E) != 0) {
        scpTorchLightOn(0x580);
        stage_SetAnimation(0xD4, 0, -1);
    } else {
        D_004F96E0[0].func = actSt04rTorch2_1XLChk;
        self->mail = D_004F96E0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern ActMail D_004F9700[];
extern void actSt04rTorch2_2XLChk(volatile int a0);

void actSt04rTorch2_2XL(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x10D) != 0 || gflagChk(0x10F) != 0) {
        scpTorchLightOn(0x581);
        stage_SetAnimation(0xD5, 0, -1);
    } else {
        D_004F9700[0].func = actSt04rTorch2_2XLChk;
        self->mail = D_004F9700;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSt04rTorch3_1XL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x110) != 0) {
        scpTorchLightOn(0x61A);
    }
}

void actSt04rTorch3_2XL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x111) != 0) {
        scpTorchLightOn(0x61B);
    }
}

extern ActMail D_004F94A0[];

void actSt04rMonyou01(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x112) == 0) {
        stage_SetAnimation(0x151, 0, 0);

        D_004F94A0[0].func = actSt04rMonyou01Chk;
        self->mail = D_004F94A0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x151, 0, -1);
    }
}

extern ActMail D_004F94C0[];

void actSt04rMonyou02(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x113) == 0) {
        stage_SetAnimation(0x152, 0, 0);

        D_004F94C0[0].func = actSt04rMonyou02Chk;
        self->mail = D_004F94C0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x152, 0, -1);
    }
}

extern ActMail D_004F94E0[];

void actSt04rMonyou03(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x114) == 0) {
        stage_SetAnimation(0x153, 0, 0);

        D_004F94E0[0].func = actSt04rMonyou03Chk;
        self->mail = D_004F94E0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x153, 0, -1);
    }
}

extern ActMail D_004F9500[];

void actSt04rMonyou04(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x115) == 0) {
        stage_SetAnimation(0x154, 0, 0);

        D_004F9500[0].func = actSt04rMonyou04Chk;
        self->mail = D_004F9500;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x154, 0, -1);
    }
}

extern ActMail D_004F9520[];

void actSt04rMonyou05(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x116) == 0) {
        stage_SetAnimation(0x155, 0, 0);

        D_004F9520[0].func = actSt04rMonyou05Chk;
        self->mail = D_004F9520;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x155, 0, -1);
    }
}

extern ActMail D_004F9540[];

void actSt04rMonyou06(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x117) == 0) {
        stage_SetAnimation(0x156, 0, 0);

        D_004F9540[0].func = actSt04rMonyou06Chk;
        self->mail = D_004F9540;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x156, 0, -1);
    }
}

extern ActMail D_004F9560[];

void actSt04rMonyou07(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x118) == 0) {
        stage_SetAnimation(0x157, 0, 0);

        D_004F9560[0].func = actSt04rMonyou07Chk;
        self->mail = D_004F9560;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x157, 0, -1);
    }
}

void actSt05cDoorInit(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xA5) != 0 && gflagChk(0xEA) == 0) {
        stage_SetAnimation(0x15B, 0, -1);
    }

    if (gflagChk(0xA5) == 0 || gflagChk(0xEA) != 0) {
        stage_SetAnimation(0x15B, 0, 0);
    }
}

extern ActMail D_004F9160[];

void actSt04rC1BallMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = D_004F9160;
    while (1) {
        _ACTWait(1);
    }
}

extern ActMail D_004F91A0[];
extern void actSt04rC1BallTurn(volatile int a0);

void actSt04rC1BallSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    D_004F91A0[0].func = actSt04rC1BallTurn;
    sub->mail = D_004F91A0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt04rC1BallTurn(volatile int a0)
{
    turnBall(a0, 0xFA, 0x13D, 0x57C, 0x57D);
}

extern ActMail D_004F91C0[];

void actSt04rC2BallMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = D_004F91C0;
    while (1) {
        _ACTWait(1);
    }
}

extern ActMail D_004F9200[];
extern void actSt04rC2BallTurn(volatile int a0);

void actSt04rC2BallSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    D_004F9200[0].func = actSt04rC2BallTurn;
    sub->mail = D_004F9200;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt04rC2BallTurn(volatile int a0)
{
    turnBall(a0, 0xFB, 0x13E, 0x5CF, 0x5D0);
}

extern ActMail D_004F9220[];

void actSt04rC3BallMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = D_004F9220;
    while (1) {
        _ACTWait(1);
    }
}

extern ActMail D_004F9260[];
extern void actSt04rC3BallTurn(volatile int a0);

void actSt04rC3BallSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    D_004F9260[0].func = actSt04rC3BallTurn;
    sub->mail = D_004F9260;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt04rC3BallTurn(volatile int a0)
{
    turnBall(a0, 0xFC, 0x13F, 0x5D1, 0x5D2);
}

void actSt04rCrestMain(volatile int a0)
{
    while (scpIsTorchLightOn(0x57C) == 0 || scpIsTorchLightOn(0x57D) == 0 || gflagChk(0xFA) == 0) {
        _ACTWait(1);
    }

    D_0063C540 = 0x135;
    D_0063C544 = 0x1B;
    openGate(a0);
    _ACTWait(1);

    gflagOn(0xF3);
    gflagOn(0xF6);
    gflagOff(0xF7);
    gflagOff(0xF8);
    gflagOff(0xF9);
    gflagOff(0xE9);
}

void actSt04rSolarStageChangeChk(volatile int a0)
{
    while (gflagChk(0xF3) == 0 || gflagChk(0xF4) == 0 || gflagChk(0xF5) == 0 ||
           gflagChk(0xE8) == 0) {
        _ACTWait(1);
    }

    RequestStageChange(8, D_00639EA4, 0, 2.0f, 8.0f);
}

void actSt04rStairEvent(int x)
{
    volatile int local = x;
}

void actSt04rRope1Event(int x)
{
    volatile int local = x;
}

void actSt04rRope2Event(int x)
{
    volatile int local = x;
}

void actSt04rBrg1Event(int x)
{
    volatile int local = x;
}

extern ActMail D_004F93C0[];

void actSt04rBrg1Chk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (gflagChk(0x105) == 0 || gflagChk(0x106) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x103);

    sekizo_4r = 0x148;

    D_004F93C0[0].func = actSt04rBrgCommon;
    sub->mail = D_004F93C0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt04rBrg1Sub(volatile int a0)
{
    _ACTWait(0x3C);

    while (sekizo5c == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(sekizo5c + 0x2C));

    stage_SetAnimation(sekizo_4r, 1, 0);

    while (stage_CheckAnimationFrame(sekizo_4r, 0x4B, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_CheckAnimationFinish(sekizo_4r) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C53C = 1;
    _ACTWait(0);
}

void actSt04rRope3Event(int x)
{
    volatile int local = x;
}

void actSt04rRope4Event(int x)
{
    volatile int local = x;
}

void actSt04rBrg2Event(int x)
{
    volatile int local = x;
}

extern ActMail D_004F9440[];

void actSt04rBrg2Chk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (gflagChk(0x107) == 0 || gflagChk(0x108) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x104);

    sekizo_4r = 0x149;

    D_004F9440[0].func = actSt04rBrgCommon;
    sub->mail = D_004F9440;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt04rBrg1WayChk(volatile int a0)
{
    while (gflagChk(0x103) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(3, 1);
}

void actSt04rBrg2WayChk(volatile int a0)
{
    while (gflagChk(0x103) == 0 || gflagChk(0x104) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(4, 1);
}

void actSt04rMonyou01Event(int x)
{
    volatile int local = x;
}

void actSt04rMonyou02Event(int x)
{
    volatile int local = x;
}

void actSt04rMonyou03Event(int x)
{
    volatile int local = x;
}

void actSt04rMonyou04Event(int x)
{
    volatile int local = x;
}

void actSt04rMonyou05Event(int x)
{
    volatile int local = x;
}

void actSt04rMonyou06Event(int x)
{
    volatile int local = x;
}

void actSt04rMonyou07Event(int x)
{
    volatile int local = x;
}

void actSt04rBarricadeEvent(int x)
{
    volatile int local = x;
}

extern ActMail D_004F9600[];

void actSt04rGondolaCharaChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttr(D_00639EA4, 0xA000000) != 0 &&
           (gflagChk(0x11E) == 0 || scpTriggerFloorAttr(D_00639EA8, 0xA000000) == 0)) {
        _ACTWait(1);
    }

    D_004F9600[0].func = actSt04rGondolaChk;
    sub->mail = D_004F9600;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt04rTorch1_1Chk(volatile int a0)
{
    while (scpIsTorchLightOn(0x57C) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x10A);
    stage_SetAnimation(0xD2, 1, 0);
}

void actSt04rTorch1_2Chk(volatile int a0)
{
    while (scpIsTorchLightOn(0x57D) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x10B);
    stage_SetAnimation(0xD3, 1, 0);
}

void actSt04rTorch2_1Chk(volatile int a0)
{
    while (scpIsTorchLightOn(0x5CF) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x10C);
}

void actSt04rTorch2_2Chk(volatile int a0)
{
    while (scpIsTorchLightOn(0x5D0) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x10D);
}

void actSt04rTorch3_1Chk(volatile int a0)
{
    while (scpIsTorchLightOn(0x5D1) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x110);
}

void actSt04rTorch3_2Chk(volatile int a0)
{
    while (scpIsTorchLightOn(0x5D2) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x111);
}

void actSt04rTorch2_1XLChk(volatile int a0)
{
    while (scpIsTorchLightOn(0x580) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x10E);
    stage_SetAnimation(0xD4, 1, 0);
}

void actSt04rTorch2_2XLChk(volatile int a0)
{
    while (scpIsTorchLightOn(0x581) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x10F);
    stage_SetAnimation(0xD5, 1, 0);
}
