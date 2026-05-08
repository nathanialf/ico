void func_0023EFB8(unsigned int a0)
{
    *(volatile int *)0x1000A030 = a0 & 0x0FFFFFFF;
    *(volatile int *)0x1000A020 = 0;
    *(volatile int *)0x1000A000 = 0x105;
}
