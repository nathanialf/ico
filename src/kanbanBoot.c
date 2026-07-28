#include "common.h"


extern void debug_assertMessage();
extern int D_00616CE0[];
extern void soundSeDefPlayWithVolumeRate(int a0, unsigned int a1, int a2, int a3);

void kanbanBootMcCheck(void) {
    soundSeDefPlayWithVolumeRate(0x191, 0xFFFFFFFE, 0, 0);
}

void kanbanBootMain(void) {
    soundSeDefPlayWithVolumeRate(0x18F, 0xFFFFFFFE, 0, 0);
}

void kanbanBootInit(void)
{
    debug_assertMessage(D_00616CE0);
}

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", kanbanBootStart);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B0BB8);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B0F18);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B1270);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B1438);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B15F0);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B1800);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B19E8);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B1B90);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B1EF0);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B20C0);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B21F0);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B2558);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B2750);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B2920);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B2A30);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B2E28);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B3120);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B3338);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B3530);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B3810);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B3990);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B3B38);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B3CD0);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B3F58);

INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", func_001B4208);

/* .data — carved VMA 0x4BCEC0..0x4BCED8 (1 symbol), bytes verified against baserom/baseelf.rom */
unsigned int D_004BCEC0[6] = {
    0x00000163, 0x0000015F, 0x0000015E, 0x00000160,
    0x0000015D, 0x00000000,
};

