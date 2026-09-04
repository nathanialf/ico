#include "common.h"

#include "ico/types.h"
typedef struct { float m[16]; } Mtx44;
typedef struct { float m[4]; } Vec4;



extern int SetAP1DeadStatus(int *self, int a1);
extern int D_004BEFA8[];
extern void debug_StdPrintfDummy();
extern GObj *D_00631AE4;
extern void GetRootPosition(void *out, GObj *g);
extern void MatrixDrive_TransMatrix(void *out, void *src);
extern void MatrixDrive_TurnObjectMatrix(void *dst, void *src);
extern void _ApplyMatrix(void *out, void *m, void *v);

void SetActressLight(GObj *a0) {
    Vec4 r;
    Mtx44 m;
    Vec4 v;
    char *o = (char *)GOBJ_SUB(a0)->p_800;
    int *p10 = (int *)(o + 0x10);
    int *p60 = (int *)(o + 0x60);
    GetRootPosition(&r, D_00631AE4);
    MatrixDrive_TransMatrix(&m, o + 0x230);
    _ApplyMatrix(&v, &m, &r);
    MatrixDrive_TurnObjectMatrix(o + 0x30, &v);
    p10[1] = 0;
    *(int *)(o + 0x10) = 0;
    MatrixDrive_TurnObjectMatrix(o + 0x80, &v);
    *(int *)(o + 0x60) = 0;
    p60[1] = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/actressLight", func_001BA928);

INCLUDE_ASM("asm/nonmatchings/src/actressLight", func_001BA9B0);

INCLUDE_ASM("asm/nonmatchings/src/actressLight", func_001BAB68);

void func_001BAEE0(int a0)
{
    int idx = *(int *)(*(int *)(a0 + 0x164) + 0x30);
    debug_StdPrintfDummy(D_004BEFA8[idx]);
}

INCLUDE_ASM("asm/nonmatchings/src/actressLight", func_001BAF00);

INCLUDE_ASM("asm/nonmatchings/src/actressLight", func_001BAF48);

INCLUDE_ASM("asm/nonmatchings/src/actressLight", func_001BAFD0);

void func_001BB390(int a0)
{
    SetAP1DeadStatus(a0, 5);
}

INCLUDE_ASM("asm/nonmatchings/src/actressLight", func_001BB398);

INCLUDE_ASM("asm/nonmatchings/src/actressLight", func_001BB3E0);

INCLUDE_ASM("asm/nonmatchings/src/actressLight", func_001BB6B0);

int func_001BB7E0(int *a0)
{
    int *v1 = (int *)a0[0x164 / 4];
    long x = *(unsigned int *)((char *)v1 + 0x1C);
    return (((int)x) & 1) ^ 1;
}

void func_001BB800(char *self, int val) {
    *(int *)(*(char **)(self + 0x164) + 0x98) = val;
}

void func_001BB810(char *self, int val) {
    *(int *)(*(char **)(self + 0x164) + 0x9C) = val;
}

