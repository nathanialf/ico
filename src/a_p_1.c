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
extern void RotQuaternionY(int q, int ang);
extern void RegularizeQuaternion(int q);
extern void updateMatrix(char *a0);
int AP1Turn(char *a0, short a1) {
    Vec4 q;
    int s = *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8);
    if (s < 6) {
        if (s >= 2) goto out;
    }
    GetRootQuaternion((int)&q, (int *)a0);
    RotQuaternionY((int)&q, a1);
    RegularizeQuaternion((int)&q);
    SetRootQuaternion((int)a0, (int)&q);
    updateMatrix(a0);
    return 1;
out:
    return 0;
}
extern int (*motFuncList[][2])(char *);
int AP1MotReqForce(char *a0, int a1) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);

    *(int *)(p + 8) = a1;
    if (motFuncList[a1][0] != 0) {
        motFuncList[a1][0](a0);
    }
    return 1;
}
int AP1MotReq(char *a0, int a1) {
    int s = *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8);
    if (s < 6) {
        if (s >= 2) return 0;
    }
    AP1MotReqForce(a0, a1);
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
    AP1MotReqForce(a0, a1);
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
typedef struct {
    int unk0;    /* 0x00 */
    int unk4;    /* 0x04 */
    int unk8;    /* 0x08 */
    int unkC;    /* 0x0C */
    int unk10;   /* 0x10 */
    int unk14;   /* 0x14 */
    int unk18;   /* 0x18 */
    int unk1C;   /* 0x1C */
} AP1Layout;
extern AP1Layout D_0062B588[];
extern char *CreateLayoutedGObj(int id, int a1, int a2, int a3, void *a4, int a5, int a6, int a7);
char *MakeAP1GObj(char *a0) { return CreateLayoutedGObj(0x3E, D_0062B588[*(int *)(a0 + 0x30)].unkC, -1, 0, a0, 0, 7, 1); }
extern int D_004E5520[];
int GetAP1Mode(char *a0) {
    return D_004E5520[*(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8)];
}
extern int fitToCol(char *a0, int a1);
int standMot(char *a0) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int ret = fitToCol(a0, 0);
    if (ret != -1) return ret;
    *(int *)(p + 0x1C0) = 0;
    *(int *)(p + 0x1C4) = 0;
    *(int *)(p + 0x1C8) = 0;
    return 0;
}
extern int rolling(char *a0);
int rollingMot(char *a0) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int ret = rolling(a0);
    if (ret != -1) return ret;
    *(int *)(p + 0x1C0) = 0;
    *(int *)(p + 0x1C4) = 0;
    *(int *)(p + 0x1C8) = 0;
    return 2;
}
extern int D_00639EA4;
extern void GetRootPosition(void *dst, void *self);
extern void MatrixDrive_SetTransposeMatrix(void *dst, void *src);
extern void CopyVector(void *dst, void *src);

typedef struct {
    int state;      /* 0x00 */
    float frame;    /* 0x04 */
    int unk8[6];    /* 0x08 */
    Vec4 vec;       /* 0x20 */
} AP1MotCtrl;

/* Two static helpers the listing places at a_p_1.c lines 384-393 (the census
 * gap between 353 and 397), expanded twice each into attackMotInit and
 * attackMot; neither is emitted out of line, so both names are ours. */
static inline void setAP1MotCtrlState(AP1MotCtrl *m, int state)
{
    m->state = state;
    m->frame = 0.0f;
}

static inline void setAP1MotCtrlVector(AP1MotCtrl *m, Vec4 *v)
{
    CopyVector(&m->vec, v);
    setAP1MotCtrlState(m, 0);
}

void attackMotInit(char *a0)
{
    Vec4 pos;
    Mtx44 mtx;
    Vec4 dir;
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);

    GetRootPosition(&pos, (void *)D_00639EA4);
    MatrixDrive_SetTransposeMatrix(&mtx, p + 0x230);
    _ApplyMatrix((int)&dir, (int)&mtx, (int)&pos);
    setAP1MotCtrlVector((AP1MotCtrl *)(p + 0x10), &dir);
    setAP1MotCtrlVector((AP1MotCtrl *)(p + 0x60), &dir);
}
extern float D_00639390;
int attackMot(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int ret = fitToCol(a0, 0);
    if (ret != -1) return ret;
    *(int *)(p + 0x1C0) = 0;
    *(int *)(p + 0x1C4) = 0;
    *(float *)(p + 0x1C8) += D_00639390;
    if (*(float *)(p + 0x1C8) > 1.0f) {
        setAP1MotCtrlState((AP1MotCtrl *)(p + 0x10), 2);
        setAP1MotCtrlState((AP1MotCtrl *)(p + 0x60), 2);
        return 0;
    }
    return 3;
}
