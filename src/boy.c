#include "common.h"
#include "sugiCommon.h"

typedef struct { /* 0x10 */
    float x, y, z, w;
} __attribute__((aligned(16))) LLVec;

typedef struct {
    float *phase; /* 0x00 */
    float *speed; /* 0x04 */
    LLVec **line; /* 0x08 */
} LightLineExt;

extern LightLineExt *llExtGeo;
extern void AdjustMotionHeightToNearestField(void *a0);
/* prototypes: their order is the inline tail's emission order */
void SelectBoyCrown(char *a0, int a1);
void LightLineGeo(void);
void SetBoyStonizedVisual(char *a0);
extern void DispCloth4D(void *cloth, void *a1, void *a2);

void dispClothes(char *gobj)
{
    char *w = *(char **)(*(char **)(gobj + 0x15C) + 0x830);
    char *x;

    x = *(char **)(*(char **)(gobj + 0x15C) + 0x874);
    DispCloth4D(*(void **)(w + 0x20), x + 0x40, x);
    x = *(char **)(*(char **)(gobj + 0x15C) + 0x874);
    DispCloth4D(*(void **)(w + 0x24), x + 0x40, x);
    x = *(char **)(*(char **)(gobj + 0x15C) + 0x874);
    DispCloth4D(*(void **)(w + 0x2C), x + 0x40, x);
    x = *(char **)(*(char **)(gobj + 0x15C) + 0x874);
    DispCloth4D(*(void **)(w + 0x28), x + 0x40, x);
    x = *(char **)(*(char **)(gobj + 0x15C) + 0x874);
    DispCloth4D(*(void **)(w + 0x30), x + 0x40, x);
}

ASM_LIT4_SLOT(D_0063940C, 0.98f);
ASM_LIT4_SLOT(D_00639410, 0.98f);
ASM_LIT4_SLOT(D_00639414, 0.98f);
ASM_LIT4_SLOT(D_00639418, 0.98f);
ASM_LIT4_SLOT(D_0063941C, 0.98f);
ASM_LIT4_SLOT(D_00639420, 0.98f);
ASM_LIT4_SLOT(D_00639424, 0.999f);
INCLUDE_ASM("asm/nonmatchings/src/boy", execClothes);

extern void *iosMallocDebug(void *heap, int size, char *file, int line);
extern char D_0061F178[];
extern void *D_0063A438;
extern char D_004E6E10[];
extern void CopyVector(void *dst, void *src);

LightLineExt *InitLightLineGeo(char *gobj, float *pos)
{
    LLVec v = {pos[0] + 500.0f, pos[1], pos[2] + 200.0f, 1.0f};
    int i;
    int j;
    int n;
    float f;

    llExtGeo = (LightLineExt *)D_004E6E10;
    llExtGeo->phase = iosMallocDebug(D_0063A438, 0x190, D_0061F178, 0xA1);
    llExtGeo->speed = iosMallocDebug(D_0063A438, 0x190, D_0061F178, 0xA2);
    llExtGeo->line = iosMallocDebug(D_0063A438, 0x190, D_0061F178, 0xA3);
    for (i = 0; i < 100; i++) {
        llExtGeo->phase[i] = 0.0f;
        llExtGeo->speed[i] = random_unit() * 0.1f + 0.01f;
        llExtGeo->line[i] = iosMallocDebug(D_0063A438, 0x140, D_0061F178, 0xA8);
        CopyVector(llExtGeo->line[i], &v);
        llExtGeo->line[i][0].x += (float)((i - 0x32) * 5);
        for (j = 1; j < 20; j++) {
            CopyVector(&llExtGeo->line[i][j], &llExtGeo->line[i][j - 1]);
            if (random_unit() < 0.9f) {
                if (j & 1) {
                    llExtGeo->line[i][j].y -= (float)((int)(random_unit() * 10.0f) + 1) * 5.0f;
                } else {
                    n = (int)(random_signed() * 10.0f) + 1;
                    llExtGeo->line[i][j].x += (float)n * 5.0f;
                }
            } else {
                f = (float)((int)(random_unit() * 10.0f) + 1) * 5.0f;
                llExtGeo->line[i][j].y -= f;
                llExtGeo->line[i][j].x += f;
            }
        }
    }
    return llExtGeo;
}

