#include "common.h"




extern int D_00632B00[];
extern int D_00632B10[];
extern void func_00264DF8();
extern void debug_FlushFontWindow();
extern void func_00268DA0();
INCLUDE_ASM("asm/nonmatchings/src/debug_exception", initLineTraceTable);

void traceLine(int *a, int *b, int *c, int x, ...)
{
    char buf[0x100];
    void *args = (char *)__builtin_next_arg(x) - 0x20;
    func_00268DA0(buf, x, args);
    debug_FlushFontWindow(a, b, c, buf);
}

void dispSource(int *a, int *b, int *c, int x, ...)
{
    char buf[0x100];
    void *args = (char *)__builtin_next_arg(x) - 0x20;
    func_00268DA0(buf, x, args);
    debug_FlushFontWindow(a, b, c, buf);
}

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", display);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debugEEExceptionMain);

void debugIOPExceptionMain(int a0, int a1, ...) {
}

void debug_assertMessage(char *fmt, ...)
{
    (void)fmt;
}

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debug_assert);

extern const char D_0060DAF0_a[] __asm__("D_006150F0");
extern const char D_00631CF0_a[] __asm__("D_00632AD0");
extern void debug_assertMessage__p4() __asm__("debug_assertMessage");
extern int func_00263FB0(float);

void debug_SetExceptionMessage(float *arg) {
    int i;
    for (i = 3; i >= 0; i--) {
        int v0 = func_00263FB0(arg[0]);
        int v1 = func_00263FB0(arg[1]);
        int v2 = func_00263FB0(arg[2]);
        int v3 = func_00263FB0(arg[3]);
        debug_assertMessage__p4((int)D_0060DAF0_a, v0, v1, v2, v3);
        arg += 4;
    }
    debug_assertMessage__p4((int)D_00631CF0_a);
}

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debugExceptionInit);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debugIOPExceptionInit);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A76B8);

void func_001A7820(int a0, int a1, int a2)
{
    func_00264DF8(a0, D_00632B10, a1, a2);
}

void func_001A7838(int a0)
{
    func_00264DF8(a0, D_00632B00);
}

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A7848);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A7AD0);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A7BB0);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A7DF0);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A7F20);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A80D0);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A82B0);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A84F8);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A8670);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A88F0);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A8B90);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A8D40);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A8E30);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A8F70);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A9370);

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", func_001A96D0);

