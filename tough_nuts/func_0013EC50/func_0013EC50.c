/* isys/gobj.c — __FILE__ anchor at .rodata 0x00557a10 */

/* Inlined data (Phase 3e) — migrated from gobj_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
unsigned char D_00281A70[32] = { 0 };
unsigned char D_00281A90[32] = { 0 };
unsigned int D_00632008 = 0x00000000;
unsigned int D_0063200C = 0x00000000;
unsigned char D_006321C0[8] = { 0 };
unsigned int D_006321C8 = 0x00000030;
unsigned int D_006321D0 = 0x00000000;

#include "include_asm.h"
#include "regpin.h"

const char D_00557A10[16] = "isys/gobj.c";

/* String rodata migrated from gobj_data.c */
const char D_00557A20[16] = "isys:null GObj\n";
const char D_00557A30[40] = "isys:not enough memory for GObj\n";
const char D_00557A58[16] = "isys:null GObj\n";
const char D_00557A68[24] = "gobj dl added to tail\n";
const char D_00557A80[16] = "no_entry %p\n";
const char D_00557A90[16] = "add to head %p\n";
const char D_00557AA0[16] = "add to tail %p\n";
const char D_00557AB0[16] = "GObjLinkDL in\n";
const char D_00557AC0[16] = "GObjLinkDL out\n";

extern int D_006A93D0[];
extern int D_006321CC;

extern void func_002641D8(int *a0, int a1, int a2);
extern void func_0013DDF8(int a0);
extern int  func_0013DFF0(int a0, int a1, int a2);
extern int  func_0013E0C0(int a0, int a1, int a2);

void func_0013DD88(void)
{
    func_002641D8(D_006A93D0, 0, 0x110);
}

INCLUDE_ASM_NOP_PAD(func_0013DD9C);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013DDA0);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013DDF8);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013DEA0);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013DFF0);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013E0C0);

void func_0013E190(int a0, int a1, int a2)
{
    int s1 = a1 & 0xFF;
    int new_var;
    new_var = a2;
    func_0013DDF8(a0);
    return func_0013DFF0(a0, s1, new_var);
}

void func_0013E1D8(int a0, int a1, int a2)
{
    int new_var;
    int s1 = a1 & 0xFF;
    func_0013DDF8(a0);
    new_var = s1;
    return func_0013E0C0(a0, new_var, a2);
}

INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013E220);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013E350);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013E488);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013E4D0);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013E548);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013E648);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013E728);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013E7F8);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013E868);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013E8D8);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013E9E0);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013EAE8);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013EB50);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013EBE0);
struct GObj { int unk0; int unk4; char pad[0x16C]; };
extern struct GObj *D_00633CA0;
extern unsigned int D_00633CA4;

struct GObj *func_0013EC50(int key)
{
    register unsigned int n REG("$8") = D_00633CA4;
    register struct GObj *base REG("$7") = D_00633CA0;
    register unsigned int i REG("$6");
    register int stride REG("$2");
    if (n == 0) goto ret0;
    i = 0;
    do {
        struct GObj *e;
        stride = 0x174;
        e = (struct GObj *)((char *)base + i * stride);
        if (e->unk0 != 0 && e->unk4 == key) return e;
        i++;
    } while (i < n);
ret0:
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013ECA8);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013ECF8);

void func_0013ED40(int bit, int set)
{
    if (set != 0) goto set_path;
    D_006321CC &= ~(1 << bit);
    return;
set_path:
    D_006321CC |= (1 << bit);
}

INCLUDE_ASM_NOP_PAD(func_0013ED74);
