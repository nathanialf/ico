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

extern int D_0062B07C;
extern void *D_0062B698;
extern void ClipWallDebug(void *a0, int a1);

void func_001CD630(void) {
    if (D_0062B07C && D_0062B698)
        ClipWallDebug(D_0062B698, 0);
}

extern void *D_0062B698;

int func_001CD658(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    D_0062B698 = a0;
    p[0x1D] = 0;
    return 0;
}
