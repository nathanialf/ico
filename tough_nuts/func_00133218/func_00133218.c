#include "regpin.h"

extern void func_00264DF8(char *buf, const char *fmt, int arg);
extern void func_00265168(int a0, char *buf);
extern const char D_00631F70[];
extern unsigned char D_0062FC79[];

void func_00133218(int a0)
{
    char buf[256];
    register char *p REG("$16");
    unsigned char c;
    func_00264DF8(buf, D_00631F70, a0);
    p = buf;
    c = *p;
    do
    {
        int sc = (signed char) c;
        if (sc == 0x2F)
        {
            *p = 0x5C;
        }
        else
        {
            int t = sc - 0x20;
            if ((D_0062FC79[sc] & 2) == 0)
            {
                t = sc;
            }
            *p = t;
        }
        p++;
        c = *p;
    } while (c != 0);
    func_00265168(a0, buf);
}
