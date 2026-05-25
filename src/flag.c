/* src/flag.c — __FILE__ anchor at .rodata 0x00618DC8 */

#include "include_asm.h"

const char D_00618DC8[16] = "src/flag.c";

const char D_00618DD8[40] = "SE \033[36m\"%s\"\033[m \244\317\245\355\241\274\245\311\244\265\244\354\244\306\244\244\244\336\244\273\244\363\n";

const char D_00618E58[72] = "\303\355\260\325\241\247\245\316\241\274\245\311\273\330\304\352\244\316\245\342\241\274\245\267\245\347\245\363\245\250\245\325\245\247\245\257\245\310\244\307\245\316\241\274\245\311\244\254\270\253\244\304\244\253\244\352\244\336\244\273\244\363\244\307\244\267\244\277\n";

const char D_00618EC8[16] = "poncho005";

const char D_00618ED8[16] = "g_hair9_d";

const char D_00618EE8[16] = "g_poncho_test03";

extern int D_00632DB4;
extern int D_006333D8;
extern int func_00167528(int a0, int a1);

INCLUDE_ASM("asm/nonmatchings/src/flag", func_001CFA38);
INCLUDE_ASM("asm/nonmatchings/src/flag", func_001CFB58);
INCLUDE_ASM("asm/nonmatchings/src/flag", func_001D00F8);
INCLUDE_ASM("asm/nonmatchings/src/flag", func_001D01E8);

void func_001D03A0(void)
{
    int v0 = D_00632DB4;
    int a0 = D_006333D8;
    if (v0 == 0) {
        return;
    }
    if (a0 == 0) {
        return;
    }
    return func_00167528(a0, 0);
}
