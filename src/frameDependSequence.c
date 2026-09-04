#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", playSE);
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", playSERandomID);
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", playSEConditionID);
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", playEff);
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", execEff);
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", execVibCondition);
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", ExecFrameDependSequence);
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", executeSEPackageByGObj);
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", executeSEPackageWithNoGObj);
extern float D_0063B8B0;
extern void executeSEPackageWithNoGObj(int a0);
void ExecuteSEPackageWithGroupVariation(void *a0, int a1, int a2) {
    D_0063B8B0 = 1.0f;
    if (a0 != 0) {
        executeSEPackageByGObj(a0, a1, a2);
    } else {
        executeSEPackageWithNoGObj(a1);
    }
}
extern void ExecuteSEPackageWithGroupVariation(void *a0, int a1, int a2);

void ExecuteSEPackage(int a0, int a1) {
    ExecuteSEPackageWithGroupVariation(a0, a1, 0);
}
extern float D_0063B8B0;
extern void executeSEPackageByGObj();

void ExecuteSEPackageWithVolumeRate(int a0, int a1, float f)
{
    D_0063B8B0 = f;
    executeSEPackageByGObj(a0, a1, 0);
}
extern void soundSeGroupStop(int a0);

void StopSEPackageWithGroupVariation(int a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    p += a1;
    soundSeGroupStop(p[0x187]);
}
void StopSEPackage(int a0) {
    StopSEPackageWithGroupVariation(a0, 0);
}
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", InitFrameDependSequence);
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", ExecuteDirectSEWithGroupVariation);
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", ExecuteDirectSE);
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", StopFDSVibration);
extern int playSE(void);
extern int playSEConditionID(int a0);
extern int playSERandomID(int a0);

int execSE(int a0) {
    if (a0 <= 0xFFFF) {
        return playSE();
    } else if (a0 <= 0x1FFFF) {
        return playSERandomID(a0 - 0x10000);
    } else {
        return playSEConditionID(a0 - 0x20000);
    }
}
int checkWaterDepth(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    return (int)(*(float *)((char *)p + 0x644)) < a1;
}
int checkModelDataID(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    return p[0x21] == a1;
}
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", checkWeaponType);
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", execVib);
extern int CheckWeaponKind(char *self);
extern int D_0063B8AC;
extern void LightTorchOffOfWeapon(int *self);

int execWeaponLightOff(void)
{
    int *p;
    int *q;
    p = (int *)((int *)D_0063B8AC)[0x15C/4];
    q = (int *)p[0x630/4];
    if (q != 0) {
        if (CheckWeaponKind(q) == 1) {
            int *r = (int *)((int *)D_0063B8AC)[0x15C/4];
            LightTorchOffOfWeapon((int *)r[0x630/4]);
        }
    }
    return 1;
}
