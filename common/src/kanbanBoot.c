#include "common.h"

extern void soundSeDefPlayWithVolumeRate(int a0, unsigned int a1, int a2, int a3);

void kanbanBootMcCheck(void) {
    soundSeDefPlayWithVolumeRate(0x191, 0xFFFFFFFE, 0, 0);
}

void kanbanBootMain(void) {
    soundSeDefPlayWithVolumeRate(0x18F, 0xFFFFFFFE, 0, 0);
}

extern int D_0060F6E0[];
extern void debug_assertMessage(void *a0);

void kanbanBootInit(void) {
    debug_assertMessage(D_0060F6E0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", kanbanBootStart);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AE148);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AE4A8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AE800);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AE9C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AEB80);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AED90);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AEF78);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AF120);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AF478);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AF648);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AF778);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AFAE0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AFCB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AFE88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001AFF98);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001B0388);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001B0680);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001B0898);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001B0A90);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001B0D70);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001B0EF0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001B1098);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001B1230);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001B14B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanbanBoot", func_001B1760);
