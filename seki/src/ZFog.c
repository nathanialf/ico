#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/ZFog", fog_MakeFogClut);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/ZFog", fog_DrawFog);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/ZFog", fog_FogTool);

extern void tex_scrollClut(void);

void func_0012FC08(void) {
    tex_scrollClut();
    __asm__ __volatile__("");
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/ZFog", func_0012FC28);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/ZFog", func_0012FC48);

extern unsigned char D_0067AE50[];

void *func_0012FCE0(int a0) {
    return &D_0067AE50[a0 * 0x2E8];
}

void *func_0012FCF8(int a0) {
    return &D_0067AE50[a0 * 0x2E8];
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/ZFog", func_0012FD10);

extern unsigned char D_0067B0B8[];

void *func_0012FD38(int a0) {
    return &D_0067B0B8[a0 * 0x2E8];
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/ZFog", func_0012FD50);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/ZFog", func_0012FD70);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/ZFog", func_0012FE30);

extern int D_0062BF68;

int func_0012FEC0(void) {
    return D_0062BF68;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/ZFog", func_0012FEC8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/ZFog", func_00130000);
