/* src/fightSound.c — __FILE__ anchor at .rodata 0x0055AE88 */

#include "include_asm.h"
#include "regpin.h"

/* D_00632784 is gp_rel-reached by func_00191F50; D_00632788/90 sit in
 * the same neighborhood so extern them too (memory lit4_gp_rel_extern). */
extern int D_00632784;
extern char D_00632788[8];
extern const char D_00632790[];

const char D_0055AE88[24] = "src/fightSound.c";

extern int D_00632780;
extern int D_006D0D20[];
extern int D_006D0D28[];
extern void func_00141E00(int a0);
extern int func_00141D18(int *p);
extern void func_00140710(int a0);
extern void func_001AD768(const char *file);
extern void func_00263FF0(const char *file, int line, const char *fmt);
extern void func_00191D70(void);

extern int D_00631AE4;
extern int D_00631AE8;
extern int D_00632F7C;
extern int D_00274EC0[];
extern int func_00143CD0(void *p);
extern int func_0014B2F0(int a, int b);
extern void func_00141C28(void *p, int a, int b, int c, int d);
extern void func_00140B60(int a, int b);

INCLUDE_ASM("asm/nonmatchings/src/fightSound", func_00191D70);

/* func_00191F50: parked (tough_nuts/). rc=3 reorg b-delay-fill floor —
 * dbr steals the file la-%lo into the two goto-b delay slots where the ROM
 * copies the redundant line const (a1=#255). Not source-reachable without
 * widening the file %hi live range (reg-pins disallowed; no asm goto in
 * gcc 2.9). Full analysis + clean-C seed in tough_nuts/func_00191F50/. */
INCLUDE_ASM("asm/nonmatchings/src/fightSound", func_00191F50);

void func_00192040(void)
{
    D_00632780 = 1;
}

void func_00192050(void)
{
    if (D_006D0D20[0] != 0) {
        func_00141E00(D_006D0D20[0]);
        D_006D0D20[0] = 0;
    }
}

void func_00192088(void) {
    D_00632780 = 0;
}

int func_00192090(void) {
    return D_00632780;
}

int func_00192098(void) {
    return D_006D0D20[0];
}