inline void LightLineGeo(void)
{
    int i;

    for (i = 0; i < 100; i++) {
        llExtGeo->phase[i] += llExtGeo->speed[i];
        if (llExtGeo->phase[i] > 1.0f) {
            llExtGeo->speed[i] = random_unit() * 0.01f + 0.001f;
            llExtGeo->phase[i] = 0;
        }
    }
}

ASM_LIT4_SLOT(D_00639434, 0.05f);
ASM_LIT4_SLOT(D_00639438, 0.4f);
ASM_LIT4_SLOT(D_0063943C, 18.99998f);
ASM_LIT4_SLOT(D_00639440, 0.05f);
ASM_LIT4_SLOT(D_00639444, 0.4f);
INCLUDE_ASM("asm/nonmatchings/src/boy", LightLineDL);

inline void SelectBoyCrown(char *a0, int a1)
{
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x0) = a1;
}

/* The display-list record's 0x38 word carries single bits set and cleared with
   ld/or/sd and ld/and/sd, and a 16-bit field two bytes into the same
   container reached with a plain sh; the same union src/enemyParts.c uses. */
typedef union DlFlag {
    int i;
    long long ll;
} DlFlag;

extern void *D_0063A44C;
extern void iosFree(int p);
extern char *CSVSYSTEM_InitDObj(int kind, void *arg);
extern char *InitCloth4D(char *gobj, void *cfg, void *tbl);
extern void InitMotionOrient(char *self, int a1, int a2, int a3, int a4, int a5);
extern void SetLodLevel(char *self, int lod);
extern void InitLimitedPoolReflactionMesh(char *a0);
extern char *AllocWaterDot(char *gobj, int num, int a2);
extern void sceVu0UnitMatrix(void *a0);
extern char D_004E62B0[];
extern char D_004E65B0[];
extern char D_004E68B0[];
extern char D_004E69F0[];
extern char D_004E6B30[];
extern char D_004E6C70[];
extern char D_004E6D30[];

