extern int D_006F8EE0[];

void func_001AA5C0(int idx)
{
    int *p = (int *)((char *)D_006F8EE0 + idx * 0xD0 + 0xC8);
    int i;
    for (i = 0x19; i >= 0; i--) {
        *p = 0;
        p = (int *)((char *)p - 8);
    }
}
