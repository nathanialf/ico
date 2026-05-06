void func_0014B330(char *self, unsigned int x, float f) {
    char *sub = *(char **)(self + 0x164);
    char *p = *(char **)(sub + 0x670);
    if (x >= *(unsigned int *)(p + 0x54)) {
        *(unsigned int *)(p + 0x54) = x;
        __asm__ __volatile__("" : : : "memory");
        *(float *)(p + 0x58) = f;
    }
}