char *InitBoyGeo(char *gobj, void *csv)
{
    char *w;
    char *p;
    int i;

    w = (char *)iosMallocDebug(D_0063A438, 0x68, D_0061F178, 0x118);
    *(char **)(*(char **)(gobj + 0x15C) + 0x830) = w;
    p = *(char **)(*(char **)(gobj + 0x15C) + 0x830);
    *(char **)(p + 0x20) = InitCloth4D(gobj, D_004E62B0, D_004E6C70);
    *(char **)(p + 0x24) = InitCloth4D(gobj, D_004E65B0, D_004E6D30);
    *(char **)(p + 0x2C) = InitCloth4D(gobj, D_004E68B0, 0);
    *(char **)(p + 0x28) = InitCloth4D(gobj, D_004E69F0, 0);
    *(char **)(p + 0x30) = InitCloth4D(gobj, D_004E6B30, 0);
    *(int *)(*(char **)(gobj + 0x15C) + 0x554) = 1;
    *(char **)(w + 0x4) = CSVSYSTEM_InitDObj(2, csv);
    *(char **)(w + 0x8) = CSVSYSTEM_InitDObj(3, csv);
    if (*(int *)(*(char **)(w + 0x8) + 0xC) != 0) {
        iosFree(*(int *)(*(char **)(w + 0x8) + 0xC) & 0xFFFFFFF);
    }
    if (*(int *)(*(char **)(w + 0x8) + 0x10) != 0) {
        iosFree(*(int *)(*(char **)(w + 0x8) + 0x10) & 0xFFFFFFF);
    }
    *(int *)(*(char **)(w + 0x8) + 0xC) = 0;
    *(int *)(*(char **)(w + 0x8) + 0x10) = 0;
    *(int *)(*(char **)(w + 0x8) + 0xC) = (int)iosMallocDebug(D_0063A44C, 0x80, D_0061F178, 0x123);
    *(int *)(*(char **)(w + 0x8) + 0x10) = (int)iosMallocDebug(D_0063A44C, 0x20, D_0061F178, 0x123);
    *(int *)(*(char **)(w + 0x8) + 0x8) = 2;
    if (*(int *)(*(char **)(w + 0x8) + 0x870) != 0) {
        iosFree(*(int *)(*(char **)(w + 0x8) + 0x870) & 0xFFFFFFF);
    }
    *(int *)(*(char **)(w + 0x8) + 0x870) =
        (int)iosMallocDebug(D_0063A44C, 0xA0, D_0061F178, 0x123);
    for (i = 0; i < 2; i++) {
        ((DlFlag *)(i * 0x50 + *(int *)(*(char **)(w + 0x8) + 0x870) + 0x38))->ll &= ~1;
        ((DlFlag *)(i * 0x50 + *(int *)(*(char **)(w + 0x8) + 0x870) + 0x38))->ll &= ~2;
        *(float *)(i * 0x50 + *(int *)(*(char **)(w + 0x8) + 0x870) + 0x40) = 0.0f;
        *(float *)(i * 0x50 + *(int *)(*(char **)(w + 0x8) + 0x870) + 0x44) = 0.0f;
        *(float *)(i * 0x50 + *(int *)(*(char **)(w + 0x8) + 0x870) + 0x48) = 0.0f;
        *(float *)(i * 0x50 + *(int *)(*(char **)(w + 0x8) + 0x870) + 0x4C) = 1.0f;
        ((DlFlag *)(i * 0x50 + *(int *)(*(char **)(w + 0x8) + 0x870) + 0x38))->ll &= ~4;
        *(float *)(i * 0x50 + *(int *)(*(char **)(w + 0x8) + 0x870) + 0x30) = 0.0f;
        *(float *)(i * 0x50 + *(int *)(*(char **)(w + 0x8) + 0x870) + 0x34) = 1.0f;
        *(short *)(i * 0x50 + *(int *)(*(char **)(w + 0x8) + 0x870) + 0x3A) = 0;
        *(float *)(i * 0x50 + *(int *)(*(char **)(w + 0x8) + 0x870) + 0x20) = 1.0f;
        *(float *)(i * 0x50 + *(int *)(*(char **)(w + 0x8) + 0x870) + 0x24) = 1.0f;
        *(float *)(i * 0x50 + *(int *)(*(char **)(w + 0x8) + 0x870) + 0x28) = 1.0f;
    }
    *(short *)(*(char **)(w + 0x8) + 0x84C) = 2;
    *(char **)(w + 0xC) = CSVSYSTEM_InitDObj(1, csv);
    *(char **)(w + 0x10) = CSVSYSTEM_InitDObj(0xF, csv);
    *(char **)(w + 0x14) = CSVSYSTEM_InitDObj(0x10, csv);
    *(int *)(*(char **)(*(char **)(gobj + 0x15C) + 0x830)) = 0;
    sceVu0UnitMatrix(*(char **)(w + 0xC) + 0x20);
    InitMotionOrient(gobj, 0, 0x503, 0, 0xC, 0);
    InitLightLineGeo(gobj, csv);
    SetLodLevel(gobj, 2);
    *(int *)(w + 0x18) = 0;
    *(int *)(w + 0x1C) = 0;
    *(int *)(w + 0x34) = 0x14;
    *(int *)(w + 0x38) = 0x14;
    *(float *)(w + 0x3C) = 300.0f;
    *(float *)(w + 0x40) = 300.0f;
    *(int *)(w + 0x50) = 0x80808080;
    InitLimitedPoolReflactionMesh(w + 0x34);
    *(char **)(w + 0x54) = AllocWaterDot(gobj, 0x1E, 5);
    *(int *)(w + 0x58) = 0;
    *(int *)(w + 0x5C) = 0;
    *(int *)(w + 0x60) = 0;
    *(int *)(w + 0x64) = 0;
    return w;
}

