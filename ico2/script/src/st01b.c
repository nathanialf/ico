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
    int act;           /* 0x164 */
} PObjGObj;

/* This stage's actor mail records. Word 0 of each entry is the mail id the
   entry answers (430 = the actor's own wake-up post, 429 = the trailing
   entry); the handler in .func is installed at run time just before the
   record is posted. Each record is named for the actor thread that owns
   and posts it. */
static ActMail ene_mes[2] = {{430}, {429}};

static ActMail floor_mes[2] = {{430}, {429}};

static ActMail way_mes[2] = {{430}, {429}};

static ActMail way_on_mes[2] = {{430}, {429}};

static ActMail way_off_mes[2] = {{430}, {429}};

extern Act *actInitialize(int a0);
extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern int gflagChk(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
extern void Generator_MaskOff(int a0);
extern void SetWayGroupActive(int grp, int on);
extern void stage_SetAnimation(int no, int a1, int a2);
extern void FinishHint(int no);

void actSt01bInit(void)
{
    if (gflagChk(0x46) == 0) {
        SetWayGroupActive(2, 0);
        stage_SetAnimation(0xB7, 0, 0);
        return stage_SetAnimation(0xB4, 0, 0);
    }
    SetWayGroupActive(2, 1);
    stage_SetAnimation(0xB7, 0, -1);
    stage_SetAnimation(0xB4, 0, -1);
    return FinishHint(9);
}

extern int D_00639EA4;
extern int D_00639EA8;
extern int D_0063AA08;
extern int scpTriggerFloorAttr(int gobj, int attr);
extern void scpSleepEnemyOne(int id);
extern void scpWakeupEnemyOne(int id);
extern void lt_switch_layout(int a0);
extern void gflagOn(int a0);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);

