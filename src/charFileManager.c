#include "common.h"


extern int D_00633E28;
void InitCharFileManager(void) {
    D_00633E28 = 0;
}

void ResetCharFileManager(void) {}

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadModelFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadVolumeModelFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadShadowModelFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadTextureFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadSkeltonFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadCollisionFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadStageAnimationFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadMotionFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadParticleEffectFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadSoundBdFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadSoundHdFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadShockFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadCamerasetFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadEndCheckFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadStageSettingFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", CSVSYSTEM_ReadCharFiles);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadSoundSqFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadSoundAdpcmFile);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", GetPObjAddress);

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", func_001A2C18);

