#include "common.h"
#include "typedef.h"
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
/* kept local: this TU's uses of these do not fit the prototypes in Matrix.h */
extern void _ScaleVectorXYZ(void *a0, void *a1, float a2);
extern void _AddVectorXYZ(void *a0, void *a1, void *a2);
extern void _InterVectorXYZ(void *a0, void *a1, void *a2, float t);
extern void _MulCurrentMatrixL(void *a0);
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

/* The listing puts this body at rows 750-751, inside shadow_EntryNormalShadow's
 * own line span, so the dev wrote it at the head of that function. One asm
 * block because the two vnop runs are hand scheduled around the multiply, and
 * both addresses are "r" operands: the ROM's copy reaches them in $3 and $2,
 * the registers the surrounding loop allocates, not in the argument
 * registers a fixed spelling would force. */
static inline void applyCurrentMatrixV(void *dst, void *src)
{
    __asm__ __volatile__("lqc2 $vf8, 0(%1)\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "vmulax.xyzw ACC, $vf4, $vf8x\n\t"
                         "vmadday.xyzw ACC, $vf5, $vf8y\n\t"
                         "vmaddaz.xyzw ACC, $vf6, $vf8z\n\t"
                         "vmaddw.xyzw $vf9, $vf7, $vf0w\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "sqc2 $vf9, 0(%0)"
                         :
                         : "r"(dst), "r"(src));
}

void shadow_EntryNormalShadow(char *a0, int a1, float a2)
{
    float v[4];
    float sa[4];
    float sb[4];
    char *x = *(char **)(a0 + 0x858);
    int i;
    int j;
    char *p;

    shadow_getShadowVectorAverage(v, a0);
    _ScaleVectorXYZ(sa, v, a2);
    _ScaleVectorXYZ(sb, v, 4.0f);
    _SetCurrentMatrix(*(char **)(a0 + 0xC) + a1 * 0x40);
    _MulCurrentMatrixL(matrixptr + 0x80);

    p = *(char **)(x + 0x40);
    for (i = 0; i < *(char *)(x + 0x2E); i++, p += 0x180) {
        for (j = 0; j < *(unsigned int *)(p + 0x94); j++) {
            applyCurrentMatrixV(*(char **)(p + 0x174) + j * 16, *(char **)(p + 0x90) + j * 16);
        }
        for (j = 0; j < *(unsigned int *)(p + 0x94); j++) {
            _AddVectorXYZ(*(char **)(p + 0x178) + j * 16, *(char **)(p + 0x174) + j * 16, sa);
            _AddVectorXYZ(*(char **)(p + 0x174) + j * 16, *(char **)(p + 0x174) + j * 16, sb);
        }
    }

    p = *(char **)(x + 0x40);
    for (i = 0; i < *(char *)(x + 0x2E); i++, p += 0x180) {
        VECTOR *va = (VECTOR *)*(char **)(p + 0x174);
        VECTOR *vb = (VECTOR *)*(char **)(p + 0x178);

        for (j = 0; j < *(unsigned int *)(p + 0x94); j++) {
            if (1.0f <= va[j].z && 1.0f <= vb[j].z) {
            } else if (va[j].z < 1.0f && vb[j].z < 1.0f) {
                vb[j].w = -1.0f;
                va[j].w = -1.0f;
            } else if (vb[j].z < 1.0f) {
                _InterVectorXYZ(&vb[j], &va[j], &vb[j],
                                1.0f - (va[j].z - 1.0f) / (va[j].z - vb[j].z));
            } else if (va[j].z < 1.0f) {
                _InterVectorXYZ(&va[j], &vb[j], &va[j],
                                1.0f - (vb[j].z - 1.0f) / (vb[j].z - va[j].z));
            }
        }
    }
}

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

/* one row of the shadow tool: the name it prints, the variable it edits and
 * the range it wraps that variable through */
typedef struct ShadowToolRow {
    char *name;
    int *val;
    int min;
    int max;
} ShadowToolRow;

extern ShadowToolRow D_0054FE18[];
/* the two menu colours, unselected then selected */
extern unsigned int D_0054FF58[];
/* "Shadow Tool" */
extern char D_0054FF60[];
/* "%s : %s" */
extern char D_0063A198[];
/* "%s : %d" */
extern char D_0063A1A0[];
/* "Shadow %s => %s\n" */
extern char D_0054FF70[];
/* "Shadow %s => %d\n" */
extern char D_0054FF88[];
/* the names a 0/1 row prints instead of its number */
extern char *D_00290B50[];
/* the row the tool has selected */
extern int D_0063A194;

/* the pad record this TU reads, the same one common/src/layout_action.c calls
 * R58: the flag word it tests for the two buttons at 4 and the auto-repeat
 * word it tests for the four directions at 0xC */
typedef struct PadRec {
    int _0;
    int flags;
    int _8;
    int repeat;
    char _10[0x48];
} PadRec;

extern PadRec D_0028F8F0[];

int shadow_Tool(void)
{
    int ret = 0;
    int i;

    debug_PrintfDummy(10, 50, 0xFF800000u, (int)D_0054FF60);
    for (i = 0; i < 8; i++) {
        if (D_0054FE18[i].min == 0 && D_0054FE18[i].max == 1) {
            debug_PrintfDummy(0x12, (i + 1) * 8 + 50, D_0054FF58[D_0063A194 == i], (int)D_0063A198,
                              (int)D_0054FE18[i].name, (int)D_00290B50[*D_0054FE18[i].val]);
        } else {
            debug_PrintfDummy(0x12, (i + 1) * 8 + 50, D_0054FF58[D_0063A194 == i], (int)D_0063A1A0,
                              (int)D_0054FE18[i].name, *D_0054FE18[i].val);
        }
    }
    if (D_0028F8F0[0].repeat & 0x4000) {
        D_0063A194++;
        if (8 <= D_0063A194) {
            D_0063A194 = 0;
        }
    }
    if (D_0028F8F0[0].repeat & 0x1000) {
        D_0063A194--;
        if (D_0063A194 < 0) {
            D_0063A194 = 7;
        }
    }
    if (D_0028F8F0[0].repeat & 0x2000) {
        if (++*D_0054FE18[D_0063A194].val > D_0054FE18[D_0063A194].max) {
            *D_0054FE18[D_0063A194].val = D_0054FE18[D_0063A194].min;
        }
    }
    if (D_0028F8F0[0].repeat & 0x8000) {
        if (--*D_0054FE18[D_0063A194].val < D_0054FE18[D_0063A194].min) {
            *D_0054FE18[D_0063A194].val = D_0054FE18[D_0063A194].max;
        }
    }
    if (D_0028F8F0[0].flags & 0x20) {
        for (i = 0; i < 8; i++) {
            if (D_0054FE18[i].min == 0 && D_0054FE18[i].max == 1) {
                debug_StdPrintfDummy(D_0054FF70, D_0054FE18[i].name,
                                     D_00290B50[*D_0054FE18[i].val]);
            } else {
                debug_StdPrintfDummy(D_0054FF88, D_0054FE18[i].name, *D_0054FE18[i].val);
            }
        }
        ret = 1;
    }
    if (D_0028F8F0[0].flags & 0x40) {
        ret = -1;
    }
    if (ret != 0) {
        D_0063A194 = 0;
    }
    return ret;
}
