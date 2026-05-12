/* src/cod/155F50.c — func_00255F50 */

extern int D_00552DC8[];
extern int D_005524E4;

void func_00255F50(unsigned int a0)
{
    *(volatile int *)0x10002000 = (int)a0;
    D_005524E4 = D_00552DC8[a0 >> 28];
}
