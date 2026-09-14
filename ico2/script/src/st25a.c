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

extern char D_005549D0[];
extern void tex_SetUVScroll(void *a0, float f12, float f13, float f14, float f15, float f16,
                            float f17, int a1);
extern void Generator_Mask(char *self);
extern Act *actInitialize(int a0);
extern int scpGameStat_BoyWeaponkind(void);
extern void scpLinkBGAtoLayoutedTarget(int a0, int a1);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int D_0063AA30;
extern int D_00639EA4;

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
extern void jimakuJump(int a0);
extern int D_0028F4C0[];
extern void _ACTWait(int a0);
extern void gflagOn(int a0);
extern void jimakuBegin(int a0);
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
extern int scpTriggerFloorAttr(int a0, int a1);
extern int dead;
extern char D_00618ED0[];
extern char D_00554930[];
extern int InqQueenBarrierExist(void);
extern int gflagChk(int a0);
extern void StandbyStreamMotion(int self);
extern int CheckReadyStreamMotion(void);
extern void debug_StdPrintfDummy(char *fmt, ...);
extern char D_005549C0[];
extern ActMail D_002A5440[];
extern ActMail D_002A5480[];
extern ActMail D_002A54A0[];
extern ActMail D_002A54C0[];
extern ActMail D_002A54E0[];
extern ActMail D_002A5500[];
extern ActMail D_002A5520[];
extern ActMail D_002A5560[];
extern PObjGObj *scpSearchGobj(int a0);
extern int ForMotionViewer_GetCurrentMotion(char *self);
extern void ACTSendMailCorrect(int a0, int mail);
extern void actSt25aElevChk(volatile int a0);
extern void MallocStreamMotionBuffer(void);
extern void fightSoundProcessRequestPause(void);
extern void actSt25aQueenTalkChk(volatile int a0);
extern void actSt25aQueenDeadChk(volatile int a0);
void actSt25aQueenBeforeChk(volatile int a0);
void actSt25aQueenDeadReadyChk(volatile int a0);
void actItouQueenAttackChk(volatile int a0);
extern int enable_game_pause;
extern int D_0063AA08;
extern void AdpcmPlay(int handle);
extern void actCreateSubThread(void *entry, int prio);
void actConte11(volatile int a0);
void actConte11Jimaku(volatile int a0);

void actSt25aQueenAppearChk(volatile int a0)
{
    while (scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0 || gflagChk(0x14B) == 0) {
        _ACTWait(1);
    }
    enable_game_pause = 0;
    gflagOn(0x14C);
    actCreateSubThread(actConte11Jimaku, 0x15);
    while (D_0063AA30 == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(*(int *)(D_0063AA30 + 0x2C));
    D_0063AA08 = 1;
    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 3);
    actCreateSubThread(actConte11, 0x15);
}

INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st25a", actConte11);
ASM_LIT4_SLOT(D_006390D4, 0.99f);
ASM_LIT4_SLOT(D_006390D8, 0.1f);
ASM_LIT4_SLOT(D_006390DC, 0.8f);
ASM_LIT4_SLOT(D_006390E0, 0.45f);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st25a", actSt25aQueenTalkChk);
ASM_LIT4_SLOT(D_006390E4, 625.0f);
ASM_LIT4_SLOT(D_006390E8, 1650.0f);
INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st25a", actConte12);

void actConte12Jimaku(volatile int a0)
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
        case 341:
            jimaku_msg.sub.unk2C = 96;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 521:
            jimaku_msg.sub.unk2C = 97;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 801:
            jimaku_msg.sub.unk2C = 98;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 1031:
            jimaku_msg.sub.unk2C = 99;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 1301:
            jimaku_msg.sub.unk2C = 100;
            jimaku_msg.sub.unk38 = 200;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 1781:
            jimaku_msg.sub.unk2C = 104;
            jimaku_msg.sub.unk38 = 200;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 2261:
            jimaku_msg.sub.unk2C = 105;
            jimaku_msg.sub.unk38 = 150;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 2561:
            jimaku_msg.sub.unk2C = 106;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 3780:
            jimaku_msg.sub.unk2C = 109;
            jimaku_msg.sub.unk38 = 180;
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
    } while (t < 4200.0f);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st25a", actSt25aQueenDeadChk);

void actConte13Jimaku(volatile int a0)
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
        case 600:
            jimaku_msg.sub.unk2C = 110;
            jimaku_msg.sub.unk38 = 400;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 1320:
            jimaku_msg.sub.unk2C = 111;
            jimaku_msg.sub.unk38 = 200;
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
    } while (t < 3100.0f);
}

void BoySekikaTexScroll(void)
{
    tex_SetUVScroll(D_005549D0, 0.0f, 0.0f, 0.0f, 0.01f, 0.0f, 0.5f, 1);
}

extern ActMail D_002A5540[];
extern int D_0063AA44;
extern int D_0063AA48;
extern int D_00639EAC;
extern void gflagOff(int a0);
extern void RequestStageChange(int a0, int gobj, float f12, float f13, int a2);
extern void actSt25aElevCharaChk(volatile int a0);
extern int iosPadActRequest(int port, int id);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern void lt_switch_layout(int a0);

