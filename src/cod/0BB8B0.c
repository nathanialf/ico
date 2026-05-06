void func_001BB8B0(int x) {
    volatile int local = x;
    __asm__ __volatile__("" : : "r"(local) : "memory");
}
