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

INCLUDE_ASM("asm/nonmatchings/src/fightSound", func_00191D70);

void func_00191F50(void) {
    int d = D_00632784;
    if (d == 1) goto case_1;
    if (d < 2) {
        if (d == 0) goto case_0;
        goto default_case;
    } else {
        if (d == 2) goto case_2;
        goto default_case;
    }
case_0:
    func_00191D70();
    return;
case_1:
    {
        int *p = &D_006D0D28[0];
        int ret = func_00141D18(p);
        p[-2] = ret;
        if ((unsigned int)ret == 0xFFFFFFFFu) return;
        if (ret != 0) {
            func_00140710(((int *)ret)[11]);
        }
        D_00632784 = 0;
        return;
    }
case_2:
    if (D_006D0D20[0] != 0) {
        func_00141E00(D_006D0D20[0]);
    }
    D_006D0D20[0] = 0;
    D_00632784 = 0;
    return;
default_case:
    func_001AD768(D_0055AE88);
    func_00263FF0(D_0055AE88, 0xFF, D_00632790);
}

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
