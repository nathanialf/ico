#include "common.h"

extern char D_0028F8F0[];
extern int D_00639EA4;
extern void GetRootPosition(void *a0, int a1);
extern int GetSkeltonFocusNode(int a0, int a1);
extern void GetWormCaptureVector__pn(void *a0, int a1, int a2, float f12) __asm__("GetWormCaptureVector");
extern void GetWormRoute(int a0, int a1);
extern void SetDirectRootPosition(int a0, void *a1);
extern void SetDirectWormTargetPos(int a0, int a1);
extern void SetWormReduceRatio(int a0, float f12);
extern void sceVu0AddVector(void *a0, void *a1, void *a2);

INCLUDE_ASM("asm/nonmatchings/src/worm", outerProcess);
INCLUDE_ASM("asm/nonmatchings/src/worm", simulate);
INCLUDE_ASM("asm/nonmatchings/src/worm", getAnimation);
INCLUDE_ASM("asm/nonmatchings/src/worm", disp);
INCLUDE_ASM("asm/nonmatchings/src/worm", GetWormRoute);
INCLUDE_ASM("asm/nonmatchings/src/worm", InitWormGeo);
extern void sceVu0Normalize(void *a0, void *a1);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);
extern void sceVu0SubVector(void *a0, void *a1);

void GetWormCaptureVector(void *a0, char *a1, float f12) {
    sceVu0SubVector(a0, (void *)(*(int *)(a1 + 0x15C) + 0x50));
    sceVu0Normalize(a0, a0);
    sceVu0ScaleVector(a0, a0, f12);
}
INCLUDE_ASM("asm/nonmatchings/src/worm", WormGeo);
extern void disp(void);

void WormDL(void) {
    disp();
}
INCLUDE_ASM("asm/nonmatchings/src/worm", SetDirectWormTargetPos);
void SetWormReduceRatio(int a0, float f12) {
    *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8) = f12;
}
INCLUDE_ASM("asm/nonmatchings/src/worm", TraceWormRoute);
