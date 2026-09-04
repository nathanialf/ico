#include "common.h"

typedef struct { float m[4]; } Vec4;
typedef struct { float m[16]; } Mtx44;

extern int D_0062B474;
extern int D_0062C1CC;
extern float D_0062C1D0;
extern float D_0062C1D4;
extern int D_0062C1D8;

extern int D_004B8C80[];

void InitAP1(void)
{
    register int a __asm__("$3") = D_004B8C80[0] + 0x1400;
    register int one __asm__("$2") = 1;
    register int b4 __asm__("$6") = 0xFF;
    int b;
    D_0062C1D8 = one;
    D_0062C1D0 = (float)(a / 30);
    b = D_0062C1CC - 0x280;
    D_0062C1D4 = (float)(b / 30);
    D_0062B474 = b4;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/a_p_1", yAxisRotFitting);

extern void getQuaternionFromMatrix(int dst, int src);
extern float _InnerProduct(int dst, int v);
extern int *GetTableArcCos(float f);
extern void _OuterProduct(int dst, int v, int src);
extern void _NormalizeVector(int dst, int src);
extern void SetQuaternionByAxisRotateV(int dst, int p, int src);
extern void MultiQuaternion(int dst, int a, int b);
extern char D_004B9E00[];
extern void func_00102820(int p, int *self);
extern void _ApplyMatrix(int a, int b, int c);
extern void func_00102840(int self, int src);

void zAxisRotFitting(int *self, int arg2)
{
    Vec4 l0;
    Vec4 l10;
    Mtx44 m20;
    Vec4 l60;
    Vec4 l70;
    int *r;
    float f;

    func_00102820((int)&l70, self);
    getQuaternionFromMatrix((int)&m20, (int)&l70);
    _ApplyMatrix((int)&l0, (int)&m20, (int)D_004B9E00);
    f = _InnerProduct((int)&l0, arg2);
    r = GetTableArcCos(f);
    if (r != 0) {
        _OuterProduct((int)&l10, arg2, (int)&l0);
        _NormalizeVector((int)&l10, (int)&l10);
        SetQuaternionByAxisRotateV((int)&l60, (int)r, (int)&l10);
        MultiQuaternion((int)&l70, (int)&l60, (int)&l70);
        func_00102840((int)self, (int)&l70);
    }
}

extern char D_00271C10[];

void fitToCol(int *self, int arg2)
{
    Vec4 l0;
    Vec4 l10;
    Mtx44 m20;
    Vec4 l60;
    Vec4 l70;
    int *r;
    float f;

    func_00102820((int)&l70, self);
    getQuaternionFromMatrix((int)&m20, (int)&l70);
    _ApplyMatrix((int)&l0, (int)&m20, (int)D_00271C10);
    f = _InnerProduct((int)&l0, arg2);
    r = GetTableArcCos(f);
    if (r != 0) {
        _OuterProduct((int)&l10, arg2, (int)&l0);
        _NormalizeVector((int)&l10, (int)&l10);
        SetQuaternionByAxisRotateV((int)&l60, (int)r, (int)&l10);
        MultiQuaternion((int)&l70, (int)&l60, (int)&l70);
        func_00102840((int)self, (int)&l70);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/a_p_1", walkMot);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/a_p_1", rolling);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/a_p_1", calcSubMission);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/a_p_1", updateMatrix);
