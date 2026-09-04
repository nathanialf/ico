#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/FileManager", file_Init);
INCLUDE_ASM("asm/nonmatchings/src/FileManager", file_LoadCDFile);
extern int file_LoadCDFile(void);

int file_LoadFile(void)
{
    return file_LoadCDFile();
}
