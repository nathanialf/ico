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

extern int D_0062C074;
extern int D_0062C078;

void Camctrl_ExitEveRock(int a0, int a1) {
    D_0062C074 = a0;
    D_0062C078 = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/camera-root", Camctrl_SetTarget);

extern int D_0062C074;

int GetCameraDefaultTargetGObj(void) {
    return D_0062C074;
}
