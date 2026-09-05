#include "common.h"

typedef struct {
    char _0[0x20];
    float f_20;        /* 0x20 */
    char _24[0x0C];
    float sub30[4];    /* 0x30 */
    float sub40[4];    /* 0x40 */
    float f_50;        /* 0x50 */
    float f_54;        /* 0x54 */
    unsigned char f_58;  /* 0x58 */
    unsigned char f_59;
    unsigned char f_5A;
    unsigned char f_5B;
    unsigned char f_5C;
    unsigned char f_5D;
    unsigned char f_5E;
} GirlStand;

INCLUDE_ASM("asm/nonmatchings/src/girl_act", GetEyeDirection);
extern void ACTGame_DisconnectHand(void);
extern char D_00553990[];
extern void debug_StdPrintfDummy__pn(void *a0) __asm__("debug_StdPrintfDummy");

void funcGirlHandDisconnect(void) {
    ACTGame_DisconnectHand();
    debug_StdPrintfDummy__pn(D_00553990);
}
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0016F6B0);
extern int D_002A5580[];
extern void brainClsTargetLevel();

void GirlBrainClearTarget(void)
{
    brainClsTargetLevel(D_002A5580);
}
extern void ACTGame_SetMotionPlaySpeedRatio_Reserve(void *a0, int a1, float f);
void SetTurnSpeedInEscape(char *a0) {
    if (*(int *)(*(char **)(a0 + 0x164) + 0x34) == 10) {
        ACTGame_SetMotionPlaySpeedRatio_Reserve(a0, 5, 1.5f);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/girl_act", sort_list);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainMain_MakeOthersList);
ASM_LIT4_SLOT(D_00638F64, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainHideCheckIntercept);
ASM_LIT4_SLOT(D_00638F68, 90000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainMain_CheckWarningMode);
ASM_LIT4_SLOT(D_00638F6C, 160000.0f);
ASM_LIT4_SLOT(D_00638F70, 40000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainMain_DecideMode);
extern char D_002A2E70[];
extern int *D_00639EA4;
extern void *D_00639EA8;
extern void GetRootPosition(void *out, void *obj);
extern void GetRootProjectionPosOfGObj(void *out, void *obj);

void girlBrainMain_PositionUpdate(void) {
    GetRootPosition(D_002A2E70 + 0x00, D_00639EA8);
    GetRootPosition(D_002A2E70 + 0x20, D_00639EA4);
    GetRootProjectionPosOfGObj(D_002A2E70 + 0x10, D_00639EA8);
    GetRootProjectionPosOfGObj(D_002A2E70 + 0x30, D_00639EA4);
}
extern char D_0029D650[];
void girlBrainMain_Init(void) {
    memset(D_0029D650, 0, 0x5920);
}
INCLUDE_ASM("asm/nonmatchings/src/girl_act", ChangeRunMode);
ASM_LIT4_SLOT(D_00638F74, 250000.0f);
ASM_LIT4_SLOT(D_00638F78, 22500.0f);
ASM_LIT4_SLOT(D_00638F7C, 160000.0f);
ASM_LIT4_SLOT(D_00638F80, 0.1f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00171188);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", ATGoalTurnMail);
ASM_LIT4_SLOT(D_00638F84, 2300.0f);
ASM_LIT4_SLOT(D_00638F88, 850.0f);
ASM_LIT4_SLOT(D_00638F8C, 2300.0f);
ASM_LIT4_SLOT(D_00638F90, 850.0f);
ASM_LIT4_SLOT(D_00638F94, 750.0f);
ASM_LIT4_SLOT(D_00638F98, 650.0f);
ASM_LIT4_SLOT(D_00638F9C, 950.0f);
ASM_LIT4_SLOT(D_00638FA0, 1900.0f);
ASM_LIT4_SLOT(D_00638FA4, 870.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", checkWaterfallResult);
ASM_LIT4_SLOT(D_00638FA8, 90000.0f);
ASM_LIT4_SLOT(D_00638FAC, 10000.0f);
ASM_LIT4_SLOT(D_00638FB0, 40000.0f);
ASM_LIT4_SLOT(D_00638FB4, 90000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00172D00);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_001744A0);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainHide_GoalTurn);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", isHideRecheck);
ASM_LIT4_SLOT(D_00638FB8, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00174998);
ASM_LIT4_SLOT(D_00638FBC, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00174CE8);
ASM_LIT4_SLOT(D_00638FC0, 10000.0f);
ASM_LIT4_SLOT(D_00638FC4, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainRunawaySearchPoint);
ASM_LIT4_SLOT(D_00638FC8, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainRunawayMoveByWay);
ASM_LIT4_SLOT(D_00638FCC, 90000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00175688);
ASM_LIT4_SLOT(D_00638FD0, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", GetSafePosition);
ASM_LIT4_SLOT(D_00638FD4, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00176028);
ASM_LIT4_SLOT(D_00638FD8, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_001762A0);
ASM_LIT4_SLOT(D_00638FDC, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00176570);
ASM_LIT4_SLOT(D_00638FE0, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00176838);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00176C28);
ASM_LIT4_SLOT(D_00638FE4, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00177098);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00177340);
ASM_LIT4_SLOT(D_00638FE8, 1500.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_001776D8);
extern int D_00639EA4__pn __asm__("D_00639EA4");
extern void *D_00629DE4, *D_00639EA8__pn __asm__("D_00639EA8");
extern float _DistxzSqGV(void *, void *);
extern int func_001776D8(void *, void *);

