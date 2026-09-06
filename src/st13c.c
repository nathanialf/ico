#include "common.h"

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;
typedef struct JimakuSub {
    char unk00[0x2C];           /* 0x0C */
    int  unk2C;                 /* 0x38 */
    int  n;                     /* 0x3C */
    int  unk34;                 /* 0x40 */
    int  unk38;                 /* 0x44 */
    void *unk3C;                /* 0x48 */
    void *unk40;                /* 0x4C */
} JimakuSub;
typedef struct JimakuArg {
    int  cmd;                   /* 0x00 */
    int  unk04;                 /* 0x04 */
    int  done;                  /* 0x08 */
    JimakuSub sub;              /* 0x0C */
} JimakuArg;
typedef struct EffectArg {
    long long lo;               /* 0x00 */
    long long hi;               /* 0x08 */
} EffectArg;
typedef struct AnimSet {
    int anim[5];                /* 0x00 */
} AnimSet;
typedef struct AnimSet16 {
    int anim[16];               /* 0x00 */
} AnimSet16;
typedef struct AdpcmSlot {
    char pad00[0x2C];           /* 0x00 */
    int unk2C;                  /* 0x2C */
} AdpcmSlot;
typedef struct MotObj {
    char pad00[0x514];          /* 0x000 */
    int unk514;                 /* 0x514 */
} MotObj;
typedef struct Act {
    char unk00[0x20];           /* 0x00 */
    long long flags20;          /* 0x20 */
    char unk28[0xC];            /* 0x28 */
    int unk34;                  /* 0x34 */
    char unk38[0x68];           /* 0x38 */
    long long flags;            /* 0xA0 */
    char unkA8[0x28];           /* 0xA8 */
    ActMail *mainMail;          /* 0xD0 */
    ActMail *mail;              /* 0xD4 */
    char unkD8[0x20C];          /* 0xD8 */
    int unk2E4;                 /* 0x2E4 */
} Act;
typedef struct PObjGObj {
    char pad00[0x15C];          /* 0x000 */
    int unk15C;                 /* 0x15C */
    int unk160;                 /* 0x160 */
    int act;                    /* 0x164 (Act * handle) */
    int unk168;                 /* 0x168 */
    int unk16C;                 /* 0x16C */
} PObjGObj;

