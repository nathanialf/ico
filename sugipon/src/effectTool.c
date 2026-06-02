#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", _dispParam);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", editParam);

extern int D_0062B5CC;
extern int D_0062B5D4;

void dispXZYZCircle(void) {
    D_0062B5CC = 0;
    D_0062B5D4 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", dispCircle2);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", setQ);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", dispEffectToolField);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", EditTarget);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", saveEffectData);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", moveEffectToolGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", execEffectTool);
