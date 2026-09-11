#include "common.h"
#include "sugiCommon.h"

typedef struct {
    float *phase; /* 0x00 */
    float *speed; /* 0x04 */
    float *unk8;  /* 0x08 */
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
ASM_LIT4_SLOT(D_00639428, 0.1f);
ASM_LIT4_SLOT(D_0063942C, 0.01f);
ASM_LIT4_SLOT(D_00639430, 0.9f);
INCLUDE_ASM("asm/nonmatchings/src/boy", InitLightLineGeo);

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

INCLUDE_ASM("asm/nonmatchings/src/boy", InitBoyGeo);
ASM_LIT4_SLOT(D_00639448, 0.9f);
INCLUDE_ASM("asm/nonmatchings/src/boy", synchronizeMotionOutputOriginForGirl);
ASM_LIT4_SLOT(D_0063944C, 0.98f);
INCLUDE_ASM("asm/nonmatchings/src/boy", actionOfWater);

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

INCLUDE_ASM("asm/nonmatchings/src/boy", dispSubParts);

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
extern void ExecutePauseSlipProc(char *gobj);
extern void GetRootPosition(void *dst, char *gobj);
extern void GetRootQuaternion(void *dst, char *gobj);
extern void RotQuaternionY(void *q, int ang);
extern float stage_PlayBgAnimation(int obj, void *a1, void *a2, float f);
extern void p2o_SetDefaultEnviroment(void);
extern void p2o_DispVU1(char *gobj);
extern int CheckPoolHasGridMesh(void);
extern void SetLimitedPoolReflactionMesh(void *a0, int a1, char *a2);
extern void DispLimitedPoolReflactionMesh(void *a0);
extern void DispWaterDot(int a0);
void dispSubParts(char *gobj);

INCLUDE_ASM("asm/nonmatchings/src/boy", BoyDL);
