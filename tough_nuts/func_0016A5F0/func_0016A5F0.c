/* Trimmed permuter seed for func_0016A5F0 (from src/commonact.c).
 * The full commonact TU snapshot is ~1.7 MB (huge EUC-JP data), which
 * trips check_no_rom's size guard, so only the target function + its
 * minimal externs are kept here. Best real_count=3 (barrier + base REG).
 */
#include "matching.h"
#include "regpin.h"

extern int func_00109F10(int *obj, int code);
extern void func_002438B8(int *self, int v, char *p);

void func_0016A5F0(int *a0, int *a1)
{
    int idx = func_00109F10(a1, 0x23);
    int c = *(int *)((char *)a1 + 0xC);
    *(int *)a0 = 0;
    if (c == 4) {
        *(float *)((char *)a0 + 0x4) = -1.0f;
    } else {
        *(float *)((char *)a0 + 0x4) = 1.0f;
    }
    *(int *)((char *)a0 + 0x8) = 0;
    *(int *)((char *)a0 + 0xC) = 0;
    MEM_BARRIER();
    {
        register int base REG("$2") =
            *(int *)(*(int *)((char *)a1 + 0x15C) + 0xC);
        func_002438B8(a0, base + (idx << 6), (char *)a0);
    }
}
