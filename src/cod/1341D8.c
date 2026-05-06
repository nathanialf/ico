void func_002341D8(int x) {
    volatile int local = x;
    __asm__ __volatile__("" : : "r"(local) : "memory");
}
