#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcard", iosMcHandlerWrite);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcard", iosMcHandlerRead);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcard", iosMcMgrChdirProduct);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcard", iosMcMgrSaveSeg);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcard", iosMcMgrLoadSeg);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcard", iosMcMgrSaveProductBlock);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcard", iosMcMgrLoadProductBlock);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcard", iosMcMgrGetBlockSaveInfo);

void iosMcManager(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcard", iosMcMgrSync);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcard", iosMcTest);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcard", iosMcSync);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mcard", iosMcGetInfo);
