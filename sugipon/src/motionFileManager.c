#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", pursueNodeList);

int InitMotionFile(void *a0) {
    return (char *)a0 + 0x10 < *(char **)((char *)a0 + 0x8) ? 0 : -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", InitMotionMemorySize);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", AddMotionMemorySize);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", GetMotionMemorySize);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", ResetDynamicMotionManager);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", ResetStatic2MotionManager);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", CheckMotionIncludeFacialData);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", func_001D5928);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", func_001D5AF0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", func_001D5C50);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", func_001D5D00);
