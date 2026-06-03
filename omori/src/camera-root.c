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


/* recovered struct shapes */
typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    short              f_12;  /* 0x12 */
    unsigned long long f_18;  /* 0x18 */
} S_006C9F60;

typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
} S_006C9F80;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
} S_006C9FA0;

typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
} S_00287150;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00554C30;  /* stride 0x4 */

/* end struct shapes */
