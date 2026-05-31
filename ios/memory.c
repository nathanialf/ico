/* ios/memory.c — __FILE__ anchor at .rodata 0x005570E0 */

#include "matching.h"
#include "include_asm.h"

const char D_00556F50[32] = "mem:partition size too small\n";
const char D_00556F70[16] = "<PARTITION>____";
const char D_00556F80[16] = "<FREE AREA>____";
const char D_00556F90[40] = "mem:init partition 0x%08x - 0x%08x\n";
const char D_00556FB8[32] = "mem:null partition pointer\n";
const char D_00556FD8[32] = "mem:illegal partition pointer\n";
const char D_00556FF8[40] = "mem: memory lack %dqw > parent:%dqw\n";
const char D_00557020[32] = "mem:set partition 0x%08x\n";
const char D_00557040[32] = "mem:fail init partition\n";
const char D_00557060[16] = " free memory   ";
const char D_00557070[24] = "mem:not last partition\n";
const char D_00557088[16] = " del partition ";
const char D_00557098[72] = "MALLOC: REENTER FOR PARTITION \"%s\" SIZE %d\nBEFORE FILE %s LINE %d";
const char D_005570E0[16] = "ios/memory.c";
const char D_005570F0[48] = "IOSMALLOC():\nNULL PARTITION POINTER AT MALLOC\n";
const char D_00557120[32] = "mem:illegal free area pointer\n";
const char D_00557140[40] = "mem: prev block, %08x called at %s\n";
const char D_00557168[24] = "mem:prev magic %s\n";
const char D_00557180[40] = "mem:cur block, %08x called at %s\n";
const char D_005571A8[24] = "mem:cur magic %s\n";
const char D_005571C0[40] = "mem: next block, %08x called at %s\n";
const char D_005571E8[24] = "mem:next magic %s\n";
const char D_00557200[32] = "mem:called by %s of line %d\n";
const char D_00557220[16] = "<ALLOC>________";
const char D_00557230[16] = "cur: %8p %s\n";
const char D_00557240[16] = "next:%8p %s\n";
const char D_00557250[24] = "mem:no memory for %d\n";
const char D_00557268[64] = "MALLOC: NO EMEMORY FOR PARTITION \"%s\"\nSIZE %d BYTES (%1.1fM)\n";
const char D_005572A8[16] = "align%05d";
const char D_005572B8[32] = "IOSFILLFREE %s(%d) %p - %p\n";
const char D_005572D8[16] = "mem:free ";
const char D_005572E8[24] = "null memory pointer\n";
const char D_00557300[32] = "IOSFREE(): NULL MEMORY POINTER\n";
const char D_00557320[64] = "IOSFREE():\n\tPREV MAGIC: %s\n\t CUR MAGIC: %s\n\tNEXT MAGIC: %s\n";
const char D_00557360[16] = " free memory0  ";
const char D_00557370[32] = "IOSFREE(): MEMORY LINK MISS\n";
const char D_00557390[16] = " free memory1  ";
const char D_005573A0[16] = " free memory2  ";
const char D_005573B0[24] = "IOSFREE(): ALLOC NULL\n";
const char D_005573C8[16] = "IOSFREE(): ??\n";
const char D_005573D8[24] = "magic broken :%p\n";
const char D_005573F0[16] = "mem:addr:$%08x ";
const char D_00557400[16] = "FREEAREA ";
const char D_00557410[16] = "DELETED_MEMORY ";
const char D_00557420[40] = "!!! unrecognized memory block !!!\n";
const char D_00557448[16] = "siz:$%5x ";
const char D_00557458[24] = "<<< check leak2 >>> %p\n";
const char D_00557470[16] = "%p:ALLOC %s\n";
const char D_00557480[16] = "%p:FREEAREA\n";
const char D_00557490[24] = "%p:DELETED_MEMORY\n";
const char D_005574A8[40] = "%p:!!! unrecognized block!!!:%s\n";
const char D_005574D0[48] = "IOSREALLOC():\nNULL MEMORY POINTER AT MALLOC\n";
const char D_00557500[32] = "mem:realloc; not support yet\n";
const char D_00557520[32] = "mem:realloc; not enough memory\n";

