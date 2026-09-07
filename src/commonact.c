#include "common.h"

#include "ico/types.h"

typedef struct { int a, b, c; } Blob12;

typedef struct { int w[6]; } SlowrunRec;

extern void SetDirectRootPosition();

void ACTSetPositionWithFitting(int a0, int a1, int a2, int a3)
{
    SetDirectRootPosition(a0, a1, a2, a3);
}
extern void SetDirectRootPositionNoFitting__pn() __asm__("SetDirectRootPositionNoFitting");

void ACTSetPositionNoFitting(int a0, int a1, int a2, int a3)
{
    SetDirectRootPositionNoFitting__pn(a0, a1, a2, a3);
}
extern void SetDirectRootPositionWithNodePoint();

void ACTSetPositionNodeWithFitting(int a0, int a1, int a2, int a3)
{
    SetDirectRootPositionWithNodePoint(a0, a1, a2, a3);
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", ChangeMailInLadder);
INCLUDE_ASM("asm/nonmatchings/src/commonact", _ACTCorrectMsg);
INCLUDE_ASM("asm/nonmatchings/src/commonact", ACTGetOrientFromIntrK);
INCLUDE_ASM("asm/nonmatchings/src/commonact", ACTRunIntrCorrect);
void WithMailFunc_WayBeginPosError(void *a0) {
    ACTWay_SetBeginPositionIllegal(a0);
}
extern char *D_00639EA4;
extern char *D_00639EA8;
extern void ExecWeaponHitReaction(void *a0);

void WithMailFunc_AttackFail(char *a0) {
    char *s = *(char **)(a0 + 0x164);
    char *p = *(char **)(s + 0x30);
    int v = p != 0 ? *(int *)p : *(int *)(s + 0x5E0);
    if (a0 == D_00639EA4) {
        char *t = *(char **)(s + 0x150);
        if (t != 0) {
            *(int *)(*(char **)(t + 0x15C) + 0x5F4) = v;
            ExecWeaponHitReaction(t);
        }
    }
}
extern int stage_no;
extern int D_0063B210;
extern void ReleaseWeaponWithFumbleSequential(void *a0);
extern void *isysGObjSearchFromObjKindID_begin(int a0);

void WithMailFunc_AttackRejectInQueen(char *a0) {
    char *s = *(char **)(a0 + 0x164);
    void *w = *(void **)(s + 0x150);
    if (w != 0) {
        ReleaseWeaponWithFumbleSequential(w);
        *(int *)(s + 0x150) = 0;
    }
    if (stage_no == 0x55 || D_0063B210 != 0) {
        void *e = isysGObjSearchFromObjKindID_begin(0x36);
        if (e != 0) {
            iosOmSendMail(e, 0xD, (int)a0);
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", GetCorrectOrientOfChain);
ASM_LIT4_SLOT(D_00638E3C, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", CollisCheckInRope);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRope);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonRopeTurnR);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonRopeTurnL);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeClimbEnd1);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeCliff);
ASM_LIT4_SLOT(D_00638E40, 3.1415927f);
ASM_LIT4_SLOT(D_00638E44, 3.1415927f);
ASM_LIT4_SLOT(D_00638E48, 3.1415927f);
ASM_LIT4_SLOT(D_00638E4C, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", TestCageUpDown);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeSpecial);
ASM_LIT4_SLOT(D_00638E50, 0.7853982f);
ASM_LIT4_SLOT(D_00638E54, 3.1415927f);
extern void SetFloorLeverWithNodePoint(void *a0, void *a1, int a2);
extern void SetWallLeverWithNodePoint(void *a0, void *a1, int a2);

void lever_nego1(void *a0, void *a1) {
    int m = *(int *)((char *)a1 + 0xC);
    if (m < 0x16) {
        return;
    }
    if (m < 0x18) {
        goto lever;
    }
    if (m >= 0x1A) {
        return;
    }
    SetWallLeverWithNodePoint(a1, a0, 0x16);
    return;
lever:
    SetFloorLeverWithNodePoint(a1, a0, 0x16);
}
extern void SetDirectRootPositionNoFitting(void *a0, void *a1);
extern void *test_CURRENTROOT(void *a0);

void SetDirectRootPositionXZ(void *a0, void *a1) {
    void *ret = test_CURRENTROOT(a0);
    *(float *)((char *)a1 + 4) = *(float *)((char *)ret + 4);
    SetDirectRootPositionNoFitting(a0, a1);
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonLever);
ASM_LIT4_SLOT(D_00638E58, 0.2f);
extern void eBrainSendMes(void *a0);

void EBRAIN_SEND_MES(void *a0, int a1) {
    if (a0 && *(int *)((char *)a0 + 0xC) == 4)
        eBrainSendMes(a0);
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", DamageFunc);
extern void DamageFunc(char *a0);

void DownFunc(char *a0) {
    DamageFunc(a0);
    if (*(int *)(a0 + 0xC) == 1) {
        EBRAIN_SEND_MES(*(void **)(*(char **)(a0 + 0x164) + 0x1B0), 6);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonDown);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonDie);
ASM_LIT4_SLOT(D_00638E5C, 0.01f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", Cling);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonCling);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonSlip);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonStoneDead);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonStone);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonSofa);
void BoxBarSoundOn(char *a0) {
    char *s = *(char **)(a0 + 0x164);
    switch (*(int *)(s + 0x34)) {
    case 0x31:
        ExecBoxMoveStartReaction(*(int *)(s + 0x158), *(int *)(s + 0x38));
        break;
    case 0x33:
        ExecRotObjectMoveStartReaction(*(int *)(s + 0x5F8));
        break;
    }
}
void BoxBarSoundOff(char *a0) {
    char *s = *(char **)(a0 + 0x164);
    switch (*(int *)(s + 0x34)) {
    case 0x31:
        ExecBoxMoveEndReaction(*(int *)(s + 0x158));
        break;
    case 0x33:
        ExecRotObjectMoveEndReaction(*(int *)(s + 0x5F8));
        break;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", _boxbar_set_sound);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonBox);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonBar);
INCLUDE_ASM("asm/nonmatchings/src/commonact", funcCommonJumpDircorrect);
ASM_LIT4_SLOT(D_00638E60, 0.3f);
ASM_LIT4_SLOT(D_00638E64, 0.3f);
void funcCommonFallDircorrect(char *a0) {
    SetMotionDirection(a0, *(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x360);
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", correctJumpOrientByChain);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonJump);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonFall);
ASM_LIT4_SLOT(D_00638E68, 0.1f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", debugDispFlyLimit);
extern int MatrixDrive_GetMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_TransMatrixV(void *a0);
extern void _UnitMatrix(int a0);
extern void gif_EndPacket(void);
extern void gif_StartPacketPri(int a0);
extern void prim_DispWireSphere(void *a0, int a1, int a2, float a3);

void debugDispSphere(void *a0, void *a1, float f) {
    MatrixDrive_PushMatrix();
    _UnitMatrix(MatrixDrive_GetMatrix());
    gif_StartPacketPri(0xB);
    MatrixDrive_TransMatrixV(a0);
    prim_DispWireSphere(a1, 4, 4, f);
    gif_EndPacket();
    MatrixDrive_PopMatrix();
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", getLandOffset);
INCLUDE_ASM("asm/nonmatchings/src/commonact", completeEmergency);
ASM_LIT4_SLOT(D_00638E6C, 7000.0f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", emergencyCheck);
ASM_LIT4_SLOT(D_00638E70, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", flyCoreLoop);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonFly);
ASM_LIT4_SLOT(D_00638E74, 0.005f);
ASM_LIT4_SLOT(D_00638E78, 10000.0f);
ASM_LIT4_SLOT(D_00638E7C, 0.005f);
ASM_LIT4_SLOT(D_00638E80, 90000.0f);
ASM_LIT4_SLOT(D_00638E84, 0.05f);
ASM_LIT4_SLOT(D_00638E88, 0.005f);
ASM_LIT4_SLOT(D_00638E8C, 360000.0f);
ASM_LIT4_SLOT(D_00638E90, 0.92f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonLadder);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonEdgeHang);
INCLUDE_ASM("asm/nonmatchings/src/commonact", funcCommonBeginReady);
INCLUDE_ASM("asm/nonmatchings/src/commonact", funcCommonEndReady);
INCLUDE_ASM("asm/nonmatchings/src/commonact", funcCommonEndExec);
INCLUDE_ASM("asm/nonmatchings/src/commonact", funcCommonError);
INCLUDE_ASM("asm/nonmatchings/src/commonact", SetMotionDirectionSmooze);
ASM_LIT4_SLOT(D_00638E94, 3.1415927f);
ASM_LIT4_SLOT(D_00638E98, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", _ACTDebugPrint);
void ACTSendMailCorrect(char *a0, int a1) {
    char *s = *(char **)(a0 + 0x164);
    if ((a1 == 0xB5 || a1 == 0xBA) && *(int *)(a0 + 0xC) == 1) {
        long long f = *(long long *)(s + 0x488);
        if (((int)(f >> 5) & 1) && ((int)(*(long long *)(s + 0x498) >> 5) & 1)) {
            a1 = 0xB6;
        } else if ((int)(f >> 3) & 1) {
            a1 = ((int)(*(long long *)(s + 0x498) >> 3) & 1) ? 0xB7 : a1;
        }
    }
    iosOmSendMail(a0, a1, (int)a0);
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", _ACTCommonMailTest);
ASM_LIT4_SLOT(D_00638E9C, 0.1f);
ASM_LIT4_SLOT(D_00638EA0, 0.1f);
ASM_LIT4_SLOT(D_00638EA4, 0.1f);
ASM_LIT4_SLOT(D_00638EA8, 0.1f);
ASM_LIT4_SLOT(D_00638EAC, 0.1f);
ASM_LIT4_SLOT(D_00638EB0, 0.99f);
ASM_LIT4_SLOT(D_00638EB4, 0.1f);
ASM_LIT4_SLOT(D_00638EB8, 0.99f);
ASM_LIT4_SLOT(D_00638EBC, 0.1f);
ASM_LIT4_SLOT(D_00638EC0, 0.1f);
ASM_LIT4_SLOT(D_00638EC4, 0.99f);
ASM_LIT4_SLOT(D_00638EC8, 0.1f);
ASM_LIT4_SLOT(D_00638ECC, 0.99f);
extern void _ApplyRyGV(void *a0, float a1);
extern void *test_CURRENTORIENT(char *a0);

extern int _RotyGV(void *a0, void *a1);

int E3_LeverCheck(char *a0) {
    float buf[3];
    int v;
    buf[0] = *(float *)((char *)test_CURRENTORIENT(*(char **)(*(char **)(a0 + 0x15C) + 0x180)) + 0x0);
    buf[1] = *(float *)((char *)test_CURRENTORIENT(*(char **)(*(char **)(a0 + 0x15C) + 0x180)) + 0x4);
    buf[2] = *(float *)((char *)test_CURRENTORIENT(*(char **)(*(char **)(a0 + 0x15C) + 0x180)) + 0x8);
    _ApplyRyGV(buf, -1.5707964f);
    return _RotyGV(test_CURRENTORIENT(a0), buf) < 0
               ? -_RotyGV(test_CURRENTORIENT(a0), buf) < 0x2D
               : _RotyGV(test_CURRENTORIENT(a0), buf) < 0x2D;
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonBecarry);
INCLUDE_ASM("asm/nonmatchings/src/commonact", subCommonIdle);
INCLUDE_ASM("asm/nonmatchings/src/commonact", ContinueCorrectPosition);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonTurn);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonBackhand);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonSlowrun);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonTruckLever);
ASM_LIT4_SLOT(D_00638ED4, 0.2f);
ASM_LIT4_SLOT(D_00638ED8, 0.2f);
ASM_LIT4_SLOT(D_00638EDC, 0.1f);
ASM_LIT4_SLOT(D_00638EE0, 0.2f);
extern int D_00639EB8;
void ACT_LAYOUT_GAMEOVER(void) {
    if (D_00639EB8 == 0) {
        D_00639EB8 = 1;
        lt_switch_layout(0x3E);
    }
}
extern void AdjustRootPositionToVerticalSidePlaneOfWall(int a0, int a1, float a2);

void ACTAdjustPlane(int a0, int a1) {
    AdjustRootPositionToVerticalSidePlaneOfWall(a0, a1, 30.0f);
}
extern int D_0028F4C0[];

void ACTAcceptMail(char *a0, int a1) {
    if (a1 == 0xB1) {
        *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x3C4) =
            ((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 10;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", _ACTMotDirSmzDirect);
INCLUDE_ASM("asm/nonmatchings/src/commonact", WithMailFunc_Idling);
void WithMailFunc_BossDamaged(char *a0) {
    char *m = *(char **)(*(char **)(a0 + 0x164) + 0x680);
    *(int *)(m + 0x20C) -= 1;
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", WithMailFunc_FallDead);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRevive);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonReviveAir);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonPlay);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonOne);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonDelete);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonCatchFire);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonCatchFireBomb);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonPutFire);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonBoxReverbe);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonItem);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonClimb);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonCliffdown);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonLadderBellow);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonLadderBellowHang);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonEdge);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonDodge);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonDodgeJump);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonGuard);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonFallDamage);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonDamage);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonShoal);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonSwim);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonLever2);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeTouchWall);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeSwing);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeTurn);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeDownEnd);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeJump);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeJumpBefore);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeTurnSpecial);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonRopeClimbEnd2);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonCornered);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonLookaround);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonTurnWarn);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonTurnStrict);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonPPipe);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonHandrail);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonOneWall);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonNull);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonBoxPush);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonBoxPull);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonBarPush);
void motCommonBarPull(volatile int a0) {
    char *g = (char *)a0;
    *(unsigned int *)(*(char **)(g + 0x164) + 0x38) = 0xFFFFFFFFu;
    _ACTWait(0);
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonLadderUp);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonLadderDown);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonSlip);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonRopejumpDircorrect);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonHangNone);
extern char D_00553188[];
extern void _ACTWait(int a0);
extern void debug_StdPrintfDummy();

void motCommonHangWall(volatile int a0) {
    debug_StdPrintfDummy(D_00553188);
    _ACTWait(0);
}
extern char D_005531A8[];

void motCommonHangCliff(volatile int a0) {
    debug_StdPrintfDummy(D_005531A8);
    _ACTWait(0);
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonRopeTurnSpecialR);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonRopeTurnSpecialL);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonTruckLeverLoop);
ASM_LIT4_SLOT(D_00638EE4, 0.1f);
ASM_LIT4_SLOT(D_00638EE8, 3.1415927f);
ASM_LIT4_SLOT(D_00638EEC, 0.1f);
ASM_LIT4_SLOT(D_00638EF0, 3.1415927f);
extern char D_0063A780[];
extern void SetSwitchState(int a0, int a1);

void motCommonTruckLeverPull(volatile int a0) {
    int sw = *(int *)(*(int *)(a0 + 0x164) + 0x5FC);
    _ACTWait(0x1E);
    SetSwitchState(sw, -1);
    debug_StdPrintfDummy(D_0063A780);
    _ACTWait(0);
}
extern char D_0063A788[];

void motCommonTruckLeverPush(volatile int a0) {
    int sw = *(int *)(*(int *)(a0 + 0x164) + 0x5FC);
    _ACTWait(0x1E);
    SetSwitchState(sw, 1);
    debug_StdPrintfDummy(D_0063A788);
    _ACTWait(0);
}
void funcCommonRopeBefore(char *a0, int a1, int a2) {
    *(int *)(*(char **)(a0 + 0x164) + 0x190) = a2;
}
extern char D_00552D78[];
extern void ReleaseChain(int a0, int a1);

void afterCommonRope(volatile int a0) {
    int s = *(int *)(a0 + 0x164);
    debug_StdPrintfDummy(D_00552D78);
    ReleaseChain(*(int *)(s + 0x190), a0);
    {
        int g = a0;
        *(int *)(s + 0x194) = *(int *)(s + 0x190);
        *(int *)(*(int *)(g + 0x15C) + 0x420) = 0;
    }
}
void extraCommonNull(volatile int a0) {
    for (;;) {
        _ACTWait(1);
    }
}
extern int D_0063A61C;
extern void iosOmSendMail(void *a0, int a1, int a2);

void extraCommonCall(volatile int a0) {
    if (D_00639EA8) {
        iosOmSendMail(D_00639EA8, 0x44, D_0063A61C);
    }
    for (;;) {
        _ACTWait(1);
    }
}
extern int girlcalled;

void funcCommonWayOn(void *a0) {
    if (a0 == D_00639EA8) {
        girlcalled = 1;
    }
}
void funcCommonSofaWakeup(char *a0) {
    *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x250) = 0;
}
int _ACTMotReqResult(char *a0, int a1) {
    char *s = *(char **)(a0 + 0x164);
    char *r = SetMotionRequest(a0, a1, s + 0x620);
    *(char **)(s + 0x130) = r;
    return *(int *)(r + 0xC) != 0;
}
extern char D_006C0BA0[];
extern void GetRootOrient(void *a0, void *a1);
extern void _GetMotionDirection(void *a0, void *a1);

void *test_CURRENTORIENT(char *a0) {
    if (a0 != D_00639EA4 && a0 != D_00639EA8 && *(int *)(a0 + 0xC) != 4) {
        GetRootOrient(D_006C0BA0, a0);
        return D_006C0BA0;
    }
    {
        char *p = *(char **)(a0 + 0x164) + 0xF0;
        _GetMotionDirection(p, a0);
        return p;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", test_CURRENTROOT);
INCLUDE_ASM("asm/nonmatchings/src/commonact", StartCorrectPosition);
int IsCorrectPosition(char *a0) {
    unsigned long long v = *(unsigned int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0xBC);
    return (int)v & 1;
}
extern SlowrunRec D_002ADD60[];

void ControlMotionOrient(int a0, int a1) {
    D_002ADD60[a0].w[2] = a1;
}
extern int IsThisBoxTruck(void *a0);

int FloorIsTruck(void *a0) {
    char *p = *(char **)(*(int *)((char *)a0 + 0x15C));
    if (p != 0) {
        if (*(int *)(p + 0xC) == 0x11) {
            if (IsThisBoxTruck(p) == 7) {
                return 1;
            }
        }
    }
    return 0;
}
extern void SetMotionDirection();
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);

void _ACTMotDir_V(void *a0, void *a1) {
    int local[4];
    sceVu0ScaleVector(local, a1, -1.0f);
    SetMotionDirection(a0, local);
}
void ACTMotDirToWall(char *a0) {
    int local[4];
    sceVu0ScaleVector(local, *(char **)(a0 + 0x164) + 0x4B0, -1.0f);
    SetMotionDirection(a0, local);
}
extern void GetCorrectOrientOfChain(void *buf, void *obj);

void SetCorrectOrientOfChain(void *a0) {
    int local[4];
    GetCorrectOrientOfChain(local, a0);
    SetMotionDirection(a0, local);
}
extern char D_00552D90[];
extern char D_00552DA0[];
extern void debug_assert(char *a0, int a1);
extern void __assert(char *a0, int a1, char *a2);
extern void UnLockChainGeo(int a0);

void actAfterForceRope(volatile int a0) {
    int s = *(int *)(a0 + 0x164);
    if (*(int *)(s + 0x190) == 0) {
        debug_assert(D_00552D90, 0x5FB);
        __assert(D_00552D90, 0x5FB, D_00552DA0);
    }
    UnLockChainGeo(*(int *)(s + 0x190));
}
void actAfterForceRopeSwing(volatile int a0) {
    int s = *(int *)(a0 + 0x164);
    if (*(int *)(s + 0x190) == 0) {
        debug_assert(D_00552D90, 0x675);
        __assert(D_00552D90, 0x675, D_00552DA0);
    }
    UnLockChainGeo(*(int *)(s + 0x190));
}
void actAfterRopeJump(volatile int a0) {
    char *g = (char *)a0;
    *(unsigned long long *)(*(char **)(g + 0x164) + 0x20) |= (1ULL << 31);
}
extern char *D_00639EA4;

void afterCommonRopeCliff(char *a0) {
    char *volatile local = a0;
    char *g = *(char **)(D_00639EA4 + 0x15C);
    *(int *)(g + 0x420) = 0;
}
void afterCommonRopeTurnSpecial(volatile int a0) {
    char *g = (char *)a0;
    *(int *)(*(char **)(g + 0x15C) + 0x420) = 0;
}
void actAfterDown(volatile int a0) {
    *(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x688) + 0x37C) =
        ((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 0x82 / 0x3C;
}
extern void ACTGameCollisionOn(volatile int *self);

void afterCommonCling(volatile unsigned int a0)
{
    ACTGameCollisionOn(a0);
}
void actAfterSlip(int x) {
    volatile int local = x;
}
void afterCommonRevive(volatile unsigned int a0)
{
    ACTGameCollisionOn(a0);
}
void afterCommonStone(volatile int a0) {
    int g1 = a0;
    int g2 = a0;
    *(int *)(*(int *)(*(int *)(g1 + 0x164) + 0x680) + 0x2A0) = -1;
    *(int *)(*(int *)(*(int *)(g2 + 0x164) + 0x680) + 0x2A4) = 0;
}
extern void _boxbar_set_sound(int a0, int a1);

void afterCommonBox(volatile int a0) {
    _boxbar_set_sound(a0, 0);
}
extern Blob12 InitialColInfo;

extern void debug_StdPrintfDummy();

void afterCommonBar(volatile int a0) {
    debug_StdPrintfDummy("reset\n");
    *(Blob12 *)(*(char **)(a0 + 0x15C) + 0x1C0) = InitialColInfo;
    _boxbar_set_sound(a0, 0);
}
void actAfterJump(volatile int a0) {
    char *g = (char *)a0;
    *(unsigned long long *)(*(char **)(g + 0x164) + 0x20) |= (1ULL << 31);
}
void actAfterFall(volatile int a0) {
    int s = *(int *)(a0 + 0x164);
    unsigned long long st = *(unsigned long long *)(s + 0x20) & ~(1ULL << 42);
    unsigned long long fl = *(unsigned long long *)(s + 0x18) & ~(1ULL << 53);
    *(unsigned long long *)(s + 0x18) = fl;
    *(unsigned long long *)(s + 0x20) = st | (1ULL << 31);
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", actAfterFly);
extern void sceVu0CopyVector(void *a0, void *a1);
extern void ClipWallField(void *a0);
extern void ClipFloor(void *a0);

void ClipCollisionWithField(char *a0) {
    int tmp[4];
    sceVu0CopyVector(tmp, a0 + 0x10);
    ClipWallField(a0);
    sceVu0CopyVector(a0 + 0x10, a0 + 0x20);
    ClipFloor(a0);
    sceVu0CopyVector(a0 + 0x10, tmp);
}
void afterCommonOneWall(int x) {
    volatile int local = x;
}
int ACTCheckFlagAttack(char *a0) {
    return *(int *)(*(char **)(a0 + 0x164) + 0x34) == 0xF;
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", afterCommonBecarry);
void afterCommonTruckLever(volatile int a0) {
    char *g = (char *)a0;
    SetSwitchState(*(int *)(*(char **)(g + 0x164) + 0x5FC), 0);
}
