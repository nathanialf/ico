#include "common.h"

extern int execNormalMove(void);

int warpGirlOutStage(void) {
    return execNormalMove() != 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", warpGirlInStage);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", warpGirlInit);

extern void *D_00629DE4;

void func_0017C0B8(void) {
    void *o = D_00629DE4;
    if (o) {
        void *s = *(void **)((char *)o + 0x164);
        *(long *)((char *)s + 0x20) &= -0x201;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C0E0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C108);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C130);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C1B0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C230);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C308);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C3D0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C560);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C658);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C910);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017CE38);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017D318);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017D560);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DA68);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DC10);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DC40);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DC68);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DCE0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DD70);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DDD8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DE40);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DE80);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DEE8);
