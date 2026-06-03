#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/wireLetter", DispWireLetter);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/wireLetter", DispWireString);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/wireLetter", DefaultColorWireString);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/wireLetter", ChangeColorWireString);

extern int D_004C36B0[];

void Draw2DBox(int a0, int a1, int a2) {
    D_004C36B0[0] = a0;
    D_004C36B0[1] = a1;
    D_004C36B0[2] = a2;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/wireLetter", func_001F2610);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/wireLetter", func_001F26F0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/wireLetter", func_001F2818);
