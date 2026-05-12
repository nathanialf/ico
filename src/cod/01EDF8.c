/* src/cod/01EDF8.c — func_0011EDF8 */

extern void func_00118E88(int);

void func_0011EDF8(char *a0)
{
    int *p820 = *(int **)(a0 + 0x820);
    if (*((signed char *)p820 + 0x2F) != 0) {
        return func_00118E88(3);
    }
    {
        int *p844 = *(int **)(a0 + 0x844);
        if (*(int *)((char *)p844 + 0xF0) == 0) {
            return func_00118E88(1);
        }
    }
    return func_00118E88(2);
}
