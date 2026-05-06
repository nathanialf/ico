extern int D_00632A04;

void func_001A2E10(void) {
    volatile char buf[256];
    D_00632A04 = -1;
    __asm__ __volatile__("" : : "r"(buf) : "memory");
}
