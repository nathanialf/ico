/* ios/inflate.c — __FILE__ anchor at .rodata 0x00556B00 */

const char D_00556B00[16] = "ios/inflate.c";
const char D_00556B10[32] = " incomplete literal tree\n";
const char D_00556B30[32] = " incomplete distance tree\n";
const char D_00556B50[24] = "read func not entry\n";
const char D_00556B68[48] = "iosSifAllocIopHeapDebug: %s %d not alloc\n";
const char D_00556B98[24] = "SgSndn2RemoteInit()\n";
const char D_00556BB0[32] = "allocate IOP heap memory - \n";
const char D_00556BD0[24] = "iosInitialize()\n";
const char D_00556BE8[16] = "stat mot";
const char D_00556BF8[16] = "demo mot";

/* .sdata — five 4-byte zero slots. The middle two (0x..2C, 0x..34) are
 * 4-aligned VMAs but extent == typed size == 4, so ee-gcc's forced
 * .align 3 lands them on their own VMA without shifting siblings. */
unsigned char D_00632028[4] = { 0 };
unsigned int  D_0063202C    = 0x00000000;
unsigned char D_00632030[4] = { 0 };
unsigned int  D_00632034    = 0x00000000;
unsigned char D_00632038[4] = { 0 };

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_001336C0);
INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_00133E88);
INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_001345D0);
INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_001348F0);
INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_00134B50);
extern void func_00136088(void *a0);

void func_00135468(void *a0)
{
    int *w = (int *)((char *) a0 + 0x18000);
    w[0x78 / 4] = -1;
    w[0x48 / 4] = 0;
    *(long long *)((char *) w + 0x68) = 0;
    *(long long *)((char *) w + 0x70) = 0;
    w[0x50 / 4] = 0;
    w[0x4C / 4] = 0;
    w[0x54 / 4] = 0;
    w[0x58 / 4] = 0;
    w[0x7C / 4] = 0;
    w[0x84 / 4] = 0;
    w[0x80 / 4] = 0;
    w[0x88 / 4] = 0;
    func_00136088((char *) a0 + 0x18098);
}
INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_001354B8);
INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_00135580);
extern int func_0013A0F8(int a0, int a1, const char *fmt, int line);
extern void func_00135468(void *p);
extern void func_001A6E28();
extern int D_0063203C;
extern int D_00632048;

int func_00135A48(int a0, int a1)
{
    int g = *(int *) D_00632028;
    int *s1;
    D_0063203C = g;
    D_00632048 = 0;
    s1 = (int *) func_0013A0F8(g, 0x180A8, D_00556B00, 0x2E3);
    func_00135468(s1);
    s1[0] = a1;
    if (a0 == 0)
    {
        func_001A6E28(D_00556B50);
    }
    else
    {
        s1[0x4 / 4] = a0;
    }
    return (int) s1;
}
INCLUDE_ASM("asm/nonmatchings/ios/inflate", func_00135AD8);