int isEnterHideadv(void) {
    char buf[0x20];
    int rv = 0;
    float diff;
    if (D_00639EA4__pn == 0) {
        goto ret0;
    }
    if (D_00639EA8__pn == 0) {
        return 0;
    }
    GetRootProjectionPosOfGObj(buf, D_00639EA4__pn);
    GetRootProjectionPosOfGObj(buf + 0x10, D_00639EA8__pn);
    diff = *(float *)(buf + 0x4) - *(float *)(buf + 0x14);
    if (diff < 0.0f) {
        if (-diff > 200.0f) {
            goto set;
        }
        goto test;
    }
    if (diff > 200.0f) {
    set:
        rv = 1;
    }
test:
    if (rv == 0) {
        goto ret0;
    }
    if (_DistxzSqGV(buf, buf + 0x10) < 22500.0f) {
        return 1;
    }
    if (_DistxzSqGV(buf, buf + 0x10) < 250000.0f) {
        if (func_001776D8(buf, buf + 0x10) != 0) {
            return 1;
        }
    }
ret0:
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/girl_act", WayTest);
ASM_LIT4_SLOT(D_00638FF4, 0.001f);
ASM_LIT4_SLOT(D_00638FF8, 0.1f);
ASM_LIT4_SLOT(D_00638FFC, 0.1f);
ASM_LIT4_SLOT(D_00639000, 0.99f);
ASM_LIT4_SLOT(D_00639004, 0.1f);
ASM_LIT4_SLOT(D_00639008, 0.99f);
ASM_LIT4_SLOT(D_0063900C, 0.1f);
ASM_LIT4_SLOT(D_00639010, 0.1f);
ASM_LIT4_SLOT(D_00639014, 0.1f);
ASM_LIT4_SLOT(D_00639018, 0.1f);
ASM_LIT4_SLOT(D_0063901C, 0.1f);
ASM_LIT4_SLOT(D_00639020, 0.1f);
ASM_LIT4_SLOT(D_00639024, 0.1f);
ASM_LIT4_SLOT(D_00639028, 0.1f);
ASM_LIT4_SLOT(D_0063902C, 0.1f);
ASM_LIT4_SLOT(D_00639030, 250000.0f);
ASM_LIT4_SLOT(D_00639034, 0.3f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00177BB8);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", HandMgr_GetDistHand);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", HandMgr_Update);
extern GirlStand D_002A2F70;
extern int _RotyGV(void *buf, void *vec);

