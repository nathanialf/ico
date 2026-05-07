float func_002608E0(float x)
{
    register int i __asm__("$3");
    register int mask __asm__("$2");
    register float r __asm__("$f0");
    __asm__ volatile("mfc1 %0, $f12" : "=r"(i));
    __asm__ volatile("lui %0, 0x7fff" : "=r"(mask));
    __asm__ volatile("ori %0, %0, 0xffff" : "+r"(mask));
    __asm__ volatile("and %0, %0, %1" : "+r"(i) : "r"(mask));
    __asm__ volatile("mtc1 %1, %0" : "=f"(r) : "r"(i));
    return r;
}
