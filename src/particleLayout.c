/* src/particleLayout.c — __FILE__ anchor at .rodata 0x00619EC0
 *
 * TU range: single function at 0x001E8EB8 (size 0x6C).
 * The 4-byte gap before the next TU (cod/0E8F28 at 0x001E8F28) is
 * alignment padding supplied by the linker --gap-fill.
 */

#include "particleLayout.h"

int *func_001E8EB8(int *self, int *other)
{
    int *r;
    int *p_15c;
    r = func_0013A0F8(D_00632010, 0x4, (char *)D_00619EC0, 0xC);
    p_15c = (int *)self[0x15C / 4];
    *r = func_001E8B48(other[0x30 / 4], other, (char *)p_15c + 0x60);
    return r;
}
