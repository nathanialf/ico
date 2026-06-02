#include "common.h"

extern void MatrixDrive_TurnObjectMatrix(int a0, void *a1);

void GetWaterReaction(int a0, char *a1) {
    MatrixDrive_TurnObjectMatrix(a0, *(char **)(a1 + 0x15C) + 0x5B0);
}

extern void MatrixDrive_TurnObjectMatrix(int a0, void *a1);

void CheckFieldContact(int a0, char *a1) {
    MatrixDrive_TurnObjectMatrix(a0, *(char **)(a1 + 0x15C) + 0x580);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", dispPlane);

extern void GetRootMatrixRotOffset(int a0, void *a1, void *a2);

void GetOrientOfWallOfGObj(int a0, int **a1) {
    GetRootMatrixRotOffset(a0, a1, (char *)a1[0x57] + 0x510);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetOrientOfCliffOfGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", SetMotionDirection);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", _GetMotionDirection);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", SetMotionDirectionWithLimit);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetRootPosOfNextFrame);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", AdjustMotionHeightToField);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetLowerPlaneCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", getLowerPlaneCollisionE);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", calcFootIK);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", InitMotionGeoInfo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", dispSkeltonHierarchy);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", DispSkelton);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", SlopeIKControl);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetPureVerticalPlaneOfCurrentPosition);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", getVerticalElementOfWallNormal);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", AdjustVerticalSidePlaneOfWall);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetPureVerticalPlane);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", _getS16MotRotElem);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", _getMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetStreamMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", copyMotionWithNodeHrc);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", CopyMotionWithNodeHrc);

void *GetFloatingMotion(int **a0) {
    return (char *)a0[0x57] + 0x670;
}

int MakeMirrorMotion(int **a0) {
    return a0[0x57][0x74];
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetFloatingShapeMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", FeedbackWallWorkInfoToBrainSystem);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetMotionPointer);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetCollisionOfLastActiveField);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", DebugDisp1Collision);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", DebugDisp1CollisionWithColor);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", SetMotionBlendlessNode);

void ClearMotionBlendlessNode(int **a0, int a1) {
    int *p = a0[0x57];
    p[0x132] = a1;
}

float InitMotionStateInfo(int **a0) {
    int *p = a0[0x57];
    return *(float *)((char *)p + 0x49C);
}

int GetSkeltonFocusNode(int **a0) {
    return a0[0x57][0x124];
}

void AdjustMotionHeightToNearestField(int **a0) {
    int *p = a0[0x57];
    p[0x135] = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", SetRootUpdateMode);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", ForMotionViewer_GetCurrentAnimationFrame);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", ForMotionViewer_GetCurrentMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", EnableMotionOrientUpdate);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", DisableMotionOrientUpdate);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", CheckFloorAttribute);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", CheckWallAttribute);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", CheckPureWallAttribute);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", CheckPureCliffAttribute);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetStreamShapeMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetDifferenceFromWallUpperField);

void GetDifferenceFromLastField(int **a0) {
    int *p = a0[0x57];
    p[0x130] = 1;
}

void GetDifferenceFromLowerField(int **a0) {
    int *p = a0[0x57];
    p[0x130] = 0;
}

float GetDifferenceFromWallLowerPlane(int **a0) {
    int *p = a0[0x57];
    return *(float *)((char *)p + 0x608);
}

int GetDifferenceFromWallUpperPlane(int **a0) {
    return a0[0x57][0x17C];
}

int DisableChangeRootUpdateMode(int **a0) {
    return a0[0x57][0x17D];
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", EnableChangeRootUpdateMode);

float GetRopeHangablePos(int **a0) {
    int *p = a0[0x57];
    return *(float *)((char *)p + 0x590);
}

float GetMotionFrameFlag1(int **a0) {
    int *p = a0[0x57];
    return *(float *)((char *)p + 0x570);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetMotionFrameFlag2);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetHeightOfFieldPlaneDifference);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetHeightOfWallFromGObj);

void GetHeightOfCliffFromGObj(int **a0, float a1) {
    int *p = a0[0x57];
    *(float *)((char *)p + 0x4A8) = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", InitMotionRotElem);

extern int D_00629E4C;

void SetMotionNodeFixModeParameter(int a0) {
    D_00629E4C = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetRootProjectionPosOfGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", SetMotionPlaySpeedRatio);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", ClearMotionGeometryInfo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", SetSkeltonDispSwitch);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", CopyMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager2", GetMotionRootPos);
