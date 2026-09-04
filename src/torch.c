#include "common.h"

#include "ico/types.h"
#include "vu0.h"

INCLUDE_ASM("asm/nonmatchings/src/torch", torchOffSE);
INCLUDE_ASM("asm/nonmatchings/src/torch", LightTorchOn);
INCLUDE_ASM("asm/nonmatchings/src/torch", LightTorchOff);
INCLUDE_ASM("asm/nonmatchings/src/torch", torchDrainControl);
INCLUDE_ASM("asm/nonmatchings/src/torch", moveTorch);
INCLUDE_ASM("asm/nonmatchings/src/torch", setPauseFlag);
INCLUDE_ASM("asm/nonmatchings/src/torch", CheckTorchChainReactionReverse);
INCLUDE_ASM("asm/nonmatchings/src/torch", procChainReaction);
INCLUDE_ASM("asm/nonmatchings/src/torch", TorchGeo);
INCLUDE_ASM("asm/nonmatchings/src/torch", InitTorchGeo);
void TorchDL(void) {}
int IsTorchLightOn(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x20);
}
INCLUDE_ASM("asm/nonmatchings/src/torch", CheckTorchChainReaction);
void SetTorchLife(char *a0, int a1, int a2) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    *(int *)(p + 0x28) = a1;
    *(int *)(p + 0x2C) = a1 - a2;
}
void SetTorchChainReactionFlag(char *a0, int a1) {
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x30) = a1;
}
extern void CopyVector(void *a0, void *a1);
extern void GetRootPosition(void *a0, void *a1);
extern void sceVu0SubVector(void *a0, void *a1, void *a2);

void UpdateRealTimeGeometryValue(char *a0) {
    int buf[4];
    char *sub;
    GetRootPosition(buf, a0);
    sub = *(char **)(a0 + 0x15C);
    sceVu0SubVector(sub + 0x130, buf, sub + 0x1F0);
    sub = *(char **)(a0 + 0x15C);
    CopyVector(sub + 0x1F0, buf);
}
