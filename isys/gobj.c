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
#include "matching.h"

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
void func_0013E7F8(int self, int other)
{
    int u, w;
    unsigned char t;
    func_0013DDF8(self);
    t = *(unsigned char *)(other + 0x18);
    *(int *)(self + 0x14) = other;
    *(unsigned char *)(self + 0x18) = t;
    u = *(int *)(other + 0x10);
    w = *(int *)(other + 0x1C);
    *(int *)(self + 0x10) = u;
    *(int *)(other + 0x10) = self;
    *(int *)(self + 0x1C) = w;
    if (*(int *)(self + 0x10) == 0) {
        *(int *)(D_00281A90 + *(unsigned char *)(self + 0x18) * 4) = self;
    }
}
void func_0013E868(int self, int other)
{
    unsigned char t;
    int u;
    func_0013DDF8(self);
    t = *(unsigned char *)(other + 0x18);
    *(unsigned char *)(self + 0x18) = t;
    u = *(int *)(other + 0x14);
    *(int *)(self + 0x10) = other;
    *(int *)(self + 0x14) = u;
    *(int *)(other + 0x14) = self;
    *(int *)(self + 0x1C) = *(int *)(other + 0x1C);
    if (*(int *)(self + 0x14) == 0) {
        *(int *)(D_00281A70 + *(unsigned char *)(self + 0x18) * 4) = self;
    }
}
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013E8D8);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013E9E0);

struct GObj { int unk0; int unk4; int unk8; char pad[0x168]; };
extern struct GObj *D_00633CA0;
extern unsigned int D_00633CA4;

struct GObj *func_0013EAE8(int key)
{
    register unsigned int n REG("$8") = D_00633CA4;
    register unsigned int i REG("$6");
    register struct GObj *base REG("$7");
    register int stride REG("$2");
    if (n == 0) goto ret0;
    i = 0;
    ANCHOR(i);
    base = D_00633CA0;
    do {
        struct GObj *e;
        register int f0 REG("$3");
        stride = 0x174;
        e = (struct GObj *)((char *)base + i * stride);
        f0 = e->unk0;
        stride = 1;
        if (f0 != 0 && e->unk4 == stride && e->unk8 == key) return e;
        i++;
    } while (i < n);
ret0:
    return 0;
}
struct GObj *func_0013EB50(int key_param)
{
    register int key REG("$5") = key_param;
    register struct GObj *p REG("$3");
    if (*(int *)D_006321C0 == 0) goto alt;
    {
        register struct GObj *base REG("$4") = D_00633CA0;
        register struct GObj *end REG("$4");
        register int one REG("$6") = 1;
        p = base - 1;
        end = (struct GObj *)((char *)base + (D_00633CA4 * 0x174 - 0x174));
        if (p == end) goto ret0;
        p++;
        NOP();
    loop:
        if (*(int *)((char *)p + 4) == one && *(int *)((char *)p + 0xC) == key) goto found;
        if (p != end) { p++; goto loop; }
    }
ret0:
    return 0;
found:
    return p;
alt:
    if ((unsigned int)(key - 1) < 0x43) {
        register int idx REG("$3") = key * 4;
        return (struct GObj *)*(int *)((char *)D_006A93D0 + idx);
    }
    goto ret0;
}
struct GObj *func_0013EBE0(struct GObj *obj)
{
    register struct GObj *p REG("$5");
    register int key REG("$3");
    if (*(int *)D_006321C0 == 0) goto alt;
    {
        register struct GObj *base REG("$4") = D_00633CA0;
        register struct GObj *end REG("$4");
        int one;
        p = obj;
        ANCHOR(p);
        end = (struct GObj *)((char *)base + (D_00633CA4 * 0x174 - 0x174));
        key = *(int *)((char *)obj + 0xC);
        if (obj == end) goto ret0;
        one = 1;
        ANCHOR(p);
        p++;
    loop:
        if (*(int *)((char *)p + 4) == one && *(int *)((char *)p + 0xC) == key) goto found;
        if (p != end) { p++; goto loop; }
    }
ret0:
    return 0;
found:
    return p;
alt:
    return *(struct GObj **)((char *)obj + 0x3C);
}
struct GObj *func_0013EC50(int key)
{
    register unsigned int n REG("$8") = D_00633CA4;
    register unsigned int i REG("$6");
    register struct GObj *base REG("$7");
    register int stride REG("$2");
    if (n == 0) goto ret0;
    i = 0;
    ANCHOR(i);
    base = D_00633CA0;
    do {
        struct GObj *e;
        register int f0 REG("$3");
        stride = 0x174;
        e = (struct GObj *)((char *)base + i * stride);
        f0 = e->unk0;
        if (f0 != 0 && e->unk4 == key) return e;
        i++;
    } while (i < n);
ret0:
    return 0;
}

struct GObj *func_0013ECA8(void)
{
    struct GObj *base = D_00633CA0;
    struct GObj *p = base - 1;
    struct GObj *end = (struct GObj *)((char *)base + (D_00633CA4 * 0x174 - 0x174));
    ANCHOR(p);
    if (p == end) goto ret0;
    p++;
    NOP();
loop:
    if (p->unk0 != 0) return p;
    if (p != end) { p++; goto loop; }
ret0:
    return 0;
}
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
