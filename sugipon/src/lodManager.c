#include "common.h"

extern void gif_SpriteOrg(int a0, int a1);
extern int D_0062B708;

void SetLodLevel(void) {
    gif_SpriteOrg(0, D_0062B708);
}

extern void gif_SpriteOrg_ll(int a0, long long a1) __asm__("gif_SpriteOrg");

void func_001D16F0(int *a0, int *a1, int *a2) {
    gif_SpriteOrg_ll(1, (long long)a2[0] | ((long long)a2[1] << 8) | ((long long)a2[2] << 16) | ((long long)a2[3] << 24));
    gif_SpriteOrg_ll(5, (long long)a0[0] | ((long long)a0[1] << 16) | ((long long)a0[2] << 32));
    gif_SpriteOrg_ll(5, (long long)a1[0] | ((long long)a1[1] << 16) | ((long long)a1[2] << 32));
}

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

extern void func_00118068();
extern void func_001D1790(int *a0, int *a1, int *a2, int *a3, int a4);

void func_001D1DF0(int *a0, int *a1, int *a2, int *a3, int a4) {
    int t0[4];
    int t1[4];
    int t2[4];
    int t3[4];
    int r;

    func_00118068();
    r = func_001D1948(t0, t1, a0, a2);
    if (r == -1) {
        return;
    }
    mc_setBaseOffset(t2, t0);
    mc_setBaseOffset(t3, t1);
    if (r != 0) {
        func_001D1790(t3, a1, t2, a3, a4);
    } else {
        func_001D1790(t2, a1, t3, a3, a4);
    }
}

extern void debug_assertMessage();
extern void GetMotionPointer();
extern char D_004C0A88[];
extern char D_004C0A78[];
extern char D_0029F060[];
extern char D_00611958[];
extern char D_00611990[];

void func_001D1ED8(char *a0, int a1) {
    if (*(int *)(a0 + 0xC) >= 0) {
        debug_assertMessage(D_00611958, D_00611990,
            D_0029F060 + *(int *)(a0 + 0xC) * 0x64,
            *(int *)(D_004C0A88 + a1 * 4));
    }
    GetMotionPointer(a0, *(int *)(D_004C0A78 + a1 * 4));
}

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

extern int D_004C0A98[];

typedef struct {
    char _pad0[0x134];
    int  f_134;
    char _pad1[0x190 - 0x138];
} LodEnt; /* stride 0x190 */
extern LodEnt D_0055DA10[];

void func_001D2180(void)
{
    int i;
    for (i = 0; i <= 0x43F; i++) {
        if (D_0055DA10[i].f_134 == 4) {
            D_004C0A98[i] = 0;
        }
    }
    D_0062C210 = 0;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_004C0A88;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00611A10;  /* stride 0x4 */

/* end struct shapes */
