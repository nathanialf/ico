#include "common.h"

typedef struct { int count; int *arr; } ShockMgr;
extern ShockMgr *D_0062A490;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", Vibration_ShotDecode);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", Vibration_WaveDecode);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", Shock_Request);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", Shock_SetMotor);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", func_0013B550);

void Init_ShockVoiceSet(void) {
}

void Vibration_SetDecodeData(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", Init_ShockRequestBox);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockRequestBox_Clear);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockRequestBox_Regst);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockRequestBox_Request);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockRequestBox_DecodeRequest);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockRequestBox_EndRequestFree);

extern void iosThreadInit(void);

void ShockRequestBox_VoiceSetUseRequestFree(int *a0, int a1, int a2, int a3) {
    a0[0] = 0;
    if (a1) {
        a0[1] = a1;
    } else {
        a0[1] = (int)iosThreadInit;
    }
    a0[2] = a2;
    a0[3] = a3;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockRequestBox_GetRequest);

void ShockRequestBox_RequestCancel(void *a0, void *a1) {
    void *head = *(void **)a0;
    *(int *)((char *)a1 + 0x30) = 0;
    *(void **)((char *)a1 + 0x34) = head;
    if (head) {
        *(void **)((char *)head + 0x30) = a1;
    }
    *(void **)a0 = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockRequestBox_RequestDirectCancel);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", Init_ShockDriver);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockDriver_VoiceSet_NumberRegist);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockDriver_VoiceSet_Regist);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockDriver_VoiceSet_Remove);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockDriver_GetShockVoiceMax);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockDriver_GetShockVoiceSet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockDriver_GetShockVoice);

int Init_ShockEmulator(int a0, int a1) {
    if ((unsigned int)a0 < (unsigned int)D_0062A490->count) {
        goto body;
    }
    return -1;
body:
    D_0062A490->arr[a0] = a1;
    return a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockEmulator_EmulationShot);

int ShockEmulator_EmulationWave(int a0) {
    if ((unsigned int)a0 < (unsigned int)D_0062A490->count) {
        goto body;
    }
    return -1;
body:
    D_0062A490->arr[a0] = 0;
    return a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", Init_ShockRequestAlloc);


int Get_ShockRequestStruct(int a0) {
    if ((unsigned int)a0 < (unsigned int)D_0062A490->count) {
        goto body;
    }
    return 0;
body:
    return D_0062A490->arr[a0];
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", Reset_ShockRequestStruct);

void ShockRevice_Wave(short *a0) {
    a0[1] = 0;
    a0[0] = 0;
}

int Init_Shock(int a0, int a1) {
    return a1;
}
