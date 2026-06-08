#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", iosMallocSetPartition);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", iosMallocResetPartition);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", iosMallocSetPartitionName);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", iosMallocClearPartition);

extern int func_002613B4(int *a0, const char *a1);
extern void func_002614F8(unsigned char *ptr, int value);
extern void debug_assertMessage(const char *fmt, ...);

extern char D_00551340[];

extern char D_00551388[];

extern char D_005513A8[];

int iosMallocDebug(int *a0, int a1)
{
    if (a0 == 0)
    {
        debug_assertMessage(D_00551388);
        return 0;
    }
    if (func_002613B4(a0, D_00551340) != 0)
    {
        debug_assertMessage(D_005513A8);
        return 0;
    }
    func_002614F8((unsigned char *)((char *) a0 + 0x10), a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", _iosFreeWithFill);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", iosFree);

extern int func_001007A0(int a0);

extern char D_00551688[];

void iosMallocCheckLeak(int *a0, int a1, int a2)
{
    int *end = *(int **)((char *) a0 - 0x1C);
    func_001007A0(0);
    iosMallocCheckLeak2(a0);
    debug_assertMessage(D_00551688, a1, a2, a0, end);
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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", iosMallocCheckLeak2);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", iosReallocDebug);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", iosMallocInitPartition);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", iosMallocAlignDebug);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", func_00139B40);
