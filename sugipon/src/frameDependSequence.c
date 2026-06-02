#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/frameDependSequence", playSE);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/frameDependSequence", playSERandomID);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/frameDependSequence", playSEConditionID);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/frameDependSequence", playEff);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/frameDependSequence", execEff);

extern void execEff(int a0, int a1);

void ExecFrameDependSequence(int a0) {
    execEff(a0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/frameDependSequence", executeSEPackageByGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/frameDependSequence", executeSEPackageWithNoGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/frameDependSequence", ExecuteSEPackageWithGroupVariation);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/frameDependSequence", ExecuteSEPackage);
