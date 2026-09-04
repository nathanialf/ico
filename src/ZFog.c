#include "common.h"






extern int tex_scrollClut();
extern int D_00633C60;
extern short D_00681278[];
extern int D_00681538[];
extern int D_006812D0[];
INCLUDE_ASM("asm/nonmatchings/src/ZFog", fog_MakeFogClut);

INCLUDE_ASM("asm/nonmatchings/src/ZFog", fog_DrawFog);

int fog_FogTool(int a0)
{
    int ret = -1;
    int i;
    for (i = 0; i < 11; i++)
    {
        if ((1 << i) >= a0)
        {
            ret = i;
            break;
        }
    }
    return ret;
}

int func_0012FD30(void)
{
    return tex_scrollClut();
}

extern int tex_textureAnimation(void *a0, int a1);

int func_0012FD50(void *a0)
{
    return tex_textureAnimation(a0, 0);
}

INCLUDE_ASM("asm/nonmatchings/src/ZFog", tex_GetTextureNo);

int *func_0012FE08(int idx)
{
    return (int *)((char *)D_006812D0 + idx * 0x2E8);
}

int *func_0012FE20(int idx)
{
    return (int *)((char *)D_006812D0 + idx * 0x2E8);
}

void tex_SetSamplingType(int *a0, int a1, int a2)
{
    long long *slot = (long long *)((char *)a0 + 0x78);
    *slot = (*slot & ~(long long)0xE0) | (a1 << 5) | (a2 << 6);
}

int *func_0012FE60(int idx)
{
    return (int *)((char *)D_00681538 + idx * 0x2E8);
}

short tex_GetVramFreeAddress(int a0)
{
    return *(short *)((char *)D_00681278 + a0 * 6);
}

INCLUDE_ASM("asm/nonmatchings/src/ZFog", func_0012FE98);

INCLUDE_ASM("asm/nonmatchings/src/ZFog", func_0012FF58);

int func_0012FFE8(void) {
    return D_00633C60;
}

INCLUDE_ASM("asm/nonmatchings/src/ZFog", tex_SetUVScroll);

INCLUDE_ASM("asm/nonmatchings/src/ZFog", tex_Init);

