/* src/cod/154CF8.c — func_00254CF8 */

void func_00254CF8(int a0)
{
    volatile int *reg = (volatile int *)0x10002010;
    *reg = (*reg & 0xFF7FFFFF) | (a0 << 23);
}
