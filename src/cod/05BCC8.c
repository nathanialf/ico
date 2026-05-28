#include "common.h"
#include "matching.h"

extern void func_0013FF88(int *a0, int a1, int *a2);

void func_0015BCC8(int *a0, int a1)
{
    int *e = *(int **)((char *)a0 + 0x164);
    if (a1 == 0xA8 || a1 == 0xAD) {
        if (*(int *)((char *)a0 + 0xC) == 1) {
            unsigned long v = *(unsigned long *)((char *)e + 0x470);
            unsigned long b = (v >> 61) & 1;
            if (b) {
                unsigned long c2 = (*(unsigned long *)((char *)e + 0x480) >> 61) & 1;
                if (c2) {
                    a1 = 0xA9;
                    goto end;
                }
            }
            MEM_BARRIER();
            b = (v >> 59) & 1;
            if (b) {
                unsigned long c3 = (*(unsigned long *)((char *)e + 0x480) >> 59) & 1;
                a1 = c3 ? 0xAA : a1;
            }
        }
    }
end:
    func_0013FF88(a0, a1, a0);
}
