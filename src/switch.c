/* src/switch.c — __FILE__ anchor at .rodata 0x00618630 */

__attribute__((section(".rodata.0x00618630"))) const char D_00618630[16] = "src/switch.c";

#include "include_asm.h"
#include "regpin.h"
#include "matching.h"

INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C09C4);
INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C09C8);

/* Override ee-gcc's default .align 3 (8-byte) function alignment so the
 * matched body lands at its expected 4-aligned VMA offset 0x114 (the
 * VMA 0x1C0AD8 is 4-aligned but not 8-aligned within this .o). */
__asm__(".align 2");

short func_001C0AD8(char *self) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    return *(short *)(p + 0x2);
}

INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C0AE8);

int func_001C0BE0(char *self) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    return *(int *)(p + 0x4) == 0;
}

INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C0BF4);
int func_001C0BF8(char *self)
{
    register int accum __asm__("$4");
    short *p = *(short **)(*(char **)(self + 0x15C) + 0x800);
    if (__builtin_abs((int)p[1]) < 0xBB9) {
        accum = 0;
        __asm__ __volatile__("" : "+r"(accum));
        if (__builtin_abs((int)p[0]) < 0xBB9) goto done;
    }
    accum = 1;
done:
    __asm__ __volatile__("" : "+r"(accum));
    return accum;
}
TRAILING_PAD_NOP();
INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C0C40);
