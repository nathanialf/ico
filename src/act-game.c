#include "common.h"

#include "ico/types.h"

typedef struct { char _0[0x1C]; int f_1C; char _20[4]; } WeaponEntry;

typedef struct { long long w; } __attribute__((packed)) U64ag;

typedef struct {
    char _00[0x20];
    float _20, _24, _28;
    char _2c[0x44];
    float _70;
    char _74[0x0C];
    float _80;
    char _84[0x04];
    int _88;
    char _8c[0x0C];
    int _98;
    char _9c[0x24];
} HandWork;

typedef union { int i; float f; } IntFloat;

extern void gamesysObjInfoCls();

void ACTGame_DeleteActorInformation(int a0)
{
    gamesysObjInfoCls(*(int *)(a0 + 0xC), *(int *)(a0 + 0x8));
}
INCLUDE_ASM("asm/nonmatchings/src/act-game", EXITDATA_GetNextPosition);
ASM_LIT4_SLOT(D_00638CC8, 0.017453292f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_StageChangeGObj);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_SetActors_Debug);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_TryConnectHand);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_TryDisconnectHand);
extern void ACTGame_DisconnectHand(void);
extern const char D_005523F0[];
extern void debug_StdPrintfDummy();

void ACTGame_DisconnectHand_WithMail(void)
{
    ACTGame_DisconnectHand();
    debug_StdPrintfDummy(D_005523F0);
}
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTCheckView);
ASM_LIT4_SLOT(D_00638CCC, 0.8f);
ASM_LIT4_SLOT(D_00638CD0, 0.8f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGameView_Loop);
ASM_LIT4_SLOT(D_00638CD4, 5000.0f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_LwsEffectProcess);
INCLUDE_ASM("asm/nonmatchings/src/act-game", _ACTGame_SearchGObj);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTLookTarget_Exec);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTParaStatus_Clear);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTParaStatus_Exec);
INCLUDE_ASM("asm/nonmatchings/src/act-game", _ACTCharStatus_Clear);
INCLUDE_ASM("asm/nonmatchings/src/act-game", GetSkeltonOrient);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_InnerVelocityUpdate);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_BeforeFunc);
INCLUDE_ASM("asm/nonmatchings/src/act-game", FunctionAboutClingedStatus);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTEnvGetTest);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ActOrientTest);
ASM_LIT4_SLOT(D_00638CD8, -1.5707964f);
ASM_LIT4_SLOT(D_00638CDC, 1.5707964f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", GetGirlHandlinkClInfo);
ASM_LIT4_SLOT(D_00638CE0, 12100.0f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", hand_able_connect);
ASM_LIT4_SLOT(D_00638CE4, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_CommonLoop);
ASM_LIT4_SLOT(D_00638CE8, 160000.0f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", GetTarget);
ASM_LIT4_SLOT(D_00638CEC, 0.3f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTLookTargetSystem_Exec);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTItemThrow);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTItemWatchMotion);
ASM_LIT4_SLOT(D_00638CF0, 0.2f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_InsertCamera_GirlIsPinch);
ASM_LIT4_SLOT(D_00638CF4, 22500.0f);
ASM_LIT4_SLOT(D_00638CF8, 0.05f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", updateHMC);
INCLUDE_ASM("asm/nonmatchings/src/act-game", RequestChangeHandMode);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTNotNeedCameraOffset);
void ACTGameCollisionOn(volatile int *self)
{
    ((int *)self[0x57])[0x151] = 1;
    ((int *)self[0x57])[0x153] = 1;
    ((int *)self[0x57])[0x152] = 1;
    ((int *)self[0x57])[0x1F] = 1;
}
void ACTGameCollisionOff(volatile int *self)
{
    ((int *)self[0x57])[0x151] = 0;
    ((int *)self[0x57])[0x153] = 0;
    ((int *)self[0x57])[0x152] = 0;
    ((int *)self[0x57])[0x1F] = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_CheckItemMotion);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_CheckHandMotion);
