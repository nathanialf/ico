#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/flag", InitFlagGeo);

int FlagGeo(void *a0) {
    int *t = *(int **)((char *)a0 + 0x4);
    t[0xC] = 1;
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/flag", FlagDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/flag", func_001CCDE8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/flag", func_001CD388);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/flag", func_001CD478);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/flag", func_001CD630);

extern void *D_0062B698;

int func_001CD658(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    D_0062B698 = a0;
    p[0x1D] = 0;
    return 0;
}
