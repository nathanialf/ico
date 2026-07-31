#include "common.h"




extern int D_00632B00[];
extern int D_00632B10[];
extern void func_00264DF8();
extern void debug_FlushFontWindow();
extern void func_00268DA0();
extern char D_00615060[];
extern char D_00615078[];
extern const char D_00631CD8_a[] __asm__("D_00632AB8");
extern const char D_00631CE0_a[] __asm__("D_00632AC0");
extern const char D_00631CE8_a[] __asm__("D_00632AC8");
extern const char D_00631CF0_a[] __asm__("D_00632AD0");
extern void debug_assertMessage(char *fmt, ...);
extern int func_00263FB0(float);

void initLineTraceTable(unsigned char *arg, int slot_size) {
    int is_float = 0;
    int row;

    switch (slot_size) {
    case 0:
        is_float = 1;
        slot_size = 4;
        debug_assertMessage((int)D_00615060, arg);
        break;
    case 1:
    case 2:
    case 4:
    case 8:
    case 16:
        debug_assertMessage((int)D_00615078, arg, slot_size);
        break;
    default:
        return;
    }

    for (row = 0; row < 0x10 / slot_size; row++) {
        if (!is_float) {
            int col;
            for (col = 0x10 / (0x10 / slot_size) - 1; col >= 0; col--) {
                debug_assertMessage((int)D_00631CD8_a, arg[row * slot_size + col]);
            }
            debug_assertMessage((int)D_00631CE0_a);
        } else {
            debug_assertMessage((int)D_00631CE8_a, func_00263FB0(((float *)arg)[row]));
        }
    }
    debug_assertMessage((int)D_00631CF0_a);
}

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

void debugEEExceptionMain(int a0, int a1, int a2, int a3, ...) {
}

void debugIOPExceptionMain(int a0, int a1, ...) {
}

void debug_assertMessage(char *fmt, ...)
{
    (void)fmt;
}

INCLUDE_ASM("asm/nonmatchings/src/debug_exception", debug_assert);

extern const char D_0060DAF0_a[] __asm__("D_006150F0");
extern const char D_00631CF0_a[] __asm__("D_00632AD0");
extern int func_00263FB0(float);

void debug_SetExceptionMessage(float *arg) {
    int i;
    for (i = 3; i >= 0; i--) {
        int v0 = func_00263FB0(arg[0]);
        int v1 = func_00263FB0(arg[1]);
        int v2 = func_00263FB0(arg[2]);
        int v3 = func_00263FB0(arg[3]);
        debug_assertMessage((int)D_0060DAF0_a, v0, v1, v2, v3);
        arg += 4;
    }
    debug_assertMessage((int)D_00631CF0_a);
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

