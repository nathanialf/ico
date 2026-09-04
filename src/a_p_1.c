#include "common.h"

typedef struct { float m[16]; } Mtx44;
typedef struct { float m[4]; } Vec4;


extern int D_00633EDC;
extern float D_00633EE4;
extern int D_004BD980[];   /* defined as unsigned char[16] in box_data.c */;
extern float D_00633EE0;
extern int D_00633EE8;
extern int D_006331B4;
void InitAP1(void)
{
    D_00633EE8 = 1;
    D_00633EE0 = (float)((D_004BD980[0] + 0x1400) / 30);
    D_00633EE4 = (float)((D_00633EDC - 0x280) / 30);
    D_006331B4 = 0xFF;
}

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", yAxisRotFitting);

extern char D_004BEB00[];
extern void _OuterProduct(int dst, int v, int src);
extern float _InnerProduct(int dst, int v);
extern void _NormalizeVector(int dst, int src);
extern void func_00102850(int p, int *self);
extern void func_00102870(int self, int src);
extern void SetQuaternionByAxisRotateV(int dst, int p, int src);
extern void MultiQuaternion(int dst, int a, int b);
extern int *GetTableArcCos(float f);
extern void _ApplyMatrix(int a, int b, int c);
extern void getQuaternionFromMatrix(int dst, int src);

void zAxisRotFitting(int *self, int arg2)
{
    Vec4 l0;
    Vec4 l10;
    Mtx44 m20;
    Vec4 l60;
    Vec4 l70;
    int *r;
    float f;

    func_00102850((int)&l70, self);
    getQuaternionFromMatrix((int)&m20, (int)&l70);
    _ApplyMatrix((int)&l0, (int)&m20, (int)D_004BEB00);
    f = _InnerProduct((int)&l0, arg2);
    r = GetTableArcCos(f);
    if (r != 0) {
        _OuterProduct((int)&l10, arg2, (int)&l0);
        _NormalizeVector((int)&l10, (int)&l10);
        SetQuaternionByAxisRotateV((int)&l60, (int)r, (int)&l10);
        MultiQuaternion((int)&l70, (int)&l60, (int)&l70);
        func_00102870((int)self, (int)&l70);
    }
}

extern char D_00275890[];

void fitToCol(int *self, int arg2)
{
    Vec4 l0;
    Vec4 l10;
    Mtx44 m20;
    Vec4 l60;
    Vec4 l70;
    int *r;
    float f;

    func_00102850((int)&l70, self);
    getQuaternionFromMatrix((int)&m20, (int)&l70);
    _ApplyMatrix((int)&l0, (int)&m20, (int)D_00275890);
    f = _InnerProduct((int)&l0, arg2);
    r = GetTableArcCos(f);
    if (r != 0) {
        _OuterProduct((int)&l10, arg2, (int)&l0);
        _NormalizeVector((int)&l10, (int)&l10);
        SetQuaternionByAxisRotateV((int)&l60, (int)r, (int)&l10);
        MultiQuaternion((int)&l70, (int)&l60, (int)&l70);
        func_00102870((int)self, (int)&l70);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", walkMot);

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", rolling);

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", calcSubMission);

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", updateMatrix);

