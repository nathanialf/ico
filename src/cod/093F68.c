void func_00193F68(short *p) {
    *(volatile short *)(p + 1) = 1;
    __asm__ __volatile__("" : : "r"(p) : "memory");
    p[0] = 1;
}
