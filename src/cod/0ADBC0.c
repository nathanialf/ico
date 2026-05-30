#include "regpin.h"

extern char D_004B3D10[];
extern char D_004B3B68[];
extern void func_002641D8(char *p, int a, int len);
extern void func_001A1008(void);

void func_001ADBC0(void)
{
    register char *p = D_004B3D10;
    register unsigned int v = 0xFFFF;
    register int i = 0xB5;
    do {
        *(short *)(p + 2) = 0;
        *(unsigned short *)(p + 4) = v;
        p += 0x40;
        i--;
    } while (i >= 0);
    func_002641D8(D_004B3B68, 0, 0x1A0);
    func_001A1008();
}
