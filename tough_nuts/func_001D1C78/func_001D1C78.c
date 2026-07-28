/* src/girlForceField.c — __FILE__ anchor at .rodata 0x00618F08 */

const char D_00618F08[24] = "src/girlForceField.c";

#include "include_asm.h"
#include "ico/types.h"
#include "matching.h"
#include "regpin.h"

extern int D_00632010;
extern int func_0013A0F8(int handle, int size, const char *file, int line);
void func_001D1C78(int *a0, int *a1)
{
    float *r = (float *)func_0013A0F8(D_00632010, 0xC, D_00618F08, 0x17);
    float v = *(float *)((char *)a1 + 0x28);
    float one = 1.0f;
    r[0] = v;
    *(int *)((char *)r + 0x8) = 0;
    r[1] = one / v;
    {
        float *y = *(float **)((char *)*(int **)((char *)a0 + 0x15C) + 0x840);
        *(float *)((char *)y + 0x20) = one;
        *(float *)((char *)y + 0x28) = one;
        *(float *)((char *)y + 0x24) = one;
    }
}
