#include "common.h"

extern void shadow_RenderVolumeMulti(void *a0);

void file_Init(void *a0) {
    shadow_RenderVolumeMulti(a0);
}

void file_LoadCDFile(void *a0) {
    shadow_RenderVolumeMulti(a0);
}

void file_LoadFile(int a0) {
    file_LoadCDFile(*(void **)(a0 + 0x15C));
}

void func_0010F040(int a0) {
    file_LoadFile(a0);
}

void func_0010F048(int a0) {
    file_Init(*(void **)(a0 + 0x15C));
}

void func_0010F050(int a0) {
    func_0010F048(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", func_0010F058);

void func_0010F068(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", func_0010F070);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", func_0010F220);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", func_0010F958);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", func_0010F978);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", func_0010F9D0);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", func_0010FAB0);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", func_0010FB08);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", func_0010FC20);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", func_0010FD48);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", func_0010FEC8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", func_00110060);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", func_001102C8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", func_001103F0);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/FileManager", func_00110580);
