#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aEnd);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aBridgeDown);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aGondolaDown);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aGondolaUp);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aFence);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aFenceDownChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aFenceUpChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aFenceDownChk2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aFenceUpChk2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aBridge);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aGondola);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aExit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aElv);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aEne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aEnemy1);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);

void actSt20aEnemy2(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_00178DB0(0x18) == 0) {
        _ACTWait(1);
    }
    Generator_MaskOff(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aEnemy3);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aBridgeMain);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aBridgeSwitch);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aGondolaMain);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aGondolaSwitch);