extern int D_0055C518[][10];
extern void EXITDATA_GetNextPosition(int idx, char *tmp_a, char *tmp_b);
extern void gamesysObjInfoPosNewStageSet(char *self, char *other, int v, char *tmp_a, char *tmp_b);

void ACTGame_StageChangeGObjID(char *self, char *other, int idx)
{
    char tmp_a[0x10];
    char tmp_b[0x10];
    EXITDATA_GetNextPosition(idx, tmp_a, tmp_b);
    gamesysObjInfoPosNewStageSet(self, other, D_0055C518[idx][9], tmp_a, tmp_b);
}
extern void memset(void *a0, int a1, int a2);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);

void ACTGame_StageChangeGObjDirect(int *a0, int a1, void *a2, int a3) {
    char buf0[0x10];
    char buf1[0x10];
    memset(buf1, 0, 0x10);
    *(float *)(buf1 + 4) = (float)a3 * 3.1415927f / 180.0f;
    sceVu0ScaleVector(buf0, a2, -1.0f);
    gamesysObjInfoPosNewStageSet((char *)a0[2], (char *)a0[3], a1, buf0, buf1);
}
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_FLAG_LIFEPINCH);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_FLAG_TETSUNAGI);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_FLAG_TETSUNAGI_VISUAL);
extern int GetSkeltonFocusNode(void *a0, void *a1);

void GetSkeltonPosition(float *dst, char *obj, void *a2)
{
    int idx = GetSkeltonFocusNode(obj, a2) << 6;
    ((IntFloat *)dst)[0].f = *(float *)(idx + *(int *)((int)((GObj *)(obj))->p_15C + 0xC) + 0x30);
    ((IntFloat *)dst)[1].f = *(float *)(idx + *(int *)((int)((GObj *)(obj))->p_15C + 0xC) + 0x34);
    ((IntFloat *)dst)[2].f = *(float *)(idx + *(int *)((int)((GObj *)(obj))->p_15C + 0xC) + 0x38);
}
extern float FSqrt(float a0);
extern void GetSkeltonPosition__pn(void *a0, void *a1, int a2) __asm__("GetSkeltonPosition");
extern void SetDirectRootPositionNoFittingWithNodePoint(void *a0, void *a1, void *a2, float a3);
extern void sceVu0AddVector(void *a0, void *a1, void *a2);
extern void sceVu0Normalize(void *a0, void *a1);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);
extern void sceVu0SubVector(void *a0, void *a1, void *a2);

void SetDirectRootPositionWithNodePointLimit(void *a0, void *a1, void *a2, float farg0, float farg1) {
    float buf0[4];
    float buf18[4];
    float buf16[4];

    GetSkeltonPosition__pn(buf0, a0, a1);
    sceVu0SubVector(buf16, a2, buf0);
    if (farg1 < FSqrt(buf16[0] * buf16[0] + buf16[1] * buf16[1] + buf16[2] * buf16[2])) {
        sceVu0Normalize(buf16, buf16);
        sceVu0ScaleVector(buf16, buf16, farg1);
        sceVu0AddVector(buf18, buf0, buf16);
        if (0.0f < buf18[1] - *(float *) ((char *) a2 + 4)) {
            buf18[1] = *(float *) ((char *) a2 + 4);
        }
        SetDirectRootPositionNoFittingWithNodePoint(a0, a1, buf18, 1.0f);
        return;
    }
    SetDirectRootPositionNoFittingWithNodePoint(a0, a1, a2, farg0);
}
extern int D_006C0470[];

void ACTGameView_Init(void) {
    int *p = D_006C0470;
    *(int *)((char *)p + 0x4B0) = 0;
    *(int *)((char *)p + 0x4B4) = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTCharctrl_Lock);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTCharctrl_Unlock);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_ConnectHand);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_DisconnectHand);
