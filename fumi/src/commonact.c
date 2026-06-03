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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_001561E8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", WithMailFunc_AttackRejectInQueen);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", GetCorrectOrientOfChain);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", CollisCheckInRope);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_00156750);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonRope);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", motCommonRopeTurnR);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", motCommonRopeTurnL);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_00156D18);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonRopeClimbEnd1);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonRopeCliff);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", TestCageUpDown);

extern void dispPlane(void *a0, void *a1);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", func_0015B4C8);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonDodge);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonEdgeHang);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", funcCommonBeginReady);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", funcCommonEndReady);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonBecarry);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonRevive);

void actCommonReviveAir(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonPlay);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonOne);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/commonact", actCommonDelete);
