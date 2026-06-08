#include "common.h"

extern void gif_SpriteOrg(int a0, int a1);
extern int D_0062B708;

void SetLodLevel(void) {
    gif_SpriteOrg(0, D_0062B708);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lodManager", func_001D16F0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lodManager", func_001D1790);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lodManager", func_001D1948);

extern int func_001D1948(int *t0, int *t1, int *p1, int *p2);
extern void mc_setBaseOffset(int *out, int *src);
extern void func_001D15C0(int *a, int *b, int x, int y);

void func_001D1D58(int *p1, int *p2, int a2, int a3)
{
    int t0[4];
    int t1[4];
    int t2[4];
    int t3[4];
    if (func_001D1948(t0, t1, p1, p2) < 0) return;
    mc_setBaseOffset(t2, t0);
    mc_setBaseOffset(t3, t1);
    func_001D15C0(t2, t3, a2, a3);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lodManager", func_001D1DF0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lodManager", func_001D1ED8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lodManager", func_001D1F68);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lodManager", func_001D2060);

extern int D_0062C20C;
extern int D_0062C210;

void func_001D2130(void) {
    D_0062C20C = 0;
    D_0062C210 = 0;
}

extern int D_0062C20C, D_0062C210;

void func_001D2140(int a0, int a1) {
    if (a1)
        D_0062C210 += a0;
    else
        D_0062C20C += a0;
}

int func_001D2168(int a0) {
    return a0 ? D_0062C210 : D_0062C20C;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/lodManager", func_001D2180);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_004C0A88;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00611A10;  /* stride 0x4 */

/* end struct shapes */
