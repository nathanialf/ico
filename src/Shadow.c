#include "common.h"

#include "vu0.h"

INCLUDE_ASM("asm/nonmatchings/src/Shadow", shadow_Reset);
INCLUDE_ASM("asm/nonmatchings/src/Shadow", shadow_Draw);
extern char D_0054FD50[];
extern void debug_StdPrintfDummy();

void shadow_Render(void)
{
    float buf[4];
    debug_StdPrintfDummy(D_0054FD50);
}
INCLUDE_ASM("asm/nonmatchings/src/Shadow", shadow_getShadowVectorAverage);
INCLUDE_ASM("asm/nonmatchings/src/Shadow", shadow_EntryClusterShadow);
INCLUDE_ASM("asm/nonmatchings/src/Shadow", shadow_EntryNormalShadow);
extern char *D_00639CF0;
extern void _ApplyCurrentMatrix(void *a0, void *a1);
extern void _ClearTransCurrentMatrix(void);
extern void _PopCurrentMatrix(void);
extern void _PushCurrentMatrix(void *a0);
extern void _ScaleVector(void *a0, void *a1, float a2);
extern void _SetCurrentMatrix(void *a0);
extern void _TransposeCurrentMatrix(void);

void __GetCameraPos(void *a0) {
    _PushCurrentMatrix(a0);
    _SetCurrentMatrix(D_00639CF0 + 0x80);
    _ClearTransCurrentMatrix();
    _TransposeCurrentMatrix();
    _ApplyCurrentMatrix(a0, D_00639CF0 + 0xB0);
    _ScaleVector(a0, a0, -1.0f);
    *(float *)((char *)a0 + 0xC) = 1.0f;
    _PopCurrentMatrix();
}
INCLUDE_ASM("asm/nonmatchings/src/Shadow", shadow_RenderVolume);
INCLUDE_ASM("asm/nonmatchings/src/Shadow", shadow_RenderVolumeMulti);
INCLUDE_ASM("asm/nonmatchings/src/Shadow", shadow_MakeObjectData);
INCLUDE_ASM("asm/nonmatchings/src/Shadow", shadow_Tool);
extern int D_0063A17C;

void shadow_KillShadow(int val) {
    D_0063A17C = val;
}
INCLUDE_ASM("asm/nonmatchings/src/Shadow", shadow_DispCancel);
INCLUDE_ASM("asm/nonmatchings/src/Shadow", shadow_SetLength);
INCLUDE_ASM("asm/nonmatchings/src/Shadow", shadow_Init);
