#include "common.h"

typedef struct { int f_0; char _4[0x14]; } DbgSlot;

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", InitCharFileManager);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ResetCharFileManager);
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
extern DbgSlot D_006FAD00[];

INCLUDE_ASM("asm/nonmatchings/src/charFileManager", GetPObjAddress);