typedef struct MotSyncPair { /* 0x08 */
    int girl;                /* 0x00 */
    int boy;                 /* 0x04 */
} MotSyncPair;

extern MotSyncPair D_00533FC0[];
extern char *D_00639EA8;
extern int D_0063B154;
extern char D_004E6DF0[];
extern char D_004E6E00[];
extern void _InterVectorXYZ(void *dst, void *a, void *b, float t);
extern void _SubVectorXYZ(void *dst, void *a, void *b);
extern void _AddVectorXYZ(void *dst, void *a, void *b);
extern void GetRootPosition(void *dst, char *gobj);
extern void SetDirectRootPositionNoFitting(char *self, void *v);
extern void gif_StartPacketPri(int a0);
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void gif_EndPacket(void);
extern void _UnitMatrix(void *p);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_TransMatrixV(char *a0);
extern void prim_DispWireSphere(float r, void *a0, int a1, int a2);

void synchronizeMotionOutputOriginForGirl(char *gobj)
{
    float d[4];
    float v[4];
    MotSyncPair *p;
    int i;
    int okA = 0;
    int okB = 0;

    if (D_00639EA8 != 0) {
        p = D_00533FC0;
        for (i = 0; i < 5; i++) {
            if (*(int *)(*(char **)(D_00639EA8 + 0x15C) + 0x4A0) == p->girl) {
                okA = 1;
            }
            if (*(int *)(*(char **)(gobj + 0x15C) + 0x4A0) == p->boy) {
                okB = 1;
            }
            p++;
        }
        if (okA != 0 && okB != 0) {
            _InterVectorXYZ(v, *(char **)(D_00639EA8 + 0x15C) + 0x100,
                            *(char **)(gobj + 0x15C) + 0x100, 0.9f);
            _SubVectorXYZ(d, v, *(char **)(D_00639EA8 + 0x15C) + 0x100);
            d[1] = 0.0f;
            GetRootPosition(v, D_00639EA8);
            _AddVectorXYZ(v, v, d);
            SetDirectRootPositionNoFitting(D_00639EA8, v);
            if (D_0063B154 != 0) {
                gif_StartPacketPri(0xB);
                gif_SetAlpha(1, 5, 0x80);
                _UnitMatrix(MatrixDrive_GetMatrix());
                MatrixDrive_TransMatrixV(*(char **)(D_00639EA8 + 0x15C) + 0x100);
                prim_DispWireSphere(10.0f, D_004E6DF0, 0x10, 8);
                _UnitMatrix(MatrixDrive_GetMatrix());
                MatrixDrive_TransMatrixV(*(char **)(gobj + 0x15C) + 0x100);
                prim_DispWireSphere(10.0f, D_004E6E00, 0x10, 8);
                gif_EndPacket();
            }
        }
    }
}

extern char D_0028FEF0[];
extern int ExecWaterDot(int work);
extern void EntryWaterDot(int work, void *pos, char *kind, float range);
extern void CopyVector(void *dst, void *src);
extern int GetSkeltonFocusNode(char *gobj, int node);

