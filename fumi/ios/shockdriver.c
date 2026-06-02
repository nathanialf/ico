#include "common.h"

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockRequestBox_VoiceSetUseRequestFree);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockRequestBox_GetRequest);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockRequestBox_RequestCancel);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockRequestBox_RequestDirectCancel);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", Init_ShockDriver);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockDriver_VoiceSet_NumberRegist);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockDriver_VoiceSet_Regist);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockDriver_VoiceSet_Remove);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockDriver_GetShockVoiceMax);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockDriver_GetShockVoiceSet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockDriver_GetShockVoice);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", Init_ShockEmulator);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockEmulator_EmulationShot);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockEmulator_EmulationWave);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", Init_ShockRequestAlloc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", Get_ShockRequestStruct);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", Reset_ShockRequestStruct);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/shockdriver", ShockRevice_Wave);

int Init_Shock(int a0, int a1) {
    return a1;
}
