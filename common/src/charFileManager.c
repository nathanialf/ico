#include "common.h"

extern int D_0062C118;

void InitCharFileManager(void) {
    D_0062C118 = 0;
}

void ResetCharFileManager(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadModelFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadVolumeModelFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadShadowModelFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadTextureFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadSkeltonFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadCollisionFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadStageAnimationFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadMotionFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadParticleEffectFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadSoundBdFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadSoundHdFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadShockFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadCamerasetFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadEndCheckFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadStageSettingFile);

extern int D_0062A328;
extern int D_00271240[];
extern int iosFree(int a0, char *q, const char *src, int code);
extern void iosCdvdLoad(int *self, int p, char *q);
extern void iosMallocCheckLeak2(int p);

extern char D_0060B4E0[];

void CSVSYSTEM_ReadCharFiles(int *self, int unused, char *q)
{
    int p = iosFree(D_0062A328, q, D_0060B4E0, 0x349);
    D_00271240[8]++;
    iosCdvdLoad(self, p, q);
    iosMallocCheckLeak2(p);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadSoundSqFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", ReadSoundAdpcmFile);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", GetPObjAddress);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/charFileManager", func_001A01B8);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_14;  /* 0x14 */
} S_006DE110;  /* stride 0x18 */

/* end struct shapes */
