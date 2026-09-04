#include "common.h"

#include "ico/types.h"

typedef struct { int a, b, c; } Blob12;

typedef struct { int w[6]; } SlowrunRec;

extern void SetDirectRootPosition();

extern void SetDirectRootPosition__pn(void *a0, void *a1) __asm__("SetDirectRootPosition");
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
INCLUDE_ASM("asm/nonmatchings/src/commonact", WithMailFunc_WayBeginPosError);
INCLUDE_ASM("asm/nonmatchings/src/commonact", WithMailFunc_AttackFail);
INCLUDE_ASM("asm/nonmatchings/src/commonact", WithMailFunc_AttackRejectInQueen);
INCLUDE_ASM("asm/nonmatchings/src/commonact", GetCorrectOrientOfChain);
ASM_LIT4_SLOT(D_00638E3C, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", CollisCheckInRope);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015A800);
ASM_LIT4_SLOT(D_00638E40, 3.1415927f);
ASM_LIT4_SLOT(D_00638E44, 3.1415927f);
ASM_LIT4_SLOT(D_00638E48, 3.1415927f);
ASM_LIT4_SLOT(D_00638E4C, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015B398);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015B8F8);
ASM_LIT4_SLOT(D_00638E50, 0.7853982f);
ASM_LIT4_SLOT(D_00638E54, 3.1415927f);
extern void SetFloorLeverWithNodePoint(void *a0, void *a1, int a2);
extern void SetWallLeverWithNodePoint(void *a0, void *a1, int a2);

void func_0015BD00(void *a0, void *a1) {
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
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015BD88);
ASM_LIT4_SLOT(D_00638E58, 0.2f);
extern void eBrainSendMes(void *a0);

void func_0015BF40(void *a0, int a1) {
    if (a0 && *(int *)((char *)a0 + 0xC) == 4)
        eBrainSendMes(a0);
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", DamageFunc);
INCLUDE_ASM("asm/nonmatchings/src/commonact", DownFunc);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015C050);
ASM_LIT4_SLOT(D_00638E5C, 0.01f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015C520);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actCommonCling);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015C768);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015C968);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015CC28);
INCLUDE_ASM("asm/nonmatchings/src/commonact", BoxBarSoundOff);
INCLUDE_ASM("asm/nonmatchings/src/commonact", _boxbar_set_sound);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015CD88);
ASM_LIT4_SLOT(D_00638E60, 0.3f);
ASM_LIT4_SLOT(D_00638E64, 0.3f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", funcCommonFallDircorrect);
INCLUDE_ASM("asm/nonmatchings/src/commonact", correctJumpOrientByChain);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015D818);
ASM_LIT4_SLOT(D_00638E68, 0.1f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015E240);
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
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015E928);
ASM_LIT4_SLOT(D_00638E74, 0.005f);
ASM_LIT4_SLOT(D_00638E78, 10000.0f);
ASM_LIT4_SLOT(D_00638E7C, 0.005f);
ASM_LIT4_SLOT(D_00638E80, 90000.0f);
ASM_LIT4_SLOT(D_00638E84, 0.05f);
ASM_LIT4_SLOT(D_00638E88, 0.005f);
ASM_LIT4_SLOT(D_00638E8C, 360000.0f);
ASM_LIT4_SLOT(D_00638E90, 0.92f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015F7A0);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015FF58);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0015FFB0);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00160008);
INCLUDE_ASM("asm/nonmatchings/src/commonact", SetMotionDirectionSmooze);
ASM_LIT4_SLOT(D_00638E94, 3.1415927f);
ASM_LIT4_SLOT(D_00638E98, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", _ACTDebugPrint);
INCLUDE_ASM("asm/nonmatchings/src/commonact", ACTSendMailCorrect);
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
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00160B28);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00161510);
ASM_LIT4_SLOT(D_00638ED4, 0.2f);
ASM_LIT4_SLOT(D_00638ED8, 0.2f);
ASM_LIT4_SLOT(D_00638EDC, 0.1f);
ASM_LIT4_SLOT(D_00638EE0, 0.2f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00161AC0);
extern void AdjustRootPositionToVerticalSidePlaneOfWall(int a0, int a1, float a2);

