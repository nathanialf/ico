#include "common.h"

typedef struct { short f0; char pad2[0xE]; int f10; int f14; int f18; } EBSlot;

INCLUDE_ASM("asm/nonmatchings/src/ebrain", eBrainProcess);
INCLUDE_ASM("asm/nonmatchings/src/ebrain", eBrainGetTargetGeneratorFromLabel);
INCLUDE_ASM("asm/nonmatchings/src/ebrain", eBrainGetTarget);
extern int eBrainBoyChaseCount;
extern int eBrainGirlChaseCount;
extern int D_0063C2CC;
extern int D_0063C2D0;
extern int D_006E6750[];

void eBrainInit(void)
{
    int *p = D_006E6750;
    int i;
    eBrainGirlChaseCount = 0;
    eBrainBoyChaseCount = 0;
    D_0063C2CC = 0;
    p = (int *)((char *)p + 0x37C);
    D_0063C2D0 = 0;
    i = 0x1F;
    do {
        *p = 0;
        p = (int *)((char *)p - 0x1C);
        i--;
    } while (i >= 0);
}
extern char D_00555580[];
extern void debug_StdPrintfDummy(const char *);

int eBrainStatusSet(int a0, int a1) {
    EBSlot *slot;
    int i;
    if (a1 != 4) return 0;
    for (i = 0; i < 0x20; i++) {
        if (((EBSlot *)D_006E6750)[i].f18 == 0) break;
    }
    if (i < 0x20) slot = &((EBSlot *)D_006E6750)[i];
    else slot = 0;
    if (slot == 0) {
        debug_StdPrintfDummy(D_00555580);
        return 0;
    }
    slot->f18 = a0;
    slot->f0 = 0;
    slot->f10 = 0;
    return (int)slot;
}
INCLUDE_ASM("asm/nonmatchings/src/ebrain", eBrainSendMes);
INCLUDE_ASM("asm/nonmatchings/src/ebrain", GetStageFromLabel);
INCLUDE_ASM("asm/nonmatchings/src/ebrain", eBrainGetTargetGeneratorFromLabelStage);
