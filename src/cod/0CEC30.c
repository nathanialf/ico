/* src/cod/0CEC30.c — func_001CEC30 */

extern char D_0061D560[];

int func_001CEC30(char *self)
{
    char *p = *(char **)(*(char **)(self + 0x15C) + 0x800);
    int idx = *(int *)(p + 8);
    int new_var = 3;
    char *new_var3 = D_0061D560;
    unsigned int *new_var2 = (unsigned int *)((new_var3 + (idx * 0x14)) + 0x10);
    return ((*new_var2) >> 2) & new_var;
}
