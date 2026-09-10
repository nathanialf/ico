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
extern int D_0063AA08;
extern int D_00639EAC;
extern int D_0063BFF4;
extern unsigned char D_0063BFF8;
extern int D_0063C57C;
extern int iosPadActRequest(int port, int id);
extern int *iosPadActVolumeSet(int key, unsigned int val);
extern void iosPadActStop(int key);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);
extern int D_0063C58C;
extern float D_004FAC80[];
extern int D_00639EA4;
extern int scpTriggerFloorAttr(int a0, int a1);
extern int scpTriggerBall(int a0, int gobj, float r);
extern void actSt13bElev2Chk(volatile int a0);
extern ActMail D_004FACF0[];
extern ActMail D_004FAB00[];
extern Act *actInitialize(int a0);
extern int gflagChk(int a0);
extern void actSt13bSekizoChk(volatile int a0);
extern void actSt13bSekizo2Chk(volatile int a0);
extern ActMail D_004FAB20[];
extern ActMail D_004FAB80[];
extern void actSt13bBossAfterChk(volatile int a0);
extern int D_00639ED4;
extern PObjGObj *scpSearchGobj(int a0);
extern void scpPlayMot(void *a0, int mot);

typedef struct JimakuSub {
    char unk00[0x2C]; /* 0x0C */
    int unk2C;        /* 0x38 */
    int n;            /* 0x3C */
    int unk34;        /* 0x40 */
    int unk38;        /* 0x44 */
    void *unk3C;      /* 0x48 */
    void *unk40;      /* 0x4C */
} JimakuSub;

typedef struct JimakuArg {
    int cmd;       /* 0x00 */
    int unk04;     /* 0x04 */
    int done;      /* 0x08 */
    JimakuSub sub; /* 0x0C */
} JimakuArg;

extern JimakuArg jimaku_msg;
extern int jimakuOn;
extern void jimakuBegin(int a0);
extern void jimakuJump(int a0);
extern int D_0028F4C0[];
extern void SetCameraFlag_LwsCutBack(void);
extern ActMail D_004FABC0[];
extern ActMail D_004FAC90[];
extern ActMail D_004FACB0[];
extern void actSt13bElevMain(volatile int a0);
extern void actSt13bElevDown(volatile int a0);
extern void actSt13bDoorUp(volatile int a0);
/* st13b.o's own .data run (no MAIN.MAP symbols): actor mail packets. */
extern ActMail D_004FABA0[];
extern ActMail D_004FABE0[];
extern ActMail D_004FAC20[];
extern ActMail D_004FAC60[];
extern ActMail D_004FAC40[];
extern void actSt13bDoorMain(volatile int a0);
extern void gflagOn(int a0);
extern void lt_switch_layout(int a0);
extern void scpFadeOut(float f, int a1, int a2, int a3);
extern int actCreateSubThread(void *entry, int prio);
extern int scpAdpcmPlayRequestNum(void);
extern void scpAdpcmFadeCloseFunc(int *h, short a1);
extern void scpAdpcmPlayRequestFunc(int a0, int *h, int a2, int a3, int a4);
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern void ScpCallCameraSetTarget(float x, float y, float z);
extern void fightSoundProcessRequestPause(void);
extern int fightSoundPlayChk(void);
extern void actSt13bConte02(volatile int a0);
extern void actSt13bConte02Jimaku(volatile int a0);
extern void actSt13bElevUpChk(volatile int a0);
extern void actSt13bBossChk(volatile int a0);
extern ActMail D_004FAC00[];
extern ActMail D_004FAB60[];
extern int D_0063C580;
extern int D_0063BFC0;
extern int boss;
extern float D_0063AA0C;

typedef struct PadState {
    int unk00; /* 0x00 */
    int flags; /* 0x04 */
} PadState;