void ACTAdjustPlane(int a0, int a1) {
    AdjustRootPositionToVerticalSidePlaneOfWall(a0, a1, 30.0f);
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", ACTAcceptMail);
INCLUDE_ASM("asm/nonmatchings/src/commonact", _ACTMotDirSmzDirect);
INCLUDE_ASM("asm/nonmatchings/src/commonact", WithMailFunc_Idling);
INCLUDE_ASM("asm/nonmatchings/src/commonact", WithMailFunc_BossDamaged);
INCLUDE_ASM("asm/nonmatchings/src/commonact", WithMailFunc_FallDead);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00161D48);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00161E48);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00161EF8);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_001626A0);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00162D50);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00162DE8);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonBarPull);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00162F98);
extern char D_00553188[];
extern void _ACTWait(int a0);
extern void debug_StdPrintfDummy();

void func_001631F0(volatile int a0) {
    debug_StdPrintfDummy(D_00553188);
    _ACTWait(0);
}
extern char D_005531A8[];

void func_00163220(volatile int a0) {
    debug_StdPrintfDummy(D_005531A8);
    _ACTWait(0);
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00163250);
ASM_LIT4_SLOT(D_00638EE4, 0.1f);
ASM_LIT4_SLOT(D_00638EE8, 3.1415927f);
ASM_LIT4_SLOT(D_00638EEC, 0.1f);
ASM_LIT4_SLOT(D_00638EF0, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonTruckLeverPull);
INCLUDE_ASM("asm/nonmatchings/src/commonact", motCommonTruckLeverPush);
INCLUDE_ASM("asm/nonmatchings/src/commonact", funcCommonRopeBefore);
INCLUDE_ASM("asm/nonmatchings/src/commonact", afterCommonRope);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_00163670);
INCLUDE_ASM("asm/nonmatchings/src/commonact", funcCommonSofaWakeup);
INCLUDE_ASM("asm/nonmatchings/src/commonact", _ACTMotReqResult);
INCLUDE_ASM("asm/nonmatchings/src/commonact", test_CURRENTORIENT);
INCLUDE_ASM("asm/nonmatchings/src/commonact", test_CURRENTROOT);
INCLUDE_ASM("asm/nonmatchings/src/commonact", StartCorrectPosition);
INCLUDE_ASM("asm/nonmatchings/src/commonact", IsCorrectPosition);
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
extern void sceVu0ScaleVector(void *a0, float f);

void _ACTMotDir_V(void *a0) {
    int local[4];
    sceVu0ScaleVector(local, -1.0f);
    SetMotionDirection(a0, local);
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", ACTMotDirToWall);
extern void GetCorrectOrientOfChain(void *buf, void *obj);

void SetCorrectOrientOfChain(void *a0) {
    int local[4];
    GetCorrectOrientOfChain(local, a0);
    SetMotionDirection(a0, local);
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", actAfterForceRope);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actAfterForceRopeSwing);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actAfterRopeJump);
INCLUDE_ASM("asm/nonmatchings/src/commonact", afterCommonRopeCliff);
INCLUDE_ASM("asm/nonmatchings/src/commonact", afterCommonRopeTurnSpecial);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actAfterDown);
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
INCLUDE_ASM("asm/nonmatchings/src/commonact", afterCommonStone);
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
INCLUDE_ASM("asm/nonmatchings/src/commonact", actAfterJump);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actAfterFall);
INCLUDE_ASM("asm/nonmatchings/src/commonact", actAfterFly);
INCLUDE_ASM("asm/nonmatchings/src/commonact", ClipCollisionWithField);
void afterCommonOneWall(int x) {
    volatile int local = x;
}
INCLUDE_ASM("asm/nonmatchings/src/commonact", ACTCheckFlagAttack);
INCLUDE_ASM("asm/nonmatchings/src/commonact", afterCommonBecarry);
INCLUDE_ASM("asm/nonmatchings/src/commonact", afterCommonTruckLever);
