/* src/Basic.c — __FILE__ anchor at .rodata 0x0061a8a8
 *
 * TU range: [0x001F6CB0, 0x001F6E28)  (next TU: src/BgAnimation.c at 0x001F6E28)
 *
 * The 4-byte `nop` at 0x001F6E24 (between func_001F6E00 and the next TU)
 * is alignment padding — not a real function. Linker --gap-fill=0x00
 * supplies the 4 zero bytes (nop = 0x00000000) automatically.
 */

#include "matching.h"

extern int   D_00633780;
extern int   D_00633784;
extern int   D_00632014;
extern int   D_00632024;
extern int   D_00633788[];
extern char  D_0061A890[];
extern char  D_0061A8A8[];
extern void  func_001A6E28(char *p);
extern void  func_001AD768(char *buf, int sz);
extern void  func_00263FF0(char *buf, int sz, int *list);
extern void  func_00139598(void *p);
extern int   func_0013A0F8(int a0, int a1, char *file, int line);
extern void  func_00139D78(int a0, int a1, char *a2, int a3);

int func_001F6CB0(int size)
{
    int rv = 0;
    if (D_00633780 == -1) {
        func_001A6E28(D_0061A890);
        func_001AD768(D_0061A8A8, 0x174);
        func_00263FF0(D_0061A8A8, 0x174, D_00633788);
    }
    if (D_00633780 == 0) {
        D_00633784 = D_00633784 + 0x30 + size;
        rv = func_0013A0F8(D_00632014, size, D_0061A8A8, 0x17B);
    } else if (D_00633780 == 1) {
        rv = func_0013A0F8(D_00632024, size, D_0061A8A8, 0x17E);
    }
    return rv;
}

void func_001F6D90(void *p)
{
    if (p != 0) {
        func_00139598(p);
        DEFEAT_TCO();
    }
}

void func_001F6DB0(void) {}

int func_001F6DB8(int a0)
{
    int saved = D_00633780;
    int rv;
    D_00633780 = 1;
    rv = func_0013A0F8(D_00632024, a0, D_0061A8A8, 0x17E);
    D_00633780 = saved;
    return rv;
}

void func_001F6E00(int a0, int a1)
{
    func_00139D78(a0, a1, D_0061A8A8, 0x1A8);
    DEFEAT_TCO();
}