extern void _ACTWait(int a0);
extern void SetWayGroupActive(int a0, int a1);
extern void debug_StdPrintfDummy(char *fmt);
extern void gflagOn(int a0);
extern void CameraSetCameraSet(int a0);
extern void Generator_Call(int a0);
extern int scpSearchGobj(int a0);
extern void scpSleepEnemyAll(void);
extern void scpPlayWaitMotEnd(int a0);
extern void scpPlayStart(int a0);
extern void scpPlayMot(int a0, int mot);
extern int ForMotionViewer_GetCurrentMotion(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern Act *actInitialize(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int gflagChk(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void gflagOff(int a0);
extern int actCreateSubThread(void *entry, int prio);
extern int scpTriggerFloorAttr(int a0, int a1);
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
extern int stage_ContinueAnimation(int a0, int a1);
extern int stage_CheckAnimationFinish(int a0);
extern int scpTriggerBall(int a0, int gobj, float r);
extern void *test_CURRENTROOT(int a0);
extern void sceVu0SubVector(void *out, void *a, void *b);
extern void scpPlayMotDir(int a0, void *dir);
extern void scpPlayMotReq(int a0, int mot);
extern void scpPlayPosSet(int a0, float x, float y, float z);
extern void ScpCallCameraOff(void);
extern void jimakuBegin(int a0);
extern void iosThreadSetPri(int *a0, int a1);
extern int scpAdpcmPlayRequestNum(void);
extern void scpFadeOut(float t, int a1, int a2, int a3);
extern void scpFadeIn(float f);
extern int scpFadeChk(void);
extern int lt_fade_status(void);
extern void scpPlayEnd(int a0);
extern void memset(void *a0, int a1, int a2);
extern void ScpCallCameraOn(void);
extern void scpAdpcmFadeCloseFunc(int *a0, int a1);
extern void jimakuUndisp(int a0);
extern void scpEffectStart(void *a0, int a1);
extern void scpKillEnemyAll(void);
extern void SetHandCameraLimitInDemo(int a0, int a1);
extern void ResetHandCameraLimitInDemo(void);
extern void scpTorchLightOn(int a0);
extern void fightSoundProcessRequestStart(void);
extern void fightSoundProcessRequestPause(void);
extern int fightSoundPlayChk(void);
extern int scpActStatusDeathFall(int a0);
extern int actEnemyFlagCheckDead(int a0);
extern void gsb_SetZoom(float a0, float a1);
extern void scpLockMaxRotate(int a0, float a1);
extern void scpUnLockMaxRotate(int a0);
extern void _SCPMoveByWay_ToChar(int a0, int a1, int a2, int a3, float f0, float f1);
extern void ACTGame_ConnectHand(void);
extern void iosOmSendMail(int a0, int a1, int a2);
extern void scpWakeupEnemyAll(void);
extern void CheckPoint(void);
extern void AdpcmPlay(int a0);
extern void Generator_QuickCall(int a0);
extern int isEnemyActive(int a0);
extern void DirectCallEnemy(int a0, int a1, void *a2, void *a3, int a4);
extern void SetCameraFlag_LwsCutBack(void);
extern void scpTorchLightOff(int a0);
extern void ACTEnemyForceSwitchToCarry(int a0);
extern void scpMaskGeneratorAll(void);
extern void scpSekizouCheckPoint(void);
extern int iosPadActRequest(int port, int id);
extern int *iosPadActVolumeSet(int key, unsigned int val);
extern void iosPadActStop(int key);
extern void jimakuJump(int a0);
extern void SetWeaponTorchChainReactionFlagAll(int a0);
extern void lt_switch_layout(int a0);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);
extern void soundSeDefStop(int handle);

extern void actSt13cBukiChk(volatile int a0);
extern void actSt13cSleepChk(volatile int a0);
extern void actSt13cBmg1Chk(volatile int a0);
extern void actSt13cCageFallChk(volatile int a0);
extern void actSt13cCage1stDownDemoCancel(volatile int a0);
extern void actSt13cCage1stDownDemo(volatile int a0);
extern void actSt13cConte04(volatile int a0);
extern void actSt13cConte04Jimaku(volatile int a0);
extern void actSt13cHandJimaku(volatile int a0);
extern void actSt13cHandSub(volatile int a0);
extern void actSt13cConte05(volatile int a0);
extern void actSt13cConte05Jimaku(volatile int a0);
extern void actSt13cCageFallEffect(volatile int a0);
extern void actSt13cGirlCarryAgainChk(volatile int a0);
extern void actSt13cCage1stDown(volatile int a0);
extern void actSt13cSekizoJimakuChk(volatile int a0);
extern void actSt13cSekizoJimakuEff(volatile int a0);
extern void actSt13cHandChk(volatile int a0);
extern void actSt13cGirlCarryChk(volatile int a0);
extern void actSt13cCageFallReadyChk(volatile int a0);
extern void actSt13cRescueChk(volatile int a0);
extern void actSt13cSekizoChk(volatile int a0);
extern void actSt13cCageDownMain(volatile int a0);

extern int D_00639EA4;
extern int D_0063C590;

extern char D_00622E10[];
/* st13c.o's own .rodata: the sleeping-girl wake-up offset vector. */
extern AnimSet D_00622E20;
extern AnimSet16 D_00622E50;
extern const EffectArg D_00622E90;
extern const EffectArg D_00622EA0;
extern const EffectArg D_00622EB0;
extern const EffectArg D_00622EC0;
extern const EffectArg D_00622ED0;
extern const EffectArg D_00622EE0;
extern const EffectArg D_00622EF0;
extern const EffectArg D_00622F00;
extern const EffectArg D_00622F10;
extern const long long D_00622E40[];
extern int D_0028F4C0[];
extern int D_0028F8F4[];
extern JimakuArg jimaku_msg;
extern int jimakuOn;

/* st13c.o's own .data run (no MAIN.MAP symbols): actor mail packets. */
extern ActMail D_004FAD50[];
extern ActMail D_004FAD10[];
extern ActMail D_004FAD30[];
extern ActMail D_004FAD70[];
extern ActMail D_004FADB0[];
extern ActMail D_004FADD0[];
extern ActMail D_004FADF0[];
extern ActMail D_004FAD90[];
extern ActMail D_004FAE10[];
extern ActMail D_004FAE30[];
extern ActMail D_004FAE50[];
extern ActMail D_004FAE70[];
extern ActMail D_004FAE90[];
extern ActMail D_004FAEB0[];
extern ActMail D_004FAED0[];
extern ActMail D_004FAEF0[];
extern int D_0063AA08;
extern int bmg;
extern int hand;
extern int D_00639EAC;
extern unsigned char D_0063C014;
extern int D_0063C010;
extern int D_0063C000;
extern int D_0063C004;
extern int D_0063C00C;
extern int D_0063C594;
extern int D_00639EA8;

void actSt13cInit(void) {
    if (gflagChk(0x15)) {
        SetWayGroupActive(9, 0);
    }
}
void actSt13cEnd(void) {
    if (gflagChk(0x1F) == 0) {
        debug_StdPrintfDummy(D_00622E10);
        gflagOn(0x186);
    }
}
void actSt13cBmg1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (D_00639EA8 == 0) {
        return;
    }
    if (gflagChk(0x15) != 0) {
        return;
    }

    ((Act *)((PObjGObj *)D_00639EA4)->act)->flags |= 0x100000;

    if (gflagChk(0x14) != 0) {
        scpPlayPosSet(D_00639EA8, -30.0f, -436.0f, -1.0f);
        _ACTWait(0x3C);
        scpPlayStart(D_00639EA8);
    } else if (gflagChk(0x12) == 0) {
        ScpCallCameraOff();
        scpPlayPosSet(D_00639EA8, -7.0f, -5725.0f, 18.0f);

        D_004FAD10[0].func = actSt13cBmg1Chk;
        self->mail = D_004FAD10;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        scpPlayPosSet(D_00639EA8, -7.0f, -5725.0f, 18.0f);
    }
}
void actSt13cBmg1Chk(volatile int a0)
{
    AnimSet w;
    int th1;
    int th2;
    unsigned int i;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0) {
        _ACTWait(1);
    }

    ScpCallCameraOn();
    lt_switch_layout(0x37);
    gflagOn(0x12);

    scpAdpcmPlayRequestFunc(0xD, &bmg, 1, 1, 1);

    while (bmg == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;
    _ACTWait(1);

    th1 = actCreateSubThread(actSt13cConte04, 0x15);
    th2 = actCreateSubThread(actSt13cConte04Jimaku, 0x15);

    D_0063C590 = 0;

    while (D_0063C590 == 0 &&
           ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    if (D_0063C590 == 0) {
        scpAdpcmFadeCloseFunc(&bmg, 0x100);

        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        iosThreadSetPri((int *)(th1 + 0x24), 0x22);
        iosThreadSetPri((int *)(th2 + 0x24), 0x22);

        w = D_00622E20;
        for (i = 0; i < 5; i++) {
            stage_SetAnimation(w.anim[i], 1, -1);
            _ACTWait(1);
        }

        jimakuUndisp((int)&jimaku_msg);

        stage_SetAnimation(0x275, 1, -1);
        scpFadeIn(3.0f);
    } else {
        iosThreadSetPri((int *)(th1 + 0x24), 0x22);
        iosThreadSetPri((int *)(th2 + 0x24), 0x22);
    }

    scpPlayMot(D_00639EA4, 0);

    sceVu0SubVector(&w, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, &w);
    scpPlayEnd(D_00639EA4);

    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}
void actSt13cConte04(volatile int a0)
{
    scpPlayStart(D_00639EA4);

    stage_SetAnimation(0x271, 1, 0);

    scpPlayMot(D_00639EA4, 0x134);
    while (stage_ContinueAnimation(0x271, 0x272) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x135);
    while (stage_ContinueAnimation(0x272, 0x273) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x136);
    while (stage_ContinueAnimation(0x273, 0x274) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x137);
    while (stage_ContinueAnimation(0x274, 0x275) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x138);
    while (stage_CheckAnimationFinish(0x275) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C590 = 1;
    _ACTWait(0);
}
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cConte04Jimaku);
void actSt13cCage1stDownDemoCancel(volatile int a0)
{
    float ofs[4];
    float dir[4];
    int *th;

    D_0063C590 = 0;

    th = (int *)(actCreateSubThread(actSt13cCage1stDownDemo, 0x15) + 0x24);

    while (D_0063C590 == 0 &&
           ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th, 0x22);

    if (D_0063C590 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
    }

    scpPlayMot(D_00639EA4, 0x13A);
    scpPlayWaitMotEnd(D_00639EA4);

    if (D_0063C590 == 0) {
        scpFadeIn(3.0f);
    }

    while (stage_CheckAnimationFrame(0x49, 0, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(D_00639EA4, 0);

    memset(ofs, 0, 0x10);
    ofs[3] = 1.0f;
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);
    scpPlayEnd(D_00639EA4);

    CameraSetCameraSet(0x25);
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}
void actSt13cCage1stDown(volatile int a0)
{
    int se;

    lt_switch_layout(0x37);
    gflagOn(0x14);

    scpAdpcmPlayRequestFunc(0xE, &D_0063C000, 1, 1, 1);

    while (D_0063C000 == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x48, 1, 0);
    stage_SetAnimation(0x49, 1, 0);

    actCreateSubThread(actSt13cCage1stDownDemoCancel, 0x15);

    scpPlayStart(D_00639EA8);

    while (stage_CheckAnimationFrame(0x48, 0xF, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMotReq(D_00639EA8, 0x11E);

    while (stage_CheckAnimationFrame(0x48, 0x2D, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    se = soundSeDefPlay(0x54B, 0, 0, 1);

    while (stage_CheckAnimationFinish(0x48) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefStop(se);

    while (stage_CheckAnimationFinish(0x48) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}
void actSt13cCageFall(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x14) == 0) {
        stage_SetAnimation(0x48, -1, -2);

        ((PObjGObj *)scpSearchGobj(0x80))->unk16C = 0;
        SetWeaponTorchChainReactionFlagAll(1);

        D_004FADD0[0].func = actSt13cCageFallChk;
        self->mail = D_004FADD0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        if (gflagChk(0x16) == 0) {
            ((PObjGObj *)scpSearchGobj(0x80))->unk16C = 0;
            SetWeaponTorchChainReactionFlagAll(1);

            stage_SetAnimation(0x48, 0, -1);
            stage_SetAnimation(0x4C, 0, 0);

            D_004FADF0[0].func = actSt13cCageFallChk;
            self->mail = D_004FADF0;
            ACTSendMailCorrect(a0, 0x1AE);
            _ACTWait(0);
        }

        ((PObjGObj *)scpSearchGobj(0x90))->unk16C = 0;

        stage_SetAnimation(0x4C, 0, -1);
        stage_SetAnimation(0x4A, 0, -1);
        stage_SetAnimation(0x4B, 0, -1);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cCageFallChk);
void actSt13cConte05(volatile int a0)
{
    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);

    stage_SetAnimation(0x276, 1, 0);

    scpPlayMot(D_00639EA4, 0x13B);
    scpPlayMot(D_00639EA8, 0x2D6);

    while (stage_ContinueAnimation(0x276, 0x277) == 0) {
        _ACTWait(1);
    }

    SetHandCameraLimitInDemo(0, 0);
    scpPlayMot(D_00639EA8, 0x2D6);

    while (stage_ContinueAnimation(0x277, 0x278) == 0) {
        _ACTWait(1);
    }

    ResetHandCameraLimitInDemo();
    scpPlayMot(D_00639EA8, 0x2D6);

    while (stage_ContinueAnimation(0x278, 0x279) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA8, 0x2D7);

    while (stage_ContinueAnimation(0x279, 0x27A) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x13C);

    while (stage_ContinueAnimation(0x27A, 0x27B) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x13D);

    while (stage_ContinueAnimation(0x27B, 0x27C) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA8, 0x2D8);
    _ACTWait(1);

    ((PObjGObj *)scpSearchGobj(0x80))->unk16C = 1;
    ((PObjGObj *)scpSearchGobj(0x81))->unk16C = 0;
    ((PObjGObj *)scpSearchGobj(0x82))->unk16C = 0;
    ((PObjGObj *)scpSearchGobj(0x36))->unk16C = 0;

    scpTorchLightOn(0x90);

    while (stage_ContinueAnimation(0x27C, 0x27D) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA8, 0x2D9);

    while (stage_ContinueAnimation(0x27D, 0x27E) == 0) {
        _ACTWait(1);
    }

    SetHandCameraLimitInDemo(5, 5);

    ((PObjGObj *)scpSearchGobj(0x36))->unk16C = 1;

    scpPlayMot(D_00639EA4, 0x13E);
    scpPlayMot(D_00639EA8, 0x2DA);

    while (stage_ContinueAnimation(0x27E, 0x27F) == 0) {
        _ACTWait(1);
    }

    ResetHandCameraLimitInDemo();

    scpPlayMot(D_00639EA4, 0x13F);
    scpPlayMot(D_00639EA8, 0x2DB);

    ((PObjGObj *)scpSearchGobj(0x81))->unk16C = 1;
    ((PObjGObj *)scpSearchGobj(0x82))->unk16C = 1;

    _ACTWait(0x12C);
    gflagOn(0x17);

    while (stage_ContinueAnimation(0x27F, 0x280) == 0) {
        _ACTWait(1);
    }

    scpPlayStart(scpSearchGobj(0x96));
    scpPlayMot(scpSearchGobj(0x96), 0x3C4);

    while (stage_ContinueAnimation(0x280, 0x281) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x140);
    scpPlayMot(D_00639EA8, 0x2DC);
    scpPlayMot(scpSearchGobj(0x96), 0x3C4);

    while (stage_ContinueAnimation(0x281, 0x282) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x141);
    scpPlayMot(D_00639EA8, 0x2DD);
    scpPlayMot(scpSearchGobj(0x96), 0x3C5);

    while (stage_ContinueAnimation(0x282, 0x283) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x142);
    scpPlayMot(D_00639EA8, 0x2DE);
    scpPlayMot(scpSearchGobj(0x96), 0x3C6);

    while (stage_ContinueAnimation(0x283, 0x284) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA8, 0x2DF);
    scpPlayMot(scpSearchGobj(0x96), 0x3C7);

    while (stage_ContinueAnimation(0x284, 0x285) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x143);

    while (stage_ContinueAnimation(0x285, 0x286) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA8, 0x2E0);
    scpPlayMot(scpSearchGobj(0x96), 0x3C8);

    fightSoundProcessRequestStart();

    D_0063C590 = 1;
    _ACTWait(0);
}
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cConte05Jimaku);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cCageFallEffect);
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cSekizoChk);
void actSt13cGirlCarryChk(volatile int a0)
{
    Act *self = (Act *)((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (gflagChk(0x19) == 0 ||
           ((Act *)((PObjGObj *)D_00639EA8)->act)->unk34 == 0x6F ||
           ((Act *)((PObjGObj *)D_00639EA8)->act)->unk34 == 0x6E ||
           gflagChk(0x1D) != 0) {
        _ACTWait(1);
    }

    _ACTWait(0xF);

    scpPlayStart(D_00639EA8);
    scpPlayMot(D_00639EA8, 0x253);
    scpPlayWaitMotEnd(D_00639EA8);
    scpPlayMot(D_00639EA8, 0x254);

    ((MotObj *)((PObjGObj *)D_00639EA8)->unk15C)->unk514 =
        (int)((float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 60.0f * 30.0f);

    gflagOn(0x1A);

    D_004FAE70[0].func = actSt13cGirlCarryAgainChk;
    self->mail = D_004FAE70;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);

    _ACTWait(1);
}
void actSt13cHandChk(volatile int a0)
{
    float dir[4];
    int th1;
    int th2;
    int t;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (1) {
        if (scpActStatusDeathFall(D_00639EA4) == 0 &&
            actEnemyFlagCheckDead(scpSearchGobj(0x96)) != 0 &&
            scpTriggerFloorAttr(D_00639EA4, 0x1000000) == 0 &&
            scpTriggerFloorAttr(D_00639EA4, 0x3000000) != 0 &&
            gflagChk(0x1A) != 0 &&
            scpTriggerBall(D_00639EA8, D_00639EA4, 550.0f) != 0 &&
            (((Act *)((PObjGObj *)D_00639EA4)->act)->unk2E4 & 8) != 0 &&
            ((Act *)((PObjGObj *)D_00639EA8)->act)->unk34 != 0x6E) {
            break;
        }
        if (gflagChk(0x1E) != 0) {
            break;
        }
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    ((Act *)((PObjGObj *)scpSearchGobj(0x96))->act)->flags20 &= ~0x20000;

    fightSoundProcessRequestPause();

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    gsb_SetZoom(2.0f, 1000.0f);
    gflagOn(0x1B);
    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);
    sceVu0SubVector(dir, test_CURRENTROOT(D_00639EA4), test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, dir);

    scpLockMaxRotate(D_00639EA4, 6.0f);
    _SCPMoveByWay_ToChar(D_00639EA4, D_00639EA8, 0, 6, 50.0f, 30.0f);
    scpUnLockMaxRotate(D_00639EA4);

    sceVu0SubVector(dir, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);
    sceVu0SubVector(dir, test_CURRENTROOT(D_00639EA4), test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, dir);

    scpAdpcmPlayRequestFunc(0x10, &D_0063C00C, 1, 1, 1);
    while (D_0063C00C == 0) {
        _ACTWait(1);
    }

    ACTGame_ConnectHand();

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);
    scpPlayMot(D_00639EA4, 0x105);
    scpPlayMot(D_00639EA8, 0x2D1);

    th1 = actCreateSubThread(actSt13cHandJimaku, 0x15);
    th2 = actCreateSubThread(actSt13cHandSub, 0x15);

    D_0063C590 = 0;

    while (D_0063C590 == 0 &&
           ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri((int *)(th2 + 0x24), 0x22);
    iosThreadSetPri((int *)(th1 + 0x24), 0x22);

    if (D_0063C590 == 0) {
        scpAdpcmFadeCloseFunc(&D_0063C00C, 0x200);

        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        jimakuUndisp((int)&jimaku_msg);
        scpFadeIn(3.0f);
    }

    scpPlayMot(D_00639EA4, 0);
    scpPlayMot(D_00639EA8, 0x214);

    gsb_SetZoom(1.0f, 1000.0f);
    lt_switch_layout(0x36);

    t = (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1];
    _ACTWait(t * 3);

    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);

    ((MotObj *)((PObjGObj *)D_00639EA4)->unk15C)->unk514 =
        (int)((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f * 30.0f);

    _ACTWait(1);

    iosOmSendMail(D_00639EA8, 0x3F, D_00639EA4);

    D_0063AA08 = 0;
    scpWakeupEnemyAll();
    fightSoundProcessRequestStart();
    gflagOn(0x1C);
}
INCLUDE_ASM("asm/nonmatchings/src/st13c", actSt13cHandJimaku);
void actSt13cSleep(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x13) == 0) {
        D_004FAD30[0].func = actSt13cSleepChk;
        self->mail = D_004FAD30;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt13cCageDown(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x14) == 0) {
        stage_SetAnimation(0x48, 0, 0);
        stage_SetAnimation(0x4C, 0, 0);

        D_004FAD70[0].func = actSt13cCageDownMain;
        self->mail = D_004FAD70;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }

    if (gflagChk(0x14) != 0) {
        CameraSetCameraSet(0x25);
    }
}
void actSt13cCageFallReady(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x16) == 0) {
        D_004FADB0[0].func = actSt13cCageFallReadyChk;
        self->mail = D_004FADB0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt13cEnemy(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    D_0063C594 = a0;
    Generator_Mask(a0);

    while (gflagChk(0x17) == 0) {
        _ACTWait(1);
    }

    Generator_Call(scpSearchGobj(0x98));
    _ACTWait(0xB4);

    Generator_Call(a0);
    scpSleepEnemyAll();
    gflagOff(0x17);
}
void actSt13cEnemyNull(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x19) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(a0);
}
void actSt13cSekizo(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x1F) == 0) {
        stage_SetAnimation(0x4D, 0, 0);
        SetWayGroupActive(2, 0);

        D_004FAE30[0].func = actSt13cSekizoChk;
        self->mail = D_004FAE30;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x4D, 0, -1);
        SetWayGroupActive(2, 1);
    }
}
void actSt13cSekizoJimaku(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x1F) == 0) {
        D_004FAE10[0].func = actSt13cSekizoJimakuChk;
        self->mail = D_004FAE10;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt13cHand(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x1B) == 0) {
        D_004FAEB0[0].func = actSt13cHandChk;
        self->mail = D_004FAEB0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt13cGirlCarry(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x1B) == 0) {
        D_004FAE50[0].func = actSt13cGirlCarryChk;
        self->mail = D_004FAE50;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt13cRescue(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x1E) == 0 && gflagChk(0x1B) == 0) {
        D_004FAED0[0].func = actSt13cRescueChk;
        self->mail = D_004FAED0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt13cBuki(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    D_004FAEF0[0].func = actSt13cBukiChk;
    self->mail = D_004FAEF0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
INCLUDE_ASM("asm/nonmatchings/src/st13c", actE3St13cSekizo);
void actSt13cBmg1Event(int x) {
    volatile int local = x;
}
void actSt13cSleepEvent(int x) {
    volatile int local = x;
}
void actSt13cSleepChk(volatile int a0)
{
    long long ofs[2];
    float dir[4];

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(a0, D_00639EA8, 200.0f) == 0) {
        _ACTWait(1);
    }

    scpPlayStart(D_00639EA8);
    _ACTWait(1);

    ofs[0] = D_00622E40[0];
    ofs[1] = D_00622E40[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, dir);

    scpPlayMotReq(D_00639EA8, 0x11D);
}
void actSt13cCageDownMain(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    sub->mainMail = D_004FAD50;
    while (1) {
        _ACTWait(1);
    }
}
void actSt13cCageDownSwitch(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    D_0063AA08 = 1;

    if (gflagChk(0x14) == 0) {
        D_004FAD90[0].func = actSt13cCage1stDown;
        sub->mail = D_004FAD90;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt13cCage1stDownDemo(volatile int a0)
{
    scpPlayStart(D_00639EA4);
    scpPlayMot(D_00639EA4, 0x139);
    scpPlayWaitMotEnd(D_00639EA4);
    _ACTWait(0xF0);
    D_0063C590 = 1;
    _ACTWait(0);
}
void actSt13cCageFallReadyChk(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    while (scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0 || gflagChk(0x14) == 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(0xF, &D_0063C004, 1, 1, 0);
}
void actSt13cCageFallEvent(int x) {
    volatile int local = x;
}
void actE3St13cSekizoEvent(int x) {
    volatile int local = x;
}
void actSt13cSekizoJimakuChk(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    while (gflagChk(0x1F) == 0) {
        _ACTWait(1);
    }

    gflagOff(0x186);
    actCreateSubThread(actSt13cSekizoJimakuEff, 0x15);
}
void actSt13cSekizoJimakuEff(volatile int a0)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 1:
            jimakuBegin((int)&jimaku_msg);
            break;
        case 0x2D:
            jimaku_msg.sub.unk2C = 0x13;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        }

        n = (int)t;
        tn = t + (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 500.0f);
}
void actSt13cGirlCarryAgainChk(volatile int a0)
{
    Act *self = (Act *)((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (((Act *)((PObjGObj *)D_00639EA8)->act)->unk34 != 0x6F) {
        _ACTWait(1);
    }

    gflagOff(0x1A);

    D_004FAE90[0].func = actSt13cGirlCarryChk;
    self->mail = D_004FAE90;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);

    _ACTWait(1);
}
void actSt13cHandSub(volatile int a0)
{
    _ACTWait(100);
    scpPlayWaitMotEnd(D_00639EA4);
    D_0063C590 = 1;
    _ACTWait(0);
}
void actSt13cRescueChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (((Act *)((PObjGObj *)D_00639EA8)->act)->unk34 != 0x6E) {
        _ACTWait(1);
    }

    gflagOn(0x1D);
    D_0063AA08 = 1;
    _ACTWait(0xC8);

    scpPlayStart(D_00639EA8);
    scpPlayMot(D_00639EA8, 0x254);
    _ACTWait(0x78);

    gflagOn(0x1E);
}
void actSt13cBukiEvent(int x) {
    volatile int local = x;
}
void actSt13cBukiChk(volatile int a0)
{
    while (ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0xE7) {
        _ACTWait(1);
    }
    stage_SetAnimation(0x4C, -1, -2);
}
