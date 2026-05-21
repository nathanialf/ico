/* src/act_bird.c — __FILE__ anchor at .rodata 0x0055AFD8 */

const char D_0055AFD8[16] = "src/act_bird.c";

#include "include_asm.h"
#include "matching.h"
#include "regpin.h"

extern int D_00632010;

extern int  *func_0013A0F8(int handle, int size, char *file, int line);
extern void  func_002641D8(void *dst, int val, int n);
extern void  func_00105F00(int *out, int *src);
extern void  func_001E4798(int *self, int a, int b, int c, int d, int e);
extern float func_00118A68(void);
extern void  func_001D4B40(int *self, int mode);

int *func_00197240(int *a0, int *a1)
{
    int *obj;
    register int *p_v1 REG("$3");
    register int *p_v0 REG("$2");
    float f;
    register int one_val REG("$4");

    obj = func_0013A0F8(D_00632010, 0x40, (char *)D_0055AFD8, 0x3D2);
    func_002641D8(obj, 0, 0x40);
    func_00105F00(obj, a1);
    *((char *)obj + 0x10) = 0;

    func_001E4798(a0, 0x847, 0x875, -1, -1, 0x431);

    p_v1 = (int *)*(int * volatile *)((char *)a0 + 0x15C);
    one_val = 1;
    KEEP_LIVE(one_val);
    *(volatile int *)((char *)p_v1 + 0x544) = one_val;
    p_v0 = (int *)*(int * volatile *)((char *)a0 + 0x15C);
    *(volatile int *)((char *)p_v0 + 0x54C) = 0;
    p_v1 = (int *)*(int * volatile *)((char *)a0 + 0x15C);
    *(volatile int *)((char *)p_v1 + 0x548) = one_val;
    p_v0 = (int *)*(int * volatile *)((char *)a0 + 0x15C);
    *(volatile int *)((char *)p_v0 + 0x550) = 0;

    f = func_00118A68();

    p_v0 = (int *)*(int * volatile *)((char *)a0 + 0x15C);
    *(volatile float *)((char *)p_v0 + 0x4AC) = f * 100.0f;
    p_v1 = (int *)*(int * volatile *)((char *)a0 + 0x15C);
    *(volatile float *)((char *)p_v1 + 0x4B0) = *(volatile float *)((char *)p_v1 + 0x4AC);
    p_v0 = (int *)*(int * volatile *)((char *)a0 + 0x15C);
    *(volatile int *)((char *)p_v0 + 0x4C4) = 0;

    func_001D4B40(a0, 3);

    return obj;
}
