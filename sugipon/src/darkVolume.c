#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/darkVolume", draw);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/darkVolume", drawHT);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/darkVolume", renderViewCoordZSphere);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/darkVolume", sonic);

extern void MatrixDrive_TurnObjectMatrix(int a0, void *a1);
extern int D_004BBC80[];

void darkVolume(int a0) {
    MatrixDrive_TurnObjectMatrix(a0, D_004BBC80);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/darkVolume", SetDarkVolumeEffect);

int DispGameOverEffect(void) {
    return 0;
}

void GetGameOverEffectCenterPosition(void) {
}

void InitGameOverEffect(void) {
}

void InitDarkVolumeGeo(void) {
}
