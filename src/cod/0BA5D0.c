void func_001BA5D0(char *self, int val) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    *(int *)(p + 0x278) = val;
}
