/* src/switch.c — __FILE__ anchor at .rodata 0x00618630 */

unsigned int D_0028A550[20] = { 0x00000000, 0x00000010, 0x00000020, 0x00000080, 0x00000178, 0x0017CFA0, 0x00000000, 0x00000000, 0x0000018C, 0x00000000, 0x00000000, 0x00000000, 0x00000179, 0x0017CFA0, 0x00000000, 0x00000000, 0x0000018C, 0x00000000, 0x00000000, 0x00000000 };

/* Inlined data (Phase 3e) — migrated from switch_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
unsigned int D_0028A640[84] = { 0x00000635, 0x00000000, 0x00000000, 0x00000000, 0xC2C80000, 0xC3480000, 0x00000000, 0x00000000, 0xC4B04000, 0x447A0000, 0x00000000, 0x00000000, 0x00060630, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC3480000, 0x42C80000, 0x00000000, 0x4430C000, 0x44FA0000, 0x440E8000, 0x44806000, 0x00060632, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC3480000, 0x42C80000, 0x00000000, 0x4430C000, 0x44FA0000, 0x440E8000, 0x44806000, 0x00060386, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC3480000, 0x42C80000, 0x00000000, 0xC4B2E000, 0x42D20000, 0xC3EB0000, 0xC3818000, 0x00080326, 0x00000000, 0x00000000, 0x00000000, 0xC2C80000, 0xC3480000, 0x00000000, 0x00000000, 0xC3AF0000, 0xC38E8000, 0xC3E10000, 0xC38C0000, 0x00080327, 0x00000000, 0x00000000, 0x00000000, 0xC2C80000, 0xC3480000, 0x00000000, 0x00000000, 0xC3AF0000, 0xC38E8000, 0xC3E10000, 0xC38C0000, 0x0007066B, 0x00000000, 0x00000000, 0x00000000, 0xC2C80000, 0xC3480000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

/* Inlined data (Phase 3e) — migrated from switch_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
float D_0028A790[16] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

/* Inlined data (Phase 3e) — migrated from switch_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
unsigned int D_0055A010[4] = { 0x00000001, 0x00000002, 0x00000004, 0xFFFFFFFF };

/* Inlined data (Phase 3e) — migrated from switch_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
unsigned int D_0055A020[4] = { 0x00000001, 0x00000002, 0x00000004, 0x00000011 };

/* Inlined data (Phase 3e) — migrated from switch_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
const char D_00618630[16] = "src/switch.c";

/* Inlined data (Phase 3e) — migrated from switch_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
unsigned int D_006188E0[4] = { 0x000000FF, 0x000000FF, 0x000000FF, 0x00000080 };

/* Inlined data (Phase 3e) — migrated from switch_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
unsigned int D_006188F0[4] = { 0x000000FF, 0x00000000, 0x00000000, 0x00000080 };

/* Inlined data (Phase 3e) — migrated from switch_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
unsigned int D_00632CD0 = 0x00000000;

/* Inlined data (Phase 3e) — migrated from switch_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
unsigned int D_00632CD4 = 0x00000000;

#include "include_asm.h"
#include "regpin.h"
#include "matching.h"
#include "ico/types.h"

extern void func_001BC0A8(void);

int func_001C0690(char *self_) {
    GObj *self = (GObj *)self_;
    Sub15C *sub = self->p_15C;
    Obj800 *p = sub->p_800;
    return p->f_58;
}

extern void func_001BC9B0(void);
extern void func_001BC9B8(void);

int func_001C06A0(char *self_, int a1)
{
    GObj *self = (GObj *)self_;
    register Sub15C *sub REG("$2") = self->p_15C;
    Obj800 *s0 = sub->p_800;
    register int f58 REG("$3") = s0->f_58;
    if (f58 == 0 || s0->f_110 == 0) {
        if (a1 >= 0) {
            func_001BC9B0();
        } else {
            func_001BC9B8();
        }
        s0->f_114 = 0;
    }
    {
        register int r REG("$2") = 1;
        s0->f_110 = r;
        return r;
    }
}
extern void func_001D12D8(int *self);
extern void func_001D12C0(int *self, int v);
extern void func_001D12A8(int *self, int v);
extern void func_001BC9C0(int *self);

void func_001C0708(int *self)
{
    GObj *g = (GObj *)self;
    Sub15C *sub = g->p_15C;
    Obj800 *inner = sub->p_800;
    if (inner->f_58 == 0 || inner->f_110 != 0) {
        func_001D12D8(self);
        func_001D12C0(self, 1);
        func_001D12A8(self, 0x16);
        if (inner->f_140 != 0) {
            func_001BC9C0(self);
            inner->f_140 = 0;
        }
    }
    inner->f_110 = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C0790);

int func_001C0838(void) { return 1; }
int func_001C0840(void) { return 1; }
int func_001C0848(void) { return 0; }
void func_001C0850(void) {}
void func_001C0858(void) {}

void func_001C0860(char *self_, int val) {
    GObj *self = (GObj *)self_;
    Sub15C *sub = self->p_15C;
    Obj800 *p = sub->p_800;
    p->f_1C = val;
}

void func_001C0870(int *self, int x)
{
    GObj *g = (GObj *)self;
    register Sub15C *t REG("$2");
    Obj800 *q;
    register int v REG("$3");
    t = g->p_15C;
    q = t->p_800;
    v = q->f_4;
    if (v != x) {
        func_001BC0A8();
    }
    q->f_4 = x;
}

INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C08B8);

int func_001C09B0(char *self_) {
    GObj *self = (GObj *)self_;
    Sub15C *sub = self->p_15C;
    Obj800 *p = sub->p_800;
    return p->f_4 == 0;
}

INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C09C4);
extern int D_00632010;
extern int func_0013A0F8(int handle, int size, const char *file, int line);
extern unsigned char D_004BEFD0[];
extern unsigned int D_0028CA88[];
extern int func_0019F310(int x, void *y);
typedef struct { long long w[4]; } __attribute__((packed)) SwitchBuf20_09C8;
int *func_001C09C8(char *self, void *arg1)
{
    int *buf = (int *)func_0013A0F8(D_00632010, 0x20, D_00618630, 0x8D);
    int *entry;
    *(SwitchBuf20_09C8 *)buf = *(SwitchBuf20_09C8 *)D_004BEFD0;
    if (((int *)arg1)[0x30 / 4] != 0) {
        buf[0x14 / 4] = 1;
    } else {
        buf[0x14 / 4] = 0;
    }
    entry = (int *)((char *)D_0028CA88 + (*(int **)(self + 0x15C))[0x814 / 4] * 0x28);
    buf[0xC / 4] = func_0019F310(entry[0], arg1);
    KEEP_LIVE_MEM(buf);
    {
        register void *a1 REG("$5") = arg1;
        register int *t1 REG("$3");
        register int idx2 REG("$2");
        KEEP_LIVE(a1);
        t1 = *(int **)(self + 0x15C);
        idx2 = t1[0x814 / 4];
        entry = (int *)((char *)D_0028CA88 + idx2 * 0x28);
        buf[0x10 / 4] = func_0019F310(entry[1], a1);
    }
    return buf;
}

/* Override ee-gcc's default .align 3 (8-byte) function alignment so the
 * matched body lands at its expected 4-aligned VMA offset 0x114 (the
 * VMA 0x1C0AD8 is 4-aligned but not 8-aligned within this .o). */
