/* src/cod/1453D0.c — func_002453D0 */

void func_002453D0(void)
{
    *(volatile int *)0x1000F000 = 4;
    while ((*(volatile int *)0x1000F000 & 4) == 0) {
    }
    *(volatile int *)0x1000F000 = 4;
}
