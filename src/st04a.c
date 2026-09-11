#include "common.h"

typedef union ActStatus {
    unsigned long long ll;
    int i[2];
} ActStatus;

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;

typedef struct Act {
    char unk00[0x20];  /* 0x00 */
    ActStatus flags20; /* 0x20 */
    char unk28[0xA8];  /* 0x28 */
    ActMail *mainMail; /* 0xD0 */
    ActMail *mail;     /* 0xD4 */
    char unkD8[0x398]; /* 0xD8 */
    int unk470;        /* 0x470 */
    void *unk474;      /* 0x474 */
    int unk478;        /* 0x478 */
} Act;

typedef struct PObjGObj {
    char pad00[0x15C]; /* 0x000 */
    char *f15C;        /* 0x15C */
    char pad160[0x4];  /* 0x160 */
    Act *act;          /* 0x164 */
    char pad168[0x4];  /* 0x168 */
    int f16C;          /* 0x16C */
} PObjGObj;

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern PObjGObj *scpSearchGobj(int a0);
extern int gflagChk(int a0);
extern void gflagOn(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern int scpTriggerBall(int a0, void *a1, float radius);
extern int scpTriggerFloorAttr(void *a0, int a1);
extern void scpFadeOut(float a0, int a1, int a2, int a3);
extern void iosOmSendMail(void *gobj, int mail, void *src);
extern char *D_00639EA4;
extern char *D_00639EA8;
extern void debug_StdPrintfDummy();
extern Act *actInitialize(int a0);
extern int D_0028F4C0[];
extern float D_0063AA0C;
extern void MallocStreamMotionBuffer(void);
extern void stage_SetLoopFlag(int key, int a1);
extern void gflagOff(int a0);
extern void actSt04aGateChk(volatile int a0);
extern ActMail D_004F85D0[];

void actSt04aGate(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    MallocStreamMotionBuffer();

    scpSearchGobj(0x24E)->f16C = 0;

    if (gflagChk(0x89) == 0) {
        scpFadeOut(255.0f, 0, 0, 0);

        stage_SetLoopFlag(0x22B, 0);

        stage_SetAnimation(0x10D, 0, 0);
        stage_SetAnimation(0x110, 0, 0);

        gflagOff(0x186);

        D_004F85D0[0].func = actSt04aGateChk;
        self->mail = D_004F85D0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetLoopFlag(0x22B, 0);

        stage_SetAnimation(0x10D, 0, -1);
        stage_SetAnimation(0x110, 0, 0);
    }
}

ASM_LIT4_SLOT(D_006398D8, 3000.0f);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aGateChk);
ASM_LIT4_SLOT(D_006398DC, 0.99f);
ASM_LIT4_SLOT(D_006398E0, 0.1f);
ASM_LIT4_SLOT(D_006398E4, 0.8f);
ASM_LIT4_SLOT(D_006398E8, 0.45f);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aConte06);

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

void actSt04aConte06Jimaku(volatile int a0)
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
        case 0xFA:
            jimaku_msg.sub.unk2C = 0x19;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x564:
            jimaku_msg.sub.unk2C = 0x1A;
            jimaku_msg.sub.unk38 = 0x3C;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x94C:
            jimaku_msg.sub.unk2C = 0x1F;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0xB2D:
            jimaku_msg.sub.unk2C = 0x22;
            jimaku_msg.sub.unk38 = 0x96;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0xC58:
            jimaku_msg.sub.unk2C = 0x23;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0xD84:
            jimaku_msg.sub.unk2C = 0x24;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0xEB0:
            jimaku_msg.sub.unk2C = 0x25;
            jimaku_msg.sub.unk38 = 0xAE;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x1054:
            jimaku_msg.sub.unk2C = 0x26;
            jimaku_msg.sub.unk38 = 0xAE;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x12C0:
            jimaku_msg.sub.unk2C = 0x2B;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x15CC:
            jimaku_msg.sub.unk2C = 0x1B;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x17A2:
            jimaku_msg.sub.unk2C = 0x1D;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x1A54:
            jimaku_msg.sub.unk2C = 0x30;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x1B44:
            jimaku_msg.sub.unk2C = 0x31;
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
    } while (t < 7300.0f);
    _ACTWait(0);
}

