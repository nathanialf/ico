/* src/cod/0918A8.c — func_001918A8 */

extern int D_00632778;
extern int D_00632774;
extern int D_00633DAC;
extern int D_00633DB0;
extern int D_006D0710[];

void func_001918A8(void)
{
    int *p = D_006D0710;
    int i;
    D_00632778 = 0;
    D_00632774 = 0;
    D_00633DAC = 0;
    p = (int *)((char *)p + 0x37C);
    D_00633DB0 = 0;
    i = 0x1F;
    do {
        *p = 0;
        p = (int *)((char *)p - 0x1C);
        i--;
    } while (i >= 0);
}
