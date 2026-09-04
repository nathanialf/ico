#include "common.h"





extern int tex_SetClutAnimation();
extern int D_00632CA4;
extern int  D_00631970;
extern void _SetCurrentMatrix(void *p0);
extern void _NormalizeVector();
extern void _ClearTransCurrentMatrix(void);
extern void mc_TransMicroCode(void *dst, void *src);
extern void _ApplyCurrentMatrix();
extern int D_00631D40;
extern void reg_DispAccessoryWithShadow();
INCLUDE_ASM("asm/nonmatchings/src/Shadow", shadow_Reset);

INCLUDE_ASM("asm/nonmatchings/src/Shadow", shadow_Draw);

INCLUDE_ASM("asm/nonmatchings/src/Shadow", shadow_Render);

INCLUDE_ASM("asm/nonmatchings/src/Shadow", shadow_getShadowVectorAverage);

INCLUDE_ASM("asm/nonmatchings/src/Shadow", shadow_EntryClusterShadow);

INCLUDE_ASM("asm/nonmatchings/src/Shadow", shadow_EntryNormalShadow);

INCLUDE_ASM("asm/nonmatchings/src/Shadow", __GetCameraPos);

INCLUDE_ASM("asm/nonmatchings/src/Shadow", func_001224E0);

INCLUDE_ASM("asm/nonmatchings/src/Shadow", func_001227C8);

INCLUDE_ASM("asm/nonmatchings/src/Shadow", func_00122BA0);

void func_00122C40(int a0, int a1, int a2, int a3)
{
    reg_DispAccessoryWithShadow(a0, a1, a2, a3);
}

void func_00122C48(int val) {
    D_00631D40 = val;
}

void reg_TransTexturePacket(int a0)
{
    if (a0 >= 0) {
        D_00632CA4 += tex_SetClutAnimation(a0);
    }
}

void shadow_DispCancel(void) {
    D_00631D40 = 0;
}

int reg_GetShinePri(int a0)
{
    switch (a0) {
        case 1: return 7;
        case 2: return 8;
        case 3: return 9;
    }
    return 7;
}

INCLUDE_ASM("asm/nonmatchings/src/Shadow", shadow_Init);

INCLUDE_ASM("asm/nonmatchings/src/Shadow", func_00123140);

extern char D_00555920[];
extern void debug_StdPrintfDummy(char *fmt, ...);

void func_00123C00(void)
{
    float buf[4];
    debug_StdPrintfDummy(D_00555920);
}

void func_00123C20(int *self, int p)
{
    mc_TransMicroCode(self, p + 0x830);
    _SetCurrentMatrix((int)D_00631970 + 0x80);
    _ClearTransCurrentMatrix();
    _ApplyCurrentMatrix(self, self);
    _NormalizeVector(self, self);
}

INCLUDE_ASM("asm/nonmatchings/src/Shadow", func_00123C70);

