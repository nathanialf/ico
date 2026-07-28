#include "common.h"





extern int tex_SetClutAnimation();
extern int D_00632CA4;
extern int  D_00631970;
extern void _PopCurrentMatrix(void *p0);
extern void _SetCurrentMatrix();
extern void func_00117CE0(void);
extern void mc_TransMicroCode(void *dst, void *src);
extern void _ClearTransCurrentMatrix();
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

void shadow_KillShadow(int a0)
{
    if (a0 >= 0) {
        D_00632CA4 += tex_SetClutAnimation(a0);
    }
}

void shadow_DispCancel(void) {
    D_00631D40 = 0;
}

int shadow_SetLength(int a0)
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

INCLUDE_ASM("asm/nonmatchings/src/Shadow", func_00123C00);

void func_00123C20(int *self, int p)
{
    mc_TransMicroCode(self, p + 0x830);
    _PopCurrentMatrix((int)D_00631970 + 0x80);
    func_00117CE0();
    _ClearTransCurrentMatrix(self, self);
    _SetCurrentMatrix(self, self);
}

INCLUDE_ASM("asm/nonmatchings/src/Shadow", func_00123C70);

