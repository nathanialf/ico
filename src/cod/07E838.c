extern void func_00105F00(char *dst, void *src);

void func_0017E838(char *a0, float f12, float f13, float f14)
{
    int local[4];
    *(float *)&local[0] = f12;
    *(float *)&local[1] = f13;
    *(float *)&local[2] = f14;
    local[3] = 0;
    return func_00105F00(*(char **)(a0 + 0x15C) + 0x670, local);
}
