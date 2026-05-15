/* src/attackhit.c — __FILE__ anchor at .rodata 0x0055A518
 *
 * TU range: [0x00181960, 0x00181F38)  (next subseg: src/cod/081F38 at 0x00181F38)
 *
 * Six funcs:
 *   - func_00181960 (anchor; complex linked-list scan with debug logs)
 *   - func_00181BB8 (jr ra + nop — empty stub)
 *   - func_00181BC0 (jr ra + nop — empty stub)
 *   - func_00181BC8 (small wrapper: forward to func_00180F40 + func_00181960)
 *   - func_00181BF8 (anchor; long initializer using D_0055A3F0 template)
 *   - func_00181D88 (anchor; same shape as func_00181BF8 at line 0x300)
 */

#include "attackhit.h"

INCLUDE_ASM("asm/nonmatchings/src/attackhit", func_00181960);

void func_00181BB8(void) {}

void func_00181BC0(void) {}

void func_00181BC8(int a0)
{
    int buf[28];
    int *v0 = *(int **)((char *)a0 + 0x164);
    func_00180F40(buf, a0, v0[0x140 / 4]);
    func_00181960(buf);
}

/* func_00181BF8 parked at tough_nuts/func_00181BF8/ (67-byte diff plateau;
 * gcc 2.9 caller-save regalloc choices for D_0055A3F0 copy loop). */
INCLUDE_ASM("asm/nonmatchings/src/attackhit", func_00181BF8);

INCLUDE_ASM("asm/nonmatchings/src/attackhit", func_00181D88);
