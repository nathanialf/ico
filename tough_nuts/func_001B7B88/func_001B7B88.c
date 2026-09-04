#include "matching.h"

extern unsigned char D_002A4C48[];
extern unsigned char D_002A31B8[];
extern const char D_00633190[];
extern char D_00617298[];
extern char D_006172E0[];
extern char D_006172F8[];
extern char D_00617308[];
extern int func_0013EAE8(int x);
extern void func_001A6E28();
extern void func_001AD768(const char *file, int line);
extern int __assert(const char *file, int line, const void *p);

void func_001B7B88(int a0)
{
    unsigned char *entry = D_002A4C48 + a0 * 0x4C;
    int pid = entry[0x46];
    register unsigned char *pbase REG("$4") = D_002A31B8;
    register int off REG("$5") = pid * 0x64;
    unsigned char *parent = pbase + off;
    int hw;
    int ra0, rhw;
    if (*(int *)(parent + 0x44) == 0) return;
    hw = *(unsigned short *)(entry + 0x44);
    if (hw == 0) return;
    if (pid == 4) return;
    ra0 = func_0013EAE8(a0);
    rhw = func_0013EAE8(hw);
    if (rhw != 0) {
        if (rhw == ra0) {
            func_001A6E28(D_00617298, parent);
            func_001AD768(D_006172E0, 0x1E7);
            __assert(D_006172E0, 0x1E7, D_00633190);
        }
        func_001A6E28(D_006172F8, parent);
        *(int *)(*(int *)(ra0 + 0x15C)) = rhw;
        *(int *)(*(int *)(ra0 + 0x15C) + 4) = 0;
        return;
    }
    func_001A6E28(D_00617308, parent);
    func_001AD768(D_006172E0, 0x1F0);
    __assert(D_006172E0, 0x1F0, D_00633190);
}
