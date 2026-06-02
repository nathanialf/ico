#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/torch", torchOffSE);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/torch", LightTorchOn);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/torch", LightTorchOff);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/torch", moveTorch);

void CheckTorchChainReactionReverse(void) {
}

int TorchGeo(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return q[1];
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/torch", InitTorchGeo);

void TorchDL(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    q[3] = a1;
}

void IsTorchLightOn(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    q[4] = a1;
}
