int func_001010C8(int a0)
{
    while (*(volatile int *)0x1000F130 & 0x8000) {}
    *(volatile unsigned char *)0x1000F180 = (unsigned char)a0;
    return a0;
}
