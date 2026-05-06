int func_001F42D0(char *self) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    *(int *)(p + 0xA0) = 0;
    return 1;
}