__asm__(".align 2");

short func_001C0AD8(char *self) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    return *(short *)(p + 0x2);
}

INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C0AE8);

int func_001C0BE0(char *self) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    return *(int *)(p + 0x4) == 0;
}

INCLUDE_ASM("asm/nonmatchings/src/switch", func_001C0BF4);
int func_001C0BF8(char *self)
{
    register int accum REG("$4");
    short *p = *(short **)(*(char **)(self + 0x15C) + 0x800);
    if (__builtin_abs((int)p[1]) < 0xBB9) {
        accum = 0;
        MATERIALIZE(accum);
        if (__builtin_abs((int)p[0]) < 0xBB9) goto done;
    }
    accum = 1;
done:
    MATERIALIZE(accum);
    return accum;
}
TRAILING_PAD_NOP();
extern int D_00632010;
extern int func_0013A0F8(int handle, int size, const char *file, int line);
extern unsigned char D_004BEFD0[];
extern unsigned int D_0028CA88[];
extern int func_0019F310(int x, void *y);
typedef struct { long long w[4]; } __attribute__((packed)) SwitchBuf20;
int *func_001C0C40(char *self, void *arg1)
{
    int *buf = (int *)func_0013A0F8(D_00632010, 0x20, D_00618630, 0x12C);
    int *entry;
    *(SwitchBuf20 *)buf = *(SwitchBuf20 *)D_004BEFD0;
    if (((int *)arg1)[0x30 / 4] != 0) {
        buf[0x14 / 4] = 1;
    } else {
        buf[0x14 / 4] = 0;
    }
    entry = (int *)((char *)D_0028CA88 + (*(int **)(self + 0x15C))[0x814 / 4] * 0x28);
    buf[0xC / 4] = func_0019F310(entry[0], arg1);
    KEEP_LIVE_MEM(buf);
    {
        register void *a1 REG("$5") = arg1;
        register int *t1 REG("$3");
        register int idx2 REG("$2");
        KEEP_LIVE(a1);
        t1 = *(int **)(self + 0x15C);
        idx2 = t1[0x814 / 4];
        entry = (int *)((char *)D_0028CA88 + idx2 * 0x28);
        buf[0x10 / 4] = func_0019F310(entry[1], a1);
    }
    return buf;
}

/* ASCII debug strings — re-derived from EE rodata bytes. */
/* ASCII preview: "<ESC>[33mInitialize candle geometries.<ESC>[m<LF>" */
const char D_00618868[40] = "\033[33mInitialize candle geometries.\033[m\n";
