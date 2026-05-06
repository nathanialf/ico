void func_0019E4F8(int *p) {
    *(volatile int *)(p + 3) = 0;
    *(volatile int *)(p + 2) = 0;
    __asm__ __volatile__(".set noreorder\n\t.set reorder" : : : "memory");
}