extern PadState D_0028F8F0[];
extern int D_0028F8F4[];
extern int stage_ContinueAnimation(int a0, int a1);
extern void iosThreadSetPri(int th, int pri);
extern int scpFadeChk(void);
extern void scpFadeIn(float f);
extern int lt_fade_status(void);
extern void actSt13bDoorUpSub(volatile int a0);
extern void actSt13bMeetAgainChk(volatile int a0);
extern ActMail D_004FAB40[];
extern ActMail D_004FAAE0[];
extern void actSt13bFloorChk(volatile int a0);
extern void actSt13bElevDownSub(volatile int a0);
extern void preload(int a0);
extern int st13b_down;
extern int st13b_up;
extern int sd;
extern void gflagOff(int a0);
extern void AdpcmPlay(int a0);
extern void CapsuleGhostBossStart(void);
extern void scpPlayPosSet(void *a0, float x, float y, float z);
extern void actSt13bElevUpSub(volatile int a0);
extern void actConte10c(volatile int a0);
extern int InqCapsuleGhostBossEnd(void);
extern int scpAdpcmCloseChkFunc(int *h);
extern void scpPlayEnd(int a0);
extern void scpPlayStart(int a0);
extern void scpPlayWaitMotEnd(int a0);
extern void scpPlayMotDir(int a0, float *dir);
extern void scpSekizouCheckPoint(void);
extern void *test_CURRENTROOT(int a0);
extern void sceVu0SubVector(float *d, void *a, void *b);
extern int scpGameStat_BoyWeaponkind(void);
extern int ForMotionViewer_GetCurrentMotion(int a0);
extern int boss_dead;
extern int sekizo13b;
extern int sekizo13b2;
extern int meets_again;

typedef struct StgPre {
    unsigned char _0[0xA0];
    short ent[0x18];
    unsigned char _d0[0xC4];
} StgPre;

typedef struct ExitData {
    float pos[3];
    float rot[3];
    int f_18;
    int f_1C;
    int f_20;
    int f_24;
} ExitData;

extern StgPre D_005F5D50[];
extern const ExitData D_0055C518[];
extern int stage_no;
extern void stgmgrNextStagePreLoadForceStageSet(int val);
extern void stgmgrNextStagePreLoadForceNoCancel(int val);
extern int D_0063C584;
extern unsigned char D_0063C588;
extern int sekizo_13b;
extern int sekizo_13b_vol;
extern void actSt13bElev2CharaChk(volatile int a0);
extern ActMail D_004FACD0[];
extern void actSt13bMeetAgainSub(volatile int a0);
extern int st13b_yure;
extern unsigned char st13b_yure_vol;

void actSt13bFloor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(5) == 0) {
        scpFadeOut(255.0f, 0, 0, 0);
        lt_switch_layout(0x37);
        D_0063AA08 = 1;

        stage_SetAnimation(0x1E, 0, 0);
        stage_SetAnimation(0x1A, 0, 0);
        stage_SetAnimation(0x21, 0, 0);
        stage_SetAnimation(0x22, 0, 0);
        stage_SetAnimation(0x24, 0, 0);
        stage_SetAnimation(0x26, 0, 0);
        stage_SetAnimation(0x28, 0, 0xEB);
        stage_SetAnimation(0x2B, 0, 0);
        stage_SetAnimation(0x23, 0, 0);

        D_004FAAE0[0].func = actSt13bFloorChk;
        self->mail = D_004FAAE0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x20, 0, -1);
        stage_SetAnimation(0x1A, 0, -1);
        stage_SetAnimation(0x24, 0, 0);
        stage_SetAnimation(0x26, 0, 0);
    }
}

