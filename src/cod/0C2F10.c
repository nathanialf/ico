void func_001C2F10(char *self, int val) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    *(int *)(p + 0x40) = val;
}
