#include "matching.h"

#include "regpin.h"

extern int D_00631B7C;
extern char D_00553E00[];
extern char D_00553E28[];
extern char D_00660A40[];
extern void func_001A6E28(char *p);
extern void func_0010D520(void);
extern void func_0010D830(char *p, char *q);

void func_0010D4A8(void)
{
    register int idx REG("$3") = D_00631B7C;
    if (idx < 0) {
        func_001A6E28(D_00553E00);
        func_0010D520();
        idx = D_00631B7C;
    }
    idx++;
    D_00631B7C = idx;
    if (idx >= 0x40) {
        func_001A6E28(D_00553E28);
        idx = 0x3F;
        D_00631B7C = idx;
    }
    {
        int i = D_00631B7C;
        int byte_off = i * 16;
        func_0010D830(D_00660A40 + byte_off, (char *)D_00660A40 - 0x10 + byte_off);
    }
}

TRAILING_PAD_NOP();
