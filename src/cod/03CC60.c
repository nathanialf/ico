void func_0013CC60(short *p) {
    *(volatile short *)p = 0;
    __asm__ __volatile__("" : : "r"(p) : "memory");
    p[1] = 0;
}
