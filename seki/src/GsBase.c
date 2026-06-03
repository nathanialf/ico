#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_SetFrame);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_Init);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_Reduction);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_KeepFrameBuffer);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_fade);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_scissorOnDemo);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_controlBrightness);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_antiAlias);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_setNormalReg);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_setSemitransReg);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_setSpecularReg);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_setParticleReg);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_MakeCommonMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_SetGsDefault);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_PostEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_InitGSSystem);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_UpdateGSSystem);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_ResetGSSystem);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_SetVSMatrixSub);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_SetVSMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_ClipBox);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_StageSettingTool);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_StageSetting);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_SetBGColor);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/GsBase", gsb_GetBGColor);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
} S_0054E7E0;  /* stride 0x10 */

/* end struct shapes */
