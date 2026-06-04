#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_SaveActorInformation);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_DeleteActorInformation);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", EXITDATA_GetNextPosition);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_StageChangeGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_SetActors_Debug);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_TryConnectHand);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_TryDisconnectHand);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_DisconnectHand_WithMail);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTCheckView);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGameView_Loop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_LwsEffectProcess);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", _ACTGame_SearchGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTLookTarget_Exec);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTParaStatus_Clear);

void ACTParaStatus_Exec(void *a0) {
    *(int *)(*(int *)((char *)a0 + 0x15C) + 0x534) = 0;
    *(int *)(*(int *)((char *)a0 + 0x15C) + 0x53C) = 0;
    *(int *)(*(int *)((char *)a0 + 0x15C) + 0x538) = 0;
    *(int *)(*(int *)((char *)a0 + 0x15C) + 0x7C) = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", _ACTCharStatus_Clear);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", GetSkeltonOrient);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_InnerVelocityUpdate);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_BeforeFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", FunctionAboutClingedStatus);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", GetOtherStageGirlOrient);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-game", ACTGame_DisconnectHand);

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
