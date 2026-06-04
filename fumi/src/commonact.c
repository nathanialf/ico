#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", ACTSetPositionWithFitting);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", ACTSetPositionNodeWithFitting);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", ChangeMailInLadder);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", _ACTCorrectMsg);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", ACTGetOrientFromIntrK);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_00155738);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", ACTRunIntrCorrect);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_00155FF8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", WithMailFunc_WayBeginPosError);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", WithMailFunc_AttackFail);

extern void func_0018F2A0(void *a0);

void func_001561E8(void *a0) {
    if (a0 && *(int *)((char *)a0 + 0xC) == 4)
        func_0018F2A0(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", WithMailFunc_AttackRejectInQueen);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", GetCorrectOrientOfChain);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", CollisCheckInRope);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_00156750);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonRope);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", motCommonRopeTurnR);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", motCommonRopeTurnL);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_00156D18);

extern void BoxExtGeoRestore(void *a0);
extern void getRootMatrix(void *a0);

void actCommonRopeClimbEnd1(void *a0) {
    char *s = *(char **)((char *)a0 + 0x164);
    int state = *(int *)(s + 0x30);
    if (state == 0x31) goto l1;
    if (state == 0x33) goto l2;
    return;
l1:
    BoxExtGeoRestore(*(void **)(s + 0x138));
    return;
l2:
    getRootMatrix(*(void **)(s + 0x5E8));
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonRopeCliff);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", TestCageUpDown);

extern void dispPlane(void *a0, void *a1);

extern void ACTParaStatus_Clear(int a0);
void actCommonRopeSpecial(void *a0) {
    int *p = *(int **)((char *)a0 + 0x164);
    void *x = *(void **)((char *)p + 0x678);
    dispPlane(a0, (char *)x + 0x350);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", lever_nego1);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", SetDirectRootPositionXZ);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_00157E70);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonLever);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", EBRAIN_SEND_MES);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", DamageFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", DownFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonDown);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonDie);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", Cling);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonCling);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonSlip);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonStoneDead);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonStone);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", BoxBarSoundOn);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", BoxBarSoundOff);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", _boxbar_set_sound);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonBox);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015AF10);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonBar);

extern int D_00629DF4;
extern void lt_fade_status(int a0);

void func_0015B4C8(void) {
    if (D_00629DF4 == 0) {
        D_00629DF4 = 1;
        lt_fade_status(0x3A);
    }
}

extern void setNodePursueParticleEffectWithUpperLimit(int a0, int a1, float a2);

void funcCommonJumpDircorrect(int a0, int a1) {
    setNodePursueParticleEffectWithUpperLimit(a0, a1, 30.0f);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", funcCommonFallDircorrect);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", correctJumpOrientByChain);

void actCommonJump(void *a0) {
    int *p = *(int **)((char *)a0 + 0x164);
    int *q = *(int **)((char *)p + 0x670);
    q[0x81]--;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonFall);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", debugDispFlyLimit);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", debugDispSphere);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", getLandOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", getAvoidCollisionFlyLevel);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", emergencyCheck);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", flyCoreLoop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonFly);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonLadder);

extern void _ACTWait(int a0);

void actCommonDodge(volatile int a0) {
    char *s = *(char **)(a0 + 0x164);
    *(unsigned int *)(s + 0x34) = 0xFFFFFFFF;
    _ACTWait(0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonEdgeHang);

extern void debug_assertMessage(void *a0);
extern void _ACTWait(int a0);
extern char D_00552F18[];
extern char D_00552F38[];

void funcCommonBeginReady(volatile int a0) {
    debug_assertMessage(D_00552F18);
    _ACTWait(0);
}

void funcCommonEndReady(volatile int a0) {
    debug_assertMessage(D_00552F38);
    _ACTWait(0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", funcCommonEndExec);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", funcCommonError);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", SetMotionDirectionSmooze);

void _ACTDebugPrint(int **a0, int a1, int a2) {
    int *p = a0[0x59];
    p[0x60] = a2;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", ACTSendMailCorrect);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", _ACTCommonMailTest);

void E3_LeverCheck(void *a0) {
    int *p = *(int **)((char *)a0 + 0x164);
    int *q = *(int **)((char *)p + 0x670);
    q[0x94] = 0;
}

extern void *ExecMotionOrient(void *a0, void *a1, void *a2);

int actCommonBecarry(void *a0, void *a1) {
    char *s = *(char **)((char *)a0 + 0x164);
    void *r = ExecMotionOrient(a0, a1, s + 0x610);
    *(void **)(s + 0x110) = r;
    return *(int *)((char *)r + 0xC) != 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", subCommonIdle);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", ContinueCorrectPosition);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonTurn);

int actCommonBackhand(void *a0) {
    int *p = *(int **)((char *)a0 + 0x164);
    int *q = *(int **)((char *)p + 0x670);
    long long v = ((unsigned int *)q)[0x2F];
    return (int)v & 1;
}

typedef struct { int w[6]; } SlowrunRec;
extern SlowrunRec D_0028E680[];

void actCommonSlowrun(int a0, int a1) {
    D_0028E680[a0].w[2] = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", ACT_LAYOUT_GAMEOVER);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", ACTAdjustPlane);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", _ACTMotDirSmzDirect);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", WithMailFunc_Idling);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", WithMailFunc_BossDamaged);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", WithMailFunc_FallDead);

void actCommonRevive(volatile int a0) {
    ACTParaStatus_Clear(a0);
}

void actCommonReviveAir(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actCommonPlay(volatile int a0) {
    ACTParaStatus_Clear(a0);
}

void actCommonOne(volatile int a0) {
    int x = a0;
    int y = a0;
    *(int *)(*(int *)(*(int *)(x + 0x164) + 0x670) + 0x2A0) = -1;
    *(int *)(*(int *)(*(int *)(y + 0x164) + 0x670) + 0x2A4) = 0;
}

extern void actCommonRopeCliff(int a0, int a1);

void actCommonDelete(volatile int a0) {
    actCommonRopeCliff(a0, 0);
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
} S_00288FD0;  /* stride 0x14 */

typedef struct {
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_28;  /* 0x28 */
} S_0027E700;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_8;  /* 0x08 */
} S_0028E680;  /* stride 0x18 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0055D4B0;  /* stride 0x4 */

/* end struct shapes */
