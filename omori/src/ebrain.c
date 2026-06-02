#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", eBrainProcess);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", eBrainGetTargetGeneratorFromLabel);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", eBrainGetTarget);

void eBrainInit(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    *((char *)q + 0xCC) = 0;
}

float eBrainStatusSet(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return *(float *)((char *)q + 0xC8);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", eBrainSendMes);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", GetStageFromLabel);

void eBrainGetTargetGeneratorFromLabelStage(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    *((char *)q + 0xCD) = 0;
}

int func_0018DFA8(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    void *q = *(void **)((char *)p + 0x7F0);
    return *(unsigned char *)((char *)q + 0xCD);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018DFB8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018E0E0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018E2B8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018E348);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018E430);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018E670);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018E830);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018F1A8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018F1F0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018F2A0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018F3A0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018F470);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018F580);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/ebrain", func_0018F608);
