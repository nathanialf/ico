#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", pursueNodeList);

int InitMotionFile(unsigned int *self)
{
    int r;
    unsigned int p = (unsigned int)self + 0x10;
    if (p < self[2]) r = 0; else r = -1;
    return r;
}

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", InitMotionMemorySize);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", AddMotionMemorySize);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", GetMotionMemorySize);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", ResetDynamicMotionManager);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", ResetStatic2MotionManager);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", CheckMotionIncludeFacialData);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", func_001D8590);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", func_001D8758);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", func_001D88B8);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", func_001D8968);

