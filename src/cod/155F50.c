extern unsigned int D_005524E4[100];
extern unsigned char D_00552DC8[];

void func_00255F50(unsigned int a0)
{
    *(volatile unsigned int *)0x10002000 = a0;
    D_005524E4[0] = ((unsigned int *)D_00552DC8)[a0 >> 28];
}
