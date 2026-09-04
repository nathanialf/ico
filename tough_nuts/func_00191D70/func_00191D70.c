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
extern void __assert(const char *file, int line, const char *fmt);
extern void func_00191D70(void);

extern int D_00631AE4;
extern int D_00631AE8;
extern int D_00632F7C;
extern int D_00274EC0[];
extern int func_00143CD0(void *p);
extern int func_0014B2F0(int a, int b);
extern void func_00141C28(void *p, int a, int b, int c, int d);
extern void func_00140B60(int a, int b);

void func_00191D70(void)
{
    int buf;
    int flag = 0;
    register int one REG("$18");

    buf = 0x110001;
    D_006D0D20[0] = func_00143CD0(&buf);
    if (D_006D0D20[0] != 0) goto L_DC4;
    D_006D0D20[1] = 0;
    if (D_00632780 == 1) return;
L_DC4:
    if (D_00274EC0[6] != 0) return;
    if (D_00274EC0[5] != 0) { *(int *)D_00632788 = 0; goto L_E48; }
    one = 1;
    if (D_00632780 == one) goto L_E44;
    if (D_00631AE4 != 0) {
        flag = 0;
        if (func_0014B2F0(D_00631AE4, 0xF) != 0) flag = one;
    }
    if (D_00274EC0[6] != 0) goto L_E4C;
    *(int *)D_00632788 = 0;
    if (D_00631AE8 != 0) {
        if (func_0014B2F0(D_00631AE8, 9) != 0) goto L_E3C;
    }
    if (D_00632F7C == 0) goto L_E4C;
L_E3C:
    *(int *)D_00632788 = 1;
    goto L_E4C;
L_E44:
    *(int *)D_00632788 = 0;
L_E48:
    flag = 0;
L_E4C:
    if (D_006D0D20[0] != 0) goto L_EAC;
    if (flag != 0) goto L_E6C;
    if (*(int *)D_00632788 == 0) goto L_EA0;
L_E6C:
    if (D_00274EC0[6] != 0) goto L_EA4;
    func_00141C28(&D_006D0D20[2], 2, 1, 2, 0);
    if (D_006D0D20[5] != 0) D_00632784 = 1;
L_EA0:
L_EA4:
    if (D_006D0D20[0] == 0) return;
L_EAC:
    {
        int amt = (D_00632780 == 1) ? 0x400 : 0x60;
        if (flag == 0) {
            if (*(int *)D_00632788 == 0) {
                int v = D_006D0D20[1] - amt;
                D_006D0D20[1] = v;
                if (v < 0) D_006D0D20[1] = 0;
                goto L_F0C;
            }
        }
        {
            int v = D_006D0D20[1] + amt;
            D_006D0D20[1] = v;
            if (v >= 0x1801) D_006D0D20[1] = 0x1800;
        }
    }
L_F0C:
    func_00140B60(D_006D0D20[0], D_006D0D20[1]);
    if (D_006D0D20[1] != 0) return;
    D_00632784 = 2;
}

/* func_00191F50: parked (tough_nuts/). rc=3 reorg b-delay-fill floor —
 * dbr steals the file la-%lo into the two goto-b delay slots where the ROM
 * copies the redundant line const (a1=#255). Not source-reachable without
 * widening the file %hi live range (reg-pins disallowed; no asm goto in
 * gcc 2.9). Full analysis + clean-C seed in tough_nuts/func_00191F50/. */
INCLUDE_ASM("asm/nonmatchings/src/fightSound", func_00191F50);

int func_00192040(void)
{
    register int v REG("$2") = 1;
    D_00632780 = v;
    return v;
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
