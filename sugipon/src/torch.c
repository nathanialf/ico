#include "common.h"
#include "ico/types.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/torch", torchOffSE);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/torch", LightTorchOn);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/torch", LightTorchOff);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/torch", moveTorch);

void CheckTorchChainReactionReverse(void) {
}

int TorchGeo(void *a0) {
    return GOBJ_SUB(a0)->p_7F0->f_4;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/torch", InitTorchGeo);

void TorchDL(void *a0, int a1) {
    GOBJ_SUB(a0)->p_7F0->f_C = a1;
}

void IsTorchLightOn(void *a0, int a1) {
    GOBJ_SUB(a0)->p_7F0->f_10 = a1;
}
