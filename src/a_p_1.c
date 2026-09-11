#include "common.h"

typedef struct {
    float m[16];
} Mtx44;

typedef struct {
    float m[4];
} Vec4;

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
ASM_LIT4_SLOT(D_00639374, 10000.0f);

extern int fitToCol(char *a0, int a1);
extern void GetRootPosition(void *dst, void *self);
extern void SetRootPosition(void *self, void *src);
extern void GetRootMatrix(void *dst, void *self);
extern void MatrixDrive_SetTransposeMatrix(void *dst, void *src);
extern void _ScaleVector(void *dst, void *src, float s);
extern void _AddVectorXYZ(void *dst, void *a, void *b);
extern float VectorLength(void *v);

typedef union {
    int i;
    float f;
} AP1Val;

int walkMot(char *a0)
{
    Vec4 pos;
    Vec4 v;
    Mtx44 m;
    Mtx44 tm;
    Vec4 out;
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int ret = fitToCol(a0, 1);
    int i;
    int n;

    if (ret != -1)
        return ret;

    GetRootPosition(&pos, a0);
    GetRootMatrix(&m, a0);
    _ApplyMatrix((int)&v, (int)&m, (int)(p + 0x1B0));
    n = 0;
    for (i = 0; i < 4; i++) {
        if (*(int *)(p + 0x10 + i * 0x50) == 0) {
            n++;
        }
    }
    _ScaleVector(&v, &v, ((float)n * 0.25f + 0.5f) * 0.5f);
    _ScaleVector(*(char **)(a0 + 0x15C) + 0x130, *(char **)(a0 + 0x15C) + 0x130, 0.8f);
    _AddVectorXYZ(*(char **)(a0 + 0x15C) + 0x130, *(char **)(a0 + 0x15C) + 0x130, &v);
    MatrixDrive_SetTransposeMatrix(&tm, &m);
    _ApplyMatrix((int)&out, (int)&tm, (int)(*(char **)(a0 + 0x15C) + 0x130));
    ((AP1Val *)(p + 0x1C4))->f = out.m[0];
    ((AP1Val *)(p + 0x1C0))->f = VectorLength(*(char **)(a0 + 0x15C) + 0x130) * 0.1f;
    _AddVectorXYZ(&pos, &pos, *(char **)(a0 + 0x15C) + 0x130);
    SetRootPosition(a0, &pos);
    *(int *)(p + 0x1C8) = 0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/a_p_1", rolling);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", calcSubMission);
ASM_LIT4_SLOT(D_00639380, 2500.0f);
INCLUDE_ASM("asm/nonmatchings/src/a_p_1", updateMatrix);
ASM_LIT4_SLOT(D_00639384, 0.1f);

void resetPositionInfo(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    GetRootPosition(p + 0x1E0, a0);
    GetRootQuaternion(p + 0x1D0, a0);
    ResetEnemyEye(*(int *)(p + 0x19C));
}

extern void calcSubMission(char *a0);
extern void updateMatrix(char *a0);
extern int (*motFuncList[][2])(char *);
extern void *MatrixDrive_GetMatrix(void);
extern void _MulMatrix(void *dst, void *a, void *b);
extern void CopyMatrix(void *dst, void *src);
extern void MatrixDrive_RotMatrixZ(int ang);
extern void MatrixDrive_RotMatrixX(int ang);
extern int UpdateEnemyEye(int eye, void *m, float s);
extern void debug_StdPrintfDummy(char *fmt, ...);
extern char D_004E5970[];
extern char D_004E59F0[];
extern char D_0061EE70[];

/* static helper the listing places at a_p_1.c lines 889-891, expanded only
 * into AP1Geo, so this name is ours. */
static inline void stepAP1BlinkTimer(char *g)
{
    char *q = (char *)*(int *)(*(int *)(g + 0x15C) + 0x830);
    int t = *(int *)(q + 0x270) + 1;

    *(int *)(q + 0x270) = t;
    if (t > 32) {
        *(int *)(q + 0x270) = 0;
    }
}

