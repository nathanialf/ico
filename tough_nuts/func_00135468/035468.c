/* src/cod/035468.c — func_00135468 */

extern void func_00136088(char *a0);

void func_00135468(char *base)
{
    char *p = base + 0x18000;
    *(int *)(p + 0x78) = -1;
    *(int *)(p + 0x88) = 0;
    *(int *)(p + 0x48) = 0;
    *(long long *)(p + 0x68) = 0;
    *(long long *)(p + 0x70) = 0;
    *(int *)(p + 0x50) = 0;
    *(int *)(p + 0x4C) = 0;
    *(int *)(p + 0x54) = 0;
    *(int *)(p + 0x58) = 0;
    *(int *)(p + 0x7C) = 0;
    *(int *)(p + 0x84) = 0;
    *(int *)(p + 0x80) = 0;
    return func_00136088(base + 0x18098);
}
