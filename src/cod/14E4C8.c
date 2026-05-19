#include "matching.h"
#include "regpin.h"

extern char D_00717C50[];
extern int func_0026F3A0(int, int);

int *func_0024E4C8(int a0_idx, int a1_idx)
{
    int a0_prod;
    register int *s0_ptr REG("$16");
    int v_lt;
    int *result;
    __asm__("mult1 %0, %1, %2" : "=r"(a0_prod) : "r"(a0_idx), "r"(0x70));
    a1_idx *= 0x1C;
    a1_idx += a0_prod;
    s0_ptr = *(int **)(D_00717C50 + a1_idx);
    func_0026F3A0((int)s0_ptr, (int)s0_ptr + 0x100);
    v_lt = (((int *)s0_ptr)[0x58 / 4] < ((int *)s0_ptr)[0xD8 / 4]);
    result = (int *)((char *)s0_ptr + (v_lt << 7));
    return result;
}
