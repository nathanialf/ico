int func_00244958(int a0)
{
    int old = *(volatile int *)0x1000E060;
    if ((unsigned int)a0 != 0xFFFFFFFF) {
        *(volatile int *)0x1000E060 = a0;
    }
    return old;
}
