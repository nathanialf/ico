#include "common.h"



extern int D_006337B8;
extern void func_001185A8(void *dst, void *src);
extern int D_00710BE0[];
extern int D_006337B0;
extern int D_00633F64;
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F6E28);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F71D0);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F74E8);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F77A0);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_GetMotion);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_GetExtMotion);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_GetGizmoMotion);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_setCounter);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_calcEnvelope);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", _RotTransCurrentMatrixYXZ);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_CalcObject);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_resetObjectCounter);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_SetFrame);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_CalcAnimation);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_CalcSdfCamera);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_addLightning);

void bga_DispLightning(void) {
    D_00633F64 = 0;
}

int bga_ResetCamera(void *p)
{
    int v = D_00633F64;
    if (v != 0) {
        func_001185A8(p, D_00710BE0);
        v = D_00633F64;
    } else {
        D_006337B0 = 0;
    }
    return v != 0 && D_006337B8 == 0;
}

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_GetCameraMatrix);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_InitSdfCamera);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_SetCamFrame);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_CheckAnimationFinish);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_CheckAnimationFrame);