void HandMgr_Judge(void) {
    volatile int home;
    int uninit;
    float one = 1.0f;
    home = uninit;
    if (D_002A2F70.f_20 < 2.0f) {
        D_002A2F70.f_58 = 1;
    }
    if ((_RotyGV(D_002A2F70.sub40, D_002A2F70.sub30) < 0
            ? -_RotyGV(D_002A2F70.sub40, D_002A2F70.sub30)
            : _RotyGV(D_002A2F70.sub40, D_002A2F70.sub30)) >= 0x3D) {
        D_002A2F70.f_59 = 1;
    }
    if (D_002A2F70.f_54 > 15.0f) {
        D_002A2F70.f_5E = 1;
    }
    if (one * 100.0f < D_002A2F70.f_50) {
        D_002A2F70.f_5A = 1;
    }
    if (one * 125.0f < D_002A2F70.f_50) {
        D_002A2F70.f_5B = 1;
    }
    if (one * 135.0f < D_002A2F70.f_50) {
        D_002A2F70.f_5C = 1;
    }
    if (D_002A2F70.f_50 < 90.0f) {
        D_002A2F70.f_5D = 1;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/girl_act", HandMgr_Print);
ASM_LIT4_SLOT(D_00639038, 0.9f);
ASM_LIT4_SLOT(D_0063903C, 1.1f);
ASM_LIT4_SLOT(D_00639040, 1.4f);
ASM_LIT4_SLOT(D_00639044, 1.3f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", HandMgr_Speed);
extern char D_0055FE58[];

void GetBoyMode(int *mode, int *p1, int *p2, int *p3)
{
    /* Static-chain home: GetBoyMode is a gcc nested function of
       actGirlHand (caller sets $2 = its $sp before the jal), so the
       prologue stores the incoming chain register into frame slot 0.
       Same stand-in as the matched sibling HandMgr_Judge above; it is
       replaced by a real nested definition once actGirlHand is C.  */
    volatile int home;
    int uninit;
    char *rec;
    home = uninit;
    *mode = ((int *)D_00639EA4[0x59])[0xD];
    *p1 = 0;
    *p2 = 0;
    *p3 = 0;
    switch (*mode) {
    case 14:
        *mode = 1;
        break;
    case 15:
        *mode = 1;
        break;
    case 8:
        *mode = 1;
        break;
    case 2:
    case 3:
        if (((int *)D_00639EA4[0x59])[0x55] != 0) {
            *mode = 2;
        }
        rec = D_0055FE58 + ((int *)D_00639EA4[0x57])[0x128] * 0x194;
        switch ((*(unsigned int *)(rec + 0x188) >> 22) & 3) {
        case 1:
            *mode = 2;
            break;
        case 2:
            *mode = 3;
            break;
        }
        if (*mode == 3) {
            unsigned long long f = *(unsigned long long *)((char *)((int *)D_00639EA4[0x59])[0x1A2] + 0x448);
            if ((int)(f >> 33) & 1) {
                *mode = 1;
            } else if ((int)(f >> 32) & 1) {
                *mode = 2;
            }
        }
        if (*mode == 2) {
            unsigned long long f = *(unsigned long long *)((char *)((int *)D_00639EA4[0x59])[0x1A2] + 0x448);
            if ((int)(f >> 33) & 1) {
                *mode = 1;
            }
        }
        break;
    case 36:
        if (((int *)D_00639EA4[0x59])[0xF] == 0x5E) {
            *p2 = 1;
        } else {
            *mode = 1;
        }
        break;
    case 5:
    case 13:
    case 17:
    case 18:
    case 68:
        *mode = 3;
        break;
    }
}
ASM_LIT4_SLOT(D_00639048, 0.1f);
ASM_LIT4_SLOT(D_0063904C, -1.5707964f);
ASM_LIT4_SLOT(D_00639050, 0.1f);
ASM_LIT4_SLOT(D_00639054, 0.7f);
ASM_LIT4_SLOT(D_00639058, 0.6f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlHand);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlPulledReady);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlPulledGo);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlDitch3mReady);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlReadyMove);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlRescueDst);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlSupportBGBegin);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlStart);
extern void ACTSendMailCorrect(void *a0, int mail);
extern void *test_CURRENTORIENT(void *a0);
extern void sceVu0SubVector(void *out, void *a, void *b);
extern void sceVu0Normalize(void *out, void *in);

