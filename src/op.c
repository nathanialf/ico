#include "common.h"

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
extern void lt_switch_layout(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void actOpDemo03Chk(int a0);
extern ActMail D_004F7E30[];
extern int D_0063AA08;
extern int D_0028F4C0[];
extern void stgmgrNextStagePreLoadForceNoCancel(int a0);
extern void stgmgrNextStagePreLoadForceStageSet(int a0);
extern int gflagChk(int a0);
extern void gflagOn(int a0);
extern void debug_StdPrintfDummy(char *a0);
extern int RequestStageChange(int a0, char *a1, int a2, float a3, float a4);
extern char *D_00639EA4;
extern char D_00622680[];
extern char D_00622690[];
typedef struct PadState {
    int unk00;                  /* 0x00 */
    int flags;                  /* 0x04 */
    char unk08[0x50];           /* 0x08 */
} PadState;
extern PadState D_0028F8F0[];
extern int actCreateSubThread(void *entry, int prio);
extern void actSt24aConte01_2(int a0);
extern int scpAdpcmPlayRequestNum(void);
extern void scpAdpcmFadeCloseFunc(int *handle, int mask);
extern int D_0063C4F0;
extern int D_0063C4F4;
extern int D_0063BE60;
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
/* prototypes: their order is the inline tail's emission order */
void actOpDemo03(volatile int a0);
void actSubMpegReturnPreload(volatile int a0);
void actSt26aConte01_1_newgame(volatile int a0);
void actOpDemo02Chk(volatile int a0);
void actSt24aConte01_2_Jimaku(volatile int a0);
inline void actSubMpegReturnPreload(volatile int a0) {
    _ACTWait((int)((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) * 5.0f));
    stgmgrNextStagePreLoadForceStageSet(1);
    stgmgrNextStagePreLoadForceNoCancel(1);
}
INCLUDE_ASM("asm/nonmatchings/src/op", actTitleReadTimeDemo0);
inline void actSt26aConte01_1_newgame(volatile int a0) {
    _ACTWait(1);

    while (gflagChk(0x17E) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy(D_00622680);

    debug_StdPrintfDummy(D_00622690);

    gflagOn(2);

    RequestStageChange(1, D_00639EA4, 0, 0.25f, 2.0f);
}
INCLUDE_ASM("asm/nonmatchings/src/op", actOpDemo01_2);
INCLUDE_ASM("asm/nonmatchings/src/op", actOpDemo01_2Chk);
INCLUDE_ASM("asm/nonmatchings/src/op", actOpDemo02);
inline void actOpDemo02Chk(volatile int a0) {
    gflagOn(3);

    actCreateSubThread(actSt24aConte01_2, 0x15);

    actCreateSubThread(actSt24aConte01_2_Jimaku, 0x15);

    D_0063C4F0 = 0;
    while (D_0063C4F0 == 0) {
        if ((D_0028F8F0[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            break;
        }
        _ACTWait(1);
    }

    if (D_0063C4F0 == 0) {
        if (D_0063C4F4 != 0) {
            scpAdpcmFadeCloseFunc(&D_0063C4F4, 0x200);
        }
        if (D_0063BE60 != 0) {
            scpAdpcmFadeCloseFunc(&D_0063BE60, 0x40);
        }
    }

    RequestStageChange(2, D_00639EA4, 0, 0.5f, 4.0f);
}
INCLUDE_ASM("asm/nonmatchings/src/op", actSt24aConte01_2);
inline void actSt24aConte01_2_Jimaku(volatile int a0) {
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 100:
            jimakuBegin((int)&jimaku_msg);
            break;
        case 2400:
            jimaku_msg.sub.unk2C = 0;
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
}
inline void actOpDemo03(volatile int a0) {
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    stage_SetAnimation(0xB0, 0, 0);
    stage_SetAnimation(0xAC, 0, 0);

    D_004F7E30[0].func = actOpDemo03Chk;
    self->mail = D_004F7E30;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}
INCLUDE_ASM("asm/nonmatchings/src/op", actOpDemo03Chk);
INCLUDE_ASM("asm/nonmatchings/src/op", actSt13aConte01_3);
