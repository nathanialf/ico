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
struct GObj { int unk0; int unk4; int unk8; char pad[0x168]; };
extern struct GObj *D_00633CA0;
extern unsigned int D_00633CA4;
extern void func_001A6E28(const char *fmt);

INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013E8D8);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013E9E0);

INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013EAE8);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013EB50);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013EBE0);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013EC50);

INCLUDE_ASM("asm/nonmatchings/isys/gobj", func_0013ECA8);
struct GObj *func_0013ECF8(struct GObj *start)
{
    struct GObj *end = (struct GObj *)((char *)D_00633CA0 + (D_00633CA4 * 0x174 - 0x174));
    while (start != end) {
        start++;
        if (start->unk0 != 0) {
            return start;
        }
    }
    return 0;
}

void func_0013ED40(int bit, int set)
{
    if (set != 0) goto set_path;
    D_006321CC &= ~(1 << bit);
    return;
set_path:
    D_006321CC |= (1 << bit);
}

INCLUDE_ASM_NOP_PAD(func_0013ED74);


/* === BEGIN recovered struct shapes (tools/place_struct_shapes.py) === */
/* Field layouts mined from load/store access patterns; SPARSE
 * (only touched offsets, no padding). Unused typedefs — they add
 * no symbol and cannot affect codegen. Cast as ((S_<VMA> *)D_<VMA>).
 */

typedef struct {
    unsigned int     f_0;  /* 0x0  x18 */
} S_00281A70;  /* stride 0x4, 18 accesses */

typedef struct {
    unsigned int     f_0;  /* 0x0  x8 */
} S_006A93D0;  /* stride 0x4, 8 accesses */

typedef struct {
    unsigned int     f_0;  /* 0x0  x5 */
} S_00281A90;  /* stride 0x4, 5 accesses */

/* === END recovered struct shapes === */