void actSt25aElevChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttr(D_00639EA4, 0x4000000) == 0) {
        _ACTWait(1);
    }
    lt_switch_layout(55);
    D_0063AA08 = 1;
    if (gflagChk(0x151) == 0) {
        scpAdpcmPlayRequestFunc(100, &D_0063AA48, 1, 1, 1);
        while (D_0063AA48 == 0) {
            _ACTWait(1);
        }
        _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]);
        stage_SetAnimation(0xA1, 1, 0);
        while (stage_CheckAnimationFrame(0xA1, 50, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        iosPadActRequest(D_00639EAC, 16);
        while (stage_CheckAnimationFinish(0xA1) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        gflagOn(0x151);
    } else {
        scpAdpcmPlayRequestFunc(99, &D_0063AA44, 0, 1, 1);
        while (D_0063AA44 == 0) {
            _ACTWait(1);
        }
        _ACTWait((int)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0.15));
        stage_SetAnimation(0xA2, 1, 0);
        while (stage_CheckAnimationFinish(0xA2) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        gflagOff(0x151);
        RequestStageChange(1, D_00639EA4, 2.0f, 8.0f, 0);
    }
    D_0063AA08 = 0;
    lt_switch_layout(54);
    D_002A5540[0].func = actSt25aElevCharaChk;
    sub->mail = D_002A5540;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt25aGenerator(volatile unsigned int a0)
{
    Generator_Mask(a0);
}

void actSt25aQueenBefore(volatile int a0)
{
    int x = a0;
    Act *sub = actInitialize(a0);

    _ACTWait(1);

    MallocStreamMotionBuffer();

    if (gflagChk(0x14B) == 0) {
        D_002A5440[0].func = actSt25aQueenBeforeChk;
        sub->mail = D_002A5440;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSt25aQueenTalk(volatile int a0)
{
    int x = a0;
    Act *sub = actInitialize(a0);

    _ACTWait(1);

    fightSoundProcessRequestPause();

    if (gflagChk(0x14D) == 0) {
        scpSearchGobj(0x86E)->f16C = 0;
        D_002A5480[0].func = actSt25aQueenTalkChk;
        sub->mail = D_002A5480;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSt25aQueenDeadReady(volatile int a0)
{
    int x = a0;
    Act *sub = actInitialize(a0);

    _ACTWait(1);

    D_002A54A0[0].func = actSt25aQueenDeadReadyChk;
    sub->mail = D_002A54A0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt25aQueenDead(volatile int a0)
{
    int x = a0;
    Act *sub = actInitialize(a0);

    _ACTWait(1);

    D_002A54C0[0].func = actSt25aQueenDeadChk;
    sub->mail = D_002A54C0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actItouQueenAttack(volatile int a0)
{
    int x = a0;
    Act *sub = actInitialize(a0);

    _ACTWait(1);

    D_002A54E0[0].func = actItouQueenAttackChk;
    sub->mail = D_002A54E0;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt25aElev(volatile int a0)
{
    int x = a0;
    Act *sub = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x151) != 0) {
        stage_SetAnimation(0xA2, 0, 0);
        D_002A5500[0].func = actSt25aElevChk;
        sub->mail = D_002A5500;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xA1, 0, 0);
        D_002A5520[0].func = actSt25aElevChk;
        sub->mail = D_002A5520;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSwordEff(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpLinkBGAtoLayoutedTarget(0x832, 0x1E7);
}

void actSwordEffXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (scpGameStat_BoyWeaponkind() == 5) {
        scpLinkBGAtoLayoutedTarget(0x832, 0x1E7);
    } else {
        stage_SetAnimation(0x1E7, -1, -2);
    }
}

void actSt25aQueenBeforeChk(volatile int a0)
{
    D_0063AA30 = 0;
    while (scpTriggerFloorAttr(D_00639EA4, 0x1000000) == 0) {
        _ACTWait(1);
    }
    gflagOn(0x14B);
    jimakuBegin((int)&jimaku_msg);
    scpAdpcmPlayRequestFunc(0x27, &D_0063AA30, 1, 1, 0);
}

void actConte11Jimaku(volatile int a0)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 1:
            break;
        case 10:
            jimaku_msg.sub.unk2C = 0x5D;
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
    } while (t < 1500.0f);
}

void actSt25aQueenDeadReadyChk(volatile int a0)
{
    int i;

    dead = 0;
    while (InqQueenBarrierExist() != 0 || gflagChk(0x14E) == 0) {
        _ACTWait(1);
    }
    StandbyStreamMotion((int)D_00618ED0);
    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy(D_00554930, i);
        _ACTWait(1);
    }
    scpAdpcmPlayRequestFunc(0x2A, &dead, 0, 1, 0);
}

void actSt25aQueenDeadEvent(int x)
{
    volatile int local = x;
}

void actItouQueenAttackChk(volatile int a0)
{
    while (1) {
        while (ForMotionViewer_GetCurrentMotion((char *)scpSearchGobj(0xDC6)) != 0x436) {
            _ACTWait(1);
        }
        tex_SetUVScroll(D_005549C0, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 1);
        _ACTWait(1);
    }
}

void actSt25aElevCharaChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttr(D_00639EA4, 0x4000000) != 0) {
        _ACTWait(1);
    }

    D_002A5560[0].func = actSt25aElevChk;
    sub->mail = D_002A5560;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
