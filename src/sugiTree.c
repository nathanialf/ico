/* src/sugiTree.c — __FILE__ anchor at .rodata 0x0061A6D8
 *
 * TU range: [0x001F16A0, 0x001F1838)  (next TU: cod/0F1838 at 0x001F1838)
 *
 * The 4-byte `nop` between each function (at 0xF16F4, 0xF17AC, 0xF1834) is
 * 8-byte function alignment — supplied by `__asm__(".skip 4")` at file
 * scope. D_00632010 is gp_rel; verified -0x68E0 from _gp (in range).
 */

/* Inlined data (Phase 3e) — migrated from sugiTree_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
unsigned int D_00633710 = 0x00000000;

/* Inlined data (Phase 3e) — migrated from sugiTree_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* C-referenced data (extern kept, def supplies bytes) */
int D_00633724 = 0x00000000;
int D_00633728 = 0x00000000;

#include "include_asm.h"
#include "ico/types.h"
#include "regpin.h"
#include "matching.h"

const char D_0061A6D8[16] = "src/sugiTree.c";

extern int    D_00632010;
extern int    D_00633720;
extern int    D_00633724;
extern int    D_00633728;
extern void   func_00139598(int a0);
extern void   func_001F08D8(void);
extern void   func_001D12D8(int a0);
extern void   func_001D12A8(int a0, int a1);
extern short *func_0013A0F8(int handle, int size, char *file, int line);
extern int    func_00264D60(void);
extern int    func_00105278(void);
extern int    func_00105F20(int a0, int *a1);
extern float  func_0010E950(int x);
extern void   func_00104FC0(int x);
extern void   func_00104F48(int x);

void func_001F1168(void)
{
    if (D_00633720 != 0) {
        func_00139598(D_00633720);
        func_00139598(D_00633728);
        D_00633728 = 0;
        D_00633720 = 0;
        D_00633724 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/sugiTree", func_001F11A0);

int func_001F1240(void) {
    func_001F08D8();
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/sugiTree", func_001F1260);
INCLUDE_ASM("asm/nonmatchings/src/sugiTree", func_001F1330);
INCLUDE_ASM("asm/nonmatchings/src/sugiTree", func_001F1508);

short *func_001F16A0(void)
{
    int  local_pad[4];
    short *buf = func_0013A0F8(D_00632010, 2, (char *)D_0061A6D8, 0xC);
    int v = func_00264D60();
    *buf = (short)v;
    if (v < 0) {
        KEEP_LIVE(v + 0xFFFF);
    }
    KEEP_LIVE(local_pad);
    return buf;
}

__asm__(".skip 4");

void func_001F16F8(int *self)
{
    register int   final_v REG("$2");
    int *s1 = (int *)((GObj *)(self))->p_15C;
    short *s0 = (short *)s1[0x800 / 4];
    float scale = 256.0f;
    int v0;
    int v0_b;
    float a1, a2;
    int s_val;

    v0 = func_00105278();
    func_00105F20(v0, s1 + (0x20 / 4));

    s_val = (int)(short)s0[0];
    a1 = func_0010E950(s_val);
    func_00104FC0((int)(short)(int)(a1 * scale));

    s_val = ((int)(short)s0[0]) << 1;
    s_val = (s_val << 16) >> 16;
    a2 = func_0010E950(s_val);
    func_00104F48((int)(short)(int)(a2 * scale));

    v0_b = func_00105278();
    func_00105F20(s1[0xC / 4], (int *)v0_b);

    final_v = (unsigned short)s0[0];
    final_v += 0x80;
    s0[0] = (short)final_v;
}

__asm__(".skip 4");

short *func_001F17B0(int *self)
{
    register int s3 REG("$19");
    int  pad[8];
    int *p = (int *)((GObj *)(self))->p_15C;
    int *q = (int *)p[0x820 / 4];
    int  count = *((signed char *)q + 0x2E);
    short *buf = func_0013A0F8(D_00632010, count * 2, (char *)D_0061A6D8, 0x23);
    if (count > 0) {
        short *b = buf;
        int i = count;
        do {
            *b = (short)func_00264D60();
            i--;
            b++;
        } while (i != 0);
    }
    KEEP_LIVE(pad);
    KEEP_LIVE(s3);
    return buf;
}

__asm__(".skip 4");

void func_001F1838(int a0)
{
    func_001D12D8(a0);
    func_001D12A8(a0, 0x41);
}