void GirlAct_BoyAndMeCollisionMail(void *a0)
{
    float vec[4];
    float boyPos[4];
    float myPos[4];
    float ang;

    ACTSendMailCorrect(a0, 0x10D);

    if (((int *)D_00639EA4[0x59])[0xD] == 1) {
        return;
    }
    GetRootPosition(boyPos, D_00639EA4);
    GetRootPosition(myPos, a0);

    sceVu0SubVector(vec, boyPos, myPos);
    sceVu0Normalize(vec, vec);

    ang = _RotyGV(vec, test_CURRENTORIENT(a0));

    if ((ang < 0.0f ? -ang : ang) < 45.0f) {
        ACTSendMailCorrect(a0, 0x10E);
        return;
    } else if ((ang < 0.0f ? -ang : ang) > 135.0f) {
        ACTSendMailCorrect(a0, 0x10F);
        return;
    } else if (ang > 45.0f) {
        ACTSendMailCorrect(a0, 0x110);
        return;
    } else {
        ACTSendMailCorrect(a0, 0x111);
    }
}
extern char D_005577D0[];

typedef struct {
    float x;    /* 0x00 */
    float y;    /* 0x04 */
    float z;    /* 0x08 */
    int f_0C;   /* 0x0C */
    int f_10;   /* 0x10 */
    float f_14; /* 0x14 */
    float f_18; /* 0x18 */
} EscortPoint;  /* 0x1C */

extern EscortPoint D_0055BA60[98];
extern void *test_CURRENTROOT(void *a0);
extern float _DistGV(void *a, void *b);
extern float _DistSqGV(void *a, void *b);
extern float _ACTGame_GetParamF(int idx);

static inline unsigned char isGirlEscortStatus(void)
{
    char *s = *(char **)((char *)D_00639EA8 + 0x164);
    int mode = *(int *)(s + 0x34);
    char *attr = D_005577D0 + mode * 0x50;
    if (((*(unsigned int *)(attr + 0x4C) >> 13) & 1) && mode != 0x6F
            && ((int)(*(unsigned long long *)(s + 0x20) >> 46) & 1)) {
        return 1;
    }
    return 0;
}

static inline EscortPoint *searchEscortPoint(int a0, int a1)
{
    EscortPoint *p;
    int i;
    for (i = 0; i < 98; i++) {
        p = &D_0055BA60[i];
        if (p->f_0C == a0 && p->f_10 == a1) {
            return p;
        }
    }
    return 0;
}

int IsGirlStatusEscortEnable(int a0, int a1)
{
    float v[4];
    EscortPoint *p;
    float d;

    if (D_00639EA4 != 0 && D_00639EA8 != 0
            && isGirlEscortStatus()) {
        p = searchEscortPoint(a0, a1);
        if (p != 0) {
            v[0] = -p->x;
            v[1] = -p->y;
            v[2] = -p->z;
            d = _DistGV(v, test_CURRENTROOT(D_00639EA8));
            if (d < p->f_14) {
                *(float *)(*(int *)(*(char **)((char *)D_00639EA8 + 0x164) + 0x688) + 0x330) = d * p->f_18;
                return 1;
            }
        } else {
            if (_DistSqGV(test_CURRENTROOT(D_00639EA4), test_CURRENTROOT(D_00639EA8))
                    < _ACTGame_GetParamF(5) * _ACTGame_GetParamF(5)) {
                return 1;
            }
        }
    }
    return 0;
}
typedef union { float f[4]; long long ll[2]; } Vec4;
typedef union { int c[4]; long long ll[2]; } Col4;