/* .data — single u32, value 7. */
unsigned int D_00274EEC = 0x00000007;

/* .sdata — two 4-byte slots. */
unsigned char D_00631F50[4] = { 0 };
unsigned int  D_00631F54    = 0x00000000;

extern void func_00136280(int a0, int a1, int a2);
extern void func_00138E30(void);

int func_001383D8(int a0, int a1)
{
    func_00136280(a0, a1, 0x63FC);
    return 0;
}

extern unsigned int D_00274EEC_a[] __asm__("D_00274EEC");
extern unsigned char D_00280C60[];
extern unsigned char D_00281180[];
extern unsigned int D_00632110;
extern int func_00136678();
extern void func_001412B8(int);
typedef struct { long long x[8]; } __attribute__((packed)) Blk40_001383F8;
typedef struct { char pad[0x140]; int f140; int f144; int f148; Blk40_001383F8 f14C; } Elem_001383F8;

int func_001383F8(int *a0, int a1)
{
    func_00136678(a0, a1, 0x63FC);
    D_00274EEC_a[0] = ((Elem_001383F8 *) D_00280C60)[a0[0x8 / 4]].f140;
    func_001412B8(((Elem_001383F8 *) D_00280C60)[a0[0x8 / 4]].f144);
    {
        int i = a0[0x8 / 4];
        int v = ((Elem_001383F8 *) D_00280C60)[i].f148;
        *(Blk40_001383F8 *) D_00281180 =
            *(Blk40_001383F8 *) (D_00280C60 + 0x14C + i * 0x18C);
        D_00632110 = v;
    }
    return a0[0x10 / 4];
}
extern int func_00132630(int a0, void *handler, int *state, int a3, int a4, int a5, int a6, int a7);
extern void func_00137E48(int *a0);
extern void func_00133450(int a0);
extern int func_00138720(int a0, int *a1);
extern int D_00633C80;

INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00138510);
INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00138618);
extern void func_00132B90(int a0, void *buf, int n);
extern void func_0013D3F0(void);
extern int D_00633C80;

INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00138720);
INCLUDE_ASM("asm/nonmatchings/ios/memory", func_001387F0);
INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00138A10);
extern int func_00265024(int *a0, const char *a1);
extern void func_00265168(unsigned char *ptr, int value);
extern void func_001A6E28(const char *fmt, ...);

int func_00138BF0(int *a0, int a1)
{
    if (a0 == 0)
    {
        func_001A6E28(D_00556FB8);
        return 0;
    }
    if (func_00265024(a0, D_00556F70) != 0)
    {
        func_001A6E28(D_00556FD8);
        return 0;
    }
    func_00265168((unsigned char *)((char *) a0 + 0x10), a1);
}
INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00138C78);
INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00138E30);
INCLUDE_ASM("asm/nonmatchings/ios/memory", func_001392A8);
extern int func_001007A0(int a0);

void func_001394F0(int *a0, int a1, int a2)
{
    int *end = *(int **)((char *) a0 - 0x1C);
    func_001007A0(0);
    func_00139598(a0);
    func_001A6E28(D_005572B8, a1, a2, a0, end);
    {
        register int g = (unsigned int) a0 < (unsigned int) end;
        if (g)
        {
            do
            {
                *(unsigned int *) a0 = 0xFFFFFFFFu;
                a0++;
            } while ((unsigned int) a0 < (unsigned int) end);
        }
    }
    func_001007A0(0);
}
INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00139598);
INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00139A50);
INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00139C30);
INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00139D78);
INCLUDE_ASM("asm/nonmatchings/ios/memory", func_00139FE8);
INCLUDE_ASM("asm/nonmatchings/ios/memory", func_0013A0F8);

INCLUDE_ASM("asm/nonmatchings/ios/memory", func_0013A200);
