/* src/girlForceField.c — __FILE__ anchor at .rodata 0x00618F08 */

const char D_00618F08[24] = "src/girlForceField.c";

#include "include_asm.h"
#include "matching.h"
#include "regpin.h"

extern int D_00632010;
extern int func_0013A0F8(int handle, int size, const char *file, int line);
int *func_001D1C78(int *self, int *src)
{
    register int *ret REG("$2") = (int *)func_0013A0F8(D_00632010, 0xC, D_00618F08, 0x17);
    register float val REG("$f0") = *(float *)((char *)src + 0x28);
    register int *buf REG("$3");
    buf = ret;
    MATERIALIZE(buf);
    KEEP_LIVE(ret);
    {
        register float one REG("$f1") = 1.0f;
        int *p_840;
        *(float *)((char *)buf + 0) = val;
        *(int *)((char *)buf + 8) = 0;
        val = one / val;
        *(float *)((char *)buf + 4) = val;
        KEEP_LIVE_MEM(buf);
        p_840 = (int *)((int *)self[0x15C / 4])[0x840 / 4];
        *(float volatile *)((char *)p_840 + 0x20) = one;
        *(float volatile *)((char *)p_840 + 0x28) = one;
        *(float volatile *)((char *)p_840 + 0x24) = one;
    }
    return ret;
}
