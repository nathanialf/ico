/* src/Basic.c — __FILE__ anchor at .rodata 0x0061a8a8
 *
 * TU range: [0x001F6CB0, 0x001F6E28)  (next TU: src/BgAnimation.c at 0x001F6E28)
 *
 * The 4-byte `nop` at 0x001F6E24 (between func_001F6E00 and the next TU)
 * is alignment padding — not a real function. Linker --gap-fill=0x00
 * supplies the 4 zero bytes (nop = 0x00000000) automatically.
 *
 * func_001F6CB0 reverted to INCLUDE_ASM: previous C body compiled to
 * 0xD8 vs original 0xE0 (8-byte deficit in if-else-if dispatch).
 * Parked seed at tough_nuts/func_001F6CB0/.
 */

#include "matching.h"
#include "include_asm.h"

extern int   D_00633780;
extern int   D_00632024;
extern char  D_0061A8A8[];
extern void  func_00139598(void *p);
extern int   func_0013A0F8(int a0, int a1, char *file, int line);
extern void  func_00139D78(int a0, int a1, char *a2, int a3);

INCLUDE_ASM("asm/nonmatchings/Basic", func_001F6CB0);

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
