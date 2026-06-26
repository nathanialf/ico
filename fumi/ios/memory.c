#include "common.h"
#include "vu0.h"

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

extern int func_00261900(char *dst, int src, int n);
extern char D_00551350[];
extern char D_00551430[];
extern char D_005515F0[];
extern char D_00551828[];
extern char D_00551840[];
extern char D_00551850[];
extern char D_00551860[];
extern char D_00551878[];
extern char D_006A04F0[];

void iosMallocInitPartition(int a0, int a1) {
    int node = *(int *)(a0 + a1 + 0x38);
    int r;

    debug_assertMessage(D_00551828, a0);
    if (node == 0) {
        return;
    }
    do {
            node += a1;
            func_00261900(D_006A04F0, node + 0x10, 0xF);
            D_006A04F0[0xF] = 0;
            r = func_002613B4((int *)node, D_005515F0);
            if (r == 0) {
                debug_assertMessage(D_00551840, node - a1, D_006A04F0);
                r = 0xB;
                goto delay;
            }
            r = func_002613B4((int *)node, D_00551350);
            if (r == 0) {
                debug_assertMessage(D_00551850, node - a1);
                r = 0xB;
                goto delay;
            }
            r = func_002613B4((int *)node, D_00551430);
            if (r != 0) {
                debug_assertMessage(D_00551878, node - a1, node);
                return;
            }
            debug_assertMessage(D_00551860);
            r = 0xB;
        delay:
            do {
                r--;
                VU0_NOP();
                VU0_NOP();
                VU0_NOP();
                VU0_NOP();
            } while (r >= 0);
            node = *(volatile int *)(node + 0x24);
    } while (node != 0);
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", iosMallocAlignDebug);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/memory", func_00139B40);
