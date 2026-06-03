#include "common.h"

typedef struct { int w[6]; } SugiRec;
extern SugiRec D_00706DA8[];

void SugiLeafGeo2(int a0, int a1) {
    D_00706DA8[a0].w[5] = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/sugiTree", SugiLeafDL2);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/sugiTree", InitSugiLeafGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/sugiTree", SugiLeafGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/sugiTree", InitSugiLeafGeo2);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/sugiTree", func_001EE648);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/sugiTree", func_001EE7E0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/sugiTree", func_001EE838);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/sugiTree", func_001EE8F0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/sugiTree", func_001EE978);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/sugiTree", func_001EE9A8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/sugiTree", func_001EEB10);
