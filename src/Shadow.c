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
extern char *matrixptr;
extern void _CopyVector(void *a0, void *a1);
extern void _SetCurrentMatrix(void *a0);
extern void _ClearTransCurrentMatrix(void);
extern void _ApplyCurrentMatrix(void *a0, void *a1);
extern void _NormalizeVector(void *a0, void *a1);
void shadow_getShadowVectorAverage(void *a0, char *a1) {
    _CopyVector(a0, a1 + 0x860);
    _SetCurrentMatrix(matrixptr + 0x80);
    _ClearTransCurrentMatrix();
    _ApplyCurrentMatrix(a0, a0);
    _NormalizeVector(a0, a0);
}
INCLUDE_ASM("asm/nonmatchings/src/Shadow", shadow_EntryClusterShadow);
INCLUDE_ASM("asm/nonmatchings/src/Shadow", shadow_EntryNormalShadow);
extern char *matrixptr;
extern void _ApplyCurrentMatrix(void *a0, void *a1);
extern void _ClearTransCurrentMatrix(void);
extern void _PopCurrentMatrix(void);
extern void _PushCurrentMatrix(void *a0);
extern void _ScaleVector(void *a0, void *a1, float a2);
extern void _SetCurrentMatrix(void *a0);
extern void _TransposeCurrentMatrix(void);

void __GetCameraPos(void *a0) {
    _PushCurrentMatrix(a0);
    _SetCurrentMatrix(matrixptr + 0x80);
    _ClearTransCurrentMatrix();
    _TransposeCurrentMatrix();
    _ApplyCurrentMatrix(a0, matrixptr + 0xB0);
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
void shadow_SetLength(char *a0, float f) {
    if (0.0f < f) {
        *(float *)(*(char **)(a0 + 0x858) + 0x3C) = f;
    } else {
        *(float *)(*(char **)(a0 + 0x858) + 0x3C) = *(float *)(*(char **)(a0 + 0x854) + 0x3C);
    }
}
extern int D_0063A178;
extern int D_0063A17C;
void shadow_Init(void) {
    char *obj;
    D_0063A178 = 0;
    D_0063A17C = 0;
    for (obj = isysGObjGetExist_begin(); obj != 0; obj = isysGObjGetExist_next(obj)) {
        char *node = *(char **)(obj + 0x15C);
        if (node != 0) {
            char *dl = *(char **)(node + 0x854);
            if (dl != 0) {
                char *x = *(char **)(node + 0x858);
                if (x != 0) {
                    *(long long *)(x + 0x30) &= ~0x04000000;
                }
            }
        }
    }
}
