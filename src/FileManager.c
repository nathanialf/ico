#include "common.h"

#include "ico/types.h"

extern int file_LoadCDFile(void);
INCLUDE_ASM("asm/nonmatchings/src/FileManager", file_Init);
INCLUDE_ASM("asm/nonmatchings/src/FileManager", file_LoadCDFile);
int file_LoadFile(void) {
    return file_LoadCDFile();
}
