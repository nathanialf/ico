#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/darkVolume", draw);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/darkVolume", drawHT);

extern void MatrixDrive_TurnObjectMatrix(int a0, void *a1);
extern int D_004BBC90[];
extern float D_0062B5E4;

void renderViewCoordZSphere(int a0, float a1) {
    D_0062B5E4 = a1;
    MatrixDrive_TurnObjectMatrix((int)D_004BBC90, (void *)a0);
}

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