void actSt01bEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (gflagChk(0x46) == 0 || scpTriggerFloorAttr(D_00639EA4, 0x1000000) == 0 ||
           (scpTriggerFloorAttr(D_00639EA8, 0x1000000) == 0 &&
            scpTriggerFloorAttr(D_00639EA8, 0x2000000) == 0)) {
        _ACTWait(1);
    }
    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyOne(0xEAD);
    _ACTWait(0x1E);
    gflagOn(0x44);
    gflagOn(0x45);
    stage_SetAnimation(0xB6, 1, 0);
    while (stage_CheckAnimationFrame(0xB6, 0x5A, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    while (stage_CheckAnimationFinish(0xB6) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_switch_layout(0x36);
    D_0063AA08 = 0;
    scpWakeupEnemyOne(0xEAD);
}

typedef struct {
    char pad00[0x2C];
    int f2C;
} FloorRec;

extern FloorRec *st01b_floor;
extern unsigned int st01b_yure;
extern unsigned char st01b_yure_vol;
extern int D_0063C4FC;
extern int D_0063C500;
extern int D_00639EAC;
extern long long D_00622700[];
extern void AdpcmPlay(int a0);
extern int soundSeDefPlay(int se, int a1, void *pos, int a3);
extern void soundSeDefStop(int handle);
extern int iosPadActRequest(int port, int id);
extern int *iosPadActVolumeSet(int key, unsigned int val);

void actSt01bFloorChkSub(volatile int a0)
{
    long long pos[2];

    while (st01b_floor == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(st01b_floor->f2C);
    stage_SetAnimation(0xB4, 1, 0);
    stage_SetAnimation(0xB5, 1, 0);
    pos[0] = D_00622700[0];
    pos[1] = D_00622700[1];
    D_0063C500 = soundSeDefPlay(0x52D, 0, pos, 1);
    _ACTWait(0x5A);
    soundSeDefStop(D_0063C500);
    D_0063C500 = -1;
    soundSeDefPlay(0x508, 0, 0, 1);
    stage_SetAnimation(0xB7, 1, 0);
    st01b_yure = iosPadActRequest(D_00639EAC, 9);
    st01b_yure_vol = 0x80;
    iosPadActVolumeSet(st01b_yure, 0x80);
    while (stage_CheckAnimationFrame(0xB7, 0xB4, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0063C4FC = 1;
    _ACTWait(0);
}

extern int D_0028F8F4[];
extern int scpIsHangChainOptional(int gobj, int id);
extern void scpPlayPosSet(int gobj, float x, float y, float z);
extern void scpAdpcmPlayRequestFunc(int a0, void *a1, int a2, int a3, int a4);
extern int scpAdpcmFadeCloseFunc(void *h, int fade);
extern int scpAdpcmPlayRequestNum(void);
extern int actCreateSubThread(void *entry, int prio);
extern void iosThreadSetPri(int th, int pri);
extern void scpFadeOut(float t, int a1, int a2, int a3);
extern void scpFadeIn(float t);
extern int scpFadeChk(void);
extern int lt_fade_status(void);
extern void iosPadActStop(int key);
extern void scpSleepEnemyAll(void);
extern void scpWakeupEnemyAll(void);
extern void *scpSearchGobj(int id);
extern void ChainPositionReset(void *gobj);
extern void actSt01bFloorChkSub(volatile int a0);

void actSt01bFloorChk(volatile int a0)
{
    int th;
    int notdone;

    while (scpIsHangChainOptional(D_00639EA4, 0x325) == 0) {
        _ACTWait(1);
    }
    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();
    gflagOn(0x46);
    FinishHint(9);
    SetWayGroupActive(2, 1);
    if (D_00639EA8 != 0) {
        scpPlayPosSet(D_00639EA8, -200.0f, 900.0f, -200.0f);
    }
    scpAdpcmPlayRequestFunc(0x51, &st01b_floor, 1, 1, 0);
    th = actCreateSubThread(actSt01bFloorChkSub, 0x15);
    D_0063C500 = -1;
    st01b_yure = 0xFFFFFFFF;
    D_0063C4FC = 0;
    st01b_floor = 0;

    while (D_0063C4FC == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    notdone = D_0063C4FC ^ 1;
    if (notdone) {
        while (st01b_floor == 0) {
            _ACTWait(1);
        }
        scpAdpcmFadeCloseFunc(&st01b_floor, 0x100);
        scpFadeOut(16.0f, 0, 0, 0);
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    iosThreadSetPri(th + 0x24, 0x22);

    if (notdone) {
        stage_SetAnimation(0xB5, 1, -1);
        stage_SetAnimation(0xB4, 1, -1);
        stage_SetAnimation(0xB7, 0, 0xB4);
        if (D_0063C500 >= 0) {
            soundSeDefStop(D_0063C500);
            soundSeDefPlay(0x508, 0, 0, 1);
        }
        _ACTWait(1);
        ChainPositionReset(scpSearchGobj(0x325));
        _ACTWait(1);
        scpFadeIn(3.0f);
    }

    iosPadActStop(st01b_yure);
    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}

extern void scpSekizou(int a0, int a1, int a2, int a3, int a4, float x1, float y1, float z1,
                       float x2, float y2, float z2);

void actSt01bSekizo(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x41, 0xB2, 0, 0x12, 1000.0f, 528.0f, -150.0f, 1000.0f, 528.0f, -100.0f);
}

extern void actSt01bEneChk(volatile int a0);

void actSt01bEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x44) == 0) {
        ene_mes[0].func = actSt01bEneChk;
        self->mail = ene_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt01bEnemy1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);

    while (gflagChk(0x45) == 0) {
        _ACTWait(1);
    }

    _ACTWait(0x74);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt01bEnemy2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);

    while (gflagChk(0x45) == 0) {
        _ACTWait(1);
    }

    _ACTWait(0x64);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt01bEnemy3(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);

    while (gflagChk(0x45) == 0) {
        _ACTWait(1);
    }

    _ACTWait(0x82);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt01bEnemy4(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);

    while (gflagChk(0x45) == 0) {
        _ACTWait(1);
    }

    _ACTWait(0x73);
    Generator_Call(a0);
}

void actSt01bEnemy5(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);

    while (gflagChk(0x45) == 0) {
        _ACTWait(1);
    }

    _ACTWait(0x7D);
    Generator_Call(a0);
}

void actSt01bEnemy6(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);

    while (gflagChk(0x45) == 0) {
        _ACTWait(1);
    }

    _ACTWait(0x6E);
    Generator_Call(a0);
}

extern void actSt01bFloorChk(volatile int a0);

void actSt01bFloor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x46) == 0) {
        floor_mes[0].func = actSt01bFloorChk;
        self->mail = floor_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

extern void actSt01bWayOnChk(volatile int a0);

void actSt01bWay(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    way_mes[0].func = actSt01bWayOnChk;
    self->mail = way_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt01bEnd(void) {}

void actSt01bSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt01bFloorEvent(int x)
{
    volatile int local = x;
}

extern void actSt01bWayOffChk(volatile int a0);
extern int D_00639EA8;
extern int scpTriggerFloorAttr(int a0, int a1);
extern void SetWayGroupActive(int a0, int a1);

void actSt01bWayOnChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0x1000000) == 0 || gflagChk(0x46) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(4, 1);

    way_on_mes[0].func = actSt01bWayOffChk;
    sub->mail = way_on_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt01bWayOffChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0x2000000) == 0 || gflagChk(0x46) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(4, 0);

    way_off_mes[0].func = actSt01bWayOnChk;
    sub->mail = way_off_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}
