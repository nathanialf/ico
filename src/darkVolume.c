#include "common.h"


extern void MatrixDrive_TurnObjectMatrix(void *dst, void *src);
extern int D_004C09A0[];
INCLUDE_ASM("asm/nonmatchings/src/darkVolume", draw);

INCLUDE_ASM("asm/nonmatchings/src/darkVolume", drawHT);

INCLUDE_ASM("asm/nonmatchings/src/darkVolume", renderViewCoordZSphere);

INCLUDE_ASM("asm/nonmatchings/src/darkVolume", sonic);

void darkVolume(int a0)
{
    MatrixDrive_TurnObjectMatrix(a0, D_004C09A0);
}

INCLUDE_ASM("asm/nonmatchings/src/darkVolume", SetDarkVolumeEffect);

int DispGameOverEffect(void)
{
    return 0;
}

void GetGameOverEffectCenterPosition(void) {}

void InitGameOverEffect(void) {}

void InitDarkVolumeGeo(void) {}

