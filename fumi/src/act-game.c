#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_SaveActorInformation);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_DeleteActorInformation);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", EXITDATA_GetNextPosition);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_StageChangeGObj);

extern int InitIcoMisc(void *a0);
extern int D_00629C90;
extern void func_0019A4B8(void *a0, int a1, int a2);

void ACTGame_SetActors_Debug(void *a0) {
    int r = InitIcoMisc(a0);
    func_0019A4B8(a0, D_00629C90, r);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_TryConnectHand);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_TryDisconnectHand);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_DisconnectHand_WithMail);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTCheckView);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGameView_Loop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_LwsEffectProcess);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", _ACTGame_SearchGObj);

extern void *D_00629DE4;

int ACTLookTarget_Exec(char *a0) {
    long long v;
    if (a0 == 0) {
        goto ret0;
    }
    if (a0 != D_00629DE4) {
        goto ret0;
    }
    a0 = *(char **)(a0 + 0x164);
    if (a0 == 0) {
        goto ret0;
    }
    v = *(long long *)(a0 + 0x20);
    v = v << 15;
    return (int)(v >> 32) & 1;
ret0:
    return 0;
}

void ACTParaStatus_Clear(int a0) {
    *(int *)(*(int *)(a0 + 0x15C) + 0x534) = 1;
    *(int *)(*(int *)(a0 + 0x15C) + 0x53C) = 1;
    *(int *)(*(int *)(a0 + 0x15C) + 0x538) = 1;
    *(int *)(*(int *)(a0 + 0x15C) + 0x7C) = 1;
}

void ACTParaStatus_Exec(void *a0) {
    *(int *)(*(int *)((char *)a0 + 0x15C) + 0x534) = 0;
    *(int *)(*(int *)((char *)a0 + 0x15C) + 0x53C) = 0;
    *(int *)(*(int *)((char *)a0 + 0x15C) + 0x538) = 0;
    *(int *)(*(int *)((char *)a0 + 0x15C) + 0x7C) = 0;
}

typedef struct { char _[0x186]; unsigned short f186; char _pad[8]; } ACTCharStat;
extern ACTCharStat D_0055DA10[];

int _ACTCharStatus_Clear(void *a0) {
    ACTCharStat *t = D_0055DA10;
    int idx = *(int *)(*(int *)((char *)a0 + 0x15C) + 0x490);
    return t[idx].f186 & 7;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", GetSkeltonOrient);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_InnerVelocityUpdate);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_BeforeFunc);

int FunctionAboutClingedStatus(void *a0) {
    float f = *(float *)(*(char **)((char *)a0 + 0x164) + 0x1D0);
    if (f <= 20.0f) {
        return 1;
    }
    return 0;
}

extern void *D_00629DE8;
int ACTEnvGetTest(void) {
    void *q;
    if (D_00629DE8 == 0) return 0;
    q = *(void **)((char *)D_00629DE8 + 0x164);
    return (int)(*(unsigned long long *)((char *)q + 0x18) >> 36) & 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ActOrientTest);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", GetGirlHandlinkClInfo);

extern int D_006A3F70[];

void hand_able_connect(void) {
    D_006A3F70[0x12C] = 0;
    D_006A3F70[0x12D] = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_CommonLoop);

void GetOtherStageGirlOrient(void *a0) {
    long long *p = (long long *)((char *)*(void **)((char *)a0 + 0x164) + 0x18);
    *p |= (long long)0x8000 << 28;
    *p |= (long long)0x8000 << 29;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", GetTarget);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTLookTargetSystem_Exec);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTItemThrow);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTItemWatchMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_InsertCamera_GirlIsPinch);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", updateHMC);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", RequestChangeHandMode);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTNotNeedCameraOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGameCollisionOn);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGameCollisionOff);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_CheckItemMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_CheckHandMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_StageChangeGObjID);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_StageChangeGObjDirect);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_FLAG_LIFEPINCH);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_FLAG_TETSUNAGI);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", GetSkeltonPosition);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", SetDirectRootPositionWithNodePointLimit);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGameView_Init);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTCharctrl_Lock);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTCharctrl_Unlock);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_ConnectHand);

extern int checkHit(void);
int ACTGame_DisconnectHand(void) {
    return checkHit() == 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", PAIR_GetPosition_BOY);

void PAIR_IsStatus_BOY_PULL(void *a0) {
    int *p = *(int **)((char *)a0 + 0x164);
    p[0x22] = 0;
    p[0x24] = 0;
    p[0x23] = 0;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_190;  /* 0x190 */
    unsigned int       f_320;  /* 0x320 */
    unsigned int       f_4B0;  /* 0x4B0 */
    unsigned int       f_4B4;  /* 0x4B4 */
} S_006A3F70;  /* stride 0x4 */

typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
    unsigned long long f_20;  /* 0x20 */
    unsigned long long f_28;  /* 0x28 */
    unsigned long long f_30;  /* 0x30 */
    unsigned long long f_38;  /* 0x38 */
} S_0027DED0;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_005523F0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00552430;  /* stride 0x4 */

/* end struct shapes */
