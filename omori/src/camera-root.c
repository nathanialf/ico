#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-root", SetWSMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-root", ConvertCameraSet);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-root", MakeCameraMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-root", CameraEditManual);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-root", DebugCameraManual);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-root", DebugCameraSemiAuto);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-root", BackToGameCamera);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-root", GetCameraInfomationFromGlobalPosition);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-root", InitCamera);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-root", SetCameraMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-root", Camctrl_ExitEveRock);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-root", Camctrl_SetTarget);

extern int D_0062C074;

int GetCameraDefaultTargetGObj(void) {
    return D_0062C074;
}
