void func_002358F8(int x) {
    volatile int local = x;
    __asm__ __volatile__("" : : "r"(local) : "memory");
}