extern void MallocStreamMotionBuffer(void);
extern void SetWayGroupActive(int a0, int a1);
extern void SetGirlHairDispSwitch(char *a0, int a1);
extern void actSt04aGateOpenChk(volatile int a0);
extern ActMail D_004F85F0[];

void actSt04aGateOpen(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    MallocStreamMotionBuffer();

    if (gflagChk(0x8C) == 0) {
        stage_SetAnimation(0x10E, 0, 0);

        scpSearchGobj(0x29D)->f16C = 0;

        D_004F85F0[0].func = actSt04aGateOpenChk;
        self->mail = D_004F85F0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        SetWayGroupActive(2, 1);

        stage_SetAnimation(0x10E, 0, -1);
        stage_SetAnimation(0x110, 0, -1);
        stage_SetAnimation(0x113, 0, -1);

        scpSearchGobj(0x29D)->f16C = 0;

        SetGirlHairDispSwitch(D_00639EA8, 1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aGateOpenChk);

extern int EntryStreamMotion(char *a0);
extern void SetStreamMotionFinishCallBackFunc(int a0, void *a1);
extern void PlayStreamMotion(void);
extern void scpPlayMot(void *o, int mot);
extern void scpKillEnemyAll(void);
extern void scpDispOnAllWithKind(int a0);
extern void SetGirlHairDispSwitch(char *a0, int a1);
extern int iosPadActRequest(int port, int id);
extern int *iosPadActVolumeSet(int key, unsigned int val);
extern void iosPadActStop(int a0);
extern void finishCallBackFunc(int a0);
extern int D_00639EAC;
extern int D_0063BEC4;
extern unsigned char D_0063BEC8;
extern int D_0063C508;

void actConte09(volatile int a0)
{
    int th1;
    int th2;

    th1 = EntryStreamMotion(D_00639EA4);
    th2 = EntryStreamMotion(D_00639EA8);

    SetStreamMotionFinishCallBackFunc(th1, finishCallBackFunc);
    SetStreamMotionFinishCallBackFunc(th2, finishCallBackFunc);

    PlayStreamMotion();

    scpPlayMot(D_00639EA4, 0);

    scpSearchGobj(0x288)->f16C = 1;

    stage_SetAnimation(0x2C8, 1, 0);

    while (stage_ContinueAnimation(0x2C8, 0x2C9) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x2C9, 0x2CA) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x118, 1, 0);

    while (stage_CheckAnimationFrame(0x2CA, 0x7D, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0xF);

    scpKillEnemyAll();

    while (stage_ContinueAnimation(0x2CA, 0x2CB) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(0x2CB, 0xF, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_ContinueAnimation(0x2CB, 0x2CC) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x10E, 1, 0);

    while (stage_ContinueAnimation(0x2CC, 0x2CD) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x2CD, 0x2CE) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(0x2CE, 0x46, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetGirlHairDispSwitch(D_00639EA8, 1);

    while (stage_ContinueAnimation(0x2CE, 0x2CF) == 0) {
        _ACTWait(1);
    }

    _ACTWait(0x12C);

    stage_SetAnimation(0x113, 1, 0);

    _ACTWait(0x78);

    D_0063BEC4 = iosPadActRequest(D_00639EAC, 0xA);
    D_0063BEC8 = 0x80;
    iosPadActVolumeSet(D_0063BEC4, 0x80);

    while (stage_ContinueAnimation(0x2CF, 0x2D0) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x110, 1, 0);

    while (stage_ContinueAnimation(0x2D0, 0x2D1) == 0) {
        _ACTWait(1);
    }

    iosPadActStop(D_0063BEC4);

    while (stage_ContinueAnimation(0x2D1, 0x2D2) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x2D2, 0x2D3) == 0) {
        _ACTWait(1);
    }

    scpDispOnAllWithKind(0x13);

    gflagOn(0x8C);

    while (stage_ContinueAnimation(0x2D3, 0x2D4) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFinish(0x2D4) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    *(int *)(*(int *)(D_00639EA4 + 0x15C) + 0x514) =
        (int)((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f * 0.0f);
    *(int *)(*(int *)(D_00639EA8 + 0x15C) + 0x514) =
        (int)((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f * 0.0f);

    D_0063C508 = 1;

    _ACTWait(0);
}

void actConte09Jimaku(volatile int a0)
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
        case 0x871:
            jimaku_msg.sub.unk2C = 0x58;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x97E:
            jimaku_msg.sub.unk2C = 0x56;
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
    } while (t < 2700.0f);
    _ACTWait(0);
}

extern int ACTGame_FLAG_TETSUNAGI(void);
extern void lt_switch_layout(int a0);
extern void scpPlayStart(char *a0);
extern void AdpcmPlay(int handle);
extern int actCreateSubThread(void *entry, int prio);
extern int D_0063AA08;
extern int D_0063BEA8;
extern void scpPlayMotReq(void *a0, int mot);
extern void scpPlayMot(void *o, int mot);
extern void *test_CURRENTROOT(int a0);
extern void sceVu0SubVector(void *out, void *a, void *b);
extern void scpPlayMotDir(void *a0, void *dir);
extern void scpDisActivateAllWithKind(int a0);
extern void actConte09_2(volatile int a0);
/* st04a.o's own .rodata: the gate-open exit direction vector. */
extern long long D_006229A0[];

void actSt04aGateOpen2Chk(volatile int a0)
{
    long long ofs[2];
    float dir[4];

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA8, 0x1000000) == 0 || ACTGame_FLAG_TETSUNAGI() == 0) {
        _ACTWait(1);
    }

    ((PObjGObj *)D_00639EA8)->act->flags20.ll &= ~0x10000;
    scpPlayMotReq(D_00639EA8, 0x13B);

    scpPlayMot(D_00639EA4, 0);

    ofs[0] = D_006229A0[0];
    ofs[1] = D_006229A0[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT((int)D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    lt_switch_layout(0x37);

    D_0063AA08 = 1;
    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);

    scpDisActivateAllWithKind(0x13);

    while (D_0063BEA8 == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(D_0063BEA8 + 0x2C));

    actCreateSubThread(actConte09_2, 0x15);
}

extern void ClearStreamMotionEntry(char *a0);
extern void scpAdpcmPlayRequestFunc(int a0, void *a1, int a2, int a3, int a4);
extern void StandbyStreamMotion(char *a0);
extern int CheckReadyStreamMotion(void);
extern void scpPlayPosSet(char *a0, float x, float y, float z);
extern void scpPlayEnd(char *a0);
extern char D_00618E10[];
extern char D_00622840[];
/* st04a.o's own .rodata: the two demo exit direction vectors. */
extern long long D_00622990[];
extern int D_0063BEAC;
extern int D_0063BECC;
extern unsigned char D_0063BED0;

void actConte09_2(volatile int a0)
{
    long long ofs[2];
    float dir[4];
    int i;

    EntryStreamMotion(D_00639EA4);
    EntryStreamMotion(D_00639EA8);

    PlayStreamMotion();

    stage_SetAnimation(0x2D8, 1, 0);
    stage_SetAnimation(0x119, 1, 0);

    while (stage_ContinueAnimation(0x2D8, 0x2D9) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(0x2D9, 0x1E, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0xF);

    while (stage_ContinueAnimation(0x2D9, 0x2DA) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(0x2DA, 0xF, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_ContinueAnimation(0x2DA, 0x2DB) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x2DB, 0x2DC) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x2DC, 0x2DD) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x2DD, 0x2DE) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x2DE, 0x2DF) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x2DF, 0x2E0) == 0) {
        _ACTWait(1);
    }

    D_0063BECC = iosPadActRequest(D_00639EAC, 0xA);
    D_0063BED0 = 0x80;
    iosPadActVolumeSet(D_0063BECC, 0x80);

    stage_SetAnimation(0x111, 1, 0);

    while (stage_ContinueAnimation(0x2E0, 0x2E1) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x2E1, 0x2E2) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x2E2, 0x2E3) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x2E3, 0x2E4) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x2E4, 0x2E5) == 0) {
        _ACTWait(1);
    }

    ClearStreamMotionEntry(D_00639EA8);

    scpPlayMotReq(D_00639EA8, 0x13B);

    scpPlayPosSet(D_00639EA8, 14.8948f, 210.136f, 4858.48f);

    ofs[0] = D_00622990[0];
    ofs[1] = D_00622990[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT((int)D_00639EA8));
    scpPlayMotDir(D_00639EA8, dir);

    lt_switch_layout(0x36);

    while (stage_CheckAnimationFinish(0x2E5) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(D_0063BECC);

    ofs[0] = D_006229A0[0];
    ofs[1] = D_006229A0[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT((int)D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    StandbyStreamMotion(D_00618E10);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy(D_00622840, i);
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(0x21, &D_0063BEAC, 1, 1, 0);

    scpPlayEnd(D_00639EA4);

    D_0063AA08 = 0;

    gflagOn(0x8D);
}

extern void stage_SetLoopFlag(int key, int a1);
extern void actSt04aGateOpen3Chk(volatile int a0);
extern ActMail D_004F8690[];

void actSt04aGateOpen3(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x8E) == 0) {
        stage_SetLoopFlag(0x22B, 0);

        while (stage_CheckAnimationFrame(0x22B, 1, 1) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        D_004F8690[0].func = actSt04aGateOpen3Chk;
        self->mail = D_004F8690;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetLoopFlag(0x22B, 0);

        while (stage_CheckAnimationFrame(0x22B, 1, 1) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
    }
}

extern void lt_switch_layout(int a0);
extern void scpPlayStart(char *a0);
extern void scpAdpcmFadeCloseFunc(int *handle, int mask);
extern void AdpcmPlay(int handle);
extern int actCreateSubThread(void *entry, int prio);
extern void actSt04aEnvSeWakare2(volatile int a0);
extern void actConte09_3(volatile int a0);
extern void actConte09_3Jimaku(volatile int a0);
extern int D_0063AA08;
extern int D_0063BEA8;
extern int D_0063BEAC;

void actSt04aGateOpen3Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (gflagChk(0x8D) == 0 || scpTriggerBall(a0, D_00639EA4, 450.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x8E);

    lt_switch_layout(0x37);

    D_0063AA08 = 1;
    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);

    if (D_0063BEA8 != 0) {
        scpAdpcmFadeCloseFunc(&D_0063BEA8, 0x50);
    }

    while (D_0063BEAC == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(D_0063BEAC + 0x2C));

    actCreateSubThread(actSt04aEnvSeWakare2, 0x15);
    actCreateSubThread(actConte09_3, 0x15);
    actCreateSubThread(actConte09_3Jimaku, 0x15);
}

ASM_LIT4_SLOT(D_00639900, 0.99f);
ASM_LIT4_SLOT(D_00639904, 0.1f);
ASM_LIT4_SLOT(D_00639908, 0.8f);
ASM_LIT4_SLOT(D_0063990C, 0.45f);
INCLUDE_ASM("asm/nonmatchings/src/st04a", actConte09_3);

typedef struct PadState {
    int unk00; /* 0x00 */
    int flags; /* 0x04 */
} PadState;

extern PadState D_0028F8F0[];
extern void preload(int idx);
extern void scpFadeIn(float t);
extern int scpFadeChk(void);
extern int lt_fade_status(void);
extern int scpAdpcmPlayRequestNum(void);
extern void iosThreadSetPri(int *th, int pri);
extern void scpAdpcmPlayRequestFunc(int a0, void *a1, int a2, int a3, int a4);
extern int RequestStageChange(int a0, char *a1, int a2, float a3, float a4);
extern void actSt04aGateLSub(volatile int a0);
extern int D_0063BEB0;
extern int D_0063C508;

void actSt04aGateLChk(volatile int a0)
{
    int *th;

    while (gflagChk(0xAE) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);

    D_0063AA08 = 1;
    gflagOn(0x8A);

    scpAdpcmPlayRequestFunc(0x1D, &D_0063BEB0, 1, 1, 1);
    while (D_0063BEB0 == 0) {
        _ACTWait(1);
    }

    preload(4);

    scpFadeIn(16.0f);

    th = (int *)actCreateSubThread(actSt04aGateLSub, 0x15);

    D_0063C508 = 0;

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    while (D_0063C508 == 0 &&
           ((D_0028F8F0[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 9, 0x22);

    if (D_0063C508 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&D_0063BEB0, 0x100);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(0x125, 0, -1);

        scpFadeIn(3.0f);
    }

    RequestStageChange(4, D_00639EA4, 0, 1.0f, 8.0f);
}

extern void fightSoundProcessRequestPause(void);
extern int fightSoundPlayChk(void);
extern void actSt04aGateRSub(volatile int a0);
extern int D_0063BEB4;

void actSt04aGateRChk(volatile int a0)
{
    int *th;
    int stage;

    while (gflagChk(0xEA) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);

    D_0063AA08 = 1;
    gflagOn(0x8B);

    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(0x1E, &D_0063BEB4, 1, 1, 1);
    while (D_0063BEB4 == 0) {
        _ACTWait(1);
    }

    if (gflagChk(0xF6) != 0) {
        stage = 5;
    } else if (gflagChk(0xF7) != 0) {
        stage = 6;
    } else if (gflagChk(0xF8) != 0) {
        stage = 9;
    } else if (gflagChk(0xF9) != 0) {
        stage = 7;
    } else if (gflagChk(0xE9) != 0) {
        stage = 8;
    } else {
        stage = 0;
    }

    preload(stage);

    scpFadeIn(16.0f);

    th = (int *)actCreateSubThread(actSt04aGateRSub, 0x15);

    D_0063C508 = 0;

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    while (D_0063C508 == 0 &&
           ((D_0028F8F0[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 9, 0x22);

    if (D_0063C508 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&D_0063BEB4, 0x100);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(0x127, 0, -1);

        scpFadeIn(3.0f);
    }

    RequestStageChange(stage, D_00639EA4, 0, 1.0f, 8.0f);
}

extern void SleepHint(int a0);
extern void scpTorchLightOn(int a0);
extern void actSt04aTorch1Chk(volatile int a0);
extern ActMail D_004F86F0[];

void actSt04aTorch1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x99) == 0) {
        SleepHint(6);
        SleepHint(4);

        if (gflagChk(0x91) != 0) {
            scpSearchGobj(0x233)->f16C = 0;
            stage_SetAnimation(0x11B, 0, -1);
        }

        if (gflagChk(0x92) != 0) {
            scpSearchGobj(0x234)->f16C = 0;
            stage_SetAnimation(0x11C, 0, -1);
        }

        if (gflagChk(0x93) != 0) {
            scpSearchGobj(0x235)->f16C = 0;
            stage_SetAnimation(0x11D, 0, -1);
        }

        if (gflagChk(0x94) != 0) {
            scpSearchGobj(0x236)->f16C = 0;
            stage_SetAnimation(0x11E, 0, -1);
        }

        if (gflagChk(0x95) != 0) {
            scpSearchGobj(0x237)->f16C = 0;
            stage_SetAnimation(0x11F, 0, -1);
        }

        if (gflagChk(0x96) != 0) {
            scpSearchGobj(0x238)->f16C = 0;
            stage_SetAnimation(0x120, 0, -1);
        }

        if (gflagChk(0x97) != 0) {
            scpSearchGobj(0x239)->f16C = 0;
            stage_SetAnimation(0x121, 0, -1);
        }

        if (gflagChk(0x98) != 0) {
            scpSearchGobj(0x23A)->f16C = 0;
            stage_SetAnimation(0x122, 0, -1);
        }

        D_004F86F0[0].func = actSt04aTorch1Chk;
        self->mail = D_004F86F0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        scpSearchGobj(0x233)->f16C = 0;
        scpSearchGobj(0x234)->f16C = 0;
        scpSearchGobj(0x235)->f16C = 0;
        scpSearchGobj(0x236)->f16C = 0;
        scpSearchGobj(0x237)->f16C = 0;
        scpSearchGobj(0x238)->f16C = 0;
        scpSearchGobj(0x239)->f16C = 0;
        scpSearchGobj(0x23A)->f16C = 0;

        stage_SetAnimation(0x11B, 0, -1);
        stage_SetAnimation(0x11C, 0, -1);
        stage_SetAnimation(0x11D, 0, -1);
        stage_SetAnimation(0x11E, 0, -1);
        stage_SetAnimation(0x11F, 0, -1);
        stage_SetAnimation(0x120, 0, -1);
        stage_SetAnimation(0x121, 0, -1);
        stage_SetAnimation(0x122, 0, -1);

        scpTorchLightOn(0x23B);
        scpTorchLightOn(0x23C);
        scpTorchLightOn(0x23D);
        scpTorchLightOn(0x23E);
        scpTorchLightOn(0x23F);
        scpTorchLightOn(0x240);
        scpTorchLightOn(0x241);
        scpTorchLightOn(0x242);
        scpTorchLightOn(0x243);
        scpTorchLightOn(0x244);
    }
}

extern void actSt04aTorchAllFlagfChk(volatile int a0);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);

void actSt04aTorch1Chk(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    switch (*(int *)(a0 + 8)) {
    case 0x22B:
        self->unk478 = 0x91;
        self->unk474 = scpSearchGobj(0x233);
        self->unk470 = 0x11B;
        actCreateSubThread(actSt04aTorchAllFlagfChk, 0x15);
        break;
    case 0x22C:
        self->unk478 = 0x92;
        self->unk474 = scpSearchGobj(0x234);
        self->unk470 = 0x11C;
        break;
    case 0x22D:
        self->unk478 = 0x93;
        self->unk474 = scpSearchGobj(0x235);
        self->unk470 = 0x11D;
        break;
    case 0x22E:
        self->unk478 = 0x94;
        self->unk474 = scpSearchGobj(0x236);
        self->unk470 = 0x11E;
        break;
    case 0x22F:
        self->unk478 = 0x95;
        self->unk474 = scpSearchGobj(0x237);
        self->unk470 = 0x11F;
        break;
    case 0x230:
        self->unk478 = 0x96;
        self->unk474 = scpSearchGobj(0x238);
        self->unk470 = 0x120;
        break;
    case 0x231:
        self->unk478 = 0x97;
        self->unk474 = scpSearchGobj(0x239);
        self->unk470 = 0x121;
        break;
    case 0x232:
        self->unk478 = 0x98;
        self->unk474 = scpSearchGobj(0x23A);
        self->unk470 = 0x122;
        break;
    }

    while (1) {
        if (scpTriggerBall(a0, self->unk474, 5.0f) != 0) {
            D_0063AA08 = 1;

            ((PObjGObj *)self->unk474)->f16C = 0;

            stage_SetAnimation(self->unk470, 1, 0);

            while (stage_CheckAnimationFrame(self->unk470, 2, 0) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);

            soundSeDefPlay(0x553, 0, 0, 1);

            while (stage_CheckAnimationFinish(self->unk470) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);

            gflagOn(self->unk478);

            D_0063AA08 = 0;
            break;
        }
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/st04a", actSt04aTorchAllFlagfChk);

extern int D_002A5580[];
extern void OverrideBrainStatusByGObj(int *b, void *gobj, float f8, float f10, float fC);

void actSt04aTorchHintChk(volatile int a0)
{
    while (gflagChk(0x9B) == 0) {
        _ACTWait(1);
    }

    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(0x233), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(0x234), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(0x235), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(0x236), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(0x237), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(0x238), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(0x239), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(0x23A), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(0x24F), 1.0f, 0.001f, 1.0f);

    if (gflagChk(0x9C) == 0) {
        _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0x14);
    }

    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(0x233), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(0x234), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(0x235), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(0x236), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(0x237), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(0x238), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(0x239), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(0x23A), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(0x24F), 2.0f, 0.01f, 1.0f);

    gflagOn(0x9C);
}

