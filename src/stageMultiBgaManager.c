#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", InitStageMultiBgaManager);

extern char *D_0070D430[];
extern char D_0070CAF0[];
extern int D_00274EC0[];
extern int stage_CheckAnimationFrameIn(void *a0);
extern void _AddVector(void *a0, void *a1, void *a2);

void EntryStageMultiBgaManager(void) {
    int i;
    for (i = 0; i <= 0x1D; i++) {
        if (D_0070D430[i] != 0) {
            if (stage_CheckAnimationFrameIn(&D_0070D430[i]) != 0) {
                D_0070D430[i] = 0;
            } else if (D_00274EC0[5] == 0) {
                char *x = D_0070D430[i] + 0x20;
                _AddVector(x, x, &D_0070CAF0[i * 0x50]);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", EntryStageMultiBgaManagerSensitive);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", auraInspireBefore);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001EC168);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001EC2E0);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", copyCurrentFBToFeedBackArea);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", blendWork0ToWork1);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", parallelAddFeedBackAreaToWork0);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", blurBlendFeedBackAreaToWork1);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001ECA40);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001ECB98);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001ECCA0);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", cleanUpFB);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001ED2F8);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", dispSun);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001ED4C8);

INCLUDE_ASM("asm/nonmatchings/src/stageMultiBgaManager", func_001ED608);