extern Vec4 D_005540A0;   /* { FLT_MAX, 0, 0, 1 } : "no girl" position */
extern Col4 D_00554090;   /* { 0, 0x10, 0x20, 0x80 } : wire sphere colour */
extern int D_0063B228;    /* debug display switch */
extern int stage_no;

extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_TransMatrixV(void *a0);
extern void sceVu0UnitMatrix(void *a0);
extern void gif_StartPacketPri(int a0);
extern void gif_SetZTest(int a0);
extern void gif_EndPacket(void);
extern void prim_DispWireSphere(void *col, int a1, int a2, float r);

static inline void dispEscortSphere(void *pos, float r, unsigned char in)
{
    Col4 col;

    if (D_0063B228) {
        MatrixDrive_PushMatrix();
        col = D_00554090;
        if (in) {
            col.c[0] = 0xFF;
        }
        gif_StartPacketPri(0xB);
        gif_SetZTest(1);
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrixV(pos);
        prim_DispWireSphere(&col, 0x10, 8, r);
        gif_EndPacket();
        MatrixDrive_PopMatrix();
    }
}

void DebugDispAutoEscort(void)
{
    Vec4 pos = D_005540A0;
    Vec4 v;
    EscortPoint *p;
    int i;
    int in;

    if (D_0063B228 == 0) {
        return;
    }
    if (D_00639EA8 != 0 && isGirlEscortStatus()) {
        pos.f[0] = ((float *)test_CURRENTROOT(D_00639EA8))[0];
        pos.f[1] = ((float *)test_CURRENTROOT(D_00639EA8))[1];
        pos.f[2] = ((float *)test_CURRENTROOT(D_00639EA8))[2];
    }
    for (i = 1; i < 16; i++) {
        p = searchEscortPoint(stage_no, i);
        if (p != 0) {
            v.f[0] = -p->x;
            v.f[1] = -p->y;
            v.f[2] = -p->z;
            in = _DistSqGV(&v, &pos) < p->f_14 * p->f_14;
            dispEscortSphere(&v, p->f_14, in);
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlHintPoint);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", ACTGame_GirlBeforeFunc);
extern int D_002A2E2C[];

void *FindGirlPullupFloorBoxGObj(void) {
    void *g = D_00639EA8;
    if (D_002A2E2C[0] == 7 &&
        *(int *)(*(char **)((char *)D_00639EA4 + 0x164) + 0x34) == 0x4E) {
        return *(void **)(*(char **)(*(char **)((char *)g + 0x164) + 0x688) + 0x374);
    }
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0017B8A0);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0017BB90);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0017BBD8);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0017BC20);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlBecall);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0017BF68);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0017C1D0);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0017C290);
int NotNeedBackHand(void) {
    char *g = D_00639EA8;
    char *w = *(char **)(g + 0x164);

    if ((((int)(*(unsigned long long *)(w + 0x18) >> 40)) & 1) == 0) {
        return 1;
    }
    if (*(int *)(w + 0x34) == 0x45 && D_002A2F70.f_5D != 0 && D_002A2F70.f_58 == 0) {
        return 1;
    }
    return 0;
}
void SetGirlDangerGObj(int a0) {
    char *g = D_00639EA8;
    if (g != 0) {
        *(int *)(*(char **)(*(char **)(g + 0x164) + 0x688) + 0x3E4) = a0;
    }
}
void ClearGirlDangerGObj(void) {
    char *g = (char *)D_00639EA8;
    if (g != 0) {
        *(int *)(*(char **)(*(char **)(g + 0x164) + 0x688) + 0x3E4) = 0;
    }
}
void subGirlBrain_Idle(volatile int a0) {
    char *g = (char *)a0;
    *(int *)(*(char **)(g + 0x164) + 0x34C) = 0;
    _ACTWait(0);
}
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0017C418);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0017C4F8);
int enemy_list_compare(int a0, int a1)
{
    float diff = *(float *)(a0 + 0x20) - *(float *)(a1 + 0x20);
    return (int)diff;
}
typedef struct {
    float a[4];        /* 0x00 start point   */
    float b[4];        /* 0x10 end point     */
    float pos[4];      /* 0x20 clipped point */
    char  _30[0x40];
    float f_70;        /* 0x70 radius/height */
    char  _74[0x14];
    int   f_88;        /* 0x88 wall hit      */
    char  _8c[0x08];
    int   f_94;        /* 0x94 floor hit     */
    char  _98[0x28];
} ClipWork;
extern void ClipWall(void *);
extern void ClipWallField(void *);
extern void ClipFloor(void *);