extern ActMail D_004F86B0[];
extern void actSt04aGateLChk(volatile int a0);

void actSt04aGateL(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x8A) == 0) {
        gflagOn(0x185);

        scpFadeOut(255.0f, 0, 0, 0);

        stage_SetAnimation(0x127, 0, 0);

        D_004F86B0[0].func = actSt04aGateLChk;
        self->mail = D_004F86B0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern ActMail D_004F86D0[];
extern void actSt04aGateRChk(volatile int a0);

void actSt04aGateR(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x8B) == 0) {
        gflagOn(0x185);

        scpFadeOut(255.0f, 0, 0, 0);

        stage_SetAnimation(0x125, 0, -1);

        D_004F86D0[0].func = actSt04aGateRChk;
        self->mail = D_004F86D0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actSt04aTorchXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    stage_SetAnimation(0x123, 0, 0);
}

void actSt04aDeadCam(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(0x8D) == 0 || scpTriggerBall(a0, D_00639EA4, 600.0f) == 0) {
        _ACTWait(1);
    }

    while (stage_CheckAnimationFrame(0x111, 1400, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(0x112, 1, 0);

    while (stage_CheckAnimationFinish(0x112) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

extern ActMail D_004F8670[];
extern void actSt04aGateOpen2Chk(volatile int a0);

void actSt04aGateOpen2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x8D) == 0) {
        scpSearchGobj(0x29D)->f16C = 0;

        D_004F8670[0].func = actSt04aGateOpen2Chk;
        self->mail = D_004F8670;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern ActMail D_004F8650[];
extern void actSt04aGateOpen2ReadyChk(volatile int a0);

void actSt04aGateOpen2Ready(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    D_004F8650[0].func = actSt04aGateOpen2ReadyChk;
    self->mail = D_004F8650;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern ActMail D_004F8710[];
extern void actSt04aGirlSitChk(volatile int a0);

void actSt04aGirlSit(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    D_004F8710[0].func = actSt04aGirlSitChk;
    self->mail = D_004F8710;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

extern ActMail D_004F8730[];
extern void actSt04aTorchHintChk(volatile int a0);

void actSt04aTorchHint(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x99) == 0) {
        D_004F8730[0].func = actSt04aTorchHintChk;
        self->mail = D_004F8730;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

extern ActMail D_004F8750[];
extern void actSt04aModelOnChk(volatile int a0);

void actSt04aModel(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    scpSearchGobj(0x288)->f16C = 0;

    D_004F8750[0].func = actSt04aModelOnChk;
    self->mail = D_004F8750;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

void actSt04aEnvSe(volatile int a0)
{
    float f = 0.0f;

    D_0063AA0C = 0.0f;

    for (;;) {
        float nf = f + (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f;
        if ((int)f != (int)nf) {
            _ACTWait(1);
            f = nf;
        } else {
            f = nf + 1.0f;
        }
        if ((int)f >= 5401) {
            D_0063AA0C += 1.0f / 1800.0f;
            if (D_0063AA0C > 1.0f) {
                D_0063AA0C = 1.0f;
                break;
            }
        }
    }
    _ACTWait(0);
}

void actSt04aEnvSeWakare1(volatile int a0)
{
    float f = 0.0f;

    D_0063AA0C = 0.0f;

    for (;;) {
        float nf = f + (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f;
        if ((int)f != (int)nf) {
            _ACTWait(1);
            f = nf;
        } else {
            f = nf + 1.0f;
        }
        if ((int)f >= 2201) {
            D_0063AA0C += 1.0f / 3800.0f;
            if (D_0063AA0C > 1.0f) {
                D_0063AA0C = 1.0f;
                break;
            }
        }
    }
    _ACTWait(0);
}

typedef struct {
    float m[16];
} Mtx44 __attribute__((aligned(16)));

typedef struct {
    float m[4];
} Vec4;

extern void _ApplyMatrix(int dst, int m, int src);
extern void _NormalizeVector(int dst, int src);
extern char D_0028FF20[];
extern Mtx44 D_004F8610;

void finishCallBackFunc(int a0)
{
    Vec4 v;
    int i;

    _ApplyMatrix((int)&v, *(int *)(*(int *)(a0 + 0x15C) + 0xC), (int)D_0028FF20);
    v.m[1] = 0.0f;
    _NormalizeVector(*(int *)(a0 + 0x15C) + 0x520, (int)&v);

    for (i = 0; i < *(int *)(*(int *)(a0 + 0x15C) + 0x88); i++) {
        *(Mtx44 *)(*(int *)(*(int *)(a0 + 0x15C) + 0x80C) + i * 64) = D_004F8610;
    }
}

extern char D_00618DE0[];
extern char D_00622840[];
extern void StandbyStreamMotion(char *a0);
extern int CheckReadyStreamMotion(void);
extern void scpAdpcmPlayRequestFunc(int a0, void *a1, int a2, int a3, int a4);
extern int D_0063BEA8;

void actSt04aGateOpen2ReadyChk(volatile int a0)
{
    int x = a0;
    int i;

    actInitialize(a0);
    _ACTWait(1);

    while (D_00639EA8 == 0 || scpTriggerFloorAttr(D_00639EA8, 0x2000000) == 0) {
        _ACTWait(1);
    }

    StandbyStreamMotion(D_00618DE0);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy(D_00622840, i);
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(0x20, &D_0063BEA8, 1, 0, 0);
}

void actSt04aEnvSeWakare2(volatile int a0)
{
    float f = 0.0f;

    for (;;) {
        float nf = f + (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f;
        if ((int)f != (int)nf) {
            _ACTWait(1);
            f = nf;
        } else {
            f = nf + 1.0f;
        }
        if ((int)f >= 2351) {
            D_0063AA0C -= 1.0f / 720.0f;
            if (D_0063AA0C < 0.0f) {
                D_0063AA0C = 0.0f;
                break;
            }
        }
    }
    _ACTWait(0);
}

extern JimakuArg jimaku_msg;
extern int jimakuOn;
extern void jimakuBegin(int a0);
extern void jimakuJump(int a0);

void actConte09_3Jimaku(volatile int a0)
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
        case 2470:
            jimaku_msg.sub.unk2C = 91;
            jimaku_msg.sub.unk38 = 300;
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
    } while (t < 3000.0f);
}

extern void _ACTWait(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int D_0063C508;

void actConte09_3_demoCancel(volatile int a0)
{
    while (1) {
        _ACTWait(1);
    }
}

void actSt04aGateLSub(volatile int a0)
{
    stage_SetAnimation(0x125, 1, 0);
    while (stage_CheckAnimationFinish(0x125) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0063C508 = 1;
    _ACTWait(0);
}

void actSt04aGateRSub(volatile int a0)
{
    stage_SetAnimation(0x127, 1, 0);
    while (stage_CheckAnimationFinish(0x127) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0063C508 = 1;
    _ACTWait(0);
}

void actSt04aGirlSitChk(volatile int a0)
{
    int n;

    while (gflagChk(0x8C) == 0) {
        _ACTWait(1);
    }
    ((ActStatus *)(*(char **)(D_00639EA8 + 0x164) + 0x20))->ll |= 0x10000;
    n = 0;
    for (;;) {
        if ((int)(*(unsigned long long *)(*(char **)(D_00639EA8 + 0x164) + 0x20) >> 20) & 1) {
            n++;
        } else {
            n = 0;
        }
        if (((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) * 3 < n) {
            iosOmSendMail(D_00639EA8, 0x6D, D_00639EA8);
            n = 0;
        }
        _ACTWait(1);
    }
}

/* The model-on watcher's mail record: it installs actSt04aModelOffChk here
   and posts it. Word 0 of each entry is the mail id the entry answers (0x1AE
   the actor post, 0x1AD the trailing entry); .func is filled in at run time.
   Named for the thread that owns and posts it. */
static ActMail model_on[2] = {{0x1AE}, {0x1AD}};

extern void actSt04aModelOffChk(volatile int a0);

void actSt04aModelOnChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttr(D_00639EA4, 0x3000000) != 0) {
        _ACTWait(1);
    }

    scpSearchGobj(0x288)->f16C = 1;

    model_on[0].func = actSt04aModelOffChk;
    sub->mail = model_on;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

/* The model-off watcher's own mail record (installs actSt04aModelOnChk). */
static ActMail model_off[2] = {{0x1AE}, {0x1AD}};

extern void actSt04aModelOnChk(volatile int a0);

void actSt04aModelOffChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttr(D_00639EA4, 0x3000000) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(0x288)->f16C = 0;

    model_off[0].func = actSt04aModelOnChk;
    sub->mail = model_off;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
