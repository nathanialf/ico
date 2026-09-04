#include "common.h"

typedef struct { int w[6]; } AssertRec;

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
extern int D_0063A438;
extern char D_006193B0[];
extern int D_0028F4C0[];
void ReadParticleEffectFile(void *h, int a1, int size, int a3) {
    char *buf = iosMallocDebug(D_0063A438, size, D_006193B0, 0x228);
    D_0028F4C0[8]++;
    iosCdvdHandlerRead(h, buf, size);
    SetParticleEffectPackage(a3, buf, size);
    iosFree(buf);
}
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadSoundBdFile);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadSoundHdFile);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadShockFile);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadCamerasetFile);
extern char D_006193B0[];
extern int D_0063A450;
extern int D_0028F4C0[];
void ReadEndCheckFile(void *h, int a1, int size) {
    char *buf = iosMallocDebug(D_0063A450, size, D_006193B0, 0x356);
    D_0028F4C0[8]++;
    iosCdvdHandlerRead(h, buf, size);
    iosFree(buf);
}
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadStageSettingFile);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", CSVSYSTEM_ReadCharFiles);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadSoundSqFile);
INCLUDE_ASM("asm/nonmatchings/src/charFileManager", ReadSoundAdpcmFile);
extern DbgSlot D_006FAD00[];

extern AssertRec D_006FAD00__pn[] __asm__("D_006FAD00");

int GetPObjAddress(int a0) {
    return D_006FAD00__pn[a0].w[0];
}
