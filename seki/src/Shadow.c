#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_Reset);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_Draw);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_Render);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_getShadowVectorAverage);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_EntryClusterShadow);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_EntryNormalShadow);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", __GetCameraPos);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_RenderVolume);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_RenderVolumeMulti);

extern void reg_DispAccessoryWithShadow(void);
extern int D_0062A040;

void shadow_MakeObjectData(void) {
    reg_DispAccessoryWithShadow();
}

void shadow_Tool(int a0) {
    D_0062A040 = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_KillShadow);

void shadow_DispCancel(void) {
    D_0062A040 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_SetLength);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", shadow_Init);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", func_00122FE8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", func_00123AA8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", func_00123AC8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/Shadow", func_00123B18);
