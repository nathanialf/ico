#include "common.h"

/* The TU starts at 0x0021F060, where MAIN.MAP puts op.o: these three sit before
   the functions the listing hashes named. */
typedef struct ActMail {
    int mail;          /* 0x00 */
    void (*func)(int); /* 0x04 */
    int unk08;         /* 0x08 */
    int unk0C;         /* 0x0C */
} ActMail;

typedef struct Act {
    char unk00[0xD4]; /* 0x00 */
    ActMail *mail;    /* 0xD4 */
} Act;

/* the three functions at the head of the TU need their callees declared here,
   above their definitions; the TU's own declaration block below repeats them */
extern Act *actInitialize(int a0);
extern void _ACTWait(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int D_0063ABA8;
extern void *D_0063BE6C;
extern int D_0063C4E8;
extern void SetHandCameraLimitInDemo(int a0, int a1);
extern void SetZoomMaxValInDemo(int a0);
extern char *D_00639EA4;
extern void scpPlayStart(char *gobj);
extern char *scpSearchGobj(int id);
extern int stage_CheckAnimationFinish(int a0);
extern void scpFadeIn(float t);
extern void scpAdpcmPlayRequestFunc(int kind, void *id, int a2, int a3, int a4);
extern int enable_game_pause;
extern int D_0063BE68;

void actTitleCamera2(volatile int a0)
{
    int x = a0;

    enable_game_pause = 1;

    D_0063BE68 = 0;
    actInitialize(a0);
    _ACTWait(1);

    while (1) {
        switch (D_0063BE68) {
        case 1:
            stage_SetAnimation(0, 1, 0);
            while (stage_CheckAnimationFinish(0) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            while (D_0063BE68 == 1) {
                _ACTWait(1);
            }
            break;

        case 2:
            stage_SetAnimation(2, 1, 0);
            while (stage_CheckAnimationFinish(2) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            while (D_0063BE68 == 2) {
                _ACTWait(1);
            }
            break;

        case 0:
            stage_SetAnimation(2, 0, -1);
            while (D_0063BE68 == 0) {
                _ACTWait(1);
            }
            break;

        default:
            _ACTWait(1);
            break;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/script/src/op", actOpDemo01);

void actTitleShortCut(volatile int a0)
{
    int x = a0;

    D_0063ABA8 = 1;
    actInitialize(a0);
    _ACTWait(1);

    if (D_00639EA4 != 0) {
        scpPlayStart(D_00639EA4);
    }
    if (D_0063BE6C == 0) {
        scpAdpcmPlayRequestFunc(0x38, &D_0063BE6C, 0, 0, 1);
    }
    stage_SetAnimation(0x23B, 1, 0x547);

    SetHandCameraLimitInDemo(0, 0);
    SetZoomMaxValInDemo(0);

    *(int *)(scpSearchGobj(43) + 0x16C) = 1;
    *(int *)(scpSearchGobj(44) + 0x16C) = 1;
    *(int *)(scpSearchGobj(45) + 0x16C) = 1;
    *(int *)(scpSearchGobj(48) + 0x16C) = 1;
    *(int *)(scpSearchGobj(49) + 0x16C) = 1;
    *(int *)(scpSearchGobj(50) + 0x16C) = 1;
    *(int *)(scpSearchGobj(51) + 0x16C) = 1;

    while (D_0063BE6C != 0) {
        _ACTWait(1);
    }

    scpFadeIn(3.0f);

    while (stage_CheckAnimationFinish(0x23B) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C4E8 = 1;
    _ACTWait(0);
}

extern Act *actInitialize(int a0);
extern void _ACTWait(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern void lt_switch_layout(int a0);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void actOpDemo03Chk(int a0);
extern ActMail D_004F7E10[];
extern ActMail D_004F7E30[];
extern int D_0063AA08;
extern int D_0028F4C0[];
extern void stgmgrNextStagePreLoadForceNoCancel(int a0);
extern void stgmgrNextStagePreLoadForceStageSet(int a0);
extern int gflagChk(int a0);
extern void gflagOn(int a0);
/* the retail build's printf stub; the 2001 declaration was unprototyped, which
   is why the extra arguments still travel in $a1/$a2 rather than on the stack */
extern void debug_StdPrintfDummy();
extern int frame_count;
extern char D_00622630[];
extern char D_00622648[];
extern char D_00622658[];
extern char D_00622668[];
extern int D_0063ABA8;
extern int D_0063BE68;
extern void *D_0063BE6C;
extern int D_0063C4E8;
extern int D_0063C4EC;
extern void ResetHandCameraLimitInDemo(void);
extern void ResetZoomMaxValInDemo(void);
extern void SetHandCameraLimitInDemo(int a0, int a1);
extern void SetZoomMaxValInDemo(int a0);
extern int RequestStageChange(int a0, char *a1, int a2, float a3, float a4);
extern char *D_00639EA4;
extern char D_00622680[];
extern char D_00622690[];

typedef struct PadState {
    int unk00;        /* 0x00 */
    int flags;        /* 0x04 */
    char unk08[0x50]; /* 0x08 */
} PadState;

extern PadState D_0028F8F0[];
extern int actCreateSubThread(void *entry, int prio);
extern void actOpDemo01_2Chk(int a0);
extern void scpPlayStart(char *gobj);
extern char *scpSearchGobj(int id);
extern int stage_ContinueAnimation(int a0, int a1);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern int stage_CheckAnimationFinish(int a0);
extern int stage_no;

/* the 0x194-byte per-stage record; the cutscene entries read their exit index
   out of `ent`.  The leading padding is spelled `int` so the record is 4-byte
   aligned: at 2-byte alignment gcc folds the member offset into the array base
   before the index add, which swaps which of the two values ends up in $a1 and
   which in $a2. */
typedef struct {
    int _0[0x28];
    short ent[0x18];
    char _d0[0xC4];
} StgPre;

/* Both tables live in the ELF's .rodata run, so `const` is what they are, and
   on D_005F5D50 it is load-bearing: only a reference rooted at a const object
   makes the `ent` load unchanging, and only then is that load free of the
   `volatile int a0` parameter home's memory dependence, which is what lets the
   home store issue three slots later. */
extern const StgPre D_005F5D50[];

typedef struct {
    float pos[3];
    float rot[3];
    int f_18;
    int f_1C;
    int f_20;
    int f_24;
} ExitData;

extern const ExitData D_0055C518[];
extern void actSt13aConte01_3(int a0);
extern int scpFadeChk(void);
extern void scpPlayMot(char *self, int mot);
extern void scpFadeOut(int a0, int a1, int a2, float t);
extern void scpFadeIn(float t);
extern int RequestStageChangeWithColor(int a0, char *a1, int a2, float a3, float a4, int r, int g,
                                       int b);
extern int D_0063BE64;
extern void scpAdpcmPlayRequestFunc(int kind, void *id, int a2, int a3, int a4);
extern void actSt24aConte01_2(int a0);
extern int scpAdpcmPlayRequestNum(void);
extern void scpAdpcmFadeCloseFunc(int *handle, int mask);
extern int D_0063C4F0;
extern int D_0063C4F4;
extern int D_0063BE60;

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
/* prototypes: their order is the inline tail's emission order */
void actOpDemo03(volatile int a0);
void actSubMpegReturnPreload(volatile int a0);
void actSt26aConte01_1_newgame(volatile int a0);
void actOpDemo02Chk(volatile int a0);
void actSt24aConte01_2_Jimaku(volatile int a0);

inline void actSubMpegReturnPreload(volatile int a0)
{
    _ACTWait((int)((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) * 5.0f));
    stgmgrNextStagePreLoadForceStageSet(1);
    stgmgrNextStagePreLoadForceNoCancel(1);
}

void actTitleReadTimeDemo0(volatile int a0)
{
    debug_StdPrintfDummy(D_00622630, frame_count);

    stage_SetAnimation(2, 0, -1);

    D_0063ABA8 = 0;

    _ACTWait(1);
    lt_switch_layout(0x37);

    _ACTWait(1);

    *(int *)(scpSearchGobj(43) + 0x16C) = 0;
    *(int *)(scpSearchGobj(44) + 0x16C) = 0;
    *(int *)(scpSearchGobj(45) + 0x16C) = 0;
    *(int *)(scpSearchGobj(48) + 0x16C) = 0;
    *(int *)(scpSearchGobj(49) + 0x16C) = 0;
    *(int *)(scpSearchGobj(50) + 0x16C) = 0;
    *(int *)(scpSearchGobj(51) + 0x16C) = 0;

    *(int *)(scpSearchGobj(46) + 0x16C) = 1;

    scpAdpcmPlayRequestFunc(6, &D_0063C4EC, 1, 1, 1);
    while (D_0063C4EC == 0) {
        _ACTWait(1);
    }

    scpFadeIn(3.0f);

    ResetHandCameraLimitInDemo();
    ResetZoomMaxValInDemo();

    stage_SetAnimation(563, 1, 0);

    while (stage_ContinueAnimation(563, 564) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(59), 1051);
    *(int *)(scpSearchGobj(59) + 0x16C) = 1;
    scpPlayMot(scpSearchGobj(60), 1058);
    *(int *)(scpSearchGobj(60) + 0x16C) = 1;
    scpPlayMot(scpSearchGobj(61), 1065);
    *(int *)(scpSearchGobj(61) + 0x16C) = 1;

    while (stage_ContinueAnimation(564, 565) == 0) {
        _ACTWait(1);
    }

    scpPlayStart(D_00639EA4);

    scpPlayMot(D_00639EA4, 263);

    scpPlayMot(scpSearchGobj(56), 983);
    *(int *)(scpSearchGobj(56) + 0x16C) = 1;
    scpPlayMot(scpSearchGobj(57), 1005);
    *(int *)(scpSearchGobj(57) + 0x16C) = 1;
    scpPlayMot(scpSearchGobj(58), 1028);
    *(int *)(scpSearchGobj(58) + 0x16C) = 1;
    scpPlayMot(scpSearchGobj(59), 1052);
    scpPlayMot(scpSearchGobj(60), 1059);
    scpPlayMot(scpSearchGobj(61), 1066);

    while (stage_ContinueAnimation(565, 566) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 264);
    scpPlayMot(scpSearchGobj(56), 984);
    scpPlayMot(scpSearchGobj(57), 1006);
    scpPlayMot(scpSearchGobj(58), 1029);
    scpPlayMot(scpSearchGobj(59), 1053);
    scpPlayMot(scpSearchGobj(60), 1060);
    scpPlayMot(scpSearchGobj(61), 1067);

    while (stage_CheckAnimationFrame(566, 60, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    *(int *)(scpSearchGobj(60) + 0x16C) = 0;
    *(int *)(scpSearchGobj(57) + 0x16C) = 0;

    while (stage_ContinueAnimation(566, 567) == 0) {
        _ACTWait(1);
    }

    *(int *)(scpSearchGobj(60) + 0x16C) = 1;
    *(int *)(scpSearchGobj(57) + 0x16C) = 1;

    scpPlayMot(D_00639EA4, 265);
    scpPlayMot(scpSearchGobj(56), 985);
    scpPlayMot(scpSearchGobj(57), 1007);
    scpPlayMot(scpSearchGobj(58), 1030);
    scpPlayMot(scpSearchGobj(59), 1054);
    scpPlayMot(scpSearchGobj(60), 1061);
    scpPlayMot(scpSearchGobj(61), 1068);

    while (stage_CheckAnimationFrame(567, 90, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    *(int *)(scpSearchGobj(54) + 0x16C) = 0;

    while (stage_ContinueAnimation(567, 568) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(56), 986);
    scpPlayMot(scpSearchGobj(57), 1008);
    scpPlayMot(scpSearchGobj(58), 1031);
    scpPlayMot(scpSearchGobj(59), 1055);
    scpPlayMot(scpSearchGobj(60), 1062);
    scpPlayMot(scpSearchGobj(61), 1069);

    _ACTWait(1);

    *(int *)(scpSearchGobj(57) + 0x16C) = 0;

    while (stage_ContinueAnimation(568, 569) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 267);
    scpPlayMot(scpSearchGobj(56), 987);
    scpPlayMot(scpSearchGobj(57), 1009);
    scpPlayMot(scpSearchGobj(58), 1032);
    scpPlayMot(scpSearchGobj(59), 1056);
    scpPlayMot(scpSearchGobj(60), 1063);
    scpPlayMot(scpSearchGobj(61), 1070);

    _ACTWait(1);

    *(int *)(scpSearchGobj(54) + 0x16C) = 1;
    *(int *)(scpSearchGobj(57) + 0x16C) = 1;

    *(int *)(scpSearchGobj(43) + 0x16C) = 1;
    *(int *)(scpSearchGobj(44) + 0x16C) = 1;
    *(int *)(scpSearchGobj(45) + 0x16C) = 1;
    *(int *)(scpSearchGobj(48) + 0x16C) = 1;
    *(int *)(scpSearchGobj(49) + 0x16C) = 1;
    *(int *)(scpSearchGobj(50) + 0x16C) = 1;
    *(int *)(scpSearchGobj(51) + 0x16C) = 1;

    *(int *)(scpSearchGobj(46) + 0x16C) = 0;

    while (stage_ContinueAnimation(569, 571) == 0) {
        _ACTWait(1);
    }

    SetHandCameraLimitInDemo(0, 0);
    SetZoomMaxValInDemo(0);

    scpPlayMot(D_00639EA4, 268);
    scpPlayMot(scpSearchGobj(56), 988);
    scpPlayMot(scpSearchGobj(57), 1010);
    scpPlayMot(scpSearchGobj(58), 1033);
    scpPlayMot(scpSearchGobj(59), 1057);
    scpPlayMot(scpSearchGobj(60), 1064);
    scpPlayMot(scpSearchGobj(61), 1071);

    debug_StdPrintfDummy(D_00622648, frame_count);

    debug_StdPrintfDummy(D_00622658, frame_count);

    _ACTWait(900);

    _ACTWait(1000);

    D_0063BE68 = 1;
    while (stage_CheckAnimationFrame(571, 1300, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063ABA8 = 1;

    debug_StdPrintfDummy(D_00622668, frame_count, gflagChk(386));

    lt_switch_layout(12);

    if (D_0063BE6C == 0) {
        scpAdpcmPlayRequestFunc(0x38, &D_0063BE6C, 0, 0, 1);
    }
    D_0063C4E8 = 1;

    _ACTWait(0);
}

inline void actSt26aConte01_1_newgame(volatile int a0)
{
    _ACTWait(1);

    while (gflagChk(0x17E) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy(D_00622680);

    debug_StdPrintfDummy(D_00622690);

    gflagOn(2);

    RequestStageChange(1, D_00639EA4, 0, 0.25f, 2.0f);
}

void actOpDemo01_2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    scpFadeOut(0, 0, 0, 255.0f);

    D_0063BE64 = 0;
    D_0063BE60 = 0;

    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    scpAdpcmPlayRequestFunc(7, &D_0063BE64, 0, 0, 1);
    while (D_0063BE64 != 0) {
        _ACTWait(1);
    }
    scpFadeIn(2.0f);

    actCreateSubThread(actOpDemo01_2Chk, 0x15);

    D_0063C4F0 = 0;
    while (D_0063C4F0 == 0) {
        if ((D_0028F8F0[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            break;
        }
        _ACTWait(1);
    }

    if (D_0063BE64 != 0) {
        scpAdpcmFadeCloseFunc(&D_0063BE64, 0x80);
    }

    RequestStageChangeWithColor(1, D_00639EA4, 0, 1.0f, 4.0f, 255, 255, 255);
}

void actOpDemo01_2Chk(volatile int a0)
{
    stgmgrNextStagePreLoadForceStageSet(0);

    scpPlayStart(D_00639EA4);

    stage_SetAnimation(572, 1, 0);

    stgmgrNextStagePreLoadForceStageSet(D_0055C518[D_005F5D50[stage_no].ent[0]].f_24);

    stage_SetAnimation(7, 1, 0);

    scpPlayMot(D_00639EA4, 269);
    scpPlayMot(scpSearchGobj(2312), 989);
    *(int *)(scpSearchGobj(2312) + 0x16C) = 1;
    scpPlayMot(scpSearchGobj(2313), 1011);
    *(int *)(scpSearchGobj(2313) + 0x16C) = 1;
    scpPlayMot(scpSearchGobj(2314), 1034);
    *(int *)(scpSearchGobj(2314) + 0x16C) = 1;

    while (stage_ContinueAnimation(572, 573) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 270);
    scpPlayMot(scpSearchGobj(2312), 990);
    scpPlayMot(scpSearchGobj(2313), 1012);
    scpPlayMot(scpSearchGobj(2314), 1035);

    _ACTWait(1);

    stage_SetAnimation(8, 1, 0);

    while (stage_CheckAnimationFrame(573, 340, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpFadeOut(255, 255, 255, 3.0f);
    while (scpFadeChk() != 0) {
        _ACTWait(45);
    }
    stage_SetAnimation(573, -1, -2);
    scpFadeIn(3.0f);

    stage_SetAnimation(574, 1, 0);

    scpAdpcmPlayRequestFunc(10, &D_0063BE60, 0, 1, 1);

    stage_SetAnimation(9, 1, 0);

    scpPlayMot(D_00639EA4, 271);
    scpPlayMot(scpSearchGobj(2312), 991);
    scpPlayMot(scpSearchGobj(2313), 1013);
    scpPlayMot(scpSearchGobj(2314), 1036);

    while (stage_ContinueAnimation(574, 575) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 272);
    scpPlayMot(scpSearchGobj(2312), 992);
    scpPlayMot(scpSearchGobj(2313), 1014);
    scpPlayMot(scpSearchGobj(2314), 1037);

    _ACTWait(1);

    stage_SetAnimation(10, 1, 0);

    while (stage_CheckAnimationFinish(575) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C4F0 = 1;
}

void actOpDemo02(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (D_00639EA4 != 0) {
        scpPlayMot(D_00639EA4, 0);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    stage_SetAnimation(0x97, 0, 0);

    scpAdpcmPlayRequestFunc(8, &D_0063C4F4, 0, 1, 1);
    while (D_0063C4F4 == 0) {
        _ACTWait(1);
    }

    if (D_0063BE60 == 0) {
        scpAdpcmPlayRequestFunc(10, &D_0063BE60, 0, 1, 1);
    }

    D_004F7E10[0].func = actOpDemo02Chk;
    self->mail = D_004F7E10;
    ACTSendMailCorrect(a0, 0x1AE);
    _ACTWait(0);
}

inline void actOpDemo02Chk(volatile int a0)
{
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

void actSt24aConte01_2(volatile int a0)
{
    stgmgrNextStagePreLoadForceStageSet(D_0055C518[D_005F5D50[stage_no].ent[1]].f_24);

    scpPlayStart(D_00639EA4);

    stage_SetAnimation(576, 1, 0);

    stage_SetAnimation(11, 1, 0);

    scpPlayMot(D_00639EA4, 273);

    scpPlayMot(scpSearchGobj(2336), 993);
    *(int *)(scpSearchGobj(2336) + 0x16C) = 1;
    scpPlayMot(scpSearchGobj(2337), 1015);
    *(int *)(scpSearchGobj(2337) + 0x16C) = 1;
    scpPlayMot(scpSearchGobj(2338), 1038);
    *(int *)(scpSearchGobj(2338) + 0x16C) = 1;

    while (stage_ContinueAnimation(576, 577) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 274);
    scpPlayMot(scpSearchGobj(2336), 994);
    scpPlayMot(scpSearchGobj(2337), 1016);

    scpPlayMot(scpSearchGobj(2338), 1041);

    _ACTWait(1);

    stage_SetAnimation(12, 1, 0);

    _ACTWait(120);

    stage_SetAnimation(151, 1, 0);

    while (stage_ContinueAnimation(577, 578) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 275);
    scpPlayMot(scpSearchGobj(2336), 995);
    scpPlayMot(scpSearchGobj(2337), 1017);
    scpPlayMot(scpSearchGobj(2338), 1039);

    _ACTWait(1);

    stage_SetAnimation(13, 1, 0);

    while (stage_ContinueAnimation(578, 579) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 276);
    scpPlayMot(scpSearchGobj(2336), 996);
    scpPlayMot(scpSearchGobj(2337), 1018);
    scpPlayMot(scpSearchGobj(2338), 1040);

    _ACTWait(1);

    stage_SetAnimation(14, 1, 0);

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0xA);

    scpFadeOut(0, 0, 0, 6.0f);
    while (scpFadeChk() != 0) {
        _ACTWait(45);
    }
    stage_SetAnimation(579, -1, -2);
    scpFadeIn(3.0f);

    stage_SetAnimation(580, 1, 0);

    stage_SetAnimation(15, 0, 0);

    scpPlayMot(D_00639EA4, 277);
    scpPlayMot(scpSearchGobj(2336), 997);
    scpPlayMot(scpSearchGobj(2337), 1019);
    scpPlayMot(scpSearchGobj(2338), 1041);

    while (stage_CheckAnimationFinish(580) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C4F0 = 1;
}

inline void actSt24aConte01_2_Jimaku(volatile int a0)
{
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

inline void actOpDemo03(volatile int a0)
{
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

void actOpDemo03Chk(volatile int a0)
{
    float t = 4.0f;

    gflagOn(4);

    scpFadeOut(0, 0, 0, 255.0f);

    scpAdpcmPlayRequestFunc(9, &D_0063BE60, 0, 1, 1);
    while (D_0063BE60 == 0) {
        _ACTWait(1);
    }
    scpFadeIn(3.0f);

    actCreateSubThread(actSt13aConte01_3, 0x15);

    D_0063C4F0 = 0;
    while (D_0063C4F0 == 0) {
        if ((D_0028F8F0[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            break;
        }
        _ACTWait(1);
    }

    if (D_0063C4F0 == 0) {
        if (D_0063BE60 != 0) {
            scpAdpcmFadeCloseFunc(&D_0063BE60, 0x80);
            t = 16.0f;
        }
    }

    scpFadeOut(0, 0, 0, t);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    RequestStageChange(4, D_00639EA4, 0, 255.0f, 2.0f);
}

void actSt13aConte01_3(volatile int a0)
{
    stgmgrNextStagePreLoadForceStageSet(D_0055C518[D_005F5D50[stage_no].ent[3]].f_24);

    scpPlayStart(D_00639EA4);

    stage_SetAnimation(581, 1, 0);

    scpPlayMot(D_00639EA4, 278);
    scpPlayMot(scpSearchGobj(2364), 998);
    *(int *)(scpSearchGobj(2364) + 0x16C) = 1;
    scpPlayMot(scpSearchGobj(2365), 1020);
    *(int *)(scpSearchGobj(2365) + 0x16C) = 1;
    scpPlayMot(scpSearchGobj(2366), 1042);
    *(int *)(scpSearchGobj(2366) + 0x16C) = 1;

    _ACTWait(1);
    stage_SetAnimation(16, 1, 0);

    while (stage_ContinueAnimation(581, 582) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2366), 1043);

    scpPlayMot(scpSearchGobj(2364), 999);
    scpPlayMot(scpSearchGobj(2365), 1021);

    _ACTWait(1);
    stage_SetAnimation(17, 1, 0);

    while (stage_ContinueAnimation(582, 583) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 279);
    scpPlayMot(scpSearchGobj(2366), 1044);

    _ACTWait(1);
    stage_SetAnimation(18, 1, 0);
    stage_SetAnimation(176, 1, 0);

    while (stage_ContinueAnimation(583, 584) == 0) {
        _ACTWait(1);
    }

    scpFadeIn(3.0f);

    scpPlayMot(D_00639EA4, 280);
    scpPlayMot(scpSearchGobj(2364), 999);
    scpPlayMot(scpSearchGobj(2365), 1021);
    scpPlayMot(scpSearchGobj(2366), 1045);

    _ACTWait(1);
    stage_SetAnimation(19, 1, 0);
    stage_SetAnimation(172, 1, 0);

    while (stage_ContinueAnimation(584, 585) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 281);
    scpPlayMot(scpSearchGobj(2364), 1000);
    scpPlayMot(scpSearchGobj(2365), 1022);
    scpPlayMot(scpSearchGobj(2366), 1046);

    _ACTWait(1);
    stage_SetAnimation(20, 1, 0);

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 8);

    D_0063C4F0 = 1;
    _ACTWait(0);
}
