#include "common.h"

extern void gif_SpriteOrg(int a0, int a1);
extern int D_0062B708;

void SetLodLevel(void) {
    gif_SpriteOrg(0, D_0062B708);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lodManager", func_001D16F0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lodManager", func_001D1790);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lodManager", func_001D1948);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lodManager", func_001D1D58);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lodManager", func_001D1DF0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lodManager", func_001D1ED8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lodManager", func_001D1F68);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lodManager", func_001D2060);

extern int D_0062C20C;
extern int D_0062C210;

void func_001D2130(void) {
    D_0062C20C = 0;
    D_0062C210 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lodManager", func_001D2140);

int func_001D2168(int a0) {
    return a0 ? D_0062C210 : D_0062C20C;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lodManager", func_001D2180);
