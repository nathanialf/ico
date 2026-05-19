/* src/Basic.c — __FILE__ anchor at .rodata 0x0061a8a8
 *
 * TU range: [0x001F6CB0, 0x001F6E28)  (next TU: src/BgAnimation.c at 0x001F6E28)
 *
 * The 4-byte `nop` at 0x001F6E24 (between func_001F6E00 and the next TU)
 * is alignment padding — not a real function. Linker --gap-fill=0x00
 * supplies the 4 zero bytes (nop = 0x00000000) automatically.
 */

#include "matching.h"
#include "regpin.h"
#include "include_asm.h"

__attribute__((section(".rodata.0x0061A890"))) char D_0061A890[24] = "set partition first!\n";
__attribute__((section(".rodata.0x0061A8A8"))) char D_0061A8A8[24] = "src/Basic.c";

extern int   D_00633780;
extern int   D_00633784;
extern int   D_00632014;
extern int   D_00632024;
extern int   D_00633788[];
extern void  func_00139598(void *p);
extern void  func_001A6E28(char *p);
extern void  func_001AD768(char *buf, int sz);
extern void  func_00263FF0(char *buf, int sz, int *list);
extern int   func_0013A0F8(int a0, int a1, char *file, int line);
extern void  func_00139D78(int a0, int a1, char *a2, int a3);

int func_001F6CB0(int size)
{
    int rv = 0;
    if (D_00633780 == -1) {
        func_001A6E28(D_0061A890);
        DEFEAT_TCO();
        func_001AD768(D_0061A8A8, 0x174);
        DEFEAT_TCO();
        {
            register char *buf REG("$4") = D_0061A8A8;
            register int *list REG("$6") = D_00633788;
            DEFEAT_TCO();
            func_00263FF0(buf, 0x174, list);
        }
        DEFEAT_TCO();
    }
    switch (D_00633780) {
    case 0: {
        int ret;
        D_00633784 += 0x30 + size;
        ret = func_0013A0F8(D_00632014, size, D_0061A8A8, 0x17B);
        DEFEAT_TCO();
        rv = ret;
        break;
    }
    case 1:
        rv = func_0013A0F8(D_00632024, size, D_0061A8A8, 0x17E);
        break;
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
