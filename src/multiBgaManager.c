/* src/multiBgaManager.c — __FILE__ anchor at .rodata 0x00619DC8 */

__attribute__((section(".rodata.0x00619DC8"))) const char D_00619DC8[24] = "src/multiBgaManager.c";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/multiBgaManager", func_001E69D8);
extern char D_00275850[];

void func_001E6A98(char *base, int idx, int v6, char *a7, char *a8)
{
    char *p = base + idx * 0x50;
    *(int *)(p + 0x40) = v6;
    func_00105F00(p + 0x10, a7);
    func_00105F00(p + 0x20, D_00275850);
    func_0010D830(p + 0x30, a8);
    *(int *)p = 0;
}
extern void func_00105F00(char *dst, char *src);
extern void func_0010D830(char *dst, int v);

void func_001E6B00(char *base, int idx, int v6, char *a7, char *a8, int a9)
{
    char *p = base + idx * 0x50;
    *(int *)(p + 0x40) = v6;
    func_00105F00(p + 0x10, a7);
    func_00105F00(p + 0x20, a9);
    func_0010D830(p + 0x30, a8);
    *(int *)p = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/multiBgaManager", func_001E6B70);
INCLUDE_ASM("asm/nonmatchings/src/multiBgaManager", func_001E6C30);
INCLUDE_ASM("asm/nonmatchings/src/multiBgaManager", func_001E6CA0);
