/* src/cod/002790.c — func_00102790 */

extern void func_0010DDB8(int a0, int a1, char *a2);
extern void func_0010D830(int a0, char *a1);

void func_00102790(int a0, char *a1)
{
    char *a2 = a1;
    int *p = (int *)a2;
    if (p[0] == 0) {
        return func_0010D830(a0, a2 + 0xD0);
    }
    {
        int *p15c = *(int **)(p[0] + 0x15C);
        int idx_val = p[1];
        char *p_d0 = a2 + 0xD0;
        int addr = (int)((char *)p15c + 0x10) + idx_val * 16;
        ((void)0);
        return func_0010DDB8(a0, addr, p_d0);
    }
}
