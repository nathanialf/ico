void func_00229E38(int x) {
    volatile int local = x;
    __asm__ __volatile__("" : : "r"(local) : "memory");
}
