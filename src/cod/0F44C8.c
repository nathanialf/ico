void func_001F44C8(char *self) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    int val = *(int *)(sub + 0x74);
    char *q = *(char **)(p + 0x5C);
    *(int *)(q + 0x16C) = val;
}
