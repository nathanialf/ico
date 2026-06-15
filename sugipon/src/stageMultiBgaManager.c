#include "common.h"

extern char *stage_SetLocalizeGeometry(void *a0);
extern void mc_TransMicroCode(void *a0, void *a1);
extern void GetInverseQuaternion(void *a0, void *a1);
extern void EntryMultiBgaManagerSensitive(void *a0, int a1, void *a2, void *a3, void *a4, void *a5);
extern int D_0062B8FC;
extern char *D_00706D00[];
extern char D_007063A0[];

void InitStageMultiBgaManager(void *a0, void *a1, void *a2, void *a3) {
    char *r = stage_SetLocalizeGeometry(a0);
    D_00706D00[D_0062B8FC] = r;
    mc_TransMicroCode(r + 0x20, a1);
    GetInverseQuaternion(D_00706D00[D_0062B8FC] + 0x30, a2);
    EntryMultiBgaManagerSensitive(D_007063A0, D_0062B8FC++, a0, a1, a2, a3);
    if (D_0062B8FC >= 30) {
        D_0062B8FC = 0;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", EntryStageMultiBgaManager);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", EntryStageMultiBgaManagerSensitive);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", DispStageMultiBgaManager);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001E9370);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001E94E8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001E9618);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001E9750);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001E9888);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001E9B38);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001E9BD0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001E9D28);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001E9E30);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001EA3C8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001EA488);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001EA558);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001EA658);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stageMultiBgaManager", func_001EA798);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
    unsigned int       f_14;  /* 0x14 */
    unsigned int       f_18;  /* 0x18 */
    unsigned int       f_1C;  /* 0x1C */
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_24;  /* 0x24 */
    unsigned int       f_28;  /* 0x28 */
    unsigned int       f_2C;  /* 0x2C */
} S_00706D78;

/* end struct shapes */