void actionOfWater(char *gobj)
{
    float pos[4];
    char *w = *(char **)(*(char **)(gobj + 0x15C) + 0x830);
    int node;

    ExecWaterDot(*(int *)(w + 0x54));
    if (*(int *)(*(char **)(gobj + 0x15C) + 0x4D8) == 0xB) {
        *(int *)(w + 0x58) = 1;
        *(float *)(w + 0x5C) = 5.0f;
        *(float *)(w + 0x60) = 0.0f;
    } else {
        *(int *)(w + 0x58) = 0;
        *(float *)(w + 0x5C) = *(float *)(w + 0x5C) * 0.98f;
        *(float *)(w + 0x60) = *(float *)(w + 0x60) + *(float *)(w + 0x5C);
        if (1.0f < *(float *)(w + 0x60)) {
            node = GetSkeltonFocusNode(gobj, 0x16);
            CopyVector(pos, *(char **)(*(char **)(gobj + 0x15C) + 0xC) + (node << 6) + 0x30);
            EntryWaterDot(*(int *)(w + 0x54), pos, D_0028FEF0, 8.0f);
            node = GetSkeltonFocusNode(gobj, 0x6);
            CopyVector(pos, *(char **)(*(char **)(gobj + 0x15C) + 0xC) + (node << 6) + 0x30);
            EntryWaterDot(*(int *)(w + 0x54), pos, D_0028FEF0, 8.0f);
            node = GetSkeltonFocusNode(gobj, 0x2C);
            CopyVector(pos, *(char **)(*(char **)(gobj + 0x15C) + 0xC) + (node << 6) + 0x30);
            EntryWaterDot(*(int *)(w + 0x54), pos, D_0028FEF0, 10.0f);
            *(float *)(w + 0x60) = 0.0f;
        }
    }
}

extern void HandManager(char *gobj);
extern void ExecMotionOrient(char *gobj);
extern void ExecuteSlipProc(char *gobj);
extern void SetActressLight(char *gobj, int a1, int a2, int a3);
extern int CylinderCollision(char *self, int group, float r, float h, float s);
extern void iosOmSendMail(char *gobj, int mail, char *a2);
extern int ACTGame_FLAG_TETSUNAGI(void);
void synchronizeMotionOutputOriginForGirl(char *gobj);
void execClothes(char *gobj);
void actionOfWater(char *gobj);

void BoyGeo(char *gobj)
{
    HandManager(gobj);
    ExecMotionOrient(gobj);
    synchronizeMotionOutputOriginForGirl(gobj);
    execClothes(gobj);
    ExecuteSlipProc(gobj);
    SetActressLight(gobj, 0x23, 0x2C, 0x1D7);
    if (CylinderCollision(gobj, 4, 50.0f, 50.0f, 0.7f) != 0) {
        iosOmSendMail(gobj, 6, gobj);
    }
    CylinderCollision(gobj, 2, ACTGame_FLAG_TETSUNAGI() != 0 ? 15.0f : 30.0f, 50.0f, 0.7f);
    actionOfWater(gobj);
}

extern void p2o_DispVU1DObj(void *a0);
extern void p2o_DispVU1DObjMulti(void *a0);
extern void CopyMatrix(void *dst, void *src);
extern int GetSkeltonFocusNode(char *gobj, int node);

void dispSubParts(char *gobj)
{
    char *w = *(char **)(*(char **)(gobj + 0x15C) + 0x830);
    char *a;
    char *c;
    int node;

    a = *(char **)(w + 0x4);
    node = GetSkeltonFocusNode(gobj, 0x23);
    CopyMatrix(*(char **)(a + 0xC), *(char **)(*(char **)(gobj + 0x15C) + 0xC) + (node << 6));
    p2o_DispVU1DObj(*(char **)(w + 0x4));
    a = *(char **)(w + 0x8);
    node = GetSkeltonFocusNode(gobj, 0x14);
    CopyMatrix(*(char **)(a + 0xC), *(char **)(*(char **)(gobj + 0x15C) + 0xC) + (node << 6));
    c = *(char **)(*(char **)(w + 0x8) + 0xC) + 0x40;
    node = GetSkeltonFocusNode(gobj, 0x4);
    CopyMatrix(c, *(char **)(*(char **)(gobj + 0x15C) + 0xC) + (node << 6));
    p2o_DispVU1DObjMulti(*(char **)(w + 0x8));
}

