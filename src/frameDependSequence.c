#include "common.h"


extern float D_006333F0;
extern void func_001D0FA8();
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", playSE);

void playSERandomID(int a0, int a1)
{
    D_006333F0 = 1.0f;
    if (a0) {
        func_001D0FA8(a0);
    } else {
        playSE(a1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", playSEConditionID);

void playEff(int a0, int a1, float f)
{
    D_006333F0 = f;
    func_001D0FA8(a0, a1, 0);
}

INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", execEff);

INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", ExecFrameDependSequence);

INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", executeSEPackageByGObj);

INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", executeSEPackageWithNoGObj);

INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", ExecuteSEPackageWithGroupVariation);

INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", ExecuteSEPackage);

