#include "common.h"



extern int D_0063318C;
extern char D_00633188;
extern int D_00633EC8;
extern int D_00633EC4;
extern int D_00633ECC;
void staffRollStart(int unused, int a, int b, int c) {
    D_00633EC4 = a;
    D_00633EC8 = b;
    D_00633ECC = c;
}

INCLUDE_ASM("asm/nonmatchings/src/staffroll", staffRollScroll);

void staffRollNameOut(void) {
    D_00633188 = 0;
    D_0063318C = -1;
}

INCLUDE_ASM("asm/nonmatchings/src/staffroll", staffRollMain);

INCLUDE_ASM("asm/nonmatchings/src/staffroll", staffRollWide);

INCLUDE_ASM("asm/nonmatchings/src/staffroll", func_001B8388);

INCLUDE_ASM("asm/nonmatchings/src/staffroll", func_001B84C8);