extern void reg_DispAccessoryWithShadow(void *a0, void *a1);
extern void MatrixDrive_RotMatrixX(int a0);
extern void *MatrixDrive_GetMatrix(void);
extern void CopyMatrix(void *dst, void *src);
extern int GetSkeltonFocusNode(char *gobj, int node);

void dispCrown(char *gobj)
{
    char *w = *(char **)(*(char **)(gobj + 0x15C) + 0x830);
    int node = GetSkeltonFocusNode(gobj, 0x23);
    char *obj;

    switch (*(int *)w) {
    case 1:
        obj = *(char **)(w + 0x10);
        break;
    case 2:
        obj = *(char **)(w + 0x14);
        break;
    default:
        obj = *(char **)(w + 0xC);
        break;
    }
    CopyMatrix(MatrixDrive_GetMatrix(), *(char **)(*(char **)(gobj + 0x15C) + 0xC) + (node << 6));
    MatrixDrive_RotMatrixX(-0x8000);
    CopyMatrix(*(char **)(obj + 0xC), MatrixDrive_GetMatrix());
    reg_DispAccessoryWithShadow(obj, *(char **)(gobj + 0x15C));
}

inline void SetBoyStonizedVisual(char *a0)
{
    char *crown = (char *)*(int *)(*(int *)(a0 + 0x15C) + 0x830);
    AdjustMotionHeightToNearestField(a0);
    *(int *)(crown + 0x18) = 1;
    *(int *)(crown + 0x1C) = 0;
    *(int *)(*(int *)(a0 + 0x15C) + 0x62C) = 0;
}

extern int stage_no;
extern int D_0028F4D4[];
extern int ExecutePauseSlipProc(char *gobj);
extern void GetRootPosition(void *dst, char *gobj);
extern void GetRootQuaternion(void *dst, char *gobj);
extern void RotQuaternionY(void *q, int ang);
extern float stage_PlayBgAnimation(int obj, void *a1, void *a2, float f);
extern void p2o_SetDefaultEnviroment(void);
extern void p2o_DispVU1(char *gobj);
extern int CheckPoolHasGridMesh(char *a0);
extern void SetLimitedPoolReflactionMesh(void *a0, int a1, char *a2);
extern void DispLimitedPoolReflactionMesh(void *a0);
extern void DispWaterDot(int a0);
void dispSubParts(char *gobj);

void BoyDL(char *gobj)
{
    char pos[0x10];
    char quat[0x10];
    char *w = *(char **)(*(char **)(gobj + 0x15C) + 0x830);
    char *m;
    char *sub;
    int r;

    ExecutePauseSlipProc(gobj);
    if (*(int *)(w + 0x18) != 0) {
        GetRootPosition(pos, gobj);
        GetRootQuaternion(quat, gobj);
        RotQuaternionY(quat, -0x8000);
        r = (int)stage_PlayBgAnimation(0x1E8, pos, quat, (float)*(int *)(w + 0x1C));
        if (D_0028F4D4[0] == 0 && r != -1) {
            *(int *)(w + 0x1C) = r;
        }
    } else {
        p2o_SetDefaultEnviroment();
        p2o_DispVU1(gobj);
        dispSubParts(gobj);
        dispCrown(gobj);
        dispClothes(gobj);
    }
    if (stage_no == 0x27 && 20.0f < *(float *)(*(char **)(gobj + 0x15C) + 0x644) &&
        *(int *)(*(char **)(gobj + 0x15C) + 0x648) != 0 &&
        CheckPoolHasGridMesh(*(char **)(*(char **)(gobj + 0x15C) + 0x648)) == 0) {
        sub = *(char **)(gobj + 0x15C);
        m = *(char **)(sub + 0x830) + 0x34;
        SetLimitedPoolReflactionMesh(m, *(int *)(sub + 0x648), gobj);
        DispLimitedPoolReflactionMesh(m);
    }
    DispWaterDot(*(int *)(w + 0x54));
}