INCLUDE_ASM("asm/nonmatchings/src/act-game", PAIR_GetPosition_BOY);
INCLUDE_ASM("asm/nonmatchings/src/act-game", PAIR_IsStatus_BOY_PULL);
INCLUDE_ASM("asm/nonmatchings/src/act-game", PAIR_IsStatus_GIRL_PULL);
INCLUDE_ASM("asm/nonmatchings/src/act-game", PAIR_IsStatus_BOY_WAIT);
INCLUDE_ASM("asm/nonmatchings/src/act-game", PAIR_GetPosition_BOY_DITCH);
INCLUDE_ASM("asm/nonmatchings/src/act-game", PAIR_IsStatus_BOY_DITCH);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_isHangChain);
extern int ACTGame_isWeaponCombustible(void);
extern int GetTorchGObjOfWeapon(int *self);

int ACTGame_isWeaponEnableCatchfire(int *self)
{
    unsigned long new_var;
    int ret = 0;
    new_var = ACTGame_isWeaponCombustible();
    if (new_var != 0)
    {
        ret = GetTorchGObjOfWeapon(self);
    }
    return ret;
}
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTCheckCollis_WF);
extern void ClipWall(void *);
extern void GetOrientOfWall(void *out, int n, void *vec);
extern void memset(void *a0, int a1, int a2);
extern void sceVu0CopyVector(void *buf, int x);

int ACTCheckCollis_W(float f, void *hand0, void *hand1, void *actor, void *posout, void *magtarget, int *flagout) {
    HandWork work;
    int flag;
    int rv;
    int cnt;

    memset(&work, 0, 0xC0);
    rv = 1;
    flag = actor ? *(int *) ((char *) *(int *) ((char *) actor + 0x15C) + 0x74) : 0;
    work._70 = f;
    sceVu0CopyVector(&work, (int) hand0);
    sceVu0CopyVector((char *) &work + 0x10, (int) hand1);
    if (flag != 0) {
        *(int *) ((char *) *(int *) ((char *) actor + 0x15C) + 0x74) = 0;
    }
    ClipWall(&work);
    if (flagout != 0) {
        *flagout = work._98;
    }
    cnt = work._88;
    if (cnt == 0) {
        rv = 0;
    }
    if (posout != 0) {
        *(float *) ((char *) posout + 0) = work._20;
        *(float *) ((char *) posout + 4) = work._24;
        *(float *) ((char *) posout + 8) = work._28;
    }
    if (cnt != 0 && magtarget != 0) {
        GetOrientOfWall(magtarget, cnt, &work._80);
    }
    if (flag != 0) {
        *(int *) ((char *) *(int *) ((char *) actor + 0x15C) + 0x74) = 1;
    }
    return rv & 0xFF;
}
int ACTCheckCollis_CI(int a0, int a1, int *a2, char *a3)
{
    char buf[0xC0];
    memset(buf, 0, 0xC0);
    *(int *)(buf + 0x70) = 0;
    sceVu0CopyVector(buf, a0);
    sceVu0CopyVector(buf + 0x10, a1);
    ClipWall(buf);
    if (a2 != 0) {
        *a2 = *(int *)(buf + 0x98);
    }
    if (a3 != 0) {
        *(U64ag *)a3 = *(U64ag *)(buf + 0x80);
        *(int *)(a3 + 8) = *(int *)(buf + 0x88);
    }
    return *(int *)(buf + 0x88) != 0;
}
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTCheckCollis_WELL);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTCheckCollis_WAY);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTCheckViewCl);
ASM_LIT4_SLOT(D_00638D00, 25000000.0f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGameView_FirstSet);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGameView_Add);
int ACTGameView_Check(int a0, int a1)
{
    int i;
    for (i = 0; i < D_006C0470[0x4B0 / 4]; i++) {
        if (D_006C0470[i] == a1) {
            return *((unsigned char *)&D_006C0470[i] + 0x190);
        }
    }
    return 0;
}
int ACTGameViewSimple_Check(int a0, int a1) {
    int i;
    for (i = 0; i < D_006C0470[0x12C]; i++) {
        if (D_006C0470[i] == a1) {
            return *(unsigned char *)((char *)D_006C0470 + i * 4 + 0x320);
        }
    }
    return 0;
}
extern int CheckWeaponKind();
extern WeaponEntry D_00318EB8[];

