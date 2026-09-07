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
    int act;                    /* 0x164 */
    char pad168[0x4];           /* 0x168 */
    int f16C;                   /* 0x16C */
} PObjGObj;

extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void FinishHint(int a0);
extern void gflagOn(int a0);
extern void debug_StdPrintfDummy(char *fmt, ...);
extern int scpTriggerFloorAttr(int a0, int a1);
extern int scpTriggerBall(int a0, int a1, float radius);
extern int D_00639EA4;
extern int D_00639EAC;
extern int D_0063C570;
extern void lt_switch_layout(int a0);
extern void gflagOff(int a0);
extern int stage_CheckAnimationFinish(int a0);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern void soundSeDefStop(int handle);
extern void iosPadActRequest(int a0, int a1);

/* st09a.o's own .rodata run 0x00622DA0..0x00622DE0 (no MAIN.MAP symbols):
   the two hint-finished debug strings. */
extern char D_00622DA0[];
extern char D_00622DC0[];
extern int gflagChk(int a0);
extern int D_0063AA08;
extern Act *actInitialize(int a0);
extern int soundSeDefPlay(int se, int a1, float *pos, int a3);
extern void scpSekizou(int a0, int a1, int a2, int a3, int a4,
                       float x1, float y1, float z1,
                       float x2, float y2, float z2);

extern void actSt09aBrgDown(volatile int a0);
extern void actSt09aBrgMain(volatile int a0);
extern void actSt09aElvMain(volatile int a0);
extern void actSt09aIntroChk(volatile int a0);
extern void actSt09aHint1Chk(volatile int a0);
extern void actSt09aHint2Chk(volatile int a0);

/* st09a.o's own .data run 0x004FA2F0..0x004FA480 (no MAIN.MAP symbols):
   actor mail packets. */
extern ActMail D_004FA310[];
extern ActMail D_004FA390[];
extern float D_004FA3B0[];   /* the sekizou SE position, (1548, -412, -608) */
extern ActMail D_004FA3C0[];
extern ActMail D_004FA3E0[];
extern ActMail D_004FA2F0[];
extern ActMail D_004FA330[];
extern ActMail D_004FA350[];
extern void actSt09aElvUp(volatile int a0);
extern void actSt09aElvDown(volatile int a0);
extern ActMail D_004FA400[];
extern ActMail D_004FA420[];
extern ActMail D_004FA440[];
extern ActMail D_004FA460[];

INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aInit);
INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aElvDown);
INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aBrgDown);
void actSt09aElv(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x53) != 0) {
        stage_SetAnimation(0x177, 0, 0xD2);
    } else {
        stage_SetAnimation(0x177, 0, 0);
    }

    D_004FA310[0].func = actSt09aElvMain;
    self->mail = D_004FA310;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt09aSekizo(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    soundSeDefPlay(0x542, 0, D_004FA3B0, 1);
    soundSeDefPlay(0x543, 0, D_004FA3B0, 1);
    soundSeDefPlay(0x544, 0, D_004FA3B0, 1);

    scpSekizou(a0, 0x54, 0x178, 0, 0x12,
               -1350.0f, -100.0f, 1515.0f,
               -1450.0f, -100.0f, 1515.0f);
}
void actSt09aIntro(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x55) == 0) {
        D_004FA3C0[0].func = actSt09aIntroChk;
        self->mail = D_004FA3C0;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt09aBrg(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x56) == 0) {
        D_004FA400[0].func = actSt09aBrgMain;
        self->mail = D_004FA400;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}
void actSt09aHint1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x57) == 0) {
        D_004FA440[0].func = actSt09aHint1Chk;
        self->mail = D_004FA440;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        FinishHint(0xA);
    }
}
void actSt09aHint2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x58) == 0) {
        D_004FA460[0].func = actSt09aHint2Chk;
        self->mail = D_004FA460;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        FinishHint(0xB);
    }
}
void actSt09aElvMain(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 0;

    sub->mainMail = D_004FA2F0;

    while (1) {
        _ACTWait(1);
    }
}
void actSt09aElvSwitch(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    if (gflagChk(0x53) != 0) {
        D_004FA330[0].func = actSt09aElvUp;
        sub->mail = D_004FA330;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }

    D_004FA350[0].func = actSt09aElvDown;
    sub->mail = D_004FA350;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt09aElvUp(volatile int a0)
{
    Act *self = (Act *)((PObjGObj *)a0)->act;
    /* sound handle owned by the sound subsystem: ROM homes it at 4(sp)
       across the animation wait and reloads it for soundSeDefStop. */
    volatile int se;

    lt_switch_layout(0x37);

    stage_SetAnimation(0x177, 1, 0xD3);

    se = soundSeDefPlay(0x4C1, 0, 0, 1);

    gflagOff(0x53);

    while (stage_CheckAnimationFrame(0x177, 0x1A4, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefStop(se);

    lt_switch_layout(0x36);

    D_004FA390[0].func = actSt09aElvMain;
    self->mail = D_004FA390;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt09aSekizoEvent(int x) {
    volatile int local = x;
}
void actSt09aIntroChk(volatile int a0)
{
    lt_switch_layout(0x37);
    gflagOn(0x55);

    D_0063AA08 = 1;
    _ACTWait(1);

    stage_SetAnimation(0x179, 1, 0);

    while (stage_CheckAnimationFinish(0x179) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(0x36);

    D_0063AA08 = 0;
}
void actSt09aBrgMain(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    sub->mainMail = D_004FA3E0;

    while (1) {
        _ACTWait(1);
    }
}
void actSt09aBrgSwitch(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    D_004FA420[0].func = actSt09aBrgDown;
    sub->mail = D_004FA420;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
void actSt09aBrgDownSub(volatile int a0)
{
    stage_SetAnimation(0x17A, 1, 0);

    while (stage_CheckAnimationFrame(0x17A, 0x73, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFrame(0x17A, 0xA5, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_CheckAnimationFinish(0x17A) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C570 = 1;
    _ACTWait(0);
}
void actSt09aHint1Chk(volatile int a0)
{
    while (scpTriggerFloorAttr(D_00639EA4, 0x1000000) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy(D_00622DA0);

    gflagOn(0x57);
    FinishHint(0xA);
}
void actSt09aHint2Chk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 400.0f) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy(D_00622DC0);

    gflagOn(0x58);
    FinishHint(0xB);
}