int ACTCheckCollis_SAFE(float height, float *p0, float *p1, void *actor, float *posout, int radius)
{
    ClipWork work;
    float tmp[4];
    int flag;
    int rv;

    rv = 1;
    flag = actor ? *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) : 0;

    work.f_70 = (float)radius;
    work.a[0] = p0[0];
    work.a[1] = p0[1];
    work.a[2] = p0[2];
    work.b[0] = p1[0];
    work.b[2] = p1[2];
    work.b[1] = p0[1];

    tmp[0] = p1[0];
    tmp[1] = p0[1];
    tmp[2] = p1[2];

    if (flag != 0) {
        *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) = 0;
    }
    ClipWall(&work);
    if (work.f_88 == 0) {
        ClipWallField(&work);
        if (work.f_88 == 0) goto no_wall;
    }
    tmp[0] = work.pos[0];
    tmp[1] = work.pos[1];
    tmp[2] = work.pos[2];
no_wall:
    work.a[0] = tmp[0];
    work.a[1] = tmp[1];
    work.a[2] = tmp[2];
    work.b[0] = tmp[0];
    work.b[2] = tmp[2];
    work.b[1] = tmp[1] + height;
    ClipFloor(&work);
    if (work.f_94 == 0) {
        rv = 0;
    } else {
        work.pos[1] -= 10.0f;
    }
    if (posout != 0) {
        posout[0] = work.pos[0];
        posout[1] = work.pos[1];
        posout[2] = work.pos[2];
    }
    if (flag != 0) {
        *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) = 1;
    }
    return rv;
}
extern void ACTGame_DisconnectHand(void);
extern void ACTWay_SetBeginPositionIllegal(char *self);
extern char D_00553E50[];
extern void debug_StdPrintfDummy();
extern void iosPadActStop(int key);

void afterGirlHand(unsigned int a0)
{
  volatile unsigned int local = a0;
 do { ACTGame_DisconnectHand(); debug_StdPrintfDummy(D_00553E50); iosPadActStop(7); ACTWay_SetBeginPositionIllegal(local); } while (0);
}
void afterGirlPulledGo(void *a0) {
    void *volatile q = a0;
    int *p = *(int **)((char *)q + 0x15C);
    *(int *)((char *)p + 0x634) = 0;
}
extern char D_00554048[];
void actGirlJump(volatile int a0) {
    char *g = (char *)a0;
    char *s = *(char **)(g + 0x164);
    debug_StdPrintfDummy(D_00554048);
    *(int *)(s + 0x34) = 4;
    _ACTWait(0);
}
void afterGirlSupportBGBegin(unsigned int a0)
{
    volatile unsigned int local = a0;
    ACTGame_DisconnectHand();
}
int isMustCheckCylinder(void *a, void *b) {
    if ((a == (void *)D_00639EA4 && b == D_00639EA8) || (a == D_00639EA8 && b == (void *)D_00639EA4)) {
        if (*(int *)(*(char **)((char *)D_00639EA8 + 0x164) + 0x34) == 0x51) {
            return 1;
        }
    }
    return 0;
}
void afterGirlHintPoint(volatile int a0) {
    RequestChangeHandMode((void *)a0, 1, 4, 0, 0, 0, 0);
}
