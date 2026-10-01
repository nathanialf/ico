#include "motionManager2.h"
#include "quaternion.h"
#include "actressLight.h"
#include "StageAnimation.h"

void SetActressLight(GObj *self, int rotFocus, int posFocus, int anim)
{
    char buf[16];
    int r1 = GetSkeltonFocusNode(self, rotFocus);
    int r2 = GetSkeltonFocusNode(self, posFocus);
    stage_SetLoopFlag(anim, 1);
    CopyQuaternion(buf, (char *)GOBJ_SUB(self)->nodeQuat + r1 * 16);
    RotQuaternionX(buf, 16384);
    RotQuaternionZ(buf, 16384);
    stage_PlayBgAnimation(anim, 0.0f, (char *)GOBJ_SUB(self)->nodeMtx + r2 * 64 + 48, buf);
    stage_SetLoopFlag(anim, 0);
}
