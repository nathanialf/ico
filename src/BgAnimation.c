#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_InitData);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_initLightEnvelope);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_ApplyDObject);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_GetMotion);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_GetMotionParticle);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_GetMotionLightning);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_GetExtMotion);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_GetGizmoMotion);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_calcEnvelope);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", _RotTransCurrentMatrixYXZ);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_CalcObject);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_resetObjectCounter);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_SetFrame);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_CalcAnimation);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_CalcSdfCamera);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_addLightning);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_DispLightning);
extern int D_0063C4B4;

void bga_ResetCamera(void) {
    D_0063C4B4 = 0;
}
extern int D_0063BCC0;
extern int D_0063BCC8;
extern int D_0063C4B4;
extern int D_007281F0[];
extern void _CopyMatrix(void *dst, void *src);

int bga_GetCameraMatrix(void *p)
{
    int v = D_0063C4B4;
    if (v != 0) {
        _CopyMatrix(p, D_007281F0);
        v = D_0063C4B4;
    } else {
        D_0063BCC0 = 0;
    }
    return v != 0 && D_0063BCC8 == 0;
}
extern char D_0063BCE0[];
extern char D_006215D8[];
extern char D_00621598[];
extern char D_0063BCD8[];
char *bga_InitSdfCamera(char *a0) {
    if (strncmp(a0, D_0063BCE0, 3) != 0) {
        debug_StdPrintfDummy(D_006215D8);
        debug_assert(D_00621598, 0x415);
        __assert(D_00621598, 0x415, D_0063BCD8);
    }
    return a0;
}
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_SetCamFrame);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_CheckAnimationFinish);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_CheckAnimationFrame);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_CheckAnimationFrameIn);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_CheckSdfCameraFinish);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_CheckSdfCameraFrame);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_CheckSdfCameraFrameIn);
void bga_SetCameraForceOff(void) {
    D_0063BCC8 = 1;
}
extern int D_0063BCCC;

void bga_InitBGA(void)
{
    D_0063BCC8 = 0;
    D_0063BCCC = 0;
}
extern int D_0063BCC4;

void bga_SetUniqAnimationFlag(int val) {
    D_0063BCC4 = val;
}
extern int D_0028F4D4[];
extern void freeseki(void *p);

void bga_ResetAnimation(void) {
    void *p;
    D_0063C4B4 = 0;
    if (D_0028F4D4[0] != 0) {
        return;
    }
    p = (void *)D_0063BCCC;
    D_0063BCCC = 0;
    if (p == 0) {
        return;
    }
    do {
        void *next = *(void **)((char *)p + 0x154);
        freeseki(p);
        p = next;
    } while (p != 0);
}
extern float D_0063BCC0__pn __asm__("D_0063BCC0");

float bga_GetZoom(void)
{
    return D_0063BCC0__pn;
}
