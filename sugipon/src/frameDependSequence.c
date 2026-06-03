#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/frameDependSequence", playSE);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/frameDependSequence", playSERandomID);

extern void playSERandomID(int a0, int a1, int a2);

void playSEConditionID(int a0, int a1) {
    playSERandomID(a0, a1, 0);
}

extern float D_0062B6B4;
extern void func_001CE340(int a0, int a1, int a2);

void playEff(int a0, int a1, float f) {
    D_0062B6B4 = f;
    func_001CE340(a0, a1, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/frameDependSequence", execEff);

extern void execEff(int a0, int a1);

void ExecFrameDependSequence(int a0) {
    execEff(a0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/frameDependSequence", executeSEPackageByGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/frameDependSequence", executeSEPackageWithNoGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/frameDependSequence", ExecuteSEPackageWithGroupVariation);

int ExecuteSEPackage(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    return p[0x21] == a1;
}
