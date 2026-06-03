#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", kanbanReqAdd);

void init_textures_of_specified_property(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", kanbanInit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", func_001AD258);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", fade_exec);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", display_layout);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", kanbanReqDel);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", kanbanReqDelFade);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", kanbanReqAllDel);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", kanbanReqAllDelFade);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", kanbanExec);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", func_001ADB00);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", func_001ADB38);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", func_001ADC68);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", func_001ADE70);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/kanban", func_001ADFC8);

extern int D_0062B2E4;

void func_001ADFE8(void) {
    D_0062B2E4 = 1;
}

extern void soundSeDefPlayWithVolumeRate(int a0, unsigned int a1, int a2, int a3);

void func_001ADFF8(void) {
    soundSeDefPlayWithVolumeRate(0x190, 0xFFFFFFFE, 0, 0);
}
