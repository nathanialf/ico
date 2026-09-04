#include "common.h"

typedef struct { float m[16]; } Mtx44;
typedef struct { float m[4]; } Vec4;

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", InitAP1);
extern char D_004E55D0[];
extern void GetMatrixFromQuaternion(int dst, int src);
extern void GetRootQuaternion(int p, int *self);
extern int *GetTableArcCos(float f);
extern void MultiQuaternion(int dst, int a, int b);
extern void SetQuaternionByAxisRotateV(int dst, int p, int src);
extern void SetRootQuaternion(int self, int src);
extern void _ApplyMatrix(int a, int b, int c);
extern float _InnerProduct(int dst, int v);
extern void _NormalizeVector(int dst, int src);
extern void _OuterProduct(int dst, int v, int src);

void yAxisRotFitting(int *self, int arg2)
{
    Vec4 l0;
    Vec4 l10;
    Mtx44 m20;
    Vec4 l60;
    Vec4 l70;
    int *r;
    float f;

    GetRootQuaternion((int)&l70, self);
    GetMatrixFromQuaternion((int)&m20, (int)&l70);
    _ApplyMatrix((int)&l0, (int)&m20, (int)D_004E55D0);
    f = _InnerProduct((int)&l0, arg2);
    r = GetTableArcCos(f);
    if (r != 0) {
        _OuterProduct((int)&l10, arg2, (int)&l0);
        _NormalizeVector((int)&l10, (int)&l10);
        SetQuaternionByAxisRotateV((int)&l60, (int)r, (int)&l10);
        MultiQuaternion((int)&l70, (int)&l60, (int)&l70);
        SetRootQuaternion((int)self, (int)&l70);
    }
}
extern char D_0028FF30[];

void zAxisRotFitting(int *self, int arg2)
{
    Vec4 l0;
    Vec4 l10;
    Mtx44 m20;
    Vec4 l60;
    Vec4 l70;
    int *r;
    float f;

    GetRootQuaternion((int)&l70, self);
    GetMatrixFromQuaternion((int)&m20, (int)&l70);
    _ApplyMatrix((int)&l0, (int)&m20, (int)D_0028FF30);
    f = _InnerProduct((int)&l0, arg2);
    r = GetTableArcCos(f);
    if (r != 0) {
        _OuterProduct((int)&l10, arg2, (int)&l0);
        _NormalizeVector((int)&l10, (int)&l10);
        SetQuaternionByAxisRotateV((int)&l60, (int)r, (int)&l10);
        MultiQuaternion((int)&l70, (int)&l60, (int)&l70);
        SetRootQuaternion((int)self, (int)&l70);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", fitToCol);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", walkMot);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", rolling);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", calcSubMission);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", updateMatrix);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", resetPositionInfo);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", AP1Geo);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", AP1DL);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", GetAP1SpecType);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", SetAP1VisualState);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", AP1Turn);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", AP1MotReqForce);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", AP1MotReq);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", AP1JumpReq);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", MakeAP1GObj);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", GetAP1Mode);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", standMot);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", rollingMot);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", attackMotInit);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", attackMot);
