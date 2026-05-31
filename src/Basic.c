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

const char D_0061A890[24] = "set partition first!\n";
const char D_0061A8A8[24] = "src/Basic.c";

extern int   D_00633780;
extern int   D_00633784;
extern int   D_00632014;
extern int   D_00632024;
extern int   D_00633788[];
extern int   func_00139598(void *p);
extern void  func_001A6E28(char *p);
extern void  func_001AD768(char *buf, int sz);
extern void  func_00263FF0(char *buf, int sz, int *list);
extern int   func_0013A0F8(int a0, int a1, char *file, int line);
extern void  func_00139D78(int a0, int a1, char *a2, int a3);

INCLUDE_ASM("asm/nonmatchings/src/Basic", func_001F6CB0);

int func_001F6D90(void *a0)
{
    if (a0 != 0)
    {
        return func_00139598(a0);
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

INCLUDE_ASM("asm/nonmatchings/src/Basic", func_001F6E00);
