#include "regpin.h"

extern int   func_00105278(void);
extern int   func_00105F20(int a0, int *a1);
extern float func_0010E950(int x);
extern void  func_00104FC0(int x);
extern void  func_00104F48(int x);

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

__asm__ (".skip 4");
