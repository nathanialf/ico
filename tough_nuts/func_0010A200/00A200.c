#include "matching.h"
#include "regpin.h"

extern void func_001080F8(void *out, int flag1, void *out2, void *src, int flag2);
extern void GetYDistanceFromPlane(void *out, void *src);

void func_0010A200(int *self, int idx)
{
    char buf[0x50];
    register int *v1 REG("$3");
    int *p810;
    signed char b;
    v1 = (int *)self[0x57];
    p810 = (int *)v1[0x204];
    b = ((signed char *)p810)[idx];
    func_001080F8(buf, 0, &buf[0x10], (char *)v1 + 0x180, 1);
    v1 = (int *)self[0x57];
    GetYDistanceFromPlane(buf, (char *)v1[3] + b * 0x40 + 0x30);
}
