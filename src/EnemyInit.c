/* src/EnemyInit.c — __FILE__ anchor at .rodata 0x0061AC70 */

#include "matching.h"
#include "include_asm.h"
#include "regpin.h"

/* sdata defs live in the gitignored EnemyInit_data.c sidecar — keeping
 * them out of this TU's .o lets ee-gcc emit %gp_rel for func_001FBC48
 * (per memory lit4_gp_rel_extern). */
extern char D_00633828[8];
extern const char D_00633830[8];

__attribute__((section(".rodata.0x0061AC70"))) const char D_0061AC70[16] = "src/EnemyInit.c";

/* String rodata migrated from EnemyInit_data.c */
__attribute__((section(".rodata.0x0061AC80"))) const char D_0061AC80[16] = "isys:null GObj\n";
__attribute__((section(".rodata.0x0061AC90"))) const char D_0061AC90[16] = "camera gop:%x\n";
__attribute__((section(".rodata.0x0061ACA0"))) const char D_0061ACA0[16] = "first entry\n";
__attribute__((section(".rodata.0x0061ACB0"))) const char D_0061ACB0[24] = "entry into head\n";
__attribute__((section(".rodata.0x0061ACC8"))) const char D_0061ACC8[24] = "entry into tail\n";
__attribute__((section(".rodata.0x0061ACE0"))) const char D_0061ACE0[24] = "LinkCameraDL in\n";
__attribute__((section(".rodata.0x0061ACF8"))) const char D_0061ACF8[24] = "LinkCameraDL out\n";

extern int D_004C7710[];
extern int D_00710FA0[];
extern int *D_006321D8;
extern void func_001A6E28();
extern void func_001FBFC8();
extern int func_001FC048(int a0, int a1);

int func_001FBC18(void)
{
    int idx = D_004C7710[0];
    int adj_cur = D_004C7710[4] - 0x80000;
    int end_off = (D_004C7710 + idx)[1];
    return (end_off - adj_cur) >> 4;
}

INCLUDE_ASM("asm/nonmatchings/src/EnemyInit", func_001FBC48);

int func_001FBF88(int idx, int sub_idx)
{
    register int factor REG("$4");
    if (idx < 0 || idx >= *(int *)D_00633828) return 0;
    factor = 0x6C;
    return *(int *)((char *)D_00710FA0 + idx * factor + sub_idx * 4);
}

INCLUDE_ASM("asm/nonmatchings/src/EnemyInit", func_001FBFC8);

void func_001FC040(int a0, int a1, int a2, int a3)
{
    func_001FBFC8(a0, a1, a2, a3);
}

INCLUDE_ASM("asm/nonmatchings/src/EnemyInit", func_001FC048);

void func_001FC168(int a0, int a1)
{
    func_001FBFC8(a0);
    return func_001FC048(a0, a1);
}

INCLUDE_ASM("asm/nonmatchings/src/EnemyInit", func_001FC1A0);

void func_001FC220(int *self, int a1, int a2, int a3, int *t0)
{
    register int *t1 REG("$9") = self;
    int v34, v44;
    if (t0 == 0) {
        func_001A6E28(D_0061AC80);
        return;
    }
    MATERIALIZE(t1);
    t1[0x13] = a2;
    t1[0x14] = a3;
    t1[0x12] = a1;
    *((unsigned char *)t1 + 0x40) = *((unsigned char *)t0 + 0x40);
    t1[0xE] = (int)t0;
    v34 = t0[0xD];
    v44 = t0[0x11];
    t1[0xD] = v34;
    t0[0xD] = (int)t1;
    t1[0x11] = v44;
    if (t1[0xD] == 0) {
        D_006321D8 = t1;
    }
}
