#include "common.h"

#include "vu0.h"

INCLUDE_ASM("asm/nonmatchings/ios/memory", iosMallocSetPartition);

INCLUDE_ASM("asm/nonmatchings/ios/memory", iosMallocResetPartition);

INCLUDE_ASM("asm/nonmatchings/ios/memory", iosMallocSetPartitionName);

INCLUDE_ASM("asm/nonmatchings/ios/memory", iosMallocClearPartition);

extern char D_00556F70[];
extern char D_00556FB8[];
extern char D_00556FD8[];
extern void debug_assertMessage();
extern int func_00265024(int *a0, const char *a1);
extern void func_00265168(unsigned char *ptr, int value);

int iosMallocDebug(int *a0, int a1)
{
    if (a0 == 0)
    {
        debug_assertMessage(D_00556FB8);
        return 0;
    }
    if (func_00265024(a0, D_00556F70) != 0)
    {
        debug_assertMessage(D_00556FD8);
        return 0;
    }
    func_00265168((unsigned char *)((char *) a0 + 0x10), a1);
}

INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00138C78);

INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00138E30);

INCLUDE_ASM("asm/nonmatchings/ios/memory", func_001392A8);

extern char D_005572B8[];
extern int func_001007A0(int a0);
extern int iosMallocCheckLeak2(int a0);

void iosMallocCheckLeak(int *a0, int a1, int a2)
{
    int *end = *(int **)((char *) a0 - 0x1C);
    func_001007A0(0);
    iosMallocCheckLeak2(a0);
    debug_assertMessage(D_005572B8, a1, a2, a0, end);
    {
        register int g = (unsigned int) a0 < (unsigned int) end;
        if (g)
        {
            do
            {
                *(unsigned int *) a0 = 0xFFFFFFFFu;
                a0++;
            } while ((unsigned int) a0 < (unsigned int) end);
        }
    }
    func_001007A0(0);
}

INCLUDE_ASM("asm/nonmatchings/ios/memory", iosMallocCheckLeak2);

INCLUDE_ASM("asm/nonmatchings/ios/memory", iosReallocDebug);

INCLUDE_ASM("asm/nonmatchings/ios/memory", iosMallocInitPartition);

INCLUDE_ASM("asm/nonmatchings/ios/memory", iosMallocAlignDebug);

INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00139FE8);

INCLUDE_ASM("asm/nonmatchings/ios/memory", func_0013A0F8);

INCLUDE_ASM("asm/nonmatchings/ios/memory", func_0013A200);

