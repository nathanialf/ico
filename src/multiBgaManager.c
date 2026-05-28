/* src/multiBgaManager.c — __FILE__ anchor at .rodata 0x00619DC8 */

const char D_00619DC8[24] = "src/multiBgaManager.c";

#include "include_asm.h"
#include "regpin.h"

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

extern char D_00276140[];

void func_001E6C30(char *base, int idx, char *a7)
{
    char *g = D_00276140;
    register int neg REG("$3") = -1;
    register int prod REG("$7") = idx * 0x50;
    char *p = base + prod;
    *(int *)(p + 0x40) = neg;
    func_00105F00(p + 0x10, a7);
    func_00105F00(p + 0x20, D_00275850);
    func_0010D830(p + 0x30, (int)g);
    *(int *)p = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/multiBgaManager", func_001E6CA0);
