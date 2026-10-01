#include "motionManager2.h"
#include "quaternion.h"
#include "actressLight.h"
#include "StageAnimation.h"

void SetActressLight(GObj *a0, int a1, int a2, int a3)
{
    char buf[0x10];
    int r1 = GetSkeltonFocusNode(a0, a1);
    int r2 = GetSkeltonFocusNode(a0, a2);
    stage_SetLoopFlag(a3, 1);
    CopyQuaternion(buf, (char *)GOBJ_SUB(a0)->nodeQuat + r1 * 0x10);
    RotQuaternionX(buf, 0x4000);
    RotQuaternionZ(buf, 0x4000);
    stage_PlayBgAnimation(a3, 0.0f, (char *)GOBJ_SUB(a0)->nodeMtx + r2 * 0x40 + 0x30, buf);
    stage_SetLoopFlag(a3, 0);
}