void AP1Geo(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    float d;

    switch (*(int *)(p + 8)) {
    default:
        if (*(int *)(p + 0x274) < 10) {
            *(int *)(p + 0x274) = *(int *)(p + 0x274) + 1;
            resetPositionInfo(a0);
        }
        *(int *)(p + 8) = motFuncList[*(int *)(p + 8)][1](a0);
        stepAP1BlinkTimer(a0);
        break;

    case 5:
        *(int *)(p + 8) = 4;
        break;

    case 4:
        *(int *)(p + 8) = 6;
        break;

    case 6:
        *(int *)(a0 + 0x16C) = 0;
        break;

    case 7:
        break;
    }
    updateMatrix(a0);
    calcSubMission(a0);
    _MulMatrix(MatrixDrive_GetMatrix(), *(void **)(*(char **)(a0 + 0x15C) + 0xC), D_004E5970);
    UpdateEnemyEye(*(int *)(p + 0x19C), MatrixDrive_GetMatrix(), 1.0f);
    if (*(int *)(p + 4) != 0) {
        CopyMatrix(MatrixDrive_GetMatrix(), *(void **)(*(char **)(a0 + 0x15C) + 0xC));
        MatrixDrive_RotMatrixZ(0x4000);
        MatrixDrive_RotMatrixX(0x4000);
        _MulMatrix(*(void **)(*(char **)(a0 + 0x15C) + 0xC), MatrixDrive_GetMatrix(), D_004E59F0);
    }
    d = *(float *)(*(char **)(a0 + 0x15C) + 0x54) -
        *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0xC) + 0x34);
    if ((d < 0.0f) ? ((d = -d) > 10000.0f) : (d > 10000.0f)) {
        *(int *)(*(char **)(a0 + 0x15C) + 0x5F8) = 0x800;
        debug_StdPrintfDummy(D_0061EE70);
    }
}

extern void p2o_SetDefaultEnviroment(void);
extern void p2o_DispVU1(void *gobj);
extern void p2o_DispVU1DObjMulti(int obj);
extern void DispEnemyEye(int eye);

void AP1DL(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);

    if (*(int *)(p + 8) < 5) {
        if (*(int *)(p + 0x278) != 0) {
            p2o_SetDefaultEnviroment();
            p2o_DispVU1(a0);
            if (*(int *)(p + 4) == 0) {
                p2o_DispVU1DObjMulti(*(int *)(p + 0x194));
                p2o_DispVU1DObjMulti(*(int *)(p + 0x198));
            }
            DispEnemyEye(*(int *)(p + 0x19C));
        }
    }
}

int GetAP1SpecType(char *a0)
{
    return **(int **)(*(char **)(a0 + 0x15C) + 0x830);
}

void SetAP1VisualState(char *a0, int a1)
{
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x278) = a1;
}

extern void RotQuaternionY(int q, int ang);
extern void RegularizeQuaternion(int q);
extern void updateMatrix(char *a0);

int AP1Turn(char *a0, short a1)
{
    Vec4 q;
    int s = *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8);
    if (s < 6) {
        if (s >= 2)
            goto out;
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

int AP1MotReqForce(char *a0, int a1)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);

    *(int *)(p + 8) = a1;
    if (motFuncList[a1][0] != 0) {
        motFuncList[a1][0](a0);
    }
    return 1;
}

int AP1MotReq(char *a0, int a1)
{
    int s = *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8);
    if (s < 6) {
        if (s >= 2)
            return 0;
    }
    AP1MotReqForce(a0, a1);
    return 1;
}

int AP1JumpReq(char *a0, int a1, void *a2)
{
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
    int unk0;  /* 0x00 */
    int unk4;  /* 0x04 */
    int unk8;  /* 0x08 */
    int unkC;  /* 0x0C */
    int unk10; /* 0x10 */
    int unk14; /* 0x14 */
    int unk18; /* 0x18 */
    int unk1C; /* 0x1C */
} AP1Layout;

extern AP1Layout D_0062B588[];
extern char *CreateLayoutedGObj(int id, int a1, int a2, int a3, void *a4, int a5, int a6, int a7);

char *MakeAP1GObj(char *a0)
{
    return CreateLayoutedGObj(0x3E, D_0062B588[*(int *)(a0 + 0x30)].unkC, -1, 0, a0, 0, 7, 1);
}

extern int D_004E5520[];

int GetAP1Mode(char *a0)
{
    return D_004E5520[*(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8)];
}

extern int fitToCol(char *a0, int a1);

int standMot(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int ret = fitToCol(a0, 0);
    if (ret != -1)
        return ret;
    *(int *)(p + 0x1C0) = 0;
    *(int *)(p + 0x1C4) = 0;
    *(int *)(p + 0x1C8) = 0;
    return 0;
}

extern int rolling(char *a0);

int rollingMot(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int ret = rolling(a0);
    if (ret != -1)
        return ret;
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
    int state;   /* 0x00 */
    float frame; /* 0x04 */
    int unk8[6]; /* 0x08 */
    Vec4 vec;    /* 0x20 */
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

int attackMot(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int ret = fitToCol(a0, 0);
    if (ret != -1)
        return ret;
    *(int *)(p + 0x1C0) = 0;
    *(int *)(p + 0x1C4) = 0;
    *(float *)(p + 0x1C8) += 0.05f;
    if (*(float *)(p + 0x1C8) > 1.0f) {
        setAP1MotCtrlState((AP1MotCtrl *)(p + 0x10), 2);
        setAP1MotCtrlState((AP1MotCtrl *)(p + 0x60), 2);
        return 0;
    }
    return 3;
}
