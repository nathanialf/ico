#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetWaterReaction);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", CheckFieldContact);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", dispPlane);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetOrientOfWallOfGObj);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetOrientOfCliffOfGObj);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", SetMotionDirection);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", _GetMotionDirection);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", SetMotionDirectionWithLimit);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetRootPosOfNextFrame);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", AdjustMotionHeightToField);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetLowerPlaneCollision);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", getLowerPlaneCollisionE);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", calcFootIK);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", InitMotionGeoInfo);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", dispSkeltonHierarchy);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", DispSkelton);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", SlopeIKControl);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetPureVerticalPlaneOfCurrentPosition);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", getVerticalElementOfWallNormal);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", AdjustVerticalSidePlaneOfWall);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetPureVerticalPlane);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", _getS16MotRotElem);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", _getMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetStreamMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", copyMotionWithNodeHrc);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", CopyMotionWithNodeHrc);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetFloatingMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", MakeMirrorMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetFloatingShapeMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", FeedbackWallWorkInfoToBrainSystem);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetMotionPointer);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetCollisionOfLastActiveField);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", DebugDisp1Collision);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", DebugDisp1CollisionWithColor);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", SetMotionBlendlessNode);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", ClearMotionBlendlessNode);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", InitMotionStateInfo);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetSkeltonFocusNode);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", AdjustMotionHeightToNearestField);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", SetRootUpdateMode);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", ForMotionViewer_GetCurrentAnimationFrame);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", ForMotionViewer_GetCurrentMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", EnableMotionOrientUpdate);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", DisableMotionOrientUpdate);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", CheckFloorAttribute);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", CheckWallAttribute);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", CheckPureWallAttribute);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", CheckPureCliffAttribute);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetStreamShapeMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetDifferenceFromWallUpperField);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetDifferenceFromLastField);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetDifferenceFromLowerField);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetDifferenceFromWallLowerPlane);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetDifferenceFromWallUpperPlane);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", DisableChangeRootUpdateMode);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", EnableChangeRootUpdateMode);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetRopeHangablePos);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetMotionFrameFlag1);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetMotionFrameFlag2);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetHeightOfFieldPlaneDifference);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetHeightOfWallFromGObj);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetHeightOfCliffFromGObj);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", InitMotionRotElem);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", SetMotionNodeFixModeParameter);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetRootProjectionPosOfGObj);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", SetMotionPlaySpeedRatio);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", ClearMotionGeometryInfo);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", SetSkeltonDispSwitch);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", CopyMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager2", GetMotionRootPos);

