#include "matching.h"
#include "regpin.h"

extern int D_006A6DB0[];
extern unsigned char D_002811C0[1024];
extern unsigned int D_00632194;
extern void func_002641D8(void *dst, int val, int n);
extern void func_0013CE48(void);
extern void func_0013CF08(int a, int b);
extern void func_0013CF38(int *p);
extern void func_0013CF70(int *p);

void func_0013B878(void)
{
    int i;
    char *p;
    func_002641D8(D_006A6DB0, 0, 0x180);
    func_0013CE48();
    func_0013CF08(0, D_00632194);
    i = 1;
    {
        register char *b REG("$3") = (char *)D_002811C0;
        KEEP_LIVE(b);
        p = b + 0x1B8;
    }
    do
    {
        func_0013CF70((int *)p);
        func_0013CF38((int *)(p - 0x14));
        p += 0x200;
    } while (--i >= 0);
}
