/* src/sugiTree.c — __FILE__ anchor at .rodata 0x0061A6D8
 *
 * TU range: [0x001F16A0, 0x001F1838)  (next TU: cod/0F1838 at 0x001F1838)
 *
 * The 4-byte `nop` between each function (at 0xF16F4, 0xF17AC, 0xF1834) is
 * 8-byte function alignment — supplied by `__asm__(".skip 4")` at file
 * scope. D_00632010 is gp_rel; verified -0x68E0 from _gp (in range).
 */

#include "sugiTree.h"

short *func_001F16A0(void)
{
    int  local_pad[4];
    short *buf = func_0013A0F8(D_00632010, 2, (char *)D_0061A6D8, 0xC);
    int v = func_00264D60();
    *buf = (short)v;
    if (v < 0) {
        KEEP_LIVE(v + 0xFFFF);
    }
    KEEP_LIVE(local_pad);
    return buf;
}

__asm__(".skip 4");

void func_001F16F8(int *self)
{
    register int   final_v REG("$2");
    int *s1 = (int *)self[0x15C / 4];
    short *s0 = (short *)s1[0x800 / 4];
    float scale = 256.0f;
    int v0;
    int v0_b;
    float a1, a2;
    int s_val;

    v0 = func_00105278();
    func_00105F20(v0, s1 + (0x20 / 4));

    s_val = (int)(short)s0[0];
    a1 = func_0010E950(s_val);
    func_00104FC0((int)(short)(int)(a1 * scale));

    s_val = ((int)(short)s0[0]) << 1;
    s_val = (s_val << 16) >> 16;
    a2 = func_0010E950(s_val);
    func_00104F48((int)(short)(int)(a2 * scale));

    v0_b = func_00105278();
    func_00105F20(s1[0xC / 4], (int *)v0_b);

    final_v = (unsigned short)s0[0];
    final_v += 0x80;
    s0[0] = (short)final_v;
}

__asm__(".skip 4");

short *func_001F17B0(int *self)
{
    register int s3 REG("$19");
    int  pad[8];
    int *p = (int *)self[0x15C / 4];
    int *q = (int *)p[0x820 / 4];
    int  count = *((signed char *)q + 0x2E);
    short *buf = func_0013A0F8(D_00632010, count * 2, (char *)D_0061A6D8, 0x23);
    if (count > 0) {
        short *b = buf;
        int i = count;
        do {
            *b = (short)func_00264D60();
            i--;
            b++;
        } while (i != 0);
    }
    KEEP_LIVE(pad);
    KEEP_LIVE(s3);
    return buf;
}

__asm__(".skip 4");
