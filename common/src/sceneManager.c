#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/sceneManager", GetRealModelId);

extern int D_0062B418;

int InitStageLight(void) {
    return D_0062B418;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/sceneManager", initSceneGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/sceneManager", initParentLink);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/sceneManager", initWayData);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/sceneManager", InitSceneObjects);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/sceneManager", HotInitSceneObjects);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/sceneManager", ChangeStageStartInfo);

extern void group_select(int a0);

void CreateLayoutedGObj(int a0) {
    group_select(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/sceneManager", MoveNextStage_Set);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/sceneManager", test_nextstage_firstwalk_set);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/sceneManager", GetStageStartInfo);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/sceneManager", MoveNextStage_Clear);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/sceneManager", func_001B55D8);