int ACTGame_GetMotOrientFromWeapon(int a0)
{
    int rv;
    if (a0 != 0) {
        rv = D_00318EB8[CheckWeaponKind(a0)].f_1C;
    } else {
        rv = 0;
    }
    return rv;
}
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_NoWeapon);
int ACTGame_isWeaponCombustible(void) {
    return CheckWeaponKind() == 1;
}
extern const float D_0063A6AC[];
extern float _DistSqGV(int *a0, int a1);
extern int *isysGObjSearchFromObjKindID_begin(int);
extern int *isysGObjSearchFromObjKindID_next(int *);
extern int *test_CURRENTROOT(int *a0);

int *ACTGame_GetNearestGObj(int a0, int a1) {
    float best_val = D_0063A6AC[0];
    int *best = 0;
    int *node;

    node = isysGObjSearchFromObjKindID_begin(a1);
    if (node != 0) {
        do {
            float val = _DistSqGV(test_CURRENTROOT(node), a0);
            if (val < best_val) {
                best_val = val;
                best = node;
            }
            node = isysGObjSearchFromObjKindID_next(node);
        } while (node != 0);
    }
    return best;
}
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTLookTarget_Init);
INCLUDE_ASM("asm/nonmatchings/src/act-game", _ACTLookTarget_Set);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTParaStatus_Init);
INCLUDE_ASM("asm/nonmatchings/src/act-game", _ACTParaStatus_Set);
INCLUDE_ASM("asm/nonmatchings/src/act-game", _ACTParaStatus_Check);
void _ACTCharStatus_Init(int **a0) {
    long long *p = (long long *)a0[0x59];
    p[0xB] = 0;
    p[0xC] = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/act-game", _ACTCharStatus_Set);
INCLUDE_ASM("asm/nonmatchings/src/act-game", _ACTCharStatus_Check);
void _ACTCharStatus_Exec(void) {}
INCLUDE_ASM("asm/nonmatchings/src/act-game", _ACTSetEnemyDisappearSpeed);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_SetMotionPlaySpeedRatio_Reserve);
extern float D_002ADAF0[];

float _ACTGame_GetParamF(int idx)
{
    return D_002ADAF0[idx];
}
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_GetCurrentCallStatus);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_CheckPriInputFrame);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_SendSoundMail);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_LwsEffectInit);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_LwsEffect_Guard);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ActGame_GetOrientQ);
ASM_LIT4_SLOT(D_00638D04, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", _GetRootObjectOrient);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTItemForceDrop);
INCLUDE_ASM("asm/nonmatchings/src/act-game", GetOtherStageGirlOrient);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTChkAttackIgnore_BOY);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTChkAttackIgnore_GIRL);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTChkAttackIgnore_ENEMY);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTCheckCollis_VIEW);
ASM_LIT4_SLOT(D_00638D08, 25000000.0f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTCheckViewClDetail);
ASM_LIT4_SLOT(D_00638D0C, 25000000.0f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_SetMotionPlaySpeedRatio_Clear);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_SetMotionPlaySpeedRatio_Exec);
extern int D_00639D10;
extern void OtherStagePositionGet();
extern int gamesysGetGirlStageIDAndPosition(int a0);

void GetGirlPositionAtThisStage(int a0)
{
    int buf[4];
    int v0 = gamesysGetGirlStageIDAndPosition(buf);
    OtherStagePositionGet(a0, D_00639D10, v0, buf);
}
