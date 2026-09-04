#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/darkVolume", draw);
INCLUDE_ASM("asm/nonmatchings/src/darkVolume", drawHT);
INCLUDE_ASM("asm/nonmatchings/src/darkVolume", renderViewCoordZSphere);
INCLUDE_ASM("asm/nonmatchings/src/darkVolume", sonic);
INCLUDE_ASM("asm/nonmatchings/src/darkVolume", darkVolume);
extern void CopyVector(void *dst, void *src);
extern int D_004E7470[];
extern float D_0063B7D4;

void SetDarkVolumeEffect(int a0, float a1) {
    D_0063B7D4 = a1;
    CopyVector(D_004E7470, (void *)a0);
}
INCLUDE_ASM("asm/nonmatchings/src/darkVolume", DispGameOverEffect);
extern int D_004E7460[];

void GetGameOverEffectCenterPosition(int a0)
{
    CopyVector(a0, D_004E7460);
}
INCLUDE_ASM("asm/nonmatchings/src/darkVolume", InitGameOverEffect);
INCLUDE_ASM("asm/nonmatchings/src/darkVolume", SetupDarkVolume);
INCLUDE_ASM("asm/nonmatchings/src/darkVolume", DarkVolumeGeo);
int InitDarkVolumeGeo(char *a0) {
    **(int **)(*(char **)(a0 + 0x15C) + 0xC) = 0;
    return 0;
}
void DarkVolumeDL(void) {}
void ExecGameOverEffect(void) {}
INCLUDE_ASM("asm/nonmatchings/src/darkVolume", StartGameOverEffect);
extern int D_004E7460[];
extern int D_0063B7BC;
extern int D_0063B7C0;
extern int D_0063B7C4;
extern int D_0063B7C8;
extern float D_0063B7CC;

void StartQueenAttackEffect(int a0, float t)
{
    D_0063B7BC = 1;
    D_0063B7C4 = 1;
    D_0063B7C0 = 0;
    D_0063B7C8 = 0;
    CopyVector((int) D_004E7460, a0);
    D_0063B7CC = t;
    D_0063B7C8 = 1;
    D_0063B7C4 = 0;
}
void ResetGameOverEffect(void) {
    D_0063B7BC = 0;
    D_0063B7C4 = 0;
}
