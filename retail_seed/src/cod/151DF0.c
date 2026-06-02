int func_00251DF0(char *self, int val) {
    char *sub = *(char **)(self + 0x40);
    int prev = *(int *)(sub + 0xE8);
    *(int *)(sub + 0xE8) = val;
    return prev;
}
