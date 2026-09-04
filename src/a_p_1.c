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
void resetPositionInfo(char *a0) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    GetRootPosition(p + 0x1E0, a0);
    GetRootQuaternion(p + 0x1D0, a0);
    ResetEnemyEye(*(int *)(p + 0x19C));
}
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", AP1Geo);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", AP1DL);
int GetAP1SpecType(char *a0) {
    return **(int **)(*(char **)(a0 + 0x15C) + 0x830);
}
void SetAP1VisualState(char *a0, int a1) {
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x278) = a1;
}
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", AP1Turn);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", AP1MotReqForce);
extern void AP1MotReqForce(void *a0);
int AP1MotReq(char *a0) {
    int s = *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8);
    if (s < 6) {
        if (s >= 2) return 0;
    }
    AP1MotReqForce(a0);
    return 1;
}
int AP1JumpReq(char *a0, int a1, void *a2) {
    int flag;
    char *p = *(char **)(a0 + 0x15C);
    char *q = *(char **)(p + 0x830);
    if (*(int *)(q + 8) < 6) {
        if (*(int *)(q + 8) >= 2) {
            flag = 0;
            goto check;
        }
    }
    AP1MotReqForce(a0);
    flag = 1;
check:
    if (flag != 0) {
        char *pp = *(char **)(a0 + 0x15C);
        char *qq = *(char **)(pp + 0x830);
        _ApplyMatrix((int)(pp + 0x130), (int)(qq + 0x230), (int)a2);
        return 1;
    }
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", MakeAP1GObj);
extern int D_004E5520[];
int GetAP1Mode(char *a0) {
    return D_004E5520[*(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8)];
}
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", standMot);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", rollingMot);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", attackMotInit);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", attackMot);
