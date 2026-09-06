#include "common.h"

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;
typedef struct Act {
    char unk00[0xD0];           /* 0x00 */
    ActMail *mainMail;          /* 0xD0 */
    ActMail *mail;              /* 0xD4 */
} Act;
typedef struct PObjGObj {
    char pad00[0x164];          /* 0x000 */
    Act *act;                   /* 0x164 */
    char pad168[0x4];           /* 0x168 */
    int f16C;                   /* 0x16C */
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

INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bFloor);
ASM_LIT4_SLOT(D_00639A30, 0.025f);
INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bFloorChk);
INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bConte02);
ASM_LIT4_SLOT(D_00639A34, -1338.0f);
ASM_LIT4_SLOT(D_00639A38, 3085.0f);
INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bSekizoChk);
ASM_LIT4_SLOT(D_00639A3C, 527.0f);
ASM_LIT4_SLOT(D_00639A40, -1563.0f);
INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bSekizo2Chk);
INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bMeetAgain);
INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bMeetAgainSub);
INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bMeetAgainChk);
ASM_LIT4_SLOT(D_00639A44, -1886.0f);
ASM_LIT4_SLOT(D_00639A48, 625.0f);
INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bBoss);
INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bBossChk);
INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bBossAfterChk);
INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bElevDownSub);
INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bElevDown);
INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bElevUp);
ASM_LIT4_SLOT(D_00639A4C, 527.0f);
INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bElevUpChk);
INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bDoorUp);
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
void actSt13bConte02Jimaku(volatile int a0) {
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
void actSt13bSekizo2Event(int x) {
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
