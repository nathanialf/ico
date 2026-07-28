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

extern char D_00556F80[];
extern char D_00557060[];
extern char D_00557220[];
extern char D_00557458[];
extern char D_00557470[];
extern char D_00557480[];
extern char D_00557490[];
extern char D_005574A8[];
extern char D_006A6970[];
extern void debug_assertMessage__p4(const char *fmt, ...) __asm__("debug_assertMessage");
extern int func_00265570(char *dst, int src, int n);

void iosMallocInitPartition(int a0, int a1) {
    int node = *(int *)(a0 + a1 + 0x38);
    int r;

    debug_assertMessage__p4(D_00557458, a0);
    if (node == 0) {
        return;
    }
    do {
            node += a1;
            func_00265570(D_006A6970, node + 0x10, 0xF);
            D_006A6970[0xF] = 0;
            r = func_00265024((int *)node, D_00557220);
            if (r == 0) {
                debug_assertMessage__p4(D_00557470, node - a1, D_006A6970);
                r = 0xB;
                goto delay;
            }
            r = func_00265024((int *)node, D_00556F80);
            if (r == 0) {
                debug_assertMessage__p4(D_00557480, node - a1);
                r = 0xB;
                goto delay;
            }
            r = func_00265024((int *)node, D_00557060);
            if (r != 0) {
                debug_assertMessage__p4(D_005574A8, node - a1, node);
                return;
            }
            debug_assertMessage__p4(D_00557490);
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

INCLUDE_ASM("asm/nonmatchings/ios/memory", iosMallocAlignDebug);

INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00139FE8);

INCLUDE_ASM("asm/nonmatchings/ios/memory", func_0013A0F8);

INCLUDE_ASM("asm/nonmatchings/ios/memory", func_0013A200);

