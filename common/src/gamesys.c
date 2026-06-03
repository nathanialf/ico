#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysObjInfoInit);

extern int iosMcManager(void);

int gamesysObjInfoSave(void)
{
    iosMcManager();
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysObjInfoLoad);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysObjInfoEmptyAreaSearch);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysObjInfoBaseSet);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysBackStageProcess);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysGeneratorInfoLoad);

extern int init_debug_menu(void);

int gamesysCharacterInfoLoad(void)
{
    init_debug_menu();
    return -1;
}

int gamesysNObjInfoInit(void)
{
    init_debug_menu();
    return -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysObjInfoStageInitFlagCls);

extern int InitCharFileManager(void);

int gamesysObjInfoStageInitPosSaveUnlock(void)
{
    InitCharFileManager();
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysObjInfoPosSetStage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysObjInfoUniqDataSet);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysObjInfoPosNewStageSet);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysObjInfoGet);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysObjInfoCls);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysGirlStageGet);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysGetGirlStageIDAndPosition);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysStageExitTimeSet);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysMemoryHandlerWrite);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysMemoryHandlerRead);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysMemorySave);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysMemoryLoad);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysVersionLoad);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysVersionSave);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysCharacterInfoSave);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", gamesysGeneratorInfoSave);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", func_001A98E0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/gamesys", func_001A99D0);
