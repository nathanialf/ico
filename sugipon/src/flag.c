#include "common.h"

extern void func_001189D0();
extern void file_Init();
extern void gif_SpriteOffset();
extern void gsb_SetFrame();
extern void gif_Line();
extern void func_0010F9D0();

int InitFlagGeo(char *a0) {
    func_001189D0(*(int *)(*(char **)(a0 + 0x50) + 0xC), a0 + 0x10);
    file_Init(*(int *)(a0 + 0x50));
    if (*(int *)a0 != 0) {
        char *fobj = *(char **)(a0 + 0x4);
        gif_SpriteOffset(*(int *)fobj);
        gsb_SetFrame(1, *(int *)(fobj + 0x34), 0x80);
        gif_Line(*(int *)(fobj + 0xC), *(int *)(fobj + 0x10), *(int *)(fobj + 0x4) << 1, 1);
        func_0010F9D0();
    }
    return 1;
}

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
