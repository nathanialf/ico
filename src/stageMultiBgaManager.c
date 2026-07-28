#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", InitStageMultiBgaManager);

extern char *D_0070D430[];
extern char D_0070CAF0[];
extern int D_00274EC0[];
extern int stage_CheckAnimationFrameIn(void *a0);
extern void _ApplyCurrentMatrix(void *a0, void *a1, void *a2);

void EntryStageMultiBgaManager(void) {
    int i;
    for (i = 0; i <= 0x1D; i++) {
        if (D_0070D430[i] != 0) {
            if (stage_CheckAnimationFrameIn(&D_0070D430[i]) != 0) {
                D_0070D430[i] = 0;
            } else if (D_00274EC0[5] == 0) {
                char *x = D_0070D430[i] + 0x20;
                _ApplyCurrentMatrix(x, x, &D_0070CAF0[i * 0x50]);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", EntryStageMultiBgaManagerSensitive);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", DispStageMultiBgaManager);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001EC168);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001EC2E0);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001EC410);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001EC5C0);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001EC6F8);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001EC9A8);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001ECA40);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001ECB98);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001ECCA0);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001ED238);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001ED2F8);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001ED3C8);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001ED4C8);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001ED608);

