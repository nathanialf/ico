/* src/clothTest.c — __FILE__ anchor at .rodata 0x00618960
 *
 * TU range: single function at 0x001C92D8 (size 0x4C).
 * The 4-byte gap before the next TU (cod/0C9324 at 0x001C9324) is
 * alignment padding supplied by the linker --gap-fill.
 */

#include "clothTest.h"

int *func_001C92D8(void)
{
    int *p = func_0013A0F8(D_00632010, 0x290, (char *)D_00618960, 0x41);
    *p = func_001C5BA0(D_004C0960);
    return p;
}
