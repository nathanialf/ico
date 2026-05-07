void func_00133460(int a0, int a1)
{
    register int v __asm__("$2") = *(int *)(a0 + 0x108);
    v = (v & -0x11) | ((a1 & 1) << 4);
    *(int *)(a0 + 0x108) = v;
}
