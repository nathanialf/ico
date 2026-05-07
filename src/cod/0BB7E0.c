int func_001BB7E0(int *a0)
{
    register int *v1 __asm__("$3") = (int *)a0[0x164 / 4];
    int v;
    __asm__ __volatile__("lwu %0, 0x1C(%1)" : "=r"(v) : "r"(v1));
    __asm__ __volatile__("dsll32 %0, %0, 0" : "+r"(v));
    __asm__ __volatile__("dsra32 %0, %0, 0" : "+r"(v));
    return (v & 1) ^ 1;
}
