/* src/cod/0CEC30.c — func_001CEC30 */

extern char D_0061D560[];

int func_001CEC30(char *self)
{
    char *p = *(char **)(*(char **)(self + 0x15C) + 0x800);
    int idx = *(int *)(p + 8);
    unsigned int val = *(unsigned int *)((D_0061D560 + idx * 0x14) + 0x10);
    return (val >> 2) & 3;
}
