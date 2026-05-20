/* src/candle.c — __FILE__ anchor at .rodata 0x00618858 */

#include "include_asm.h"

__attribute__((section(".rodata.0x00618858"))) const char D_00618858[16] = "src/candle.c";

/* String rodata migrated from candle_data.c */
__attribute__((section(".rodata.0x00618900"))) const char D_00618900[24] = "No more weights... \n";
__attribute__((section(".rodata.0x00618918"))) const char D_00618918[24] = "Illegal weight number\n";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "飛び中の敵があまりにフレーム数のかかるRAYを飛ばしたので無効にしました.
" */
__attribute__((section(".rodata.0x00618890"))) const char D_00618890[80] = "\310\364\244\323\303\346\244\316\305\250\244\254\244\242\244\336\244\352\244\313\245\325\245\354\241\274\245\340\277\364\244\316\244\253\244\253\244\353RAY\244\362\310\364\244\320\244\267\244\277\244\316\244\307\314\265\270\372\244\313\244\267\244\336\244\267\244\277.\n";

extern void func_0010ECD8(void);
extern void func_0010ECA0(int s);

extern int D_00632010;
extern unsigned char D_00618868[];
extern unsigned int D_00276140[];

extern int func_0013A0F8(int a0, int a1, const char *a2, int a3);
extern int func_00105278(void);
extern void func_00105F20(int p, int q);
extern void func_00105308(int p, float a, float b, float c);
extern int func_001E8B48(int a, int b, unsigned int *c);
extern void func_001A6E28(unsigned char *fmt);

int func_001C2FE8(void)
{
    return 0;
}

int func_001C2FF0(int *a0, int a1)
{
    int *sub = (int *)a0[0x15C / 4];
    int count = sub[2];
    int *ret;
    int i;

    if (count >= 2) {
        ret = (int *)func_0013A0F8(D_00632010, count * 8, D_00618858, 0x18);
        if (sub[2] > 0) {
            i = 0;
            do {
                int p1 = func_00105278();
                func_00105F20(p1, sub[3] + i * 0x40);
                func_00105308(p1, 0.0f, -40.0f, 0.0f);
                ret[i * 2] = func_001E8B48(4, func_00105278() + 0x30, D_00276140);
                ret[i * 2 + 1] = 0;
                i++;
            } while (i < sub[2]);
        }
    } else {
        ret = (int *)func_0013A0F8(D_00632010, 8, D_00618858, 0x23);
        ret[0] = func_001E8B48(4, a1, D_00276140);
        ret[1] = 0;
    }
    func_001A6E28(D_00618868);
    return (int)ret;
}

void func_001C3130(int a0)
{
    int s0 = *(int *)(a0 + 0x15C);
    if (*(int *)(s0 + 0x74)) {
        func_0010ECD8();
        func_0010ECA0(s0);
    }
}
