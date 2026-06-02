extern int func_00240B70(void);
extern int D_002A31B8[];

int func_001ADB88(void)
{
    int rc = func_00240B70();
    return (int)((char *)D_002A31B8 + *(int *)(rc + 0xC) * 0x64);
}
