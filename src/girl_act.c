#include "common.h"

typedef struct {
    char _0[0x20];
    float f_20;        /* 0x20 */
    char _24[0x0C];
    float sub30[4];    /* 0x30 */
    float sub40[4];    /* 0x40 */
    float f_50;        /* 0x50 */
    float f_54;        /* 0x54 */
    signed char f_58;  /* 0x58 */
    signed char f_59;
    signed char f_5A;
    signed char f_5B;
    signed char f_5C;
    signed char f_5D;
    signed char f_5E;
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

void func_0016FC20(void)
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
INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainHideCheckIntercept);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainMain_CheckWarningMode);
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
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00171188);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00172920);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", checkWaterfallResult);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00172D00);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_001744A0);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainHide_GoalTurn);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", isHideRecheck);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00174998);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00174CE8);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainRunawaySearchPoint);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainRunawayMoveByWay);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00175688);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", GetSafePosition);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00176028);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_001762A0);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00176570);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00176838);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00176C28);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00177098);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00177340);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_001776D8);
extern float D_00638FEC;
extern float D_00638FF0;
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
    if (_DistxzSqGV(buf, buf + 0x10) < D_00638FEC) {
        return 1;
    }
    if (_DistxzSqGV(buf, buf + 0x10) < D_00638FF0) {
        if (func_001776D8(buf, buf + 0x10) != 0) {
            return 1;
        }
    }
ret0:
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/girl_act", WayTest);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00177BB8);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_001790F8);
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
INCLUDE_ASM("asm/nonmatchings/src/girl_act", HandMgr_Speed);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", GetBoyMode);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00179940);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", GirlAct_BoyAndMeCollisionMail);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", IsGirlStatusEscortEnable);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", DebugDispAutoEscort);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0017B530);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0017B760);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", FindGirlPullupFloorBoxGObj);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0017B8A0);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0017BB90);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0017BBD8);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0017BC20);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0017BE70);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0017BF68);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0017C1D0);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0017C290);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", NotNeedBackHand);
void SetGirlDangerGObj(int a0) {
    char *g = D_00639EA8;
    if (g != 0) {
        *(int *)(*(char **)(*(char **)(g + 0x164) + 0x688) + 0x3E4) = a0;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/girl_act", ClearGirlDangerGObj);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", subGirlBrain_Idle);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0017C418);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_0017C4F8);
int enemy_list_compare(int a0, int a1)
{
    float diff = *(float *)(a0 + 0x20) - *(float *)(a1 + 0x20);
    return (int)diff;
}
INCLUDE_ASM("asm/nonmatchings/src/girl_act", ACTCheckCollis_SAFE);
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
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlJump);
void afterGirlSupportBGBegin(unsigned int a0)
{
    volatile unsigned int local = a0;
    ACTGame_DisconnectHand();
}
INCLUDE_ASM("asm/nonmatchings/src/girl_act", isMustCheckCylinder);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", afterGirlHintPoint);
