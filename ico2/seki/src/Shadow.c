#include "common.h"
#include "debug.h"
#include "Shadow.h"

extern char D_0054FD50[];
extern char *matrixptr;
/* kept local: this TU's uses of _CopyVector do not fit the prototype in Matrix.h */
extern void _CopyVector(void *a0, void *a1);
/* kept local: this TU's uses of _SetCurrentMatrix do not fit the prototype in Matrix.h */
extern void _SetCurrentMatrix(void *a0);
/* kept local: this TU's uses of _ClearTransCurrentMatrix do not fit the prototype in Matrix.h */
extern void _ClearTransCurrentMatrix(void);
/* kept local: this TU's uses of _ApplyCurrentMatrix do not fit the prototype in Matrix.h */
extern void _ApplyCurrentMatrix(void *a0, void *a1);
/* kept local: this TU's uses of _NormalizeVector do not fit the prototype in Matrix.h */
extern void _NormalizeVector(void *a0, void *a1);
/* kept local: this TU's uses of _PopCurrentMatrix do not fit the prototype in Matrix.h */
extern void _PopCurrentMatrix(void);
/* kept local: this TU's uses of _PushCurrentMatrix do not fit the prototype in Matrix.h */
extern void _PushCurrentMatrix(void *a0);
/* kept local: this TU's uses of _ScaleVector do not fit the prototype in Matrix.h */
extern void _ScaleVector(void *a0, void *a1, float a2);
/* kept local: this TU's uses of _TransposeCurrentMatrix do not fit the prototype in Matrix.h */
extern void _TransposeCurrentMatrix(void);
extern int D_0063A17C;
extern int D_0063A178;

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Shadow", shadow_Reset);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Shadow", shadow_Draw);

void shadow_Render(void)
{
    /* CRUTCH: zero-code frame reservation. The body is one printf stub and ROM
       still reserves 16 bytes of vars, so the vector the stub printed was a
       local here. Deleting it changes the object. See docs/crutch_ledger.md. */
    float buf[4];
    debug_StdPrintfDummy(D_0054FD50);
}

void shadow_getShadowVectorAverage(void *a0, char *a1)
{
    _CopyVector(a0, a1 + 0x860);
    _SetCurrentMatrix(matrixptr + 0x80);
    _ClearTransCurrentMatrix();
    _ApplyCurrentMatrix(a0, a0);
    _NormalizeVector(a0, a0);
}

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Shadow", shadow_EntryClusterShadow);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Shadow", shadow_EntryNormalShadow);

void __GetCameraPos(void *a0)
{
    _PushCurrentMatrix(a0);
    _SetCurrentMatrix(matrixptr + 0x80);
    _ClearTransCurrentMatrix();
    _TransposeCurrentMatrix();
    _ApplyCurrentMatrix(a0, matrixptr + 0xB0);
    _ScaleVector(a0, a0, -1.0f);
    *(float *)((char *)a0 + 0xC) = 1.0f;
    _PopCurrentMatrix();
}

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Shadow", shadow_RenderVolume);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Shadow", shadow_RenderVolumeMulti);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Shadow", shadow_MakeObjectData);

inline void shadow_KillShadow(int val)
{
    D_0063A17C = val;
}

inline void shadow_DispCancel(int a0, int a1)
{
    char *obj = isysGObjGetExist_begin(a0);
    if (obj != 0) {
        long long bit = (long long)(a1 & 1) << 26;
        do {
            char *node = *(char **)(obj + 0x15C);
            if (node != 0) {
                char *dl = *(char **)(node + 0x854);
                if (dl != 0) {
                    char *x = *(char **)(node + 0x858);
                    if (x != 0) {
                        if (*(short *)(dl + 0x30) == a0) {
                            *(long long *)(x + 0x30) =
                                (*(long long *)(x + 0x30) & ~0x04000000) | bit;
                        }
                    }
                }
            }
            obj = isysGObjGetExist_next(obj);
        } while (obj != 0);
    }
}

inline void shadow_SetLength(char *a0, float f)
{
    if (0.0f < f) {
        *(float *)(*(char **)(a0 + 0x858) + 0x3C) = f;
    } else {
        *(float *)(*(char **)(a0 + 0x858) + 0x3C) = *(float *)(*(char **)(a0 + 0x854) + 0x3C);
    }
}

inline void shadow_Init(void)
{
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

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Shadow", shadow_Tool);
