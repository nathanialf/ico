#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_MakeGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_ApplyData);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_Init);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_SetAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_ContinueAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_ResetAnimation);

extern int D_0062A054;

void stage_CalcAnimationNoParent(int a0) {
    D_0062A054 = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_CalcAnimationParent);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_DispAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_SetScale);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_PlayBgAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_PlayBgAnimationDissolve);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_MakePlayBgAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_KillPlayBgAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_DispBgAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_SetCameraForceOff);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_CheckAnimationFinish);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_CheckAnimationFrame);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_SetLoopFlag);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_SetFrameStep);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_SetParentOfGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_SetParentOfGObjWithLocalRotationFlag);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_SetLocalizeGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_KillPlayBgAnimationIfOverMaxCount);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_CheckAnimationFrameIn);

extern void font_GetWidth(void);

void func_0012A950(void) {
    font_GetWidth();
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", func_0012A958);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", func_0012AA28);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", func_0012AAB8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", func_0012AB00);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", func_0012AB48);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", func_0012ABB0);
