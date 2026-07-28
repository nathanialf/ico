#include "common.h"


extern int D_006333D8;
extern int D_00632DB4;
extern int ClipWallDebug();
extern void func_001185A8();
extern void func_001227C8();
extern void gif_SpriteOffset();
extern void gsb_SetFrame();
extern void gif_Line();
extern void func_0010F630();

int InitFlagGeo(char *a0) {
    func_001185A8(*(int *)(*(char **)(a0 + 0x50) + 0xC), a0 + 0x10);
    func_001227C8(*(int *)(a0 + 0x50), 0xA);
    if (*(int *)a0 != 0) {
        char *fobj = *(char **)(a0 + 0x4);
        gif_SpriteOffset(*(int *)fobj);
        gsb_SetFrame(1, *(int *)(fobj + 0x34), 0x80);
        gif_Line(*(int *)(fobj + 0xC), *(int *)(fobj + 0x10), *(int *)(fobj + 0x4) << 1, 1);
        func_0010F630();
    }
    return 1;
}

int FlagGeo(char *self) {
    char *p = *(char **)(self + 0x4);
    *(int *)(p + 0x30) = 1;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/flag", FlagDL);

INCLUDE_ASM("asm/nonmatchings/src/flag", func_001CFB58);

INCLUDE_ASM("asm/nonmatchings/src/flag", func_001D00F8);

INCLUDE_ASM("asm/nonmatchings/src/flag", func_001D01E8);

void func_001D03A0(void)
{
    int v0 = D_00632DB4;
    int a0 = D_006333D8;
    if (v0 == 0) {
        return;
    }
    if (a0 == 0) {
        return;
    }
    return ClipWallDebug(a0, 0);
}

int func_001D03C8(int *self)
{
    int *p = (int *)self[0x57];
    D_006333D8 = self;
    p[0x1D] = 0;
    return 0;
}

