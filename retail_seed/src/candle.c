/* src/candle.c — __FILE__ anchor at .rodata 0x00618858 */

#include "include_asm.h"
#include "ico/types.h"

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

extern int D_00632010;
extern char D_00618868[];
extern char D_00276140[];
extern int func_0013A0F8(int handle, int size, const char *file, int line);
extern int func_00105278(void);
extern int func_00105F20(int a, int b);
extern void func_00105308(float a, float b, float c);
extern int func_001E8B48(int a, int b, void *c);
extern void func_001A6E28(const char *s);

int func_001C2FF0(int self, int a1)
{
    int *obj = ((GObj *)(self))->p_15C;
    int count = obj[2];
    int *base;
    int i;
    int r;
    if (count < 2) goto error;
    base = (int *)func_0013A0F8(D_00632010, count * 8, D_00618858, 0x18);
    i = 0;
    if (obj[2] > 0) {
        do {
            int t = func_00105278();
            func_00105F20(t, obj[3] + i * 0x40);
            func_00105308(0.0f, -40.0f, 0.0f);
            r = func_00105278();
            r = func_001E8B48(4, r + 0x30, D_00276140);
            base[i * 2] = r;
            base[i * 2 + 1] = 0;
            i++;
        } while (i < obj[2]);
    }
    goto print;
error:
    base = (int *)func_0013A0F8(D_00632010, 8, D_00618858, 0x23);
    r = func_001E8B48(4, a1, D_00276140);
    base[0] = r;
    base[1] = 0;
print:
    func_001A6E28(D_00618868);
    return (int)base;
}

void func_001C3130(int a0)
{
    Sub15C *s0 = ((GObj *)a0)->p_15C;
    if (s0->f_74) {
        func_0010ECD8();
        func_0010ECA0((int)s0);
    }
}
