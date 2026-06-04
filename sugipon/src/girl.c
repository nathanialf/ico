#include "common.h"

extern int iosPadDevRead(int a0, void *a1);
extern int D_00629DEC;

int func_001CE7D8(void *a0) {
    iosPadDevRead(D_00629DEC, a0);
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/girl", func_001CE800);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/girl", InitGirlGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/girl", GirlGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/girl", debugWireStringGirl);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/girl", GirlDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/girl", GirlAI);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/girl", SetGirlClothDispSwitch);
