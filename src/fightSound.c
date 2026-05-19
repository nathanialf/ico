/* src/fightSound.c — __FILE__ anchor at .rodata 0x0055AE88 */

#include "include_asm.h"
#include "regpin.h"

/* D_00632784 is gp_rel-reached by func_00191F50; D_00632788/90 sit in
 * the same neighborhood so extern them too (memory lit4_gp_rel_extern). */
extern int D_00632784;
extern char D_00632788[8];
extern const char D_00632790[8];

__attribute__((section(".rodata.0x0055AE88"))) const char D_0055AE88[24] = "src/fightSound.c";

extern int D_00632780;
extern int D_006D0D20[];
extern void func_00141E00(int a0);

INCLUDE_ASM("asm/nonmatchings/src/fightSound", func_00191D70);
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
