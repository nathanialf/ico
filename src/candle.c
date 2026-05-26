/* src/candle.c — __FILE__ anchor at .rodata 0x00618858 */

#include "include_asm.h"

const char D_00618858[16] = "src/candle.c";

/* String rodata migrated from candle_data.c */
/* EUC-JP: "飛び中の敵があまりにフレーム数のかかるRAYを飛ばしたので無効にしました.\n" */
const char D_00618890[80] = "\310\364\244\323\303\346\244\316\305\250\244\254\244\242\244\336\244\352\244\313\245\325\245\354\241\274\245\340\277\364\244\316\244\253\244\253\244\353RAY\244\362\310\364\244\320\244\267\244\277\244\316\244\307\314\265\270\372\244\313\244\267\244\336\244\267\244\277.\n";

/* String rodata migrated from candle_data.c */
const char D_00618900[24] = "No more weights... \n";

/* String rodata migrated from candle_data.c */
const char D_00618918[24] = "Illegal weight number\n";

extern void func_0010ECD8(void);
extern void func_0010ECA0(int s);

int func_001C2FE8(void)
{
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/candle", func_001C2FF0);

void func_001C3130(int a0)
{
    int s0 = *(int *)(a0 + 0x15C);
    if (*(int *)(s0 + 0x74)) {
        func_0010ECD8();
        func_0010ECA0(s0);
    }
}