void actSt13bFloorChk(volatile int a0)
{
    int v = 0x20;

    gflagOn(5);
    actCreateSubThread(actSt13bConte02, 0x15);
    actCreateSubThread(actSt13bConte02Jimaku, 0x15);

    D_0063C580 = 0;
    D_0063BFC0 = 0;

    do {
        _ACTWait(1);
    } while (D_0063BFC0 == 0);

    while (D_0063C580 == 0 &&
           ((D_0028F8F0[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    if (D_0063C580 == 0) {
        v = 0x40;
    }

    if (D_0063BFC0 != 0) {
        scpAdpcmFadeCloseFunc(&D_0063BFC0, v);
    }

    RequestStageChange(4, D_00639EA4, 0, 0.025f, 2.0f);
}

void actSt13bConte02(volatile int a0)
{
    scpPlayStart(D_00639EA4);
    stgmgrNextStagePreLoadForceStageSet(0);
    scpAdpcmPlayRequestFunc(0xB, &D_0063BFC0, 0, 1, 0);

    while (D_0063BFC0 == 0) {
        _ACTWait(1);
    }

    scpFadeIn(8.0f);

    stgmgrNextStagePreLoadForceStageSet(D_0055C518[(&D_005F5D50[stage_no])->ent[3]].f_24);
    stgmgrNextStagePreLoadForceNoCancel(1);

    stage_SetAnimation(0x24A, 1, 0);
    scpPlayMot((void *)D_00639EA4, 0x11A);
    scpPlayMot(scpSearchGobj(0x963), 0x3E9);
    scpSearchGobj(0x963)->f16C = 1;
    scpPlayMot(scpSearchGobj(0x964), 0x3FF);
    scpSearchGobj(0x964)->f16C = 1;
    scpPlayMot(scpSearchGobj(0x965), 0x417);
    scpSearchGobj(0x965)->f16C = 1;
    _ACTWait(1);

    stage_SetAnimation(0x22, 1, 0);
    stage_SetAnimation(0x15, 1, 0);

    _ACTWait((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 0.15);

    if (D_0028F4C0[0] != 0) {
        _ACTWait((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 1.0);
    }

    AdpcmPlay(*(int *)(D_0063BFC0 + 0x2C));

    while (stage_ContinueAnimation(0x24A, 0x24B) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 0x11B);
    scpPlayMot(scpSearchGobj(0x963), 0x3EA);
    scpPlayMot(scpSearchGobj(0x964), 0x400);
    scpPlayMot(scpSearchGobj(0x965), 0x418);
    _ACTWait(1);

    stage_SetAnimation(0x1B, 1, 0);
    stage_SetAnimation(0x16, 1, 0);

    while (stage_ContinueAnimation(0x24B, 0x24C) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    stage_SetAnimation(0x1C, 1, 0);

    while (stage_ContinueAnimation(0x24C, 0x24D) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 0x11C);
    scpPlayMot(scpSearchGobj(0x963), 0x3EB);
    scpPlayMot(scpSearchGobj(0x964), 0x401);
    scpPlayMot(scpSearchGobj(0x965), 0x419);
    _ACTWait(1);

    stage_SetAnimation(0x1D, 1, 0);
    stage_SetAnimation(0x17, 1, 0);

    while (stage_ContinueAnimation(0x24D, 0x24E) == 0) {
        _ACTWait(1);
    }

    scpFadeIn(3.0f);

    scpPlayMot((void *)D_00639EA4, 0x11D);
    scpPlayMot(scpSearchGobj(0x964), 0x402);
    _ACTWait(1);

    stage_SetAnimation(0x1E, 1, 0);

    while (stage_ContinueAnimation(0x24E, 0x24F) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 0x11E);
    scpPlayMot(scpSearchGobj(0x963), 0x3EA);
    scpPlayMot(scpSearchGobj(0x964), 0x400);
    scpPlayMot(scpSearchGobj(0x965), 0x418);
    _ACTWait(1);

    stage_SetAnimation(0x1F, 1, 0);

    while (stage_ContinueAnimation(0x24F, 0x250) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(0x963), 0x3EC);
    scpPlayMot(scpSearchGobj(0x964), 0x403);
    scpPlayMot(scpSearchGobj(0x965), 0x41A);
    _ACTWait(1);

    stage_SetAnimation(0x18, 1, 0);

    while (stage_ContinueAnimation(0x250, 0x251) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 0x11F);
    scpSearchGobj(0x963)->f16C = 0;
    scpSearchGobj(0x964)->f16C = 0;
    scpSearchGobj(0x965)->f16C = 0;

    stage_SetAnimation(0x22, 0, 0);

    while (stage_CheckAnimationFrame(0x251, 0xC8, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpFadeOut(3.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(0x2D);
    }

    stage_SetAnimation(0x251, -1, -2);
    scpFadeIn(3.0f);
    stage_SetAnimation(0x252, 1, 0);

    while (stage_ContinueAnimation(0x252, 0x253) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 0x120);
    _ACTWait(1);

    stage_SetAnimation(0x1A, 1, 0);
    _ACTWait(0x3C);

    D_0063C584 = iosPadActRequest(D_00639EAC, 9);
    D_0063C588 = 0x80;
    iosPadActVolumeSet(D_0063C584, 0x80);

    while (stage_ContinueAnimation(0x253, 0x254) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(0x254, 0x255) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x19, 1, 0);

    while (stage_ContinueAnimation(0x255, 0x256) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 0x121);
    _ACTWait(0x82);

    stage_SetAnimation(0x20, 1, 0);

    while (stage_ContinueAnimation(0x256, 0x257) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(0x257, 0x258) == 0) {
        _ACTWait(1);
    }

    iosPadActStop(D_0063C584);
    scpPlayMot((void *)D_00639EA4, 0x122);

    while (stage_ContinueAnimation(0x258, 0x259) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 0x120);

    while (stage_ContinueAnimation(0x259, 0x25A) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 0x124);
    _ACTWait(1);

    stage_SetAnimation(0x20, 1, 0xD0);

    while (stage_ContinueAnimation(0x25A, 0x25B) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 0x125);
    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_ContinueAnimation(0x25B, 0x25C) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 0x126);

    _ACTWait(0x1E);
    iosPadActRequest(D_00639EAC, 0xF);
    _ACTWait(0x1E);
    iosPadActRequest(D_00639EAC, 0x11);
    _ACTWait(0xF);
    iosPadActRequest(D_00639EAC, 0x11);
    _ACTWait(5);
    iosPadActRequest(D_00639EAC, 0x10);
    _ACTWait(0xF);
    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_ContinueAnimation(0x25C, 0x25D) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 0x127);

    while (stage_ContinueAnimation(0x25D, 0x25E) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 0x128);

    while (stage_ContinueAnimation(0x25E, 0x25F) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 0x129);

    while (stage_CheckAnimationFrame(0x25F, 0x96, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    D_0063C580 = 1;
}

void actSt13bSekizoChk(volatile int a0)
{
    float dir[4];

    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0 || scpGameStat_BoyWeaponkind() != 5 ||
           ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0x4B) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpAdpcmPlayRequestFunc(0x13, &sekizo13b, 1, 1, 1);

    while (sekizo13b == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x21, 1, 0);

    st13b_yure = iosPadActRequest(D_00639EAC, 9);
    st13b_yure_vol = 0x80;
    iosPadActVolumeSet(st13b_yure, 0x80);

    scpPlayStart(D_00639EA4);
    scpPlayPosSet((void *)D_00639EA4, 3085.0f, -1338.0f, 0.0f);
    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(a0), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);
    scpSekizouCheckPoint();
    scpPlayMot((void *)D_00639EA4, 0xFB);
    scpPlayWaitMotEnd(D_00639EA4);
    scpPlayMot((void *)D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);
    gflagOn(0xA);

    while (stage_CheckAnimationFrame(0x21, 0x97, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(st13b_yure);

    while (stage_CheckAnimationFinish(0x21) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    lt_switch_layout(0x36);
    D_0063AA08 = 0;
}

void actSt13bSekizo2Chk(volatile int a0)
{
    float dir[4];

    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0 || scpGameStat_BoyWeaponkind() != 5 ||
           ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0x4B) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpAdpcmPlayRequestFunc(0x12, &sekizo13b2, 1, 1, 1);

    while (sekizo13b2 == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x22, 1, 0);

    st13b_yure = iosPadActRequest(D_00639EAC, 9);
    st13b_yure_vol = 0x80;
    iosPadActVolumeSet(st13b_yure, 0x80);

    scpPlayStart(D_00639EA4);
    scpPlayPosSet((void *)D_00639EA4, -1563.0f, 527.0f, 0.0f);
    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(a0), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);
    scpSekizouCheckPoint();
    scpPlayMot((void *)D_00639EA4, 0xFB);
    scpPlayWaitMotEnd(D_00639EA4);
    scpPlayMot((void *)D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);
    gflagOn(0xB);

    while (stage_CheckAnimationFrame(0x22, 0x97, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(st13b_yure);

    while (stage_CheckAnimationFinish(0x22) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    lt_switch_layout(0x36);
    D_0063AA08 = 0;
}

void actSt13bMeetAgain(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xC) == 0) {
        stage_SetAnimation(0x20, 0, -1);
        stage_SetAnimation(0x1A, 0, 0);
        stage_SetAnimation(0x23, 0, 0);
        stage_SetAnimation(0x24, 0, 0);
        stage_SetAnimation(0x26, 0, 0);

        D_004FAB40[0].func = actSt13bMeetAgainChk;
        self->mail = D_004FAB40;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x20, 0, -1);
        stage_SetAnimation(0x1A, 0, 0);
        stage_SetAnimation(0x23, 0, 0);
        stage_SetAnimation(0x24, 0, 0);
        stage_SetAnimation(0x26, 0, 0);
    }
}

void actSt13bMeetAgainSub(volatile int a0)
{
    stage_SetAnimation(0x2F8, 1, 0);

    scpPlayMot((void *)D_00639EA4, 2);
    scpPlayMot(scpSearchGobj(0x9A0), 0x3CB);
    scpPlayMot(scpSearchGobj(0x9A1), 0x3CC);
    scpPlayMot(scpSearchGobj(0x9A2), 0x3CD);
    scpPlayMot(scpSearchGobj(0x9A3), 0x3CE);
    scpPlayMot(scpSearchGobj(0x9A4), 0x3CF);
    scpPlayMot(scpSearchGobj(0x9A5), 0x3D0);

    while (stage_ContinueAnimation(0x2F8, 0x2F9) == 0) {
        _ACTWait(1);
    }

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(0x2F9) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    D_0063C57C = 1;
    _ACTWait(0);
}

void actSt13bMeetAgainChk(volatile int a0)
{
    int th;

    while (scpTriggerFloorAttr(D_00639EA4, 0x1000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpPlayStart(D_00639EA4);
    scpPlayMot((void *)D_00639EA4, 0);
    gflagOn(0xC);
    scpAdpcmPlayRequestFunc(0x23, &meets_again, 1, 1, 1);

    while (meets_again == 0) {
        _ACTWait(1);
    }

    th = actCreateSubThread(actSt13bMeetAgainSub, 0x15);
    D_0063C57C = 0;

    while (D_0063C57C == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 0x24, 0x22);

    if (D_0063C57C == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(0x2F8, 0, -1);
        scpFadeIn(3.0f);
    }

    scpPlayMot(scpSearchGobj(0x9A0), 0x3D1);
    scpPlayMot(scpSearchGobj(0x9A1), 0x3D2);
    scpPlayMot(scpSearchGobj(0x9A2), 0x3D3);
    scpPlayMot(scpSearchGobj(0x9A3), 0x3D4);
    scpPlayMot(scpSearchGobj(0x9A4), 0x3D5);
    scpPlayMot(scpSearchGobj(0x9A5), 0x3D6);

    scpPlayMot((void *)D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
    scpAdpcmFadeCloseFunc(&meets_again, 0x80);
}

void actSt13bBoss(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    ScpCallCameraSetTarget(-1886.0f, 625.0f, -4.0f);
    fightSoundProcessRequestPause();

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    if (gflagChk(0xD) == 0) {
        scpSearchGobj(0x9A6)->f16C = 0;
        D_004FAB60[0].func = actSt13bBossChk;
        self->mail = D_004FAB60;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else if (gflagChk(0xE) == 0) {
        scpAdpcmPlayRequestFunc(0x25, &boss, 1, 0, 1);
        D_0063AA0C = 0.5f;
    }
}

void actSt13bBossChk(volatile int a0)
{
    while (scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(0xD);
    scpAdpcmPlayRequestFunc(0x24, &sd, 1, 1, 1);

    while (sd == 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(0x25, &boss, 1, 0, 0);
    D_0063AA0C = 0.5f;

    scpSearchGobj(0x9A6)->f16C = 1;
    scpPlayPosSet(scpSearchGobj(0x9A6), 0.0f, -100.0f, 0.0f);

    scpPlayMot(scpSearchGobj(0x9A0), 0x342);
    scpPlayMot(scpSearchGobj(0x9A1), 0x342);
    scpPlayMot(scpSearchGobj(0x9A2), 0x342);
    scpPlayMot(scpSearchGobj(0x9A3), 0x342);
    scpPlayMot(scpSearchGobj(0x9A4), 0x342);
    scpPlayMot(scpSearchGobj(0x9A5), 0x342);

    CapsuleGhostBossStart();

    _ACTWait((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 6);

    while (boss == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(boss + 0x2C));
}

void actSt13bBossAfterChk(volatile int a0)
{
    int th;

    while (InqCapsuleGhostBossEnd() == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    gflagOn(0xE);
    scpAdpcmFadeCloseFunc(&boss, 0x80);

    while (scpAdpcmCloseChkFunc(&boss) != 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(0x26, &boss_dead, 1, 1, 1);

    while (boss_dead == 0) {
        _ACTWait(1);
    }

    th = actCreateSubThread(actConte10c, 0x15);
    D_0063C57C = 0;

    while (D_0063C57C == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 0x24, 0x22);

    if (D_0063C57C == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        scpAdpcmFadeCloseFunc(&boss_dead, 0x200);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(0x2FB, 0, -1);
        stage_SetAnimation(0x23, 0, -1);
        scpFadeIn(3.0f);
    }

    scpPlayMot((void *)D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}

void actSt13bElevDownSub(volatile int a0)
{
    stage_SetAnimation(0x28, 1, 0xEB);

    while (stage_CheckAnimationFrame(0x28, 0x141, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFrame(0x28, 0x15E, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0063BFF4 = iosPadActRequest(D_00639EAC, 9);
    D_0063BFF8 = 0x80;
    iosPadActVolumeSet(D_0063BFF4, 0x80);

    while (stage_CheckAnimationFrame(0x28, 0x1C2, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0063C57C = 1;
    _ACTWait(0);
}

void actSt13bElevDown(volatile int a0)
{
    int th;

    lt_switch_layout(0x37);
    gflagOn(0xF);
    scpAdpcmPlayRequestFunc(0x4F, &st13b_down, 0, 1, 1);

    while (st13b_down == 0) {
        _ACTWait(1);
    }

    preload(3);
    D_0063BFF4 = -1;
    th = actCreateSubThread(actSt13bElevDownSub, 0x15);
    D_0063C57C = 0;

    while (D_0063C57C == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 0x24, 0x22);

    if (D_0063C57C == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        scpAdpcmFadeCloseFunc(&st13b_down, 0x200);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
    }

    if (D_0063BFF4 >= 0) {
        iosPadActStop(D_0063BFF4);
    }

    RequestStageChange(3, D_00639EA4, 0, 2.0f, 4.0f);
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}

void actSt13bElevUp(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x145) != 0) {
        lt_switch_layout(0x37);
        D_0063AA08 = 1;
        scpFadeOut(255.0f, 0, 0, 0);
        stage_SetAnimation(0x28, 0, 0xEB);
        _ACTWait(0xA);
        D_0063AA08 = 1;
        stage_SetAnimation(0x28, 0, 0);
        D_004FAC00[0].func = actSt13bElevUpChk;
        self->mail = D_004FAC00;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x28, 0, 0xEB);
    }
}

void actSt13bElevUpChk(volatile int a0)
{
    int th;

    scpAdpcmPlayRequestFunc(0x4E, &st13b_up, 1, 1, 1);

    while (st13b_up == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);
    th = actCreateSubThread(actSt13bElevUpSub, 0x15);

    D_0063C57C = 0;
    D_0063BFF4 = -1;

    while (D_0063C57C == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 0x24, 0x22);

    if (D_0063C57C == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        scpAdpcmFadeCloseFunc(&st13b_up, 0x200);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(0x28, 0, 0xEB);
        _ACTWait(2);
        scpPlayPosSet((void *)D_00639EA4, -772.0f, 527.0f, -226.0f);

        if (D_0063BFF4 >= 0) {
            iosPadActStop(D_0063BFF4);
        }

        scpFadeIn(3.0f);
    }

    D_0063AA08 = 0;
    lt_switch_layout(0x36);
    gflagOff(0x145);
}

void actSt13bDoorUp(volatile int a0)
{
    int th;

    lt_switch_layout(0x37);
    gflagOn(0x11);
    th = actCreateSubThread(actSt13bDoorUpSub, 0x15);

    D_0063C57C = 0;
    D_0063C58C = 0;

    while (D_0063C57C == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 0x24, 0x22);

    if (D_0063C57C == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(0x2B, 0, -1);
        scpFadeIn(3.0f);
    }

    if (D_0063C58C == 0) {
        soundSeDefPlay(0x4C6, 0, 0, 1);
    }

    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}

INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bElev2Chk);

void actSt13bSekizo(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0xA) == 0) {
        stage_SetAnimation(0x21, 0, 0);

        D_004FAB00[0].func = actSt13bSekizoChk;
        self->mail = D_004FAB00;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x21, 0, -1);
    }
}

void actSt13bSekizo2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0xB) == 0) {
        stage_SetAnimation(0x22, 0, 0);

        D_004FAB20[0].func = actSt13bSekizo2Chk;
        self->mail = D_004FAB20;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x22, 0, -1);
    }
}

void actSt13bBossAfter(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0xE) == 0) {
        stage_SetAnimation(0x23, 0, 0);

        D_004FAB80[0].func = actSt13bBossAfterChk;
        self->mail = D_004FAB80;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x23, 0, -1);
    }
}

void actSt13bStoneGirl(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (D_00639ED4 == 0x2E) {
        scpPlayMot(scpSearchGobj(0x99E), 0x328);
        scpSearchGobj(0x99E)->f16C = 1;
    }
}

void actSt13bElev(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    D_004FABC0[0].func = actSt13bElevMain;
    self->mail = D_004FABC0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt13bElev2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x10) != 0) {
        stage_SetAnimation(0x2A, 0, 0);

        D_004FAC90[0].func = actSt13bElev2Chk;
        self->mail = D_004FAC90;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x29, 0, 0);

        D_004FACB0[0].func = actSt13bElev2Chk;
        self->mail = D_004FACB0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSt13bDoor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x11) == 0) {
        stage_SetAnimation(0x2B, 0, 0);

        D_004FAC40[0].func = actSt13bDoorMain;
        self->mail = D_004FAC40;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x2B, 0, -1);
    }
}

void actBossTest(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    stage_SetAnimation(0x20, 0, -1);
    stage_SetAnimation(0x1A, 0, 0);
    stage_SetAnimation(0x23, 0, 0);
    stage_SetAnimation(0x24, 0, 0);
    stage_SetAnimation(0x26, 0, 0);
}

void actSt13bConte02Jimaku(volatile int a0)
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
        case 1800:
            jimaku_msg.sub.unk2C = 1;
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
    } while (t < 2500.0f);
}

void actSt13bSekizo2Event(int x)
{
    volatile int local = x;
}

void actConte10c(volatile int a0)
{
    stage_SetAnimation(0x2FB, 1, 0);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFrame(0x2FB, 0x12C, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(0x23, 1, 0);

    while (stage_CheckAnimationFinish(0x2FB) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C57C = 1;
    _ACTWait(0);
}

void actSt13bElevMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = D_004FABA0;
    while (1) {
        _ACTWait(1);
    }
}

void actSt13bElevSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    D_0063AA08 = 1;

    D_004FABE0[0].func = actSt13bElevDown;
    sub->mail = D_004FABE0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt13bElevUpSub(volatile int a0)
{
    stage_SetAnimation(0x28, 1, 0);
    D_0063BFF4 = iosPadActRequest(D_00639EAC, 9);
    D_0063BFF8 = 0x80;
    iosPadActVolumeSet(D_0063BFF4, 0x80);
    while (stage_CheckAnimationFrame(0x28, 0xC8, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);
    iosPadActStop(D_0063BFF4);
    while (stage_CheckAnimationFrame(0x28, 0xEA, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0063C57C = 1;
    _ACTWait(0);
}

void actSt13bDoorMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = D_004FAC20;
    while (1) {
        _ACTWait(1);
    }
}

void actSt13bDoorSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    D_0063AA08 = 1;

    D_004FAC60[0].func = actSt13bDoorUp;
    sub->mail = D_004FAC60;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt13bDoorUpSub(volatile int a0)
{
    _ACTWait(0x3C);

    stage_SetAnimation(0x2B, 1, 0);

    _ACTWait(0x78);

    soundSeDefPlay(0x4C5, 0, D_004FAC80, 1);

    _ACTWait(0x1E);

    D_0063C58C = 1;
    soundSeDefPlay(0x4C6, 0, D_004FAC80, 1);

    while (stage_CheckAnimationFinish(0x2B) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C57C = 1;
    _ACTWait(0);
}

void actSt13bElev2CharaChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttr(D_00639EA4, 0x4000000) != 0) {
        _ACTWait(1);
    }

    D_004FACF0[0].func = actSt13bElev2Chk;
    sub->mail = D_004FACF0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
