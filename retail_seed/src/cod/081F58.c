/* src/cod/081F58.c — func_00181F58 */

extern char D_0028A890[];
extern void func_001918A8(void);

void func_00181F58(void)
{
    char *new_var;
    char *p = D_0028A890;
    char *q;
    int i = 0x13;
    *((int *) (p + 0)) = 0;
    *((int *) (p + 0x4)) = 0;
    new_var = p;
    q = new_var + 0x23C;
    *((int *) (p + 0xC)) = 0;
    *((int *) (p + 0x10)) = 0;
    do {
        *((int *) q) = 0;
        i--;
        q -= 0x1C;
    } while (i >= 0);
    *((int *) (new_var + 0x8)) = 0;
    *((short *) (new_var + 0x24)) = (short) (-1);
    *((int *) (new_var + 0x14)) = 0;
    do { } while (0);
    *((short *) (new_var + 0x1C)) = 0;
    func_001918A8();
}
