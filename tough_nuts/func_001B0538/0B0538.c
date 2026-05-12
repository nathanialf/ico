/* src/cod/0B0538.c — func_001B0538 */

extern int D_00706110[];
extern int D_00633E6C;

void func_001B0538(void)
{
    int *p = D_00706110;
    int i;
    p = (int *)((char *)p + 0x3A0);
    for (i = 0x1D; i >= 0; i--) {
        *p = 0;
        p = (int *)((char *)p - 0x20);
    }
    D_00633E6C = 0;
}
