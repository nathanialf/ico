void func_00219728(int x) {
    volatile int local = x;
    __asm__ __volatile__("" : : "r"(local) : "memory");
}
